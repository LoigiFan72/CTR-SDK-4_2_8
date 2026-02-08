/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_SendBuffer.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_SendBuffer.h"

#include "Test.h"


namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {

//
SendBuffer::SendBuffer(void)
     :m_initialized(false)
{
}


//
SendBuffer::~SendBuffer(void)
{
    Finalize();
}


void SendBuffer::Initialize(void *pBuf, u16 bufSize)
{
    ASSERT(pBuf!=NULL);
    ASSERT(bufSize > 0);

    if(m_initialized)
    {
        LOG("ReceiveWindow object is already initialized.  Do nothing.\n");
    }
    else
    {
        m_ringBuf.Initialize(pBuf, bufSize);
        m_readByte     = 0;
        m_initialized  = true;
    }
}


void SendBuffer::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
        m_ringBuf.Finalize();
    }
}

/* Please see man pages for details 
    
    
    
 */
bool SendBuffer::Push(const void *pBuf, size_t len)
{
    ASSERT(m_initialized);
    ASSERT(pBuf!=NULL);
    ASSERT(len > 0);

    bool ret = m_ringBuf.Push(pBuf, len);
    if(ret)
    {
        return true;
    }
    else
    {
        return false;
    }
}


size_t SendBuffer::Pull(void *pBuf, u32 *pSeq, size_t len)
{
    ASSERT(m_initialized);
    ASSERT(pBuf!=NULL);
    ASSERT(pSeq!=NULL);
    ASSERT(len > 0);

    size_t ret = m_ringBuf.Read(pBuf, len);
    if(ret > 0)
    {
        m_ringBuf.Pop(ret);
        *pSeq = GetCurrentSequenceNumber();
        m_readByte += ret;
        return ret;
    }
    else
    {
        return 0;
    }
}


bool SendBuffer::IsEmpty(void) const
{
    ASSERT(m_initialized);

    return m_ringBuf.IsEmpty();
}


u32 SendBuffer::GetInitialSequenceNumber(void) const
{
    ASSERT(m_initialized);

    return m_initSeqNum;
}


u32 SendBuffer::GetCurrentSequenceNumber(void) const
{
    ASSERT(m_initialized);

    return m_initSeqNum + 1 + m_readByte;
}


void SendBuffer::Clear(u32 initSeqNum)
{
    m_ringBuf.Clear();
    m_readByte   = 0;
    m_initSeqNum = initSeqNum;
}


void SendBuffer::PrintDebugInfo(void) const
{
    LOG("[SendBuffer] %u bytes read by Pull().\n", m_readByte);
}


#ifdef _WIN32
void SendBuffer::Test(void)
{
    const u16 BUFSIZE = 8;
    u8 buf[BUFSIZE];

    SendBuffer s;
    s.Initialize(buf, BUFSIZE);
    s.Clear(300);

    const u32 ISS = s.GetInitialSequenceNumber();  // Initial sequence number

    CU_ASSERT(s.IsEmpty());
    CU_ASSERT(s.Push("ABC", 3));
    CU_ASSERT(s.Push("DEFGH", 5));
    CU_ASSERT(!s.IsEmpty());
    CU_ASSERT(!s.Push("XYZ", 3));

    char msg[256];
    u32 seq = 0;
    CU_ASSERT(s.Pull(msg, &seq, 4)==4);
    CU_ASSERT(strncmp(msg, "ABCD", 4)==0);
    CU_ASSERT(seq==ISS+1);
    CU_ASSERT(!s.IsEmpty());
    CU_ASSERT(s.Pull(msg, &seq, 5)==4);
    CU_ASSERT(strncmp(msg, "EFGH", 4)==0);
    CU_ASSERT(seq==ISS+1+4);
    CU_ASSERT(s.IsEmpty());

    // OK to call multiple times?
    s.Finalize();
    s.Finalize();
}
#endif  // end of _WIN32


}}} // namespace nn::rdt::CTR
