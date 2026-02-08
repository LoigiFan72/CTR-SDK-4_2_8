/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Arithmetic.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARMV6_MATH_ARITHMETIC_H_
#define NN_MATH_ARMV6_MATH_ARITHMETIC_H_

#include <nn/assert.h>
#include <nn/math/math_Config.h>
#include <nn/math/math_Constant.h>

#include <cmath>

namespace nn {
namespace math {
namespace ARMv6 {

/* =======================================================================
        Arithmetic functions related to floating-point numbers
   ======================================================================== */

/* Please see man pages for details 
    
    
*/

//
f32 HermiteAsm(f32 v0, f32 t0, f32 v1, f32 t1, f32 s);
f32 HermiteAsm(f32 v0, f32 t0, f32 v1, f32 t1, f32 p, f32 d);

/*
  

  
  
  
  
  

  
 */
NN_MATH_INLINE f32 
HermiteC(f32 v0, f32 t0, f32 v1, f32 t1, f32 s)
{
    f32 SS   = s * s;
    f32 SS_S = s * s - s;
    f32 b1 = SS_S * s - SS_S;
    f32 b2 = SS_S * s;
    f32 a2 = SS - 2.f * b2;
    
    return v0 - a2 * v0 + a2 * v1 + b1 * t0 + b2 * t1;
}
NN_MATH_INLINE f32
HermiteC_FAST(f32 v0, f32 t0, f32 v1, f32 t1, f32 s)
{
    f32 SS;
    f32 SS_S;
    f32 b1;
    f32 b2;
    f32 a2;

    SS   = s * s;
    SS_S = s * s - s;
    b2 = SS_S * s;
    b1 = b2 - SS_S;
    a2 = SS - 2.f * b2;
    
    return v0 - a2 * v0 + a2 * v1 + b1 * t0 + b2 * t1;
}


/*
  

  
  
  
  
  
  

  
 */
NN_MATH_INLINE f32
HermiteC(f32 v0, f32 t0, f32 v1, f32 t1, f32 p, f32 d)
{
    f32 inv_d = 1 / d;
    f32 s = p * inv_d;
    f32 s_1 = s - 1;
    return v0 + (v0 - v1) * (2 * s - 3) * s * s + p * s_1 * (s_1 * t0 + s * t1);
}

NN_MATH_INLINE f32
HermiteC_FAST(f32 v0, f32 t0, f32 v1, f32 t1, f32 p, f32 d)
{

    f32 s = p / d;
    f32 s_1 = s - 1;
    f32 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, ret;
    
    tmp1 = (v0 - v1);
    tmp2 = (2 * s - 3);
    tmp3 = s * s;
    tmp4 = p * s_1;
    tmp5 = s_1 * t0;
    tmp6 = s * t1;
    
    ret = v0 + tmp1 * tmp2 * tmp3 + tmp4 * (tmp5 + tmp6);
    return ret;
}

/*  

*/


}}}  // nn::math::ARMv6

/* NN_MATH_ARMV6_MATH_ARITHMETIC_H_ */
#endif
