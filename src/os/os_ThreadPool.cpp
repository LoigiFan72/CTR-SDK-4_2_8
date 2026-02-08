/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ThreadPool.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_ThreadPool.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <new>

namespace nn { namespace os {

inline Thread* ThreadPool::GetThreads() const
{
    return reinterpret_cast<Thread*>(m_Buffer);
}

inline nn::Handle* ThreadPool::GetWaitHandleBuffer() const
{
    return reinterpret_cast<nn::Handle*>(m_Buffer + sizeof(Thread) * m_NumThreads);
}

inline QueueableWaitTask** ThreadPool::GetWaitTaskBuffer() const
{
    return reinterpret_cast<QueueableWaitTask**>(m_Buffer + sizeof(Thread) * m_NumThreads + sizeof(nn::Handle) * (m_NumMaxWaitObjects + 1));
}

size_t ThreadPool::GetWorkBufferSize(size_t numMaxWaitObjects, size_t numThreads)
{
    return sizeof(Thread) * numThreads
         + sizeof(nn::Handle) * (numMaxWaitObjects + 1)
         + sizeof(QueueableWaitTask*) * numMaxWaitObjects;
}

inline void ThreadPool::InitializeCommon(size_t numMaxWaitObjects, size_t numThreads, void* workBuffer)
{
    this->m_Finalizing = false;
    this->m_WaitingCount = 0;
    this->m_NumMaxWaitObjects = numMaxWaitObjects;
    this->m_NumThreads = numThreads;
    this->m_Buffer = reinterpret_cast<uptr>(workBuffer);
    this->m_WaitEvent.Initialize(false);
    this->m_ExecuteEvent.Initialize(false);
    this->m_WaitLock.Initialize();
    this->m_ExecuteLock.Initialize();
}

namespace {
    struct StackBufferAdapter
    {
        uptr stackBottom;
        StackBufferAdapter(uptr stackBottom) : stackBottom(stackBottom) {}
        uptr GetStackBottom() const { return stackBottom; }
    };
}

// Starts the thread to manage tasks on standby.
inline void ThreadPool::StartWaitThread(s32 priority)
{
    GetWaitHandleBuffer()[0] = this->m_WaitEvent.GetHandle();
    m_WaitThread.Start(ThreadPool::WaitThreadFunc, this, m_WaitThreadStack, priority);
}

// Starts worker thread to execute tasks.
inline void ThreadPool::StartExecuteThread(size_t i, uptr stackBottom, s32 priority)
{
    Thread* thread = new (GetThreads() + i) Thread();
    StackBufferAdapter stack(stackBottom);
    thread->Start(ThreadPool::ExecuteThreadFunc, this, stack, priority);
}

void ThreadPool::Initialize(void* workBuffer, size_t numMaxWaitObjects, size_t numThreads, uptr stackBottoms[], s32 workerPriority, s32 waitPriority)
{
    // TODO: Recommend NULL check of workBuffer.

    InitializeCommon(numMaxWaitObjects, numThreads, workBuffer);
    for (size_t i = 0; i < numThreads; i++)
    {
        StartExecuteThread(i, stackBottoms[i], workerPriority);
    }
    StartWaitThread(waitPriority);
}

#if NN_PLATFORM_HAS_MMU
void ThreadPool::Initialize(void* workBuffer, size_t numMaxWaitObjects, size_t numThreads, nn::os::StackMemoryBlock stacks[], s32 workerPriority, s32 waitPriority)
{
    // TODO: Recommend NULL check of workBuffer.

    InitializeCommon(numMaxWaitObjects, numThreads, workBuffer);
    for (size_t i = 0; i < numThreads; i++)
    {
        StartExecuteThread(i, stacks[i].GetStackBottom(), workerPriority);
    }
    StartWaitThread(waitPriority);
}
#endif  // if NN_PLATFORM_HAS_MMU

void ThreadPool::Finalize()
{
    // Stops the task standby thread and worker thread.
    this->m_Finalizing = true;
    
    m_WaitEvent.Signal();
    m_ExecuteEvent.Signal();
    
    for (size_t i = 0; i < m_NumThreads; i++)
    {
        Thread& thread = GetThreads()[i];
        thread.Join();
        thread.Finalize();
    }

    m_WaitThread.Join();
    m_WaitThread.Finalize();
}

void ThreadPool::AddToExecuteQueue(QueueableTask* task)
{
    {
        nn::os::CriticalSection::ScopedLock locker(m_ExecuteLock);

        m_ExecuteQueue.Enqueue(task);
    }

    // Wakes up the worker thread to execute tasks.
    m_ExecuteEvent.Signal();
}

void ThreadPool::AddToWaitQueue(QueueableWaitTask* task)
{
    {
        nn::os::CriticalSection::ScopedLock locker(m_WaitLock);
        
        m_WaitQueue.Enqueue(task->AsNonWaitableTask());
    }

    // Wakes up synchronization wait thread.
    m_WaitEvent.Signal();
}

// Loop processing for the synchronization wait thread.
inline void ThreadPool::WaitThreadFunc()
{
    // The stack size of this function (WAIT_THREAD_STACK_SIZE) is fixed and small.
    // Take note when revising the code.
    // Revise the stack size if necessary.
    while (!m_Finalizing)
    {
        {
            nn::os::CriticalSection::ScopedLock locker(m_WaitLock);
            
            // Adds new tasks added to the synchronization task queue to the synchronization wait handle buffer.
            for (; m_WaitingCount < m_NumMaxWaitObjects && !m_WaitQueue.IsEmpty(); ++m_WaitingCount)
            {
                QueueableWaitTask* task = GetWaitTaskPointer(m_WaitQueue.Dequeue());
                GetWaitTaskBuffer()[m_WaitingCount] = task;
                // Specifies a value of 1 or greater in the index because a 0 value for the synchronization wait handle buffer index is used to notify that a task has been added.
                // 
                GetWaitHandleBuffer()[m_WaitingCount + 1] = task->GetWaitObject()->GetHandle();
            }
        }
        
        // Waits until one of the handles waiting for synchronization enters a signal state.
        s32 n;
        NN_OS_ERROR_IF_FAILED(nn::svc::WaitSynchronization(&n, GetWaitHandleBuffer(), m_WaitingCount + 1, false, WAIT_INFINITE));
        // Does not process when a synchronization task is added to the queue (n == 0).
        if (n >= 1)
        {
            // Move tasks that have completed synchronization wait to the task execution buffer.
            QueueableTask* task;
            {
                nn::os::CriticalSection::ScopedLock locker(m_WaitLock);
                
                task = GetWaitTaskBuffer()[n - 1]->AsNonWaitableTask();
                GetWaitTaskBuffer()[n - 1] = GetWaitTaskBuffer()[m_WaitingCount - 1];
                GetWaitHandleBuffer()[n] = GetWaitHandleBuffer()[m_WaitingCount];
                --m_WaitingCount;
            }
            AddToExecuteQueue(task);
        }
    }
}

void ThreadPool::WaitThreadFunc(ThreadPool* this_)
{
    this_->WaitThreadFunc();
}

// Loop processing for the task execution worker thread.
inline void ThreadPool::ExecuteThreadFunc()
{
    while (!m_Finalizing)
    {
        // If notification of task execution is received, one of the worker threads on standby executes a task.
        m_ExecuteEvent.Wait();
        if (m_Finalizing)
        {
            break;
        }
        // Locks so that the execution task queue content cannot be read or written while obtaining a task.
        m_ExecuteLock.Enter();
        if (QueueableTask* task = m_ExecuteQueue.Dequeue())
        {
            if (!m_ExecuteQueue.IsEmpty())
            {
                m_ExecuteLock.Leave();
                // If other tasks exist in the execution task queue, another worker thread is awakened and a task is executed.
                m_ExecuteEvent.Signal();
            }
            else
            {
                m_ExecuteLock.Leave();
            }
            // Executes a task.
            task->Invoke();
        }
        else
        {
            m_ExecuteLock.Leave();
        }
    }
    
    // Wakes another worker thread, and executes the finalization process.
    m_ExecuteEvent.Signal();
}

void ThreadPool::ExecuteThreadFunc(ThreadPool* this_)
{
    this_->ExecuteThreadFunc();
}

// -----------------------------------------------------------------------



void SingleThreadPool::Initialize(uptr stackBottom, s32 priority)
{
    this->m_ExecuteEvent.Initialize(false);
    this->m_ExecuteLock.Initialize();
    StackBufferAdapter stack(stackBottom);
    m_WorkerThread.Start(SingleThreadPool::ExecuteThreadFunc, this, stack, priority);
}

void SingleThreadPool::Finalize()
{
    // Stops the task standby thread and worker thread.
    if(!m_Finalizing)
    {
        this->m_Finalizing = true;
        m_ExecuteEvent.Signal();
        m_WorkerThread.Join();
        m_WorkerThread.Finalize();
    }
}

// Loop processing for the task execution worker thread.
inline void SingleThreadPool::ExecuteThreadFunc()
{
    while (!m_Finalizing)
    {
        // If notification of task execution is received, one of the worker threads on standby executes a task.
        m_ExecuteEvent.Wait();
        if (m_Finalizing)
        {
            break;
        }
        // Locks so that the execution task queue content cannot be read or written while obtaining a task.
        m_ExecuteLock.Enter();
        if (QueueableTask* task = m_ExecuteQueue.Dequeue())
        {
            if (!m_ExecuteQueue.IsEmpty())
            {
                m_ExecuteLock.Leave();
                // If another task exists in the execution task queue, an event notification is made so that the next execution can be done immediately
                m_ExecuteEvent.Signal();
            }
            else
            {
                m_ExecuteLock.Leave();
            }
            // Executes a task.
            task->Invoke();
        }
        else
        {
            m_ExecuteLock.Leave();
        }
    }
}

void SingleThreadPool::ExecuteThreadFunc(SingleThreadPool* this_)
{
    this_->ExecuteThreadFunc();
}

void SingleThreadPool::AddToExecuteQueue(QueueableTask* task)
{
    {
        nn::os::CriticalSection::ScopedLock locker(m_ExecuteLock);

        m_ExecuteQueue.Enqueue(task);
    }
    // Wakes up the worker thread to execute tasks.
    m_ExecuteEvent.Signal();
}

}} // namespace nn::os

#include <new>
using namespace nn::os;
using namespace nn::os::detail;

NN_EXTERN_C void nnosThreadPoolTaskInitialize(nnosThreadPoolTask* p, void (*f)(uptr), uptr param)
{
    new (p) ThreadPoolTaskForC(f, param);
}

void nnosThreadPoolTaskFinalize(nnosThreadPoolTask* p)
{
    ThreadPoolTaskForC* pThreadPoolTaskForC = reinterpret_cast<ThreadPoolTaskForC*>(p);
    pThreadPoolTaskForC->~ThreadPoolTaskForC();
}

NN_EXTERN_C void nnosThreadPoolWaitTaskInitialize(nnosThreadPoolWaitTask* p, nnosWaitObject* waitObject, void (*f)(uptr), uptr param)
{
    new (p) ThreadPoolWaitTaskForC(waitObject, f, param);
}

void nnosThreadPoolWaitTaskFinalize(nnosThreadPoolWaitTask* p)
{
    ThreadPoolWaitTaskForC* pThreadPoolWaitTaskForC = reinterpret_cast<ThreadPoolWaitTaskForC*>(p);
    pThreadPoolWaitTaskForC->~ThreadPoolWaitTaskForC();
}

void nnosThreadPoolInitialize(nnosThreadPool* p, void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, uptr workerStackBottoms[], s32 workerPriority)
{
    ThreadPool* pThreadPool = new (p) ThreadPool();
    pThreadPool->Initialize(workBuffer, numMaxWaitObjects, numWorkerThreads, workerStackBottoms, workerPriority);
}

#if NN_PLATFORM_HAS_MMU
void nnosThreadPoolInitializeWithStackMemoryBlock(nnosThreadPool* p, void* workBuffer, size_t numMaxWaitObjects, size_t numWorkerThreads, nnosStackMemoryBlock workerStacks[], s32 workerPriority)
{
    ThreadPool* pThreadPool = new (p) ThreadPool();
    StackMemoryBlock* pWorkerStacks = reinterpret_cast<StackMemoryBlock*>(workerStacks);
    pThreadPool->Initialize(workBuffer, numMaxWaitObjects, numWorkerThreads, pWorkerStacks, workerPriority);
}
#endif  // if NN_PLATFORM_HAS_MMU

void nnosThreadPoolFinalize(nnosThreadPool* p)
{
    ThreadPool* pThreadPool = reinterpret_cast<ThreadPool*>(p);
    pThreadPool->Finalize();
}

void nnosThreadPoolAddWaitTask(nnosThreadPool* p, nnosThreadPoolWaitTask* task)
{
    ThreadPool* pThreadPool = reinterpret_cast<ThreadPool*>(p);
    ThreadPoolWaitTaskForC* pThreadPoolTask = reinterpret_cast<ThreadPoolWaitTaskForC*>(task);
    pThreadPool->AddWaitTask(pThreadPoolTask);
}

void nnosThreadPoolAddTask(nnosThreadPool* p, nnosThreadPoolTask* task)
{
    ThreadPool* pThreadPool = reinterpret_cast<ThreadPool*>(p);
    ThreadPoolTaskForC* pThreadPoolTask = reinterpret_cast<ThreadPoolTaskForC*>(task);
    pThreadPool->AddTask(pThreadPoolTask);
}

size_t nnosThreadPoolGetWorkBufferSize(size_t numMaxWaitObjects, size_t numWorkerThreads)
{
    return ThreadPool::GetWorkBufferSize(numMaxWaitObjects, numWorkerThreads);
}

