/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_SendBuffer.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_SENDBUFFER_H_
#define NN_RDT_SENDBUFFER_H_

#include "rdt_RingBuffer.h"

namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
*/
class SendBuffer{
public:
/* Please see man pages for details 
    
*/
    SendBuffer(void);

/* Please see man pages for details 
    
*/
   ~SendBuffer(void);

/* Please see man pages for details 
    
 */
    void Initialize(void *pBuf, u16 bufSize);

/* Please see man pages for details 
    
*/
    void Finalize(void);

/* Please see man pages for details 
    
    
    
*/
    bool Push(const void *pBuf, size_t len);

/* Please see man pages for details 
    
    
    
    
 */
    size_t Pull(void *pBuf, u32 *pSeq, size_t len);

/* Please see man pages for details 
    
*/
    bool IsEmpty(void) const;

/* Please see man pages for details 
    
*/
    u32 GetInitialSequenceNumber(void) const;

/* Please see man pages for details 
    
*/
    u32 GetCurrentSequenceNumber(void) const;

/* Please see man pages for details 
    
           
           
*/
    void Clear(u32 initSeqNum);

/* Please see man pages for details 
    
*/
    void PrintDebugInfo(void) const;

/* Please see man pages for details 
    
*/
    static void Test(void);


private:
/* Please see man pages for details 
    
*/
    SendBuffer           (const SendBuffer&);

/* Please see man pages for details 
    
*/
    SendBuffer& operator=(const SendBuffer&);

    u32 genInitSeqNum(void) const;

    RingBuffer m_ringBuf;
    u32        m_initSeqNum;   // Initial sequence number
    u32        m_readByte;     // Number of bytes of data read with Pull up to this point
    bool       m_initialized;

    u8         m_padding[3];   // Padding
};



}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_SENDBUFFER_H_
