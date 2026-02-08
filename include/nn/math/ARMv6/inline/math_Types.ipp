/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Types.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 13623 $
 *---------------------------------------------------------------------------*/

namespace nn { 
namespace math {
namespace ARMv6 {

/* Please see man pages for details 
    
    
*/


/*
  

  
  

  
 */
NN_MATH_INLINE  MTX33*
MTX34ToMTX33C(MTX33* pOut, const MTX34* pM)
{
    pOut->f._00 = pM->f._00; pOut->f._01 = pM->f._01; pOut->f._02 = pM->f._02;
    pOut->f._10 = pM->f._10; pOut->f._11 = pM->f._11; pOut->f._12 = pM->f._12;
    pOut->f._20 = pM->f._20; pOut->f._21 = pM->f._21; pOut->f._22 = pM->f._22;

    return pOut;
}

/*
  

  
  

  
 */
NN_MATH_INLINE MTX34*
MTX33ToMTX34C(MTX34* pOut, const MTX33* pM)
{
    pOut->f._00 = pM->f._00; pOut->f._01 = pM->f._01; pOut->f._02 = pM->f._02;
    pOut->f._10 = pM->f._10; pOut->f._11 = pM->f._11; pOut->f._12 = pM->f._12;
    pOut->f._20 = pM->f._20; pOut->f._21 = pM->f._21; pOut->f._22 = pM->f._22;

    return pOut;
}
NN_MATH_INLINE MTX34*
MTX33ToMTX34C_FAST(MTX34* pOut, const MTX33* pM)
{
    register f32 m00, m01, m02, m10, m11, m12, m20, m21, m22;
    
    m00 = pM->f._00;
    m01 = pM->f._01;
    m02 = pM->f._02;
    
    m10 = pM->f._10;
    m11 = pM->f._11;
    m12 = pM->f._12;
    
    m20 = pM->f._20;
    m21 = pM->f._21;
    m22 = pM->f._22;

    pOut->f._00 = m00;
    pOut->f._01 = m01;
    pOut->f._02 = m02;

    pOut->f._10 = m10;
    pOut->f._11 = m11;
    pOut->f._12 = m12;

    pOut->f._20 = m20;
    pOut->f._21 = m21;
    pOut->f._22 = m22;
    
    return pOut;
}


/*
  

  
  

  
 */
NN_MATH_INLINE QUAT*
MTX34ToQUATC(QUAT* pOut, const MTX34* pMtx)
{
    f32 tr, s;
    s32 i, j, k;
    s32 nxt[3] = {1, 2, 0};
    f32 q[3];

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pMtx );

    const f32 (*const m)[4] = pMtx->m;

    tr = m[0][0] + m[1][1] + m[2][2];
    if ( tr > 0.0f )
    {
        s = (f32)::std::sqrtf(tr + 1.0f);
        pOut->w = s * 0.5f;
        s = 0.5f / s;
        pOut->x = (m[2][1] - m[1][2]) * s;
        pOut->y = (m[0][2] - m[2][0]) * s;
        pOut->z = (m[1][0] - m[0][1]) * s;
    }
    else 
    {
        i = 0;
        if (m[1][1] > m[0][0]) i = 1;
        if (m[2][2] > m[i][i]) i = 2;
        j = nxt[i];
        k = nxt[j];
        s = (f32)::std::sqrtf( (m[i][i] - (m[j][j] + m[k][k])) + 1.0f );
        q[i] = s * 0.5f;
        
        if (s!=0.0f)
            s = 0.5f / s;
        
        pOut->w = (m[k][j] - m[j][k]) * s;
        q[j] = (m[i][j] + m[j][i]) * s;
        q[k] = (m[i][k] + m[k][i]) * s;

        pOut->x = q[0];
        pOut->y = q[1];
        pOut->z = q[2];
    }
    
    return pOut;
}
NN_MATH_INLINE QUAT*
MTX34ToQUATC_FAST(QUAT* pOut, const MTX34* pMtx)
{
    f32 tr;
    s32 i;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pMtx );

    const f32 (*const m)[4] = pMtx->m;

    tr = m[0][0] + m[1][1] + m[2][2];
    if ( tr > 0.0f )
    {
        f32 x, y, z, w, s;
        s = (f32)::std::sqrtf(tr + 1.0f);
        w = s * 0.5f;
        s = 0.5f / s;
        x = (m[2][1] - m[1][2]) * s;
        y = (m[0][2] - m[2][0]) * s;
        z = (m[1][0] - m[0][1]) * s;
        pOut->w = w;
        pOut->x = x;
        pOut->y = y;
        pOut->z = z;
    }
    else 
    {
        f32 x, y, z, w, s;
        i = 0;

        if (m[1][1] > m[0][0])
        {
            if (m[2][2] > m[1][1]) i = 2;
            else    i=1;
        }
        else
        {
            if (m[2][2] > m[0][0]) i = 2;
        }

        if(i==0)
        {
            s = (f32)::std::sqrtf( (m[0][0] - (m[1][1] + m[2][2])) + 1.0f );
            x = s * 0.5f;
            
            if (s!=0.0f)
                s = 0.5f / s;
            
            w = (m[2][1] - m[1][2]) * s;
            y = (m[0][1] + m[1][0]) * s;
            z = (m[0][2] + m[2][0]) * s;

            pOut->x = x;
            pOut->w = w;
            pOut->y = y;
            pOut->z = z;


        }
        else if(i==1)
        {
            s = (f32)::std::sqrtf( (m[1][1] - (m[2][2] + m[0][0])) + 1.0f );
            y = s * 0.5f;
            
            if (s!=0.0f)
                s = 0.5f / s;
            
            w = (m[0][2] - m[2][0]) * s;
            z = (m[1][2] + m[2][1]) * s;
            x = (m[1][0] + m[0][1]) * s;

            pOut->y = y;
            pOut->w = w;
            pOut->z = z;
            pOut->x = x;
        }
        else//i==2
        {
            s = (f32)::std::sqrtf( (m[2][2] - (m[0][0] + m[1][1])) + 1.0f );
            z = s * 0.5f;
            
            if (s!=0.0f)
                s = 0.5f / s;
            
            w = (m[1][0] - m[0][1]) * s;
            x = (m[2][0] + m[0][2]) * s;
            y = (m[2][1] + m[1][2]) * s;

            pOut->z = z;
            pOut->w = w;
            pOut->x = x;
            pOut->y = y;

        }
    }
    
    return pOut;
}
/*
  

  
  

  
 */
NN_MATH_INLINE MTX43*
MTX34TransposeC(MTX43* pOut, const MTX34* p) 
{ 
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );
    
    pOut->f._00 = p->f._00;
    pOut->f._01 = p->f._10;
    pOut->f._02 = p->f._20;

    pOut->f._10 = p->f._01;
    pOut->f._11 = p->f._11;
    pOut->f._12 = p->f._21;
    
    pOut->f._20 = p->f._02;
    pOut->f._21 = p->f._12;
    pOut->f._22 = p->f._22;
    
    pOut->f._30 = p->f._03;
    pOut->f._31 = p->f._13;
    pOut->f._32 = p->f._23;
    
    return pOut;
}

/*
  

  
  

  
 */
NN_MATH_INLINE MTX34*
MTX43TransposeC(MTX34* pOut, const MTX43* p) 
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );
    
    pOut->f._00 = p->f._00;
    pOut->f._01 = p->f._10;
    pOut->f._02 = p->f._20;
    pOut->f._03 = p->f._30;

    pOut->f._10 = p->f._01;
    pOut->f._11 = p->f._11;
    pOut->f._12 = p->f._21;
    pOut->f._13 = p->f._31;
    
    pOut->f._20 = p->f._02;
    pOut->f._21 = p->f._12;
    pOut->f._22 = p->f._22;
    pOut->f._23 = p->f._32;
    
    return pOut;
}


/*  

*/

}  // namespace ARMv6
}  // namespace math
}  // namespace nn


