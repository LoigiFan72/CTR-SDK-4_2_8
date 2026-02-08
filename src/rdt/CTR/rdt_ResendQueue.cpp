/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_ResendQueue.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_ResendQueue.h"

#include <string.h>

#include "Test.h"

#include "rdt_Utility.h"


namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {


ResendQueue::ResendQueue(void)
     :m_bResendMode(false)
{
    Clear();
}


ResendQueue::~ResendQueue(void)
{
}


bool ResendQueue::Push(const Segment &seg)
{
    if(m_queue.IsFull())
    {
        return false;
    }

    // TORIAEZU
    SegmentWithTime swt;
    swt.segment   = seg;
    swt.timeStamp = nn::rdt::CTR::GetCurrentTimeAsMillisecond();

    // Unlike data segments, SYN segments do not need to be sent at a high pace.
    if(seg.IsSyn())
    {
        swt.timeOut = SYN_SEGMENT_TIMEOUT;
    }
    else
    {
        swt.timeOut = m_defaultTimeout;
    }


    if(!m_queue.IsEmpty())
    {
        // In the new implementation, the partial order relation of time stamps is no longer guaranteed. (In send mode, the partial order relationship does not hold)
        // 
        // However, since it is a problem for this function to be called in that state (= attempting to send new data before the resend process completes), this code will be left for a little longer.
        // 
        // 
        // Checks whether the time stamps for the element group recorded in the queue maintains a partial order relation.
        //  
        ASSERT(swt.timeStamp >= m_queue.Back().timeStamp);
    }

    m_queue.PushBack(swt);

    return true;
}


bool ResendQueue::Front(Segment *pSeg) const
{
    ASSERT(pSeg!=NULL);

    if(m_queue.IsEmpty())
    {
        return false;
    }
    else
    {
        *pSeg = m_queue.Front().segment;
        return true;
    }
}


// 
// Remove function must be revised. Because it already cannot be assumed that the queue is arranged in the time stamp order.
// 
// With this implementation, if the Remove function target is not at the beginning of the queue, the target is not removed.
void ResendQueue::Remove(u32 ack)
{
    while(!m_queue.IsEmpty())
    {
        const Segment &seg = m_queue.Front().segment;
        u32 lastSeq = seg.GetLastSeqNumber();

        if(0 < static_cast<s32>(ack) - static_cast<s32>(lastSeq))
        {
            m_queue.PopFront();
            VERBOSE("Start of the resend queue was removed. \n");
            if(m_queue.IsEmpty())
            {
                // Resend mode ends if the resend queue is empty.
                m_bResendMode = false;
            }
        }
        else
        {
            // If even the start cannot get arrival confirmation with ACK, the following segment surely won't be able to.
            //  Leave loop.
            break;
        }
    }
}


bool ResendQueue::IsResendRequired(void) const
{
    if(m_queue.IsEmpty())
    {
        return false;
    }
    else
    {
        return m_queue.Front().IsTimeOut();
    }
}


u32 ResendQueue::GetTotalDataSize(void) const
{
    u32 ret = 0;
    for(size_t i= 0; i<m_queue.Size(); ++i)
    {
        ret += m_queue.At(i).segment.GetDataLength();
    }

    return ret;
}


void ResendQueue::Clear(void)
{
    m_queue.Clear();
    m_defaultTimeout = DEFAULT_TIMEOUT;
}


// Move start element to the end. At this time, the element time stamp is changed.
void ResendQueue::TryAgain(void)
{
    ASSERT(IsResendMode());

    // Start element to the end. Set resend mode flag.
    struct SegmentWithTime s = m_queue.Front();
    m_queue.PopFront();
    s.timeStamp = nn::rdt::CTR::GetCurrentTimeAsMillisecond();
    if(!m_bResendMode)
    {
        // If first TryAgain function attempt, place mark on element.
        // Enable resend mode flag.
        s.resendMark = true;
        m_bResendMode = true;
    }
    m_queue.PushBack(s);

    if(m_queue.Front().resendMark)
    {
        // By calling TryAgain function several times, one cycle is complete!
        // Disable the resend mode flag
        m_queue.Front().resendMark = false;
        m_bResendMode = false;
    }
}


bool ResendQueue::IsResendMode(void) const
{
    return m_bResendMode || IsResendRequired();
}


void ResendQueue::PrintDebugInfo(void) const
{
    LOG("Number of ResendQueue elements: %d, total data size is %d bytes.\n", m_queue.Size(), GetTotalDataSize());
}


void ResendQueue::Test(void)
{
    char data[100 + 50 + 30];
    memset(data, 0, 100 + 50 + 30);

    ResendQueue r;
    r.SetDefaultTimeout(500);  // 500-millisecond resend timeout

    const u32 SEQ = 5000;

    Segment a;  // Data is 100 bytes
    a.SetData(data, 100);
    a.SetSeqNumber(SEQ);

    Segment b;  // Data is 50 bytes
    b.SetData(data+100, 50);
    b.SetSeqNumber(SEQ + 100);

    Segment c;  // Data is 30 bytes
    c.SetData(data+100+50, 30);
    c.SetSeqNumber(SEQ + 100 + 50);

    CU_ASSERT(r.Push(a));
    CU_ASSERT(r.m_queue.Size()==1);
    r.Remove(SEQ);
    CU_ASSERT(r.m_queue.Size()==1);  // Should be no changes

    r.Remove(SEQ+99);
    CU_ASSERT(r.m_queue.Size()==1);  // Should still be no changes

    r.Remove(SEQ+100);
    CU_ASSERT(r.m_queue.Size()==0);  // Should be removed

    CU_ASSERT(r.Push(b));
    CU_ASSERT(r.Push(c));
    CU_ASSERT(r.m_queue.Size()==2);
    
    r.Remove(SEQ+101);
    CU_ASSERT(r.m_queue.Size()==2);

    r.Remove(SEQ+149);
    CU_ASSERT(r.m_queue.Size()==2);

    r.Remove(SEQ+180);
    CU_ASSERT(r.m_queue.Size()==0);

    // Hereafter, timeout check

    r.SetDefaultTimeout(500);
    Segment d;
    CU_ASSERT(r.Push(a));
    CU_ASSERT(r.m_queue.Size()==1);
    CU_ASSERT(!r.IsResendRequired());
    SleepCurrentThread(200);
    CU_ASSERT(!r.IsResendRequired());
    SleepCurrentThread(500);
    CU_ASSERT(r.IsResendRequired());
    CU_ASSERT(r.IsResendRequired());
    CU_ASSERT(r.m_queue.Size()==1); 

    CU_ASSERT(r.Push(a));
    SleepCurrentThread(300);
    CU_ASSERT(r.Push(b));
    SleepCurrentThread(300);
    CU_ASSERT(r.m_queue.Size()==3);
    CU_ASSERT(r.IsResendRequired());
    r.Remove(SEQ+100);
    CU_ASSERT(!r.IsResendRequired());
    CU_ASSERT(r.m_queue.Size()==1);

    // Hereafter, checks IsResendMode and TryAgain function
    Segment e, f, g;
    r.Clear();
    r.SetDefaultTimeout(500);
    CU_ASSERT(r.m_queue.Size()==0);
    CU_ASSERT(!r.IsResendMode());
    CU_ASSERT(r.Push(e));
    SleepCurrentThread(400);
    CU_ASSERT(r.Push(f));
    CU_ASSERT(r.Push(g));
    SleepCurrentThread(200);  // At this point, e is in timeout.
    CU_ASSERT(r.IsResendMode());  // Since there is one timeout element, must be in resend mode.
    r.TryAgain();
    CU_ASSERT(r.IsResendMode());
    r.TryAgain();
    CU_ASSERT(r.IsResendMode());
    r.TryAgain();
    CU_ASSERT(!r.IsResendMode()); // Since all elements have had a turn, should exit from resend mode.
    CU_ASSERT(r.m_queue.Size()==3);

    // Check SYN segment
    r.Clear();
    Segment s;
    s.SetSyn();
    r.SetDefaultTimeout(10);
    r.Push(s);
    SleepCurrentThread(150);
    CU_ASSERT(!r.IsResendRequired());  // The timeout value for SYN segments is made to be long so it will not become a resend target.
    SleepCurrentThread(150);
    CU_ASSERT(r.IsResendRequired());
}

}}} // namespace nn::rdt::CTR
