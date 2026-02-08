/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_SecureUncompression.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47707 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/os.h>
#include <nn/cx/cx_Uncompression.h>
#include <nn/cx/cx_SecureUncompression.h>
#include "cx_Utility.h"

namespace nn {
namespace cx {

//======================================================================
//          Expanding compressed data
//======================================================================

/*---------------------------------------------------------------------------*
  Name:         SecureUncompressAny

  Description:  Determines the compression type from the data header and executes the appropriate decompression process.
                
                Because the decompression processes for all of the compression types are linked, it may be good to execute a function for each compression type when only specific compression formats are used.
                
                

  Arguments:    srcp    Source address
                srcSize Source size
                destp   Destination address

  Returns:      Returns 0 when conversion succeeds
                Returns a negative error code if failed
 *---------------------------------------------------------------------------*/
s32 SecureUncompressAny( const void* srcp, u32 srcSize, void* destp )
{
    NN_NULL_TASSERT_(srcp);

    switch ( GetCompressionType( srcp ) )
    {
    // Run-length compressed data
    case COMPRESSION_RL:
        return SecureUncompressRL( srcp, srcSize, destp );
    // LZ77-compressed data
    case COMPRESSION_LZ:
        return SecureUncompressLZ( srcp, srcSize, destp );
    // Huffman-compressed data
    case COMPRESSION_HUFFMAN:
        return SecureUncompressHuffman( srcp, srcSize, destp );
    // Difference filter
    case COMPRESSION_DIFF:
        return SecureUnfilterDiff( srcp, srcSize, destp );
    default:
        return CX_ERR_UNSUPPORTED;
    }
}


/*---------------------------------------------------------------------------*
  Name:         SecureUncompressRL

  Description:  8-bit decompression of run-length compressed data

  - Decompresses run-length compressed data, writing in 8 bit units.
  - Use 4 byte alignment for the source address.

  - Data header
      u32 :4  :                Reserved
          compType:4          Compression type( = 3)
          destSize:24         Data size after decompression

  - Flag data format
      u8  length:7            Decompressed data length - 1 (When not compressed)
                              Decompressed data length - 3 (only compress when the contiguous length is 3 bytes or greater)
          flag:1              (0, 1) = (not compressed, compressed)

  Arguments:    *srcp   Source address
                srcSize Source size
                *destp  Destination address

  Returns:      Returns 0 when conversion succeeds
                Returns a negative error code if failed
 *---------------------------------------------------------------------------*/
s32 SecureUncompressRL( const void *srcp, u32 srcSize, void *destp )
{
    NN_NULL_TASSERT_(srcp);
    NN_NULL_TASSERT_(destp);

    const u8 *pSrc  = static_cast<const u8*>(srcp);
    u8       *pDst  = static_cast<u8*>(destp);
    u8       compType  = *pSrc;
    u32      destCount = internal::Read32Le(pSrc) >> 8;
    s32      srcCount  = (s32)srcSize;

    if ( (compType & COMPRESSION_TYPE_MASK) != COMPRESSION_RL )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( (compType & 0xF) != 0 )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( srcSize <= 4 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    pSrc     += 4;
    srcCount -= 4;

    if ( destCount == 0 )
    {
        if ( srcCount < 4 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }
        destCount = internal::Read32Le(pSrc);
        pSrc     += 4;
        srcCount -= 4;
    }

    while ( destCount > 0 )
    {
        u8  flags  = *pSrc++;
        u32 length = flags & 0x7f;
        if ( --srcCount < 0 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }

        if ( !(flags & 0x80) )
        {
            length++;
            if ( length > destCount )
            // Measures for buffer overrun when invalid data is decompressed.
            {
                return CX_ERR_DEST_OVERRUN;
            }
            srcCount -= length;
            if ( srcCount < 0 )
            {
                return CX_ERR_SRC_SHORTAGE;
            }

            destCount -= length;
            do
            {
                *pDst++ = *pSrc++;
            } while ( --length > 0 );
        }
        else
        {
            u8 srcTmp;

            length    += 3;
            if ( length > destCount )
            // Measures for buffer overrun when invalid data is decompressed.
            {
                return CX_ERR_DEST_OVERRUN;
            }

            destCount -= length;
            srcTmp    = *pSrc++;
            if ( --srcCount < 0 )
            {
                return CX_ERR_SRC_SHORTAGE;
            }
            do
            {
                *pDst++ =  srcTmp;
            } while ( --length > 0 );
        }
    }

    if ( srcCount > 32 )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return CX_ERR_SUCCESS;
}


/*---------------------------------------------------------------------------*
  Name:         SecureUncompressLZ

  Description:  8-bit decompression of LZ77 compressed data

  * Expands LZ77-compressed data and writes it in 8-bit units.
  - Use 4 byte alignment for the source address.

  - Data header
      u32 :4  :                Reserved
          compType:4          Compression type( = 1)
          destSize:24         Data size after decompression

  - Flag data format
      u8  flags               Compression/no compression flag
                              (0, 1) = (not compressed, compressed)
  - Code data format (Big Endian)
      u16 length:4            Decompressed data length - 3 (only compress when the match length is 3 bytes or greater)
          offset:12           Match data offset - 1

  Arguments:    *srcp   Source address
                srcSize Source size
                *destp  Destination address

  Returns:      Returns 0 when conversion succeeds
                Returns a negative error code if failed
 *---------------------------------------------------------------------------*/
s32 SecureUncompressLZ( const void *srcp, u32 srcSize, void *destp )
{
    NN_NULL_TASSERT_(srcp);
    NN_NULL_TASSERT_(destp);

    const u8* pSrc      = static_cast<const u8*>(srcp);
    u8*       pDst      = static_cast<u8*>(destp);
    u8        compType  = *pSrc;
    u32       destCount = internal::Read32Le(pSrc) >> 8;
    s32       srcCount  = (s32)srcSize;
    bool      exFormat  = (*pSrc & 0x0F)? true : false;

    if ( (compType & COMPRESSION_TYPE_MASK) != COMPRESSION_LZ )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( ((compType & 0xF) != 0x0) && ((compType & 0xF) != 0x1) )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( srcSize <= 4 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    pSrc += 4;
    srcCount -= 4;

    if ( destCount == 0 )
    {
        if ( srcCount < 4 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }

        destCount = internal::Read32Le(pSrc);
        pSrc += 4;
        srcCount -= 4;
    }

    while ( destCount > 0 )
    {
        u32 i;
        u32 flags = *pSrc++;
        if ( --srcCount < 0 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }

        for ( i = 0; i < 8; ++i )
        {
            if ( !(flags & 0x80) )
            {
                *pDst++ = *pSrc++;
                if ( --srcCount < 0 )
                {
                    return CX_ERR_SRC_SHORTAGE;
                }
                destCount--;
            }
            else
            {
                u32 length = (*pSrc >> 4);
                s32 offset;

                if ( ! exFormat )
                {
                    length += 3;
                }
                else
                {
                    // LZ77 extended format
                    if ( length == 1 )
                    {
                        length =  (*pSrc++ & 0x0F) << 12;
                        length |= (*pSrc++) << 4;
                        length |= (*pSrc >> 4);
                        length += 0xFF + 0xF + 3;
                        srcCount -= 2;
                    }
                    else if ( length == 0 )
                    {
                        length =  (*pSrc++ & 0x0F) << 4;
                        length |= (*pSrc >> 4);
                        length += 0xF + 2;
                        srcCount -= 1;
                    }
                    else
                    {
                        length += 1;
                    }
                }
                offset  = (*pSrc++ & 0x0f) << 8;
                offset = (offset | *pSrc++) + 1;

                srcCount -= 2;
                if ( srcCount < 0 )
                {
                    return CX_ERR_SRC_SHORTAGE;
                }

                // Measures for buffer overrun when invalid data is decompressed.
                if ( length > destCount )
                {
                    return CX_ERR_DEST_OVERRUN;
                }
                if ( &pDst[ -offset ] < destp )
                {
                    return CX_ERR_DEST_OVERRUN;
                }

                destCount -= length;
                do
                {
                    *pDst++ = pDst[ -offset ];
                } while ( --length > 0 );
            }
            if ( destCount <= 0 )
            {
                break;
            }
            flags <<= 1;
        }
    }

    if ( srcCount > 32 )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return CX_ERR_SUCCESS;
}


namespace internal {

/*---------------------------------------------------------------------------*
  Name:         VerifyHuffmanTable

  Description:  Huffman table integrity check

  Arguments:    Pointer to the Huffman table

  Returns:      true when the table is valid
                false when the table is invalid
 *---------------------------------------------------------------------------*/
bool
VerifyHuffmanTable( const void* pTable, u8 bit )
{
    const u32 FLAGS_ARRAY_NUM = 512 / 8; /* 64 Bytes */
    u8* treep = (u8*)pTable;
    u8* treeStartp = treep + 1;
    u32 treeSize   = *treep;
    u8* treeEndp   = (u8*)pTable + (treeSize + 1) * 2;
    u32 i;
    u8  end_flags[ FLAGS_ARRAY_NUM ];
    u32 idx;

    for ( i = 0; i < FLAGS_ARRAY_NUM; i++ )
    {
        end_flags[ i ] = 0;
    }

    if ( bit == 4 )
    {
        if ( treeSize >= 0x10 )
        {
            return false;
        }
    }

    idx = 1;
    treep = treeStartp;
    while ( treep < treeEndp )
    {
        if ( (end_flags[ idx / 8 ] & (1 << (idx % 8) )) == 0 )
        {
            u32  offset = (u32)( ( (*treep & 0x3F) + 1 ) << 1);
            u8*  nodep  = (u8*)( (((u32)treep >> 1) << 1) + offset );

            // Skip data added at the end for alignment.
            if ( *treep == 0 && idx >= (treeSize * 2) )
            {
                goto next;
            }

            if ( nodep >= treeEndp )
            {
                return false;
            }
            if ( *treep & 0x80 )
            {
                u32 left = (idx & ~0x1) + offset;
                end_flags[ left / 8 ] |= (u8)( 1 << (left % 8) );
            }
            if ( *treep & 0x40 )
            {
                u32 right = (idx & ~0x1) + offset + 1;
                end_flags[ right / 8 ] |= (u8)( 1 << (right % 8) );
            }
        }
    next:
        ++idx;
        ++treep;
    }
    return true;
}

}   // namespace internal

/*---------------------------------------------------------------------------*
  Name:         SecureUncompressHuffman

  Description:  Decompression of Huffman compressed data

  - Decompresses Huffman compressed data, writing in 32 bit units.
  - Use 4 byte alignment for the source address.
  - Use 4-byte alignment for the destination address.
  - The target decompression buffer size must be prepared in 4-byte multiples.

  - Data header
      u32 bitSize:4           1 data bit size (Normally 4|8)
          compType:4          Compression type( = 2)
          destSize:24         Data size after decompression

  - Tree table
      u8           treeSize        Tree table size/2 - 1
      TreeNodeData nodeRoot        Root node

      TreeNodeData nodeLeft        Root left node
      TreeNodeData nodeRight       Root right node

      TreeNodeData nodeLeftLeft    Left left node
      TreeNodeData nodeLeftRight   Left right node

      TreeNodeData nodeRightLeft   Right left node
      TreeNodeData nodeRightRight  Right right node

      .
      .

    The compressed data itself follows

  - TreeNodeData structure
      u8  nodeNextOffset:6 :   Offset to the next node data - 1 (2 byte units)
          rightEndFlag:1      Right node end flag
          leftEndzflag:1      Left node end flag
                              When the end flag is set
                              There is data in next node

  Arguments:    *srcp   Source address
                srcSize Source size
                *destp  Destination address

  Returns:      Returns 0 when conversion succeeds
                Returns a negative error code if failed
 *---------------------------------------------------------------------------*/
s32 SecureUncompressHuffman( const void *srcp, u32 srcSize, void *destp )
{
    NN_NULL_TASSERT_(srcp);
    NN_NULL_TASSERT_(destp);
    NN_CX_CHECK_ALIGN(srcp, sizeof(u32));
    NN_CX_CHECK_ALIGN(destp, sizeof(u32));

#define TREE_END 0x80
    const u32 *pSrc          = static_cast<const u32*>(srcp);
    u32       *pDst          = static_cast<u32*>(destp);
    u8        compType       = (u8)( internal::ConvertEndian( *pSrc ) & 0xFF );
    s32       destCount      = (s32)( internal::ConvertEndian( *pSrc ) >> 8 );
    u8        *treep         = (destCount != 0)? ((u8*)pSrc + 4) : ((u8*)pSrc + 8);
    u8        *treeStartp    = treep + 1;
    u32       dataBit        = *(u8*)pSrc & 0x0FU;
    u32       destTmp        = 0;
    u32       destTmpCount   = 0;
    u32       destTmpDataNum = 4 + ( dataBit & 0x7 );
    s32       srcCount       = (s32)srcSize;
    u32       treeSize       = (u32)( (*treep + 1) << 1 );

    if ( (compType & COMPRESSION_TYPE_MASK) != COMPRESSION_HUFFMAN )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( (dataBit != 4) && (dataBit != 8) )
    {
        return CX_ERR_UNSUPPORTED;
    }

    if ( destCount == 0 )
    {
        if ( srcSize < 8 + treeSize )
        {
            return CX_ERR_SRC_SHORTAGE;
        }
        destCount = (s32)( internal::ConvertEndian( *(pSrc + 1) ) );
    }
    else if ( srcSize < 4 + treeSize )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    if ( ! internal::VerifyHuffmanTable(treep, (u8)dataBit) )
    {
        return CX_ERR_ILLEGAL_TABLE;
    }

    pSrc  = (u32*)( treep + treeSize );
    srcCount -= ( (u32)pSrc - (u32)srcp );

    if ( srcCount < 0 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    treep = treeStartp;

    while ( destCount > 0 )
    {
        s32 srcTmpCount = 32;
        u32 srcTmp   = internal::ConvertEndian( *pSrc++ );      // Endian strategy
        srcCount -= 4;
        if ( srcCount < 0 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }

        while ( --srcTmpCount >= 0 )
        {
            u32 treeShift = (srcTmp >> 31) & 0x1;
            u32 treeCheck = *treep;
            treeCheck <<= treeShift;
            treep = (u8*)( (((u32)treep >> 1) << 1) + (((*treep & 0x3f) + 1) << 1) + treeShift );
            if ( treeCheck & TREE_END )
            {
                destTmp >>= dataBit;
                destTmp |= *treep << (32 - dataBit);
                treep = treeStartp;
                ++destTmpCount;

                if ( destCount <= (s32)((destTmpCount * dataBit) / 8) )
                {
                    destTmp >>= (destTmpDataNum - destTmpCount) * dataBit;
                    destTmpCount = destTmpDataNum;
                }

                if ( destTmpCount == destTmpDataNum )
                {
                    // Over-access until the last 4-byte alignment of the decompression buffer
                    *pDst++ = internal::ConvertEndian(destTmp); // Endian strategy
                    destCount -= 4;
                    destTmpCount = 0;
                }
            }
            if ( destCount <= 0 )
            {
                break;
            }
            srcTmp <<= 1;
        }
    }
    if ( srcCount > 32 )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return CX_ERR_SUCCESS;
}


namespace {

/*---------------------------------------------------------------------------*
  Name:         HuffImportTree

  Description:  Decompresses a resource's Huffman table into the work buffer.

  Arguments:    pTable:        Pointer to a buffer for decompressing the Huffman table
                srcp:          Pointer to the resource data
                bitSize:       Size (in bits) of the Huffman table elements
                srcRemainSize: Valid remaining data size contained in srcp

  Returns:      Returns the actual data size loaded from the resource.
 *---------------------------------------------------------------------------*/
u32
HuffImportTree( u16* pTable, const u8* srcp, u8 bitSize, u32 srcRemainSize )
{
    u32 tableSize;
    u32 idx     = 1;
    u32 data    = 0;
    u32 bitNum  = 0;
    u32 bitMask = (1 << bitSize) - 1U;
    u32 srcCnt  = 0;
    const u32 MAX_IDX = (u32)( (1 << bitSize) * 2 );

    // The number of Huffman table elements is in srcp.
    // When bitSize is 8 or less, the range is from 0 to 255 and can therefore fit within 1 byte.
    // Beyond that, the size information is stored across 2 bytes.
    if ( bitSize > 8 )
    {
        tableSize = internal::ConvertEndian16( *(u16*)srcp );
        srcp   += 2;
        srcCnt += 2;
    }
    else
    {
        tableSize = *srcp;
        srcp   += 1;
        srcCnt += 1;
    }

    // The actual number of table bytes is sizeof(u16) * 2
    tableSize = (tableSize + 1) * 4;

    if ( srcRemainSize < tableSize )
    {
        return tableSize;
    }

    while ( srcCnt < tableSize || bitSize <= bitNum )
    {
        while ( bitNum < bitSize )
        {
            data <<= 8;
            data |= *srcp++;
            ++srcCnt;
            bitNum += 8;
        }
        if ( idx < MAX_IDX )
        {
            pTable[ idx++ ] = (u16)( ( data >> (bitNum - bitSize) ) & bitMask );
        }
        bitNum -= bitSize;
    }

    pTable[0] = (u16)idx;

    return tableSize;
}

}   // Namespace

/*---------------------------------------------------------------------------*
  Name:         SecureUnfilterDiff

  Description:  8-bit decompression to restore differential filter conversion.

    - Restores a differential filter, writing in 8 bit units.
    - Use 4 byte alignment for the source address.

  Arguments:    *srcp   Source address
                *destp  Destination address

  Returns:      Returns 0 when conversion succeeds
                Returns a negative error code if failed
 *---------------------------------------------------------------------------*/
s32 SecureUnfilterDiff( register const void *srcp, u32 srcSize, register void *destp )
{
    NN_NULL_TASSERT_(srcp);
    NN_NULL_TASSERT_(destp);

    const u8* pSrc = static_cast<const u8*>(srcp);
    u8*       pDst = static_cast<u8*>(destp);
    u32       bitSize    = *pSrc & 0xFU;
    u8        compType   = *pSrc;
    s32       destCount  = (s32)( internal::Read32Le(pSrc) >> 8 );
    u32       sum = 0;
    s32       srcCount  = (s32)srcSize;

    if ( (compType & COMPRESSION_TYPE_MASK) != COMPRESSION_DIFF )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( (bitSize != 1) && (bitSize != 2) )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( srcSize <= 4 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    pSrc     += 4;
    srcCount -= 4;

    if ( bitSize == 1 )
    {
        // Difference calculation in units of 8 bits
        do
        {
            u8 tmp = *(pSrc++);
            if ( --srcCount < 0 )
            {
                return CX_ERR_SRC_SHORTAGE;
            }
            destCount--;
            sum += tmp;
            *(pDst++) = (u8)sum;
        } while ( destCount > 0 );
    }
    else
    {
        NN_CX_CHECK_ALIGN(srcp, sizeof(u16));
        NN_CX_CHECK_ALIGN(destp, sizeof(u16));

        // Difference calculation in units of 16 bits
        do
        {
            u16 tmp = internal::ConvertEndian16( *(u16*)pSrc );
            pSrc += 2;
            srcCount -= 2;
            if ( srcCount < 0 )
            {
                return CX_ERR_SRC_SHORTAGE;
            }
            destCount -= 2;
            sum += tmp;
            *(u16*)pDst = internal::ConvertEndian16( (u16)sum );
            pDst += 2;
        } while ( destCount > 0 );
    }
    if ( srcCount > 32 )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return CX_ERR_SUCCESS;
}

namespace {

struct BitReader
{
   const u8* srcp;
   u32       cnt;
   u32       stream;
   u32       stream_len;
   u32       srcSize;
};

inline void
BitReader_Init( BitReader* context, const u8* srcp, u32 srcSize )
{
    context->srcp       = srcp;
    context->cnt        = 0;
    context->stream     = 0;
    context->stream_len = 0;
    context->srcSize    = srcSize;
}

s8
BitReader_Read( BitReader* context )
{
    s8 bit;
    if ( context->stream_len == 0 )
    {
        if ( context->cnt > context->srcSize )
        {
            return -1;
        }

        context->stream     = context->srcp[context->cnt++];
        context->stream_len = 8;
    }
    bit = (s8)( (context->stream >> (context->stream_len - 1)) & 0x1 );
    context->stream_len--;
    return bit;
}

}   // Namespace

#define ENC_OFFSET_WIDTH

namespace internal {

/*---------------------------------------------------------------------------*
  Name:         LHVerifyTable

  Description:  Huffman table integrity check

  Arguments:    pTable: Pointer to the Huffman table
                bit:    Number of bits used by the Huffman coding

  Returns:      true when the table is valid
                false when the table is invalid
 *---------------------------------------------------------------------------*/
bool
LHVerifyTable( const void* pTable, u8 bit )
{
#if !defined(ENC_OFFSET_WIDTH)
    enum { FLAGS_ARRAY_NUM = 8192 / 8 }; /* 1024 Bytes */
    static u8  end_flags[ FLAGS_ARRAY_NUM ];
#else
    enum { FLAGS_ARRAY_NUM = 1024 / 8 };  /* 128 Bytes */
    u8  end_flags[ FLAGS_ARRAY_NUM ];
#endif
    u16*  treep = (u16*)pTable;
    u16*  treeStartp = treep + 1;
    u32   treeSize   = *treep;
    u16*  treeEndp   = (u16*)pTable + treeSize;
    u32 i;
    u32 idx;
    const u16 ofs_mask = (u16)( (1 << (bit - 2)) - 1 );
    const u16 l_mask   = (u16)( 1 << (bit - 1) );
    const u16 r_mask   = (u16)( 1 << (bit - 2) );

    for ( i = 0; i < FLAGS_ARRAY_NUM; i++ )
    {
        end_flags[ i ] = 0;
    }

    if ( treeSize > (1U << (bit + 1)) )
    {
        return false;
    }

    idx = 1;
    treep = treeStartp;
    while ( treep < treeEndp )
    {
        if ( (end_flags[ idx / 8 ] & (1 << (idx % 8) )) == 0 )
        {
            u32  offset = (u32)( ( (*treep & ofs_mask) + 1 ) << 1 );
            u16* nodep  = (u16*)((u32)treep & ~0x3) + offset;

            // Skip data added at the end for alignment.
            if ( *treep == 0 && idx >= treeSize - 4 )
            {
                goto next;
            }
            if ( nodep >= treeEndp )
            {
                return false;
            }
            if ( *treep & l_mask )
            {
                u32 left = (idx & ~0x1) + offset;
                end_flags[ left / 8 ] |= (u8)( 1 << (left % 8) );
            }
            if ( *treep & r_mask )
            {
                u32 right = (idx & ~0x1) + offset + 1;
                end_flags[ right / 8 ] |= (u8)( 1 << (right % 8) );
            }
        }
    next:
        ++idx;
        ++treep;
    }
    return true;
}

}   // namespace internal

/*---------------------------------------------------------------------------*
  Name:         UncompressLH

  Description:  Decompress LZ-Huffman (combined) compression.

  Arguments:    *srcp   Source address
                srcSize Source size
                *destp  Destination address
                *work   Working buffer
                        The required size is UNCOMPRESS_LH_WORK_SIZE (18 KB)

  Returns:      Returns 0 when conversion succeeds
                Returns a negative error code if failed
 *---------------------------------------------------------------------------*/
s32
SecureUncompressLH( const u8* srcp, u32 srcSize, u8* dstp, void* work )
{
    NN_NULL_TASSERT_(srcp);
    NN_NULL_TASSERT_(dstp);
    NN_NULL_TASSERT_(work);
    NN_CX_CHECK_ALIGN(srcp, sizeof(u32));
    NN_CX_CHECK_ALIGN(work, sizeof(u16));

#define LENGTH_BITS  9
#if defined(ENC_OFFSET_WIDTH)
    #define OFFSET_BITS  5
    #define OFFSET_MASK  0x07
    #define LEAF_FLAG    0x10
    u16 offset_bit;
#else
    #define OFFSET_BITS  12
    #define OFFSET_MASK  0x3FF
    #define LEAF_FLAG    0x800
#endif
    u32       dstSize;
    u32       dstCnt = 0;
    const u8  *pSrc  = srcp;
    BitReader stream;
    u16* huffTable9;    // Huffman table for length
    u16* huffTable12;   // Huffman table for offset

    if ( (*srcp & COMPRESSION_TYPE_MASK) != COMPRESSION_LH )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( srcSize <= 4 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    huffTable9  = static_cast<u16*>(work);
    huffTable12 = (u16*)work + (1 << LENGTH_BITS) * 2;

    // For checking out-of-bounds accesses in the Huffman table (TODO: Not yet used)
    // u8*  verify_work = (u8*)work + UNCOMPRESS_LH_WORK_SIZE;

    // load the header
    dstSize = internal::Read32Le(pSrc) >> 8;
    pSrc += 4;
    if ( dstSize == 0 )
    {
        dstSize = internal::Read32Le(pSrc);
        pSrc += 4;
        if ( srcSize < 8 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }
    }

    // read the Huffman table
    pSrc += HuffImportTree( huffTable9,  pSrc, LENGTH_BITS, srcSize - ((u32)pSrc - (u32)srcp) );
    if ( pSrc > srcp + srcSize )
    {
        return CX_ERR_SRC_SHORTAGE;
    }
    if ( ! internal::LHVerifyTable( huffTable9, LENGTH_BITS ) )
    {
        return CX_ERR_ILLEGAL_TABLE;
    }
    pSrc += HuffImportTree( huffTable12, pSrc, OFFSET_BITS, srcSize - ((u32)pSrc - (u32)srcp) );
    if ( pSrc > srcp + srcSize )
    {
        return CX_ERR_SRC_SHORTAGE;
    }
    if ( ! internal::LHVerifyTable( huffTable12, OFFSET_BITS ) )
    {
        return CX_ERR_ILLEGAL_TABLE;
    }

    BitReader_Init( &stream, pSrc, srcSize - ((u32)pSrc - (u32)srcp) );

    while ( dstCnt < dstSize )
    {
        u16  val;
        {
            u16* nodep = huffTable9 + 1;
            do
            {
                s8  bit    = BitReader_Read( &stream );
                u32 offset = (((*nodep & 0x7F) + 1U) << 1) + bit;
                if ( bit < 0 )
                {
                    return CX_ERR_SRC_SHORTAGE;
                }

                if ( *nodep & (0x100 >> bit) )
                {
                    nodep = (u16*)((u32)nodep & ~0x3);
                    val  = *(nodep + offset);
                    break;
                }
                else
                {
                    nodep = (u16*)((u32)nodep & ~0x3);
                    nodep += offset;
                }
            } while ( 1 );
        }

        if ( val < 0x100 )
        // uncompressed data
        {
            dstp[dstCnt++] = (u8)val;
        }
        else
        // compressed data
        {
            u16 length = (u16)( (val & 0xFF) + 3 );
            u16* nodep = huffTable12 + 1;
            do
            {
                s8  bit    = BitReader_Read( &stream );
                u32 offset = (((*nodep & OFFSET_MASK) + 1U) << 1) + bit;

                if ( bit < 0 )
                {
                    return CX_ERR_SRC_SHORTAGE;
                }

                if ( *nodep & (LEAF_FLAG >> bit) )
                {
                    nodep = (u16*)((u32)nodep & ~0x3);
                    val   = *(nodep + offset);
                    break;
                }
                else
                {
                    nodep = (u16*)((u32)nodep & ~0x3);
                    nodep += offset;
                }
            } while ( 1 );

        #if defined(ENC_OFFSET_WIDTH)
            offset_bit = val;
            val = 0;
            if ( offset_bit > 0 )
            {
                val = 1;
                while ( --offset_bit > 0 )
                {
                    val <<= 1;
                    val |= BitReader_Read( &stream );
                }
            }
        #endif
            val += 1;

            if ( dstCnt < val )
            {
                return CX_ERR_DEST_OVERRUN;
            }
            if ( dstCnt + length > dstSize )
            {
                return CX_ERR_DEST_OVERRUN;
            }

            while ( length-- > 0 )
            {
                dstp[dstCnt] = dstp[dstCnt - val];
                ++dstCnt;
            }
        }
    }

    if ( stream.srcSize - stream.cnt > 32 )
    {
        return CX_ERR_SRC_REMAINDER;
    }

    return CX_ERR_SUCCESS;

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
  Name:         RCInitState_

  Description:  Initializes the RC state.

  Arguments:    state: Pointer to an RC state structure

  Returns:      None.
 *---------------------------------------------------------------------------*/
inline void
RCInitState_( RCState* state )
{
    // The starting range is 0x80000000, so a carry will not suddenly occur the first time
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
RCInitInfo_( RCCompressionInfo* info, u8 bitSize, void* work )
{
    u32 tableSize = (u32)(1 << bitSize);
    u32 i;

    info->bitSize = bitSize;
    info->freq    = (u32*)work;
    info->low_cnt = (u32*)( (u32)work + tableSize * sizeof(u32) );

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
RCGetData_( const u8* srcp, RCCompressionInfo* info, RCState* state, u32* pSrcCnt )
{
#define MIN_RANGE 0x01000000
    u16 val = RCSearch_( info, state->code, state->range, state->low );
    u32 cnt = 0;

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
        state->code  <<= 8;
        state->code  += srcp[ cnt++ ];
        state->range <<= 8;
        state->low   <<= 8;
    }
    *pSrcCnt = cnt;

    return val;
#undef MIN_RANGE
}

}   // Namespace

/*---------------------------------------------------------------------------*
  Name:         SecureUncompressLRC

  Description:  LZ/Range Coder combined compression

  Arguments:    srcp
                dstp
                work

  Returns:      None.
 *---------------------------------------------------------------------------*/
s32
SecureUncompressLRC( const u8* srcp, u32 srcSize, u8* dstp, void* work )
{
    NN_NULL_TASSERT_(srcp);
    NN_NULL_TASSERT_(dstp);
    NN_NULL_TASSERT_(work);
    NN_CX_CHECK_ALIGN(srcp, sizeof(u32));
    NN_CX_CHECK_ALIGN(work, sizeof(u32));

#define LENGTH_BITS  9
#define OFFSET_BITS  12
    RCCompressionInfo infoVal;
    RCCompressionInfo infoOfs;
    RCState           rcState;
    const u8*         pSrc = srcp;
    u32               dstCnt  = 0;
    u32               dstSize = 0;

    if ( (*srcp & COMPRESSION_TYPE_MASK) != COMPRESSION_LRC )
    {
        return CX_ERR_UNSUPPORTED;
    }
    if ( srcSize <= 4 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }

    RCInitInfo_( &infoVal, LENGTH_BITS, work );
    RCInitInfo_( &infoOfs, OFFSET_BITS, (u8*)work + (1 << LENGTH_BITS) * sizeof(u32) * 2 );
    RCInitState_( &rcState );

    // load the header
    dstSize = internal::Read32Le(pSrc) >> 8;
    pSrc += 4;
    if ( dstSize == 0 )
    {
        dstSize = internal::Read32Le(pSrc);
        pSrc += 4;
        if ( srcSize < 8 )
        {
            return CX_ERR_SRC_SHORTAGE;
        }
    }

    // load the initial code
    if ( srcSize - ((u32)pSrc - (u32)srcp) < 4 )
    {
        return CX_ERR_SRC_SHORTAGE;
    }
    rcState.code = (u32)( (*pSrc       << 24) |
                          (*(pSrc + 1) << 16) |
                          (*(pSrc + 2) <<  8) |
                          (*(pSrc + 3)      ) );
    pSrc += 4;

    // continue to get values from the range coder and perform LZ decompression
    while ( dstCnt < dstSize )
    {
        u32 cnt;
        u16 val = (u16)( RCGetData_( pSrc, &infoVal, &rcState, &cnt ) );
        pSrc += cnt;

        if ( val < 0x100 )
        // uncompressed data
        {
            dstp[ dstCnt++ ] = (u8)val;
        }
        else
        // compressed data
        {
            u16 length = (u16)( (val & 0xFF) + 3 );
            val = (u16)( RCGetData_( pSrc, &infoOfs, &rcState, &cnt ) + 1 );
            pSrc += cnt;

            // check for a buffer overrun
            if ( dstCnt + length > dstSize )
            {
                return CX_ERR_DEST_OVERRUN;
            }
            if ( dstCnt < val )
            {
                return CX_ERR_DEST_OVERRUN;
            }
            if ( ((u32)pSrc - (u32)srcp) > srcSize )
            {
                return CX_ERR_SRC_SHORTAGE;
            }

            while ( length-- > 0 )
            {
                dstp[ dstCnt ] = dstp[ dstCnt - val ];
                ++dstCnt;
            }
        }
    }
    return CX_ERR_SUCCESS;
#undef LENGTH_BITS
#undef OFFSET_BITS
}

/*
    
    
    
    
    
 */
s32 SecureUncompressBLZ(void* pData, size_t dataSize, size_t bufferSize)
{
    NN_NULL_TASSERT_(pData);
    NN_MIN_TASSERT_(dataSize, 8);  // TORIAEZU: Is 8 really OK??

    u8* pBottom = reinterpret_cast<u8*>(pData) + dataSize;

    // Checks whether the compressed data is BLZ (if the footer seems correct, it is determined to be BLZ)
    // Check bufferTop
    u32 offsetInTop = (pBottom[-6] << 16) | (pBottom[-7] << 8) | pBottom[-8];
    NN_TASSERT_(offsetInTop <= dataSize);
    if (offsetInTop > dataSize)
    {
        return CX_ERR_UNSUPPORTED;
    }
    // Check compressBottom
    u32 offsetInBtm = pBottom[-5];
    NN_TASSERT_(offsetInBtm >= 0x08 || offsetInBtm <= 0x0B);
    if (offsetInBtm < 0x08 && offsetInBtm > 0x0B)
    {
        return CX_ERR_UNSUPPORTED;
    }
    // Size check
    u32 offsetOut = (pBottom[-1] << 24) | (pBottom[-2] << 16) |
                    (pBottom[-3] <<  8) | (pBottom[-4] <<  0);
    NN_TASSERT_((offsetOut + dataSize <= bufferSize));
    if (offsetOut + dataSize > bufferSize)
    {
        return CX_ERR_DEST_OVERRUN;
    }

    u8* pOut   = pBottom + offsetOut;
    u8* pInBtm = pBottom - offsetInBtm;
    u8* pInTop = pBottom - offsetInTop;

    while (pInTop < pInBtm)
    {
        u8 flag = *--pInBtm;

        for (int i = 0; i < 8; ++i)
        {
            if (pInBtm < pInTop)
            {
                return CX_ERR_SRC_SHORTAGE;
            }
            if (pOut < pInTop)
            {
                return CX_ERR_DEST_OVERRUN;
            }
            if (!(flag & 0x80))
            {
                *--pOut = *--pInBtm;
            }
            else
            {
                if (pInBtm - 2 < pInTop)
                {
                    return CX_ERR_DEST_OVERRUN;
                }

                u32 length = *--pInBtm;
                u32 offset = (((length & 0xf) << 8) | (*--pInBtm)) + 3;
                length = (length >> 4) + 3;

                u8* pTmp = pOut + offset;

                if (pOut - length < pInTop)
                {
                    return CX_ERR_DEST_OVERRUN;
                }

                for (int j = 0; j < length; ++j)
                {
                    *--pOut = *--pTmp;
                }
            }
            if (pInBtm <= pInTop)
            {
                break;
            }
            flag <<= 1;
        }
    }

    return CX_ERR_SUCCESS;
}

}   // namespace cx
}   // namespace nn
