/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_ReceiveBuffer.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_ReceiveBuffer.h"

#include "Test.h"

#include "rdt_Utility.h"


namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {

//
ReceiveBuffer::ReceiveBuffer(void)
     :m_initialized(false)
{
}


//
ReceiveBuffer::~ReceiveBuffer(void)
{
    Finalize();
}



void ReceiveBuffer::Initialize(void *pBuf, u16 bufSize)
{
    ASSERT(pBuf!=NULL);
    ASSERT(bufSize > 0);

    if(m_initialized)
    {
        LOG("ReceiveBuffer object is already initialized.\n");
    }
    else
    {
        m_ringBuf.Initialize(pBuf, bufSize);
        Clear();
        m_initialized  = true;
    }
}


void ReceiveBuffer::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
        m_ringBuf.Finalize();
    }
}


void ReceiveBuffer::SetInitialSequenceNumber(u32 num)
{
    m_initSeqNum   = num;
    m_latestSeqNum = num;
}


void ReceiveBuffer::Pop(size_t n)
{
    ASSERT(m_initialized);

    ASSERT(n >= 0);
    m_ringBuf.Pop(n);
}


bool ReceiveBuffer::Push(const void *pBuf, size_t len)
{
    ASSERT(m_initialized);
    ASSERT(pBuf!=NULL);
    ASSERT(len > 0);

    bool ret = m_ringBuf.Push(pBuf, len);
    if(ret)
    {
        m_latestSeqNum += len;  // Newest octet sequence number update
    }
    return ret;
}


size_t ReceiveBuffer::Read(void *pBuf, size_t len)
{
    ASSERT(m_initialized);
    ASSERT(pBuf!=NULL);
    ASSERT(len > 0);

    return m_ringBuf.Read(pBuf, len);
}


u32 ReceiveBuffer::GetLatestSequenceNumber(void) const
{
    ASSERT(m_initialized);

    return m_latestSeqNum;
}


size_t ReceiveBuffer::GetRestSize(void) const
{
    ASSERT(m_initialized);

    size_t ret = m_ringBuf.GetRestSize();

    // With the Initialize function, the size can only be specified with u16, so it is odd if the size is out of this range.
    // 
    ASSERT((0 <= ret) && (ret <= USHRT_MAX));

    return ret;
}


void ReceiveBuffer::Clear(void)
{
    m_ringBuf.Clear();
    m_initSeqNum   = 0;
    m_latestSeqNum = 0;
}


bool ReceiveBuffer::IsEmpty(void) const
{
    return m_ringBuf.IsEmpty();
}


void ReceiveBuffer::PrintDebugInfo(void) const
{
    if(m_initialized)
    {
        LOG("Initialized.\n");
        LOG("Initial sequecne number: %u\n", m_initSeqNum);
        LOG("Latest octet sequence nubmer: %u\n",  m_latestSeqNum);
    }
    else
    {
        LOG("Not initialized.\n");
    }
}


#ifdef _WIN32
// Single unit test with CUnit
void ReceiveBuffer::Test(void)
{
    ReceiveBuffer w;

    const int BUFSIZE = 4096;
    u8 windowBuf[BUFSIZE];
    const u32 SEQ_NUM = 100;
    
    w.Initialize(windowBuf, BUFSIZE);
    w.SetInitialSequenceNumber(SEQ_NUM);
    CU_ASSERT(w.GetRestSize()==BUFSIZE);
    CU_ASSERT(w.GetLatestSequenceNumber()==SEQ_NUM);

    char buf[BUFSIZE*2];
    CU_ASSERT(!w.Push(buf, sizeof(buf)));  // Should fail because the data is too large to Push.

    CU_ASSERT(w.Push("Hello", 5));
    CU_ASSERT(w.Read(buf, 5)==5);
    CU_ASSERT(strncmp(buf, "Hello", 5)==0);
    CU_ASSERT(w.GetLatestSequenceNumber()==SEQ_NUM+5);
    CU_ASSERT(w.GetRestSize()==BUFSIZE-5);

    w.Pop(3);
    CU_ASSERT(w.GetRestSize()==BUFSIZE-2);
    CU_ASSERT(w.GetLatestSequenceNumber()==SEQ_NUM+5);
    CU_ASSERT(w.Read(buf, 5)==2);

    CU_ASSERT(w.Push("ading", 5));
    CU_ASSERT(w.GetRestSize()==BUFSIZE-7);
    CU_ASSERT(w.Read(buf, 100)==7);
    CU_ASSERT(w.GetLatestSequenceNumber()==SEQ_NUM+10);
}
#endif // end of _WIN32

}}} // namespace nn::rdt::CTR
