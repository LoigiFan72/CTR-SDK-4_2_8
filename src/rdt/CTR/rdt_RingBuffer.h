/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_RingBuffer.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_RINGBUFFER_H_
#define NN_RDT_RINGBUFFER_H_

#include "rdt_Utility.h"


namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
*/
class RingBuffer{
public:
/* Please see man pages for details 
    
*/
    RingBuffer(void);

/* Please see man pages for details 
    
*/
    RingBuffer(void *pBuf, size_t len);

/* Please see man pages for details 
    
*/
   ~RingBuffer(void);

/* Please see man pages for details 
    
    
*/
    void Initialize(void *pBuf, size_t len);

/* Please see man pages for details 
    
*/
    void Finalize(void);


    // Removes n bytes from the start of the data string.
    // When a numerical value larger than the length of the data string is specified, all data is removed.
    void Pop(size_t n);

    // n bytes of data indicated by pBuf is appended to the end of the existing data string.
    // Returns false when the buffer is insufficient and the given data string cannot be written.
    bool Push(const void *pBuf, size_t n);

    // Load a maximum of n bytes of data (from the beginning of the maintained data string).
    // At this time, the data string is not removed from the buffer.
    // The returned value is the actual number of bytes that could be read.
    // Returns zero if no data to read exists.
    size_t Read(void *pBuf, size_t n) const;

    // Load a maximum of n bytes of data from the position shifted offset bytes from the beginning of the data string.
    // At this time, the data string is not removed from the buffer.
    // The returned value is the actual number of bytes that could be read.
    // Returns zero if no data to read exists.
    size_t Read(void *pBuf, size_t n, size_t offset) const;

    // Determines whether the data string is empty.
    bool IsEmpty(void) const { ASSERT(m_initialized); return m_dataLength==0; }

    // Empties the data string.
    void Clear(void) { ASSERT(m_initialized); m_pHeadData = getHeadOfBuffer(); m_dataLength = 0; }

    // Returns the length (in bytes) of the currently maintained data string.
    size_t GetDataSize(void) const { ASSERT(m_initialized); return m_dataLength; }

    // Returns this buffer size (in bytes).
    size_t GetBufferSize(void) const { ASSERT(m_initialized); return m_bufLength; }

    // Returns the number of bytes that can currently be written (the free size, in other words).
    size_t GetRestSize(void) const { ASSERT(m_initialized); return GetBufferSize() - GetDataSize(); }

/* Please see man pages for details 
    
*/
    static void Test(void);


private:
/* Please see man pages for details 
    
*/
    RingBuffer           (const RingBuffer&);

/* Please see man pages for details 
    
*/
    RingBuffer& operator=(const RingBuffer&);

    // Returns the start address of the buffer.
    u8* getHeadOfBuffer(void) const { return m_pHeadBuffer; }

    // Returns the end address +1 for the buffer.
    u8* getEndOfBuffer(void) const { return m_pHeadBuffer + m_bufLength; }

    // Returns the address of the location where the data is to be written next.
    u8* getEndOfData(void) const;

    // Subcontracting function for Read function
    size_t read(void *pBuf, size_t n, size_t offset) const;

    // For debugging. Is the passed pointer indicating in the buffer?
    bool isValidAddress(u8 *p) const { return (getHeadOfBuffer() <= p) && (p < getEndOfBuffer()); }

    u8    *m_pHeadBuffer; // Indicates the start of the buffer.
    size_t m_bufLength;   // Buffer length.
    u8    *m_pHeadData;   // Pointer indicating start of (meaningful) data.
                          // Data can be read from this position.
    size_t m_dataLength;  // Length of currently maintained data string.
    bool   m_initialized; // Has the object been initialized?

    u8     m_padding[3];  // Padding
};

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_RINGBUFFER_H_
