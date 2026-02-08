/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix23.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48334 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATRIX23_H_
#define NN_MATH_MATRIX23_H_

#include <cstring>
#include <nn/math/math_Config.h>
#include <nn/math/math_Vector2.h>
#include <nn/math/math_Vector3.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct MTX23;
struct MTX22;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for MTX23
   ------------------------------------------------------------------------ */
/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Add(MTX23* pOut, const MTX23* p1, const MTX23* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Copy(MTX23* pOut, const MTX23* p);

/*
  

  

  
 */
NN_MATH_INLINE MTX23* MTX23Identity(MTX23* pOut);

/*
  

  

  
 */
NN_MATH_INLINE bool   MTX23IsIdentity(const MTX23* p);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23MAdd(MTX23* pOut, f32 t, const MTX23* p1, const MTX23* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Mult(MTX23* pOut, const MTX23* p, f32 f);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Mult(MTX23* pOut, const MTX23* p1, const MTX23* p2);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23MultTranslate(MTX23* pOut, const MTX23* pM, const VEC2* pT);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23MultTranslate(MTX23* pOut, const VEC2* pT, const MTX23* pM);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23RotCenterFIdx(MTX23* pOut, const VEC2* pCenter, f32 fIdx);

/*
  

  
  

  
 */
NN_MATH_INLINE MTX23* MTX23RotFIdx(MTX23* pOut, f32 fIdx);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Scale(MTX23* pOut, const MTX23* pM, const VEC2* pS);

/*
  

  
  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Sub(MTX23* pOut, const MTX23* p1, const MTX23* p2);

/*
  

  
  

  
 */
NN_MATH_INLINE MTX23* MTX23Translate(MTX23* pOut, const VEC2* pT);

/*
  

  

  
 */
NN_MATH_INLINE MTX23* MTX23Zero(MTX23* pOut);

/*  

*/

NN_MATH_INLINE MTX23* MTX22ToMTX23(MTX23* pOut, const MTX22* pM);

/*
  
  
 */
struct MTX23_
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
        };
    #endif
        BaseData f;     //
        f32 m[2][3];    //
        f32 a[6];       //
        VEC3_ v[2];     //
    //
    };
};

/*
  
  
 */
class MTX23 : public MTX23_
{
public:
    static const int ROW_COUNT = 2; //
    static const int COLUMN_COUNT = 3; //

    //
    static const MTX23& Identity()
    {
        static const MTX23 identity(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f);
        
        return identity;
    }

    typedef MTX23 self_type; //
    typedef f32   value_type; //
public:
    //----------------------------------------
    //
    //

    //
    MTX23() {}
    //
    explicit MTX23(const f32* p) { (void)MTX23Copy(this, reinterpret_cast<const MTX23*>(p)); }
    //
    explicit MTX23(const MTX22& rhs) { MTX22ToMTX23(this, &rhs); }
    //
    MTX23(f32 x00, f32 x01, f32 x02,
          f32 x10, f32 x11, f32 x12)
    {
        f._00 = x00; f._01 = x01; f._02 = x02;
        f._10 = x10; f._11 = x11; f._12 = x12;
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
    VEC2 GetColumn(int index) const
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, COLUMN_COUNT);
        VEC2 column;
        column.x = this->m[0][index];
        column.y = this->m[1][index];
        return column;
    }
    
    //
    void SetColumn(int index, const VEC2& column)
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, COLUMN_COUNT);
        this->m[0][index] = column.x;
        this->m[1][index] = column.y;
    }
    //

    //----------------------------------------
    //
    //
    
    //
    self_type& SetupIdentity() { return *MTX23Identity(this); }
    
    //
    
    //----------------------------------------
    //
    //

    //
    self_type& operator += (const self_type& rhs) { return *MTX23Add(this, this, &rhs); }

    //
    self_type& operator -= (const self_type& rhs) { return *MTX23Sub(this, this, &rhs); }
    
    //
    self_type& operator *= (f32 f) { return *MTX23Mult(this, this, f); }

    //
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    //
    self_type operator + () const { return *this; }

    //
    self_type operator - () const
    {
        return MTX23(-f._00, -f._01, -f._02,
                     -f._10, -f._11, -f._12);
    }

    //
    self_type operator + (const self_type& rhs) const { MTX23 tmp; return *MTX23Add(&tmp, this, &rhs); }

    //
    self_type operator - (const self_type& rhs) const { MTX23 tmp; return *MTX23Sub(&tmp, this, &rhs); }

    //
    self_type operator * (f32 f) const { MTX23 tmp; return *MTX23Mult(&tmp, this, f); }

    //
    self_type operator / (f32 f) const { return *this * (1.f / f); }

    //

    //----------------------------------------
    //
    //
    
    //
    //
    //
    //
    //
    self_type& SetupScale(const MTX23& matrix, const VEC2& scale)
    {
        return *MTX23Scale(this, &matrix, &scale);
    }

    //
    //
    //
    //
    //
    self_type& SetupTranslate(const MTX23& matrix, const VEC2& translate)
    {
        return *MTX23MultTranslate(this, &matrix, &translate);
    }

    //
    //
    //
    //
    self_type& SetupRotate(f32 rotate)
    {
        return *MTX23RotFIdx(this, NN_MATH_RAD_TO_FIDX(rotate));
        
    }

    //
    //
    //
    //
    //
    self_type& SetupRotate(const VEC2& center, f32 rotate)
    {
        return *MTX23RotCenterFIdx(this, &center, NN_MATH_RAD_TO_FIDX(rotate));
    }

    //
    
    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX23)) == 0; }

    //
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX23)) != 0; }

    //
    bool IsIdentity() const { return MTX23IsIdentity(this); }
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
typedef class MTX23 Matrix23;

//

}  // namespace math
}  // namespace nn

namespace nn { 
namespace math {

//Overload referencing the -- const argument

inline MTX23* MTX23Copy(MTX23* pOut, const MTX23& m) { return MTX23Copy( pOut, &m ); }
inline bool   MTX23IsIdentity(const MTX23& m) { return MTX23IsIdentity( &m ); }
inline MTX23* MTX23Add(MTX23* pOut, const MTX23& m1, const MTX23& m2) { return MTX23Add( pOut, &m1, &m2 ); }
inline MTX23* MTX23Sub(MTX23* pOut, const MTX23& m1, const MTX23& m2) { return MTX23Sub( pOut, &m1, &m2 ); }
inline MTX23* MTX23Mult(MTX23* pOut, const MTX23& m, f32 f) { return MTX23Mult( pOut, &m, f ); }
inline MTX23* MTX23Mult(MTX23* pOut, const MTX23& m1, const MTX23& m2) { return MTX23Mult( pOut, &m1, &m2); }
inline MTX23* MTX23Scale(MTX23* pOut, const MTX23& m, const VEC2& vS) { return MTX23Scale( pOut, &m, &vS); }
inline MTX23* MTX23Translate(MTX23* pOut, const VEC2& vT) { return MTX23Translate( pOut, &vT); }
inline MTX23* MTX23MultTranslate(MTX23* pOut, const MTX23& m, const VEC2& vT) { return MTX23MultTranslate( pOut, &m, &vT); }
inline MTX23* MTX23MultTranslate(MTX23* pOut, const VEC2& vT, const MTX23& m) { return MTX23MultTranslate( pOut, &vT, &m); }
inline MTX23* MTX23RotCenterFIdx(MTX23* pOut, const VEC2& vCenter, f32 fIdx) { return MTX23RotCenterFIdx( pOut, &vCenter, fIdx ); }
inline MTX23* MTX23MAdd(MTX23* pOut, f32 t, const MTX23& m1, const MTX23& m2) { return MTX23MAdd( pOut, t, &m1, &m2 ); }

}  // namespace math
}  // namespace nn

#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix23.ipp>
#endif

#pragma pop

#endif
