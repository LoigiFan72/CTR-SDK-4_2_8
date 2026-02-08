/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47498 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_TYPES_H_
#define NN_MATH_TYPES_H_

#include <nn/types.h>
#include <nn/math/math_Config.h>
#include <nn/math/math_Triangular.h>
#include <nn/math/math_Vector2.h>
#include <nn/math/math_Vector3.h>
#include <nn/math/math_Vector4.h>
#include <nn/math/math_Quaternion.h>
#include <nn/math/math_Matrix22.h>
#include <nn/math/math_Matrix23.h>
#include <nn/math/math_Matrix33.h>
#include <nn/math/math_Matrix34.h>
#include <nn/math/math_Matrix44.h>
#include <nn/math/math_Matrix43.h>
#include <nn/math/math_Transform.h>

#include <nn/math/ARMv6/math_Types.h>

#include <cstring>

namespace nn { 
namespace math {

/* =======================================================================
        Class definitions
   ======================================================================== */
struct VEC2;
struct VEC3;
struct VEC4;
struct QUAT;
struct MTX34;
struct MTX43;

/* Please see man pages for details 
    
    
*/

/* ------------------------------------------------------------------------
    MatrixUtility
   ------------------------------------------------------------------------ */

/*
  

  
  

  
 */
NN_MATH_INLINE MTX22* MTX23ToMTX22(MTX22* pOut, const MTX23* pM);

/*
  

  
  

  
 */
NN_MATH_INLINE MTX23* MTX22ToMTX23(MTX23* pOut, const MTX22* pM);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* MTX33ToMTX34(MTX34* pOut, const MTX33* pM);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX33* MTX34ToMTX33(MTX33* pOut, const MTX34* pM);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* QUATToMTX34(MTX34* pOut, const QUAT* pQ);

/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* QUATToMTX34Partially(MTX34* pOut, const QUAT* pQ);

/*
  

  
  

  
 */
NN_FORCE_INLINE QUAT* MTX34ToQUAT(QUAT* pOut, const MTX34* pMtx);

/*  

*/
/* Please see man pages for details 
    
    
*/

/*
  

  

  
  

  
 */
NN_FORCE_INLINE MTX43* MTX34Transpose(MTX43* pOut, const MTX34* p);

/*  

*/
/* Please see man pages for details 
    
    
*/


/*
  

  
  

  
 */
NN_FORCE_INLINE MTX34* MTX43Transpose(MTX34* pOut, const MTX43* p);

/*  

*/

NN_FORCE_INLINE MTX34*
MTX33ToMTX34(MTX34* pOut, const MTX33* pM)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX33TOMTX34_CONFIG == D_ORG)
        return ARMv6::MTX33ToMTX34C(pOut, pM);
    #elif (MTX33TOMTX34_CONFIG == D_FAST_C)
        return ARMv6::MTX33ToMTX34C_FAST(pOut, pM);
    #elif (MTX33TOMTX34_CONFIG == D_FAST_ASM)
    #elif (MTX33TOMTX34_CONFIG == D_FAST_C_ALGO)
    #elif (MTX33TOMTX34_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}

NN_FORCE_INLINE MTX33* 
MTX34ToMTX33(MTX33* pOut, const MTX34* pM)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34TOMTX33_CONFIG == D_ORG)
        return ARMv6::MTX34ToMTX33C(pOut, pM);
    #elif (MTX34TOMTX33_CONFIG == D_FAST_C)
    #elif (MTX34TOMTX33_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34ToMTX33Asm(pOut, pM);
    #elif (MTX34TOMTX33_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34TOMTX33_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}

NN_FORCE_INLINE QUAT*
MTX34ToQUAT(QUAT* pOut, const MTX34* pMtx)
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34TOQUAT_CONFIG == D_ORG)
        return ARMv6::MTX34ToQUATC(pOut, pMtx);
    #elif (MTX34TOQUAT_CONFIG == D_FAST_C)
        return ARMv6::MTX34ToQUATC_FAST(pOut, pMtx);
    #elif (MTX34TOQUAT_CONFIG == D_FAST_ASM)
    #elif (MTX34TOQUAT_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34TOQUAT_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}

NN_FORCE_INLINE MTX34*
QUATToMTX34(MTX34* pOut, const QUAT* pQ)
{
#if defined( NN_HARDWARE_CTR )
    #if (QUATTOMTX34_CONFIG == D_ORG)
        return ARMv6::QUATToMTX34C(pOut, pQ);
    #elif (QUATTOMTX34_CONFIG == D_FAST_C)
        return ARMv6::QUATToMTX34C_FAST(pOut, pQ);
    #elif (QUATTOMTX34_CONFIG == D_FAST_ASM)
    #elif (QUATTOMTX34_CONFIG == D_FAST_C_ALGO)
    #elif (QUATTOMTX34_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX34*
QUATToMTX34Partially(MTX34* pOut, const QUAT* pQ)
{
#if defined( NN_HARDWARE_CTR )
    #if (QUATTOMTX34_CONFIG == D_ORG)
        return ARMv6::QUATToMTX34C(pOut, pQ, false);
    #elif (QUATTOMTX34_CONFIG == D_FAST_C)
        return ARMv6::QUATToMTX34C_FAST(pOut, pQ, false);
    #elif (QUATTOMTX34_CONFIG == D_FAST_ASM)
    #elif (QUATTOMTX34_CONFIG == D_FAST_C_ALGO)
    #elif (QUATTOMTX34_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif // #if defined( NN_HARDWARE_CTR )
}

NN_FORCE_INLINE MTX43*
MTX34Transpose(MTX43* pOut, const MTX34* p) 
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX34TRANSPOSE_34TO43_CONFIG == D_ORG)
        return ARMv6::MTX34TransposeC(pOut, p);
    #elif (MTX34TRANSPOSE_34TO43_CONFIG == D_FAST_C)
    #elif (MTX34TRANSPOSE_34TO43_CONFIG == D_FAST_ASM)
        return ARMv6::MTX34TransposeAsm(pOut, p);
    #elif (MTX34TRANSPOSE_34TO43_CONFIG == D_FAST_C_ALGO)
    #elif (MTX34TRANSPOSE_34TO43_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif
}

NN_FORCE_INLINE MTX34*
MTX43Transpose(MTX34* pOut, const MTX43* p) 
{
#if defined( NN_HARDWARE_CTR )
    #if (MTX43TRANSPOSE_CONFIG == D_ORG)
        return ARMv6::MTX43TransposeC(pOut, p);
    #elif (MTX43TRANSPOSE_CONFIG == D_FAST_C)
    #elif (MTX43TRANSPOSE_CONFIG == D_FAST_ASM)
        return ARMv6::MTX43TransposeAsm(pOut, p);
    #elif (MTX43TRANSPOSE_CONFIG == D_FAST_C_ALGO)
    #elif (MTX43TRANSPOSE_CONFIG == D_FAST_ASM_ALGO)
    #endif
#else
#endif

}

}  // namespace math
}  // namespace nn


#if defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Types.ipp>
#include <nn/math/ARMv6/inline/math_Types.ipp>
#endif

namespace nn { 
namespace math {

//Overload referencing the -- const argument
inline MTX22* MTX23ToMTX22(MTX22* pOut, const MTX23& m) { return MTX23ToMTX22(pOut, &m); }
inline MTX23* MTX22ToMTX23(MTX23* pOut, const MTX22& m) { return MTX22ToMTX23( pOut, &m ); }
inline MTX33* MTX34ToMTX33(MTX33* pOut, const MTX34& m) { return MTX34ToMTX33( pOut, &m ); }
inline MTX34* MTX33ToMTX34(MTX34* pOut, const MTX33& m) { return MTX33ToMTX34( pOut, &m ); }
inline QUAT*  MTX34ToQUAT(QUAT* pOut, const MTX34& mtx) { return MTX34ToQUAT( pOut, &mtx ); }
inline MTX34* QUATToMTX34(MTX34* pOut, const QUAT& q) { return QUATToMTX34( pOut, &q ); }
inline MTX34* MTX43Transpose(MTX34* pOut, const MTX43& m) { return MTX43Transpose( pOut, &m ); }
inline MTX43* MTX34Transpose(MTX43* pOut, const MTX34& m) { return MTX34Transpose( pOut, &m ); }

}  // namespace math
}  // namespace nn

#endif


