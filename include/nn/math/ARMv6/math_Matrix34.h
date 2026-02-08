/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix34.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47498 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARMV6_MATH_MATRIX34_H_
#define NN_MATH_ARMV6_MATH_MATRIX34_H_

#include <cstring>
#include <nn/math/math_Config.h>

#pragma push
#pragma Otime

namespace nn { 
namespace math {
namespace ARMv6 {

MTX34* MTX34CopyAsm(MTX34* pOut, const MTX34* p);
MTX34* MTX34MultAsm(MTX34* pOut, const MTX34* p1, const MTX34* p2);
MTX34* MTX34MultAsm_ORG(MTX34* pOut, const MTX34* p1, const MTX34* p2);
MTX34* MTX34MultAsm(MTX34* pOut, const MTX34* p, f32 f);
MTX34* MTX34AddAsm(MTX34* pOut, const MTX34* p1, const MTX34* p2);
u32    MTX34InverseAsm(MTX34* pOut, const MTX34* p);
u32    MTX34InvTransposeAsm(MTX34* pOut, const MTX34* __restrict p);
MTX34* MTX34MAddAsm(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2);
MTX34* MTX34MultScaleAsm(MTX34* pOut, const MTX34* pM, const VEC3* pS);
MTX34* MTX34MultScaleAsm(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM);
MTX34* MTX34MultTranslateAsm(MTX34* pOut, const VEC3* pT, const MTX34* pM);
MTX34* MTX34MultTranslateAsm(MTX34* pOut, const MTX34* pM, const VEC3* pT);
MTX34* MTX34ScaleAsm(MTX34* pOut, const VEC3* pS);
MTX34* MTX34TransposeAsm(MTX34* pOut, const MTX34* p);
VEC3*  VEC3TransformAsm(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV);

NN_MATH_INLINE MTX34* MTX34ScaleC_FAST(MTX34* pOut, const VEC3* pS);
NN_MATH_INLINE MTX34* MTX34TranslateC_FAST(MTX34* pOut, const VEC3* pT);
NN_MATH_INLINE MTX34* MTX34RotAxisRad_C_FAST( MTX34* pOut, const VEC3 *pAxis, f32 fRad, bool isChangeTrans = true);
NN_MATH_INLINE MTX34* MTX34RotXYZFIdxC_FAST(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, bool isChangeTrans = true);
NN_MATH_INLINE MTX34* MTX34LookAtC_FAST(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget);
NN_MATH_INLINE MTX34* MTX34LookAtC_FAST(MTX34* pOut, const VEC3* pCamPos, f32 twist, const VEC3* pTarget);
NN_MATH_INLINE MTX34* MTX34CameraRotateC_FAST(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotate);
NN_MATH_INLINE MTX34* QUATToMTX34C_FAST(MTX34* pOut, const QUAT* pQ, bool isChangeTrans = true);


NN_MATH_INLINE VEC3*  VEC3TransformC(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV);
NN_MATH_INLINE MTX34* MTX34CopyC(MTX34* pOut, const MTX34* p);
NN_MATH_INLINE MTX34* MTX34MultC(MTX34* pOut, const MTX34* __restrict p1, const MTX34* __restrict p2);
NN_MATH_INLINE MTX34* MTX34MultC(MTX34* pOut, const MTX34* p, f32 f);
NN_MATH_INLINE MTX34* MTX34AddC(MTX34* pOut, const MTX34* p1, const MTX34* p2);
NN_MATH_INLINE MTX34* MTX34ScaleC(MTX34* pOut, const VEC3* pS);
NN_MATH_INLINE MTX34* MTX34MultScaleC(MTX34* pOut, const MTX34* pM, const VEC3* pS);
NN_MATH_INLINE MTX34* MTX34MultScaleC(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM);
NN_MATH_INLINE MTX34* MTX34TranslateC(MTX34* pOut, const VEC3* pT);
NN_MATH_INLINE MTX34* MTX34MultTranslateC(MTX34* pOut, const VEC3* pT, const MTX34* pM);
NN_MATH_INLINE MTX34* MTX34MultTranslateC(MTX34* pOut, const MTX34* pM, const VEC3* pT);
NN_MATH_INLINE MTX34* MTX34MAddC(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2);
NN_MATH_INLINE MTX34* MTX34RotAxisRad_C( MTX34* pOut, const VEC3 *pAxis, f32 fRad, bool isChangeTrans = true );
NN_MATH_INLINE MTX34* MTX34RotXYZFIdxC(MTX34* pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, bool isChangeTrans = true );
NN_MATH_INLINE u32    MTX34InverseC(MTX34* pOut, const MTX34* p);
NN_MATH_INLINE MTX34* MTX34TransposeC(MTX34* pOut, const MTX34* p);
NN_MATH_INLINE u32    MTX34InvTransposeC(MTX34* pOut, const MTX34* __restrict p);
NN_MATH_INLINE MTX34* MTX34LookAtC(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget);
NN_MATH_INLINE MTX34* MTX34LookAtC(MTX34* pOut, const VEC3* pCamPos, f32 twist, const VEC3* pTarget);
NN_MATH_INLINE MTX34* MTX34CameraRotateC(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotate);
NN_MATH_INLINE MTX34* QUATToMTX34C(MTX34* pOut, const QUAT* pQ, bool isChangeTrans = true);

}  // namespcae ARMv6
}  // namespace math
}  // namespace nn


#pragma pop

/* NN_MATH_ARMV6_MATH_MATRIX34_H_ */
#endif
