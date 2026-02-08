/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_HeapBase.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/fnd/fnd_HeapBase.h>
#include <nn/assert.h>
#include "./detail/fnd_DetailHeapCommon.h"

namespace nn { namespace fnd {

void HeapBase::Destroy(HeapBase* child)
{
    NN_TASSERT_(child);
    NN_TASSERT_(child->m_Parent == this);
    m_Children.Erase(child);
    child->m_Parent = 0;
    child->~HeapBase();
}


HeapBase::~HeapBase()
{
    if ( m_Parent )
    {
        NN_TPANIC_("yet not call HeapBase::Destroy");
    }
    if ( !m_Children.IsEmpty() )
    {
        NN_TPANIC_("Child Heaps left.");
    }
}

HeapBase* HeapBase::GetRoot()
{
    HeapBase* heap = this;
    while (heap->m_Parent)
    {
        heap = heap->m_Parent;
    }
    return heap;
}


void HeapBase::SetFillValue(HeapFillType type, u32 val)
{
#ifdef NN_BUILD_VERBOSE
    (void)detail::SetFillValForHeap(type, val);
#else
    NN_UNUSED_VAR(type);
    NN_UNUSED_VAR(val);
#endif
}

u32 HeapBase::GetFillValue(HeapFillType type)
{
#ifdef NN_BUILD_VERBOSE
    return detail::GetFillValForHeap(type);
#else
    NN_UNUSED_VAR(type);
    return 0;
#endif
}

HeapBase* HeapBase::FindHeap(void* addr)
{
    if (this->HasAddress(addr))
    {
        HeapBase* heap = this;
    repeat:
        for (HeapBase* child = heap->m_Children.GetFront(); child; child = heap->m_Children.GetNext(child))
        {
            if (child->HasAddress(addr))
            {
                heap = child;
                goto repeat;
            }
        }
        return heap;
    }
    else
    {
        return 0;
    }
}

void HeapBase::SetParent(HeapBase* parent)
{
    NN_TASSERT_(!this->m_Parent);
    this->m_Parent = parent;
    this->m_Parent->m_Children.PushBack(this);
}

namespace {

inline void FillMemory8(uptr begin, uptr end, bit8 v)
{
    NN_TASSERT_(begin <= end);
    bit8*& p = reinterpret_cast<bit8*&>(begin);
    bit8*& q = reinterpret_cast<bit8*&>(end);
    while (p != q)
    {
        *p++ = v;
    }
}

}

void HeapBase::FillMemory32(uptr begin, uptr end, bit32 v)
{
    NN_TASSERT_(begin <= end);
    NN_TASSERT_(begin % sizeof(bit32) == 0);
    NN_TASSERT_(end % sizeof(bit32) == 0);
    bit32*& p = reinterpret_cast<bit32*&>(begin);
    bit32*& q = reinterpret_cast<bit32*&>(end);
    while (p != q)
    {
        *p++ = v;
    }
}

void HeapBase::FillMemory(uptr addr, uptr end, bit8 v)
{
    // TODO: Replace if there is a faster function
    uptr begin = addr;
    uptr rbegin = RoundUp(begin, sizeof(bit32));
    uptr rend = RoundDown(end, sizeof(bit32));
    if (rbegin > rend)
    {
        FillMemory8(begin, end, v);
    }
    else
    {
        bit32 vv = v | (v << 8);
        bit32 vvvv = vv | (vv << 16);
        FillMemory8(begin, rbegin, v);
        FillMemory32(rbegin, rend, vvvv);
        FillMemory8(rend, end, v);
    }
}

}}
