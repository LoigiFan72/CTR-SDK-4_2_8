/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_SenderImpl.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_SenderImpl.h"

#include <nn/rdt/CTR/rdt_define.h>
#include <nn/rdt/CTR/rdt_Result.h>

#include "rdt_Stopwatch.h"

#include "Test.h"


namespace
{

}  // End of anonymous namespace


namespace nn { namespace rdt { namespace CTR {


// Base class for "State"
class SenderStateBase{
public:
    virtual ~SenderStateBase(void){}

    virtual void initialize(SenderImpl *pSender); // Called when this state is started
    virtual void finalize  (SenderImpl *pSender); // Called when this state is finished
    void update    (SenderImpl *pSender);
    virtual void updatePrologue   (SenderImpl *pSender);
    virtual void updateCore       (SenderImpl *pSender);
    virtual void updateEpilogue   (SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const = 0;

protected:
    SenderStateBase(void){}
};


void SenderStateBase::initialize(SenderImpl *pSender)
{
    (void)pSender;
}


void SenderStateBase::finalize(SenderImpl *pSender)
{
    (void)pSender;
}


void SenderStateBase::updatePrologue(SenderImpl *pSender)
{
    (void)pSender;
}


void SenderStateBase::updateCore(SenderImpl *pSender)
{
    (void)pSender;
}


void SenderStateBase::updateEpilogue(SenderImpl *pSender)
{
    (void)pSender;
}


void SenderStateBase::update(SenderImpl *pSender)
{
    updatePrologue(pSender);
    updateCore(pSender);
    updateEpilogue(pSender);
}


class SenderStateOpenRequested : public SenderStateBase{
public:
    static SenderStateBase* getInstance(void);

    virtual void updateCore(SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const;

protected:
    SenderStateOpenRequested(void){}
};


class SenderStateOpening : public SenderStateBase{
public:
    static SenderStateBase* getInstance(void);

    virtual void updateCore(SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const;

protected:
    SenderStateOpening(void){}
};


class SenderStateOpened : public SenderStateBase{
public:
    static SenderStateBase* getInstance(void);

    virtual void updateCore(SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const;

protected:
    SenderStateOpened(void){}
};


class SenderStateCloseRequested : public SenderStateBase{
public:
    static SenderStateBase* getInstance(void);

    virtual void updateCore(SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const;

protected:
    SenderStateCloseRequested(void){}
};


class SenderStateClosing : public SenderStateBase{
public:
    static SenderStateBase* getInstance(void);

    virtual void updateCore(SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const;

protected:
    SenderStateClosing(void){}
};


class SenderStateClosed : public SenderStateBase{
public:
    static SenderStateBase* getInstance(void);

    virtual void initialize(SenderImpl *pSender);
    virtual void updateCore(SenderImpl *pSender);
    virtual enum SenderState getStatus(void) const;

protected:
    SenderStateClosed(void){}
};


// The following is an implementation of State inherited class.
SenderStateBase* SenderStateClosed::getInstance(void)
{
    static SenderStateClosed s_instance;
    return &s_instance;
}


enum SenderState SenderStateClosed::getStatus(void) const
{
    return SENDER_STATE_CLOSED;
}


void SenderStateClosed::initialize(SenderImpl *pSender)
{
    ASSERT(pSender!=NULL);

    pSender->clear();
}


void SenderStateClosed::updateCore(SenderImpl *pSender)
{
    ASSERT(pSender!=NULL);

    // For segments (not including RST) received while in CLOSED state, respond with RST
    Segment seg;
    if(pSender->pullSegment(&seg).IsSuccess() && !seg.IsRst())
    {
#if 0
        LOG("The Sender is in CLOSED state, but respond with RST since the segment was received. \n");
        LOG("The received segment contains \n.");
        seg.PrintDebugInfo();
        LOG("   \n");
        const u32 SEQ = 0;
        pSender->sendRstSegment(SEQ);
#else
        LOG("Sender is in CLOSED state, but received segment.  Ignored.\n");
#endif
    }
}


SenderStateBase* SenderStateOpenRequested::getInstance(void)
{
    static SenderStateOpenRequested s_instance;
    return &s_instance;
}


enum SenderState SenderStateOpenRequested::getStatus(void) const
{
    return SENDER_STATE_OPEN_REQUESTED;
}


void SenderStateOpenRequested::updateCore(SenderImpl *pSender)
{
    // Send connection request segment
    pSender->sendSynSegment();

    // To next state.
    pSender->setNextState(SenderStateOpening::getInstance());
}


SenderStateBase* SenderStateOpening::getInstance(void)
{
    static SenderStateOpening s_instance;
    return &s_instance;
}


enum SenderState SenderStateOpening::getStatus(void) const
{
    return SENDER_STATE_OPENING;
}


void SenderStateOpening::updateCore(SenderImpl *pSender)
{
    ASSERT(pSender!=NULL);

    // Check content of received segment.
    Segment seg;
    if(pSender->pullSegment(&seg).IsSuccess())
    {
        pSender->processReceivedSegment(seg);

        if(seg.IsRst())
        {
            // Check if the RST is for this SYN. If not, discard segment.
            if(seg.IsAck() && seg.GetAckNumber()==pSender->getInitialSequenceNumber()+1)
            {
                // Treated as SYN is denied. To CLOSED.
                LOG("SYN rejected.  CLOSED... ack of segment = %u\n", seg.GetAckNumber());
                pSender->setNextState(SenderStateClosed::getInstance());
                pSender->errorHandling(ResultResetReceived());
                return;
            }
            else
            {
                LOG("Ignored RST segment.\n");
            }
        }
        else if(seg.IsAck())
        {
            if(seg.GetAckNumber()==pSender->getInitialSequenceNumber()+1)
            {
                // Since ACK for SYN is returned, transition to next state.
                pSender->setNextState(SenderStateOpened::getInstance());
            }
            else
            {
                LOG("ack : %u\n", seg.GetAckNumber());
                LOG("una : %u\n", pSender->getUnacknowledgeNumber());
                LOG("nxt : %u\n", pSender->getNextSequenceNumber());
                LOG("It seems that it isn't ACK for SYN.  Ignored\n");
            }
        }
    }

    // Resend process.
    pSender->processResending();
}


SenderStateBase* SenderStateOpened::getInstance(void)
{
    static SenderStateOpened s_instance;
    return &s_instance;
}


enum SenderState SenderStateOpened::getStatus(void) const
{
    return SENDER_STATE_OPENED;
}


void SenderStateOpened::updateCore(SenderImpl *pSender)
{
    ASSERT(pSender!=NULL);

    // Check content of received segment.
    Segment seg;
    if(pSender->pullSegment(&seg).IsSuccess())
    {
        pSender->processReceivedSegment(seg);

        if(seg.IsRst())
        {
            // Since it was RST, to CLOSED.
            pSender->setNextState(SenderStateClosed::getInstance());
            pSender->errorHandling(ResultResetReceived());
            return;
        }
    }

    bool bSent = false;  // Set to true if the send process was executed.

    // Resend process.
    bSent = pSender->processResending();

    // If no send process has occurred, try to send data.
    if(!bSent)
    {
        if(!pSender->isSendBufferEmpty())
        {
            pSender->sendData();
            bSent = true;
        }
    }
}


SenderStateBase* SenderStateCloseRequested::getInstance(void)
{
    static SenderStateCloseRequested s_instance;
    return &s_instance;
}


enum SenderState SenderStateCloseRequested::getStatus(void) const
{
    return SENDER_STATE_CLOSE_REQUESTED;
}


void SenderStateCloseRequested::updateCore(SenderImpl *pSender)
{
    ASSERT(pSender!=NULL);

    // Check content of received segment. This is the same as the Opened state.
    Segment seg;
    if(pSender->pullSegment(&seg).IsSuccess())
    {
        pSender->processReceivedSegment(seg);

        if(seg.IsRst())
        {
            // Since it was RST, to CLOSED.
            pSender->setNextState(SenderStateClosed::getInstance());
            pSender->errorHandling(ResultResetReceived());
            return;
        }
    }

    bool bSent = false;  // Set to true if the send process was executed.

    // Resend process.
    bSent = pSender->processResending();

    if(pSender->isSendBufferEmpty())
    {
        // Send FIN segment
        if(!bSent)
        {
            pSender->sendFinSegment();
            bSent = true;

            // To CLOSING state.
            pSender->setNextState(SenderStateClosing::getInstance());
        }
    }
    else
    {
        // Clean out send buffer data
        if(!bSent)
        {
            pSender->sendData();
            bSent = true;
        }
    }

    // If no send process has occurred, try to send data.
    if(!bSent)
    {
        if(!pSender->isSendBufferEmpty())
        {
            pSender->sendData();
            bSent = true;
        }
    }
}


SenderStateBase* SenderStateClosing::getInstance(void)
{
    static SenderStateClosing s_instance;
    return &s_instance;
}


enum SenderState SenderStateClosing::getStatus(void) const
{
    return SENDER_STATE_CLOSING;
}


void SenderStateClosing::updateCore(SenderImpl *pSender)
{
    ASSERT(pSender!=NULL);

    // Resend process.
    pSender->processResending();

    // Check content of received segment.
    Segment seg;
    if(pSender->pullSegment(&seg).IsSuccess())
    {
        pSender->processReceivedSegment(seg);

        if(seg.IsRst())
        {
            // Since it was RST, to CLOSED.
            pSender->setNextState(SenderStateClosed::getInstance());
            pSender->errorHandling(ResultResetReceived());
            return;
        }
        else if(seg.IsAck() && seg.GetAckNumber()==pSender->m_sendBuffer.GetCurrentSequenceNumber()+1)
        {
            // Check content of received segment. (FIN check)
            // Since an ACK for FIN was returned, to CLOSED.
            pSender->setNextState(SenderStateClosed::getInstance());
        }
        else
        {
            VERBOSE("Although a segment was received, it does not seem to be an ACK segment to FIN. Destroy. \n");
        }
    }
}



//
SenderImpl::SenderImpl(void) throw()
     :m_initialized(false)
{
}


//
SenderImpl::~SenderImpl(void)
{
    Finalize();
}


#ifdef _WIN32
nn::Result SenderImpl::Initialize(SOCKET sock, void *pSendBuf, u16 sendBufSize)
#else
nn::Result SenderImpl::Initialize(u16 nodeId, u8 port, void *pSendBuf, u16 sendBufSize)
#endif
{
    if(m_initialized)
    {
        return ResultAlreadyInitialized();
    }
    else
    {
        if(pSendBuf==NULL)
        {
            return ResultNullPointer();
        }

        if(sendBufSize==0)
        {
            return ResultInvalidSize();
        }

#ifdef _WIN32
        nn::Result result = HostBase::Initialize(sock);
#elif defined(NN_PLATFORM_CTR)
        nn::Result result = HostBase::Initialize(nodeId, port);
#endif
        if(result.IsFailure())
        {
            return result;
        }
        else
        {
            m_sendBuffer.Initialize(pSendBuf, sendBufSize);
            m_pState     = SenderStateClosed::getInstance();
            m_pNextState = NULL;

            clear();

            m_initialized = true;
            return ResultSuccess();
        }
    }
}


void SenderImpl::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
        m_sendBuffer.Finalize();
        HostBase::Finalize();
    }
    else
    {
        // Do nothing.
    }
}


nn::Result SenderImpl::Process(void)
{
    ASSERT(m_initialized);

    // update() for each state
    if(m_pState)
    {
        m_pState->update(this);
    }

    // State Transitions
    changeState();

    // For debugging
    //    PrintDebugInfo();

    // Error returned here.
    // If returned, reset error.
    nn::Result ret = GetErrorCode();
    errorHandling(ResultSuccess());
    return ret;
}


nn::Result SenderImpl::Open(void)
{
    ASSERT(m_initialized);

    if(GetStatus()==SENDER_STATE_CLOSED)
    {
        setNextState(SenderStateOpenRequested::getInstance());
        changeState();
        return ResultSuccess();
    }
    else
    {
        return ResultUntimelyFunctionCall();
    }
}


nn::Result SenderImpl::Close(void)
{
    ASSERT(m_initialized);

    if(GetStatus()==SENDER_STATE_OPENED)
    {
        setNextState(SenderStateCloseRequested::getInstance());
        changeState();
        return ResultSuccess();
    }
    else
    {
        // If Close() is called while in a CLOSED state, error occurs.
        // This behavior follows the RFC for TCP, and this behavior is also included here.
        return ResultUntimelyFunctionCall();
    }
}


nn::Result SenderImpl::Send(const void *pBuf, size_t bufSize)
{
    ASSERT(m_initialized);

    if(pBuf==NULL)
    {
        return ResultNullPointer();
    }

    if(bufSize==0)
    {
        return ResultDoNothing();
    }

    if(GetStatus()!=SENDER_STATE_OPENED)
    {
        return ResultUntimelyFunctionCall();
    }

    if(m_sendBuffer.Push(pBuf, bufSize))
    {
        return ResultSuccess();
    }
    else
    {
        return ResultSendBufferIsNotAvailable();
    }
}


void SenderImpl::Cancel(void)
{
    ASSERT(m_initialized);

    // The cancel process executes immediately without waiting for Process().
    // While writing a sample program implementing error handling, I thought it might be easier to use this on the application side.
    // 

    // RST transmission
    sendRstSegment(m_sendBuffer.GetCurrentSequenceNumber());

    // To Closed state immediately.
    setNextState(SenderStateClosed::getInstance());
    changeState();
}


enum SenderState SenderImpl::GetStatus(void) const
{
    ASSERT(m_initialized);
    ASSERT(m_pState!=NULL);

    return m_pState->getStatus();
}


bool SenderImpl::processResending(void)
{
    Segment seg;
    // A segment in the queue either timed out or is waiting for the remaining segments to finish transmission.
    // 
    // 
    if(m_resendQueue.IsResendMode())
    {
        bool ret = m_resendQueue.Front(&seg);
        ASSERT(ret);
        VERBOSE("Execute the new send or resend process. \n");
        VERBOSE("The send segment sequence number is: %d. \n", seg.GetSeqNumber());
        putSegment(seg);

        static detail::Stopwatch s_sp("ResendQueue::TryAgain()");
        s_sp.Start();
        m_resendQueue.TryAgain();  // Elements at the start of the queue are sent to the very end
        s_sp.Stop();
        return true;
    }
    else
    {
        return false;
    }
}


void SenderImpl::sendData(void)
{
    if(m_sendBuffer.IsEmpty())
    {
        VERBOSE("Since the send buffer was empty, no send process is performed. \n");
        return;
    }

    u32 unackDataSize = m_resendQueue.GetTotalDataSize();
    if(unackDataSize >= m_remoteWindowSize)
    {
        VERBOSE("Since the arrival for the data is not confirmed and the data size is larger than the receive window size, transmission is put off. \n");
        return;
    }

    if(m_resendQueue.IsFull())
    {
        VERBOSE("Since the resend queue is full, no send process is performed. \n");
        return;
    }

    size_t vacant = m_remoteWindowSize - unackDataSize;
    size_t pullSize = min(Segment::PAYLOAD_SIZE, vacant);  // Amount pulled from the send buffer
    ASSERT(pullSize > 0);

    // The following is the data send process
    Segment seg;
    seg.ClearHeader();
    u32 seq = 0;

    // Executes process to pack segments with data.
    size_t sz = m_sendBuffer.Pull(seg.payload, &seq, pullSize);
    ASSERT(sz > 0);

    // Before arriving at this point, be sure to guarantee that the resend process and other processes have been reliably performed (that there is room in the resend queue).
    // 
    seg.header.dataLength = sz;
    seg.SetSeqNumber(seq);
    putSegmentWithResend(seg);
}


void SenderImpl::sendSynSegment(void)
{
    Segment seg;
    seg.ClearHeader();
    seg.SetSeqNumber(getInitialSequenceNumber());
    seg.SetSyn();
    putSegmentWithResend(seg);
}


void SenderImpl::sendFinSegment(void)
{
    ASSERTMSG(m_sendBuffer.IsEmpty(), "You cannot request FIN if send buffer is not empty.");

    VERBOSE("sendFinSegment() called.\n");

    Segment seg;
    seg.ClearHeader();
    seg.SetFin();
    seg.SetSeqNumber(m_sendBuffer.GetCurrentSequenceNumber());
    putSegmentWithResend(seg);
}


void SenderImpl::clear(void)
{
    m_resendQueue.Clear();
    m_remoteWindowSize = 0;
#if 1
    m_iss = static_cast<u32>(0xffffffff & GetCurrentTimeAsMillisecond());
#else
    m_iss = 0xffffffff - 100;
#endif
    m_sendBuffer.Clear(m_iss);
    m_una = m_iss;
    m_nxt = m_iss;

    m_arrivals = 0;
}


bool SenderImpl::isValidAckNumber(u32 ack) const
{
    s32 s32_ack = static_cast<s32>(ack);
    s32 s32_una = static_cast<s32>(getUnacknowledgeNumber());
    s32 s32_nxt = static_cast<s32>(getNextSequenceNumber());

    // Express the acceptable ACK inequalities: snd.una < seg.ack <= snd.nxt.
    if((0 <= s32_una - s32_ack) || (0 < s32_ack - s32_nxt))
    {
        return false;
    }
    else
    {
        return true;
    }
}



// State Transitions. Do nothing specific if the next state is not set.
void SenderImpl::changeState(void)
{
    if(m_pNextState)
    {
        if(m_pState)
        {
            m_pState->finalize(this);
        }
        m_pState = m_pNextState;
        m_pNextState = NULL;
        m_pState->initialize(this);
    }
}


void SenderImpl::setNextState(SenderStateBase *p)
{
    ASSERT(p!=NULL);
    ASSERT(m_pNextState==NULL);

    m_pNextState = p;
}


void SenderImpl::putSegmentWithResend(const Segment &seg)
{
    // If the resend queue is full, reliable communications cannot be implemented.
    ASSERT(!m_resendQueue.IsFull());

    putSegment(seg);

    // All segments depend on being the target for resending.
    // Excluding the SYN segment from the resend target could cause problems. 
    // 
    m_nxt = seg.GetLastSeqNumber() + 1;

    // Add segments in the resend queue.
    // Basically, if the sending side cannot confirm "arrival," it must be resent.
    // Will not have the receiving side worry whether the response arrived to the other party.
    // Expects that the other party will report if nothing arrives.
    bool ret = m_resendQueue.Push(seg);
    if(!ret)
    {
        errorHandling(ResultResendQueueIsFull());
        PANIC("It seems that resend queue in RDT library is full.");
    }
}


void SenderImpl::processReceivedSegment(const Segment &seg)
{
    // All processing that must happen when a segment arrives should be performed here. 
    // 

    ++m_arrivals;

    // ACK field check
    if(seg.IsAck())
    {
        const u32 ack = seg.GetAckNumber();
        if(isValidAckNumber(ack))
        {
            m_una = ack;

            // Packets for which delivery has been confirmed can be removed from the resend queue.
            VERBOSE("Received ACK number %d. \n", ack);
            m_resendQueue.Remove(ack);

            // Update window size
            m_remoteWindowSize = seg.GetWindowSize();
        }
        else
        {
            VERBOSE("una : %d\n", getUnacknowledgeNumber());
            VERBOSE("nxt : %d\n", getNextSequenceNumber());
            VERBOSE("Invalid ACK number or ACK number that has already been received. (%u)\n", ack);
        }
    }
}


void SenderImpl::PrintDebugInfo(void) const
{
    ASSERT(m_initialized);

    m_resendQueue.PrintDebugInfo();
    m_sendBuffer.PrintDebugInfo();
    LOG("m_remoteWindowSize: %d\n", m_remoteWindowSize);
    LOG("m_arrivals: %u\n", m_arrivals);
}


void SenderImpl::PrintProperty(void)
{
    LOG("m_sendBuffer: %d (%d)\n",       offsetof(SenderImpl, m_sendBuffer), sizeof(SendBuffer));
    LOG("m_remoteWindowSize: %d (%d)\n", offsetof(SenderImpl, m_remoteWindowSize), sizeof(u16));
    LOG("m_resendQueue: %d (%d)\n",      offsetof(SenderImpl, m_resendQueue), sizeof(ResendQueue));
    LOG("m_pState: %d (%d)\n",           offsetof(SenderImpl, m_pState), sizeof(SenderStateBase*));
    LOG("m_pNextState: %d (%d)\n",       offsetof(SenderImpl, m_pNextState), sizeof(SenderStateBase*));
    LOG("m_arrivals: %d (%d)\n",         offsetof(SenderImpl, m_arrivals), sizeof(u32));

    LOG("sizeof(SenderImpl)=%ld\n", (long) sizeof(SenderImpl));
}


// We want to create a single unit test that can execute without Receiver. This is not ready yet. 
// 
void SenderImpl::Test(void)
{
    /*
    const int BUFSIZE = 1024;
    char buf[BUFSIZE];
    SenderImpl s;
    const int SUCCESS = 0;
    CU_ASSERT(s.GetStatus()==SENDER_STATE_CLOSED);
    CU_ASSERT(s.Open()==SUCCESS);
    for(int i=0; i10; ++i)
    {
        CU_ASSERT(s.Process()==SUCCESS);
        CU_ASSERT(s.GetStatus()==SENDER_STATE_OPENING);
        SleepCurrentThread(50);
    }
    CU_ASSERT(s.Cancel()==SUCCESS);
    while(1)
    {
        CU_ASSERT(s.Process()==SUCCESS);
        CU_ASSERT(s.GetStatus()==SENDER_STATE_CLOSED);
        SleepCurrentThread(50);
    }
     



*/
}


}}} // namespace nn::rdt::CTR
