/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_ReceiverImpl.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_ReceiverImpl.h"

#include <nn/rdt/CTR/rdt_define.h>
#include <nn/rdt/CTR/rdt_Result.h>


namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {


// Base class for "state."
class ReceiverStateBase{
public:
    virtual ~ReceiverStateBase(void){}

    virtual void initialize(ReceiverImpl *pReceiver); // Called when this state begins
    virtual void finalize  (ReceiverImpl *pReceiver); // Called when this state ends
    virtual void update    (ReceiverImpl *pReceiver);
    virtual enum ReceiverState getStatus(void) const = 0;

protected:
    ReceiverStateBase(void){}
};


void ReceiverStateBase::initialize(ReceiverImpl *pReceiver)
{
    (void)pReceiver;
}


void ReceiverStateBase::finalize(ReceiverImpl *pReceiver)
{
    (void)pReceiver;
}


void ReceiverStateBase::update(ReceiverImpl *pReceiver)
{
    (void)pReceiver;
}


class ReceiverStateWaiting : public ReceiverStateBase{
public:
    static ReceiverStateBase* getInstance(void);
    virtual void update(ReceiverImpl *pReceiver);
    virtual enum ReceiverState getStatus(void) const;

protected:
    ReceiverStateWaiting(void){}
};


class ReceiverStateOpened : public ReceiverStateBase{
public:
    static ReceiverStateBase* getInstance(void);
    virtual void update(ReceiverImpl *pReceiver);
    virtual enum ReceiverState getStatus(void) const;

protected:
    ReceiverStateOpened(void){}
};


class ReceiverStateWaitingFinished : public ReceiverStateBase{
public:
    static ReceiverStateBase* getInstance(void);
    virtual void update(ReceiverImpl *pReceiver);
    virtual enum ReceiverState getStatus(void) const;

protected:
    ReceiverStateWaitingFinished(void){}
};


class ReceiverStateFinished : public ReceiverStateBase{
public:
    static ReceiverStateBase* getInstance(void);
    virtual void update(ReceiverImpl *pReceiver);
    virtual enum ReceiverState getStatus(void) const;

protected:
    ReceiverStateFinished(void){}
};


class ReceiverStateClosed : public ReceiverStateBase{
public:
    static ReceiverStateBase* getInstance(void);
    virtual void initialize(ReceiverImpl *pReceiver);
    virtual void update    (ReceiverImpl *pReceiver);
    virtual enum ReceiverState getStatus(void) const;

protected:
    ReceiverStateClosed(void){}
};


// Below is the implementation of the derived class.

ReceiverStateBase* ReceiverStateWaiting::getInstance(void)
{
    static ReceiverStateWaiting s_instance;
    return &s_instance;
}


enum ReceiverState ReceiverStateWaiting::getStatus(void) const
{
    return RECEIVER_STATE_WAITING;
}


void ReceiverStateWaiting::update(ReceiverImpl *pReceiver)
{
    ASSERT(pReceiver!=NULL);

    //Process here if a segment is received.
    Segment seg;
    if(pReceiver->pullSegment(&seg).IsSuccess())
    {
        if(seg.IsRst())
        {
            // According to the TCP RFC, the received RST should be ignored during the LISTEN state.
            // Therefore, nothing is done here.
        }
        else if(seg.IsSyn())
        {
            // Return ACK if a the connection request from the remote is correct.

            // Set receive buffer
            pReceiver->m_recvBuf.SetInitialSequenceNumber(seg.GetSeqNumber());

            // Response to SYN.
            pReceiver->putSynAckSegment(seg.GetSeqNumber() + 1);
            pReceiver->setNextState(ReceiverStateOpened::getInstance());
        }
    }
}


ReceiverStateBase* ReceiverStateOpened::getInstance(void)
{
    static ReceiverStateOpened s_instance;
    return &s_instance;
}


enum ReceiverState ReceiverStateOpened::getStatus(void) const
{
    return RECEIVER_STATE_OPENED;
}


void ReceiverStateOpened::update(ReceiverImpl *pReceiver)
{
    ASSERT(pReceiver!=NULL);

    //Process here if a segment is received.
    Segment seg;
    if(pReceiver->pullSegment(&seg).IsSuccess())
    {
        // First, RST bit check
        if(seg.IsRst())
        {
            pReceiver->setNextState(ReceiverStateClosed::getInstance());
            pReceiver->errorHandling(ResultResetReceived());
            return;
        }

        // Has the segment of the anticipated sequence number arrived?
        ReceiveBuffer &rBuf = pReceiver->m_recvBuf;
        if(seg.GetSeqNumber()==rBuf.GetLatestSequenceNumber()+1)
        {
            if(seg.IsData())
            {
                bool result = rBuf.Push(seg.payload, seg.GetDataLength());
                if(result)
                {
                    // Data was stored in the receive buffer without any problems.
                    // Previous implementations returned ACKs, but this resulted in too many ACK packets from the receiver.
                    // So, we quit returning ACKs here.
                }
                else
                {
                    LOG("Received data segment, but could not return ACK because receive buffer did not have enough space.\n");
                }
            }
            else if(seg.IsFin())
            {
                // Send ACK for the FIN segment
                pReceiver->putFinAckSegment(seg.GetSeqNumber() + 1);
                pReceiver->setNextState(ReceiverStateWaitingFinished::getInstance());
            }
            else
            {
                seg.PrintDebugInfo();
                PANIC("It seems that SEQ number is valid, but unexpected segment.  It is not DATA, nor FIN.");
            }
        }
        else if(seg.GetSeqNumber()==rBuf.GetLatestSequenceNumber())
        {
            // If the response for Syn does not arrive, it could be that the Sender resent a Syn request.
            // Handling for that case.
            if(seg.IsSyn())
            {
                // Response to SYN.
                pReceiver->putSynAckSegment(seg.GetSeqNumber() + 1);
            }
        }

        else
        {
            VERBOSE("Unexpected SEQ number. (%d)\n", seg.GetSeqNumber());
            VERBOSE("SEQ number %d is expected.\n", rBuf.GetLatestSequenceNumber()+1);
            VERBOSE("Received segment will be ignored.\n");

#if 0
            // Since it was an unexpected segment, the possibility of a packet loss is suspect.
            // For now, quickly return ACK for the portion received up to this point.
            pReceiver->putAckSegment();

            // (above) If this code is used, it actually becomes slower. Probably because a large amount of ACK packets are issued ...
#endif
        }
    }
}


ReceiverStateBase* ReceiverStateWaitingFinished::getInstance(void)
{
    static ReceiverStateWaitingFinished s_instance;
    return &s_instance;
}


enum ReceiverState ReceiverStateWaitingFinished::getStatus(void) const
{
    return RECEIVER_STATE_WAITING_FINISHED;
}


void ReceiverStateWaitingFinished::update(ReceiverImpl *pReceiver)
{
    // Even if a ACK is returned for a FIN and Finished state is entered, it is not guaranteed that that ACK reached the recipient.
    // 
    // To determine if the ACK reached the recipient, you must confirm that no resent packets have been received from the other side after some time passes.
    // 

    ASSERT(pReceiver!=NULL);

    //Process here if a segment is received.
    Segment seg;
    if(pReceiver->pullSegment(&seg).IsSuccess())
    {
        // RST bit check
        if(seg.IsRst())
        {
            pReceiver->setNextState(ReceiverStateClosed::getInstance());
            pReceiver->errorHandling(ResultResetReceived());
            return;
        }

        // Has the FIN segment arrived?
        ReceiveBuffer &rBuf = pReceiver->m_recvBuf;
        if(seg.GetSeqNumber()==rBuf.GetLatestSequenceNumber()+1)
        {
            if(seg.IsFin())
            {
                pReceiver->putFinAckSegment(seg.GetSeqNumber() + 1);
            }
            else
            {
                seg.PrintDebugInfo();
                PANIC("Sequence number is valid, but FIN is not included.\n");
            }
        }
        else
        {
//            seg.PrintDebugInfo();
            LOG("Segment with unexpected sequence number.  Ignored.\n");
        }
    }

    // After determining a timeout, state transition.
    if(pReceiver->isSenderClosed())
    {
        pReceiver->setNextState(ReceiverStateFinished::getInstance());
    }
}


ReceiverStateBase* ReceiverStateFinished::getInstance(void)
{
    static ReceiverStateFinished s_instance;
    return &s_instance;
}


enum ReceiverState ReceiverStateFinished::getStatus(void) const
{
    return RECEIVER_STATE_FINISHED;
}


void ReceiverStateFinished::update(ReceiverImpl *pReceiver)
{
    ASSERT(pReceiver!=NULL);

    //Process here if a segment is received.
    Segment seg;
    if(pReceiver->pullSegment(&seg).IsSuccess())
    {
        // For segments without RST, should have sent RST.
        // However, since compatibility with past rdt may be lost, there is some concern for enbug via specification changes, so set to "do nothing" as previously.
        // 
        // However, replace PANIC() with LOG().
        LOG("State is FINISHED, but received segment from remote!\n");
    }
}



ReceiverStateBase* ReceiverStateClosed::getInstance(void)
{
    static ReceiverStateClosed s_instance;
    return &s_instance;
}


enum ReceiverState ReceiverStateClosed::getStatus(void) const
{
    return RECEIVER_STATE_CLOSED;
}


void ReceiverStateClosed::initialize(ReceiverImpl *pReceiver)
{
    ASSERT(pReceiver!=NULL);

    pReceiver->clear();
}


void ReceiverStateClosed::update(ReceiverImpl *pReceiver)
{
    ASSERT(pReceiver!=NULL);

    // Respond with RST to segments (without RST) received during CLOSED state
    Segment seg;
    if(pReceiver->pullSegment(&seg).IsSuccess() && !seg.IsRst())
    {
        LOG("Receiver is in CLOSED state, but received segment.  RST will be sent.\n");
        if(seg.IsAck())
        {
            pReceiver->sendRstSegment(seg.GetAckNumber());
        }
        else
        {
            const u32 SEQ = 0;
            const u32 ACK = seg.GetSeqNumber() + seg.GetSegmentLength();
            pReceiver->sendRstAckSegment(SEQ, ACK);
        }
    }
}



//
ReceiverImpl::ReceiverImpl(void) throw()
     :m_initialized(false)
{
}


//
ReceiverImpl::~ReceiverImpl(void)
{
    Finalize();
}


#ifdef _WIN32
nn::Result ReceiverImpl::Initialize(SOCKET sock, void *pRecvBuf, u16 recvBufSize)
#else
nn::Result ReceiverImpl::Initialize(u16 nodeId, u8 port, void *pRecvBuf, u16 recvBufSize)
#endif
{
    if(m_initialized)
    {
        return ResultAlreadyInitialized();
    }
    else
    {
        if(pRecvBuf==NULL)
        {
            return ResultNullPointer();
        }

        if(recvBufSize==0)
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
            m_pState     = ReceiverStateClosed::getInstance();
            m_pNextState = NULL;
            m_recvBuf.Initialize(pRecvBuf, recvBufSize);

            clear();

            m_initialized = true;
            return ResultSuccess();
        }
    }
}


void ReceiverImpl::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
        m_recvBuf.Finalize();
        HostBase::Finalize();
    }
    else
    {
        // Do nothing.
    }
}


nn::Result ReceiverImpl::Wait(void)
{
    ASSERT(m_initialized);

    if(GetStatus()==RECEIVER_STATE_CLOSED)
    {
        setNextState(ReceiverStateWaiting::getInstance());
        changeState();
        return ResultSuccess();
    }
    else
    {
        return ResultUntimelyFunctionCall();
    }
}


nn::Result ReceiverImpl::Close(void)
{
    ASSERT(m_initialized);

    if(GetStatus()==RECEIVER_STATE_FINISHED)
    {
        setNextState(ReceiverStateClosed::getInstance());
        changeState();
        return ResultSuccess();
    }
    else
    {
        return ResultUntimelyFunctionCall();
    }
}


nn::Result ReceiverImpl::Receive(void *pBuf, size_t *recvSize, size_t bufSize)
{
    ASSERT(m_initialized);

    if((pBuf==NULL) || (recvSize==NULL))
    {
        return ResultNullPointer();
    }

    if(bufSize==0)
    {
        return ResultDoNothing();
    }

    enum ReceiverState stat = GetStatus();
    if((stat!=RECEIVER_STATE_OPENED) && (stat!=RECEIVER_STATE_WAITING_FINISHED) && (stat!=RECEIVER_STATE_FINISHED))
    {
        return ResultUntimelyFunctionCall();
    }

    *recvSize = m_recvBuf.Read(pBuf, bufSize);
    if(*recvSize > 0)
    {
        m_recvBuf.Pop(*recvSize);
    }

    // Make Receive trigger, and notify the window remotely.
    // Since there is space in the receive window, send segment with the purpose of notifying remotely.
    // When trying to send a segment when the state is not OPENED, a state check is performed with an if statement because the connection may be disconnected.
    // 
    if(GetStatus()==RECEIVER_STATE_OPENED)
    {
        putAckSegment();
    }

    return ResultSuccess();
}


nn::Result ReceiverImpl::Process(void)
{
    ASSERT(m_initialized);

    // update() for each state.
    if(m_pState)
    {
        m_pState->update(this);
    }

    // State Transitions
    changeState();

    // Errors are returned here.
    // If returned, errors are reset.
    nn::Result ret = GetErrorCode();
    errorHandling(ResultSuccess());
    return ret;
}


enum ReceiverState ReceiverImpl::GetStatus(void) const
{
    ASSERT(m_initialized);
    ASSERTMSG(m_pState!=NULL, "It seems that state is not initialized.\n");

    return m_pState->getStatus();
}


void ReceiverImpl::Cancel(void)
{
    ASSERT(m_initialized);

    // Cancel processes are executed immediately without waiting for the Process() function.

    // RST transmission
    const u32 seq = 0;
    sendRstSegment(seq);

    // Immediately to Closed state.
    setNextState(ReceiverStateClosed::getInstance());
    changeState();
}


// State Transitions. Do nothing in particular if the next state is not set.
void ReceiverImpl::changeState(void)
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


void ReceiverImpl::setNextState(ReceiverStateBase *p)
{
    ASSERT(p!=NULL);
    ASSERT(m_pNextState==NULL);

    m_pNextState = p;
}


void ReceiverImpl::putSynAckSegment(u32 ack)
{
    Segment a;
    a.ClearHeader();
    a.SetAckNumber(ack);
    a.SetWindowSize(m_recvBuf.GetRestSize());
    putSegment(a);
}


void ReceiverImpl::putAckSegment(void)
{
    Segment a;
    a.ClearHeader();
    a.SetAckNumber(m_recvBuf.GetLatestSequenceNumber()+1);
    a.SetWindowSize(m_recvBuf.GetRestSize());
    putSegment(a);
}


void ReceiverImpl::putFinAckSegment(u32 ack)
{
    Segment a;
    a.ClearHeader();
    a.SetAckNumber(ack);
    a.SetWindowSize(m_recvBuf.GetRestSize());
    putSegment(a);

    m_finAckSentTime = GetCurrentTimeAsMillisecond();
}


bool ReceiverImpl::isSenderClosed(void) const
{
    ASSERT(m_finAckSentTime!=0);

//    LOG("m_finAckSentTime = %lld\n", m_finAckSentTime);
//    LOG("Current: %lld\n", GetCurrentTimeAsMillisecond());
    return GetCurrentTimeAsMillisecond() - m_finAckSentTime > FIN_TIMEOUT;
}


void ReceiverImpl::clear(void)
{
    m_recvBuf.Clear();
    m_finAckSentTime = 0;
}


void ReceiverImpl::PrintDebugInfo(void) const
{
    LOG("-- Receiver debug information --\n");
    LOG("Current state: %d\n", GetStatus());
    m_recvBuf.PrintDebugInfo();
    LOG("\n");
}

}}} // namespace nn::rdt::CTR
