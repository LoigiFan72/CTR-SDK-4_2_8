/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_TransferMemoryBlock.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_TRANSFERMEMORYBLOCK_H_
#define NN_OS_OS_TRANSFERMEMORYBLOCK_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/os/os_MemoryBlockBase.h>
#include <nn/os/os_HandleObject.h>

#ifdef __cplusplus

namespace nn{ namespace os{


class TransferMemoryBlock : public MemoryBlockBase, public HandleObject
{
public:
    
    TransferMemoryBlock() : m_SpaceAllocated(false) {}
    ~TransferMemoryBlock() { Finalize(); }

    void Initialize(
        void*   p,
        size_t  size,
        bit32   myPermission    = os::MEMORY_PERMISSION_NONE,
        bit32   otherPermission = os::MEMORY_PERMISSION_READ_WRITE );

    Result TryInitialize(
        void*   p,
        size_t  size,
        bit32   myPermission    = os::MEMORY_PERMISSION_NONE,
        bit32   otherPermission = os::MEMORY_PERMISSION_READ_WRITE );

    void Finalize();


private:
    friend class HandleManager;

    Result AttachAndMap(
        Handle handle,
        size_t  size,
        bit32   otherPermission,
        bit32   myPermission );

    Result Map(
        size_t  size,
        bit32   otherPermission,
        bit32   myPermission );

    void Unmap(void);

private:
    bool    m_SpaceAllocated;
    NN_PADDING3;
    NN_PADDING4;
};

}} // namespace nn::os

#endif

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_TRANSFERMEMORYBLOCK_H_ */
