/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Header.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_Header.h"

#include <string.h>

#include "rdt_Utility.h"

namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {

//
Header::Header(void)
{
    Clear();
}


void Header::Clear(void)
{
    magicNum = MAGIC_NUMBER;

    // Zero clear except for the magic number.
    memset(&magicNum + 1, 0, sizeof(Header)-sizeof(magicNum));
}


void Header::PrintDebugInfo(void) const
{
    ASSERTMSG(magicNum==MAGIC_NUMBER, "Wrong magic number.");
    ASSERTMSG(reserved==0, "Don't use reserved.  Keep it as zero.");

    char buf[256] = "";
#ifdef _WIN32
    controlBit & BIT_ACK ? strcat_s(buf, "[ACK]") : strcat_s(buf, "[---]");
    controlBit & BIT_SYN ? strcat_s(buf, "[SYN]") : strcat_s(buf, "[---]");
    controlBit & BIT_FIN ? strcat_s(buf, "[FIN]") : strcat_s(buf, "[---]");
    controlBit & BIT_RST ? strcat_s(buf, "[RST]") : strcat_s(buf, "[---]");
#else
    controlBit & BIT_ACK ? strcat(buf, "[ACK]") : strcat(buf, "[---]");
    controlBit & BIT_SYN ? strcat(buf, "[SYN]") : strcat(buf, "[---]");
    controlBit & BIT_FIN ? strcat(buf, "[FIN]") : strcat(buf, "[---]");
    controlBit & BIT_RST ? strcat(buf, "[RST]") : strcat(buf, "[---]");
#endif
    LOG("Control bit: %s\n", buf);
    LOG("SEQ: %u, ACK: %u, dataOffset: %u, dataLength: %u\n", seqNum, ackNum, dataOffset, dataLength);
    LOG("WindowSize: %u, checksum: %u\n", windowSize, checkSum);
}


}}} // namespace nn::rdt::CTR
