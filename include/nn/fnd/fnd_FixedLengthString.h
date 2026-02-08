/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_FixedLengthString.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_FIXEDLENGTHSTRING_H_
#define NN_FND_FIXEDLENGTHSTRING_H_

#include <cstring>
#include <algorithm>
#include <nn/util/util_TypeTraits.h>
#include <nn/util/util_StaticAssert.h>

namespace nn { namespace fnd {

#pragma push
#pragma diag_suppress 1301
#pragma diag_suppress 2530

namespace detail
{
    template <class TChar>
    class FixedLengthStringHeader
    {
    protected:
        TChar* m_Data;
        s32 m_Length;
    };
    
    template <class TChar, size_t TMaxLength>
    struct FixedLengthStringSize
    {
        static const size_t value = sizeof(FixedLengthStringHeader<TChar>) + (TMaxLength + 1) * sizeof(TChar);
    };
    
    template <class TChar, size_t TObjectSize>
    struct FixedLengthStringBuffer : public FixedLengthStringHeader<TChar>
    {
        static const size_t Length = (TObjectSize - sizeof(FixedLengthStringHeader<TChar>)) / sizeof(TChar) - 1;
        TChar m_Buffer[Length + 1];
    };
}

/*
    

           
*/
template <
    class TChar,
    size_t TMaxLength,
    size_t TObjectSize = detail::FixedLengthStringSize<TChar, TMaxLength>::value,
    class = typename nn::util::enable_if<(
        TObjectSize >= detail::FixedLengthStringSize<TChar, TMaxLength>::value
    )>::type
>
class FixedLengthString : private detail::FixedLengthStringBuffer<TChar, TObjectSize>
{
    typedef detail::FixedLengthStringBuffer<TChar, TObjectSize> Base;
public:

    typedef TChar Char;
    static const size_t MaxLength = TMaxLength;
    static const size_t ObjectSize = TObjectSize;
    static const size_t DefaultHead = (Base::Length - MaxLength) / 2;
    
private:

    using Base::m_Buffer;
    using Base::m_Length;
    using Base::m_Data;
    
    size_t GetHeadIndex() const
    {
        return m_Data - m_Buffer;
    }
    
    void SetInvalid()
    {
        this->m_Length = -1;
        this->m_Data[0] = 0;
        this->m_Data = 0;
    }
    
    void CheckValid() const
    {
        NN_TASSERT_(IsValid());
    }
    
    void CheckIndex(s32 i) const
    {
        NN_UNUSED_VAR(i);
        NN_TASSERT_(0 <= i && i <= m_Length);
    }
    
    void CheckLength(s32 length) const
    {
        NN_UNUSED_VAR(length);
        NN_TASSERT_(0 <= length && length <= MaxLength);
    }
    
    static s32 CalculateLength(const Char* s, s32 maxLength)
    {
        for (s32 i = 0; i < maxLength + 1; ++i)
        {
            if (!s[i])
            {
                return i;
            }
        }
        return maxLength;
    }
    
    template <class T>
    void CopyFrom(const T* s, s32 i = 0)
    {
        for (; i < MaxLength + 1; ++i)
        {
            if (!*s)
            {
                SetLength(i);
                return;
            }
            this->m_Data[i] = *s++;
        }
        NN_TWARNING_(true, "too long string.");
        SetInvalid();
    }
    
    void MoveData(size_t index = DefaultHead)
    {
        NN_TASSERT_(GetLength() + index <= Base::Length);
        std::memmove(m_Buffer + index, m_Data, sizeof(Char) * (GetLength() + 1));
        SetHead(index);
    }
    
    void SetHead(size_t index = DefaultHead)
    {
        this->m_Data = m_Buffer + index;
    }
    
    void SetLength(s32 length)
    {
        if (0 <= length && length <= MaxLength)
        {
            this->m_Length = length;
            this->m_Data[length] = 0;
        }
        else
        {
            NN_TWARNING_(true, "too long string.");
            SetInvalid();
        }
    }
    
public:

    bool IsValid() const
    {
        return m_Data != 0;
    }
    
    // for Test
    bool CheckState() const
    {
        if (!IsValid())
        {
            return true;
        }
        return
               m_Buffer <= m_Data
            && 0 <= m_Length && m_Length <= MaxLength
            && m_Data + m_Length <= m_Buffer + Base::Length
            && m_Data[m_Length] == 0
            && MaxLength <= Base::Length
        ;
    }

    FixedLengthString()
    {
        SetHead();
        SetLength(0);
    }
    
    template <class T>
    FixedLengthString(const T* s)
    {
        if (s)
        {
            SetHead();
            SetLength(0);
            CopyFrom(s);
        }
        else
        {
            SetInvalid();
        }
    }
    
    FixedLengthString(const FixedLengthString& s)
    {
        SetHead();
        SetLength(0);
        AppendTail(s);
    }
    
    template <size_t Length, size_t Size>
    FixedLengthString(const FixedLengthString<TChar, Length, Size>& s1)
    {
        SetHead();
        SetLength(0);
        AppendTail(s1);
    }
    
    s32 GetLength() const
    {
        CheckValid();
        return m_Length;
    }
    
    FixedLengthString& Clear()
    {
        SetHead();
        SetLength(0);
        return *this;
    }
    
    const Char* GetString() const
    {
        CheckValid();
        return m_Data;
    }
    
    operator const Char*() const { return GetString(); }
    
    const Char& operator[](s32 i) const
    {
        CheckValid();
        CheckIndex(i);
        return m_Data[i];
    }
    
    Char GetChar(s32 i) const { return (*this)[i]; }
    
    template <size_t Length, size_t Size>
    FixedLengthString& AppendHead(const FixedLengthString<Char, Length, Size>& str)
    {
        if (!this->IsValid() || !str.IsValid())
        {
            this->SetInvalid();
            return *this;
        }
        const Char* s = str.GetString();
        s32 length = str.GetLength();
        size_t totalSize = this->GetLength() + length;
        if (totalSize > MaxLength)
        {
            SetInvalid();
            return *this;
        }
        if (this->GetHeadIndex() < length)
        {
            s32 originalLength = this->GetLength();
            std::memmove(m_Buffer + MaxLength - this->GetLength(), m_Data, sizeof(Char) * originalLength);
            std::memcpy(m_Buffer + MaxLength - totalSize, s, sizeof(Char) * length);
            SetHead(MaxLength - totalSize);
            SetLength(totalSize);
            NN_TASSERT_(m_Data[m_Length] == 0);
        }
        else
        {
            SetHead(GetHeadIndex() - length);
            SetLength(this->GetLength() + length);
            if (IsValid())
            {
                std::memcpy(m_Data, s, length * sizeof(Char));
            }
        }
        return *this;
    }
    
    FixedLengthString& AppendHead(const Char* s)
    {
        if (!this->IsValid())
        {
            return *this;
        }
        s32 length = CalculateLength(s, MaxLength - this->GetLength());
        if (s[length])
        {
            SetInvalid();
            return *this;
        }
        if (this->GetHeadIndex() < length)
        {
            s32 originalLength = this->GetLength();
            size_t totalSize = this->GetLength() + length;
            std::memmove(m_Buffer + MaxLength - this->GetLength(), m_Data, sizeof(Char) * originalLength);
            std::memcpy(m_Buffer + MaxLength - totalSize, s, sizeof(Char) * length);
            SetHead(MaxLength - totalSize);
            SetLength(totalSize);
            NN_TASSERT_(m_Data[m_Length] == 0);
        }
        else
        {
            SetHead(GetHeadIndex() - length);
            SetLength(this->GetLength() + length);
            if (IsValid())
            {
                std::memcpy(m_Data, s, length * sizeof(Char));
            }
        }
        return *this;
    }
    
    template <size_t Length, size_t Size>
    FixedLengthString& AppendTail(const FixedLengthString<Char, Length, Size>& s)
    {
        if (!this->IsValid() || !s.IsValid())
        {
            this->SetInvalid();
            return *this;
        }
        if (GetHeadIndex() > Base::Length - MaxLength)
        {
            MoveData();
        }
        Char* p = m_Data + this->GetLength();
        SetLength(this->GetLength() + s.GetLength());
        if (IsValid())
        {
            std::memcpy(p, s.GetString(), sizeof(Char) * s.GetLength());
            NN_TASSERT_(m_Data[m_Length] == 0);
        }
        return *this;
    }
    
    FixedLengthString& AppendTail(const Char* s)
    {
        if (!this->IsValid())
        {
            return *this;
        }
        if (GetHeadIndex() > Base::Length - MaxLength)
        {
            MoveData();
        }
        CopyFrom(s, this->GetLength());
        return *this;
    }
    
    FixedLengthString& AppendHeadAsHex(bit32 x)
    {
        Char hex[9];
        for (s32 i = 0; i < 8; ++i)
        {
            bit32 n = (x >> ((7 - i) * 4)) & 0xf;
            NN_TASSERT_(0 <= n && n < 16);
            hex[i] = static_cast<Char>(n < 10 ? '0' + n : 'a' + (n - 10));
        }
        hex[8] = 0;
        return AppendHead(hex);
    }
    
    FixedLengthString& AppendTailAsHex(bit32 x)
    {
        if (!this->IsValid())
        {
            return *this;
        }
        if (GetHeadIndex() > Base::Length - MaxLength)
        {
            MoveData();
        }
        Char* p = m_Data + this->GetLength();
        SetLength(this->GetLength() + 8);
        if (IsValid())
        {
            for (s32 i = 0; i < 8; ++i)
            {
                bit32 n = (x >> ((7 - i) * 4)) & 0xf;
                NN_TASSERT_(0 <= n && n < 16);
                p[i] = static_cast<Char>(n < 10 ? '0' + n : 'a' + (n - 10));
            }
            NN_TASSERT_(m_Data[m_Length] == 0);
        }
        return *this;
    }
    
    template <class Char2>
    FixedLengthString& AppendTail(const Char2* s, size_t size)
    {
        if (!this->IsValid())
        {
            return *this;
        }
        if (GetHeadIndex() > Base::Length - MaxLength)
        {
            MoveData();
        }
        Char* p = m_Data + this->GetLength();
        SetLength(this->GetLength() + size);
        if (IsValid())
        {
            for (s32 i = 0; i < size; ++i)
            {
                p[i] = s[i];
            }
            NN_TASSERT_(m_Data[m_Length] == 0);
        }
        return *this;
    }
    
    template <class Char2, size_t Size>
    FixedLengthString& AppendTail(const Char2 s[Size])
    {
        return AppendTail(s, Size);
    }
    
    FixedLengthString& EraseTail(size_t length)
    {
        if (!this->IsValid())
        {
            return *this;
        }
        this->SetLength(this->GetLength() - length);
        return *this;
    }
    
    FixedLengthString& EraseHead(size_t length)
    {
        if (!this->IsValid())
        {
            return *this;
        }
        this->SetHead(this->GetHeadIndex() + length);
        this->SetLength(this->GetLength() - length);
        return *this;
    }
    
    template <size_t Length, size_t Size>
    FixedLengthString& operator+=(const FixedLengthString<Char, Length, Size>& rhs)
    {
        this->AppendTail(rhs);
        return *this;
    }
    
    template <class Char2, size_t Size>
    FixedLengthString& operator+=(const Char2 s[Size]) { return AppendTail(s); }
    
    FixedLengthString& operator+=(const Char* rhs)
    {
        this->AppendTail(rhs);
        return *this;
    }
    
    template <size_t Length2, size_t Size2>
    friend bool operator==(const FixedLengthString& lhs, const FixedLengthString<Char, Length2, Size2>& rhs)
    {
        return lhs.GetLength() == rhs.GetLength() && std::memcmp(lhs.GetString(), rhs.GetString(), sizeof(Char) * lhs.GetLength()) == 0;
    }
    
    friend bool operator==(const FixedLengthString& lhs, const Char* rhs)
    {
        return std::memcmp(lhs.m_Data, rhs, sizeof(Char) * lhs.GetLength()) == 0 && rhs[lhs.GetLength()] == 0;
    }
    
    friend bool operator==(const Char* lhs, const FixedLengthString& rhs)
    {
        return rhs == lhs;
    }
    
    template <size_t Length2, size_t Size2>
    friend bool operator!=(const FixedLengthString& lhs, const FixedLengthString<Char, Length2, Size2>& rhs)
    {
        return !(lhs == rhs);
    }
    
    friend bool operator!=(const FixedLengthString& lhs, const Char* rhs)
    {
        return !(lhs == rhs);
    }
    
    friend bool operator!=(const Char* lhs, const FixedLengthString& rhs)
    {
        return !(lhs == rhs);
    }
    
    template <size_t Length, size_t Size>
    friend bool operator<(const FixedLengthString& lhs, const FixedLengthString<TChar, Length, Size>& rhs)
    {
        int n = std::memcmp(lhs.GetString(), rhs.GetString(), sizeof(Char) * std::min(lhs.GetLength(), rhs.GetLength()));
        return n < 0 || (n == 0 && lhs.GetLength() < rhs.GetLength());
    }
    
    template <size_t Length, size_t Size>
    friend bool operator>(const FixedLengthString& lhs, const FixedLengthString<TChar, Length, Size>& rhs)
    {
        return rhs < lhs;
    }
    
    template <size_t Length, size_t Size>
    friend bool operator<=(const FixedLengthString& lhs, const FixedLengthString<TChar, Length, Size>& rhs)
    {
        return !(lhs > rhs);
    }
    
    template <size_t Length, size_t Size>
    friend bool operator>=(const FixedLengthString& lhs, const FixedLengthString<TChar, Length, Size>& rhs)
    {
        return rhs <= lhs;
    }
    
};

// Fixed-length string
// Not always terminated by NULL
// const value classes
template <class TChar, size_t TMaxLength>
class LightFixedLengthString
{
public:

    typedef TChar Char;
    static const size_t MaxLength = TMaxLength;
    
private:

    Char m_Buffer[MaxLength];
    
    void CopyFrom(const Char* s)
    {
        for (size_t i = 0; i < MaxLength; ++i)
        {
            this->m_Buffer[i] = *s;
            if (!*s++)
            {
                return;
            }
        }
        NN_TWARNING_(*s, "too long string.");
        if (*s)
        {
            // Invalid because it's too long
            this->m_Buffer[0] = 0;
        }
    }
    
public:

    LightFixedLengthString()
    {
        this->m_Buffer[0] = 0;
    }
    
    LightFixedLengthString(const Char* s)
    {
        CopyFrom(s);
    }
    
    LightFixedLengthString(const Char* s, size_t size)
    {
        if (size > MaxLength)
        {
            size = MaxLength;
        }
        NN_TASSERT_(size <= MaxLength);
        std::memcpy(this->m_Buffer, s, size);
        if (size < MaxLength)
        {
            this->m_Buffer[size] = 0;
        }
    }
    
    size_t GetLength() const
    {
        size_t i = 0;
        for (; i < MaxLength; ++i)
        {
            if (!m_Buffer[i])
            {
                break;
            }
        }
        return i;
    }
    
    Char operator[](size_t i) const
    {
        NN_TASSERT_(i < MaxLength);
        return m_Buffer[i];
    }
    
    LightFixedLengthString& operator=(const Char* s)
    {
        CopyFrom(s);
        return *this;
    }
    
};

#pragma pop

}}

#endif
