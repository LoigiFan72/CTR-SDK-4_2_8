/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_BlockingQueue.cpp

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
#include <nn/os/os_BlockingQueue.h>
#include <nn/os/os_Mutex.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/fnd/fnd_Interlocked.h>
#include <nn/util/detail/util_InitializationTransaction.h>

#include <climits>

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::fnd;
using namespace nn::svc;
using namespace nn::os;
using namespace nn::util;

namespace nn{ namespace os{

namespace detail {

template <class Locker>
BlockingQueueBase<Locker>::~BlockingQueueBase()
{
    NN_TASSERT_(m_WaitingEnqueueCount == 0 && m_WaitingDequeueCount == 0);
    Finalize();
}

template <class Locker>
void BlockingQueueBase<Locker>::Initialize(uptr buffer[], size_t size)
{
    m_ppBuffer      = buffer;
    m_size          = size;
    m_firstIndex    = 0;
    m_usedCount     = 0;
    m_WaitingEnqueueCount = 0;
    m_WaitingDequeueCount = 0;
    m_EnqueueSemaphore.Initialize(0);
    m_DequeueSemaphore.Initialize(0);
    m_cs.Initialize();
}

template <class Locker>
nn::Result BlockingQueueBase<Locker>::TryInitialize(uptr buffer[], size_t size)
{
    m_ppBuffer      = buffer;
    m_size          = size;
    m_firstIndex    = 0;
    m_usedCount     = 0;
    m_WaitingEnqueueCount = 0;
    m_WaitingDequeueCount = 0;

    m_EnqueueSemaphore.Initialize(0);
    m_DequeueSemaphore.Initialize(0);

    NN_UTIL_RETURN_IF_FAILED(m_cs.TryInitialize());
    return ResultSuccess();
}

template <class Locker>
void BlockingQueueBase<Locker>::Finalize()
{
    m_cs.Finalize();
    m_DequeueSemaphore.Finalize();
    m_EnqueueSemaphore.Finalize();
}


template <class Locker>
inline void BlockingQueueBase<Locker>::NotifyEnqueue() const
{
    if (m_WaitingEnqueueCount > 0)
    {
        m_EnqueueSemaphore.Release();
    }
}

template <class Locker>
inline void BlockingQueueBase<Locker>::NotifyDequeue() const
{
    if (m_WaitingDequeueCount > 0)
    {
        m_DequeueSemaphore.Release();
    }
}

template <class Locker>
bool BlockingQueueBase<Locker>::TryEnqueue(uptr data)
{
    // Locks while inserting data in the queue so that other threads cannot perform operations.
    ScopedLock locker(m_cs);

    if (m_size > m_usedCount)
    {
        s32 lastIndex = (m_firstIndex + m_usedCount) % m_size;
        m_ppBuffer[lastIndex] = data;
        m_usedCount++;

        // Wakes up thread waiting for data insertion.
        NotifyEnqueue();
        return true;
    }
    else
    {
        return false;
    }
}

template <class Locker>
bool BlockingQueueBase<Locker>::ForceEnqueue(uptr data, uptr* pOut)
{
    // Locks while inserting data in the queue so that other threads cannot perform operations.
    ScopedLock locker(m_cs);
    bool bReturn;
    s32 lastIndex = (m_firstIndex + m_usedCount) % m_size;
    if (m_size > m_usedCount)
    {
        m_usedCount++;
        bReturn = true;
    }
    else
    {
        if (pOut)
        {
            *pOut = m_ppBuffer[lastIndex];
        }
        m_firstIndex = (m_firstIndex + 1) % m_size;
        bReturn = false;
    }

    m_ppBuffer[lastIndex] = data;
    // Wakes up thread waiting for data insertion.
    NotifyEnqueue();
    return bReturn;
}

template <class Locker>
void BlockingQueueBase<Locker>::Enqueue(uptr data)
{
    // Updates the number of threads during the process to insert in queue.
    ++m_WaitingDequeueCount;
    for(;;)
    {
        if (TryEnqueue(data))
        {
            break;
        }

        // Waits until there is space in the queue.
        m_DequeueSemaphore.Acquire();
    }
    --m_WaitingDequeueCount;
}

template <class Locker>
bool BlockingQueueBase<Locker>::TryJam(uptr data)
{
    // Locks while inserting data in the queue so that other threads cannot perform operations.
    ScopedLock locker(m_cs);

    if (m_size > m_usedCount)
    {
        m_firstIndex = (m_firstIndex + m_size - 1) % m_size;
        m_ppBuffer[m_firstIndex] = data;
        m_usedCount++;

        // Wakes up thread waiting for data insertion.
        NotifyEnqueue();
        return true;
    }
    else
    {
        return false;
    }
}

template <class Locker>
void BlockingQueueBase<Locker>::Jam(uptr data)
{
    // Updates the number of threads during the process to insert in queue.
    ++m_WaitingDequeueCount;
    for(;;)
    {
        if (TryJam(data))
        {
            break;
        }

        // Waits until there is space in the queue.
        m_DequeueSemaphore.Acquire();
    }
    --m_WaitingDequeueCount;
}

template <class Locker>
bool BlockingQueueBase<Locker>::TryDequeue(uptr* pOut)
{
    // Locks while retrieving data from the queue so that other threads cannot perform operations.
    ScopedLock locker(m_cs);

    if (0 < m_usedCount)
    {
        *pOut = m_ppBuffer[m_firstIndex];
        m_firstIndex = (m_firstIndex + 1) % m_size;
        m_usedCount--;

        // Wakes up the thread waiting for a space in the queue.
        NotifyDequeue();
        return true;
    }
    else
    {
        return false;
    }
}

template <class Locker>
uptr BlockingQueueBase<Locker>::Dequeue()
{
    // Updates the number of threads during the process to retrieve data from the queue.
    ++m_WaitingEnqueueCount;
    uptr data;
    for(;;)
    {
        if (TryDequeue(&data))
        {
            break;
        }

        // Waits when the queue content is empty.
        m_EnqueueSemaphore.Acquire();
    }
    --m_WaitingEnqueueCount;
    return data;
}

template <class Locker>
bool BlockingQueueBase<Locker>::TryGetFront(uptr* pOut) const
{
    // Locks while retrieving data from the queue so that other threads cannot perform operations.
    ScopedLock locker(m_cs);

    if (0 < m_usedCount)
    {
        *pOut = m_ppBuffer[m_firstIndex];

        return true;
    }
    else
    {
        return false;
    }
}

template <class Locker>
uptr BlockingQueueBase<Locker>::GetFront() const
{
    // Updates the number of threads during the process to retrieve data from the queue.
    ++m_WaitingEnqueueCount;
    uptr data;
    for(;;)
    {
        if (TryGetFront(&data))
        {
            break;
        }

        // Waits when the queue content is empty.
        m_EnqueueSemaphore.Acquire();
    }
    --m_WaitingEnqueueCount;
    return data;
}

template class BlockingQueueBase<nn::os::CriticalSection>;
template class BlockingQueueBase<nn::os::Mutex>;

} // namespace detail

}} // namespace nn::os


#include <new>

using namespace nn::os;

extern "C" {

void nnosBlockingQueueInitialize(nnosBlockingQueue* this_, uptr buffer[], size_t size)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    new (pBlockingQueue) BlockingQueue();
    pBlockingQueue->Initialize(buffer, size);
}

bool nnosBlockingQueueTryInitialize(nnosBlockingQueue* this_, uptr buffer[], size_t size)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    new (pBlockingQueue) BlockingQueue();
    Result result = pBlockingQueue->TryInitialize(buffer, size);
    return result.IsSuccess();
}

void nnosBlockingQueueFinalize(nnosBlockingQueue* this_)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    pBlockingQueue->Finalize();
    pBlockingQueue->~BlockingQueue();
}

bool nnosBlockingQueueTryEnqueue(nnosBlockingQueue* this_, uptr data)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    return pBlockingQueue->TryEnqueue(data);
}

void nnosBlockingQueueEnqueue(nnosBlockingQueue* this_, uptr data)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    pBlockingQueue->Enqueue(data);
}

bool nnosBlockingQueueTryJam(nnosBlockingQueue* this_, uptr data)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    return pBlockingQueue->TryJam(data);
}

void nnosBlockingQueueJam(nnosBlockingQueue* this_, uptr data)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    pBlockingQueue->Jam(data);
}

bool nnosBlockingQueueTryDequeue(nnosBlockingQueue* this_, uptr* pOut)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    return pBlockingQueue->TryDequeue(pOut);
}

uptr nnosBlockingQueueDequeue(nnosBlockingQueue* this_)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    return pBlockingQueue->Dequeue();
}

bool nnosBlockingQueueTryGetFront(nnosBlockingQueue* this_, uptr* pOut)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    return pBlockingQueue->TryGetFront(pOut);
}

uptr nnosBlockingQueueGetFront(nnosBlockingQueue* this_)
{
    BlockingQueue* pBlockingQueue = reinterpret_cast<BlockingQueue*>(this_);
    return pBlockingQueue->GetFront();
}

void nnosSafeBlockingQueueInitialize(nnosSafeBlockingQueue* this_, uptr buffer[], size_t size)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    new (pBlockingQueue) SafeBlockingQueue();
    pBlockingQueue->Initialize(buffer, size);
}

bool nnosSafeBlockingQueueTryInitialize(nnosSafeBlockingQueue* this_, uptr buffer[], size_t size)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    new (pBlockingQueue) SafeBlockingQueue();
    Result result = pBlockingQueue->TryInitialize(buffer, size);
    return result.IsSuccess();
}

void nnosSafeBlockingQueueFinalize(nnosSafeBlockingQueue* this_)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    pBlockingQueue->Finalize();
    pBlockingQueue->~SafeBlockingQueue();
}

bool nnosSafeBlockingQueueTryEnqueue(nnosSafeBlockingQueue* this_, uptr data)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    return pBlockingQueue->TryEnqueue(data);
}

void nnosSafeBlockingQueueEnqueue(nnosSafeBlockingQueue* this_, uptr data)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    pBlockingQueue->Enqueue(data);
}

bool nnosSafeBlockingQueueTryJam(nnosSafeBlockingQueue* this_, uptr data)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    return pBlockingQueue->TryJam(data);
}

void nnosSafeBlockingQueueJam(nnosSafeBlockingQueue* this_, uptr data)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    pBlockingQueue->Jam(data);
}

bool nnosSafeBlockingQueueTryDequeue(nnosSafeBlockingQueue* this_, uptr* pOut)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    return pBlockingQueue->TryDequeue(pOut);
}

uptr nnosSafeBlockingQueueDequeue(nnosSafeBlockingQueue* this_)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    return pBlockingQueue->Dequeue();
}

bool nnosSafeBlockingQueueTryGetFront(nnosSafeBlockingQueue* this_, uptr* pOut)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    return pBlockingQueue->TryGetFront(pOut);
}

uptr nnosSafeBlockingQueueGetFront(nnosSafeBlockingQueue* this_)
{
    SafeBlockingQueue* pBlockingQueue = reinterpret_cast<SafeBlockingQueue*>(this_);
    return pBlockingQueue->GetFront();
}

}
