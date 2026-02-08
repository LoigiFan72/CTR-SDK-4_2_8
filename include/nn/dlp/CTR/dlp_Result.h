/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47289 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_RESULT_H_
#define NN_DLP_CTR_DLP_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/


namespace nn {
namespace dlp {
namespace CTR {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_INVALID_STATE                           = 1,        //
        DESCRIPTION_INTERNAL_ERROR                          = 2,        //
        DESCRIPTION_ALREADY_OCCUPIED_WIRELESS_DEVICE        = 3,        //
        DESCRIPTION_WIRELESS_OFF                            = 4,        //
        DESCRIPTION_NOT_FOUND_SERVER                        = 5,        //
        DESCRIPTION_SERVER_IS_FULL                          = 6,        //
        DESCRIPTION_INVALID_MEDIA_TYPE                      = 7,        //
        DESCRIPTION_FAILED_TO_ACCESS_MEDIA                  = 8,        //
        DESCRIPTION_CHILD_TOO_LARGE                         = 9,        //
        DESCRIPTION_INCOMMUTABLE                            = 10,       //
        DESCRIPTION_INVALID_DLP_VERSION                     = 11,
        DESCRIPTION_INVALID_REGION                          = 12        //
    };


    NN_DEFINE_RESULT_FUNC_LSM(  MakeInvalidStateResult,     Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_STATE,     Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeInvalidArgumentResult,  Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_ARGUMENT,  Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeOutOfResourceResult,    Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE,   Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeInternalResult,         Result::LEVEL_PERMANENT, Result::SUMMARY_INTERNAL,          Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeNotSupportedResult,     Result::LEVEL_PERMANENT, Result::SUMMARY_NOT_SUPPORTED,     Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeNotFoundResult,         Result::LEVEL_STATUS,    Result::SUMMARY_NOT_FOUND,         Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeOutOfResourceResulttemporarily, Result::LEVEL_STATUS,    Result::SUMMARY_OUT_OF_RESOURCE,   Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeStatusChangedResult,    Result::LEVEL_STATUS,    Result::SUMMARY_STATUS_CHANGED,    Result::MODULE_NN_DLP);
    NN_DEFINE_RESULT_FUNC_LSM(  MakeCanceledResult,         Result::LEVEL_STATUS,    Result::SUMMARY_CANCELLED,         Result::MODULE_NN_DLP);

    /* Please see man pages for details 
      
      
    */

    // LEVEL_USAGE
    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultAlreadyOccupiedWirelessDevice,
            MakeInvalidStateResult, DESCRIPTION_ALREADY_OCCUPIED_WIRELESS_DEVICE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInvalidState,
            MakeInvalidStateResult, DESCRIPTION_INVALID_STATE
    );

    // LEVEL_PERMANENT
    /* Please see man pages for details 
        
        
        
    */
	NN_DEFINE_RESULT_CONST_LSM(
			ResultOutOfRange,
			MakeInvalidArgumentResult, Result::DESCRIPTION_OUT_OF_RANGE
	);

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInvalidPointer,
            MakeInvalidArgumentResult, Result::DESCRIPTION_INVALID_POINTER
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInvalidHandle,
            MakeInvalidArgumentResult, Result::DESCRIPTION_INVALID_HANDLE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInternalError,
            MakeInternalResult, DESCRIPTION_INTERNAL_ERROR
    );

    NN_DEFINE_RESULT_CONST_LSM(
            ResultOutOfMemory,
            MakeOutOfResourceResult, Result::DESCRIPTION_OUT_OF_MEMORY
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInvalidMediaType,
            MakeNotSupportedResult, DESCRIPTION_INVALID_MEDIA_TYPE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultFailedToAccessMedia,
            MakeInternalResult, DESCRIPTION_FAILED_TO_ACCESS_MEDIA
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultChildTooLarge,
            MakeNotSupportedResult, DESCRIPTION_CHILD_TOO_LARGE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInvalidRegion,
            MakeNotSupportedResult, DESCRIPTION_INVALID_REGION
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultInvalidDlpVersion,
            MakeNotSupportedResult, DESCRIPTION_INVALID_DLP_VERSION
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultIncommutable,
            MakeNotSupportedResult, DESCRIPTION_INCOMMUTABLE
    );

    // LEVEL_STATUS
    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultNoData,
            MakeNotFoundResult, Result::DESCRIPTION_NO_DATA
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultWirelessOff,
            MakeStatusChangedResult, DESCRIPTION_WIRELESS_OFF
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultNotFoundServer,
            MakeNotFoundResult, DESCRIPTION_NOT_FOUND_SERVER
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultServerIsFull,
            MakeOutOfResourceResulttemporarily, DESCRIPTION_SERVER_IS_FULL
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultDeniedFromServer,
            MakeCanceledResult, Result::DESCRIPTION_CANCEL_REQUESTED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LSM(
            ResultConnectionTimeout,
            MakeCanceledResult, Result::DESCRIPTION_TIMEOUT
    );

    /*  

*/
}
}
}


#endif /* NN_DLP_CTR_DLP_RESULT_H_ */
