/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CFG_RESULT_H_
#define NN_CFG_CFG_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn { namespace cfg {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_NOT_VERIFIED                        = 1,        //
        DESCRIPTION_VERIFICATION_FAILED                 = 2,        //
        DESCRIPTION_INVALID_NTR_SETTING                 = 3,        //
        DESCRIPTION_ALREADY_LATEST_VERSION              = 4,        //
        DESCRIPTION_MOUNT_CONTENT_FAILED                = 5,        //
        DESCRIPTION_OBSOLETE_RESULT                     = 1023      //
    };
    
    NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_CFG);
    
    
    NN_DEFINE_RESULT_CONST(
        MakeResultOutOfMemory,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_CFG, nn::Result::DESCRIPTION_OUT_OF_MEMORY
    );

    NN_DEFINE_RESULT_CONST(
        MakeResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CFG, nn::Result::DESCRIPTION_OUT_OF_RANGE
    );
    
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultNotInitialized,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, nn::Result::DESCRIPTION_NOT_INITIALIZED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultNotVerified,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_NOT_VERIFIED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultVerificationFailed,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_VERIFICATION_FAILED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultInvalidSize,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, nn::Result::DESCRIPTION_INVALID_SIZE
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultAlreadyExists,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, nn::Result::DESCRIPTION_ALREADY_EXISTS
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultNotFound,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, nn::Result::DESCRIPTION_NOT_FOUND
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultNotAuthorized,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, nn::Result::DESCRIPTION_NOT_AUTHORIZED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultInvalidNtrSetting,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_NTR_SETTING
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultAlreadyInitialized,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, nn::Result::DESCRIPTION_ALREADY_INITIALIZED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultInvalidHandle,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, nn::Result::DESCRIPTION_INVALID_HANDLE
    );
    
    NN_DEFINE_RESULT_CONST(
        MakeResultAlreadyLatestVersion,
        Result::LEVEL_INFO, Result::SUMMARY_SUCCESS, Result::MODULE_NN_CFG, DESCRIPTION_ALREADY_LATEST_VERSION
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultCancelRequested,
        MakePermanentResult, Result::SUMMARY_CANCELLED, nn::Result::DESCRIPTION_CANCEL_REQUESTED
    );
    
    NN_DEFINE_RESULT_CONST_LM(
        MakeResultMountContentFailed,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_MOUNT_CONTENT_FAILED
    );
    
    namespace CTR {
        
        /* Please see man pages for details 
            
            
            
        */
        typedef MakeResultMountContentFailed    ResultOutOfMemory;
        
        /* Please see man pages for details 
            
            
            
        */
        typedef MakeResultNotFound              ResultNotFound;
        
        /* Please see man pages for details 
            
            
            
        */
        typedef MakeResultMountContentFailed    ResultMountContentFailed;
        
    }
}}

#endif // __cplusplus

#endif /* NN_CFG_CFG_RESULT_H_ */
