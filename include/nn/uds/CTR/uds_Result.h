/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47172 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UDS_CTR_UDS_RESULT_H_
#define NN_UDS_CTR_UDS_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/


namespace nn {
namespace uds {
namespace CTR {
//New definition

    /*
        
    */
    enum Description
    {
        DESCRIPTION_NETWORK_IS_FULL          = 1,        //
        DESCRIPTION_WIFI_OFF                 = 2,        //
        DESCRIPTION_INVALID_PARAMS           = 3,        //
        DESCRIPTION_MISCELLANOUS_SYSTEM_ERROR= 4,        //
        DESCRIPTION_MALFORMED_DATA           = 5,        //
        DESCRIPTION_INVALID_SDK_VERSION      = 6,        // Non-public error: the UDS SDK version is invalid.
        DESCRIPTION_SYSTEM_ERROR             = 7,        //
        DESCRIPTION_INVALID_DATA             = 8,        //
        DESCRIPTION_MAX
    };

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotFoundNetwork,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_UDS, Result::DESCRIPTION_NOT_FOUND
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyNetworkIsFull,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_UDS, DESCRIPTION_NETWORK_IS_FULL
    );

/* Please see man pages for details 
    
    
    
           
*/
    NN_DEFINE_RESULT_CONST(
        ResultDeniedFromMaster,
        Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_UDS, Result::DESCRIPTION_CANCEL_REQUESTED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultConnectionTimeout,
        Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_UDS, Result::DESCRIPTION_TIMEOUT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidState,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_UDS, Result::DESCRIPTION_NOT_AUTHORIZED
    );

/* Please see man pages for details 
    
    
    
           
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidNode,
        Result::LEVEL_STATUS, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_NOT_FOUND
    );

/* Please see man pages for details 
    
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultOutOfResource,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_UDS, Result::DESCRIPTION_OUT_OF_MEMORY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultBufferIsFull,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_UDS, Result::DESCRIPTION_BUSY
    );

/* Please see man pages for details 
    
    
    

    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultWirelessOff,
        Result::LEVEL_STATUS, Result::SUMMARY_STATUS_CHANGED, Result::MODULE_NN_UDS, DESCRIPTION_WIFI_OFF
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_UDS, Result::DESCRIPTION_NOT_INITIALIZED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyOccupiedWirelessDevice,
        Result::LEVEL_USAGE, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_UDS, Result::DESCRIPTION_ALREADY_INITIALIZED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMisalignedAddress,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_MISALIGNED_ADDRESS
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMisalignedSize,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_MISALIGNED_SIZE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultTooLarge,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_TOO_LARGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotAuthorized,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_NOT_AUTHORIZED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMiscellaneousSystemError,
        Result::LEVEL_TEMPORARY, Result::SUMMARY_INTERNAL, Result::MODULE_NN_UDS, DESCRIPTION_MISCELLANOUS_SYSTEM_ERROR
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotImplemented,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_UDS, Result::DESCRIPTION_NOT_IMPLEMENTED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMalformedData,
        Result::LEVEL_USAGE, Result::SUMMARY_CANCELLED, Result::MODULE_NN_UDS, DESCRIPTION_MALFORMED_DATA
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidPointer,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_UDS, Result::DESCRIPTION_INVALID_POINTER
    );
/* Please see man pages for details 
    
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultRequestCanceled,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE , Result::MODULE_NN_UDS, Result::DESCRIPTION_CANCEL_REQUESTED 
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidData,
        Result::LEVEL_USAGE, Result::SUMMARY_CANCELLED, Result::MODULE_NN_UDS, DESCRIPTION_INVALID_DATA
    );
/*  

*/

/******************************
  Error used only within the system
 ******************************/
    NN_DEFINE_RESULT_CONST(
        ResultInvalildSdkVersion,
        Result::LEVEL_FATAL, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_UDS, DESCRIPTION_INVALID_SDK_VERSION
    );

    NN_DEFINE_RESULT_CONST(
        ResultSystemError,
        Result::LEVEL_FATAL, Result::SUMMARY_INTERNAL, Result::MODULE_NN_UDS, DESCRIPTION_SYSTEM_ERROR
    );


} // namespace CTR
} // namespace uds
} // namespace nn

#endif //NN_UDS_CTR_UDS_RESULT_H_
