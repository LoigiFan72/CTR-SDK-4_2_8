/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Quaternion.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <cmath>
#include <nn/math/math_Quaternion.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Quaternion.ipp>
#include <nn/math/ARMv6/inline/math_Quaternion.ipp>
#endif


namespace nn {
namespace math {
namespace ARMv6 {
#include <nn/hw/ARM/code32.h>

NN_FUNC_ATTR_PRIVATE_SECTION
asm QUAT* QUATMultAsm(QUAT*, const QUAT*, const QUAT* )
{
    VLDMIA      r1,{s4-s7}        // All q1 vectors are put in the [S4-S7] registers
    VLDMIA      r2,{s8-s11}       // All q2 vectors are put in the [S8-S11] registers

    VMUL.F32    s0,s7,s8
    VMUL.F32    s1,s7,s9
    VMUL.F32    s2,s7,s10
    VMUL.F32    s3,s7,s11

    VMLA.F32    s0,s4,s11
    VMLA.F32    s1,s5,s11
    VMLA.F32    s2,s6,s11
    VMLS.F32    s3,s4,s8

    VMLA.F32    s0,s5,s10
    VMLA.F32    s1,s6,s8
    VMLA.F32    s2,s4,s9
    VMLS.F32    s3,s5,s9

    VMLS.F32    s0,s6,s9
    VMLS.F32    s1,s4,s10
    VMLS.F32    s2,s5,s8
    VMLS.F32    s3,s6,s10

    VSTMIA      r0,{s0-s3}          // Store result
    BX          lr                  // Return
}


#include <nn/hw/ARM/codereset.h>

}  // namespace ARMv6
}}  // nw::math

