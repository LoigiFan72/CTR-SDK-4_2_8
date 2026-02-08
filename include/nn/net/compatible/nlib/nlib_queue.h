/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nlib_queue.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 
 */

#ifndef __NLIB_QUEUE_H__
#define __NLIB_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NLIBQueue  NLIBQueue, NLIBLink;

/* Please see man pages for details 
 
 */
struct NLIBQueue {
    struct NLIBQueue *next;   /* Please see man pages for details */
    struct NLIBQueue *prev;   /* Please see man pages for details */
};

/* Please see man pages for details 
 
 */
#define NLIB_Queue_Init(queue)          ((queue)->next = (queue)->prev = NULL)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_QueryHead(queue)     ((queue)->next)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_QueryTail(queue)     ((queue)->prev)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_QueryLinkPrev(item, link) ((item)->link.prev)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_QueryLinkNext(item, link) ((item)->link.next)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_IsEmpty(queue)       ((queue)->next == NULL)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_IsEnd(queue, item)   ((item) == NULL)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_EnqueueAfter(type, queue, previtem, item, link)           \
do {                                                                \
    (item)->link.prev = (NLIBQueue*) (previtem);                      \
    (item)->link.next = (previtem)->link.next;                      \
    (previtem)->link.next = (NLIBQueue*) (item);                      \
    if (NLIB_Queue_IsEnd(queue, (item)->link.next))                     \
        (queue)->prev = (NLIBQueue*) (item);                          \
    else                                                            \
        ((type) (item)->link.next)->link.prev = (NLIBQueue*) (item);  \
} while (0)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_EnqueueBefore(type, queue, item, afteritem, link)         \
do {                                                                \
    (item)->link.prev = (afteritem)->link.prev;                     \
    (item)->link.next = (NLIBQueue*) (afteritem);                     \
    (afteritem)->link.prev = (NLIBQueue*) (item);                     \
    if (NLIB_Queue_IsEnd(queue, (item)->link.prev))                     \
        (queue)->next = (NLIBQueue*) (item);                          \
    else                                                            \
        ((type) (item)->link.prev)->link.next = (NLIBQueue*) (item);  \
} while (0)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_EnqueueTail(type, queue, item, link)                      \
do {                                                                \
    register NLIBQueue* ___prev;                                      \
                                                                    \
    ___prev = (queue)->prev;                                        \
    if (NLIB_Queue_IsEnd(queue, ___prev))                               \
        (queue)->next = (NLIBQueue*) (item);                          \
    else                                                            \
        ((type) ___prev)->link.next = (NLIBQueue*) (item);            \
    (item)->link.prev = ___prev;                                    \
    (item)->link.next = NULL;                                       \
    (queue)->prev = (NLIBQueue*) item;                                \
} while (0)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_EnqueueHead(type, queue, item, link)                      \
do {                                                                \
    register NLIBQueue* ___next;                                      \
                                                                    \
    ___next = (queue)->next;                                        \
    if (NLIB_Queue_IsEnd(queue, ___next))                               \
        (queue)->prev = (NLIBQueue*) (item);                          \
    else                                                            \
        ((type) ___next)->link.prev = (NLIBQueue*) (item);            \
    (item)->link.next = ___next;                                    \
    (item)->link.prev = NULL;                                       \
    (queue)->next = (NLIBQueue*) item;                                \
} while (0)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_DequeueItem(type, queue, item, link)                      \
do {                                                                \
    register NLIBQueue* ___next;                                      \
    register NLIBQueue* ___prev;                                      \
                                                                    \
    ___next = (item)->link.next;                                    \
    ___prev = (item)->link.prev;                                    \
                                                                    \
    if (NLIB_Queue_IsEnd(queue, ___next))                               \
        (queue)->prev = ___prev;                                    \
    else                                                            \
        ((type) ___next)->link.prev = ___prev;                      \
                                                                    \
    if (NLIB_Queue_IsEnd(queue, ___prev))                               \
        (queue)->next = ___next;                                    \
    else                                                            \
        ((type) ___prev)->link.next = ___next;                      \
} while (0)

/* Please see man pages for details 
 
 
 */
#define NLIB_Queue_DequeueHead(type, queue, item, link)                      \
do {                                                                \
    register NLIBQueue* ___next;                                      \
                                                                    \
    (item) = (type) NLIB_Queue_QueryHead(queue);                        \
    ___next = (item)->link.next;                                    \
                                                                    \
    if (NLIB_Queue_IsEnd(queue, ___next))                               \
        (queue)->prev = NULL;                                       \
    else                                                            \
        ((type) ___next)->link.prev = NULL;                         \
    (queue)->next = ___next;                                        \
} while (0)

/* Please see man pages for details 
 
 
 */
#define NLIB_Queue_DequeueTail(type, queue, item, link)                      \
do {                                                                \
    register NLIBQueue* ___prev;                                      \
                                                                    \
    (item) = (type) NLIB_Queue_QueryTail(queue);                        \
    ___prev = (item)->link.prev;                                    \
                                                                    \
    if (NLIB_Queue_IsEnd(queue, ___prev))                               \
        (queue)->next = NULL;                                       \
    else                                                            \
        ((type) ___prev)->link.next = NULL;                         \
    (queue)->prev = ___prev;                                        \
} while (0)

/* Please see man pages for details 
 
 */
#define NLIB_Queue_IterateQueue(type, queue, item, next, link)               \
    for ((item) = (type) NLIB_Queue_QueryHead(queue),                   \
         (next) = NLIB_Queue_IsEnd(queue, item) ? NULL : (type) NLIB_Queue_QueryLinkNext(item, link);    \
         !NLIB_Queue_IsEnd(queue, item);                                 \
         (item) = (next),                                           \
         (next) = NLIB_Queue_IsEnd(queue, item) ? NULL : (type) NLIB_Queue_QueryLinkNext(item, link))

/* Please see man pages for details 
 
 */
#define NLIB_Queue_IterateQueueReverse(type, queue, item, prev, link)        \
    for ((item) = (type) NLIB_Queue_QueryTail(queue),                   \
         (prev) = NLIB_Queue_IsEnd(queue, item) ? NULL : (type) NLIB_Queue_QueryLinkPrev(item, link);    \
         !NLIB_Queue_IsEnd(queue, item);                                 \
         (item) = (prev),                                           \
         (prev) = NLIB_Queue_IsEnd(queue, item) ? NULL : (type) NLIB_Queue_QueryLinkPrev(item, link))

#ifdef __cplusplus
}
#endif

/* __NLIB_QUEUE_H__ */
#endif
