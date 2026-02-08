/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightAlarm.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
    

    
*/

#ifndef NN_OS_OS_LIGHTALARM_H_
#define NN_OS_OS_LIGHTALARM_H_

#include <nn/os.h>
#include <nn/fnd/fnd_TimeSpan.h>
#include <nn/os/os_Timer.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/fnd/fnd_Interlocked.h>
#include <nn/fnd/fnd_LinkedList.h>

typedef void (*nnosLightAlarmHandler)(void* param, bool cancelled);

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
    
    
    
*/
typedef void (*LightAlarmHandler)(void* param, bool canceled);
void InitializeLightAlarmSystemImpl(uptr stackBottom, s32 priority = 0);

/* Please see man pages for details 
    
    
    
    
    
*/ 
template <typename Stack>
inline void InitializeLightAlarmSystem(Stack& stack, s32 priority = 0)
{
    InitializeLightAlarmSystemImpl(stack.GetStackBottom(), priority); 
}

/* Please see man pages for details 
    
*/
void FinalizeLightAlarmSystem();

/* Please see man pages for details 
    
           
           
*/

namespace detail {
// Class for saving data for LightAlarm registered to wait queue
class LightAlarmNode : public nn::fnd::IntrusiveLinkedList<LightAlarmNode>::Item
{
public:
    LightAlarmNode() : event(false), waiting(false) {}
    volatile LightAlarmHandler handler;  //Alarm handler
    LightEvent event;                    //Expression notification event
    void* volatile parameter;            //Alarm handler parameters
    bool  canceled;                      //Cancel flag
    bool  waiting;                       //Flag for alarm waiting to be set
    NN_PADDING2;
    NN_PADDING4;
    Tick  fire;                          //Expression tick count
    Tick  period;                        //Expression interval tick count
};
//Class for saving data for LightAlarms related to system
class LightAlarmSystem
{
public:
    Timer timer;
    Thread thread;
    nn::fnd::IntrusiveLinkedList<LightAlarmNode> list;
    bool initialized;
    NN_PADDING3;
    void SetTimer( Tick nowTick );
    void InsertAlarm( LightAlarmNode *pInsertNode, Tick nowTick );
};
} //namespace detail

/* Please see man pages for details 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
*/
class LightAlarm : private nn::util::NonCopyable<LightAlarm>
{
public:
    
    /* Please see man pages for details 
      
                    
    */
    LightAlarm(){};
    
    /* Please see man pages for details 
      
                    
    */
    virtual ~LightAlarm();
    
    /* Please see man pages for details 
      
    */
    void Initialize();
    
    /* Please see man pages for details 
      
                    
                    
    */
    void Finalize();
    
    /* Please see man pages for details 
      
                    

      
      
      

      

    */
    void SetOneShot(nn::fnd::TimeSpan time, LightAlarmHandler handler, void* param);
    
    template <typename T>
    void SetOneShot(nn::fnd::TimeSpan time, void (*handler)(T* param, bool cancelled), T* param);
    
    /* Please see man pages for details 
      
                    
                    

      
      
      
      

      

    */
    void SetPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval, LightAlarmHandler handler, void* param);
    
    template <typename T>
    void SetPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval, void (*handler)(T* param, bool cancelled), T* param);

    /* Please see man pages for details 
      
                    

      
      
      

      

    */
    void SetPeriodic(nn::fnd::TimeSpan interval, LightAlarmHandler handler, void* param) { SetPeriodic(0, interval, handler, param); }
    
    template <typename T>
    void SetPeriodic(nn::fnd::TimeSpan interval, void (*handler)(T* param, bool cancelled), T* param);

    /* Please see man pages for details 
      
      
                    
                    
                    

      

    */
    void Cancel();
    
    /* Please see man pages for details 
      
      
                    
                    
                    
      
      
    */
    bool CanSet();

    static nn::os::detail::LightAlarmSystem* s_System;

private:
    NN_PADDING4;
    nn::os::detail::LightAlarmNode m_LightAlarm;
};

template <typename T>
inline void LightAlarm::SetOneShot(nn::fnd::TimeSpan time, void (*handler)(T* param, bool cancelled), T* param)
{
    SetOneShot(time, reinterpret_cast<LightAlarmHandler&>(handler), reinterpret_cast<void*&>(param));
}

template <typename T>
inline void LightAlarm::SetPeriodic(nn::fnd::TimeSpan initial, nn::fnd::TimeSpan interval, void (*handler)(T*, bool), T* param)
{
    SetPeriodic(initial, interval, reinterpret_cast<LightAlarmHandler&>(handler), reinterpret_cast<void*&>(param));
}

template <typename T>
inline void LightAlarm::SetPeriodic(nn::fnd::TimeSpan interval, void (*handler)(T*, bool), T* param)
{
    SetPeriodic(interval, reinterpret_cast<LightAlarmHandler&>(handler), reinterpret_cast<void*&>(param));
}

namespace detail {
    //Debug Functions
    void InitializeLightAlarmSystemImplCore( uptr stackBottom, s32 priority, nn::os::detail::LightAlarmSystem* lightAlarmSystem );
    void FinalizeLightAlarmSystemImpl( nn::os::detail::LightAlarmSystem* lightAlarmSystem );
} //namespace detail

}} // namespace nn::os

#endif // __cplusplus


// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosInitializeLightAlarmSystem( uptr stackBottom, s32 priority );

/* Please see man pages for details 
  
*/


/* Please see man pages for details 
  
  
  
  
  
  


  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosLightAlarm, nn::os::LightAlarm, 56, u64);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightAlarmInitialize(nnosLightAlarm* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightAlarmFinalize(nnosLightAlarm* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightAlarmSetOneShot(nnosLightAlarm* this_, s64 time, nnosLightAlarmHandler handler, void* param);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightAlarmSetPeriodic(nnosLightAlarm* this_, s64 initial, s64 interval, nnosLightAlarmHandler handler, void* param);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosLightAlarmCancel(nnosLightAlarm* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosLightAlarmCanSet(
                                      nnosLightAlarm* p);

/* Please see man pages for details 
  

  
*/

#endif // NN_OS_OS_LIGHTALARM_H_
