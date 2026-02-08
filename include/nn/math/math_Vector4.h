/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector4.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_VECTOR4_H_
#define NN_MATH_VECTOR4_H_

#include <cstring>
#include <nn/math/math_Config.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct VEC4;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for VEC4
   ------------------------------------------------------------------------ */
/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE f32   VEC4DistSq(const VEC4* p1, const VEC4* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE f32   VEC4Dot(const VEC4* p1, const VEC4* p2);

/*
  

  

  
 */
NN_MATH_INLINE bool VEC4IsZero(const VEC4* p);

/*
  

  

  
 */
NN_MATH_INLINE bool VEC4IsZeroWOne(const VEC4* p);

/*
  

  

  
 */
NN_MATH_INLINE f32   VEC4Len(const VEC4* p);

/*
  

  

  
 */
NN_MATH_INLINE f32   VEC4LenSq(const VEC4* p);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Lerp(VEC4* pOut, const VEC4* p1, const VEC4* p2, f32 t);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Mult(VEC4* pOut, const VEC4* p1, const VEC4* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Normalize(VEC4* pOut, const VEC4* p);

/*
  
                

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4SafeNormalize(VEC4* pOut, const VEC4* p, const VEC4& alt);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2);

/*  

*/

/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct VEC4_
{
    f32 x;  //
    f32 y;  //
    f32 z;  //
    f32 w;  //
};


/*
    
    
   */
class VEC4 : public VEC4_
{
public:
    static const int DIMENSION = 4; //

    //
    static const VEC4& Zero()
    {
        static const VEC4 zero(0.0f, 0.0f, 0.0f, 0.0f);

        return zero;
    }

    //
    static const VEC4& ZeroWOne()
    {
        static const VEC4 zero(0.0f, 0.0f, 0.0f, 1.0f);

        return zero;
    }

    //
    static const VEC4& One()
    {
        static const VEC4 one(1.0f, 1.0f, 1.0f, 1.0f);

        return one;
    }

    typedef VEC4 self_type; //
    typedef f32  value_type; //
public:

    //----------------------------------------
    //
    //

    //
    VEC4() {}
    //
    explicit VEC4(const f32* p) { x = p[0]; y = p[1]; z = p[2]; w = p[3]; }
    //
    VEC4(const VEC4_& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    //
    VEC4(f32 fx, f32 fy, f32 fz, f32 fw) { x = fx; y = fy; z = fz; w = fw; }
    //
    explicit VEC4(const VEC3& v) { x = v.x; y = v.y; z = v.z; w = 0.0f; }

    //

    //----------------------------------------
    //
    //

    //
    operator f32*() { return &x; }

    //
    operator const f32*() const { return &x; }

    //

    //----------------------------------------
    //
    //

    //
    self_type& operator += (const self_type& rhs) { (void)VEC4Add(this, this, &rhs); return *this; }

    //
    self_type& operator -= (const self_type& rhs) { (void)VEC4Sub(this, this, &rhs); return *this; }

    //
    self_type& operator *= (f32 f) { (void)VEC4Scale(this, this, f); return *this; }

    //
    self_type& operator *= (const self_type& rhs) { (void)VEC4Mult(this, this, &rhs); return *this; }

    //
    self_type& operator /= (f32 f) { (void)VEC4Scale(this, this, 1/f); return *this; }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const { return self_type(-x, -y, -z, -w); }

    //
    self_type operator + (const self_type& rhs) const { VEC4 tmp; (void)VEC4Add(&tmp, this, &rhs); return tmp; }

    //
    self_type operator - (const self_type& rhs) const { VEC4 tmp; (void)VEC4Sub(&tmp, this, &rhs); return tmp; }

    //
    self_type operator * (f32 f) const { VEC4 tmp; (void)VEC4Scale(&tmp, this, f); return tmp; }

    //
    self_type operator / (f32 f) const { f32 r = 1.f / f; return operator*(r); }

    //
    //
    //
    //
    //
    //
    self_type& Lerp(const VEC4& lhs, const VEC4& rhs, f32 t)
    {
        return *VEC4Lerp(this, &lhs, &rhs, t);
    }

    //
    //
    //
    //
    f32 Dot(const VEC4& vec) const
    {
        return VEC4Dot(this, &vec);
    }

    //
    //
    //
    f32 LenSq() const { return VEC4LenSq(this); }

    //
    f32 LengthSquare() const { return VEC4LenSq(this); }

    //
    f32 Length() const { return VEC4Len(this); }

    //
    self_type& Normalize()
    {
        return *VEC4Normalize(this, this);
    }

    //
    //
    //
    //
    self_type& SafeNormalize(const VEC4& alt)
    {
        return *VEC4SafeNormalize(this, this, alt);
    }

    //
    //
    //
    f32 DistanceSquare(const VEC4& vec)
    {
        return VEC4DistSq(this, &vec);
    }

    //
    //
    //
    //
    self_type& Maximize(const VEC4& lhs, const VEC4& rhs)
    {
        return *VEC4Maximize(this, &lhs, &rhs);
    }

    //
    //
    //
    //
    self_type& Minimize(const VEC4& lhs, const VEC4& rhs)
    {
        return *VEC4Minimize(this, &lhs, &rhs);
    }

    //

    //----------------------------------------
    //
    //

    //
    void Set(f32 fx, f32 fy, f32 fz, f32 fw) { x = fx; y = fy; z = fz; w = fw; }

    //

    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }

    //
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w; }

    //
    bool IsZero() const { return VEC4IsZero(this); }

    //
    bool IsZeroWOne() const { return VEC4IsZeroWOne(this); }
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
typedef class VEC4 Vector4;

//

inline VEC4
operator * (f32 f, const VEC4& rhs) { VEC4 tmp; (void)VEC4Scale(&tmp, &rhs, f); return tmp; }


}  // namespace math
}  // namespace nn


#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Vector4.ipp>
#endif

namespace nn {
namespace math {

//Overload referencing the -- const argument
inline bool VEC4IsZero(const VEC4& v){ return VEC4IsZero( &v ); }
inline bool VEC4IsZeroWOne(const VEC4& v){ return VEC4IsZeroWOne( &v ); }
inline VEC4* VEC4Add(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Add( pOut, &v1, &v2 ); }
inline VEC4* VEC4Sub(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Sub( pOut, &v1, &v2 ); }
inline VEC4* VEC4Mult(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Mult( pOut, &v1, &v2 ); }
inline VEC4* VEC4Scale(VEC4* pOut, const VEC4& v, f32 scale) { return VEC4Scale( pOut, &v, scale); }
inline VEC4* VEC4Lerp(VEC4* pOut, const VEC4& v1, const VEC4& v2, f32 t) { return VEC4Lerp( pOut, &v1, &v2, t ); }
inline f32   VEC4Dot(const VEC4& v1, const VEC4& v2) { return VEC4Dot( &v1, &v2 ); }
inline f32   VEC4LenSq(const VEC4& v) { return VEC4LenSq( &v ); }
inline f32   VEC4Len(const VEC4& v) { return VEC4Len( &v ); }
inline VEC4* VEC4Normalize(VEC4* pOut, const VEC4& v) { return VEC4Normalize( pOut, &v ); }
inline VEC4* VEC4SafeNormalize(VEC4* pOut, const VEC4& v, const VEC4& alt) { return VEC4SafeNormalize( pOut, &v, alt ); }
inline f32   VEC4DistSq(const VEC4& v1, const VEC4& v2) { return VEC4DistSq( &v1, &v2 ); }
inline VEC4* VEC4Maximize(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Maximize( pOut, &v1, &v2 ); }
inline VEC4* VEC4Minimize(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Minimize( pOut, &v1, &v2 ); }


}  // namespace math
}  // namespace nn

#pragma pop

#endif
