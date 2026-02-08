/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryBlock.cpp

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


#include <nn/assert.h>
#include <nn/dbg/dbg_Logger.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/os/os_Memory.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_StackMemoryBlock.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/svc/svc_Stub.h>
#include <nn/util/util_Result.h>

#include "os_AddressSpaceManager.h"

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::svc;

namespace nn{ namespace os{

    namespace
    {
        nnosAddressSpaceManager s_SpaceManager;
        bool s_IsMemoryBlockEnabled = false;
    }

    namespace detail
    {
        uptr AllocateFromMemoryBlockSpace(MemoryBlockBase* p, size_t s)
        {
            AddressSpaceManager* pManager = reinterpret_cast<AddressSpaceManager*>(&s_SpaceManager);
            return pManager->Allocate(p, s, 0);
        }
        void FreeToMemoryBlockSpace(MemoryBlockBase* p)
        {
            AddressSpaceManager* pManager = reinterpret_cast<AddressSpaceManager*>(&s_SpaceManager);
            pManager->Free(p);
        }
        void Switch(MemoryBlock* pTo, MemoryBlock* pFrom)
        {
            nnosAddressSpaceManagerSwitch(&s_SpaceManager, ConvertToC(pTo), ConvertToC(pFrom));
        }

        bool IsMemoryBlockEnabled()
        {
            return s_IsMemoryBlockEnabled;
        }
    }

void MemoryBlock::Initialize(size_t size)
{
    // Check that the memory block has been initialized and that this instance is not initialized.
    NN_TASSERTMSG_(os::detail::IsMemoryBlockEnabled(), "InitializeMemoryBlock is not called.\n");
    NN_TASSERTMSG_(GetAddress() == 0, "This MemoryBlock instance has been already initialized.\n");
    if ( !os::detail::IsMemoryBlockEnabled() || GetAddress() != 0 )
    {
        return;
    }
    
    // Get memory from the virtual address space.
    size = GetPageAlignedSize(size);
    uptr addr = os::detail::AllocateFromMemoryBlockSpace(this, size);
    if (addr == 0)
    {
        NN_OS_ERROR_IF_FAILED(ResultNoAddressSpace());
    }
    this->MemoryBlockBase::SetReadOnly(false);
}

void MemoryBlock::Finalize()
{
    if (GetAddress())
    {
        // Return the memory block to the virtual memory space.
        os::detail::FreeToMemoryBlockSpace(this);
    }
}

// Set the read-only attribute.
void MemoryBlock::SetReadOnly(bool readOnly)
{
    NN_TASSERT_(GetAddress());
    if (GetAddress() )
    {
        if (IsReadOnly() == readOnly)
        {
            return;
        }
        this->MemoryBlockBase::SetReadOnly(readOnly);
    }
}


void InitializeMemoryBlock(uptr begin, size_t size)
{
    if ( s_IsMemoryBlockEnabled )
    {
        NN_TASSERTMSG_(false, "nn::os::InitializeMemoryBlock() called twice.");
    }
    else
    {
        s_IsMemoryBlockEnabled = true;
        nnosAddressSpaceManagerInitialize(&s_SpaceManager, begin, size);
    }
}


}} // namespace nn::os


#include <new>
using namespace nn::os;

extern "C" {

// MemoryBlock

void nnosMemoryBlockAllocate(nnosMemoryBlock* p, size_t size)
{
    NN_TASSERT_(os::detail::IsMemoryBlockEnabled());
    new (p) MemoryBlock(size);
}

void nnosMemoryBlockSetReadOnly(nnosMemoryBlock* p, bool readOnly)
{
    MemoryBlock* pMemoryBlock = reinterpret_cast<MemoryBlock*>(p);
    pMemoryBlock->SetReadOnly(readOnly);
}

void nnosMemoryBlockFree(nnosMemoryBlock* p)
{
    MemoryBlock* pMemoryBlock = reinterpret_cast<MemoryBlock*>(p);
    pMemoryBlock->~MemoryBlock();
}

uptr nnosMemoryBlockGetAddress(nnosMemoryBlock* p)
{
    MemoryBlock* pMemoryBlock = reinterpret_cast<MemoryBlock*>(p);
    return pMemoryBlock->GetAddress();
}

size_t nnosMemoryBlockGetSize(nnosMemoryBlock* p)
{
    MemoryBlock* pMemoryBlock = reinterpret_cast<MemoryBlock*>(p);
    return pMemoryBlock->GetSize();
}

bool nnosMemoryBlockIsReadOnly(nnosMemoryBlock* p)
{
    MemoryBlock* pMemoryBlock = reinterpret_cast<MemoryBlock*>(p);
    return pMemoryBlock->IsReadOnly();
}


}
#endif  // if NN_PLATFORM_HAS_MMU
