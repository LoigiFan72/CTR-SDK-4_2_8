/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_UserFileSystem.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_CTR_MPCORE_FS_USERFILESYSTEM_H_
#define NN_FS_CTR_MPCORE_FS_USERFILESYSTEM_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/fs_Result.h>
#include <nn/util/util_NonCopyable.h>

#include <nn/os.h>
#include <nn/fnd.h>

#include <nn/fslow/fslow_Path.h>

namespace nn { namespace fs { namespace CTR { namespace MPCore {

typedef nn::fslow::LowPath<const char*, const wchar_t*> Path;

namespace detail {

class UserFileSystem
{
public:
    static Result Initialize(nn::Handle handle);
    static void Finalize();
    
    // File and directory operations
    static void OpenDirect(void** pOut, Handle handle);
    static void CloseDirect(void* p);
    static Handle GetFileHandle(void* p);
    static void DetachHandle(void *p);
    
    static Result DuplicateHandleForFile(Handle* pOut, void* p, s64 offset, s64 length);
    
    static Result TryOpenFile(void** pOut, const wchar_t* pathName, bit32 mode);
    static void CloseFile(void* p);
    
    static Result TryReadFile(s32* pOut, void* p, s64 offset, void* buffer, size_t size);
    static Result TryWriteFile(s32* pOut, void* p, s64 offset, const void* buffer, size_t size, bool flush=true);
    static Result TryGetFileSize(s64* pOut, const void* p);
    static Result TrySetFileSize(void* p, s64 size);
    static Result TryFlush(void* p);
    
    static Result TrySetPriorityForFile(void* p, s32 priority);
    static Result TryGetPriorityForFile(s32* pOut, const void* p);
    static Result TrySetPriorityForDirectory(void* p, s32 priority);
    static Result TryGetPriorityForDirectory(s32* pOut, const void* p);
    
    static Result TryOpenDirectory(void** pOut, const wchar_t* pathName);
    static void CloseDirectory(void* p);
    
    static Result TryReadDirectory(s32* pOut, void* p, DirectoryEntry pEntries[], s32 numEntries);
    
    static Result TryDeleteFile(const wchar_t* pathName);
    static Result TryRenameFile(const wchar_t* currentPath, const wchar_t* newPath);
    static Result TryDeleteDirectory(const wchar_t* pathName);
    static Result TryDeleteDirectoryRecursively(const wchar_t* pathName);
    static Result TryCreateFile(const wchar_t* pathName, s64 size);
    static Result TryCreateDirectory(const wchar_t* pathName);
    static Result TryRenameDirectory(const wchar_t* currentPath, const wchar_t* newPath);
    
    // raw
    static Result TryOpenFileRaw(void** pOut, ArchiveHandle archiveHandle, const Path& path, bit32 mode);
    static Result TryOpenFileRawDirectly(void** pOut, bit32 archiveType, const Path& archivePath, const Path& path, bit32 mode);
    static Result TryOpenDirectoryRaw(void** pOut, ArchiveHandle archiveHandle, const Path& path);
    static Result TryDeleteFileRaw(ArchiveHandle archiveHandle, const Path& path);
    static Result TryRenameFileRaw(ArchiveHandle currentArchiveHandle, const Path& currentPath, ArchiveHandle newArchiveHandle, const Path& newPath);
    static Result TryDeleteDirectoryRaw(ArchiveHandle archiveHandle, const Path& path);
    static Result TryDeleteDirectoryRecursivelyRaw(ArchiveHandle archiveHandle, const Path& path);
    static Result TryCreateDirectoryRaw(ArchiveHandle archiveHandle, const Path& path);
    static Result TryRenameDirectoryRaw(ArchiveHandle currentArchiveHandle, const Path& currentPath, ArchiveHandle newArchiveHandle, const Path& newPath);
};

}}}}}

#endif
