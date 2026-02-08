/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SharedMemory.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_SHAREDMEMORY_H_
#define NN_OS_OS_SHAREDMEMORY_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/os/os_MemoryBlockBase.h>
#include <nn/os/os_HandleObject.h>

#ifdef __cplusplus

namespace nn{ namespace os{

    namespace detail
    {
        void InitializeSharedMemory();
        uptr AllocateFromSharedMemorySpace(MemoryBlockBase* p, size_t s);
        void FreeToSharedMemorySpace(MemoryBlockBase* p);
    }

class SharedMemoryBlock : public MemoryBlockBase, public HandleObject
{
public:
    SharedMemoryBlock() : m_SpaceAllocated(false) {}
    explicit SharedMemoryBlock(size_t size, bool readOnly = false, bool otherReadOnly = false, bool noMap = false) { Initialize(size, otherReadOnly, readOnly, noMap); }
    
    void Initialize(size_t size, bool readOnly = false, bool otherReadOnly = false, bool noMap = false);

    Result TryInitialize(size_t size, bool readOnly = false, bool otherReadOnly = false, bool noMap = false);

    ~SharedMemoryBlock() { Finalize(); }
    
    void Finalize();


private:

    friend class HandleManager;

    Result AttachAndMap(Handle handle, size_t size, bool readOnly);
    Result Map(size_t size, bool readOnly);
    void   Unmap(void);

private:
    bool    m_SpaceAllocated;
    NN_PADDING3;
    NN_PADDING4;
};

}} // namespace nn::os

#endif

// C declarations follow

#include <nn/util/detail/util_CLibImpl.h>

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosSharedMemoryBlock, nn::os::SharedMemoryBlock, 32, u32);
NN_EXTERN_C void nnosSharedMemoryBlockAllocate(nnosSharedMemoryBlock* this_, size_t size, bool readOnly, bool otherReadOnly, bool noMap);
NN_EXTERN_C void nnosSharedMemoryBlockInitializeNoAllocate(nnosSharedMemoryBlock* this_);
NN_EXTERN_C void nnosSharedMemoryBlockFree(nnosSharedMemoryBlock* this_);
NN_EXTERN_C uptr nnosSharedMemoryBlockGetAddress(nnosSharedMemoryBlock* this_);
NN_EXTERN_C size_t nnosSharedMemoryBlockGetSize(nnosSharedMemoryBlock* this_);
NN_EXTERN_C bool nnosSharedMemoryBlockIsReadOnly(nnosSharedMemoryBlock* this_);

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_SHAREDMEMORY_H_ */
