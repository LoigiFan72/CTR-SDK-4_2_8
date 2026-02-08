/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Types.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 45601 $
 *---------------------------------------------------------------------------*/

namespace nn { 
namespace math {

NN_MATH_INLINE MTX23* 
MTX22ToMTX23(MTX23* pOut, const MTX22* pM)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pM );
    
    pOut->f._00 = pM->f._00;
    pOut->f._01 = pM->f._01;
    pOut->f._10 = pM->f._10;
    pOut->f._11 = pM->f._11;

    pOut->f._02 = pOut->f._12 = 0.f;
    return pOut;
}

NN_MATH_INLINE MTX22* 
MTX23ToMTX22(MTX22* pOut, const MTX23* pM)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pM );
    
    pOut->f._00 = pM->f._00; pOut->f._01 = pM->f._01;
    pOut->f._10 = pM->f._10; pOut->f._11 = pM->f._11;
    
    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2Transform(VEC2* pOut, const MTX23* pM, const VEC2* pV)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pM );
    NN_NULL_ASSERT( pV );
    
    VEC2 tmp;
    const VEC2* pVec;
    if (pOut == pV)
    {
        tmp.x = pV->x;
        tmp.y = pV->y;
        pVec = &tmp;
    }
    else
    {
        pVec = pV;
    }
    
    pOut->x = pM->f._00 * pVec->x + pM->f._01 * pVec->y + pM->f._02;
    pOut->y = pM->f._10 * pVec->x + pM->f._11 * pVec->y + pM->f._12;
    
    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3TransformArray(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV, s32 count)
{
    NN_NULL_ASSERT( pM );
    NN_NULL_ASSERT( pV );
    NN_NULL_ASSERT( pOut );
    NN_ASSERT( count > 1 );
#if 1 //Revert expanded one to original form
    VEC3* __restrict pOutBase = pOut;

    for (s32 i = 0; i < count; ++i)
    {
        (void)VEC3Transform(pOut, pM, pV);

        pV++;
        pOut++;
    }
#else
    VEC3 vTmp;
    VEC3* __restrict pOutBase = pOut;
    const f32 (*const m)[4] = pM->m;
    
    for (s32 i = 0; i < count; ++i)
    {
        // Vec has a 4th implicit 'w' coordinate of 1
        vTmp.x = m[0][0] * pV->x + m[0][1] * pV->y + m[0][2] * pV->z + m[0][3];
        vTmp.y = m[1][0] * pV->x + m[1][1] * pV->y + m[1][2] * pV->z + m[1][3];
        vTmp.z = m[2][0] * pV->x + m[2][1] * pV->y + m[2][2] * pV->z + m[2][3];

        // copy back
        pOut->x = vTmp.x;
        pOut->y = vTmp.y;
        pOut->z = vTmp.z;

        pV++;
        pOut++;
    }
#endif
    
    return pOutBase;
}

NN_MATH_INLINE VEC4*
VEC3TransformArray(VEC4* pOut, const MTX44* __restrict pM, const VEC3* __restrict pV, u32 count)
{
    u32 i;
    VEC4* pDst = pOut;
    for (i = 0; i < count; ++i)
    {
        (void)VEC3Transform(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV)
{
    VEC3 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    
    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3TransformNormalArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, u32 count)
{
    u32 i;
    VEC3 tmp;
    VEC3* pDst = pOut;

    for (i = 0; i < count; i++)
    {
        // Vec has a 4th implicit 'w' coordinate of 1
        tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z;
        tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z;
        tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z;

        // copy back
        pDst->x = tmp.x;
        pDst->y = tmp.y;
        pDst->z = tmp.z;

        pV++;
        pDst++;
    }

    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV)
{
    VEC3 tmp;
    f32 rw;
    
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23;
       rw = pM->f._30 * pV->x + pM->f._31 * pV->y + pM->f._32 * pV->z + pM->f._33;
    rw = 1.f / rw;

    pOut->x = rw * tmp.x;
    pOut->y = rw * tmp.y;
    pOut->z = rw * tmp.z;

    return pOut;
}

NN_MATH_INLINE VEC3*
VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count)
{
    u32 i;
    VEC3* pDst = pOut;
    for (i = 0; i < count; ++i)
    {
        (void)VEC3TransformCoord(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX44* __restrict pM, const VEC4* __restrict pV)
{
    VEC4 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03 * pV->w;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13 * pV->w;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23 * pV->w;
    tmp.w = pM->f._30 * pV->x + pM->f._31 * pV->y + pM->f._32 * pV->z + pM->f._33 * pV->w;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = tmp.w;

    return pOut;
}

NN_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 count)
{
    u32 i;
    VEC4* pDst = pOut;
    for (i = 0; i < count; ++i)
    {
        (void)VEC4Transform(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

}  // namespace math
}  // namespace nn


