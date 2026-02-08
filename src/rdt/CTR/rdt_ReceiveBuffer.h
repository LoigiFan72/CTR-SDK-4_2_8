/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_ReceiveBuffer.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_RECEIVEBUFFER_H_
#define NN_RDT_RECEIVEBUFFER_H_

#include "rdt_RingBuffer.h"


namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
           
           
*/
class ReceiveBuffer{
public:
/* Please see man pages for details 
    
*/
    ReceiveBuffer(void);

/* Please see man pages for details 
    
*/
   ~ReceiveBuffer(void);

/* Please see man pages for details 
    
           
 */
    void Initialize(void *pBuf, u16 bufSize);

/* Please see man pages for details 
    
*/
    void Finalize(void);

/* Please see man pages for details 
    
    
    
    
*/
    void SetInitialSequenceNumber(u32 num);

/* Please see man pages for details 
    
    
*/
    void Pop(size_t n);

/* Please see man pages for details 
    
    
    
*/
    bool Push(const void *pBuf, size_t len);

/* Please see man pages for details 
    
    
    
    
*/
    size_t Read(void *pBuf, size_t len);

/* Please see man pages for details 
    
     
*/
    u32 GetLatestSequenceNumber(void) const;

/* Please see man pages for details 
    
*/
    size_t GetRestSize(void) const;

/* Please see man pages for details 
    
           
*/
    void Clear(void);

/* Please see man pages for details 
    
*/
    bool IsEmpty(void) const;

/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

/* Please see man pages for details 
    
*/
    static void Test(void);


private:
/* Please see man pages for details 
    
*/
    ReceiveBuffer           (const ReceiveBuffer&);

/* Please see man pages for details 
    
*/
    ReceiveBuffer& operator=(const ReceiveBuffer&);


    // Member variable group
    RingBuffer m_ringBuf;
    u32        m_initSeqNum;  // Initial sequence number
    u32        m_latestSeqNum;
    bool       m_initialized; // true if initialization completes

    // Padding
    u8         m_padding[3];
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_RECEIVEBUFFER_H_
