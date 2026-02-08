/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Timer.h

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

#ifndef NN_OS_OS_TIMER_H_
#define NN_OS_OS_TIMER_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/fnd/fnd_TimeSpan.h>

#include <nn/util/util_Result.h>

#ifdef __cplusplus

namespace nn{ namespace os {

/* Please see man pages for details 
    

    
    
            
            

            
            
            
            
            
            
            
            

            
            
*/
class Timer : public WaitObject
{
public:
    
    /* Please see man pages for details 
      
               
      
               
      
        
     */
    explicit Timer(bool isManualReset);
    
    Timer() {}
    
    /* Please see man pages for details 
        

        
                                 
                                 
                                 

        
     */
    void Initialize(bool isManualReset);

    /* Please see man pages for details 
      
      
      
                                  
                                  
                                  

      
    */
    nn::Result TryInitialize(bool isManualReset);
    
    /* Please see man pages for details 
      
      
             
      
    */
    void Finalize() { WaitObject::Finalize(); }
    
    /* Please see man pages for details 
      
    */
    ~Timer() {}
    
    /* Please see man pages for details 
        
        
        

        
    */
    void StartOneShot(nn::fnd::TimeSpan timeSpan);

    /* Please see man pages for details 
        

        

        

        
    */
    void StartPeriodic(nn::fnd::TimeSpan first, nn::fnd::TimeSpan interval);
    
    /* Please see man pages for details 
        

        
    */
    void Signal();
    
    /* Please see man pages for details 
        

                    
                    

        
    */              
    void Wait() { this->WaitOne(); }
    
    /* Please see man pages for details 
        

        
    */
    void Stop();
    
    /* Please see man pages for details 
        
        
                    

        
    */
    void ClearSignal();

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
    
    Result TryInitializeImpl(bool isManualReset);
    void StartImpl(nn::fnd::TimeSpan first, nn::fnd::TimeSpan interval);

};

// In-line implementation

inline Result Timer::TryInitializeImpl(bool isManualReset)
{
    Handle handle;
    NN_UTIL_RETURN_IF_FAILED(nn::svc::CreateTimer(&handle, isManualReset));
    this->SetHandle(handle);
    return ResultSuccess();
}

inline void Timer::Initialize(bool isManualReset)
{
    NN_OS_ERROR_IF_FAILED(TryInitializeImpl(isManualReset));
}

inline nn::Result Timer::TryInitialize(bool isManualReset)
{
    Result result = TryInitializeImpl(isManualReset);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

inline Timer::Timer(bool isManualReset)
{
    Initialize(isManualReset);
}

inline void Timer::StartImpl(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval)
{
    NN_OS_ERROR_IF_FAILED(nn::svc::SetTimer(GetHandle(), initial.GetNanoSeconds(), interval.GetNanoSeconds()));
}

inline void Timer::StartPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval)
{
    NN_TASSERT_(interval > 0);
    this->StartImpl(initial, interval);
}

inline void Timer::StartOneShot(nn::fnd::TimeSpan initial)
{
    this->StartImpl(initial, 0);
}

inline void Timer::Signal()
{
    this->StartOneShot(0);
}

inline void Timer::Stop()
{
    NN_OS_ERROR_IF_FAILED(nn::svc::CancelTimer(GetHandle()));
}

inline void Timer::ClearSignal()
{
    NN_OS_ERROR_IF_FAILED(nn::svc::ClearTimer(GetHandle()));
}

}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  
  
*/

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosTimer, nn::os::Timer, 4, u32);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosTimerToWaitObject, nnosTimer, nnosWaitObject);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosWaitObjectToTimer, nnosWaitObject, nnosTimer);


/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerInitialize(nnosTimer* this_, bool isManualReset);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosTimerTryInitialize(nnosTimer* this_, bool isManualReset);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerStartPeriodic(nnosTimer* this_, s64 first, s64 interval);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerStartOneShot(nnosTimer* this_, s64 time);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerWait(nnosTimer* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerStop(nnosTimer* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerClearSignal(nnosTimer* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerFinalize(nnosTimer* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosTimerSignal(nnosTimer* this_);

/*  



*/

#endif

