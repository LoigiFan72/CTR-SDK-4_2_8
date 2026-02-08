/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Semaphore.h

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

#ifndef NN_OS_OS_SEMAPHORE_H_
#define NN_OS_OS_SEMAPHORE_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_ErrorHandlerSelect.h>

#include <nn/util/util_Result.h>
#include <nn/util/detail/util_ScopedLockImpl.h>

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
    

    

           
           
           

           
           

           

           

           
           
*/

class Semaphore : public InterruptEvent
{
public:

    /* Please see man pages for details 
      
      
                    
                    
      
      
      
    */
    Semaphore(s32 initialCount, s32 maxCount);
    
    /* Please see man pages for details 
      
      
    */
    Semaphore() {}
    
    /* Please see man pages for details 
      
      
      
      
      
      
    */
    void Initialize(s32 initialCount, s32 maxCount);

    /* Please see man pages for details 
      
      
      
      

      
    */
    nn::Result TryInitialize(s32 initialCount, s32 maxCount);

    /* Please see man pages for details 
      

                    
      
      
    */
    void Finalize() { InterruptEvent::Finalize(); }
    
    /* Please see man pages for details 
      
    */
    ~Semaphore() {}
    
    /* Please see man pages for details 
      
                    
                    
      
      
      
      
    */
    s32 Release(s32 releaseCount = 1);
    
    /* Please see man pages for details 
      

      
    */
    void Acquire() { this->WaitOne(); }
    
    /* Please see man pages for details 
      
                    
                    
      
      
      
      
    */
    bool TryAcquire(nn::fnd::TimeSpan timeout) { return this->WaitOne(timeout); }

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
    
    class ScopedLock;

private:
    
    Result TryInitializeImpl(s32 initialCount, s32 maxCount);
    
};

inline Result Semaphore::TryInitializeImpl(s32 initialCount, s32 maxCount)
{
    Handle handle;
    NN_UTIL_RETURN_IF_FAILED(nn::svc::CreateSemaphore(&handle, initialCount, maxCount));
    this->SetHandle(handle);
    return ResultSuccess();
}

inline void Semaphore::Initialize(s32 initialCount, s32 maxCount)
{
    NN_OS_ERROR_IF_FAILED(TryInitializeImpl(initialCount, maxCount));
}

inline nn::Result Semaphore::TryInitialize(s32 initialCount, s32 maxCount)
{
    Result result = TryInitializeImpl(initialCount, maxCount);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

inline Semaphore::Semaphore(s32 initialCount, s32 maxCount)
{
    Initialize(initialCount, maxCount);
}

inline s32 Semaphore::Release(s32 releaseCount)
{
    s32 ret;
    NN_OS_ERROR_IF_FAILED(nn::svc::ReleaseSemaphore(&ret, GetHandle(), releaseCount));
    return ret;
}

NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(Semaphore, Acquire(), Release());

}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  
  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosSemaphore, nn::os::Semaphore, 4, u32);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosSemaphoreToWaitObject, nnosSemaphore, nnosWaitObject);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosWaitObjectToSemaphore, nnosWaitObject, nnosSemaphore);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosSemaphoreInitialize(nnosSemaphore* this_, s32 initialCount, s32 maxCount);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosSemaphoreTryInitialize(nnosSemaphore* this_, s32 initialCount, s32 maxCount);

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosSemaphoreRelease(nnosSemaphore* this_, s32 releaseCount);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosSemaphoreAcquire(nnosSemaphore* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosSemaphoreTryAcquire(nnosSemaphore* this_, s64 nanoSeconds);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosSemaphoreFinalize(nnosSemaphore* this_);

/*  



*/

#endif
