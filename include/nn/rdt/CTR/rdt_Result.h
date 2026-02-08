/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

////#include <stdafx.h>

#ifndef NN_RDT_RESULT_H_
#define NN_RDT_RESULT_H_

#include <nn/Result.h>


namespace nn { namespace rdt { namespace CTR {


enum Description
{
    DESCRIPTION_RESET_RECEIVED = 1,   //
    DESCRIPTION_UNTIMELY_CALL  = 2,   //
    DESCRIPTION_INVALID_VALUE  = 3    //
};


/*
Please see man pages for details



 */
NN_DEFINE_RESULT_CONST(
    ResultAlreadyInitialized,
    Result::LEVEL_INFO,
    Result::SUMMARY_NOTHING_HAPPENED,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_ALREADY_INITIALIZED);


/*
Please see man pages for details



*/
NN_DEFINE_RESULT_CONST(
    ResultDoNothing,
    Result::LEVEL_INFO,
    Result::SUMMARY_NOTHING_HAPPENED,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_SUCCESS);


/*
Please see man pages for details




*/
NN_DEFINE_RESULT_CONST(
    ResultNotInitialized,
    Result::LEVEL_USAGE,
    Result::SUMMARY_INVALID_STATE,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_NOT_INITIALIZED);


/*
Please see man pages for details







 */
NN_DEFINE_RESULT_CONST(
    ResultSendBufferIsNotAvailable,
    Result::LEVEL_TEMPORARY,
    Result::SUMMARY_OUT_OF_RESOURCE,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_OUT_OF_MEMORY);


/*
Please see man pages for details



 */
NN_DEFINE_RESULT_CONST(
    ResultInvalidSize,
    Result::LEVEL_USAGE,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_INVALID_SIZE);


/*
Please see man pages for details





 */
NN_DEFINE_RESULT_CONST(
    ResultMisalignedAddress,
    Result::LEVEL_USAGE,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_MISALIGNED_ADDRESS);


/*
Please see man pages for details




 */
NN_DEFINE_RESULT_CONST(
    ResultNullPointer,
    Result::LEVEL_USAGE,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_INVALID_POINTER);


/*
Please see man pages for details






 */
NN_DEFINE_RESULT_CONST(
    ResultResetReceived,
    Result::LEVEL_STATUS,
    Result::SUMMARY_STATUS_CHANGED,
    Result::MODULE_NN_RDT,
            DESCRIPTION_RESET_RECEIVED);


/*
Please see man pages for details




 */
NN_DEFINE_RESULT_CONST(
    ResultResendQueueIsFull,
    Result::LEVEL_RESET,
    Result::SUMMARY_OUT_OF_RESOURCE,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_OUT_OF_MEMORY);


/*
Please see man pages for details





 */
NN_DEFINE_RESULT_CONST(
    ResultUntimelyFunctionCall,
    Result::LEVEL_STATUS,
    Result::SUMMARY_INVALID_STATE,
    Result::MODULE_NN_RDT,
            DESCRIPTION_UNTIMELY_CALL);


/*
Please see man pages for details




 */
NN_DEFINE_RESULT_CONST(
    ResultNoData,
    Result::LEVEL_TEMPORARY,
    Result::SUMMARY_NOT_FOUND,
    Result::MODULE_NN_RDT,
    Result::DESCRIPTION_NO_DATA);


/*
Please see man pages for details



 */
NN_DEFINE_RESULT_CONST(
    ResultInvalidValue,
    Result::LEVEL_USAGE,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_RDT,
            DESCRIPTION_INVALID_VALUE);


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_RESULT_H_
