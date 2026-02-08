/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Receiver.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"


#include <nn/rdt/CTR/rdt_Receiver.h>
#include <nn/rdt/CTR/rdt_Result.h>

#include "rdt_ReceiverImpl.h"
#include "rdt_Stopwatch.h"

namespace
{

}  // End of anonymous namespace


namespace nn { namespace rdt { namespace CTR {


Receiver::Receiver(void)
     :m_pImpl(NULL)
{
    ASSERT(RECEIVER_WORKBUF_SIZE >= sizeof(ReceiverImpl));
}


Receiver::~Receiver(void)
{
    Finalize();
}


nn::Result Receiver::Initialize(const struct ReceiverConfig &cfg)
{
    if(m_pImpl)
    {
        return ResultAlreadyInitialized();
    }
    else if(cfg.pWorkBuf==NULL)
    {
        return ResultNullPointer();
    }
    else if(reinterpret_cast<u32>(cfg.pWorkBuf) % 8 != 0)
    {
        return ResultMisalignedAddress();
    }
    else
    {
        ASSERT(RECEIVER_WORKBUF_SIZE >= sizeof(ReceiverImpl));

        std::memset(cfg.pWorkBuf, 0, RECEIVER_WORKBUF_SIZE);  // Zero clear, just in case.
        m_pImpl = new (cfg.pWorkBuf) ReceiverImpl();
#ifdef _WIN32
        nn::Result result = m_pImpl->Initialize(cfg.sock, cfg.pRecvBuf, cfg.recvBufSize);
#elif defined(NN_PLATFORM_CTR)
        nn::Result result = m_pImpl->Initialize(cfg.nodeId, cfg.port, cfg.pRecvBuf, cfg.recvBufSize);
#else
    #error no platform selected
#endif
        if(result.IsFailure())
        {
            m_pImpl->~ReceiverImpl();
            m_pImpl = NULL;
            return result;
        }
        else
        {
            return ResultSuccess();
        }
    }
}


void Receiver::Finalize(void)
{
    if(m_pImpl)
    {
        m_pImpl->~ReceiverImpl();
        m_pImpl = NULL;
    }
    else
    {
        // Do nothing.
    }
}


nn::Result Receiver::Wait(void)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    return m_pImpl->Wait();
}


nn::Result Receiver::Close(void)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    return m_pImpl->Close();
}


nn::Result Receiver::Receive(void *pBuf, size_t *pRecvSize, size_t bufSize)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    return m_pImpl->Receive(pBuf, pRecvSize, bufSize);
}


nn::Result Receiver::Process(void)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    static detail::Stopwatch s_sp("Receiver::Process()");

    s_sp.Start();
    nn::Result ret = m_pImpl->Process();
    s_sp.Stop();

    return ret;
}


void Receiver::Cancel(void)
{
    if(!m_pImpl)
    {
        LOG("Receiver is not initialized.  Ignored %s.\n", __FUNCTION__);
        return;
    }

    m_pImpl->Cancel();
}


enum ReceiverState Receiver::GetStatus(void) const
{
    if(!m_pImpl)
    {
        return RECEIVER_STATE_NOT_INITIALIZED;
    }

    return m_pImpl->GetStatus();
}


void Receiver::SetPacketLossRatio(int per)
{
    if(!m_pImpl)
    {
        LOG("Receiver is not initialized.  Ignored %s.\n", __FUNCTION__);
        return;
    }

    m_pImpl->SetPacketLossRatio(per);
}


void Receiver::PrintDebugInfo(void) const
{
    if(!m_pImpl)
    {
        LOG("Receiver is not initialized.  Ignored %s.\n", __FUNCTION__);
        return;
    }

    m_pImpl->PrintDebugInfo();

    detail::Stopwatch::PrintAll();
}


}}} // namespace nn::rdt::CTR
