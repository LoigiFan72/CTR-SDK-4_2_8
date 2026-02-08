/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix33.cpp

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
#include <nn/math/ARMv6/math_Matrix33.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/ARMv6/inline/math_Matrix33.ipp>
#endif

namespace nn {
namespace math {
namespace ARMv6 {

#include <nn/hw/ARM/code32.h>

/* Please see man pages for details 
    
    
*/

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX33* MTX33CopyAsm(MTX33*, const MTX33*)
{
    VLDMIA      r1!,{s0-s4}         // Segment and load to shorten stall times due to data hazards
    MOV         r2, r0              // 
    VLDMIA      r1,{s5-s8}          
    VSTMIA      r2!,{s0-s4}         // Store result
    VSTMIA      r2,{s5-s8}          // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX33* MTX33MAddAsm(MTX33* , f32, const MTX33*, const MTX33*)
{
    VLDMIA      r2,{s1-s9}          // The entire p2 matrix is put in the [S4-S15] registers
    VLDMIA      r1!,{s10-s15}       // Matrix p1 is put into the [S16-S23] registers

    VMLA.F32    s1,s10,s0
    VMLA.F32    s2,s11,s0
    VMLA.F32    s3,s12,s0

    VLDMIA      r1,{s10-s12}        // Continuation of p1

    VMLA.F32    s4,s13,s0
    VMLA.F32    s5,s14,s0
    VMLA.F32    s6,s15,s0

    VMLA.F32    s7,s10,s0
    VMLA.F32    s8,s11,s0
    VMLA.F32    s9,s12,s0

    VSTMIA      r0,{s1-s9}          // Store result
    BX          lr                  // Return

}

NN_FUNC_ATTR_PRIVATE_SECTION
asm VEC3* VEC3TransformAsm(VEC3*, const MTX33*, const VEC3*)
{
    VLDMIA      r1,{s0-s8}          // First line of matrix pM to register [S0-S2]
    VLDMIA      r2,{s9-s11}         // All vectors are put in the [S10-S12] registers

    VMUL.F32    s12,s0,s9
    VMUL.F32    s13,s3,s9
    VMUL.F32    s14,s6,s9

    VMLA.F32    s12,s1,s10
    VMLA.F32    s13,s4,s10
    VMLA.F32    s14,s7,s10

    VMLA.F32    s12,s2,s11
    VMLA.F32    s13,s5,s11
    VMLA.F32    s14,s8,s11

    VSTMIA      r0,{s12-s14}        // Store result

    BX          lr                  // Return

}

#include <nn/hw/ARM/codereset.h>

}  // namespace ARMv6
}  // namespace math
}  // namespace nn
