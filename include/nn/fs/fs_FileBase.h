/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_FILEBASE_H_
#define NN_FS_FS_FILEBASE_H_

#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <nn/err.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/util/util_Int64.h>
#include <nn/fs/fs_FileSystemBase.h>

#ifdef NN_PLATFORM_CTR
    #include <nn/fs/CTR/fs_FileBase.h>
#endif

namespace nn { namespace fs { namespace detail {

class FileBase : public FileBaseImpl
{
protected:
    FileBase() : m_Position(0), m_Size(0) {}
    FileBase(const wchar_t* pathName, bit32 mode);
    FileBase(const char* pathName, bit32 mode);
    void Initialize(const wchar_t* pathName, bit32 mode);
    void Initialize(const char* pathName, bit32 mode);
    nn::Result TryInitialize(const wchar_t* pathName, bit32 mode);
    nn::Result TryInitialize(const char* pathName, bit32 mode);
    
    nn::Result TryRead(s32* pOut, void* buffer, size_t size);
    nn::Result TryWrite(s32* pOut, const void* buffer, size_t size, bool flush=true);
    nn::Result TrySeek(s64 position, PositionBase base);
    nn::Result TryGetPosition(s64* pOut) const;
    nn::Result TrySetPosition(s64 position);
    nn::Result TryGetSize(s64* pOut) const;
    nn::Result TrySetSize(s64 size);
    nn::Result TryFlush();
    s32 Read(void* buffer, size_t size);
    s32 Write(const void* buffer, size_t size, bool flush=true);
    void Seek(s64 position, PositionBase base);
    s64 GetPosition() const;
    void SetPosition(s64 position);
    s64 GetSize() const;
    void SetSize(s64 size);
    void Flush();
    void SetPriority(s32 priority);
    void GetPriority(s32* pOut) const;
    
private:
    
    typedef nn::util::Int64<s64> S64;
    S64 m_Position;
    mutable S64 m_Size;

#ifndef NN_PROCESSOR_ARM946ES
public:
    void OpenDirect(Handle handle)
    {
        this->m_Position = this->m_Size = 0;
        FileBaseImpl::OpenDirect(handle);
    }
#endif

};

inline nn::Result FileBase::TryInitialize(const wchar_t* pathName, bit32 mode)
{
    this->m_Position = this->m_Size = 0;
    return TryOpenImpl(pathName, mode);
}

inline nn::Result FileBase::TryInitialize(const char* pathName, bit32 mode)
{
    static const size_t BUF_SIZE = MAX_FILE_PATH_LENGTH + 1;
    wchar_t buffer[BUF_SIZE];
    ConvertMbsToWcs(buffer, MAX_FILE_PATH_LENGTH, pathName);
    return TryInitialize(buffer, mode);
}

inline void FileBase::Initialize(const wchar_t* pathName, bit32 mode)
{
    Result result = TryInitialize(pathName, mode);
    if (result.IsFailure())
    {
        NN_SLOG_("file open failed: ");
        NN_SLOG_("%lls\n", pathName);
        NN_ERR_THROW_FATAL_ALL(result);
    }
}

inline void FileBase::Initialize(const char* pathName, bit32 mode)
{
    Result result = TryInitialize(pathName, mode);
    if (result.IsFailure())
    {
        NN_SLOG_("file open failed: ");
        NN_SLOG_("%s\n", pathName);
        NN_ERR_THROW_FATAL_ALL(result);
    }
}

inline FileBase::FileBase(const wchar_t* pathName, bit32 mode)
{
    Initialize(pathName, mode);
}

inline FileBase::FileBase(const char* pathName, bit32 mode)
{
    Initialize(pathName, mode);
}

inline nn::Result FileBase::TryGetPosition(s64* pOut) const
{
    *pOut = m_Position;
    return ResultSuccess();
}

inline s32 FileBase::Read(void* buffer, size_t size)
{
    s32 ret;
    NN_ERR_THROW_FATAL_ALL(TryRead(&ret, buffer, size));
    return ret;
}

inline s32 FileBase::Write(const void* buffer, size_t size, bool flush)
{
    s32 ret;
    NN_ERR_THROW_FATAL_ALL(TryWrite(&ret, buffer, size, flush));
    return ret;
}

inline void FileBase::Seek(s64 position, PositionBase base)
{
    NN_ERR_THROW_FATAL_ALL(TrySeek(position, base));
}

inline s64 FileBase::GetPosition() const
{
    s64 ret;
    NN_ERR_THROW_FATAL_ALL(TryGetPosition(&ret));
    return ret;
}

inline void FileBase::SetPosition(s64 position)
{
    NN_ERR_THROW_FATAL_ALL(TrySetPosition(position));
}

inline s64 FileBase::GetSize() const
{
    s64 ret;
    NN_ERR_THROW_FATAL_ALL(TryGetSize(&ret));
    return ret;
}

inline void FileBase::SetSize(s64 size)
{
    NN_ERR_THROW_FATAL_ALL(TrySetSize(size));
}

inline void FileBase::Flush()
{
    NN_ERR_THROW_FATAL_ALL(TryFlush());
}

inline void FileBase::SetPriority(s32 priority)
{
    NN_ERR_THROW_FATAL_ALL(TrySetPriority(priority));
}

inline void FileBase::GetPriority(s32* pOut) const
{
    NN_ERR_THROW_FATAL_ALL(TryGetPriority(pOut));
}

}}}

#endif
