/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Quaternion.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_QUATERNION_H_
#define NN_MATH_QUATERNION_H_

#include <nn/math/math_Config.h>

namespace nn {
namespace math {

struct QUAT;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for QUAT
   ------------------------------------------------------------------------ */
/*
  

  
                      
  
  

  
 */
NN_MATH_INLINE QUAT* QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2);

/*
  

  
                
  
  

  
 */
NN_MATH_INLINE QUAT* QUATDivide(QUAT* pOut, const QUAT* q1, const QUAT* q2);

/*
  

  
  

  
 */
NN_MATH_INLINE f32   QUATDot(const QUAT* q1, const QUAT* q2);

/*
  

  
                      
  
                      

  
 */
NN_MATH_INLINE QUAT* QUATExp(QUAT* pOut, const QUAT* q);

/*
  

  
  

  
 */
NN_FORCE_INLINE QUAT* QUATInverse(QUAT* pOut, const QUAT* __restrict q);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE QUAT* QUATLerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);

/*
  

  
                      
  

  
 */
NN_MATH_INLINE QUAT* QUATLogN(QUAT* pOut, const QUAT* q);

/*
  

  
  
  

  
 */
NN_MATH_INLINE QUAT* QUATMakeClosest( QUAT* pOut, const QUAT *q, const QUAT *qto );

/*
  

  
  
  

  
 */
NN_FORCE_INLINE QUAT* QUATMult(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2);

/*
  

  
  

  
 */
NN_FORCE_INLINE QUAT* QUATNormalize(QUAT* pOut, const QUAT* __restrict q);

/*
  

  
                       
  
  

  
 */
NN_MATH_INLINE QUAT* QUATScale(QUAT* pOut, const QUAT* q, f32 scale);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE QUAT* QUATSlerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);

/*
  

  
  
  
  
  
  

  
 */
NN_MATH_INLINE QUAT* QUATSquad(QUAT* pOut, const QUAT* p, const QUAT* a, const QUAT* b, const QUAT* q, f32 t);

/*
  

  
                      
  
  

  
 */
NN_MATH_INLINE QUAT* QUATSub(QUAT* pOut, const QUAT* q1, const QUAT* q2);

/*
  
               

  
  
                       
  

  
 */
NN_MATH_INLINE QUAT* QUATRotAxisRad( QUAT* pOut, const VEC3 *axis, f32 rad );

/*  

*/

/* ------------------------------------------------------------------------
    QUAT
   ------------------------------------------------------------------------ */
/*
    
    
 */
struct QUAT_
{
    f32 x;  //
    f32 y;  //
    f32 z;  //
    f32 w;  //
};

/*
    
    
 */
class QUAT : public QUAT_
{
public:
    typedef QUAT self_type;     //
    typedef f32  value_type;    //
public:
    //----------------------------------------
    //
    //
    //
    QUAT() {}
    //
    explicit QUAT(const f32* p) { x = p[0]; y = p[1]; z = p[2]; w = p[3]; }
    //
    QUAT(const QUAT_& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; }
    //
    QUAT(f32 fx, f32 fy, f32 fz, f32 fw) { x = fx; y = fy; z = fz; w = fw; }

    //

    //----------------------------------------
    //
    //

    //
    operator f32*() { return &x; }
    //
    operator const f32*() const { return &x; }
#if 0
    // The cast operator is put off because the function name is the same as DolphinSDK.
    operator Quaternion*() { return (Quaternion*)&x; }
    operator const Quaternion*() const { return (const Quaternion*)&x; }
#endif
    //

    //----------------------------------------
    //
    //

    //
    self_type& operator += (const self_type& rhs) { (void)QUATAdd(this, this, &rhs); return *this; }

    //
    self_type& operator -= (const self_type& rhs) { (void)QUATSub(this, this, &rhs); return *this; }

    //
    self_type& operator *= (f32 f) { (void)QUATScale(this, this, f); return *this; }

    //
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const { return self_type(-x, -y, -z, -w); }

    //
    self_type operator + (const self_type& rhs) const { QUAT tmp; (void)QUATAdd(&tmp, this, &rhs); return tmp; }

    //
    self_type operator - (const self_type& rhs) const { QUAT tmp; (void)QUATSub(&tmp, this, &rhs); return tmp; }

    //
    self_type operator * (f32 f) const { QUAT tmp; (void)QUATScale(&tmp, this, f); return tmp; }

    //
    self_type operator / (f32 f) const { return operator*(1.f / f); }

    //
    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }

    //
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w; }

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
typedef class QUAT Quaternion;

//

inline QUAT
operator * (f32 f, const QUAT& rhs) { QUAT tmp; (void)QUATScale(&tmp, &rhs, f); return tmp; }

}  // namespace math
}  // namespace nn

#include <nn/math/ARMv6/math_Quaternion.h>

namespace nn { 
namespace math {

NN_FORCE_INLINE QUAT*
QUATInverse(QUAT* pOut, const QUAT* __restrict q)
{
#if defined( NN_HARDWARE_CTR )
    #if (QUATINVERSE_CONFIG == D_ORG)
        return ARMv6::QUATInverseC( pOut, q );
    #elif (QUATINVERSE_CONFIG == D_FAST_C)
        return ARMv6::QUATInverseC_FAST( pOut, q);
    #elif (QUATINVERSE_CONFIG == D_FAST_ASM)
    #elif (QUATINVERSE_CONFIG == D_FAST_C_ALGO)
    #elif (QUATINVERSE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE QUAT*
QUATMult(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2)
{
#if defined( NN_HARDWARE_CTR )
    #if (QUATMULT_CONFIG == D_ORG)
        return ARMv6::QUATMultC( pOut, q1, q2);
    #elif (QUATMULT_CONFIG == D_FAST_C)
        return ARMv6::QUATMultC_FAST( pOut, q1, q2);
    #elif (QUATMULT_CONFIG == D_FAST_ASM)
        return ARMv6::QUATMultAsm( pOut, q1, q2);
    #elif (QUATMULT_CONFIG == D_FAST_C_ALGO)
    #elif (QUATMULT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE QUAT*
QUATNormalize(QUAT* pOut, const QUAT* __restrict q)
{
#if defined( NN_HARDWARE_CTR )
    #if (QUATNORMALIZE_CONFIG == D_ORG)
        return ARMv6::QUATNormalizeC( pOut, q );
    #elif (QUATNORMALIZE_CONFIG == D_FAST_C)
        return ARMv6::QUATNormalizeC_FAST( pOut, q);
    #elif (QUATNORMALIZE_CONFIG == D_FAST_ASM)
    #elif (QUATNORMALIZE_CONFIG == D_FAST_C_ALGO)
    #elif (QUATNORMALIZE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

}  // namespace math
}  // namespace nn


#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Quaternion.ipp>
#include <nn/math/ARMv6/inline/math_Quaternion.ipp>
#endif

namespace nn {
namespace math {

//Overload referencing the -- const argument
inline QUAT* QUATAdd(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATAdd( pOut, &q1, &q2 ); }
inline QUAT* QUATSub(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATSub( pOut, &q1, &q2 ); }
inline QUAT* QUATDivide(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATDivide( pOut, &q1, &q2 ); }
inline QUAT* QUATMult(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATMult( pOut, &q1, &q2 ); }
inline f32   QUATDot(const QUAT& q1, const QUAT& q2) { return QUATDot( &q1, &q2 ); }
inline QUAT* QUATInverse(QUAT* pOut, const QUAT& q) { return QUATInverse( pOut, &q ); }
inline QUAT* QUATScale(QUAT* pOut, const QUAT& q, f32 scale) { return QUATScale( pOut, &q, scale ); }
inline QUAT* QUATNormalize(QUAT* pOut, const QUAT& q) { return QUATNormalize( pOut, &q ); }
inline QUAT* QUATExp(QUAT* pOut, const QUAT& q) { return QUATExp( pOut, &q ); }
inline QUAT* QUATLogN(QUAT* pOut, const QUAT& q) { return QUATLogN( pOut, &q ); }
inline QUAT* QUATLerp(QUAT* pOut, const QUAT& q1, const QUAT& q2, f32 t) { return QUATLerp( pOut, &q1, &q2, t ); }
inline QUAT* QUATSlerp(QUAT* pOut, const QUAT& q1, const QUAT& q2, f32 t) { return QUATSlerp( pOut, &q1, &q2, t ); }
inline QUAT* QUATSquad(QUAT* pOut, const QUAT& p, const QUAT& a, const QUAT& b, const QUAT& q, f32 t) { return QUATSquad( pOut, &p, &a, &b, &q, t ); }

inline QUAT* QUATMakeClosest( QUAT*  pOut, const QUAT& q, const QUAT& qto ) { return QUATMakeClosest( pOut, &q, &qto ); }
inline QUAT* QUATRotAxisRad( QUAT* pOut, const VEC3& axis, f32 rad ) { return QUATRotAxisRad( pOut, &axis, rad ); }

}  // namespace math
}  // namespace nn


#endif // NN_MATH_QUATERNION_H_
