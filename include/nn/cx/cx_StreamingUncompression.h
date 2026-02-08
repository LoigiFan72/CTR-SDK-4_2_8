/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_StreamingUncompression.h

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

#ifndef NN_CX_STREAMING_UNCOMPRESSION_H_
#define NN_CX_STREAMING_UNCOMPRESSION_H_

#include <nn/types.h>
#include <nn/assert.h>

namespace nn {
namespace cx {

/* Please see man pages for details 
    
 */
struct UncompContextRL
{
    u8 *destp;                         //
    s32 destCount;                     //
    s32 forceDestCount;                //
    u16 length;                        //
    u8  flags;                         //
    u8  headerSize;                    //
};


/* Please see man pages for details 
    
 */
struct UncompContextLZ
{
    u8 *destp;                         //
    s32 destCount;                     //
    s32 forceDestCount;                //
    s32 length;                        //
    u8  lengthFlg;                     //
    u8  flags;                         //
    u8  flagIndex;                     //
    u8  headerSize;                    //
    u8  exFormat;                      //
    NN_PADDING3;
};


/* Please see man pages for details 
    
 */
struct UncompContextHuffman
{
    u8 *destp;                         //
    s32 destCount;                     //
    s32 forceDestCount;                //
    u8 *treep;                         //
    u32 srcTmp;                        //
    u32 destTmp;                       //
    s16 treeSize;                      //
    u8  srcTmpCnt;                     //
    u8  destTmpCnt;                    //
    u8  bitSize;                       //
    u8  headerSize;                    //
    NN_PADDING2;
    u8  tree[0x200];                   //
};


/* Please see man pages for details 
    
 */
struct UncompContextLH
{
    u8   *destp;                         //
    s32  destCount;                      //
    s32  forceDestCount;                 //
    u16  huffTable9 [ 1 << (9 + 1) ];    //
    u16  huffTable12[ 1 << (5 + 1) ];    //
    u16  *nodep;                         //
    s32  tableSize9;                     //
    s32  tableSize12;                    //
    u32  tableIdx;                       //
    u32  stream;                         //
    u32  stream_len;                     //
    u16  length;                         //
    s8   offset_bits;                    //
    u8   headerSize;                     //
};


/* Please see man pages for details 
    
 */
struct UncompContextLRC
{
    u8   *destp;                         //
    s32  destCount;                      //
    s32  forceDestCount;                 //
    u32  freq9    [ 1 << 9  ];           //
    u32  low_cnt9 [ 1 << 9  ];           //
    u32  freq12   [ 1 << 12 ];           //
    u32  low_cnt12[ 1 << 12 ];           //
    u32  total9;                         //
    u32  total12;                        //
    u32  range;                          //
    u32  code;                           //
    u32  low;                            //
    u32  carry_cnt;                      //
    u8   carry;                          //
    u8   codeLen;                        //
    u16  length;                         //
    u8   headerSize;                     //
    NN_PADDING3;
};

//----------------------------------------------------------------------
/* Please see man pages for details 
            
 *///-------------------------------------------------------------------
struct UncompContextDeflate
{
    bit8 dummy[39956] NN_ATTRIBUTE_ALIGN(4);
};

//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
typedef UncompContextDeflate UncompContextGzip;

//----------------------------------------------------------------------
/* Please see man pages for details 
 *///-------------------------------------------------------------------
typedef UncompContextDeflate UncompContextZlib;


/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
    
    
 */
void InitUncompContextRL( UncompContextRL *context, void *dest );


/* Please see man pages for details 
    

                

    
    
 */
void InitUncompContextLZ( UncompContextLZ *context, void *dest );


/* Please see man pages for details 
    
    
    
 */
void InitUncompContextHuffman( UncompContextHuffman    *context,
                                 void                      *dest );

/* Please see man pages for details 
    
    
    
 */
void InitUncompContextLH( UncompContextLH * context, void* dest );


/* Please see man pages for details 
    
    
    
 */
void InitUncompContextLRC( UncompContextLRC * context, void* dest );


//----------------------------------------------------------------------
/* Please see man pages for details 
            

    
    
    
 *///-------------------------------------------------------------------
void InitUncompContextDeflate( UncompContextDeflate* pContext, void* pDst, size_t dstSize );

//----------------------------------------------------------------------
/* Please see man pages for details 
            

    
    
    
 *///-------------------------------------------------------------------
void InitUncompContextGzip   ( UncompContextGzip* pContext, void* pDst, size_t dstSize );

//----------------------------------------------------------------------
/* Please see man pages for details 
            

    
    
    
 *///-------------------------------------------------------------------
void InitUncompContextZlib   ( UncompContextZlib* pContext, void* pDst, size_t dstSize );



/* Please see man pages for details 
    
    
    
    
    
 */
s32 ReadUncompRL( UncompContextRL *context, const void *data, u32 len );


/* Please see man pages for details 
    

                

    
    
    
    
 */
s32 ReadUncompLZ( UncompContextLZ *context, const void *data, u32 len );


/* Please see man pages for details 
    
    
    
    
    
 */
s32 ReadUncompHuffman( UncompContextHuffman *context, const void *data, u32 len );


/* Please see man pages for details 
    
    
    
    
    
 */
s32 ReadUncompLH( UncompContextLH *context, const void* data, u32 len );


/* Please see man pages for details 
    
    
    
    
    
 */
s32 ReadUncompLRC( UncompContextLRC *context, const void* data, u32 len );

//----------------------------------------------------------------------
/* Please see man pages for details 

    
    
    

    
                
 *///-------------------------------------------------------------------
s32 ReadUncompDeflate( UncompContextDeflate* pContext, const void* pData, size_t dataSize );

//----------------------------------------------------------------------
/* Please see man pages for details 

    

    
    
    

    
                
 *///-------------------------------------------------------------------
s32 ReadUncompGzip   ( UncompContextGzip*    pContext, const void* pData, size_t dataSize );

//----------------------------------------------------------------------
/* Please see man pages for details 

    

    
    
    

    
                
 *///-------------------------------------------------------------------
s32 ReadUncompZlib   ( UncompContextZlib*    pContext, const void* pData, size_t dataSize );



/* Please see man pages for details 
    
    
    
                
 */
template <typename UncompContext>
inline bool IsFinishedUncomp( const UncompContext *context )
{
    NN_NULL_TASSERT_(context);
    return (context->destCount > 0 || context->headerSize > 0)? false : true;
}

/* Please see man pages for details 
    
                
*/
template <typename UncompContext>
inline bool IsFinishedUncompRL( const UncompContext *context ) NN_ATTRIBUTE_DEPRECATED
{
    NN_NULL_TASSERT_(context);
    return (context->destCount > 0 || context->headerSize > 0)? false : true;
}


/* Please see man pages for details 
    
                
    
    
    
 */
inline void InitUncompContextRLFront( UncompContextRL *context, void *dest, s32 destSize )
{
    NN_ASSERT( destSize > 0 );
    InitUncompContextRL( context, dest );
    context->forceDestCount = destSize;
}


/* Please see man pages for details 
    
                

                

    
    
    
 */
inline void InitUncompContextLZFront( UncompContextLZ *context, void *dest, s32 destSize )
{
    NN_ASSERT( destSize > 0 );
    InitUncompContextLZ( context, dest );
    context->forceDestCount = destSize;
}


/* Please see man pages for details 
    
                
    
    
    
 */
inline void InitUncompContextHuffmanFront( UncompContextHuffman *context, void *dest, s32 destSize )
{
    NN_ASSERT( destSize > 0 );
    InitUncompContextHuffman( context, dest );
    context->forceDestCount = destSize;
}


/* Please see man pages for details 
    
                
    
    
    
 */
inline void InitUncompContextLHFront( UncompContextLH *context, void *dest, s32 destSize )
{
    NN_ASSERT( destSize > 0 );
    InitUncompContextLH( context, dest );
    context->forceDestCount = destSize;
}


/* Please see man pages for details 
    
                
    
    
    
 */
inline void InitUncompContextLRCFront( UncompContextLRC *context, void *dest, s32 destSize )
{
    NN_ASSERT( destSize > 0 );
    InitUncompContextLRC( context, dest );
    context->forceDestCount = destSize;
}

/*  

*/

}   // namespace cx
}   // namespace nn

/* NN_CX_STREAMING_UNCOMPRESSION_H_ */
#endif
