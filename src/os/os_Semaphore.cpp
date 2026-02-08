/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Semaphore.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_Semaphore.h>
#include <nn/assert.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_Synchronization.h>
#include <nn/svc/svc_Stub.h>

#include "os_Limits.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::svc;


// C Function Definitions

#include <new>

using namespace nn::fnd;
using namespace nn::os;

namespace nn { namespace os {

#if NN_PLATFORM_HAS_MMU
    s32  Semaphore::GetCurrentCount()
    {
        return os::detail::GetLimitCurrentCount(LIMITABLE_RESOURCE_MAX_SEMAPHORE);
    }

    s32  Semaphore::GetMaxCount()
    {
        return os::detail::GetLimitMaxCount(LIMITABLE_RESOURCE_MAX_SEMAPHORE);
    }
#endif  // if NN_PLATFORM_HAS_MMU

}}

extern "C" {

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(nnosSemaphoreToWaitObject, nnosSemaphore, nnosWaitObject, Semaphore, WaitObject)
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(nnosWaitObjectToSemaphore, nnosWaitObject, nnosSemaphore, WaitObject, Semaphore)


void nnosSemaphoreInitialize(nnosSemaphore* p, s32 initialCount, s32 maxCount)
{
    new (p) Semaphore(initialCount, maxCount);
}

bool nnosSemaphoreTryInitialize(nnosSemaphore* p, s32 initialCount, s32 maxCount)
{
    new (p) Semaphore();
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    Result result = pSemaphore->TryInitialize(initialCount, maxCount);
    return result.IsSuccess();
}

s32 nnosSemaphoreRelease(nnosSemaphore* p, s32 releaseCount)
{
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    return pSemaphore->Release(releaseCount);
}

void nnosSemaphoreAcquire(nnosSemaphore* p)
{
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    pSemaphore->Acquire();
}

bool nnosSemaphoreTryAcquire(nnosSemaphore* p, s64 nanoSeconds)
{
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    return pSemaphore->TryAcquire(TimeSpan::FromNanoSeconds(nanoSeconds));
}

void nnosSemaphoreFinalize(nnosSemaphore* p)
{
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    pSemaphore->~Semaphore();
}

}
