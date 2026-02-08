/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix43.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 47340 $
 *---------------------------------------------------------------------------*/

namespace nn { namespace math {

NN_MATH_INLINE MTX43*
MTX43Identity(MTX43* pOut)
{
    NN_NULL_ASSERT( pOut );

    MTX43Copy(pOut, MTX43::Identity());

    return pOut;
}

NN_MATH_INLINE bool
MTX43IsIdentity(const MTX43* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f &&
           p->f._20 == 0.f && p->f._21 == 0.f && p->f._22 == 1.f &&
           p->f._30 == 0.f && p->f._31 == 0.f && p->f._32 == 0.f;
}

NN_MATH_INLINE MTX43*
MTX43Sub(MTX43* pOut, const MTX43* p1, const MTX43* p2)
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

    pOut->f._20 = p1->f._20 - p2->f._20;
    pOut->f._21 = p1->f._21 - p2->f._21;
    pOut->f._22 = p1->f._22 - p2->f._22;

    pOut->f._30 = p1->f._30 - p2->f._30;
    pOut->f._31 = p1->f._31 - p2->f._31;
    pOut->f._32 = p1->f._32 - p2->f._32;

    return pOut;
}

NN_MATH_INLINE MTX43*
MTX43Zero(MTX43* pOut)
{
    NN_NULL_ASSERT( pOut );

    pOut->f._00 = pOut->f._01 = pOut->f._02 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 =
    pOut->f._20 = pOut->f._21 = pOut->f._22 = 
    pOut->f._30 = pOut->f._31 = pOut->f._32 = 0.f;

    return pOut;
}

}  // namespace math
}  // namespace nn
