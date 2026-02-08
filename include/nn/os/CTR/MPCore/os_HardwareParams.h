/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_HardwareParams.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_CTR_MPCORE_OS_HARDWAREPARAMS_H_
#define NN_OS_CTR_MPCORE_OS_HARDWAREPARAMS_H_


#define NN_HW_CPU_CLOCK         (67027964 * 4)

#define NN_HW_TICKS_PER_SECOND  (NN_HW_CPU_CLOCK)

#ifdef __cplusplus

    namespace nn { namespace os { namespace CTR { namespace MPCore {
        const s64 SLEEP_SPIN_THRESHOLD = 13431;
        const s64 SLEEP_OFFSET         = 11000;
    }}}}

#endif  // ifdef __cplusplus


#endif  // ifndef NN_OS_CTR_MPCORE_OS_HARDWAREPARAMS_H_
