/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/*!
    @file

    :include nn/socket.h
 */

#ifndef NN_SOCKET_SOCKET_RESULT_H_
#define NN_SOCKET_SOCKET_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn {
namespace socket {

    enum Description
    {
        DESCRIPTION_FAILED_TO_INITIALIZE_INTERFACE = 1,
        DESCRIPTION_FAILED_TO_INITIALIZE_SOCKET_CORE,
        DESCRIPTION_TOO_MANY_REQUESTS,
        DESCRIPTION_PERMISSION_DENIED,
        DESCRIPTION_UNKOWN_CONFIGURATION,
        DESCRIPTION_UNKOWN_CLIENT,
        DESCRIPTION_BAD_DESCRIPTOR,
        DESCRIPTION_REQUEST_SESSION_FULL,
        DESCRIPTION_NETWORK_RESETTED,
        DESCRIPTION_TOO_MANY_PROCESSES,
        DESCRIPTION_ALREADY_REGISTERED,
        DESCRIPTION_TOO_MANY_SOCKETS,
        DESCRIPTION_MISMATCH_VERSION,
        DESCRIPTION_ADDRESS_COLLISION,
        DESCRIPTION_TIMEOUT,
        DESCRIPTION_OUT_OF_SYSTEM_RESOURCE,
        DESCRIPTION_INVLID_CORE_STATE,
        DESCRIPTION_ABORTED
    };

    namespace detail {
        s32 ConvertErrorResult(Result result);
    }

    NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_SOCKET);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInternalResult, Result::LEVEL_STATUS, Result::SUMMARY_INTERNAL, Result::MODULE_NN_SOCKET);    
    NN_DEFINE_RESULT_FUNC_LSM(MakeOutOfResourceResult, Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_SOCKET);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInvalidStateResult, Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_SOCKET);
    NN_DEFINE_RESULT_FUNC_LSM(MakeStatusChangedResult, Result::LEVEL_STATUS, Result::SUMMARY_STATUS_CHANGED, Result::MODULE_NN_SOCKET);
    NN_DEFINE_RESULT_FUNC_LSM(MakeCancelledResult, Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_SOCKET);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInvalidArgumentResult, Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_SOCKET);

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultFailedToInitializeInterface,
        MakeInvalidArgumentResult, DESCRIPTION_FAILED_TO_INITIALIZE_INTERFACE
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultFailedToInitializeSocketCore,
        MakeInvalidArgumentResult, DESCRIPTION_FAILED_TO_INITIALIZE_SOCKET_CORE
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTooManyRequests,
        MakeOutOfResourceResult, DESCRIPTION_TOO_MANY_REQUESTS
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAlreadyInitialized,
        MakeInvalidStateResult, Result::DESCRIPTION_ALREADY_INITIALIZED
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotInitialized,
        MakeInvalidStateResult, Result::DESCRIPTION_NOT_INITIALIZED
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultOutOfMemory,
        MakeOutOfResourceResult, Result::DESCRIPTION_OUT_OF_MEMORY
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultPermissionDenied,
        MakeInvalidStateResult, DESCRIPTION_PERMISSION_DENIED
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultUnkownConfiguration,
        MakeInvalidArgumentResult, DESCRIPTION_UNKOWN_CONFIGURATION
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidSize,
        MakeInvalidArgumentResult, Result::DESCRIPTION_INVALID_SIZE
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultUnkownClient,
        MakeInvalidArgumentResult, DESCRIPTION_UNKOWN_CLIENT
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultBadDescriptor,
        MakeInvalidArgumentResult, DESCRIPTION_BAD_DESCRIPTOR
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNetworkResetted,
        MakeInvalidStateResult, DESCRIPTION_NETWORK_RESETTED
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultRequestSessionFull,
        MakeOutOfResourceResult, DESCRIPTION_REQUEST_SESSION_FULL
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultToBeDefined,
        MakeInternalResult, Result::DESCRIPTION_INVALID_RESULT_VALUE
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTooManyProcesses,
        MakeOutOfResourceResult, DESCRIPTION_TOO_MANY_PROCESSES
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAlreadyRegistered,
        MakeInvalidStateResult, DESCRIPTION_ALREADY_REGISTERED
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTooManySockets,
        MakeOutOfResourceResult, DESCRIPTION_TOO_MANY_SOCKETS
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultMismatchVersion,
        MakeInvalidArgumentResult, DESCRIPTION_MISMATCH_VERSION
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAddressCollision,
        MakeCancelledResult, DESCRIPTION_ADDRESS_COLLISION
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTimeOut,
        MakeCancelledResult, DESCRIPTION_TIMEOUT
    );

    //!< 
    NN_DEFINE_RESULT_CONST_LSM(
        ResultOutOfSystemResource,
        MakeOutOfResourceResult, DESCRIPTION_OUT_OF_SYSTEM_RESOURCE
    );    

    //!<
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidCoreState,
        MakeInvalidStateResult, DESCRIPTION_INVLID_CORE_STATE
    );

    //!<
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAborted,
        MakeCancelledResult, DESCRIPTION_ABORTED
    );    
}
}

#endif // __cplusplus

#endif /* NN_SOCKET_SOCKET_RESULT_H_ */
