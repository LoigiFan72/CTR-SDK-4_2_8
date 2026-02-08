/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ARMv6_reg.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_ARM_ARMV6_REG_H_
#define NN_HW_ARM_ARMV6_REG_H_

#include <nn/hw/ARM/reg_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SDK_MG20EMU
#ifndef SDK_NE1EMU
#define HW_CPU_CLOCK_ARM11          ((67028 * 1000) * 4) // A typical value is 67027964 * 4 [1/2,000,000 = an error of 1 sec in 23 days]
#else // SDK_NE1EMU
#define HW_CPU_CLOCK_ARM11          (400 * 1000 * 1000)
#endif // SDK_NE1EMU
#else // SDK_MG20EMU
#define HW_CPU_CLOCK_ARM11          (302 * 1000 * 1000)
#endif // SDK_MG20EMU
#define HW_CPU_CLOCK                HW_CPU_CLOCK_ARM11

#if !defined(SDK_MG20EMU) && !defined(SDK_NE1EMU)
#define HW_ARM11_IC_SIZE            0x4000      // Inst Cache
#define HW_ARM11_DC_SIZE            0x4000      // Data Cache
#else // SDK_MG20EMU || SDK_NE1EMU
#define HW_ARM11_IC_SIZE            0x8000      // Inst Cache
#define HW_ARM11_DC_SIZE            0x8000      // Data Cache
#endif // SDK_MG20EMU || SDK_NE1EMU
#define HW_ARM11_CACHE_LINE_SIZE    32

#define HW_IC_SIZE                  HW_ARM11_IC_SIZE
#define HW_DC_SIZE                  HW_ARM11_DC_SIZE
#define HW_CACHE_LINE_SIZE          HW_ARM11_CACHE_LINE_SIZE

//**********************************************************************
//                  Coprocessor Control Bits
//**********************************************************************

//----------------------------------------------------------------------
//                  System Control Coprocessor
//----------------------------------------------------------------------

// Register 0.0 : ID Code
// Register 0.1 : Cache Type
// Register 0.3 : TLB Type

// Register 0.5 : CPU ID

#define HW_C0_AP_CLUSTER_ID_MASK    0x00000f00  // Cluster ID
#define HW_C0_AP_CPU_ID_MASK        0x00000003  // CPU ID

#define HW_C0_AP_CLUSTER_ID_SFT     8
#define HW_C0_AP_CPU_ID_SFT         0

// Register 1.0 : Master Control

#ifdef SDK_ARMULATOR
#define HW_C1_0_SB1                 0x00004078  // Should be 1
#else
#define HW_C1_0_SB1                 0x000040f8  // Should be 1
#endif

#define HW_C1_FORCE_AP_BIT          0x20000000  // AP[0] used as Access Bit
#define HW_C1_TEX_CB_REMAP          0x10000000  // Remap registers are used for remapping
#define HW_C1_NMFI_FIQ              0x08000000  // FIQs behave as NMFIs
#define HW_C1_EXCEPT_LITTLE_ENDIAN  0x00000000  // CPSR E bit is set to 0 on taking an exception
#define HW_C1_EXCEPT_BIG_ENDIAN     0x02000000  // CPSR E bit is set to 1 on taking an exception
#define HW_C1_MMU_V6                0x00800000  // MMUv6 selected (Subpage AP bits disabled)
#define HW_C1_MMU_V5                0x00000000  // MMUv5 selected (Subpage AP bits enabled)
#define HW_C1_UNALIGN_ACCESS_ENABLE 0x00400000  // Unaligned data and mixed-endian data access enable

#define HW_C1_LD_INTERWORK_DISABLE  0x00008000  // Loads to PC do not set the T bit (ARMv4 behavior)
#define HW_C1_EXCEPT_VEC_UPPER      0x00002000  // High exception vectors selected
#define HW_C1_EXCEPT_VEC_LOWER      0x00000000  // Low exception vectors selected
#define HW_C1_IC_ENABLE             0x00001000  // Instruction Cache enabled
#define HW_C1_DC_ENABLE             0x00000004  // Data Cache enabled

#define HW_C1_BR_PREDICT_ENABLE     0x00000800  // Branch prediction enable
#define HW_C1_ROM_PROTECT_ENABLE    0x00000200  // ROM protection enable (Deprecated)
#define HW_C1_MMU_PROTECT_ENABLE    0x00000100  // MMU System protection enable (Deprecated)
#define HW_C1_ALIGN_FAULT_ENABLE    0x00000002  // Strict alignment fault checking enabled (Higher than UNALIGN)
#define HW_C1_MMU_ENABLE            0x00000001  // MMU enable

#define HW_C1_IC_ENABLE_SFT         12
#define HW_C1_DC_ENABLE_SFT         2


// Register 1.1 : Auxiliary Control

#define HW_C1_SMP_MODE              0x00000020  // Symmetric Multi Processing mode
#define HW_C1_AMP_MODE              0x00000000  // Asymmetric Multi Processing mode
#define HW_C1_EXCLUSIVE_L1C_L2C     0x00000010  // L1 and L2 caches are exclusive (Invalid for CTR)
#define HW_C1_BR_FOLDING_ENABLE     0x00000008  // Branch instruction folding enable
#define HW_C1_SBR_PREDICT_ENABLE    0x00000004  // Static branch prediction enable
#define HW_C1_DBR_PREDICT_ENABLE    0x00000002  // Dynamic branch prediction enable
#define HW_C1_RETURN_STACK_ENABLE   0x00000001  // Return stack enable


// Register 1.2 : VFP Access Permission Control

#define HW_C1_VFP_AP_PACK( vfp_float, vfp_double ) \
                                       \
        ( ((vfp_float) << HW_C1_AP_CP10_SFT) \
        | ((vfp_double) << HW_C1_AP_CP11_SFT) )

#define HW_C1_AP_CP10_MASK          0x00300000  // Permit access to CP10
#define HW_C1_AP_CP11_MASK          0x00C00000  //                  CP11

#define HW_C1_AP_CP10_SFT           20
#define HW_C1_AP_CP11_SFT           22

#define HW_C1_AP_NA                 0   // Access denied
#define HW_C1_AP_SVR                1   // Supervisor access only
#define HW_C1_AP_PRIV               3   // Full access


// Register 2.0.0/1 : MMU L1 Table Base

#define HW_C2_0_T1_BASE_MASK_MAX    0xffffff80  // Pointer to the level one translation table when Boundary = 0 or VA = 0
#define HW_C2_0_T1_BASE_MASK_MIN    0xffffc000
#define HW_C2_1_T1_BASE_MASK        0xffffc000  //                                            when Boundary > 0 and VA > 0
#define HW_C2_WALK_L2C_CA_MASK      0x00000018  // L2 Cache cachable attributes for page table walking (Invalid for CTR)
#define HW_C2_WALK_ON_SHARED_MEM    0x00000002  // Page table walk is to shared memory

#define HW_C2_WALK_L2C_CA_SFT       3

#define HW_C2_WALK_L2C_CA_NC        0   // L2 Cache Noncachable (Invalid for CTR)
#define HW_C2_WALK_L2C_CA_WB_WA     1   // L2 Cache Cachable Write-Back cached, Write Allocate (Invalid for CTR)


// Register 2.0.2 : MMU L1 Table Boundary

#define HW_C2_V5_T1_BOUNBARY_MASK   0x00000007  // the size of the first-level translation table base boundary for MMUv5

#define HW_C2_V5_T1_BOUNBARY_16KB   0   // 16 KB
#define HW_C2_V5_T1_BOUNBARY_8KB    1   // 8 KB
#define HW_C2_V5_T1_BOUNBARY_4KB    2   // 4 KB
#define HW_C2_V5_T1_BOUNBARY_2KB    3   // 2 KB
#define HW_C2_V5_T1_BOUNBARY_1KB    4   // 1 KB
#define HW_C2_V5_T1_BOUNBARY_512B   5   // 512 Byte
#define HW_C2_V5_T1_BOUNBARY_256B   6   // 256 byte
#define HW_C2_V5_T1_BOUNBARY_128B   7   // 128 byte


// Register 3 : Domain Access Control

#define HW_C3_DOMAIN_PACK( d0, d1, d2, d3, d4, d5, d6, d7, \
                           d8, d9, d10, d11, d12, d13, d14, d15 ) \
                                  \
        ( ((d0) << HW_C3_DM0_SFT) \
        | ((d1) << HW_C3_DM1_SFT) \
        | ((d2) << HW_C3_DM2_SFT) \
        | ((d3) << HW_C3_DM3_SFT) \
        | ((d4) << HW_C3_DM4_SFT) \
        | ((d5) << HW_C3_DM5_SFT) \
        | ((d6) << HW_C3_DM6_SFT) \
        | ((d7) << HW_C3_DM7_SFT) \
        | ((d8) << HW_C3_DM8_SFT) \
        | ((d9) << HW_C3_DM9_SFT) \
        | ((d10) << HW_C3_DM10_SFT) \
        | ((d11) << HW_C3_DM11_SFT) \
        | ((d12) << HW_C3_DM12_SFT) \
        | ((d13) << HW_C3_DM13_SFT) \
        | ((d14) << HW_C3_DM14_SFT) \
        | ((d15) << HW_C3_DM15_SFT) )

#define HW_C3_DOMAIN_ID_SFT( no )  ( (no) * 2 )

#define HW_C3_DM0_SFT               0   // Domain 0
#define HW_C3_DM1_SFT               2   //        1
#define HW_C3_DM2_SFT               4   //        2
#define HW_C3_DM3_SFT               6   //        3
#define HW_C3_DM4_SFT               8   //        4
#define HW_C3_DM5_SFT               10  //        5
#define HW_C3_DM6_SFT               12  //        6
#define HW_C3_DM7_SFT               14  //        7
#define HW_C3_DM8_SFT               16  //        8
#define HW_C3_DM9_SFT               18  //        9
#define HW_C3_DM10_SFT              20  //        10
#define HW_C3_DM11_SFT              22  //        11
#define HW_C3_DM12_SFT              24  //        12
#define HW_C3_DM13_SFT              26  //        13
#define HW_C3_DM14_SFT              28  //        14
#define HW_C3_DM15_SFT              30  //        15

#define HW_C3_DM_AP_NA              0   // Any access generates a domain fault
#define HW_C3_DM_AP_CLIENT          1   // Permit clients to access a domain
#define HW_C3_DM_AP_MANAGER         3   // Permit managers to access a domain


// Register 5 : Data/Instruction Fault Status

#define HW_C5_FAULT_DOMAIN_ID_MASK  0x000000f0  // Domain's specify at data fault
#define HW_C5_FAULT_STATUS_MASK     0x0000040f  // Fault status
#define HW_C5_FAULT_AXI_SLVERR      0x00001000  // AXI abort marked as SLVERR
#define HW_C5_FAULT_AXI_DECERR      0x00000000  //                     DECERR
#define HW_C5_FAULT_WRITE           0x00000800  // Write access caused the abort
#define HW_C5_FAULT_READ            0x00000000  // Read access

#define HW_C5_FAULT_DOMAIN_ID_SFT   4

#define HW_C5_ALIGN_FAULT           0x001   // Alignment fault
#define HW_C5_ICACHE_OP_FAULT       0x004   // Instruction cache maintenance operation fault
#define HW_C5_SECTION_TRANS_FAULT   0x005   // Section translation fault
#define HW_C5_SECTION_ACCESS_FAULT  0x003   // Section access bit fault
#define HW_C5_SECTION_DOMAIN_FAULT  0x009   // Section domain fault
#define HW_C5_SECTION_AP_FAULT      0x00d   // Section permission fault
#define HW_C5_PAGE_TRANS_FAULT      0x007   // Page translation fault
#define HW_C5_PAGE_ACCESS_FAULT     0x006   // Page access bit fault
#define HW_C5_PAGE_DOMAIN_FAULT     0x00b   // Page domain fault
#define HW_C5_PAGE_AP_FAULT         0x00f   // Page permission fault

#define HW_C5_EA1_EXT_ABORT         0x00c   // First-level external abort on translation
#define HW_C5_EA2_EXT_ABORT         0x00e   // Second-level external abort on translation
#define HW_C5_PRECISE_EXT_ABORT     0x008   // Precise external abort
#define HW_C5_IMPRECISE_EXT_ABORT   0x106   // Imprecise external abort

#define HW_C5_DEGUB_EVENT_ABORT     0x002   // Debug event abort


// Register 7.0 : Wait for interrupt

// Register 7.5 : Prefetch Buffer / Branch Target Cache Operation

// Register 7.10 : Data Memory Barrier / Drain Synchronization Barrier (Wait for Write Buffer Empty)

// Register 7.5/6/7/10/14 : Cache Operations

#define HW_C7_IC_MVA_MASK           0xffffffe0  // Instruction cache's modified virtual address (per 32B)
#define HW_C7_DC_MVA_MASK           0xffffffe0  // Data cache's modified virtual address (per 32B)
#define HW_C7_BC_MVA_MASK           0xfffffff8  // Modified virtual address of Branch Target Cache (per 8B)

#define HW_C7_IC_IDX_MASK           0x00001fe0  // Instruction cache's address index (per 32B)
#define HW_C7_DC_IDX_MASK           0x00001fe0  // Data cache's address index (per 32B)
#define HW_C7_CACHE_WAY_NO_MASK     0xc0000000  // Number of cache way

#define HW_C7_CACHE_IDX_SFT         5
#define HW_C7_CACHE_WAY_NO_SFT      30


// Register 7.4/8 : VA to PA operations

#define HW_C7_VA_SRC_MASK           0xfffffc00  // Virtual address (per 1KB)
#define HW_C7_PA_DEST_MASK          0xfffff000  // Physical address (per 4KB)
#define HW_C7_PA_RGT_MASK           0x000000c0  // Region Type
#define HW_C7_PA_L1C_CA_MASK        0x00000030  // L1 Cache attributes
#define HW_C7_PA_L2C_CA_MASK        0x0000000c  // L2 Cache attributes (Invalid for CTR)
#define HW_C7_PA_SHAREABLE          0x00000100  // Shareable
#define HW_C7_PA_AXI_SLVERR         0x00000040  // AXI abort marked as SLVERR
#define HW_C7_PA_AXI_DECERR         0x00000000  //                     DECERR
#define HW_C7_PA_FSR_ALIAS_MASK     0x0000003e  // Fault Status Register Alias
#define HW_C7_PA_ABORT              0x00000001  // Abort

#define HW_C7_PA_RGT_TYPE_SFT       6
#define HW_C7_PA_L1C_CA_SFT         4
#define HW_C7_PA_L2C_CA_SFT         2
#define HW_C7_PA_SHAREABLE_SFT      8
#define HW_C7_PA_FSR_ALIAS_SFT      1

#define HW_C7_RGT_STRONG_ORDER      0   // Strongly ordered Region
#define HW_C7_RGT_DEVICE            1   // Device Region
#define HW_C7_RGT_NORMAL            2   // Normal Region

#define HW_C7_CA_NC                 0   // Noncachable
#define HW_C7_CA_WB_WA              1   // Write-back Write-allocate
#define HW_C7_CA_WT_RA              2   // Write-through Read-allocate-only
#define HW_C7_CA_WB_RA              3   // Write-back Read-allocate


// Register 8 : TLB Operations

#define HW_C8_TLB_MVA_MASK          0xfffffc00  // Modified virtual address (per 1KB)
#define HW_C8_TLB_ASID_MASK         0x000000ff  // Application Space ID


// Register 9 : Data Cache Lockdown

#define HW_C9_DCL_WAY0              0x00000001  // Lockdown Way0
#define HW_C9_DCL_WAY1              0x00000002  //          Way1
#define HW_C9_DCL_WAY2              0x00000004  //          Way2
#define HW_C9_DCL_WAY3              0x00000008  //          Way3


// Register 10.0 : TLB Lockdown

#define HW_C10_TLBL_PRESERVE        0x00000001  // Preserve bit
#define HW_C10_TLBL_VICTIM_MASK     0x1c000000  // Victim

#define HW_C10_TLBL_VICTIM_SFT      26


// Register 10.2.0 : Region Type Remap for Primary Region

#define HW_C10_PRGT_SH_ON_NML_S1    0x00080000  // Remaps shareable attribute when S = 1, for Normal regions
#define HW_C10_PRGT_SH_ON_NML_S0    0x00040000  //                            when S = 0, for Normal regions
#define HW_C10_PRGT_SH_ON_DEV_S1    0x00020000  //                            when S = 1, for Device regions
#define HW_C10_PRGT_SH_ON_DEV_S0    0x00010000  //                            when S = 0, for Device regions
#define HW_C10_PRGT_TCB2_000_MASK   0x0000c000  // Remaps {TEX[0], C, B} = 000 for primary region
#define HW_C10_PRGT_TCB_101_MASK    0x00000c00  // Remaps {TEX[0], C, B} = 101
#define HW_C10_PRGT_TCB_100_MASK    0x00000300  // Remaps {TEX[0], C, B} = 100
#define HW_C10_PRGT_TCB_011_MASK    0x000000c0  // Remaps {TEX[0], C, B} = 011
#define HW_C10_PRGT_TCB_010_MASK    0x00000030  // Remaps {TEX[0], C, B} = 010
#define HW_C10_PRGT_TCB_001_MASK    0x0000000c  // Remaps {TEX[0], C, B} = 001
#define HW_C10_PRGT_TCB_000_MASK    0x00000003  // Remaps {TEX[0], C, B} = 000

#define HW_C10_PRGT_TCB2_000_SFT    14
#define HW_C10_PRGT_TCB_101_SFT     10
#define HW_C10_PRGT_TCB_100_SFT     8
#define HW_C10_PRGT_TCB_011_SFT     6
#define HW_C10_PRGT_TCB_010_SFT     4
#define HW_C10_PRGT_TCB_001_SFT     2
#define HW_C10_PRGT_TCB_000_SFT     0

#define HW_C10_PRGT_STRONG_ORDER    0   // Strongly ordered Region
#define HW_C10_PRGT_DEVICE          1   // Device Region
#define HW_C10_PRGT_NORMAL          2   // Normal Region

// Register 10.2.1 : Region Attribute Remap for Normal Region 

#define HW_C10_NCA_L2C_TCB_111_MASK 0xc0000000  // Remaps L2 Cache attribute for normal region {TEX[0], C, B} = 111
#define HW_C10_NCA_L2C_TCB_101_MASK 0x0c000000  //                                             {TEX[0], C, B} = 101
#define HW_C10_NCA_L2C_TCB_100_MASK 0x03000000  //                                             {TEX[0], C, B} = 100
#define HW_C10_NCA_L2C_TCB_011_MASK 0x00c00000  //                                             {TEX[0], C, B} = 011
#define HW_C10_NCA_L2C_TCB_010_MASK 0x00300000  //                                             {TEX[0], C, B} = 010
#define HW_C10_NCA_L2C_TCB_001_MASK 0x000c0000  //                                             {TEX[0], C, B} = 001
#define HW_C10_NCA_L2C_TCB_000_MASK 0x00030000  //                                             {TEX[0], C, B} = 000

#define HW_C10_NCA_L1C_TCB_111_MASK 0x0000c000  // Remaps L1 Cache attribute for normal region {TEX[0], C, B} = 111
#define HW_C10_NCA_L1C_TCB_101_MASK 0x00000c00  //                                             {TEX[0], C, B} = 101
#define HW_C10_NCA_L1C_TCB_000_MASK 0x00000300  //                                             {TEX[0], C, B} = 000
#define HW_C10_NCA_L1C_TCB_001_MASK 0x000000c0  //                                             {TEX[0], C, B} = 001
#define HW_C10_NCA_L1C_TCB_010_MASK 0x00000030  //                                             {TEX[0], C, B} = 010
#define HW_C10_NCA_L1C_TCB_011_MASK 0x0000000c  //                                             {TEX[0], C, B} = 011
#define HW_C10_NCA_L1C_TCB_100_MASK 0x00000003  //                                             {TEX[0], C, B} = 100

#define HW_C10_NCA_L2C_TCB_111_SFT  30
#define HW_C10_NCA_L2C_TCB_101_SFT  26
#define HW_C10_NCA_L2C_TCB_100_SFT  24
#define HW_C10_NCA_L2C_TCB_011_SFT  22
#define HW_C10_NCA_L2C_TCB_010_SFT  20
#define HW_C10_NCA_L2C_TCB_001_SFT  18
#define HW_C10_NCA_L2C_TCB_000_SFT  16

#define HW_C10_NCA_L1C_TCB_111_SFT  14
#define HW_C10_NCA_L1C_TCB_101_SFT  10
#define HW_C10_NCA_L1C_TCB_000_SFT  8
#define HW_C10_NCA_L1C_TCB_010_SFT  4
#define HW_C10_NCA_L1C_TCB_011_SFT  2
#define HW_C10_NCA_L1C_TCB_100_SFT  0

#define HW_C10_NCA_NC               0   // Noncachable
#define HW_C10_NCA_WB_WA            1   // Write-back Write-allocate


// Register 13.0.0 : FCSE Process ID (Not Recommended for MPCore)

#define HW_C13_FCSE_PID_MASK        0xfe000000  // FCSE Process ID

#define HW_C13_FCSE_PID_SFT         25


// Register 13.0.1 : Context ID

#define HW_C13_CONTEXT_PROCID_MASK  0xffffff00  // Process ID
#define HW_C13_CONTEXT_ASID_MASK    0x000000ff  // Application Space ID

#define HW_C13_CONTEXT_PROCID_SFT   8


// Register 13.0.2/3/4 : Thread ID


// Register 15.12.0 : Performance Monitor Control

#define HW_C15_COUNT0_EVT_MASK      0x0ff00000  // Identifies the source of events for Count Register 0
#define HW_C15_COUNT1_EVT_MASK      0x000ff000  //                                 for Count Register 1
#define HW_C15_CYCLE_COUNT_OVERFLOW 0x00000400  // Cycle Counter overflow
#define HW_C15_COUNT1_OVERFLOW      0x00000200  // Count Register 1 overflow
#define HW_C15_COUNT0_OVERFLOW      0x00000100  // Count Register 0 overflow
#define HW_C15_CYCLE_COUNT_IE       0x00000040  // Cycle Counter interrupt enable
#define HW_C15_COUNT1_IE            0x00000020  // Count Register 1 interrupt enable
#define HW_C15_COUNT0_IE            0x00000010  // Count Register 0 interrupt enable
#define HW_C15_CYCLE_COUNT_D64      0x00000008  // Cycle Counter counts every 64th processor clock cycle
#define HW_C15_CYCLE_COUNT_RESET    0x00000004  // Cycle Counter Reset on Write
#define HW_C15_COUNT01_RESET        0x00000002  // Counter Register 0/1 Reset on Write
#define HW_C15_PMN_ENABLE           0x00000001  // All three counters enable

#define HW_C15_COUNT0_EVT_SFT       20
#define HW_C15_COUNT1_EVT_SFT       12

#define HW_C15_EVT_IC_MISS          0x00    // Instruction cache miss
#define HW_C15_EVT_IFETCH_STALL     0x01    // Instruction fetch stall
#define HW_C15_EVT_DATA_STALL       0x02    // Data stall
#define HW_C15_EVT_ITLB_MISS        0x03    // Instruction MicroTLB miss
#define HW_C15_EVT_DTLB_MISS        0x04    // Data MicroTLB miss
#define HW_C15_EVT_MIGHT_BR_MISS    0x05    // Branch might have changed program flow
#define HW_C15_EVT_BR_NOT_PREDICT   0x06    // Branch not predicted
#define HW_C15_EVT_BR_PREDICT_MISS  0x07    // Branch predict miss
#define HW_C15_EVT_INST_EXEC        0x08    // Instruction executed
#define HW_C15_EVT_FOLD_INST_EXEC   0x09    // Folded instruction executed
#define HW_C15_EVT_DC_READ          0x0a    // Data cache read
#define HW_C15_EVT_DC_MISS          0x0b    // Data cache miss
#define HW_C15_EVT_DC_WRITE         0x0c    // Data cache write
#define HW_C15_EVT_DC_WRITE_MISS    0x0d    // Data cache write miss
#define HW_C15_EVT_DC_LINE_EVICT    0x0e    // Data cache line eviction
#define HW_C15_EVT_SW_CHANGE_PC     0x0f    // Software changed the PC and there is not a mode change
#define HW_C15_EVT_MTLB_MISS        0x10    // Main TLB miss
#define HW_C15_EVT_EXMEM_REQ        0x11    // External memory request (Cache Refill, Noncachable, Write-Back)
#define HW_C15_EVT_LSQ_FULL_STALL   0x12    // Stall because of Load Store Unit request queue being full
#define HW_C15_EVT_STB_DRAIN_TIMES  0x13    // Store buffer drain times
#define HW_C15_EVT_STB_MERGED       0x14    // Store buffer write is merged
#define HW_C15_EVT_LSU_SAFE_MODE    0x15    // Load Store Unit is in safe mode
#define HW_C15_EVT_INC_EACH_CYCLE   0xff    // An increment each cycle


// Register 15.1.0 : Main TLB Debug Control

#define HW_C15_MTLB_LD_ENABLE       0x00000000  // Main TLB load enabled
#define HW_C15_MTLB_LD_DISABLE      0x00000030  // Main TLB load disabled


// Register 15.4 : Select TLB lockdown entry operations

#define HW_C15_TLBL_SEL_ENTRY_IDX   0x0000003f  // Set-associative region index
#define HW_C15_TLBL_LKABLE_IDX      0x80000000  // Lockable region index

#define HW_C15_TLBL_ASSOC_WAY_MASK  0x00000020  // if ASSOCIATIVE, Way index
#define HW_C15_TLBL_ASSOC_SET_MASK  0x0000001f  // if ASSOCIATIVE, Set index
#define HW_C15_TLBL_LKABLE_ET_MASK  0x00000003  // if LOCKABLE,    Lockable entry


// Register 15.5 : TLB Lockdown VA operations

#define HW_C15_TLBL_VPN_MASK        0xfffff000  // TLB Virtual page number (per 4KB)
#define HW_C15_TLBL_MSID_MASK       0x000003ff  // Memory space ID

#define HW_C15_TLBL_VPN_SFT         12

#define HW_C15_TLBL_MSID_GLOBAL     0x200   // Global entries
#define HW_C15_TLBL_MSID_ASID_MASK  0x0ff   // Application Space ID entries


// Register 15.6 : TLB Lockdown PA operations

#define HW_C15_TLBL_PPN_MASK        0xfffff000  // TLB Physical page number (per 4KB)
#define HW_C15_TLBL_PSIZE_MASK      0x000000c0  // Page size
#define HW_C15_TLBL_APX_MASK        0x0000000e  // Access Permissions Extension
#define HW_C15_TLBL_LOCKED_VALID    0x00000001  // Locked and valid

#define HW_C15_TLBL_PPN_SFT         12
#define HW_C15_TLBL_PSIZE_SFT       6
#define HW_C15_TLBL_APX_SFT         1

#define HW_C15_PSIZE_4KB            1   // 4KB page
#define HW_C15_PSIZE_64KB           2   // 64KB page
#define HW_C15_PSIZE_1MB            3   // 1MB page
#define HW_C15_PSIZE_16MB           0   // 16MB page

#define HW_C15_APX_NA               0   // Access denied
#define HW_C15_APX_S_RW_U_NA        1   // Supervisor access only
#define HW_C15_APX_S_RW_U_RO        2   // Supervisor full access, User read only
#define HW_C15_APX_ALL              3   // Full access
#define HW_C15_APX_S_RO_U_NA        5   // Supervisor read only
#define HW_C15_APX_S_RO_U_RO        6   // Supervisor/User read only


// Register 15.7 : TLB Lockdown Attributes
/*
#define HW_C15_TLBL_SP4_AP_MASK     0xc0000000  // Permissions for the 4th subpage (for MMUv5)
#define HW_C15_TLBL_SP3_AP_MASK     0x30000000  // Permissions for the 3rd subpage (for MMUv5)
#define HW_C15_TLBL_SP2_AP_MASK     0x0c000000  // Permissions for the 2nd subpage (for MMUv5)
#define HW_C15_TLBL_SP_VALID        0x02000000  // Subpages are supported (for MMUv5)
*/
#define HW_C15_TLBL_SP_INVALID      0x00000000  // Subpages are not supported (for MMUv6)
#define HW_C15_TLBL_DOMAIN_MASK     0x00000780  // Domain number of the TLB entry
#define HW_C15_TLBL_XN              0x00000040  // Execute Never
#define HW_C15_TLBL_RGT_MASK        0x0000003e  // Region Type
#define HW_C15_TLBL_SHARED          0x00000001  // Shared
/*
#define HW_C15_TLBL_SP4_AP_SFT      30
#define HW_C15_TLBL_SP3_AP_SFT      28
#define HW_C15_TLBL_SP2_AP_SFT      26
*/
#define HW_C15_TLBL_DOMAIN_SFT      7
#define HW_C15_TLBL_RGT_SFT         1
#define HW_C15_TLBL_CBA_L1C_SFT     1
#define HW_C15_TLBL_CBA_L2C_SFT     3

#define HW_C15_SP_AP_NA             0   // Access denied (not use S, R)
#define HW_C15_SP_AP_S_RW_U_NA      1   // Supervisor access only
#define HW_C15_SP_AP_S_RW_U_RO      2   // Supervisor full access, User read only
#define HW_C15_SP_AP_ALL            3   // Full access

#define HW_C15_RGT_STRONG_ORDER     0x00    // Strongly Ordered, regardless of the S bit in the page table
#define HW_C15_RGT_SHARED_DEVICE    0x01    // Shared Device, regardless of the S bit in the page table
#define HW_C15_RGT_NSHARED_DEVICE   0x08    // Non-Shared Device, regardless of the S bit in the page table
#define HW_C15_RGT_L1C_NC_NB        0x10    // L1C Noncachable, Unbuffered
#define HW_C15_RGT_L1C_WB_WA        0x11    // L1C Write-back Write-allocate, Buffered
#define HW_C15_RGT_L1L2C_NC         0x04    // L1C and L2C Noncachable
#define HW_C15_RGT_L1L2C_WB_WA      0x07    // L1C and L2C Write-Back, Allocate on Write
    
#define HW_C15_TTBR0_MASK           0xFFFFFFFF
    
#ifdef __cplusplus
} // extern "C"
#endif

// NN_HW_ARM_ARMV6_REG_H_
#endif
