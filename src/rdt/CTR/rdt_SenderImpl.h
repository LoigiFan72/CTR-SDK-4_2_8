/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_SenderImpl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_SENDERIMPL_H_
#define NN_RDT_SENDERIMPL_H_

#include "rdt_HostBase.h"
#include "rdt_SendBuffer.h"
#include "rdt_ResendQueue.h"
#include "rdt_Segment.h"

namespace nn { namespace rdt { namespace CTR {

// Forward declaration
class SenderStateBase;


/* Please see man pages for details 
    
*/
class SenderImpl : public HostBase{
public:
/* Please see man pages for details 
    
*/
    SenderImpl(void) throw();

/* Please see man pages for details 
    
*/
   virtual ~SenderImpl(void);

/* Please see man pages for details 
    
*/
#ifdef _WIN32
    nn::Result Initialize(SOCKET sock, void *pSendBuf, u16 sendBufSize);
#elif defined(NN_PLATFORM_CTR)
    nn::Result Initialize(u16 nodeId, u8 port, void *pSendBuf, u16 sendBufSize);
#endif

/* Please see man pages for details 
    
*/
    void Finalize(void);

/* Please see man pages for details 
    
           
           
*/
    nn::Result Open(void);

/* Please see man pages for details 
    
           
           
*/
    nn::Result Close(void);

/* Please see man pages for details 
    
    
    
    
    
*/
    nn::Result Send(const void *pBuf, size_t bufSize);

/* Please see man pages for details 
    
           
*/
    nn::Result Process(void);

/* Please see man pages for details 
    
*/
    void Cancel(void);

/* Please see man pages for details 
    
*/
    enum SenderState GetStatus(void) const;


/* Please see man pages for details 
    
*/
    static void* operator new(size_t size, void *pBuf) throw()
    {
        if(size!=sizeof(SenderImpl))
        {
            PANIC("Wrong size.\n");
            return NULL;
        }

        if(pBuf==NULL)
        {
            PANIC("NULL pointer is detected.\n");
            return NULL;
        }

        ALIGN_ASSERT(pBuf, 8);

        return pBuf;
    }

    // Although placement delete has been written, if it is called the same as delete(m_pImpl, m_workBuf), it seems that the global delete(void *p) is called for some reason.
    // 
    // Found some descriptions to reinforce the above explanation on the Web, so decided not to define the delete and leave it alone.
    // However, a Warning is given in the RealView compiler with this.
    // As a result, decided to at least define it. But do not call it.
    // If you use SenderImpl call the destructor explicitly.

    // C++ Labyringth (http://www.fides.dti.ne.jp/~oka-t/cpplab-placement-new-2.html)
    // If both are defined using "operator delete( void *p )", "operator delete( void *p )" is called. This is described in the C++ standards doc, but not very clearly. 
    // 
    // 
    //  Maybe compatibility with the old spec is being emphasized.

    static void  operator delete (void *p) throw()
    {
        PANIC("Do not call this delete!  Please call destructor manually.\n");
        (void)p;
    }


/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

/* Please see man pages for details 
    
*/
    static void PrintProperty(void);

/* Please see man pages for details 
    
*/
    static void Test(void);


private:
/* Please see man pages for details 
    
*/
    SenderImpl           (const SenderImpl&);

/* Please see man pages for details 
    
*/
    SenderImpl& operator=(const SenderImpl&);


    // Private Function Group.
    void changeState(void);                // Calling this function executes a state transition.
    void setNextState(SenderStateBase *p); // Set the next state.

    void putSegmentWithResend(const Segment &seg);

    // The received segment is passed to seg.
    // The shared processes for the received segment are collected in this function.
    // 
    void processReceivedSegment(const Segment &seg);

    // Executes the series of resend processes.
    // Returns true when the segment is resent.
    // Returns false when it is not resent.
    bool processResending(void);

    // Executes the cancel process.
    void processCanceling(void);

    // If the send buffer is full, the amount of data that can fit in one segment is removed and sent.
    // 
    void sendData(void);

    // Create and send segment including the SYN request.
    void sendSynSegment(void);

    // Create and send segment including the FIN request.
    // This function must be called with the send buffer in an empty condition.
    void sendFinSegment(void);

    // Is the send buffer empty?
    bool isSendBufferEmpty(void) const { return m_sendBuffer.IsEmpty(); }

    // Assumes that it is called when the system enters the Closed state.
    // Excluding members maintaining a state for the State pattern, each member variable is restored to a new state.
    // 
    void clear(void);

    // Gets ISS (initial sequence number).
    u32 getInitialSequenceNumber(void) const { return m_iss; }

    // Gets the oldest sequence number of the octet for which arrival is unconfirmed
    u32 getUnacknowledgeNumber(void) const { return m_una; }

    // Sequence number of the octet to send next
    u32 getNextSequenceNumber(void) const { return m_nxt; }

    // Is the ACK received from the remote site valid?
    bool isValidAckNumber(u32 ack) const;

    // Member variable group.
    SendBuffer    m_sendBuffer;       // Send buffer
    u16           m_remoteWindowSize; // Most recent information of the window size for which notification was made from the remote side.
    bool          m_initialized;
    u8            m_padding;          // Padding
    u32           m_iss;              // Initial sequence number
    u32           m_una;              // Oldest sequence number of the sequence numbers for which arrival is not confirmed
    u32           m_nxt;              // Sequence number of the octet that should be sent next
    ResendQueue   m_resendQueue;      // Resend queue (requires 8-byte alignment)

    // Applies State pattern.
    SenderStateBase *m_pState;
    SenderStateBase *m_pNextState;
    friend class SenderStateOpenRequested;
    friend class SenderStateOpening;
    friend class SenderStateOpened;
    friend class SenderStateCloseRequested;
    friend class SenderStateClosing;
    friend class SenderStateClosed;

    // Debug Variables
    u32           m_arrivals;    // Segment arrival count

    // Padding may be required here because the SenderImpl class is shifted by the ResendQueue alignment
    // 
    u8            m_padding2[4];
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_SENDERIMPL_H_
