/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_IArchive.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FSLOW_FSLOW_IARCHIVE_H_
#define NN_FSLOW_FSLOW_IARCHIVE_H_

#include <nn/Result.h>
#include <nn/fs/fs_Result.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/util/util_NonCopyable.h>

#include <cstring>
#include <cstdlib>

namespace nn { namespace fslow {

template <class TChar, size_t TMaxLength, TChar TSeparator>
class ArchiveName
{
public:

    typedef TChar Char;
    static const size_t MaxLength = TMaxLength;
    static const TChar Separator = TSeparator;

private:
    
    static const size_t ByteSize = sizeof(Char) * (MaxLength + 1);
    
    union Data
    {
        Char c[MaxLength + 1];
        bit32 w[ByteSize / sizeof(bit32)];
    };
    
    Data m_Data;
    
    void Clear() { std::memset(&m_Data, 0, sizeof(m_Data)); }

public:

    ArchiveName() { Clear(); }

    ArchiveName(const Char* s)
    {
        Clear();
        for (s32 i = 0; i <= MaxLength; ++i)
        {
            if (!s[i] || s[i] == Separator)
            {
                return;
            }
            m_Data.c[i] = s[i];
        }
        Clear();
    }

    static const Char* GetPathString(const Char* s)
    {
        for (s32 i = 0; i <= MaxLength; ++i)
        {
            if (!*s)
            {
                return 0;
            }
            if (*s++ == Separator)
            {
                return s;
            }
        }
        return 0;
    }

    template <class Path>
    static Path GetPathString(Path path)
    {
        const typename Path::Char* s = path;
        for (s32 i = 0; i <= MaxLength; ++i)
        {
            if (!*s)
            {
                return Path();
            }
            if (*s++ == Separator)
            {
                {
                    typename Path::Updater u(path);
                    u->EraseHead(i + 1);
                }
                return path;
            }
        }
        return Path();
    }
    
    operator const Char*() const { return m_Data.c; }
    
    bool IsValid() const { return m_Data.c[0] != 0; }
    
    bool operator==(const ArchiveName& rhs) const { return std::memcmp(&this->m_Data, &rhs.m_Data, sizeof(Data)) == 0; }
    bool operator!=(const ArchiveName& rhs) const { return !(*this == rhs); }
    
    bool operator>(const ArchiveName& rhs) const { return std::memcmp(&this->m_Data, &rhs.m_Data, sizeof(Data)) > 0; }
    bool operator<=(const ArchiveName& rhs) const { return !(*this > rhs); }
    bool operator<(const ArchiveName& rhs) const { return rhs > *this; }
    bool operator>=(const ArchiveName& rhs) const { return rhs <= *this; }
    
};

}}

#endif
