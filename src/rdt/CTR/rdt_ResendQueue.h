/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_ResendQueue.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_RESENDQUEUE_H_
#define NN_RDT_RESENDQUEUE_H_

#include "rdt_Deque.h"

#include "rdt_Segment.h"

#include "rdt_Utility.h"


namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
    
    
    
*/

class ResendQueue{
public:
/* Please see man pages for details 
    
*/
    ResendQueue(void);

/* Please see man pages for details 
    
*/
   ~ResendQueue(void);

/* Please see man pages for details 
  
                     
                     
  
  
*/
    bool Push(const Segment &seg);

/* Please see man pages for details 
  
         
*/
    bool Front(Segment *pSeg) const;

/* Please see man pages for details 
  
         
*/
    void Remove(u32 ack);

/* Please see man pages for details 
  
*/
    void SetDefaultTimeout(MSEC_T msec) { m_defaultTimeout = msec; }

/* Please see man pages for details 
  
         
*/
    bool IsResendRequired(void) const;

/* Please see man pages for details 
  
         
         
*/
    u32 GetTotalDataSize(void) const;

/* Please see man pages for details 
  
*/
    void Clear(void);


/* Please see man pages for details 
  
         
  */
    void TryAgain(void);

/* Please see man pages for details 
  
         
         
         
         
 */
    bool IsResendMode(void) const;

/* Please see man pages for details 
  
         
         
 */
    bool IsFull(void) const { return m_queue.IsFull(); }

/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

/* Please see man pages for details 
    
*/
    static void Test(void);

private:
/* Please see man pages for details 
    
*/
    ResendQueue           (const ResendQueue&);

/* Please see man pages for details 
    
*/
    ResendQueue& operator=(const ResendQueue&);

    // If the queue capacity is not larger than the window size notified by the receiving side, the queue may become full.
    // 
    // If the RDT payload is set to 1400 bytes, it is 16 * 1400 = 22400 bytes. So if the receiving-side receive buffer (window size) is set to a larger value, the sending side queue may become blocked.
    // 
    // 
    static const size_t DEPTH = 16;

    // TODO: Parameter that needs to be adjusted with a CTR device. Has a major impact on throughput.
    // Previously, this value was 500. At that time, 256 KB of data takes 35 seconds to send and receive.
//    static const MSEC_T DEFAULT_TIMEOUT = 100;
    static const MSEC_T DEFAULT_TIMEOUT = 50;  // 150 ~ 180KB

    // Timeout value for segments including SYN. Provided to prevent the bug that causes the connection to be in a half-open state when resending at a fast pace similar to data segments.
    // 
    // 
    static const MSEC_T SYN_SEGMENT_TIMEOUT = 200;

    bool checkTimeStamp(void) const;

    struct SegmentWithTime
    {
        SegmentWithTime(void) : timeStamp(0), timeOut(0), resendMark(false) {}
        bool IsTimeOut(void) const { return (timeStamp + timeOut < GetCurrentTimeAsMillisecond()); }

        Segment segment;
        MSEC_T timeStamp;  // Time when sending
        MSEC_T timeOut;    // If the time specified here is exceeded, it becomes a resend target.
        bool resendMark;   // Marking of an element at the moment of entering to resend mode.
        u8   padding[7];   // Padding
    };

    MSEC_T                        m_defaultTimeout; // Timeout time (in milliseconds)
    Deque<SegmentWithTime, DEPTH> m_queue;          // Resend queue

    bool                          m_bResendMode;    // Resend mode flag
    u8                            m_padding[7];
};


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_RESENDQUEUE_H_
