/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix43.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Matrix43.h>
#include <nn/math/ARMv6/math_Matrix43.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix43.ipp>
#include <nn/math/ARMv6/inline/math_Matrix43.ipp>
#endif


namespace nn {
namespace math {
namespace ARMv6 {

#include <nn/hw/ARM/code32.h>

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX43* 
MTX43CopyAsm(MTX43* , const MTX43*)
{
    CMP         r1,r0           // Are p and pOut the same?
    BXEQ        lr              // If the same, returns without copying
    VLDMIA      r1,{s0-s11}     // All p are put in the [S0-S11] registers
    VSTMIA      r0,{s0-s11}     // All pOut are put in the [S0-S11] registers
    BX          lr
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX43* 
MTX43AddAsm(MTX43* , const MTX43* , const MTX43* )
{
    VPUSH       {d8-d9}             // Save registers
    VLDMIA      r2,{s0-s11}         // The entire p2 matrix is put in the [S0-S11] registers
    VLDMIA      r1!,{s12-s19}       // Matrix p1 is put into the [S12-S19] registers

    VADD.F32    s0,s12,s0
    VADD.F32    s1,s13,s1
    VADD.F32    s2,s14,s2
    VADD.F32    s3,s15,s3
    VLDMIA      r1,{s12-s15}        // Continuation of p1
    
    VADD.F32    s4,s16,s4
    VADD.F32    s5,s17,s5
    VADD.F32    s6,s18,s6
    VADD.F32    s7,s19,s7

    VADD.F32    s8,s12,s8
    VADD.F32    s9,s13,s9
    VADD.F32    s10,s14,s10
    VADD.F32    s11,s15,s11

    VPOP        {d8-d9}             // Register return
    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX43* 
MTX43MultAsm(MTX43*, const MTX43*, const MTX43*)
{
    VPUSH       {d8-d15}            // Save registers

    VLDR.F32    s9,[r2,#3*3*4]      // Matrix p2[3][0]
    VLDR.F32    s10,[r2,#4+3*3*4]   // Matrix p2[3][1]
    VLDR.F32    s11,[r2,#8+3*3*4]   // Matrix p2[3][2]

    VLDMIA      r1,{s12-s23}        // The entire matrix p1 is put into the [S12-S23] registers
    VLDMIA      r2!,{s24-s29}       // Matrix p2 is put into the [S24-S29] registers

    VMUL.F32    s0,s12,s24
    VMUL.F32    s1,s12,s25
    VMUL.F32    s2,s12,s26

    VMUL.F32    s3,s15,s24
    VMUL.F32    s4,s15,s25
    VMUL.F32    s5,s15,s26

    VMUL.F32    s6,s18,s24
    VMUL.F32    s7,s18,s25
    VMUL.F32    s8,s18,s26

    VMLA.F32    s9,s21,s24
    VMLA.F32    s10,s21,s25
    VMLA.F32    s11,s21,s26

    VMLA.F32    s0,s13,s27
    VMLA.F32    s1,s13,s28
    VMLA.F32    s2,s13,s29

    VMLA.F32    s3,s16,s27
    VMLA.F32    s4,s16,s28
    VMLA.F32    s5,s16,s29

    VLDMIA      r2,{s24-s26}        // Continuation of p2

    VMLA.F32    s6,s19,s27
    VMLA.F32    s7,s19,s28
    VMLA.F32    s8,s19,s29

    VMLA.F32    s9,s22,s27
    VMLA.F32    s10,s22,s28
    VMLA.F32    s11,s22,s29

    VMLA.F32    s0,s14,s24
    VMLA.F32    s1,s14,s25
    VMLA.F32    s2,s14,s26

    VMLA.F32    s3,s17,s24
    VMLA.F32    s4,s17,s25
    VMLA.F32    s5,s17,s26

    VMLA.F32    s6,s20,s24
    VMLA.F32    s7,s20,s25
    VMLA.F32    s8,s20,s26

    VMLA.F32    s9,s23,s24
    VMLA.F32    s10,s23,s25
    VMLA.F32    s11,s23,s26

    VPOP        {d8-d15}            // Register return
    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return

}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX43* 
MTX43MultAsm(MTX43*, const MTX43*, f32)
{
    VLDMIA      r1,{s1-s12}        // Matrix p is put into the [S1-S12] registers

    VMUL.F32    s1,s1,s0
    VMUL.F32    s2,s2,s0
    VMUL.F32    s3,s3,s0
    VMUL.F32    s4,s4,s0

    VMUL.F32    s5,s5,s0
    VMUL.F32    s6,s6,s0
    VMUL.F32    s7,s7,s0
    VMUL.F32    s8,s8,s0

    VMUL.F32    s9,s9,s0
    VMUL.F32    s10,s10,s0
    VMUL.F32    s11,s11,s0
    VMUL.F32    s12,s12,s0

    VSTMIA      r0,{s1-s12}         // Store result
    BX          lr                  // Return

}

#include <nn/hw/ARM/codereset.h>

}  // namespace ARMv6
}  // namespace math
}  // namespace nn
