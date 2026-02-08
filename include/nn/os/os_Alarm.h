/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Alarm.h

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

#ifndef NN_OS_OS_ALARM_H_
#define NN_OS_OS_ALARM_H_

#include <nn/os/os_ThreadPool.h>
#include <nn/os/os_Thread.h>
#include <nn/fnd/fnd_TimeSpan.h>
#include <nn/os/os_Timer.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/fnd/fnd_Interlocked.h>

typedef void (*nnosAlarmHandler)(void* param, bool cancelled);

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
  
*/
typedef void (*AlarmHandler)(void* param, bool cancelled);

/* Please see man pages for details 
    
           
           
    
    
*/
void InitializeAlarmSystem(s32 priority = 0);

/* Please see man pages for details 
    
           
           
    
    
    
*/
void InitializeAlarmSystem(s32 workerPriority, s32 waitPriority);

size_t GetRequiredMemorySizeForAlarmSystem(void);

/* Please see man pages for details 
    

    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
    
    
    
    
    
    
    
    

*/
class Alarm : private nn::os::QueueableWaitTask, private nn::util::NonCopyable<Alarm>
{
public:
    
    /* Please see man pages for details 
      
                    
    */
    Alarm() : m_Handler(0), m_Flags(Flags::Create(false, false, false)), m_Invoker(0) {}
    
    /* Please see man pages for details 
      
                    
                    
    */
    virtual ~Alarm();
    
    /* Please see man pages for details 
      
      
    */
    Result TryInitialize();
    
    /* Please see man pages for details 
      
      
    */
    void Initialize();
    
    /* Please see man pages for details 
      
                    
    */
    void Finalize();
    
    /* Please see man pages for details 
      
                    

      
      
      

      

    */
    void SetOneShot(nn::fnd::TimeSpan time, AlarmHandler handler, void* param);
    
    template <typename T>
    void SetOneShot(nn::fnd::TimeSpan time, void (*handler)(T* param, bool cancelled), T* param);
    
    /* Please see man pages for details 
      
                    
                    

      
      
      
      

      

    */
    void SetPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval, AlarmHandler handler, void* param);
    
    template <typename T>
    void SetPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval, void (*handler)(T* param, bool cancelled), T* param);

    /* Please see man pages for details 
      
                    

      
      
      

      

    */
    void SetPeriodic(nn::fnd::TimeSpan interval, AlarmHandler handler, void* param) { SetPeriodic(0, interval, handler, param); }
    
    template <typename T>
    void SetPeriodic(nn::fnd::TimeSpan interval, void (*handler)(T* param, bool cancelled), T* param);

    /* Please see man pages for details 
      

      

    */
    void Cancel();
    
    /* Please see man pages for details 
      
      
                    
                    
      
      
    */
    bool CanSet() const { return !m_Flags.Read().isSet; }
    
private:

    struct Flags
    {
        bool cancelled;
        bool isOneShot;
        bool isSet;
        NN_PADDING1;
        
        static Flags Create(bool cancelled, bool isOneShot, bool isSet)
        {
            Flags ret = { cancelled, isOneShot, isSet };
            return ret;
        }
    };
    
    struct CancelFunc;
    struct InvokeFunc;
    friend struct CancelFunc;
    friend struct InvokeFunc;

    volatile AlarmHandler m_Handler;
    void* volatile m_Parameter;
    nn::fnd::InterlockedVariable<Flags> m_Flags;
    IWaitTaskInvoker* m_Invoker;
    Timer m_Timer;
    
    virtual void Invoke();
    virtual nn::os::WaitObject* GetWaitObject();
};

template <typename T>
inline void Alarm::SetOneShot(nn::fnd::TimeSpan time, void (*handler)(T* param, bool cancelled), T* param)
{
    SetOneShot(time, reinterpret_cast<AlarmHandler&>(handler), reinterpret_cast<void*&>(param));
}

template <typename T>
inline void Alarm::SetPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval, void (*handler)(T*, bool), T* param)
{
    SetPeriodic(initial, interval, reinterpret_cast<AlarmHandler&>(handler), reinterpret_cast<void*&>(param));
}

template <typename T>
inline void Alarm::SetPeriodic(nn::fnd::TimeSpan interval, void (*handler)(T*, bool), T* param)
{
    SetPeriodic(interval, reinterpret_cast<AlarmHandler&>(handler), reinterpret_cast<void*&>(param));
}

}} // namespace nn::os

#endif // __cplusplus


// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosInitializeAlarmSystem(void);

/*  

*/


/* Please see man pages for details 
  
  
  
  
  
  

  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosAlarm, nn::os::Alarm, 28, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAlarmInitialize(nnosAlarm* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAlarmFinalize(nnosAlarm* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAlarmSetOneShot(nnosAlarm* this_, s64 time, nnosAlarmHandler handler, void* param);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAlarmSetPeriodic(nnosAlarm* this_, s64 initial, s64 interval, nnosAlarmHandler handler, void* param);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAlarmCancel(nnosAlarm* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosAlarmCanSet(const nnosAlarm* p);

/*  



*/

#endif
