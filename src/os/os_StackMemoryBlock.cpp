/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_StackMemoryBlock.cpp

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

#include <nn/os/os_StackMemoryBlock.h>
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
        size_t GetPageAlignedSize(size_t size)
        {
            return (size + NN_OS_MEMORY_PAGE_SIZE - 1) & ~(NN_OS_MEMORY_PAGE_SIZE - 1);
        }
    }

    namespace detail
    {
        void Switch(StackMemoryBlock* pTo, StackMemoryBlock* pFrom)
        {
            Switch( reinterpret_cast<MemoryBlock*>(pTo),
                    reinterpret_cast<MemoryBlock*>(pFrom) );
        }
    }


// Allocate a memory block from the stack region.
void StackMemoryBlock::Initialize(size_t size)
{
    // Check that the memory block has been initialized and that this instance is not initialized.
    NN_TASSERTMSG_(os::detail::IsMemoryBlockEnabled(), "InitializeMemoryBlock is not called.\n");
    NN_TASSERTMSG_(GetAddress() == 0, "This StackMemoryBlock instance has been already initialized.\n");
    if ( !os::detail::IsMemoryBlockEnabled() || GetAddress() != 0 )
    {
        return;
    }

    size = GetPageAlignedSize(size);

    // Get memory from the virtual address space.
    uptr addr = os::detail::AllocateFromMemoryBlockSpace(this, size);
    if (addr == NULL)
    {
        NN_OS_ERROR_IF_FAILED(ResultNoAddressSpace());
    }
}

void StackMemoryBlock::Finalize()
{
    if ( GetAddress() != NULL )
    {
        os::detail::FreeToMemoryBlockSpace(this);
    }
}

}} // namespace nn::os


#include <new>
using namespace nn::os;

extern "C" {

// StackMemoryBlock

void nnosStackMemoryBlockInitialize(nnosStackMemoryBlock* p)
{
    new (p) StackMemoryBlock();
}

void nnosStackMemoryBlockAllocate(nnosStackMemoryBlock* p, size_t size)
{
    NN_TASSERT_(os::detail::IsMemoryBlockEnabled());
    new (p) StackMemoryBlock(size);
}

void nnosStackMemoryBlockFree(nnosStackMemoryBlock* p)
{
    StackMemoryBlock* pStackMemoryBlock = reinterpret_cast<StackMemoryBlock*>(p);
    pStackMemoryBlock->~StackMemoryBlock();
}

uptr nnosStackMemoryBlockGetAddress(nnosStackMemoryBlock* p)
{
    StackMemoryBlock* pStackMemoryBlock = reinterpret_cast<StackMemoryBlock*>(p);
    return pStackMemoryBlock->GetAddress();
}

size_t nnosStackMemoryBlockGetSize(nnosStackMemoryBlock* p)
{
    StackMemoryBlock* pStackMemoryBlock = reinterpret_cast<StackMemoryBlock*>(p);
    return pStackMemoryBlock->GetSize();
}

uptr nnosStackMemoryBlockGetStackBottom(nnosStackMemoryBlock* p)
{
    StackMemoryBlock* pStackMemoryBlock = reinterpret_cast<StackMemoryBlock*>(p);
    return pStackMemoryBlock->GetStackBottom();
}

}
#endif  // if NN_PLATFORM_HAS_MMU
