/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Tick.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/assert.h>
#include <nn/config.h>
#include <nn/os/os_Tick.h>
#include <nn/svc/svc_Stub.h>

//---------------------------------------------------------------------------

#include <new>

using namespace nn::os;

extern "C" {

s64 nnosTickGetSystemCurrent(void)
{
    return nn::svc::GetSystemTick();
}

}
