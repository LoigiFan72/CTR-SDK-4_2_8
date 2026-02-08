/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix33.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47340 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATRIX33_H_
#define NN_MATH_MATRIX33_H_

#include <cstring>
#include <nn/math/math_Config.h>
#include <nn/math/math_Vector3.h>
#include <nn/math/ARMv6/math_Matrix33.h>

#pragma push
#pragma Otime

namespace nn {
namespace math {

struct MTX33;
struct MTX34;

/* Please see man pages for details 
    
    
*/
/* ------------------------------------------------------------------------
    Function for MTX33
   ------------------------------------------------------------------------ */
/*
  

  
  

  
 */
NN_FORCE_INLINE MTX33* MTX33Copy(MTX33* pOut, const MTX33* p);

/*
  

  

  
 */
NN_MATH_INLINE MTX33* MTX33Identity(MTX33* pOut);

/*
  

  

  
 */
NN_MATH_INLINE bool   MTX33IsIdentity(const MTX33* p);

/*
  

  
  
  
  

  
 */
NN_FORCE_INLINE MTX33* MTX33MAdd(MTX33* pOut, f32 t, const MTX33* p1, const MTX33* p2);

/*
  

  
  
  

  
 */
template<typename TMatrix>
NN_FORCE_INLINE TMatrix* MTX33Mult(TMatrix* pOut, const TMatrix* p1, const TMatrix* p2);

/*
  

  

  
 */
NN_MATH_INLINE MTX33* MTX33Zero(MTX33* pOut);

/*  

*/

NN_MATH_INLINE MTX34* MTX33ToMTX34(MTX34* pOut, const MTX33* pM);
NN_MATH_INLINE MTX33* MTX34ToMTX33(MTX33* pOut, const MTX34* pM);

NN_FORCE_INLINE VEC3* VEC3Transform(VEC3* pOut, const MTX33* pM, const VEC3* pV);

/* =======================================================================
        Class definitions
   ======================================================================== */
/*
    
    
 */
struct MTX33_
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
        };
    #endif
        BaseData f;     //
        f32 m[3][3];    //
        f32 a[9];       //
        VEC3_ v[3];     //
    //
    };
};

/*
  
  
 */
// Exists mainly for the normal matrix.
// For now, only those things that are definitely necessary are implemented.
class MTX33 : public MTX33_
{
public:
    static const int ROW_COUNT = 3; //
    static const int COLUMN_COUNT = 3; //

    //
    static const MTX33& Identity()
    {
        static const MTX33 identity(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f);

        return identity;
    }

    typedef MTX33 self_type; //
    typedef f32   value_type; //
public:
    //----------------------------------------
    //
    //

    //
    MTX33() {}
    //
    explicit MTX33(const f32* p) { MTX33Copy(this, reinterpret_cast<const MTX33*>(p)); }
    //
    explicit MTX33(const MTX34& rhs) { MTX34ToMTX33(this, &rhs); }
    //
    MTX33(f32 x00, f32 x01, f32 x02,
          f32 x10, f32 x11, f32 x12,
          f32 x20, f32 x21, f32 x22)
    {
        f._00 = x00; f._01 = x01; f._02 = x02;
        f._10 = x10; f._11 = x11; f._12 = x12;
        f._20 = x20; f._21 = x21; f._22 = x22;
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
    self_type& SetupIdentity() { return *MTX33Identity(this); }

    //

    //----------------------------------------
    //
    //

    //
    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX33)) == 0; }

    //
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX33)) != 0; }

    //
    bool IsIdentity() const { return MTX33IsIdentity(this); }

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
typedef class MTX33 Matrix33;

//

}  // namespace math
}  // namespace nn


namespace nn {
namespace math {

template<typename TMatrix>
NN_FORCE_INLINE TMatrix*
MTX33Mult(TMatrix* pOut, const TMatrix* p1, const TMatrix* p2)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX33MULT_CONFIG == D_ORG)
        return ARMv6::MTX33MultC( pOut, p1, p2 );
    #elif (MTX33MULT_CONFIG == D_FAST_C)
    #elif (MTX33MULT_CONFIG == D_FAST_ASM)
        return ARMv6::MTX33MultAsm( pOut, p1, p2 );
    #elif (MTX33MULT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX33MULT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}

NN_FORCE_INLINE MTX33*
MTX33MAdd(MTX33* pOut, f32 t, const MTX33* p1, const MTX33* p2)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX33MADD_CONFIG == D_ORG)
        return ARMv6::MTX33MAddC(pOut, t, p1, p2);
    #elif (MTX33MADD_CONFIG == D_FAST_C)
        return ARMv6::MTX33MAddC_FAST(pOut, t, p1, p2);
    #elif (MTX33MADD_CONFIG == D_FAST_ASM)
        return ARMv6::MTX33MAddAsm(pOut, t, p1, p2);
    #elif (MTX33MADD_CONFIG == D_FAST_C_ALGO)
    #elif (MTX33MADD_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX33*
MTX33Copy(MTX33* pOut, const MTX33* p)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX33COPY_CONFIG == D_ORG)
        return ARMv6::MTX33CopyC(pOut, p);
    #elif (MTX33COPY_CONFIG == D_FAST_C)
    #elif (MTX33COPY_CONFIG == D_FAST_ASM)
        return ARMv6::MTX33CopyAsm(pOut, p);
    #elif (MTX33COPY_CONFIG == D_FAST_C_ALGO)
    #elif (MTX33COPY_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE VEC3*
VEC3Transform(VEC3* pOut, const MTX33* pM, const VEC3* pV)
{
#if defined( NN_HARDWARE_CTR )
    #if (VEC3TRANSFORM_33XVEC3_CONFIG == D_ORG)
        return ARMv6::VEC3TransformC(pOut, pM, pV);
    #elif (VEC3TRANSFORM_33XVEC3_CONFIG == D_FAST_C)
    #elif (VEC3TRANSFORM_33XVEC3_CONFIG == D_FAST_ASM)
        return ARMv6::VEC3TransformAsm(pOut, pM, pV);
    #elif (VEC3TRANSFORM_33XVEC3_CONFIG == D_FAST_C_ALGO)
    #elif (VEC3TRANSFORM_33XVEC3_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

//Overload referencing the -- const argument
template<typename TMatrix>
inline TMatrix* MTX33Mult(TMatrix* pOut, const TMatrix& m1, const TMatrix& m2) { return MTX33Mult( pOut, &m1, &m2 ); }
inline bool   MTX33IsIdentity(const MTX33& m) { return MTX33IsIdentity( &m ); }
inline MTX33* MTX33Copy(MTX33* pOut, const MTX33& m) { return MTX33Copy( pOut, &m ); }
inline MTX33* MTX33MAdd(MTX33* pOut, f32 t, const MTX33& m1, const MTX33& m2) { return MTX33MAdd( pOut, t, &m1, &m2 ); }

}  // namespace math
}  // namespace nn


#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix33.ipp>
#include <nn/math/ARMv6/inline/math_Matrix33.ipp>
#endif

#pragma pop

#endif
