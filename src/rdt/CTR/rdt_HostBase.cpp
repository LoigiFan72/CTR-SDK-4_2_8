/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_HostBase.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_HostBase.h"

#include "rdt_Utility.h"

#include <cstdlib>  // For rand function.

#include <nn/rdt/CTR/rdt_Result.h>


namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {


HostBase::HostBase(void)
     :m_initialized(false)
{
}


//
HostBase::~HostBase(void)
{
    Finalize();
}


nn::Result HostBase::Initialize(
#ifdef _WIN32
    SOCKET &sock
#elif defined(NN_PLATFORM_CTR)
    u16 nodeId,
    u8 port
#endif
    )
{
    if(m_initialized)
    {
        return ResultAlreadyInitialized();
    }
    else
    {
        nn::Result result = m_transceiver.Initialize(
#ifdef _WIN32
            sock
#elif defined(NN_PLATFORM_CTR)
            nodeId,
            port
#endif
            );

        if(result.IsFailure())
        {
            return result;
        }
        else
        {
            m_packetLossRatio = 0;
            m_resultCode      = ResultSuccess();
            m_initialized     = true;
            return ResultSuccess();
        }
    }
}


void HostBase::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
        m_transceiver.Finalize();
    }
    else
    {
        // Do nothing.
    }
}


void HostBase::SetPacketLossRatio(int per)
{
    ASSERT(m_initialized);
    ASSERT((0<=per) && (per<=100));

    m_packetLossRatio = per;
}


void HostBase::PrintProperty(void)
{
    LOG("m_transceiver: %d (%d)\n",     offsetof(HostBase, m_transceiver), sizeof(Transceiver));
    LOG("m_packetLossRatio: %d (%d)\n", offsetof(HostBase, m_packetLossRatio), sizeof(int));
    LOG("m_resultCode: %d (%d)\n",      offsetof(HostBase, m_resultCode), sizeof(Result));

    LOG("sizeof(HostBase)=%ld\n", (long) sizeof(HostBase));
}


void HostBase::putSegment(const Segment &seg)
{
    // Perform packet loss emulation here.
    // When there are no packet loss settings, the following was written because we did not want high-cost residue calculations performed.
    // 
    // Be aware that unless the srand function is executed properly in advance, the values obtained the with rand function would be all 0.
    int r = (m_packetLossRatio==0) ? 100 : std::rand()%100;

    if(r >= m_packetLossRatio)
    {
        nn::Result result = m_transceiver.Put(seg);
        if(result.IsFailure())
        {
            errorHandling(result);
        }
#if 0
        LOG("Sent segment is:\n");
        seg.PrintDebugInfo();
#endif
    }
    else
    {
        LOG("Packet loss happened!  Lost segment is:\n");
        seg.PrintDebugInfo();
    }
}


nn::Result HostBase::pullSegment(Segment *pSeg)
{
    ASSERT(pSeg!=NULL);

    nn::Result result = m_transceiver.Pull(pSeg);
    if(result.IsFailure() && result!=ResultNoData())
    {
        errorHandling(result);
    }
    return result;
}


void HostBase::sendRstSegment(u32 seq)
{
    VERBOSE("%s called.\n", __FUNCTION__);

    Segment seg;
    seg.ClearHeader();
    seg.SetRst();
    seg.SetSeqNumber(seq);
    putSegment(seg);
}


void HostBase::sendRstAckSegment(u32 seq, u32 ack)
{
    VERBOSE("%s called.\n", __FUNCTION__);

    Segment seg;
    seg.ClearHeader();
    seg.SetRst();
    seg.SetSeqNumber(seq);
    seg.SetAckNumber(ack);
    putSegment(seg);
}


void HostBase::errorHandling(Result resultCode)
{
    if(resultCode.IsFailure())
    {
        LOG("Failure result code will be set...\n");
    }

    m_resultCode = resultCode;
}


}}} // namespace nn::rdt::CTR
