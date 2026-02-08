/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ManagedThread.h

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

#ifndef NN_OS_OS_MANAGEDTHREAD_H_
#define NN_OS_OS_MANAGEDTHREAD_H_

#include <nn/types.h>
#include <nn/os/os_Thread.h>
#include <nn/os/os_ThreadLocalStorage.h>
#include <nn/util.h>
#include <nn/fnd/fnd_LinkedList.h>


#ifdef __cplusplus


namespace nn{ namespace os{



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
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    class ManagedThread : public fnd::IntrusiveLinkedList<ManagedThread>::Item, public util::NonCopyable<ManagedThread>
    {
    private:
        static const s32 PRIORITY_DEFAULT = DEFAULT_THREAD_PRIORITY;
        static const s32 CORE_NO_DEFAULT  = CORE_NO_USE_PROCESS_VALUE;

        struct TypeInfo;
        struct StartParam;

    public:
        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        class EnumerateCallback
        {
        public:
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
            //----------------------------------------------------------------------
            virtual bool operator()(ManagedThread* p) = 0;
        };

    public:

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        ManagedThread() {}

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        ~ManagedThread() { Finalize(); }

    //

    //
    //

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
        //----------------------------------------------------------------------
        template <typename T, typename U, typename Stack>
        nn::Result TryInitialize              (void (*f)(T),  U param , Stack& stack,     s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T, typename Stack>
        nn::Result TryInitialize              (void (*f)(T*), const T& param, Stack& stack,     s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T, typename Stack>
        nn::Result TryInitialize              (void (*f)(const T*), const T& param, Stack& stack, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename Stack>
        nn::Result TryInitialize              (void (*f)(),             Stack& stack,     s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);

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
        //----------------------------------------------------------------------
        template <typename T, typename U, typename Stack>
        void       Initialize                 (void (*f)(T),  U param,  Stack& stack,     s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T, typename Stack>
        void       Initialize                 (void (*f)(T*), const T& param, Stack& stack,     s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T, typename Stack>
        void       Initialize                 (void (*f)(const T*), const T& param, Stack& stack, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename Stack>
        void       Initialize                 (void (*f)(),             Stack& stack,     s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);

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
        //----------------------------------------------------------------------
        template <typename T, typename U>
        nn::Result TryInitializeUsingAutoStack(void (*f)(T),  U param,  size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T>
        nn::Result TryInitializeUsingAutoStack(void (*f)(T*), const T& param, size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T>
        nn::Result TryInitializeUsingAutoStack(void (*f)(const T*), const T& param, size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        nn::Result TryInitializeUsingAutoStack(void (*f)(),             size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);

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
        //----------------------------------------------------------------------
        template <typename T, typename U>
        void       InitializeUsingAutoStack   (void (*f)(T),  U param,  size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T>
        void       InitializeUsingAutoStack   (void (*f)(T*), const T& param, size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        //----------------------------------------------------------------------
        template <typename T>
        void       InitializeUsingAutoStack   (void (*f)(const T*), const T& param, size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);
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
        void       InitializeUsingAutoStack   (void (*f)(),             size_t stackSize, s32 priority = PRIORITY_DEFAULT, s32 coreNo = CORE_NO_DEFAULT);

    //

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void    Start();

    //

    //
    //

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
        //----------------------------------------------------------------------
        void Finalize();

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //----------------------------------------------------------------------
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
        //----------------------------------------------------------------------
        void Detach();

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        bool IsAlive() const    { return m_Thread.IsAlive(); }

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        bool IsValid() const    { return m_Thread.IsValid(); }

    //

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        bit32 GetId() const                     { return m_Id; }

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
        //----------------------------------------------------------------------
        static bit32 GetCurrentId()             { return ms_IdStorage.GetValue(); }

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        s32 GetPriority() const                 { return m_Thread.GetPriority(); }

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void ChangePriority(s32 priority)       { m_Thread.ChangePriority(priority); }

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        s32 GetIdealProcessor() const           { return m_Thread.GetIdealProcessor(); }

    //

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        uptr    GetStackBufferBegin() const;

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
        //----------------------------------------------------------------------
        uptr    GetStackBottom() const;

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
        //----------------------------------------------------------------------
        uptr    GetStackBufferEnd() const;

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
        size_t  GetStackSize() const;

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        size_t  GetStackBufferSize() const;

    //

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        const char8* GetName() const;

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
        //----------------------------------------------------------------------
        void    SetName(const char8* pName);

    //

    //
    //

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
        //----------------------------------------------------------------------
        static ManagedThread* GetCurrentThread();

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
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        static ManagedThread* FindByStackAddress(uptr address);

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
        //----------------------------------------------------------------------
        static ManagedThread* FindById(bit32 id);

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
        //
        //
        //
        //----------------------------------------------------------------------
        static void Enumerate(EnumerateCallback* p);

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        static s32  GetCurrentManagedCount();

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
        static void InitializeEnvironment();

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        static bool IsEnabled();

    //

    private:
        Result TryInitialize(const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, size_t stackSize, s32 priority, s32 coreNo);
        Result TryInitializeUsingAutoStack(const TypeInfo& typeInfo, ThreadFunc f, const void* p, size_t stackSize, s32 priority, s32 coreNo);

        void InitializeAsMainThread();

        static void Register(ManagedThread* p);
        static void Unregister(ManagedThread* p);

        static void SetCurrentThread(ManagedThread* p);
        static void SetCurrentThreadId(bit32 id);

    private:
        Result TryInitializeImpl(
                const TypeInfo& typeInfo,
                ThreadFunc      f,
                const void*     p,
                uptr            stackBottom,
                size_t          stackSize,
                s32             priority,
                s32             coreNo );
        Result TryInitializeImpl(
                const TypeInfo& typeInfo,
                ThreadFunc      f,
                const void*     p,
                uptr            stackBottom,
                size_t          stackSize,
                s32             priority,
                s32             coreNo,
                bool            useAutoStack );
        Result TryInitializeImplUsingAutoStack(const TypeInfo& typeInfo, ThreadFunc f, const void* p, size_t stackSize, s32 priority, s32 coreNo);
        uptr SetupStackAndParam(StartParam* pParam, const TypeInfo& typeInfo, ThreadFunc f, const void* p, uptr stackBottom, size_t stackSize);

    private:
        static void ThreadStart(StartParam* p);
        static void ThreadStartUsingAutoStack(uptr);
        static void NoParameterFunc(void (*)());

    private:
        Thread          m_Thread;
        uptr            m_StackBottom;
        uptr            m_StackBufferEnd;
        size_t          m_StackSize;
        LightEvent*     m_pStartEvent;
        const char8*    m_pName;
        bit32           m_Id;

    private:
        static ThreadLocalStorage   ms_ThreadStorage;
        static ThreadLocalStorage   ms_IdStorage;
    };


#ifdef NN_SYSTEM_PROCESS

    struct ManagedThread::TypeInfo
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
        TypeInfo(T* dummy1, U* dummy2, typename nn::util::enable_if<nn::util::is_convertible<U, T>::value>::type* = 0)
        {
            NN_UNUSED_VAR(dummy1);
            NN_UNUSED_VAR(dummy2);
            this->size = sizeof(T);
            this->copy = &(Copy<T, U>);
            this->destroy = &(Destroy<T>);
            this->invoke = &(Invoke<T>);
        }
        template <typename T>
        TypeInfo(T* dummy)
        {
            NN_UNUSED_VAR(dummy);
            this->size = sizeof(T);
            this->copy = &(Copy<T>);
            this->destroy = &(Destroy<T>);
            this->invoke = &(Invoke2<T>);
        }
    };



    template <typename T, typename U, typename Stack>
    inline nn::Result ManagedThread::TryInitialize(void (*f)(T), U param, Stack& stack, s32 priority, s32 coreNo)
    {
        return TryInitializeImpl(
                            TypeInfo(reinterpret_cast<T*>(NULL), &param),
                            reinterpret_cast<ThreadFunc>(f),
                            &param,
                            stack.GetStackBottom(),
                            stack.GetStackSize(),
                            priority,
                            coreNo );
    }
    template <typename T, typename Stack>
    inline nn::Result ManagedThread::TryInitialize(void (*f)(T*), const T& param, Stack& stack, s32 priority, s32 coreNo)
    {
        return TryInitializeImpl(
                            TypeInfo(reinterpret_cast<T*>(NULL)),
                            reinterpret_cast<ThreadFunc>(f),
                            &param,
                            stack.GetStackBottom(),
                            stack.GetStackSize(),
                            priority,
                            coreNo );
    }
    template <typename T, typename Stack>
    inline nn::Result ManagedThread::TryInitialize(void (*f)(const T*), const T& param, Stack& stack, s32 priority, s32 coreNo)
    {
        return TryInitializeImpl(
                            TypeInfo(reinterpret_cast<T*>(NULL)),
                            reinterpret_cast<ThreadFunc>(f),
                            &param,
                            stack.GetStackBottom(),
                            stack.GetStackSize(),
                            priority,
                            coreNo );
    }
    template <typename Stack>
    inline nn::Result ManagedThread::TryInitialize(void (*f)(), Stack& stack, s32 priority, s32 coreNo)
    {
        return TryInitialize(NoParameterFunc, f, stack, priority, coreNo);
    }

    template <typename T, typename U, typename Stack>
    inline void ManagedThread::Initialize(void (*f)(T), U param, Stack& stack, s32 priority, s32 coreNo)
    {
        NN_OS_ERROR_IF_FAILED(
            TryInitializeImpl(
                TypeInfo(reinterpret_cast<T*>(NULL), &param),
                reinterpret_cast<ThreadFunc>(f),
                &param,
                stack.GetStackBottom(),
                stack.GetStackSize(),
                priority,
                coreNo ) );
    }
    template <typename T, typename Stack>
    inline void ManagedThread::Initialize(void (*f)(T*), const T& param, Stack& stack, s32 priority, s32 coreNo)
    {
        NN_OS_ERROR_IF_FAILED(
            TryInitializeImpl(
                TypeInfo(reinterpret_cast<T*>(NULL)),
                reinterpret_cast<ThreadFunc>(f),
                &param,
                stack.GetStackBottom(),
                stack.GetStackSize(),
                priority,
                coreNo ) );
    }
    template <typename T, typename Stack>
    inline void ManagedThread::Initialize(void (*f)(const T*), const T& param, Stack& stack, s32 priority, s32 coreNo)
    {
        NN_OS_ERROR_IF_FAILED(
            TryInitializeImpl(
                TypeInfo(reinterpret_cast<const T*>(NULL)),
                reinterpret_cast<ThreadFunc>(f),
                &param,
                stack.GetStackBottom(),
                stack.GetStackSize(),
                priority,
                coreNo ) );
    }
    template <typename Stack>
    inline void ManagedThread::Initialize(void (*f)(), Stack& stack, s32 priority, s32 coreNo)
    {
        Initialize(NoParameterFunc, f, stack, priority, coreNo);
    }

    template <typename T, typename U>
    inline nn::Result ManagedThread::TryInitializeUsingAutoStack(void (*f)(T), U param, size_t stackSize, s32 priority, s32 coreNo)
    {
        return TryInitializeImplUsingAutoStack(
                            TypeInfo(reinterpret_cast<T*>(NULL), &param),
                            reinterpret_cast<ThreadFunc>(f),
                            &param,
                            stackSize,
                            priority,
                            coreNo );
    }
    template <typename T>
    inline nn::Result ManagedThread::TryInitializeUsingAutoStack(void (*f)(T*), const T& param, size_t stackSize, s32 priority, s32 coreNo)
    {
        return TryInitializeImplUsingAutoStack(
                            TypeInfo(reinterpret_cast<T*>(NULL)),
                            reinterpret_cast<ThreadFunc>(f),
                            &param,
                            stackSize,
                            priority,
                            coreNo );
    }
    template <typename T>
    inline nn::Result ManagedThread::TryInitializeUsingAutoStack(void (*f)(const T*), const T& param, size_t stackSize, s32 priority, s32 coreNo)
    {
        return TryInitializeImplUsingAutoStack(
                            TypeInfo(reinterpret_cast<T*>(NULL)),
                            reinterpret_cast<ThreadFunc>(f),
                            &param,
                            stackSize,
                            priority,
                            coreNo );
    }
    inline nn::Result ManagedThread::TryInitializeUsingAutoStack(void (*f)(), size_t stackSize, s32 priority, s32 coreNo)
    {
        return TryInitializeUsingAutoStack(NoParameterFunc, f, stackSize, priority, coreNo);
    }

    template <typename T, typename U>
    inline void ManagedThread::InitializeUsingAutoStack(void (*f)(T), U param, size_t stackSize, s32 priority, s32 coreNo)
    {
        NN_OS_ERROR_IF_FAILED(
            TryInitializeImplUsingAutoStack(
                TypeInfo(reinterpret_cast<T*>(NULL), &param),
                reinterpret_cast<ThreadFunc>(f),
                &param,
                stackSize,
                priority,
                coreNo ) );
    }
    template <typename T>
    inline void ManagedThread::InitializeUsingAutoStack(void (*f)(T*), const T& param, size_t stackSize, s32 priority, s32 coreNo)
    {
        NN_OS_ERROR_IF_FAILED(
            TryInitializeImplUsingAutoStack(
                TypeInfo(reinterpret_cast<T*>(NULL)),
                reinterpret_cast<ThreadFunc>(f),
                &param,
                stackSize,
                priority,
                coreNo ) );
    }
    template <typename T>
    inline void ManagedThread::InitializeUsingAutoStack(void (*f)(const T*), const T& param, size_t stackSize, s32 priority, s32 coreNo)
    {
        NN_OS_ERROR_IF_FAILED(
            TryInitializeImplUsingAutoStack(
                TypeInfo(reinterpret_cast<const T*>(NULL)),
                reinterpret_cast<ThreadFunc>(f),
                &param,
                stackSize,
                priority,
                coreNo ) );
    }
    inline void ManagedThread::InitializeUsingAutoStack(void (*f)(), size_t stackSize, s32 priority, s32 coreNo)
    {
        InitializeUsingAutoStack(NoParameterFunc, f, stackSize, priority, coreNo);
    }




#endif  // ifdef NN_SYSTEM_PROCESS



}}


#endif
/* NN_OS_OS_MANAGEDTHREAD_H_ */
#endif

