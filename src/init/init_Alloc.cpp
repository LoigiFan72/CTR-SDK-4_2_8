/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     init_Alloc.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------

#include <new>
#include <nn/Result.h>
#include <nn/config.h>
#include <nn/assert.h>
#include <nn/fnd.h>
#include <nn/init/init_Allocator.h>
#include <nn/os/os_LockPolicy.h>
#include <nn/os/os_Memory.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/svc/svc_stub.h>
#include <nn/util/util_Result.h>
#include <nn/util/util_TypeTraits.h>

#include <algorithm>
#include <cstring>

using namespace nn::os;

typedef nn::fnd::ExpHeapTemplate<nn::os::LockPolicy::Object<nn::os::CriticalSection> > SystemExpHeap;

namespace 
{
    SystemExpHeap*              s_pSystemHeap = 0;       //
    nn::util::aligned_storage<sizeof(SystemExpHeap::Allocator), nn::util::alignment_of<SystemExpHeap::Allocator>::value >::type s_SystemAllocatorBuffer;
    SystemExpHeap::Allocator*   s_pSystemAllocator = 0;  //<! Allocator for the system heap

#if NN_PLATFORM_HAS_MMU
    nnosMemoryBlock s_HeapMemoryBlock;
#endif  // if NN_PLATFORM_HAS_MMU
}

extern "C"{

    NN_WEAK_SYMBOL void* malloc(size_t size)
    {
        return s_pSystemHeap->Allocate(size);
    }

    NN_WEAK_SYMBOL void free(void* p)
    {
        if (p)
        {
            s_pSystemHeap->Free(p);
        }
    }

    NN_WEAK_SYMBOL void* calloc(size_t num, size_t size)
    {
        size_t sum = num * size;
        void* p = std::malloc(sum);

        if( p != NULL )
        {
            std::memset(p, 0, sum);
        }

        return p;
    }

    NN_WEAK_SYMBOL void* realloc(void* p, size_t size)
    {
        if( p != NULL )
        {
            // If the size is 0, it only frees
            if( size == 0 )
            {
                std::free(p);
                return NULL;
            }

            // If can be handled by changing the size of the memory block, do so
            // 
            size_t newSize = s_pSystemHeap->ResizeBlock(p, size);

            if( newSize != 0 )
            {
                return p;
            }

            // If it could not be handled, allocate and copy in addition
            void* newMem = std::malloc(size);

            if( newMem != NULL )
            {
                size_t oldSize = s_pSystemHeap->GetSizeOf(p);
                std::memcpy(newMem, p, std::min(size, oldSize));
                std::free(p);
            }

            return newMem;
        }
        else
        {
            // If p is NULL, only do malloc
            return std::malloc(size);
        }
    }

} // extern "C"


NN_WEAK_SYMBOL void* operator new (size_t size, const ::std::nothrow_t&) throw()
{
    return std::malloc(size);
}

NN_WEAK_SYMBOL void* operator new[] (size_t size, const ::std::nothrow_t&) throw()
{
    return operator new(size, ::std::nothrow_t());
}

NN_WEAK_SYMBOL void operator delete (void* p) throw()
{
    std::free(p);
}

NN_WEAK_SYMBOL void operator delete[] (void* p) throw()
{
    operator delete(p);
}

//NN_WEAK_SYMBOL void operator delete (void* p, const ::std::nothrow_t&) throw()
//{
//    if( p != 0 )
//    {
//        free(p);
//    }
//}

//NN_WEAK_SYMBOL void operator delete[] (void* p, const ::std::nothrow_t&) throw()
//{
//    if( p != 0 )
//    {
//        free(p);
//    }
//}

namespace nn { namespace init {

// Note
// Some of these peripheral functions are called from initStartup.
// Because initStartup is called before static initializer, if a non-POD class static object is initialized by these peripheral functions, it will be reinitialized with static initializer and not run properly.
// 
// 
// Implement with aligned_storage + placement new.

// Create system heap
void InitializeAllocator(uptr addr, size_t size)
{
    NN_TASSERT_(size >= sizeof(SystemExpHeap));
    const size_t alignment = nn::util::alignment_of<SystemExpHeap>::value;
    uptr heapAddr = (((addr - 1) / alignment) + 1) * alignment;
    uptr headAddr = heapAddr + sizeof(SystemExpHeap);
    s_pSystemHeap = new (reinterpret_cast<void*>(heapAddr)) SystemExpHeap(headAddr, addr + size - headAddr);
    s_pSystemAllocator = new (&s_SystemAllocatorBuffer) SystemExpHeap::Allocator(*s_pSystemHeap);
}

#if NN_PLATFORM_HAS_MMU
void InitializeAllocator(size_t size)
{
    nnosMemoryBlockAllocate(&s_HeapMemoryBlock, size);
    NN_TASSERT_(nnosMemoryBlockGetSize(&s_HeapMemoryBlock) == size);
    InitializeAllocator(nnosMemoryBlockGetAddress(&s_HeapMemoryBlock), size);
}
#endif  // if NN_PLATFORM_HAS_MMU

nn::fnd::IAllocator* GetAllocator(void)
{
    return s_pSystemAllocator;
}

}} // namespace nn::init

