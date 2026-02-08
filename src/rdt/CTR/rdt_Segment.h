/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Segment.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_SEGMENT_H_
#define NN_RDT_SEGMENT_H_

#include "rdt_Header.h"

namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
*/
struct Segment{
public:
    // In the uds_Api.h, there was a description "@param[in] bufferSize   This is a buffer size. Requires received data size + 10 bytes." Accordingly, that amount was subtracted. Subtract 12 (not 10) because of padding. 
    //  
    //  
    static const size_t PAYLOAD_SIZE = 1476 - sizeof(Header) - 12;
/* Please see man pages for details 
    
*/
    Segment(void){}


/* Please see man pages for details 
    
*/
    bool IsValid(void) const { return header.magicNum==Header::MAGIC_NUMBER; }

/* Please see man pages for details 
    
           
*/
    bool IsAck(void) const { return (header.controlBit & Header::BIT_ACK)!=0; }
    bool IsSyn(void) const { return (header.controlBit & Header::BIT_SYN)!=0; }
    bool IsFin(void) const { return (header.controlBit & Header::BIT_FIN)!=0; }
    bool IsRst(void) const { return (header.controlBit & Header::BIT_RST)!=0; }

/* Please see man pages for details 
    
*/
    void SetSyn(void) { header.controlBit |= Header::BIT_SYN; }
    void SetFin(void) { header.controlBit |= Header::BIT_FIN; }
    void SetRst(void) { header.controlBit |= Header::BIT_RST; }

    void SetSrv(void) { header.controlBit |= Header::BIT_SRV; }
    void SetCli(void) { header.controlBit |= Header::BIT_CLI; }

/* Please see man pages for details 
    
*/
    u32  GetAckNumber(void) const { return header.ackNum; }

/* Please see man pages for details 
    
*/
    void SetAckNumber(u32 ack) { header.ackNum = ack; header.controlBit |= Header::BIT_ACK;}

/* Please see man pages for details 
    
*/
    u32  GetSeqNumber(void) const { return header.seqNum; }

/* Please see man pages for details 
    
*/
    u32  GetLastSeqNumber(void) const;

/* Please see man pages for details 
    
*/
    void SetSeqNumber(u32 seq) { header.seqNum = seq; }

/* Please see man pages for details 
    
*/
    void SetData(const void *pBuf, u32 len);

/* Please see man pages for details 
    
    
*/
    u32  GetData(      void *pBuf, u32 len) const;

/* Please see man pages for details 
    
*/
    bool IsData(void) const { return header.dataLength > 0; }

/* Please see man pages for details 
    
*/
    u32  GetDataLength(void) const { return header.dataLength; }

/* Please see man pages for details 
    
*/
    u32  GetSegmentLength(void) const;

/* Please see man pages for details 
    
           
*/
    void SetWindowSize(u16 n) { header.windowSize = n; }

/* Please see man pages for details 
    
*/
    u16  GetWindowSize(void) const { return header.windowSize; }

/* Please see man pages for details 
    
*/
    void Clear(void);

/* Please see man pages for details 
    
*/
    void ClearHeader(void);

/* Please see man pages for details 
    
*/
    bool IsResendRequired(void) const;

/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

    Header header;
    u8     payload[PAYLOAD_SIZE];
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_SEGMENT_H_
