/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Thread.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50238 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_THREAD_H_
#define NN_OS_OS_THREAD_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_Tick.h>
#include <nn/os/os_SpinWaitSelect.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/os/os_AutoStackManager.h>
#include <nn/os/os_SvcTypes.autogen.h>

#include <nn/util/util_Result.h>
#include <nn/util/util_TypeTraits.h>

/*
    
    
*/
#define NN_OS_CORE_NO_ALL                           (-1)

/*
    
    
*/
#define NN_OS_CORE_NO_USE_PROCESS_VALUE             (-2)

#define NN_OS_THREAD_PRIORITY_RANGE_SIZE            32

/*
    
    
*/
#define NN_OS_LOWEST_THREAD_PRIORITY                (NN_OS_THREAD_PRIORITY_RANGE_SIZE - 1)

/*
    
    
*/
#define NN_OS_HIGHEST_THREAD_PRIORITY               0

/*
    
    
*/
#define NN_OS_DEFAULT_THREAD_PRIORITY               16



#ifdef __cplusplus

#include <nn/os/os_SvcTypes.autogen.h>

namespace nn{ namespace os{

namespace detail {
    s32 ConvertSvcToLibraryPriority(s32 svc);
    s32 ConvertLibraryToSvcPriority(s32 lib);
    void InitializeThreadEnvrionment();
}

/*
    
*/
const s32 LOWEST_THREAD_PRIORITY = NN_OS_LOWEST_THREAD_PRIORITY;

/*
    
*/
const s32 HIGHEST_THREAD_PRIORITY = NN_OS_HIGHEST_THREAD_PRIORITY;

/*
    
*/
const s32 DEFAULT_THREAD_PRIORITY = NN_OS_DEFAULT_THREAD_PRIORITY;

/*
    
*/
const s32 CORE_NO_ALL = NN_OS_CORE_NO_ALL;

/*
    
*/
const s32 CORE_NO_USE_PROCESS_VALUE = NN_OS_CORE_NO_USE_PROCESS_VALUE;

const s32 THREAD_PRIORITY_RANGE_SIZE = NN_OS_THREAD_PRIORITY_RANGE_SIZE;

/* 
    
*/

class ManagedThread;

/* Please see man pages for details 
    

    

    
    
    

    
    

    
    
    
    
    

    

    
    
    

    
    
    

    
    

    
    
    

    
    
*/

class Thread : public WaitObject
{
public:
    typedef nn::os::AutoStackManager AutoStackManager;

public:

//
//

    /* Please see man pages for details 
    

                  
    */
    Thread() : m_CanFinalize(true) {}

    /* Please see man pages for details 
    

                  
                  
    */
    ~Thread();

//

//
//

    /* Please see man pages for details 
    

                  
                  

    
    
    
    

    

    

    
    */
    template <typename Stack>
    void Start(void (*f)(), Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 
    

                  
                  

    
    
    
    
    

    
    
    

    

    
    */
    template <typename T, typename U, typename Stack>
    void Start(void (*f)(T), U param, Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);
    template <typename T, typename Stack>
    void Start(void (*f)(T*), T& param, Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);
    template <typename T, typename Stack>
    void Start(void (*f)(const T&), const T& param, Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 
    

                  
                  

    

    
    
    
    

    

    

    
    */
    template <typename Stack>
    nn::Result TryStart(void (*f)(), Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 
    

                  
                  

    

    
    
    
    
    

    
    
    

    

    
    */
    template <typename T, typename U, typename Stack>
    nn::Result TryStart(void (*f)(T), U param, Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);
    template <typename T, typename Stack>
    nn::Result TryStart(void (*f)(T*), T& param, Stack& stack, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 

    

                  
                  

    
    
    
    

    

    
    */
    void StartUsingAutoStack(void (*f)(), size_t stackSize, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 
    

                  
                  

    
    
    
    
    

    
    

    

    
    */
    template <typename T, typename U>
    void StartUsingAutoStack(void (*f)(T), U param, size_t stackSize, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 

    

    

                  
                  

    

    
    
    
    

    
    */
    nn::Result TryStartUsingAutoStack(void (*f)(), size_t stackSize, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);
    nn::Result TryStartUsingAutoStack(ThreadFunc f, size_t stackSize, const void* pParam, size_t paramSize, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

    /* Please see man pages for details 

    

    

                  
                  

    

    
    
    
    
    

    
    

    

    */
    template <typename T, typename U>
    nn::Result TryStartUsingAutoStack(void (*f)(T), U param, size_t stackSize, s32 priority = DEFAULT_THREAD_PRIORITY, s32 coreNo = CORE_NO_USE_PROCESS_VALUE);

//

//
//

    /* Please see man pages for details 
    

                  
                  

    
    */
    void Finalize();

    /* Please see man pages for details 
    

                  
                  
                  
                  

    
    */
    void Join();

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void Detach();

    /* Please see man pages for details 
    

    
    */
    bool IsAlive() const;

//


//
//

    /* Please see man pages for details 
    

    

    
    */
    static void Sleep(nn::fnd::TimeSpan span);

    /* Please see man pages for details 
    

                  
                  
                  
                  
                  
                  

                  
                  
                  

    
    */
    static void Yield();

//

//
//

    // Get/set the thread status
    // Non-static member functions act on the instance.
    // Static member functions that include "Current" in their name act on the current thread.
    // static member functions with "Default" included in their names act on the default value of the attributes of the created thread when coreNo = CORE_NO_USE_PROCESS_VALUE in CreateThread.
    // 

    // Get the context
    //   TODO: Not implemented.
    // void GetContext(nn::os::ThreadContext* pContext) const;
    // static void GetCurrentContext(nn::os::ThreadContext* pContext);

    /* Please see man pages for details 
    

    
    */
    bit32 GetId() const;

    /* Please see man pages for details 
    

    
    */
    static bit32 GetCurrentId();

    /* Please see man pages for details 
    

    
    */
    s32 GetPriority() const;

    /* Please see man pages for details 
    

    
    */
    static s32 GetCurrentPriority();

    /* Please see man pages for details 
    

    

    
    */
    void ChangePriority(s32 priority);

    /* Please see man pages for details 
    

    

    
    */
    static void ChangeCurrentPriority(s32 priority);

    // Get/set the thread affinity

    /* 
    

    
    

    
    */
    //void GetAffinityMask(bit8* pAffinityMask, s32 numProcessor) const;

    /* 
    

    
    

    
    */
    //static void GetCurrentAffinityMask(bit8* pAffinityMask, s32 numProcessor);

    /* 
    

    
    

    
    */
    //static void GetDefaultAffinityMask(bit8* pAffinityMask, s32 numProcessor);

    /* 
    

    
    

    
    */
    //void ChangeAffinityMask(const bit8* pAffinityMask, s32 numProcessor);

    /* 
    

    
    

    
    */
    //static void ChangeCurrentAffinityMask(const bit8* pAffinityMask, s32 numProcessor);

    /* 
    

    
    

    
    */
    //static void SetDefaultAffinityMask(const bit8* pAffinityMask, s32 numProcessor);

    // Get/set IdealProcessor
    /* Please see man pages for details 
    

    
    */
    s32 GetIdealProcessor() const;

    /* 
    

    
    */
    //static s32 GetCurrentIdealProcessor();

    /* 
    

    
    */
    static s32 GetDefaultIdealProcessor();

    /* 
    

    

    
    */
    //void ChangeIdealProcessor(s32 coreNo);

    /* 
    

    

    
    */
    //static void ChangeCurrentIdealProcessor(s32 coreNo);

    /* 
    

    

    
    */
    //static void SetDefaultIdealProcessor(s32 coreNo);

    /* Please see man pages for details 
    

    
    */
    static s32 GetCurrentProcessorNumber();

//

//
//

    /* Please see man pages for details 
    
    
    */
    static Thread& GetMainThread() { return s_MainThread; }

    /* Please see man pages for details 
    

        
        
        

        
        
        

    
    */
    static void SetAutoStackManager(AutoStackManager* pManager);

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    static s32  GetCurrentCount();

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    static s32  GetMaxCount();

//

private:
    struct InitializeAsCurrentTag {};
    struct TypeInfo;
    struct FunctionInfo;

private:
    bool        m_CanFinalize;
    bool        m_UsingAutoStack;
    NN_PADDING2;

    static Thread               s_MainThread;
    static AutoStackManager*    s_pAutoStackManager;

private:
    Thread(const InitializeAsCurrentTag&);
    void FinalizeImpl();

    Result TryInitializeAndStartImpl(const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, s32 priority, s32 coreNo, bool isAutoStack);
    Result TryInitializeAndStartImpl(const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, s32 priority, s32 coreNo, uptr autoStackBuffer);
    Result TryInitializeAndStartImplUsingAutoStack(const TypeInfo& typeInfo, ThreadFunc f, const void* p, size_t stackSize, s32 priority, s32 coreNo);
    uptr   PreStartUsingAutoStack(size_t stackSize);
    Result PostStartUsingAutoStack(Result result, uptr stackBottom);

private:
    static void OnThreadStart();
    static void OnThreadExit();

    static void ThreadStart(uptr);
    static void ThreadStartUsingAutoStack(uptr);
    static void NoParameterFunc(void (*)());
    static void SleepImpl(nn::fnd::TimeSpan span);

    static void CallDestructorAndExit(void* pStackBottom);

public:
    class ProtectedAccessor
    {
    private:
        friend class ::nn::os::ManagedThread;

        static uptr PreStartUsingAutoStack(Thread* pThread, size_t stackSize)
        {
            return pThread->PreStartUsingAutoStack(stackSize);
        }
        static Result PostStartUsingAutoStack(Thread* pThread, Result result, uptr stackBottom)
        {
            return pThread->PostStartUsingAutoStack(result, stackBottom);
        }
        template <typename T, typename Stack>
        static Result TryStart(Thread* pThread, void (*f)(T*), T& param, Stack& stack, s32 priority, s32 coreNo, uptr autoStackBuffer);
        static void InitializeAsMainThread(void* p);
    };
};

/* Please see man pages for details 
    

    

           
           

    
*/
template <size_t Size>
class StackBuffer
{
private:
    typename nn::util::aligned_storage<Size, 8>::type m_Buffer;
public:

    /* Please see man pages for details 
    

    
    */
    uptr GetStackBottom() const { return reinterpret_cast<uptr>(this + 1); }

    /* Please see man pages for details 
    

    
    */
    size_t GetStackSize() const { return Size; }

    void MarkCanary(bit32 value = 0xDEADBEEF) { reinterpret_cast<bit32*>(this)[0] = value; }
    bool CheckCanary(bit32 value = 0xDEADBEEF) const { return reinterpret_cast<const bit32*>(this)[0] == value; }
};

}}

// In-line implementation

#ifdef NN_SYSTEM_PROCESS

#include <new>

#include <nn/dbg/dbg_Logger.h>

namespace nn { namespace os {

struct Thread::TypeInfo
{
private:

    template <typename T, typename U>
    static void Copy(const void* src, void* dst)
    {
        new (dst) T(*reinterpret_cast<const U*>(src));
    }
    template <typename T>
    static void Copy(const void* src, void* dst)
    {
        new (dst) T(*reinterpret_cast<const T*>(src));
    }

    template <typename T>
    static void Destroy(void* p)
    {
        reinterpret_cast<T*>(p)->~T();
    }

    template <typename T>
    static void Invoke(ThreadFunc f, const void* p)
    {
        (*reinterpret_cast<void (*)(T)>(f))(*reinterpret_cast<const T*>(p));
    }
    template <typename T>
    static void Invoke2(ThreadFunc f, const void* p)
    {
        (*reinterpret_cast<void (*)(const T*)>(f))(reinterpret_cast<const T*>(p));
    }

public:

    size_t size;
    void (*copy)(const void* src, void* dst);
    void (*destroy)(void* p);
    void (*invoke)(ThreadFunc f, const void* p);

    template <typename T, typename U>
    void SetData(typename nn::util::enable_if<nn::util::is_convertible<U, T>::value>::type* = 0)
    {
        this->size = sizeof(T);
        this->copy = &(Copy<T, U>);
        this->destroy = &(Destroy<T>);
        this->invoke = &(Invoke<T>);
    }
    template <typename T>
    void SetData()
    {
        this->size = sizeof(T);
        this->copy = &(Copy<T>);
        this->destroy = &(Destroy<T>);
        this->invoke = &(Invoke2<T>);
    }
};


template <typename T, typename U, typename Stack>
inline void Thread::Start(void (*f)(T), U param, Stack& stack, s32 priority, s32 coreNo)
{
    TypeInfo info;
    info.SetData<T, U>();
    NN_OS_ERROR_IF_FAILED(TryInitializeAndStartImpl(info, reinterpret_cast<ThreadFunc>(f), &param, stack.GetStackBottom(), priority, coreNo, false));
}

template <typename T, typename Stack>
inline void Thread::Start(void (*f)(T*), T& param, Stack& stack, s32 priority, s32 coreNo)
{
    TypeInfo info;
    info.SetData<T>();
    NN_OS_ERROR_IF_FAILED(TryInitializeAndStartImpl(info, reinterpret_cast<ThreadFunc>(f), &param, stack.GetStackBottom(), priority, coreNo, false));
}

//template <typename T, typename Stack>
//inline void Thread::Start(void (*f)(const T&), const T& param, Stack& stack, s32 priority, s32 coreNo)
//{
//    TypeInfo info;
//    info.SetData<T>();
//    NN_OS_ERROR_IF_FAILED(TryInitializeAndStartImpl(info, reinterpret_cast<ThreadFunc>(f), &param, stack.GetStackBottom(), priority, coreNo, false));
//}

template <typename Stack>
inline void Thread::Start(void (*f)(), Stack& stack, s32 priority, s32 coreNo)
{
    Start(NoParameterFunc, f, stack, priority, coreNo);
}

template <typename T, typename Stack>
inline nn::Result Thread::ProtectedAccessor::TryStart(Thread* pThread, void (*f)(T*), T& param, Stack& stack, s32 priority, s32 coreNo, uptr autoStackBuffer)
{
    TypeInfo info;
    info.SetData<T>();
    Result result = pThread->TryInitializeAndStartImpl(info, reinterpret_cast<ThreadFunc>(f), &param, stack.GetStackBottom(), priority, coreNo, autoStackBuffer);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

template <typename T, typename U, typename Stack>
inline nn::Result Thread::TryStart(void (*f)(T), U param, Stack& stack, s32 priority, s32 coreNo)
{
    TypeInfo info;
    info.SetData<T, U>();
    Result result = TryInitializeAndStartImpl(info, reinterpret_cast<ThreadFunc>(f), &param, stack.GetStackBottom(), priority, coreNo, false);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

template <typename Stack>
inline nn::Result Thread::TryStart(void (*f)(), Stack& stack, s32 priority, s32 coreNo)
{
    return TryStart(NoParameterFunc, f, stack, priority, coreNo);
}

template <typename T, typename Stack>
inline nn::Result Thread::TryStart(void (*f)(T*), T& param, Stack& stack, s32 priority, s32 coreNo)
{
    TypeInfo info;
    info.SetData<T>();
    Result result = TryInitializeAndStartImpl(info, reinterpret_cast<ThreadFunc>(f), &param, stack.GetStackBottom(), priority, coreNo, false);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

template <typename T, typename U>
inline void Thread::StartUsingAutoStack(void (*f)(T), U param, size_t stackSize, s32 priority, s32 coreNo)
{
    TypeInfo info;
    info.SetData<T, U>();
    NN_OS_ERROR_IF_FAILED(TryInitializeAndStartImplUsingAutoStack(info, reinterpret_cast<ThreadFunc>(f), &param, stackSize, priority, coreNo));
}

inline void Thread::StartUsingAutoStack(void (*f)(), size_t stackSize, s32 priority, s32 coreNo)
{
    StartUsingAutoStack(NoParameterFunc, f, stackSize, priority, coreNo);
}

template <typename T, typename U>
inline nn::Result Thread::TryStartUsingAutoStack(void (*f)(T), U param, size_t stackSize, s32 priority, s32 coreNo)
{
    TypeInfo info;
    info.SetData<T, U>();
    Result result = TryInitializeAndStartImplUsingAutoStack(info, reinterpret_cast<ThreadFunc>(f), &param, stackSize, priority, coreNo);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

inline nn::Result Thread::TryStartUsingAutoStack(void (*f)(), size_t stackSize, s32 priority, s32 coreNo)
{
    return TryStartUsingAutoStack(NoParameterFunc, f, stackSize, priority, coreNo);
}

inline void Thread::Finalize()
{
    FinalizeImpl();
    this->WaitObject::Finalize();
}

inline Thread::~Thread()
{
    FinalizeImpl();
}

inline void Thread::Join()
{
    this->WaitOne();
    this->m_CanFinalize = true;
}

inline void Thread::Detach()
{
    NN_TASSERT_(m_UsingAutoStack);
    this->m_CanFinalize = true;
    Finalize();
}

inline bool Thread::IsAlive() const
{
    if (IsValid())
    {
        return !const_cast<Thread*>(this)->WaitOne(0);
    }
    else
    {
        return false;
    }
}

inline void Thread::Sleep(nn::fnd::TimeSpan span)
{
    SleepImpl(span);
}

inline void Thread::Yield()
{
    nn::svc::SleepThread(0);
}

inline bit32 Thread::GetId() const
{
    bit32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::GetThreadId(&ret, GetHandle()));
    return ret;
}

inline bit32 Thread::GetCurrentId()
{
    bit32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::GetThreadId(&ret, PSEUDO_HANDLE_CURRENT_THREAD));
    return ret;
}

inline s32 Thread::GetPriority() const
{
    s32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::GetThreadPriority(&ret, GetHandle()));
    return os::detail::ConvertSvcToLibraryPriority(ret);
}

inline s32 Thread::GetCurrentPriority()
{
    s32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::GetThreadPriority(&ret, PSEUDO_HANDLE_CURRENT_THREAD));
    return os::detail::ConvertSvcToLibraryPriority(ret);
}

inline void Thread::ChangePriority(s32 priority)
{
    NN_OS_ERROR_IF_FAILED(nn::svc::SetThreadPriority(GetHandle(), os::detail::ConvertLibraryToSvcPriority(priority)));
}

inline void Thread::ChangeCurrentPriority(s32 priority)
{
    NN_OS_ERROR_IF_FAILED(nn::svc::SetThreadPriority(PSEUDO_HANDLE_CURRENT_THREAD, os::detail::ConvertLibraryToSvcPriority(priority)));
}

//inline void Thread::GetAffinityMask(bit8* pAffinityMask, s32 numProcessor) const
//{
//    NN_ERR_THROW_FATAL(nn::svc::GetThreadAffinityMask(pAffinityMask, GetHandle(), numProcessor));
//}
//
//inline void Thread::GetCurrentAffinityMask(bit8* pAffinityMask, s32 numProcessor)
//{
//    NN_ERR_THROW_FATAL(nn::svc::GetThreadAffinityMask(pAffinityMask, PSEUDO_HANDLE_CURRENT_THREAD, numProcessor));
//}
//
//inline void Thread::GetDefaultAffinityMask(bit8* pAffinityMask, s32 numProcessor)
//{
//    NN_ERR_THROW_FATAL(nn::svc::GetProcessAffinityMask(pAffinityMask, PSEUDO_HANDLE_CURRENT_PROCESS, numProcessor));
//}
//
//inline void Thread::ChangeAffinityMask(const bit8* pAffinityMask, s32 numProcessor)
//{
//    NN_ERR_THROW_FATAL(nn::svc::SetThreadAffinityMask(GetHandle(), pAffinityMask, numProcessor));
//}
//
//inline void Thread::ChangeCurrentAffinityMask(const bit8* pAffinityMask, s32 numProcessor)
//{
//    NN_ERR_THROW_FATAL(nn::svc::SetThreadAffinityMask(PSEUDO_HANDLE_CURRENT_THREAD, pAffinityMask, numProcessor));
//}
//
//inline void Thread::SetDefaultAffinityMask(const bit8* pAffinityMask, s32 numProcessor)
//{
//    NN_ERR_THROW_FATAL(nn::svc::SetProcessAffinityMask(PSEUDO_HANDLE_CURRENT_PROCESS, pAffinityMask, numProcessor));
//}

inline s32 Thread::GetIdealProcessor() const
{
    s32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::GetThreadIdealProcessor(&ret, GetHandle()));
    return ret;
}

//inline s32 Thread::GetCurrentIdealProcessor()
//{
//    s32 ret;
//    NN_ERR_THROW_FATAL(nn::svc::GetThreadIdealProcessor(&ret, PSEUDO_HANDLE_CURRENT_THREAD));
//    return ret;
//}

inline s32 Thread::GetDefaultIdealProcessor()
{
    s32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::GetProcessIdealProcessor(&ret, PSEUDO_HANDLE_CURRENT_PROCESS));
    return ret;
}

//inline void Thread::ChangeIdealProcessor(s32 coreNo)
//{
//    NN_ERR_THROW_FATAL(nn::svc::SetThreadIdealProcessor(GetHandle(), coreNo));
//}
//
//inline void Thread::ChangeCurrentIdealProcessor(s32 coreNo)
//{
//    NN_ERR_THROW_FATAL(nn::svc::SetThreadIdealProcessor(PSEUDO_HANDLE_CURRENT_THREAD, coreNo));
//}
//
//inline void Thread::SetDefaultIdealProcessor(s32 coreNo)
//{
//    NN_ERR_THROW_FATAL(nn::svc::SetProcessIdealProcessor(PSEUDO_HANDLE_CURRENT_PROCESS, coreNo));
//}

inline s32 Thread::GetCurrentProcessorNumber()
{
    return nn::svc::GetCurrentProcessorNumber();
}

inline void Thread::ProtectedAccessor::InitializeAsMainThread(void* p)
{
    new(p) Thread(Thread::InitializeAsCurrentTag());
}


/*  

*/
/*  

*/

}} // namespace nn::os

#endif // NN_SYSTEM_PROCESS

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>


/* Please see man pages for details 
  
  

  

  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosThread, nn::os::Thread, 8, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadInitializeAndStart(nnosThread* this_, void (*f)(uptr), uptr param, uptr stackBottom, s32 priority, s32 coreNo);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosThreadTryInitializeAndStart(nnosThread* this_, void (*f)(uptr), uptr param, uptr stackBottom, s32 priority, s32 coreNo);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadFinalize(nnosThread* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadJoin(nnosThread* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadSleep(s64 nanoSeconds);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadYield(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bit32 nnosThreadGetCurrentId(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosThreadGetPriority(const nnosThread* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosThreadGetCurrentPriority(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadChangePriority(nnosThread* this_, s32 priority);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadChangeCurrentPriority(s32 priority);

    // Get/set the thread affinity

/* 
  
*/
//NN_EXTERN_C void nnosThreadGetAffinityMask(const nnosThread* this_, bit8* pAffinityMask, s32 numProcessor);

/* 
  
*/
//NN_EXTERN_C void nnosThreadGetCurrentAffinityMask(bit8* pAffinityMask, s32 numProcessor);

/* 
  
*/
//NN_EXTERN_C void nnosThreadGetDefaultAffinityMask(bit8* pAffinityMask, s32 numProcessor);

/* 
  
*/
//NN_EXTERN_C void nnosThreadChangeAffinityMask(nnosThread* this_, const bit8* pAffinityMask, s32 numProcessor);

/* 
  
*/
//NN_EXTERN_C void nnosThreadChangeCurrentAffinityMask(const bit8* pAffinityMask, s32 numProcessor);

/* 
  
*/
//NN_EXTERN_C void nnosThreadSetDefaultAffinityMask(const bit8* pAffinityMask, s32 numProcessor);

    // Get/set IdealProcessor

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosThreadGetIdealProcessor(const nnosThread* this_);

/* 
  
*/
//NN_EXTERN_C s32 nnosThreadGetCurrentIdealProcessor(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosThreadGetDefaultIdealProcessor(void);

/* 
  
*/
//NN_EXTERN_C void nnosThreadChangeIdealProcessor(nnosThread* this_, s32 coreNo);

/* 
  
*/
//NN_EXTERN_C void nnosThreadChangeCurrentIdealProcessor(s32 coreNo);

/* 
  
*/
//NN_EXTERN_C void nnosThreadSetDefaultIdealProcessor(s32 coreNo);

    // Get the processor number operating the current thread

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosThreadGetCurrentProcessorNumber(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bit32 nnosThreadGetId(nnosThread* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosThreadIsAlive(nnosThread* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnosThread* nnosThreadGetMainThread(void);

/*  


*/

/* NN_OS_THREAD_H_ */
#endif

