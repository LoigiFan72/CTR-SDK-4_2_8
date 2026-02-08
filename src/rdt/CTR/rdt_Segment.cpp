/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Segment.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_Segment.h"

#include <string.h>

#include "rdt_Utility.h"

namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {



void Segment::SetData(const void *pBuf, u32 len)
{
    ASSERT(pBuf!=NULL);
    ASSERTMSG(len <= PAYLOAD_SIZE, "Amount of data exceeds payload.\n");;

    memcpy(payload, pBuf, len);
    header.dataLength = len;
}


u32 Segment::GetData(void *pBuf, u32 len) const
{
    ASSERT(pBuf!=NULL);
    WARNINGMSG((len <= PAYLOAD_SIZE), "You attempted to read too much data (bigger than payload size).  Ignored.");

    u32 ret = min(header.dataLength, len);
    memcpy(pBuf, payload, ret);

    return ret;
}


void Segment::Clear(void)
{
    header.Clear();
    memset(payload, 0, PAYLOAD_SIZE);
}


void Segment::ClearHeader(void)
{
    header.Clear();
}


u32 Segment::GetLastSeqNumber(void) const
{
    if(IsSyn() || IsAck() || IsFin() || IsRst())
    {
        // Because, in fact, these control bits should only be sent separately and not mixed with data.
        ASSERT(GetDataLength()==0);
        return GetSeqNumber() + GetDataLength();
    }
    else
    {
        // When it is a data segment.
        return GetSeqNumber() + GetDataLength() - 1;
    }
}


/* Please see man pages for details 
    
*/
u32 Segment::GetSegmentLength(void) const
{
    u32 ret = header.dataLength;
    if(IsSyn())
    {
        ++ret;
    }
    if(IsFin())
    {
        ++ret;
    }

    return ret;
}


void Segment::PrintDebugInfo(void) const
{
    LOG("--Header contents--\n");
    header.PrintDebugInfo();
    if(GetDataLength()==0)
    {
        LOG("--No data--\n");
    }
    else
    {
        char buf[PAYLOAD_SIZE+1];
        u32 len = GetData(buf, PAYLOAD_SIZE);
        buf[len] = '\0';
        LOG("--Data(%d bytes)--\n", GetDataLength());
//        LOG("%s\n", buf);
    }
}



}}} // namespace nn::rdt::CTR
