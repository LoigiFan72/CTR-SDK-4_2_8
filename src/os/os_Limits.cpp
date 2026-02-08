/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Limits.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/os.h>
#include "os_Limits.h"

namespace nn { namespace os { namespace detail {

    namespace
    {
        class AutoCloser
        {
        public:
            AutoCloser(Handle h) : m_Handle(h)
            {
            }
            ~AutoCloser()
            {
                svc::CloseHandle(m_Handle);
            }

        private:
            Handle  m_Handle;
        };
    }

    s32 GetLimitCurrentCount(LimitableResource res)
    {
        Handle h;
        s64 v;
        Result result;

        result = svc::GetResourceLimit(&h, nn::PSEUDO_HANDLE_CURRENT_PROCESS);
        if( result.IsFailure() )
        {
            return 0;
        }

        AutoCloser ac(h);

        result = svc::GetResourceLimitCurrentValues(&v, h, &res, 1);
        if( result.IsFailure() )
        {
            return 0;
        }

        return static_cast<s32>(v);
    }

    s32 GetLimitMaxCount(LimitableResource res)
    {
        Handle h;
        s64 v;
        Result result;

        result = svc::GetResourceLimit(&h, nn::PSEUDO_HANDLE_CURRENT_PROCESS);
        if( result.IsFailure() )
        {
            return 0;
        }

        AutoCloser ac(h);

        result = svc::GetResourceLimitLimitValues(&v, h, &res, 1);
        if( result.IsFailure() )
        {
            return 0;
        }

        return static_cast<s32>(v);
    }

}}}


#endif  // if NN_PLATFORM_HAS_MMU
