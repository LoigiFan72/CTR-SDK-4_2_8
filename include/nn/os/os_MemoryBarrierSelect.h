/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryBarrierSelect.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/*!
    @file

    :include nn/os.h
*/

#ifndef NN_OS_OS_MEMORYBARRIERSELECT_H_
#define NN_OS_OS_MEMORYBARRIERSELECT_H_


#ifdef __cplusplus

#if   defined(NN_PROCESSOR_ARM)

#include <nn/os/ARM/os_MemoryBarrier.h>

namespace nn { namespace os {
    using ARM::DataSynchronizationBarrier;
    using ARM::DataMemoryBarrier;
    using ARM::InstructionMemoryBarrier;
}}

#else
#error no processor is selected
#endif

#endif // __cplusplus


#endif /* NN_OS_OS_MEMORYBARRIERSELECT_H_ */
