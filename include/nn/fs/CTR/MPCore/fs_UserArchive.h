/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_UserArchive.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_CTR_MPCORE_FS_USERARCHIVE_H_
#define NN_FS_CTR_MPCORE_FS_USERARCHIVE_H_

#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>

namespace nn { namespace fs { namespace CTR { namespace MPCore { namespace detail {

class IFile
{
public:
    virtual Result TryRead(s32* pOut, s64 offset, void* buffer, size_t size) = 0;
    virtual Result TryWrite(s32* pOut, s64 offset, const void* buffer, size_t size, bool flush=true) = 0;
    virtual Result TryGetSize(s64* pOut) const = 0;
    virtual Result TrySetSize(s64 size) = 0;
    virtual Result TryFlush() = 0;
    
    virtual Result TrySetPriority(s32 priority) = 0;
    virtual Result TryGetPriority(s32* pOut) const = 0;
    
    virtual Result DuplicateHandle(Handle* pOut, s64 offset, s64 length) = 0;
    virtual Result OpenLinkHandle(Handle* pOut) = 0;
    
    virtual Handle GetFileHandle() { return nn::Handle(); }
    virtual void DetachFileHandle() { }
    
    virtual void Close() = 0;
    
    virtual ~IFile() {}
};

class IDirectory
{
public:
    virtual Result TryRead(s32* pNumEntriesOut, DirectoryEntry pEntries[], s32 numEntries) = 0;
    
    virtual void Close() = 0;
    
    virtual Result TrySetPriority(s32 priority) = 0;
    virtual Result TryGetPriority(s32* pOut) const = 0;
    
    virtual ~IDirectory() {}
};

class IArchive
{
public:
    virtual Result OpenFile(IFile** pOut, const Path& path, bit32 mode) = 0;
    virtual Result OpenDirectory(IDirectory** pOut, const Path& path) = 0;
    virtual Result DeleteFile(const Path& path) = 0;
    virtual Result RenameFile(const Path& currentPath, const Path& newPath) = 0;
    virtual Result DeleteDirectory(const Path& path) = 0;
    virtual Result DeleteDirectoryRecursively(const Path& path) = 0;
    virtual Result CreateFile(const Path& path, s64 size) = 0;
    virtual Result CreateDirectory(const Path& path) = 0;
    virtual Result RenameDirectory(const Path& currentPath, const Path& newPath) = 0;
    virtual Result SetArchivePriority(s32) = 0;
    virtual Result GetArchivePriority(s32*) = 0;
    virtual Result GetFreeBytes(s64*) { return nn::fs::ResultUnsupportedOperation(); }

    virtual void DeleteObject() = 0;
    
    virtual ~IArchive() {}
};

Result RegisterArchive(const char* path, IArchive* archive, bool isAddOnContent = false, bool isAlias = false);

}}}}}

#endif
