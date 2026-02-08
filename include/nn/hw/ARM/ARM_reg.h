/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ARM_reg.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_ARM_ARM_REG_H_
#define NN_HW_ARM_ARM_REG_H_


#if     defined(NN_PROCESSOR_ARM_V7)
    #include <nn/hw/ARM/ARMv7_reg.h>
#elif   defined(NN_PROCESSOR_ARM_V6)
    #include <nn/hw/ARM/ARMv6_reg.h>
#elif   defined(NN_PROCESSOR_ARM_V5)
    #include <nn/hw/ARM/ARMv5_reg.h>
#elif   defined(NN_PROCESSOR_ARM_V4)
    #include <nn/hw/ARM/ARMv4_reg.h>
#else
    #error  processor not selected
#endif

#if     defined(NN_PROCESSOR_ARM_VFP_V3)
    #include <nn/hw/ARM/VFPv3_reg.h>
#elif   defined(NN_PROCESSOR_ARM_VFP_V2)
    #include <nn/hw/ARM/VFPv2_reg.h>
#endif

#include <nn/hw/ARM/reg_common.h>

#endif  // ifndef NN_HW_ARM_ARM_REG_H_
