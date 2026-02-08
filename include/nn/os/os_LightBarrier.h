/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightBarrier.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_LIGHTBARRIER_H_
#define NN_OS_OS_LIGHTBARRIER_H_

#ifdef __cplusplus

#include <nn/os/os_WaitableCounter.h>
#include <nn/assert.h>
#include <nn/WithInitialize.h>
#include <nn/util/detail/util_ScopedLockImpl.h>
#include <nn/util/util_NonCopyable.h>
#include <cstdlib>

namespace nn { namespace os {

/* Please see man pages for details 
    
    

    
*/

/*
  

  

                
                

                
                

                
                
                

 */
class LightBarrier : private nn::util::NonCopyable<LightBarrier>
{
private:
    struct IncrementIfLessThan_1
    {
        bool operator()(s32& x)
        {
            if( x < -1 )
            {
                ++x;
                return true;
            }
            else
            {
                return false;
            }
        }
    };

private:
    WaitableCounter     m_CounterPlus;
    WaitableCounter     m_CounterMinus;
    s32                 m_ReleaseCountAndSign;

public:
    //----------------------------------------
    //
    //

    /*
      

                    

                    

      

     */
    LightBarrier() {}

    /*
      

                    

                    

      

      

     */
    explicit LightBarrier(s32 numWait) { Initialize(numWait); }

    /*
      

      

      

     */
    void Initialize(s32 numWait)
    {
        NN_MIN_TASSERT_( numWait, 1 );

        *m_CounterPlus  = - numWait;
        *m_CounterMinus = - numWait;
        m_ReleaseCountAndSign = numWait;
    }

    /*
      

      

     */
    void Finalize() {}

    //

    //----------------------------------------
    //
    //

    /*
      

                    
                    

      

     */
    s32 GetReleaseCount() const { return std::abs(m_ReleaseCountAndSign); }

    /*
      

                    
                    

      

     */
    s32 GetNumOfWaiting() const
    {
        const s32 relCountAndSign = m_ReleaseCountAndSign;
        s32 minusRemain;
        s32 relCount;

        if( relCountAndSign > 0 )
        {
            minusRemain = *m_CounterPlus;
            relCount    = relCountAndSign;
        }
        else
        {
            minusRemain = *m_CounterMinus;
            relCount    = - relCountAndSign;
        }

        return (minusRemain == 0) ? 0: relCount + minusRemain;
    }

    //

    //----------------------------------------
    //
    //

    /*
      

                    
                    

      

     */
    void Await()
    {
        const s32 relCountAndSign = m_ReleaseCountAndSign;

        if( relCountAndSign > 0 )
        {
            AwaitImpl(&m_CounterPlus, &m_CounterMinus, relCountAndSign);
        }
        else
        {
            AwaitImpl(&m_CounterMinus, &m_CounterPlus, - relCountAndSign);
        }
    }

    //

private:
    void AwaitImpl(nn::os::WaitableCounter* pCur, nn::os::WaitableCounter* pNext, s32 relCount)
    {
        IncrementIfLessThan_1 updater;

        if( (*pCur)->AtomicUpdateConditional(updater) )
        {
            pCur->WaitIfLessThan(0);
        }
        else
        {
            m_ReleaseCountAndSign = - m_ReleaseCountAndSign;
            **pNext = - relCount;
            **pCur  = 0;
            pCur->SignalAll();
        }
    }
};


}} // namespace nn::os

#endif // __cplusplus

// TODO: Requires an API for C.

#endif  // ifndef NN_OS_OS_LIGHTBARRIER_H_
