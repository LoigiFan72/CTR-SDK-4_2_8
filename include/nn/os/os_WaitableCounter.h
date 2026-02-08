/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_WaitableCounter.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_WAITABLETIMER_H_
#define NN_OS_OS_WAITABLETIMER_H_

#ifdef __cplusplus

#include <nn/fnd/fnd_Interlocked.h>
#include <nn/fnd/fnd_TimeSpan.h> 
#include <nn/util/util_NonCopyable.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/svc.h>

namespace nn { namespace os {

class WaitableCounter
{
private:
    static nnHandle s_Handle;

private:
    typedef nn::fnd::InterlockedVariable<s32> ValueType;
    ValueType   m_Value;

public:
    static void Initialize();

    static void Finalize();

    ValueType& operator *() { return m_Value; }
    const ValueType& operator *() const { return m_Value; }
    ValueType* operator->() { return &m_Value; }

    Result DecrementAndWaitIfLessThan(s32 value, fnd::TimeSpan timeout)
    {
        return ArbitrateAddress(nn::os::ARBITRATION_TYPE_DECREMENT_AND_WAIT_IF_LESS_THAN_WITH_TIMEOUT, value, timeout);
    }

    Result WaitIfLessThan(s32 value, fnd::TimeSpan timeout)
    {
        return ArbitrateAddress(nn::os::ARBITRATION_TYPE_WAIT_IF_LESS_THAN_WITH_TIMEOUT, value, timeout);
    }

    Result DecrementAndWaitIfLessThan(s32 value)
    {
        return ArbitrateAddress(nn::os::ARBITRATION_TYPE_DECREMENT_AND_WAIT_IF_LESS_THAN, value);
    }

    Result WaitIfLessThan(s32 value)
    {
        return ArbitrateAddress(nn::os::ARBITRATION_TYPE_WAIT_IF_LESS_THAN, value);
    }

    Result Signal(s32 num)
    {
        return ArbitrateAddress(nn::os::ARBITRATION_TYPE_SIGNAL, num);
    }

    Result SignalAll()
    {
        return Signal(-1);
    }

private:
    Result ArbitrateAddress(nn::os::ArbitrationType type, s32 value)
    {
        return nn::svc::ArbitrateAddress(s_Handle, reinterpret_cast<uptr>(&m_Value), type, value, 0);
    }
    Result ArbitrateAddress(nn::os::ArbitrationType type, s32 value, fnd::TimeSpan timeout)
    {
        return nn::svc::ArbitrateAddress(s_Handle, reinterpret_cast<uptr>(&m_Value), type, value, timeout.GetNanoSeconds());
    }
};


}} // namespace nn::os

#endif // __cplusplus

#endif
