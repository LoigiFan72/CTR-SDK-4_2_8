/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_ExpHeap.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/fnd/fnd_Expheap.h>
#include "./detail/fnd_DetailHeap.h"

namespace nn { namespace fnd {

bool ExpHeapBase::HasAddress(const void* addr) const
{
    return reinterpret_cast<uptr>(m_ExpHeapImpl.heapStart) <= reinterpret_cast<uptr>(addr)
       && reinterpret_cast<uptr>(addr) < reinterpret_cast<uptr>(m_ExpHeapImpl.heapEnd);
}


void ExpHeapBase::Initialize(uptr addr, size_t size, bit32 option)
{
    // TODO: Use this->m_Option rather than an internal implementation for option
    nn::fnd::detail::Heap heap = detail::CreateHeap(&m_ExpHeapImpl, reinterpret_cast<void*>(addr), size, option);
    if (heap == NN_OS_HEAP_INVALID_HANDLE)
    {
        NN_PANIC("Failed to detail::CreateHeap");
    }
    this->m_AllocCount = 0;
}

void ExpHeapBase::Finalize()
{
    NN_TASSERT_(m_AllocCount == 0);
    if (m_ExpHeapImpl.signature != 0)
    {
        detail::DestroyHeap(&m_ExpHeapImpl);
        m_ExpHeapImpl.signature = 0;
    }
}

void ExpHeapBase::Invalidate()
{
    m_AllocCount = 0;
    Finalize();
}

void* ExpHeapBase::Allocate(size_t byteSize, s32 alignment, bit8 groupId, AllocationMode mode, bool reuse)
{
    detail::SetGroupIDForHeap(&m_ExpHeapImpl, groupId);
    detail::SetAllocModeForHeap(&m_ExpHeapImpl, mode);
    detail::UseMarginOfAlignmentForHeap(&m_ExpHeapImpl, reuse);
    void* memory =  detail::AllocFromHeap(&m_ExpHeapImpl, byteSize, alignment);
    if(memory != NULL)
    {
        ++this->m_AllocCount;
    }
    return memory;
}

void ExpHeapBase::Free(void* p)
{
    NN_TASSERT_(CheckBlock(p));
    detail::FreeToHeap(&m_ExpHeapImpl, p);
    --this->m_AllocCount;
}

size_t ExpHeapBase::ResizeBlock(void *p, size_t newSize)
{
    return detail::ResizeForMBlockHeap(&m_ExpHeapImpl, p, newSize);
}

namespace {

    struct FuncAndParam {
        nn::fnd::ExpHeapBase::BlockVisitor f;
        uptr param;
        ExpHeapBase* heap;
    };

    void VisitFunc(void* p, detail::Heap, u32 param)
    {
        FuncAndParam& fap = *reinterpret_cast<FuncAndParam*>(param);
        fap.f(p, fap.heap, fap.param);
    }

}

void ExpHeapBase::VisitAllBlocks(nn::fnd::ExpHeapBase::BlockVisitor visitor, uptr param)
{
    // TODO: Optimize this
    FuncAndParam fap;
    fap.f = visitor;
    fap.param = param;
    fap.heap = this;
    detail::VisitAllocatedForHeap(&m_ExpHeapImpl, VisitFunc, reinterpret_cast<u32>(&fap));
}

size_t ExpHeapBase::GetTotalFreeSize() const
{
    return detail::GetTotalFreeSizeForHeap(&m_ExpHeapImpl);
}

size_t ExpHeapBase::GetAllocatableSize(s32 alignment) const
{
    return detail::GetAllocatableSizeForHeap(&m_ExpHeapImpl, alignment);
}
    
size_t ExpHeapBase::GetSizeOf(const void* p) const
{
    return detail::GetSizeForMBlockHeap(p);
}

bit8 ExpHeapBase::GetGroupIdOf(const void* p) const
{
    return detail::GetGroupIDForMBlockHeap(p);
}
    
ExpHeapBase::AllocationDirection ExpHeapBase::GetDirectionOf(const void* p) const
{
    return static_cast<AllocationDirection>(detail::GetAllocDirForMBlockHeap(p));
}

u32 ExpHeapBase::Adjust()
{
    u32 oldsize = ExpHeapBase::GetTotalSize();
    return oldsize - detail::AdjustHeap(&m_ExpHeapImpl, HEAP_ADJUST_TAIL).GetSize();
}

MemoryRange ExpHeapBase::Adjust(HeapAdjustMode mode)
{
    return detail::AdjustHeap(&m_ExpHeapImpl, mode);
}

bool ExpHeapBase::CheckHeap(bit32 option) const
{
    return detail::CheckHeap(&m_ExpHeapImpl, option);
}

bool ExpHeapBase::CheckBlock(const void* p, bit32 option) const
{
    return detail::CheckForMBlockHeap(p, &m_ExpHeapImpl, option);
}

void* ExpHeapBase::GetStartAddress() const
{
    return GetHeapStartAddress(&m_ExpHeapImpl); 
}

size_t ExpHeapBase::GetTotalSize() const
{
    return GetHeapTotalSize(&m_ExpHeapImpl);
}

void ExpHeapBase::Dump() const
{
#if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
    detail::NNSi_FndDumpHeap(&m_ExpHeapImpl);
#endif
}

}}
