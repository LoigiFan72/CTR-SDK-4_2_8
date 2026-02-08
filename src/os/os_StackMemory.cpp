/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_StackMemory.cpp

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

#include <nn/os/os_StackMemory.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_Result.h>
#include <nn/assert.h>
#include <nn/svc/svc_Stub.h>
#include <nn/dbg/dbg_Logger.h>
#include <nn/util/util_Result.h>
#include <nn/os/os_Memory.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include "os_AddressSpaceManager.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::svc;

namespace nn{ namespace os{

    namespace
    {
        nnosAddressSpaceManager s_SpaceManager;
    }

    namespace detail
    {
        void InitializeStackMemory()
        {
            nnosAddressSpaceManagerInitialize(&s_SpaceManager, NN_OS_ADDR_STACK_BEGIN, NN_OS_ADDR_STACK_SIZE);
        }
    }


void StackMemory::Initialize(void* pMem, size_t size)
{
    NN_OS_ERROR_IF_FAILED(TryInitialize(pMem, size));
}

Result StackMemory::TryInitialize(void* pMem, size_t size)
{
    // Check that it is uninitialized.
    if ( GetAddress() )
    {
        return ResultAlreadyInitialized();
    }
    
    // Check alignment.
    //NN_ALIGN_TASSERT_( pMem, NN_OS_MEMORY_PAGE_SIZE );
    //NN_ALIGN_TASSERT_( size, NN_OS_MEMORY_PAGE_SIZE );
    if ( ( size % NN_OS_MEMORY_PAGE_SIZE ) != 0 )
    {
        return ResultMisalignedSize();
    }
    if ( ( reinterpret_cast<uptr>(pMem) % NN_OS_MEMORY_PAGE_SIZE ) != 0 )
    {
        return ResultMisalignedAddress();
    }
    
    // Get memory from the virtual address space.
    uptr addr = nnosAddressSpaceManagerAllocate(&s_SpaceManager, os::detail::ConvertToC(this), size, NN_OS_MEMORY_PAGE_SIZE);
    if (addr == NULL)
    {
        return ResultNoAddressSpace();
    }

    m_MemoryAddress = reinterpret_cast<uptr>(pMem);

    Result result;
    uptr dummy;
    result = nn::svc::ControlMemory( &dummy,
                                     addr,
                                     m_MemoryAddress,
                                     size,
                                     nn::os::MEMORY_OPERATION_MAP,
                                     nn::os::MEMORY_PERMISSION_READ_WRITE );
    
    if ( result.IsFailure() )
    {
        nnosAddressSpaceManagerFree(&s_SpaceManager, os::detail::ConvertToC(this));
        
        return result;
    }
    
    result = nn::svc::ControlMemory( &dummy,
                                     m_MemoryAddress,
                                     NULL,
                                     size,
                                     nn::os::MEMORY_OPERATION_PROTECT,
                                     nn::os::MEMORY_PERMISSION_NONE );
    
    if ( result.IsFailure() )
    {
        uptr memAddr = m_MemoryAddress;

        nnosAddressSpaceManagerFree(&s_SpaceManager, os::detail::ConvertToC(this));

        nn::svc::ControlMemory( &dummy,
                                addr,
                                memAddr,
                                size,
                                nn::os::MEMORY_OPERATION_UNMAP,
                                nn::os::MEMORY_PERMISSION_READ_WRITE );
    }
    
    return result;
}

void* StackMemory::Finalize()
{
    if ( GetAddress() != NULL )
    {
        const uptr addr = GetAddress();
        const size_t size = GetSize();
        const uptr memAddr = m_MemoryAddress;

        nnosAddressSpaceManagerFree(&s_SpaceManager, os::detail::ConvertToC(this));

        Result result;
        uptr dummy;
        result = nn::svc::ControlMemory( &dummy,
                                         addr,
                                         memAddr,
                                         size,
                                         nn::os::MEMORY_OPERATION_UNMAP,
                                         nn::os::MEMORY_PERMISSION_READ_WRITE );
        NN_OS_ERROR_IF_FAILED(result);
        // Hereafter, must not access this

        result = nn::svc::ControlMemory( &dummy,
                                         memAddr,
                                         NULL,
                                         size,
                                         nn::os::MEMORY_OPERATION_PROTECT,
                                         nn::os::MEMORY_PERMISSION_READ_WRITE );
        NN_OS_ERROR_IF_FAILED(result);

        return reinterpret_cast<void*>(memAddr);
    }

    return NULL;
}

void StackMemory::MoveFrom(StackMemory* pFrom)
{
    reinterpret_cast<AddressSpaceManager*>(&s_SpaceManager)->Switch(this, pFrom);
    this->m_MemoryAddress = pFrom->m_MemoryAddress;
    pFrom->m_MemoryAddress = NULL;
}


}} // namespace nn::os


#include <new>
using namespace nn::os;

extern "C" {

// StackMemory

void nnosStackMemoryProtect(nnosStackMemory* p, void* pMem, size_t size)
{
    new (p) StackMemory(pMem, size);
}

void nnosStackMemoryUnprotect(nnosStackMemory* p)
{
    StackMemory* pStackMemory = reinterpret_cast<StackMemory*>(p);
    pStackMemory->~StackMemory();
}

uptr nnosStackMemoryGetAddress(nnosStackMemory* p)
{
    StackMemory* pStackMemory = reinterpret_cast<StackMemory*>(p);
    return pStackMemory->GetAddress();
}

size_t nnosStackMemoryGetSize(nnosStackMemory* p)
{
    StackMemory* pStackMemory = reinterpret_cast<StackMemory*>(p);
    return pStackMemory->GetSize();
}

uptr nnosStackMemoryGetStackBottom(nnosStackMemory* p)
{
    StackMemory* pStackMemory = reinterpret_cast<StackMemory*>(p);
    return pStackMemory->GetStackBottom();
}

}
#endif  // if NN_PLATFORM_HAS_MMU
