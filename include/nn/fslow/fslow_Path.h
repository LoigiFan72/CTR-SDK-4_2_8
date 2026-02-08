/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_Path.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FSLOW_FSLOW_PATH_H_
#define NN_FSLOW_FSLOW_PATH_H_

#include <nn/util/util_NonCopyable.h>
#include <nn/util/util_StaticAssert.h>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <cwchar>

namespace nn { namespace fslow {

enum PathType
{
    PATH_TYPE_INVALID = 0,
    PATH_TYPE_EMPTY = 1,
    PATH_TYPE_BINARY = 2,
    PATH_TYPE_STRING = 3,
    PATH_TYPE_WSTRING = 4
};

template <class TStringPath, class TWStringPath>
class LowPath
{
public:
    
    typedef TWStringPath WStringPath;
    typedef TStringPath StringPath;
    
private:
    
    bit32 m_PathType;
    const void* m_Data;
    size_t m_BinarySize;
    
    size_t GetBinarySize() const { return m_BinarySize; }
    
public:

    void PRINT() const
    {
#if 1
        switch (GetPathType())
        {
            case PATH_TYPE_INVALID:
            {
                nn::dbg::detail::TPrintf("PATH_TYPE_INVALID\n");
                break;
            }
            case PATH_TYPE_EMPTY:
            {
                nn::dbg::detail::TPrintf("PATH_TYPE_EMPTY\n");
                break;
            }
            case PATH_TYPE_BINARY:
            {
                if (GetBinarySize() == 1) { nn::dbg::detail::TPrintf("PATH_TYPE_BINARY(1 byte) %d\n", *(static_cast<const bit8*>(m_Data))); }
                else if (GetBinarySize() == 2) { nn::dbg::detail::TPrintf("PATH_TYPE_BINARY(2 byte) %d\n", *(static_cast<const bit16*>(m_Data))); }
                else if (GetBinarySize() == 4) { nn::dbg::detail::TPrintf("PATH_TYPE_BINARY(4 byte) %d\n", *(static_cast<const bit32*>(m_Data))); }
                else if (GetBinarySize() == 8) { nn::dbg::detail::TPrintf("PATH_TYPE_BINARY(8 byte) %lld\n", *(static_cast<const bit64*>(m_Data))); }
                else
                {
                    nn::dbg::detail::TPrintf("PATH_TYPE_BINARY(%d byte) ", GetBinarySize());
                    for (int i = 0; i < GetBinarySize(); i++)
                    {
                        nn::dbg::detail::TPrintf("%2X ", *(static_cast<const bit8*>(m_Data) + i));
                    }
                    nn::dbg::detail::TPrintf("\n");
                }
                break;
            }
            case PATH_TYPE_STRING:
            {
                nn::dbg::detail::TPrintf("PATH_TYPE_STRING \"%s\"\n", static_cast<const char*>(m_Data));
                break;
            }
            case PATH_TYPE_WSTRING:
            {
                char buf[256];
                std::wcstombs(buf, static_cast<const wchar_t*>(m_Data), 256);
                nn::dbg::detail::TPrintf("PATH_TYPE_WSTRING \"%s\"\n", buf);
                break;
            }
            default:
            {
                nn::dbg::detail::TPrintf("PATH_TYPE_unknown \n");
                break;
            }
        }
#endif
    }
    
    LowPath(bit32 pathType, const void* data, size_t size)
    {
        NN_TASSERT_(pathType == PATH_TYPE_EMPTY || data != 0);
        this->m_PathType = pathType;
        this->m_Data = data;
        this->m_BinarySize = size;
        // TODO: Required asserts
    }
    
    LowPath()
    {
        this->m_PathType = PATH_TYPE_EMPTY;
        // TODO: Originally, the following should be 0
        this->m_Data = &m_Data;
        this->m_BinarySize = 1;
    }
    
    template <typename T>
    void SetBinary(const T* p)
    {
        this->m_PathType = PATH_TYPE_BINARY;
        this->m_Data = p;
        this->m_BinarySize = sizeof(T);
    }
    
    template <typename T>
    static LowPath Make(const T* p)
    {
        LowPath ret;
        ret.SetBinary(p);
        return ret;
    }
    
    LowPath(const char* path)
    {
        // TODO: Check size, etc.
        this->m_PathType = PATH_TYPE_STRING;
        this->m_Data = path;
        this->m_BinarySize = (std::strlen(path) + 1) * sizeof(*path);
    }
    
    LowPath(const wchar_t* path)
    {
        // TODO: Check size, etc.
        this->m_PathType = PATH_TYPE_WSTRING;
        this->m_Data = path;
        this->m_BinarySize = (std::wcslen(path) + 1) * sizeof(*path);
    }
    
    bool IsEmptyPath() const
    {
        return GetPathType() == PATH_TYPE_EMPTY;
    }
    
    struct BinaryProxy
    {
        friend class LowPath;
    private:
    
        const LowPath* m_Path;
    
        explicit BinaryProxy(const LowPath* path) : m_Path(path) {}
        
    public:
        
        template <class T>
        operator const T*() const
        {
            if (m_Path->GetPathType() == PATH_TYPE_BINARY && m_Path->GetBinarySize() == sizeof(T))
            {
                return static_cast<const T*>(m_Path->m_Data);
            }
            else
            {
                return 0;
            }
        }
        
    };
    friend struct BinaryProxy;
    
    const BinaryProxy GetBinary() const
    {
        return BinaryProxy(this);
    }
    
    StringPath GetString() const
    {
        if (GetPathType() == PATH_TYPE_STRING)
        {
            return StringPath(static_cast<const char*>(m_Data));
        }
        if (GetPathType() == PATH_TYPE_WSTRING)
        {
            return StringPath(static_cast<const wchar_t*>(m_Data));
        }
        return StringPath();
    }
    
    const char* GetStringRaw() const
    {
        if (GetPathType() == PATH_TYPE_STRING)
        {
            return static_cast<const char*>(m_Data);
        }
        else
        {
            return 0;
        }
    }
    
    WStringPath GetWString() const
    {
        if (GetPathType() == PATH_TYPE_WSTRING)
        {
            return WStringPath(static_cast<const wchar_t*>(m_Data));
        }
        if (GetPathType() == PATH_TYPE_STRING)
        {
            return WStringPath(static_cast<const char*>(m_Data));
        }
        return WStringPath();
    }
    
    const wchar_t* GetWStringRaw() const
    {
        if (GetPathType() == PATH_TYPE_WSTRING)
        {
            return static_cast<const wchar_t*>(m_Data);
        }
        else
        {
            return 0;
        }
    }
    
    bit32 GetPathType() const { return m_PathType; }
    
    const bit8* GetDataBuffer() const
    {
        return static_cast<const bit8*>(m_Data);
    }
    
    size_t GetDataSize() const
    {
        return m_BinarySize;
    }
    
};

}}

#endif
