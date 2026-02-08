/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_TransferMemoryBlock.cpp

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
#include <nn/os/os_TransferMemoryBlock.h>
#include <nn/os/os_SharedMemory.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include "os_AddressSpaceManager.h"

namespace nn { namespace os {

void TransferMemoryBlock::Initialize(
        void*   p,
        size_t  size,
        bit32   myPermission,
        bit32   otherPermission )
{
    NN_OS_ERROR_IF_FAILED(TryInitialize(p, size, myPermission, otherPermission));
}

Result TransferMemoryBlock::TryInitialize(
        void*   p,
        size_t  size,
        bit32   myPermission,
        bit32   otherPermission )
{
    // Check that it is uninitialized.
    NN_TASSERTMSG_( GetAddress() == NULL, "This TransferMemoryBlock instance has been already initialized.\n" );
    if ( GetAddress() )
    {
        return ResultAlreadyInitialized();
    }
    
    // Check alignment.
    if ( (reinterpret_cast<uptr>(p) % NN_OS_MEMORY_PAGE_SIZE ) != 0 )
    {
        return ResultMisalignedAddress();
    }
    if ( ( size % NN_OS_MEMORY_PAGE_SIZE ) != 0 )
    {
        return ResultMisalignedSize();
    }

    Handle handle;
    Result result;
    result = nn::svc::CreateMemoryBlock(&handle, reinterpret_cast<uptr>(p), size, myPermission, otherPermission);
    NN_UTIL_RETURN_IF_FAILED(result);
    this->SetHandle(handle);

    SetAddressAndSize(reinterpret_cast<uptr>(p), size);
    return result;
}

void TransferMemoryBlock::Finalize()
{
    if (this->IsValid())
    {
        Unmap();
        this->HandleObject::Close();
    }
}




Result TransferMemoryBlock::AttachAndMap(
        Handle  handle,
        size_t  size,
        bit32   otherPermission,
        bit32   myPermission )
{
    // Check alignment.
    if ( ( size % NN_OS_MEMORY_PAGE_SIZE ) != 0 )
    {
        return ResultMisalignedSize();
    }

    this->SetHandle(handle);
    return Map(size, otherPermission, myPermission);
}

Result TransferMemoryBlock::Map(
        size_t  size,
        bit32   otherPermission,
        bit32   myPermission )
{
    // Check that it is uninitialized.
    NN_TASSERT_( GetAddress() == NULL );
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

    this->MemoryBlockBase::SetReadOnly((myPermission & os::MEMORY_PERMISSION_WRITE) == 0);

    Result result = nn::svc::MapMemoryBlock(GetHandle(), addr, myPermission, otherPermission);
    if( result.IsFailure() )
    {
        os::detail::FreeToSharedMemorySpace(this);
        return result;
    }

    m_SpaceAllocated = true;
    return result;
}

void TransferMemoryBlock::Unmap()
{
    if (GetAddress() != NULL)
    {
        if( m_SpaceAllocated )
        {
            nn::svc::UnmapMemoryBlock(GetHandle(), GetAddress());
            os::detail::FreeToSharedMemorySpace(this);
        }
        else
        {
            SetAddressAndSize(0, 0);
        }
    }
}


}}

#endif  // if NN_PLATFORM_HAS_MMU
