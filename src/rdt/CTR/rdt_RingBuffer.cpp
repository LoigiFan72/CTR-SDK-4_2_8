/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_RingBuffer.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_RingBuffer.h"

#include "rdt_Stopwatch.h"

#include "Test.h"


#include <string.h>


namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {

//
RingBuffer::RingBuffer(void)
     :m_initialized(false)
{
}


//
RingBuffer::RingBuffer(void *pBuf, size_t len)
{
    Initialize(pBuf, len);
}


//
RingBuffer::~RingBuffer(void)
{
    if(m_initialized)
    {
        Finalize();
    }
}


void RingBuffer::Initialize(void *pBuf, size_t len)
{
    ASSERT(pBuf!=NULL);
    ASSERT(len > 0);

    m_pHeadBuffer = static_cast<u8*>(pBuf);
    m_bufLength   = len;
    m_pHeadData   = m_pHeadBuffer;
    m_dataLength  = 0;

    m_initialized = true;
}


void RingBuffer::Finalize(void)
{
    m_initialized = false;
}


void RingBuffer::Pop(size_t n)
{
    ASSERT(m_initialized);

    WARNINGMSG(n > 0, "Argument is not positive number.  Do nothing.\n");

    if(n > 0)
    {
        size_t len = min(n, m_dataLength);
        ASSERT((0<len) && (len<=m_dataLength));

        u8 *p = m_pHeadData += n;
        if(p >= getEndOfBuffer())
        {
            m_pHeadData = p - m_bufLength;
        }
        else
        {
            m_pHeadData = p;
        }
        ASSERT(isValidAddress(m_pHeadData));

        m_dataLength -= len;
        ASSERT((0<=len) && (len<=m_bufLength));
    }
}


bool RingBuffer::Push(const void *pBuf, size_t n)
{
    ASSERT(m_initialized);

    // TODO. Is n=0 a problem?
    if(n <= 0)
    {
        PANIC("Size of buffer is not positive number.(n=%d)\n", n);
        return false;
    }

    if(m_dataLength + n > m_bufLength)
    {
        // Cannot fit in buffer.
        return false;
    }
    else
    {
        static detail::Stopwatch s_sw("memcpy() in RingBuffer::Push()");
        s_sw.Start();

        // 01234567
        u8 *dst = getEndOfData();
        if(dst + n > getEndOfBuffer())
        {
            // Case of data overflow.
            // The overflow is written to the beginning of the buffer.
            size_t n1 = getEndOfBuffer() - dst;
            size_t n2 = n - n1;
            memcpy(dst, pBuf, n1);
            memcpy(getHeadOfBuffer(), static_cast<const u8*>(pBuf)+n1, n2);
        }
        else
        {
            memcpy(dst, pBuf, n);
        }
        s_sw.Stop();

        m_dataLength += n;
        return true;
    }
}


size_t RingBuffer::Read(void *pBuf, size_t n) const
{
    ASSERT(pBuf!=NULL);
    ASSERT(n > 0);

    return read(pBuf, n, 0);
}


size_t RingBuffer::Read(void *pBuf, size_t n, size_t offset) const
{
    ASSERT(pBuf!=NULL);
    ASSERT(n > 0);
    ASSERT((0 <= offset) && (offset < m_bufLength));

    return read(pBuf, n, offset);
}


size_t RingBuffer::read(void *pBuf, size_t n, size_t offset) const
{
    ASSERT(m_initialized);
    ASSERT(n > 0);
    ASSERT((0 <= offset) && (offset < m_bufLength));

    if(offset >= m_dataLength)
    {
        // The offset is larger than the data length and cannot be read.
        return 0;
    }

    // Calculates the number of bytes that can actually be read.
    // Even if a large n is passed, it is corrected to the length of the existing data string.
    size_t len = min(m_dataLength - offset, n);

    // Calculates the position to start the read. Also takes care of the case of a buffer overflow.
    u8 *from = m_pHeadData + offset;
    if(from >= getEndOfBuffer())
    {
        from = from - m_bufLength;
    }
    ASSERT(isValidAddress(from));

    if(from + len <= getEndOfBuffer())
    {
        // When copy does not have to be divided into two parts
        memcpy(pBuf, from, len);
    }
    else
    {
        // When copy is divided into two parts because the data to be read straddles the ring buffer boundary
        // 
        size_t len1 = getEndOfBuffer() - from;
        size_t len2 = len - len1;
        memcpy(pBuf, from, len1);
        memcpy(static_cast<u8*>(pBuf) + len1, getHeadOfBuffer(), len2);
    }

    return len;
}


// Returns the address of the location where the data is to be written next.
u8* RingBuffer::getEndOfData(void) const
{
    u8 *ret = m_pHeadData + m_dataLength;
    if(ret < getEndOfBuffer())
    {
        // Since it does not extend beyond the buffer, you do not need to modify the ret.
    }
    else
    {
        ret -= m_bufLength;
    }

    ASSERT(isValidAddress(ret));

    return ret;
}


#ifdef _WIN32
void RingBuffer::Test(void)
{
    const int BUFSIZE = 8;
    u8 buffer[BUFSIZE];

    RingBuffer r(buffer, BUFSIZE);

    CU_ASSERT(r.IsEmpty());  // If just created, should be empty.

    CU_ASSERT(r.Push("ABC", 3));
    CU_ASSERT(!r.IsEmpty());
    r.Pop(3);
    CU_ASSERT(r.IsEmpty());

    {
        r.Clear();
        const char *msg = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        CU_ASSERT(!r.Push(msg, strlen(msg)));  // Push of long text strings must fail
    }

    {
        r.Clear();
        CU_ASSERT(r.Push("ABCD", 4));
        CU_ASSERT(r.GetDataSize()==4);
        CU_ASSERT(r.Push("EFGH", 4));
        CU_ASSERT(r.GetDataSize()==8);
        CU_ASSERT(!(r.Push("XYZ", 3)));  // Doesn't fit
        char msgBuf[32];
        CU_ASSERT(r.Read(msgBuf, 32)==8);  // 8 characters, should be able to be read
        CU_ASSERT(strncmp(msgBuf, "ABCDEFGH", 8)==0);

        r.Pop(2);
        CU_ASSERT(r.GetDataSize()==6);
        CU_ASSERT(r.Read(msgBuf, 32)==6);
        CU_ASSERT(strncmp(msgBuf, "CDEFGH", 6)==0);

        r.Pop(2);
        CU_ASSERT(r.GetDataSize()==4);
        CU_ASSERT(r.Push("IJKL", 4));
        CU_ASSERT(r.GetDataSize()==8);
        CU_ASSERT(r.Read(msgBuf, 32)==8);
        CU_ASSERT(strncmp(msgBuf, "EFGHIJKL", 8)==0);

        r.Pop(3);
        CU_ASSERT(r.GetDataSize()==5);
        r.Pop(5);
        CU_ASSERT(r.GetDataSize()==0);
        CU_ASSERT(r.IsEmpty());

        CU_ASSERT(r.Push("M", 1));
        CU_ASSERT(r.Push("N", 1));
        CU_ASSERT(r.GetDataSize()==2);
        CU_ASSERT(r.Push("O", 1));
        CU_ASSERT(r.Push("P", 1));
        CU_ASSERT(r.Push("Q", 1));
        CU_ASSERT(r.GetDataSize()==5);
        CU_ASSERT(r.Push("R", 1));
        CU_ASSERT(r.Push("S", 1));
        CU_ASSERT(r.Push("T", 1));
        CU_ASSERT(r.GetDataSize()==8);
        CU_ASSERT(!r.Push("Z", 1));
        CU_ASSERT(!r.Push("Z", 1));

        r.Pop(1);
        CU_ASSERT(r.GetDataSize()==7);
        CU_ASSERT(r.Push("U", 1));
        r.Pop(2);
        CU_ASSERT(r.GetDataSize()==6);
        CU_ASSERT(r.Push("VW", 2));
        CU_ASSERT(r.Read(msgBuf, 7)==7);
        CU_ASSERT(strncmp(msgBuf, "PQRSTUV", 7)==0);
        CU_ASSERT(r.GetDataSize()==8);
        // r.Pop(0);  // Issue WARNING
        CU_ASSERT(r.GetDataSize()==8);

        // Read zero byte
        r.Pop(8);
        CU_ASSERT(r.Read(msgBuf, 8)==0);
        CU_ASSERT(r.IsEmpty());

        // Test for Read function with offset.
        CU_ASSERT(r.Push("123456", 6));
        CU_ASSERT(!r.IsEmpty());
        CU_ASSERT(r.GetDataSize()==6);
        CU_ASSERT(r.Read(msgBuf, 8, 4)==2);
        CU_ASSERT(strncmp(msgBuf, "56", 2)==0);
        r.Pop(3);
        CU_ASSERT(r.Push("789", 3));
        CU_ASSERT(r.GetDataSize()==6);
        CU_ASSERT(r.Read(msgBuf, 8, 5)==1);
        CU_ASSERT(strncmp(msgBuf, "9", 1)==0);
    }
}
#endif  // end of _WIN32


}}} // namespace nn::rdt::CTR
