/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_Compression.h

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

#ifndef NN_CX_COMPRESSION_H_
#define NN_CX_COMPRESSION_H_

#include <nn/types.h>

namespace nn {
namespace cx {

/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
 */
const int   LZ_COMPRESS_WORK_SIZE   = (4096 + 256 + 256) * sizeof(s16);

u32 CompressLZImpl(const u8 *srcp, u32 size, u8 *dstp, void *work, bool exFormat);

/* Please see man pages for details 
    
    
    
    
    
    
                
 */
inline u32 CompressLZ(const u8 *srcp, u32 size, u8 *dstp, void *work)
{
    return CompressLZImpl( srcp, size, dstp, work, false );
}

/* Please see man pages for details 
    
    
    
    
    
    
                
 */
inline u32 CompressLZEx(const u8 *srcp, u32 size, u8 *dstp, void* work)
{
    return CompressLZImpl( srcp, size, dstp, work, true );
}

/* Please see man pages for details 
    
    
    
    
    
                
 */
u32 CompressRL( const u8 *srcp, u32 size, u8 *dstp );

/* Please see man pages for details 
    
 */
const int   HUFFMAN_COMPRESS_WORK_SIZE  = 12288 + 512 + 1536;

/* Please see man pages for details 
    
    
    
    
    
    
    
                
 */
u32 CompressHuffman( const u8 *srcp, u32 size, u8 *dstp, u8 huffBitSize, void *work );



//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
const int   DEFLATE_COMPRESS_WORK_SIZE  = 267972;

//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
const int   GZIP_COMPRESS_WORK_SIZE     = DEFLATE_COMPRESS_WORK_SIZE;

//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
const int   ZLIB_COMPRESS_WORK_SIZE     = DEFLATE_COMPRESS_WORK_SIZE;


//----------------------------------------------------------------------
/* Please see man pages for details 

    
    

    

    
    
    
    
    
                            

    
                
 *///-------------------------------------------------------------------
s32 CompressDeflate( void* pDst, size_t dstSize, const void* pSrc, size_t srcSize, void* pWork );

//----------------------------------------------------------------------
/* Please see man pages for details 

    
    

    

    
    
    
    
    
                            

    
                
 *///-------------------------------------------------------------------
s32 CompressGzip   ( void* pDst, size_t dstSize, const void* pSrc, size_t srcSize, void* pWork );

//----------------------------------------------------------------------
/* Please see man pages for details 

    
    

    

    
    
    
    
    
                            

    
                
 *///-------------------------------------------------------------------
s32 CompressZlib   ( void* pDst, size_t dstSize, const void* pSrc, size_t srcSize, void* pWork );

}   // namespace cx
}   // namespace nn

/*  

*/

/* NN_CX_COMPRESSION_H_ */
#endif
