/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Misccellaneous.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47779 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATH_MISCCELLANEOUS_H_
#define NN_MATH_MATH_MISCCELLANEOUS_H_

#include <nn/types.h>
#include <nn/assert.h>

#ifdef __cplusplus

namespace nn { namespace math {

    template <u32 MUL, u32 DIV>
    struct MakeRate
    {
        static const u64 VALUE = (static_cast<u64>(MUL) << 32) / DIV;
        NN_STATIC_ASSERT( (((static_cast<u64>(MUL) << 32) / DIV) >> 32) != 0 );
    };
    template <u32 MUL, u32 DIV>
    struct MakeRate32
    {
        static const u32 VALUE = static_cast<u32>( (static_cast<u64>(MUL) << 32) / DIV );
        NN_STATIC_ASSERT( (((static_cast<u64>(MUL) << 32) / DIV) >> 32) == 0 );
    };

}}  // nn::math

#endif // __cplusplus

// C declarations follow

#include <nn/util/detail/util_CLibImpl.h>


NN_EXTERN_C inline s64 nnmathMultiplyAndDivide(s64 x, s32 mul, s32 div)
{
    // Note right shift
    // Compiler dependent
    const s64 rate = ((s64)(mul) << 32) / div;
    const s32 r_hi = (s32)(rate >> 32);
    const u32 r_lo = (u32)(rate >>  0);
    const s32 x_hi = (s32)(x    >> 32);
    const u32 x_lo = (u32)(x    >>  0);

    return (((s64)(x_hi) * r_hi) << 32)
         + ( (s64)(x_hi) * r_lo
           + (s64)(r_hi) * x_lo )
         + (((u64)(x_lo) * r_lo) >> 32);
}

//NN_EXTERN_C inline s64 nnmathArithmeticShiftRightS64(s64 x, int shift)
//{
//#if (-2 >> 1) == -1
//    return x >> shift;
//#elif (u64)-1 == 0xFFFFFFFFFFFFFFFFull
//    u64 ux   = static_cast<u64>(x);
//    u64 uxs  = (ux >> shift);
//    u64 us   = - (ux >> 63);
//    u64 sign = us << (64 - shift);
//    return sign | uxs;
//#else
//    #error
//#endif
//}

NN_EXTERN_C inline u64 nnmathMakeRate(u32 mul, u32 div)
{
    return ((u64)(mul) << 32) / div;
}
NN_EXTERN_C inline u32 nnmathMakeRate32(u32 mul, u32 div)
{
    return (u32)( ((u64)(mul) << 32) / div );
}

NN_EXTERN_C inline u64 nnmathMultiplyRate(u64 x, u64 rate)
{
    const u32 r_hi = (u32)(rate >> 32);
    const u32 r_lo = (u32)(rate >>  0);
    const s32 x_hi = (u32)(x    >> 32);
    const u32 x_lo = (u32)(x    >>  0);

    return (((u64)(x_hi) * r_hi) << 32)
         + ( (u64)(x_hi) * r_lo
           + (u64)(r_hi) * x_lo )
         + (((u64)(x_lo) * r_lo) >> 32);
}

NN_EXTERN_C inline u64 nnmathMultiplyRate32(u64 x, u32 rate)
{
    const s32 x_hi = (u32)(x >> 32);
    const u32 x_lo = (u32)(x >>  0);

    return   (u64)(x_hi) * rate
         + (((u64)(x_lo) * rate) >> 32);
}


#endif // NN_MATH_MATH_MISCCELLANEOUS_H_
