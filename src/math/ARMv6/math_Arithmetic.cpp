/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Arithmetic.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/ARMv6/math_Arithmetic.h>
#include <cstdlib>

namespace nn {
namespace math {
namespace ARMv6 {

    #include <nn/hw/ARM/code32.h>
    
    NN_FUNC_ATTR_PRIVATE_SECTION
    asm f32
    HermiteAsm(f32 /* v0 */, f32 /* t0 */, f32 /* v1 */, f32 /* t1 */, f32 /* p */, f32 /* d */)
    {
        VDIV.F32    s6,s4,s5        //s = p/d
        VLDR.F32    s7,%F1          //s7=1.0
        VLDR.F32    s8,%F2          //s8=2.0
        VLDR.F32    s9,%F3          //s9=3.0
        VSUB.F32    s10,s0,s2       //v0-v1
        VSUB.F32    s11,s6,s7       //s_1
        VMUL.F32    s12,s6,s6       //s*s
        VNMLS.F32   s9,s6,s8        //2*s-3
        VMUL.F32    s13,s6,s3       //s*t1
        VMUL.F32    s14,s4,s11      //p*s_1
        VMUL.F32    s15,s10,s9
        VMLA.F32    s13,s11,s1
        VMLA.F32    s0,s15,s12
        VMLA.F32    s0,s13,s14
        BX          lr
        
1
        DCD         0x3F800000
2
        DCD         0x40000000
3
        DCD         0x40400000
    }
    
    #include <nn/hw/ARM/codereset.h>




}}}  // nn::math::ARMv6
