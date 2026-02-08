/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightEvent.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os.h>

//---------------------------------------------------------------------------


namespace nn {
namespace os {

    void LightEvent::Initialize(bool isManualReset)
    {
        m_Lock.Initialize();
        *m_Counter = isManualReset ? NOT_SIGNALED_MANUAL: NOT_SIGNALED_AUTO;
    }

    // Get whether flag is set.
    bool LightEvent::TryWait()
    {
        if( *m_Counter == SIGNALED_MANUAL )
        {
            // The flag is not reset because this is a manual reset.
            return true;
        }
        else
        {
            // If the flag is set, reset the flag and return true.
            return m_Counter->CompareAndSwap(SIGNALED_AUTO, NOT_SIGNALED_AUTO) == SIGNALED_AUTO;
        }
    }

    bool LightEvent::TryWait(fnd::TimeSpan timeout)
    {
        switch( *m_Counter )
        {
        // Wait for the flag to be set and do not clear the flag.
        case NOT_SIGNALED_MANUAL:
            return m_Counter.WaitIfLessThan(0, timeout) == ResultSuccess();

        // Do not wait because the flag is set.
        case SIGNALED_MANUAL:       return true;

        // Wait because the flag is not set.
        case NOT_SIGNALED_AUTO:     break;

        // Do not wait because the flag is set. Reset the flag.
        case SIGNALED_AUTO:
            {
                if( m_Counter->CompareAndSwap(SIGNALED_AUTO, NOT_SIGNALED_AUTO) == SIGNALED_AUTO )
                {
                    return true;
                }
            }
            break;
        }


        os::Tick begin = os::Tick::GetSystemCurrent();
        os::Tick end = begin + timeout;

        for(;;)
        {
            os::Tick remainTick = end - os::Tick::GetSystemCurrent();

            if( remainTick <= 0 )
            {
                return false;
            }

            Result result = m_Counter.WaitIfLessThan(0, remainTick);

            if( result != ResultSuccess() )
            {
                return false;
            }

            if( *m_Counter == SIGNALED_AUTO )
            {
                if( m_Counter->CompareAndSwap(SIGNALED_AUTO, NOT_SIGNALED_AUTO) == SIGNALED_AUTO )
                {
                    return true;
                }
            }
        }
    }

    // Wait until the flag is set.
    void LightEvent::Wait()
    {
        for(;;)
        {
            switch( *m_Counter )
            {
            // Wait for the flag to be set and do not clear the flag.
            case NOT_SIGNALED_MANUAL:   m_Counter.WaitIfLessThan(0);    return;

            // Do not wait because the flag is set.
            case SIGNALED_MANUAL:       return;

            // Wait because the flag is not set.
            case NOT_SIGNALED_AUTO:     break;

            // Do not wait because the flag is set. Reset the flag.
            case SIGNALED_AUTO:
                {
                    if( m_Counter->CompareAndSwap(SIGNALED_AUTO, NOT_SIGNALED_AUTO) == SIGNALED_AUTO )
                    {
                        return;
                    }
                }
                break;
            }

            // Wait until the flag is set.
            // If the flag is set, m_Counter changes from NOT_SIGNALED_AUTO to SIGNALED_AUTO.
            m_Counter.WaitIfLessThan(0);
        }
    }

    // Set the flag.
    void LightEvent::Signal()
    {
        if( *m_Counter == NOT_SIGNALED_AUTO )
        {
            *m_Counter = SIGNALED_AUTO;
            // In case of auto reset, the thread with the highest priority wakes up.
            // The flag is reset at the same time the thread wakes up.
            m_Counter.Signal(1);
        }
        else if( *m_Counter == NOT_SIGNALED_MANUAL )
        {
            SimpleLock::ScopedLock lock(m_Lock);
            *m_Counter = SIGNALED_MANUAL;
            // In case of manual reset, the all waiting threads wake up.
            // The flag is not reset even if the thread wakes up.
            m_Counter.SignalAll();
        }
        // The flag remains unchanged if there is no waiting threads.
    }

    // Cancel threads waiting for the flag to be set.
    void LightEvent::Pulse()
    {
        switch( *m_Counter )
        {
        case SIGNALED_MANUAL:
            {
                SimpleLock::ScopedLock lock(m_Lock);
                *m_Counter = NOT_SIGNALED_MANUAL;
                m_Counter.SignalAll();
            }
            break;

        case NOT_SIGNALED_MANUAL:
            // Wake up all threads waiting for the flag to be set.
            // The flag is reset at the same time the thread wakes up.
            m_Counter.SignalAll();
            break;

        case NOT_SIGNALED_AUTO:
            // Of the threads waiting for a flag to be set, wakes up the highest priority thread.
            // 
            // The flag is reset at the same time the thread wakes up.
            m_Counter.Signal(1);
            break;

        case SIGNALED_AUTO:
            // Reset the flag.
            *m_Counter = NOT_SIGNALED_AUTO;
            break;
        }
    }

    // Clear the flag.
    void LightEvent::ClearSignal()
    {
        if( *m_Counter == SIGNALED_MANUAL )
        {
            SimpleLock::ScopedLock lock(m_Lock);
            *m_Counter = NOT_SIGNALED_MANUAL;
        }
        else if( *m_Counter == SIGNALED_AUTO )
        {
            *m_Counter = NOT_SIGNALED_AUTO;
        }
    }

}
}



using namespace nn;


// C Function Definitions

#include <new>

using namespace nn::os;

extern "C" {

void nnosLightEventInitialize(nnosLightEvent* p, bool isManualReset)
{
    new (p) LightEvent(isManualReset);
}

bool nnosLightEventIsSignaled(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    return pLightEvent->IsSignaled();
}

bool nnosLightEventIsManualReset(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    return pLightEvent->IsManualReset();
}

bool nnosLightEventTryWait(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    return pLightEvent->TryWait();
}

void nnosLightEventWait(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    pLightEvent->Wait();
}

void nnosLightEventSignal(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    pLightEvent->Signal();
}

void nnosLightEventPulse(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    pLightEvent->Pulse();
}

void nnosLightEventClearSignal(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    pLightEvent->ClearSignal();
}

void nnosLightEventFinalize(nnosLightEvent* p)
{
    LightEvent* pLightEvent = reinterpret_cast<LightEvent*>(p);
    pLightEvent->Finalize();
    pLightEvent->~LightEvent();
}

} // extern "C"
