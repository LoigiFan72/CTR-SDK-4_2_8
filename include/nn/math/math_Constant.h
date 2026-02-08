/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Constant.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_CONSTANT_H_
#define NN_MATH_CONSTANT_H_

#include <cfloat>
#include <nn/math/math_Config.h>

namespace nn { namespace math {


const f32 F_E       = 2.718281828459045f;   // Napier's constant (natural log base) e
const f32 F_LOG2E   = 1.442695040888963f;   // log2(e)
const f32 F_LOG10E  = 0.434294481903251f;   // log10(e)
const f32 F_LN2     = 0.693147180559945f;   // ln(2)
const f32 F_LN10    = 2.302585092994045f;   // ln(10)
const f32 F_PI      = 3.141592653589793f;   // pi
const f32 F_SQRTPI  = 1.772453850905516f;   // sqrt(pi)
const f32 F_SQRT2   = 1.414213562373095f;   // sqrt(2)
const f32 F_SQRT3   = 1.732050807568877f;   // sqrt(3)

const f32 F_INVLN2  = 1.442695040888963f;   // 1/ln2


const f32 F_MAX     = FLT_MAX;              // Maximum positive number = 3.40282346638529 * 10^38
const f32 F_MIN     = FLT_MIN;              // Minimum positive value = 1.17549435082229 * 10^-38


#ifdef __ARMCC_VERSION
// Definitions that use extended functionality of ARM compiler
const f32 F_NAN     = 0f_7FFFFFFF;    // Non-numbers
const f32 F_INF     = 0f_7F800000;    // Infinity
const f32 F_NINF    = 0f_FF800000;    // Negative infinity
const f32 F_ULP     = 0f_34000000;    // Minimum positive value that satisfies  1.0f + x != 1.0f

#else // __ARMCC_VERSION
namespace internal
{
    const u32 I_NAN     = 0x7FFFFFFF;   // sign=+ exp=max frac=max
    const u32 I_INF     = 0x7F800000;   // sign=+ exp=max frac=0
    const u32 I_NINF    = 0xFF800000;   // sign=- exp=max frac=0
    const u32 I_ULP     = 0x34000000;   // sign=+ exp=-23 frac=0
} /* namespace internal */

const f32 F_NAN     = *reinterpret_cast<const f32*>(&internal::I_NAN);    // Non-numbers
const f32 F_INF     = *reinterpret_cast<const f32*>(&internal::I_INF);    // Infinity
const f32 F_NINF    = *reinterpret_cast<const f32*>(&internal::I_NINF);   // Negative infinity
const f32 F_ULP     = *reinterpret_cast<const f32*>(&internal::I_ULP);    // Minimum positive value that satisfies  1.0f + x != 1.0f

#endif // __ARMCC_VERSION

}}  // nn::math

/* NN_MATH_CONSTANT_H_ */
#endif
