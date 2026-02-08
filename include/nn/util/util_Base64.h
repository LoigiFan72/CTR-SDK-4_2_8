/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Base64.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_BASE64_H_
#define NN_UTIL_UTIL_BASE64_H_

#include <nn/types.h>
#include <nn/util/util_Result.h>

#ifdef __cplusplus

namespace nn { namespace util {

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultBufferFull,
        Result::LEVEL_PERMANENT,
        Result::SUMMARY_OUT_OF_RESOURCE,
        Result::MODULE_NN_UTIL,
        DESCRIPTION_BUFFER_FULL
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultBadData,
        Result::LEVEL_PERMANENT,
        Result::SUMMARY_WRONG_ARGUMENT,
        Result::MODULE_NN_UTIL,
        DESCRIPTION_BAD_DATA
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidPtr,
        Result::LEVEL_USAGE,
        Result::SUMMARY_INVALID_ARGUMENT,
        Result::MODULE_NN_UTIL,
        Result::DESCRIPTION_INVALID_POINTER
    );

/* Please see man pages for details 
    
 */
class Base64
{
public:

    /* Please see man pages for details 
      
      
      
      
      
      
      
      
     */
    static nn::Result ToBase64String(const void* pSrc, size_t sizeSrc, char* pDst, size_t sizeDst);

    /* Please see man pages for details 
      
      
      
      
      
      
      
      
     */
    static nn::Result FromBase64String(const char* pSrc, void* pDst, size_t sizeDst, size_t* pNum);
};

}}

#endif // __cplusplus

#endif // ifndef NN_UTIL_UTIL_BASE64_H_
