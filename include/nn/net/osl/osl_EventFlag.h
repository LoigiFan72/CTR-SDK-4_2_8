/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     osl_EventFlag.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NET_OSL_OSL_EVENTFLAG_H_
#define NN_NET_OSL_OSL_EVENTFLAG_H_

#include <nn/fnd/fnd_Interlocked.h>
#include <nn/os/os_Event.h>
#include <nn/os/os_CriticalSection.h>

typedef enum
{
    NN_NET_OSL_WAITMODE_AND,
    NN_NET_OSL_WAITMODE_OR
} nnnetOslWaitMode;

#ifdef __cplusplus

namespace nn{ namespace net{ namespace osl{

class EventFlag
{
public:
    enum WaitMode
    {
        ModeAnd = NN_NET_OSL_WAITMODE_AND,
        ModeOr  = NN_NET_OSL_WAITMODE_OR
    };
    static const bit32  INITIAL_ALLOCATE    = 0x3;
    static const size_t MAX_FLAG_BITS       = 4;
    static const bit32  VALID_MASK          = (1 << MAX_FLAG_BITS) - 1;

    EventFlag()
        : m_validMap(0)
    {
    }

    ~EventFlag()
    {
        Finalize();
    }
    
    void Initialize(void);
    Result TryInitialize(void);
    void Finalize(void);

    void Signal(bit32 pattern);
    bit32 Wait(bit32 pattern, WaitMode mode, nn::fnd::TimeSpan timeout);
    bit32 Wait(bit32 pattern, WaitMode mode);

    bit32 WaitAndClear(bit32 pattern, WaitMode mode, bit32 clear, nn::fnd::TimeSpan timeout);
    bit32 WaitAndClear(bit32 pattern, WaitMode mode, bit32 clear);

    void ClearSignal(bit32 pattern);

protected:
    Result AllocateEvents(bit32 bitmap);
    void FreeEvents(bit32 bitmap);

    static inline fnd::TimeSpan InfiniteTimeSpan()
    {
        return fnd::TimeSpan::FromNanoSeconds(NN_OS_WAIT_INFINITE);
    }

private:
    nn::os::CriticalSection m_cs;
    nn::os::Event           m_events[MAX_FLAG_BITS];
    bit32                   m_validMap;
};

inline bit32 EventFlag::Wait(bit32 pattern, WaitMode mode)
{
    return Wait(pattern, mode, InfiniteTimeSpan());
}

inline bit32 EventFlag::WaitAndClear(bit32 pattern, WaitMode mode, bit32 clear)
{
    return WaitAndClear(pattern, mode, clear, InfiniteTimeSpan());
}

}}} // namesapce nn::net::osl

#endif // __cplusplus

// C declarations follow

#include <nn/util/detail/util_CLibImpl.h>

#define NN_NET_OSL_EVENTFLAG_SIZE                   (NN_OS_CRITICALSECTION_SIZE + (4 + 1) * 4)
#define NN_NET_OSL_EVENTFLAG_ALIGNMENT_HOLDER_TYPE  u32

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnnetOslEventFlag, nn::net::osl::EventFlag, NN_NET_OSL_EVENTFLAG_SIZE, NN_NET_OSL_EVENTFLAG_ALIGNMENT_HOLDER_TYPE);

NN_EXTERN_C void nnnetOslEventFlagInitialize(nnnetOslEventFlag* this_);
NN_EXTERN_C bool nnnetOslEventFlagTryInitialize(nnnetOslEventFlag* this_);
NN_EXTERN_C void nnnetOslEventFlagSignal(nnnetOslEventFlag* this_, bit32 pattern);
NN_EXTERN_C bit32 nnnetOslEventFlagWaitSignal(nnnetOslEventFlag* this_, bit32 pattern, nnnetOslWaitMode mode, s64 timeout);
NN_EXTERN_C void nnnetOslEventFlagClearSignal(nnnetOslEventFlag* this_, bit32 pattern);
NN_EXTERN_C bit32 nnnetOslEventFlagWaitAndClear(nnnetOslEventFlag* this_, bit32 pattern, nnnetOslWaitMode mode, bit32 clear, s64 timeout);
NN_EXTERN_C void nnnetOslEventFlagFinalize(nnnetOslEventFlag* this_);

#endif // NN_NET_OSL_OSL_EVENTFLAG_H_
