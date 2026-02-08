/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Header.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_HEADER_H_
#define NN_RDT_HEADER_H_


namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
*/
struct Header{
public:
    static const u32 MAGIC_NUMBER = 'N' << 24 | 'N' << 16 | 'R' << 8 | 'P' << 0;

    // Control bit group.
    static const u16 BIT_ACK = 0x0001;
    static const u16 BIT_RST = 0x0002;
    static const u16 BIT_SYN = 0x0008;
    static const u16 BIT_FIN = 0x0010;
    static const u16 BIT_SRV = 0x0100;
    static const u16 BIT_CLI = 0x0200;

/* Please see man pages for details 
    
*/
    Header(void);

/* Please see man pages for details 
    
    
*/
    void Clear(void);

/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

    u32 magicNum;    // Magic number (place at start of structure!)
    u32 seqNum;      // Sequence number
    u32 ackNum;      // ACK number
    u8  dataOffset;  // Data offset. Where the data portion begins from. (=header length)
    u8  reserved;    // Unused (may also function as padding)
    u16 controlBit;  // Control bit
    u32 dataLength;  // Actual data size. Probably will be unnecessary.
    u16 windowSize;  // Window size Used for notifications from receiving side to sending side.
    u16 checkSum;    // Checksum
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_HEADER_H_
