/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_NonRecursiveCriticalSection.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_NONRECURSIVECRITICALSECTION_H_
#define NN_OS_OS_NONRECURSIVECRITICALSECTION_H_

#include <nn/os/os_WaitableCounter.h>
#include <nn/assert.h>
#include <nn/WithInitialize.h>
#include <nn/util/detail/util_ScopedLockImpl.h>

#ifdef __cplusplus

// Untested

namespace nn { namespace os {

class NonRecursiveCriticalSection : private nn::util::NonCopyable<CriticalSection>
{
private:
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

public:

    static const bool CAN_LOCK_RECURSIVELY = false;

    // No initialization needed
    NonRecursiveCriticalSection() { *m_Counter = 1; }

    ~NonRecursiveCriticalSection() {}

    void Enter()
    {
        while (!TryEnter())
        {
            m_Counter.DecrementAndWaitIfLessThan(0);
        }
    }

    bool TryEnter()
    {
        ReverseIfPositiveUpdater updater;
        return m_Counter->AtomicUpdateConditional(updater);
    }

    void Leave()
    {
        NN_TASSERTMSG_( *m_Counter < 0 , "CriticalSection is not entered.");
        
        // Unlock by setting the counter's sign to positive.
        ReverseUpdater updater;
        m_Counter->AtomicUpdateConditional(updater);

        // Wake the waiting thread that has the highest priority.
        if( updater.afterUpdate > 1 )
        {
            m_Counter.Signal(1);
        }
    }

    class ScopedLock;

private:
    nn::os::WaitableCounter m_Counter;
};

NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(NonRecursiveCriticalSection, Enter(), Leave());

}}

#endif // __cplusplus

#endif
