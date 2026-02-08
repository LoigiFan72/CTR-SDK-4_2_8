/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_BlockingQueue.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_BLOCKINGQUEUE_H_
#define NN_OS_OS_BLOCKINGQUEUE_H_

#include <nn/os/os_LightSemaphore.h>
#include <nn/os/os_Mutex.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/fnd/fnd_Interlocked.h>
#include <nn/util/util_NonCopyable.h>

#ifdef __cplusplus

namespace nn { namespace os {

namespace detail {

/* Please see man pages for details 
    

    
*/
template <class Locker>
class BlockingQueueBase : private nn::util::NonCopyable<BlockingQueueBase<Locker> >
{
protected:
    BlockingQueueBase() {}
    BlockingQueueBase(uptr buffer[], size_t size) { Initialize(buffer, size); }
    ~BlockingQueueBase();
    void Initialize(uptr buffer[], size_t size);
    nn::Result TryInitialize(uptr buffer[], size_t size);
    void Finalize();
    void Enqueue(uptr data);
    bool TryEnqueue(uptr data);
    bool ForceEnqueue(uptr data, uptr* pOut);
    void Jam(uptr data);
    bool TryJam(uptr data);
    uptr Dequeue();
    bool TryDequeue(uptr* pOut);
    uptr GetFront() const;
    bool TryGetFront(uptr* pOut) const;
    
    // TODO: Decide on handling for these functions
    
    s32 GetWaitingEnqueueCount(void) const
        { return m_WaitingEnqueueCount; }

    s32 GetWaitingDequeueCount(void) const
        { return m_WaitingDequeueCount; }

    // Internal member accessor for testing
    s32 GetSize() const
        { return m_size; }
        
    s32 GetUsedCount() const
        { return m_usedCount; }
        
    s32 GetFirstIndex() const
        { return m_firstIndex; }

private:
    typedef typename Locker::ScopedLock ScopedLock;
    
    uptr*                   m_ppBuffer;			//
    mutable LightSemaphore  m_EnqueueSemaphore; //
    mutable LightSemaphore  m_DequeueSemaphore; //
    mutable Locker          m_cs;				//
    size_t                  m_size;             //
    s32                     m_firstIndex;       //
    s32                     m_usedCount;        //
    mutable nn::fnd::InterlockedVariable<s32> m_WaitingEnqueueCount; //
    mutable nn::fnd::InterlockedVariable<s32> m_WaitingDequeueCount; //
    
	//
    void NotifyEnqueue() const;

	//
    void NotifyDequeue() const;
};

}

/* Please see man pages for details 
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
*/
class BlockingQueue : private os::detail::BlockingQueueBase<nn::os::CriticalSection>
{
private:
    typedef os::detail::BlockingQueueBase<nn::os::CriticalSection> Base;
public:
    
    /* Please see man pages for details 
      
                    
                    
                    
                    
                    
                    
    */
    BlockingQueue() {}
    
    /* Please see man pages for details 
      
                    
                    

      
      
    */
    BlockingQueue(uptr buffer[], size_t size) : Base(buffer, size) {}
    
    /* Please see man pages for details 
      

                    
    */
    ~BlockingQueue() { Finalize(); }
    
    /* Please see man pages for details 
      

      
      
      
      
    */
    void Initialize(uptr buffer[], size_t size) { Base::Initialize(buffer, size); }
    
    /* Please see man pages for details 
      
      
                    

      
      
      
      
    */
    nn::Result TryInitialize(uptr buffer[], size_t size) { return Base::TryInitialize(buffer, size); }
    
    /* Please see man pages for details 
      
      
                    

      
    */
    void Finalize() { Base::Finalize(); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    

      

      
    */
    void Enqueue(uptr data) { Base::Enqueue(data); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    

      

      
    */
    bool TryEnqueue(uptr data) { return Base::TryEnqueue(data); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    

      

      
    */
    void Jam(uptr data) { Base::Jam(data); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    

      

      
    */
    bool TryJam(uptr data) { return Base::TryJam(data); }
    
    /* Please see man pages for details 
      
      
                    
                    
                    
                    
                    

      
    */
    uptr Dequeue() { return Base::Dequeue(); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    

      

      
    */
    bool TryDequeue(uptr* pOut) { return Base::TryDequeue(pOut); }
    
    /* Please see man pages for details 
      
      
                    
                    

      
    */
    uptr GetFront() const { return Base::GetFront(); }
    
    /* Please see man pages for details 
      
      
                    
                    
                    
      
      
      
    */
    bool TryGetFront(uptr* pOut) const { return Base::TryGetFront(pOut); }
    
    // TODO: For testing
    using Base::GetSize;
    using Base::GetUsedCount;
    using Base::GetFirstIndex;
    
};


/* Please see man pages for details 
    

    
    
           
           
*/
class SafeBlockingQueue : private os::detail::BlockingQueueBase<nn::os::Mutex>
{
private:
    typedef os::detail::BlockingQueueBase<nn::os::Mutex> Base;
public:
    
    /* Please see man pages for details 
      
                    
                    
    */
    SafeBlockingQueue() {}
    
    /* Please see man pages for details 
      
                    
                    

      
      
    */
    SafeBlockingQueue(uptr buffer[], size_t size) : Base(buffer, size) {}
    
    /* Please see man pages for details 
      

                    
    */
    ~SafeBlockingQueue() {}
    
    /* Please see man pages for details 
      

      
      
      
      
    */
    void Initialize(uptr buffer[], size_t size) { Base::Initialize(buffer, size); }
    
    /* Please see man pages for details 
      
      
                    

      
      
      
      
    */
    nn::Result TryInitialize(uptr buffer[], size_t size) { return Base::TryInitialize(buffer, size); }
    
    /* Please see man pages for details 
      
      
                    

      
    */
    void Finalize() { Base::Finalize(); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    

      

      
    */
    void Enqueue(uptr data) { Base::Enqueue(data); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    

      

      
    */
    bool TryEnqueue(uptr data) { return Base::TryEnqueue(data); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    

      

      
    */
    void Jam(uptr data) { Base::Jam(data); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    

      

      
    */
    bool TryJam(uptr data) { return Base::TryJam(data); }
    
    /* Please see man pages for details 
      
      
                    
                    
                    
                    
                    

      
    */
    uptr Dequeue() { return Base::Dequeue(); }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
                    

      

      
    */
    bool TryDequeue(uptr* pOut) { return Base::TryDequeue(pOut); }
    
    /* Please see man pages for details 
      
      
                    
                    

      
    */
    uptr GetFront() const { return Base::GetFront(); }
    
    /* Please see man pages for details 
      
      
                    
                    
                    
      
      
      
    */
    bool TryGetFront(uptr* pOut) const { return Base::TryGetFront(pOut); }
    
    // TODO: For testing
    using Base::GetSize;
    using Base::GetUsedCount;
    using Base::GetFirstIndex;
    
};

}}

#endif

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/


/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosBlockingQueue, nn::os::BlockingQueue, 40 + NN_OS_CRITICALSECTION_SIZE, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosBlockingQueueInitialize(nnosBlockingQueue* this_, uptr buffer[], size_t size);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosBlockingQueueTryInitialize(nnosBlockingQueue* this_, uptr buffer[], size_t size);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosBlockingQueueFinalize(nnosBlockingQueue* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosBlockingQueueTryEnqueue(nnosBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosBlockingQueueEnqueue(nnosBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosBlockingQueueTryJam(nnosBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosBlockingQueueJam(nnosBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosBlockingQueueTryDequeue(nnosBlockingQueue* this_, uptr* pOut);

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosBlockingQueueDequeue(nnosBlockingQueue* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosBlockingQueueTryGetFront(nnosBlockingQueue* this_, uptr* pOut);

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosBlockingQueueGetFront(nnosBlockingQueue* this_);

/*  



*/


/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosSafeBlockingQueue, nn::os::SafeBlockingQueue, 44, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosSafeBlockingQueueInitialize(nnosSafeBlockingQueue* this_, uptr buffer[], size_t size);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosSafeBlockingQueueTryInitialize(nnosSafeBlockingQueue* this_, uptr buffer[], size_t size);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosSafeBlockingQueueFinalize(nnosSafeBlockingQueue* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosSafeBlockingQueueTryEnqueue(nnosSafeBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  

*/
NN_EXTERN_C void nnosSafeBlockingQueueEnqueue(nnosSafeBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  

*/
NN_EXTERN_C bool nnosSafeBlockingQueueTryJam(nnosSafeBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  

*/
NN_EXTERN_C void nnosSafeBlockingQueueJam(nnosSafeBlockingQueue* this_, uptr data);

/* Please see man pages for details 
  

*/
NN_EXTERN_C bool nnosSafeBlockingQueueTryDequeue(nnosSafeBlockingQueue* this_, uptr* pOut);

/* Please see man pages for details 
  

*/
NN_EXTERN_C uptr nnosSafeBlockingQueueDequeue(nnosSafeBlockingQueue* this_);

/* Please see man pages for details 
  

*/
NN_EXTERN_C bool nnosSafeBlockingQueueTryGetFront(nnosSafeBlockingQueue* this_, uptr* pOut);

/* Please see man pages for details 
  

*/
NN_EXTERN_C uptr nnosSafeBlockingQueueGetFront(nnosSafeBlockingQueue* this_);


/*  



*/

#endif
