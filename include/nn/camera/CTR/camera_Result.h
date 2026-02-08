/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     camera_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CAMERA_CTR_CAMERA_RESULT_H_
#define NN_CAMERA_CTR_CAMERA_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/


namespace nn {
namespace camera {
namespace CTR {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_CAMERA_IS_SLEEPING = 1,
        DESCRIPTION_CAMERA_FATAL_ERROR
    };

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultIsSleeping,
        Result::LEVEL_STATUS, Result::SUMMARY_STATUS_CHANGED, Result::MODULE_NN_CAMERA, DESCRIPTION_CAMERA_IS_SLEEPING
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultFatalError,
        Result::LEVEL_FATAL, Result::SUMMARY_INTERNAL, Result::MODULE_NN_CAMERA, DESCRIPTION_CAMERA_FATAL_ERROR
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_ALREADY_INITIALIZED
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultUsingOtherProcess,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_ALREADY_INITIALIZED
    );

    // For internal use
    // Indicates that the specified argument was not in the enum value's range.
    NN_DEFINE_RESULT_CONST(
        ResultInvalidEnumValue,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_INVALID_ENUM_VALUE
    );

    // For internal use
    // Indicates that shutter sound failed to play via csnd.
    // The application will not return a fatal error immediately because the sim layer library for receiving will retry once.
    NN_DEFINE_RESULT_CONST(
        ResultBusy,
        Result::LEVEL_STATUS, Result::SUMMARY_INTERNAL, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_BUSY
    );

    // For internal use
    // Indicates that an unauthorized function was called for the connection port.
    NN_DEFINE_RESULT_CONST(
        ResultNotAuthorized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_NOT_AUTHORIZED
    );

    // For internal use
    // Indicates that data retrieval size specified to GetLatestVsyncTiming was bigger than the maximum storage size.
    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_OUT_OF_RANGE
    );

    // For internal use
    // Indicates that retry processing exceeded the specified number.
    NN_DEFINE_RESULT_CONST(
        ResultTimeout,
        Result::LEVEL_FATAL, Result::SUMMARY_INTERNAL, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_TIMEOUT
    );

    // For internal use
    // Indicates that it was not initialized in the process.
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_NOT_INITIALIZED
    );

}
}
}

#endif //NN_CAMERA_CTR_CAMERA_RESULT_H_
