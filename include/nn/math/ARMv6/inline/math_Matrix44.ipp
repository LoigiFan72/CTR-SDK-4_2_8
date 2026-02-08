/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix44.ipp
  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.
  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.
  $Revision: 13623 $
 *---------------------------------------------------------------------------


*/

#include <cmath>
#include <nn/math/math_Vector3.h>

namespace nn { 
namespace math {
namespace ARMv6 {
/* Please see man pages for details 
    
    
*/

/*
  
  
  
  
  
 

*/
NN_MATH_INLINE VEC4*
VEC3TransformC(VEC4* pOut, const MTX44* pM, const VEC3* pV)
{
    VEC4 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23;
    tmp.w = pM->f._30 * pV->x + pM->f._31 * pV->y + pM->f._32 * pV->z + pM->f._33;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = tmp.w;

    return pOut;
}

/*  

*/

/* ------------------------------------------------------------------------
        MTX44
   ------------------------------------------------------------------------ */

/* Please see man pages for details 
    
    
*/



/*
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44CopyC(MTX44* pOut, const MTX44* p)
{
    if (pOut != p)
    {
        *pOut = *p;
    }
    
    return pOut;
}

/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44AddC(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    pOut->f._00 = p1->f._00 + p2->f._00;
    pOut->f._01 = p1->f._01 + p2->f._01;
    pOut->f._02 = p1->f._02 + p2->f._02;
    pOut->f._03 = p1->f._03 + p2->f._03;

    pOut->f._10 = p1->f._10 + p2->f._10;
    pOut->f._11 = p1->f._11 + p2->f._11;
    pOut->f._12 = p1->f._12 + p2->f._12;
    pOut->f._13 = p1->f._13 + p2->f._13;

    pOut->f._20 = p1->f._20 + p2->f._20;
    pOut->f._21 = p1->f._21 + p2->f._21;
    pOut->f._22 = p1->f._22 + p2->f._22;
    pOut->f._23 = p1->f._23 + p2->f._23;

    pOut->f._30 = p1->f._30 + p2->f._30;
    pOut->f._31 = p1->f._31 + p2->f._31;
    pOut->f._32 = p1->f._32 + p2->f._32;
    pOut->f._33 = p1->f._33 + p2->f._33;

    return pOut;
}



/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44MultC(MTX44* pOut, const MTX44* p, f32 f)
{
    pOut->f._00 = p->f._00 * f;
    pOut->f._01 = p->f._01 * f;
    pOut->f._02 = p->f._02 * f;
    pOut->f._03 = p->f._03 * f;

    pOut->f._10 = p->f._10 * f;
    pOut->f._11 = p->f._11 * f;
    pOut->f._12 = p->f._12 * f;
    pOut->f._13 = p->f._13 * f;

    pOut->f._20 = p->f._20 * f;
    pOut->f._21 = p->f._21 * f;
    pOut->f._22 = p->f._22 * f;
    pOut->f._23 = p->f._23 * f;

    pOut->f._30 = p->f._30 * f;
    pOut->f._31 = p->f._31 * f;
    pOut->f._32 = p->f._32 * f;
    pOut->f._33 = p->f._33 * f;

    return pOut;
}


/*
  
  
  
  
 

*/
NN_MATH_INLINE MTX44* 
MTX44TransposeC(MTX44* pOut, const MTX44 *pSrc)
{
    MTX44 tmp;
    const MTX44 *pMtx;
    
    if (pOut != pSrc)
    {
        pMtx = pSrc;
        pOut->f._00 = pSrc->f._00;
        pOut->f._11 = pSrc->f._11;
        pOut->f._22 = pSrc->f._22;
        pOut->f._33 = pSrc->f._33;
    }
    else
    {
        pMtx = &tmp;
        tmp.f._01 = pSrc->f._01;
        tmp.f._02 = pSrc->f._02;
        tmp.f._03 = pSrc->f._03;
        tmp.f._12 = pSrc->f._12;
        tmp.f._13 = pSrc->f._13;
        tmp.f._23 = pSrc->f._23;
    }
    
    pOut->f._01 = pSrc->f._10;
    pOut->f._02 = pSrc->f._20;
    pOut->f._03 = pSrc->f._30;
    pOut->f._12 = pSrc->f._21;
    pOut->f._13 = pSrc->f._31;
    pOut->f._23 = pSrc->f._32;
    
    pOut->f._10 = pMtx->f._01;
    pOut->f._20 = pMtx->f._02;
    pOut->f._30 = pMtx->f._03;
    pOut->f._21 = pMtx->f._12;
    pOut->f._31 = pMtx->f._13;
    pOut->f._32 = pMtx->f._23;
    
    return pOut;
}


/*
  
  
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44PerspectiveRadC(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f)
{
    NN_NULL_ASSERT(pOut);

    f32 (*const m)[4] = pOut->m;

    // find the cotangent of half the (YZ) field of view
    
    const f32 angle = fovy * 0.5f;

    const f32 cot = 1.0f / ::std::tanf(angle);

    m[0][0] =  cot / aspect;
    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] =  0.0f;
              
    m[1][0] =  0.0f;
    m[1][1] =   cot;
    m[1][2] =  0.0f;
    m[1][3] =  0.0f;
              
    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    const f32 tmp = 1.0f / (f - n);
    m[2][2] = f * tmp;
    m[2][3] = f * n * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44PerspectiveRadC_FAST(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f)
{
    NN_NULL_ASSERT(pOut);

    f32 (*const m)[4] = pOut->m;

    // find the cotangent of half the (YZ) field of view
    
    const f32 angle = fovy * 0.5f;
#if (MTX44PERSPECTIVERAD_CONFIG == D_FAST_C_ALGO)
    f32 sin, cos;
    SinCosFIdx(&sin, &cos, NN_MATH_RAD_TO_FIDX(angle));
    const f32 cot = cos/sin;
#else
    const f32 cot = 1.0f / ::std::tanf(angle);
#endif
    const f32 tmp = 1.0f / (f - n);
    
    register f32 m00, m11, m22, m23;

    m00 =  cot / aspect;
    m11 =  cot;
    m22 = f * tmp;
    m23 = f * n * tmp;

    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] =  0.0f;
    m[1][0] =  0.0f;
    m[1][2] =  0.0f;
    m[1][3] =  0.0f;
    m[2][0] =  0.0f;
    m[2][1] =  0.0f;
    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;

    m[0][0] = m00;
    m[1][1] = m11;
    m[2][2] = m22;
    m[2][3] = m23;

    
    return pOut;
}

/*
  
                
  
  
  
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44FrustumC(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    NN_NULL_ASSERT( pOut );

    // Note: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp     =  1.0f / (r - l);
    m[0][0] =  (2*n) * tmp;
    m[0][1] =  0.0f;
    m[0][2] =  (r + l) * tmp;
    m[0][3] =  0.0f;

    tmp     =  1.0f / (t - b);
    m[1][0] =  0.0f;
    m[1][1] =  (2*n) * tmp;
    m[1][2] =  (t + b) * tmp;
    m[1][3] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    tmp = 1.0f / (f - n);

    m[2][2] = f * tmp;
    m[2][3] = f * n * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44FrustumC_FAST(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    NN_NULL_ASSERT( pOut );

    // Note: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp1 =  1.0f / (r - l);
    f32 tmp3 =  1.0f / (f - n);
    f32 tmp2 =  1.0f / (t - b);
    
    register f32 m00, m02, m11, m12, m22, m23;

    m00 =  (2*n) * tmp1;
    m02 =  (r + l) * tmp1;

    m11 =  (2*n) * tmp2;
    m12 =  (t + b) * tmp2;

    m22 = f * tmp3;
    m23 = f * n * tmp3;

    m[0][1] =  0.0f;
    m[0][3] =  0.0f;

    m[1][0] =  0.0f;
    m[1][3] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;

    m[0][0] =  m00;
    m[0][2] =  m02;

    m[1][1] =  m11;
    m[1][2] =  m12;

    m[2][2] =  m22;
    m[2][3] =  m23;

    return pOut;
}


/*
  
                
  
  
  
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44OrthoC(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    NN_NULL_ASSERT( pOut );

    // Note: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp     =  1.0f / (r - l);
    m[0][0] =  2.0f * tmp;
    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] = -(r + l) * tmp;

    tmp     =  1.0f / (t - b);
    m[1][0] =  0.0f;
    m[1][1] =  2.0f * tmp;
    m[1][2] =  0.0f;
    m[1][3] = -(t + b) * tmp;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    tmp     =  1.0f / (f - n);

    m[2][2] = tmp;
    m[2][3] = n * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] =  0.0f;
    m[3][3] =  1.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44OrthoC_FAST(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    NN_NULL_ASSERT( pOut );

    // Note: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    register f32 tmp1     =  1.0f / (r - l);
    register f32 tmp2     =  1.0f / (t - b);
    register f32 tmp3     =  1.0f / (f - n);
    register f32 m00, m03, m11, m13, m22, m23;

    m00 =  2.0f * tmp1;
    m03 = -(r + l) * tmp1;

    m11 =  2.0f * tmp2;
    m13 = -(t + b) * tmp2;

    m22 = tmp3;
    m23 = n * tmp3;

    m[0][1] =  0.0f;
    m[0][2] =  0.0f;

    m[1][0] =  0.0f;
    m[1][2] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] =  0.0f;
    m[3][3] =  1.0f;

    m[0][0] =  m00;
    m[0][3] =  m03;
    m[1][1] =  m11;
    m[1][3] =  m13;
    m[2][2] =  m22;
    m[2][3] =  m23;
    
    return pOut;
}


    /*---------------------------------------------------------------------------*
          Description:  Rotates projection matrix in the direction of the screen.
      Arguments:    pOut    Pointer to the matrix to rotate
                    pivot   
      Returns:      
     *---------------------------------------------------------------------------

*/
    inline MTX44*
    MTX44PivotC( MTX44* pOut, PivotDirection pivot )
    {
        // TODO: Need to optimize the routine. 
        
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
    inline MTX44*
    MTX44PivotC_FAST( MTX44* pOut, PivotDirection pivot )
    {
        f32 (*const m)[4] = pOut->m;
        #ifdef NN_PLATFORM_CTR
        if ( ( pivot == PIVOT_NONE ) || ( pivot == PIVOT_UPSIDE_TO_LEFT ) )
        #else
        if ( ( pivot == PIVOT_NONE ) || ( pivot == PIVOT_UPSIDE_TO_TOP ) )      
        #endif
        {
            return pOut;
        }

        #ifdef NN_PLATFORM_CTR
        if ( pivot == PIVOT_UPSIDE_TO_RIGHT )
        #else
        if ( pivot == PIVOT_UPSIDE_TO_BOTTOM )
        #endif
        {
            register f32 m00, m01, m02, m03, m10, m11, m12, m13;

            m00 = -m[0][0];
            m01 = -m[0][1];
            m02 = -m[0][2];
            m03 = -m[0][3];

            m10 = -m[1][0];
            m11 = -m[1][1];
            m12 = -m[1][2];
            m13 = -m[1][3];

            m[0][0] = m00;
            m[0][1] = m01;
            m[0][2] = m02;
            m[0][3] = m03;
            
            m[1][0] = m10;
            m[1][1] = m11;
            m[1][2] = m12;
            m[1][3] = m13;
        }
        #ifdef NN_PLATFORM_CTR
        else if ( pivot == PIVOT_UPSIDE_TO_BOTTOM )
        #else
        else if ( pivot == PIVOT_UPSIDE_TO_LEFT )
        #endif
        {
            register f32 m00, m01, m02, m03, m10, m11, m12, m13;

            m10 = m[0][0];
            m11 = m[0][1];
            m12 = m[0][2];
            m13 = m[0][3];

            m00 = -m[1][0];
            m01 = -m[1][1];
            m02 = -m[1][2];
            m03 = -m[1][3];

            m[0][0] = m00;
            m[0][1] = m01;
            m[0][2] = m02;
            m[0][3] = m03;
            
            m[1][0] = m10;
            m[1][1] = m11;
            m[1][2] = m12;
            m[1][3] = m13;
        }
        #ifdef NN_PLATFORM_CTR
        else // if ( pivot == PIVOT_UPSIDE_TO_TOP )
        #else
        else // if ( pivot == PIVOT_UPSIDE_TO_RIGHT )
        #endif
        {
            register f32 m00, m01, m02, m03, m10, m11, m12, m13;

            m10 = -m[0][0];
            m11 = -m[0][1];
            m12 = -m[0][2];
            m13 = -m[0][3];

            m00 = m[1][0];
            m01 = m[1][1];
            m02 = m[1][2];
            m03 = m[1][3];

            m[0][0] = m00;
            m[0][1] = m01;
            m[0][2] = m02;
            m[0][3] = m03;
            
            m[1][0] = m10;
            m[1][1] = m11;
            m[1][2] = m12;
            m[1][3] = m13;
        }
        return pOut;
    }    


/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44MultC(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2) 
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );
    
    MTX44 mTmp;
    
    MTX44* __restrict pDst = ( pOut == p1 || pOut == p2 ) ? &mTmp : pOut;
    
    pDst->f._00 = p1->f._00 * p2->f._00 + p1->f._01 * p2->f._10 + p1->f._02 * p2->f._20 + p1->f._03 * p2->f._30;
    pDst->f._01 = p1->f._00 * p2->f._01 + p1->f._01 * p2->f._11 + p1->f._02 * p2->f._21 + p1->f._03 * p2->f._31;
    pDst->f._02 = p1->f._00 * p2->f._02 + p1->f._01 * p2->f._12 + p1->f._02 * p2->f._22 + p1->f._03 * p2->f._32;
    pDst->f._03 = p1->f._00 * p2->f._03 + p1->f._01 * p2->f._13 + p1->f._02 * p2->f._23 + p1->f._03 * p2->f._33;
    
    pDst->f._10 = p1->f._10 * p2->f._00 + p1->f._11 * p2->f._10 + p1->f._12 * p2->f._20 + p1->f._13 * p2->f._30;
    pDst->f._11 = p1->f._10 * p2->f._01 + p1->f._11 * p2->f._11 + p1->f._12 * p2->f._21 + p1->f._13 * p2->f._31;
    pDst->f._12 = p1->f._10 * p2->f._02 + p1->f._11 * p2->f._12 + p1->f._12 * p2->f._22 + p1->f._13 * p2->f._32;
    pDst->f._13 = p1->f._10 * p2->f._03 + p1->f._11 * p2->f._13 + p1->f._12 * p2->f._23 + p1->f._13 * p2->f._33;
    
    pDst->f._20 = p1->f._20 * p2->f._00 + p1->f._21 * p2->f._10 + p1->f._22 * p2->f._20 + p1->f._23 * p2->f._30;
    pDst->f._21 = p1->f._20 * p2->f._01 + p1->f._21 * p2->f._11 + p1->f._22 * p2->f._21 + p1->f._23 * p2->f._31;
    pDst->f._22 = p1->f._20 * p2->f._02 + p1->f._21 * p2->f._12 + p1->f._22 * p2->f._22 + p1->f._23 * p2->f._32;
    pDst->f._23 = p1->f._20 * p2->f._03 + p1->f._21 * p2->f._13 + p1->f._22 * p2->f._23 + p1->f._23 * p2->f._33;

    pDst->f._30 = p1->f._30 * p2->f._00 + p1->f._31 * p2->f._10 + p1->f._32 * p2->f._20 + p1->f._33 * p2->f._30;
    pDst->f._31 = p1->f._30 * p2->f._01 + p1->f._31 * p2->f._11 + p1->f._32 * p2->f._21 + p1->f._33 * p2->f._31;
    pDst->f._32 = p1->f._30 * p2->f._02 + p1->f._31 * p2->f._12 + p1->f._32 * p2->f._22 + p1->f._33 * p2->f._32;
    pDst->f._33 = p1->f._30 * p2->f._03 + p1->f._31 * p2->f._13 + p1->f._32 * p2->f._23 + p1->f._33 * p2->f._33;
    
    if ( pDst != pOut )
    {
        MTX44Copy( pOut, pDst );
    }
    
    return pOut;
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


/*
  
  
  
  
 

*/
NN_MATH_INLINE u32
MTX44InverseC(MTX44* pOut, const MTX44* p)
{
    MTX44 mTmp;
    f32 (*src)[4];
    f32 (*inv)[4];
    f32   w;
    
    NN_NULL_ASSERT( p );
    NN_NULL_ASSERT( pOut );

    MTX44Copy(&mTmp, p);
    MTX44Identity(pOut);
    
    src = mTmp.m;
    inv = pOut->m;
    
    for (int i = 0; i < 4; ++i)
    {
        f32 max = 0.0f;
        s32 swp = i;
        
        // ---- partial pivoting -----
        for(int k = i ; k < 4 ; k++ )
        {
            f32 ftmp;
            ftmp = ::std::fabs(src[k][i]);
            if ( ftmp > max )
            {
                max = ftmp;
                swp = k;
            }
        }
        
        // check singular matrix
        //(or can't solve inverse matrix with this algorithm)
        if ( max == 0.0f )
        {
            return 0;
        }
        
        // swap row
        if ( swp != i )
        {
            for (int k = 0; k < 4; k++)
            {
                SwapF(src[i][k], src[swp][k]);
                SwapF(inv[i][k], inv[swp][k]);
            }
        }
        
        // ---- pivoting end ----
        
        w = 1.0f / src[i][i];
        for (int j = 0; j < 4; ++j)
        {
            src[i][j] *= w;
            inv[i][j] *= w;
        }
        
        for (int k = 0; k < 4; ++k )
        {
            if ( k == i )
                continue;
            
            w = src[k][i];
            for (int j = 0; j < 4; ++j)
            {
                src[k][j] -= src[i][j] * w;
                inv[k][j] -= inv[i][j] * w;
            }
        }
    }
    
    return 1;
}
NN_MATH_INLINE u32
MTX44InverseC_FAST_ALGO(MTX44* pOut, const MTX44* p)
{
    const f32 (*src)[4];
    f32 (*inv)[4];
    
    NN_NULL_ASSERT( p );
    NN_NULL_ASSERT( pOut );

    src = p->m;
    inv = pOut->m;

    f32 a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44;
    f32 b11, b12, b13, b14, b21, b22, b23, b24, b31, b32, b33, b34, b41, b42, b43, b44;
    f32 det;
    
    a11 = src[0][0];
    a12 = src[0][1];
    a13 = src[0][2];
    a14 = src[0][3];

    a21 = src[1][0];
    a22 = src[1][1];
    a23 = src[1][2];
    a24 = src[1][3];

    a31 = src[2][0];
    a32 = src[2][1];
    a33 = src[2][2];
    a34 = src[2][3];

    a41 = src[3][0];
    a42 = src[3][1];
    a43 = src[3][2];
    a44 = src[3][3];
    
    det = a11*(a22*a33*a44 + a23*a34*a42 + a24*a32*a43)
        + a12*(a21*a34*a43 + a23*a31*a44 + a24*a33*a41)
        + a13*(a21*a32*a44 + a22*a34*a41 + a24*a31*a42)
        + a14*(a21*a33*a42 + a22*a31*a43 + a23*a32*a41)
        - a11*(a22*a34*a43 + a23*a32*a44 + a24*a33*a42)
        - a12*(a21*a33*a44 + a23*a34*a41 + a24*a31*a43)
        - a13*(a21*a34*a42 + a22*a31*a44 + a24*a32*a41)
        - a14*(a21*a32*a43 + a22*a33*a41 + a23*a31*a42);
        
    if(det==0.0f)
        return 0;

    det = 1.0f / det;

    f32 a33xa44_a34xa43, a32xa44_a34xa42, a33xa42_a32xa43,
        a33xa41_a31xa43, a31xa44_a34xa41, a32xa41_a31xa42;
    
    a33xa44_a34xa43 = a33*a44 - a34*a43;
    a32xa44_a34xa42 = a32*a44 - a34*a42;
    a33xa42_a32xa43 = a33*a42 - a32*a43;
    a33xa41_a31xa43 = a33*a41 - a31*a43;
    a31xa44_a34xa41 = a31*a44 - a34*a41;
    a32xa41_a31xa42 = a32*a41 - a31*a42;
    
    f32 a23xa44_a24xa43, a24xa33_a23xa34, a24xa42_a22xa44, a22xa43_a23xa42,
        a22xa34_a24xa32, a23xa32_a22xa33, a21xa44_a24xa41, a23xa41_a21xa43,
        a24xa31_a21xa34, a21xa33_a23xa31, a21xa42_a22xa41, a22xa31_a21xa32;
    
    a23xa44_a24xa43 = a23*a44 - a24*a43;
    a24xa33_a23xa34 = a24*a33 - a23*a34;
    a24xa42_a22xa44 = a24*a42 - a22*a44;
    a22xa43_a23xa42 = a22*a43 - a23*a42;
    a22xa34_a24xa32 = a22*a34 - a24*a32;
    a23xa32_a22xa33 = a23*a32 - a22*a33;
    a21xa44_a24xa41 = a21*a44 - a24*a41;
    a23xa41_a21xa43 = a23*a41 - a21*a43;
    a24xa31_a21xa34 = a24*a31 - a21*a34;
    a21xa33_a23xa31 = a21*a33 - a23*a31;
    a21xa42_a22xa41 = a21*a42 - a22*a41;
    a22xa31_a21xa32 = a22*a31 - a21*a32;
    
    b11 =( a22*a33xa44_a34xa43) - (a23*a32xa44_a34xa42) - (a24*a33xa42_a32xa43);
    b12 =( a13*a32xa44_a34xa42) + (a14*a33xa42_a32xa43) - (a12*a33xa44_a34xa43);
    b13 =( a12*a23xa44_a24xa43) + (a13*a24xa42_a22xa44) + (a14*a22xa43_a23xa42);
    b14 =( a12*a24xa33_a23xa34) + (a13*a22xa34_a24xa32) + (a14*a23xa32_a22xa33);
    b21 =( a23*a31xa44_a34xa41) + (a24*a33xa41_a31xa43) - (a21*a33xa44_a34xa43);
    b22 =( a11*a33xa44_a34xa43) - (a13*a31xa44_a34xa41) - (a14*a33xa41_a31xa43);
    b23 =( a13*a21xa44_a24xa41) + (a14*a23xa41_a21xa43) - (a11*a23xa44_a24xa43);
    b24 =( a13*a24xa31_a21xa34) + (a14*a21xa33_a23xa31) - (a11*a24xa33_a23xa34);
    b31 =( a21*a32xa44_a34xa42) - (a22*a31xa44_a34xa41) - (a24*a32xa41_a31xa42);
    b32 =( a12*a31xa44_a34xa41) + (a14*a32xa41_a31xa42) - (a11*a32xa44_a34xa42);
    b33 =( a14*a21xa42_a22xa41) - (a11*a24xa42_a22xa44) - (a12*a21xa44_a24xa41);
    b34 =( a14*a22xa31_a21xa32) - (a11*a22xa34_a24xa32) - (a12*a24xa31_a21xa34);
    b41 =( a21*a33xa42_a32xa43) - (a22*a33xa41_a31xa43) + (a23*a32xa41_a31xa42);
    b42 =( a12*a33xa41_a31xa43) - (a13*a32xa41_a31xa42) - (a11*a33xa42_a32xa43);
    b43 =(-a13*a21xa42_a22xa41) - (a11*a22xa43_a23xa42) - (a12*a23xa41_a21xa43);
    b44 =(-a13*a22xa31_a21xa32) - (a11*a23xa32_a22xa33) - (a12*a21xa33_a23xa31);

    b11 = b11 * det;
    b12 = b12 * det;
    b13 = b13 * det;
    b14 = b14 * det;
    b21 = b21 * det;
    b22 = b22 * det;
    b23 = b23 * det;
    b24 = b24 * det;
    b31 = b31 * det;
    b32 = b32 * det;
    b33 = b33 * det;
    b34 = b34 * det;
    b41 = b41 * det;
    b42 = b42 * det;
    b43 = b43 * det;
    b44 = b44 * det;

    inv[0][0] = b11;
    inv[0][1] = b12;
    inv[0][2] = b13;
    inv[0][3] = b14;

    inv[1][0] = b21;
    inv[1][1] = b22;
    inv[1][2] = b23;
    inv[1][3] = b24;

    inv[2][0] = b31;
    inv[2][1] = b32;
    inv[2][2] = b33;
    inv[2][3] = b34;

    inv[3][0] = b41;
    inv[3][1] = b42;
    inv[3][2] = b43;
    inv[3][3] = b44;

    return 1;
}


/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44RotAxisRad_C( MTX44* pOut, const VEC3 *pAxis, f32 fRad )
{
    VEC3 vN;
    f32 s, c;             // sinTheta, cosTheta
    f32 t;                // ( 1 - cosTheta )
    f32 x, y, z;          // x, y, z components of normalized axis
    f32 xSq, ySq, zSq;    // x, y, z squared


    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pAxis );

    f32 (*const m)[4] = pOut->m;

    s = ::std::sinf(fRad);
    c = ::std::cosf(fRad);
    t = 1.0f - c;

    VEC3Normalize( &vN, pAxis );

    x = vN.x;
    y = vN.y;
    z = vN.z;

    xSq = x * x;
    ySq = y * y;
    zSq = z * z;

    m[0][0] = ( t * xSq )   + ( c );
    m[0][1] = ( t * x * y ) - ( s * z );
    m[0][2] = ( t * x * z ) + ( s * y );
    m[0][3] = 0.0f;

    m[1][0] = ( t * x * y ) + ( s * z );
    m[1][1] = ( t * ySq )   + ( c );
    m[1][2] = ( t * y * z ) - ( s * x );
    m[1][3] = 0.0f;

    m[2][0] = ( t * x * z ) - ( s * y );
    m[2][1] = ( t * y * z ) + ( s * x );
    m[2][2] = ( t * zSq )   + ( c );
    m[2][3] = 0.0f;
    
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44RotAxisRad_C_FAST( MTX44* pOut, const VEC3 *pAxis, f32 fRad )
{
    VEC3 vN;
    f32 s, c;             // sinTheta, cosTheta
    f32 t;                // ( 1 - cosTheta )
    f32 x, y, z;          // x, y, z components of normalized axis
    f32 xSq, ySq, zSq;    // x, y, z squared
    f32 m00, m01, m02, m10, m11, m12, m20, m21, m22;


    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pAxis );

    f32 (*const m)[4] = pOut->m;

#if (MTX44ROTAXISRAD__CONFIG == D_FAST_C_ALGO)
    SinCosFIdx(&s, &c, NN_MATH_RAD_TO_FIDX(fRad));
#else
    s = ::std::sinf(fRad);
    c = ::std::cosf(fRad);
#endif
    t = 1.0f - c;

    VEC3Normalize( &vN, pAxis );

    x = vN.x;
    y = vN.y;
    z = vN.z;

    xSq = x * x;
    ySq = y * y;
    zSq = z * z;

    m00 = ( t * xSq )   + ( c );
    m01 = ( t * x * y ) - ( s * z );
    m02 = ( t * x * z ) + ( s * y );

    m10 = ( t * x * y ) + ( s * z );
    m11 = ( t * ySq )   + ( c );
    m12 = ( t * y * z ) - ( s * x );

    m20 = ( t * x * z ) - ( s * y );
    m21 = ( t * y * z ) + ( s * x );
    m22 = ( t * zSq )   + ( c );


    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = 0.0f;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = 0.0f;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = 0.0f;
    
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    
    return pOut;
}


/*
  
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44RotXYZFIdxC(MTX44* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ)
{
    NN_FLOAT_ASSERT(fIdxX);
    NN_FLOAT_ASSERT(fIdxY);
    NN_FLOAT_ASSERT(fIdxZ);

    f32 sinx, cosx;
    f32 siny, cosy;
    f32 sinz, cosz;
    f32 f1, f2;

    SinCosFIdx(&sinx, &cosx, fIdxX);
    SinCosFIdx(&siny, &cosy, fIdxY);
    SinCosFIdx(&sinz, &cosz, fIdxZ);

    pOut->f._20 = -siny;
    pOut->f._00 = cosz * cosy;
    pOut->f._10 = sinz * cosy;
    pOut->f._21 = cosy * sinx;
    pOut->f._22 = cosy * cosx;

    f1 = cosx * sinz;
    f2 = sinx * cosz;

    pOut->f._01 = f2 * siny - f1;
    pOut->f._12 = f1 * siny - f2;

    f1 = sinx * sinz;
    f2 = cosx * cosz;
    pOut->f._02 = f2 * siny + f1;
    pOut->f._11 = f1 * siny + f2;

    pOut->f._03 = 0.f;
    pOut->f._13 = 0.f;
    pOut->f._23 = 0.f;
    
    pOut->f._30 = 0.0f;
    pOut->f._31 = 0.0f;
    pOut->f._32 = 0.0f;
    pOut->f._33 = 1.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44RotXYZFIdxC_FAST(MTX44* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ)
{
    NN_FLOAT_ASSERT(fIdxX);
    NN_FLOAT_ASSERT(fIdxY);
    NN_FLOAT_ASSERT(fIdxZ);

    f32 sinx, cosx;
    f32 siny, cosy;
    f32 sinz, cosz;
    f32 f1, f2, f3, f4;
    f32 f00, f10, f21, f22;
    f32 f01, f11, f02, f12;



    {

        u16 idxx;
        f32 abs_fidxx;
        f32 rx;
     
        u16 idxy;
        f32 abs_fidxy;
        f32 ry;

        u16 idxz;
        f32 abs_fidxz;
        f32 rz;

        int negx, negy, negz;

        negx = (fIdxX < 0.0f) ? 1 : 0;
        abs_fidxx = FAbs(fIdxX);
        negy = (fIdxY < 0.0f) ? 1 : 0;
        abs_fidxy = FAbs(fIdxY);
        negz = (fIdxZ < 0.0f) ? 1 : 0;
        abs_fidxz = FAbs(fIdxZ);


        while ( abs_fidxx >= 65536.0f )
        {
            abs_fidxx -= 65536.0f;
        }
        while ( abs_fidxy >= 65536.0f )
        {
            abs_fidxy -= 65536.0f;
        }
        while ( abs_fidxz >= 65536.0f )
        {
            abs_fidxz -= 65536.0f;
        }

        idxx = F32ToU16(abs_fidxx);
        idxy = F32ToU16(abs_fidxy);
        idxz = F32ToU16(abs_fidxz);
        {
            f32 idxxf, idxyf, idxzf;
            
            idxxf = U16ToF32(idxx);
            idxyf = U16ToF32(idxy);
            idxzf = U16ToF32(idxz);
            
            rx = abs_fidxx - idxxf;
            ry = abs_fidxy - idxyf;
            rz = abs_fidxz - idxzf;
            

        }

        idxx &= 0xff;
        idxy &= 0xff;
        idxz &= 0xff;

        {
            f32 sinx_val, sinx_delta, cosx_val, cosx_delta;
            f32 siny_val, siny_delta, cosy_val, cosy_delta;
            f32 sinz_val, sinz_delta, cosz_val, cosz_delta;
            
            sinx_val = internal::gSinCosTbl[idxx].sin_val;
            cosx_val = internal::gSinCosTbl[idxx].cos_val;
            sinx_delta = internal::gSinCosTbl[idxx].sin_delta;
            cosx_delta = internal::gSinCosTbl[idxx].cos_delta;

            sinx = sinx_val + rx * sinx_delta;
            cosx = cosx_val + rx * cosx_delta;

            siny_val = internal::gSinCosTbl[idxy].sin_val;
            cosy_val = internal::gSinCosTbl[idxy].cos_val;
            siny_delta = internal::gSinCosTbl[idxy].sin_delta;
            cosy_delta = internal::gSinCosTbl[idxy].cos_delta;

            siny = siny_val + ry * siny_delta;
            cosy = cosy_val + ry * cosy_delta;

            sinz_val = internal::gSinCosTbl[idxz].sin_val;
            cosz_val = internal::gSinCosTbl[idxz].cos_val;
            sinz_delta = internal::gSinCosTbl[idxz].sin_delta;
            cosz_delta = internal::gSinCosTbl[idxz].cos_delta;

            sinz = sinz_val + rz * sinz_delta;
            cosz = cosz_val + rz * cosz_delta;

        }

        sinx = (negx) ? -sinx : sinx;
        siny = (negy) ? -siny : siny;
        sinz = (negz) ? -sinz : sinz;

    }

    f00 = cosz * cosy;
    f10 = sinz * cosy;
    f21 = sinx * cosy;
    f22 = cosx * cosy;

    f1 = cosx * sinz;
    f2 = sinx * cosz;

    f01 = f2 * siny - f1;
    f12 = f1 * siny - f2;

    f3 = sinx * sinz;
    f4 = cosx * cosz;

    f02 = f4 * siny + f3;
    f11 = f3 * siny + f4;

    pOut->f._00 = f00;
    pOut->f._10 = f10;
    pOut->f._21 = f21;
    pOut->f._22 = f22;

    pOut->f._01 = f01;
    pOut->f._12 = f12;
    pOut->f._02 = f02;
    pOut->f._11 = f11;
    pOut->f._20 = -siny;

    *(unsigned int*)&pOut->f._03 = 0x00000000;
    *(unsigned int*)&pOut->f._13 = 0x00000000;
    *(unsigned int*)&pOut->f._23 = 0x00000000;

    *(unsigned int*)&pOut->f._30 = 0x00000000;
    *(unsigned int*)&pOut->f._31 = 0x00000000;
    *(unsigned int*)&pOut->f._32 = 0x00000000;
    *(unsigned int*)&pOut->f._33 = 0x3F800000;
    
    return pOut;
}

/*
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44ScaleC(MTX44* pOut, const VEC3* pS)
{
    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( pS  );

    f32 (*const m)[4] = pOut->m;

    m[0][0] = pS->x;    m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = 0.0f;
    m[1][0] = 0.0f;     m[1][1] = pS->y; m[1][2] = 0.0f;  m[1][3] = 0.0f;
    m[2][0] = 0.0f;     m[2][1] = 0.0f;  m[2][2] = pS->z; m[2][3] = 0.0f;
    m[3][0] = 0.0f;     m[3][1] = 0.0f;  m[3][2] = 0.0f; m[3][3] = 1.0f;

    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44ScaleC_FAST(MTX44* pOut, const VEC3* pS)
{
    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( pS  );

    unsigned int *m = reinterpret_cast<unsigned int *>(pOut->m);

    f32 f1 = 1.0f;
    f32 f0 = 0.0f;
    const unsigned int f32_1 = *(reinterpret_cast<unsigned int*>(&f1));
    const unsigned int f32_0 = *(reinterpret_cast<unsigned int*>(&f0));
    const unsigned int *p = reinterpret_cast<const unsigned int*>(pS);

    m[ 0] =  p[0];  m[ 1] = f32_0;  m[ 2] = f32_0;  m[ 3] = f32_0;
    m[ 4] = f32_0;  m[ 5] =  p[1];  m[ 6] = f32_0;  m[ 7] = f32_0;
    m[ 8] = f32_0;  m[ 9] = f32_0;  m[10] =  p[2];  m[11] = f32_0;
    m[12] = f32_0;  m[13] = f32_0;  m[14] = f32_0;  m[15] = f32_1;

    return pOut;
}


/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44MultScaleC(MTX44* pOut, const MTX44* pM, const VEC3* pS)
{
    // Version where the scale matrix is applied from the right.
    pOut->f._00 = pM->f._00 * pS->x;
    pOut->f._10 = pM->f._10 * pS->x;
    pOut->f._20 = pM->f._20 * pS->x;

    pOut->f._01 = pM->f._01 * pS->y;
    pOut->f._11 = pM->f._11 * pS->y;
    pOut->f._21 = pM->f._21 * pS->y;

    pOut->f._02 = pM->f._02 * pS->z;
    pOut->f._12 = pM->f._12 * pS->z;
    pOut->f._22 = pM->f._22 * pS->z;

    if (pOut != pM)
    {
        pOut->f._03 = pM->f._03;
        pOut->f._13 = pM->f._13;
        pOut->f._23 = pM->f._23;
    }

    return pOut;
}


/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44MultScaleC(MTX44* pOut, const VEC3* pS, const MTX44* pM)
{
    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( pS  );
    NN_NULL_ASSERT( pM  );

    const f32 (*const src)[4] = pM->m;
    f32 (*const dst)[4] = pOut->m;

    dst[0][0] = src[0][0] * pS->x;     dst[0][1] = src[0][1] * pS->x;
    dst[0][2] = src[0][2] * pS->x;     dst[0][3] = src[0][3] * pS->x;

    dst[1][0] = src[1][0] * pS->y;     dst[1][1] = src[1][1] * pS->y;
    dst[1][2] = src[1][2] * pS->y;     dst[1][3] = src[1][3] * pS->y;

    dst[2][0] = src[2][0] * pS->z;     dst[2][1] = src[2][1] * pS->z;
    dst[2][2] = src[2][2] * pS->z;     dst[2][3] = src[2][3] * pS->z;
    
    return pOut;
}


/*
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44TranslateC(MTX44* pOut, const VEC3* pT)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pT );

    f32 (*const m)[4] = pOut->m;

    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = pT->x;
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f;  m[1][3] = pT->y;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f;  m[2][3] = pT->z;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;

    return pOut;
}
NN_MATH_INLINE MTX44*
MTX44TranslateC_FAST(MTX44* pOut, const VEC3* pT)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pT );

    unsigned int *m = reinterpret_cast<unsigned int *>(pOut->m);

    f32 f1 = 1.0f;
    f32 f0 = 0.0f;
    const unsigned int f32_1 = *(reinterpret_cast<unsigned int*>(&f1));
    const unsigned int f32_0 = *(reinterpret_cast<unsigned int*>(&f0));
    const unsigned int *p = reinterpret_cast<const unsigned int*>(pT);

    m[ 0] = f32_1;  m[ 1] = f32_0;  m[ 2] = f32_0;  m[ 3] = p[0];
    m[ 4] = f32_0;  m[ 5] = f32_1;  m[ 6] = f32_0;  m[ 7] = p[1];
    m[ 8] = f32_0;  m[ 9] = f32_0;  m[10] = f32_1;  m[11] = p[2];
    m[12] = f32_0;  m[13] = f32_0;  m[14] = f32_0;  m[15] = f32_1;

    return pOut;
}


/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44MultTranslateC(MTX44* pOut, const VEC3* pT, const MTX44* pM)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pT);
    NN_NULL_ASSERT(pM);

    const f32 (*const src)[4] = pM->m;
    f32 (*const dst)[4] = pOut->m;
    
    if ( src != dst )
    {
        dst[0][0] = src[0][0];    dst[0][1] = src[0][1];    dst[0][2] = src[0][2];
        dst[1][0] = src[1][0];    dst[1][1] = src[1][1];    dst[1][2] = src[1][2];
        dst[2][0] = src[2][0];    dst[2][1] = src[2][1];    dst[2][2] = src[2][2];
    }
    
    dst[0][3] = src[0][3] + pT->x;
    dst[1][3] = src[1][3] + pT->y;
    dst[2][3] = src[2][3] + pT->z;
    
    return pOut;
}

/*
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX44*
MTX44MultTranslateC(MTX44* pOut, const MTX44* pM, const VEC3* pT)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pT);
    NN_NULL_ASSERT(pM);

    // pOut = pM * pT
    if (pOut != pM)
    {
        (void)MTX44Copy(pOut, pM);
    }

    VEC4 tmp;
    VEC3Transform(&tmp, pM, pT);

    pOut->f._03 = tmp.x;
    pOut->f._13 = tmp.y;
    pOut->f._23 = tmp.z;

    return pOut;
}

/*  

*/

}  // namespace ARMv6
}  // namespace math
}  // namespace nn
