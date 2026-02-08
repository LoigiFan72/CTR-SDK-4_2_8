/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Default.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/Result.h>
#include <nn/os.h>
#include <nn/math.h>

namespace nn { namespace os {

#if NN_PLATFORM_HAS_MMU
    namespace
    {
        class DefaultAutoStackManager : public AutoStackManager
        {
        private:
            static const size_t DESTRUCTOR_STACK_SIZE = 512;

        private:
            nn::os::Mutex                               m_DestructorMutex;         //
            bool                                        m_Initialized;
            NN_PADDING3;
            NN_PADDING4;
            nn::os::StackBuffer<DESTRUCTOR_STACK_SIZE>  m_DestructorStack;

        public:
            DefaultAutoStackManager() : m_Initialized(false)
            {
            }

            virtual ~DefaultAutoStackManager()
            {
                if ( m_Initialized )
                {
                    m_DestructorMutex.Finalize();
                    m_Initialized = false;
                }
            }

            virtual void* Construct(size_t stackSize)
            {
                if ( !m_Initialized )
                {
                    Initialize();
                }
                
                nnosStackMemoryBlock stackBlock;
                nnosStackMemoryBlockAllocate(&stackBlock, stackSize);

                uptr stackBottom = nnosStackMemoryBlockGetStackBottom(&stackBlock);
                stackBottom -= math::RoundUp(sizeof(nnosStackMemoryBlock), 8);

                nnosStackMemoryBlock* pBlockOnStack = reinterpret_cast<nnosStackMemoryBlock*>(stackBottom);

                nnosStackMemoryBlockInitialize(pBlockOnStack);
                nn::os::detail::Switch(
                    reinterpret_cast<nn::os::StackMemoryBlock*>(pBlockOnStack),
                    reinterpret_cast<nn::os::StackMemoryBlock*>(&stackBlock) );

                return reinterpret_cast<void*>(stackBottom);
            }

            virtual void Destruct(void* pStackBottom, bool isError)
            {
                if( isError )
                {
                    FreeStack(reinterpret_cast<nnosStackMemoryBlock*>(pStackBottom));
                }
                else
                {
                    // Locks so that stack region release processes do not occur simultaneously on multiple threads.
                    m_DestructorMutex.Lock();

                    // Destroys the thread stack.
                    InvokeOnOtherStack(m_DestructorStack.GetStackBottom(), &FreeStack, pStackBottom, __return_address());
                }
            }

        private:
            void Initialize(void)
            {
                m_DestructorMutex.Initialize(false);
                m_Initialized = true;
            }

            static void FreeStack(void* pStackBottom)
            {
                nnosStackMemoryBlock* pBlockOnStack = reinterpret_cast<nnosStackMemoryBlock*>(pStackBottom);
                nnosStackMemoryBlockFree(pBlockOnStack);
            }

            static asm void InvokeOnOtherStack(
                uptr    stackBottom NN_IS_UNUSED_VAR,
                void (*f)(void*)    NN_IS_UNUSED_VAR,
                void*   param       NN_IS_UNUSED_VAR,
                uptr    returnAddr  NN_IS_UNUSED_VAR)
            {
                ARM

                // r0: stackBottom
                // r1: f
                // r2: param
                // r3: returnAddr

                mov     sp, r0
                mov     r0, r2
                mov     lr, r3

                // r0: param
                // r1: f
                // lr: returnAddr

                bx      r1
            }
        };

        DefaultAutoStackManager s_AutoStackManager;
    }
#endif  // if NN_PLATFORM_HAS_MMU


void SetDefaultAutoStackManager()
{
#if NN_PLATFORM_HAS_MMU
    nn::os::Thread::SetAutoStackManager(&s_AutoStackManager);
#endif  // if NN_PLATFORM_HAS_MMU
}



}}
