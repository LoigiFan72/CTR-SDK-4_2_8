/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47276 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CEC_RESULT_H_
#define NN_CEC_CEC_RESULT_H_

#include <nn/Result.h>

namespace nn {
namespace cec {

enum ResultDescription
{
    DESCRIPTION_UNKNOWN = 100,

    DESCRIPTION_BOXSIZE_FULL,
    DESCRIPTION_BOXMESSNUM_FULL,
    DESCRIPTION_BOXNUM_FULL,
    DESCRIPTION_BOX_ALREADY_EXISTS,

    DESCRIPTION_MESS_TOO_LARGE,
    DESCRIPTION_INVALID_DATA,
    DESCRIPTION_INVALID_ID,

    DESCRIPTION_NOT_AGREE_EULA,                 //
    DESCRIPTION_PARENTAL_CONTROL_CEC,           //

    DESCRIPTION_FILE_ACCESS_FAILED,             //


    DESCRIPTION_END
};

NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_ALREADY_INITIALIZED 
    );
NN_DEFINE_RESULT_CONST(
        MakeResultAlreadyInitialized,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_ALREADY_INITIALIZED 
    );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultNotAgreeEula,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, DESCRIPTION_NOT_AGREE_EULA );
NN_DEFINE_RESULT_CONST(
        MakeResultNotAgreeEula,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, DESCRIPTION_NOT_AGREE_EULA );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultParentalControlCec,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, DESCRIPTION_PARENTAL_CONTROL_CEC );
NN_DEFINE_RESULT_CONST(
        MakeResultParentalControlCec,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, DESCRIPTION_PARENTAL_CONTROL_CEC );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_USAGE,  Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_CEC, Result::DESCRIPTION_NOT_INITIALIZED );
NN_DEFINE_RESULT_CONST(
        MakeResultNotInitialized,
        Result::LEVEL_USAGE,  Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_CEC, Result::DESCRIPTION_NOT_INITIALIZED );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultAlreadyDone,
        Result::LEVEL_USAGE,  Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_CEC, Result::DESCRIPTION_ALREADY_DONE );
NN_DEFINE_RESULT_CONST(
        MakeResultAlreadyDone,
        Result::LEVEL_USAGE,  Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_CEC, Result::DESCRIPTION_ALREADY_DONE );

/* Please see man pages for details 

    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultInvalidState,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_INVALID_COMBINATION );
NN_DEFINE_RESULT_CONST(
        MakeResultInvalidState,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_INVALID_COMBINATION );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultInvalidCombination,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_INVALID_COMBINATION );
NN_DEFINE_RESULT_CONST(
        MakeResultInvalidCombination,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_INVALID_COMBINATION );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultInvalidArgument,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_OUT_OF_RANGE );
NN_DEFINE_RESULT_CONST(
        MakeResultInvalidArgument,
        Result::LEVEL_USAGE,  Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_OUT_OF_RANGE );
/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultBufferFull,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_CEC, Result::DESCRIPTION_OUT_OF_MEMORY );

NN_DEFINE_RESULT_CONST(
        MakeResultBufferFull,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_CEC, Result::DESCRIPTION_OUT_OF_MEMORY );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultNoData,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_CEC, Result::DESCRIPTION_NO_DATA );

NN_DEFINE_RESULT_CONST(
        MakeResultNoData,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_CEC, Result::DESCRIPTION_NO_DATA );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultNotAuthorized,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_CEC, Result::DESCRIPTION_NOT_AUTHORIZED );

NN_DEFINE_RESULT_CONST(
        MakeResultNotAuthorized,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_CEC, Result::DESCRIPTION_NOT_AUTHORIZED );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultTooLarge,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_TOO_LARGE );

NN_DEFINE_RESULT_CONST(
        MakeResultTooLarge,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_TOO_LARGE );



/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultBoxSizeFull,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOXSIZE_FULL );

NN_DEFINE_RESULT_CONST(
        MakeResultBoxSizeFull,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOXSIZE_FULL );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultBoxMessNumFull,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOXMESSNUM_FULL );

NN_DEFINE_RESULT_CONST(
        MakeResultBoxMessNumFull,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOXMESSNUM_FULL );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultBoxNumFull,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOXNUM_FULL );

NN_DEFINE_RESULT_CONST(
        MakeResultBoxNumFull,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOXNUM_FULL );


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultBoxAlreadyExists,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOX_ALREADY_EXISTS );

NN_DEFINE_RESULT_CONST(
        MakeResultBoxAlreadyExists,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_BOX_ALREADY_EXISTS );
/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultMessTooLarge,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_MESS_TOO_LARGE );

NN_DEFINE_RESULT_CONST(
        MakeResultMessTooLarge,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_MESS_TOO_LARGE );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultInvalidId,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_INVALID_ID );

NN_DEFINE_RESULT_CONST(
        MakeResultInvalidId,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_INVALID_ID );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultInvalidData,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_INVALID_DATA );

NN_DEFINE_RESULT_CONST(
        MakeResultInvalidData,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, DESCRIPTION_INVALID_DATA );
/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultInvalidPointer,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_INVALID_POINTER);

NN_DEFINE_RESULT_CONST(
        MakeResultInvalidPointer,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CEC, Result::DESCRIPTION_INVALID_POINTER);


/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultStateBusy,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_BUSY );

NN_DEFINE_RESULT_CONST(
        MakeResultStateBusy,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_BUSY );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultMisalignedSize,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_MISALIGNED_SIZE );

NN_DEFINE_RESULT_CONST(
        MakeResultMisalignedSize,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, Result::DESCRIPTION_MISALIGNED_SIZE );

/* Please see man pages for details 
    
    
    
*/
NN_DEFINE_RESULT_CONST(
        ResultFileAccessFailed,
        Result::LEVEL_TEMPORARY, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_CEC, DESCRIPTION_FILE_ACCESS_FAILED );


} // namespace cec
} // namespace nn


#endif  // NN_CEC_CEC_RESULT_H_

