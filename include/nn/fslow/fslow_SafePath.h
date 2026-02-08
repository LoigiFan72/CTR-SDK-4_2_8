/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_SafePath.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FSLOW_FSLOW_SAFEPATH_H_
#define NN_FSLOW_FSLOW_SAFEPATH_H_

#include <nn/util/util_AutoObject.h>
#include <nn/util/util_StaticAssert.h>
#include <nn/fnd/fnd_FixedLengthString.h>
#include <nn/fnd/fnd_Interlocked.h>
#include <memory>

namespace nn { namespace fslow {

template <typename TChar, size_t TMaxLength, size_t TSize>
class ReferenceCountedString :
    public nn::util::ReferenceCounter<u32>,
    public nn::fnd::FixedLengthString<TChar, TMaxLength, TSize - sizeof(nn::util::ReferenceCounter<u32>)>
{
private:
    typedef nn::fnd::FixedLengthString<TChar, TMaxLength, TSize - sizeof(nn::util::ReferenceCounter<u32>)> Base;
public:
    ReferenceCountedString() {}
    ReferenceCountedString(const TChar* s) : Base(s) {}
    template <class T> explicit ReferenceCountedString(const T* s) : Base(s) {}
};

NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_T1(SafePath, NN_UTIL_AUTOOBJECT_T0)
public:
    using typename Base::Updater;
    
    typedef NN_UTIL_AUTOOBJECT_T0 String;
    typedef typename String::Char Char;
    
    SafePath() {}
    SafePath(const Char* s) : Base(s) {}
    template <class T> explicit SafePath(const T* s) : Base(s) {}
    
    size_t GetLength() const { return (*this)->GetLength(); }
    
    size_t GetDataSize() const { return ((*this)->GetLength() + 1) * sizeof(Char); }
    const void* GetDataBuffer() const { return &((*this)[0]); }
    
    const Char* GetString() const { return (*this)->GetString(); }
    
    operator const Char*() const { return (*this)->GetString(); }
    const Char& operator[](int i) const { return (**this)[i]; }
    operator bool() const { return (*this)->IsValid(); }
    bool operator!() const { return !(*this)->IsValid(); }
    
    void EraseHead(size_t size)
    {
        Updater(*this)->EraseHead(size);
    }
    
    template <size_t MaxSize, Char Separator>
    s32 GetArchiveNameLength() const
    {
        const Char* s = *this;
        for (s32 i = 0; i < MaxSize; ++i)
        {
            if (s[i] == Separator)
            {
                return i;
            }
        }
        return -1;
    }

    void PRINT()
    {
        nn::dbg::detail::Printf("SafePath::PRINT \"%ls\"\n", (*this)->GetString());
    }

NN_UTIL_AUTOOBJECT_END_DEFINE

}}

#endif
