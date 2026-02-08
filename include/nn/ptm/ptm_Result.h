/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ptm_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47251 $
 *---------------------------------------------------------------------------*/

#ifndef NN_PTM_CTR_PTM_RESULT_H_
#define NN_PTM_CTR_PTM_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn {
namespace ptm {

/*
    
*/
enum Description
{
    DESCRIPTION_INVALID_SYSTEMTIME = 1,
    DESCRIPTION_NOALARM,
    DESCRIPTION_OVERWRITEALARM,
    DESCRIPTION_FILEERROR,
    DESCRIPTION_NOT_SLEEPING,
    DESCRIPTION_INVALID_TRIGGER,
    DESCRIPTION_MCU_FATAL_ERROR
};

/* Please see man pages for details 
  
  
*/

NN_DEFINE_RESULT_CONST(
    ResultNotImplemented,
    Result::LEVEL_FATAL, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_PTM, nn::Result::DESCRIPTION_NOT_IMPLEMENTED
);

NN_DEFINE_RESULT_CONST(
    ResultInvalidSystemTime,
    Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_PTM, DESCRIPTION_INVALID_SYSTEMTIME
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultOverWriteAlarm,
    Result::LEVEL_SUCCESS, Result::SUMMARY_SUCCESS, Result::MODULE_NN_PTM, DESCRIPTION_OVERWRITEALARM
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultNoAlarm,
    Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_PTM, DESCRIPTION_NOALARM
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultNotRegistered,
    Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_PTM, Result::DESCRIPTION_NOT_INITIALIZED
);

NN_DEFINE_RESULT_CONST(
    ResultFileError,
    Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_PTM, DESCRIPTION_FILEERROR
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultWrongArgument,
    Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_PTM, Result::DESCRIPTION_NO_DATA
);

NN_DEFINE_RESULT_CONST(
    ResultNotSleeping,
    Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_PTM, DESCRIPTION_NOT_SLEEPING
);

NN_DEFINE_RESULT_CONST(
    ResultInvalidTrigger,
    Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_PTM, DESCRIPTION_INVALID_TRIGGER
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultInvalidAlarm,
    Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_PTM, Result::DESCRIPTION_OUT_OF_RANGE
);

NN_DEFINE_RESULT_CONST(
    ResultOutOfRange,
    Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_PTM, Result::DESCRIPTION_OUT_OF_RANGE
);

NN_DEFINE_RESULT_CONST(
    ResultInvalidSize,
    Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_PTM, Result::DESCRIPTION_INVALID_SIZE
);

// For internal use
NN_DEFINE_RESULT_CONST(
    ResultMcuFatalError,
    Result::LEVEL_FATAL, Result::SUMMARY_INTERNAL, Result::MODULE_NN_PTM, DESCRIPTION_MCU_FATAL_ERROR
);

// For internal use
NN_DEFINE_RESULT_CONST(
    ResultNotWrite,
    Result::LEVEL_SUCCESS, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_PTM, Result::DESCRIPTION_SUCCESS
);

// For internal use
NN_DEFINE_RESULT_CONST(
    ResultNotFound,
    Result::LEVEL_PERMANENT, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_PTM, Result::DESCRIPTION_NOT_FOUND
);

} // end of namespace ptm
} // end of namespace nn

#endif // #ifdef __cplusplus
#endif // #ifndef NN_PTM_CTR_PTM_RESULT_H_
