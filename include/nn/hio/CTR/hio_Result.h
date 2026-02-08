/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HIO_CTR_HIO_RESULT_H_
#define NN_HIO_CTR_HIO_RESULT_H_

#include <nn/Result.h>

namespace nn {
namespace hio {
namespace CTR {

    /* Please see man pages for details 
        
    */
    enum ResultDescription
    {
        DESCRIPTION_INVALID_SELECTION,          //
        DESCRIPTION_TOO_LARGE,                  //
        DESCRIPTION_NOT_AUTHORIZED,             //
        DESCRIPTION_ALREADY_DONE,               //
        DESCRIPTION_INVALID_SIZE,               //
        DESCRIPTION_INVALID_ENUM_VALUE,         //
        DESCRIPTION_INVALID_COMBINATION,        //
        DESCRIPTION_NO_DATA,                    //
        DESCRIPTION_BUSY,                       //
        DESCRIPTION_MISALIGNED_ADDRESS,         //
        DESCRIPTION_MISALIGNED_SIZE,            //
        DESCRIPTION_OUT_OF_MEMORY,              //
        DESCRIPTION_NOT_IMPLEMENTED,            //
        DESCRIPTION_INVALID_ADDRESS,            //
        DESCRIPTION_INVALID_POINTER,            //
        DESCRIPTION_INVALID_HANDLE,             //
        DESCRIPTION_NOT_INITIALIZED,            //
        DESCRIPTION_ALREADY_INITIALIZED,        //
        DESCRIPTION_NOT_FOUND,                  //
        DESCRIPTION_CANCEL_REQUESTED,           //
        DESCRIPTION_ALREADY_EXISTS,             //
        DESCRIPTION_OUT_OF_RANGE,               //
        DESCRIPTION_TIMEOUT,                    //
        DESCRIPTION_INVALID_RESULT_VALUE,       //
        DESCRIPTION_END
    };


    // Definitions for result values used by hio

    NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_HIO);
    NN_DEFINE_RESULT_FUNC_LM(MakeTemporaryResult, Result::LEVEL_TEMPORARY, Result::MODULE_NN_HIO);
    NN_DEFINE_RESULT_FUNC_LM(MakeStatusResult,    Result::LEVEL_STATUS,    Result::MODULE_NN_HIO);

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidSection,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_INVALID_SELECTION
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultAlreadyExists,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_ALREADY_EXISTS
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultNotAuthorized,
        MakePermanentResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_NOT_AUTHORIZED
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultTooLarge,
        MakePermanentResult, Result::SUMMARY_INVALID_ARGUMENT, DESCRIPTION_TOO_LARGE
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultBusy,
        MakePermanentResult, Result::SUMMARY_STATUS_CHANGED, DESCRIPTION_BUSY
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidHandle,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_HANDLE
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidPointer,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_POINTER
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidSize,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_SIZE
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidEnumValue,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_ENUM_VALUE
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultMisalignedAddress,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_MISALIGNED_ADDRESS
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultMisalignedSize,
        MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_MISALIGNED_SIZE
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultCancelRequested,
        MakePermanentResult, Result::SUMMARY_NOT_SUPPORTED, DESCRIPTION_CANCEL_REQUESTED
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultAlreadyDone,
        MakePermanentResult, Result::SUMMARY_NOTHING_HAPPENED, DESCRIPTION_ALREADY_DONE
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultNotFound,
        MakePermanentResult, Result::SUMMARY_NOT_FOUND, DESCRIPTION_NOT_FOUND
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidAddress,
        MakeStatusResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_ADDRESS
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidCombination,
        MakeStatusResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INVALID_COMBINATION
    );

    NN_DEFINE_RESULT_CONST_LM(
        ResultCancelledBusy,
        MakeTemporaryResult, Result::SUMMARY_CANCELLED, DESCRIPTION_BUSY
    );


} // namespace CTR
} // namespace hio
} // namespace nn

#endif //NN_HIO_CTR_HIO_RESULT_H_
