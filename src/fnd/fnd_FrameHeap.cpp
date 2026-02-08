/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_FrameHeap.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/fnd/fnd_FrameHeap.h>

namespace nn { namespace fnd {

/*
FrameHeapBase* FrameHeapBase::Create(HeapBase* parent, void* addr, size_t size, bit32 option)
{
    if ( parent->FindHeap(addr) != parent ) return 0;
    FrameHeap* frameheap = new (addr) FrameHeap(reinterpret_cast<uptr>(addr)+sizeof(FrameHeap), static_cast<size_t>(size - sizeof(FrameHeap)), option);
    frameheap->SetParent(parent);
    return frameheap;
}
*/

void FrameHeapBase::Initialize(uptr addr, size_t size, bit32 option)
{
    NN_TASSERT_(size >= 0);
    HeapBase::Initialize(option);
    this->m_Addr = this->m_CurrentHead = addr;
    this->m_Size = size;
    this->m_CurrentTail = this->m_Addr + this->m_Size;

    DebugFillMemory(addr, size, HEAP_FILL_TYPE_NOUSE);
}

void FrameHeapBase::Dump() const
{
#if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)

    NN_TLOG_("     attr  address(from - to):     size\n");   // wb_[s

    // ---------------- UsedBlock ?_v ----------------
    NN_TLOG_("    (Used Blocks)\n" );
    if(this->m_Addr == this->m_CurrentHead)
    {
        NN_TLOG_("    front NONE\n"); 
    }
    else
    {
        NN_TLOG_("    front %08x - %08x: %8d\n", 
            this->m_Addr, this->m_CurrentHead, this->m_CurrentHead - this->m_Addr);
    }

    if(this->m_Addr + this->m_Size == this->m_CurrentTail)
    {
        NN_TLOG_("     rear NONE\n"); 
    }
    else
    {
        NN_TLOG_("     rear %08x - %08x: %8d\n", 
            this->m_CurrentTail, this->m_Addr + this->m_Size, this->m_Addr + this->m_Size - this->m_CurrentTail);
    }

    // ---------------- FreeBlock ?_v ----------------
    NN_TLOG_("    (Free Blocks)\n" );
    if(this->m_CurrentHead == this->m_CurrentTail)
    {
        NN_TLOG_("     free NONE\n"); 
    }
    else
    {
        NN_TLOG_("     free %08x - %08x: %8d\n", 
            this->m_CurrentHead, this->m_CurrentTail, this->m_CurrentTail - this->m_CurrentHead);
    }

    u32 usedSize = this->m_Size - (this->m_CurrentTail - this->m_CurrentHead);
    NN_TLOG_("\n");
    NN_TLOG_("    %d / %d bytes (%d%%) used\n",
        usedSize, this->m_Size, 100 * usedSize / this->m_Size);
    NN_TLOG_("\n");

#endif
}

}}
