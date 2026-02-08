/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_LinkedList.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47266 $
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
  Project:  NW4R - SystemLib - include - nw4r - ut
  File:     LinkedList.h

  Copyright (C)2005-2008 Nintendo  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 1.13 #$
 *---------------------------------------------------------------------------*/

/* 
  

*/

#ifndef NN_FND_FND_LINKEDLIST_H_
#define NN_FND_FND_LINKEDLIST_H_

#ifdef __cplusplus

#include <nn/assert.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/fnd/fnd_Result.h>

namespace nn { namespace fnd {

// Usage examples
//
// class Hoge : public IntrusiveLinkedList<Hoge>::Item { ... };
// tyepdef IntrusiveLinkedList<Hoge> HogeList;
//
// Hoge a, b, c;
// {
//      HogeList list;
//      list.PushFront(&a);
//      list.PushBack(&b);
//      list.PushFront(&a); // PANIC: Item cannot be inserted in list twice
//      if (Hoge* p = list.PopBack())
//      {
//          // Processing using *p
//      }
//      list.Erase(&a); // Specify the element and delete
//      list.Clear();
//  } // Automatic Clear() using destructor

// TODO: Untested
// NEED_DOCUMENT
// NEED_TEST

/*
  
*/
template <typename T, typename Tag = void>
class IntrusiveLinkedList : private nn::util::NonCopyable<IntrusiveLinkedList<T, Tag> >
{
public:

    class Item;   //
    
    /*

    */
    IntrusiveLinkedList() : m_Head(0) {}

    /*

    */
    ~IntrusiveLinkedList() { Clear(); }
    
    /*
    

    
    */
    bool IsEmpty() const { return !m_Head; }

    /*
    

    
    */
    void PushBack(T* p);

    /*
    

    
    */
    void PushFront(T* p);

    /*
    

    
    */
    T* GetFront() const;

    /*
    

    
    */
    T* GetBack() const;

    /*
    

 

 
    */
    T* PopFront();

    /*
    

    

    
    */
    T* PopBack();

    /*
    

    

    
    */
    T* GetNext(T* p) const;

    /*
    

    

 
    */
    T* GetPrevious(T* p) const;

    /*
    

    

    
    
    */
    void Insert(T* position, T* inserted);

    /*
    

    
    */
    void Erase(T* p);

    /*
    
    */
    void Clear();
    
private:
    
    Item* m_Head;  //
    
    /*
        :private

        

        
    */
    static void ClearLinks(Item* p);

    /*
        :private

        
    */
    static void InsertBefore(Item* p, Item* q);

};

// NEED_DOCUMENT
// NEED_TEST
/*
    :private


*/
template <typename T, typename Tag>
class IntrusiveLinkedList<T, Tag>::Item : private nn::util::NonCopyable<IntrusiveLinkedList<T, Tag>::Item>
{
    friend class IntrusiveLinkedList;
protected:
    Item() : m_PreviousLink(0), m_NextLink(0) {}
    ~Item() { NN_TASSERT_(!m_PreviousLink && !m_NextLink); }
    T* GetPrevious() const { return static_cast<T*>(m_PreviousLink); }
    T* GetNext() const { return static_cast<T*>(m_NextLink); }
    bool IsChained() const { return m_PreviousLink != NULL; }
private:
    Item* m_PreviousLink;
    Item* m_NextLink;
};

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::ClearLinks(Item* p)
{
    p->m_PreviousLink = p->m_NextLink = 0;
}

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::InsertBefore(Item* p, Item* q)
{
    q->m_NextLink = p;
    p->m_PreviousLink->m_NextLink = q;
    q->m_PreviousLink = p->m_PreviousLink;
    p->m_PreviousLink = q;
}

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::PushBack(T* p)
{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    NN_TASSERT_(p);
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(!pNode->m_PreviousLink, MakeResultAlreadyListed());
    NN_TASSERT_(!pNode->m_PreviousLink);
    NN_TASSERT_(!pNode->m_NextLink);
    if (IsEmpty())
    {
        p->m_PreviousLink = p->m_NextLink = p;
        this->m_Head = p;
    }
    else
    {
        InsertBefore(m_Head, pNode);
    }
}

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::PushFront(T* p)
{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    NN_TASSERT_(p);
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(!pNode->m_PreviousLink, MakeResultAlreadyListed());
    NN_TASSERT_(!pNode->m_PreviousLink);
    NN_TASSERT_(!pNode->m_NextLink);
    if (IsEmpty())
    {
        p->m_PreviousLink = p->m_NextLink = p;
    }
    else
    {
        InsertBefore(m_Head, pNode);
    }
    this->m_Head = p;
}

template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetFront() const
{
    return static_cast<T*>(m_Head);
}

template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetBack() const
  {
    if (IsEmpty())
    {
        return 0;
    }
    else
    {
        return static_cast<T*>(m_Head->m_PreviousLink);
    }
}

template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::PopFront()
{
    if (T* ret = GetFront())
    {
        this->Erase(ret);
        return ret;
    }
    else
    {
        return 0;
    }
}

template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::PopBack()
{
    if (T* ret = GetBack())
    {
        this->Erase(ret);
        return ret;
    }
    else
    {
        return 0;
    }
}

template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetPrevious(T* p) const
{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    NN_TASSERT_(p);
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(pNode->m_PreviousLink, MakeResultInvalidNode());
    NN_TASSERT_(pNode->m_PreviousLink);
    NN_TASSERT_(pNode->m_NextLink);
    if (p == this->GetFront())
    {
        return 0;
    }
    return static_cast<T*>(pNode->m_PreviousLink);
}

template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetNext(T* p) const
{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    NN_TASSERT_(p);
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(pNode->m_PreviousLink, MakeResultInvalidNode());
    NN_TASSERT_(pNode->m_PreviousLink);
    NN_TASSERT_(pNode->m_NextLink);
    if (p == this->GetBack())
    {
        return 0;
    }
    return static_cast<T*>(pNode->m_NextLink);
}

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::Insert(T* position, T* inserted)
{
    NN_ASSERT_WITH_RESULT(inserted, MakeResultInvalidAddress());
    NN_TASSERT_(inserted);
    Item* pNodeInserted = static_cast<Item*>(inserted);
    Item* pNodePosition = static_cast<Item*>(position);
    NN_ASSERT_WITH_RESULT(!pNodeInserted->m_PreviousLink, MakeResultAlreadyListed());
    NN_TASSERT_(!pNodeInserted->m_PreviousLink);
    NN_TASSERT_(!pNodeInserted->m_NextLink);
    if (pNodePosition == m_Head)
    {
        PushFront(inserted);
    }
    else if (pNodePosition)
    {
        NN_ASSERT_WITH_RESULT(pNodePosition->m_PreviousLink, MakeResultInvalidNode());
        NN_TASSERT_(pNodePosition->m_PreviousLink);
        NN_TASSERT_(pNodePosition->m_NextLink);
        InsertBefore(pNodePosition, pNodeInserted);
    }
    else
    {
        PushBack(inserted);
    }
}

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::Erase(T* p)
{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    NN_TASSERT_(p);
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(pNode->m_PreviousLink, MakeResultInvalidNode());
    NN_TASSERT_(pNode->m_PreviousLink);
    NN_TASSERT_(pNode->m_NextLink);
    if (pNode == pNode->m_PreviousLink)
    {
        this->m_Head = 0;
    }
    else
    {
        if (m_Head == pNode)
        {
            this->m_Head = m_Head->m_NextLink;
        }
        pNode->m_NextLink->m_PreviousLink = pNode->m_PreviousLink;
        pNode->m_PreviousLink->m_NextLink = pNode->m_NextLink;
    }
    ClearLinks(pNode);
}

template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::Clear()
{
    if (m_Head)
    {
        Item* p = m_Head;
        while (p)
        {
            Item* q = p;
            p = p->m_NextLink;
            ClearLinks(q);
        }
        this->m_Head = 0;
    }
}

}  // namespace util
}  // namespace nn

#endif // __cplusplus

#endif  /* NN_UTIL_LINKEDLIST_H_ */
