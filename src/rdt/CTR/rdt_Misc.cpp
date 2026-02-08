/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Misc.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#include "stdafx.h"

#include <nn/rdt/CTR/rdt_Misc.h>

#include <nn/rdt/CTR/rdt_Result.h>


namespace
{

    bit32 s_logLevel = nn::rdt::CTR::LOG_LEVEL_NONE;

}  // end of anonymous namespace

namespace nn { namespace rdt { namespace CTR {


nn::Result SetLogLevel(const bit32 level)
{
    switch(level)
    {
    case LOG_LEVEL_NONE:
    case LOG_LEVEL_ALL:
        s_logLevel = level;
        return ResultSuccess();
    default:
        return ResultInvalidValue();
    }
}


bit32 GetLogLevel(void)
{
    return s_logLevel;
}


}}} // namespace nn::rdt::CTR
