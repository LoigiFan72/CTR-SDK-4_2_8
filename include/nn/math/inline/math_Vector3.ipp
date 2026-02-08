/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector3.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 45840 $
 *---------------------------------------------------------------------------*/

#include <cmath>

namespace nn {
namespace math {

/* ------------------------------------------------------------------------
        VEC3
   ------------------------------------------------------------------------ */

NN_MATH_INLINE VEC3*
VEC3Cross(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(p1);
    NN_NULL_ASSERT(p2);

    VEC3 tmpVec;

    tmpVec.x = ( p1->y * p2->z ) - ( p1->z * p2->y );
    tmpVec.y = ( p1->z * p2->x ) - ( p1->x * p2->z );
    tmpVec.z = ( p1->x * p2->y ) - ( p1->y * p2->x );

    pOut->x = tmpVec.x;
    pOut->y = tmpVec.y;
    pOut->z = tmpVec.z;

    return pOut;
}

NN_MATH_INLINE bool
VEC3IsZero(const VEC3* p)
{
    return p->x == 0.f && p->y == 0.f && p->z == 0.f;
}

NN_MATH_INLINE VEC3*
VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = (p1->x > p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y > p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z > p2->z) ? p1->z : p2->z;

    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = (p1->x < p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y < p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z < p2->z) ? p1->z : p2->z;

    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3SafeNormalize(VEC3* pOut, const VEC3* p, const VEC3& alt)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(p);

    register f32 x, y, z, mag;

    x = p->x;
    y = p->y;
    z = p->z;

    mag = (x * x) + (y * y) + (z * z);

    if (mag == 0)
    {
        *pOut = alt;

        return pOut;
    }

    mag = 1.0f / ::std::sqrtf(mag);

    x *= mag;
    y *= mag;
    z *= mag;

    pOut->x = x;
    pOut->y = y;
    pOut->z = z;

    return pOut;
}

NN_MATH_INLINE f32
VEC3SquareDist(const VEC3* p1, const VEC3* p2)
{
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

  VEC3 diff;

    diff.x = p1->x - p2->x;
    diff.y = p1->y - p2->y;
    diff.z = p1->z - p2->z;

    return (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
}

}  // namespace math
}  // namespace nn
