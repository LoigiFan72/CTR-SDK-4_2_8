/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SimpleAutoStackManager.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_SIMPLEAUTOSTACKMANAGER_H_
#define NN_OS_OS_SIMPLEAUTOSTACKMANAGER_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#ifdef __cplusplus

#include <nn/os/os_Mutex.h>
#include <nn/os/os_SimpleAutoStackManagerBase.h>

namespace nn { 
    namespace fnd
    {
        class IAllocator;
    }

namespace os {


    /* Please see man pages for details 
        

        

        
        
        

        
        
        
        
        
        
    */
    class SimpleAutoStackManager : public SimpleAutoStackManagerBase
    {
    private:
        typedef SimpleAutoStackManagerBase Base;

    public:
        /* Please see man pages for details 
            

            
        */
        SimpleAutoStackManager(){}

        /* Please see man pages for details 
            

            
            

            
        */
        virtual ~SimpleAutoStackManager(){}

        /* Please see man pages for details 
            

            

            

            
            
            
            
            
            
            
            

            
            
            
            
            

            
            
        */
        void Initialize(fnd::IAllocator* pAllocator, uptr stackBottom)
        { Base::Initialize(pAllocator, stackBottom); }

        /* Please see man pages for details 
            

            

            
            

            

            

            
            
        */
        template <typename StackT>
        void Initialize(fnd::IAllocator* pAllocator, StackT& stack)
        {
            Initialize(pAllocator, stack.GetStackBottom());
        }

        /* Please see man pages for details 
            

            
        */
        uptr Finalize()
        { return Base::Finalize(); }

        /* Please see man pages for details 
            

            

            
        */
        virtual void* Construct(size_t stackSize);

        /* Please see man pages for details 
            

            

            
            
        */
        virtual void Destruct(void* pStackBottom, bool isError)
        { Base::DestructImpl(pStackBottom, isError); }

    private:
        virtual void FreeStack(void* pStackBottom);
    };


}} // namespace nn::os

#endif // __cplusplus

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_SIMPLEAUTOSTACKMANAGER_H_ */
