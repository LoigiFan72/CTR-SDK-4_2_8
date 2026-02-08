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

#ifndef NN_FS_FS_DIRECTORYBASE_H_
#define NN_FS_FS_DIRECTORYBASE_H_

#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <nn/err.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/fs_FileSystemBase.h>

#ifdef NN_PLATFORM_CTR
    #include <nn/fs/CTR/fs_DirectoryBase.h>
#endif

namespace nn { namespace fs { namespace detail {

class DirectoryBase : public DirectoryBaseImpl
{
protected:
    
    DirectoryBase() {}
    explicit DirectoryBase(const wchar_t* pathName);
    explicit DirectoryBase(const char* pathName);
    void Initialize(const wchar_t* pathName);
    void Initialize(const char* pathName);
    Result TryInitialize(const wchar_t* pathName);
    Result TryInitialize(const char* pathName);
    
    s32 Read(DirectoryEntry pEntries[], s32 numEntries);
    
    void SetPriority(s32 priority);
    void GetPriority(s32* pOut) const;
};

inline Result DirectoryBase::TryInitialize(const wchar_t* pathName)
{
    return DirectoryBaseImpl::TryInitialize(pathName);
}

inline nn::Result DirectoryBase::TryInitialize(const char* pathName)
{
    static const size_t BUF_SIZE = MAX_FILE_PATH_LENGTH + 1;
    wchar_t buffer[BUF_SIZE];
    ConvertMbsToWcs(buffer, MAX_FILE_PATH_LENGTH, pathName);
    return DirectoryBaseImpl::TryInitialize(buffer);
}

inline void DirectoryBase::Initialize(const wchar_t* pathName)
{
    Result result = TryInitialize(pathName);
    if (result.IsFailure())
    {
        NN_SLOG_("directory open failed: ");
        NN_SLOG_("%lls\n", pathName);
        NN_ERR_THROW_FATAL_ALL(result);
    }
}

inline void DirectoryBase::Initialize(const char* pathName)
{
    Result result = TryInitialize(pathName);
    if (result.IsFailure())
    {
        NN_SLOG_("directory open failed: ");
        NN_SLOG_("%s\n", pathName);
        NN_ERR_THROW_FATAL_ALL(result);
    }
}

inline DirectoryBase::DirectoryBase(const wchar_t* pathName)
{
    Initialize(pathName);
}

inline DirectoryBase::DirectoryBase(const char* pathName)
{
    Initialize(pathName);
}

inline s32 DirectoryBase::Read(DirectoryEntry pEntries[], s32 numEntries)
{
    s32 ret;
    NN_ERR_THROW_FATAL_ALL(TryRead(&ret, pEntries, numEntries));
    return ret;
}

inline void DirectoryBase::SetPriority(s32 priority)
{
    NN_ERR_THROW_FATAL_ALL(TrySetPriority(priority));
}

inline void DirectoryBase::GetPriority(s32* pOut) const
{
    NN_ERR_THROW_FATAL_ALL(TryGetPriority(pOut));
}
}}}

#endif
