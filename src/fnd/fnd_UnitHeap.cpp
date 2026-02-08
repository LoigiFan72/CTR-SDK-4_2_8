/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_UnitHeap.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/fnd/fnd_UnitHeap.h>
#include <nn/assert.h>
#include <new>

namespace nn { namespace fnd {

void UnitHeapBase::Initialize(size_t unit, uptr addr, size_t size, s32 alignment, bit32 option)
{
    NN_TASSERT_(m_FreeNode == 0);
    NN_TASSERT_(alignment >= sizeof(void*));
    NN_TASSERT_(unit >= sizeof(void*));
    NN_TASSERT_(alignment % sizeof(void*) == 0);
    HeapBase::Initialize(option);
    this->m_Unit = RoundUp(unit, alignment);
    this->m_Addr = RoundUp(addr, alignment);
    this->m_Size = RoundDown((addr+size)-m_Addr, m_Unit);
    this->m_Alignment = alignment;
    this->m_Count = 0;

    DebugFillMemory(addr, size, HEAP_FILL_TYPE_NOUSE);
    
    Node* freeNode = 0;
    for (uptr addr2 = m_Addr + m_Size - m_Unit; addr2 >= m_Addr; addr2 -= m_Unit)
    {
        reinterpret_cast<Node*>(addr2)->next = freeNode;
        freeNode = reinterpret_cast<Node*>(addr2);
    }
    NN_TASSERT_(reinterpret_cast<uptr>(freeNode) == m_Addr);
    this->m_FreeNode = freeNode;
}

size_t UnitHeapBase::GetRequiredHeapSize(size_t unit, size_t numUnit, s32 alignment)
{
    return RoundUp(unit, alignment) * numUnit;
}

bool UnitHeapBase::IsFreeNode(uptr addr) const
{
    if(this->m_FreeNode == NULL)
    {
        return false;
    }
    else
    {
        Node* pNode = this->m_FreeNode;
        while( pNode != NULL )
        {
            if(reinterpret_cast<uptr>(pNode) == addr)
            {
                return true;
            }
            pNode = pNode->next;
        }
    }

    return false;
}

void UnitHeapBase::Dump() const
{
#if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)

    NN_TLOG_("     address(from - to):     size\n");   // header line

    // ---------------- UsedBlock dump ----------------
    NN_TLOG_("    (Used Nodes)\n" );
    if(this->m_Count == 0)
    {
        NN_TLOG_("    NONE\n"); 
    }
    else
    {
        for( int i = 0; i < m_Size / m_Unit; i++ )
        {
            uptr start = this->m_Addr + m_Unit * i;
            if(! IsFreeNode(start))
            {
                NN_TLOG_("    %08x - %08x: %8d\n", 
                    start, start + this->m_Unit, this->m_Unit);
            }
        }
    }

    // ---------------- FreeBlock dump ----------------
    NN_TLOG_("    (Free Nodes)\n" );
    if(this->m_FreeNode == NULL)
    {
        NN_TLOG_("    NONE\n"); 
    }
    else
    {
        Node* pNode = this->m_FreeNode;
        while(pNode != NULL)
        {
            uptr start = reinterpret_cast<uptr>(pNode);
            NN_TLOG_("    %08x - %08x: %8d\n", 
                start, start + this->m_Unit, this->m_Unit);
            pNode = pNode->next;
        }
    }

    u32 usedSize = this->m_Unit * this->m_Count;
    NN_TLOG_("\n");
    NN_TLOG_("    %d / %d bytes (%d%%) used\n",
        usedSize, this->m_Size, 100 * usedSize / this->m_Size);
    NN_TLOG_("\n");

#endif
}

}}
