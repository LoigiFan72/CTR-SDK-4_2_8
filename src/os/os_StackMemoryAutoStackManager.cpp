/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_StackMemoryAutoStackManager.cpp

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
            StackMemory     stackMemory;
            void*           pHead;
        };
    }

    void* StackMemoryAutoStackManager::Construct(size_t stackSize)
    {
        NN_TASSERT_(IsInitialized());
        NN_ALIGN_TASSERT_(stackSize, 0x1000);

        void* const pMemory = GetAllocator()->Allocate(stackSize, 0x1000);
        NN_POINTER_TASSERT_(pMemory);

        StackMemory stackMemory;
        stackMemory.Initialize(pMemory, stackSize);

        uptr stackBottom = stackMemory.GetStackBottom();
        stackBottom -= math::RoundUp(sizeof(DataOnStack), 8);
        DataOnStack* const pStackBottom = reinterpret_cast<DataOnStack*>(stackBottom);

        new(&pStackBottom->stackMemory) StackMemory();
        pStackBottom->stackMemory.MoveFrom(&stackMemory);
        pStackBottom->pHead = pMemory;

        return pStackBottom;
    }

    void StackMemoryAutoStackManager::FreeStack(void* pStackBottom)
    {
        DataOnStack& dos = *reinterpret_cast<DataOnStack*>(pStackBottom);

        void* volatile pHead = dos.pHead;

        StackMemory stackMemory;
        stackMemory.MoveFrom(&dos.stackMemory);
        stackMemory.Finalize();
        GetAllocator()->Free(pHead);
    }


}}  //  namespace nn::os

#endif  // if NN_PLATFORM_HAS_MMU
