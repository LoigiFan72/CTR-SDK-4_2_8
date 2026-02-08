/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_Compression.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47707 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/assert.h>
#include <nn/cx/cx_Uncompression.h>
#include <nn/cx/cx_Compression.h>
#include "cx_Utility.h"

namespace nn {
namespace cx {

namespace {

//===========================================================================
//  LZ Encoding
//===========================================================================

// Temporary information for LZ high-speed encoding
struct LZCompressInfo
{
    u16     windowPos;                 // Initial position of the history window
    u16     windowLen;                 // Length of the history window
    
    s16    *LZOffsetTable;             // Offset buffer of the history window
    s16    *LZByteTable;               // Pointer to the most recent character history
    s16    *LZEndTable;                // Pointer to the oldest character history
};

void        LZInitTable( LZCompressInfo * info, void *work );
u32         SearchLZ   ( LZCompressInfo * info, const u8 *nextp, u32 remainSize, u16 *offset, u32 maxLength );
void        SlideByte  ( LZCompressInfo * info, const u8 *srcp );
inline void LZSlide    ( LZCompressInfo * info, const u8 *srcp, u32 n );

}   // Namespace


/*---------------------------------------------------------------------------*
  Name:         CompressLZ

  Description:  Performs LZ77 compression.

  Arguments:    srcp:            Pointer to compression source data
                size:            Size of compression source data
                dstp            Pointer to compressed data
                                The buffer must be larger than the size of the compression source data.
                work            Temporary buffer for compression
                                A region for the size of  CX_LZ_FAST_COMPRESS_WORK_SIZE is necessary.

  Returns:      The data size after compression.
                If compressed data is larger than original data, compression is terminated and 0 is returned.
 *---------------------------------------------------------------------------*/
u32 CompressLZImpl(const u8 *srcp, u32 size, u8 *dstp, void *work, bool exFormat)
{
    u32     LZDstCount;                // Number of bytes of compressed data
    u8      LZCompFlags;               // Flag sequence indicating whether there is a compression
    u8     *LZCompFlagsp;              // Point to memory regions storing LZCompFlags
    u16     lastOffset;                // Offset to matching data (the longest matching data at the time) 
    u32     lastLength;                // Length of matching data (the longest matching data at the time)
    u8      i;
    u32     dstMax;
    LZCompressInfo info;               // Temporary LZ compression information
    const u32 MAX_LENGTH = (exFormat)? (0xFFFF + 0xFF + 0xF + 3U) : (0xF + 3U);
    
    NN_ASSERT( ((u32)srcp & 0x1) == 0 );
    NN_ASSERT( work != NULL );
    NN_ASSERT( size > 4 );
    
    if ( size < (1 << 24) )
    {
        *(u32 *)dstp = internal::ConvertEndian( size << 8 | COMPRESSION_LZ | (exFormat? 1 : 0) );  // Data header
        dstp += 4;
        LZDstCount = 4;
    }
    else
    // Use extended header if the size is larger than 24 bits
    {
        *(u32 *)dstp = internal::ConvertEndian( COMPRESSION_LZ | (exFormat? 1U : 0U) );  // Data header
        dstp += 4;
        *(u32 *)dstp = internal::ConvertEndian( size ); // Size extended header
        dstp += 4;
        LZDstCount = 8;
    }
    dstMax = size;
    LZInitTable(&info, work);
    
    while ( size > 0 )
    {
        LZCompFlags = 0;
        LZCompFlagsp = dstp++;         // Destination for storing flag sequence
        LZDstCount++;

        // Because flag sequence is stored as 8-bit data, loop eight times
        for ( i = 0; i < 8; i++ )
        {
            LZCompFlags <<= 1;         // No meaning for the first time (i=0)
            if (size <= 0)
            {
                // When reached the end, quit after shifting flag to the end
                continue;
            }

            if ( (lastLength = SearchLZ( &info, srcp, size, &lastOffset, MAX_LENGTH)) != 0 )
            {
                u32 length;
                // Enable flag if compression is possible
                LZCompFlags |= 0x1;

                if (LZDstCount + 2 >= dstMax)   // Quit on error if size becomes larger than source
                {
                    return 0;
                }
                
                if ( exFormat )
                {
                    if ( lastLength >= 0xFF + 0xF + 3 )
                    {
                        length  = (u32)( lastLength - 0xFF - 0xF - 3 );
                        *dstp++ = (u8)( 0x10 | (length >> 12) );
                        *dstp++ = (u8)( length >> 4 );
                        LZDstCount += 2;
                    }
                    else if ( lastLength >= 0xF + 2 )
                    {
                        length  = (u32)( lastLength - 0xF - 2 );
                        *dstp++ = (u8)( length >> 4 );
                        LZDstCount += 1;
                    }
                    else
                    {
                        length = (u32)( lastLength - 1 );
                    }
                }
                else
                {
                    length = (u32)( lastLength - 3 );
                }
                
                // Divide offset into upper 4 bits and lower 8 bits and store
                *dstp++ = (u8)( length << 4 | (lastOffset - 1) >> 8 );
                *dstp++ = (u8)( (lastOffset - 1) & 0xff);
                LZDstCount += 2;
                LZSlide(&info, srcp, lastLength);
                srcp += lastLength;
                size -= lastLength;
            }
            else
            {
                // No compression
                if (LZDstCount + 1 >= dstMax)       // Quit on error if size becomes larger than source
                {
                    return 0;
                }
                LZSlide(&info, srcp, 1);
                *dstp++ = *srcp++;
                size--;
                LZDstCount++;
            }
        }                              // Completed eight loops
        *LZCompFlagsp = LZCompFlags;   // Store flag series
    }
    
    // 4-byte boundary alignment
    //   Does not include Data0 used for alignment in data size
    i = 0;
    while ( (LZDstCount + i) & 0x3 )
    {
        *dstp++ = 0;
        i++;
    }
    
    return LZDstCount;
}

namespace {

//--------------------------------------------------------
// With LZ77 Compression, searches for the longest matching string from the slide window.
//  Arguments:    startp                 Pointer to starting position of data
//                nextp                  Pointer to data where search will start
//                remainSize             Size of remaining data
//                offset                 Pointer to region storing matched offset
//  Return:    TRUE if matching string is found
//                FALSE if not found.
//--------------------------------------------------------
u32 SearchLZ( LZCompressInfo * info, const u8 *nextp, u32 remainSize, u16 *offset, u32 maxLength )
{
    const u8 *searchp;
    const u8 *headp, *searchHeadp;
    u16     maxOffset = 0;
    u32     currLength = 2;
    u32     tmpLength;
    s32     w_offset;
    s16    *const LZOffsetTable = info->LZOffsetTable;
    const u16 windowPos = info->windowPos;
    const u16 windowLen = info->windowLen;

    if (remainSize < 3)
    {
        return 0;
    }

    w_offset = info->LZByteTable[*nextp];

    while (w_offset != -1)
    {
        if (w_offset < windowPos)
        {
            searchp = nextp - windowPos + w_offset;
        }
        else
        {
            searchp = nextp - windowLen - windowPos + w_offset;
        }

        /* This isn't needed, but it seems to make it a little faster */
        if (*(searchp + 1) != *(nextp + 1) || *(searchp + 2) != *(nextp + 2))
        {
            w_offset = LZOffsetTable[w_offset];
            continue;
        }

        if (nextp - searchp < 2)
        {
            // Since VRAM is 2-byte access (since there are times when data is read from VRAM), the search target data must be set to data that is two bytes before that.
            // 
            // 
            // Because the offset is stored in 12 bits, the value is 4096 or less
            break;
        }
        tmpLength = 3;
        searchHeadp = searchp + 3;
        headp = nextp + 3;

        // Increments the compression size until the data ends or different data is encountered
        while (((u32)(headp - nextp) < remainSize) && (*headp == *searchHeadp))
        {
            headp++;
            searchHeadp++;
            tmpLength++;

            // Because the data length is stored in 4 bits, the value is 18 or less (3 is added)
            if (tmpLength == maxLength)
            {
                break;
            }
        }

        if (tmpLength > currLength)
        {
            // Update the maximum-length offset
            currLength = tmpLength;
            maxOffset = (u16)(nextp - searchp);
            if (currLength == maxLength || currLength == remainSize)
            {
                // This is the longest matching length, so end search
                break;
            }
        }
        w_offset = LZOffsetTable[w_offset];
    }

    if (currLength < 3)
    {
        return 0;
    }
    *offset = maxOffset;
    return currLength;
}

//--------------------------------------------------------
// Initialize the dictionary index
//--------------------------------------------------------
void LZInitTable(LZCompressInfo * info, void *work)
{
    u16     i;
    
    info->LZOffsetTable = (s16*)work;
    info->LZByteTable   = (s16*)( (u32)work + 4096 * sizeof(s16)         );
    info->LZEndTable    = (s16*)( (u32)work + (4096 + 256) * sizeof(s16) );
    
    for ( i = 0; i < 256; i++ )
    {
        info->LZByteTable[i] = -1;
        info->LZEndTable [i]  = -1;
    }
    info->windowPos = 0;
    info->windowLen = 0;
}

//--------------------------------------------------------
// Slide the dictionary 1 byte
//--------------------------------------------------------
void SlideByte(LZCompressInfo * info, const u8 *srcp)
{
    s16     offset;
    u8      in_data = *srcp;
    u16     insert_offset;

    s16    *const LZByteTable   = info->LZByteTable;
    s16    *const LZOffsetTable = info->LZOffsetTable;
    s16    *const LZEndTable    = info->LZEndTable;
    const u16 windowPos = info->windowPos;
    const u16 windowLen = info->windowLen;

    if (windowLen == 4096)
    {
        u8      out_data = *(srcp - 4096);
        if ((LZByteTable[out_data] = LZOffsetTable[LZByteTable[out_data]]) == -1)
        {
            LZEndTable[out_data] = -1;
        }
        insert_offset = windowPos;
    }
    else
    {
        insert_offset = windowLen;
    }

    offset = LZEndTable[in_data];
    if (offset == -1)
    {
        LZByteTable[in_data] = (s16)insert_offset;
    }
    else
    {
        LZOffsetTable[offset] = (s16)insert_offset;
    }
    LZEndTable[in_data] = (s16)insert_offset;
    LZOffsetTable[insert_offset] = -1;

    if (windowLen == 4096)
    {
        info->windowPos = (u16)((windowPos + 1) % 0x1000);
    }
    else
    {
        info->windowLen++;
    }
}

//--------------------------------------------------------
// Slide the dictionary n bytes
//--------------------------------------------------------
inline void LZSlide(LZCompressInfo * info, const u8 *srcp, u32 n)
{
    u32     i;

    for (i = 0; i < n; i++)
    {
        SlideByte(info, srcp++);
    }
}

}   // Namespace


//===========================================================================
//  Run-Length Encoding
//===========================================================================

/*---------------------------------------------------------------------------*
  Name:         CompressRL

  Description:  Performs run-length compression.

  Arguments:    srcp:            Pointer to compression source data
                size:            Size of compression source data
                dstp            Pointer to compressed data
                                The buffer must be larger than the size of the compression source data.

  Returns:      The data size after compression.
                If compressed data is larger than original data, compression is terminated and 0 is returned.
 *---------------------------------------------------------------------------*/
u32 CompressRL(const u8 *srcp, u32 size, u8 *dstp)
{
    u32 RLDstCount;                    // Number of bytes of compressed data
    u32 RLSrcCount;                    // Processed data volume of the compression target data (in bytes)
    u8  RLCompFlag;                    // 1 if performing run-length encoding
    u8  runLength;                     // Run length
    u8  rawDataLength;                 // Length of data not run
    u32 i;
    
    const u8 *startp;                  // Point to the start of compression target data for each process loop
    
    NN_ASSERT( srcp != NULL );
    NN_ASSERT( dstp != NULL );
    NN_ASSERT( size > 4     );
    
    //  Data header        (The size after decompression)
    // To create the same output data as Nitro, work on on the endian.
    if ( size < (1 << 24) )
    {
        *(u32 *)dstp = internal::ConvertEndian(size << 8 | COMPRESSION_RL);       // Data header
        RLDstCount   = 4;
    }
    else
    // Use extended header if the size is larger than 24 bits
    {
        *(u32 *)dstp       = internal::ConvertEndian(COMPRESSION_RL);       // Data header
        *(u32 *)(dstp + 4) = internal::ConvertEndian(size);                  // Extend header size
        RLDstCount         = 8;
    }
    RLSrcCount = 0;
    rawDataLength = 0;
    RLCompFlag = 0;

    while (RLSrcCount < size)
    {
        startp = &srcp[RLSrcCount];    // Set compression target data

        for (i = 0; i < 128; i++)      // Data volume that can be expressed in 7 bits is 0 to 127
        {
            // Reach the end of the compression target data
            if (RLSrcCount + rawDataLength >= size)
            {
                rawDataLength = (u8)(size - RLSrcCount);
                break;
            }

            if (RLSrcCount + rawDataLength + 2 < size)
            {
                if (startp[i] == startp[i + 1] && startp[i] == startp[i + 2])
                {
                    RLCompFlag = 1;
                    break;
                }
            }
            rawDataLength++;
        }

        // Store data that will not be encoded
        // If the 8th bit of the data length storage byte is 0, the data sequence that is not encoded.
        // The data length is x - 1, so 0-127 becomes 1-128.
        if (rawDataLength)
        {
            if (RLDstCount + rawDataLength + 1 >= size) // Quit on error if size becomes larger than source
            {
                return 0;
            }
            dstp[RLDstCount++] = (u8)(rawDataLength - 1);       // Store "data length - 1" (7 bits)
            for (i = 0; i < rawDataLength; i++)
            {
                dstp[RLDstCount++] = srcp[RLSrcCount++];
            }
            rawDataLength = 0;
        }

        // Run-Length Encoding
        if (RLCompFlag)
        {
            runLength = 3;
            for (i = 3; i < 128 + 2; i++)
            {
                // Reach the end of the data for compression
                if (RLSrcCount + runLength >= size)
                {
                    runLength = (u8)(size - RLSrcCount);
                    break;
                }

                // If run is interrupted
                if (srcp[RLSrcCount] != srcp[RLSrcCount + runLength])
                {
                    break;
                }
                // Run continues
                runLength++;
            }

            // If the 8th bit of the data length storage byte is 1, the data sequence that is encoded
            if (RLDstCount + 2 >= size) // Quit on error if size becomes larger than source
            {
                return 0;
            }
            dstp[RLDstCount++] = (u8)(0x80 | (runLength - 3));  // Add 3, and store from 3 to 130
            dstp[RLDstCount++] = srcp[RLSrcCount];
            RLSrcCount += runLength;
            RLCompFlag = 0;
        }
    }

    // 4-byte boundary alignment
    //   Does not include Data0 used for alignment in data size
    i = 0;
    while ((RLDstCount + i) & 0x3)
    {
        dstp[RLDstCount + i] = 0;
        i++;
    }
    return RLDstCount;
}


//===========================================================================
//  Huffman encoding
//===========================================================================
#define HUFF_END_L  0x80
#define HUFF_END_R  0x40

namespace {

struct HuffData
{
    u32 Freq;                          // Frequency of occurrence
    u16 No;                            // Data number
    s16 PaNo;                          // Parent number 
    s16 ChNo[2];                       // Child Number (0: left side, 1: right side)
    u16 PaDepth;                       // Parent node depth
    u16 LeafDepth;                     // Depth to leaf
    u32 HuffCode;                      // Huffman code
    u8  Bit;                           // Node's bit data
    u8  _padding;
    u16 HWord;                         // For each intermediate node, the amount of memory needed to store in HuffTree the subtree that has that node as its root
};
                                       // Total of 24 bytes

struct HuffTreeCtrlData
{
    u8  leftOffsetNeed;                // 1 if offset to left child node is required
    u8  rightOffsetNeed;               // 1 if an offset to the right child node is required
    u16 leftNodeNo;                    // The left child node number
    u16 rightNodeNo;                   // Right child node number
};
                                       // Total of 6 bytes

// Structure of the Huffman work buffer
struct HuffCompressionInfo
{
    HuffData         *huffTable;    //  huffTable[ 512 ];      12288B
    u8               *huffTree;     //  huffTree[ 256 * 2 ];     512B
    HuffTreeCtrlData *huffTreeCtrl; //  huffTreeCtrl[ 256 ];    1536B
    u8               huffTreeTop;   //  
    u8               padding_[3];   //  
};
                                    // Total is 14340B

void HuffInitTable( HuffCompressionInfo* info, void* work, u16 dataNum );
void HuffCountData( HuffData* table, const u8 *srcp, u32 size, u8 bitSize );
u16  HuffConstructTree( HuffData* table, u32 dataNum );
u32  HuffConvertData( const HuffData *table, const u8* srcp, u8* dstp, u32 srcSize, u32 maxSize, u8 bitSize );

void HuffAddParentDepthToTable( HuffData *table, u16 leftNo, u16 rightNo );
void HuffAddCodeToTable       ( HuffData *table, u16 nodeNo, u32 paHuffCode );
u8   HuffAddCountHWordToTable ( HuffData *table, u16 nodeNo );

void HuffMakeHuffTree             ( HuffCompressionInfo* info, u16 rootNo );
void HuffMakeSubsetHuffTree       ( HuffCompressionInfo* info, u16 huffTreeNo, u8 rightNodeFlag );
u8   HuffRemainingNodeCanSetOffset( HuffCompressionInfo* info, u8  costHWord );
void HuffSetOneNodeOffset         ( HuffCompressionInfo* info, u16 huffTreeNo, u8 rightNodeFlag );

}   // Namespace


/*---------------------------------------------------------------------------*
  Name:         CompressHuffman

  Description:  Performs Huffman compression.

  Arguments:    srcp:            Pointer to compression source data
                size:            Size of compression source data
                dstp            Pointer to compressed data
                                The buffer must be larger than the size of the compression source data.
                huffBitSize     The number of bits to encode
                work            Work buffer for Huffman compression

  Returns:      The data size after compression.
                If compressed data is larger than original data, compression is terminated and 0 is returned.
 *---------------------------------------------------------------------------*/
u32 CompressHuffman( const u8 *srcp, u32 size, u8 *dstp, u8 huffBitSize, void *work )
{
    u32 huffDstCount;                  // Number of bytes of compressed data
    s32 i;
    u16 rootNo;                        // Binary tree's root number
    u16 huffDataNum  = (u16)(1 << huffBitSize);      // 8->256, 4->16
    u32 tableOffset;
    HuffCompressionInfo info;
    
    NN_ASSERT( srcp != NULL );
    NN_ASSERT( dstp != NULL );
    NN_ASSERT( huffBitSize == 4 || huffBitSize == 8 );
    NN_ASSERT( work != NULL );
    NN_ASSERT( ((u32)work & 0x3) == 0 );
    NN_ASSERT( size > 4 );
    
    // Initialize table
    HuffInitTable( &info, work, huffDataNum );
    
    // Check frequency of occurrence
    HuffCountData( info.huffTable, srcp, size, huffBitSize );
    
    // Create tree table
    rootNo = HuffConstructTree( info.huffTable, huffDataNum );
    
    // Create HuffTree
    HuffMakeHuffTree( &info, rootNo );
    info.huffTree[0] = --info.huffTreeTop;
    
    // Data header
    // To create the same compression data as Nitro, work on the endian.
    if ( size < (1 << 24) )
    {
        *(u32 *)dstp = internal::ConvertEndian(size << 8 | COMPRESSION_HUFFMAN | huffBitSize);
        tableOffset  = 4;
    }
    else
    // Use extended header if the size is larger than 24 bits
    {
        *(u32 *)dstp       = internal::ConvertEndian( (u32)(COMPRESSION_HUFFMAN | huffBitSize) );
        *(u32 *)(dstp + 4) = internal::ConvertEndian( size );
        tableOffset        = 8;
    }
    huffDstCount = tableOffset;
    
    if ( huffDstCount + (info.huffTreeTop + 1) * 2 >= size )   // Quit on error if size becomes larger than source
    {
        return 0;
    }
    
    for ( i = 0; i < (u16)( (info.huffTreeTop + 1) * 2 ); i++ )  // Tree table
    {
        dstp[ huffDstCount++ ] = ((u8*)info.huffTree)[ i ];
    }
    
    // 4-byte boundary alignment
    //   Data0 used for alignment is included in data size (as per the decoder algorithm)
    while ( huffDstCount & 0x3 )
    {
        if ( huffDstCount & 0x1 )
        {
            info.huffTreeTop++;
            dstp[ tableOffset ]++;
        }
        dstp[ huffDstCount++ ] = 0;
    }
    
    // Data conversion via the Huffman table
    {
        u32 convSize = HuffConvertData( info.huffTable, srcp, &dstp[ huffDstCount ], size, size - huffDstCount, huffBitSize );
        if ( convSize == 0 )
        {
            // Compression fails because the compressed data is larger than the source
            return 0;
        }
        huffDstCount += convSize;
    }
    
    return huffDstCount;
}

namespace {

/*---------------------------------------------------------------------------*
  Name:         HuffInitTable
  Description:  Initializes the Huffman table.
  Arguments:    table   
                size    
  Returns:      None.
 *---------------------------------------------------------------------------*/
void HuffInitTable( HuffCompressionInfo* info, void* work, u16 dataNum )
{
    u32 i;
    info->huffTable    = (HuffData*)(work);
    info->huffTree     = (u8*)( (u32)work + sizeof(HuffData) * 512 );
    info->huffTreeCtrl = (HuffTreeCtrlData*)( (u32)info->huffTree + sizeof(u8) * 512 );
    info->huffTreeTop  = 1;
    
    // Initialize huffTable
    {
        HuffData* table = info->huffTable;
        
        const HuffData  HUFF_TABLE_INIT_DATA  = { 0, 0, 0, {-1, -1}, 0, 0, 0, 0, 0 };
        for ( i = 0; i < dataNum * 2U; i++ )
        {
            table[ i ]    = HUFF_TABLE_INIT_DATA;
            table[ i ].No = (u16)i;
        }
    }
    
    // Initialize huffTree and huffTreeCtrl
    {
        const HuffTreeCtrlData HUFF_TREE_CTRL_INIT_DATA = { 1, 1, 0, 0 };
        u8*               huffTree     = info->huffTree;
        HuffTreeCtrlData* huffTreeCtrl = info->huffTreeCtrl;
        
        for ( i = 0; i < 256; i++ )
        {
            huffTree[ i * 2 ]     = 0;
            huffTree[ i * 2 + 1 ] = 0;
            huffTreeCtrl[ i ]     = HUFF_TREE_CTRL_INIT_DATA;
        }
    }
}


/*---------------------------------------------------------------------------*
  Name:         HuffCountData
  Description:  Count of frequency of appearance.
  Arguments:    table   
                *srcp   
                size    
                bitSize 
  Returns:      None.
 *---------------------------------------------------------------------------*/
void HuffCountData( HuffData* table, const u8 *srcp, u32 size, u8 bitSize )
{
    u32 i;
    u8  tmp;
    
    if ( bitSize == 8 )
    {
        for ( i = 0; i < size; i++ )
        {
            table[ srcp[ i ] ].Freq++; // 8-bit encoding
        }
    }
    else
    {
        for ( i = 0; i < size; i++ )   // 4-bit encoding
        {
            tmp = (u8)( (srcp[ i ] & 0xf0) >> 4 );
            table[ tmp ].Freq++;       // Store from upper 4 bits first // Either is OK
            tmp = (u8)( srcp[ i ] & 0x0f );
            table[ tmp ].Freq++;       // The problem is the encoding
        }
    }
}


/*---------------------------------------------------------------------------*
  Name:         HuffConstructTree
  Description:  Constructs a Huffman tree
  Arguments:    *table  
                dataNum 
  Returns:      None.
 *---------------------------------------------------------------------------*/
u16 HuffConstructTree( HuffData *table, u32 dataNum )
{
    s32     i;
    s32     leftNo, rightNo;         // Node number for creating binary tree
    u16     tableTop = (u16)dataNum; // When creating table, the table top number
    u16     rootNo;                  // Binary tree's root number
    // u16     nodeNum;             // Number of valid nodes (unreferenced)
    
    leftNo  = -1;
    rightNo = -1;
    while ( 1 )
    {
        // Search for two subtree vertices with low Freq value. At least one should be found.
        // Search child node (left)
        for ( i = 0; i < tableTop; i++ )
        {
            if ( ( table[i].Freq == 0 ) ||
                 ( table[i].PaNo != 0 ) )
            {
                continue;
            }
            
            if ( leftNo < 0 )
            {
                leftNo = i;
            }
            else if ( table[i].Freq < table[ leftNo ].Freq )
            {
                leftNo = i;
            }
        }
        
        // Search child node (right)
        for ( i = 0; i < tableTop; i++ )
        {
            if ( ( table[i].Freq == 0 ) || 
                 ( table[i].PaNo != 0 ) || 
                 ( i == leftNo ) )
            {
                continue;
            }
            
            if ( rightNo < 0 )
            {
                rightNo = i;
            }
            else if ( table[i].Freq < table[rightNo].Freq )
            {
                rightNo = i;
            }
        }
        
        // If only one, then end table creation
        if ( rightNo < 0 )
        {
            // When only one type of value exists or doesn't exist, then create one node that takes the same value for both 0 and 1
            if ( tableTop == dataNum )
            {
                table[ tableTop ].Freq      = table[ leftNo ].Freq;
                table[ tableTop ].ChNo[0]   = (s16)leftNo;
                table[ tableTop ].ChNo[1]   = (s16)leftNo;
                table[ tableTop ].LeafDepth = 1;
                table[ leftNo   ].PaNo      = (s16)tableTop;
                table[ leftNo   ].Bit       = 0;
                table[ leftNo   ].PaDepth   = 1;
            }
            else
            {
                tableTop--;
            }
            rootNo  = tableTop;
            // nodeNum = (u16)( (rootNo - dataNum + 1) * 2 + 1 ); // Commented out due to non-reference
            break;
        }
        
        // Create vertex that combines left subtree and right subtree
        table[ tableTop ].Freq = table[ leftNo ].Freq + table[ rightNo ].Freq;
        table[ tableTop ].ChNo[0] = (s16)leftNo;
        table[ tableTop ].ChNo[1] = (s16)rightNo;
        if ( table[ leftNo ].LeafDepth > table[ rightNo ].LeafDepth )
        {
            table[ tableTop ].LeafDepth = (u16)( table[ leftNo ].LeafDepth + 1 );
        }
        else
        {
            table[ tableTop ].LeafDepth = (u16)( table[ rightNo ].LeafDepth + 1 );
        }
        
        table[ leftNo  ].PaNo = table[ rightNo ].PaNo = (s16)(tableTop);
        table[ leftNo  ].Bit  = 0;
        table[ rightNo ].Bit  = 1;
        
        HuffAddParentDepthToTable( table, (u16)leftNo, (u16)rightNo );
        
        tableTop++;
        leftNo = rightNo = -1;
    }
    
    // Generate Huffman code (In Table[i].HuffCode)
    HuffAddCodeToTable( table, rootNo, 0x00 );        // The Huffman code is the code with HuffCode's lower bit masked for PaDepth bits
    
    // For each intermediate node, calculate the amount of memory needed to store the subtree that has that node as the root in HuffTree.
    HuffAddCountHWordToTable( table, rootNo );
    
    return rootNo;
}

//-----------------------------------------------------------------------
// When creating binary tree and when combining subtrees, add 1 to the depth of every node in the subtree.
//-----------------------------------------------------------------------
void HuffAddParentDepthToTable( HuffData *table, u16 leftNo, u16 rightNo )
{
    table[ leftNo  ].PaDepth++;
    table[ rightNo ].PaDepth++;
    
    if ( table[ leftNo ].LeafDepth != 0 )
    {
        HuffAddParentDepthToTable( table, (u16)table[ leftNo  ].ChNo[0], (u16)table[ leftNo  ].ChNo[1] );
    }
    if ( table[ rightNo ].LeafDepth != 0 )
    {
        HuffAddParentDepthToTable( table, (u16)table[ rightNo ].ChNo[0], (u16)table[ rightNo ].ChNo[1] );
    }
}

//-----------------------------------------------------------------------
// Create Huffman code
//-----------------------------------------------------------------------
void HuffAddCodeToTable( HuffData* table, u16 nodeNo, u32 paHuffCode )
{
    table[ nodeNo ].HuffCode = (paHuffCode << 1) | table[ nodeNo ].Bit;
    
    if ( table[ nodeNo ].LeafDepth != 0 )
    {
        HuffAddCodeToTable( table, (u16)table[ nodeNo ].ChNo[0], table[ nodeNo ].HuffCode );
        HuffAddCodeToTable( table, (u16)table[ nodeNo ].ChNo[1], table[ nodeNo ].HuffCode );
    }
}


//-----------------------------------------------------------------------
// Data volume required of intermediate node to create HuffTree
//-----------------------------------------------------------------------
u8 HuffAddCountHWordToTable( HuffData *table, u16 nodeNo)
{
    u8      leftHWord, rightHWord;
    
    switch ( table[ nodeNo ].LeafDepth )
    {
    case 0:
        return 0;
    case 1:
        leftHWord = rightHWord = 0;
        break;
    default:
        leftHWord  = HuffAddCountHWordToTable( table, (u16)table[nodeNo].ChNo[0] );
        rightHWord = HuffAddCountHWordToTable( table, (u16)table[nodeNo].ChNo[1] );
        break;
    }
    
    table[ nodeNo ].HWord = (u16)( leftHWord + rightHWord + 1 );
    return (u8)( leftHWord + rightHWord + 1 );
}


//-----------------------------------------------------------------------
// Create Huffman code table
//-----------------------------------------------------------------------
void HuffMakeHuffTree( HuffCompressionInfo* info, u16 rootNo )
{
    s16 i;
    s16 costHWord, tmpCostHWord;       // Make subtree code table for most-costly node when subtree code table has not been created.
    s16 costOffsetNeed, tmpCostOffsetNeed;
    s16 costMaxKey, costMaxRightFlag = 0;  // Information for singling out the least costly node from HuffTree
    u8  offsetNeedNum;
    // u8  tmpKey; // Unreferenced
    u8  tmpRightFlag;
    
    info->huffTreeTop = 1;
    costOffsetNeed    = 0;
    
    info->huffTreeCtrl[0].leftOffsetNeed = 0; // Do not use (used as table size)
    info->huffTreeCtrl[0].rightNodeNo    = rootNo;
    
    while ( 1 )                          // Until return 
    {
        // Calculate the number of nodes required to set offset
        offsetNeedNum = 0;
        for ( i = 0; i < info->huffTreeTop; i++ )
        {
            if ( info->huffTreeCtrl[ i ].leftOffsetNeed )
            {
                offsetNeedNum++;
            }
            if ( info->huffTreeCtrl[ i ].rightOffsetNeed )
            {
                offsetNeedNum++;
            }
        }

        // Search for node with greatest cost
        costHWord    = -1;
        costMaxKey   = -1;
        // tmpKey       =  0; // Commented out because unreferenced
        tmpRightFlag =  0;

        for ( i = 0; i < info->huffTreeTop; i++ )
        {
            tmpCostOffsetNeed = (u8)( info->huffTreeTop - i );
            
            // Evaluate cost of left child node
            if (info->huffTreeCtrl[i].leftOffsetNeed)
            {
                tmpCostHWord = (s16)info->huffTable[ info->huffTreeCtrl[i].leftNodeNo ].HWord;
                
                if ( (tmpCostHWord + offsetNeedNum) > 64 )
                {
                    goto leftCostEvaluationEnd;
                }
                if ( ! HuffRemainingNodeCanSetOffset( info, (u8)tmpCostHWord ) )
                {
                    goto leftCostEvaluationEnd;
                }
                if ( tmpCostHWord > costHWord )
                {
                    costMaxKey = i;
                    costMaxRightFlag = 0;
                }
                else if ( (tmpCostHWord == costHWord) && (tmpCostOffsetNeed > costOffsetNeed) )
                {
                    costMaxKey = i;
                    costMaxRightFlag = 0;
                }
            }
leftCostEvaluationEnd:{}
            
            // Evaluate cost of right child node
            if ( info->huffTreeCtrl[i].rightOffsetNeed)
            {
                tmpCostHWord = (s16)info->huffTable[info->huffTreeCtrl[i].rightNodeNo].HWord;
                
                if ( (tmpCostHWord + offsetNeedNum) > 64 )
                {
                    goto rightCostEvaluationEnd;
                }
                if ( ! HuffRemainingNodeCanSetOffset( info, (u8)tmpCostHWord ) )
                {
                    goto rightCostEvaluationEnd;
                }
                if ( tmpCostHWord > costHWord )
                {
                    costMaxKey = i;
                    costMaxRightFlag = 1;
                }
                else if ( (tmpCostHWord == costHWord) && (tmpCostOffsetNeed > costOffsetNeed) )
                {
                    costMaxKey = i;
                    costMaxRightFlag = 1;
                }
            }
rightCostEvaluationEnd:{}
        }

        // Store entire subtree in HuffTree
        if ( costMaxKey >= 0 )
        {
            HuffMakeSubsetHuffTree( info, (u8)costMaxKey, (u8)costMaxRightFlag);
            goto nextTreeMaking;
        }
        else
        {
            // Search for node with largest required offset
            for ( i = 0; i < info->huffTreeTop; i++ )
            {
                u16 tmp = 0;
                tmpRightFlag = 0;
                if (info->huffTreeCtrl[i].leftOffsetNeed)
                {
                    tmp = info->huffTable[ info->huffTreeCtrl[i].leftNodeNo ].HWord;
                }
                if (info->huffTreeCtrl[i].rightOffsetNeed)
                {
                    if ( info->huffTable[info->huffTreeCtrl[i].rightNodeNo ].HWord > tmp )
                    {
                        tmpRightFlag = 1;
                    }
                }
                if ( (tmp != 0) || (tmpRightFlag) )
                {
                    HuffSetOneNodeOffset( info, (u8)i, tmpRightFlag);
                    goto nextTreeMaking;
                }
            }
        }
        return;
nextTreeMaking:{}
    }
}

//-----------------------------------------------------------------------
// Store entire subtree in HuffTree
//-----------------------------------------------------------------------
void HuffMakeSubsetHuffTree( HuffCompressionInfo* info, u16 huffTreeNo, u8 rightNodeFlag )
{
    u8  i;
    
    i = info->huffTreeTop;
    HuffSetOneNodeOffset( info, huffTreeNo, rightNodeFlag);
    
    if ( rightNodeFlag )
    {
        info->huffTreeCtrl[ huffTreeNo ].rightOffsetNeed = 0;
    }
    else
    {
        info->huffTreeCtrl[ huffTreeNo ].leftOffsetNeed = 0;
    }
    
    while ( i < info->huffTreeTop )
    {
        if ( info->huffTreeCtrl[ i ].leftOffsetNeed )
        {
            HuffSetOneNodeOffset( info, i, 0);
            info->huffTreeCtrl[ i ].leftOffsetNeed = 0;
        }
        if ( info->huffTreeCtrl[ i ].rightOffsetNeed )
        {
            HuffSetOneNodeOffset( info, i, 1);
            info->huffTreeCtrl[ i ].rightOffsetNeed = 0;
        }
        i++;
    }
}

//-----------------------------------------------------------------------
// Check if there is any problems with huffTree construction if subtree of obtained data size is decompressed.
//-----------------------------------------------------------------------
u8 HuffRemainingNodeCanSetOffset( HuffCompressionInfo* info, u8 costHWord )
{
    u8  i;
    s16 capacity;
    
    capacity = (s16)( 64 - costHWord );
    
    // The offset value is larger for smaller values of i, so you should calculate without sorting, with i=0 -> huffTreeTop
    for ( i = 0; i < info->huffTreeTop; i++ )
    {
        if ( info->huffTreeCtrl[i].leftOffsetNeed )
        {
            if ( (info->huffTreeTop - i) <= capacity )
            {
                capacity--;
            }
            else
            {
                return 0;
            }
        }
        if ( info->huffTreeCtrl[i].rightOffsetNeed )
        {
            if ( (info->huffTreeTop - i) <= capacity )
            {
                capacity--;
            }
            else
            {
                return 0;
            }
        }
    }
    
    return 1;
}

/*---------------------------------------------------------------------------*
  Name:         HuffSetOneNodeOffset
  Description:  Create Huffman code table for one node
  Arguments:    *info           Pointer to data for constructing a Huffman tree
                huffTreeNo      
                rightNodeFlag   Flag for whether node is at right
  Returns:      None.
 *---------------------------------------------------------------------------*/
void HuffSetOneNodeOffset( HuffCompressionInfo* info, u16 huffTreeNo, u8 rightNodeFlag )
{
    u16 nodeNo;
    u8  offsetData = 0;
    
    HuffData*         huffTable    = info->huffTable;
    u8*               huffTree     = info->huffTree;
    HuffTreeCtrlData* huffTreeCtrl = info->huffTreeCtrl;
    u8                huffTreeTop  = info->huffTreeTop;
    
    if (rightNodeFlag)
    {
        nodeNo = huffTreeCtrl[ huffTreeNo ].rightNodeNo;
        huffTreeCtrl[ huffTreeNo ].rightOffsetNeed = 0;
    }
    else
    {
        nodeNo = huffTreeCtrl[ huffTreeNo ].leftNodeNo;
        huffTreeCtrl [huffTreeNo ].leftOffsetNeed = 0;
    }
    
    // Left child node
    if ( huffTable[ huffTable[nodeNo].ChNo[0] ].LeafDepth == 0)
    {
        offsetData |= 0x80;
        huffTree[ huffTreeTop * 2 + 0 ] = (u8)huffTable[ nodeNo ].ChNo[0];
        huffTreeCtrl[ huffTreeTop ].leftNodeNo = (u8)huffTable[ nodeNo ].ChNo[0];
        huffTreeCtrl[ huffTreeTop ].leftOffsetNeed = 0;   // Offset no longer required
    }
    else
    {
        huffTreeCtrl[ huffTreeTop ].leftNodeNo = (u16)huffTable[ nodeNo ].ChNo[0];  // Offset is required
    }
    
    // Right child node
    if ( huffTable[ huffTable[ nodeNo ].ChNo[1] ].LeafDepth == 0 )
    {
        offsetData |= 0x40;
        huffTree[ huffTreeTop * 2 + 1 ] = (u8)huffTable[nodeNo].ChNo[1];
        huffTreeCtrl[ huffTreeTop ].rightNodeNo = (u8)huffTable[ nodeNo ].ChNo[1];
        huffTreeCtrl[ huffTreeTop ].rightOffsetNeed = 0;  // Offset no longer required
    }
    else
    {
        huffTreeCtrl[ huffTreeTop ].rightNodeNo = (u16)huffTable[ nodeNo ].ChNo[1]; // Offset is required
    }
    
    offsetData |= (u8)( huffTreeTop - huffTreeNo - 1 );
    huffTree[ huffTreeNo * 2 + rightNodeFlag ] = offsetData;
    
    info->huffTreeTop++;
}


/*---------------------------------------------------------------------------*
  Name:         HuffConvertData
  Description:  Data conversion based on Huffman table.
  Arguments:    *table  
                srcp    
                dstp    
                srcSize 
                bitSize 
  Returns:      None.
 *---------------------------------------------------------------------------*/
u32 HuffConvertData( const HuffData *table, const u8* srcp, u8* dstp, u32 srcSize, u32 maxSize, u8 bitSize )
{
    u32     i, ii, iii;
    u8      srcTmp;
    u32     bitStream    = 0;
    u32     streamLength = 0;
    u32     dstSize      = 0;
    
    // Huffman encoding
    for ( i = 0; i < srcSize; i++ )
    {                                  // Data compression
        u8 val = srcp[ i ];
        if ( bitSize == 8 )
        {                              // 8-bit Huffman
            bitStream = (bitStream << table[ val ].PaDepth) | table[ val ].HuffCode;
            streamLength += table[ val ].PaDepth;
            
            if ( dstSize + (streamLength / 8) >= maxSize )
            {
                // Error if size becomes larger than source
                return 0;
            }
            
            for ( ii = 0; ii < streamLength / 8; ii++ )
            {
                dstp[ dstSize++ ] = (u8)(bitStream >> (streamLength - (ii + 1) * 8));
            }
            streamLength %= 8;
        }
        else                           // 4-bit Huffman
        {
            for ( ii = 0; ii < 2; ii++ )
            {
                if ( ii )
                {
                    srcTmp = (u8)( val >> 4 );     // First four bits come later
                }
                else
                {
                    srcTmp = (u8)( val & 0x0F );   // Last four bits come first (because the decoder accesses in a Little-Endian method)
                }
                bitStream = (bitStream << table[ srcTmp ].PaDepth) | table[ srcTmp ].HuffCode;
                streamLength += table[ srcTmp ].PaDepth;
                if ( dstSize + (streamLength / 8) >= maxSize )
                {
                    // Error if size becomes larger than source
                    return 0;
                }
                for ( iii = 0; iii < streamLength / 8; iii++ )
                {
                    dstp[ dstSize++ ] = (u8)(bitStream >> (streamLength - (iii + 1) * 8));
                }
                streamLength %= 8;
            }
        }
    }
    
    if ( streamLength != 0 )
    {
        if ( dstSize + 1 >= maxSize )
        {
            // Error if size becomes larger than source
            return 0;
        }
        dstp[ dstSize++ ] = (u8)( bitStream << (8 - streamLength) );
    }
    
    // 4-byte boundary alignment
    //   Data0 for alignment is included in data size 
    //   This is special to Huffman encoding!　 Data is stored after the alignment-boundary data because little endian conversion is used.
    while ( dstSize & 0x3 )
    {
        dstp[ dstSize++ ] = 0;
    }
    
    // Little endian conversion
    for ( i = 0; i < dstSize / 4; i++ )
    {
        u8 tmp;
        tmp = dstp[i * 4 + 0];
        dstp[i * 4 + 0] = dstp[i * 4 + 3];
        dstp[i * 4 + 3] = tmp;         // Swap
        tmp = dstp[i * 4 + 1];
        dstp[i * 4 + 1] = dstp[i * 4 + 2];
        dstp[i * 4 + 2] = tmp;         // Swap
    }
    return dstSize;
}

}   // Namespace
}   // namespace cx
}   // namespace nn


#include "zutil.h"
#include "zlib.h"
#include "deflate.h"

namespace nn {
namespace cx {

    namespace
    {
        const int MEM_LEVEL = MAX_MEM_LEVEL - 1;

        void ZlibStaticAssert() NN_IS_UNUSED_VAR;
        void ZlibStaticAssert()
        {
            NN_STATIC_ASSERT( sizeof(deflate_state)
                            + (1 << (MAX_WBITS + 2))
                            + (1 << (MEM_LEVEL + 9))
                            == GZIP_COMPRESS_WORK_SIZE );
            NN_STATIC_ASSERT( sizeof(deflate_state) == 5828 );
            NN_STATIC_ASSERT( MAX_WBITS == 15 );
            NN_STATIC_ASSERT( MAX_MEM_LEVEL == 9 );
        }

        s32 CompressDeflateCommon( void* pDest, size_t destSize, const void* pSrc, size_t srcSize, void* pWork, int wbits )
        {
            NN_POINTER_TASSERT_(pDest);
            NN_POINTER_TASSERT_(pSrc);
            NN_POINTER_TASSERT_(pWork);

            detail::ZlibAllocator za(pWork, GZIP_COMPRESS_WORK_SIZE);
            z_stream s;
            int err;

            s.next_in   = reinterpret_cast<nncxZlib_Bytef*>(const_cast<void*>(pSrc));
            s.avail_in  = srcSize;
            s.next_out  = reinterpret_cast<nncxZlib_Bytef*>(pDest);
            s.avail_out = destSize;

            s.zalloc    = detail::ZlibAllocator::Allocate;
            s.zfree     = detail::ZlibAllocator::Free;
            s.opaque    = &za;

            err = deflateInit2(&s, 
                    Z_DEFAULT_COMPRESSION,
                    Z_DEFLATED,
                    wbits,
                    MEM_LEVEL,
                    Z_DEFAULT_STRATEGY );
            if (err != Z_OK)
            {
                return detail::ConvertZlibReturnCode(err);
            }

            err = nncxZlib_deflate(&s, Z_FINISH);
            if (err != Z_STREAM_END)
            {
                nncxZlib_deflateEnd(&s);
                return detail::ConvertZlibReturnCode(err);
            }

            size_t ret = s.total_out;

            err = nncxZlib_deflateEnd(&s);
            if (err != Z_OK)
            {
                return detail::ConvertZlibReturnCode(err);
            }

            return ret;
        }
    }

s32 CompressGzip( void* pDest, size_t destSize, const void* pSrc, size_t srcSize, void* pWork )
{
    NN_POINTER_TASSERT_(pDest);
    NN_POINTER_TASSERT_(pSrc);
    NN_POINTER_TASSERT_(pWork);

    const int wbits = MAX_WBITS + 16;       // Specify +16 = gzip format
    return CompressDeflateCommon(pDest, destSize, pSrc, srcSize, pWork, wbits);
}

s32 CompressZlib( void* pDest, size_t destSize, const void* pSrc, size_t srcSize, void* pWork )
{
    NN_POINTER_TASSERT_(pDest);
    NN_POINTER_TASSERT_(pSrc);
    NN_POINTER_TASSERT_(pWork);

    return CompressDeflateCommon(pDest, destSize, pSrc, srcSize, pWork, MAX_WBITS);
}

s32 CompressDeflate( void* pDest, size_t destSize, const void* pSrc, size_t srcSize, void* pWork )
{
    NN_POINTER_TASSERT_(pDest);
    NN_POINTER_TASSERT_(pSrc);
    NN_POINTER_TASSERT_(pWork);

    int headerSize;
    bit8* p8 = reinterpret_cast<bit8*>(pDest);
    *p8++ = COMPRESSION_DEFLATE;
    if( srcSize < (1 << 24) )
    {
        *p8++ = ((srcSize >>  0) & 0xFF);
        *p8++ = ((srcSize >>  8) & 0xFF);
        *p8++ = ((srcSize >> 16) & 0xFF);
        headerSize = 4;
    }
    else
    {
        *p8++ = 0;
        *p8++ = 0;
        *p8++ = 0;
        *p8++ = ((srcSize >>  0) & 0xFF);
        *p8++ = ((srcSize >>  8) & 0xFF);
        *p8++ = ((srcSize >> 16) & 0xFF);
        *p8++ = ((srcSize >> 24) & 0xFF);
        headerSize = 8;
    }

    const int wbits = - MAX_WBITS;      // Specify - = raw deflate format
    s32 ret = CompressDeflateCommon(p8, destSize - headerSize, pSrc, srcSize, pWork, wbits);

    if( ret > 0 )
    {
        return ret + headerSize;
    }
    else
    {
        return ret;
    }
}

}   // namespace cx
}   // namespace nn
