/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
    
 
*/

#ifndef NN_OS_OS_RESULT_H_
#define NN_OS_OS_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn { namespace os {

    /* Please see man pages for details 
        
        
    
*/
    enum Description
    {
        DESCRIPTION_FAILED_TO_ALLOCATE_MEMORY           = 1,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_SHARED_MEMORY    = 2,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_THREAD           = 3,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_MUTEX            = 4,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_SEMAPHORE        = 5,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_EVENT            = 6,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_TIMER            = 7,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_PORT             = 8,        //
        DESCRIPTION_FAILED_TO_ALLOCATE_SESSION          = 9,        //
        DESCRIPTION_EXCEED_MEMORY_LIMIT                 = 10,       //
        DESCRIPTION_EXCEED_SHARED_MEMORY_LIMIT          = 11,       //
        DESCRIPTION_EXCEED_THREAD_LIMIT                 = 12,       //
        DESCRIPTION_EXCEED_MUTEX_LIMIT                  = 13,       //
        DESCRIPTION_EXCEED_SEMAPHORE_LIMIT              = 14,       //
        DESCRIPTION_EXCEED_EVENT_LIMIT                  = 15,       //
        DESCRIPTION_EXCEED_TIMER_LIMIT                  = 16,       //
        DESCRIPTION_EXCEED_PORT_LIMIT                   = 17,       //
        DESCRIPTION_EXCEED_SESSION_LIMIT                = 18,       //
        DESCRIPTION_MAX_HANDLE                          = 19,       //
        DESCRIPTION_INACCESSIBLE_PAGE                   = 20,       //
        DESCRIPTION_ABANDONED                           = 21,       //
        // 22 Eliminated
        // 23 Eliminated
        DESCRIPTION_INVALID_PROCESS_ID                  = 24,       //
        DESCRIPTION_INVALID_THREAD_ID                   = 25,       //
        DESCRIPTION_SESSION_CLOSED                      = 26,       //
        DESCRIPTION_INVALID_MESSAGE                     = 28,       //
        DESCRIPTION_MANUAL_RESET_EVENT_REQUIRED         = 29,       //
        DESCRIPTION_TOO_LONG_NAME                       = 30,       //
        DESCRIPTION_NOT_OWNED                           = 31,       //
        DESCRIPTION_PROCESS_TERMINATED                  = 32,       //
        DESCRIPTION_INVALID_TLS_INDEX                   = 33,       //
        DESCRIPTION_NO_RUNNABLE_PROCESSOR               = 34,       //
        DESCRIPTION_NO_SESSION                          = 35,       //
        DESCRIPTION_USING_REGION                        = 36,       //
        DESCRIPTION_ALREADY_RECEIVED                    = 37,       //
        DESCRIPTION_CANCEL_REQUESTD                     = 38,       //
        DESCRIPTION_NOT_RECEIVED                        = 39,       //
        // 40 Eliminated
        DESCRIPTION_DELIVER_ARG_NOT_READY               = 41,       //
        DESCRIPTION_DELIVER_ARG_OVER_SIZE               = 42,       //
        DESCRIPTION_INVALID_DELIVER_ARG                 = 43,       //
        DESCRIPTION_I_AM_OWNER                          = 44,       //
        DESCRIPTION_EXCEEDS_SHARED_LIMIT                = 45,
        DESCRIPTION_UNEXPECTED_PERMISSION               = 46,
        DESCRIPTION_INVALID_TAG                         = 47,
        DESCRIPTION_INVALID_FORMAT                      = 48,
        DESCRIPTION_OTHER_HANDLE                        = 49,
        DESCRIPTION_FAILED_TO_ALLOCATE_ADDRESS_ARBITER  = 50,
        DESCRIPTION_EXCEED_ADDRESS_ARBITER_LIMIT        = 51,
        DESCRIPTION_OVER_PORT_CAPACITY                  = 52,
        DESCRIPTION_NOT_MAPPED                          = 53,
        DESCRIPTION_BUFFER_TOO_FLAGMENTED               = 54,
        DESCRIPTION_NO_ADDRESS_SPACE                    = 55,
        DESCRIPTION_EXCEED_TLS_LIMIT                    = 56,
        DESCRIPTION_CANT_START                          = 57,
        DESCRIPTION_LOCKED                              = 58,

        DESCRIPTION_OBSOLETE_RESULT                     = 1023      //
    };
    
    NN_DEFINE_RESULT_FUNC_LM(
        MakePermanentResult,
        Result::LEVEL_PERMANENT, Result::MODULE_NN_FND
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultNoRunnableProcessor,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_NO_RUNNABLE_PROCESSOR
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultNoSession,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WOULD_BLOCK, Result::MODULE_NN_OS, DESCRIPTION_NO_SESSION
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_INFO, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_ALREADY_INITIALIZED
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_NOT_INITIALIZED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidTLSIndex,
        MakePermanentResult, Result::SUMMARY_INVALID_ARGUMENT, DESCRIPTION_INVALID_TLS_INDEX
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        ResultOutOfMemory,
        MakePermanentResult, Result::SUMMARY_OUT_OF_RESOURCE, nn::Result::DESCRIPTION_OUT_OF_MEMORY
    );
    
    NN_DEFINE_RESULT_FUNC_LSM(
        MakeResultInvalidArgument,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS
    );
    
    NN_DEFINE_RESULT_FUNC_LSM(
        MakeResultWrongArgument,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS
    );

    NN_DEFINE_RESULT_CONST(
        ResultNotImplemented,
        Result::LEVEL_USAGE, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_NOT_IMPLEMENTED
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultResourceLimitAlreadyAttached,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, nn::Result::DESCRIPTION_ALREADY_INITIALIZED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        ResultMaxHandle,
        MakePermanentResult, Result::SUMMARY_OUT_OF_RESOURCE, DESCRIPTION_MAX_HANDLE
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        ResultResourceLimitNotAttached,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, nn::Result::DESCRIPTION_NOT_INITIALIZED
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultMisalignedAddress,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_MISALIGNED_ADDRESS
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultMisalignedSize,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_MISALIGNED_SIZE
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultInvalidAddress,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_INVALID_ADDRESS
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultInvalidCombination,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_INVALID_COMBINATION
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultBusy,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_BUSY
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultTooLongName,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_TOO_LONG_NAME
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultInaccessiblePage,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_INACCESSIBLE_PAGE
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultNotFound,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_NOT_FOUND
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultInvalidHandle,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_INVALID_HANDLE
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultInvalidThreadId,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_INVALID_THREAD_ID
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultNoData,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_NO_DATA
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_OUT_OF_RANGE
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultInvalidProcessId,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_INVALID_PROCESS_ID
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyExists,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_ALREADY_EXISTS
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultSessionClosed,
        Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_OS, DESCRIPTION_SESSION_CLOSED
    );
    
    NN_DEFINE_RESULT_CONST(
        ResultNotAuthorized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_NOT_AUTHORIZED
    );

    NN_DEFINE_RESULT_CONST(
        ResultDeliverArgNotReady,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, DESCRIPTION_DELIVER_ARG_NOT_READY
    );

    NN_DEFINE_RESULT_CONST(
        ResultDeliverArgOverSize,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, DESCRIPTION_DELIVER_ARG_OVER_SIZE
    );

    NN_DEFINE_RESULT_CONST(
        ResultInvalidDeliverArg,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, DESCRIPTION_INVALID_DELIVER_ARG
    );

    NN_DEFINE_RESULT_CONST(
        ResultIAmOwner,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_I_AM_OWNER
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedsSharedLimit,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_EXCEEDS_SHARED_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultUnexpectedPermission,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_UNEXPECTED_PERMISSION
    );

    NN_DEFINE_RESULT_CONST(
        ResultInvalidTag,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_INVALID_TAG
    );

    NN_DEFINE_RESULT_CONST(
        ResultInvalidFormat,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_INVALID_FORMAT
    );

    NN_DEFINE_RESULT_CONST(
        ResultOtherHandle,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_OS, DESCRIPTION_OTHER_HANDLE
    );

    
    
    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateMemory,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_MEMORY
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateSharedMemory,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_SHARED_MEMORY
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateThread,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_THREAD
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateMutex,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_MUTEX
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateSemaphore,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_SEMAPHORE
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateEvent,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_EVENT
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateTimer,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_TIMER
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocatePort,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_PORT
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateSession,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_SESSION
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedMemoryLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_MEMORY_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedSharedMemoryLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_SHARED_MEMORY_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedThreadLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_THREAD_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedMutexLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_MUTEX_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedSemaphoreLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_SEMAPHORE_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedEventLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_EVENT_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedTimerLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_TIMER_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedPortLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_PORT_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedSessionLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_SESSION_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultFailedToAllocateAddressArbiter,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_FAILED_TO_ALLOCATE_ADDRESS_ARBITER
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedAddressArbiterLimit,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_ADDRESS_ARBITER_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultExceedTlsLimit,
        Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_EXCEED_TLS_LIMIT
    );

    NN_DEFINE_RESULT_CONST(
        ResultOverPortCapacity,
        Result::LEVEL_TEMPORARY, Result::SUMMARY_WOULD_BLOCK, Result::MODULE_NN_OS, DESCRIPTION_OVER_PORT_CAPACITY
    );

    NN_DEFINE_RESULT_CONST(
        ResultInvalidAddressState,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, nn::Result::DESCRIPTION_INVALID_ADDRESS
    );

    NN_DEFINE_RESULT_CONST(
        ResultNotMapped,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, DESCRIPTION_NOT_MAPPED
    );

    NN_DEFINE_RESULT_CONST(
        ResultBufferTooFragmented,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, DESCRIPTION_BUFFER_TOO_FLAGMENTED
    );

    NN_DEFINE_RESULT_CONST(
        ResultNoAddressSpace,
        Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_OS, DESCRIPTION_NO_ADDRESS_SPACE
    );


    NN_DEFINE_RESULT_CONST(
        ResultNotSupported,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_OS, Result::DESCRIPTION_NOT_IMPLEMENTED
    );

    NN_DEFINE_RESULT_CONST(
        ResultCantStart,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_OS, DESCRIPTION_CANT_START
    );

    NN_DEFINE_RESULT_CONST(
        ResultLocked,
        Result::LEVEL_TEMPORARY, Result::SUMMARY_WOULD_BLOCK, Result::MODULE_NN_OS, DESCRIPTION_LOCKED
    );
}}

#endif // __cplusplus

#endif /* NN_OS_OS_RESULT_H_ */
