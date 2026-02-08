/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix44.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARMV6_MATRIX44_H_
#define NN_MATH_ARMV6_MATRIX44_H_

namespace nn { 
namespace math {
namespace ARMv6 {

NN_MATH_INLINE VEC4* VEC3TransformC(VEC4* pOut, const MTX44* pM, const VEC3* pV);
NN_MATH_INLINE MTX44* MTX44CopyC(MTX44* pOut, const MTX44* p);
NN_MATH_INLINE MTX44* MTX44AddC(MTX44* pOut, const MTX44* p1, const MTX44* p2);
NN_MATH_INLINE MTX44* MTX44MultC(MTX44* pOut, const MTX44* p, f32 f);
NN_MATH_INLINE MTX44* MTX44TransposeC(MTX44* pOut, const MTX44 *pSrc);
NN_MATH_INLINE MTX44* MTX44PerspectiveRadC(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f);
NN_MATH_INLINE MTX44* MTX44PerspectiveRadC_FAST(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f);
NN_MATH_INLINE MTX44* MTX44FrustumC(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NN_MATH_INLINE MTX44* MTX44FrustumC_FAST(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NN_MATH_INLINE MTX44* MTX44OrthoC(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NN_MATH_INLINE MTX44* MTX44OrthoC_FAST(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NN_MATH_INLINE MTX44* MTX44MultC(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2);
NN_MATH_INLINE u32 MTX44InverseC(MTX44* pOut, const MTX44* p);
NN_MATH_INLINE u32 MTX44InverseC_FAST_ALGO(MTX44* pOut, const MTX44* p);
NN_MATH_INLINE MTX44* MTX44RotAxisRad_C( MTX44* pOut, const VEC3 *pAxis, f32 fRad );
NN_MATH_INLINE MTX44* MTX44RotAxisRad_C_FAST( MTX44* pOut, const VEC3 *pAxis, f32 fRad );
NN_MATH_INLINE MTX44* MTX44RotXYZFIdxC(MTX44* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ);
NN_MATH_INLINE MTX44* MTX44RotXYZFIdxC_FAST(MTX44* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ);
NN_MATH_INLINE MTX44* MTX44ScaleC(MTX44* pOut, const VEC3* pS);
NN_MATH_INLINE MTX44* MTX44ScaleC_FAST(MTX44* pOut, const VEC3* pS);
NN_MATH_INLINE MTX44* MTX44MultScaleC(MTX44* pOut, const MTX44* pM, const VEC3* pS);
NN_MATH_INLINE MTX44* MTX44MultScaleC(MTX44* pOut, const VEC3* pS, const MTX44* pM);
NN_MATH_INLINE MTX44* MTX44TranslateC(MTX44* pOut, const VEC3* pT);
NN_MATH_INLINE MTX44* MTX44TranslateC_FAST(MTX44* pOut, const VEC3* pT);
NN_MATH_INLINE MTX44* MTX44MultTranslateC(MTX44* pOut, const VEC3* pT, const MTX44* pM);
NN_MATH_INLINE MTX44* MTX44MultTranslateC(MTX44* pOut, const MTX44* pM, const VEC3* pT);

inline MTX44*  MTX44PivotC( MTX44* pOut, PivotDirection pivot );
inline MTX44*  MTX44PivotC_FAST( MTX44* pOut, PivotDirection pivot );

MTX44* MTX44AddAsm(MTX44* pOut, const MTX44* p1, const MTX44* p2);
MTX44* MTX44CopyAsm(MTX44* pOut, const MTX44* p);
MTX44* MTX44MultAsm(MTX44* pOut, const MTX44* p, f32 f);
MTX44* MTX44MultAsm(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2);
MTX44* MTX44MultScaleAsm(MTX44* pOut, const MTX44* pM, const VEC3* pS);
MTX44* MTX44MultScaleAsm(MTX44* pOut, const VEC3* pS, const MTX44* pM);
MTX44* MTX44MultTranslateAsm(MTX44* pOut, const VEC3* pT, const MTX44* pM);
MTX44* MTX44MultTranslateAsm(MTX44* pOut, const MTX44* pM, const VEC3* pT);
MTX44* MTX44TransposeAsm(MTX44* pOut, const MTX44 *pSrc);
VEC4* VEC3TransformAsm(VEC4* pOut, const MTX44* pM, const VEC3* pV);
}  // namespace ARMv6
}  // namespace math
}  // namespace nn


#endif
