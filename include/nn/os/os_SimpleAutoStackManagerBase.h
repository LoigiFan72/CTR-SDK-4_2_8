/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SimpleAutoStackManagerBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_SIMPLEAUTOSTACKMANAGERBASE_H_
#define NN_OS_OS_SIMPLEAUTOSTACKMANAGERBASE_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#ifdef __cplusplus

#include <nn/os/os_Mutex.h>
#include <nn/os/os_AutoStackManager.h>

namespace nn { 
    namespace fnd
    {
        class IAllocator;
    }

namespace os {


    class SimpleAutoStackManagerBase : public AutoStackManager
    {
    private:
        Mutex                               m_DestructorMutex;
        fnd::IAllocator*                    m_pAllocator;
        uptr                                m_DestructorStackBottom;

    public:
        SimpleAutoStackManagerBase()
            : m_pAllocator(NULL)
        {
        }

        virtual ~SimpleAutoStackManagerBase();

        void Initialize(fnd::IAllocator* pAllocator, uptr stackBottom);

        uptr Finalize();


    protected:
        virtual void FreeStack(void* pStackBottom) = 0;

        bool IsInitialized() const { return m_DestructorMutex.IsValid(); }
        fnd::IAllocator* GetAllocator() { return m_pAllocator; }

        void DestructImpl(void* pStackBottom, bool isError);
        void CallFreeStackOnOtherStack(void* pStackBottom, uptr stackBottom, uptr returnAddress);
    };


}} // namespace nn::os

#endif // __cplusplus

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_SIMPLEAUTOSTACKMANAGERBASE_H_ */
