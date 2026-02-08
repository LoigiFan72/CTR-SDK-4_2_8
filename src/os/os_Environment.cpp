/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Environment.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_EnvironmentSelect.h>
#include <nn/os/os_SharedInfo.h>
#include <nn/assert.h>
#include <nn/svc.h>
#include <nn/util.h>

namespace nn { namespace os {

    size_t  GetAppMemorySize()
    {
        return (GetReadOnlySharedInfo().kParamValues[0]);
    }

    size_t  GetUsingPrivateMemorySize()
    {
        s64 currentUse;

        nn::svc::GetProcessInfo(
            &currentUse,
            nn::PSEUDO_HANDLE_CURRENT_PROCESS,
            PROCESS_INFO_TYPE_PRIVATE_PHYSICAL_MEMORY_SIZE );

        return static_cast<size_t>(currentUse);
    }

    size_t  GetMemoryQuotaSize()
    {
        Handle h;
        s64 v[1];
        LimitableResource names[1] = { LIMITABLE_RESOURCE_MAX_COMMIT };

        svc::GetResourceLimit(&h, PSEUDO_HANDLE_CURRENT_PROCESS);
        svc::GetResourceLimitLimitValues(v, h, names, sizeof(*util::NumOfElementsT(names)) );
        svc::CloseHandle(h);

        return static_cast<size_t>(v[0]);
    }

    size_t  GetUsingMemorySize()
    {
        Handle h;
        s64 v[1];
        LimitableResource names[1] = { LIMITABLE_RESOURCE_MAX_COMMIT };

        svc::GetResourceLimit(&h, PSEUDO_HANDLE_CURRENT_PROCESS);
        svc::GetResourceLimitCurrentValues(v, h,  names, sizeof(*util::NumOfElementsT(names)) );
        svc::CloseHandle(h);

        return static_cast<size_t>(v[0]);
    }

    Tick GetCreationTime()
    {
        s64 tick;

        svc::GetHandleInfo(
            &tick,
            PSEUDO_HANDLE_CURRENT_PROCESS,
            HANDLE_INFO_TYPE_CREATION_TIME );

        return Tick(tick);
    }

}}

