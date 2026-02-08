/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Quaternion.ipp

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

#define NN_QUAT_EPSILON        0.00001F

NN_MATH_INLINE QUAT*
QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q1 );
    NN_NULL_ASSERT( q2 );

    pOut->x = q1->x + q2->x;
    pOut->y = q1->y + q2->y;
    pOut->z = q1->z + q2->z;
    pOut->w = q1->w + q2->w;

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATDivide(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    QUAT qtmp;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q1 );
    NN_NULL_ASSERT( q2 );

    QUATInverse(&qtmp, q2);
    QUATMult(pOut, &qtmp, q1);

    return pOut;
}

NN_MATH_INLINE f32
QUATDot(const QUAT* q1, const QUAT* q2)
{
    NN_NULL_ASSERT( q1 );
    NN_NULL_ASSERT( q2 );

    return (q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w);
}

NN_MATH_INLINE QUAT*
QUATExp(QUAT* pOut, const QUAT* __restrict q)
{
    f32 theta, scale;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q );

    // pure quaternion check
    NN_ASSERT( q->w == 0.0F );

    theta = ::std::sqrtf( q->x * q->x + q->y * q->y + q->z * q->z );
    scale = 1.0F;

    if ( theta > NN_QUAT_EPSILON )
    {
        scale = (f32)::std::sinf(theta) / theta;
    }

    pOut->x = scale * q->x;
    pOut->y = scale * q->y;
    pOut->z = scale * q->z;
    pOut->w = (f32)::std::cosf(theta);

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATLerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q1 );
    NN_NULL_ASSERT( q2 );

    pOut->x = t * ( q2->x - q1->x ) + q1->x;
    pOut->y = t * ( q2->y - q1->y ) + q1->y;
    pOut->z = t * ( q2->z - q1->z ) + q1->z;
    pOut->w = t * ( q2->w - q1->w ) + q1->w;

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATLogN(QUAT* pOut, const QUAT* __restrict q)
{
    f32 theta, scale;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q );

    scale = q->x * q->x + q->y * q->y + q->z * q->z;

    scale = ::std::sqrtf(scale);
    theta = ::std::atan2f( scale, q->w );

    if ( scale > 0.0F )
    {
        scale = theta / scale;
    }

    pOut->x = scale * q->x;
    pOut->y = scale * q->y;
    pOut->z = scale * q->z;
    pOut->w = 0.0F;

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATMakeClosest(QUAT* pOut, const QUAT *q, const QUAT *qto)
{
    f32 dot;

    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(q   );
    NN_NULL_ASSERT(qto );

    dot =  q->x * qto->x + q->y * qto->y + q->z * qto->z + q->w * qto->w;

    if ( dot < 0.0f )
    {
        pOut->x = -q->x;
        pOut->y = -q->y;
        pOut->z = -q->z;
        pOut->w = -q->w;
    }
    else
    {
        *pOut = *q;
    }

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATRotAxisRad( QUAT *pOut, const VEC3 *axis, f32 rad )
{
    f32 half, sh, ch;
    VEC3 nAxis;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( axis );

    VEC3Normalize(&nAxis, axis);

    half = rad * 0.50F;
    sh   = ::std::sinf(half);
    ch   = ::std::cosf(half);

    pOut->x = sh * nAxis.x;
    pOut->y = sh * nAxis.y;
    pOut->z = sh * nAxis.z;
    pOut->w = ch;

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATScale(QUAT* pOut, const QUAT* q, f32 scale)
{
    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( q  );

    pOut->x = q->x * scale;
    pOut->y = q->y * scale;
    pOut->z = q->z * scale;
    pOut->w = q->w * scale;

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATSlerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    f32 theta, sin_th, cos_th, tp, tq;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q1 );
    NN_NULL_ASSERT( q2 );

    cos_th = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;
    tq     = 1.0F;

    if ( cos_th < 0.0F )
    {
        cos_th = -cos_th;
        tq     = -tq;
    }

    if ( cos_th <= 1.0F - NN_QUAT_EPSILON )
    {
        theta  = ::std::acosf(cos_th);
        sin_th = ::std::sinf(theta);
        tp     = ::std::sinf((1.0F - t) * theta) / sin_th;
        tq    *= ::std::sinf( t * theta ) / sin_th;
    }
    else
    {
        // cos(theta) is close to 1.0F -> linear
        tp = 1.0F - t;
        tq = tq * t;
    }

    pOut->x = tp * q1->x + tq * q2->x;
    pOut->y = tp * q1->y + tq * q2->y;
    pOut->z = tp * q1->z + tq * q2->z;
    pOut->w = tp * q1->w + tq * q2->w;

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATSquad(QUAT* pOut, const QUAT* p, const QUAT* a, const QUAT* b, const QUAT* q, f32 t)
{
    QUAT pq, ab;
    f32 t2;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );
    NN_NULL_ASSERT( a );
    NN_NULL_ASSERT( b );
    NN_NULL_ASSERT( q );

    t2 = 2 * t * ( 1.0F - t );
    QUATSlerp(&pq, p, q, t);
    QUATSlerp(&ab, a, b, t);
    QUATSlerp(pOut, &pq, &ab, t2);

    return pOut;
}

NN_MATH_INLINE QUAT*
QUATSub(QUAT *pOut,  const QUAT *q1, const QUAT *q2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q1 );
    NN_NULL_ASSERT( q2 );

    pOut->x = q1->x - q2->x;
    pOut->y = q1->y - q2->y;
    pOut->z = q1->z - q2->z;
    pOut->w = q1->w - q2->w;

    return pOut;
}

}  // namespace math
}  // namespace nn

