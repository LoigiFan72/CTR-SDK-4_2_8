/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Event.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47812 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
  

    
*/

#ifndef NN_OS_OS_EVENT_H_
#define NN_OS_OS_EVENT_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/os/os_Synchronization.h>

#include <nn/util/util_Result.h>
#include <nn/os/os_ErrorHandlerSelect.h>

#ifdef __cplusplus

namespace nn{ namespace os {

/* Please see man pages for details 
    

    
*/
class EventBase : public InterruptEvent
{
protected:
    explicit EventBase(ResetType resetType);
    EventBase() {}
    ~EventBase() {}

    void        Initialize(ResetType resetType);
    nn::Result  TryInitialize(ResetType resetType);
    void        Finalize();
    void        Signal();
    void        ClearSignal();

private:
    Result TryInitializeImpl(ResetType resetType);
};

// In-line implementation

inline Result EventBase::TryInitializeImpl(ResetType resetType)
{
    Handle handle;
    NN_UTIL_RETURN_IF_FAILED(nn::svc::CreateEvent(&handle, resetType));
    this->SetHandle(handle);
    return ResultSuccess();
}

inline void EventBase::Initialize(ResetType resetType)
{
    NN_OS_ERROR_IF_FAILED(TryInitializeImpl(resetType));
}

inline nn::Result EventBase::TryInitialize(ResetType resetType)
{
    Result result = TryInitializeImpl(resetType);
    if (result.GetSummary() == Result::SUMMARY_OUT_OF_RESOURCE)
    {
        return result;
    }
    NN_OS_ERROR_IF_FAILED(result);
    return result;
}

inline void EventBase::Finalize()
{
    InterruptEvent::Finalize();
}

inline EventBase::EventBase(ResetType resetType)
{
    Initialize(resetType);
}

inline void EventBase::Signal()
{
    NN_OS_ERROR_IF_FAILED(nn::svc::SignalEvent(GetHandle()));
}

inline void EventBase::ClearSignal()
{
    NN_OS_ERROR_IF_FAILED(nn::svc::ClearEvent(GetHandle()));
}


/* Please see man pages for details 
    

    

            
            
            

            
            

            
            

            
            
            

            
            
            

            
            

    
*/
class Event : public EventBase
{
public:

    /* Please see man pages for details 
      
      
      
    */
    explicit Event(bool manualReset) : EventBase(manualReset ? RESET_TYPE_STICKY: RESET_TYPE_ONESHOT) {}
    
    /* Please see man pages for details 
      
                    
    */
    Event() {}
    
    /* Please see man pages for details 
      
      
      
    */
    void Initialize(bool manualReset) { EventBase::Initialize(manualReset ? RESET_TYPE_STICKY: RESET_TYPE_ONESHOT); }
    void Initialize(ResetType resetType) { EventBase::Initialize(resetType); }
    
    nn::Result TryInitialize(bool manualReset) { return EventBase::TryInitialize(manualReset ? RESET_TYPE_STICKY: RESET_TYPE_ONESHOT); }
    
    /* Please see man pages for details 
      
      
             
      
    */
    void Finalize() { EventBase::Finalize(); }
    
    /* Please see man pages for details 
      
    */
    ~Event() {}
    
    /* Please see man pages for details 
      
      
      
    */
    void Signal() { EventBase::Signal(); }
    
    /* Please see man pages for details 
      
      
      
    */
    void Wait() { EventBase::WaitOne(); }
    
    /* Please see man pages for details 
      
                    
                    
                    
                    
                    
      
      
      
      
    */
    bool Wait(nn::fnd::TimeSpan timeout) { return EventBase::WaitOne(timeout); }
    
    /* Please see man pages for details 
      
      
      
    */
    void ClearSignal() { EventBase::ClearSignal(); }

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
};

}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  
  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosEvent, nn::os::Event, 4, u32);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosEventToWaitObject, nnosEvent, nnosWaitObject);
NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(nnosWaitObjectToEvent, nnosWaitObject, nnosEvent);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosEventInitialize(nnosEvent* this_, bool manualReset);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosEventTryInitialize(nnosEvent* this_, bool manualReset);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosEventSignal(nnosEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosEventWaitSignal(nnosEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosEventTryWaitSignal(nnosEvent* this_, s64 nanoSecondsTimeout);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosEventClearSignal(nnosEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosEventFinalize(nnosEvent* this_);

/*  



*/

#endif

