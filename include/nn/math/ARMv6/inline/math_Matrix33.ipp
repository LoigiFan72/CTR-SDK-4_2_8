/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix33.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 13623 $
 *---------------------------------------------------------------------------*/
#include <nn/math/math_Vector3.h>

namespace nn { 
namespace math {
namespace ARMv6 {

#include <nn/hw/ARM/code32.h>
/* Please see man pages for details 
    
    
*/

template<typename TMatrix>
inline asm TMatrix* 
MTX33MultAsm_ORG(TMatrix*, const TMatrix*, const TMatrix*)
{
    VPUSH       {d8-d13}            // Save registers

    //Because a template is being used, calculate an offset value for the matrix...
    MOV         r3,#__cpp(offsetof(TMatrix,f))
    ADD         r1,r1,r3
    ADD         r2,r2,r3
    MOV         r3,#__cpp(TMatrix::COLUMN_COUNT)*4

    VLDMIA      r2,{s9-s11}         // First line of matrix p2 to registers [S9-S11]
    VLDMIA      r1,{s0-s2}          // First line of matrix p1 to registers [S0-S2]
    ADD         r1,r1,r3
    ADD         r2,r2,r3
    VLDMIA      r2,{s12-s14}        // Second line of matrix p2 to registers [S12-S14]
    VLDMIA      r1,{s3-s5}          // Second line of matrix p1 to registers [S3-S5]
    ADD         r1,r1,r3
    ADD         r2,r2,r3
    VLDMIA      r2,{s15-s17}        // Third line of matrix p2 to registers [S15-S17]
    VLDMIA      r1,{s6-s8}          // Third line of matrix p1 to registers [S6-S8]

    VMUL.F32    s18,s9,s0
    VMUL.F32    s19,s10,s0
    VMUL.F32    s20,s11,s0

    VMUL.F32    s21,s9,s3
    VMUL.F32    s22,s10,s3
    VMUL.F32    s23,s11,s3

    VMUL.F32    s24,s9,s6
    VMUL.F32    s25,s10,s6
    VMUL.F32    s26,s11,s6

    VMLA.F32    s18,s12,s1
    VMLA.F32    s19,s13,s1
    VMLA.F32    s20,s14,s1

    VMLA.F32    s21,s12,s4
    VMLA.F32    s22,s13,s4
    VMLA.F32    s23,s14,s4

    VMLA.F32    s24,s12,s7
    VMLA.F32    s25,s13,s7
    VMLA.F32    s26,s14,s7

    VMLA.F32    s18,s15,s2
    VMLA.F32    s19,s16,s2
    VMLA.F32    s20,s17,s2

    VMLA.F32    s21,s15,s5
    VMLA.F32    s22,s16,s5
    VMLA.F32    s23,s17,s5

    VMLA.F32    s24,s15,s8
    VMLA.F32    s25,s16,s8
    VMLA.F32    s26,s17,s8

    VSTMIA      r0,{s18-s20}        // Store result
    VPOP        {d8-d9}             // Faster to segment POP
    ADD         r1,r0,r3
    VSTMIA      r1,{s21-s23}        // Store result
    VPOP        {d10-d11}           // Faster to break into small pieces
    ADD         r1,r1,r3
    VSTMIA      r1,{s24-s26}        // Store result
    VPOP        {d12-d13}           // Faster to break into chunks
    BX          lr                  // Return
}

template<typename TMatrix>
inline asm TMatrix* 
MTX33MultAsm(TMatrix*, const TMatrix*, const TMatrix*)
{


    //Because a template is being used, calculate an offset value for the matrix...
    MOV         r3,#__cpp(offsetof(TMatrix,f))
    ADD         r1,r1,r3
    ADD         r2,r2,r3
    MOV         r3,#__cpp(TMatrix::COLUMN_COUNT)*4

    CMP         r3,#3*4
    BNE         %FT0

    VPUSH       {d8}                  // Save registers
    VLDMIA      r2!,{s10-s15}         // First and second line of matrix p2 to registers [S10-S15]

    VLDR.F32    s16,[r1,#3*4*0+4*0]  // Matrix p1[0][0]
    VLDR.F32    s17,[r1,#3*4*1+4*0]  // Matrix p1[1][0]

    VMUL.F32    s0,s10,s16
    VMUL.F32    s1,s11,s16
    VMUL.F32    s2,s12,s16
    VLDR.F32    s16,[r1,#3*4*2+4*0]  // Matrix p1[2][0]

    VMUL.F32    s3,s10,s17
    VMUL.F32    s4,s11,s17
    VMUL.F32    s5,s12,s17
    VLDR.F32    s17,[r1,#3*4*0+4*1]  // Matrix p1[0][1]

    VMUL.F32    s6,s10,s16
    VMUL.F32    s7,s11,s16
    VMUL.F32    s8,s12,s16
    VLDR.F32    s16,[r1,#3*4*1+4*1]  // Matrix p1[1][1]

    VLDMIA      r2,{s10-s12}         // Third line of matrix p2 to registers [S10-S12]
    VMLA.F32    s0,s13,s17
    VMLA.F32    s1,s14,s17
    VMLA.F32    s2,s15,s17
    VLDR.F32    s17,[r1,#3*4*2+4*1]  // Matrix p1[2][1]
                
    VMLA.F32    s3,s13,s16
    VMLA.F32    s4,s14,s16
    VMLA.F32    s5,s15,s16
    VLDR.F32    s16,[r1,#3*4*0+4*2]  // Matrix p1[0][2]
                
    VMLA.F32    s6,s13,s17
    VMLA.F32    s7,s14,s17
    VMLA.F32    s8,s15,s17
    VLDR.F32    s17,[r1,#3*4*1+4*2]  // Matrix p1[1][2]

    VMLA.F32    s0,s10,s16
    VMLA.F32    s1,s11,s16
    VMLA.F32    s2,s12,s16
    VLDR.F32    s16,[r1,#3*4*2+4*2]  // Matrix p1[2][2]
                
    VMLA.F32    s3,s10,s17
    VMLA.F32    s4,s11,s17
    VMLA.F32    s5,s12,s17
                
    VMLA.F32    s6,s10,s16
    VMLA.F32    s7,s11,s16
    VMLA.F32    s8,s12,s16

    VPOP        {d8}                // POP

    VSTMIA      r0,{s0-s8}          // Store result
    BX          lr                  // Return

0
    VPUSH       {d8-d13}            // Save registers
    VLDMIA      r2,{s9-s11}         // First line of matrix p2 to registers [S9-S11]
    VLDMIA      r1,{s18-s20}        // First line of matrix p1 to registers [S18-S20]
    ADD         r1,r1,r3
    ADD         r2,r2,r3
    VLDMIA      r2,{s12-s14}        // Second line of matrix p2 to registers [S12-S14]
    VLDMIA      r1,{s21-s23}        // Second line of matrix p1 to registers [S21-S23]
    ADD         r1,r1,r3
    ADD         r2,r2,r3
    VLDMIA      r2,{s15-s17}        // Third line of matrix p2 to registers [S15-S17]
    VLDMIA      r1,{s24-s26}        // Third line of matrix p1 to registers [S24-S26]

    VMUL.F32    s0,s9,s18
    VMUL.F32    s1,s10,s18
    VMUL.F32    s2,s11,s18

    VMUL.F32    s3,s9,s21
    VMUL.F32    s4,s10,s21
    VMUL.F32    s5,s11,s21

    VMUL.F32    s6,s9,s24
    VMUL.F32    s7,s10,s24
    VMUL.F32    s8,s11,s24

    VMLA.F32    s0,s12,s19
    VMLA.F32    s1,s13,s19
    VMLA.F32    s2,s14,s19
                
    VMLA.F32    s3,s12,s22
    VMLA.F32    s4,s13,s22
    VMLA.F32    s5,s14,s22
                
    VMLA.F32    s6,s12,s25
    VMLA.F32    s7,s13,s25
    VMLA.F32    s8,s14,s25

    VMLA.F32    s0,s15,s20
    VMLA.F32    s1,s16,s20
    VMLA.F32    s2,s17,s20
                
    VMLA.F32    s3,s15,s23
    VMLA.F32    s4,s16,s23
    VMLA.F32    s5,s17,s23
                
    VMLA.F32    s6,s15,s26
    VMLA.F32    s7,s16,s26
    VMLA.F32    s8,s17,s26

    VPOP        {d8-d13}            // POP

    ADD         r1,r0,r3
    ADD         r2,r1,r3
    VSTMIA      r0,{s0-s2}          // Store result
    VSTMIA      r1,{s3-s5}          // Store result
    VSTMIA      r2,{s6-s8}          // Store result
    BX          lr                  // Return

}

/*  

*/

#include <nn/hw/ARM/codereset.h>
/* Please see man pages for details 
    
    
*/

/*
  
  
  
  
  
 

*/
NN_MATH_INLINE VEC3*
VEC3TransformC(VEC3* pOut, const MTX33* pM, const VEC3* pV)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(pM);
    NN_NULL_ASSERT(pV);

    VEC3 vTmp;
    VEC3* pDst = (pOut == pV) ? &vTmp : pOut;
    pDst->x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z;
    pDst->y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z;
    pDst->z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z;

    if (pDst == &vTmp)
    {
        pOut->x = pDst->x;
        pOut->y = pDst->y;
        pOut->z = pDst->z;
    }

    return pOut;
}

/*  

*/

/* ------------------------------------------------------------------------
        MTX33
   ------------------------------------------------------------------------ */

/* Please see man pages for details 
    
    
*/

/*
  
  
  
  
  
 

*/
template<typename TMatrix>
inline TMatrix*
MTX33MultC(TMatrix* pOut, const TMatrix* __restrict p1, const TMatrix* __restrict p2)
{
    NN_NULL_ASSERT( p1 );
    NN_NULL_ASSERT( p2 );
    NN_NULL_ASSERT( pOut );

    TMatrix mTmp;
    TMatrix* __restrict pDst = (pOut == p1 || pOut == p2) ? &mTmp : pOut;

    pDst->f._00 = p1->f._00 * p2->f._00 + p1->f._01 * p2->f._10 + p1->f._02 * p2->f._20;
    pDst->f._01 = p1->f._00 * p2->f._01 + p1->f._01 * p2->f._11 + p1->f._02 * p2->f._21;
    pDst->f._02 = p1->f._00 * p2->f._02 + p1->f._01 * p2->f._12 + p1->f._02 * p2->f._22;

    pDst->f._10 = p1->f._10 * p2->f._00 + p1->f._11 * p2->f._10 + p1->f._12 * p2->f._20;
    pDst->f._11 = p1->f._10 * p2->f._01 + p1->f._11 * p2->f._11 + p1->f._12 * p2->f._21;
    pDst->f._12 = p1->f._10 * p2->f._02 + p1->f._11 * p2->f._12 + p1->f._12 * p2->f._22;

    pDst->f._20 = p1->f._20 * p2->f._00 + p1->f._21 * p2->f._10 + p1->f._22 * p2->f._20;
    pDst->f._21 = p1->f._20 * p2->f._01 + p1->f._21 * p2->f._11 + p1->f._22 * p2->f._21;
    pDst->f._22 = p1->f._20 * p2->f._02 + p1->f._21 * p2->f._12 + p1->f._22 * p2->f._22;

    if (pDst == &mTmp)
    {
        pOut->f._00 = pDst->f._00; pOut->f._01 = pDst->f._01; pOut->f._02 = pDst->f._02;
        pOut->f._10 = pDst->f._10; pOut->f._11 = pDst->f._11; pOut->f._12 = pDst->f._12;
        pOut->f._20 = pDst->f._20; pOut->f._21 = pDst->f._21; pOut->f._22 = pDst->f._22;
    }

    return pOut;
}

/*
  
  
  
  
 

*/
NN_MATH_INLINE MTX33*
MTX33CopyC(MTX33* pOut, const MTX33* p)
{
    if (pOut != p)
    {
        *pOut = *p;
    }

    return pOut;
}



/*
  
  
  
  
  
  
 

*/
NN_MATH_INLINE MTX33*
MTX33MAddC(MTX33* pOut, f32 t, const MTX33* p1, const MTX33* p2)
{
    pOut->f._00 = t * p1->f._00 + p2->f._00;
    pOut->f._01 = t * p1->f._01 + p2->f._01;
    pOut->f._02 = t * p1->f._02 + p2->f._02;

    pOut->f._10 = t * p1->f._10 + p2->f._10;
    pOut->f._11 = t * p1->f._11 + p2->f._11;
    pOut->f._12 = t * p1->f._12 + p2->f._12;

    pOut->f._20 = t * p1->f._20 + p2->f._20;
    pOut->f._21 = t * p1->f._21 + p2->f._21;
    pOut->f._22 = t * p1->f._22 + p2->f._22;

    return pOut;
}
NN_MATH_INLINE MTX33*
MTX33MAddC_FAST(MTX33* pOut, f32 t, const MTX33* p1, const MTX33* p2)
{
    register f32 m00, m01, m02, m10, m11, m12, m20, m21, m22;

    m00 = p2->f._00;
    m01 = p2->f._01;
    m02 = p2->f._02;
          
    m10 = p2->f._10;
    m11 = p2->f._11;
    m12 = p2->f._12;
          
    m20 = p2->f._20;
    m21 = p2->f._21;
    m22 = p2->f._22;

    m00 += t * p1->f._00;
    m01 += t * p1->f._01;
    m02 += t * p1->f._02;
    
    m10 += t * p1->f._10;
    m11 += t * p1->f._11;
    m12 += t * p1->f._12;
    
    m20 += t * p1->f._20;
    m21 += t * p1->f._21;
    m22 += t * p1->f._22;
    
    pOut->f._00 = m00;
    pOut->f._01 = m01;
    pOut->f._02 = m02;

    pOut->f._10 = m10;
    pOut->f._11 = m11;
    pOut->f._12 = m12;

    pOut->f._20 = m20;
    pOut->f._21 = m21;
    pOut->f._22 = m22;

    return pOut;

}

/*  

*/
}  // namespace ARMv6
}  // namespace math
}  // namespace nn
