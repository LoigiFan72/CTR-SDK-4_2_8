/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryBlockBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

/* 
    

    
*/

#ifndef NN_OS_OS_MEMORYBLOCKBASE_H_
#define NN_OS_OS_MEMORYBLOCKBASE_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/svc.h>
#include <nn/fnd/fnd_LinkedList.h>
#include <nn/os/CTR/os_MemoryConfig.h>

#ifdef __cplusplus

#include <nn/util/util_NonCopyable.h>
#include <nn/os/os_SvcTypes.autogen.h>
#include <nn/util/util_Result.h>

// Forward declaration
union nnosMemoryBlockBase;

namespace nn{ namespace os{


/* Please see man pages for details 
    

    
*/
class MemoryBlockBase
    : public nn::fnd::IntrusiveLinkedList<MemoryBlockBase>::Item
{
    friend class AddressSpaceManager;

private:
    uptr    m_Addr;
    size_t  m_Size;
    bool    m_ReadOnly;
    NN_PADDING3;

protected:

    MemoryBlockBase() : m_Addr(0), m_Size(0), m_ReadOnly(false) {}

    ~MemoryBlockBase() {}
    void SetAddressAndSize(uptr addr, size_t size)
    {
        this->m_Addr = addr;
        this->m_Size = size;
    }
    void SetReadOnly(bool readOnly) { this->m_ReadOnly = readOnly; }

public:
    /* Please see man pages for details 
        

        
    */
    uptr GetAddress() const { return m_Addr; }

    /* Please see man pages for details 
        

        
    */
    size_t GetSize() const { return m_Size; }

    /* Please see man pages for details 
        

        
    */
    bool IsReadOnly() const { return m_ReadOnly; }

};


    namespace detail
    {

        inline nnosMemoryBlockBase* ConvertToC(MemoryBlockBase* p)
        {
            return reinterpret_cast<nnosMemoryBlockBase*>(p);
        }
    }


}} // namespace nn::os

#endif // __cplusplus

#include <nn/util/detail/util_CLibImpl.h>

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosMemoryBlockBase, nn::os::MemoryBlockBase, 20, bit32);


#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_MEMORYBLOCKBASE_H_ */
