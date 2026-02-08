/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     reg_common.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_ARM_REG_COMMON_H_
#define NN_HW_ARM_REG_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------
//                  Program Status Register
//----------------------------------------------------------------------

#define HW_PSR_CPU_MODE_MASK       0x1f // CPU mode

#define HW_PSR_USR_MODE            0x10 // User mode
#define HW_PSR_FIQ_MODE            0x11 // FIQ mode
#define HW_PSR_IRQ_MODE            0x12 // IRQ mode
#define HW_PSR_SVC_MODE            0x13 // Supervisor mode
#define HW_PSR_ABORT_MODE          0x17 // Abort mode (prefetch/Data)
#define HW_PSR_UNDEF_MODE          0x1b // Undefined instruction mode
#define HW_PSR_SYS_MODE            0x1f // System mode

#define HW_PSR_ARM_STATE           0x0  // ARM state
#define HW_PSR_THUMB_STATE         0x20 // Thumb state

#define HW_PSR_FIQ_DISABLE         0x40 // FIQ Disable
#define HW_PSR_IRQ_DISABLE         0x80 // IRQ Disable
#define HW_PSR_IRQ_FIQ_DISABLE     0xc0 // IRQ & FIQ Disable

#define HW_PSR_IRQ_DISABLE_SHIFT   7   // HW_PSR_IRQ_DISABLE == (1 << PSR_IRQ_DISABLE_SHIFT)

#if defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)

#define HW_PSR_IMPR_ABORT_DISABLE  0x00000100   // Imprecise Abort Disable
#define HW_PSR_DATA_LITTLE_ENDIAN  0x00000000   // Data Little Endian
#define HW_PSR_DATA_BIG_ENDIAN     0x00000200   // Data Big Endian

#define HW_PSR_SIMD_GE0            0x00010000   // SIMD greater-than-or-equal
#define HW_PSR_SIMD_GE1            0x00020000
#define HW_PSR_SIMD_GE2            0x00040000
#define HW_PSR_SIMD_GE3            0x00080000

#define HW_PSR_JAVA_STATE          0x01000000   // JAVA state

#endif // SDK_ARM11

#define HW_PSR_Q_FLAG              0x08000000   // Sticky Overflow (Q) flag
#define HW_PSR_V_FLAG              0x10000000   // Overflow flag
#define HW_PSR_C_FLAG              0x20000000   // Carry/Borrow/Extend flag
#define HW_PSR_Z_FLAG              0x40000000   // Zero flag
#define HW_PSR_N_FLAG              0x80000000   // Negative/Less than flag


#ifdef __cplusplus
} // extern "C"
#endif

// NN_HW_ARM_REG_COMMON_H_
#endif
