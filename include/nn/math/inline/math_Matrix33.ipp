/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix33.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 45840 $
 *---------------------------------------------------------------------------*/
#include <nn/math/math_Vector3.h>

namespace nn {
namespace math {

NN_MATH_INLINE MTX33*
MTX33Identity(MTX33* pOut)
{
    NN_NULL_ASSERT( pOut );

    MTX33Copy(pOut, MTX33::Identity());

    return pOut;
}

NN_MATH_INLINE bool
MTX33IsIdentity(const MTX33* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f &&
           p->f._20 == 0.f && p->f._21 == 0.f && p->f._22 == 1.f;
}

NN_MATH_INLINE MTX33*
MTX33Zero(MTX33* pOut)
{
    pOut->f._00 = pOut->f._01 = pOut->f._02 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 =
    pOut->f._20 = pOut->f._21 = pOut->f._22 = 0.f;

    return pOut;
}

}  // namespace math
}  // namespace nn
