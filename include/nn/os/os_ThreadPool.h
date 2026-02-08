/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ThreadPool.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
            
            
            
            
    

    
*/

#ifndef NN_OS_OS_THREADPOOL_H_
#define NN_OS_OS_THREADPOOL_H_

#include <nn/os/os_Synchronization.h>
#include <nn/os/os_StackMemoryBlock.h>
#include <nn/os/os_Thread.h>
#include <nn/os/os_Event.h>
#include <nn/os/os_LightEvent.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/fnd/fnd_Queue.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/os/os_Task.h>

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
    

    
*/
class ThreadPool : public IWaitTaskInvoker, private nn::util::NonCopyable<ThreadPool>
{
public:
    
    // Size of buffer to pass to the first argument at initialization.
    // This buffer must be allocated by the user.
    /* Please see man pages for details 
        

        
        

        
     */
    static size_t GetWorkBufferSize(size_t numMaxWaitObjects, size_t numWorkerThreads);
    
    /* Please see man pages for details 
        

        
     */
    ThreadPool();
    /* Please see man pages for details 
        

        
        
        
        
        
        
     */
    ThreadPool(void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, uptr workerStackBottoms[], s32 workerPriority = DEFAULT_THREAD_PRIORITY, s32 waitPriority = 0);

#if NN_PLATFORM_HAS_MMU
    /* Please see man pages for details 
        

        
        
        
        
        
        
     */
    ThreadPool(void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, nn::os::StackMemoryBlock workerStacks[], s32 workerPriority = DEFAULT_THREAD_PRIORITY, s32 waitPriority = 0);
#endif  // if NN_PLATFORM_HAS_MMU

    /* Please see man pages for details 
        

        
     */
    virtual ~ThreadPool() { Finalize(); }

    /* Please see man pages for details 
        

        
        
        
        
        
        

        
     */
    void Initialize(void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, uptr workerStackBottoms[], s32 workerPriority = DEFAULT_THREAD_PRIORITY, s32 waitPriority = 0);
#if NN_PLATFORM_HAS_MMU
    /* Please see man pages for details 
        

        
        
        
        
        
        

        
     */
    void Initialize(void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, nn::os::StackMemoryBlock workerStacks[], s32 workerPriority = DEFAULT_THREAD_PRIORITY, s32 waitPriority = 0);
#endif  // if NN_PLATFORM_HAS_MMU

    // TODO: Need TryInitialize? Implementation is low priority as it is very difficult to rewind.
    
    /* Please see man pages for details 
        

        
     */
    void Finalize();
    
    /* Please see man pages for details 
        

                    
                    

        

        
     */
    virtual void AddTask(QueueableTask* task) { AddToExecuteQueue(task); }

    /* Please see man pages for details 
        

                    
                    
                    
                    

        

        
     */
    virtual void AddWaitTask(QueueableWaitTask* task) { AddToWaitQueue(task); }
    
private:
    size_t                  m_NumMaxWaitObjects;
    size_t                  m_NumThreads;
    
    uptr                    m_Buffer;
    s32                     m_WaitingCount;
    
    bool                    m_Finalizing;
    bit8                    m_Padding[3];

    static const size_t WAIT_THREAD_STACK_SIZE = 392;
    StackBuffer<WAIT_THREAD_STACK_SIZE> m_WaitThreadStack;
    
    Thread                  m_WaitThread;
    nn::fnd::IntrusiveQueue<QueueableTask> m_WaitQueue;
    nn::os::CriticalSection m_WaitLock;
    nn::os::Event           m_WaitEvent;
    
    nn::fnd::IntrusiveQueue<QueueableTask> m_ExecuteQueue;
    nn::os::CriticalSection m_ExecuteLock;
    nn::os::LightEvent      m_ExecuteEvent;
    NN_PADDING4;
    
private:
    Thread* GetThreads() const;
    nn::Handle* GetWaitHandleBuffer() const;
    QueueableWaitTask** GetWaitTaskBuffer() const;
    
    void AddToWaitQueue(QueueableWaitTask*);

    void AddToExecuteQueue(QueueableTask*);

    static void WaitThreadFunc(ThreadPool*);
    void WaitThreadFunc();
    static void ExecuteThreadFunc(ThreadPool*);
    void ExecuteThreadFunc();

    void InitializeCommon(size_t numMaxWaitObjects, size_t numWorkerThreads, void* workBuffer);
    void StartWaitThread(s32 priority);
    void StartExecuteThread(size_t i, uptr stackBottom, s32 priority);
    
};

inline ThreadPool::ThreadPool() : m_Buffer(0) {}

inline ThreadPool::ThreadPool(void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, uptr workerStackBottoms[], s32 workerPriority, s32 waitPriority) 
    : m_Buffer(0)
{
    Initialize(workBuffer, numMaxWaitObjects, numWorkerThreads, workerStackBottoms, workerPriority, waitPriority);
}

#if NN_PLATFORM_HAS_MMU
inline ThreadPool::ThreadPool(void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, nn::os::StackMemoryBlock workerStacks[], s32 workerPriority, s32 waitPriority) 
    : m_Buffer(0)
{
    Initialize(workBuffer, numMaxWaitObjects, numWorkerThreads, workerStacks, workerPriority, waitPriority);
}
#endif  // if NN_PLATFORM_HAS_MMU


class SingleThreadPool : public ITaskInvoker, private nn::util::NonCopyable<SingleThreadPool>
{
public:
    SingleThreadPool() : m_Finalizing(false) {}
    virtual ~SingleThreadPool() { Finalize(); }
    void Initialize(uptr workerThreadStackBottom, s32 workerPriority = DEFAULT_THREAD_PRIORITY);
    void Finalize();

    virtual void AddTask(QueueableTask* task) { AddToExecuteQueue(task); }

    static void ExecuteThreadFunc(SingleThreadPool* pInstance);
    void ExecuteThreadFunc();

private:
    nn::os::Thread m_WorkerThread;
    nn::fnd::IntrusiveQueue<QueueableTask> m_ExecuteQueue;
    nn::os::CriticalSection m_ExecuteLock;
    nn::os::LightEvent m_ExecuteEvent;

    bool    m_Finalizing;
    NN_PADDING3;
    
    void AddToExecuteQueue(QueueableTask*);
};


}}

#endif // __cplusplus

// C declarations follow


#ifdef __cplusplus

namespace nn { namespace os {

namespace detail
{
    class ThreadPoolTaskForC : public QueueableTask
    {
    public:
        ThreadPoolTaskForC(void (*f)(uptr), uptr param) : m_F(f), m_Param(param) {}
        virtual void Invoke() { m_F(m_Param); }
    private:
        void (*m_F)(uptr);
        uptr m_Param;
    };

    class ThreadPoolWaitTaskForC : public QueueableWaitTask
    {
    public:
        ThreadPoolWaitTaskForC(nnosWaitObject* waitObject, void (*f)(uptr), uptr param) : m_WaitObject(waitObject), m_F(f), m_Param(param) {}
        virtual nn::os::WaitObject* GetWaitObject() { return reinterpret_cast<nn::os::WaitObject*&>(m_WaitObject); }
        virtual void Invoke() { m_F(m_Param); }
    private:
        nnosWaitObject* m_WaitObject;
        void (*m_F)(uptr);
        uptr m_Param;
    };
}

}}

#endif

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  

  
*/

/* Please see man pages for details 
  

  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosThreadPoolTask, nn::os::detail::ThreadPoolTaskForC, 16, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolTaskInitialize(nnosThreadPoolTask* this_, void (*f)(uptr), uptr param);

/* Please see man pages for details 
  
*/

NN_EXTERN_C void nnosThreadPoolTaskFinalize(nnosThreadPoolTask* this_);


/* Please see man pages for details 
  

  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosThreadPoolWaitTask, nn::os::detail::ThreadPoolWaitTaskForC, 20, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolWaitTaskInitialize(nnosThreadPoolWaitTask* this_, nnosWaitObject* waitObject, void (*f)(uptr), uptr param);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolWaitTaskFinalize(nnosThreadPoolWaitTask* this_);


/* Please see man pages for details 
  

  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosThreadPool, nn::os::ThreadPool, 480, bit64);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolInitialize(nnosThreadPool* this_, void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, uptr workerStackBottoms[], s32 workerPriority);
#if NN_PLATFORM_HAS_MMU
NN_EXTERN_C void nnosThreadPoolInitializeWithStackMemoryBlock(nnosThreadPool* this_, void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, nnosStackMemoryBlock workerStacks[], s32 workerPriority);
#endif  // if NN_PLATFORM_HAS_MMU

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolFinalize(nnosThreadPool* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolAddWaitTask(nnosThreadPool* this_, nnosThreadPoolWaitTask* task);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosThreadPoolAddTask(nnosThreadPool* this_, nnosThreadPoolTask* task);

/* Please see man pages for details 
  
*/
NN_EXTERN_C size_t nnosThreadPoolGetWorkBufferSize(size_t numMaxWaitObjects, size_t numWorkerThreads);

/*  



*/

#endif // NN_OS_OS_THREADPOOL_H_
