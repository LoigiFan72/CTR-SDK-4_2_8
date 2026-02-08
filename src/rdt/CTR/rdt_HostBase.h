/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_HostBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_HOSTBASE_H_
#define NN_RDT_HOSTBASE_H_


#include "rdt_Transceiver.h"

namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
           
*/
class HostBase{
public:

/* Please see man pages for details 
    
*/
    HostBase(void);

/* Please see man pages for details 
    
*/
    virtual ~HostBase(void);

/* Please see man pages for details 
    
*/
#ifdef _WIN32
    nn::Result Initialize(SOCKET &sock);
#elif defined(NN_PLATFORM_CTR)
    nn::Result Initialize(u16 nodeId, u8 port);  // Sender node ID and port number
#else
    #error no platform selected
#endif

/* Please see man pages for details 
    
*/
    void Finalize(void);

/* Please see man pages for details 
    
    
*/
    void SetPacketLossRatio(int per);

/* Please see man pages for details 
    
*/
    nn::Result GetErrorCode(void) const { return m_resultCode; }

/* Please see man pages for details 
    
*/
    static void PrintProperty(void);


protected:
    // Sends segment. To perform resend process, do so outside of this function.
    // Depending on the packet loss rate, the send fails (no send is performed)
    void putSegment(const Segment &seg);

    // Receive segment.
    nn::Result pullSegment(Segment *pSeg);

    // Sends segment that includes the RST control bit.
    // This segment is not a target for resending.
    void sendRstSegment(u32 seq);

    // Sends segment that includes the RST and ACK control bit.
    // This segment is not a target for resending.
    void sendRstAckSegment(u32 seq, u32 ack);

    // Records error information. Call this function if a state where an error occurs happens.
    void errorHandling(Result resultCode);


private:
/* Please see man pages for details 
    
*/
    HostBase           (const HostBase&);

/* Please see man pages for details 
    
*/
    HostBase& operator=(const HostBase&);

    Transceiver   m_transceiver; // Send/receive object

    int m_packetLossRatio;       // Packet loss rate. Zero or higher, 100 or lower.

    Result m_resultCode;         // Record most recent result code here

    bool m_initialized;
    u8   m_padding[3];
};


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_HOSTBASE_H_
