/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Timer.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_Timer.h>
#include <nn/assert.h>
#include <nn/config.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_Synchronization.h>
#include <nn/svc/svc_Stub.h>

#include "os_Limits.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::svc;

// C Function Definitions

#include <new>

using namespace nn::os;

namespace nn { namespace os {

#if NN_PLATFORM_HAS_MMU
    s32  Timer::GetCurrentCount()
    {
        return os::detail::GetLimitCurrentCount(LIMITABLE_RESOURCE_MAX_TIMER);
    }

    s32  Timer::GetMaxCount()
    {
        return os::detail::GetLimitMaxCount(LIMITABLE_RESOURCE_MAX_TIMER);
    }
#endif  // if NN_PLATFORM_HAS_MMU

}}

extern "C" {

NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosTimerToWaitObject, nnosTimer, nnosWaitObject);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosWaitObjectToTimer, nnosWaitObject, nnosTimer);

void nnosTimerInitialize(nnosTimer* p, bool isManualReset)
{
    new (p) Timer(isManualReset);
}

bool nnosTimerTryInitialize(nnosTimer* p, bool isManualReset)
{
    new (p) Timer();
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    Result result = pTimer->TryInitialize(isManualReset);
    return result.IsSuccess();
}

void nnosTimerStartPeriodic(nnosTimer* p, s64 first, s64 interval)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->StartPeriodic(nn::fnd::TimeSpan::FromNanoSeconds(first), nn::fnd::TimeSpan::FromNanoSeconds(interval));
}

void nnosTimerStartOneShot(nnosTimer* p, s64 time)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->StartOneShot(nn::fnd::TimeSpan::FromNanoSeconds(time));
}

void nnosTimerWait(nnosTimer* p)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->Wait();
}

void nnosTimerStop(nnosTimer* p)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->Stop();
}

void nnosTimerClearSignal(nnosTimer* p)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->ClearSignal();
}

void nnosTimerFinalize(nnosTimer* p)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->~Timer();
}

void nnosTimerSignal(nnosTimer* p)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    pTimer->Signal();
}

}
