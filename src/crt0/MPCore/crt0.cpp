/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crt0.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/os/os_MemoryMapSelect.h>
#include <nn/init/init_StartUp.h>
#include <rt_sys.h>
#include <rt_locale.h>
#include <nn/os/os_SharedInfo.h>
#include <nn/svc.h>
#include <nn/assert.h>
#include <nn/version.h>
#include <nn/middleware.h>

namespace
{
#if defined(NN_BUILD_NOOPT) || defined(NN_BUILD_VERBOSE)
    NN_DEFINE_MIDDLEWARE(s_DebugIndicator,  "NINTENDO", "DEBUG");
#endif

    NN_DEFINE_MIDDLEWARE(s_SdkVersion,      "NINTENDO", NN_CURRENT_SDK_VERSION);
    NN_DEFINE_MIDDLEWARE(s_FirmwareVersion, "NINTENDO", NN_CURRENT_FIRMWARE_VERSION);
}


extern "C" void     nninitLocale();
extern "C" void     nninitRegion();

extern "C" NN_WEAK_SYMBOL void __cpp_initialize__aeabi_(void);
extern "C" bit32*   __rt_locale(void);
extern "C" void     _fp_init(void);

extern "C" bit8     Image$$ZI$$ZI$$Base[];
extern "C" bit8     Image$$ZI$$ZI$$Limit[];

#include <nn/hw/ARM/code32.h>
extern "C" asm void __ctr_start( void )
{
        PRESERVE8

        // Initialization of the ZI region
        bl              __cpp(nninitRegion)
        bl              __cpp(nninitLocale)

        // Initialization
        blx             __cpp(nninitSystem)
        blx             __cpp(nninitStartUp)
        
        // Calls the C++ static initializer
        blx             __cpp(__cpp_initialize__aeabi_)
        // Calls the C static initializer
        blx             __cpp(nninitCallStaticInitializers)

        // Library setup
        blx             __cpp(nninitSetup)

        //---- Start (to 16-bit code)
        blx             __cpp(nnMain)

terminate
        b               __cpp(nn::svc::ExitProcess)
}
#include <nn/hw/ARM/codereset.h>



extern "C" void nninitLocale()
{
#if defined(NN_BUILD_NOOPT) || defined(NN_BUILD_VERBOSE)
    NN_UTIL_REFER_SYMBOL(s_DebugIndicator);
#endif
    NN_UTIL_REFER_SYMBOL(s_SdkVersion);
    NN_UTIL_REFER_SYMBOL(s_FirmwareVersion);

    bit32* p = __rt_locale();
    *(p + 1) = (bit32)_get_lc_ctype(0, 0) + 1;
    *(p + 3) = (bit32)_get_lc_numeric(0, 0);
}

#include <nn/hw/ARM/code32.h>
extern "C" asm void nninitRegion(void)
{
        ldr     r0, =__cpp(Image$$ZI$$ZI$$Base)
        ldr     r1, =__cpp(Image$$ZI$$ZI$$Limit)
        mov     r2, #0
loop
        cmp     r0, r1
        strcc   r2, [r0], #4
        bcc     loop
        bx      lr
}
#include <nn/hw/ARM/codereset.h>




