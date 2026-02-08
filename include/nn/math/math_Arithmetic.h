/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Arithmetic.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARITHMETIC_H_
#define NN_MATH_ARITHMETIC_H_

#include <nn/assert.h>
#include <nn/math/math_Config.h>
#include <nn/math/math_Constant.h>
#include <nn/math/ARMv6/math_Arithmetic.h>

#include <cmath>

#pragma push
#pragma Otime

namespace nn { namespace math {



/* =======================================================================
        Arithmetic functions related to floating-point numbers
   ======================================================================== */

/* Please see man pages for details 
    
    
*/

// u32 F32AsU32(f32 x)
//
// Description: Converts an f32 type into a u32 type without changing the bit array
// Arguments: x: The value to convert to a u32 type.
// Return value: A u32-type value that has a bit expression equivalent to x.
inline u32
F32AsU32(f32 x)
{
    return *reinterpret_cast<u32*>(&x);
}



/*
  

  

  
 */
inline f32
U32AsF32(u32 x)
{
    return *reinterpret_cast<f32*>(&x);
}


/*
  

  

  
 */
inline s32
FGetExpPart(f32 f)
{
    s32 s = static_cast<s32>((F32AsU32(f) >> 23) & 0xFF);
    return s - 127;
}


/*
  

  

  
 */
inline f32
FGetMantPart(f32 f)
{
    // Sets the exponent portion to 127
    u32 u = (F32AsU32(f) & 0x807FFFFF) | 0x3F800000;
    return U32AsF32(u);
}


/*
  

  
  
  

  
 */
inline f32
FSelect(f32 cond, f32 ifPos, f32 ifNeg)
{
    f32 ret;

    ret = (cond >= 0) ? ifPos: ifNeg;


    return ret;
}


/*
  

  

  
 */
inline f32
FAbs(f32 x)
{
    f32 ret;

    ret = ::std::fabsf(x);


    return ret;
}


/*
  

  

  
 */
inline f32
FNAbs(f32 x)
{
    f32 ret;

    ret = - FAbs(x);


    return ret;
}


/*
  

  
  

  
 */
inline f32
FCopySign(f32 abs, f32 sign)
{
    f32 pos = FAbs(abs);
    f32 neg = FNAbs(abs);

    return FSelect(sign, pos, neg);
}

namespace internal
{
    f32 FExp(f32 x);
    f32 FLog(f32 x);
}


/*
  

  

  
 */
inline f32
FExp(f32 x)
{
    return ::std::expf(x);

}


/*
  

  

  
 */
inline f32
FLog(f32 x)
{
    NN_MATH_WARNING(x > 0, "FLog: Input is out of the domain.");

    return ::std::logf(x);

}


/*
  

  

  
 */
inline f32
FLog10(f32 x)
{
    NN_MATH_WARNING(x > 0, "FLog10: Input is out of the domain.");

    return ::std::log10f(x);
}


/*
  

  
  

  
 */
inline f32
FMod(f32 x, f32 y)
{
    return ::std::fmodf(x, y);
}


/*
  

  
  

  
 */
inline f32
FModf(f32 x, f32* y)
{
    return ::std::modff(x, y);
}


/*
  

  

  
 */
inline f32
FCeil(f32 x)
{
    return ::std::ceilf(x);
}


/*
  

  

  
 */
inline f32
FFloor(f32 x)
{
    return ::std::floorf(x);
}


/*
  

  

  
 */
inline s16
F32ToS16(f32 x)
{
    return s16(x);

}


/*
  

  

  
 */
inline u16
F32ToU16(f32 x)
{
    return u16(x);

}


/*
  

  

  
 */
inline f32
U16ToF32(u16 x)
{
    return f32(x);

}


/*
  

  

  
 */
inline f32
S16ToF32(s16 x)
{
    return f32(x);

}



/*
  

  

  
 */
inline f32
FInv(f32 x)
{
    f32 ix;

    ix = 1.0f / x;


    return ix;
}


/*
  

  

  
 */
inline f32 
FrSqrt(f32 x)
{
    NN_MATH_WARNING(x > 0, "FrSqrt: Input is out of the domain.");

    return 1.f / ::std::sqrtf(x);
}


/*
  

  

  
 */
inline f32
FSqrt(f32 x)
{
    NN_MATH_WARNING(x >= 0, "FSqrt: Input is out of the domain.");

    return ::std::sqrtf(x);
}


/*
  

  

  
 */
inline f32
FCbrt(f32 x)
{
#if defined(NN_CW3)
    return ::std::cbrtf(x);
#else
    return ::std::pow(x, 1/3.f);
#endif
}


/*
  

  
  
  
  
  

  
 */
inline f32 
Hermite(f32 v0, f32 t0, f32 v1, f32 t1, f32 s)
{
#if defined( NN_HARDWARE_CTR )
    #if (HERMITE_5_CONFIG == D_ORG)
        return ARMv6::HermiteC(v0, t0, v1, t1, s);
    #elif (HERMITE_5_CONFIG == D_FAST_C)
        return ARMv6::HermiteC_FAST(v0, t0, v1, t1, s);
    #elif (HERMITE_5_CONFIG == D_FAST_ASM)
    #elif (HERMITE_5_CONFIG == D_FAST_C_ALGO)
    #elif (HERMITE_5_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}


/*
  

  
  
  
  
  
  

  
 */
NN_FORCE_INLINE f32
Hermite(f32 v0, f32 t0, f32 v1, f32 t1, f32 p, f32 d)
{
#if defined( NN_HARDWARE_CTR )
    #if (HERMITE_6_CONFIG == D_ORG)
        return ARMv6::HermiteC(v0, t0, v1, t1, p, d);
    #elif (HERMITE_6_CONFIG == D_FAST_C)
        return ARMv6::HermiteC_FAST(v0, t0, v1, t1, p, d);
    #elif (HERMITE_6_CONFIG == D_FAST_ASM)
        return ARMv6::HermiteAsm(v0, t0, v1, t1, p, d);
    #elif (HERMITE_6_CONFIG == D_FAST_C_ALGO)
    #elif (HERMITE_6_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}


f32 Bezier(f32 p1, f32 p2, f32 p3, f32 p4, f32 s);
f32 CatmullRom(f32 p0, f32 p1, f32 p2, f32 p3, f32 s);

/*  

*/

/* =======================================================================
        Integer-related
   ======================================================================== */

/* Please see man pages for details 
    
    
*/

// Non-Inline Functions

u32 CntBit1(u32 x);
u32 CntBit1(const u32* first, const u32* last);
u32 DistBit(const u32* first1, const u32* last1, const u32* first2);
u32 RevBit(u32 x);
int IExp(int x, u32 n);
u32 ILog10(u32 x);

#ifndef NN_PROCESSOR_ARM
namespace internal
{
u32 CntLz_(u32 x);
}
#endif

/*
  

  

  
 */
inline u32
CntLz(u32 x)
{
#ifdef NN_PROCESSOR_ARM
    return __clz(x);
#else
    return internal::CntLz_(x);
#endif
}


/*
  

  

  
 */
//          However, the function returns TRUE if x is 0.
inline bool IsPwr2(int x) { return 0 == (x & (x - 1)); }

/*
  

  

  
 */
inline int Rightmost1(int x) { return x & (-x); }
/*
  

  

  
 */
inline bit32 Rightmost1(bit32 x) { return x & (-x); }
/*
  

  

  
 */
inline bit64 Rightmost1(bit64 x) { return x & (-x); }

/*
  

  

  
 */
inline int Rightmost0(int x) { return ~x & (x + 1); }
/*
  

  

  
 */
inline bit32 Rightmost0(bit32 x) { return ~x & (x + 1); }
/*
  

  

  
 */
inline bit64 Rightmost0(bit64 x) { return ~x & (x + 1); }

/*
  

  
  

  
 */
inline u32 DistBit(u32 x, u32 y) { return CntBit1(x ^ y); }

/*
  

  

  
 */
inline u32 CntTz(u32 x) { return 32 - CntLz(~x & (x - 1)); }

/*
  

  

  
 */
inline u32 ILog2(u32 x) { return 31 - CntLz(x); }

/*
  

  

  
 */
inline u32 FloorPwr2(u32 x) { return 0x80000000 >> CntLz(x); }

/*
  

  

  
 */
inline u32 CeilPwr2(u32 x) { return 0x80000000 >> (CntLz(x - 1) - 1); }

/*  

*/

}}  // nn::math

#pragma pop

/* NN_MATH_ARITHMETIC_H_ */
#endif
