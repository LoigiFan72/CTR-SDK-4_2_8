/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix23.ipp

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
        MTX23
   ------------------------------------------------------------------------ */
NN_MATH_INLINE MTX23*
MTX23Add(MTX23* pOut, const MTX23* p1, const MTX23* p2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    pOut->f._00 = p1->f._00 + p2->f._00;
    pOut->f._01 = p1->f._01 + p2->f._01;
    pOut->f._02 = p1->f._02 + p2->f._02;

    pOut->f._10 = p1->f._10 + p2->f._10;
    pOut->f._11 = p1->f._11 + p2->f._11;
    pOut->f._12 = p1->f._12 + p2->f._12;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Copy(MTX23* pOut, const MTX23* p)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );

    if (pOut != p)
    {
        *pOut = *p;
    }

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Identity(MTX23* pOut)
{
    NN_NULL_ASSERT( pOut );

    MTX23Copy(pOut, MTX23::Identity());

    return pOut;
}

NN_MATH_INLINE bool
MTX23IsIdentity(const MTX23* p)
{
    NN_NULL_ASSERT( p );

    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f;
}

NN_MATH_INLINE MTX23*
MTX23MAdd(MTX23* pOut, f32 t, const MTX23* p1, const MTX23* p2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    pOut->f._00 = t * p1->f._00 + p2->f._00;
    pOut->f._01 = t * p1->f._01 + p2->f._01;
    pOut->f._02 = t * p1->f._02 + p2->f._02;

    pOut->f._10 = t * p1->f._10 + p2->f._10;
    pOut->f._11 = t * p1->f._11 + p2->f._11;
    pOut->f._12 = t * p1->f._12 + p2->f._12;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Mult(MTX23* pOut, const MTX23* p, f32 f)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );

    pOut->f._00 = p->f._00 * f;
    pOut->f._01 = p->f._01 * f;
    pOut->f._02 = p->f._02 * f;

    pOut->f._10 = p->f._10 * f;
    pOut->f._11 = p->f._11 * f;
    pOut->f._12 = p->f._12 * f;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Mult(MTX23* pOut, const MTX23* __restrict p1, const MTX23* __restrict p2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    MTX23  tmp;
    MTX23* __restrict pMtx;

    if ( (pOut == p1) || (pOut == p2) )
    {
        pMtx = &tmp;
    }
    else
    {
        pMtx = pOut;
    }

    pMtx->f._00 = p1->f._00 * p2->f._00 + p1->f._01 * p2->f._10;
    pMtx->f._01 = p1->f._00 * p2->f._01 + p1->f._01 * p2->f._11;
    pMtx->f._02 = p1->f._00 * p2->f._02 + p1->f._01 * p2->f._12 + p1->f._02;

    pMtx->f._10 = p1->f._10 * p2->f._00 + p1->f._11 * p2->f._10;
    pMtx->f._11 = p1->f._10 * p2->f._01 + p1->f._11 * p2->f._11;
    pMtx->f._12 = p1->f._10 * p2->f._02 + p1->f._11 * p2->f._12 + p1->f._12;

    if (pMtx == &tmp)
    {
        MTX23Copy(pOut, &tmp);
    }

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23MultTranslate(MTX23* pOut, const MTX23* pM, const VEC2* pT)
{
    if (pOut != pM)
    {
        (void)MTX23Copy(pOut, pM);
    }

    VEC2 tmp;
    VEC2Transform(&tmp, pM, pT);

    pOut->f._02 = tmp.x;
    pOut->f._12 = tmp.y;
    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23MultTranslate(MTX23* pOut, const VEC2* pT, const MTX23* pM)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pT);
    NN_NULL_ASSERT(pM);

    const f32 (*const src)[3] = pM->m;
    f32 (*const dst)[3] = pOut->m;

    if ( src != dst )
    {
        dst[0][0] = src[0][0];    dst[0][1] = src[0][1];
        dst[1][0] = src[1][0];    dst[1][1] = src[1][1];
    }

    dst[0][2] = src[0][2] + pT->x;
    dst[1][2] = src[1][2] + pT->y;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23RotCenterFIdx(MTX23* pOut, const VEC2* pCenter, f32 fIdx)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pCenter );

    MTX23 trans;
    trans.f._00 = trans.f._11 = 1.f;
    trans.f._10 = trans.f._01 = 0.f;
    trans.f._02 = pCenter->x;
    trans.f._12 = pCenter->y;

    f32 sin, cos;

    SinCosFIdx(&sin, &cos, fIdx);

    (void)MTX23RotFIdx(pOut, fIdx);

    MTX23Mult(pOut, &trans, pOut);

    trans.f._02 = -trans.f._02;
    trans.f._12 = -trans.f._12;

    MTX23Mult(pOut, pOut, &trans);

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23RotFIdx(MTX23* pOut, f32 fIdx)
{
    NN_NULL_ASSERT( pOut );

    f32 sin, cos;

    SinCosFIdx(&sin, &cos, fIdx);

    pOut->f._00 = pOut->f._11 = cos;
    pOut->f._01 = sin;
    pOut->f._10 = -sin;
    pOut->f._02 = pOut->f._12 = 0.f;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Scale(MTX23* pOut, const MTX23* __restrict pM, const VEC2* __restrict pS)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pM );
    NN_NULL_ASSERT( pS );

    pOut->f._00 = pM->f._00 * pS->x;
    pOut->f._10 = pM->f._10 * pS->x;

    pOut->f._01 = pM->f._01 * pS->y;
    pOut->f._11 = pM->f._11 * pS->y;

    if (pOut != pM)
    {
        pOut->f._02 = pM->f._02;
        pOut->f._12 = pM->f._12;
    }
    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Sub(MTX23* pOut, const MTX23* p1, const MTX23* p2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    pOut->f._00 = p1->f._00 - p2->f._00;
    pOut->f._01 = p1->f._01 - p2->f._01;
    pOut->f._02 = p1->f._02 - p2->f._02;

    pOut->f._10 = p1->f._10 - p2->f._10;
    pOut->f._11 = p1->f._11 - p2->f._11;
    pOut->f._12 = p1->f._12 - p2->f._12;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Translate(MTX23* pOut, const VEC2* pT)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pT );

    f32 (*const m)[3] = pOut->m;

    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = pT->x;
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = pT->y;

    return pOut;
}

NN_MATH_INLINE MTX23*
MTX23Zero(MTX23* pOut)
{
    NN_NULL_ASSERT( pOut );

    pOut->f._00 = pOut->f._01 = pOut->f._02 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 = 0.f;

    return pOut;
}

}  // namespace math
}  // namespace nn
