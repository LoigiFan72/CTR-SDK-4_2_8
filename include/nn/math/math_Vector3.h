/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector3.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_VECTOR3_H_
#define NN_MATH_VECTOR3_H_

#include <cstring>
#include <nn/math/math_Config.h>
#include <nn/math/math_Constant.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct VEC3;
struct MTX33;
struct MTX34;

/* Please see man pages for details 
    
    
*/
// Transformed as (x, y, z, 0)
/*
  

  
  
  

  
 */
inline VEC3* VEC3Add(VEC3* pOut, const VEC3* p1, const VEC3* p2);

/*
  

  
                      
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3Cross(VEC3* pOut, const VEC3* p1, const VEC3* p2);

/*
  

  
  

  
 */
inline f32   VEC3Dist(const VEC3* p1, const VEC3* p2);

/*
  

  
  

  
 */
inline f32   VEC3Dot(const VEC3* p1, const VEC3* p2);

/*
  

  

  
 */
NN_MATH_INLINE bool VEC3IsZero(const VEC3* p);

/*
  

  

  
 */
inline f32   VEC3Len(const VEC3* p);

/*
  

  
  
  
  

  
 */
inline VEC3* VEC3Lerp(VEC3* pOut, const VEC3* p1, const VEC3* p2, f32 t);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2);

/*
  

  
  
  

  
 */
inline VEC3* VEC3Mult(VEC3* pOut, const VEC3* p1, const VEC3* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE VEC3* VEC3Normalize(VEC3* pOut, const VEC3* p);

/*
  
                

  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3SafeNormalize(VEC3* pOut, const VEC3* p, const VEC3& alt);

/*
  

  
  
  

  
 */
inline VEC3* VEC3Scale(VEC3* pOut, const VEC3* p, f32 scale);

/*
  

  
  

  
 */
NN_MATH_INLINE f32   VEC3SquareDist(const VEC3* p1, const VEC3* p2);

/*
  

  

  
 */
inline f32   VEC3SquareLen(const VEC3* p);

/*
  

  
  
  

  
 */
inline VEC3* VEC3Sub(VEC3* pOut, const VEC3* p1, const VEC3* p2);

/*  

*/

NN_FORCE_INLINE VEC3* VEC3Normalize(VEC3* pOut, const VEC3* p);

/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct VEC3_
{
    f32 x;  //
    f32 y;  //
    f32 z;  //
};

/*
    
    
   */
class VEC3 : public VEC3_
{
public:
    static const int DIMENSION = 3; //

    //
    static const VEC3& Zero()
    {
        static const VEC3 zero(0.0f, 0.0f, 0.0f);
        
        return zero;
    }
    
    //
    static const VEC3& One()
    {
        static const VEC3 one(1.0f, 1.0f, 1.0f);
        
        return one;
    }

    typedef VEC3 self_type; //
    typedef f32  value_type; //
public:
    //----------------------------------------
    //
    //

    //
    VEC3() {}
    explicit VEC3(const f32* p) { x = p[0]; y = p[1]; z = p[2]; }
    //
    VEC3(const VEC3_& v) { x = v.x; y = v.y; z = v.z; }
    //
    VEC3(f32 fx, f32 fy, f32 fz) { x = fx; y = fy; z = fz; }

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
    self_type& operator += (const self_type& rhs) { (void)VEC3Add(this, this, &rhs); return *this; }

    //
    self_type& operator -= (const self_type& rhs) { (void)VEC3Sub(this, this, &rhs); return *this; }

    //
    self_type& operator *= (f32 f) { (void)VEC3Scale(this, this, f); return *this; }

    //
    self_type& operator *= (const self_type& rhs) { (void)VEC3Mult(this, this, &rhs); return *this; }

    //
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const { return self_type(-x, -y, -z); }

    // The best implementation for binary operators differs depending on whether return values are optimized.
    //
    self_type operator + (const self_type& rhs) const { VEC3 tmp; (void)VEC3Add(&tmp, this, &rhs); return tmp; }

    //
    self_type operator - (const self_type& rhs) const { VEC3 tmp; (void)VEC3Sub(&tmp, this, &rhs); return tmp; }

    //
    self_type operator * (f32 f) const { VEC3 tmp; (void)VEC3Scale(&tmp, this, f); return tmp; }

    //
    self_type operator / (f32 f) const { f32 r = 1.f / f; return operator*(r); }

    //
    //
    //
    //
    //
    //
    self_type& Lerp(const VEC3& lhs, const VEC3& rhs, f32 t)
    {
        return *VEC3Lerp(this, &lhs, &rhs, t);
    }

    //
    //
    //
    //
    f32 Dot(const VEC3& vec) const
    {
        return VEC3Dot(this, &vec);
    }

    //
    //
    //
    f32 LenSq() const { return VEC3SquareLen(this); }

    //
    f32 LengthSquare() const { return VEC3SquareLen(this); }

    //
    f32 Length() const { return VEC3Len(this); }

    //
    self_type& Normalize()
    {
        return *VEC3Normalize(this, this);
    }

    //
    //
    //
    //
    self_type& SafeNormalize(const VEC3& alt)
    {
        return *VEC3SafeNormalize(this, this, alt);
    }

    //
    //
    //
    f32 DistanceSquare(const VEC3& vec) const
    {
        return VEC3SquareDist(this, &vec);
    }

    //
    //
    //
    //
    self_type& Maximize(const VEC3& lhs, const VEC3& rhs)
    {
        return *VEC3Maximize(this, &lhs, &rhs);
    }

    //
    //
    //
    //
    self_type& Minimize(const VEC3& lhs, const VEC3& rhs)
    {
        return *VEC3Minimize(this, &lhs, &rhs);
    }

    //
    //
    //
    //
    self_type& Cross(const VEC3& lhs, const VEC3& rhs)
    {
        return *VEC3Cross(this, &lhs, &rhs);
    }

    //

    //----------------------------------------
    //
    //
    
    //
    void Set(f32 fx, f32 fy, f32 fz) { x = fx; y = fy; z = fz; }
    
    //
    void Set(const self_type& value) { x = value.x; y = value.y; z = value.z; }

    //

    //----------------------------------------
    //
    //
    //
    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

    //
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

    //
    bool IsZero() const { return VEC3IsZero(this); }

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
typedef class VEC3 Vector3;

//

/* ------------------------------------------------------------------------
    Function for VEC3
   ------------------------------------------------------------------------ */
inline VEC3*
VEC3Add(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = p1->x + p2->x;
    pOut->y = p1->y + p2->y;
    pOut->z = p1->z + p2->z;
    return pOut;
}

inline VEC3*
VEC3Sub(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = p1->x - p2->x;
    pOut->y = p1->y - p2->y;
    pOut->z = p1->z - p2->z;
    return pOut;
}

inline VEC3*
VEC3Mult(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = p1->x * p2->x;
    pOut->y = p1->y * p2->y;
    pOut->z = p1->z * p2->z;
    return pOut;
}

inline VEC3*
VEC3Scale(VEC3* pOut, const VEC3* p, f32 scale)
{
    pOut->x = scale * p->x;
    pOut->y = scale * p->y;
    pOut->z = scale * p->z;
    return pOut;
}

inline VEC3*
VEC3Lerp(VEC3* pOut, const VEC3* p1, const VEC3* p2, f32 t)
{
    pOut->x = p1->x + t * (p2->x - p1->x);
    pOut->y = p1->y + t * (p2->y - p1->y);
    pOut->z = p1->z + t * (p2->z - p1->z);
    return pOut;
}

inline f32
VEC3Dot(const VEC3* p1, const VEC3* p2)
{
    return p1->x * p2->x + p1->y * p2->y + p1->z * p2->z;
}

inline f32
VEC3Len(const VEC3* p)
{
    NN_NULL_ASSERT( p );
    
    return ::std::sqrtf( VEC3SquareLen( p ) );
}

inline f32
VEC3SquareLen(const VEC3* p)
{
    return p->x * p->x + p->y * p->y + p->z * p->z;
}

inline f32
VEC3Dist( const VEC3* p1, const VEC3* p2 )
{
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );
    
    return ::std::sqrtf( VEC3SquareDist( p1, p2 ) );
}


inline VEC3
operator * (f32 f, const VEC3& rhs) { VEC3 tmp; (void)VEC3Scale(&tmp, &rhs, f); return tmp; }

}  // namespace math
}  // namespace nn

#include <nn/math/ARMv6/math_Vector3.h>

namespace nn { 
namespace math {

NN_FORCE_INLINE VEC3*
VEC3Normalize(VEC3* pOut, const VEC3* p)
{
#if defined( NN_HARDWARE_CTR )
    #if (VEC3NORMALIZE__CONFIG == D_ORG)
        return ARMv6::VEC3NormalizeC(pOut, p);
    #elif (VEC3NORMALIZE__CONFIG == D_FAST_C)
        return ARMv6::VEC3NormalizeC_FAST(pOut, p);
    #elif (VEC3NORMALIZE__CONFIG == D_FAST_ASM)
    #elif (VEC3NORMALIZE__CONFIG == D_FAST_C_ALGO)
    #elif (VEC3NORMALIZE__CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

}  // namespace math
}  // namespace nn



#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Vector3.ipp>
#include <nn/math/ARMv6/inline/math_Vector3.ipp>
#endif

namespace nn { 
namespace math {

//Overload referencing the -- const argument
inline bool VEC3IsZero(const VEC3& v){ return VEC3IsZero( &v ); }
inline VEC3* VEC3Maximize(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Maximize( pOut, &v1, &v2 ); }
inline VEC3* VEC3Minimize(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Minimize( pOut, &v1, &v2 ); }
inline VEC3* VEC3Cross(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Cross( pOut, &v1, &v2 ); }
inline VEC3* VEC3Normalize(VEC3* pOut, const VEC3& v) { return VEC3Normalize( pOut, &v ); }
inline VEC3* VEC3SafeNormalize(VEC3* pOut, const VEC3& v, const VEC3& alt) { return VEC3SafeNormalize( pOut, &v, alt ); }
inline f32   VEC3SquareDist(const VEC3& v1, const VEC3& v2) { return VEC3SquareDist( &v1, &v2 ); }

inline VEC3* VEC3Add(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Add( pOut, &v1, &v2 ); }
inline VEC3* VEC3Sub(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Sub( pOut, &v1, &v2 ); }
inline VEC3* VEC3Mult(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Mult( pOut, &v1, &v2 ); }
inline VEC3* VEC3Scale(VEC3* pOut, const VEC3& v, f32 scale) { return VEC3Scale( pOut, &v, scale ); }
inline VEC3* VEC3Lerp(VEC3* pOut, const VEC3& v1, const VEC3& v2, f32 t) { return VEC3Lerp( pOut, &v1, &v2, t ); }
inline f32   VEC3Dot(const VEC3& v1, const VEC3& v2) { return VEC3Dot( &v1, &v2 ); }
inline f32   VEC3Len(const VEC3& v) { return VEC3Len( &v ); }
inline f32   VEC3SquareLen(const VEC3& v) { return VEC3SquareLen( &v ); }
inline f32   VEC3Dist(const VEC3& v1, const VEC3& v2) { return VEC3Dist( &v1, &v2 ); }

}  // namespace math
}  // namespace nn

#pragma pop

#endif
