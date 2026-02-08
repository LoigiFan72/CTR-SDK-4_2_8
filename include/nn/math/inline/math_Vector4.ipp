/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector4.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 45840 $
 *---------------------------------------------------------------------------*/

namespace nn {
namespace math {

/* ------------------------------------------------------------------------
        VEC4
   ------------------------------------------------------------------------ */

NN_MATH_INLINE VEC4*
VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = p1->x + p2->x;
    pOut->y = p1->y + p2->y;
    pOut->z = p1->z + p2->z;
    pOut->w = p1->w + p2->w;

    return pOut;
}

NN_MATH_INLINE f32 
VEC4DistSq(const VEC4* p1, const VEC4* p2)
{
    VEC4 tmp;
    return VEC4LenSq(VEC4Sub(&tmp, p1, p2));
}

NN_MATH_INLINE f32 
VEC4Dot(const VEC4* p1, const VEC4* p2)
{
    return p1->x * p2->x + p1->y * p2->y + p1->z * p2->z + p1->w * p2->w;
}

NN_MATH_INLINE bool
VEC4IsZero(const VEC4* p)
{
    return p->x == 0.f && p->y == 0.f && p->z == 0.f && p->w == 0.f;
}

NN_MATH_INLINE bool
VEC4IsZeroWOne(const VEC4* p)
{
    return p->x == 0.f && p->y == 0.f && p->z == 0.f && p->w == 1.f;
}

NN_MATH_INLINE f32
VEC4Len(const VEC4* p)
{
    return FSqrt(VEC4LenSq(p));

}

NN_MATH_INLINE f32 
VEC4LenSq(const VEC4* __restrict p)
{
    return p->x * p->x + p->y * p->y + p->z * p->z + p->w * p->w;

}

NN_MATH_INLINE VEC4*
VEC4Lerp(VEC4* pOut, const VEC4* __restrict p1, const VEC4* __restrict p2, f32 t)
{
    // (1-t)*p1 + t*p2
    pOut->x = p1->x + t * (p2->x - p1->x);
    pOut->y = p1->y + t * (p2->y - p1->y);
    pOut->z = p1->z + t * (p2->z - p1->z);
    pOut->w = p1->w + t * (p2->w - p1->w);

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2) 
{
    pOut->x = (p1->x > p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y > p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z > p2->z) ? p1->z : p2->z;
    pOut->w = (p1->w > p2->w) ? p1->w : p2->w;

    return pOut;
}
NN_MATH_INLINE VEC4*
VEC4Mult(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = p1->x * p2->x;
    pOut->y = p1->y * p2->y;
    pOut->z = p1->z * p2->z;
    pOut->w = p1->w * p2->w;
    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4Normalize(VEC4* pOut, const VEC4* p)
{
    (void)VEC4Scale(pOut, p, FrSqrt(VEC4LenSq(p)));

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4SafeNormalize(VEC4* pOut, const VEC4* p, const VEC4& alt)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(p);

    f32 mag = VEC4LenSq(p);

    if (mag == 0)
    {
        *pOut = alt;

        return pOut;
    }

    (void)VEC4Scale(pOut, p, FrSqrt(mag));

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2) 
{
    pOut->x = (p1->x < p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y < p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z < p2->z) ? p1->z : p2->z;
    pOut->w = (p1->w < p2->w) ? p1->w : p2->w;

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale)
{
    pOut->x = scale * p->x;
    pOut->y = scale * p->y;
    pOut->z = scale * p->z;
    pOut->w = scale * p->w;

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = p1->x - p2->x;
    pOut->y = p1->y - p2->y;
    pOut->z = p1->z - p2->z;
    pOut->w = p1->w - p2->w;

    return pOut;
}

}  // namespace math
}  // namespace nn
