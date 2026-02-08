/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix34.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 13664 $
 *---------------------------------------------------------------------------*/
#include <cmath>
#include <nn/math/math_Vector3.h>

namespace nn { 
namespace math {
namespace ARMv6 {
/* Please see man pages for details 
    
    
*/

/*
  

  
                      
  
  

  
 */
NN_MATH_INLINE VEC3*
VEC3TransformC(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV)
{
    NN_NULL_ASSERT( pM );
    NN_NULL_ASSERT( pV  );
    NN_NULL_ASSERT( pOut  );

    VEC3 vTmp;
    VEC3* pDst = (pOut == pV) ? &vTmp : pOut;
    
    pDst->x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03;
    pDst->y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13;
    pDst->z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23;
    
    if (pDst == &vTmp)
    {
        pOut->x = pDst->x;
        pOut->y = pDst->y;
        pOut->z = pDst->z;
    }

    return pOut;
}

/* ------------------------------------------------------------------------
        MTX34
   ------------------------------------------------------------------------ */

/* Please see man pages for details 
    
    
*/

/*
  

  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34CopyC(MTX34* pOut, const MTX34* p)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );

    if ( p != pOut )
    {
        *pOut = *p;
    }
    
    return pOut;
}



/*
  

  
                
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34MultC(MTX34* pOut, const MTX34* __restrict p1, const MTX34* __restrict p2)
{
    MTX34 mTmp;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    MTX34* __restrict pDst = (pOut == p1 || pOut == p2) ? &mTmp : pOut;

    pDst->f._00 = p1->f._00 * p2->f._00 + p1->f._01 * p2->f._10 + p1->f._02 * p2->f._20;
    pDst->f._01 = p1->f._00 * p2->f._01 + p1->f._01 * p2->f._11 + p1->f._02 * p2->f._21;
    pDst->f._02 = p1->f._00 * p2->f._02 + p1->f._01 * p2->f._12 + p1->f._02 * p2->f._22;
    pDst->f._03 = p1->f._00 * p2->f._03 + p1->f._01 * p2->f._13 + p1->f._02 * p2->f._23 + p1->f._03;

    pDst->f._10 = p1->f._10 * p2->f._00 + p1->f._11 * p2->f._10 + p1->f._12 * p2->f._20;
    pDst->f._11 = p1->f._10 * p2->f._01 + p1->f._11 * p2->f._11 + p1->f._12 * p2->f._21;
    pDst->f._12 = p1->f._10 * p2->f._02 + p1->f._11 * p2->f._12 + p1->f._12 * p2->f._22;
    pDst->f._13 = p1->f._10 * p2->f._03 + p1->f._11 * p2->f._13 + p1->f._12 * p2->f._23 + p1->f._13;

    pDst->f._20 = p1->f._20 * p2->f._00 + p1->f._21 * p2->f._10 + p1->f._22 * p2->f._20;
    pDst->f._21 = p1->f._20 * p2->f._01 + p1->f._21 * p2->f._11 + p1->f._22 * p2->f._21;
    pDst->f._22 = p1->f._20 * p2->f._02 + p1->f._21 * p2->f._12 + p1->f._22 * p2->f._22;
    pDst->f._23 = p1->f._20 * p2->f._03 + p1->f._21 * p2->f._13 + p1->f._22 * p2->f._23 + p1->f._23;

    // overwrite a or b if needed
    if ( pDst == &mTmp )
    {
        MTX34Copy( pOut, &mTmp );
    }
    
    return pOut;
}

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34AddC(MTX34* pOut, const MTX34* p1, const MTX34* p2)
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

    return pOut;
}

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34MultC(MTX34* pOut, const MTX34* p, f32 f)
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

    return pOut;
}


/*
  

  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34ScaleC(MTX34* pOut, const VEC3* pS)
{
    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( pS  );

    f32 (*const m)[4] = pOut->m;

    m[0][0] = pS->x;    m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = 0.0f;
    m[1][0] = 0.0f;     m[1][1] = pS->y; m[1][2] = 0.0f;  m[1][3] = 0.0f;
    m[2][0] = 0.0f;     m[2][1] = 0.0f;  m[2][2] = pS->z; m[2][3] = 0.0f;

    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34ScaleC_FAST(MTX34* pOut, const VEC3* pS)
{
    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( pS  );

    f32 f0 = 0.0f;
    const unsigned int f32_0 = *(reinterpret_cast<unsigned int*>(&f0));
    unsigned int *m = reinterpret_cast<unsigned int *>(pOut->m);
    const unsigned int *p = reinterpret_cast<const unsigned int*>(pS);

    m[ 0] =  p[0];  m[ 1] = f32_0;  m[ 2] = f32_0;  m[ 3] = f32_0;
    m[ 4] = f32_0;  m[ 5] =  p[1];  m[ 6] = f32_0;  m[ 7] = f32_0;
    m[ 8] = f32_0;  m[ 9] = f32_0;  m[10] =  p[2];  m[11] = f32_0;

    return pOut;
}

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34MultScaleC(MTX34* pOut, const MTX34* pM, const VEC3* pS)
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
NN_MATH_INLINE MTX34*
MTX34MultScaleC(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM)
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
NN_MATH_INLINE MTX34*
MTX34TranslateC(MTX34* pOut, const VEC3* pT)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pT );

    f32 (*const m)[4] = pOut->m;

    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = pT->x;
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f;  m[1][3] = pT->y;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f;  m[2][3] = pT->z;

    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34TranslateC_FAST(MTX34* pOut, const VEC3* pT)
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

    return pOut;
}

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34MultTranslateC(MTX34* pOut, const VEC3* pT, const MTX34* pM)
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
NN_MATH_INLINE MTX34*
MTX34MultTranslateC(MTX34* pOut, const MTX34* pM, const VEC3* pT)
{
    // pOut = pM * pT
    if (pOut != pM)
    {
        (void)MTX34Copy(pOut, pM);
    }

    VEC3 tmp;
    VEC3Transform(&tmp, pM, pT);

    pOut->f._03 = tmp.x;
    pOut->f._13 = tmp.y;
    pOut->f._23 = tmp.z;

    return pOut;
}



/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34MAddC(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2)
{
    pOut->f._00 = t * p1->f._00 + p2->f._00;
    pOut->f._01 = t * p1->f._01 + p2->f._01;
    pOut->f._02 = t * p1->f._02 + p2->f._02;
    pOut->f._03 = t * p1->f._03 + p2->f._03;

    pOut->f._10 = t * p1->f._10 + p2->f._10;
    pOut->f._11 = t * p1->f._11 + p2->f._11;
    pOut->f._12 = t * p1->f._12 + p2->f._12;
    pOut->f._13 = t * p1->f._13 + p2->f._13;

    pOut->f._20 = t * p1->f._20 + p2->f._20;
    pOut->f._21 = t * p1->f._21 + p2->f._21;
    pOut->f._22 = t * p1->f._22 + p2->f._22;
    pOut->f._23 = t * p1->f._23 + p2->f._23;

    return pOut;
}


/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34RotAxisRad_C( MTX34* pOut, const VEC3 *pAxis, f32 fRad, bool isChangeTrans )
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
    if ( isChangeTrans )    m[0][3] =    0.0f;

    m[1][0] = ( t * x * y ) + ( s * z );
    m[1][1] = ( t * ySq )   + ( c );
    m[1][2] = ( t * y * z ) - ( s * x );
    if ( isChangeTrans )    m[1][3] =    0.0f;

    m[2][0] = ( t * x * z ) - ( s * y );
    m[2][1] = ( t * y * z ) + ( s * x );
    m[2][2] = ( t * zSq )   + ( c );
    if ( isChangeTrans )    m[2][3] =    0.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34RotAxisRad_C_FAST( MTX34* pOut, const VEC3 *pAxis, f32 fRad, bool isChangeTrans )
{
    VEC3 vN;
    f32 s, c;             // sinTheta, cosTheta
    f32 t;                // ( 1 - cosTheta )
    f32 x, y, z;          // x, y, z components of normalized axis
    f32 xSq, ySq, zSq;    // x, y, z squared


    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( pAxis );

    f32 (*const m)[4] = pOut->m;

#if (MTX34ROTAXISRAD__CONFIG == D_FAST_C_ALGO)
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

    register f32 m00, m01, m02, m10, m11, m12, m20, m21, m22;
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
    if ( isChangeTrans )    m[0][3] = 0.0f;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    if ( isChangeTrans )    m[1][3] = 0.0f;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    if ( isChangeTrans )    m[2][3] = 0.0f;


    return pOut;
}

/*
  

  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34RotXYZFIdxC(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, bool isChangeTrans)
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

    if ( isChangeTrans )
    {
        pOut->f._03 = 0.f;
        pOut->f._13 = 0.f;
        pOut->f._23 = 0.f;
    }

    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34RotXYZFIdxC_FAST(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, bool isChangeTrans)
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

    if ( isChangeTrans )
    {
        *(unsigned int*)&pOut->f._03 = 0x00000000;
        *(unsigned int*)&pOut->f._13 = 0x00000000;
        *(unsigned int*)&pOut->f._23 = 0x00000000;
    }

    return pOut;
}

/*
  

  
  

  
 */
NN_MATH_INLINE u32
MTX34InverseC(MTX34* pOut, const MTX34* p)
{
    MTX34 mTmp;
    f32 (*m)[4];
    f32 det;

    NN_NULL_ASSERT( p );
    NN_NULL_ASSERT( pOut );

    f32 (*const inv)[4] = pOut->m;
    const f32 (*const src)[4] = p->m;
    
    if ( p == pOut )
    {
        m = mTmp.m;
    }
    else
    {
        m = inv;
    }

    // compute the determinant of the upper 3x3 submatrix
    det =   src[0][0]*src[1][1]*src[2][2] + src[0][1]*src[1][2]*src[2][0] + src[0][2]*src[1][0]*src[2][1]
          - src[2][0]*src[1][1]*src[0][2] - src[1][0]*src[0][1]*src[2][2] - src[0][0]*src[2][1]*src[1][2];

    // check if matrix is singular
    if ( det == 0.0f )
    {
        return 0;
    }

    // compute the inverse of the upper submatrix:

    // find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    det = 1.0f / det;

    m[0][0] =  (src[1][1]*src[2][2] - src[2][1]*src[1][2]) * det;
    m[0][1] = -(src[0][1]*src[2][2] - src[2][1]*src[0][2]) * det;
    m[0][2] =  (src[0][1]*src[1][2] - src[1][1]*src[0][2]) * det;

    m[1][0] = -(src[1][0]*src[2][2] - src[2][0]*src[1][2]) * det;
    m[1][1] =  (src[0][0]*src[2][2] - src[2][0]*src[0][2]) * det;
    m[1][2] = -(src[0][0]*src[1][2] - src[1][0]*src[0][2]) * det;

    m[2][0] =  (src[1][0]*src[2][1] - src[2][0]*src[1][1]) * det;
    m[2][1] = -(src[0][0]*src[2][1] - src[2][0]*src[0][1]) * det;
    m[2][2] =  (src[0][0]*src[1][1] - src[1][0]*src[0][1]) * det;


    // compute (invA)*(-C)
    m[0][3] = -m[0][0]*src[0][3] - m[0][1]*src[1][3] - m[0][2]*src[2][3];
    m[1][3] = -m[1][0]*src[0][3] - m[1][1]*src[1][3] - m[1][2]*src[2][3];
    m[2][3] = -m[2][0]*src[0][3] - m[2][1]*src[1][3] - m[2][2]*src[2][3];

    // copy back if needed
    if ( m == mTmp.m )
    {
        MTX34Copy( pOut, &mTmp );
    }

    return 1;
}


/*
  

  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34TransposeC(MTX34* pOut, const MTX34* p)
{
    MTX34 mTmp;

    NN_NULL_ASSERT( p );
    NN_NULL_ASSERT( pOut );

    const f32 (*const src)[4] = p->m;
    f32 (*m)[4];

    if (p == pOut)
    {
        m = mTmp.m;
    }
    else
    {
        m = pOut->m;
    }

    m[0][0] = src[0][0];   m[0][1] = src[1][0];      m[0][2] = src[2][0];     m[0][3] = 0.0f;
    m[1][0] = src[0][1];   m[1][1] = src[1][1];      m[1][2] = src[2][1];     m[1][3] = 0.0f;
    m[2][0] = src[0][2];   m[2][1] = src[1][2];      m[2][2] = src[2][2];     m[2][3] = 0.0f;

    // copy back if needed
    if ( m == mTmp.m )
    {
        MTX34Copy( pOut, &mTmp );
    }
    
    return pOut;
}


/*
  

  
  

  
 */
NN_MATH_INLINE u32
MTX34InvTransposeC(MTX34* pOut, const MTX34* __restrict p)
{
    MTX34 mTmp;
    f32 (*m)[4];
    f32 det;

    NN_NULL_ASSERT(p);
    NN_NULL_ASSERT(pOut);

    f32 (*const invX)[4] = pOut->m;
    const f32 (*const src)[4] = p->m;
    
    if ( p == pOut )
    {
        m = mTmp.m;
    }
    else
    {
        m = invX;
    }

    // compute the determinant of the upper 3x3 submatrix
    det =   src[0][0]*src[1][1]*src[2][2] + src[0][1]*src[1][2]*src[2][0] + src[0][2]*src[1][0]*src[2][1]
          - src[2][0]*src[1][1]*src[0][2] - src[1][0]*src[0][1]*src[2][2] - src[0][0]*src[2][1]*src[1][2];

    // check if matrix is singular
    if ( det == 0.0f )
    {
        return 0;
    }

    // compute the inverse-transpose of the upper submatrix:

    // find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    det = 1.0f / det;

    m[0][0] =  (src[1][1]*src[2][2] - src[2][1]*src[1][2]) * det;
    m[0][1] = -(src[1][0]*src[2][2] - src[2][0]*src[1][2]) * det;
    m[0][2] =  (src[1][0]*src[2][1] - src[2][0]*src[1][1]) * det;

    m[1][0] = -(src[0][1]*src[2][2] - src[2][1]*src[0][2]) * det;
    m[1][1] =  (src[0][0]*src[2][2] - src[2][0]*src[0][2]) * det;
    m[1][2] = -(src[0][0]*src[2][1] - src[2][0]*src[0][1]) * det;

    m[2][0] =  (src[0][1]*src[1][2] - src[1][1]*src[0][2]) * det;
    m[2][1] = -(src[0][0]*src[1][2] - src[1][0]*src[0][2]) * det;
    m[2][2] =  (src[0][0]*src[1][1] - src[1][0]*src[0][1]) * det;


    // the fourth columns should be all zero
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = 0.0F;

    // copy back if needed
    if ( m == mTmp.m )
    {
        MTX34Copy( pOut, &mTmp );
    }

    return 1;
}


/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34LookAtC(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pCamPos);
    NN_NULL_ASSERT(pCamUp);
    NN_NULL_ASSERT(pTarget);

    f32 (*const m)[4] = pOut->m;

    // compute unit target vector
    // use negative value to look down (-Z) axis
    VEC3 vLook;
    VEC3Sub(&vLook, pCamPos, pTarget);
    VEC3Normalize(&vLook, &vLook);

    // vRight = pCamUp x vLook
    VEC3 vRight;
    VEC3Cross(&vRight, pCamUp, &vLook);
    VEC3Normalize(&vRight, &vRight);

    // vUp = vLook x vRight
    VEC3 vUp;
    VEC3Cross(&vUp, &vLook, &vRight);
    // Don't need to normalize vUp since it should already be unit length
    // VECNormalize( &vUp, &vUp );

    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -( pCamPos->x * vRight.x + pCamPos->y * vRight.y + pCamPos->z * vRight.z );

    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -( pCamPos->x * vUp.x + pCamPos->y * vUp.y + pCamPos->z * vUp.z );

    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -( pCamPos->x * vLook.x + pCamPos->y * vLook.y + pCamPos->z * vLook.z );
    
    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34LookAtC_FAST(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pCamPos);
    NN_NULL_ASSERT(pCamUp);
    NN_NULL_ASSERT(pTarget);

    f32 (*const m)[4] = pOut->m;

    // compute unit target vector
    // use negative value to look down (-Z) axis
    f32 vLookx, vLooky, vLookz;
    {
        vLookx = pCamPos->x - pTarget->x;
        vLooky = pCamPos->y - pTarget->y;
        vLookz = pCamPos->z - pTarget->z;
    }

    // vLook Normalize
    {
        f32 mag = (vLookx * vLookx) + (vLooky * vLooky) + (vLookz * vLookz);
    
        NN_ASSERTMSG(mag != 0, "MATHNormalize3():  zero magnitude vector");
    
        mag = 1.0f / ::std::sqrtf(mag);
    
    
        vLookx = vLookx * mag;
        vLooky = vLooky * mag;
        vLookz = vLookz * mag;
    }

    // vRight = pCamUp x vLook
    f32 vRightx, vRighty, vRightz;
    {
        vRightx = ( pCamUp->y * vLookz ) - ( pCamUp->z * vLooky );
        vRighty = ( pCamUp->z * vLookx ) - ( pCamUp->x * vLookz );
        vRightz = ( pCamUp->x * vLooky ) - ( pCamUp->y * vLookx );
    }
    
    // vRight Normalize
    {
        f32 mag = (vRightx * vRightx) + (vRighty * vRighty) + (vRightz * vRightz);
    
        NN_ASSERTMSG(mag != 0, "MATHNormalize3():  zero magnitude vector");
    
        mag = 1.0f / ::std::sqrtf(mag);

        vRightx = vRightx * mag;
        vRighty = vRighty * mag;
        vRightz = vRightz * mag;
    }

    // vUp = vLook x vRight
    f32 vUpx, vUpy, vUpz;
    {
        vUpx = ( vLooky * vRightz ) - ( vLookz * vRighty );
        vUpy = ( vLookz * vRightx ) - ( vLookx * vRightz );
        vUpz = ( vLookx * vRighty ) - ( vLooky * vRightx );
    }
    

    // Don't need to normalize vUp since it should already be unit length
    // VECNormalize( &vUp, &vUp );
    f32 tmp1, tmp2, tmp3;

    tmp1 = -( pCamPos->x * vRightx + pCamPos->y * vRighty + pCamPos->z * vRightz );
    tmp2 = -( pCamPos->x * vUpx + pCamPos->y * vUpy + pCamPos->z * vUpz );
    tmp3 = -( pCamPos->x * vLookx + pCamPos->y * vLooky + pCamPos->z * vLookz );
    
    m[0][0] = vRightx;
    m[0][1] = vRighty;
    m[0][2] = vRightz;

    m[1][0] = vUpx;
    m[1][1] = vUpy;
    m[1][2] = vUpz;

    m[2][0] = vLookx;
    m[2][1] = vLooky;
    m[2][2] = vLookz;

    m[0][3] = tmp1;
    m[1][3] = tmp2;
    m[2][3] = tmp3;

    return pOut;
}

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34LookAtC(MTX34* pOut, const VEC3* pCamPos, f32 twist, const VEC3* pTarget)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pCamPos);
    NN_NULL_ASSERT(pTarget);

    f32 (*const m)[4] = pOut->m;

    // Z-direction for camera coordinate system
    VEC3 lookReverse(pCamPos->x - pTarget->x, pCamPos->y - pTarget->y, pCamPos->z - pTarget->z);

    if ((lookReverse.x == 0.0f) && (lookReverse.z == 0.0f))
    {
        // Twist is not defined if the xz-coordinates of the camera and the target are the same.
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = -pCamPos->x;

        m[1][0] = 0.0f;
        m[1][1] = 0.0f;

        m[2][0] = 0.0f;
        m[2][2] = 0.0f;

        if (lookReverse.y <= 0.0f)
        {
            // When looking straight up
            m[1][2] = 1.0f;
            m[1][3] = -pCamPos->z;

            m[2][1] = -1.0f;
            m[2][3] = pCamPos->y;
        }
        else
        {
            // When looking straight down
            m[1][2] = -1.0f;
            m[1][3] = pCamPos->z;

            m[2][1] = 1.0f;
            m[2][3] = -pCamPos->y;
        }
    }
    else
    {
        // X-direction for camera coordinate system
        VEC3 r(lookReverse.z, 0.0f, -lookReverse.x);

        VEC3Normalize(&lookReverse, &lookReverse);
        VEC3Normalize(&r, &r);

        // Y-direction for camera coordinate system
        VEC3 u;
        VEC3Cross(&u, &lookReverse, &r);

        f32 st, ct;
        SinCosDeg(&st, &ct, twist);
        VEC3 right, up;

        // Get 'right' by rotating the r-axis and u-axis cameraTwist values a half rotation clockwise on the ru-plane
        // Note that r.y == 0.
        right.x = st * u.x + ct * r.x;
        right.y = st * u.y;
        right.z = st * u.z + ct * r.z;

        up.x    = ct * u.x - st * r.x;
        up.y    = ct * u.y;
        up.z    = ct * u.z - st * r.z;

        // Right
        m[0][0] = right.x;
        m[0][1] = right.y;
        m[0][2] = right.z;
        m[0][3] = -VEC3Dot(pCamPos, &right);

        // Up
        m[1][0] = up.x;
        m[1][1] = up.y;
        m[1][2] = up.z;
        m[1][3] = -VEC3Dot(pCamPos, &up);

        // look
        m[2][0] = lookReverse.x;
        m[2][1] = lookReverse.y;
        m[2][2] = lookReverse.z;
        m[2][3] = -VEC3Dot(pCamPos, &lookReverse);
    }

    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34LookAtC_FAST(MTX34* pOut, const VEC3* pCamPos, f32 twist, const VEC3* pTarget)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pCamPos);
    NN_NULL_ASSERT(pTarget);

    f32 (*const m)[4] = pOut->m;

    // Z-direction for camera coordinate system
    f32 lookReversex, lookReversey, lookReversez;
    
    lookReversex = pCamPos->x - pTarget->x;
    lookReversez = pCamPos->z - pTarget->z;
    lookReversey = pCamPos->y - pTarget->y;

    if ((lookReversex == 0.0f) && (lookReversez == 0.0f))
    {
        // Twist is not defined if the xz-coordinates of the camera and the target are the same.
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = -pCamPos->x;

        m[1][0] = 0.0f;
        m[1][1] = 0.0f;

        m[2][0] = 0.0f;
        m[2][2] = 0.0f;

        if (lookReversey <= 0.0f)
        {
            // When looking straight up
            m[1][2] = 1.0f;
            m[1][3] = -pCamPos->z;

            m[2][1] = -1.0f;
            m[2][3] = pCamPos->y;
        }
        else
        {
            // When looking straight down
            m[1][2] = -1.0f;
            m[1][3] = pCamPos->z;

            m[2][1] = 1.0f;
            m[2][3] = -pCamPos->y;
        }
    }
    else
    {
        // X-direction for camera coordinate system
        f32 rx, ry, rz;
        f32 mag1, mag2;
        f32 ux, uy, uz;
        f32 fidx;
        
        mag1 = (lookReversez * lookReversez) + (-lookReversex * -lookReversex);
        mag2 = (lookReversex * lookReversex) + (lookReversey * lookReversey) + (lookReversez * lookReversez);
        NN_ASSERTMSG(mag1 != 0, "MATHNormalize3():  zero magnitude vector");
        NN_ASSERTMSG(mag2 != 0, "MATHNormalize3():  zero magnitude vector");
        mag1 = ::std::sqrtf(mag1);
        mag2 = ::std::sqrtf(mag2);
        fidx = NN_MATH_DEG_TO_FIDX(twist);
        mag1 = 1.0f / mag1;
        mag2 = 1.0f / mag2;
        
        // r Normalize
        {
            rx = lookReversez * mag1;
            ry = 0.0f;
            rz = -lookReversex * mag1;
        }
        // lookReverse Normalize
        {
            lookReversex = lookReversex * mag2;
            lookReversey = lookReversey * mag2;
            lookReversez = lookReversez * mag2;
        }

        // Y-direction for camera coordinate system
        {
            ux = ( lookReversey * rz ) - ( lookReversez * ry );
            uy = ( lookReversez * rx ) - ( lookReversex * rz );
            uz = ( lookReversex * ry ) - ( lookReversey * rx );
        }


        f32 st, ct;
//        SinCosDeg(&st, &ct, twist);
        SinCosFIdx(&st, &ct, fidx);
        f32 rightx, righty, rightz;
        f32 upx, upy, upz;

        // Get 'right' by rotating the r-axis and u-axis cameraTwist values a half rotation clockwise on the ru-plane
        // Note that r.y == 0.
        rightx = st * ux + ct * rx;
        righty = st * uy;
        rightz = st * uz + ct * rz;

        upx    = ct * ux - st * rx;
        upy    = ct * uy;
        upz    = ct * uz - st * rz;

        // Right
        f32 tmp1, tmp2, tmp3;

        tmp1 = pCamPos->x * rightx + pCamPos->y * righty + pCamPos->z * rightz;
        tmp2 = pCamPos->x * upx + pCamPos->y * upy + pCamPos->z * upz;
        tmp3 = pCamPos->x * lookReversex + pCamPos->y * lookReversey + pCamPos->z * lookReversez;
        
        m[0][0] = rightx;
        m[0][1] = righty;
        m[0][2] = rightz;
        m[0][3] = -tmp1;

        // Up
        m[1][0] = upx;
        m[1][1] = upy;
        m[1][2] = upz;
        m[1][3] = -tmp2;

        // look
        m[2][0] = lookReversex;
        m[2][1] = lookReversey;
        m[2][2] = lookReversez;
        m[2][3] = -tmp3;
    }

    return pOut;
}

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34*
MTX34CameraRotateC(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotate)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pCamPos);
    NN_NULL_ASSERT(pCamRotate);

    f32 (*const m)[4] = pOut->m;

    f32 sx, sy, sz, cx, cy, cz;
    SinCosDeg(&sx, &cx, pCamRotate->x);
    SinCosDeg(&sy, &cy, pCamRotate->y);
    SinCosDeg(&sz, &cz, pCamRotate->z);

    // Rotate in the order of z-axis, x-axis, y-axis
    VEC3 right, up, back;

    right.x = sx * sy * sz + cy * cz;
    right.y = cx * sz;
    right.z = sx * cy * sz - sy * cz;

    up.x    = sx * sy * cz - cy * sz;
    up.y    = cx * cz;
    up.z    = sx * cy * cz + sy * sz;

    back.x  = cx * sy;
    back.y  = - sx;
    back.z  = cx * cy;

    m[0][0] = right.x;
    m[0][1] = right.y;
    m[0][2] = right.z;
    m[0][3] = -VEC3Dot(pCamPos, &right);

    m[1][0] = up.x;
    m[1][1] = up.y;
    m[1][2] = up.z;
    m[1][3] = -VEC3Dot(pCamPos, &up);

    m[2][0] = back.x;
    m[2][1] = back.y;
    m[2][2] = back.z;
    m[2][3] = -VEC3Dot(pCamPos, &back);

    return pOut;
}
NN_MATH_INLINE MTX34*
MTX34CameraRotateC_FAST(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotate)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pCamPos);
    NN_NULL_ASSERT(pCamRotate);

    f32 (*const m)[4] = pOut->m;

    f32 sinx, cosx;
    f32 siny, cosy;
    f32 sinz, cosz;
    f32 fIdxX = NN_MATH_DEG_TO_FIDX(pCamRotate->x);
    f32 fIdxY = NN_MATH_DEG_TO_FIDX(pCamRotate->y);
    f32 fIdxZ = NN_MATH_DEG_TO_FIDX(pCamRotate->z);

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




    // Rotate in the order of z-axis, x-axis, y-axis
    register VEC3 right, up, back;
    register f32 m00, m01, m02, m03;
    register f32 m10, m11, m12, m13;
    register f32 m20, m21, m22, m23;



    right.x = sinx * siny * sinz + cosy * cosz;
    right.y = cosx * sinz;
    right.z = sinx * cosy * sinz - siny * cosz;

    up.x    = sinx * siny * cosz - cosy * sinz;
    up.y    = cosx * cosz;
    up.z    = sinx * cosy * cosz + siny * sinz;

    back.x  = cosx * siny;
    back.y  = - sinx;
    back.z  = cosx * cosy;

    m00 = right.x;
    m01 = right.y;
    m02 = right.z;
    m03 = -VEC3Dot(pCamPos, &right);

    m10 = up.x;
    m11 = up.y;
    m12 = up.z;
    m13 = -VEC3Dot(pCamPos, &up);

    m20 = back.x;
    m21 = back.y;
    m22 = back.z;
    m23 = -VEC3Dot(pCamPos, &back);

    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    
    return pOut;
}

/*  

*/
/* Please see man pages for details 
    
    
*/

/*
  

  
  

  
 */
NN_MATH_INLINE MTX34*
QUATToMTX34C(MTX34* pOut, const QUAT* pQ, bool isChangeTrans)
{
    f32 s, xs, ys, zs;
    f32 wx, wy, wz, xx, xy, xz, yy, yz, zz;

    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pQ);
    NN_ASSERT( pQ->x || pQ->y || pQ->z || pQ->w );

    f32 (*const m)[4] = pOut->m;

    s = 2.0f / ( (pQ->x * pQ->x) + (pQ->y * pQ->y) + (pQ->z * pQ->z) + (pQ->w * pQ->w) );

    xs = pQ->x *  s;     ys = pQ->y *  s;  zs = pQ->z *  s;
    wx = pQ->w * xs;     wy = pQ->w * ys;  wz = pQ->w * zs;
    xx = pQ->x * xs;     xy = pQ->x * ys;  xz = pQ->x * zs;
    yy = pQ->y * ys;     yz = pQ->y * zs;  zz = pQ->z * zs;

    m[0][0] = 1.0f - (yy + zz);
    m[0][1] = xy   - wz;
    m[0][2] = xz   + wy;
    if ( isChangeTrans )    m[0][3] = 0.0f;

    m[1][0] = xy   + wz;
    m[1][1] = 1.0f - (xx + zz);
    m[1][2] = yz   - wx;
    if ( isChangeTrans )    m[1][3] = 0.0f;

    m[2][0] = xz   - wy;
    m[2][1] = yz   + wx;
    m[2][2] = 1.0f - (xx + yy);
    if ( isChangeTrans )    m[2][3] = 0.0f;
    
    return pOut;
}
NN_MATH_INLINE MTX34*
QUATToMTX34C_FAST(MTX34* pOut, const QUAT* pQ, bool isChangeTrans)
{
    f32 s, xs, ys, zs;
    f32 wx, wy, wz, xx, xy, xz, yy, yz, zz;
    f32 m00, m01, m02, m10, m11, m12, m20, m21, m22;
    f32 pQx, pQy, pQz, pQw;

    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pQ);
    NN_ASSERT( pQ->x || pQ->y || pQ->z || pQ->w );

    f32 (*const m)[4] = pOut->m;
    
    pQx = pQ->x;
    pQy = pQ->y;
    pQz = pQ->z;
    pQw = pQ->w;

    s = 2.0f / ( (pQx * pQx) + (pQy * pQy) + (pQz * pQz) + (pQw * pQw) );

    xs = pQx *  s;     ys = pQy *  s;  zs = pQz *  s;
    wx = pQw * xs;     wy = pQw * ys;  wz = pQw * zs;
    xx = pQx * xs;     xy = pQx * ys;  xz = pQx * zs;
    yy = pQy * ys;     yz = pQy * zs;  zz = pQz * zs;

    m00 = 1.0f - (yy + zz);
    m01 = xy   - wz;
    m02 = xz   + wy;

    m10 = xy   + wz;
    m11 = 1.0f - (xx + zz);
    m12 = yz   - wx;

    m20 = xz   - wy;
    m21 = yz   + wx;
    m22 = 1.0f - (xx + yy);

    if ( isChangeTrans )
    {
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
    }

    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;

    
    return pOut;
}

/*  

*/

}  // namespace ARMv6
}  // namespace math
}  // namespace nn
