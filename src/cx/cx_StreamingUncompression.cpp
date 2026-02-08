/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_StreamingUncompression.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47712 $
 *---------------------------------------------------------------------------*/

#include <nn/cx/cx_Uncompression.h>
#include <nn/cx/cx_StreamingUncompression.h>
#include <nn/cx/cx_SecureUncompression.h>
#include <nn/math.h>
#include "cx_Utility.h"
#include <zlib.h>
#include <new>

namespace nn {
namespace cx {

    namespace
    {
        struct UncompressContextDeflate_
        {
            static const size_t WORK_SIZE = UNCOMPRESS_GZIP_WORK_SIZE + (1 << MAX_WBITS);

            s32                     headerSize;
            size_t                  rawSize;
            detail::ZlibAllocator   za;
            z_stream                s;
            bit8                    workBuffer[WORK_SIZE];
        };

        UncompressContextDeflate_* GetUncompressContextDeflate_(UncompContextDeflate* p)
        {
            NN_STATIC_ASSERT( sizeof(UncompressContextDeflate_)
                           == sizeof(UncompContextDeflate) );
            return reinterpret_cast<UncompressContextDeflate_*>(p);
        }
    }



/*---------------------------------------------------------------------------*
  Name: InitUncompContextRL

  Description: Initializes the streaming decompression context for run-length compressed data.
                

  Arguments: context Pointer to the run-length uncompressed context
                dest        Destination address for uncompressed data

  Returns: Can get the data size after decompression.

 *---------------------------------------------------------------------------*/
void InitUncompContextRL( UncompContextRL *context, void* dest )
{
    NN_NULL_TASSERT_(context);
    context->destp      = (u8*)dest;
    context->destCount  = 0;
    context->flags      = 0;
    context->length     = 0;
    context->headerSize = 8;
    context->forceDestCount = 0;
}


/*---------------------------------------------------------------------------*
  Name: InitUncompContextLZ

  Description: Initializes the streaming decompression context for LZ-compressed data.

  Arguments: context Pointer to the LZ uncompressed context
                dest        Destination address for uncompressed data
                header      Pointer to the start data for the compressed data

 *---------------------------------------------------------------------------*/
void InitUncompContextLZ( UncompContextLZ *context, void* dest )
{
    NN_NULL_TASSERT_(context);
    context->destp      = (u8*)dest;
    context->destCount  = 0;
    context->flags      = 0;
    context->flagIndex  = 0;
    context->length     = 0;
    context->lengthFlg  = 3;
    context->headerSize = 8;
    context->exFormat   = 0;
    context->forceDestCount = 0;
}


/*---------------------------------------------------------------------------*
  Name: InitUncompContextHuffman

  Description: Initializes the streaming decompression context for Huffman-compressed data.

  Arguments: context Pointer to the Huffman uncompressed context
                dest        Destination address for uncompressed data
                header      Pointer to the start data for the compressed data

 *---------------------------------------------------------------------------*/
void InitUncompContextHuffman( UncompContextHuffman *context, void* dest )
{
    NN_NULL_TASSERT_(context);
    context->destp      = (u8*)dest;
    context->destCount  = 0;
    context->bitSize    = 0;
    context->treeSize   = -1;
    context->treep      = &context->tree[ 0 ];
    context->destTmp    = 0;
    context->destTmpCnt = 0;
    context->srcTmp     = 0;
    context->srcTmpCnt  = 0;
    context->headerSize = 8;
    context->forceDestCount = 0;
}

namespace {

/*---------------------------------------------------------------------------*
  Name:         ReadHeader

  Description:  Header parsing

  Arguments:    headerSize    Pointer to the remaining size of the header to be read
                *destCount    Pointer to the uncompressed data size
                srcp          Pointer to a buffer containing the header information
                srcSize       Pointer to the size of the buffer containing the header information
                forceDestSize Uncompressed data size (if 0, use the binary header information as is)

  Returns:      Size of the loaded source data
 *---------------------------------------------------------------------------*/
inline u32 ReadHeader( u8* headerSize, s32 *destCount, const u8* srcp, u32 srcSize, s32 forceDestSize )
{
    NN_NULL_TASSERT_(headerSize);
    NN_NULL_TASSERT_(destCount);

    u32 readLen = 0;
    while ( *headerSize > 0 )
    {
        --(*headerSize);
        if ( *headerSize <= 3 )
        {
            *destCount |= (*srcp << ((3 - *headerSize) * 8));
        }
        else if ( *headerSize <= 6 )
        {
            *destCount |= (*srcp << ((6 - *headerSize) * 8));
        }
        ++srcp;
        ++readLen;
        if ( *headerSize == 4 && *destCount > 0 )
        {
            *headerSize = 0;
        }
        if ( --srcSize == 0 && *headerSize > 0 )
        {
            return readLen;
        }
    }

    if ( ( forceDestSize > 0          ) &&
         ( forceDestSize < *destCount ) )
    {
        *destCount = forceDestSize;
    }
    return readLen;
}

}   // Namespace

/*---------------------------------------------------------------------------*
  Name: ReadUncompRL

  Description: This function performs streaming decompression of run-length compressed data.
                Data is written in units of 8 bits. Data cannot be directly uncompressed to VRAM.

  Arguments: context Pointer to the run-length uncompressed context
                data    Pointer to the next data
                len     Data size

  Returns: Size of remaining uncompressed data.
                Returns a negative error code if failed.

 *---------------------------------------------------------------------------*/
s32 ReadUncompRL( UncompContextRL *context, const void* data, u32 len )
{
    NN_NULL_TASSERT_(context);
    NN_NULL_TASSERT_(data);

    const u8* srcp = (const u8*)data;
    u8  srcTmp;

    // Header parsing
    if ( context->headerSize > 0 )
    {
        u32 read_len;
        if ( context->headerSize == 8 )
        {
            if ( (*srcp & COMPRESSION_TYPE_MASK) != COMPRESSION_RL )
            {
                return CX_ERR_UNSUPPORTED;
            }
            if ( (*srcp & 0x0F ) != 0 )
            {
                return CX_ERR_UNSUPPORTED;
            }
        }
        read_len = ReadHeader( &context->headerSize, &context->destCount, srcp, len, context->forceDestCount );
        srcp += read_len;
        len  -= read_len;
        if ( len == 0 )
        {
            return (context->headerSize == 0)? context->destCount : -1;
        }
    }

    while ( context->destCount > 0 )
    {
        // Process if length > 0.
        if ( ! (context->flags & 0x80) )
        // Uncompressed data has a length not equal to 0
        {
            while ( context->length > 0 )
            {
                *context->destp++ = *srcp++;
                context->length--;
                context->destCount--;
                len--;
                // End when the prepared buffer has been read in full
                if ( len == 0 )
                {
                    return context->destCount;
                }
            }
        }
        else if ( context->length > 0 )
        // Compressed data has a length not equal to 0
        {
            srcTmp = *srcp++;
            len--;
            while ( context->length > 0 )
            {
                *context->destp++ = srcTmp;
                context->length--;
                context->destCount--;
            }
            if ( len == 0 )
            {
                return context->destCount;
            }
        }

        // Reading the flag byte
        context->flags = *srcp++;
        len--;
        context->length = (u16)(context->flags & 0x7F);
        if ( context->flags & 0x80 )
        {
            context->length += 3;
        }
        else
        {
            context->length += 1;
        }

        if ( context->length > context->destCount )
        // Measures for buffer overrun when invalid data is decompressed.
        {
            if ( context->forceDestCount == 0 )
            {
                return CX_ERR_DEST_OVERRUN;
            }
            context->length = (u16)context->destCount;
        }
        if ( len == 0 )
        {
            return context->destCount;
        }
    }

    // Processing to perform in the event that (context->destCount  == 0)
    if ( (context->forceDestCount == 0) && (len > 32) )
    {
        return CX_ERR_SRC_REMAINDER;
    }
    return 0;
}


/*---------------------------------------------------------------------------*
  Name: ReadUncompLZ

  Description: This function performs streaming decompression of LZ-compressed data.
                Data is written in units of 8 bits. Data cannot be directly uncompressed to VRAM.

  Arguments: context Pointer to the LZ uncompressed context
                data    Pointer to the next data
                len     Data size

  Returns: Size of remaining uncompressed data.
                Returns a negative error code if failed.

 *---------------------------------------------------------------------------*/
s32 ReadUncompLZ( UncompContextLZ *context, const void* data, u32 len )
{
    NN_NULL_TASSERT_(context);
    NN_NULL_TASSERT_(data);

    const u8* srcp = (const u8*)data;
    s32 offset;

    // Header parsing
    if ( context->headerSize > 0 )
    {
        u32 read_len;
        // Process the first byte
        if ( context->headerSize == 8 )
        {
            if ( ( *srcp & COMPRESSION_TYPE_MASK ) != COMPRESSION_LZ )
            {
                return CX_ERR_UNSUPPORTED;
            }
            // Record as an LZ compression parameter
            context->exFormat = (u8)( *srcp & 0x0F );
            if ( (context->exFormat != 0x0) && (context->exFormat != 0x1) )
            {
                return CX_ERR_UNSUPPORTED;
            }
        }
        read_len = ReadHeader( &context->headerSize, &context->destCount, srcp, len, context->forceDestCount );
        srcp += read_len;
        len  -= read_len;
        if ( len == 0 )
        {
            return (context->headerSize == 0)? context->destCount : -1;
        }
    }

    while ( context->destCount > 0 )
    {
        while ( context->flagIndex > 0 )
        {
            if ( len == 0 )
            {
                return context->destCount;
            }

            if ( ! (context->flags & 0x80) )
            // Process for non-compressed data
            {
                *context->destp++ = *srcp++;
                context->destCount--;
                len--;
            }
            else
            // Process for compressed data
            {
                while ( context->lengthFlg > 0 )
                {
                    --context->lengthFlg;
                    if ( ! context->exFormat )
                    {
                        context->length  = *srcp++;
                        context->length += (3 << 4);
                        context->lengthFlg = 0;
                    }
                    else
                    {
                        switch ( context->lengthFlg )
                        {
                        case 2:
                            {
                                context->length = *srcp++;
                                if ( (context->length >> 4) == 1 )
                                {
                                    // Read two more bytes
                                    context->length =  (context->length & 0x0F) << 16;
                                    context->length += ( (0xFF + 0xF + 3) << 4 );
                                }
                                else if ( (context->length >> 4) == 0 )
                                {
                                    // Read one more byte
                                    context->length =  (context->length & 0x0F) << 8;
                                    context->length += ( (0xF + 2) << 4 );
                                    context->lengthFlg = 1;
                                }
                                else
                                {
                                    context->length += (1 << 4);
                                    context->lengthFlg = 0;
                                }
                            }
                            break;
                        case 1:
                            {
                                context->length += (*srcp++ << 8);
                            }
                            break;
                        case 0:
                            {
                                context->length += *srcp++;
                            }
                            break;
                        }
                    }
                    if ( --len == 0 )
                    {
                        return context->destCount;
                    }
                }

                offset = (context->length & 0xF) << 8;
                context->length = context->length >> 4;
                offset = (offset | *srcp++) + 1;
                len--;
                context->lengthFlg = 3;

                // Measures for buffer overrun when invalid data is decompressed.
                if ( context->length > context->destCount )
                {
                    if ( context->forceDestCount == 0 )
                    {
                        return CX_ERR_DEST_OVERRUN;
                    }
                    context->length = context->destCount;
                }
                // Copy a length amount of data located at the offset position
                while ( context->length > 0 )
                {
                    *context->destp = context->destp[ -offset ];
                    context->destp++;
                    context->destCount--;
                    context->length--;
                }
            }

            if ( context->destCount == 0 )
            {
                goto out;
            }
            context->flags <<= 1;
            context->flagIndex--;
        }

        if ( len == 0 )
        {
            return context->destCount;
        }
        // Read a new flag
        context->flags     = *srcp++;
        context->flagIndex = 8;
        len--;
    }

out:
    // Processing to perform in the event that (context->destCount  == 0)
    if ( (context->forceDestCount == 0) && (len > 32) )
    {
        return CX_ERR_SRC_REMAINDER;
    }
    return 0;
}

namespace {

// Get the next node in the Huffman signed table
inline u8* GetNextNode( const u8* pTree, u32 select )
{
    return (u8*)( ((u32)pTree & ~0x1) + ( ( (*pTree & 0x3F) + 1 ) * 2 ) + select );
}

}   // Namespace

/*---------------------------------------------------------------------------*
  Name: ReadUncompHuffman

  Description: This function performs streaming decompression of Huffman-compressed data.
                Returns a negative error code if failed.

  Arguments: context Pointer to the Huffman uncompressed context
                data    Pointer to the next data
                len     Data size

  Returns: Size of remaining uncompressed data.
                Returns a negative error code if failed.

 *---------------------------------------------------------------------------*/
s32 ReadUncompHuffman( UncompContextHuffman *context, const void* data, u32 len )
{
    NN_NULL_TASSERT_(context);
    NN_NULL_TASSERT_(data);

#define TREE_END_MASK   0x80U
    const u8* srcp = (const u8*)data;
    u32  select;
    u32  endFlag;

    // Header parsing
    if ( context->headerSize > 0 )
    {
        u32 read_len;
        // Process the first byte
        if ( context->headerSize == 8 )
        {
            context->bitSize = (u8)(*srcp & 0xF);

            if ( ( *srcp & COMPRESSION_TYPE_MASK ) != COMPRESSION_HUFFMAN )
            {
                return CX_ERR_UNSUPPORTED;
            }
            if ( (context->bitSize != 4) && (context->bitSize != 8) )
            {
                return CX_ERR_UNSUPPORTED;
            }
        }
        read_len = ReadHeader( &context->headerSize, &context->destCount, srcp, len, context->forceDestCount );
        srcp += read_len;
        len  -= read_len;
        if ( len == 0 )
        {
            return (context->headerSize == 0)? context->destCount : -1;
        }
    }

    // treeSize is set to -1 in InitUncompContextHuffman.
    // When context->treeSize is negative, it indicates the start of the data.
    if ( context->treeSize < 0 )
    {
        context->treeSize = (s16)( ( *srcp + 1 ) * 2 - 1 );
        *context->treep++ = *srcp++;
        len--;
    }

    // Load the Huffman signed table
    while ( context->treeSize > 0 )
    {
        if ( len == 0 )
        {
            return context->destCount;
        }
        *context->treep++ = *srcp++;
        context->treeSize--;
        len--;
        if ( context->treeSize == 0 )
        {
            context->treep = &context->tree[ 1 ];
            if ( ! internal::VerifyHuffmanTable( &context->tree[ 0 ], context->bitSize ) )
            {
                return CX_ERR_ILLEGAL_TABLE;
            }
        }
    }

    // Decoding process
    while ( context->destCount > 0 )
    {
        // src data is read in 4-byte units
        while ( context->srcTmpCnt < 32 )
        {
            if ( len == 0 )
            {
                return context->destCount;
            }
            context->srcTmp |= (*srcp++) << context->srcTmpCnt;
            len--;
            context->srcTmpCnt += 8;
        }

        // Decode the 32 bits that were loaded. After those 32 bits are processed, the next 4 bytes are read.
        while ( context->srcTmpCnt > 0 )
        {
            select  = context->srcTmp >> 31;
            endFlag = (*context->treep << select) & TREE_END_MASK;
            context->treep = GetNextNode( context->treep, select );
            context->srcTmp <<= 1;
            context->srcTmpCnt--;

            if ( ! endFlag )
            {
                continue;
            }

            // When the Huffman tree's terminal flag is set, data is stored after the offset
            // 
            context->destTmp >>= context->bitSize;
            context->destTmp |= *context->treep << ( 32 - context->bitSize );
            context->treep = &context->tree[ 1 ];
            context->destTmpCnt += context->bitSize;

            if ( context->destCount <= (context->destTmpCnt / 8) )
            {
                context->destTmp    >>= (32 - context->destTmpCnt);
                context->destTmpCnt = 32;
            }

            // Write in 4-byte units
            if ( context->destTmpCnt == 32 )
            {
                *(u32*)context->destp = internal::ConvertEndian( context->destTmp );
                context->destp     += 4;
                context->destCount -= 4;
                context->destTmpCnt = 0;
                if ( context->destCount <= 0 )
                {
                    goto out;
                }
            }
        }
    }

out:
    // Processing to perform in the event that (context->destCount  == 0)
    if ( (context->forceDestCount == 0) && (len > 32) )
    {
        return CX_ERR_SRC_REMAINDER;
    }
    return 0;
}


namespace {

struct BitReader
{
    const u8* srcp;
    u32   cnt;
    u32   stream;
    u32   stream_len;
};


inline s32
BitReader_Read( BitReader* context, u8 bits )
{
    s32 value;

    while ( context->stream_len < bits )
    {
        if ( context->cnt == 0 )
        {
            return -1;
        }
        context->stream <<= 8;
        context->stream += *context->srcp;
        context->srcp++;
        context->cnt--;
        context->stream_len += 8;
    }

    value = (s32)( (context->stream >> (context->stream_len - bits)) & ((1 << bits) - 1) );
    context->stream_len -= bits;
    return value;
}

inline s64
BitReader_ReadEx( BitReader* context, u8 bits )
{
    s64 value;
    u8  stock = 0;

    while ( context->stream_len < bits )
    {
        if ( context->cnt == 0 )
        {
            return -1;
        }
        if ( context->stream_len > 24 )
        {
            stock = (u8)( context->stream >> 24 );
        }
        context->stream <<= 8;
        context->stream += *context->srcp;
        context->srcp++;
        context->cnt--;
        context->stream_len += 8;
    }
    value = context->stream;
    value |= (s64)stock << 32;
    value = (s64)( (value >> (context->stream_len - bits)) & ((1 << bits) - 1) );
    context->stream_len -= bits;

    return value;
}

}   // Namespace


#define ENC_OFFSET_WIDTH

/*---------------------------------------------------------------------------*
  Name:         InitUncompContextLH

  Description:

  Arguments:    context
                dest

  Returns:      None.
 *---------------------------------------------------------------------------*/
void
InitUncompContextLH( UncompContextLH * context, void* dest )
{
    NN_NULL_TASSERT_(context);
    context->destp       = static_cast<u8*>(dest);
    context->destCount   = -1;
    context->nodep       = context->huffTable9  + 1;
    context->tableSize9  = -1;
    context->tableSize12 = -1;
    context->headerSize  = 8;
    context->length      = 0;
    context->stream      = 0;
    context->stream_len  = 0;
    context->offset_bits = -1;
    context->forceDestCount = 0;
}

/*---------------------------------------------------------------------------*
  Name:         ReadUncompLH

  Description:  This function performs streaming decompression of LZ-Huffman (combined) compressed data.

  Arguments:    *context: Pointer to the decompressed context
                data     Data pointer
                len     Data size

  Returns:      Size of remaining uncompressed data
                Returns a negative error code if failed.
 *---------------------------------------------------------------------------*/
s32
ReadUncompLH( UncompContextLH *context, const void* data, u32 len )
{
    NN_NULL_TASSERT_(context);
    NN_NULL_TASSERT_(data);

#define LENGTH_BITS         9
#if defined(ENC_OFFSET_WIDTH)
    #define OFFSET_BITS     5
    #define OFFSET_MASK     0x07
    #define LEAF_FLAG       0x10
#else
    #define OFFSET_BITS     12
    #define OFFSET_MASK  0x3FF
    #define LEAF_FLAG    0x800
#endif

    const u8* srcp = (const u8*)data;
    BitReader stream;
    s32  val;
    u16* nodep;
    u16  length;

    stream.srcp       = srcp;
    stream.cnt        = len;
    stream.stream     = context->stream;
    stream.stream_len = context->stream_len;

    // Header parsing
    while ( context->headerSize > 0 )
    {
        s64 val32 = BitReader_ReadEx( &stream, 32 );
        if ( val32 < 0 )
        {
            goto out;
        }
        context->headerSize -= 4;
        if ( context->headerSize == 4 )
        {
            u32 headerVal = internal::ForceConvertEndian( (u32)val32 );
            if ( (headerVal & COMPRESSION_TYPE_MASK) != COMPRESSION_LH )
            {
                return CX_ERR_UNSUPPORTED;
            }
            context->destCount = (s32)( headerVal >> 8 );

            if ( context->destCount == 0 )
            {
                context->headerSize = 4;
                context->destCount  = -1;
            }
            else
            {
                context->headerSize = 0;
            }
        }
        else // if ( context->headerSize == 0 )
        {
            context->destCount  = (s32)internal::ForceConvertEndian( (u32)val32 );
        }

        if ( context->headerSize == 0 )
        {
            if ( ( context->forceDestCount > 0 ) && ( context->forceDestCount < context->destCount ) )
            {
                context->destCount = context->forceDestCount;
            }
        }
    }

    // load the Huffman table
    {
        if ( context->tableSize9 < 0 )
        {
            if ( ( val = BitReader_Read( &stream, 16 ) ) < 0 )
            {
                goto out;
            }
            context->tableSize9 = (internal::ForceConvertEndian16( (u16)val ) + 1) * 4 * 8; // shown with the bit count
            context->tableIdx   = 1;
            context->tableSize9 -= 16;
        }

        const u32 MAX_IDX = (u32)( (1 << LENGTH_BITS) * 2 );

        while ( context->tableSize9 >= LENGTH_BITS )
        {
            if ( ( val = BitReader_Read( &stream, LENGTH_BITS ) ) < 0 )
            {
                goto out;
            }

            if ( context->tableIdx < MAX_IDX )
            {
                context->huffTable9[ context->tableIdx++ ] = (u16)val;
            }
            context->tableSize9 -= LENGTH_BITS;
        }

        context->huffTable9[ 0 ] = (u16)context->tableIdx;

        if ( context->tableSize9 > 0 )
        {
            if ( ( val = BitReader_Read( &stream, (u8)context->tableSize9 ) ) < 0 )
            {
                goto out;
            }

            context->tableSize9 = 0;

            // verify the table
            if ( ! internal::LHVerifyTable( context->huffTable9, LENGTH_BITS ) )
            {
                return CX_ERR_ILLEGAL_TABLE;
            }
        }
    }
    {
        if ( context->tableSize12 < 0 )
        {
            if ( ( val = BitReader_Read( &stream, (OFFSET_BITS > 8)? 16 : 8 ) ) < 0 )
            {
                goto out;
            }
        #if ( OFFSET_BITS > 8 )
            context->tableSize12 = (internal::ForceConvertEndian16( (u16)val ) + 1) * 4 * 8;
        #else // ( OFFSET_BITS <= 8 )
            context->tableSize12 = ((u16)val + 1) * 4 * 8;
        #endif
            context->tableIdx    = 1;
            context->tableSize12 -= (OFFSET_BITS > 8)? 16 : 8;
        }

        const u32 MAX_IDX = (u32)( (1 << OFFSET_BITS) * 2 );

        while ( context->tableSize12 >= OFFSET_BITS )
        {
            if ( ( val = BitReader_Read( &stream, OFFSET_BITS ) ) < 0 )
            {
                goto out;
            }

            if ( context->tableIdx < MAX_IDX )
            {
                context->huffTable12[ context->tableIdx++ ] = (u16)val;
            }
            context->tableSize12 -= OFFSET_BITS;
        }

        context->huffTable12[ 0 ] = (u16)context->tableIdx;

        if ( context->tableSize12 > 0 )
        {
            if ( ( val = BitReader_Read( &stream, (u8)context->tableSize12 ) ) < 0 )
            {
                goto out;
            }

            context->tableSize12 = 0;

            // verify the table
            if ( ! internal::LHVerifyTable( context->huffTable12, OFFSET_BITS ) )
            {
                return CX_ERR_ILLEGAL_TABLE;
            }
        }
    }

    nodep  = context->nodep;
    length = context->length;

    // Data conversion
    while ( context->destCount > 0 )
    {
        // get length data
        if ( length == 0 )
        {
            do
            {
                u8  bit;
                u32 offset;
                if ( ( val = BitReader_Read( &stream, 1 ) ) < 0 )
                {
                    context->nodep  = nodep;
                    context->length = length;
                    goto out;
                }
                bit = (u8)( val & 1 );
                offset = (((*nodep & 0x7F) + 1U) << 1) + bit;

                if ( *nodep & (0x100 >> bit) )
                {
                    nodep = (u16*)((u32)nodep & ~0x3);
                    length = *(nodep + offset);
                    nodep = context->huffTable12 + 1;
                    break;
                }
                else
                {
                    nodep = (u16*)((u32)nodep & ~0x3);
                    nodep += offset;
                }
            } while ( 1 );
        }

        if ( length < 0x100 )
        // uncompressed data
        {
            *context->destp++ = (u8)length;
            context->destCount--;
            nodep = context->huffTable9 + 1;
            length = 0;
        }
        else
        // compressed data
        {
            u16 lzOffset;
            u16 lzLength = (u16)( (length & 0xFF) + 3 );

        #if defined(ENC_OFFSET_WIDTH)
            if ( context->offset_bits < 0 )
            {
        #endif
                do
                {
                    u8 bit;
                    u32 offset;

                    if ( ( val = BitReader_Read( &stream, 1 ) ) < 0 )
                    {
                        context->nodep  = nodep;
                        context->length = length;
                        goto out;
                    }
                    bit = (u8)( val & 1 );
                    offset = (((*nodep & OFFSET_MASK) + 1U) << 1) + bit;

                    if ( *nodep & (LEAF_FLAG >> bit) )
                    {
                        nodep = (u16*)((u32)nodep & ~0x3);
                    #if defined(ENC_OFFSET_WIDTH)
                        context->offset_bits = (s8)( *(nodep + offset) );
                    #else
                        lzOffset = (u16)( *(nodep + offset) + 1 );
                    #endif
                        break;
                    }
                    else
                    {
                        nodep =  (u16*)((u32)nodep & ~0x3);
                        nodep += offset;
                    }
                } while ( 1 );
        #if defined(ENC_OFFSET_WIDTH)
            }
        #endif

        #if defined(ENC_OFFSET_WIDTH)
            if ( context->offset_bits <= 1 )
            {
                val = context->offset_bits;
            }
            else if ( ( val = BitReader_Read( &stream, (u8)(context->offset_bits - 1) ) ) < 0 )
            {
                context->nodep  = nodep;
                context->length = length;
                goto out;
            }
            if ( context->offset_bits >= 2 )
            {
                val |= (1 << (context->offset_bits - 1));
            }

            context->offset_bits = -1;
            lzOffset = (u16)(val + 1);
        #endif

            if ( context->destCount < lzLength )
            // Measures for buffer overrun when invalid data is decompressed.
            {
                if ( context->forceDestCount == 0 )
                {
                    return CX_ERR_DEST_OVERRUN;
                }
                lzLength = (u16)context->destCount;
            }

            context->destCount -= lzLength;
            while ( lzLength-- )
            {
                *context->destp = *(context->destp - lzOffset);
                ++context->destp;
            }
            length = 0;
            nodep  = context->huffTable9 + 1;
        }
    }

out:
    context->stream     = stream.stream;
    context->stream_len = stream.stream_len;


    // After decompression, remaining source data will be treated as an error
    if ( (context->destCount      == 0) &&
         (context->forceDestCount == 0) &&
         (stream.cnt > 32)            )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return context->destCount;

#undef OFFSET_BITS
#undef OFFSET_MASK
#undef LEAF_FLAG
}

namespace {

// Structure for the range coder state
struct RCState
{
    u32     low;
    u32     range;
    u32     code;       // only used during decompression
    u8      carry;      // only used during compression
    u8      padding_[3];
    u32     carry_cnt;  // only used during compression
};

// Range coder structure
struct RCCompressionInfo
{
    u32 *freq;          // Table for occurrence frequency: (1 << bitSize) * sizeof(u32) bytes
    u32 *low_cnt;       // Table for the LOW border value: (1 << bitSize) * sizeof(u32) bytes
    u32 total;          // Total: 4 bytes
    u8  bitSize;        // Bit size: 1 byte
    u8  padding_[3];    //
};

#define RC_MAX_RANGE    0x80000000

/*---------------------------------------------------------------------------*
  Name:         LRCIntro_

  Description:  Processing to set up streaming loads

  Arguments:    context
                info8
                info9
                state

  Returns:      None.
 *---------------------------------------------------------------------------*/
inline void
LRCIntro_(
    UncompContextLRC       *context,
    RCCompressionInfo        *info9,
    RCCompressionInfo        *info12,
    RCState                  *state )
{
    info9->freq        = context->freq9;
    info9->low_cnt     = context->low_cnt9;
    info9->total       = context->total9;
    info9->bitSize     = 9;

    info12->freq       = context->freq12;
    info12->low_cnt    = context->low_cnt12;
    info12->total      = context->total12;
    info12->bitSize    = 12;

    state->low       = context->low;
    state->range     = context->range;
    state->code      = context->code;
    state->carry     = context->carry;
    state->carry_cnt = context->carry_cnt;
}


/*---------------------------------------------------------------------------*
  Name:         LRCFin_

  Description:  Processing to stop streaming loads

  Arguments:    *context
                *info9
                *info12
                *state

  Returns:      None.
 *---------------------------------------------------------------------------*/
inline void
LRCFin_(
    UncompContextLRC       *context,
    const RCCompressionInfo  *info9,
    const RCCompressionInfo  *info12,
    const RCState            *state )
{
    context->total9  = info9->total;
    context->total12 = info12->total;

    context->low       = state->low;
    context->range     = state->range;
    context->code      = state->code;
    context->carry     = state->carry;
    context->carry_cnt = state->carry_cnt;
}

/*---------------------------------------------------------------------------*
  Name:         RCInitState_

  Description:  Initializes the RC state.

  Arguments:    state: Pointer to an RC state structure

  Returns:      None.
 *---------------------------------------------------------------------------*/
inline void
RCInitState_( RCState* state )
{
    state->low   = 0;
    state->range = RC_MAX_RANGE;
    state->code  = 0;
    state->carry = 0;
    state->carry_cnt = 0;
}

/*---------------------------------------------------------------------------*
  Name:         RCInitInfo_

  Description:  Initialize the table for the adaptive range coder.
                All occurrence frequencies are initialized to 1.

  Arguments:    info: Pointer to an RC table information structure

  Returns:      None.
 *---------------------------------------------------------------------------*/
inline void
RCInitInfo_( RCCompressionInfo* info, u8 bitSize )
{
    u32 tableSize = (u32)(1 << bitSize);
    u32 i;

    info->bitSize = bitSize;

    for ( i = 0; i < tableSize; i++ )
    {
        info->freq[ i ]    = 1;
        info->low_cnt[ i ] = i;
    }
    info->total = tableSize;
}


/*---------------------------------------------------------------------------*
  Name:         RCAAddCount_

  Description:  Updates the frequency table for an adaptive range coder.

  Arguments:    info:  Table information for a range coder
                val:  Value to add

  Returns:      None.
 *---------------------------------------------------------------------------*/
void
RCAddCount_( RCCompressionInfo* info, u16 val )
{
    u32 i;
    u32 tableSize = (u32)(1 << info->bitSize);

    info->freq[ val ]++;
    info->total++;
    for ( i = (u32)(val + 1); i < tableSize; i++ )
    {
        info->low_cnt[ i ]++;
    }

    // Reconstruct if the total exceeds the maximum value.
    if ( info->total >= 0x00010000 )
    {
        if ( info->freq[ 0 ] > 1 )
        {
            info->freq[ 0 ] = info->freq[ 0 ] / 2;
        }
        info->low_cnt[ 0 ] = 0;
        info->total = info->freq[ 0 ];

        for ( i = 1; i < tableSize; i++ )
        {
            if ( info->freq[ i ] > 1 )
            {
                info->freq[ i ] >>= 1;
            }
            info->low_cnt[ i ] = info->low_cnt[ i - 1 ] + info->freq[ i - 1 ];
            info->total += info->freq[ i ];
        }
    }
}


/*---------------------------------------------------------------------------*
  Name:         RCSearch_

  Description:  Searches for the value that must be obtained next from the code, range, and low values.

  Arguments:    info:  Table information for a range coder
                code:  Current code value
                range: Current Range value
                low:   Current Low value

  Returns:
 *---------------------------------------------------------------------------*/
u16
RCSearch_( RCCompressionInfo* info, u32 code, u32 range, u32 low )
{
    u32 tableSize = (u32)(1 << info->bitSize);
    u32 codeVal = code - low;
    u32 i;
    u32 temp = range / info->total;
    u32 tempVal = codeVal / temp;

    // binary search
    u32 left  = 0;
    u32 right = tableSize - 1;

    while ( left < right )
    {
        i = (left + right) / 2;

        if ( info->low_cnt[ i ] > tempVal )
        {
            right = i;
        }
        else
        {
            left = i + 1;
        }
    }

    i = left;
    while ( info->low_cnt[ i ] > tempVal )
    {
        --i;
    }
    return (u16)i;
}


/*---------------------------------------------------------------------------*
  Name:         RCGetData_

  Description:  Gets the next value from the state in RCState, then updates the state.

  Arguments:    stream
                info
                state
                adaptive

  Returns:
 *---------------------------------------------------------------------------*/
u16
RCGetData_( const u8* srcp, RCCompressionInfo* info, RCState* state, u32 srcCnt, s32* pReadCnt )
{
#define MIN_RANGE 0x01000000
    u16 val = RCSearch_( info, state->code, state->range, state->low );
    s32 cnt = 0;

    {
        u32 tmp;
        tmp          =  state->range / info->total;
        state->low   += info->low_cnt[ val ] * tmp;
        state->range =  info->freq[ val ] * tmp;
    }

    // Update the table for occurrence frequency
    RCAddCount_( info, val );

    while ( state->range < MIN_RANGE )
    {
        if ( srcCnt == 0 )
        {
            cnt = (cnt < 0 )? ( cnt - 1 ) : ( -1 );
        }
        else
        {
            state->code  <<= 8;
            state->code  += srcp[ cnt++ ];
            --srcCnt;
        }
        state->range <<= 8;
        state->low   <<= 8;
    }
    *pReadCnt = cnt;

    return val;
#undef MIN_RANGE
}

}   // Namespace


/*---------------------------------------------------------------------------*
  Name:         InitUncompContextLRC

  Description:  Initializes the streaming decompression context for LZ/Range Coder (combined) compressed data.

  Arguments:    context Pointer to the decompressed context
                dest        Destination address for uncompressed data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void
InitUncompContextLRC( UncompContextLRC * context, void* dest )
{
    NN_NULL_TASSERT_(context);

#define LENGTH_BITS  9
#define OFFSET_BITS  12
    RCCompressionInfo info9;
    RCCompressionInfo info12;
    RCState           rcState;

    // Set up processing
    LRCIntro_( context, &info9, &info12, &rcState );

    context->destp       = static_cast<u8*>(dest);
    context->destCount   = 0;
    context->headerSize  = 8;
    context->length      = 0;
    context->forceDestCount = 0;

    context->codeLen = 4;

    RCInitInfo_( &info9, LENGTH_BITS );
    RCInitInfo_( &info12, OFFSET_BITS );

    RCInitState_( &rcState );

    // Stop processing
    LRCFin_( context, &info9, &info12, &rcState );

#undef LENGTH_BITS
#undef OFFSET_BITS
}


/*---------------------------------------------------------------------------*
  Name:         ReadUncompLRC

  Description:  This function performs streaming decompression of LZ/Range Coder (combined) compressed data.

  Arguments:    *context: Pointer to the decompressed context
                data     Data pointer
                len     Data size

  Returns:      Size of remaining uncompressed data
                Returns a negative error code if failed.
 *---------------------------------------------------------------------------*/
s32
ReadUncompLRC( UncompContextLRC *context, const void* data, u32 len )
{
    NN_NULL_TASSERT_(context);
    NN_NULL_TASSERT_(data);

    RCCompressionInfo info9;
    RCCompressionInfo info12;
    RCState           rcState;
    const u8*         srcp = (const u8*)data;

    // Set up processing
    LRCIntro_( context, &info9, &info12, &rcState );

    // Header parsing
    if ( context->headerSize > 0 )
    {
        u32 read_len;
        if ( context->headerSize == 8 )
        {
            if ( (*srcp & COMPRESSION_TYPE_MASK) != COMPRESSION_LRC )
            {
                return CX_ERR_UNSUPPORTED;
            }
            if ( (*srcp & 0x0F) != 0 )
            {
                return CX_ERR_UNSUPPORTED;
            }
        }

        read_len = ReadHeader( &context->headerSize, &context->destCount, srcp, len, context->forceDestCount );
        srcp += read_len;
        len  -= read_len;
        if ( len == 0 )
        {
            return (context->headerSize == 0)? context->destCount : -1;
        }
    }

    // load the code
    while ( context->codeLen > 0 )
    {
        if ( len == 0 )
        {
            goto out;
        }
        rcState.code <<= 8;
        rcState.code += *srcp;
        ++srcp;
        --len;
        --context->codeLen;
    }

    while ( context->destCount > 0 )
    {
        // get the value for length
        if ( context->length == 0 )
        {
            s32 cnt;
            u16 val = RCGetData_( srcp, &info9, &rcState, len, &cnt );

            if ( val < 0x100 )
            // uncompressed data
            {
                *context->destp++  = (u8)val;
                context->destCount--;
            }
            else
            // compressed data
            {
                context->length = (u16)( (val & 0xFF) + 3 );
            }

            // prepare to read the next data
            if ( cnt < 0 )
            {
                context->codeLen = (u8)( -cnt );
                goto out;
            }
            srcp += cnt;
            len  -= cnt;
        }

        // Expanding compressed data
        if ( context->length > 0 )
        {
            s32 cnt;
            u16 val = (u16)( RCGetData_( srcp, &info12, &rcState, len, &cnt ) + 1 );

            // Measures for buffer overrun when invalid data is decompressed.
            if ( context->length > context->destCount )
            {
                if ( context->forceDestCount == 0 )
                {
                    return CX_ERR_DEST_OVERRUN;
                }
                context->length = (u16)( context->destCount );
            }

            while ( context->length > 0 )
            {
                *context->destp = context->destp[ -val ];
                context->destp++;
                context->destCount--;
                context->length--;
            }
            // advance the load position
            if ( cnt < 0 )
            {
                context->codeLen = (u8)( -cnt );
                goto out;
            }
            srcp += cnt;
            len  -= cnt;
        }
    }
out:
    // Stop processing
    LRCFin_( context, &info9, &info12, &rcState );

    // After decompression, remaining source data will be treated as an error
    if ( (context->destCount      == 0) &&
         (context->forceDestCount == 0) &&
         (len > 32)                     )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return context->destCount;
}

    namespace
    {
        void InitUncompressContextDeflateCommon( UncompContextDeflate* pContext, void* pDest, size_t destSize, int wbits )
        {
            NN_POINTER_TASSERT_(pContext);
            NN_POINTER_TASSERT_(pDest);

            UncompressContextDeflate_* pucd = GetUncompressContextDeflate_(pContext);
            pucd->headerSize = 0;
            pucd->rawSize    = 0;

            new (&pucd->za) detail::ZlibAllocator(pucd->workBuffer, sizeof(pucd->workBuffer));

            z_stream& s = pucd->s;
            int err NN_IS_UNUSED_VAR;

            s.next_in   = NULL;
            s.avail_in  = 0;
            s.next_out  = reinterpret_cast<nncxZlib_Bytef*>(pDest);
            s.avail_out = destSize;

            s.zalloc    = detail::ZlibAllocator::Allocate;
            s.zfree     = detail::ZlibAllocator::Free;
            s.opaque    = &pucd->za;

            err = inflateInit2(&s, wbits);
            NN_TASSERT_( err == Z_OK );
        }

        s32 ReadUncompressDeflateCommon( UncompContextDeflate* pContext, const void* pData, size_t dataSize )
        {
            NN_POINTER_TASSERT_(pContext);
            NN_POINTER_TASSERT_(pData);

            z_stream& s = GetUncompressContextDeflate_(pContext)->s;
            int err;

            s.next_in   = reinterpret_cast<nncxZlib_Bytef*>(const_cast<void*>(pData));
            s.avail_in  = dataSize;

            const u32 availOutBefore = s.avail_out;
            err = nncxZlib_inflate(&s, Z_NO_FLUSH);

            if (err != Z_OK)
            {
                if( err == Z_STREAM_END )
                {
                    err = nncxZlib_inflate(&s, Z_FINISH);
                }
                nncxZlib_deflateEnd(&s);
            }

            s32 cxErr = detail::ConvertZlibReturnCode(err);
            if( cxErr != ERROR_CODE_SUCCESS )
            {
                return cxErr;
            }

            const u32 outSize = availOutBefore - s.avail_out;
            return outSize;
        }
    }

void InitUncompContextDeflate( UncompContextDeflate* pContext, void* pDest, size_t destSize )
{
    NN_POINTER_TASSERT_(pContext);
    NN_POINTER_TASSERT_(pDest);

    const int wbits = - MAX_WBITS;          // Specify - = raw deflate format
    InitUncompressContextDeflateCommon(pContext, pDest, destSize, wbits);
}

void InitUncompContextGzip( UncompContextGzip* pContext, void* pDest, size_t destSize )
{
    NN_POINTER_TASSERT_(pContext);
    NN_POINTER_TASSERT_(pDest);

    const int wbits = MAX_WBITS + 16;       // Specify +16 = gzip format
    InitUncompressContextDeflateCommon(pContext, pDest, destSize, wbits);
}

void InitUncompContextZlib( UncompContextZlib* pContext, void* pDest, size_t destSize )
{
    NN_POINTER_TASSERT_(pContext);
    NN_POINTER_TASSERT_(pDest);

    InitUncompressContextDeflateCommon(pContext, pDest, destSize, MAX_WBITS);
}

s32 ReadUncompDeflate( UncompContextDeflate* pContext, const void* pData, size_t dataSize )
{
    NN_POINTER_TASSERT_(pContext);
    NN_POINTER_TASSERT_(pData);

    UncompressContextDeflate_* pucd = GetUncompressContextDeflate_(pContext);

    if( pucd->headerSize < 8 )
    {
        if( pucd->headerSize < 4 )
        {
            int copySize = math::Min<int>(dataSize, 4 - pucd->headerSize);
            std::memcpy( reinterpret_cast<bit8*>(&pucd->rawSize) + pucd->headerSize,
                         pData,
                         copySize );
            pData            = reinterpret_cast<const bit8*>(pData) + copySize;
            dataSize         -= copySize;
            pucd->headerSize += copySize;

            if( pucd->headerSize < 4 )
            {
                return ERROR_CODE_DATA_SHORTAGE;
            }

            u32 size = (internal::Read32Le(reinterpret_cast<bit8*>(&pucd->rawSize)) >> 8);

            if( size > 0 )
            {
                pucd->headerSize = 8;
                pucd->rawSize    = size;
            }
        }

        NN_TASSERT_( pucd->headerSize >= 4 );

        if( pucd->headerSize < 8 )
        {
            int copySize = math::Min<int>(dataSize, 8 - pucd->headerSize);
            std::memcpy( reinterpret_cast<bit8*>(&pucd->rawSize) + pucd->headerSize - 4,
                         pData,
                         copySize );
            pData            = reinterpret_cast<const bit8*>(pData) + copySize;
            dataSize         -= copySize;
            pucd->headerSize += copySize;

            if( pucd->headerSize < 8 )
            {
                return ERROR_CODE_DATA_SHORTAGE;
            }

            pucd->rawSize = internal::Read32Le(reinterpret_cast<bit8*>(&pucd->rawSize));
        }
    }

    s32 ret = ReadUncompressDeflateCommon(pContext, pData, dataSize);
    
    if( ret > 0 )
    {
        pucd->rawSize -= ret;
        return pucd->rawSize;
    }
    else
    {
        return ret;
    }
}

s32 ReadUncompGzip( UncompContextGzip* pContext, const void* pData, size_t dataSize )
{
    NN_POINTER_TASSERT_(pContext);
    NN_POINTER_TASSERT_(pData);

    return ReadUncompressDeflateCommon(pContext, pData, dataSize);
}

s32 ReadUncompZlib( UncompContextZlib* pContext, const void* pData, size_t dataSize )
{
    NN_POINTER_TASSERT_(pContext);
    NN_POINTER_TASSERT_(pData);

    return ReadUncompressDeflateCommon(pContext, pData, dataSize);
}

}   // namespace cx
}   // namespace nn
