/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix22.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46684 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATRIX22_H_
#define NN_MATH_MATRIX22_H_

#include <cstring>
#include <nn/math/math_Config.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct MTX22;
struct MTX23;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    Function for MTX22
   ------------------------------------------------------------------------ */
/*
  

  
  

  
 */
NN_MATH_INLINE MTX22* MTX22Copy(MTX22* pOut, const MTX22* p);

/*
  

  

  
 */
NN_MATH_INLINE MTX22* MTX22Identity(MTX22* pOut);

/*
  

  

  
 */
NN_MATH_INLINE bool   MTX22IsIdentity(const MTX22* p);

/*
  

  
  
  
  

  
 */
NN_MATH_INLINE MTX22* MTX22MAdd(MTX22* pOut, f32 t, const MTX22* p1, const MTX22* p2);

/*
  

  

  
 */
NN_MATH_INLINE MTX22* MTX22Zero(MTX22* pOut);

/*  

*/

NN_MATH_INLINE MTX22* MTX23ToMTX22(MTX22* pOut, const MTX23* pM);

/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct MTX22_
{
    //
    struct BaseData
    {
        f32 _00;    //
        f32 _01;    //
        f32 _10;    //
        f32 _11;    //
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
            f32 _00, _01;
            f32 _10, _11;
        };
    #endif
        BaseData f;     //
        f32 m[2][2];    //
        f32 a[4];       //
        VEC2_ v[2];     //
    //
    };
};

/*
  
  
 */
class MTX22 : public MTX22_
{
public:
    static const int ROW_COUNT = 2; //
    static const int COLUMN_COUNT = 2; //

    //
    static const MTX22& Identity()
    {
        static const MTX22 identity(
            1.0f, 0.0f,
            0.0f, 1.0f);

        return identity;
    }

    typedef MTX22 self_type; //
    typedef f32   value_type; //
public:
    //----------------------------------------
    //
    //

    //
    MTX22() {}
    //
    explicit MTX22(const f32* p);
    //
    explicit MTX22(const MTX23& rhs);
    //
    MTX22(f32 x00, f32 x01, 
          f32 x10, f32 x11)
    {
        f._00 = x00; f._01 = x01;
        f._10 = x10; f._11 = x11;
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
    VEC2& GetRow(int index)
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, ROW_COUNT);
        return *reinterpret_cast<VEC2*>(&this->v[index]);
    }

    //
    const VEC2& GetRow(int index) const
    {
        NN_MATH_MINMAXLT_ASSERT(index, 0, ROW_COUNT);
        return *reinterpret_cast<const VEC2*>(&this->v[index]);
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
    self_type& SetupIdentity() { return *MTX22Identity(this); }

    //

    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX22)) == 0; }

    //
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX22)) != 0; }

    //
    bool IsIdentity() const { return MTX22IsIdentity(this); }

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
typedef class MTX22 Matrix22;

//

}  // namespace math
}  // namespace nn

namespace nn {
namespace math {

inline
MTX22::MTX22(const f32* p) { MTX22Copy(this, reinterpret_cast<const MTX22*>(p)); }

inline
MTX22::MTX22(const MTX23& rhs) { MTX23ToMTX22(this, &rhs); }

//Overload referencing the -- const argument
inline bool   MTX22IsIdentity(const MTX22& m) { return MTX22IsIdentity( &m ); }
inline MTX22* MTX22Copy(MTX22* pOut, const MTX22& m) { return MTX22Copy(pOut, &m); }
inline MTX22* MTX22MAdd(MTX22* pOut, f32 t, const MTX22& m1, const MTX22& m2) { return MTX22MAdd(pOut, t, &m1, &m2); }

}  // namespace math
}  // namespace nn

#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix22.ipp>
#endif

#pragma pop

#endif
