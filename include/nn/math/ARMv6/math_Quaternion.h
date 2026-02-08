/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Quaternion.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARMV6_MATH_QUATERNION_H_
#define NN_MATH_ARMV6_MATH_QUATERNION_H_

#include <nn/math/math_Config.h>

namespace nn { 
namespace math {
namespace ARMv6 {

NN_MATH_INLINE QUAT* QUATMultC(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2);
NN_MATH_INLINE QUAT* QUATMultC_FAST(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2);
NN_MATH_INLINE QUAT* QUATNormalizeC(QUAT* pOut, const QUAT* __restrict q);
NN_MATH_INLINE QUAT* QUATNormalizeC_FAST(QUAT* pOut, const QUAT* __restrict q);
NN_MATH_INLINE QUAT* QUATInverseC(QUAT* pOut, const QUAT* __restrict q);
NN_MATH_INLINE QUAT* QUATInverseC_FAST(QUAT* pOut, const QUAT* __restrict q);

QUAT* QUATMultAsm(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2);

}  //namespace ARMv6
}  // namespace math
}  // namespace nn


#endif
