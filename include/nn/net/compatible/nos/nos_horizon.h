/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nos_horizon.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/Handle.h>
#include <nn/os.h>
#include <nn/os/os_Thread.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/os/os_LightAlarm.h>
#include <nn/os/os_Tick.h>
#include <nn/net/osl/osl_EventFlag.h>
#include <nn/net/osl/osl_Mbuf.h>
#include <nn/net/compatible/nlib.h>
#include <nn/net/compatible/ndebug.h>

#ifndef NN_NET_OSL_OSL_COMPATIBLE_H_
#define NN_NET_OSL_OSL_COMPATIBLE_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * System dependency arguments
 *
 *  When calling the system allocator, specify one of the following as the align size for each module. 
 * 
 * Define the value as appropriate.
 */
#define NOS_MEM_ALIGN_STRUCT_SAFE      8    /* Please see man pages for details */
#define NOS_MEM_ALIGN_4                4    /* Please see man pages for details */
#define NOS_MEM_ALIGN_STACK            8    /* Please see man pages for details */

#define NN_INLINE   extern __inline
#define BOOL        s32
#define TRUE        1
#define FALSE       0

typedef void (*nnosThreadFunc)(uptr param);

/* thread */

/* Please see man pages for details 
 
 */
typedef nnosThread NOSThread;

/* Please see man pages for details 
 
 
 
 
 */
typedef nnosThread *NOSThreadId;

/* Please see man pages for details 
 
 */
typedef nnosEvent NOSThreadQueue;

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE NOSThreadId NOS_CreateAndStartThread(
     NOSThread*   thread,
     void        (*func)(void*),
     void*       arg,
     void*       stack,
     u32         stackSize,
     u32         prio )
{
    NN_UNUSED_VAR(stackSize);
    bool result = nnosThreadTryInitializeAndStart(thread, (nnosThreadFunc)func, (uptr)arg, (uptr)stack, prio, NN_OS_CORE_NO_USE_PROCESS_VALUE);
    if (!result)
    {
        return 0;
    }
    return (NOSThreadId)thread;
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_JoinAndDestroyThread(NOSThreadId threadId)
{
    nnosThreadJoin(threadId);
    nnosThreadFinalize(threadId);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE NOSThreadId NOS_CreateThread(
     NOSThread*   thread,
     void        (*func)(void*),
     void*       arg,
     void*       stack,
     u32         stackSize,
     u32         prio )
{
    NN_UNUSED_VAR(stackSize);
    bool result = nnosThreadTryInitializeAndStart(thread, (nnosThreadFunc)func, (uptr)arg, (uptr)stack, prio, NN_OS_CORE_NO_USE_PROCESS_VALUE);
    if (!result)
    {
        return 0;
    }
    return (NOSThreadId)thread;
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_DestroyThread(NOSThreadId threadId)
{
    // Do not destroy threads that have not been terminated.
    nnosThreadJoin(threadId);
    nnosThreadFinalize(threadId);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE NOSThreadId NOS_GetCurrentThread(void)
{
    return (NOSThreadId)nnosThreadGetCurrentId();
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_WakeupThreadDirect(NOSThreadId threadId)
{
    NN_UNUSED_VAR(threadId);
    return;
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_InitThreadQueue(NOSThreadQueue* queue)
{
    nnosEventInitialize(queue, TRUE);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_WakeupThread(NOSThreadQueue* queue)
{
    nnosEventSignal(queue);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_SleepThread(NOSThreadQueue* queue)
{
    // This thread is not permitted to sleep without using a synchronized object
    NN_TASSERT_(queue != NULL);
    nnosEventClearSignal(queue);
    nnosEventWaitSignal(queue);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_JoinThread(NOSThreadId threadId)
{
    nnosThreadJoin(threadId);
}


/* Sleep. */

/* Please see man pages for details 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_Sleep(u32 msec)
{
    nnosThreadSleep((s64)msec*1000000 + 1);
}

NN_INLINE void NOS_YieldThread(void)
{
    nnosThreadYield();
}

/* mutex */

/* Please see man pages for details 
 
 */
typedef nnosCriticalSection NOSMutex;

/* Please see man pages for details 
 
 
 
 
 
 */
typedef nnosCriticalSection *NOSMutexId;

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE NOSMutexId NOS_CreateMutex(NOSMutex *m)
{
    NN_ASSERT(m != NULL);
    bool result = nnosCriticalSectionTryInitialize(m);
    if (!result)
    {
        return 0;
    }
    return (NOSMutexId)m;
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_DestroyMutex(NOSMutexId mutexId)
{
    NN_ASSERT(mutexId != NULL);
    nnosCriticalSectionFinalize(mutexId);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_LockMutex(NOSMutexId mutexId)
{
    NN_ASSERT(mutexId != NULL);
    nnosCriticalSectionEnter(mutexId);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_UnlockMutex(NOSMutexId mutexId)
{
    NN_ASSERT(mutexId != NULL);
    nnosCriticalSectionLeave(mutexId);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE BOOL NOS_TryLockMutex(NOSMutexId mutexId)
{
    NN_ASSERT(mutexId != NULL);
    return nnosCriticalSectionTryEnter(mutexId);
}

/* tick */

/* Please see man pages for details 
 
 
 
 
 */
typedef u64 NOSTick;

/* Please see man pages for details 
 
 
 
 
 
 
 
 */
NN_INLINE NOSTick NOS_GetTick(void)
{
    return (NOSTick)(nnosTickGetSystemCurrent() << 1);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 */        
NN_INLINE s64 NOS_CmpTick(NOSTick a, NOSTick b)
{
    return (s64)(a - b);
}


NN_INLINE s64 NOS_TicksToSeconds(s64 tick)
{
    return nnosTickConvertToSeconds(tick >> 1);
}
NN_INLINE s64 NOS_TicksToMilliSeconds(s64 tick)
{
    return nnosTickConvertToMilliSeconds(tick >> 1);
}
NN_INLINE s64 NOS_TicksToMicroSeconds(s64 tick)
{
    return nnosTickConvertToMicroSeconds(tick >> 1);
}
NN_INLINE s64 NOS_TicksToNanoSeconds(s64 tick)
{
    return nnosTickConvertToNanoSeconds(tick >> 1);
}
NN_INLINE NOSTick NOS_SecondsToTicks(s64 s)
{
    return nnosTickConvertFromSeconds(s) << 1;
}
NN_INLINE NOSTick NOS_MilliSecondsToTicks(s64 ms)
{
    return nnosTickConvertFromMilliSeconds(ms) << 1;
}
NN_INLINE NOSTick NOS_MicroSecondsToTicks(s64 ms)
{
    return nnosTickConvertFromMicroSeconds(ms) << 1;
}
NN_INLINE NOSTick NOS_NanoSecondsToTicks(s64 ns)
{
    return nnosTickConvertFromNanoSeconds(ns) << 1;
}   

/* messagequeue */

#define  NOS_MESSAGE_NOBLOCK   0
#define  NOS_MESSAGE_BLOCK     1

/* Please see man pages for details 
 
 */
typedef nnosBlockingQueue NOSMessageQueue;

/* Please see man pages for details 
 
 */
typedef nnosBlockingQueue *NOSMessageQueueId;

/* Please see man pages for details 
 
 */
typedef uptr NOSMessage;

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE NOSMessageQueueId NOS_CreateMessageQueue(NOSMessageQueue *mq, NOSMessage *msgArray, s32 msgCount)
{
    bool result = nnosBlockingQueueTryInitialize(mq, msgArray, msgCount);
    if (!result)
    {
        return 0;
    }
    return (NOSMessageQueueId)mq;
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_DestroyMessageQueue(NOSMessageQueueId mqId)
{
    nnosBlockingQueueFinalize(mqId);
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE BOOL NOS_ReceiveMessage(NOSMessageQueueId mqId, NOSMessage *msg, s32 flag)
{
    if (flag == NOS_MESSAGE_BLOCK)
    {
        *msg = nnosBlockingQueueDequeue(mqId);
        return TRUE;
    }
    else
    {
        return nnosBlockingQueueTryDequeue(mqId, msg);
    }
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE BOOL NOS_SendMessage(NOSMessageQueueId mqId, NOSMessage msg, s32 flag)
{
    if (flag == NOS_MESSAGE_BLOCK)
    {
        nnosBlockingQueueEnqueue(mqId, msg);
        return TRUE;
    }
    else
    {
        return nnosBlockingQueueTryEnqueue(mqId, msg);
    }
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE BOOL NOS_ReadMessage(NOSMessageQueueId mqId, NOSMessage *msg, s32 flag)
{
    if (flag == NOS_MESSAGE_BLOCK)
    {
        *msg = nnosBlockingQueueGetFront(mqId);
        return TRUE;
    }
    else
    {
        return nnosBlockingQueueTryGetFront(mqId, msg);
    }
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE BOOL NOS_JamMessage(NOSMessageQueueId mqId, NOSMessage msg, s32 flag)
{
    if (flag == NOS_MESSAGE_BLOCK)
    {
        nnosBlockingQueueJam(mqId, msg);
        return TRUE;
    }
    else
    {
        return nnosBlockingQueueTryJam(mqId, msg);
    }
}

typedef void (*NOSAlarmHandler) (void *);     /* Please see man pages for details */

/* Please see man pages for details 
 
 */
typedef struct NOSAlarm
{
    nnosLightAlarm      alarm;
    NOSAlarmHandler     handler;
    void*               arg;
} NOSAlarm;
/* Please see man pages for details 
 
 */
typedef NOSAlarm *NOSAlarmId;

/* NOS_alarm.c */
NN_INLINE s32 NOS_InitAlarm(void){ return 0; }

NOSAlarmId NOS_CreateAlarm(NOSAlarm *pAlarm);
s32 NOS_SetAlarm(NOSAlarmId alarmId, NOSTick tick, NOSAlarmHandler callback, void *arg);
s32 NOS_CancelAlarm(NOSAlarmId alarmId);
void NOS_DestroyAlarm(NOSAlarmId alarmId);
s32 NOS_SetPeriodicAlarm(NOSAlarmId alarmId, NOSTick start, NOSTick period, NOSAlarmHandler callback, void *arg);


typedef struct
{
    nnnetOslEventFlag   eventFlag;
    NLIBLink            link;
    s32                 priority;
} NOSEvent;
typedef NOSEvent *NOSEventId;

#define NOS_TMO_FEVR    0xffffffffffffffff

typedef enum
{
    NOS_EVENT_MODE_AND = NN_NET_OSL_WAITMODE_AND,
    NOS_EVENT_MODE_OR  = NN_NET_OSL_WAITMODE_OR
}
NOSEventMode;

NN_INLINE NOSEventId NOS_CreateEvent(NOSEvent* pEvent)
{
    bool result = nnnetOslEventFlagTryInitialize(&pEvent->eventFlag);
    if (!result)
    {
        return 0;
    }
    return (NOSEventId)pEvent;
}

NN_INLINE void NOS_DestroyEvent(NOSEventId eventId)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    nnnetOslEventFlagFinalize(&pEvent->eventFlag);
}

NN_INLINE u32 NOS_WaitEvent(NOSEventId eventId, u32 pattern, NOSEventMode mode)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitSignal(&pEvent->eventFlag, pattern, (nnnetOslWaitMode)mode, NN_OS_WAIT_INFINITE);
}

NN_INLINE u32 NOS_WaitEvent_And(NOSEventId eventId, u32 pattern)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitSignal(&pEvent->eventFlag, pattern, NN_NET_OSL_WAITMODE_AND, NN_OS_WAIT_INFINITE);
}

NN_INLINE u32 NOS_WaitEvent_Or(NOSEventId eventId, u32 pattern)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitSignal(&pEvent->eventFlag, pattern, NN_NET_OSL_WAITMODE_OR, NN_OS_WAIT_INFINITE);
}

NN_INLINE u32 NOS_WaitEventEx(NOSEventId eventId, u32 pattern, NOSEventMode mode, u32 clearBit)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitAndClear(&pEvent->eventFlag, pattern, (nnnetOslWaitMode)mode, clearBit, NN_OS_WAIT_INFINITE);
}

NN_INLINE u32 NOS_WaitEventEx_And(NOSEventId eventId, u32 pattern, u32 clearBit)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitAndClear(&pEvent->eventFlag, pattern, NN_NET_OSL_WAITMODE_AND, clearBit, NN_OS_WAIT_INFINITE);
}

NN_INLINE u32 NOS_WaitEventEx_Or(NOSEventId eventId, u32 pattern, u32 clearBit)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitAndClear(&pEvent->eventFlag, pattern, NN_NET_OSL_WAITMODE_OR, clearBit, NN_OS_WAIT_INFINITE);
}

NN_INLINE void NOS_SignalEvent(NOSEventId eventId, u32 setPattern)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    nnnetOslEventFlagSignal(&pEvent->eventFlag, setPattern);
}

NN_INLINE u32 NOS_PollEvent(NOSEventId eventId, u32 pattern, NOSEventMode mode)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    return nnnetOslEventFlagWaitSignal(&pEvent->eventFlag, pattern, (nnnetOslWaitMode)mode, 0);
}

NN_INLINE void NOS_ClearEvent(NOSEventId eventId, u32 clearBit)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    nnnetOslEventFlagClearSignal(&pEvent->eventFlag, clearBit);
}

NN_INLINE void NOS_ClearAllEvent(NOSEventId eventId)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    nnnetOslEventFlagClearSignal(&pEvent->eventFlag, 0xffffffff);
}

NN_INLINE u32 NOS_TimeWaitEventEx(NOSEventId eventId, u32 pattern, NOSEventMode mode, u32 clearBit, NOSTick timeout)
{
    NOSEvent* pEvent = (NOSEvent*)eventId;
    if (timeout != NOS_TMO_FEVR)
    {
        return nnnetOslEventFlagWaitAndClear(&pEvent->eventFlag, pattern, (nnnetOslWaitMode)mode, clearBit, NOS_TicksToNanoSeconds(timeout));
    }
    else
    {
        return nnnetOslEventFlagWaitAndClear(&pEvent->eventFlag, pattern, (nnnetOslWaitMode)mode, clearBit, NN_OS_WAIT_INFINITE);
    }
}

/* EventQueue */

typedef NLIBQueue NOSEventQueue;
typedef NOSEventQueue *NOSEventQueueId;

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE NOSEventQueueId NOS_CreateEventQueue(NOSEventQueue *eq)
{
	NLIB_Queue_Init((NLIBQueue *)eq);
    return (NOSEventQueueId)eq;
}

/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 */
NN_INLINE void NOS_DestroyEventQueue(NOSEventQueueId eqId)
{
    NN_UNUSED_VAR(eqId)
    ;
}
extern void NOS_EnqueueEventQueue(NOSEventQueueId queueId, NOSEventId eventId);
extern void NOS_DequeueEventQueue(NOSEventQueueId queueId, NOSEventId eventId);
extern void NOS_SignalEventQueue(NOSEventQueueId queueId, u32 pattern);


/* mbuf */

//#define NOS_MBUF_SIZE       NN_NET_OSL_MBUF_DATA_SIZE   /**< Data size to put in a single mbuf */
//#define NOS_MBUF_NUM        512     /**< number of mbufs */

#define NOS_M_BCAST         NN_NET_OSL_M_BCAST
#define NOS_M_MCAST         NN_NET_OSL_M_MCAST
#define NOS_M_LOOPBACK      NN_NET_OSL_M_LOOPBACK

#define NOS_M_DONTWAIT      0       /* Please see man pages for details */
#define NOS_M_WAIT          1       /* Please see man pages for details */
#define NOS_M_FREELIST      0x8000  /* Please see man pages for details */

#define NOS_MT_DATA         1       /* Please see man pages for details */

#define NOS_MBUF_ADDR_SIZE  6       /* Please see man pages for details */

#define NOS_M_CAT_NWCM      0x01    /* Please see man pages for details */
#define NOS_M_CAT_NWMETH    0x01    /* Please see man pages for details */
#define NOS_M_CAT_ARP       0x02    /* Please see man pages for details */
#define NOS_M_CAT_ICMPERR   0x03    /* Please see man pages for details */
#define NOS_M_CAT_ICMPECHO  0x04    /* Please see man pages for details */
#define NOS_M_CAT_IGMP      0x05    /* Please see man pages for details */
#define NOS_M_CAT_IPREASM   0x06    /* Please see man pages for details */
#define NOS_M_CAT_IPFRAG    0x07    /* Please see man pages for details */
#define NOS_M_CAT_TCPRESP   0x08    /* Please see man pages for details */
#define NOS_M_CAT_TCPSEND   0x09    /* Please see man pages for details */
#define NOS_M_CAT_UDP       0x0a    /* Please see man pages for details */
#define NOS_M_CAT_NDP       0x0b    /* Please see man pages for details */
#define NOS_M_CAT_MLD       0x0c    /* Please see man pages for details */

#define NOS_M_CAT_PPPOE     0x81    /* Please see man pages for details */
#define NOS_M_CAT_PPP       0x82    /* Please see man pages for details */

#ifdef NDEBUG_ENABLE
#define NOS_M_OWN_NSOC      0x02    /* NSOC is in use */
#define NOS_M_OWN_NPOE      0x03    /* NPOE is in use */
#define NOS_M_OWN_NPPP      0x04    /* NPPP is in use */
#endif

typedef nnnetOslMbuf NOSMessageBuf;

#define NOS_mtod(m, t)  ((t)(nnnetOslMbuf_tod(m)))

NN_EXTERN_C s32 NOS_m_init(void);

NN_EXTERN_C NOSMessageBuf* NOS_m_getm(u32 name, NOSMessageBuf *orig, s32 len, s32 how, u8 type);

NN_INLINE void NOS_m_freem(NOSMessageBuf *mbuf)
{
    nnnetOslMbuf_freem(mbuf);
}

NN_INLINE s32 NOS_m_adj(NOSMessageBuf *mbuf, s32 len)
{
    return nnnetOslMbuf_adj(mbuf, len);
}

NN_INLINE s32 NOS_m_append(NOSMessageBuf *mbuf, s32 len, const u8 *cp)
{
    return nnnetOslMbuf_append(mbuf, len, cp);
}

NN_INLINE NOSMessageBuf *NOS_m_prepend(NOSMessageBuf *mbuf, s32 len, int how)
{
    return nnnetOslMbuf_prepend(mbuf, len, how);
}

NN_INLINE NOSMessageBuf *NOS_m_pullup(NOSMessageBuf *mbuf, s32 len)
{
    return  nnnetOslMbuf_pullup(mbuf, len);
}

NN_INLINE NOSMessageBuf *NOS_m_dup(NOSMessageBuf *mbuf, int how)
{
    return nnnetOslMbuf_dup(mbuf, how);
}

NN_INLINE s32 NOS_m_copydata(const NOSMessageBuf *mbuf, s32 offset, s32 len, u8 *buf)
{
    return nnnetOslMbuf_copydata(mbuf, offset, len, buf);
}

NN_INLINE s32 NOS_m_copyback(NOSMessageBuf *mbuf, s32 offset, s32 len, const u8 *buf)
{
    return nnnetOslMbuf_copyback(mbuf, offset, len, buf);
}

NN_INLINE s32 NOS_m_cat(NOSMessageBuf *mbuf, NOSMessageBuf *n)
{
    return nnnetOslMbuf_cat(mbuf, n);
}

NN_INLINE NOSMessageBuf *NOS_m_split(NOSMessageBuf *mbuf, s32 len, int how)
{
    return nnnetOslMbuf_split(mbuf, len, how);
}

NN_INLINE s32 NOS_m_length(NOSMessageBuf *mbuf, NOSMessageBuf **last)
{
    return nnnetOslMbuf_length(mbuf, last);
}

NN_INLINE s32 NOS_m_apply(NOSMessageBuf *mbuf, s32 offset, s32 len, s32 (*f)(void *arg, void *data, s32 len), void *arg)
{
    return nnnetOslMbuf_apply(mbuf, offset, len, f, arg);
}

#ifdef NDEBUG_ENABLE
NN_INLINE s32 NOS_m_getfree(void)
{
    return 0;
}

NN_INLINE void NOS_m_setowner(NOSMessageBuf *mbuf, u16 owner)
{
    NN_UNUSED_VAR(mbuf);
    NN_UNUSED_VAR(owner);
}

NN_INLINE s32 NOS_m_getnum(u16 owner)
{
    NN_UNUSED_VAR(owner);
    return 0;
}

NN_INLINE NOSMessageBuf *NOS_m_getaddr(int index)
{
    NN_UNUSED_VAR(index);
    return NULL;
}
#endif

#ifdef NDEBUG_PRINT_ENABLE
NN_INLINE void NOS_m_dump(NOSMessageBuf *mbuf)
{
    nnnetOslMbuf_dump(mbuf);
}
#endif

/* NOS_main.c */
extern s32 NOS_Init(void);


#ifdef  __cplusplus
}
#endif

#endif
