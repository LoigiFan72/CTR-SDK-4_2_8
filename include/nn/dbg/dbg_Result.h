/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Result.h

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

#ifndef NN_DBG_DBG_RESULT_H_
#define NN_DBG_DBG_RESULT_H_

#include <nn/Result.h>

#ifdef __cplusplus
namespace nn { namespace dbg {

/*
    
    

*/
enum ResultDescription
{
    DESCRIPTION_DBEUG_OUTPUT_IS_DISABLED = 1,   //
    DESCRIPTION_DEBUGGER_NOT_PRESENT,           //
    DESCRIPTION_INACCESSIBLE_PAGE               //
};

NN_DEFINE_RESULT_FUNC_LM(MakeInformationalResult, Result::LEVEL_INFO, Result::MODULE_NN_DBG);
NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_DBG);

NN_DEFINE_RESULT_CONST_LM(
    ResultDebugOutputIsDisabled,
    MakeInformationalResult, Result::SUMMARY_NOTHING_HAPPENED, DESCRIPTION_DBEUG_OUTPUT_IS_DISABLED
);

NN_DEFINE_RESULT_CONST_LM(
    ResultInaccessiblePage,
    MakePermanentResult, Result::SUMMARY_WRONG_ARGUMENT, DESCRIPTION_INACCESSIBLE_PAGE
);

NN_DEFINE_RESULT_CONST(
    ResultOutOfRange,
    Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_DBG, Result::DESCRIPTION_OUT_OF_RANGE
);

NN_DEFINE_RESULT_CONST_LM(
    ResultDebuggerNotPresent,
    MakeInformationalResult, Result::SUMMARY_NOTHING_HAPPENED, DESCRIPTION_DEBUGGER_NOT_PRESENT
);

}}

#endif  // ifdef __cplusplus


#endif /* NN_DBG_DBG_RESULT_H_ */
