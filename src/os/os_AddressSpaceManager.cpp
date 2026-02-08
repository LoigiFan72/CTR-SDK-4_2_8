/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_AddressSpaceManager.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include "os_AddressSpaceManager.h"
#include <nn/os/os_MemoryBlock.h>

namespace nn {
    namespace os {

void AddressSpaceManager::Initialize(uptr begin, size_t size)
{
    if ( m_SpaceBegin == 0 && m_SpaceEnd == 0 )
    {
        m_Lock.Initialize();
        
        m_SpaceBegin = begin;
        m_SpaceEnd   = begin + size;
        NN_MIN_TASSERT_(m_SpaceEnd, m_SpaceBegin);
    }
}

uptr AddressSpaceManager::Allocate(MemoryBlockBase* pBlock, size_t size, size_t skipSize)
{
    NN_NULL_TASSERT_(pBlock);
    NN_ALIGN_TASSERT_(size, NN_OS_MEMORY_PAGE_SIZE);
    NN_ALIGN_TASSERT_(skipSize, NN_OS_MEMORY_PAGE_SIZE);

    Lock::ScopedLock scopedLock(m_Lock);

    MemoryBlockBase* pPrev = FindSpace(size, skipSize);
    uptr allocatedAddress;

    if( pPrev != NULL )
    {
        // There is space between pPrev and either GetNext(pPrev) or SpaceEnd

        allocatedAddress = pPrev->GetAddress() + pPrev->GetSize() + skipSize;
        MemoryBlockBase* pNext = m_BlockList.GetNext(pPrev);

        if( pNext != NULL )
        {
            NN_MAX_TASSERT_(allocatedAddress + size + skipSize, pNext->GetAddress());

            m_BlockList.Insert(pNext, pBlock);
        }
        else
        {
            NN_MAX_TASSERT_(allocatedAddress + size + skipSize, m_SpaceEnd);

            m_BlockList.PushBack(pBlock);
        }
    }
    else
    {
        // There is space between SpaceBegin and either GetFront() or SpaceEnd
        // Or there is no space.

        allocatedAddress = m_SpaceBegin;
        MemoryBlockBase* pNext = m_BlockList.GetFront();

        if( pNext != NULL )
        {
            const uptr allocatedEnd = allocatedAddress + size;
            const uptr nextBegin    = pNext->GetAddress();

            if( nextBegin < allocatedEnd + skipSize )
            {
                // A size-portion of open memory does not exist between the start of the address space and the next memory block.
                return NULL;
            }

            m_BlockList.Insert(pNext, pBlock);
        }
        else
        {
            // When all space is open
            const uptr allocatedEnd = allocatedAddress + size;

            if( m_SpaceEnd < allocatedEnd )
            {
                // A size-portion of open memory does not exist in the region of managed address space.
                return NULL;
            }

            m_BlockList.PushBack(pBlock);
        }
    }

    pBlock->SetAddressAndSize(allocatedAddress, size);

    return allocatedAddress;
}

// Release memory block to the address space.
void AddressSpaceManager::Free(MemoryBlockBase* pBlock)
{
    // TODO: Need to do pBlock NULL check.
    Lock::ScopedLock scopedLock(m_Lock);

    m_BlockList.Erase(pBlock);
    pBlock->SetAddressAndSize(NULL, 0);
}

// Move memory block information from pFrom to pTo.
void AddressSpaceManager::Switch(MemoryBlockBase* pTo, MemoryBlockBase* pFrom)
{
    // TODO: Need to do pTo NULL check.
    // TODO: Need to do pFrom NULL check.
    Lock::ScopedLock scopedLock(m_Lock);

    pTo->SetAddressAndSize(pFrom->GetAddress(), pFrom->GetSize());
    m_BlockList.Insert(pFrom, pTo);

    pFrom->SetAddressAndSize(NULL, 0);
    m_BlockList.Erase(pFrom);
}

// Searches for a region that has open memory equal to the specified size + page size portion.
MemoryBlockBase* AddressSpaceManager::FindSpace(size_t size, size_t skipSize)
{
    MemoryBlockBase* pItem = m_BlockList.GetBack();
    uptr end = m_SpaceEnd;
    NN_MIN_TASSERT_(end, m_SpaceBegin);

    while( pItem != NULL )
    {
        const uptr nextBegin = pItem->GetAddress();
        const uptr nextEnd   = nextBegin + pItem->GetSize();
        const size_t spaceSize = end - nextEnd;
        NN_MAX_TASSERT_(nextEnd, end);

        if( spaceSize >= size + skipSize )
        {
            // The end of pItem is open
            return pItem;
        }

        end = nextBegin - skipSize;
        pItem = m_BlockList.GetPrevious(pItem);
    }

    // All space is open
    // Or the start of space is open
    // Or there is no opening
    return NULL;
}

// Debug output the memory block list existing in the address space.
void AddressSpaceManager::Dump()
{
    // CHECK: Recommend locking so that list content from other threads is not changed during dump.

    MemoryBlockBase* pItem = m_BlockList.GetFront();
    
    NN_TLOG_("  --------  %08x %08x\n", m_SpaceBegin, m_SpaceEnd);
    while( pItem != NULL )
    {
        NN_TLOG_("  %08x  %08x %08x\n", pItem, pItem->GetAddress(), pItem->GetAddress() + pItem->GetSize());
        pItem = m_BlockList.GetNext(pItem);
    }

    NN_TPANIC_("dump complete");
}

    }
}



#include <new>
using namespace nn::os;

extern "C" {

void nnosAddressSpaceManagerInitialize(nnosAddressSpaceManager* p, uptr begin, size_t size)
{
    AddressSpaceManager* pThis = new (p) AddressSpaceManager();
    pThis->Initialize(begin, size);
}

uptr nnosAddressSpaceManagerAllocate(nnosAddressSpaceManager* p, nnosMemoryBlockBase* p2, size_t size, size_t skipSize)
{
    AddressSpaceManager* pThis = reinterpret_cast<AddressSpaceManager*>(p);
    MemoryBlockBase* pBlock = reinterpret_cast<MemoryBlockBase*>(p2);
    return pThis->Allocate(pBlock, size, skipSize);
}

void nnosAddressSpaceManagerFree(nnosAddressSpaceManager* p, nnosMemoryBlockBase* p2)
{
    AddressSpaceManager* pThis = reinterpret_cast<AddressSpaceManager*>(p);
    MemoryBlockBase* pBlock = reinterpret_cast<MemoryBlockBase*>(p2);
    pThis->Free(pBlock);
}

void nnosAddressSpaceManagerSwitch(nnosAddressSpaceManager* p, nnosMemoryBlockBase* p2, nnosMemoryBlockBase* p3)
{
    AddressSpaceManager* pThis = reinterpret_cast<AddressSpaceManager*>(p);
    MemoryBlockBase* pTo = reinterpret_cast<MemoryBlockBase*>(p2);
    MemoryBlockBase* pFrom = reinterpret_cast<MemoryBlockBase*>(p3);
    pThis->Switch(pTo, pFrom);
}

}


#endif  // if NN_PLATFORM_HAS_MMU
