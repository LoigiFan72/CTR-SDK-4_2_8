/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Transform.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47689 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_TRANSFORM_H_
#define NN_MATH_TRANSFORM_H_

#include <nn/math/math_Config.h>
#include <nn/math/math_Vector2.h>
#include <nn/math/math_Vector3.h>
#include <nn/math/math_Vector4.h>

namespace nn { namespace math {

/* ------------------------------------------------------------------------
    Transform
    Class for controlling position via SRT.
   ------------------------------------------------------------------------ */
struct _Transform2
{
    VEC2    scale;
    VEC2    rotate;
    VEC2    translate;
};

struct _Transform3
{
    VEC3    scale;
    VEC3    rotate;
    VEC3    translate;
};

struct Transform2 : public _Transform2
{
public:
    typedef Transform2 self_type;
    typedef f32        value_type;
public:
    Transform2() {}
    /* implicit */ Transform2(const _Transform2& t)
    {
        scale = t.scale; 
        rotate = t.rotate; 
        translate = t.translate;
    }
    Transform2(const VEC2& s, const VEC2& r, const VEC2& t)
    {
        scale     = s;
        rotate    = r;
        translate = t;
    }
    
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform2)) == 0; }
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform2)) != 0; }
    
    
    void Report(bool bNewline = true, const char* name = NULL) const;
};

struct Transform3 : public _Transform3
{
public:
    typedef Transform3 self_type;
    typedef f32        value_type;
public:
    Transform3() {}
    /* implicit */ Transform3(const _Transform3& t) 
    {
        scale = t.scale; 
        rotate = t.rotate; 
        translate = t.translate;
    }
    Transform3(const VEC3& s, const VEC3& r, const VEC3& t)
    {
        scale     = s;
        rotate    = r;
        translate = t;
    }
    
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform3)) == 0; }
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform3)) != 0; }
    
    void Report(bool bNewline = true, const char* name = NULL) const;
};

inline Transform2* 
Transform2Identity(Transform2* pOut) 
{
    NN_NULL_ASSERT(pOut);
    pOut->scale     = VEC2(1.f, 1.f);
    pOut->rotate    = VEC2(0.f, 0.f);
    pOut->translate = VEC2(0.f, 0.f);
    return pOut;
}

inline Transform3* 
Transform3Identity(Transform3* pOut) 
{
    NN_NULL_ASSERT(pOut);
    pOut->scale     = VEC3(1.f, 1.f, 1.f);
    pOut->rotate    = VEC3(0.f, 0.f, 0.f);
    pOut->translate = VEC3(0.f, 0.f, 0.f);
    return pOut;
}

/* Please see man pages for details 
    
    
*/

// Transformed as (x, y, z, 1)

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC2* VEC2Transform(VEC2* pOut, const MTX23* pM, const VEC2* pV);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3Transform(VEC3* pOut, const MTX33* pM, const VEC3* pV);

/*
  

  
                      
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3Transform(VEC3* pOut, const MTX34* pM, const VEC3* pV);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3TransformArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, s32 count);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC3TransformArray(VEC4* pOut, const MTX44* pM, const VEC3* pV, u32 count);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3TransformNormalArray(VEC3* pOutArray, const MTX34* pM, const VEC3* pArray, u32 n);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC3* VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count);

/*
  

  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4Transform(VEC4* pOut, const MTX44* pM, const VEC4* pV);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE VEC4* VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 n);

/*  

*/

//Overload referencing the -- const argument
inline VEC2* VEC2Transform(VEC2* pOut, const MTX23& m, const VEC2& v) { return VEC2Transform( pOut, &m, &v ); }

inline VEC3* VEC3Transform(VEC3* pOut, const MTX33& m, const VEC3& v) { return VEC3Transform( pOut, &m, &v ); }
inline VEC3* VEC3Transform(VEC3* pOut, const MTX34& m, const VEC3& v) { return VEC3Transform( pOut, &m, &v ); }
inline VEC4* VEC3Transform(VEC4* pOut, const MTX44& m, const VEC3& v) { return VEC3Transform( pOut, &m, &v ); }
inline VEC3* VEC3TransformArray(VEC3* pOutArray, const MTX34& m, const VEC3* pArray, s32 count) { return VEC3TransformArray( pOutArray, &m, pArray, count ); }
inline VEC4* VEC3TransformArray(VEC4* pOutArray, const MTX44& m, const VEC3* pArray, u32 count) { return VEC3TransformArray( pOutArray, &m, pArray, count ); }

inline VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34& m, const VEC3& v) { return VEC3TransformNormal( pOut, &m, &v ); }
inline VEC3* VEC3TransformNormalArray(VEC3* pOutArray, const MTX34& m, const VEC3* pArray, u32 n) { return VEC3TransformNormalArray( pOutArray, &m, pArray, n ); }

inline VEC3* VEC3TransformCoord(VEC3* pOut, const MTX44& m, const VEC3& v) { return VEC3TransformCoord( pOut, &m, &v ); }
inline VEC3* VEC3TransformCoordArray(VEC3* pOutArray, const MTX44& m, const VEC3* pArray, u32 count) { return VEC3TransformCoordArray( pOutArray, &m, pArray, count ); }

inline VEC4* VEC4Transform(VEC4* pOut, const MTX44& m, const VEC4& v) { return VEC4Transform( pOut, &m, &v ); }
inline VEC4* VEC4TransformArray(VEC4* pOutArray, const MTX44& m, const VEC4* pArray, u32 n) { return VEC4TransformArray( pOutArray, &m, pArray, n ); }


}}  // nn::math


/* NN_MATH_TRANSFORM_H_ */
#endif

