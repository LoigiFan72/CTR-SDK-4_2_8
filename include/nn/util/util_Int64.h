/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Int64.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_INT64_H_
#define NN_UTIL_UTIL_INT64_H_

#include <nn/types.h>
#include <nn/util/util_StaticAssert.h>
#include <nn/util/util_TypeTraits.h>

#ifdef __cplusplus

namespace nn { namespace util {

template <typename Base, typename Tag = void>
struct Int64
{
    bit32 lo;
    bit32 hi;
    Int64() {}
    Int64(Base s) : lo(static_cast<bit32>(s)), hi(static_cast<bit32>(s >> 32))  {}
    operator Base() const { return (static_cast<Base>(hi) << 32) | static_cast<Base>(lo); }
    Int64& operator++() { Base lhs = *this; lhs++; *this = lhs; return *this; }
    Int64& operator--() { Base lhs = *this; lhs--; *this = lhs; return *this; }
    Int64& operator+=(Base rhs) { Base lhs = *this; lhs += rhs; *this = lhs; return *this; }
    Int64& operator-=(Base rhs) { Base lhs = *this; lhs -= rhs; *this = lhs; return *this; }
    Int64& operator*=(Base rhs) { Base lhs = *this; lhs *= rhs; *this = lhs; return *this; }
    Int64& operator/=(Base rhs) { Base lhs = *this; lhs /= rhs; *this = lhs; return *this; }
    Int64& operator%=(Base rhs) { Base lhs = *this; lhs %= rhs; *this = lhs; return *this; }
    Int64& operator|=(Base rhs) { Base lhs = *this; lhs |= rhs; *this = lhs; return *this; }
    Int64& operator&=(Base rhs) { Base lhs = *this; lhs &= rhs; *this = lhs; return *this; }
    Int64& operator^=(Base rhs) { Base lhs = *this; lhs ^= rhs; *this = lhs; return *this; }
    Int64& operator<<=(int rhs) { Base lhs = *this; lhs <<= rhs; *this = lhs; return *this; }
    Int64& operator>>=(int rhs) { Base lhs = *this; lhs >>= rhs; *this = lhs; return *this; }
    Int64 operator++(int) { Base lhs = *this; *this = lhs + 1; return Int64(lhs); }
    Int64 operator--(int) { Base lhs = *this; *this = lhs - 1; return Int64(lhs); }
    
    Int64(const Int64<Base, void>& other) : lo(other.lo), hi(other.hi) {}
#pragma push
#pragma diag_suppress 554
    operator Int64<Base, void>() const { return static_cast<Base>(*this); }
#pragma pop
    
    bool operator==(Int64 rhs) const { return this->hi == rhs.hi && this->lo == rhs.lo; }
    bool operator!=(Int64 rhs) const { return !(*this == rhs); }
    friend bool operator==(Int64 lhs, Base rhs) { return static_cast<Base>(lhs) == rhs; }
    friend bool operator!=(Int64 lhs, Base rhs) { return !(lhs == rhs); }
    friend bool operator==(Base lhs, Int64 rhs) { return lhs == static_cast<Base>(rhs); }
    friend bool operator!=(Base lhs, Int64 rhs) { return !(lhs == rhs); }
    
    bool operator<(Int64 rhs) const { return static_cast<Base>(*this) < static_cast<Base>(rhs); }
    bool operator>(Int64 rhs) const { return rhs < *this; }
    bool operator<(Base rhs) const { return static_cast<Base>(*this) < rhs; }
    bool operator>(Base rhs) const { return rhs < *this; }
    bool operator<=(Int64 rhs) const { return !(*this > rhs); }
    bool operator>=(Int64 rhs) const { return !(*this < rhs); }
    bool operator<=(Base rhs) const { return !(static_cast<Base>(*this) > rhs); }
    bool operator>=(Base rhs) const { return !(static_cast<Base>(*this) < rhs); }
};

}}


#endif

#endif
