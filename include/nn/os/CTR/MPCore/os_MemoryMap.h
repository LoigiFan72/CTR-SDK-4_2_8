/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryMap.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_CTR_MPCORE_OS_MEMORYMAPPROCESS_H_
#define NN_OS_CTR_MPCORE_OS_MEMORYMAPPROCESS_H_


#define NN_OS_ADDR_SIZE(name)   (name ## _END - name ## _BEGIN)

//--------------------------------------------------
// Memory space overall

#define NN_OS_ADDR_SPACE_BEGIN  0x00000000
#define NN_OS_ADDR_SPACE_END    0x20000000


//--------------------------------------------------
// Specific memory spaces

#define NN_OS_ADDR_NULL_TRAP_BEGIN  NN_OS_ADDR_SPACE_BEGIN
#define NN_OS_ADDR_NULL_TRAP_END    NN_OS_ADDR_CODE_BEGIN
#define NN_OS_ADDR_NULL_TRAP_SIZE   NN_OS_ADDR_SIZE(NN_OS_ADDR_NULL_TRAP)

#define NN_OS_ADDR_CODE_BEGIN       0x00100000
#define NN_OS_ADDR_CODE_END         NN_OS_ADDR_LAND_BEGIN
#define NN_OS_ADDR_CODE_SIZE        NN_OS_ADDR_SIZE(NN_OS_ADDR_CODE)

#define NN_OS_ADDR_LAND_BEGIN       0x04000000
#define NN_OS_ADDR_LAND_END         NN_OS_ADDR_HEAP_BEGIN
#define NN_OS_ADDR_LAND_SIZE        NN_OS_ADDR_SIZE(NN_OS_ADDR_LAND)

#define NN_OS_ADDR_HEAP_BEGIN       0x08000000
#define NN_OS_ADDR_HEAP_END         NN_OS_ADDR_STACK_BEGIN
#define NN_OS_ADDR_HEAP_SIZE        NN_OS_ADDR_SIZE(NN_OS_ADDR_HEAP)

#define NN_OS_ADDR_STACK_BEGIN      0x0E000000
#define NN_OS_ADDR_STACK_END        NN_OS_ADDR_SHARED_BEGIN
#define NN_OS_ADDR_STACK_SIZE       NN_OS_ADDR_SIZE(NN_OS_ADDR_STACK)

#define NN_OS_ADDR_SHARED_BEGIN     0x10000000
#define NN_OS_ADDR_SHARED_END       NN_OS_ADDR_CONTINUOUS_BEGIN
#define NN_OS_ADDR_SHARED_SIZE      NN_OS_ADDR_SIZE(NN_OS_ADDR_SHARED)

#define NN_OS_ADDR_CONTINUOUS_BEGIN 0x14000000
#define NN_OS_ADDR_CONTINUOUS_END   NN_OS_ADDR_RESERVED_BEGIN
#define NN_OS_ADDR_CONTINUOUS_SIZE  NN_OS_ADDR_SIZE(NN_OS_ADDR_CONTINUOUS)

#define NN_OS_ADDR_RESERVED_BEGIN   0x1C000000
#define NN_OS_ADDR_RESERVED_END     NN_OS_ADDR_SPACE_END
#define NN_OS_ADDR_RESERVED_SIZE    NN_OS_ADDR_SIZE(NN_OS_ADDR_RESERVED)


//--------------------------------------------------
// Specific reserved regions

#define NN_OS_ADDR_USER_BEGIN               NN_OS_ADDR_HEAP_BEGIN
#define NN_OS_ADDR_USER_END                 NN_OS_ADDR_SHARED_END

#define NN_OS_ADDR_VRAM_BEGIN               0x1F000000
#define NN_OS_ADDR_VRAM_END                 (NN_OS_ADDR_VRAM_BEGIN + NN_OS_ADDR_VRAM_SIZE)
#if    defined(NN_HARDWARE_CTR_TEG2)
    #define NN_OS_ADDR_VRAM_SIZE            0x00400000
#else
    #define NN_OS_ADDR_VRAM_SIZE            0x00600000
#endif

#define NN_OS_ADDR_DSP_WRAM_BEGIN           0x1FF00000
#define NN_OS_ADDR_DSP_WRAM_END             (NN_OS_ADDR_DSP_WRAM_BEGIN + NN_OS_ADDR_DSP_WRAM_SIZE)
#define NN_OS_ADDR_DSP_WRAM_SIZE            0x00080000

#define NN_OS_ADDR_READONLY_SHARED_PAGE     0x1FF80000
#define NN_OS_ADDR_WRITABLE_SHARED_PAGE     0x1FF81000

#define NN_OS_ADDR_THREAD_LOCAL_REGION_BEGIN    0x1FF82000
#define NN_OS_ADDR_THREAD_LOCAL_REGION_END      NN_OS_ADDR_RESERVED_END
#define NN_OS_ADDR_THREAD_LOCAL_REGION_SIZE     NN_OS_ADDR_SIZE(NN_OS_ADDR_THREAD_LOCAL_REGION)


#endif /* NN_OS_CTR_MPCORE_OS_MEMORYMAPPROCESS_H_ */
