/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector3.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARMV6_VECTOR3_H_
#define NN_MATH_ARMV6_VECTOR3_H_

#include <nn/math/math_Config.h>
#include <nn/math/math_Constant.h>

namespace nn { 
namespace math {
namespace ARMv6 {

NN_MATH_INLINE VEC3* VEC3NormalizeC(VEC3* pOut, const VEC3* p);
NN_MATH_INLINE VEC3* VEC3NormalizeC_FAST(VEC3* pOut, const VEC3* p);

}  // namespcae ARMv6
}  // namespace math
}  // namespace nn

#endif
