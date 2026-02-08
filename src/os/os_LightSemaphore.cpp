/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightSemaphore.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os.h>

//---------------------------------------------------------------------------

namespace nn {
namespace os {

    s32 LightSemaphore::Release(s32 releaseCount /*= 1*/)
    {
        NN_MIN_TASSERT_( releaseCount, 1 );

#if NN_PLATFORM_HAS_16BIT_LL_SC
        LimitedAdd updater;
        updater.max   = m_Max;
        updater.value = releaseCount;

        m_Counter->AtomicUpdateConditional(updater);
        const s32 beforeUpdate = updater.beforeUpdate;
#else
        const s32 beforeUpdate = m_Counter->operator++(0);
#endif

        // If the counter before addition is zero, the thread for the value to be added is woken up.
        if( (beforeUpdate <= 0) || (m_NumWaiting > 0) )
        {
            m_Counter.Signal(releaseCount);
        }

        return beforeUpdate;
    }

    bool LightSemaphore::TryAcquire(fnd::TimeSpan timeout)
    {
        if( TryAcquire() )
        {
            return true;
        }

        os::Tick begin = os::Tick::GetSystemCurrent();
        os::Tick end = begin + timeout;

        do
        {
            os::Tick remainTick = end - os::Tick::GetSystemCurrent();

            if( remainTick <= 0 )
            {
                return false;
            }

            ++m_NumWaiting;
            Result result = m_Counter.WaitIfLessThan(1, remainTick);
            --m_NumWaiting;

            if( result != ResultSuccess() )
            {
                return false;
            }

        } while( ! TryAcquire() );

        return true;
    }

}
}

using namespace nn;


// C Function Definitions

#include <new>

using namespace nn::os;

extern "C" {

void nnosLightSemaphoreInitialize(nnosLightSemaphore* p, s32 initialCount, s32 maxCount)
{
    new (p) LightSemaphore();
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    pLightSemaphore->Initialize(initialCount, maxCount);
}

#if NN_PLATFORM_HAS_16BIT_LL_SC
s32 nnosLightSemaphoreGetMax(nnosLightSemaphore* p)
{
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    return pLightSemaphore->GetMax();
}
#endif

s32 nnosLightSemaphoreGetCount(nnosLightSemaphore* p)
{
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    return pLightSemaphore->GetCount();
}

s32 nnosLightSemaphoreRelease(nnosLightSemaphore* p, s32 releaseCount)
{
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    return pLightSemaphore->Release(releaseCount);
}

void nnosLightSemaphoreAcquire(nnosLightSemaphore* p)
{
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    pLightSemaphore->Acquire();
}

bool nnosLightSemaphoreTryAcquire(nnosLightSemaphore* p)
{
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    return pLightSemaphore->TryAcquire();
}

void nnosLightSemaphoreFinalize(nnosLightSemaphore* p)
{
    LightSemaphore* pLightSemaphore = reinterpret_cast<LightSemaphore*>(p);
    pLightSemaphore->~LightSemaphore();
}

} // extern "C"
