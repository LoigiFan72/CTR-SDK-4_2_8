/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SimpleAutoStackManager.cpp

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

    void* SimpleAutoStackManager::Construct(size_t stackSize)
    {
        NN_TASSERT_(IsInitialized());

        void* const pMemory = GetAllocator()->Allocate(stackSize, 4);
        NN_POINTER_TASSERT_(pMemory);

        uptr stackBottom = reinterpret_cast<uptr>(pMemory) + stackSize;
        stackBottom = math::RoundDown(stackBottom - sizeof(DataOnStack), 8);
        DataOnStack* const pStackBottom = reinterpret_cast<DataOnStack*>(stackBottom);

        pStackBottom->pHead = pMemory;

        return pStackBottom;
    }

    void SimpleAutoStackManager::FreeStack(void* pStackBottom)
    {
        DataOnStack& dos = *reinterpret_cast<DataOnStack*>(pStackBottom);
        GetAllocator()->Free(dos.pHead);
    }


}}  //  namespace nn::os

#endif  // if NN_PLATFORM_HAS_MMU
