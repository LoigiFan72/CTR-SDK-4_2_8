/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SpinWait.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os.h>

namespace nn {
namespace os {
namespace ARM {

#include    <nn/hw/ARM/code32.h>
    asm void  SpinWaitCpuCycles( s32 cycle NN_IS_UNUSED_VAR )
    {
#if     defined(NN_PROCESSOR_ARM11MPCORE)
NN_LSYM(1)
        subs   r0, r0, #2       // 1 Loop 2 Cycles
        nop                     // Eliminate nop for 5 cycles
        bgt    NN_BSYM(1)
        bx     lr
#elif   defined(NN_PROCESSOR_ARM946ES)
NN_LSYM(1)
        subs   r0, r0, #4   // 1 cycle
        bgt    NN_BSYM(1)   // 3 cycle
        bx     lr
#else
    #error no cpu selected
#endif
    }
#include    <nn/hw/ARM/codereset.h>
    
}
}
}
