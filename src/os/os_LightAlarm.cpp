/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LightAlarm.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#include <nn/os.h>
#include <nn/assert.h>
#include <nn/config.h>
#include <nn/os/os_LightAlarm.h>
#include <nn/svc/svc_Stub.h>
#include <nn/os/os_ThreadPool.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/util/util_StaticAssert.h>
#include <new>

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::fnd;
using namespace nn::svc;
using namespace nn::os;
using namespace nn::os::detail;
using namespace nn::util;

#define TICK_BORDER 0x3FFFFFFFFFFFFFFF
#define CANCEL_WAIT_TIME 1

//Global Variable Declarations
namespace {//
    CriticalSection s_CriticalSection = WithInitialize();
    //Structure to generate stack region objects from the stack region bottom address.
    struct StackBufferAdapter
    {
        uptr stackBottom;
        StackBufferAdapter(uptr stackBottom) : stackBottom(stackBottom) {}
        uptr GetStackBottom() const { return stackBottom; }
    };
    //Define class for alarm system.
    nn::os::detail::LightAlarmSystem s_LightAlarmSystemCore;
}
//Definition of static member
nn::os::detail::LightAlarmSystem* LightAlarm::s_System;

namespace nn{ namespace os{

void LightAlarmSystem::SetTimer( Tick nowTick )
{
    {   //Sets first alarm timer of the queue.
        //This process performed with mutual exclusion.
        CriticalSection::ScopedLock locker(s_CriticalSection);
        LightAlarmNode* pSetNode = list.GetFront();
        if( pSetNode == NULL)
        {
            //No alarm, so stop timer.
            LightAlarm::s_System->timer.Stop();
            return;
        }
        //If the expression timeout has already elapsed when the timer is set
        Tick diff = pSetNode->fire - nowTick;
        if( diff < 0 )
        {   //The timer signal is sent immediately.
            LightAlarm::s_System->timer.Signal();
        }
        //If the GetSystemCurrent function tick value wraps around
        //The determination boundary value is set to TICK_BORDER.
        else if( diff >= TICK_BORDER )
        {
            //The timer signal is sent immediately.
            LightAlarm::s_System->timer.Signal();
        }
        else
        {
            LightAlarm::s_System->timer.StartOneShot( pSetNode->fire - nowTick );
        }
    }
}

void LightAlarmSystem::InsertAlarm( LightAlarmNode *pInsertNode, Tick nowTick )
{
    {   //Alarms are inserted into the queue in the expressed fire order. This process performed with mutual exclusion.
        CriticalSection::ScopedLock locker(s_CriticalSection);
        for(LightAlarmNode* pLightAlarm = list.GetFront(); pLightAlarm != NULL; pLightAlarm = list.GetNext(pLightAlarm))
        {
         
            //Searches for the insertion location as though the alarms are registered in the queue in expressed time order.
            //Confirms that the GetSystemCurrent function tick value does not wrap around.
            //The determination boundary value is set to TICK_BORDER.
            if( 0 <= pLightAlarm->fire - pInsertNode->fire
             && pLightAlarm->fire - pInsertNode->fire <= TICK_BORDER )
            {
                list.Insert(pLightAlarm, pInsertNode);
                //Sets the timer.
                LightAlarm::s_System->SetTimer( nowTick );
                return;
            }
        }
        list.PushBack(pInsertNode);   //When the expression is later than any of the alarms in the queue, the alarm is inserted at the end.
        //Sets the timer.
        LightAlarm::s_System->SetTimer( nowTick );
    }
}

static void LightAlarmThread()
{
    LightAlarmHandler handler;   //Variable for saving alarm handler
    void* parameter;   //Variable for saving alarm handler argument
    bool canceled;   //Alarm cancel flag
    while(true)
    {
        LightAlarm::s_System->timer.Wait();

        {   //Performs mutual exclusion until the the first node process in the queue finishes.
            CriticalSection::ScopedLock locker(s_CriticalSection);
            //If FinalizeLightAlarmSystem has been called
            if( LightAlarm::s_System->initialized == false )
            {
                break;
            }
            //Get the first node in the queue
            LightAlarmNode* pHeadNode = LightAlarm::s_System->list.PopFront();
            NN_TASSERTMSG_(pHeadNode, "There is no node.\n");
            //NULL is never entered for pHeadNode, so if this is NULL, process nothing.
            if( pHeadNode == NULL )
            {
                continue;
            }
            //Immediately before executing the handler, save the address to a local variable in order to prepare for the memory indicating the address written in pHeadNode to be in a state to be deallocated.
            //
            handler = pHeadNode->handler;
            parameter = pHeadNode->parameter;
            canceled = pHeadNode->canceled;

            if(pHeadNode->period == 0 || pHeadNode->canceled == true)
            {
                //When there is an alarm waiting to be set, a signal is sent to the expression notification event.
                if( pHeadNode->waiting == true)
                {
                    //
                    pHeadNode->event.Signal();
                }
                //Initialize the handler to express.
                pHeadNode->handler = NULL;
                //Initialize the cancel flag.
                pHeadNode->canceled = false;
                //When the next node exists, set the timer.
                LightAlarm::s_System->SetTimer(Tick::GetSystemCurrent());
            }
            //For periodic alarms
            else
            {
                //Set the next expression time, and insert the alarm in the queue again.
                pHeadNode->fire += pHeadNode->period;
                LightAlarm::s_System->InsertAlarm(pHeadNode, Tick::GetSystemCurrent());
                
                //When the next node exists, set the timer.
                LightAlarm::s_System->SetTimer(Tick::GetSystemCurrent());
            }
        }
        /*
            With the alarm handler, limit exclusive processing to a minimum.
        */
        (handler)(parameter,canceled);
    }
}

// Initializes the alarm system.
void nn::os::detail::InitializeLightAlarmSystemImplCore( uptr stackBottom, s32 priority, nn::os::detail::LightAlarmSystem* lightAlarmSystem )
{
    if(lightAlarmSystem->initialized == true)
    {
        return;
    }
    LightAlarm::s_System = lightAlarmSystem;
    LightAlarm::s_System->timer.Initialize(false);
    StackBufferAdapter stack(stackBottom);
    LightAlarm::s_System->thread.Start(LightAlarmThread, stack, priority);
    LightAlarm::s_System->initialized = true;
}

// Initializes the alarm system.
void InitializeLightAlarmSystemImpl( uptr stackBottom, s32 priority )
{
    InitializeLightAlarmSystemImplCore( stackBottom, priority, &s_LightAlarmSystemCore );
}

// Finalize the alarm system.
void nn::os::detail::FinalizeLightAlarmSystemImpl( nn::os::detail::LightAlarmSystem* lightAlarmSystem )
{
    if(LightAlarm::s_System->initialized == false)
    {
        return;
    }
    lightAlarmSystem->initialized = false;
    lightAlarmSystem->timer.Signal();
    lightAlarmSystem->thread.Join();
    lightAlarmSystem->thread.Finalize();
    lightAlarmSystem->timer.Finalize();
    lightAlarmSystem->list.Clear();    //Delete all elements in the queue.
}

// Finalize the alarm system.
void FinalizeLightAlarmSystem()
{
    nn::os::detail::FinalizeLightAlarmSystemImpl( &s_LightAlarmSystemCore );
}

void LightAlarm::Initialize(void)
{
    NN_TASSERTMSG_(LightAlarm::s_System->initialized, "Not called InitializeLightAlarmSystem.\n");
    m_LightAlarm.handler = NULL;   //Initialization of the alarm handler
    m_LightAlarm.canceled = false; //Initialization of the cancel flag
}

void LightAlarm::Finalize(void)
{
    //If an alarm is set
    if(CanSet() == false)
    {
        //Call the Cancel function.
        Cancel();
    }
}

LightAlarm::~LightAlarm(void) { this->Finalize(); }

// Set a one-shot alarm.
void LightAlarm::SetOneShot(TimeSpan time, LightAlarmHandler handler, void* p)
{
    //NN_TASSERTMSG_(CanSet(), "Alarm is already set.\n");
    if( CanSet() == false )
    {
        m_LightAlarm.waiting = true;
        m_LightAlarm.event.Wait();
        m_LightAlarm.waiting = false;
    }
    m_LightAlarm.handler = handler;
    m_LightAlarm.parameter = p;
    m_LightAlarm.fire = time + Tick::GetSystemCurrent();
    m_LightAlarm.period = static_cast<Tick>(0);
    LightAlarm::s_System->InsertAlarm(&m_LightAlarm, Tick::GetSystemCurrent());    //Register alarms in the queue
}

// Set a periodic alarm.
void LightAlarm::SetPeriodic(TimeSpan initial, TimeSpan interval, LightAlarmHandler handler, void* p)
{
    NN_TASSERTMSG_(CanSet(), "Alarm is already set.\n");
    NN_TASSERTMSG_(interval>0, "bad period specified.\n");
    
    m_LightAlarm.handler = handler;
    m_LightAlarm.parameter = p;
    m_LightAlarm.fire = initial + Tick::GetSystemCurrent();
    m_LightAlarm.period = interval;
    LightAlarm::s_System->InsertAlarm(&m_LightAlarm, Tick::GetSystemCurrent());    //Register alarms in the queue
}

// Cancel set alarms.
void LightAlarm::Cancel(void)
{
    {   //Process under mutual exclusion to process a queue.
        CriticalSection::ScopedLock locker(s_CriticalSection);
        //Confirm that an alarm to be canceled exists in the queue.
        LightAlarmNode* node = LightAlarm::s_System->list.GetFront();
        //Continue confirming of existence of alarms to be canceled until the end of the queue is reached.
        while( node != NULL )
        {
            //When an alarm to be canceled exists in the queue
            if(node == &m_LightAlarm)
            {
                break;
            }
            node = LightAlarm::s_System->list.GetNext(node);
        }
        //When an alarm to be canceled does not exist in the queue
        if(node == NULL)
        {
            return;
        }
        //When the node to delete is not at the start of the queue
        if( &m_LightAlarm != LightAlarm::s_System->list.GetFront() )
        {
            //Moves the canceled node to the start of the queue.
            LightAlarm::s_System->list.Erase( &m_LightAlarm );
            LightAlarm::s_System->list.PushFront( &m_LightAlarm );
        }
        //Enables the Canceled flag
        m_LightAlarm.canceled = true;
        //Sends a signal to the alarm thread timer
        LightAlarm::s_System->timer.Signal();
    }
    //Wait until alarm is executed.
    while( CanSet() == false )
    {
        Thread::Sleep(TimeSpan::FromMilliSeconds(CANCEL_WAIT_TIME));
    }
}

bool LightAlarm::CanSet(void)
{
    return !(m_LightAlarm.handler);
}

}} // namespace nn::os

#include <new>

using namespace nn::os;

extern "C" {

void nnosInitializeLightAlarmSystem( uptr stackBottom, s32 priority )
{
    nn::os::InitializeLightAlarmSystemImpl(stackBottom, priority);
}

void nnosLightAlarmInitialize(nnosLightAlarm* p)
{
    LightAlarm* this_ = new (p) LightAlarm;
    this_->Initialize();
}

void nnosLightAlarmFinalize(nnosLightAlarm* p)
{
    LightAlarm* pLightAlarm = reinterpret_cast<LightAlarm*>(p);
    pLightAlarm->~LightAlarm();
}

void nnosLightAlarmSetOneShot(nnosLightAlarm* p, s64 time, nnosLightAlarmHandler handler, void* param)
{
    LightAlarm* pLightAlarm = reinterpret_cast<LightAlarm*>(p);
    pLightAlarm->SetOneShot(nn::fnd::TimeSpan::FromNanoSeconds(time), handler, param);
}

void nnosLightAlarmSetPeriodic(nnosLightAlarm* p, s64 initial, s64 interval, nnosLightAlarmHandler handler, void* param)
{
    LightAlarm* pLightAlarm = reinterpret_cast<LightAlarm*>(p);
    pLightAlarm->SetPeriodic(nn::fnd::TimeSpan::FromNanoSeconds(initial), nn::fnd::TimeSpan::FromNanoSeconds(interval), handler, param);
}

void nnosLightAlarmCancel(nnosLightAlarm* p)
{
    LightAlarm* pLightAlarm = reinterpret_cast<LightAlarm*>(p);
    pLightAlarm->Cancel();
}

bool nnosLightAlarmCanSet(nnosLightAlarm* p)
{
    LightAlarm* pLightAlarm = reinterpret_cast<LightAlarm*>(p);
    return pLightAlarm->CanSet();
}

}
