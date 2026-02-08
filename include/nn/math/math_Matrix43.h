/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix43.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATRIX43_H_
#define NN_MATH_MATRIX43_H_

#include <cstring>
#include <nn/math/math_Config.h>

#pragma push
#pragma Otime

namespace nn { 
namespace math {

struct MTX43;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for MTX43
   ------------------------------------------------------------------------ */
/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX43* MTX43Add(MTX43* pOut, const MTX43* p1, const MTX43* p2);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX43* MTX43Copy(MTX43* pOut, const MTX43* p);

/*
  

  

  
 */
NN_MATH_INLINE MTX43* MTX43Identity(MTX43* pOut);

/*
  

  

  
 */
NN_MATH_INLINE bool   MTX43IsIdentity(const MTX43* p);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX43* MTX43Mult(MTX43* pOut, const MTX43* p1, const MTX43* p2);

/*
  

  
  
  

  
 */
NN_FORCE_INLINE MTX43* MTX43Mult(MTX43* pOut, const MTX43* p, f32 f);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX43* MTX43Sub(MTX43* pOut, const MTX43* p1, const MTX43* p2);

/*
  

  

  
 */
NN_MATH_INLINE MTX43* MTX43Zero(MTX43* pOut);
/*  

*/
/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct MTX43_
{
    //
    struct BaseData
    {
        f32 _00;    //
        f32 _01;    //
        f32 _02;    //
        f32 _10;    //
        f32 _11;    //
        f32 _12;    //
        f32 _20;    //
        f32 _21;    //
        f32 _22;    //
        f32 _30;    //
        f32 _31;    //
        f32 _32;    //
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
            f32 _00, _01, _02;
            f32 _10, _11, _12;
            f32 _20, _21, _22;
            f32 _30, _31, _32;
        };
    #endif
        BaseData f;     //
        f32 m[4][3];    //
        f32 a[12];      //
        VEC3_ v[4];     //
    //
    };
};

/*
   
   
 */
class MTX43 : public MTX43_
{
public:
    static const int ROW_COUNT = 4; //
    static const int COLUMN_COUNT = 3; //

    //
    static const MTX43& Identity()
    {
        static const MTX43 identity(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f);
        
        return identity;
    }
    typedef MTX43 self_type; //
    typedef f32   value_type; //

public:
    //----------------------------------------
    //
    //

    //
    MTX43() {}
    
    //
    explicit MTX43(const f32* p) { (void)MTX43Copy(this, (MTX43*)p); }
    
    //
    MTX43(f32 x00, f32 x01, f32 x02,
          f32 x10, f32 x11, f32 x12,
          f32 x20, f32 x21, f32 x22,
          f32 x30, f32 x31, f32 x32)
    {
        f._00 = x00; f._01 = x01; f._02 = x02;
        f._10 = x10; f._11 = x11; f._12 = x12;
        f._20 = x20; f._21 = x21; f._22 = x22;
        f._30 = x30; f._31 = x31; f._32 = x32;
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
    VEC3& GetRow(int index)
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, ROW_COUNT);
        return *reinterpret_cast<VEC3*>(&this->v[index]);
    }
    
    //
    const VEC3& GetRow(int index) const
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, ROW_COUNT);
        return *reinterpret_cast<const VEC3*>(&this->v[index]);
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
    self_type& operator += (const self_type& rhs) { return *MTX43Add(this, this, &rhs); }

    //
    self_type& operator -= (const self_type& rhs) { return *MTX43Sub(this, this, &rhs); }
    
    //
    self_type& operator *= (const self_type& rhs) { return *MTX43Mult(this, this, &rhs); }

    //
    self_type& operator *= (f32 f) { return *MTX43Mult(this, this, f); }

    //
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }
    
    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const 
        {
            return MTX43(-f._00, -f._01, -f._02,
                         -f._10, -f._11, -f._12,
                         -f._20, -f._21, -f._22,
                         -f._30, -f._31, -f._32);
        }

    //
    self_type operator + (const self_type& rhs) const { MTX43 tmp; return *MTX43Add(&tmp, this, &rhs); }

    //
    self_type operator - (const self_type& rhs) const { MTX43 tmp; return *MTX43Add(&tmp, this, &rhs); }

    //
    self_type operator * (f32 f) const { MTX43 tmp; return *MTX43Mult(&tmp, this, f); }

    //
    self_type operator / (f32 f) const { return *this * (1.f / f); }

    //

    //----------------------------------------
    //
    //
    
    //
    self_type& SetupIdentity() { return *MTX43Identity(this); }
    
    //
    
    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX43)) == 0; }

    //
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX43)) != 0; }

    //
    bool IsIdentity() const { return MTX43IsIdentity(this); }

    //

    //
    void Report(bool bNewline = true, const char* name = NULL) const;

private:
    typedef void (self_type::*UnspecifiedBoolType)() const;
    operator UnspecifiedBoolType() const;
    operator UnspecifiedBoolType();
};
#include <nn/math/ARMv6/math_Matrix43.h>

NN_FORCE_INLINE MTX43* 
MTX43Add(MTX43* pOut, const MTX43* p1, const MTX43* p2)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX43ADD_CONFIG == D_ORG)
        return ARMv6::MTX43AddC(pOut, p1, p2);
    #elif (MTX43ADD_CONFIG == D_FAST_C)
    #elif (MTX43ADD_CONFIG == D_FAST_ASM)
        return ARMv6::MTX43AddAsm(pOut, p1, p2);
    #elif (MTX43ADD_CONFIG == D_FAST_C_ALGO)
    #elif (MTX43ADD_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_FORCE_INLINE MTX43*
MTX43Copy(MTX43* pOut, const MTX43* p) 
{ 
#if defined( NN_HARDWARE_CTR )
    #if (MTX43COPY_CONFIG == D_ORG)
        return ARMv6::MTX43CopyC(pOut, p);
    #elif (MTX43COPY_CONFIG == D_FAST_C)
    #elif (MTX43COPY_CONFIG == D_FAST_ASM)
        return ARMv6::MTX43CopyAsm(pOut, p);
    #elif (MTX43COPY_CONFIG == D_FAST_C_ALGO)
    #elif (MTX43COPY_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )

}

NN_FORCE_INLINE MTX43*
MTX43Mult(MTX43* pOut, const MTX43* p1, const MTX43* p2) 
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX43MULT_43_CONFIG == D_ORG)
        return ARMv6::MTX43MultC(pOut, p1, p2);
    #elif (MTX43MULT_43_CONFIG == D_FAST_C)
    #elif (MTX43MULT_43_CONFIG == D_FAST_ASM)
        return ARMv6::MTX43MultAsm(pOut, p1, p2);
    #elif (MTX43MULT_43_CONFIG == D_FAST_C_ALGO)
    #elif (MTX43MULT_43_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX43* 
MTX43Mult(MTX43* pOut, const MTX43* p, f32 f)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX43MULT_F32_CONFIG == D_ORG)
        return ARMv6::MTX43MultC(pOut, p, f);
    #elif (MTX43MULT_F32_CONFIG == D_FAST_C)
    #elif (MTX43MULT_F32_CONFIG == D_FAST_ASM)
        return ARMv6::MTX43MultAsm(pOut, p, f);
    #elif (MTX43MULT_F32_CONFIG == D_FAST_C_ALGO)
    #elif (MTX43MULT_F32_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

//
//

//
typedef class MTX43 Matrix43;

//

//Overload referencing the -- const argument
inline bool   MTX44IsIdentity(const MTX43& m) { return MTX43IsIdentity( &m ); }
inline MTX43* MTX43Copy(MTX43* pOut, const MTX43& m) { return MTX43Copy( pOut, &m ); }
inline MTX43* MTX43Add(MTX43* pOut, const MTX43& m1, const MTX43& m2) { return MTX43Add( pOut, &m1, &m2 ); }
inline MTX43* MTX43Sub(MTX43* pOut, const MTX43& m1, const MTX43& m2) { return MTX43Sub( pOut, &m1, &m2 ); }
inline MTX43* MTX43Mult(MTX43* pOut, const MTX43& m1, const MTX43& m2) { return MTX43Mult( pOut, &m1, &m2 ); }
inline MTX43* MTX43Mult(MTX43* pOut, const MTX43& m, f32 f) { return MTX43Mult( pOut, &m, f); }

}  // namespace math
}  // namespace nn


#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix43.ipp>
#include <nn/math/ARMv6/inline/math_Matrix43.ipp>
#endif

#pragma pop

#endif
