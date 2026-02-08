/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Queue.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_QUEUE_H_
#define NN_RDT_QUEUE_H_

#include "rdt_Utility.h"

namespace nn { namespace rdt { namespace CTR {


/* Please see man pages for details 
    
           
           
*/
template <class T, size_t N>
class Queue{
public:
/* Please see man pages for details 
    
*/
    Queue(void);

/* Please see man pages for details 
    
*/
   ~Queue(void);

/* Please see man pages for details 
    
*/
    bool IsEmpty(void) const;

/* Please see man pages for details 
    
*/
    size_t Size(void) const;

/* Please see man pages for details 
    
*/
    void Push(const T &value);

/* Please see man pages for details 
    
*/
    void Pop(void);

/* Please see man pages for details 
    
*/
    const T& Front(void) const;

/* Please see man pages for details 
    
*/
    const T& Back(void) const;

/* Please see man pages for details 
    
*/
    void Clear(void);

/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

private:
/* Please see man pages for details 
    
*/
    Queue           (const Queue&);

/* Please see man pages for details 
    
*/
    Queue& operator=(const Queue&);

    // Lower numbers are on the start-side.
    T m_array[N];
    size_t m_front;  // Index indicating start elements
    size_t m_back;   // Index indicating position when packing from back

    // If m_front and m_back are equal, the queue is "empty."
};

template <class T, size_t N>
Queue<T, N>::Queue(void)
{
    Clear();
}

// Destructor
template <class T, size_t N>
Queue<T, N>::~Queue(void)
{
}


template <class T, size_t N>
bool Queue<T, N>::IsEmpty(void) const
{
    return m_front==m_back;
}


template <class T, size_t N>
size_t Queue<T, N>::Size(void) const
{
    return (m_back - m_front + N) % N;
}


template <class T, size_t N>
void Queue<T, N>::Push(const T &value)
{
    ASSERTMSG((m_back + 1) % N != m_front, "You can not Push() anymore because queue is full.");

    m_array[m_back] = value;
    m_back = (m_back + 1) % N;
}


template <class T, size_t N>
void Queue<T, N>::Pop(void)
{
    ASSERTMSG(!IsEmpty(), "You attempted to execute Pop(), but queue is empty.");

    m_front = (m_front + 1) % N;
}


template <class T, size_t N>
const T& Queue<T, N>::Front(void) const
{
    return m_array[m_front];
}


template <class T, size_t N>
const T& Queue<T, N>::Back(void) const
{
    return m_array[(m_back - 1 + N) % N];
}


template <class T, size_t N>
void Queue<T, N>::Clear(void)
{
    m_front = 0;
    m_back = 0;
}


// If T is not a basic type, then this PrintDebugInfo function will not work
template <class T, size_t N>
void Queue<T, N>::PrintDebugInfo(void) const
{
    if(IsEmpty())
    {
        LOG("Queue is empty.\n");
    }
    else
    {
        for(u32 i=0; i<Size(); ++i)
        {
            LOG("[%d] : %d\n", i, m_array[(m_front + i) % N]);
        }
    }
}

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_QUEUE_H_
