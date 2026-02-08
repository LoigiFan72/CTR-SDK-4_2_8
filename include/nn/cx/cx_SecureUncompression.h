/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_SecureUncompression.h

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

#ifndef NN_CX_SECURE_UNCOMPRESSION_H_
#define NN_CX_SECURE_UNCOMPRESSION_H_

#include <nn/types.h>
#include <nn/cx/cx_Uncompression.h>

namespace nn {
namespace cx {

/* Please see man pages for details 
    
 */
enum ErrorCode
{
    ERROR_CODE_SUCCESS            =  0, //
    ERROR_CODE_UNSUPPORTED        = -1, //
    ERROR_CODE_DATA_SHORTAGE      = -2, //
    ERROR_CODE_DATA_REMAINDER     = -3, //
    ERROR_CODE_BUFFER_OVERRUN     = -4, //
    ERROR_CODE_ILLEGAL_TABLE      = -5  //
};

enum
{
    CX_ERR_SUCCESS           = ERROR_CODE_SUCCESS,
    CX_ERR_UNSUPPORTED       = ERROR_CODE_UNSUPPORTED,
    CX_ERR_SRC_SHORTAGE      = ERROR_CODE_DATA_SHORTAGE,
    CX_ERR_SRC_REMAINDER     = ERROR_CODE_DATA_REMAINDER,
    CX_ERR_DEST_OVERRUN      = ERROR_CODE_BUFFER_OVERRUN,
    CX_ERR_ILLEGAL_TABLE     = ERROR_CODE_ILLEGAL_TABLE
};

/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
                

                
                

                
                
                

    
    
    
    
 */
s32 SecureUncompressAny( const void* srcp, u32 srcSize, void* destp );


/* Please see man pages for details 
    

                
                

    
    
    
    
 */
s32 SecureUncompressRL( const void *srcp, u32 srcSize, void *destp );


/* Please see man pages for details 
    

                

                
                

    
    
    
    
 */
s32 SecureUncompressLZ( const void *srcp, u32 srcSize, void *destp );


/* Please see man pages for details 
    

                
                
                
                

    
    
    
    
 */
s32 SecureUncompressHuffman( const void *srcp, u32 srcSize, void *destp );


/* Please see man pages for details 
    
    
    
    
    
    
 */
s32 SecureUncompressLH( const u8* srcp, u32 srcSize, u8* destp, void* work );


/* Please see man pages for details 
    
    
    
    
    
    
 */
s32 SecureUncompressLRC( const u8* srcp, u32 srcSize, u8* destp, void* work );


/* Please see man pages for details 
    

    
    
    
    
 */
s32 SecureUnfilterDiff( register const void *srcp, u32 srcSize, register void *destp );

/* Please see man pages for details 
    
    
    
    
    
 */
s32 SecureUncompressBLZ(void* pData, size_t dataSize, size_t bufferSize);

/*  

*/

namespace internal {

bool VerifyHuffmanTable( const void* pTable, u8 bit );
bool LHVerifyTable( const void* pTable, u8 bit );

}   // namespace internal

}   // namespace cx
}   // namespace nn

/* NN_CX_SECURE_UNCOMPRESSION_H_ */
#endif
