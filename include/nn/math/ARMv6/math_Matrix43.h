/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix43.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_ARMV6_MATRIX43_H_
#define NN_MATH_ARMV6_MATRIX43_H_

#include <nn/math/math_Config.h>

//namespace nn { 
//namespace math {
namespace ARMv6 {

/* ------------------------------------------------------------------------
    MTX43 functions
   ------------------------------------------------------------------------ */

NN_MATH_INLINE MTX43* MTX43CopyC(MTX43* pOut, const MTX43* p);
NN_MATH_INLINE MTX43* MTX43AddC(MTX43* pOut, const MTX43* p1, const MTX43* p2);
NN_MATH_INLINE MTX43* MTX43MultC(MTX43* pOut, const MTX43* p1, const MTX43* p2);
NN_MATH_INLINE MTX43* MTX43MultC(MTX43* pOut, const MTX43* p, f32 f);

MTX43* MTX43CopyAsm(MTX43* pOut, const MTX43* p);
MTX43* MTX43AddAsm(MTX43* pOut, const MTX43* p1, const MTX43* p2);
MTX43* MTX43MultAsm(MTX43* pOut, const MTX43* p1, const MTX43* p2);
MTX43* MTX43MultAsm(MTX43* pOut, const MTX43* p, f32 f);

}  // namespcae ARMv6
//}  // namespace math
//}  // namespace nn


#endif
