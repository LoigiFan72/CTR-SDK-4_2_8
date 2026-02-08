/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_MemoryInputStream.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_MEMORYINPUTSTREAM_H_
#define NN_FS_FS_MEMORYINPUTSTREAM_H_

#include <nn/fs/fs_MemoryStream.h>

namespace nn { namespace fs {

class MemoryInputStream : public IInputStream, private detail::MemoryStreamBase, private nn::util::NonCopyable<MemoryInputStream>
{
private:
    typedef detail::MemoryStreamBase Base;
public:
    MemoryInputStream(const bit8* buffer, size_t size) : Base(const_cast<bit8*>(buffer), size) {}
    
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
    
};

}}

#endif
