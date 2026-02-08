/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_New.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/svc.h>
#include <nn/Result.h>
#include <nn/init.h>
#include <nn/config.h>
#include <nn/assert.h>
#include <nn/util/util_Result.h>
#include <nn/fnd/fnd_ExpHeap.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_MemoryBlock.h>
#include <stdlib.h>

#include <new>

namespace nn{ namespace test{

    void InitializeAllocator(size_t size)
    {
#if NN_PLATFORM_HAS_MMU
        nn::os::SetupHeapForMemoryBlock( size );
        nn::init::InitializeAllocator( size/2 );
#else
        NN_UNUSED_VAR(size);
#endif
    }
}}


namespace nn { namespace drivers { namespace fnd {
    extern nn::fnd::MemoryRange AllocateBuffer(size_t requiredSize, size_t idealSize)
    {
        NN_UNUSED_VAR(idealSize);
        void* p = malloc(requiredSize);
        NN_TASSERT_(p);
        uptr begin = reinterpret_cast<uptr>(p);
        return nn::fnd::MemoryRange(begin, begin + requiredSize);
    }

    extern void DeallocateBuffer(const nn::fnd::MemoryRange& memoryRange)
    {
        free(reinterpret_cast<void*>(memoryRange.GetAddress()));
    }

    // Allocates a relatively small object
    extern void* AllocateSmall(size_t size)
    {
        return malloc(size);
    }
    extern void DeallocateSmall(void* p, size_t)
    {
        free(p);
    }
}}}
