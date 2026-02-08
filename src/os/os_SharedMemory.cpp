/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SharedMemory.cpp

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

#include <nn/svc.h>
#include <nn/util/util_Result.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_SharedMemory.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include "os_AddressSpaceManager.h"

namespace nn { namespace os {

    namespace
    {
        nnosAddressSpaceManager s_SpaceManager;

        size_t GetPageAlignedSize(size_t size)
        {
            return (size + NN_OS_MEMORY_PAGE_SIZE - 1) & ~(NN_OS_MEMORY_PAGE_SIZE - 1);
        }
    }

    namespace detail
    {
        void InitializeSharedMemory()
        {
            nnosAddressSpaceManagerInitialize(&s_SpaceManager, NN_OS_ADDR_SHARED_BEGIN, NN_OS_ADDR_SHARED_SIZE);
        }
        uptr AllocateFromSharedMemorySpace(MemoryBlockBase* p, size_t s)
        {
            AddressSpaceManager* pManager = reinterpret_cast<AddressSpaceManager*>(&s_SpaceManager);
            return pManager->Allocate(p, s, NN_OS_MEMORY_PAGE_SIZE);
        }
        void FreeToSharedMemorySpace(MemoryBlockBase* p)
        {
            AddressSpaceManager* pManager = reinterpret_cast<AddressSpaceManager*>(&s_SpaceManager);
            pManager->Free(p);
        }

    } // detail


Result SharedMemoryBlock::Map(size_t size, bool readOnly)
{
    // Check that it is uninitialized.
    NN_TASSERTMSG_( GetAddress() == NULL, "This SharedMemoryBlock instance has been already initialized.\n" );
    if ( GetAddress() )
    {
        return ResultAlreadyInitialized();
    }
    
    // Check alignment.
    if ( ( size % NN_OS_MEMORY_PAGE_SIZE ) != 0 )
    {
        return ResultMisalignedSize();
    }
    
    // Get memory from the virtual address space.
    uptr addr = os::detail::AllocateFromSharedMemorySpace(this, size);
    if (addr == NULL)
    {
        return ResultNoAddressSpace();
    }

    this->MemoryBlockBase::SetReadOnly(readOnly);

    Result result;
    const bit32 myPermission = readOnly ? MEMORY_PERMISSION_READ : (MEMORY_PERMISSION_READ | MEMORY_PERMISSION_WRITE);
    result = nn::svc::MapMemoryBlock(GetHandle(), addr, myPermission, os::MEMORY_PERMISSION_DONT_CARE);
    NN_UTIL_RETURN_IF_FAILED(result);
    m_SpaceAllocated = true;

    // TODO: When the nn::svc::QueryMemory operation stabilizes, this comment-out will be deleted
    //MemoryInfo  memoryInfo;
    //PageInfo    pageInfo;
    //result = nn::svc::QueryMemory(&memoryInfo, &pageInfo, addr);
    //if (result.IsFailure())
    //{
    //    NN_TPANIC_("QueryMemory failed.");
    //}
    //
    //// Can it also be done by remapping with the acquired size?
    //if (memoryInfo.size != size)
    //{
    //    NN_TPANIC_("Mismatch size.");
    //}
    
    return result;
}

Result SharedMemoryBlock::TryInitialize(size_t size, bool readOnly, bool otherReadOnly, bool noMap)
{
    size = GetPageAlignedSize(size);
    bit32 myPermission = readOnly ? MEMORY_PERMISSION_READ : MEMORY_PERMISSION_READ | MEMORY_PERMISSION_WRITE;
    bit32 otherPermission = otherReadOnly ? MEMORY_PERMISSION_READ : MEMORY_PERMISSION_READ | MEMORY_PERMISSION_WRITE;

    Handle handle;
    Result result;
    result = nn::svc::CreateMemoryBlock(&handle, NULL, size, myPermission, otherPermission);
    NN_UTIL_RETURN_IF_FAILED(result);
    this->SetHandle(handle);

    if (!noMap)
    {
        result = Map(size, readOnly);
    }
    return result;
}

void SharedMemoryBlock::Initialize(size_t size, bool readOnly, bool otherReadOnly, bool noMap)
{
    NN_OS_ERROR_IF_FAILED(TryInitialize(size, readOnly, otherReadOnly, noMap));
}

Result SharedMemoryBlock::AttachAndMap(Handle handle, size_t size, bool readOnly)
{
    // TODO: If SVC is maintained, insert size or attribute check code.
    size = GetPageAlignedSize(size);

    this->SetHandle(handle);
    return Map(size, readOnly);
}

void SharedMemoryBlock::Unmap()
{
    if (GetAddress() != NULL)
    {
        if( m_SpaceAllocated )
        {
            NN_OS_ERROR_IF_FAILED(nn::svc::UnmapMemoryBlock(GetHandle(), GetAddress()));
            os::detail::FreeToSharedMemorySpace(this);
        }
        else
        {
            SetAddressAndSize(0, 0);
        }
    }
}

void SharedMemoryBlock::Finalize()
{
    if (this->IsValid())
    {
        Unmap();
        this->HandleObject::Close();
    }
}


}}

#include <new>
using namespace nn::os;

// SharedMemoryBlock

void nnosSharedMemoryBlockAllocate(nnosSharedMemoryBlock* this_, size_t size, bool readOnly, bool otherReadOnly, bool noMap)
{
    new (this_) SharedMemoryBlock(size, readOnly, otherReadOnly, noMap);
}

void nnosSharedMemoryBlockInitializeNoAllocate(nnosSharedMemoryBlock* this_)
{
    new (this_) SharedMemoryBlock();
}

void nnosSharedMemoryBlockFree(nnosSharedMemoryBlock* this_)
{
    SharedMemoryBlock* pSharedMemoryBlock = reinterpret_cast<SharedMemoryBlock*>(this_);
    pSharedMemoryBlock->~SharedMemoryBlock();
}

uptr nnosSharedMemoryBlockGetAddress(nnosSharedMemoryBlock* this_)
{
    SharedMemoryBlock* pSharedMemoryBlock = reinterpret_cast<SharedMemoryBlock*>(this_);
    return pSharedMemoryBlock->GetAddress();
}

size_t nnosSharedMemoryBlockGetSize(nnosSharedMemoryBlock* this_)
{
    SharedMemoryBlock* pSharedMemoryBlock = reinterpret_cast<SharedMemoryBlock*>(this_);
    return pSharedMemoryBlock->GetSize();
}

bool nnosSharedMemoryBlockIsReadOnly(nnosSharedMemoryBlock* this_)
{
    SharedMemoryBlock* pSharedMemoryBlock = reinterpret_cast<SharedMemoryBlock*>(this_);
    return pSharedMemoryBlock->IsReadOnly();
}

#endif  // if NN_PLATFORM_HAS_MMU
