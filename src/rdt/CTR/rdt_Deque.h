/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Deque.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_DEQUE_H_
#define NN_RDT_DEQUE_H_

#include "rdt_Utility.h"

namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
           
           

*/
template <class T, size_t N>
class Deque{
public:
/* Please see man pages for details 
    
*/
    Deque(void);

/* Please see man pages for details 
    
*/
   ~Deque(void);

/* Please see man pages for details 
    
*/
    bool IsEmpty(void) const;

/* Please see man pages for details 
    
*/
    bool IsFull(void) const;

/* Please see man pages for details 
    
*/
    size_t Size(void) const;

/* Please see man pages for details 
    
*/
    void PushBack(const T &value);

/* Please see man pages for details 
    
*/
    void PopFront(void);

/* Please see man pages for details 
    
*/
    const T& Front(void) const;

/* Please see man pages for details 
    
*/
          T& Front(void);

/* Please see man pages for details 
    
*/
    const T& Back(void) const;

/* Please see man pages for details 
    
*/
          T& Back(void);

/* Please see man pages for details 
    
*/
    const T& At(size_t n) const;

/* Please see man pages for details 
    
*/
    void Clear(void);

private:
/* Please see man pages for details 
    
*/
    Deque           (const Deque&);

/* Please see man pages for details 
    
*/
    Deque& operator=(const Deque&);

    // Lower numbers are on the start-side.
    T m_array[N];
    size_t m_front;  // Index indicating start elements
    size_t m_back;   // Index indicating position when packing from back

    // If m_front and m_back are equal, the queue is empty.

};


template <class T, size_t N>
Deque<T, N>::Deque(void)
{
    Clear();
}


// Destructor
template <class T, size_t N>
Deque<T, N>::~Deque(void)
{
}


template <class T, size_t N>
bool Deque<T, N>::IsEmpty(void) const
{
    return m_front==m_back;
}


template <class T, size_t N>
bool Deque<T, N>::IsFull(void) const
{
    return (m_back + 1) % N == m_front;
}


template <class T, size_t N>
size_t Deque<T, N>::Size(void) const
{
    return (m_back - m_front + N) % N;
}


template <class T, size_t N>
void Deque<T, N>::PushBack(const T &value)
{
    ASSERTMSG(!IsFull(), "You cannot PushBack() anymore because deque is full.");

    m_array[m_back] = value;
    m_back = (m_back + 1) % N;
}


template <class T, size_t N>
void Deque<T, N>::PopFront(void)
{
    ASSERTMSG(!IsEmpty(), "You attempt to call PopFront(), but deque is empty.");

    m_front = (m_front + 1) % N;
}


template <class T, size_t N>
const T& Deque<T, N>::Front(void) const
{
    ASSERTMSG(!IsEmpty(), "You attempt to call const T& Front(), but deque is empty.");

    return m_array[m_front];
}


template <class T, size_t N>
T& Deque<T, N>::Front(void)
{
    ASSERTMSG(!IsEmpty(), "You attempt to call T& Front(), but deque is empty.");

    return m_array[m_front];
}


template <class T, size_t N>
const T& Deque<T, N>::Back(void) const
{
    ASSERTMSG(!IsEmpty(), "You attempt to call const T& Back(), but deque is empty.");

    return m_array[(m_back - 1 + N) % N];
}


template <class T, size_t N>
T& Deque<T, N>::Back(void)
{
    ASSERTMSG(!IsEmpty(), "You attempt to call T& Back(), but deque is empty.");

    return m_array[(m_back - 1 + N) % N];
}


template <class T, size_t N>
const T& Deque<T, N>::At(size_t n) const
{
    ASSERT(n < Size());

    return m_array[(m_front + n) % N];
}


template <class T, size_t N>
void Deque<T, N>::Clear(void)
{
    m_front = 0;
    m_back  = 0;
}

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_DEQUE_H_
