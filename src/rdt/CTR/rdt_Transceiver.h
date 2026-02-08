/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Transceiver.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_TRANSCEIVER_H_
#define NN_RDT_TRANSCEIVER_H_


#include "rdt_Segment.h"

namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
*/
class Transceiver{
public:
/* Please see man pages for details 
    
*/
    Transceiver(void);

/* Please see man pages for details 
    
*/
   ~Transceiver(void);

/* Please see man pages for details 
    
*/
#ifdef _WIN32
    nn::Result Initialize(SOCKET sock);
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
    nn::Result Put(const Segment &seg);

/* Please see man pages for details 
    
*/
    nn::Result Pull(Segment *pSeg);

/* Please see man pages for details 
    
*/
    static void Test(void);

private:
/* Please see man pages for details 
    
*/
    Transceiver           (const Transceiver&);

/* Please see man pages for details 
    
*/
    Transceiver& operator=(const Transceiver&);

    bool                        m_initialized;
    u8                          m_padding1[3];
#ifdef _WIN32
    SOCKET m_sock;
#elif defined(NN_PLATFORM_CTR)
    nn::uds::EndpointDescriptor m_sendEp;
    nn::uds::EndpointDescriptor m_recvEp;
    u16                         m_remoteNodeId;  // Communication partner node ID
    u8                          m_port;
    u8                          m_padding2[1];
#else
    #error no platform selected
#endif
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_TRANSCEIVER_H_
