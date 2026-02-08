/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_MemoryStream.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_MEMORYSTREAM_H_
#define NN_FS_FS_MEMORYSTREAM_H_

#include <nn/Result.h>
#include <nn/err.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Result.h>
#include <nn/fs/fs_IStream.h>
#include <nn/util/util_NonCopyable.h>

namespace nn { namespace fs {

namespace detail {

class MemoryStreamBase
{
private:

    bit8* m_Buffer;
    size_t m_Size;
    size_t m_Position;
    
protected:

    MemoryStreamBase(bit8* buffer, size_t size) : m_Buffer(buffer), m_Size(size), m_Position(0) {}
    
    Result TrySeek(s64 position, PositionBase base);
    void Seek(s64 position, PositionBase base) { NN_ERR_THROW_FATAL_ALL(TrySeek(position, base)); }
    
    Result TryGetPosition(s64* pOut) const { *pOut = m_Position; return ResultSuccess(); }
    s64 GetPosition() const { return m_Position; }
    
    Result TrySetPosition(s64 position) { return TrySeek(position, POSITION_BASE_BEGIN); }
    void SetPosition(s64 position) { NN_ERR_THROW_FATAL_ALL(TrySetPosition(position)); }
    
    Result TryGetSize(s64* pOut) const { *pOut = m_Size; return ResultSuccess(); }
    s64 GetSize() const { return m_Size; }
    
    Result TryRead(s32* pOut, void* buffer, size_t size);
    s32 Read(void* buffer, size_t size) { s32 ret; NN_ERR_THROW_FATAL_ALL(TryRead(&ret, buffer, size)); return ret; }
    
    Result TryWrite(s32* pOut, const void* buffer, size_t size);
    s32 Write(const void* buffer, size_t size) { s32 ret; NN_ERR_THROW_FATAL_ALL(TryWrite(&ret, buffer, size)); return ret; }
    
    Result TrySetSize(s64) { return nn::fs::ResultUnsupportedOperation(); }
    void SetSize(s64 size) { NN_ERR_THROW_FATAL_ALL(TrySetSize(size)); }
    
};

}

class MemoryStream : public IStream, private detail::MemoryStreamBase, private nn::util::NonCopyable<MemoryStream>
{
private:
    typedef detail::MemoryStreamBase Base;
public:

    MemoryStream(bit8* buffer, size_t size) : Base(buffer, size) {}
    
    virtual Result TrySeek(s64 position, PositionBase base) { return Base::TrySeek(position, base); }
    virtual void Seek(s64 position, PositionBase base) { Base::Seek(position, base); }
    
    virtual Result TryGetPosition(s64* pOut) const { return Base::TryGetPosition(pOut); }
    virtual s64 GetPosition() const { return Base::GetPosition(); }
    
    virtual Result TrySetPosition(s64 position) { return Base::TrySetPosition(position); }
    virtual void SetPosition(s64 position) { Base::SetPosition(position); }
    
    virtual Result TryGetSize(s64* pOut) const { return Base::TryGetSize(pOut); }
    virtual s64 GetSize() const { return Base::GetSize(); }
    
    virtual Result TryRead(s32* pOut, void* buffer, size_t size) { return Base::TryRead(pOut, buffer, size); }
    virtual s32 Read(void* buffer, size_t size) { return Base::Read(buffer, size); }
    
    virtual Result TryWrite(s32* pOut, const void* buffer, size_t size, bool) { return Base::TryWrite(pOut, buffer, size); }
    virtual s32 Write(const void* buffer, size_t size, bool) { return Base::Write(buffer, size); }
    
    virtual Result TrySetSize(s64 size) { return Base::TrySetSize(size); }
    virtual void SetSize(s64 size) { Base::SetSize(size); }
    
};

}}

#endif
