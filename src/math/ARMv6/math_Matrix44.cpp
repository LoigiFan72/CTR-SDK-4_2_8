/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix44.cpp

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
#include <nn/math/math_Matrix44.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/ARMv6/inline/math_Matrix44.ipp>
#endif


namespace nn{
namespace math {
namespace ARMv6 {
#include <nn/hw/ARM/code32.h>

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44AddAsm(MTX44* , const MTX44* , const MTX44* )
{
    VPUSH       {d8-d11}            // Save registers
    VLDMIA      r2,{s0-s15}         // The entire p2 matrix is put in the [S0-S15] registers
    VLDMIA      r1!,{s16-s23}       // Matrix p1 is put into the [S16-S23] registers

    VADD.F32    s0,s16,s0
    VADD.F32    s1,s17,s1
    VADD.F32    s2,s18,s2
    VADD.F32    s3,s19,s3

    VLDMIA      r1!,{s16-s19}       // Continuation of p1

    VADD.F32    s4,s20,s4
    VADD.F32    s5,s21,s5
    VADD.F32    s6,s22,s6
    VADD.F32    s7,s23,s7

    VLDMIA      r1!,{s20-s23}       // Continuation of p1

    VADD.F32    s8,s16,s8
    VADD.F32    s9,s17,s9
    VADD.F32    s10,s18,s10
    VADD.F32    s11,s19,s11

    VADD.F32    s12,s20,s12
    VADD.F32    s13,s21,s13
    VADD.F32    s14,s22,s14
    VADD.F32    s15,s23,s15

    VPOP        {d8-d11}            // Register return
    VSTMIA      r0,{s0-s15}         // Store result
    BX          lr                  // Return

}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44CopyAsm(MTX44* , const MTX44* )
{
    CMP         r1,r0           // Are p and pOut the same?
    BXEQ        lr              // If the same, returns without copying
    VLDMIA      r1,{s0-s15}     // All p are put in the [S0-S15] registers
    VSTMIA      r0,{s0-s15}     // All pOut are put in the [S0-S15] registers
    BX          lr
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44MultAsm(MTX44* , const MTX44* , const MTX44* )
{
    VPUSH       {d8-d12}            // Save registers

    VLDMIA      r2!,{s16-s23}       // Matrix p2 is put into the [S16-S23] registers
    VLDR.F32    s24,[r1,#16*0+0*4]  // p1[0][0]
    VLDR.F32    s25,[r1,#16*1+0*4]  // p1[1][0]

    VMUL.F32    s0,s24,s16
    VMUL.F32    s1,s24,s17
    VMUL.F32    s2,s24,s18
    VMUL.F32    s3,s24,s19
    VLDR.F32    s24,[r1,#16*2+0*4]  // p1[2][0]

    VMUL.F32    s4,s25,s16
    VMUL.F32    s5,s25,s17
    VMUL.F32    s6,s25,s18
    VMUL.F32    s7,s25,s19
    VLDR.F32    s25,[r1,#16*3+0*4]  // p1[3][0]

    VMUL.F32    s8,s24,s16
    VMUL.F32    s9,s24,s17
    VMUL.F32    s10,s24,s18
    VMUL.F32    s11,s24,s19
    VLDR.F32    s24,[r1,#16*0+1*4]  // p1[0][1]

    VMUL.F32    s12,s25,s16
    VMUL.F32    s13,s25,s17
    VMUL.F32    s14,s25,s18
    VMUL.F32    s15,s25,s19
    VLDR.F32    s25,[r1,#16*1+1*4]  // p1[1][1]

    VLDMIA      r2!,{s16-s19}       // Matrix p2 is put into the [S16-S19] registers

    VMLA.F32    s0,s24,s20
    VMLA.F32    s1,s24,s21
    VMLA.F32    s2,s24,s22
    VMLA.F32    s3,s24,s23
    VLDR.F32    s24,[r1,#16*2+1*4]  // p1[2][1]

    VMLA.F32    s4,s25,s20
    VMLA.F32    s5,s25,s21
    VMLA.F32    s6,s25,s22
    VMLA.F32    s7,s25,s23
    VLDR.F32    s25,[r1,#16*3+1*4]  // p1[3][1]

    VMLA.F32    s8,s24,s20
    VMLA.F32    s9,s24,s21
    VMLA.F32    s10,s24,s22
    VMLA.F32    s11,s24,s23
    VLDR.F32    s24,[r1,#16*0+2*4]  // p1[0][2]

    VMLA.F32    s12,s25,s20
    VMLA.F32    s13,s25,s21
    VMLA.F32    s14,s25,s22
    VMLA.F32    s15,s25,s23
    VLDR.F32    s25,[r1,#16*1+2*4]  // p1[1][2]

    VLDMIA      r2,{s20-s23}        // Matrix p2 is put into the [S20-S23] registers

    VMLA.F32    s0,s24,s16
    VMLA.F32    s1,s24,s17
    VMLA.F32    s2,s24,s18
    VMLA.F32    s3,s24,s19
    VLDR.F32    s24,[r1,#16*2+2*4]  // p1[2][2]

    VMLA.F32    s4,s25,s16
    VMLA.F32    s5,s25,s17
    VMLA.F32    s6,s25,s18
    VMLA.F32    s7,s25,s19
    VLDR.F32    s25,[r1,#16*3+2*4]  // p1[3][2]

    VMLA.F32    s8,s24,s16
    VMLA.F32    s9,s24,s17
    VMLA.F32    s10,s24,s18
    VMLA.F32    s11,s24,s19
    VLDR.F32    s24,[r1,#16*0+3*4]  // p1[0][3]

    VMLA.F32    s12,s25,s16
    VMLA.F32    s13,s25,s17
    VMLA.F32    s14,s25,s18
    VMLA.F32    s15,s25,s19
    VLDR.F32    s25,[r1,#16*1+3*4]  // p1[1][3]

    VMLA.F32    s0,s24,s20
    VMLA.F32    s1,s24,s21
    VMLA.F32    s2,s24,s22
    VMLA.F32    s3,s24,s23
    VLDR.F32    s24,[r1,#16*2+3*4]  // p1[2][3]

    VMLA.F32    s4,s25,s20
    VMLA.F32    s5,s25,s21
    VMLA.F32    s6,s25,s22
    VMLA.F32    s7,s25,s23
    VLDR.F32    s25,[r1,#16*3+3*4]  // p1[3][3]

    VMLA.F32    s8,s24,s20
    VMLA.F32    s9,s24,s21
    VMLA.F32    s10,s24,s22
    VMLA.F32    s11,s24,s23

    VMLA.F32    s12,s25,s20
    VMLA.F32    s13,s25,s21
    VMLA.F32    s14,s25,s22
    VMLA.F32    s15,s25,s23

    VPOP        {d8-d12}            // Register return
    VSTMIA      r0,{s0-s15}         // Store result
    BX          lr                  // Return

}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44MultAsm(MTX44* , const MTX44* , f32 )
{
    VPUSH       {d8}               // Save registers
    VLDMIA      r1!,{s16}          // Matrix p is put into the [S2-S17] registers
    VLDMIA      r1,{s1-s15}        // Matrix p is put into the [S2-S17] registers

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
    VMUL.F32    s13,s13,s0
    VMUL.F32    s14,s14,s0
    VMUL.F32    s15,s15,s0

    VMUL.F32    s0,s16,s0
    VPOP        {d8}                // Register return
    VSTMIA      r0,{s0-s15}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44MultScaleAsm(MTX44*, const MTX44*, const VEC3*)
{
    VLDMIA      r1,{s0-s11}        // Matrix p is put into the [S0-S11] registers
    VLDMIA      r2,{s12-s14}       // VEC3 is put into the [S12-S14] registers

    VMUL.F32    s0,s0,s12
    VMUL.F32    s1,s1,s13
    VMUL.F32    s2,s2,s14

    VMUL.F32    s4,s4,s12
    VMUL.F32    s5,s5,s13
    VMUL.F32    s6,s6,s14

    VMUL.F32    s8,s8,s12
    VMUL.F32    s9,s9,s13
    VMUL.F32    s10,s10,s14

    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44MultScaleAsm(MTX44*, const VEC3*, const MTX44*)
{
    VLDMIA      r2,{s0-s11}        // Matrix p is put into the [S0-S11] registers
    VLDMIA      r1,{s12-s14}       // VEC3 is put into the [S12-S14] registers

    VMUL.F32    s0,s0,s12
    VMUL.F32    s1,s1,s12
    VMUL.F32    s2,s2,s12
    VMUL.F32    s3,s3,s12

    VMUL.F32    s4,s4,s13
    VMUL.F32    s5,s5,s13
    VMUL.F32    s6,s6,s13
    VMUL.F32    s7,s7,s13

    VMUL.F32    s8,s8,s14
    VMUL.F32    s9,s9,s14
    VMUL.F32    s10,s10,s14
    VMUL.F32    s11,s11,s14

    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44MultTranslateAsm(MTX44*, const VEC3*, const MTX44*)
{
    VLDMIA      r2,{s0-s11}         // The entire pM matrix is put in the [S0-S11] registers
    VLDMIA      r1,{s12-s14}        // All vectors are put in the [S12-S14] registers
    
    VADD.F32    s3,s3,s12
    VADD.F32    s7,s7,s13
    VADD.F32    s11,s11,s14

    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44MultTranslateAsm(MTX44*, const MTX44*, const VEC3*)
{
    VLDMIA      r1!,{s0-s11}        // Matrix pM is put into the [S0-S11] registers
    VLDMIA      r2,{s12-s14}        // All vectors are put in the [S12-S14] registers

    VMLA.F32    s3,s0,s12
    VMLA.F32    s7,s4,s12
    VMLA.F32    s11,s8,s12

    VMLA.F32    s3,s1,s13
    VMLA.F32    s7,s5,s13
    VMLA.F32    s11,s9,s13

    VMLA.F32    s3,s2,s14
    VMLA.F32    s7,s6,s14
    VMLA.F32    s11,s10,s14

    VLDMIA      r1!,{s12-s15}       // Matrix pM is put into the [S12-S15] registers

    VSTMIA      r0,{s0-s15}         // Store result
    BX          lr                  // Return

}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX44* MTX44TransposeAsm(MTX44* , const MTX44*)
{
    VLDR.F32    s0,[r1,#0*16+0*4]
    VLDR.F32    s1,[r1,#1*16+0*4]
    VLDR.F32    s2,[r1,#2*16+0*4]
    VLDR.F32    s3,[r1,#3*16+0*4]
    VLDR.F32    s4,[r1,#0*16+1*4]
    VLDR.F32    s5,[r1,#1*16+1*4]
    VLDR.F32    s6,[r1,#2*16+1*4]
    VLDR.F32    s7,[r1,#3*16+1*4]
    VLDR.F32    s8,[r1,#0*16+2*4]
    VLDR.F32    s9,[r1,#1*16+2*4]
    VLDR.F32    s10,[r1,#2*16+2*4]
    VLDR.F32    s11,[r1,#3*16+2*4]
    VLDR.F32    s12,[r1,#0*16+3*4]
    VLDR.F32    s13,[r1,#1*16+3*4]
    VLDR.F32    s14,[r1,#2*16+3*4]
    VLDR.F32    s15,[r1,#3*16+3*4]

    VSTMIA      r0,{s0-s15}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm VEC4* VEC3TransformAsm(VEC4*, const MTX44*, const VEC3*)
{
    VPUSH       {d8-d9}             // Save registers

    VLDMIA      r1,{s0-s15}         // The entire pM matrix is put in the [S0-S15] registers
    VLDMIA      r2,{s16-s18}        // All vectors are put in the [S16-S18] registers

    VMLA.F32    s3,s0,s16
    VMLA.F32    s7,s4,s16
    VMLA.F32    s11,s8,s16
    VMLA.F32    s15,s12,s16

    VMLA.F32    s3,s1,s17
    VMLA.F32    s7,s5,s17
    VMLA.F32    s11,s9,s17
    VMLA.F32    s15,s13,s17

    VMLA.F32    s3,s2,s18
    VMLA.F32    s7,s6,s18
    VMLA.F32    s11,s10,s18
    VMLA.F32    s15,s14,s18

    VPOP        {d8-d9}             // Register return

    VSTR.F32    s3,[r0,#0]
    VSTR.F32    s7,[r0,#4]
    VSTR.F32    s11,[r0,#8]         // Store result
    VSTR.F32    s15,[r0,#12]        // Store result

    BX          lr                  // Return

}

#include <nn/hw/ARM/codereset.h>

}  // namespace ARMv6
}  // namespace math
}  // namespace nn
