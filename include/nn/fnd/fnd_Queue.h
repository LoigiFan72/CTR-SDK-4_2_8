/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Queue.h

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

#ifndef NN_FND_FND_QUEUE_
#define NN_FND_FND_QUEUE_

#ifdef __cplusplus

#include <nn/util/util_NonCopyable.h>

namespace nn { namespace fnd {

/* Please see man pages for details 
    
*/
template <typename T, typename Tag = void>
class IntrusiveQueue : private nn::util::NonCopyable<IntrusiveQueue<T, Tag> >
{
public:
    
    class Item;   //

    /* Please see man pages for details 
        
    */
    IntrusiveQueue() : m_Head(0), m_Tail(0) {}

    /* Please see man pages for details 
        

        
    */
    bool IsEmpty() const { return m_Head == 0; }

    /* Please see man pages for details 
        

        
    */
    void Enqueue(T* p);

    /* Please see man pages for details 
        

               

        
    */
    T* Dequeue();

    /* Please see man pages for details 
        
    */
    void Clear();
    
private:
    
    Item* m_Head;   //
    Item* m_Tail;   //
    
};

/* Please see man pages for details 
    

    
*/
template <typename T, typename Tag>
class IntrusiveQueue<T, Tag>::Item : private nn::util::NonCopyable<IntrusiveQueue<T, Tag>::Item>
{
    friend class IntrusiveQueue;
protected:
    Item() : m_NextLink(0) {}
    ~Item() { NN_TASSERT_(!m_NextLink); }
private:
    Item* m_NextLink;
};

template <typename T, typename Tag>
inline void IntrusiveQueue<T, Tag>::Enqueue(T* p)
{
    NN_TASSERT_(p);
    Item* pNode = static_cast<Item*>(p);
    NN_TASSERT_(!pNode->m_NextLink);
    if (IsEmpty())
    {
        this->m_Head = this->m_Tail = pNode;
        pNode->m_NextLink = pNode;
    }
    else
    {
        m_Tail->m_NextLink = p;
        this->m_Tail = p;
    }
}

template <typename T, typename Tag>
inline T* IntrusiveQueue<T, Tag>::Dequeue()
{
    if (IsEmpty())
    {
        return 0;
    }
    else
    {
        Item* ret = m_Head;
        if (m_Head == m_Tail)
        {
            this->m_Head = 0;
        }
        else
        {
            this->m_Head = m_Head->m_NextLink;
        }
        ret->m_NextLink = 0;
        return static_cast<T*>(ret);
    }
}

template <typename T, typename Tag>
inline void IntrusiveQueue<T, Tag>::Clear()
{
    if (m_Head)
    {
        Item* p = m_Head;
        do
        {
            Item* q = p;
            p = p->m_NextLink;
            q->m_NextLink = 0;
        } while (p != m_Tail);
        this->m_Head = 0;
    }
}

}}

#endif // __cplusplus

#endif
