/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightSemaphore.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_LIGHTSEMAPHORE_H_
#define NN_OS_OS_LIGHTSEMAPHORE_H_

#ifdef __cplusplus

#include <nn/os/os_WaitableCounter.h>
#include <nn/assert.h>
#include <nn/WithInitialize.h>
#include <nn/util/detail/util_ScopedLockImpl.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/config.h>

namespace nn { namespace os {

/* Please see man pages for details 
    
    

    
*/

/*
  

  

                
                
                

                
                
                

                

 */
class LightSemaphore : private nn::util::NonCopyable<LightSemaphore>
{
public:
    static const s32 MAX_MAX_COUNT  = 0x7fff;

private:
    struct DecrementIfPositive
    {
        bool operator()(s32& x)
        {
            if( x > 0 )
            {
                --x;
                return true;
            }
            else
            {
                return false;
            }
        }
    };
    struct LimitedAdd
    {
        s32 max;
        s32 value;
        s32 beforeUpdate;

        bool operator()(s32& x)
        {
            beforeUpdate = x;

            if( x > max - value )
            {
                x = max;
            }
            else
            {
                x += value;
            }

            return true;
        }
    };

private:
    WaitableCounter                 m_Counter;
#if NN_PLATFORM_HAS_16BIT_LL_SC
    fnd::InterlockedVariable<s16>   m_NumWaiting;
    s16                             m_Max;
#else
    fnd::InterlockedVariable<s32>   m_NumWaiting;
#endif


public:
    //----------------------------------------
    //
    //

    /*
      

                    
    
                    

     */
    LightSemaphore() {}

    /*
      

                    

                    

      
      
                                    

     */
    LightSemaphore(s32 initialCount, s32 maxCount) { Initialize(initialCount, maxCount); }

    LightSemaphore(s32 initialCount) { Initialize(initialCount); }

    /*
      

      
      
                                    

      

     */
    void Initialize(s32 initialCount, s32 maxCount)
    {
        NN_MIN_TASSERT_( initialCount, 0 );
        NN_MIN_TASSERT_( maxCount, 1 );
        NN_MAX_TASSERT_( initialCount, maxCount );
        NN_MAX_TASSERT_( maxCount, MAX_MAX_COUNT );

        *m_Counter      = initialCount;
        m_NumWaiting    = 0;
#if NN_PLATFORM_HAS_16BIT_LL_SC
        m_Max           = maxCount;
#else
        NN_UNUSED_VAR(maxCount);
#endif
    }
    void Initialize(s32 initialCount) { Initialize(initialCount, MAX_MAX_COUNT); }

    /*
      

      

     */
    void Finalize() {}

    //

    //----------------------------------------
    //
    //

    /*
      
                    

      

     */
#if NN_PLATFORM_HAS_16BIT_LL_SC
    s32  GetMax()   const { return m_Max; }
#endif

    /*
      

      

     */
    s32  GetCount() const { return *m_Counter; }

    //

    //----------------------------------------
    //
    //

    /*
      

                    
                    

      

     */
    void Acquire()
    {
        while( ! TryAcquire() )
        {
            ++m_NumWaiting;
            m_Counter.WaitIfLessThan(1);
            --m_NumWaiting;
        }
    }

    /*
      

      

                    

      
                    

     */
    bool TryAcquire()
    {
        DecrementIfPositive updater;
        return m_Counter->AtomicUpdateConditional(updater);
    }

    /*
      

      

                    
                    

                    
                    

      
      
                    

     */
    bool TryAcquire(fnd::TimeSpan timeout);

    /*
      

                    
                    
                    

                    
                    
                    
                    
                    

                    

      
                                    
                                    

      

     */
    s32 Release(s32 releaseCount = 1);

    //
    
    class ScopedAcquire
    {
    private:
        LightSemaphore* m_Semaphore;
    public:
        ScopedAcquire(LightSemaphore& semaphore, bool wait = true)
            : m_Semaphore(wait ? (semaphore.Acquire(), &semaphore) : (semaphore.TryAcquire() ? &semaphore : 0)) {}
        bool Aquired() const { return m_Semaphore != 0; }
        void Detach() { this->m_Semaphore = 0; }
        ~ScopedAcquire() { if (m_Semaphore) { m_Semaphore->Release(); } }
    };
};


}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  
  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosLightSemaphore, nn::os::LightSemaphore, 8, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightSemaphoreInitialize(nnosLightSemaphore* this_, s32 initialCount, s32 maxCount);

#if NN_PLATFORM_HAS_16BIT_LL_SC
/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosLightSemaphoreGetMax(nnosLightSemaphore* p);
#endif

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosLightSemaphoreGetCount(nnosLightSemaphore* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosLightSemaphoreRelease(nnosLightSemaphore* this_, s32 releaseCount);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightSemaphoreAcquire(nnosLightSemaphore* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosLightSemaphoreTryAcquire(nnosLightSemaphore* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightSemaphoreFinalize(nnosLightSemaphore* this_);

/*  



*/

#endif  // ifndef NN_OS_OS_LIGHTSEMAPHORE_H_
