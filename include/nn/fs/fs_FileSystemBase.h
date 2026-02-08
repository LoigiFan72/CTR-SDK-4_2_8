/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileSystemBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_FILESYSTEMBASE_H_
#define NN_FS_FS_FILESYSTEMBASE_H_

#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <nn/err.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/util/util_Result.h>

#ifdef NN_PLATFORM_CTR
    #include <nn/fs/CTR/fs_FileSystemBase.h>
#endif

namespace nn { namespace fs { namespace detail {

class FileSystemBase
{
public:
    FileSystemBase() : m_pImpl(NULL) {};
    ~FileSystemBase() {};

    void Initialize(FileSystemBaseImpl& impl);
    void Finalize();

    void DeleteFile( const wchar_t* pathName );
    void DeleteFile( const char* pathName );
    Result TryDeleteFile( const wchar_t* pathName );
    Result TryDeleteFile( const char* pathName );
    void RenameFile( const wchar_t* currentPath, const wchar_t* newPath);
    void RenameFile( const char* currentPath, const char* newPath);
    Result TryRenameFile( const wchar_t* currentPath, const wchar_t* newPath);
    Result TryRenameFile( const char* currentPath, const char* newPath);
    void DeleteDirectory( const wchar_t* pathName );
    void DeleteDirectory( const char* pathName );
    Result TryDeleteDirectory( const wchar_t* pathName );
    Result TryDeleteDirectory( const char* pathName );
    void DeleteDirectoryRecursively( const wchar_t* pathName );
    void DeleteDirectoryRecursively( const char* pathName );
    Result TryDeleteDirectoryRecursively( const wchar_t* pathName );
    Result TryDeleteDirectoryRecursively( const char* pathName );
    void CreateFile( const wchar_t* pathName, s64 size );
    void CreateFile( const char* pathName, s64 size );
    Result TryCreateFile( const wchar_t* pathName, s64 size );
    Result TryCreateFile( const char* pathName, s64 size );
    void CreateDirectory( const wchar_t* pathName );
    void CreateDirectory( const char* pathName );
    Result TryCreateDirectory( const wchar_t* pathName );
    Result TryCreateDirectory( const char* pathName );
    void RenameDirectory( const wchar_t* currentPath, const wchar_t* newPath);
    void RenameDirectory( const char* currentPath, const char* newPath);
    Result TryRenameDirectory( const wchar_t* currentPath, const wchar_t* newPath);
    Result TryRenameDirectory( const char* currentPath, const char* newPath);

private:
    FileSystemBaseImpl* m_pImpl;
};

inline void ConvertMbsToWcs(wchar_t* dst0, size_t dstLength, const char* src0)
{
    NN_UNUSED_VAR(dstLength);
    std::mbstate_t mbstate;
    std::memset(&mbstate, 0, sizeof(mbstate));
    std::mbsinit(&mbstate);
    const char* src = src0;
    wchar_t* dst = dst0;
    while (true)
    {
        size_t cLen = std::mbrlen(src, MAX_FILE_PATH_LENGTH, &mbstate);
        if (cLen == 0)
        {
            *dst = L'\0';
            break;
        }
        NN_TASSERTMSG_(static_cast<int>(cLen) > 0, "invalid multibyte character");
        int c = std::mbrtowc(dst, src, cLen, &mbstate);
        if (c == 0)
        {
            *dst = L'\0';
            break;
        }
        NN_TASSERT_(c > 0);
        NN_TASSERT_(dst - dst0 <= dstLength);
        dst++;
        src += cLen;
    }
}

class WPathBuffer
{
public:
    explicit WPathBuffer(const char* pathName)
    {
        ConvertMbsToWcs(m_pBuffer, sizeof(m_pBuffer)/sizeof(m_pBuffer[0])-1, pathName);
    }
    ~WPathBuffer() {}

    const wchar_t* GetBuffer() const { return m_pBuffer; }

private:
    wchar_t m_pBuffer[MAX_FILE_PATH_LENGTH + 1 + 8];
};

inline void FileSystemBase::Initialize(FileSystemBaseImpl& impl)
{
    NN_TASSERT_(!m_pImpl);

    m_pImpl = &impl;
}

inline void FileSystemBase::Finalize()
{
    m_pImpl->Finalize();
    m_pImpl = NULL;
}

inline void FileSystemBase::DeleteFile(const wchar_t* pathName)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryDeleteFile(pathName));
}

inline void FileSystemBase::DeleteFile(const char* pathName)
{
    WPathBuffer wpath(pathName);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryDeleteFile(wpath.GetBuffer()));
}

inline Result FileSystemBase::TryDeleteFile(const wchar_t* pathName)
{
    return m_pImpl->TryDeleteFile(pathName);
}

inline Result FileSystemBase::TryDeleteFile(const char* pathName)
{
    WPathBuffer wpath(pathName);
    return m_pImpl->TryDeleteFile(wpath.GetBuffer());
}

inline void FileSystemBase::RenameFile( const wchar_t* currentPath, const wchar_t* newPath)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryRenameFile(currentPath, newPath));
}

inline void FileSystemBase::RenameFile( const char* currentPath, const char* newPath)
{
    WPathBuffer wcurStr(currentPath);
    WPathBuffer wnewStr(newPath);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryRenameFile(wcurStr.GetBuffer(), wnewStr.GetBuffer()));
}

inline Result FileSystemBase::TryRenameFile( const wchar_t* currentPath, const wchar_t* newPath)
{
    return m_pImpl->TryRenameFile(currentPath, newPath);
}

inline Result FileSystemBase::TryRenameFile( const char* currentPath, const char* newPath)
{
    WPathBuffer wcurStr(currentPath);
    WPathBuffer wnewStr(newPath);
    return m_pImpl->TryRenameFile(wcurStr.GetBuffer(), wnewStr.GetBuffer());
}

inline void FileSystemBase::DeleteDirectory(const wchar_t* pathName)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryDeleteDirectory(pathName));
}

inline void FileSystemBase::DeleteDirectory(const char* pathName)
{
    WPathBuffer wpath(pathName);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryDeleteDirectory(wpath.GetBuffer()));
}

inline void FileSystemBase::DeleteDirectoryRecursively(const wchar_t* pathName)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryDeleteDirectoryRecursively(pathName));
}

inline void FileSystemBase::DeleteDirectoryRecursively(const char* pathName)
{
    WPathBuffer wpath(pathName);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryDeleteDirectoryRecursively(wpath.GetBuffer()));
}

inline Result FileSystemBase::TryDeleteDirectory(const wchar_t* pathName)
{
    return m_pImpl->TryDeleteDirectory(pathName);
}

inline Result FileSystemBase::TryDeleteDirectory(const char* pathName)
{
    WPathBuffer wpath(pathName);
    return m_pImpl->TryDeleteDirectory(wpath.GetBuffer());
}

inline Result FileSystemBase::TryDeleteDirectoryRecursively(const wchar_t* pathName)
{
    return m_pImpl->TryDeleteDirectoryRecursively(pathName);
}

inline Result FileSystemBase::TryDeleteDirectoryRecursively(const char* pathName)
{
    WPathBuffer wpath(pathName);
    return m_pImpl->TryDeleteDirectoryRecursively(wpath.GetBuffer());
}

inline void FileSystemBase::CreateFile(const wchar_t* pathName, s64 size)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryCreateFile(pathName, size));
}

inline void FileSystemBase::CreateFile(const char* pathName, s64 size)
{
    WPathBuffer wpath(pathName);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryCreateFile(wpath.GetBuffer(), size));
}

inline Result FileSystemBase::TryCreateFile(const wchar_t* pathName, s64 size)
{
    return m_pImpl->TryCreateFile(pathName, size);
}

inline Result FileSystemBase::TryCreateFile(const char* pathName, s64 size)
{
    WPathBuffer wpath(pathName);
    return m_pImpl->TryCreateFile(wpath.GetBuffer(), size);
}

inline void FileSystemBase::CreateDirectory(const wchar_t* pathName)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryCreateDirectory(pathName));
}

inline void FileSystemBase::CreateDirectory(const char* pathName)
{
    WPathBuffer wpath(pathName);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryCreateDirectory(wpath.GetBuffer()));
}

inline Result FileSystemBase::TryCreateDirectory(const wchar_t* pathName)
{
    return m_pImpl->TryCreateDirectory(pathName);
}

inline Result FileSystemBase::TryCreateDirectory(const char* pathName)
{
    WPathBuffer wpath(pathName);
    return m_pImpl->TryCreateDirectory(wpath.GetBuffer());
}

inline void FileSystemBase::RenameDirectory( const wchar_t* currentPath, const wchar_t* newPath)
{
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryRenameDirectory(currentPath, newPath));
}

inline void FileSystemBase::RenameDirectory( const char* currentPath, const char* newPath)
{
    WPathBuffer wcurStr(currentPath);
    WPathBuffer wnewStr(newPath);
    NN_ERR_THROW_FATAL_ALL(m_pImpl->TryRenameDirectory(wcurStr.GetBuffer(), wnewStr.GetBuffer()));
}

inline Result FileSystemBase::TryRenameDirectory( const wchar_t* currentPath, const wchar_t* newPath)
{
    return m_pImpl->TryRenameDirectory(currentPath, newPath);
}

inline Result FileSystemBase::TryRenameDirectory( const char* currentPath, const char* newPath)
{
    WPathBuffer wcurStr(currentPath);
    WPathBuffer wnewStr(newPath);
    return m_pImpl->TryRenameDirectory(wcurStr.GetBuffer(), wnewStr.GetBuffer());
}

void RegisterGlobalFileSystemBase(FileSystemBase& base);
FileSystemBase& GetGlobalFileSystemBase();

}}}
#endif
