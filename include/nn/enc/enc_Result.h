/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     enc_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ENC_ENC_RESULT_H_
#define NN_ENC_ENC_RESULT_H_

#include <nn/Result.h>

#ifdef __cplusplus

namespace nn { namespace enc {

enum Description
{
    DESCRIPTION_NO_BUFFER_LEFT = 1,
    DESCRIPTION_INVALID_PARAMETER,
    DESCRIPTION_INVALID_FORMAT
};

NN_DEFINE_RESULT_FUNC_LM(
    MakeUsageResult,
    Result::LEVEL_USAGE, Result::MODULE_NN_ENC
);

NN_DEFINE_RESULT_FUNC_LM(
    MakePermanentResult,
    Result::LEVEL_PERMANENT, Result::MODULE_NN_ENC
);

NN_DEFINE_RESULT_CONST_LM(
    ResultNoBufferLeft, MakePermanentResult,
    Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_NO_BUFFER_LEFT
);

NN_DEFINE_RESULT_CONST_LM(
    ResultInvalidParameter, MakeUsageResult,
    Result::SUMMARY_INVALID_ARGUMENT, DESCRIPTION_INVALID_PARAMETER
);

NN_DEFINE_RESULT_CONST_LM(
    ResultInvalidFormat, MakePermanentResult,
    Result::SUMMARY_INVALID_ARGUMENT, DESCRIPTION_INVALID_FORMAT
);

}}

#endif // __cplusplus

#endif /* NN_ENC_ENC_RESULT_H_ */
