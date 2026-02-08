/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_DirectoryBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_CTR_MPCORE_FS_DIRECTORYBASE_H_
#define NN_FS_CTR_MPCORE_FS_DIRECTORYBASE_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>
#include <nn/util/util_NonCopyable.h>

namespace nn { namespace fs { namespace detail {

class DirectoryBaseImpl : private nn::util::NonCopyable<DirectoryBaseImpl>
{
protected:
    typedef nn::fs::CTR::MPCore::detail::UserFileSystem UserFileSystem;

    DirectoryBaseImpl() : m_P(0) {}
    
    Result TryInitialize(const wchar_t* path)
    {
        return UserFileSystem::TryOpenDirectory(&m_P, path);
    }
    
    Result TryInitializeRaw(ArchiveHandle handle, const nn::fs::CTR::MPCore::Path& path)
    {
        return UserFileSystem::TryOpenDirectoryRaw(&m_P, handle, path);
    }
    
    void Finalize() { UserFileSystem::CloseDirectory(m_P); this->m_P = 0; }
    ~DirectoryBaseImpl() { Finalize(); }
    
    Result TryRead(s32* pOut, DirectoryEntry pEntries[], s32 numEntries) { return UserFileSystem::TryReadDirectory(pOut, m_P, pEntries, numEntries); }

    nn::Result TrySetPriority(s32 priority)
    {
        return UserFileSystem::TrySetPriorityForDirectory(m_P, priority);
    }
    nn::Result TryGetPriority(s32* pOut) const
    {
        return UserFileSystem::TryGetPriorityForDirectory(pOut, m_P);
    }

private:

    void* m_P;
    
    bool IsInitialized() const { return m_P != 0; }
};

}}}

#endif
