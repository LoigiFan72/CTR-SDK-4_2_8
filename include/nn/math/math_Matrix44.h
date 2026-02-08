/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix44.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49840 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATRIX44_H_
#define NN_MATH_MATRIX44_H_

#include <cstring>
#include <nn/math/math_Config.h>

#pragma push
#pragma Otime

namespace nn { 
namespace math {

/*
  
  
 */
enum PivotDirection
{
    PIVOT_NONE,             //
    PIVOT_UPSIDE_TO_TOP,    //
    PIVOT_UPSIDE_TO_RIGHT,  //
    PIVOT_UPSIDE_TO_BOTTOM, //
    PIVOT_UPSIDE_TO_LEFT,   //
    PIVOT_NUM
};

struct MTX44;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for MTX44
   ------------------------------------------------------------------------ */
/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Copy(MTX44* pOut, const MTX44* p);

/*
  
                

  
  
  
  
  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Frustum(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);

/*
  
                

  
  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44FrustumPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE);

/*
  

  

  
 */
NN_MATH_INLINE MTX44* MTX44Identity(MTX44* pOut);

/*
  

  
  

  
 */
NN_FORCE_INLINE u32 MTX44Inverse(MTX44* pOut, const MTX44* p);

/*
  

  

  
 */
NN_MATH_INLINE bool   MTX44IsIdentity(const MTX44* p);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Mult(MTX44* pOut, const MTX44* p, f32 f);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44MultArray(MTX44* pOut, const MTX44* p1, const MTX44* pSrc, s32 count);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44MultTranslate(MTX44* pOut, const VEC3* pT, const MTX44* pM);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44MultTranslate(MTX44* pOut, const MTX44* pM, const VEC3* pT);

/*
  
                

  
  
  
  
  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Ortho(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);

/*
  
                

  
  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44OrthoPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE);

/*
  

  
  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44PerspectiveDeg(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f);

// Alias of MTX44PerspectiveDeg function.
// For compatibility reasons, the Perspective function does not have a suffix. This is for the "degree" version.
inline MTX44* 
MTX44Perspective(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f) 
{ 
    return MTX44PerspectiveDeg(pOut, fovy, aspect, n, f); 
}

/*
  

  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44PerspectivePivotDeg(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE );

/*
  
                

  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44PerspectivePivotRad(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE);

/*
  

  
  
  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44PerspectiveRad(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f);

/*
  

  
  

  
*/
NN_FORCE_INLINE MTX44* MTX44Pivot( MTX44* pOut, PivotDirection pivot );

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44RotAxisDeg(MTX44* pOut, const VEC3* pAxis, f32 fDeg);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44RotAxisFIdx(MTX44* pOut, const VEC3* pAxis, f32 fIdx);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44RotAxisRad(MTX44* pOut, const VEC3* pAxis, f32 fRad);

/*
  
  
  

  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44RotAxisRad_( MTX44* pOut, const VEC3 *pAxis, f32 fRad );

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44RotXYZDeg(MTX44* pOut, f32 fDegX, f32 fDegY, f32 fDegZ);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44RotXYZFIdx(MTX44* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44RotXYZRad(MTX44* pOut, f32 fRadX, f32 fRadY, f32 fRadZ);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Scale(MTX44* pOut, const VEC3* pS);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX44* MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Translate(MTX44* pOut, const VEC3* pT);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX44* MTX44Transpose(MTX44* pOut, const MTX44 *pSrc);

/*
  

  

  
 */
NN_MATH_INLINE MTX44* MTX44Zero(MTX44* pOut);

/*  

*/

NN_FORCE_INLINE VEC4* VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV);

/* =======================================================================
        Class definitions
   ======================================================================== */
struct MTX34;

/*
    
    
 */
struct MTX44_
{
    //
    struct BaseData
    {
        f32 _00;    //
        f32 _01;    //
        f32 _02;    //
        f32 _03;    //
        f32 _10;    //
        f32 _11;    //
        f32 _12;    //
        f32 _13;    //
        f32 _20;    //
        f32 _21;    //
        f32 _22;    //
        f32 _23;    //
        f32 _30;    //
        f32 _31;    //
        f32 _32;    //
        f32 _33;    //
    };

    union
    {
    //----------------------------------------
    //
    //
    #if defined(NN_MATH_USE_ANONYMOUS_STRUCT)
        //
        struct
        {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
            f32 _30, _31, _32, _33;
        };
    #endif
        BaseData f;     //
        f32 m[4][4];    //
        f32 a[16];      //
        VEC4_ v[4];     //
    //
    };
};

/*
  
  
 */
class MTX44 : public MTX44_
{
public:
    static const int ROW_COUNT = 4; //
    static const int COLUMN_COUNT = 4; //
    
    //
    static const MTX44& Identity()
    {
        static const MTX44 identity(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
        
        return identity;
    }
    typedef MTX44 self_type; //
    typedef f32   value_type; //

public:
    //----------------------------------------
    //
    //

    //
    MTX44() {}
    
    //
    explicit MTX44(const f32* p) { (void)MTX44Copy(this, (MTX44*)p); }
    
    //
    explicit MTX44(const MTX34& rhs)
    {
        (void)MTX34Copy((MTX34*)this, (MTX34*)&rhs);
        f._30 = f._31 = f._32 = 0.f; f._33 = 1.f;
    }
    
    //
    MTX44(const MTX44& rhs) { (void)MTX44Copy(this, &rhs); }
    
    //
    MTX44(f32 x00, f32 x01, f32 x02, f32 x03,
          f32 x10, f32 x11, f32 x12, f32 x13,
          f32 x20, f32 x21, f32 x22, f32 x23,
          f32 x30, f32 x31, f32 x32, f32 x33)
    {
        f._00 = x00; f._01 = x01; f._02 = x02; f._03 = x03;
        f._10 = x10; f._11 = x11; f._12 = x12; f._13 = x13;
        f._20 = x20; f._21 = x21; f._22 = x22; f._23 = x23;
        f._30 = x30; f._31 = x31; f._32 = x32; f._33 = x33;
    }

    //

    //----------------------------------------
    //
    //

    //
    operator f32*() { return this->a; }
    
    //
    operator const f32*() const { return this->a; }
    
    //
    VEC4& GetRow(int index)
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, ROW_COUNT);
        return *reinterpret_cast<VEC4*>(&this->v[index]);
    }
    
    //
    const VEC4& GetRow(int index) const
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, ROW_COUNT);
        return *reinterpret_cast<const VEC4*>(&this->v[index]);
    }
    
    //
    VEC4 GetColumn(int index) const
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, COLUMN_COUNT);
        VEC4 column;
        column.x = this->m[0][index];
        column.y = this->m[1][index];
        column.z = this->m[2][index];
        column.w = this->m[3][index];
        return column;
    }
    
    //
    void SetColumn(int index, const VEC4& column)
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, COLUMN_COUNT);
        this->m[0][index] = column.x;
        this->m[1][index] = column.y;
        this->m[2][index] = column.z;
        this->m[3][index] = column.w;
    }
    //

    //----------------------------------------
    //
    //

    //
    self_type& operator *= (const self_type& rhs) { return *MTX44Mult(this, this, &rhs); }

    //
    self_type& operator += (const self_type& rhs) { return *MTX44Add(this, this, &rhs); }

    //
    self_type& operator -= (const self_type& rhs) { return *MTX44Sub(this, this, &rhs); }
    
    //
    self_type& operator *= (f32 f) { return *MTX44Mult(this, this, f); }

    //
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const
    {
        return MTX44(-f._00, -f._01, -f._02, -f._03,
                     -f._10, -f._11, -f._12, -f._13,
                     -f._20, -f._21, -f._22, -f._23,
                     -f._30, -f._31, -f._32, -f._33);
    }

    //
    self_type operator + (const self_type& rhs) const { MTX44 tmp; return *MTX44Add(&tmp, this, &rhs); }

    //
    self_type operator - (const self_type& rhs) const { MTX44 tmp; return *MTX44Sub(&tmp, this, &rhs); }

    //
    self_type operator * (f32 f) const { MTX44 tmp; return *MTX44Mult(&tmp, this, f); }

    //
    self_type operator / (f32 f) const { return *this * (1.f / f); }

    //
    self_type& Transpose() { return *MTX44Transpose(this, this); }
    //

    //----------------------------------------
    //
    //
    
    //
    self_type& SetupIdentity() { return *MTX44Identity(this); }
    
    //
    //
    //
    //
    self_type& SetupScale(const VEC3& scale) { return *MTX44Scale(this, &scale); }

    //
    //
    //
    //
    self_type& SetupTranslate(const VEC3& translate)
    {
        return *MTX44Translate(this, &translate);
    }

    //
    //
    //
    //
    self_type& SetupRotateXyz(const VEC3& rotateRad)
    {
        return *MTX44RotXYZRad(this, rotateRad.x, rotateRad.y, rotateRad.z);
    }

    //
    //
    //
    //
    //
    self_type& SetupRotate(const VEC3& axis, f32 thetaRad)
    {
        return *MTX44RotAxisRad(this, &axis, thetaRad);
    }

    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    self_type& SetupFrustum(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE)
    {
        return *MTX44FrustumPivot(this, l, r, b, t, n, f, pivot);
    }

    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    self_type& SetupOrtho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE)
    {
        return *MTX44OrthoPivot(this, l, r, b, t, n, f, pivot);
    }
    
    //
    //
    //
    //
    //
    //
    //
    //
    self_type& SetupPerspective(f32 fovyRad, f32 aspect, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE)
    {
        return *MTX44PerspectivePivotRad(this, fovyRad, aspect, n, f, pivot);
    }

    //
    
    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX44)) == 0; }
    
    //
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX44)) != 0; }

    //
    bool IsIdentity() const { return MTX44IsIdentity(this); }
    //

    /*
      

      
      

      
     */
    void Report(bool bNewline = true, const char* name = NULL) const;

private:
    typedef void (self_type::*UnspecifiedBoolType)() const;
    operator UnspecifiedBoolType() const;
    operator UnspecifiedBoolType();
};

//
//

//
typedef class MTX44 Matrix44;

//

}  // namespace math
}  // namespace nn

#include <nn/math/ARMv6/math_Matrix44.h>

namespace nn { 
namespace math {

NN_FORCE_INLINE MTX44*
MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{

#if defined( NN_HARDWARE_CTR )
    #if (MTX44ADD_ASM_CONFIG == D_ORG)
        return ARMv6::MTX44AddC(pOut, p1, p2);
    #elif (MTX44ADD_ASM_CONFIG == D_FAST_C)
    #elif (MTX44ADD_ASM_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44AddAsm(pOut, p1, p2);
    #elif (MTX44ADD_ASM_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44ADD_ASM_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44Copy(MTX44* pOut, const MTX44* p)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44COPY_CONFIG == D_ORG)
        return ARMv6::MTX44CopyC(pOut, p);
    #elif (MTX44COPY_CONFIG == D_FAST_C)
    #elif (MTX44COPY_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44CopyAsm(pOut, p);
    #elif (MTX44COPY_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44COPY_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}


NN_FORCE_INLINE MTX44*
MTX44Frustum(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44FRUSTUM_CONFIG == D_ORG)
        return ARMv6::MTX44FrustumC(pOut, l, r, b, t, n, f);
    #elif (MTX44FRUSTUM_CONFIG == D_FAST_C)
        return ARMv6::MTX44FrustumC_FAST(pOut, l, r, b, t, n, f);
    #elif (MTX44FRUSTUM_CONFIG == D_FAST_ASM)
    #elif (MTX44FRUSTUM_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44FRUSTUM_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}


NN_FORCE_INLINE u32
MTX44Inverse(MTX44* pOut, const MTX44* p)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44INVERSE_CONFIG == D_ORG)
        return ARMv6::MTX44InverseC(pOut, p);
    #elif (MTX44INVERSE_CONFIG == D_FAST_C)
    #elif (MTX44INVERSE_CONFIG == D_FAST_ASM)
    #elif (MTX44INVERSE_CONFIG == D_FAST_C_ALGO)
        return ARMv6::MTX44InverseC_FAST_ALGO(pOut, p);
    #elif (MTX44INVERSE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}


NN_FORCE_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2) 
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44MULT_44_CONFIG == D_ORG)
        return ARMv6::MTX44MultC(pOut, p1, p2);
    #elif (MTX44MULT_44_CONFIG == D_FAST_C)
    #elif (MTX44MULT_44_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44MultAsm(pOut, p1, p2);
    #elif (MTX44MULT_44_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44MULT_44_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* p, f32 f)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44MULT_F32_CONFIG == D_ORG)
        return ARMv6::MTX44MultC(pOut, p, f);
    #elif (MTX44MULT_F32_CONFIG == D_FAST_C)
    #elif (MTX44MULT_F32_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44MultAsm(pOut, p, f);
    #elif (MTX44MULT_F32_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44MULT_F32_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_FORCE_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44MULTSCALE_RIGHT_CONFIG == D_ORG)
        return ARMv6::MTX44MultScaleC(pOut, pM, pS);
    #elif (MTX44MULTSCALE_RIGHT_CONFIG == D_FAST_C)
    #elif (MTX44MULTSCALE_RIGHT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44MultScaleAsm(pOut, pM, pS);
    #elif (MTX44MULTSCALE_RIGHT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44MULTSCALE_RIGHT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44MULTSCALE_LEFT_CONFIG == D_ORG)
        return ARMv6::MTX44MultScaleC(pOut, pS, pM);
    #elif (MTX44MULTSCALE_LEFT_CONFIG == D_FAST_C)
    #elif (MTX44MULTSCALE_LEFT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44MultScaleAsm(pOut, pS, pM);
    #elif (MTX44MULTSCALE_LEFT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44MULTSCALE_LEFT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44MultTranslate(MTX44* pOut, const VEC3* pT, const MTX44* pM)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44MULTTRANSLATE_LEFT_CONFIG == D_ORG)
        return ARMv6::MTX44MultTranslateC(pOut, pT, pM);
    #elif (MTX44MULTTRANSLATE_LEFT_CONFIG == D_FAST_C)
    #elif (MTX44MULTTRANSLATE_LEFT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44MultTranslateAsm(pOut, pT, pM);
    #elif (MTX44MULTTRANSLATE_LEFT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44MULTTRANSLATE_LEFT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44MultTranslate(MTX44* pOut, const MTX44* pM, const VEC3* pT)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44MULTTRANSLATE_RIGHT_CONFIG == D_ORG)
        return ARMv6::MTX44MultTranslateC(pOut, pM, pT);
    #elif (MTX44MULTTRANSLATE_RIGHT_CONFIG == D_FAST_C)
    #elif (MTX44MULTTRANSLATE_RIGHT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX44MultTranslateAsm(pOut, pM, pT);
    #elif (MTX44MULTTRANSLATE_RIGHT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44MULTTRANSLATE_RIGHT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44Ortho(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44ORTHO_CONFIG == D_ORG)
        return ARMv6::MTX44OrthoC(pOut, l, r, b, t, n, f);
    #elif (MTX44ORTHO_CONFIG == D_FAST_C)
        return ARMv6::MTX44OrthoC_FAST(pOut, l, r, b, t, n, f);
    #elif (MTX44ORTHO_CONFIG == D_FAST_ASM)
    #elif (MTX44ORTHO_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44ORTHO_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44PerspectiveRad(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44PERSPECTIVERAD_CONFIG == D_ORG)
        return ARMv6::MTX44PerspectiveRadC(pOut, fovy, aspect, n, f);
    #elif (MTX44PERSPECTIVERAD_CONFIG == D_FAST_C)
        return ARMv6::MTX44PerspectiveRadC_FAST(pOut, fovy, aspect, n, f);
    #elif (MTX44PERSPECTIVERAD_CONFIG == D_FAST_ASM)
    #elif (MTX44PERSPECTIVERAD_CONFIG == D_FAST_C_ALGO)
        return ARMv6::MTX44PerspectiveRadC_FAST(pOut, fovy, aspect, n, f);
    #elif (MTX44PERSPECTIVERAD_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44RotAxisRad_( MTX44* pOut, const VEC3 *pAxis, f32 fRad )
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44ROTAXISRAD__CONFIG == D_ORG)
        return ARMv6::MTX44RotAxisRad_C(pOut, pAxis, fRad);
    #elif (MTX44ROTAXISRAD__CONFIG == D_FAST_C)
        return ARMv6::MTX44RotAxisRad_C_FAST(pOut, pAxis, fRad);
    #elif (MTX44ROTAXISRAD__CONFIG == D_FAST_ASM)
    #elif (MTX44ROTAXISRAD__CONFIG == D_FAST_C_ALGO)
        return ARMv6::MTX44RotAxisRad_C_FAST(pOut, pAxis, fRad);
    #elif (MTX44ROTAXISRAD__CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44RotXYZFIdx(MTX44* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44ROTXYZFIDX_CONFIG == D_ORG)
        return ARMv6::MTX44RotXYZFIdxC(pOut, fIdxX, fIdxY, fIdxZ);
    #elif (MTX44ROTXYZFIDX_CONFIG == D_FAST_C)
        return ARMv6::MTX44RotXYZFIdxC_FAST(pOut, fIdxX, fIdxY, fIdxZ);
    #elif (MTX44ROTXYZFIDX_CONFIG == D_FAST_ASM)
    #elif (MTX44ROTXYZFIDX_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44ROTXYZFIDX_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44Scale(MTX44* pOut, const VEC3* pS)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44SCALE_CONFIG == D_ORG)
        return ARMv6::MTX44ScaleC(pOut, pS);
    #elif (MTX44SCALE_CONFIG == D_FAST_C)
        return ARMv6::MTX44ScaleC_FAST(pOut, pS);
    #elif (MTX44SCALE_CONFIG == D_FAST_ASM)
    #elif (MTX44SCALE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44SCALE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX44*
MTX44Translate(MTX44* pOut, const VEC3* pT)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44TRANSLATE_CONFIG == D_ORG)
        return ARMv6::MTX44TranslateC(pOut, pT);
    #elif (MTX44TRANSLATE_CONFIG == D_FAST_C)
        return ARMv6::MTX44TranslateC_FAST(pOut, pT);
    #elif (MTX44TRANSLATE_CONFIG == D_FAST_ASM)
    #elif (MTX44TRANSLATE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44TRANSLATE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_FORCE_INLINE MTX44* 
MTX44Transpose(MTX44* pOut, const MTX44 *pSrc)
{
#if defined( NN_HARDWARE_CTR )
#if (MTX44TRANSPOSE_44_CONFIG == D_ORG)
    return ARMv6::MTX44TransposeC(pOut, pSrc);
#elif (MTX44TRANSPOSE_44_CONFIG == D_FAST_C)
#elif (MTX44TRANSPOSE_44_CONFIG == D_FAST_ASM)
    return ARMv6::MTX44TransposeAsm(pOut, pSrc);
#elif (MTX44TRANSPOSE_44_CONFIG == D_FAST_C_ALGO)
#elif (MTX44TRANSPOSE_44_CONFIG == D_FAST_ASM_ALGO)
#endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_MATH_INLINE MTX44*
MTX44PerspectiveDeg(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f)
{
    return MTX44PerspectiveRad(pOut, NN_MATH_DEG_TO_RAD(fovy), aspect, n, f);
}

NN_MATH_INLINE MTX44*
MTX44PerspectivePivotDeg(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f, PivotDirection pivot)
{
    return MTX44PerspectivePivotRad(pOut, NN_MATH_DEG_TO_RAD(fovy), aspect, n, f, pivot);
}

NN_MATH_INLINE MTX44*
MTX44RotXYZRad(MTX44* pOut, f32 fRadX, f32 fRadY, f32 fRadZ)
{
    return MTX44RotXYZFIdx(pOut, NN_MATH_RAD_TO_FIDX(fRadX), NN_MATH_RAD_TO_FIDX(fRadY), NN_MATH_RAD_TO_FIDX(fRadZ));
}

NN_MATH_INLINE MTX44*
MTX44RotXYZDeg(MTX44* pOut, f32 fDegX, f32 fDegY, f32 fDegZ)
{
    return MTX44RotXYZFIdx(pOut, NN_MATH_DEG_TO_FIDX(fDegX), NN_MATH_DEG_TO_FIDX(fDegY), NN_MATH_DEG_TO_FIDX(fDegZ));
}

NN_MATH_INLINE MTX44*
MTX44RotAxisRad(MTX44* pOut, const VEC3* pAxis, f32 fRad)
{
    return MTX44RotAxisFIdx(pOut, pAxis, NN_MATH_RAD_TO_FIDX(fRad));
}

NN_MATH_INLINE MTX44*
MTX44RotAxisDeg(MTX44* pOut, const VEC3* pAxis, f32 fDeg)
{
    return MTX44RotAxisFIdx(pOut, pAxis, NN_MATH_DEG_TO_FIDX(fDeg));
}

NN_FORCE_INLINE MTX44*
MTX44Pivot( MTX44* pOut, PivotDirection pivot )
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX44PIVOT_CONFIG == D_ORG)
        return ARMv6::MTX44PivotC(pOut, pivot);
    #elif (MTX44PIVOT_CONFIG == D_FAST_C)
        return ARMv6::MTX44PivotC_FAST(pOut, pivot);
    #elif (MTX44PIVOT_CONFIG == D_FAST_ASM)
    #elif (MTX44PIVOT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX44PIVOT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_FORCE_INLINE VEC4*
VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV)
{
#if defined( NN_HARDWARE_CTR )
    #if (VEC3TRANSFORM_44XVEC3_CONFIG == D_ORG)
        return ARMv6::VEC3TransformC(pOut, pM, pV);
    #elif (VEC3TRANSFORM_44XVEC3_CONFIG == D_FAST_C)
    #elif (VEC3TRANSFORM_44XVEC3_CONFIG == D_FAST_ASM)
        return ARMv6::VEC3TransformAsm(pOut, pM, pV);
    #elif (VEC3TRANSFORM_44XVEC3_CONFIG == D_FAST_C_ALGO)
    #elif (VEC3TRANSFORM_44XVEC3_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

//Overload referencing the -- const argument
inline MTX44* MTX44Copy(MTX44* pOut, const MTX44& m) { return MTX44Copy( pOut, &m ); }
inline bool   MTX44IsIdentity(const MTX44& m) { return MTX44IsIdentity( &m ); }

inline MTX44* MTX44Add(MTX44* pOut, const MTX44& m1, const MTX44& m2) { return MTX44Add( pOut, &m1, &m2 ); }
inline MTX44* MTX44Sub(MTX44* pOut, const MTX44& m1, const MTX44& m2) { return MTX44Sub( pOut, &m1, &m2 ); }
inline MTX44* MTX44Mult(MTX44* pOut, const MTX44& m, f32 f) { return MTX44Mult( pOut, &m, f ); }
inline MTX44* MTX44Mult(MTX44* pOut, const MTX44& m1, const MTX44& m2) { return MTX44Mult( pOut, &m1, &m2 ); }

inline MTX44* MTX44Transpose(MTX44* pOut, const MTX44& m) { return MTX44Transpose( pOut, &m ); }
inline MTX44* MTX44MultArray(MTX44* pOut, const MTX44& m1, const MTX44* pSrc, s32 count) { return MTX44MultArray( pOut, &m1, pSrc, count ); }
inline u32    MTX44Inverse(MTX44* pOut, const MTX44& m) { return MTX44Inverse( pOut, &m ); }

inline MTX44* MTX44RotAxisFIdx(MTX44* pOut, const VEC3& vAxis, f32 fIdx) { return MTX44RotAxisFIdx( pOut, &vAxis, fIdx ); }
inline MTX44* MTX44RotAxisRad(MTX44* pOut, const VEC3& vAxis, f32 fRad) { return MTX44RotAxisRad( pOut, &vAxis, fRad ); }
inline MTX44* MTX44RotAxisDeg(MTX44* pOut, const VEC3& vAxis, f32 fDeg) { return MTX44RotAxisDeg( pOut, &vAxis, fDeg ); }

inline MTX44* MTX44Scale(MTX44* pOut, const VEC3& S) { return MTX44Scale(pOut, &S); }
inline MTX44* MTX44MultScale(MTX44* pOut, const MTX44& M, const VEC3& S) { return MTX44MultScale(pOut, &M, &S); }
inline MTX44* MTX44MultScale(MTX44* pOut, const VEC3& S, const MTX44& M) { return MTX44MultScale(pOut, &S, &M); }

inline MTX44* MTX44Translate(MTX44* pOut, const VEC3& T) { return MTX44Translate(pOut, &T); }
inline MTX44* MTX44MultTranslate(MTX44* pOut, const MTX44& M, const VEC3& T) { return MTX44MultTranslate(pOut, &M, &T); }
inline MTX44* MTX44MultTranslate(MTX44* pOut, const VEC3& T, const MTX44& M) { return MTX44MultTranslate(pOut, &T, &M); }

}  // namespace math
}  // namespace nn

#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix44.ipp>
#include <nn/math/ARMv6/inline/math_Matrix44.ipp>
#endif

#pragma pop

#endif
