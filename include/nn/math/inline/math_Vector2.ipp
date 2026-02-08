/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector2.ipp

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
        VEC2
   ------------------------------------------------------------------------ */
NN_MATH_INLINE bool
VEC2IsZero(const VEC2* p)
{
    return p->x == 0.f && p->y == 0.f;
}

NN_MATH_INLINE VEC2*
VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = (p1->x > p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y > p2->y) ? p1->y : p2->y;

    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = (p1->x < p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y < p2->y) ? p1->y : p2->y;

    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2Normalize(VEC2* pOut, const VEC2* p)
{
    (void)VEC2Scale(pOut, p, FrSqrt(p->x * p->x + p->y * p->y));

    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2SafeNormalize(VEC2* pOut, const VEC2* p, const VEC2& alt)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(p);

    f32 mag = (p->x * p->x) + (p->y * p->y);

    if (mag == 0)
    {
        *pOut = alt;

        return pOut;
    }

    (void)VEC2Scale(pOut, p, FrSqrt(mag));

    return pOut;
}

}  // namespace math
}  // namespace nn
