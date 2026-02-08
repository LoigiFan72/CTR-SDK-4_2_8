/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_ReceiverImpl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_RECEIVERIMPL_H_
#define NN_RDT_RECEIVERIMPL_H_

#include "rdt_HostBase.h"
#include "rdt_ReceiveBuffer.h"
#include "rdt_Segment.h"


namespace nn { namespace rdt { namespace CTR {

// Forward declaration
class ReceiverStateBase;

/* Please see man pages for details 
    
*/
class ReceiverImpl : public HostBase{
public:
/* Please see man pages for details 
    
*/
    ReceiverImpl(void) throw();

/* Please see man pages for details 
    
*/
    virtual ~ReceiverImpl(void);

/* Please see man pages for details 
    
*/
#ifdef _WIN32
    nn::Result Initialize(SOCKET sock, void *pRecvBuf, u16 recvBufSize);
#elif defined(NN_PLATFORM_CTR)
    nn::Result Initialize(u16 nodeId, u8 port, void *pRecvBuf, u16 recvBufSize);
#endif

/* Please see man pages for details 
    
*/
    void Finalize(void);

/* Please see man pages for details 
    
*/
    nn::Result Wait(void);

/* Please see man pages for details 
    
           
*/
    nn::Result Close(void);

/* Please see man pages for details 
    
    
    
*/
    nn::Result Receive(void *pBuf, size_t *recvSize, size_t bufSize);

/* Please see man pages for details 
    
           
           
*/
    nn::Result Process(void);

/* Please see man pages for details 
    
*/
    void Cancel(void);

/* Please see man pages for details 
    
*/
    enum ReceiverState GetStatus(void) const;

/* Please see man pages for details 
    
*/
    static void* operator new(size_t size, void *pBuf) throw()
    {
        if(size!=sizeof(ReceiverImpl))
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

    static void  operator delete (void *p) throw()
    {
        PANIC("Do not call this delete!  Please call destructor manually.\n");
        (void)p;
    }


/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

private:
/* Please see man pages for details 
    
*/
    ReceiverImpl           (const ReceiverImpl&);

/* Please see man pages for details 
    
*/
    ReceiverImpl& operator=(const ReceiverImpl&);

    // Constants
    static const MSEC_T FIN_TIMEOUT = 1000;  // Parameter that needs to be adjusted with a CTR device.

    // Private Function Group.
    void changeState(void);          // Calling this function executes a state transition.
    void setNextState(ReceiverStateBase *p); // Set the next state.

    // Called when creating a response to SYN.
    void putSynAckSegment(u32 ack);

    // Called when creating an ACK segment.
    void putAckSegment(void);

    // Called when sending an ACK segment for FIN.
    // At this time, the ACK send time is also recorded.
    void putFinAckSegment(u32 ack);

    // After a sufficient amount of time passes from sending an ACK for FIN, can be confident that the other party has closed? 
    // 
    bool isSenderClosed(void) const;

    // Is the receive buffer empty?
    bool isReceiveBufferEmpty(void) const { return m_recvBuf.IsEmpty(); }

    // Assumes that it is called when the system enters the Closed state.
    // Excluding members maintaining a state for the State pattern, each member variable is restored to a new state.
    // 
    void clear(void);

    // Member variable group.
    ReceiveBuffer m_recvBuf;    // Receive buffer. Stores here the actual data from the Sender.
    bool   m_initialized;       // Initialization complete?
    u8     m_padding[7];        // Note that MSEC_T format is 64-bit!
    MSEC_T m_finAckSentTime;    // Time when ACK was sent last in response to FIN segment.

    // Applies State pattern.
    ReceiverStateBase *m_pState;
    ReceiverStateBase *m_pNextState;
    friend class ReceiverStateWaiting;
    friend class ReceiverStateOpened;
    friend class ReceiverStateWaitingFinished;
    friend class ReceiverStateFinished;
    friend class ReceiverStateClosed;
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_RECEIVERIMPL_H_
