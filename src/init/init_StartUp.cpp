/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     init_StartUp.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47285 $
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------

#include <nn/config.h>
#include <nn/init.h>
#include <nn/os/os_Initialize.h>
#include <nn/ndm.h>

#define NN_SYSTEM_DEFAULT_HEAP_SIZE     0x00800000

extern "C" nninitStaticInitFunc Image$$STATIC_INIT$$RO$$Base[];
extern "C" nninitStaticInitFunc Image$$STATIC_INIT$$RO$$Limit[];

#if NN_PLATFORM_HAS_MMU
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/applet/CTR/applet_API.h>
namespace nn {
namespace applet {
namespace CTR {
namespace detail {
    // If libnn_applet.a is not linked, this is used by the nninitSetup function
    __declspec(noinline) Result Initialize( AppletAttr appletAttr )
    {
        return ResultSuccess();
    }
}}}}
#endif

extern "C" NN_WEAK_SYMBOL void nninitSystem(void)
{
    // OS Library initialization
    nn::os::Initialize();
}

extern "C" NN_WEAK_SYMBOL void nninitStartUp(void)
{
    nninitStartUpDefault();
}

#if NN_PLATFORM_HAS_MMU
extern "C" NN_WEAK_SYMBOL void nninitSetupDaemons(void)
{
    // Performs default settings for daemon manager
    nn::ndm::SetupDaemonsDefault();
}
#endif

extern "C" void nninitCallStaticInitializers(void)
{
    for( nninitStaticInitFunc* f = Image$$STATIC_INIT$$RO$$Base;
         f < Image$$STATIC_INIT$$RO$$Limit;
         ++f )
    {
        (*f)();
    }
}

extern "C" NN_WEAK_SYMBOL void nninitSetup(void)
{
    nninitSetupDefault();

#if NN_PLATFORM_HAS_MMU
    nn::os::detail::SetInternalErrorHandlingMode(false);
    nn::applet::CTR::detail::Initialize();
    nninitSetupDaemons();
#endif
}

