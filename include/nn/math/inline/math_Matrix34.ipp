/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix34.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 47340 $
 *---------------------------------------------------------------------------*/
#include <cmath>
#include <nn/math/math_Vector3.h>

namespace nn {
namespace math {


/* ------------------------------------------------------------------------
        MTX34
   ------------------------------------------------------------------------ */

NN_MATH_INLINE MTX34*
MTX34Identity(MTX34* pOut) 
{
    NN_NULL_ASSERT( pOut );

    MTX34Copy(pOut, MTX34::Identity());

    return pOut;
}

NN_MATH_INLINE u32
MTX34InvTranspose(MTX33* pOut, const MTX34* __restrict p)
{
    MTX34 tmp;
    u32 rval = MTX34InvTranspose(&tmp, p);
    (void)MTX34ToMTX33(pOut, &tmp);
    return rval;
}

NN_MATH_INLINE bool
MTX34IsIdentity(const MTX34* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f && p->f._03 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f && p->f._13 == 0.f &&
           p->f._20 == 0.f && p->f._21 == 0.f && p->f._22 == 1.f && p->f._23 == 0.f;
}

NN_MATH_INLINE MTX34*
MTX34MultArray(MTX34* pOut, const MTX34* __restrict p1, const MTX34* __restrict pSrc, s32 count)
{
    MTX34* pOutBase = pOut;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( pSrc );
    NN_ASSERT( count > 1 );

    for ( s32 i = 0 ; i < count ; i++ )
    {
        MTX34Mult(pOut, p1, pSrc);

        pSrc++;
        pOut++;
    }

    return pOutBase;
}

NN_MATH_INLINE MTX34*
MTX34RotAxisFIdx(MTX34* pOut, const VEC3* pAxis, f32 fIdx)
{
    // Okay for now if it's slow
    MTX34RotAxisRad_(pOut, pAxis, NN_MATH_FIDX_TO_RAD(fIdx));

    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34RotXYZTranslateFIdx(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, const VEC3* pT)
{
    (void)MTX34RotXYZFIdx(pOut, fIdxX, fIdxY, fIdxZ);
    pOut->f._03 = pT->x;
    pOut->f._13 = pT->y;
    pOut->f._23 = pT->z;
    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2)
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

    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34TextureProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
{
    NN_ASSERT(t != b);
    NN_ASSERT(l != r);
    NN_NULL_ASSERT(pOut);

    f32 reverseWidth = 1.0f / (r - l);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = ((2.0f * n) * reverseWidth) * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = (((r + l) * reverseWidth) * scaleS) - translateS;
    mtx[0][3] = 0.0f;

    f32 reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = ((2.0f * n) * reverseHeight) * scaleT;
    mtx[1][2] = (((t+ b) * reverseHeight) * scaleT) - translateT;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f;
    mtx[2][3] = 0.0f;
    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34TextureProjectionOrtho(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
{
    NN_ASSERT(t != b);
    NN_ASSERT(l != r);
    NN_NULL_ASSERT(pOut);

    f32 reverseWidth = 1.0f / (r - l);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = 2.0f * reverseWidth * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = ((-(r + l) * reverseWidth) * scaleS) + translateS;

    f32 reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = (2.0f * reverseHeight) * scaleT;
    mtx[1][2] = 0.0f;
    mtx[1][3] = ((-(t + b) * reverseHeight) * scaleT) + translateT;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = 0.0f;
    mtx[2][3] = 1.0f;
    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34TextureProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
{
    NN_ASSERT((fovy > 0.0f) && (fovy < math::F_PI));
    NN_ASSERT(aspect != 0.0f);
    NN_NULL_ASSERT(pOut);

    f32 angle = fovy * 0.5f;
    f32 cot = 1.0f / math::TanRad(angle);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = (cot / aspect) * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = -translateS;
    mtx[0][3] = 0.0f;

    mtx[1][0] = 0.0f;
    mtx[1][1] = cot * scaleT;
    mtx[1][2] = -translateT;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f;
    mtx[2][3] = 0.0f;

    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34ShadowProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    NN_ASSERT(t != b);
    NN_ASSERT(l != r);
    NN_NULL_ASSERT(pOut);

    f32 reverseWidth = 1.0f / (r - l);
    f32 scale = -1.0f / (f - n);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = ((-1.0f * n) * reverseWidth) * scale;
    mtx[0][1] = 0.0f;
    mtx[0][2] = ((((r + l) * reverseWidth) * -0.5f) + 0.5f) * scale;
    mtx[0][3] = 0.0f;

    f32 reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = ((-1.0f * n) * reverseHeight) * scale;
    mtx[1][2] = ((((t+ b) * reverseHeight) * -0.5f) + 0.5f) * scale;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = scale;
    mtx[2][3] = 0.0f;
    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34ShadowProjectionOrtho(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    NN_ASSERT(t != b);
    NN_ASSERT(l != r);
    NN_NULL_ASSERT(pOut);

    f32 reverseWidth = 1.0f / (r - l);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = reverseWidth;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = -(r + l) * reverseWidth + 0.5f;

    f32 reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = reverseHeight;
    mtx[1][2] = 0.0f;
    mtx[1][3] = -(t + b) * reverseHeight + 0.5f;

    f32 tmp = -1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = tmp;
    mtx[2][3] = n * tmp;
    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34ShadowProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 n, f32 f)
{
    NN_ASSERT((fovy > 0.0f) && (fovy < math::F_PI));
    NN_ASSERT(aspect != 0.0f);
    NN_NULL_ASSERT(pOut);

    f32 angle = fovy * 0.5f;
    f32 cot = -0.5f / math::TanRad(angle);
    f32 scale = -1.0f / (f - n);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = (cot / aspect) * scale;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.5f * scale;
    mtx[0][3] = 0.0f;

    mtx[1][0] = 0.0f;
    mtx[1][1] = cot * scale;
    mtx[1][2] = 0.5f * scale;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = scale;
    mtx[2][3] = 0.0f;

    return pOut;
}

NN_MATH_INLINE MTX34*
MTX34Zero(MTX34* pOut)
{
    pOut->f._00 = pOut->f._01 = pOut->f._02 = pOut->f._03 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 = pOut->f._13 =
    pOut->f._20 = pOut->f._21 = pOut->f._22 = pOut->f._23 = 0.f;

    return pOut;
}

}  // namespace math
}  // namespace nn
