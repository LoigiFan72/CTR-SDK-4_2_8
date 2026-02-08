/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ThreadLocalStorage.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47384 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_ThreadLocalStorage.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_Private.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/assert.h>
#include <nn/hw/ARM/reg_access.h>
//---------------------------------------------------------------------------

using namespace nn;
using nn::Result;

namespace nn{ namespace os{

    namespace 
    {
#if defined(NN_PROCESSOR_ARM_V6)
        NN_STATIC_ASSERT(TLS_NUM == 16);
        
        typedef ThreadLocalRegion ThreadLocalBuffer;

        inline ThreadLocalBuffer* GetThreadLocalBuffer()
        {
            return GetThreadLocalRegion();
        }
#elif defined(NN_PROCESSOR_ARM_V5)
        struct ThreadLocalBuffer
        {
            uptr tls[TLS_NUM];
        };
        
        ThreadLocalBuffer s_ThreadLocalBuffers[nn::os::CTR::ARM946ES::NUM_THREAD_INDEX];

        inline ThreadLocalBuffer* GetThreadLocalBuffer()
        {
            return s_ThreadLocalBuffers + nn::os::CTR::ARM946ES::GetThreadIndex();
        }
#endif

        u16 sTLSMap = 0;   // Manages TLS allocation status with bits 0 to 15

        /* Please see man pages for details 
            

            
        */
        inline bool IsMappedIndex(s32 index)
        {
            if( (index < 0) || (TLS_NUM <= index) )
            {
                return false;
            }

            return ((sTLSMap >> index) & 1) == 1;
        }

        /* Please see man pages for details 
            

            
        */
        s32 SearchFreeTLSIndex()
        {
            
            for(int i = 0; i < TLS_NUM; ++i)
            {
                if(!IsMappedIndex(i))
                {
                    return i;
                }
            }
            return -1;
        }

        /* Please see man pages for details 
            

            
        */
        s32 AllocateTLSIndex()
        {
            s32 index = SearchFreeTLSIndex();
            if(index >= 0 && index < TLS_NUM)
            {
                sTLSMap |= (1 << index);
            }
            return index;
        }

        /* Please see man pages for details 
            

            
        */
        s32 FreeTLSIndex(int index)
        {
            if(!IsMappedIndex(index))
            {
                return -1;
            }
            return sTLSMap &= ~(1 << index);
        }

    } // Namespace



ThreadLocalStorage::ThreadLocalStorage()
{
    Initialize();
}

ThreadLocalStorage::~ThreadLocalStorage()
{
    if( IsMappedIndex(m_Index) )
    {
        Finalize();
    }
}

void ThreadLocalStorage::Initialize()
{
    this->m_Index = AllocateTLSIndex();
    NN_TASSERTMSG_(m_Index >= 0, "Out of Thread Local Storage Slot.");
    if ( m_Index < 0 )
    {
        NN_OS_ERROR_IF_FAILED(ResultExceedTlsLimit());
    }
}

void ThreadLocalStorage::Finalize()
{
    NN_TASSERT_(m_Index >= 0 && m_Index < TLS_NUM);
    NN_TASSERT_(IsMappedIndex(m_Index));

    FreeTLSIndex(m_Index);
}

uptr ThreadLocalStorage::GetValue() const
{
    NN_TASSERT_(m_Index >= 0 && m_Index < TLS_NUM);
    NN_TASSERT_(IsMappedIndex(m_Index));

    return GetThreadLocalBuffer()->tls[m_Index];
}

void ThreadLocalStorage::SetValue(uptr value)
{
    NN_TASSERT_(m_Index >= 0 && m_Index < TLS_NUM);
    NN_TASSERT_(IsMappedIndex(m_Index));
    NN_TASSERT_(IsMappedIndex(m_Index));

    GetThreadLocalBuffer()->tls[m_Index] = value;
}

void ThreadLocalStorage::SetValueTo(void* pTo, uptr value)
{
    ThreadLocalBuffer* pTlb = reinterpret_cast<ThreadLocalBuffer*>(pTo);
    pTlb->tls[m_Index] = value;
}

void ThreadLocalStorage::ClearAllSlots()
{
    ThreadLocalBuffer& tlr = *GetThreadLocalBuffer();

    for( int i = 0; i < TLS_NUM; ++i )
    {
        tlr.tls[i] = 0;
    }
}
    
}} // namespace nn::os

