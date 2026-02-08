/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47344 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_RESULT_H_
#define NN_UTIL_UTIL_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>
#include <nn/assert.h>
#include <nn/Handle.h>
#include <nn/svc/svc_Stub.h>
#include <nn/config.h>
#include <nn/dbg/dbg_SmallSet.h>

#define NN_UTIL_RETURN_IF_FAILED_BASE(result, s1, s2, s3, s4, s5) \
    do \
    { \
        ::nn::Result nn_util_return_if_failure_result = (result); \
        if (nn_util_return_if_failure_result.IsFailure()) \
        { \
            s1; s2; s3; s4; s5; \
            return nn_util_return_if_failure_result; \
        } \
    } while(0)

#define NN_UTIL_RETURN_IF_FAILED(result) NN_UTIL_RETURN_IF_FAILED_BASE(result,,,,,)

#define NN_UTIL_RETURN_IF_FAILED_0(result) NN_UTIL_RETURN_IF_FAILED_BASE(result,,,,,)
#define NN_UTIL_RETURN_IF_FAILED_1(result, c1) NN_UTIL_RETURN_IF_FAILED_BASE(result,c1,,,,)
#define NN_UTIL_RETURN_IF_FAILED_2(result, c1, c2) NN_UTIL_RETURN_IF_FAILED_BASE(result,c1,c2,,,)
#define NN_UTIL_RETURN_IF_FAILED_3(result, c1, c2, c3) NN_UTIL_RETURN_IF_FAILED_BASE(result,c1,c2,c3,,)
#define NN_UTIL_RETURN_IF_FAILED_4(result, c1, c2, c3, c4) NN_UTIL_RETURN_IF_FAILED_BASE(result,c1,c2,c3,c4,)
#define NN_UTIL_RETURN_IF_FAILED_5(result, c1, c2, c3, c4, c5) NN_UTIL_RETURN_IF_FAILED_BASE(result,c1,c2,c3,c4,c5)

#define NN_UTIL_RETURN_IF_FAILED_EXCEPT(result, exceptResult) \
    do \
    { \
        ::nn::Result nn_util_return_if_failure_result_except = (result); \
        if (!(nn_util_return_if_failure_result_except <= (exceptResult))) \
        { \
            NN_UTIL_RETURN_IF_FAILED(nn_util_return_if_failure_result_except); \
        } \
    } while (0)

#ifdef NN_SWITCH_DISABLE_DEBUG_PRINT
    #define NN_UTIL_THROW_RESULT(result) return (result)
#else
    #define NN_UTIL_THROW_RESULT(result) \
    do \
    { \
        ::nn::Result nn_util_return_throw_result = (result); \
        NN_TASSERT_(nn_util_return_throw_result.IsFailure()); \
        NN_UTIL_RETURN_IF_FAILED_0(nn_util_return_throw_result); \
        return nn_util_return_throw_result; \
    } while(0)
#endif

#define NN_UTIL_PANIC_IF_FAILED(result) NN_PANIC_IF_FAILED(result)


namespace nn { namespace util {

    enum Description
    {
        DESCRIPTION_BUFFER_FULL = 1,
        DESCRIPTION_BAD_DATA    = 2
    };

    inline Result MakePermanentResult(Result::Summary summary, int description)
    {
        return Result(Result::LEVEL_PERMANENT, summary, Result::MODULE_NN_UTIL, description);
    }

    inline Result ResultAlreadyInitialized()
    {
        return Result(Result::LEVEL_INFO, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_UTIL, Result::DESCRIPTION_ALREADY_INITIALIZED);
    }

    inline Result ResultOutOfMemory()
    {
        return Result(Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_UTIL, Result::DESCRIPTION_OUT_OF_MEMORY);
    }
}}

#endif // __cplusplus

#endif
