/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightEvent.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_LIGHTEVENT_H_
#define NN_OS_OS_LIGHTEVENT_H_

#ifdef __cplusplus

#include <nn/os/os_WaitableCounter.h>
#include <nn/os/os_SimpleLock.h>
#include <nn/assert.h>
#include <nn/WithInitialize.h>
#include <nn/util/detail/util_ScopedLockImpl.h>
#include <nn/util/util_NonCopyable.h>

namespace nn { namespace os {

/* Please see man pages for details 
    
    

    
*/

/*
  

  

                
               

                
                
                

                

 */
class LightEvent : private nn::util::NonCopyable<LightEvent>
{
private:
    static const s32 SIGNALED_MANUAL        = 1;
    static const s32 SIGNALED_AUTO          = 0;
    static const s32 NOT_SIGNALED_AUTO      = -1;
    static const s32 NOT_SIGNALED_MANUAL    = -2;

private:
    WaitableCounter     m_Counter;
    SimpleLock          m_Lock;

public:
    //----------------------------------------
    //
    //

    /*
      

                    

                    

      

     */
    LightEvent(){}

    /*
      

                    

                    

                    
                    
                    
                    
                    

                    
                    
                    

      
                                    

      

     */
    explicit LightEvent(bool isManualReset)
    {
        Initialize(isManualReset);
    }

    /*
      

      
                                    

      

     */
    void Initialize(bool isManualReset);

    /*
      

      

     */
    void Finalize() {}

    //

    //----------------------------------------
    //
    //

    /*
      

                    
                    

                    
                    
                    

    
                    

     */
    bool IsSignaled() const { return *m_Counter >= 0; }

    /*
      

      
                    

     */
    bool IsManualReset() const
    {
        const s32 c = *m_Counter;
        return (c == SIGNALED_MANUAL) || (c == NOT_SIGNALED_MANUAL);
    }

    //

    //----------------------------------------
    //
    //

    /*
      

      

                    
                    

      
                    

     */
    bool TryWait();

    /*
      

      

                    
                    

                    
                    

      
      
                    

     */
    bool TryWait(fnd::TimeSpan timeout);

    /*
      

                    
                    

      

     */
    void Wait();

    /*
      

                    
                    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

      

     */
    void Signal();

    /*
      

                    
                    
                    
                    
                    

                    
                    

      

     */
    void Pulse();

    /*
      

      

     */
    void ClearSignal();

    //
};


}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  
  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosLightEvent, nn::os::LightEvent, 8, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightEventInitialize(nnosLightEvent* this_, bool isManualReset);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosLightEventIsSignaled(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosLightEventIsManualReset(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosLightEventTryWait(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightEventWait(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightEventSignal(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightEventPulse(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightEventClearSignal(nnosLightEvent* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightEventFinalize(nnosLightEvent* this_);

/*  



*/



#endif  // ifndef NN_OS_OS_LIGHTEVENT_H_
