/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_AddressSpaceManager.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_ADDRESSSPACEMANAGER_H_
#define NN_OS_OS_ADDRESSSPACEMANAGER_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/types.h>
#include <nn/os/os_MemoryBlockBase.h>
#include <nn/os/os_CriticalSection.h>

#ifdef __cplusplus

namespace nn {
    namespace os {

        /* Please see man pages for details 
            
        

*/
        class AddressSpaceManager
        {
        private:
            typedef fnd::IntrusiveLinkedList<MemoryBlockBase>   BlockList;
            typedef os::CriticalSection                         Lock;

        private:
            uptr        m_SpaceBegin;    //
            uptr        m_SpaceEnd;      //
            BlockList   m_BlockList;     //
            Lock        m_Lock;          //

        public:
            AddressSpaceManager() { m_SpaceBegin = m_SpaceEnd = 0; }

            /* Please see man pages for details 
                
                
                
            
*/
            void        Initialize(uptr begin, size_t size);

            /* Please see man pages for details 
                
                
                
                
            

*/
            uptr        Allocate(MemoryBlockBase* pBlock, size_t size, size_t skipSize);

            /* Please see man pages for details 
                
                
            
*/
            void        Free(MemoryBlockBase* pBlock);

            /* Please see man pages for details 
                
                
                
            
*/
            void        Switch(MemoryBlockBase* pTo, MemoryBlockBase* pFrom);

            /* Please see man pages for details 
                
            */
            void        Dump();

        private:
            /* Please see man pages for details 
                
                
                
                
                        
                        
            




*/
            MemoryBlockBase* FindSpace(size_t size, size_t skipSize);
        };


    }
}

#endif // __cplusplus

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  
  

*/

/* Please see man pages for details 
  
  
  

*/

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosAddressSpaceManager, nn::os::AddressSpaceManager, 24, bit32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAddressSpaceManagerInitialize(nnosAddressSpaceManager* p, uptr begin, size_t size);

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosAddressSpaceManagerAllocate(nnosAddressSpaceManager* p, nnosMemoryBlockBase* pBlock, size_t size, size_t skipSize);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAddressSpaceManagerFree(nnosAddressSpaceManager* p, nnosMemoryBlockBase* pBlock);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosAddressSpaceManagerSwitch(nnosAddressSpaceManager* p, nnosMemoryBlockBase* pTo, nnosMemoryBlockBase* pFrom);

/*  



*/

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_ADDRESSSPACEMANAGER_H_ */
