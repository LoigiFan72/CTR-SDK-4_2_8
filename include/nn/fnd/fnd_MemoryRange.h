/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_MemoryRange.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47798 $
 *---------------------------------------------------------------------------*/

/*
  
 */

#ifndef NN_FND_FND_MEMORYRANGE_H_
#define NN_FND_FND_MEMORYRANGE_H_

#include <nn/types.h>

#include <nn/assert.h>

#ifdef __cplusplus


namespace nn { namespace fnd {

/* Please see man pages for details 
    

    
 */
class MemoryRange
{
public:

    MemoryRange() {}

    /* Please see man pages for details 
        

        

        
    */
    MemoryRange(uptr begin, uptr end) : m_Begin(begin), m_End(end) { NN_TASSERT_(m_Begin <= m_End); }

    /* Please see man pages for details 
        

        

        
    */
    void Initialize(uptr begin, uptr end) { m_Begin = begin; m_End = end; NN_TASSERT_(m_Begin <= m_End); }

    /* Please see man pages for details 
        
    */
    uptr GetAddress() const { return m_Begin; }

    /* Please see man pages for details 
        
        
                    
    */
    uptr GetEndAddress() const { return m_End; }

    /* Please see man pages for details 
        

        
    */
    size_t GetSize() const { return m_End - m_Begin; }

private:
    uptr m_Begin;
    uptr m_End;
};

}}

#endif

#endif
