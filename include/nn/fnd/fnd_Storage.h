/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Storage.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_STORAGE_H_
#define NN_FND_STORAGE_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/Result.h>
#include <nn/assert.h>

#ifdef __cplusplus

namespace nn { namespace fnd {

/*
    
*/
class IStorageReader
{
public:
    virtual Result TryRead(size_t* pOut, void* buffer, size_t size) = 0;
    virtual Result TrySetPosition(s64 position) = 0;
    virtual Result TryGetPosition(s64* pOut) const = 0;
    virtual Result TryGetSize(s64* pOut) const = 0;
    virtual ~IStorageReader() {}
};

/*
    
*/
class IStorageWriter
{
public:
    virtual Result TryWrite(size_t* pOut, const void* buffer, size_t size) = 0;
    virtual Result TrySetPosition(s64 position) = 0;
    virtual Result TryGetPosition(s64* pOut) const = 0;
    virtual Result TryGetSize(s64* pOut) const = 0;
    virtual ~IStorageWriter() {}
};

/*
    
*/
class MemoryStorageReader : public IStorageReader
{
private:
    const char* m_Buffer;
    size_t m_Size;
    size_t m_Position;
public:
    MemoryStorageReader(const void* buffer, size_t size) : m_Buffer(reinterpret_cast<const char*>(buffer)), m_Size(size), m_Position(0) {}
    virtual Result TryRead(size_t* pOut, void* buffer, size_t size);
    virtual Result TrySetPosition(s64 position) { m_Position = static_cast<size_t>(position); return ResultSuccess(); }
    virtual Result TryGetPosition(s64* pOut) const { *pOut = m_Position; return ResultSuccess(); }
    virtual Result TryGetSize(s64* pOut) const { *pOut = m_Size; return ResultSuccess(); }
};

/*
    
*/
class MemoryStorageWriter : public IStorageWriter
{
private:
    char* m_Buffer;
    size_t m_Size;
    size_t m_Position;
public:
    MemoryStorageWriter(void* buffer, size_t size) : m_Buffer(reinterpret_cast<char*>(buffer)), m_Size(size), m_Position(0) {}
    virtual Result TryWrite(size_t* pOut, const void* buffer, size_t size);
    virtual Result TrySetPosition(s64 position) { m_Position = static_cast<size_t>(position); return ResultSuccess(); }
    virtual Result TryGetPosition(s64* pOut) const { *pOut = m_Position; return ResultSuccess(); }
    virtual Result TryGetSize(s64* pOut) const { *pOut = m_Size; return ResultSuccess(); }
};

template <class Reader>
class StorageReaderTmeplate : public IStorageReader
{
private:
    Reader& m_Impl;
public:
    StorageReaderTmeplate(Reader& reader) : m_Impl(reader) {}
    virtual Result TryRead(size_t* pOut, void* buffer, size_t size) { return m_Impl.TryRead(pOut, buffer, size); }
    virtual Result TrySetPosition(s64 position) { return m_Impl.TrySetPosition(position); }
    virtual Result TryGetPosition(s64* pOut) const { return m_Impl.TryGetPosition(pOut); }
    virtual Result TryGetSize(s64* pOut) const { return m_Impl.TryGetSize(pOut); }
};

template <class Writer>
class StorageWriterTmeplate : public IStorageWriter
{
private:
    Writer& m_Impl;
public:
    StorageWriterTmeplate(Writer& writer) : m_Impl(writer) {}
    virtual Result TryRead(size_t* pOut, void* buffer, size_t size) { return m_Impl.TryRead(pOut, buffer, size); }
    virtual Result TrySetPosition(s64 position) { return m_Impl.TrySetPosition(position); }
    virtual Result TryGetPosition(s64* pOut) const { return m_Impl.TryGetPosition(pOut); }
    virtual Result TryGetSize(s64* pOut) const { return m_Impl.TryGetSize(pOut); }
};

}}

#endif

#endif
