/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Types.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Types.h>
#include <nn/types.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Types.ipp>
#include <nn/math/ARMv6/inline/math_Types.ipp>
#endif


namespace nn {
namespace math {
namespace ARMv6 {

#include <nn/hw/ARM/code32.h>

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX33* 
MTX34ToMTX33Asm(MTX33* , const MTX34* )
{
    VLDMIA      r1,{s0-s11}         // The entire pM matrix is put in the [S0-S11] registers
    MOV         r2,r0

    VSTMIA      r2!,{s0-s2}         // Store result
    VSTMIA      r2!,{s4-s6}         // Store result
    VSTMIA      r2,{s8-s10}         // Store result

    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX34* MTX43TransposeAsm(MTX34* , const MTX43* )
{
    VLDR.F32    s0,[r1,#0*12+0*4]
    VLDR.F32    s1,[r1,#1*12+0*4]
    VLDR.F32    s2,[r1,#2*12+0*4]
    VLDR.F32    s3,[r1,#3*12+0*4]
    VLDR.F32    s4,[r1,#0*12+1*4]
    VLDR.F32    s5,[r1,#1*12+1*4]
    VLDR.F32    s6,[r1,#2*12+1*4]
    VLDR.F32    s7,[r1,#3*12+1*4]
    VLDR.F32    s8,[r1,#0*12+2*4]
    VLDR.F32    s9,[r1,#1*12+2*4]
    VLDR.F32    s10,[r1,#2*12+2*4]
    VLDR.F32    s11,[r1,#3*12+2*4]

    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return
}

NN_FUNC_ATTR_PRIVATE_SECTION
asm MTX43* MTX34TransposeAsm(MTX43*, const MTX34*)
{
    VLDR.F32    s0,[r1,#0*16+0*4]
    VLDR.F32    s1,[r1,#1*16+0*4]
    VLDR.F32    s2,[r1,#2*16+0*4]

    VLDR.F32    s3,[r1,#0*16+1*4]
    VLDR.F32    s4,[r1,#1*16+1*4]
    VLDR.F32    s5,[r1,#2*16+1*4]

    VLDR.F32    s6,[r1,#0*16+2*4]
    VLDR.F32    s7,[r1,#1*16+2*4]
    VLDR.F32    s8,[r1,#2*16+2*4]

    VLDR.F32    s9,[r1,#0*16+3*4]
    VLDR.F32    s10,[r1,#1*16+3*4]
    VLDR.F32    s11,[r1,#2*16+3*4]

    VSTMIA      r0,{s0-s11}         // Store result
    BX          lr                  // Return
}

#include <nn/hw/ARM/codereset.h>


}  // namespace ARMv6
}  // namespace math
}  // namespace nn


