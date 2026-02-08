/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Sender.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include <nn/rdt/CTR/rdt_Sender.h>
#include <nn/rdt/CTR/rdt_Result.h>

#include "rdt_SenderImpl.h"
#include "rdt_Stopwatch.h"


namespace
{
}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {


Sender::Sender(void)
     :m_pImpl(NULL)
{
}


Sender::~Sender(void)
{
    Finalize();
}


nn::Result Sender::Initialize(const struct SenderConfig &cfg)
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
        ASSERT(SENDER_WORKBUF_SIZE >= sizeof(SenderImpl));

        std::memset(cfg.pWorkBuf, 0, SENDER_WORKBUF_SIZE);  // For now, zero clear.
        m_pImpl = new (cfg.pWorkBuf) SenderImpl();
#ifdef _WIN32
        nn::Result result = m_pImpl->Initialize(cfg.sock, cfg.pSendBuf, cfg.sendBufSize);
#elif defined(NN_PLATFORM_CTR)
        nn::Result result = m_pImpl->Initialize(cfg.nodeId, cfg.port, cfg.pSendBuf, cfg.sendBufSize);
#else
    #error no platform selected
#endif
        if(result.IsFailure())
        {
            m_pImpl->~SenderImpl();
            m_pImpl = NULL;
            return result;
        }
        else
        {
            return ResultSuccess();
        }
    }
}


void Sender::Finalize(void)
{
    if(m_pImpl)
    {
        m_pImpl->~SenderImpl();
        m_pImpl = NULL;
    }
    else
    {
        // Do nothing.
    }
}


nn::Result Sender::Open(void)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    return m_pImpl->Open();
}


nn::Result Sender::Close(void)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    return m_pImpl->Close();
}


nn::Result Sender::Send(const void *pBuf, size_t bufSize)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    return m_pImpl->Send(pBuf, bufSize);
}


nn::Result Sender::Process(void)
{
    if(!m_pImpl)
    {
        return ResultNotInitialized();
    }

    static detail::Stopwatch s_sp("Sender::Process()");

    s_sp.Start();
    nn::Result ret = m_pImpl->Process();
    s_sp.Stop();

    return ret;
}


void Sender::Cancel(void)
{
    if(!m_pImpl)
    {
        LOG("Sender is not initialized.  Ignored %s.\n", __FUNCTION__);
        return;
    }

    m_pImpl->Cancel();
}


enum SenderState Sender::GetStatus(void) const
{
    if(!m_pImpl)
    {
        return SENDER_STATE_NOT_INITIALIZED;
    }

    return m_pImpl->GetStatus();
}


void Sender::SetPacketLossRatio(int per)
{
    if(!m_pImpl)
    {
        LOG("Sender is not initialized.  Ignored %s.\n", __FUNCTION__);
        return;
    }

    return m_pImpl->SetPacketLossRatio(per);
}


void Sender::PrintDebugInfo(void) const
{
    if(!m_pImpl)
    {
        LOG("Sender is not initialized.  Ignored %s.\n", __FUNCTION__);
        return;
    }

    m_pImpl->PrintDebugInfo();

    detail::Stopwatch::PrintAll();
}


}}} // namespace nn::rdt::CTR
