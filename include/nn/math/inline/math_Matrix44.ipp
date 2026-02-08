/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix44.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 45840 $
 *---------------------------------------------------------------------------*/

#include <cmath>
#include <nn/math/math_Vector3.h>

namespace nn {
namespace math {

/* ------------------------------------------------------------------------
        MTX44
   ------------------------------------------------------------------------ */

NN_MATH_INLINE MTX44*
MTX44FrustumPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot)
{
    MTX44Frustum( pOut, l, r, b, t, n, f );
    MTX44Pivot( pOut, pivot );

    return pOut;
}

NN_MATH_INLINE MTX44*
MTX44Identity(MTX44* pOut)
{
    NN_NULL_ASSERT( pOut );

    MTX44Copy(pOut, MTX44::Identity());

    return pOut;
}

NN_MATH_INLINE bool
MTX44IsIdentity(const MTX44* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f && p->f._03 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f && p->f._13 == 0.f &&
           p->f._20 == 0.f && p->f._21 == 0.f && p->f._22 == 1.f && p->f._23 == 0.f &&
           p->f._30 == 0.f && p->f._31 == 0.f && p->f._32 == 0.f && p->f._33 == 1.f;
}
#if 0
namespace {
    /*---------------------------------------------------------------------------*
          Description:  Faces toward the direction of the screen and rotates the projection matrix.

      Arguments:    pOut    Pointer to the matrix to rotate
                    pivot

      Returns:
     *---------------------------------------------------------------------------*/
    inline MTX44*
    MTX44Pivot( MTX44* pOut, PivotDirection pivot )
    {
        // TODO: Process must be optimized.

        const f32 PIVOT_ROTATION_SIN_COS[ PIVOT_NUM ][ 2 ] = 
        {
        #ifdef NN_PLATFORM_CTR
            { 0.0f,  1.0f }, // NONE
            { -1.0f, 0.0f }, // TO_UP
            { 0.0f, -1.0f }, // TO_RIGHT
            { 1.0f,  0.0f }, // TO_BOTTOM
            { 0.0f,  1.0f }, // TO_LEFT
        #else
            { 0.0f,  1.0f }, // NONE
            { 0.0f,  1.0f }, // TO_UP
            { -1.0f, 0.0f }, // TO_RIGHT
            { 0.0f, -1.0f }, // TO_BOTTOM
            { 1.0f,  0.0f }, // TO_LEFT
        #endif
        };

        if ( pivot == PIVOT_NONE )
        {
            return pOut;
        }

        f32 sin = PIVOT_ROTATION_SIN_COS[ pivot ][ 0 ];
        f32 cos = PIVOT_ROTATION_SIN_COS[ pivot ][ 1 ];

        f32 (*const m)[4] = pOut->m;

        if ( sin == 0.0f )
        {
            m[0][0] = cos * m[0][0];
            m[0][1] = cos * m[0][1];
            m[0][2] = cos * m[0][2];
            m[0][3] = cos * m[0][3];

            m[1][0] = cos * m[1][0];
            m[1][1] = cos * m[1][1];
            m[1][2] = cos * m[1][2];
            m[1][3] = cos * m[1][3];
        }
        else // if ( cos == 0.0f )
        {
            f32 tmp = m[0][0];
            m[0][0] = -sin * m[1][0];
            m[1][0] = sin * tmp;

            tmp = m[0][1];
            m[0][1] = -sin * m[1][1];
            m[1][1] = sin * tmp;

            tmp = m[0][2];
            m[0][2] = -sin * m[1][2];
            m[1][2] = sin * tmp;

            tmp = m[0][3];
            m[0][3] = -sin * m[1][3];
            m[1][3] = sin * tmp;
        }

        return pOut;
    }

} // Namespace
#endif

NN_MATH_INLINE MTX44*
MTX44MultArray(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict pSrc, s32 count)
{
    MTX44* pOutBase = pOut;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( pSrc );
    NN_ASSERT( count > 1 );

    for ( s32 i = 0 ; i < count ; i++ )
    {
        MTX44Mult(pOut, p1, pSrc);

        pSrc++;
        pOut++;
    }

    return pOutBase;
}

namespace {
    inline void SwapF(f32 &a, f32 &b)
    {
        f32 tmp;
        tmp = a;
        a = b;
        b = tmp;
    }
} // namespace (unnamed)

NN_MATH_INLINE MTX44*
MTX44OrthoPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot)
{
    MTX44Ortho( pOut, l, r, b, t, n, f );
    MTX44Pivot( pOut, pivot );

    return pOut;
}

NN_MATH_INLINE MTX44*
MTX44PerspectivePivotRad(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f, PivotDirection pivot)
{
    MTX44PerspectiveRad( pOut, fovy, aspect, n, f );
    MTX44Pivot( pOut, pivot );

    return pOut;
}

NN_MATH_INLINE MTX44*
MTX44RotAxisFIdx(MTX44* pOut, const VEC3* pAxis, f32 fIdx)
{
    // Okay for now if it's slow
    MTX44RotAxisRad_(pOut, pAxis, NN_MATH_FIDX_TO_RAD(fIdx));

    return pOut;
}

NN_MATH_INLINE MTX44*
MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    pOut->f._00 = p1->f._00 - p2->f._00;
    pOut->f._01 = p1->f._01 - p2->f._01;
    pOut->f._02 = p1->f._02 - p2->f._02;
    pOut->f._03 = p1->f._03 - p2->f._03;

    pOut->f._10 = p1->f._10 - p2->f._10;
    pOut->f._11 = p1->f._11 - p2->f._11;
    pOut->f._12 = p1->f._12 - p2->f._12;
    pOut->f._13 = p1->f._13 - p2->f._13;

    pOut->f._20 = p1->f._20 - p2->f._20;
    pOut->f._21 = p1->f._21 - p2->f._21;
    pOut->f._22 = p1->f._22 - p2->f._22;
    pOut->f._23 = p1->f._23 - p2->f._23;

    pOut->f._30 = p1->f._30 - p2->f._30;
    pOut->f._31 = p1->f._31 - p2->f._31;
    pOut->f._32 = p1->f._32 - p2->f._32;
    pOut->f._33 = p1->f._33 - p2->f._33;

    return pOut;
}

NN_MATH_INLINE MTX44*
MTX44Zero(MTX44* pOut)
{
    pOut->f._00 = pOut->f._01 = pOut->f._02 = pOut->f._03 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 = pOut->f._13 =
    pOut->f._20 = pOut->f._21 = pOut->f._22 = pOut->f._23 =
    pOut->f._30 = pOut->f._31 = pOut->f._32 = pOut->f._33 = 0.f;

    return pOut;
}

}  // namespace math
}  // namespace nn
