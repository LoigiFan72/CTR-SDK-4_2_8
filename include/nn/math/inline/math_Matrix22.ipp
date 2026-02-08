/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix22.ipp

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
        MTX22
   ------------------------------------------------------------------------ */
NN_MATH_INLINE MTX22* 
MTX22Copy(MTX22* pOut, const MTX22* p)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );

    if (pOut != p)
    {
        *pOut = *p;
    }

    return pOut;
}

NN_MATH_INLINE MTX22*
MTX22Identity(MTX22* pOut)
{
    NN_NULL_ASSERT( pOut );

    MTX22Copy(pOut, MTX22::Identity());

    return pOut;
}

NN_MATH_INLINE bool
MTX22IsIdentity(const MTX22* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f;
}

NN_MATH_INLINE MTX22* 
MTX22MAdd(MTX22* pOut, f32 t, const MTX22* p1, const MTX22* p2)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    pOut->f._00 = t * p1->f._00 + p2->f._00;
    pOut->f._01 = t * p1->f._01 + p2->f._01;

    pOut->f._10 = t * p1->f._10 + p2->f._10;
    pOut->f._11 = t * p1->f._11 + p2->f._11;

    return pOut;
}

NN_MATH_INLINE MTX22* 
MTX22Zero(MTX22* pOut)
{
    NN_NULL_ASSERT( pOut );

    pOut->f._00 = pOut->f._01 = 
    pOut->f._10 = pOut->f._11 = 0.f;
    return pOut;
}

}  // namespace math
}  // namespace nn
