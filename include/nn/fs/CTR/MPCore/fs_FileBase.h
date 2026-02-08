/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46480 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_CTR_MPCORE_FS_FILEBASE_H_
#define NN_FS_CTR_MPCORE_FS_FILEBASE_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/assert.h>
#include <nn/util/util_Result.h>
#include <nn/os/os_HandleObject.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/fs_Result.h>
#include <nn/util/util_NonCopyable.h>

#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>

namespace nn { namespace fs { namespace detail {

class FileBaseImpl : private nn::util::NonCopyable<FileBaseImpl>
{
protected:
    typedef nn::fs::CTR::MPCore::detail::UserFileSystem UserFileSystem;
    
    FileBaseImpl() : m_P(0) {}
    
    Result TryOpenImpl(const wchar_t* path, bit32 mode)
    {
        return UserFileSystem::TryOpenFile(&m_P, path, mode);
    }
    
    void Finalize()
    {
        if (GetPtr())
        {
            // For now, be sure to always Flush after Write
            NN_TPANIC_IF_FALSE_(!IsNotFlushed());

            UserFileSystem::CloseFile(GetPtr());
            this->m_P = 0; 
        }
    }
    ~FileBaseImpl() { Finalize(); }
    
    Result TryRead(s32* pOut, s64 offset, void* buffer, size_t size) { return UserFileSystem::TryReadFile(pOut, GetPtr(), offset, buffer, size); }
    Result TryWrite(s32* pOut, s64 offset, const void* buffer, size_t size, bool flush=true)
    {
        if (!flush)
        {
            NeedFlush();
        }
        else
        {
            DoneFlush();
        }
        return UserFileSystem::TryWriteFile(pOut, GetPtr(), offset, buffer, size, flush);
    }
    Result TryGetSize(s64* pOut) const { return UserFileSystem::TryGetFileSize(pOut, GetPtr()); }
    Result TrySetSize(s64 size) { return UserFileSystem::TrySetFileSize(GetPtr(), size); }
    Result TryFlush()
    {
        DoneFlush();
        return UserFileSystem::TryFlush(GetPtr());
    }

    Result TrySetPriority(s32 priority) { return UserFileSystem::TrySetPriorityForFile(GetPtr(), priority); }
    Result TryGetPriority(s32* pOut) const { return UserFileSystem::TryGetPriorityForFile(pOut, GetPtr()); }

public:

    Result DuplicateHandle(Handle* pOut, s64 offset, s64 length)
    {
        return UserFileSystem::DuplicateHandleForFile(pOut, GetPtr(), offset, length);
    }

    void OpenDirect(Handle handle)
    {
        UserFileSystem::OpenDirect(&m_P, handle);
    }
    
    void CloseDirect()
    {
        if (GetPtr())
        {
            UserFileSystem::CloseDirect(GetPtr());
            this->m_P = 0;
        }
    }
    
    Handle GetHandle()
    {
        return UserFileSystem::GetFileHandle(GetPtr());
    }
    
    void DetachHandle()
    {
        return UserFileSystem::DetachHandle(GetPtr());
    }
    
    Result TryInitializeRaw(ArchiveHandle handle, const nn::fs::CTR::MPCore::Path& path, bit32 mode)
    {
        return UserFileSystem::TryOpenFileRaw(&m_P, handle, path, mode);
    }
    
    Result TryInitializeRawDirectly(bit32 archiveType, const nn::fs::CTR::MPCore::Path& archivePath, const nn::fs::CTR::MPCore::Path& path, bit32 mode)
    {
        return UserFileSystem::TryOpenFileRawDirectly(&m_P, archiveType, archivePath, path, mode);
    }

    bool IsValid() { return GetHandle().IsValid(); }

private:

    // Because a value with 4-byte alignment is expected to be assigned, the lower 1 bit is used as a flag.
    void* m_P;

    bool IsInitialized() const { return GetPtr() != 0; }

    // Function for using the lower 1 bit of the address as a flag.
    void*   GetPtr() const  { return reinterpret_cast<void*>(reinterpret_cast<uptr>(m_P) & ~static_cast<uptr>(0x1)); }
    void    NeedFlush()     { m_P = reinterpret_cast<void*>(reinterpret_cast<uptr>(m_P) | 0x1); }
    void    DoneFlush()     { m_P = reinterpret_cast<void*>(reinterpret_cast<uptr>(m_P) & ~static_cast<uptr>(0x1)); }
    bool    IsNotFlushed()  { return (reinterpret_cast<uptr>(m_P) & 0x1) != 0; }
};

}}}

#endif
