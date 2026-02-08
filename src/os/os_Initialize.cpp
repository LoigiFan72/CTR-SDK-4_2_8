/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Initialize.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47384 $
 *---------------------------------------------------------------------------*/

#include <nn/Result.h>
#include <nn/os.h>
#include <nn/os/os_Private.h>

NN_DBG_DECLARE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(os)
NN_DBG_DECLARE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(fnd)

namespace nn { namespace os {

void Initialize()
{
    nn::os::WaitableCounter::Initialize();
#if NN_PLATFORM_HAS_MMU
    nn::os::detail::SaveThreadLocalRegionAddress();
    nn::os::detail::InitializeSharedMemory();
    nn::os::detail::InitializeStackMemory();
#endif  // if NN_PLATFORM_HAS_MMU
    nn::os::detail::InitializeThreadEnvrionment();
    NN_DBG_USE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(os);
    NN_DBG_USE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(fnd);
}

}}

extern "C" {

void nnosInitialize()
{
    nn::os::Initialize();
}

}
