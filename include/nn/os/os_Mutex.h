/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Mutex.h

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

#ifndef NN_OS_OS_MUTEX_H_
#define NN_OS_OS_MUTEX_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/WithInitialize.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_ErrorHandlerSelect.h>

#include <nn/util/util_Result.h>
#include <nn/util/detail/util_ScopedLockImpl.h>

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
    

    

            
            
            
            
    
           
           

           
           
           
           
           
           

           
           

           
           
           
           

           
           

           

           
           
*/

class Mutex : public WaitObject
{
public:

    /* Please see man pages for details 
      
      
      
    */
    explicit Mutex(bool initialLocked);
    
    /* Please see man pages for details 
      
      
                    
                    
    */
    Mutex() {}
    
    /* Please see man pages for details 
      
    */
    Mutex(const nn::WithInitialize&);
    
    /* Please see man pages for details 
      
      
      
    */
    void Initialize(bool initialLocked = false);

    /* Please see man pages for details 
      
      
      

      
    */
    nn::Result TryInitialize(bool initialLocked = false);
    
    /* Please see man pages for details 
      
      
                    
      
    */
    void Finalize() { WaitObject::Finalize(); }
    
    /* Please see man pages for details 
      
    */
    ~Mutex() {}
    
    /* Please see man pages for details 
      
      
                    
                    

      
    */
    void Lock() { this->WaitOne(); }
    
    /* Please see man pages for details 
      
                    
                    
                    
                    
                    

      

      
    */
    bool TryLock(nn::fnd::TimeSpan timeout = 0) { return this->WaitOne(timeout); }
    
    /* Please see man pages for details 
      
      
                    
                    

      
    */
    void Unlock();

    /* Please see man pages for details 
        
        
    */
    class ScopedLock;

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

private:
    
    Result TryInitializeImpl(bool initialLocked);
    
};

// In-line implementation

inline Result Mutex::TryInitializeImpl(bool initialLocked)
{
    Handle handle;
    NN_UTIL_RETURN_IF_FAILED(nn::svc::CreateMutex(&handle, initialLocked));
    this->SetHandle(handle);
    return ResultSuccess();
}

inline void Mutex::Initialize(bool initialLocked)
{
    NN_OS_ERROR_IF_FAILED(TryInitializeImpl(initialLocked));
}

inline nn::Result Mutex::TryInitialize(bool initialLocked)
{
    Result result = TryInitializeImpl(initialLocked);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

inline Mutex::Mutex(bool initialLocked)
{
    Initialize(initialLocked);
}

inline Mutex::Mutex(const nn::WithInitialize&)
{
    Initialize(false);
}

inline void Mutex::Unlock()
{
    NN_OS_ERROR_IF_FAILED(nn::svc::ReleaseMutex(GetHandle()));
}

NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(Mutex, Lock(), Unlock());

}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  
  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosMutex, nn::os::Mutex, 4, u32);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosMutexToWaitObject, nnosMutex, nnosWaitObject);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosWaitObjectToMutex, nnosWaitObject, nnosMutex);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosMutexInitialize(nnosMutex* this_, bool initialLocked);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosMutexTryInitialize(nnosMutex* this_, bool initialLocked);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosMutexLock(nnosMutex* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosMutexTryLock(nnosMutex* this_, s64 timeout);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosMutexUnlock(nnosMutex* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosMutexFinalize(nnosMutex* this_);

/*  



*/

#endif /* NN_OS_IPC_OS_MUTEX_H_ */
