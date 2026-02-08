/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Triangular.cpp

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
#include <nn/math/ARMv6/math_Triangular.h>

namespace nn { namespace math {

namespace ARMv6 {
#include <nn/hw/ARM/code32.h>

NN_FUNC_ATTR_PRIVATE_SECTION
asm void SinCosIdxAsm(f32* /* s */, f32* /* c */, u16 /* idx */)
{
    IMPORT      __cpp(nn::math::internal::gSinCosTbl)[DATA]
    AND         r3,r2,#0xff
    VMOV        s4,r3
    LSR         r3,r2,#8
    LDR         r2,=__cpp(nn::math::internal::gSinCosTbl)
    VCVT.F32.U32 s4,s4
    ADD         r2,r2,r3,LSL #4
    VLDR        s5,%F0
    VMUL.F32    s6,s4,s5
    VLDM        r2,{s0-s3}
    VMLA.F32    s0,s2,s6
    VMLA.F32    s1,s3,s6
    VSTR        s0,[r0,#0]
    VSTR        s1,[r1,#0]
    BX          lr
0
    DCD         0x3b800000      // 1.0f / 256.0f
}

#include <nn/hw/ARM/codereset.h>
} // ARMv6
}}  // nw::math
