/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Thread.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50238 $
 *---------------------------------------------------------------------------*/

#include <nn/assert.h>
#include <nn/Handle.h>
#include <nn/svc/svc_Stub.h>
#include <nn/dbg.h>
#include <nn/os.h>
#include <nn/os/os_PrivatePriority.h>
#include <nn/os/CTR/os_CppException.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/os/os_Private.h>
#include <rt_fp.h>

#include "os_Limits.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace fnd;
using namespace nn::svc;
using namespace nn::os;

namespace nn{ namespace os{

    namespace
    {
        ThreadLocalRegion* s_pTlr = NULL;

        struct StackBufferAdapter
        {
            uptr stackBottom;
            StackBufferAdapter(uptr stackBottom) : stackBottom(stackBottom) {}
            uptr GetStackBottom() const { return stackBottom; }
        };
    }

    namespace detail
    {
        s32 ConvertSvcToLibraryPriority(s32 svc)
        {
            if( svc >= SVC_USER_THREAD_PRIORITY_HIGHEST )
            {
                const s32 offset = svc - SVC_USER_THREAD_PRIORITY_HIGHEST;
                return offset;
            }
            else if( svc >= SVC_LIBRARY_THREAD_PRIORITY_HIGHEST )
            {
                const s32 offset = svc - SVC_LIBRARY_THREAD_PRIORITY_HIGHEST;
                return LIBRARY_THREAD_PRIORITY_BASE + offset;
            }
            else
            {
                return PRIVILEGED_THREAD_PRIORITY_BASE + svc;
            }
        }
        s32 ConvertLibraryToSvcPriority(s32 lib)
        {
            if ( (USER_THREAD_PRIORITY_HIGHEST <= lib)
                                              && (lib <= USER_THREAD_PRIORITY_LOWEST) )
            {
                return SVC_USER_THREAD_PRIORITY_HIGHEST + lib;
            }
            if ( (LIBRARY_THREAD_PRIORITY_HIGHEST <= lib)
                                                 && (lib <= LIBRARY_THREAD_PRIORITY_LOWEST) )
            {
                const s32 offset = lib - LIBRARY_THREAD_PRIORITY_HIGHEST;
                return SVC_LIBRARY_THREAD_PRIORITY_HIGHEST + offset;
            }
            if ( (PRIVILEGED_THREAD_PRIORITY_HIGHEST <= lib)
                                                    && (lib <= PRIVILEGED_THREAD_PRIORITY_LOWEST) )
            {
                const s32 offset = lib - PRIVILEGED_THREAD_PRIORITY_HIGHEST;
                return SVC_PRIVILEGED_THREAD_PRIORITY_HIGHEST + offset;
            }
            return -1;
        }
        void InitializeThreadEnvrionment()
        {
#ifdef NN_PROCESSOR_ARM_V6
    #if ! defined(NN_HARDWARE_CTR_LEGACY)
            ThreadLocalStorage::ClearAllSlots();
            CTR::SetupThreadCppExceptionEnvironment();
    #endif
            _fp_init();
#endif
        }
        void SaveThreadLocalRegionAddress()
        {
            NN_TASSERT_( s_pTlr == NULL );
            s_pTlr = GetThreadLocalRegion();
        }
        ThreadLocalRegion* GetMainThreadThreadLocalRegion()
        {
            return s_pTlr;
        }

    }




/* Please see man pages for details 
    
 */
struct Thread::FunctionInfo
{
    void (*destroy)(void* p);                    //
    void (*invoke)(ThreadFunc f, const void* p); //
    void (*f)(uptr);                             //
    void* p;                                     //
    void* pAutoStackBuffer;

    // Call handler.
    void Invoke()
    {
        invoke(f, p);
    };

    // End processing after handler call.
    void Destroy()
    {
        destroy(p);
    }
};



Thread Thread::s_MainThread = Thread::InitializeAsCurrentTag();
Thread::AutoStackManager*    Thread::s_pAutoStackManager = NULL;





// When initializing/ending a thread, denote whatever processes may be necessary here.
// TLS may be necessary for transferring data.

inline void Thread::OnThreadStart()
{
    nn::os::detail::InitializeThreadEnvrionment();
}

inline void Thread::OnThreadExit()
{
    // Nop
}

void Thread::NoParameterFunc(void (*f)())
{
    f();
}

#include <nn/hw/ARM/code32.h>
asm void Thread::CallDestructorAndExit(void* pStackBottom NN_IS_UNUSED_VAR)
{
    // r0: pStackBottom

    // Call stack destructor.
    // (s_pAutoStackManager->*f)(pStackBottom, false);

    mov     r2, #0                                  // Put false as the second argument
    mov     r1, r0                                  // Put pStackBottom as the first argument

    ldr     r0, =__cpp(&s_pAutoStackManager)        // Get the address of s_pAutoStackManager
    ldr     r0, [r0, #0]                            // Load s_pAutoStackManager

    ldr     r3, [r0, #0]                                                    // Load the address of vtable
    ldr     r3, [r3, #__vcall_offsetof_vfunc(AutoStackManager,Destruct)]    // Get virtual function address from vtable

    ldr     lr, =__cpp(nn::svc::ExitThread)         // Put return location in ExitThread
    bx      r3

    LTORG
}
#include <nn/hw/ARM/codereset.h>

// Thread process that runs from different context. Call handler.
void Thread::ThreadStart(uptr p)
{
    FunctionInfo& info = *reinterpret_cast<FunctionInfo*>(p);

    OnThreadStart();
    info.Invoke();
    info.Destroy();
    OnThreadExit();

    if( info.pAutoStackBuffer != NULL )
    {
        CallDestructorAndExit(info.pAutoStackBuffer);
    }

    nn::svc::ExitThread();

    NN_TASSERT_(0);
}

Result Thread::TryInitializeAndStartImpl(
        const TypeInfo& typeInfo,
        ThreadFunc      f,
        const void*     p,
        uptr            stackBottom,
        s32             priority,
        s32             coreNo,
        bool            isAutoStack )
{
    return TryInitializeAndStartImpl(
            typeInfo,
            f,
            p,
            stackBottom,
            priority,
            coreNo,
            (isAutoStack ? stackBottom: NULL) );
}

Result Thread::TryInitializeAndStartImpl(
        const TypeInfo& typeInfo,
        ThreadFunc      f,
        const void*     p,
        uptr            stackBottom,
        s32             priority,
        s32             coreNo,
        uptr            autoStackBuffer )
{
    // Thread::Start -> CreateThread --- Different context from here ---> ThreadStart -> Called in the order of f

    // The stack requires 8-byte alignment.
    // TODO: Strictly speaking, the files must be separated because this part is ARM-dependent.
    uptr stack = stackBottom;

    // Copy the parameter that is passed to the handler to the stack region.
    stack -= typeInfo.size;
    stack &= 0xfffffff8;
    void* obj = reinterpret_cast<void*>(stack);
    typeInfo.copy(p, obj);

    // Write information that is passed to the thread to the stack region.
    stack -= sizeof(FunctionInfo);
    stack &= 0xfffffff8;
    FunctionInfo& info = *reinterpret_cast<FunctionInfo*>(stack);
    info.destroy = typeInfo.destroy;
    info.invoke = typeInfo.invoke;
    info.f = f;
    info.p = obj;
    info.pAutoStackBuffer = reinterpret_cast<void*>(autoStackBuffer);

    Handle handle;
    NN_UTIL_RETURN_IF_FAILED(
        nn::svc::CreateThread(
            &handle,
            ThreadStart,
            stack,
            stack,
            os::detail::ConvertLibraryToSvcPriority(priority),
            coreNo) );

    this->SetHandle(handle);
    this->m_CanFinalize = false;
    this->m_UsingAutoStack = false;
    return ResultSuccess();
}


void Thread::SleepImpl(nn::fnd::TimeSpan span)
{
    if( span.GetNanoSeconds() >= SLEEP_SPIN_THRESHOLD )
    {
        nn::svc::SleepThread(span.GetNanoSeconds());
    }
    else
    {
        SpinWaitCpuCycles(Tick(span));
    }
}


#if NN_PLATFORM_HAS_MMU
uptr Thread::PreStartUsingAutoStack(size_t stackSize)
{
    NN_NULL_TASSERT_(s_pAutoStackManager);

    void* pStackBottom = s_pAutoStackManager->Construct(stackSize);
    NN_POINTER_TASSERT_(pStackBottom);
    NN_ALIGN_TASSERT_(pStackBottom, 8);

    return reinterpret_cast<uptr>(pStackBottom);
}
Result Thread::PostStartUsingAutoStack(Result result, uptr stackBottom)
{
    if (result.IsFailure())
    {
        s_pAutoStackManager->Destruct(reinterpret_cast<void*>(stackBottom), true);
        return result;
    }

    this->m_UsingAutoStack = true;
    return ResultSuccess();
}
Result Thread::TryInitializeAndStartImplUsingAutoStack(const TypeInfo& typeInfo, ThreadFunc f, const void* p, size_t stackSize, s32 priority, s32 coreNo)
{
    // Thread::Start -> CreateThread --- Different context from here ---> ThreadStart -> Called in the order of f

    const uptr stackBottom = PreStartUsingAutoStack(stackSize);
    Result result = TryInitializeAndStartImpl(typeInfo, f, p, stackBottom, priority, coreNo, true);
    return PostStartUsingAutoStack(result, stackBottom);
}
#endif  // if NN_PLATFORM_HAS_MMU

// For the main thread
Thread::Thread(const Thread::InitializeAsCurrentTag&)
{
    Handle handle;
    NN_OS_ERROR_IF_FAILED(nn::svc::DuplicateHandle(&handle, PSEUDO_HANDLE_CURRENT_THREAD));
    this->SetHandle(handle);
    this->m_CanFinalize = false;
    this->m_UsingAutoStack = false;
}

void Thread::SetAutoStackManager(AutoStackManager* pManager)
{
    s_pAutoStackManager = pManager;
}

void Thread::FinalizeImpl()
{
    if (!m_CanFinalize)
    {
        NN_TASSERTMSG_(m_CanFinalize, "Thread should be Joined or Detached before being Finalized.");
        this->WaitOne();
        this->m_CanFinalize = true;
    }
}

#if NN_PLATFORM_HAS_MMU
s32  Thread::GetCurrentCount()
{
    return os::detail::GetLimitCurrentCount(LIMITABLE_RESOURCE_MAX_THREAD);
}

s32  Thread::GetMaxCount()
{
    return os::detail::GetLimitMaxCount(LIMITABLE_RESOURCE_MAX_THREAD);
}
#endif  // if NN_PLATFORM_HAS_MMU

}} // namespace nn::os




#include <new>
using namespace nn::os;

extern "C" {

void nnosThreadInitializeAndStart(nnosThread* p, void (*f)(uptr), uptr param, uptr stackBottom, s32 priority, s32 coreNo)
{
    Thread* pThread = new (p) Thread();
    StackBufferAdapter stack(stackBottom);
    pThread->Start(f, param, stack, priority, coreNo);
}

bool nnosThreadTryInitializeAndStart(nnosThread* p, void (*f)(uptr), uptr param, uptr stackBottom, s32 priority, s32 coreNo)
{
    Thread* pThread = new (p) Thread();
    StackBufferAdapter stack(stackBottom);
    Result result = pThread->TryStart(f, param, stack, priority, coreNo);
    return result.IsSuccess();
}

void nnosThreadFinalize(nnosThread* p)
{
    Thread* pThread = reinterpret_cast<Thread*>(p);
    pThread->~Thread();
}

void nnosThreadJoin(nnosThread* p)
{
    Thread* pThread = reinterpret_cast<Thread*>(p);
    pThread->Join();
}

void nnosThreadSleep(s64 nanoSeconds)
{
    Thread::Sleep(TimeSpan::FromNanoSeconds(nanoSeconds));
}

void nnosThreadYield()
{
    Thread::Yield();
}

bit32 nnosThreadGetCurrentId(void)
{
    return Thread::GetCurrentId();
}

s32 nnosThreadGetPriority(const nnosThread* p)
{
    const Thread* pThread = reinterpret_cast<const Thread*>(p);
    return pThread->GetPriority();
}

s32 nnosThreadGetCurrentPriority()
{
    return Thread::GetCurrentPriority();
}

void nnosThreadChangePriority(nnosThread* p, s32 priority)
{
    Thread* pThread = reinterpret_cast<Thread*>(p);
    return pThread->ChangePriority(priority);
}

void nnosThreadChangeCurrentPriority(s32 priority)
{
    Thread::ChangeCurrentPriority(priority);
}

// Get/set the thread affinity
//void nnosThreadGetAffinityMask(const nnosThread* p, bit8* pAffinityMask, s32 numProcessor)
//{
//    const Thread* pThread = reinterpret_cast<const Thread*>(p);
//    pThread->GetAffinityMask(pAffinityMask, numProcessor);
//}
//
//void nnosThreadGetCurrentAffinityMask(bit8* pAffinityMask, s32 numProcessor)
//{
//    Thread::GetCurrentAffinityMask(pAffinityMask, numProcessor);
//}
//
//void nnosThreadGetDefaultAffinityMask(bit8* pAffinityMask, s32 numProcessor)
//{
//    Thread::GetDefaultAffinityMask(pAffinityMask, numProcessor);
//}
//
//void nnosThreadChangeAffinityMask(nnosThread* p, const bit8* pAffinityMask, s32 numProcessor)
//{
//    Thread* pThread = reinterpret_cast<Thread*>(p);
//    pThread->ChangeAffinityMask(pAffinityMask, numProcessor);
//}
//
//void nnosThreadChangeCurrentAffinityMask(const bit8* pAffinityMask, s32 numProcessor)
//{
//    Thread::ChangeCurrentAffinityMask(pAffinityMask, numProcessor);
//}
//
//void nnosThreadSetDefaultAffinityMask(const bit8* pAffinityMask, s32 numProcessor)
//{
//    Thread::SetDefaultAffinityMask(pAffinityMask, numProcessor);
//}

// Get/set IdealProcessor
s32 nnosThreadGetIdealProcessor(const nnosThread* p)
{
    const Thread* pThread = reinterpret_cast<const Thread*>(p);
    return pThread->GetIdealProcessor();
}

//s32 nnosThreadGetCurrentIdealProcessor()
//{
//    return Thread::GetCurrentIdealProcessor();
//}

s32 nnosThreadGetDefaultIdealProcessor()
{
    return Thread::GetDefaultIdealProcessor();
}

//void nnosThreadChangeIdealProcessor(nnosThread* p, s32 coreNo)
//{
//    Thread* pThread = reinterpret_cast<Thread*>(p);
//    pThread->ChangeIdealProcessor(coreNo);
//}
//
//void nnosThreadChangeCurrentIdealProcessor(s32 coreNo)
//{
//    Thread::ChangeCurrentIdealProcessor(coreNo);
//}
//
//void nnosThreadSetDefaultIdealProcessor(s32 coreNo)
//{
//    Thread::SetDefaultIdealProcessor(coreNo);
//}

s32 nnosThreadGetCurrentProcessorNumber()
{
    return Thread::GetCurrentProcessorNumber();
}

bit32 nnosThreadGetId(nnosThread* p)
{
    Thread* pThread = reinterpret_cast<Thread*>(p);
    return pThread->GetId();
}

bool nnosThreadIsAlive(nnosThread* p)
{
    Thread* pThread = reinterpret_cast<Thread*>(p);
    return pThread->IsAlive();
}

nnosThread* nnosThreadGetMainThread(void)
{
    return reinterpret_cast<nnosThread*>(&nn::os::Thread::GetMainThread());
}

}
