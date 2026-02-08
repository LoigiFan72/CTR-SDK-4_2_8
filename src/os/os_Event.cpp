/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Event.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_Event.h>
#include <nn/assert.h>
#include <nn/config.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_Synchronization.h>
#include <nn/svc/svc_Stub.h>

#include "os_Limits.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::svc;

#include <new>

using namespace nn::os;
using namespace nn::fnd;

namespace nn { namespace os {

#if NN_PLATFORM_HAS_MMU
    s32  Event::GetCurrentCount()
    {
        return os::detail::GetLimitCurrentCount(LIMITABLE_RESOURCE_MAX_EVENT);
    }

    s32  Event::GetMaxCount()
    {
        return os::detail::GetLimitMaxCount(LIMITABLE_RESOURCE_MAX_EVENT);
    }
#endif  // if NN_PLATFORM_HAS_MMU

}}

extern "C" {

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(nnosEventToWaitObject, nnosEvent, nnosWaitObject, Event, WaitObject)
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(nnosWaitObjectToEvent, nnosWaitObject, nnosEvent, WaitObject, Event)

void nnosEventInitialize(nnosEvent* p, bool isManualReset)
{
    new (p) Event(isManualReset);
}

bool nnosEventTryInitialize(nnosEvent* p, bool manualReset)
{
    new (p) Event();
    Event* pEvent = reinterpret_cast<Event*>(p);
    Result result = pEvent->TryInitialize(manualReset);
    return result.IsSuccess();
}

void nnosEventSignal(nnosEvent* p)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    pEvent->Signal();
}

void nnosEventWaitSignal(nnosEvent* p)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    pEvent->Wait();
}

bool nnosEventTryWaitSignal(nnosEvent* p, s64 nanoSecondsTimeout)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    return pEvent->Wait(TimeSpan::FromNanoSeconds(nanoSecondsTimeout));
}

void nnosEventClearSignal(nnosEvent* p)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    pEvent->ClearSignal();
}

void nnosEventFinalize(nnosEvent* p)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    pEvent->~Event();
}

}
