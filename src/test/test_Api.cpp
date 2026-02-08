/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_Api.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/Result.h>
#include <nn/dbg.h>

namespace nn{ namespace test{

#if !defined(NN_SWITCH_DISABLE_ASSERT_WARNING)
    void PrintResult(nn::Result result)
    {
        nn::dbg::detail::TPrintf("  Level:       %s (%d)\n", nn::dbg::detail::GetLevelString(result),       result.GetLevel());
        nn::dbg::detail::TPrintf("  Summary:     %s (%d)\n", nn::dbg::detail::GetSummaryString(result),     result.GetSummary());
        nn::dbg::detail::TPrintf("  Module:      %s (%d)\n", nn::dbg::detail::GetModuleString(result),      result.GetModule());
        nn::dbg::detail::TPrintf("  Description: %s (%d)\n", nn::dbg::detail::GetDescriptionString(result), result.GetDescription());
    }
#else
    void PrintResult(nn::Result result)
    {
        nn::dbg::detail::TPrintf("Result:%08X\n", result.GetPrintableBits());
    }
#endif

}}
