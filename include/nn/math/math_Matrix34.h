/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix34.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATRIX34_H_
#define NN_MATH_MATRIX34_H_

#include <cstring>
#include <nn/math/math_Config.h>
#include <nn/math/math_Vector3.h>
#include <nn/math/math_Vector4.h>
#include <nn/math/math_Quaternion.h>
#include <nn/math/ARMv6/math_Matrix34.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct MTX34;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for MTX34
   ------------------------------------------------------------------------ */
/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34CameraRotate(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotateDeg);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Copy(MTX34* pOut, const MTX34* p);

/*
  

  

  
 */
NN_MATH_INLINE MTX34* MTX34Identity(MTX34* pOut);

/*
  

  
  

  
 */
NN_FORCE_INLINE u32    MTX34Inverse(MTX34* pOut, const MTX34* p);

/*
  
  

  
  

  
 */
NN_FORCE_INLINE u32    MTX34InvTranspose(MTX34* pOut, const MTX34* p);

/*
  
  

  
  

  
 */
NN_MATH_INLINE u32 MTX34InvTranspose(MTX33* pOut, const MTX34* p);

/*
  

  

  
 */
NN_MATH_INLINE bool MTX34IsIdentity(const MTX34* p);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, f32 twistDeg, const VEC3* pTarget);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2);

/*
  

  
                
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Mult(MTX34* pOut, const MTX34* p, f32 f);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34MultArray(MTX34* pOut, const MTX34* p1, const MTX34* pSrc, s32 count);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34MultScale(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34MultTranslate(MTX34* pOut, const VEC3* pT, const MTX34* pM);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34MultTranslate(MTX34* pOut, const MTX34* pM, const VEC3* pT);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34RotAxisDeg(MTX34* pOut, const VEC3* pAxis, f32 fDeg);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34RotAxisDegPartially(MTX34* pOut, const VEC3* pAxis, f32 fDeg);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34RotAxisFIdx(MTX34* pOut, const VEC3* pAxis, f32 fIdx);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34RotAxisRad(MTX34* pOut, const VEC3* pAxis, f32 fRad);

/*
  
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34RotAxisRad_( MTX34* pOut, const VEC3 *pAxis, f32 fRad );

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34RotAxisRadPartially(MTX34* pOut, const VEC3* pAxis, f32 fRad);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34RotXYZDeg(MTX34* pOut, f32 fDegX, f32 fDegY, f32 fDegZ);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34RotXYZDegPartially(MTX34* pOut, f32 fDegX, f32 fDegY, f32 fDegZ);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34RotXYZFIdx(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34RotXYZRad(MTX34* pOut, f32 fRadX, f32 fRadY, f32 fRadZ);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34RotXYZRadPartially(MTX34* pOut, f32 fRadX, f32 fRadY, f32 fRadZ);

/*
  

  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34RotXYZTranslateFIdx(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, const VEC3* pT);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Scale(MTX34* pOut, const VEC3* pS);

/*
  

  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34ShadowProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);

/*
  

  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34ShadowProjectionOrtho(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);

/*
  

  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34ShadowProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 n, f32 f);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2);

/*
  

  
  
  
  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34TextureProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT);

/*
  

  
  
  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34TextureProjectionOrtho(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT);

/*
  

  
  
  
  
  
  
  

  
 */
NN_MATH_INLINE MTX34* MTX34TextureProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Translate(MTX34* pOut, const VEC3* pT);

/*
  

  

  
  

  
 */
NN_FORCE_INLINE MTX34* MTX34Transpose(MTX34* pOut, const MTX34* p);

/*
  

  

  
 */
NN_MATH_INLINE MTX34* MTX34Zero(MTX34* pOut);

/*  

*/

NN_FORCE_INLINE MTX34* QUATToMTX34(MTX34* pOut, const QUAT* pQ);
NN_FORCE_INLINE VEC3* VEC3Transform(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV);

// This will be implemented before long
//MTX34* MTX34Inv(MTX34* pOut, f32* pDet, const MTX34* p);
//MTX34* MTX34InvTranspose(MTX34* pOut, f32* pDet, const MTX34* p);
//f32 MTX34Det(const MTX34* p);

/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct MTX34_
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
        };
    #endif
        BaseData f;     //
        f32 m[3][4];    //
        f32 a[12];      //
        VEC4_ v[3];     //
    //
    };
};

/*
  
  
 */
class MTX34 : public MTX34_
{
public:
    static const int ROW_COUNT = 3; //
    static const int COLUMN_COUNT = 4; //

     //
    static const MTX34& Identity()
    {
        static const MTX34 identity(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f);

        return identity;
    }

    typedef MTX34 self_type; //
    typedef f32   value_type; //
public:
    //----------------------------------------
    //
    //

    //
    MTX34() {}

    //
    explicit MTX34(const f32* p) { (void)MTX34Copy(this, (MTX34*)p); }

    //
    MTX34(const MTX34& rhs) { (void)MTX34Copy(this, &rhs); }

    //
    explicit MTX34(const MTX33& rhs) { MTX33ToMTX34(this, &rhs); }

    //
    MTX34(f32 x00, f32 x01, f32 x02, f32 x03,
          f32 x10, f32 x11, f32 x12, f32 x13,
          f32 x20, f32 x21, f32 x22, f32 x23)
    {
        f._00 = x00; f._01 = x01; f._02 = x02; f._03 = x03;
        f._10 = x10; f._11 = x11; f._12 = x12; f._13 = x13;
        f._20 = x20; f._21 = x21; f._22 = x22; f._23 = x23;
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
    VEC3 GetColumn(int index) const
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, COLUMN_COUNT);
        VEC3 column;
        column.x = this->m[0][index];
        column.y = this->m[1][index];
        column.z = this->m[2][index];
        return column;
    }

    //
    void SetColumn(int index, const VEC3& column)
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, COLUMN_COUNT);
        this->m[0][index] = column.x;
        this->m[1][index] = column.y;
        this->m[2][index] = column.z;
    }
    //

    //----------------------------------------
    //
    //

    //
    self_type& operator += (const self_type& rhs) { return *MTX34Add(this, this, &rhs); }

    //
    self_type& operator -= (const self_type& rhs) { return *MTX34Sub(this, this, &rhs); }

    //
    self_type& operator *= (f32 f) { return *MTX34Mult(this, this, f); }

    //
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const
    {
        return MTX34(-f._00, -f._01, -f._02, -f._03,
                     -f._10, -f._11, -f._12, -f._13,
                     -f._20, -f._21, -f._22, -f._23);
    }

    //
    self_type operator + (const self_type& rhs) const { MTX34 tmp; return *MTX34Add(&tmp, this, &rhs); }

    //
    self_type operator - (const self_type& rhs) const { MTX34 tmp; return *MTX34Sub(&tmp, this, &rhs); }

    //
    self_type operator * (f32 f) const { MTX34 tmp; return *MTX34Mult(&tmp, this, f); }

    //
    self_type operator / (f32 f) const { return *this * (1.f / f); }

    //
    self_type& Transpose() { return *MTX34Transpose(this, this); }

    //

    //----------------------------------------
    //
    //

    //
    self_type& SetupIdentity() { return *MTX34Identity(this); }

    //
    //
    //
    //
    self_type& SetupScale(const VEC3& scale) { return *MTX34Scale(this, &scale); }

    //
    //
    //
    //
    self_type& SetupTranslate(const VEC3& translate)
    {
        return *MTX34Translate(this, &translate);
    }

    //
    //
    //
    //
    self_type& SetupRotateXyz(const VEC3& rotate)
    {
        return *MTX34RotXYZRad(this, rotate.x, rotate.y, rotate.z);
    }

    //
    //
    //
    //
    //
    self_type& SetupRotate(const VEC3& axis, f32 theta)
    {
        return *MTX34RotAxisRad(this, &axis, theta);
    }

    //
    //
    //
    self_type& SetupRotate(const QUAT& quaternion)
    {
        return *QUATToMTX34(this, &quaternion);
    }

    /*
      

      
      
      
     */
    self_type& SetupLookAt(const VEC3& camPos, const VEC3& camUp, const VEC3& target)
    {
        return *MTX34LookAt(this, &camPos, &camUp, &target);
    }

    /*
      

      
      
      
     */
    self_type& SetupLookAt(const VEC3& camPos, f32 twistDeg, const VEC3& target)
    {
        return *MTX34LookAt(this, &camPos, twistDeg, &target);
    }

    /*
      

      
      
     */
    self_type& SetupCameraRotate(const VEC3& camPos, const VEC3& camRotateDeg)
    {
        return *MTX34CameraRotate(this, &camPos, &camRotateDeg);
    }

    /*
      

      
      
      
      
      
      
      
      
      
     */
    self_type& SetupTextureProjectionFrustum(f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
    {
        return *MTX34TextureProjectionFrustum(this, l, r, b, t, n, scaleS, scaleT, translateS, translateT);
    }

    /*
      

      
      
      
      
      
      
     */
    self_type& SetupTextureProjectionFrustum(f32 fovyRad, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
    {
        return *MTX34TextureProjectionPerspective(this, fovyRad, aspect, scaleS, scaleT, translateS, translateT);
    }

    /*
      

      
      
      
      
      
      
      
      
      
     */
    self_type& SetupTextureProjectionFrustum(f32 l, f32 r, f32 b, f32 t, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
    {
        return *MTX34TextureProjectionOrtho(this, l, r, b, t, scaleS, scaleT, translateS, translateT);
    }

    //

    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX34)) == 0; }

    //
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX34)) != 0; }

    //
    bool IsIdentity() const { return MTX34IsIdentity(this); }
    //

    //
    void Report(bool bNewline = true, const char* name = NULL) const;

private:
    typedef void (self_type::*UnspecifiedBoolType)() const;
    operator UnspecifiedBoolType() const;
    operator UnspecifiedBoolType();
};

//
//

//
typedef class MTX34 Matrix34;

//

//
inline MTX34 operator * (f32 f, const MTX34& rhs)
{
    MTX34 tmp;
    (void)MTX34Mult(&tmp, &rhs, f);
    return tmp;
}

NN_MATH_INLINE MTX34*
MTX34RotXYZRad(MTX34* pOut, f32 fRadX, f32 fRadY, f32 fRadZ)
{
    return MTX34RotXYZFIdx(pOut, NN_MATH_RAD_TO_FIDX(fRadX), NN_MATH_RAD_TO_FIDX(fRadY), NN_MATH_RAD_TO_FIDX(fRadZ));
}

NN_FORCE_INLINE MTX34*
MTX34RotXYZRadPartially(MTX34* pOut, f32 fRadX, f32 fRadY, f32 fRadZ)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ROTXYZFIDX_CONFIG == D_ORG)
        return ARMv6::MTX34RotXYZFIdxC(pOut, NN_MATH_RAD_TO_FIDX(fRadX), NN_MATH_RAD_TO_FIDX(fRadY), NN_MATH_RAD_TO_FIDX(fRadZ), false);
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_C)
        return ARMv6::MTX34RotXYZFIdxC_FAST(pOut, NN_MATH_RAD_TO_FIDX(fRadX), NN_MATH_RAD_TO_FIDX(fRadY), NN_MATH_RAD_TO_FIDX(fRadZ), false);
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_ASM)
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_MATH_INLINE MTX34*
MTX34RotXYZDeg(MTX34* pOut, f32 fDegX, f32 fDegY, f32 fDegZ)
{
    return MTX34RotXYZFIdx(pOut, NN_MATH_DEG_TO_FIDX(fDegX), NN_MATH_DEG_TO_FIDX(fDegY), NN_MATH_DEG_TO_FIDX(fDegZ));
}

NN_FORCE_INLINE MTX34*
MTX34RotXYZDegPartially(MTX34* pOut, f32 fDegX, f32 fDegY, f32 fDegZ)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ROTXYZFIDX_CONFIG == D_ORG)
        return ARMv6::MTX34RotXYZFIdxC(pOut, NN_MATH_DEG_TO_FIDX(fDegX), NN_MATH_DEG_TO_FIDX(fDegY), NN_MATH_DEG_TO_FIDX(fDegZ), false);
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_C)
        return ARMv6::MTX34RotXYZFIdxC_FAST(pOut, NN_MATH_DEG_TO_FIDX(fDegX), NN_MATH_DEG_TO_FIDX(fDegY), NN_MATH_DEG_TO_FIDX(fDegZ), false);
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_ASM)
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_MATH_INLINE MTX34*
MTX34RotAxisRad(MTX34* pOut, const VEC3* pAxis, f32 fRad)
{
    return MTX34RotAxisFIdx(pOut, pAxis, NN_MATH_RAD_TO_FIDX(fRad));
}

NN_FORCE_INLINE MTX34*
MTX34RotAxisRadPartially(MTX34* pOut, const VEC3* pAxis, f32 fRad)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ROTAXISRAD__CONFIG == D_ORG)
        return ARMv6::MTX34RotAxisRad_C(pOut, pAxis, fRad, false);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_C)
        return ARMv6::MTX34RotAxisRad_C_FAST(pOut, pAxis, fRad, false);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_ASM)
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_C_ALGO)
        return ARMv6::MTX34RotAxisRad_C_FAST(pOut, pAxis, fRad, false);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_MATH_INLINE MTX34*
MTX34RotAxisDeg(MTX34* pOut, const VEC3* pAxis, f32 fDeg)
{
    return MTX34RotAxisFIdx(pOut, pAxis, NN_MATH_DEG_TO_FIDX(fDeg));
}


NN_FORCE_INLINE MTX34*
MTX34RotAxisDegPartially(MTX34* pOut, const VEC3* pAxis, f32 fDeg)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ROTAXISRAD__CONFIG == D_ORG)
        return ARMv6::MTX34RotAxisRad_C(pOut, pAxis, NN_MATH_DEG_TO_RAD(fDeg), false);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_C)
        return ARMv6::MTX34RotAxisRad_C_FAST(pOut, pAxis, NN_MATH_DEG_TO_RAD(fDeg), false);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_ASM)
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_C_ALGO)
        return ARMv6::MTX34RotAxisRad_C_FAST(pOut, pAxis, NN_MATH_DEG_TO_RAD(fDeg), false);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34Copy(MTX34* pOut, const MTX34* p)
{

#if defined( NN_HARDWARE_CTR )
    #if (MTX34COPY_CONFIG == D_ORG)
        return ARMv6::MTX34CopyC( pOut, p );
    #elif (MTX34COPY_CONFIG == D_FAST_C)
    #elif (MTX34COPY_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34CopyAsm( pOut, p );
    #elif (MTX34COPY_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34COPY_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MULT_34_CONFIG == D_ORG)
        return ARMv6::MTX34MultC( pOut, p1, p2 );
    #elif (MTX34MULT_34_CONFIG == D_FAST_C)
    #elif (MTX34MULT_34_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MultAsm( pOut, p1, p2 );
    #elif (MTX34MULT_34_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MULT_34_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p, f32 f)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MULT_F32_CONFIG == D_ORG)
        return ARMv6::MTX34MultC( pOut, p, f );
    #elif (MTX34MULT_F32_CONFIG == D_FAST_C)
    #elif (MTX34MULT_F32_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MultAsm( pOut, p, f );
    #elif (MTX34MULT_F32_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MULT_F32_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ADD_CONFIG == D_ORG)
        return ARMv6::MTX34AddC( pOut, p1, p2 );
    #elif (MTX34ADD_CONFIG == D_FAST_C)
    #elif (MTX34ADD_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34AddAsm( pOut, p1, p2 );
    #elif (MTX34ADD_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34ADD_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34CameraRotate(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotateDeg)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34CAMERAROTATE_CONFIG == D_ORG)
        return ARMv6::MTX34CameraRotateC(pOut, pCamPos, pCamRotateDeg);
    #elif (MTX34CAMERAROTATE_CONFIG == D_FAST_C)
        return ARMv6::MTX34CameraRotateC_FAST(pOut, pCamPos, pCamRotateDeg);
    #elif (MTX34CAMERAROTATE_CONFIG == D_FAST_ASM)
    #elif (MTX34CAMERAROTATE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34CAMERAROTATE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE u32
MTX34Inverse(MTX34* pOut, const MTX34* p)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34INVERSE_CONFIG == D_ORG)
        return ARMv6::MTX34InverseC( pOut, p );
    #elif (MTX34INVERSE_CONFIG == D_FAST_C)
    #elif (MTX34INVERSE_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34InverseAsm( pOut, p);
    #elif (MTX34INVERSE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34INVERSE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE u32
MTX34InvTranspose(MTX34* pOut, const MTX34* __restrict p)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34INVTRANSPOSE_34TO34_CONFIG == D_ORG)
        return ARMv6::MTX34InvTransposeC( pOut, p );
    #elif (MTX34INVTRANSPOSE_34TO34_CONFIG == D_FAST_C)
    #elif (MTX34INVTRANSPOSE_34TO34_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34InvTransposeAsm( pOut, p);
    #elif (MTX34INVTRANSPOSE_34TO34_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34INVTRANSPOSE_34TO34_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34LOOKAT_VEC3_CONFIG == D_ORG)
        return ARMv6::MTX34LookAtC(pOut, pCamPos, pCamUp, pTarget);
    #elif (MTX34LOOKAT_VEC3_CONFIG == D_FAST_C)
        return ARMv6::MTX34LookAtC_FAST(pOut, pCamPos, pCamUp, pTarget);
    #elif (MTX34LOOKAT_VEC3_CONFIG == D_FAST_ASM)
    #elif (MTX34LOOKAT_VEC3_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34LOOKAT_VEC3_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}


NN_FORCE_INLINE MTX34*
MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, f32 twistDeg, const VEC3* pTarget)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34LOOKAT_F32_CONFIG == D_ORG)
        return ARMv6::MTX34LookAtC(pOut, pCamPos, twistDeg, pTarget);
    #elif (MTX34LOOKAT_F32_CONFIG == D_FAST_C)
        return ARMv6::MTX34LookAtC_FAST(pOut, pCamPos, twistDeg, pTarget);
    #elif (MTX34LOOKAT_F32_CONFIG == D_FAST_ASM)
    #elif (MTX34LOOKAT_F32_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34LOOKAT_F32_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )


}

NN_FORCE_INLINE MTX34*
MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MADD_CONFIG == D_ORG)
        return ARMv6::MTX34MAddC( pOut, t, p1, p2 );
    #elif (MTX34MADD_CONFIG == D_FAST_C)
    #elif (MTX34MADD_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MAddAsm( pOut, t, p1, p2 );
    #elif (MTX34MADD_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MADD_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MULTSCALE_RIGHT_CONFIG == D_ORG)
        return ARMv6::MTX34MultScaleC( pOut, pM, pS );
    #elif (MTX34MULTSCALE_RIGHT_CONFIG == D_FAST_C)
    #elif (MTX34MULTSCALE_RIGHT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MultScaleAsm( pOut, pM, pS );
    #elif (MTX34MULTSCALE_RIGHT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MULTSCALE_RIGHT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MULTSCALE_LEFT_CONFIG == D_ORG)
        return ARMv6::MTX34MultScaleC( pOut, pS, pM );
    #elif (MTX34MULTSCALE_LEFT_CONFIG == D_FAST_C)
    #elif (MTX34MULTSCALE_LEFT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MultScaleAsm( pOut, pS, pM );
    #elif (MTX34MULTSCALE_LEFT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MULTSCALE_LEFT_CONFIG == D_FAST_ASM_ALGO)
    #endif
    #else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34MultTranslate(MTX34* pOut, const VEC3* pT, const MTX34* pM)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MULTTRANSLATE_LEFT_CONFIG == D_ORG)
        return ARMv6::MTX34MultTranslateC( pOut, pT, pM );
    #elif (MTX34MULTTRANSLATE_LEFT_CONFIG == D_FAST_C)
    #elif (MTX34MULTTRANSLATE_LEFT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MultTranslateAsm( pOut, pT, pM );
    #elif (MTX34MULTTRANSLATE_LEFT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MULTTRANSLATE_LEFT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34MultTranslate(MTX34* pOut, const MTX34* pM, const VEC3* pT)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34MULTTRANSLATE_RIGHT_CONFIG == D_ORG)
        return ARMv6::MTX34MultTranslateC( pOut, pM, pT );
    #elif (MTX34MULTTRANSLATE_RIGHT_CONFIG == D_FAST_C)
    #elif (MTX34MULTTRANSLATE_RIGHT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34MultTranslateAsm( pOut, pM, pT );
    #elif (MTX34MULTTRANSLATE_RIGHT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34MULTTRANSLATE_RIGHT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34RotAxisRad_( MTX34* pOut, const VEC3 *pAxis, f32 fRad )
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ROTAXISRAD__CONFIG == D_ORG)
        return ARMv6::MTX34RotAxisRad_C(pOut, pAxis, fRad);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_C)
        return ARMv6::MTX34RotAxisRad_C_FAST(pOut, pAxis, fRad);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_ASM)
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_C_ALGO)
        return ARMv6::MTX34RotAxisRad_C_FAST(pOut, pAxis, fRad);
    #elif (MTX34ROTAXISRAD__CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34RotXYZFIdx(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34ROTXYZFIDX_CONFIG == D_ORG)
        return ARMv6::MTX34RotXYZFIdxC(pOut, fIdxX, fIdxY, fIdxZ);
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_C)
        return ARMv6::MTX34RotXYZFIdxC_FAST(pOut, fIdxX, fIdxY, fIdxZ);
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_ASM)
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34ROTXYZFIDX_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_FORCE_INLINE MTX34*
MTX34Scale(MTX34* pOut, const VEC3* pS)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34SCALE_CONFIG == D_ORG)
        return ARMv6::MTX34ScaleC(pOut, pS);
    #elif (MTX34SCALE_CONFIG == D_FAST_C)
        return ARMv6::MTX34ScaleC_FAST(pOut, pS);
    #elif (MTX34SCALE_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34ScaleAsm(pOut, pS);
    #elif (MTX34SCALE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34SCALE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34Translate(MTX34* pOut, const VEC3* pT)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34TRANSLATE_CONFIG == D_ORG)
        return ARMv6::MTX34TranslateC(pOut, pT);
    #elif (MTX34TRANSLATE_CONFIG == D_FAST_C)
        return ARMv6::MTX34TranslateC_FAST(pOut, pT);
    #elif (MTX34TRANSLATE_CONFIG == D_FAST_ASM)
    #elif (MTX34TRANSLATE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34TRANSLATE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
MTX34Transpose(MTX34* pOut, const MTX34* p)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34TRANSPOSE_34TO34_CONFIG == D_ORG)
        return ARMv6::MTX34TransposeC(pOut, p);
    #elif (MTX34TRANSPOSE_34TO34_CONFIG == D_FAST_C)
    #elif (MTX34TRANSPOSE_34TO34_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34TransposeAsm(pOut, p);
    #elif (MTX34TRANSPOSE_34TO34_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34TRANSPOSE_34TO34_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE VEC3*
VEC3Transform(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV)
{
#if defined( NN_HARDWARE_CTR )
    #if (VEC3TRANSFORM_34XVEC3_CONFIG == D_ORG)
        return ARMv6::VEC3TransformC(pOut, pM, pV);
    #elif (VEC3TRANSFORM_34XVEC3_CONFIG == D_FAST_C)
    #elif (VEC3TRANSFORM_34XVEC3_CONFIG == D_FAST_ASM)
        return ARMv6::VEC3TransformAsm(pOut, pM, pV);
    #elif (VEC3TRANSFORM_34XVEC3_CONFIG == D_FAST_C_ALGO)
    #elif (VEC3TRANSFORM_34XVEC3_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

}  // namespace math
}  // namespace nn

namespace nn { 
namespace math {

//Overload referencing the -- const argument

inline bool MTX34IsIdentity(const MTX34& m) { return MTX34IsIdentity( &m ); }

inline MTX34* MTX34Add(MTX34* pOut, const MTX34& m1, const MTX34& m2) { return MTX34Add( pOut, &m1, &m2 ); }
inline MTX34* MTX34Sub(MTX34* pOut, const MTX34& m1, const MTX34& m2) { return MTX34Sub( pOut, &m1, &m2 ); }
inline MTX34* MTX34Mult(MTX34* pOut, const MTX34& m, f32 f) { return MTX34Mult( pOut, &m, f ); }
inline MTX34* MTX34Mult(MTX34* pOut, const MTX34& m1, const MTX34& m2) { return MTX34Mult( pOut, &m1, &m2 ); }
inline MTX34* MTX34MAdd(MTX34* pOut, f32 t, const MTX34& m1, const MTX34& m2) { return MTX34MAdd( pOut, t, &m1, &m2 ); }

inline MTX34* MTX34Copy(MTX34* pOut, const MTX34& m) { return MTX34Copy( pOut, &m ); }
inline MTX34* MTX34MultArray(MTX34* pOut, const MTX34& m1, const MTX34* pSrc, s32 count) { return MTX34MultArray( pOut, m1, pSrc, count ); }
inline u32    MTX34Inverse(MTX34* pOut, const MTX34& m) { return MTX34Inverse( pOut, &m ); }
inline MTX34* MTX34Transpose(MTX34* pOut, const MTX34& m) { return MTX34Transpose( pOut, &m ); }
inline u32    MTX34InvTranspose(MTX34* pOut, const MTX34& m) { return MTX34InvTranspose( pOut, &m ); }
inline u32    MTX34InvTranspose(MTX33* pOut, const MTX34& m) { return MTX34InvTranspose( pOut, &m ); }

inline MTX34* MTX34LookAt(MTX34* pOut, const VEC3& vCamPos, const VEC3& vCamUp, const VEC3& vTarget) { return MTX34LookAt( pOut, &vCamPos, &vCamUp, &vTarget ); }
inline MTX34* MTX34LookAt(MTX34* pOut, const VEC3& vCamPos, f32 twistDeg, const VEC3& vTarget) { return MTX34LookAt( pOut, &vCamPos, twistDeg, &vTarget ); }
inline MTX34* MTX34CameraRotate(MTX34* pOut, const VEC3& vCamPos, const VEC3& vCamRotateDeg) { return MTX34CameraRotate( pOut, &vCamPos, &vCamRotateDeg ); }

inline MTX34* MTX34RotXYZTranslateFIdx(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, const VEC3& vT) { return MTX34RotXYZTranslateFIdx( pOut, fIdxX, fIdxY, fIdxZ, &vT ); }
inline MTX34* MTX34RotAxisFIdx(MTX34* pOut, const VEC3& vAxis, f32 fIdx) { return MTX34RotAxisFIdx( pOut, &vAxis, fIdx ); }
inline MTX34* MTX34RotAxisRad(MTX34* pOut, const VEC3& vAxis, f32 fRad) { return MTX34RotAxisRad( pOut, &vAxis, fRad ); }
inline MTX34* MTX34RotAxisDeg(MTX34* pOut, const VEC3& vAxis, f32 fDeg) { return MTX34RotAxisDeg( pOut, &vAxis, fDeg ); }

inline MTX34* MTX34Scale(MTX34* pOut, const VEC3& vS) { return MTX34Scale( pOut, &vS ); }
inline MTX34* MTX34MultScale(MTX34* pOut, const MTX34& m, const VEC3& vS) { return MTX34MultScale( pOut, &m, &vS ); }
inline MTX34* MTX34MultScale(MTX34* pOut, const VEC3& vS, const MTX34& m) { return MTX34MultScale( pOut, &vS, &m ); }

inline MTX34* MTX34Translate(MTX34* pOut, const VEC3& vT) { return MTX34Translate( pOut, &vT ); }
inline MTX34* MTX34MultTranslate(MTX34* pOut, const MTX34& m, const VEC3& vT) { return MTX34MultTranslate( pOut, &m, &vT ); }
inline MTX34* MTX34MultTranslate(MTX34* pOut, const VEC3& vT, const MTX34& m) { return MTX34MultTranslate( pOut, &vT, &m ); }

}  // namespace math
}  // namespace nn

#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix34.ipp>
#include <nn/math/ARMv6/inline/math_Matrix34.ipp>
#endif

#pragma pop

#endif
