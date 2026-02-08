/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     VFPv2_reg.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_ARM_VFPV2_H_
#define NN_HW_ARM_VFPV2_H_

#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------
//                  VFP Control Registers
//----------------------------------------------------------------------

// Floating-Point Exception Register

#define HW_FPEXC_EXCEPTION_STATE    0x80000000  // in exception state
#define HW_FPEXC_VFP_ENABLE         0x40000000  // VFP enable
#define HW_FPEXC_FPINST2_VALID      0x10000000  // FPINST2 instruction valid flag

#define HW_FPEXC_VEC_ITR_MASK       0x00000700  // Vector iteration count

#define HW_FPEXC_INPUT_EXCEPTION    0x00000080  // Input exception flag
#define HW_FPEXC_POTENT_UNDERFLOW   0x00000008  // Potential underflow flag
#define HW_FPEXC_POTENT_OVERFLOW    0x00000004  // Potential overflow flag
#define HW_FPEXC_POTENT_INVALID     0x00000001  // Potential invalid operation flag

#define HW_FPEXC_VEC_ITR_SFT        8


// Floating-Point Status and Control Register

#define HW_FPSCR_N_FLAG             0x80000000  // Negative/Less than flag
#define HW_FPSCR_Z_FLAG             0x40000000  // Zero flag
#define HW_FPSCR_C_FLAG             0x20000000  // Carry/Borrow/Extend flag
#define HW_FPSCR_V_FLAG             0x10000000  // Overflow flag

#define HW_FPSCR_DEFAULT_NAN_MODE   0x02000000  // Default NaN mode (for std mode & fast mode)
#define HW_FPSCR_FLUSH_TO_ZERO_MODE 0x01000000  // Flush-to-zero mode (for std mode & fast mode)
#define HW_FPSCR_ROUND_MODE_MASK    0x00c00000  // Rounding mode
#define HW_FPSCR_VEC_STRIDE_MASK    0x00300000  // Vector stride
#define HW_FPSCR_VEC_LENGTH_MASK    0x00070000  // Vector length

#define HW_FPSCR_IDE_ENABLE         0x00008000  // Input Subnormal exception enable
#define HW_FPSCR_IXE_ENABLE         0x00001000  // Inexact exception enable
#define HW_FPSCR_UFE_ENABLE         0x00000800  // Underflow exception enable
#define HW_FPSCR_OFE_ENABLE         0x00000400  // Overflow exception enable
#define HW_FPSCR_DZE_ENABLE         0x00000200  // Division by Zero exception enable
#define HW_FPSCR_IOE_ENABLE         0x00000100  // Invalid Operation exception enable

#define HW_FPSCR_IDC                0x00000080  // Input Subnormal cumulative flag
#define HW_FPSCR_IXC                0x00000010  // Inexact cumulative flag
#define HW_FPSCR_UFC                0x00000008  // Underflow cumulative flag
#define HW_FPSCR_OFC                0x00000004  // Overflow cumulative flag
#define HW_FPSCR_DZC                0x00000002  // Division by Zero cumulative flag
#define HW_FPSCR_IOC                0x00000001  // Invalid Operation cumulative flag

#define HW_FPSCR_ROUND_MODE_SFT     22
#define HW_FPSCR_VEC_STRIDE_SFT     20
#define HW_FPSCR_VEC_LENGTH_SFT     16

#define HW_FPSCR_ROUND_NEAR_MODE    0           // Round to nearest mode
#define HW_FPSCR_ROUND_PLUS_MODE    1           // Round towards plus infinity mode
#define HW_FPSCR_ROUND_MINUS_MODE   2           // Round towards minus infinity mode
#define HW_FPSCR_ROUND_ZERO_MODE    3           // Round towards zero mode

#define HW_FPSCR_VEC_STRIDE_1       0           // Vector stride 1
#define HW_FPSCR_VEC_STRIDE_2       3           // Vector stride 2

#define HW_FPSCR_VEC_LENGTH_1       0           // Vector length 1
#define HW_FPSCR_VEC_LENGTH_2       1           // Vector length 2
#define HW_FPSCR_VEC_LENGTH_3       2           // Vector length 3
#define HW_FPSCR_VEC_LENGTH_4       3           // Vector length 4
#define HW_FPSCR_VEC_LENGTH_5       4           // Vector length 5
#define HW_FPSCR_VEC_LENGTH_6       5           // Vector length 6
#define HW_FPSCR_VEC_LENGTH_7       6           // Vector length 7
#define HW_FPSCR_VEC_LENGTH_8       7           // Vector length 8


// Floating-Point Instruction Register

// Floating-Point Instruction Register 2


#ifdef __cplusplus
} // extern "C"
#endif

// NN_HW_ARM_VFPV2_H_
#endif
