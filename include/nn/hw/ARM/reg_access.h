/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     reg_access.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_ARM_REG_ACCESS_H_
#define NN_HW_ARM_REG_ACCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

//TODO: Remove CTR-dependent items, if any

//----------------------------------------------------------------------
//                  instruction level macros
//  Note:
//      v is a register int variable
//      a-e are symbols as like as c0, cpsr_c, etc.
//----------------------------------------------------------------------

// MRS/MSR
#define HW_INST_MRS(a,v)            __asm { mrs a,v }

#define HW_INST_MSR(a,v)            __asm { msr a,v }

// MRC/MCR
// a: CP, b: Op1, c: CRn, d: CRm, e: Op2
#define HW_INST_MRC(a,b,c,d,e,v)    __asm { mrc a,b,v,c,d,e }

#define HW_INST_MCR(a,b,c,d,e,v)    __asm { mcr a,b,v,c,d,e }

/*
    memo: read only
        pc: __current_pc()
        sp: __current_sp()
        lr    : __return_address()
*/

//----------------------------------------------------------------------
//                  mrs/msr family
//----------------------------------------------------------------------

#define HW_GET_CPSR(v)              HW_INST_MRS(cpsr,v)
#define HW_GET_SPSR(v)              HW_INST_MRS(spsr,v)

#define HW_SET_CPSR(f,v)            HW_INST_MSR(cpsr_##f,v) // f: fields
#define HW_SET_SPSR(f,v)            HW_INST_MSR(spsr_##f,v) // f: fields

//----------------------------------------------------------------------
//                  cp15
//----------------------------------------------------------------------

#define HW_GET_CP15_C0(c,o,v)       HW_INST_MRC(p15,0,c0,c,o,v)     // Opcode_1 is fixed
#define HW_GET_CP15_C1(o,v)         HW_INST_MRC(p15,0,c1,c0,o,v)    // Opcode_1 and CRm are fixed
#define HW_GET_CP15_C2(o,v)         HW_INST_MRC(p15,0,c2,c0,o,v)    // Opcode_1 and CRm are fixed
#define HW_GET_CP15_C3(v)           HW_INST_MRC(p15,0,c3,c0,0,v)    // fixed all
#define HW_GET_CP15_C5(o,v)         HW_INST_MRC(p15,0,c5,c0,o,v)    // Opcode_1 and CRm are fixed

#if defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
    #define HW_GET_CP15_C6(o,v)         HW_INST_MRC(p15,0,c6,c0,o,v)    // Opcode_1 and CRm are fixed
#else
    #define HW_GET_CP15_C6(c,o,v)       HW_INST_MRC(p15,0,c6,c,o,v)     // Opcode_1 is fixed
#endif

#define HW_GET_CP15_C7(c,o,v)       HW_INST_MRC(p15,0,c7,c,o,v)     // Opcode_1 is fixed
#define HW_GET_CP15_C8(c,o,v)       HW_INST_MRC(p15,0,c8,c,o,v)     // Opcode_1 is fixed

#if defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
    #define HW_GET_CP15_C9(v)           HW_INST_MRC(p15,0,c9,c0,0,v)    // fixed all
#else
    #define HW_GET_CP15_C9(o,v)         HW_INST_MRC(p15,0,c9,c0,o,v)    // Opcode_1 and CRm are fixed
#endif

#define HW_GET_CP15_C10(c,o,v)      HW_INST_MRC(p15,0,c10,c,o,v)    // Opcode_1 is fixed
#define HW_GET_CP15_C13(o,v)        HW_INST_MRC(p15,0,c13,c0,o,v)   // Opcode_1 and CRm are fixed
#define HW_GET_CP15_C15(o1,c,o2,v)  HW_INST_MRC(p15,o1,c15,c,o2,v)  // not fixed all

#define HW_GET_CP15_C15_0(c,o,v)    HW_INST_MRC(p15,0,c15,c,o,v)
#define HW_GET_CP15_C15_1(c,o,v)    HW_INST_MRC(p15,1,c15,c,o,v)
#define HW_GET_CP15_C15_2(c,o,v)    HW_INST_MRC(p15,2,c15,c,o,v)
#define HW_GET_CP15_C15_5(c,o,v)    HW_INST_MRC(p15,5,c15,c,o,v)
#define HW_GET_CP15_C15_7(v)        HW_INST_MRC(p15,7,c15,c1,0,v)

// Note: must set variable not constant

#define HW_SET_CP15_C0(c,o,v)       HW_INST_MCR(p15,0,c0,c,o,v)     // Opcode_1 is fixed
#define HW_SET_CP15_C1(o,v)         HW_INST_MCR(p15,0,c1,c0,o,v)    // Opcode_1 and CRm are fixed
#define HW_SET_CP15_C2(o,v)         HW_INST_MCR(p15,0,c2,c0,o,v)    // Opcode_1 and CRm are fixed
#define HW_SET_CP15_C3(v)           HW_INST_MCR(p15,0,c3,c0,0,v)    // fixed all
#define HW_SET_CP15_C5(o,v)         HW_INST_MCR(p15,0,c5,c0,o,v)    // Opcode_1 and CRm are fixed
#define HW_SET_CP15_C6(o,v)         HW_INST_MCR(p15,0,c6,c0,o,v)    // Opcode_1 and CRm are fixed
#define HW_SET_CP15_C7(c,o,v)       HW_INST_MCR(p15,0,c7,c,o,v)     // Opcode_1 is fixed
#define HW_SET_CP15_C8(c,o,v)       HW_INST_MCR(p15,0,c8,c,o,v)     // Opcode_1 is fixed
#define HW_SET_CP15_C9(v)           HW_INST_MCR(p15,0,c9,c0,0,v)    // fixed all
#define HW_SET_CP15_C10(c,o,v)      HW_INST_MCR(p15,0,c10,c,o,v)    // Opcode_1 is fixed
#define HW_SET_CP15_C13(o,v)        HW_INST_MCR(p15,0,c13,c0,o,v)   // Opcode_1 and CRm are fixed
#define HW_SET_CP15_C15(o1,c,o2,v)  HW_INST_MCR(p15,o1,c15,c,o2,v)  // not fixed all

#define HW_SET_CP15_C15_0(c,o,v)    HW_INST_MCR(p15,0,c15,c,o,v)
#define HW_SET_CP15_C15_5(c,o,v)    HW_INST_MCR(p15,5,c15,c,o,v)
#define HW_SET_CP15_C15_7(v)        HW_INST_MCR(p15,7,c15,c1,0,v)

//
// special named macro
//

#define HW_GET_CP15_MAIN_ID(v)                          HW_INST_MRC(p15,0,c0,c0,0,v)
#define HW_GET_CP15_CACHE_TYPE(v)                       HW_INST_MRC(p15,0,c0,c0,1,v)
#define HW_GET_CP15_TLB_TYPE(v)                         HW_INST_MRC(p15,0,c0,c0,3,v)
#define HW_GET_CP15_CPU_ID(v)                           HW_INST_MRC(p15,0,c0,c0,5,v)
#define HW_GET_CP15_PFR0(v)                             HW_INST_MRC(p15,0,c0,c1,0,v)
#define HW_GET_CP15_PFR1(v)                             HW_INST_MRC(p15,0,c0,c1,1,v)
#define HW_GET_CP15_DFR0(v)                             HW_INST_MRC(p15,0,c0,c1,2,v)
#define HW_GET_CP15_MMFR0(v)                            HW_INST_MRC(p15,0,c0,c1,4,v)
#define HW_GET_CP15_MMFR1(v)                            HW_INST_MRC(p15,0,c0,c1,5,v)
#define HW_GET_CP15_MMFR2(v)                            HW_INST_MRC(p15,0,c0,c1,6,v)
#define HW_GET_CP15_MMFR3(v)                            HW_INST_MRC(p15,0,c0,c1,7,v)
#define HW_GET_CP15_ISAR0(v)                            HW_INST_MRC(p15,0,c0,c2,0,v)
#define HW_GET_CP15_ISAR1(v)                            HW_INST_MRC(p15,0,c0,c2,1,v)
#define HW_GET_CP15_ISAR2(v)                            HW_INST_MRC(p15,0,c0,c2,2,v)
#define HW_GET_CP15_ISAR3(v)                            HW_INST_MRC(p15,0,c0,c2,3,v)
#define HW_GET_CP15_ISAR4(v)                            HW_INST_MRC(p15,0,c0,c2,4,v)
#define HW_GET_CP15_CONTROL(v)                          HW_INST_MRC(p15,0,c1,c0,0,v)
#define HW_GET_CP15_AUX_CONTROL(v)                      HW_INST_MRC(p15,0,c1,c0,1,v)
#define HW_GET_CP15_COPROCESSOR_ACCESS_CONTROL(v)       HW_INST_MRC(p15,0,c1,c0,2,v)

#if defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
    #define HW_GET_CP15_TTB0(v)                             HW_INST_MRC(p15,0,c2,c0,0,v)
    #define HW_GET_CP15_TTB1(v)                             HW_INST_MRC(p15,0,c2,c0,1,v)
    #define HW_GET_CP15_TTB_CONTROL(v)                      HW_INST_MRC(p15,0,c2,c0,2,v)
    #define HW_GET_CP15_DOMAIN_ACCESS_CONTROL(v)            HW_INST_MRC(p15,0,c3,c0,0,v)
    #define HW_GET_CP15_DATA_FAULT_STATUS(v)                HW_INST_MRC(p15,0,c5,c0,0,v)
    #define HW_GET_CP15_INSTRUCTION_FAULT_STATUS(v)         HW_INST_MRC(p15,0,c5,c0,1,v)
    #define HW_GET_CP15_DATA_FAULT_ADDRESS(v)               HW_INST_MRC(p15,0,c6,c0,0,v)
    #define HW_GET_CP15_WATCHPOINT_FAULT_ADDRESS(v)         HW_INST_MRC(p15,0,c6,c0,1,v)
#else
    #define HW_GET_CP15_CACHE_ENABLE(v)                     HW_INST_MRC(p15,0,c2,c0,0,v)
    #define HW_GET_CP15_DATA_CACHE_ENABLE(v)                HW_GET_CP15_CACHE_ENABLE(v)
    #define HW_GET_CP15_INSTRUCTION_CACHE_ENABLE(v)         HW_INST_MRC(p15,0,c2,c0,1,v)
    #define HW_GET_CP15_WRITE_BUFFER_ENABLE(v)              HW_INST_MRC(p15,0,c3,c0,0,v)
    #define HW_GET_CP15_ACCESS_PERMISSION(v)                HW_INST_MRC(p15,0,c5,c0,0,v)
    #define HW_GET_CP15_DATA_ACCESS_PERMISSION(v)           HW_GET_CP15_ACCESS_PERMISSION(v)
    #define HW_GET_CP15_INSTRUCTION_ACCESS_PERMISSION(v)    HW_INST_MRC(p15,0,c5,c0,1,v)
    #define HW_GET_CP15_DATA_ACCESS_PERMISSION_EX(v)        HW_INST_MRC(p15,0,c5,c0,2,v)
    #define HW_GET_CP15_INSTRUCTION_ACCESS_PERMISSION_EX(v) HW_INST_MRC(p15,0,c5,c0,3,v)
    #define HW_GET_CP15_PROTECTION_REGION_0(v)              HW_INST_MRC(p15,0,c6,c0,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_1(v)              HW_INST_MRC(p15,0,c6,c1,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_2(v)              HW_INST_MRC(p15,0,c6,c2,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_3(v)              HW_INST_MRC(p15,0,c6,c3,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_4(v)              HW_INST_MRC(p15,0,c6,c4,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_5(v)              HW_INST_MRC(p15,0,c6,c5,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_6(v)              HW_INST_MRC(p15,0,c6,c6,0,v)
    #define HW_GET_CP15_PROTECTION_REGION_7(v)              HW_INST_MRC(p15,0,c6,c7,0,v)
#endif

#define HW_GET_CP15_PA(v)                               HW_INST_MRC(p15,0,c7,c4,0,v)
#define HW_GET_CP15_DATA_CACHE_LOCKDOWN(v)              HW_INST_MRC(p15,0,c9,c0,0,v)

#if ! (defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6))
    #define HW_GET_CP15_INSTRUCTION_CACHE_LOCKDOWN(v)       HW_INST_MRC(p15,0,c9,c0,1,v)
    #define HW_GET_CP15_DTCM(v)                             HW_INST_MRC(p15,0,c9,c1,0,v)
    #define HW_GET_CP15_ITCM(v)                             HW_INST_MRC(p15,0,c9,c1,1,v)
#endif

#define HW_GET_CP15_TLB_LOCKDOWN(v)                     HW_INST_MRC(p15,0,c10,c0,0,v)
#define HW_GET_CP15_PRIMARY_REGION_REMAP(v)             HW_INST_MRC(p15,0,c10,c2,0,v)
#define HW_GET_CP15_NORMAL_REGION_REMAP(v)              HW_INST_MRC(p15,0,c10,c2,1,v)
#define HW_GET_CP15_FSCSE_PID(v)                        HW_INST_MRC(p15,0,c13,c0,0,v)
#define HW_GET_CP15_CONTEXT_ID(v)                       HW_INST_MRC(p15,0,c13,c0,1,v)
#define HW_GET_CP15_THREAD_ID(v)                        HW_INST_MRC(p15,0,c13,c0,2,v)
#define HW_GET_CP15_THREAD_ID_USER_READ_ONLY(v)         HW_INST_MRC(p15,0,c13,c0,3,v)
#define HW_GET_CP15_THREAD_ID_PRIVILEGED_ONLY(v)        HW_INST_MRC(p15,0,c13,c0,4,v)

#if ! (defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6))
    #define HW_GET_CP15_TEST_STATE(v)                       HW_INST_MRC(p15,0,c15,c0,0,v)
    #define HW_GET_CP15_INSTRUCTIN_TAG_BIST_ADDRESS(v)      HW_INST_MRC(p15,0,c15,c0,2,v)
    #define HW_GET_CP15_INSTRUCTIN_TAG_BIST_GENERAL(v)      HW_INST_MRC(p15,0,c15,c0,3,v)
    #define HW_GET_CP15_DATA_TAG_BIST_ADDRESS(v)            HW_INST_MRC(p15,0,c15,c0,6,v)
    #define HW_GET_CP15_DATA_TAG_BIST_GENERAL(v)            HW_INST_MRC(p15,0,c15,c0,7,v)
    #define HW_GET_CP15_ITCM_BIST_ADDRESS(v)                HW_INST_MRC(p15,1,c15,c0,2,v)
    #define HW_GET_CP15_ITCM_BIST_GENERAL(v)                HW_INST_MRC(p15,1,c15,c0,3,v)
    #define HW_GET_CP15_DTCM_BIST_ADDRESS(v)                HW_INST_MRC(p15,1,c15,c0,6,v)
    #define HW_GET_CP15_DTCM_BIST_GENERAL(v)                HW_INST_MRC(p15,1,c15,c0,7,v)
    #define HW_GET_CP15_TRACE_STATE_CONTROL(v)              HW_INST_MRC(p15,1,c15,c1,0,v)
    #define HW_GET_CP15_INSTRUCTIN_CACHE_RAM_BIST_ADDRESS(v)        HW_INST_MRC(p15,2,c15,c0,2,v)
    #define HW_GET_CP15_INSTRUCTIN_CACHE_RAM_BIST_GENERAL(v)        HW_INST_MRC(p15,2,c15,c0,3,v)
    #define HW_GET_CP15_DATA_CACHE_RAM_BIST_ADDRESS(v)      HW_INST_MRC(p15,2,c15,c0,6,v)
    #define HW_GET_CP15_DATA_CACHE_RAM_BIST_GENERAL(v)      HW_INST_MRC(p15,2,c15,c0,7,v)
#endif

#define HW_GET_CP15_PERFORMANCE_MONITOR_CONTROL(v)      HW_INST_MRC(p15,0,c15,c12,0,v)
#define HW_GET_CP15_CCNT(v)                             HW_INST_MRC(p15,0,c15,c12,1,v)
#define HW_GET_CP15_PMN0(v)                             HW_INST_MRC(p15,0,c15,c12,2,v)
#define HW_GET_CP15_PMN1(v)                             HW_INST_MRC(p15,0,c15,c12,3,v)

#if ! (defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6))
    #define HW_GET_CP15_CACHE_DEBUG_INDEX(v)                HW_INST_MRC(p15,3,c15,c0,0,v)
    #define HW_GET_CP15_INSTRUCTION_TAG(v)                  HW_INST_MRC(p15,3,c15,c1,0,v)
    #define HW_GET_CP15_DATA_TAG(v)                         HW_INST_MRC(p15,3,c15,c2,0,v)
    #define HW_GET_CP15_INSTRUCTION_CACHE(v)                HW_INST_MRC(p15,3,c15,c3,0,v)
    #define HW_GET_CP15_DATA_CACHE(v)                       HW_INST_MRC(p15,3,c15,c4,0,v)
#endif

#define HW_GET_CP15_MAIN_TLB_LOCKDOWN_VA(v)             HW_INST_MRC(p15,5,c15,c5,2,v)
#define HW_GET_CP15_MAIN_TLB_LOCKDOWN_PA(v)             HW_INST_MRC(p15,5,c15,c6,2,v)
#define HW_GET_CP15_MAIN_TLB_LOCKDOWN_ATTRIBUTE(v)      HW_INST_MRC(p15,5,c15,c7,2,v)
#define HW_GET_CP15_TLB_DEBUG_CONTROL(v)                HW_INST_MRC(p15,7,c15,c1,0,v)

#define HW_SET_CP15_CONTROL(v)                          HW_INST_MCR(p15,0,c1,c0,0,v)
#define HW_SET_CP15_AUX_CONTROL(v)                      HW_INST_MCR(p15,0,c1,c0,1,v)
#define HW_SET_CP15_COPROCESSOR_ACCESS_CONTROL(v)       HW_INST_MCR(p15,0,c1,c0,2,v)

#if defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
    #define HW_SET_CP15_TTB0(v)                             HW_INST_MCR(p15,0,c2,c0,0,v)
    #define HW_SET_CP15_TTB1(v)                             HW_INST_MCR(p15,0,c2,c0,1,v)
    #define HW_SET_CP15_TTB_CONTROL(v)                      HW_INST_MCR(p15,0,c2,c0,2,v)
    #define HW_SET_CP15_DOMAIN_ACCESS_CONTROL(v)            HW_INST_MCR(p15,0,c3,c0,0,v)
    #define HW_SET_CP15_DATA_FAULT_STATUS(v)                HW_INST_MCR(p15,0,c5,c0,0,v)
    #define HW_SET_CP15_INSTRUCTION_FAULT_STATUS(v)         HW_INST_MCR(p15,0,c5,c0,1,v)
    #define HW_SET_CP15_DATA_FAULT_ADDRESS(v)               HW_INST_MCR(p15,0,c6,c0,0,v)
    #define HW_SET_CP15_WATCHPOINT_FAULT_ADDRESS(v)         HW_INST_MCR(p15,0,c6,c0,1,v)
#else
    #define HW_SET_CP15_CACHE_ENABLE(v)                     HW_INST_MCR(p15,0,c2,c0,0,v)
    #define HW_SET_CP15_DATA_CACHE_ENABLE(v)                HW_SET_CP15_CACHE_ENABLE(v)
    #define HW_SET_CP15_INSTRUCTION_CACHE_ENABLE(v)         HW_INST_MCR(p15,0,c2,c0,1,v)
    #define HW_SET_CP15_WRITE_BUFFER_ENABLE(v)              HW_INST_MCR(p15,0,c3,c0,0,v)
    #define HW_SET_CP15_ACCESS_PERMISSION(v)                HW_INST_MCR(p15,0,c5,c0,0,v)
    #define HW_SET_CP15_DATA_ACCESS_PERMISSION(v)           HW_SET_CP15_ACCESS_PERMISSION(v)
    #define HW_SET_CP15_INSTRUCTION_ACCESS_PERMISSION(v)    HW_INST_MCR(p15,0,c5,c0,1,v)
    #define HW_SET_CP15_DATA_ACCESS_PERMISSION_EX(v)        HW_INST_MCR(p15,0,c5,c0,2,v)
    #define HW_SET_CP15_INSTRUCTION_ACCESS_PERMISSION_EX(v) HW_INST_MCR(p15,0,c5,c0,3,v)
    #define HW_SET_CP15_PROTECTION_REGION_0(v)              HW_INST_MCR(p15,0,c6,c0,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_1(v)              HW_INST_MCR(p15,0,c6,c1,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_2(v)              HW_INST_MCR(p15,0,c6,c2,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_3(v)              HW_INST_MCR(p15,0,c6,c3,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_4(v)              HW_INST_MCR(p15,0,c6,c4,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_5(v)              HW_INST_MCR(p15,0,c6,c5,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_6(v)              HW_INST_MCR(p15,0,c6,c6,0,v)
    #define HW_SET_CP15_PROTECTION_REGION_7(v)              HW_INST_MCR(p15,0,c6,c7,0,v)
#endif

#define HW_SET_CP15_WFI(v)                              HW_INST_MCR(p15,0,c7,c0,4,v)
#define HW_SET_CP15_INVALIDATE_ENTIRE_INSTRUCTION_CACHE(v)      HW_INST_MCR(p15,0,c7,c5,0,v)
#define HW_SET_CP15_INVALIDATE_INSTRUCTION_CACHE_MVA(v)         HW_INST_MCR(p15,0,c7,c5,1,v)
#define HW_SET_CP15_INVALIDATE_INSTRUCTION_CACHE_INDEX(v)       HW_INST_MCR(p15,0,c7,c5,2,v)
#define HW_SET_CP15_FLUSH_PREFETCH_BUFFER(v)            HW_INST_MCR(p15,0,c7,c5,4,v)
#define HW_SET_CP15_FLUSH_ENTIRE_BRANCH_TARGET_CACHE(v) HW_INST_MCR(p15,0,c7,c5,6,v)
#define HW_SET_CP15_FLUSH_BRANCH_TARGET_CACHE_ENTRY(v)  HW_INST_MCR(p15,0,c7,c5,7,v)
#define HW_SET_CP15_INVALIDATE_ENTIRE_DATA_CACHE(v)     HW_INST_MCR(p15,0,c7,c6,0,v)
#define HW_SET_CP15_INVALIDATE_DATA_CACHE_MVA(v)        HW_INST_MCR(p15,0,c7,c6,1,v)
#define HW_SET_CP15_INVALIDATE_DATA_CACHE_INDEX(v)      HW_INST_MCR(p15,0,c7,c6,2,v)
#define HW_SET_CP15_INVALIDATE_BOTH_CACHE(v)            HW_INST_MCR(p15,0,c7,c7,0,v)
#define HW_SET_CP15_VA_TO_PA_PRIVILEGED_READ(v)         HW_INST_MCR(p15,0,c7,c8,0,v)
#define HW_SET_CP15_VA_TO_PA_PRIVILEGED_WRITE(v)        HW_INST_MCR(p15,0,c7,c8,1,v)
#define HW_SET_CP15_VA_TO_PA_USER_READ(v)               HW_INST_MCR(p15,0,c7,c8,2,v)
#define HW_SET_CP15_VA_TO_PA_USER_WRITE(v)              HW_INST_MCR(p15,0,c7,c8,3,v)
#define HW_SET_CP15_CLEAN_ENTIRE_DATA_CACHE(v)          HW_INST_MCR(p15,0,c7,c10,0,v)
#define HW_SET_CP15_CLEAN_DATA_CACHE_MVA(v)             HW_INST_MCR(p15,0,c7,c10,1,v)
#define HW_SET_CP15_CLEAN_DATA_CACHE_INDEX(v)           HW_INST_MCR(p15,0,c7,c10,2,v)
#define HW_SET_CP15_DATA_SYNC_BARRIER(v)                HW_INST_MCR(p15,0,c7,c10,4,v)
#define HW_SET_CP15_DATA_MEMORY_BARRIER(v)              HW_INST_MCR(p15,0,c7,c10,5,v)
#define HW_SET_CP15_CLEAN_INVALIDATE_ENTIRE_DATA_CACHE(v)       HW_INST_MCR(p15,0,c7,c14,0,v)
#define HW_SET_CP15_CLEAN_INVALIDATE_DATA_CACHE_MVA(v)          HW_INST_MCR(p15,0,c7,c14,1,v)
#define HW_SET_CP15_CLEAN_INVALIDATE_DATA_CACHE_INDEX(v)        HW_INST_MCR(p15,0,c7,c14,2,v)
#define HW_SET_CP15_INVALIDATE_INSTRUCTION_TLB(v)               HW_INST_MCR(p15,0,c8,c5,0,v)
#define HW_SET_CP15_INVALIDATE_INSTRUCTION_TLB_SINGLE(v)        HW_INST_MCR(p15,0,c8,c5,1,v)
#define HW_SET_CP15_INVALIDATE_INSTRUCTION_TLB_ASID(v)          HW_INST_MCR(p15,0,c8,c5,2,v)
#define HW_SET_CP15_INVALIDATE_INSTRUCTION_TLB_MVA(v)           HW_INST_MCR(p15,0,c8,c5,3,v)
#define HW_SET_CP15_INVALIDATE_DATA_TLB(v)              HW_INST_MCR(p15,0,c8,c6,0,v)
#define HW_SET_CP15_INVALIDATE_DATA_TLB_SINGLE(v)       HW_INST_MCR(p15,0,c8,c6,1,v)
#define HW_SET_CP15_INVALIDATE_DATA_TLB_ASID(v)         HW_INST_MCR(p15,0,c8,c6,2,v)
#define HW_SET_CP15_INVALIDATE_DATA_TLB_MVA(v)          HW_INST_MCR(p15,0,c8,c6,3,v)
#define HW_SET_CP15_INVALIDATE_UNIFIED_TLB(v)           HW_INST_MCR(p15,0,c8,c7,0,v)
#define HW_SET_CP15_INVALIDATE_UNIFIED_TLB_SINGLE(v)    HW_INST_MCR(p15,0,c8,c7,1,v)
#define HW_SET_CP15_INVALIDATE_UNIFIED_TLB_ASID(v)      HW_INST_MCR(p15,0,c8,c7,2,v)
#define HW_SET_CP15_INVALIDATE_UNIFIED_TLB_MVA(v)       HW_INST_MCR(p15,0,c8,c7,3,v)
#define HW_SET_CP15_DATA_CACHE_LOCKDOWN(v)              HW_INST_MCR(p15,0,c9,c0,0,v)

#if ! (defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6))
    #define HW_SET_CP15_INSTRUCTION_CACHE_LOCKDOWN(v)       HW_INST_MCR(p15,0,c9,c0,1,v)
    #define HW_SET_CP15_DTCM(v)                             HW_INST_MCR(p15,0,c9,c1,0,v)
    #define HW_SET_CP15_ITCM(v)                             HW_INST_MCR(p15,0,c9,c1,1,v)
#endif

#define HW_SET_CP15_TLB_LOCKDOWN(v)                     HW_INST_MCR(p15,0,c10,c0,0,v)
#define HW_SET_CP15_PRIMARY_REGION_REMAP(v)             HW_INST_MCR(p15,0,c10,c2,0,v)
#define HW_SET_CP15_NORMAL_REGION_REMAP(v)              HW_INST_MCR(p15,0,c10,c2,1,v)
#define HW_SET_CP15_FSCSE_PID(v)                        HW_INST_MCR(p15,0,c13,c0,0,v)
#define HW_SET_CP15_CONTEXT_ID(v)                       HW_INST_MCR(p15,0,c13,c0,1,v)
#define HW_SET_CP15_THREAD_ID(v)                        HW_INST_MCR(p15,0,c13,c0,2,v)
#define HW_SET_CP15_THREAD_ID_USER_READ_ONLY(v)         HW_INST_MCR(p15,0,c13,c0,3,v)
#define HW_SET_CP15_THREAD_ID_PRIVILEGED_ONLY(v)        HW_INST_MCR(p15,0,c13,c0,4,v)

#if ! (defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6))
    #define HW_SET_CP15_TEST_STATE(v)                       HW_INST_MCR(p15,0,c15,c0,0,v)
    #define HW_SET_CP15_INSTRUCTIN_TAG_BIST_ADDRESS(v)      HW_INST_MCR(p15,0,c15,c0,2,v)
    #define HW_SET_CP15_INSTRUCTIN_TAG_BIST_GENERAL(v)      HW_INST_MCR(p15,0,c15,c0,3,v)
    #define HW_SET_CP15_DATA_TAG_BIST_ADDRESS(v)            HW_INST_MCR(p15,0,c15,c0,6,v)
    #define HW_SET_CP15_DATA_TAG_BIST_GENERAL(v)            HW_INST_MCR(p15,0,c15,c0,7,v)
    #define HW_SET_CP15_ITCM_BIST_ADDRESS(v)                HW_INST_MCR(p15,1,c15,c0,2,v)
    #define HW_SET_CP15_ITCM_BIST_GENERAL(v)                HW_INST_MCR(p15,1,c15,c0,3,v)
    #define HW_SET_CP15_DTCM_BIST_ADDRESS(v)                HW_INST_MCR(p15,1,c15,c0,6,v)
    #define HW_SET_CP15_DTCM_BIST_GENERAL(v)                HW_INST_MCR(p15,1,c15,c0,7,v)
    #define HW_SET_CP15_TRACE_STATE_CONTROL(v)              HW_INST_MCR(p15,1,c15,c1,0,v)
    #define HW_SET_CP15_INSTRUCTIN_CACHE_RAM_BIST_ADDRESS(v)        HW_INST_MCR(p15,2,c15,c0,2,v)
    #define HW_SET_CP15_INSTRUCTIN_CACHE_RAM_BIST_GENERAL(v)        HW_INST_MCR(p15,2,c15,c0,3,v)
    #define HW_SET_CP15_DATA_CACHE_RAM_BIST_ADDRESS(v)      HW_INST_MCR(p15,2,c15,c0,6,v)
    #define HW_SET_CP15_DATA_CACHE_RAM_BIST_GENERAL(v)      HW_INST_MCR(p15,2,c15,c0,7,v)
#endif

#define HW_SET_CP15_PERFORMANCE_MONITOR_CONTROL(v)      HW_INST_MCR(p15,0,c15,c12,0,v)
#define HW_SET_CP15_CCNT(v)                             HW_INST_MCR(p15,0,c15,c12,1,v)
#define HW_SET_CP15_PMN0(v)                             HW_INST_MCR(p15,0,c15,c12,2,v)
#define HW_SET_CP15_PMN1(v)                             HW_INST_MCR(p15,0,c15,c12,3,v)
#define HW_SET_CP15_READ_MAIN_TLB_LOCKDOWN_ENTRY(v)     HW_INST_MCR(p15,5,c15,c4,2,v)
#define HW_SET_CP15_WRITE_MAIN_TLB_LOCKDOWN_ENTRY(v)    HW_INST_MCR(p15,5,c15,c4,4,v)

#if ! (defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6))
    #define HW_SET_CP15_CACHE_DEBUG_INDEX(v)                HW_INST_MCR(p15,3,c15,c0,0,v)
    #define HW_SET_CP15_INSTRUCTION_TAG(v)                  HW_INST_MCR(p15,3,c15,c1,0,v)
    #define HW_SET_CP15_DATA_TAG(v)                         HW_INST_MCR(p15,3,c15,c2,0,v)
    #define HW_SET_CP15_INSTRUCTION_CACHE(v)                HW_INST_MCR(p15,3,c15,c3,0,v)
    #define HW_SET_CP15_DATA_CACHE(v)                       HW_INST_MCR(p15,3,c15,c4,0,v)
#endif

#define HW_SET_CP15_MAIN_TLB_LOCKDOWN_VA(v)             HW_INST_MCR(p15,5,c15,c5,2,v)
#define HW_SET_CP15_MAIN_TLB_LOCKDOWN_PA(v)             HW_INST_MCR(p15,5,c15,c6,2,v)
#define HW_SET_CP15_MAIN_TLB_LOCKDOWN_ATTRIBUTE(v)      HW_INST_MCR(p15,5,c15,c7,2,v)
#define HW_SET_CP15_TLB_DEBUG_CONTROL(v)                HW_INST_MCR(p15,7,c15,c1,0,v)

//
// static input value
//
#define HW_CP15_WFI()                                   HW_INST_MCR(p15,0,c7,c0,4,0)
#define HW_CP15_INVALIDATE_ENTIRE_INSTRUCTION_CACHE()   HW_INST_MCR(p15,0,c7,c5,0,0)
#define HW_CP15_FLUSH_PREFETCH_BUFFER()                 HW_INST_MCR(p15,0,c7,c5,4,0)
#define HW_CP15_FLUSH_ENTIRE_BRANCH_TARGET_CACHE()      HW_INST_MCR(p15,0,c7,c5,6,0)
#define HW_CP15_INVALIDATE_ENTIRE_DATA_CACHE()          HW_INST_MCR(p15,0,c7,c6,0,0)
#define HW_CP15_INVALIDATE_BOTH_CACHE()                 HW_INST_MCR(p15,0,c7,c7,0,0)
#define HW_CP15_CLEAN_ENTIRE_DATA_CACHE()               HW_INST_MCR(p15,0,c7,c10,0,0)
#define HW_CP15_DATA_SYNC_BARRIER()                     HW_INST_MCR(p15,0,c7,c10,4,0)
#define HW_CP15_DATA_MEMORY_BARRIER()                   HW_INST_MCR(p15,0,c7,c10,5,0)
#define HW_CP15_CLEAN_INVALIDATE_ENTIRE_DATA_CACHE()    HW_INST_MCR(p15,0,c7,c14,0,0)
#define HW_CP15_INVALIDATE_INSTRUCTION_TLB()            HW_INST_MCR(p15,0,c8,c5,0,0)
#define HW_CP15_INVALIDATE_DATA_TLB()                   HW_INST_MCR(p15,0,c8,c6,0,0)
#define HW_CP15_INVALIDATE_UNIFIED_TLB()                HW_INST_MCR(p15,0,c8,c7,0,0)


#ifdef __cplusplus
} // extern "C"
#endif

// NN_HW_ARM_REG_ACCESS_H_
#endif
