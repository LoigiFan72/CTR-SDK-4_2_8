/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     init_Default.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48011 $
 *---------------------------------------------------------------------------*/

#include <nn/config.h>
#include <nn/init.h>
#include <nn/os.h>
#include <nn/dbg/dbg_Default.h>
#include <nn/srv.h>

namespace
{
    class ExitHandler : public nn::srv::NotificationHandler
    {
    public:
        virtual void HandleNotification(bit32 message)
        {
            NN_UNUSED_VAR(message);

            nn::svc::ExitProcess();
        }
    };



#if NN_PLATFORM_HAS_MMU
    bool        s_UsingStartUpDefault = false;
#endif  // if NN_PLATFORM_HAS_MMU
    ExitHandler s_ExitHandler;
}

extern "C" void nninitStartUpDefault(void)
{
#if NN_PLATFORM_HAS_MMU
    const size_t assingment   = nn::os::GetAppMemorySize();
    const size_t currentUsing = nn::os::GetUsingMemorySize();

    const size_t DEVICE_MEMORY_SIZE = 32 * 1024 * 1024;
    const size_t available = assingment - currentUsing;
    const size_t heapSize  = available - DEVICE_MEMORY_SIZE;

    nn::os::SetupHeapForMemoryBlock(heapSize);
    NN_UTIL_PANIC_IF_FAILED( nn::os::SetDeviceMemorySize( DEVICE_MEMORY_SIZE ) );

    nn::init::InitializeAllocator( 8 * 1024 * 1024 );

    s_UsingStartUpDefault = true;

    nn::os::ManagedThread::InitializeEnvironment();
    nn::dbg::SetDefaultExceptionHandler();
    nn::dbg::SetDefaultBreakHandler();
#endif  // if NN_PLATFORM_HAS_MMU
}

extern "C" bool nninitIsStartUpDefaultUsing()
{
    bool ret = false;
#if NN_PLATFORM_HAS_MMU
    ret = s_UsingStartUpDefault;
#endif  // if NN_PLATFORM_HAS_MMU
    return ret;
}

extern "C" void nninitSetupDefault(void)
{
#if NN_PLATFORM_HAS_MMU
    nn::srv::Initialize();
    nn::srv::StartNotification();
#endif  // if NN_PLATFORM_HAS_MMU
}

extern "C" void nninitSetupDefaultWithSettingExitHandler(void)
{
#if NN_PLATFORM_HAS_MMU
    nn::srv::Initialize();
    nn::srv::StartNotification();

    nn::srv::RegisterNotificationHandler(&s_ExitHandler, nn::srv::NOTIFICATION_EXIT);
#endif  // if NN_PLATFORM_HAS_MMU
}

