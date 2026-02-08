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

#include <calloca>
#include <nn/Handle.h>
#include <nn/assert.h>
#include <nn/dbg.h>
#include <nn/math.h>
#include <nn/os.h>
#include <nn/os/CTR/os_CppException.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/os/os_Private.h>
#include <nn/svc/svc_Stub.h>
#include <rt_fp.h>

#include "os_Limits.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace fnd;
using namespace nn::svc;
using namespace nn::os;

#define ASSERT_INITIALIZE() \
        NN_TASSERTMSG_(GetStaticStates().mainThread.IsValid(), \
            "Please call ManagedThread::InitializeAndAttachMainThread before use of ManagedThread.")

namespace nn{ namespace os{

    ThreadLocalStorage          ManagedThread::ms_ThreadStorage = ThreadLocalStorage::WithoutInitialize();
    ThreadLocalStorage          ManagedThread::ms_IdStorage     = ThreadLocalStorage::WithoutInitialize();



    namespace
    {
        typedef fnd::IntrusiveLinkedList<ManagedThread> ThreadList;
        typedef CriticalSection                         LockType;
        typedef CriticalSection::ScopedLock             ScopedLock;

        struct StaticStates
        {
            ManagedThread   mainThread;
            ThreadList      threadList;
            LockType        lock;
            bool            isInitialized;
            NN_PADDING3;
        };

        bit8 s_StaticStatesBuffer[sizeof(StaticStates)] NN_ATTRIBUTE_ALIGN(8);

        inline StaticStates& GetStaticStates()
        {
            return *reinterpret_cast<StaticStates*>(s_StaticStatesBuffer);
        }

        struct StackBufferAdapter
        {
            uptr stackBottom;
            StackBufferAdapter(uptr stackBottom) : stackBottom(stackBottom) {}
            uptr GetStackBottom() const { return stackBottom; }
        };

        void* AllocateOnStack(uptr* pStackBottom, size_t size)
        {
            *pStackBottom -= size;
            *pStackBottom = math::RoundDown(*pStackBottom, 8);
            return reinterpret_cast<void*>(*pStackBottom);
        }

#if NN_PLATFORM_HAS_MMU
        size_t GetMainThreadStackSize()
        {
            MemoryInfo  mi;
            PageInfo pi;

            Result result = svc::QueryMemory(&mi, &pi, NN_OS_ADDR_STACK_END - 1);
            NN_PANIC_IF_FAILED(result);

            return mi.size;
        }
#endif
    }

    
    /* ------------------------------------------------------------------------
            Thread Starter
       ------------------------------------------------------------------------ */

    struct ManagedThread::StartParam
    {
        void (*destroy)(void* p);                    //
        void (*invoke)(ThreadFunc f, const void* p); //
        void (*f)(uptr);                             //
        void* p;                                     //
        ManagedThread*  pObj;
        LightEvent* pStartEvent;
        
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

    void ManagedThread::NoParameterFunc(void (*f)())
    {
        f();
    }

    // Thread process that runs from different context. Call handler.
    void ManagedThread::ThreadStart(StartParam* p)
    {
        StartParam& param = *p;

        {
            SetCurrentThread(param.pObj);
            SetCurrentThreadId(Thread::GetCurrentId());
            param.pStartEvent->Wait();
        }
        {
            param.Invoke();
            param.Destroy();
        }
    }



    /* ------------------------------------------------------------------------
            Thread creation
       ------------------------------------------------------------------------ */

    uptr ManagedThread::SetupStackAndParam(StartParam* pStartParam, const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, size_t stackSize)
    {
        // The stack requires 8-byte alignment.
        // TODO: Strictly speaking, the files must be separated because this part is ARM-dependent.
        uptr stack = stackBottom;

        void* pLightEventBuffer = AllocateOnStack(&stack, sizeof(LightEvent));
        void* pCopiedParam      = AllocateOnStack(&stack, typeInfo.size);

        LightEvent* pStartEvent = new(pLightEventBuffer) LightEvent(false);

        // Copy the parameter that is passed to the handler to the stack region.
        typeInfo.copy(p, pCopiedParam);

        // Write information that is passed to the thread to the stack region.
        pStartParam->destroy      = typeInfo.destroy;
        pStartParam->invoke       = typeInfo.invoke;
        pStartParam->f            = f;
        pStartParam->p            = pCopiedParam;
        pStartParam->pObj         = this;
        pStartParam->pStartEvent  = pStartEvent;

        m_StackBottom    = stack;
        m_StackBufferEnd = stackBottom;
        m_StackSize      = stackSize;
        m_pName          = NULL;
        m_pStartEvent    = pStartEvent;

        return stack;
    }

    Result ManagedThread::TryInitializeImpl(const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, size_t stackSize, s32 priority, s32 coreNo)
    {
        return TryInitializeImpl(
                typeInfo,
                f,
                p,
                stackBottom,
                stackSize,
                priority,
                coreNo,
                false );
    }

    Result ManagedThread::TryInitializeImpl(const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, size_t stackSize, s32 priority, s32 coreNo, bool useAutoStack)
    {
        ASSERT_INITIALIZE();

        StartParam param;
        const uptr newStackBottom = SetupStackAndParam(&param, typeInfo, f, p, stackBottom, stackSize);

        StackBufferAdapter sba(newStackBottom);
        Result result = Thread::ProtectedAccessor::TryStart<StartParam, StackBufferAdapter>(
                            &m_Thread,
                            ThreadStart,
                            param,
                            sba,
                            priority,
                            coreNo,
                            (useAutoStack ? stackBottom: NULL)  );


        if( result.IsSuccess() )
        {
            m_Id = m_Thread.GetId();
            Register(this);
        }
        else
        {
            if (result.GetSummary() != Result::SUMMARY_OUT_OF_RESOURCE)
            {
                NN_OS_ERROR_IF_FAILED(result);
            }
        }

        return result;
    }

    Result ManagedThread::TryInitializeImplUsingAutoStack(const TypeInfo& typeInfo, ThreadFunc f, const void* p, size_t stackSize, s32 priority, s32 coreNo)
    {
        ASSERT_INITIALIZE();

        const uptr stackBottom = Thread::ProtectedAccessor::PreStartUsingAutoStack(&m_Thread, stackSize);
        Result result = TryInitializeImpl(typeInfo, f, p, stackBottom, stackSize, priority, coreNo, true);
        return Thread::ProtectedAccessor::PostStartUsingAutoStack(&m_Thread, result, stackBottom);
    }




    /* ------------------------------------------------------------------------
            Destroy Thread
       ------------------------------------------------------------------------ */



    /* ------------------------------------------------------------------------
            .
       ------------------------------------------------------------------------ */

    void ManagedThread::Finalize()
    {
        if( IsChained() )
        {
            m_Thread.Finalize();
            Unregister(this);
        }
    }

    void ManagedThread::Join()
    {
        m_Thread.Join();
    }

    void ManagedThread::Detach()
    {
        m_Thread.Detach();
    }



    /* ------------------------------------------------------------------------
            .
       ------------------------------------------------------------------------ */

    void ManagedThread::Start()
    {
        NN_TASSERTMSG_(m_pStartEvent != NULL,
            "ManagedThread is not initialized or this is the main thread.");
        m_pStartEvent->Signal();
    }

    uptr ManagedThread::GetStackBufferBegin() const
    {
        return m_StackBufferEnd - m_StackSize;
    }

    uptr ManagedThread::GetStackBottom() const
    {
        return m_StackBottom;
    }

    uptr ManagedThread::GetStackBufferEnd() const
    {
        return m_StackBufferEnd;
    }

    size_t ManagedThread::GetStackSize() const
    {
        return GetStackBottom() - GetStackBufferBegin();
    }

    size_t ManagedThread::GetStackBufferSize() const
    {
        return m_StackSize;
    }

    const char* ManagedThread::GetName() const
    {
        return m_pName;
    }

    void ManagedThread::SetName(const char8* pName)
    {
        m_pName = pName;
    }

    void ManagedThread::SetCurrentThread(ManagedThread* p)
    {
        ms_ThreadStorage.SetValue(reinterpret_cast<uptr>(p));
    }

    void ManagedThread::SetCurrentThreadId(bit32 id)
    {
        ms_IdStorage.SetValue(id);
    }

    ManagedThread* ManagedThread::GetCurrentThread()
    {
        return reinterpret_cast<ManagedThread*>(ms_ThreadStorage.GetValue());
    }

    ManagedThread* ManagedThread::FindByStackAddress(uptr address)
    {
        class Finder : public EnumerateCallback
        {
        private:
            uptr            m_Address;
            ManagedThread*  m_pFound;

        public:
            Finder(uptr address) : m_Address(address), m_pFound(NULL) {}

            virtual bool operator()(ManagedThread* p)
            {
                if( (p->GetStackBufferBegin() <= m_Address) && (m_Address <= p->GetStackBufferEnd()) )
                {
                    m_pFound = p;
                    return false;
                }
                return true;
            }
            ManagedThread* GetFound() const { return m_pFound; }

        } finder(address);

        Enumerate(&finder);

        return finder.GetFound();
    }

    ManagedThread* ManagedThread::FindById(bit32 id)
    {
        class Finder : public EnumerateCallback
        {
        private:
            bit32           m_Id;
            ManagedThread*  m_pFound;

        public:
            Finder(bit32 id) : m_Id(id), m_pFound(NULL) {}

            virtual bool operator()(ManagedThread* p)
            {
                if( p->GetId() == m_Id )
                {
                    m_pFound = p;
                    return false;
                }
                return true;
            }
            ManagedThread* GetFound() const { return m_pFound; }

        } finder(id);

        Enumerate(&finder);

        return finder.GetFound();
    }

    void ManagedThread::Enumerate(EnumerateCallback* p)
    {
        StaticStates& ss = GetStaticStates();
        ScopedLock lock(ss.lock);

        ManagedThread* pThread = ss.threadList.GetFront();
        while( pThread != NULL )
        {
            (*p)(pThread);
            pThread = ss.threadList.GetNext(pThread);
        }
    }

    void ManagedThread::Register(ManagedThread* p)
    {
        StaticStates& ss = GetStaticStates();
        ScopedLock lock(ss.lock);
        ss.threadList.PushBack(p);
    }

    void ManagedThread::Unregister(ManagedThread* p)
    {
        StaticStates& ss = GetStaticStates();
        ScopedLock lock(ss.lock);
        ss.threadList.Erase(p);
    }

    s32 ManagedThread::GetCurrentManagedCount()
    {
        class Counter : public EnumerateCallback
        {
        private:
            s32 m_Count;

        public:
            Counter() : m_Count(0) {}

            virtual bool operator()(ManagedThread* p)
            {
                NN_UNUSED_VAR(p);
                m_Count++;
                return true;
            }
            s32 GetCount() const { return m_Count; }

        } counter;

        Enumerate(&counter);

        return counter.GetCount();
    }

#if NN_PLATFORM_HAS_MMU
    void ManagedThread::InitializeAsMainThread()
    {
        Thread::ProtectedAccessor::InitializeAsMainThread(&m_Thread);
        m_StackBottom    = NN_OS_ADDR_STACK_END;
        m_StackBufferEnd = NN_OS_ADDR_STACK_END;
        m_StackSize      = GetMainThreadStackSize();
        m_pName          = "MainThread";
        m_pStartEvent    = NULL;
        m_Id             = m_Thread.GetId();

        ms_ThreadStorage.SetValueTo(
            os::detail::GetMainThreadThreadLocalRegion(), reinterpret_cast<uptr>(this));
        ms_IdStorage.SetValueTo(
            os::detail::GetMainThreadThreadLocalRegion(), m_Id);

        Register(this);
    }

    void ManagedThread::InitializeEnvironment()
    {
        new(s_StaticStatesBuffer) StaticStates();
        StaticStates& ss = GetStaticStates();

        ms_ThreadStorage.Initialize();
        ms_IdStorage.Initialize();

        ss.lock.Initialize();
        ss.mainThread.InitializeAsMainThread();
        ss.isInitialized = true;
    }

    bool ManagedThread::IsEnabled()
    {
        return GetStaticStates().isInitialized;
    }
#endif










}} // namespace nn::os


