/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_Uncompression.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 47717 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_CX_UNCOMPRESSION_H_
#define NN_CX_UNCOMPRESSION_H_

#include <nn/types.h>
#include <nn/assert.h>

namespace nn {
namespace cx {

/* Please see man pages for details 
    
 */
enum CompressionType
{
    COMPRESSION_LZ           = 0x10,     //
    COMPRESSION_HUFFMAN      = 0x20,     //
    COMPRESSION_RL           = 0x30,     //
    COMPRESSION_LH           = 0x40,     //
    COMPRESSION_LRC          = 0x50,     //
    COMPRESSION_DEFLATE      = 0x60,     //
    COMPRESSION_DIFF         = 0x80,     //

    COMPRESSION_TYPE_MASK    = 0xF0,
    COMPRESSION_TYPE_EX_MASK = 0xFF
};


/* Please see man pages for details 
    
 */
struct CompressionHeader
{
    u8  compType;   //
    u8  compParam;  //
    NN_PADDING2;
    u32 destSize;   //
};


/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
    
 */
CompressionHeader GetCompressionHeader(const void* pData);

/* Please see man pages for details 
    

    
    
    
    

    
    
 */
inline CompressionType GetCompressionType(const void* pData)
{
    const u8* p = static_cast<const u8*>(pData);
    return static_cast<CompressionType>(*p & 0xF0);
}


/* Please see man pages for details 
    

    
    
    
    

    
    

    
    
 */
u32 GetUncompressedSize(const void *pData);

//----------------------------------------------------------------------
/* Please see man pages for details 

    
    

    
 *///-------------------------------------------------------------------
size_t GetGzipUncompressedSize(const void* pSrc, size_t srcSize);

/* Please see man pages for details 
    

                
                

                
                
                

    
    
 */
void UncompressAny( const void* srcp, void* destp );


/* Please see man pages for details 
    

                
                

    
    
 */
void UncompressRL( const void *srcp, void *destp );


/* Please see man pages for details 
    

                

                
                

    
    
 */
void UncompressLZ( const void *srcp, void *destp );


/* Please see man pages for details 
    
    
    
    
 */
void UncompressBLZ(void* pData, size_t dataSize, size_t bufferSize);


/* Please see man pages for details 
    

                
                
                
                

    
    
 */
void UncompressHuffman( const void *srcp, void *destp );


/* Please see man pages for details 
    
 */
const int       UNCOMPRESS_LH_WORK_SIZE     = (1 << 11) + (1 << 7);

/* Please see man pages for details 
    
    
    
    
 */
void UncompressLH( const u8* srcp, u8* destp, void* work );

/* Please see man pages for details 
    
 */
const int       UNCOMPRESS_LRC_WORK_SIZE    = ((1 << 12) + (1 << 9)) * 8;

/* Please see man pages for details 
    
    
    
    
 */
void UncompressLRC( const u8* srcp, u8* destp, void* work );



//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
const int       UNCOMPRESS_DEFLATE_WORK_SIZE    = 7116;

//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
const int       UNCOMPRESS_GZIP_WORK_SIZE       = UNCOMPRESS_DEFLATE_WORK_SIZE;

//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
const int       UNCOMPRESS_ZLIB_WORK_SIZE       = UNCOMPRESS_DEFLATE_WORK_SIZE;


//----------------------------------------------------------------------
/* Please see man pages for details 

    

    
    
    
    
    
                            

    
                
 *///-------------------------------------------------------------------
s32 UncompressDeflate(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize, void* pWork );

//----------------------------------------------------------------------
/* Please see man pages for details 

    

    
    
    
    
    
                            

    
                
 *///-------------------------------------------------------------------
s32 UncompressGzip   (void* pDst, size_t dstSize, const void* pSrc, size_t srcSize, void* pWork );

//----------------------------------------------------------------------
/* Please see man pages for details 

    

    
    
    
    
    
                            

    
                
 *///-------------------------------------------------------------------
s32 UncompressZlib   (void* pDst, size_t dstSize, const void* pSrc, size_t srcSize, void* pWork );

/* Please see man pages for details 
    

    
    
 */
void UnfilterDiff( const void *srcp, void *destp );

/*  

*/

}   // namespace cx
}   // namespace nn

/* NN_CX_UNCOMPRESSION_H_ */
#endif
