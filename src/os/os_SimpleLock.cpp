/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SimpleLock.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46850 $
 *---------------------------------------------------------------------------*/

#include <nn/os.h>
#include <nn/os/os_SimpleLock.h>

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::fnd;
using namespace nn::svc;
using namespace nn::os;
using namespace nn::util;

namespace nn{ namespace os{

    namespace
    {
        struct ReverseIfPositiveUpdater
        {
            bool operator()(s32& x)
            {
                if( x > 0 )
                {
                    x = -x;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        };

        struct ReverseUpdater
        {
            s32 afterUpdate;
            bool operator()(s32& x)
            {
                x = -x;
                afterUpdate = x;
                return true;
            }
        };

        struct DecrementIfNegativeUpdater
        {
            bool operator()(s32& x)
            {
                if( x < 0 )
                {
                    --x;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        };

        struct ReverseAndIncrementIfPositiveUpdater
        {
            bool operator()(s32& x)
            {
                if( x > 0 )
                {
                    x = -x + 1;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        };
    }

    //
    // m_Counter value
    //
    //  +1      Unlocked state
    //  -1      1 client obtains lock
    //  -2      1 client obtains lock, 1 client stands by
    //  -(1+N)  1 client obtains lock, N clients stand by
    //  +(1+N)  Unlocked state, N clients stand by
    //  +2      Unlocked state, 1 client stands by
    //


void SimpleLock::Initialize()
{
    *m_Counter = 1;
}

bool SimpleLock::TryLock()
{
    ReverseIfPositiveUpdater updater;
    return m_Counter->AtomicUpdateConditional(updater);
}

void SimpleLock::Lock()
{
    if( ! TryLock() )
    {
        LockImpl();
    }
}

void SimpleLock::Unlock()
{
    ReverseUpdater updater;
    m_Counter->AtomicUpdateConditional(updater);

    if( updater.afterUpdate > 1 )
    {
        m_Counter.Signal(1);
    }
}

void SimpleLock::LockImpl()
{
    for(;;)
    {
        DecrementIfNegativeUpdater incrementNumWaiterIfLocked;

        if( m_Counter->AtomicUpdateConditional(incrementNumWaiterIfLocked) )
        {
            // Lock continuing, lock wait counter incremented
            break;
        }

        // Unlocked state

        if( TryLock() )
        {
            // Obtaining lock
            return;
        }
    }


    for(;;)
    {
        m_Counter.WaitIfLessThan(0);

        ReverseAndIncrementIfPositiveUpdater decrementNumWaiterAndLockIfUnlocked;

        if( m_Counter->AtomicUpdateConditional(decrementNumWaiterAndLockIfUnlocked) )
        {
            // Obtaining lock
            break;
        }
    }
}

}} // namespace nn::os

