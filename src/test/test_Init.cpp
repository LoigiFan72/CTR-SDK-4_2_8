/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_Init.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os.h>

extern "C" void nntestCTRARMv5TestMain();


#if defined(NN_PLATFORM_CTR) && defined(NN_PROCESSOR_ARM_V5)
extern "C" void nniopdevMain()
{
    const s32 prevPrio = nn::os::Thread::GetCurrentPriority();
    nn::os::Thread::ChangeCurrentPriority(nn::os::DEFAULT_THREAD_PRIORITY);

    nntestCTRARMv5TestMain();

    nn::os::Thread::ChangeCurrentPriority(prevPrio);
}
#endif

