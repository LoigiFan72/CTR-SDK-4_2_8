/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_WaitableCounter.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#include <nn/os/os_WaitableCounter.h>
#include <nn/assert.h>


namespace nn { namespace os {

    // When explicitly initializing with INVALID_HANDLE_VALUE,
    // relies on bss clear because it is initialized with static_initializer
    nnHandle WaitableCounter::s_Handle = {0};

    void WaitableCounter::Initialize()
    {
        if( s_Handle.value == INVALID_HANDLE_VALUE.value )
        {
            Handle h;
            Result ret = nn::svc::CreateAddressArbiter(&h);
            NN_TASSERT_( ret.IsSuccess() );

            if( ret.IsSuccess() )
            {
                s_Handle = h;
            }
        }
    }

    void WaitableCounter::Finalize()
    {
        if( s_Handle.value != INVALID_HANDLE_VALUE.value )
        {
            Result ret = nn::svc::CloseHandle(s_Handle);
            NN_TASSERT_( ret.IsSuccess() );

            if( ret.IsSuccess() )
            {
                s_Handle.value = INVALID_HANDLE_VALUE.value;
            }
        }
    }

}}

namespace nn { namespace svc {
    Result ArbitrateAddress( Handle arbiter, uptr addr, nn::os::ArbitrationType type, s32 value )
    {
        return svc::ArbitrateAddress(arbiter, addr, type, value, 0);
    }
}}
