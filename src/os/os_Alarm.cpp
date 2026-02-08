/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Alarm.cpp

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
#include <nn/os/os_Alarm.h>
#include <nn/svc/svc_Stub.h>
#include <nn/os/os_ThreadPool.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/util/util_StaticAssert.h>
#include <new>

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::fnd;
using namespace nn::svc;
using namespace nn::os;
using namespace nn::util;

namespace nn{ namespace os{

namespace {

#if NN_PLATFORM_HAS_MMU
    const size_t NUM_ALARM_THREAD = 2; //
    const size_t STACK_SIZE = 4096;    //
    StackBuffer<STACK_SIZE> s_Stacks[NUM_ALARM_THREAD];
    MemoryBlock threadPoolMemoryBlock; //
#endif  // if NN_PLATFORM_HAS_MMU
    ThreadPool* alarmThreadPool = 0;

}

#if NN_PLATFORM_HAS_MMU
// Initializes the alarm system.
// This function may be deleted in the future.
void InitializeAlarmSystem(s32 priority)
{
    InitializeAlarmSystem(priority, 0);
}
void InitializeAlarmSystem(s32 workerPriority, s32 waitPriority)
{
    if (alarmThreadPool)
    {
        return;
    }
    // Allocates the alarm thread stack.
    uptr stacks[NUM_ALARM_THREAD];
    for (s32 i = 0; i < NUM_ALARM_THREAD; ++i)
    {
        stacks[i] = s_Stacks[i].GetStackBottom();
    }
    threadPoolMemoryBlock.Initialize(sizeof(nn::os::ThreadPool));
    NN_STATIC_ASSERT(sizeof(ThreadPool) % 8 == 0);
    NN_TASSERT_(sizeof(ThreadPool) + ThreadPool::GetWorkBufferSize(100, NUM_ALARM_THREAD) <= threadPoolMemoryBlock.GetSize());
    void* threadPoolStorage = reinterpret_cast<void*>(threadPoolMemoryBlock.GetAddress());
    void* buffer = reinterpret_cast<void*>(threadPoolMemoryBlock.GetAddress() + sizeof(ThreadPool));
    alarmThreadPool = new (threadPoolStorage) ThreadPool(buffer, 100, NUM_ALARM_THREAD, stacks, workerPriority, waitPriority);
}
#endif  // if NN_PLATFORM_HAS_MMU

#if NN_PLATFORM_HAS_MMU
size_t GetRequiredMemorySizeForAlarmSystem(void)
{
    return STACK_SIZE * NUM_ALARM_THREAD + (sizeof(nn::os::ThreadPool) / NN_OS_MEMORY_PAGE_SIZE + 1) * NN_OS_MEMORY_PAGE_SIZE;
}
#endif  // if NN_PLATFORM_HAS_MMU

Result Alarm::TryInitialize()
{
    if ( alarmThreadPool == 0 )
    {
        return ResultNotInitialized();
    }
    Result result = m_Timer.TryInitialize(false);
    m_Invoker = alarmThreadPool;
    return result;
}

void Alarm::Initialize()
{
    NN_OS_ERROR_IF_FAILED(TryInitialize());
}

void Alarm::Finalize()
{
    NN_TASSERT_(CanSet());
    if ( !CanSet() )
    {
        NN_OS_ERROR_IF_FAILED(ResultBusy());
    }
    m_Timer.Finalize();
}

Alarm::~Alarm() { this->Finalize(); }

// Sets a one-shot alarm.
void Alarm::SetOneShot(TimeSpan time, AlarmHandler handler, void* p)
{
    NN_TASSERT_(CanSet());
    if ( CanSet() )
    {
        m_Handler = handler;
        m_Parameter = p;
        m_Flags = Flags::Create(false, true, true);
        m_Timer.StartOneShot(time);
        m_Invoker->AddWaitTask(this);
    }
}

// Sets a cyclic alarm.
void Alarm::SetPeriodic(TimeSpan initial, TimeSpan interval, AlarmHandler handler, void* p)
{
    NN_TASSERT_(CanSet());
    if ( CanSet() )
    {
        m_Handler = handler;
        m_Parameter = p;
        m_Flags = Flags::Create(false, false, true);
        m_Timer.StartPeriodic(initial, interval);
        m_Invoker->AddWaitTask(this);
    }
}

// Structure to set the alarm state to cancel
struct Alarm::CancelFunc
{
    // Cancels the alarm.
    // Returns true if cancel succeeds.
    bool operator()(Flags& flags)
    {
        if (flags.isSet)
        {
            // Sets the cancel flag.
            flags = Flags::Create(true, flags.isOneShot, true);
            return true;
        }
        else
        {
            // Alarm is not set.
            return false;
        }
    }
};

// Cancels set alarms.
void Alarm::Cancel()
{
    CancelFunc f;
    if (m_Flags.AtomicUpdateConditional(f))
    {
        // If cancelled, calls handler without waiting for timer.
        m_Timer.Signal();
    }
}

// Structure to set the alarm state to the state after the handler executes
struct Alarm::InvokeFunc
{
    // Sets whether the alarm was canceled
    // Returns false if the alarm continues after the handler is called; true if it does not.
    bool operator()(Flags& flags)
    {
        this->cancelled = flags.cancelled;
        if (flags.cancelled || flags.isOneShot)
        {
            // Flag reflects that the alarm has finished.
            flags = Flags::Create(flags.cancelled, flags.isOneShot, false);

			// Returns true because the alarm finished.
            return true;
        }
        else
        {
			// Returns false because the alarm continues.
            return false;
        }
    }
    
    bool cancelled;  // Whether the alarm was cancelled
};

// Process executed by the alarm.
void Alarm::Invoke()
{
    // TODO: Verification of synchronization related area here
    NN_TASSERT_(m_Flags.Read().isSet);
    NN_TASSERT_(m_Handler);
    AlarmHandler handler = m_Handler;
    void* parameter = m_Parameter;
    InvokeFunc f;
    if (m_Flags.AtomicUpdateConditional(f))
    {
        handler(parameter, f.cancelled);
    }
    else
    {
        handler(parameter, f.cancelled);

        // Register task to call alarm again.
        m_Invoker->AddWaitTask(this);
    }
}

// Gets synchronization object to issue signal.
nn::os::WaitObject* Alarm::GetWaitObject()
{
    return &m_Timer;
}

}} // namespace nn::os

#include <new>

using namespace nn::os;

extern "C" {

void nnosInitializeAlarmSystem()
{
    nn::os::InitializeAlarmSystem();
}

void nnosAlarmInitialize(nnosAlarm* p)
{
    Alarm* this_ = new (p) Alarm;
    this_->Initialize();
}

void nnosAlarmFinalize(nnosAlarm* p)
{
    Alarm* pAlarm = reinterpret_cast<Alarm*>(p);
    pAlarm->~Alarm();
}

void nnosAlarmSetOneShot(nnosAlarm* p, s64 time, nnosAlarmHandler handler, void* param)
{
    Alarm* pAlarm = reinterpret_cast<Alarm*>(p);
    pAlarm->SetOneShot(nn::fnd::TimeSpan::FromNanoSeconds(time), handler, param);
}

void nnosAlarmSetPeriodic(nnosAlarm* p, s64 initial, s64 interval, nnosAlarmHandler handler, void* param)
{
    Alarm* pAlarm = reinterpret_cast<Alarm*>(p);
    pAlarm->SetPeriodic(nn::fnd::TimeSpan::FromNanoSeconds(initial), nn::fnd::TimeSpan::FromNanoSeconds(interval), handler, param);
}

void nnosAlarmCancel(nnosAlarm* p)
{
    Alarm* pAlarm = reinterpret_cast<Alarm*>(p);
    pAlarm->Cancel();
}

bool nnosAlarmCanSet(const nnosAlarm* p)
{
    const Alarm* pAlarm = reinterpret_cast<const Alarm*>(p);
    return pAlarm->CanSet();
}

}

