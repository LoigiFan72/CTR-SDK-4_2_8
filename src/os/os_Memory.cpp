/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Memory.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47383 $
 *---------------------------------------------------------------------------*/

#include <nn/os.h>
#include <nn/assert.h>
#include <nn/svc.h>
#include <nn/dbg.h>
#include <nn/util.h>
#include <nn/init.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/os/os_ErrorHandlerSelect.h>

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::svc;

extern "C" bit8 Load$$LR$$TEXT_SECTION$$Base[];
extern "C" bit8 Load$$LR$$TEXT_SECTION$$Length[];

namespace nn{ namespace os{

namespace 
{
    uptr    s_DeviceMemoryAddress   = 0; //
    size_t  s_DeviceMemorySize      = 0; //

    size_t  s_HeapSize      = 0;         //
}


// Gets the device memory address.
uptr GetDeviceMemoryAddress()
{
    NN_TASSERTMSG_(s_DeviceMemoryAddress != NULL, "Device Memory is NOT Initialized.");
    return s_DeviceMemoryAddress;
}
    
// Sets the device memory size.
Result SetDeviceMemorySize(size_t size)
{
    // The device memory size must be a multiple of 4096.
    if ( (size % NN_OS_MEMORY_PAGE_SIZE) != 0 )
    {
        return ResultMisalignedSize();
    }
    Result result;

    if( size > s_DeviceMemorySize )
    {
        // Allocates device memory.
        // If device memory has already been allocated, immediately allocates the portion of continuous memory that was insufficient
        if (s_DeviceMemorySize != 0)
        {
            // If already allocated, the size before and after must be 1 MiB aligned.
            if (!(s_DeviceMemorySize % (1024 * 1024) == 0 && size % (1024 * 1024) == 0))
            {
                return ResultMisalignedSize();
            }
        }
        uptr addr;
        const size_t mapSize = size - s_DeviceMemorySize;
        const uptr requestAddress = (s_DeviceMemorySize == 0) ? NULL: (s_DeviceMemoryAddress + s_DeviceMemorySize);

        // Continuous memory can be allocated by specifying nn::os::MEMORY_OPERATION_FLAG_LINEAR.
        result = nn::svc::ControlMemory( &addr,
                                         requestAddress,
                                         NULL,
                                         mapSize,
                                         (nn::os::MEMORY_OPERATION_COMMIT | nn::os::MEMORY_OPERATION_FLAG_LINEAR),
                                         nn::os::MEMORY_PERMISSION_READ_WRITE );

        if( result.IsSuccess() )
        {
            // If this is not the first time device memory has been allocated, checks if memory was obtained for the continuous address.
            NN_TASSERT_( s_DeviceMemorySize == 0 || addr == requestAddress );

            // For first time device memory allocation, save addresses.
            if( s_DeviceMemorySize == 0 )
            {
                s_DeviceMemoryAddress   = addr;
            }

            s_DeviceMemorySize  = size;
        }
    }
    else
    {
        // Releases unnecessary memory of size amount from the end of the device memory.
        uptr addr;
        const size_t unmapSize = s_DeviceMemorySize - size;
        const uptr freeAddress = s_DeviceMemoryAddress + size;

        result = nn::svc::ControlMemory( &addr,
                                         freeAddress,
                                         NULL,
                                         unmapSize,
                                         nn::os::MEMORY_OPERATION_FREE,
                                         nn::os::MEMORY_PERMISSION_NONE );

        if( result.IsSuccess() )
        {
            if( size == 0 )
            {
                s_DeviceMemoryAddress   = NULL;
            }

            s_DeviceMemorySize  = size;
        }
    }

    return result;
}

// Gets the device memory size.
size_t GetDeviceMemorySize()
{
    return s_DeviceMemorySize;
}

// Sets the heap size.
Result SetHeapSize(size_t size)
{
    NN_TASSERTMSG_( ! nninitIsStartUpDefaultUsing(),
        "Using default nninitStartUp.\nPlease override nninitStartUp.");

    // The heap size must be a multiple of 4096.
    if ( (size % NN_OS_MEMORY_PAGE_SIZE) != 0 )
    {
        return ResultMisalignedSize();
    }
    Result result;

    if( size > s_HeapSize )
    {
        // Allocate a region in size amount from the start of the heap.
        // If already allocated, immediately afterwards allocates the memory size that was insufficient
        uptr addr;
        const size_t mapSize = size - s_HeapSize;
        const uptr requestAddress = NN_OS_ADDR_HEAP_BEGIN + s_HeapSize;

        result = nn::svc::ControlMemory( &addr,
                                         requestAddress,
                                         NULL,
                                         mapSize,
                                         nn::os::MEMORY_OPERATION_COMMIT,
                                         nn::os::MEMORY_PERMISSION_READ_WRITE );

        if( result.IsSuccess() )
        {
            NN_TASSERT_( addr == requestAddress );
            s_HeapSize  = size;
        }
    }
    else
    {
        // Releases unnecessary memory region in size amount from the end of the heap.
        uptr addr;
        const size_t unmapSize = s_HeapSize - size;
        const uptr freeAddress = NN_OS_ADDR_HEAP_BEGIN + size;

        result = nn::svc::ControlMemory( &addr,
                                         freeAddress,
                                         NULL,
                                         unmapSize,
                                         nn::os::MEMORY_OPERATION_FREE,
                                         nn::os::MEMORY_PERMISSION_NONE );

        if( result.IsSuccess() )
        {
            s_HeapSize  = size;
        }
    }

    return result;
}

uptr GetHeapAddress()
{
    NN_TASSERTMSG_( ! nninitIsStartUpDefaultUsing(),
        "Using default nninitStartUp.\nPlease override nninitStartUp.");
    return nn::os::detail::GetHeapAddressWithoutCheck();
}

// Get heap size.
size_t GetHeapSize()
{
    NN_TASSERTMSG_( ! nninitIsStartUpDefaultUsing(),
        "Using default nninitStartUp.\nPlease override nninitStartUp.");
    return s_HeapSize;
}

uptr GetCodeRegionAddress()
{
    return reinterpret_cast<uptr>(Load$$LR$$TEXT_SECTION$$Base);
}

size_t GetCodeRegionSize()
{
    return reinterpret_cast<size_t>(Load$$LR$$TEXT_SECTION$$Length);
}

#if NN_PLATFORM_HAS_MMU
void SetupHeapForMemoryBlock(size_t heapSize)
{
    Result result;

    result = SetHeapSize( heapSize );
    NN_OS_ERROR_IF_FAILED( result );

    InitializeMemoryBlock(GetHeapAddress(), GetHeapSize());

    SetDefaultAutoStackManager();
}
#endif  // if NN_PLATFORM_HAS_MMU





}} // namespace nn::os


#include <new>
using namespace nn::os;

extern "C" {

uptr nnosGetDeviceMemoryAddress()
{
    return nn::os::GetDeviceMemoryAddress();
}

}
