/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector2.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_VECTOR2_H_
#define NN_MATH_VECTOR2_H_

#include <cstring>
#include <nn/math/math_Config.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct VEC2;
struct MTX23;

/* Please see man pages for details 
    
    
*/
/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Add(VEC2* pOut, const VEC2* p1, const VEC2* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE f32 VEC2DistSq(const VEC2* p1, const VEC2* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE f32 VEC2Dot(const VEC2* p1, const VEC2* p2);

/*
  

  

  
 */
NN_MATH_INLINE bool VEC2IsZero(const VEC2* p);

/*
  

  

  
 */
NN_MATH_INLINE f32 VEC2Len(const VEC2* p);

/*
  

  

  
 */
NN_MATH_INLINE f32 VEC2LenSq(const VEC2* p);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Lerp(VEC2* pOut, const VEC2* p1, const VEC2* p2, f32 t);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Mult(VEC2* pOut, const VEC2* p1, const VEC2* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Normalize(VEC2* pOut, const VEC2* p);

/*
  
                

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2SafeNormalize(VEC2* pOut, const VEC2* p, const VEC2& alt);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Scale(VEC2* pOut, const VEC2* p, f32 scale);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Sub(VEC2* pOut, const VEC2* p1, const VEC2* p2);

/*  

*/

NN_MATH_INLINE VEC2* VEC2Transform(VEC2* pOut, const MTX23* pM, const VEC2* pV);

/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct VEC2_
{
    f32 x;  //
    f32 y;  //
};

#pragma diag_suppress 2530
/*
    
    
   */
class VEC2 : public VEC2_
{
public:
    static const int DIMENSION = 2; //

    //
    static const VEC2& Zero()
    {
        static const VEC2 zero(0.0f, 0.0f);

        return zero;
    }

    //
    static const VEC2& One()
    {
        static const VEC2 one(1.0f, 1.0f);

        return one;
    }

    typedef VEC2 self_type; //
    typedef f32  value_type; //
public:

    //----------------------------------------
    //
    //

    //
    VEC2() {}
    //
    explicit VEC2(const f32* p) { x = p[0]; y = p[1]; }
    //
    VEC2(const VEC2_& v) { x = v.x; y = v.y; }
    //
    VEC2(f32 fx, f32 fy) { x = fx; y = fy; }

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
    self_type& operator += (const self_type& rhs) { x += rhs.x; y += rhs.y; return *this; }

    //
    self_type& operator -= (const self_type& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    //
    self_type& operator *= (f32 f) { x *= f; y *= f; return *this; }

    //
    self_type& operator *= (const self_type& rhs) { x *= rhs.x; y *= rhs.y; return *this; }

    //
    self_type& operator /= (f32 f) { f32 r = 1.f / f; x *= r; y *= r; return *this; }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const { return self_type(-x, -y); }

    //
    self_type operator + (const self_type& rhs) const { return self_type(x + rhs.x, y + rhs.y); }

    //
    self_type operator - (const self_type& rhs) const { return self_type(x - rhs.x, y - rhs.y); }

    //
    self_type operator * (f32 f) const { return self_type(f * x, f * y); }

    //
    self_type operator / (f32 f) const { f32 r = 1.f / f; return self_type(r * x, r * y); }

    //
    //
    //
    //
    //
    //
    self_type& Lerp(const VEC2& lhs, const VEC2& rhs, f32 t)
    {
        return *VEC2Lerp(this, &lhs, &rhs, t);
    }

    //
    //
    //
    //
    f32 Dot(const VEC2& vec) const
    {
        return VEC2Dot(this, &vec);
    }

    //
    f32 LenSq() const { return x * x + y * y; }

    //
    f32 LengthSquare() const { return x * x + y * y; }

    //
    f32 Length() const { return FSqrt(this->x * this->x + this->y * this->y); }

    //
    self_type& Normalize()
    {
        return *VEC2Normalize(this, this);
    }

    //
    //
    //
    //
    self_type& SafeNormalize(const VEC2& alt)
    {
        return *VEC2SafeNormalize(this, this, alt);
    }

    //
    //
    //
    f32 DistanceSquare(const VEC2& vec)
    {
        return VEC2DistSq(this, &vec);
    }

    //
    //
    //
    //
    self_type& Maximize(const VEC2& lhs, const VEC2& rhs)
    {
        return *VEC2Maximize(this, &lhs, &rhs);
    }

    //
    //
    //
    //
    self_type& Minimize(const VEC2& lhs, const VEC2& rhs)
    {
        return *VEC2Minimize(this, &lhs, &rhs);
    }

    //

    //----------------------------------------
    //
    //

    //
    void Set(f32 fx, f32 fy) { x = fx; y = fy; }

    //

    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y; }

    //
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y; }

    //
    bool IsZero() const { return VEC2IsZero(this); }
    //

    //
    void Report(bool bNewline = true, const char* name = NULL) const;

private:
    typedef void (self_type::*UnspecifiedBoolType)() const;
    operator UnspecifiedBoolType() const;
    operator UnspecifiedBoolType();
};
#pragma diag_default 2530

//
//

//
typedef class VEC2 Vector2;

//

/* ------------------------------------------------------------------------
    Function for VEC2
   ------------------------------------------------------------------------ */
NN_MATH_INLINE VEC2*
VEC2Add(VEC2* pOut, const VEC2* p1, const VEC2* p2) 
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    pOut->x = p1->x + p2->x; pOut->y = p1->y + p2->y; 
    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2Sub(VEC2* pOut, const VEC2* p1, const VEC2* p2) 
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    pOut->x = p1->x - p2->x; pOut->y = p1->y - p2->y; 
    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2Mult(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = p1->x * p2->x;
    pOut->y = p1->y * p2->y;
    return pOut;
}


NN_MATH_INLINE VEC2*
VEC2Scale(VEC2* pOut, const VEC2* p, f32 scale)
{
    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( p );

    pOut->x = p->x * scale; pOut->y = p->y * scale;
    return pOut;
}

NN_MATH_INLINE VEC2*
VEC2Lerp(VEC2* pOut, const VEC2* p1, const VEC2* p2, f32 t)
{
    // (1-t)*p1 + t*p2
    pOut->x = p1->x + t * (p2->x - p1->x);
    pOut->y = p1->y + t * (p2->y - p1->y);
    return pOut;
}

NN_MATH_INLINE f32
VEC2Dot(const VEC2* p1, const VEC2* p2) 
{
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );

    return p1->x * p2->x + p1->y * p2->y;
}

NN_MATH_INLINE f32
VEC2LenSq(const VEC2* p)
{
    NN_NULL_ASSERT( p );
    return p->x * p->x + p->y * p->y;
}

NN_MATH_INLINE f32
VEC2Len(const VEC2* p) { return FSqrt(p->x * p->x + p->y * p->y); }

NN_MATH_INLINE f32
VEC2DistSq(const VEC2* p1, const VEC2* p2) { VEC2 tmp; return VEC2LenSq(VEC2Sub(&tmp, p1, p2)); }

NN_MATH_INLINE VEC2
operator * (f32 f, const VEC2& rhs) { return VEC2(f * rhs.x, f * rhs.y); }

}  // namespace math
}  // namespace nn

#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Vector2.ipp>
#endif

namespace nn {
namespace math {

//Overload referencing the -- const argument
inline bool VEC2IsZero(const VEC2& v){ return VEC2IsZero( &v ); }
inline VEC2* VEC2Add(VEC2* pOut, const VEC2& p1, const VEC2& p2) { return VEC2Add(pOut, &p1, &p2); }
inline VEC2* VEC2Sub(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Sub(pOut, &v1, &v2); }
inline VEC2* VEC2Mult(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Mult(pOut, &v1, &v2); }
inline VEC2* VEC2Scale(VEC2* pOut, const VEC2& v, f32 scale) { return VEC2Scale(pOut, &v, scale); }
inline VEC2* VEC2Lerp(VEC2* pOut, const VEC2& v1, const VEC2& v2, f32 t) { return VEC2Lerp(pOut, &v1, &v2, t); }
inline f32 VEC2Dot(const VEC2& v1, const VEC2& v2) { return VEC2Dot(&v1, &v2); }
inline f32 VEC2LenSq(const VEC2& v) { return VEC2LenSq( &v ); }
inline f32 VEC2Len(const VEC2& v) { return VEC2Len( &v ); }
inline f32 VEC2DistSq(const VEC2& v1, const VEC2& v2) { return VEC2DistSq( &v1, &v2 ); }

inline VEC2* VEC2Maximize(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Maximize( pOut, &v1, &v2 ); }
inline VEC2* VEC2Minimize(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Minimize( pOut, &v1, &v2 ); }
inline VEC2* VEC2Normalize(VEC2* pOut, const VEC2& v) { return VEC2Normalize( pOut, &v ); }
inline VEC2* VEC2SafeNormalize(VEC2* pOut, const VEC2& v, const VEC2& alt) { return VEC2SafeNormalize( pOut, &v, alt ); }

}  // namespace math
}  // namespace nn

#pragma pop

#endif
