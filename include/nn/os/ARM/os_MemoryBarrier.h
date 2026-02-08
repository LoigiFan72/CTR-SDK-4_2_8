/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryBarrier.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_ARM_OS_MEMORYBARRIER_H_
#define NN_OS_ARM_OS_MEMORYBARRIER_H_

#ifdef __cplusplus

#include <nn/config.h>

namespace nn {
namespace os {
namespace ARM {


    inline void DataSynchronizationBarrier()
    {
        NN_ASM("mcr   p15, 0, 0, c7, c10, 4");
    }

    inline void DataMemoryBarrier()
    {
#ifdef NN_PROCESSOR_ARM_V6
        NN_ASM("mcr   p15, 0, 0, c7, c10, 5");
#endif
    }

    inline void InstructionMemoryBarrier()
    {
#ifdef NN_PROCESSOR_ARM_V6
        NN_ASM("mcr   p15, 0, 0, c7, c5, 4");
#endif
    }


}   // end of namespace ARM
}   // end of namespace os
}   // end of namespace nn

#endif // __cplusplus

#endif /* NN_OS_ARM_OS_MEMORYBARRIER_H_ */
