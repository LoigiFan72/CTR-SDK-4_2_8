/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Mutex.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_Mutex.h>
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

using namespace nn::fnd;
using namespace nn::os;

namespace nn { namespace os {

#if NN_PLATFORM_HAS_MMU
    s32  Mutex::GetCurrentCount()
    {
        return os::detail::GetLimitCurrentCount(LIMITABLE_RESOURCE_MAX_MUTEX);
    }

    s32  Mutex::GetMaxCount()
    {
        return os::detail::GetLimitMaxCount(LIMITABLE_RESOURCE_MAX_MUTEX);
    }
#endif  // if NN_PLATFORM_HAS_MMU

}}

extern "C" {

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(nnosMutexToWaitObject, nnosMutex, nnosWaitObject, Mutex, WaitObject)
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(nnosWaitObjectToMutex, nnosWaitObject, nnosMutex, WaitObject, Mutex)

void nnosMutexInitialize(nnosMutex* p, bool initialLocked)
{
    new (p) Mutex(initialLocked);
}

bool nnosMutexTryInitialize(nnosMutex* p, bool initialLocked)
{
    new (p) Mutex();
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    Result result = pMutex->TryInitialize(initialLocked);
    return result.IsSuccess();
}

void nnosMutexLock(nnosMutex* p)
{
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    pMutex->Lock();
}

bool nnosMutexTryLock(nnosMutex* p, s64 timeout)
{
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    return pMutex->TryLock(TimeSpan::FromNanoSeconds(timeout));
}

void nnosMutexUnlock(nnosMutex* p)
{
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    pMutex->Unlock();
}

void nnosMutexFinalize(nnosMutex* p)
{
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    pMutex->~Mutex();
}

}
