/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SimpleAutoStackManagerBase.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/os.h>
#include <nn/fnd.h>
#include <nn/math.h>

namespace nn { namespace os {

    namespace
    {
        struct DataOnStack
        {
            void*           pHead;
        };
    }

    SimpleAutoStackManagerBase::~SimpleAutoStackManagerBase()
    {
        Finalize();
    }

    void SimpleAutoStackManagerBase::Initialize(fnd::IAllocator* pAllocator, uptr stackBottom)
    {
        NN_TASSERT_( ! IsInitialized());
        NN_POINTER_TASSERT_(pAllocator);

        m_pAllocator = pAllocator;
        m_DestructorStackBottom = stackBottom;
        m_DestructorMutex.Initialize();
    }

    uptr SimpleAutoStackManagerBase::Finalize()
    {
        uptr stackBottom = m_DestructorStackBottom;

        if( IsInitialized() )
        {
            m_DestructorStackBottom = NULL;
            m_DestructorMutex.Finalize();
        }

        return stackBottom;
    }


    void SimpleAutoStackManagerBase::DestructImpl(void* pStackBottom, bool isError)
    {
        NN_TASSERT_(IsInitialized());

        if( isError )
        {
            FreeStack(pStackBottom);
        }
        else
        {
            // Lock so that multiple threads do not simultaneously execute a process that clears the stack.
            m_DestructorMutex.Lock();

            // Destroy the thread stack
            CallFreeStackOnOtherStack(
                pStackBottom,
                math::RoundDown(m_DestructorStackBottom, 8),
                __return_address() );
        }
    }

    asm void SimpleAutoStackManagerBase::CallFreeStackOnOtherStack(
        void*   pStackBottom    NN_IS_UNUSED_VAR,
        uptr    stackBottom     NN_IS_UNUSED_VAR,
        uptr    returnAddress   NN_IS_UNUSED_VAR )
    {
        ARM
        PRESERVE8

        // r0: this
        // r1: pStackBottom
        // r2: stackBottom
        // r3: returnAddress

        mov     sp, r2
        mov     lr, r3

        ldr     r2, [r0]
        ldr     r2, [r2, #__vcall_offsetof_vfunc(SimpleAutoStackManagerBase, FreeStack)]

        // r0: this
        // r1: pStackBottom
        // r2: FreeStack
        // lr    : returnAddr

        bx      r2
    }


}}  //  namespace nn::os

#endif  // if NN_PLATFORM_HAS_MMU
