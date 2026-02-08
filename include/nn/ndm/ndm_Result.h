/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ndm_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47202 $
 *---------------------------------------------------------------------------*/

/*!
    @file

    :include nn/ndm.h
 */

#ifndef NN_NDM_NDM_RESULT_H_
#define NN_NDM_NDM_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>
#include <nn/util/util_Result.h>

namespace nn {
namespace ndm {

    enum Description
    {
        DESCRIPTION_INTERRUPT_BY_REQUEST = 1,
        DESCRIPTION_PROCESSING_PRIORITY_REQUEST,
        DESCRIPTION_IN_ERROR_STATE,
        DESCRIPTION_DISCONNECTED,
        DESCRIPTION_CANCELLED_BY_OTHER_REQUEST,
        DESCRIPTION_CANCELLED_BY_HARDWARE_EVENTS,
        DESCRIPTION_CANCELLED_BY_DISCONNECT,
        DESCRIPTION_CANCELLED_BY_USER_REQUEST,
        DESCRIPTION_OPERATION_DENIED,
        DESCRIPTION_LOCKED_BY_OTHER_PROCESS,
        DESCRIPTION_NOT_LOCKED,
        DESCRIPTION_ALREADY_SUSPENDED,
        DESCRIPTION_NOT_SUSPENDED,
        DESCRIPTION_INVALID_OPERATION,
        DESCRIPTION_NOT_EXCLUSIVE,
        DESCRIPTION_EXCLUSIVE_BY_OTHER_PROCESS,
        DESCRIPTION_EXCLUSIVE_BY_OWN_PROCESS,
        DESCRIPTION_BACKGROUND_DISCONNECTED,
        DESCRIPTION_FOREGROUND_CONNCECTION_EXISTS
    };

    NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_NDM);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInternalResult, Result::LEVEL_STATUS, Result::SUMMARY_INTERNAL, Result::MODULE_NN_NDM);    
    NN_DEFINE_RESULT_FUNC_LSM(MakeOutOfResourceResult, Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_NDM);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInvalidStateResult, Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_NDM);
    NN_DEFINE_RESULT_FUNC_LSM(MakeCancelledResult, Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_NDM);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInvalidArgumentResult, Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_NDM);
    NN_DEFINE_RESULT_FUNC_LSM(MakeNotSupportedResult, Result::LEVEL_USAGE, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_NDM);

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInterruptByRequest,
        MakeInvalidStateResult, DESCRIPTION_INTERRUPT_BY_REQUEST
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultCanceledByOtherRequest,
        MakeInvalidStateResult, DESCRIPTION_CANCELLED_BY_OTHER_REQUEST
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultProcessingPriorityRequest,
        MakeInvalidStateResult, DESCRIPTION_PROCESSING_PRIORITY_REQUEST
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInErrorState,
        MakeInvalidStateResult, DESCRIPTION_IN_ERROR_STATE
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultDisconnected,
        MakeInvalidStateResult, DESCRIPTION_DISCONNECTED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultCancelledByHardwareEvents,
        MakeInvalidStateResult, DESCRIPTION_CANCELLED_BY_HARDWARE_EVENTS
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultCancelledByDisconnect,
        MakeInvalidStateResult, DESCRIPTION_CANCELLED_BY_DISCONNECT
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultCancelledByUserRequest,
        MakeInvalidStateResult, DESCRIPTION_CANCELLED_BY_USER_REQUEST
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidOperation,
        MakeInvalidStateResult, DESCRIPTION_INVALID_OPERATION
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidEnumValue,
        MakeInvalidArgumentResult, Result::DESCRIPTION_INVALID_ENUM_VALUE
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultOperationDenied,
        MakeInvalidStateResult, DESCRIPTION_OPERATION_DENIED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultLockedByOtherProcess,
        MakeInvalidStateResult, DESCRIPTION_LOCKED_BY_OTHER_PROCESS
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotLocked,
        MakeInvalidStateResult, DESCRIPTION_NOT_LOCKED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAlreadyInitialized,
        MakeInvalidStateResult, Result::DESCRIPTION_ALREADY_INITIALIZED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotSuspended,
        MakeInvalidStateResult, DESCRIPTION_NOT_SUSPENDED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAlreadySuspended,
        MakeInvalidStateResult, DESCRIPTION_ALREADY_SUSPENDED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotInitialized,
        MakeInvalidStateResult, Result::DESCRIPTION_NOT_INITIALIZED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotExclusive,
        MakeInvalidStateResult, DESCRIPTION_NOT_EXCLUSIVE
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotImplemented,
        MakeNotSupportedResult, Result::DESCRIPTION_NOT_IMPLEMENTED
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultExclusiveByOtherProcess,
        MakeInvalidStateResult, DESCRIPTION_EXCLUSIVE_BY_OTHER_PROCESS
    );
    
    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultExclusiveByOwnProcess,
        MakeInvalidStateResult, DESCRIPTION_EXCLUSIVE_BY_OWN_PROCESS
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultBackgroundDisconnected,
        MakeInvalidStateResult, DESCRIPTION_BACKGROUND_DISCONNECTED
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultForegroundConnectionExists,
        MakeInvalidStateResult, DESCRIPTION_FOREGROUND_CONNCECTION_EXISTS
    );
    
}
}

#define NN_NDM_WARN(result, ...) \
        NN_LOG_WARN(__VA_ARGS__); \
        NN_DBG_TPRINT_RESULT_(result);

#define NN_NDM_WARN_AND_RETURN_IF_FAILED(result, ...) \
do \
{ \
    ::nn::Result nn_util_return_if_failure_result = (result); \
    if (nn_util_return_if_failure_result.IsFailure()) \
    { \
        NN_NDM_WARN(nn_util_return_if_failure_result, __VA_ARGS__); \
        return nn_util_return_if_failure_result; \
    } \
} while(0)

#define NN_NDM_WARN_IF_FAILED(result, ...) \
do \
{ \
    ::nn::Result nn_util_return_if_failure_result = (result); \
    if (nn_util_return_if_failure_result.IsFailure()) \
    { \
        NN_NDM_WARN(nn_util_return_if_failure_result, __VA_ARGS__); \
    } \
} while(0)

#endif // __cplusplus

#endif /* NN_NDM_NDM_RESULT_H_ */
