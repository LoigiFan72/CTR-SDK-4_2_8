/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_StackMemory.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_STACKMEMORY_H_
#define NN_OS_OS_STACKMEMORY_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/svc.h>
#include <nn/os/CTR/os_MemoryConfig.h>
#include <nn/os/os_MemoryBlockBase.h>

#ifdef __cplusplus

#include <nn/util/util_NonCopyable.h>
#include <nn/os/os_SvcTypes.autogen.h>
#include <nn/util/util_Result.h>

namespace nn{ namespace os{

    namespace detail
    {
        void InitializeStackMemory();
    }

    
/* Please see man pages for details 
    

    

    
    
    

    
    
    
    
*/
class StackMemory : public MemoryBlockBase
{
private:
    uptr    m_MemoryAddress;

public:
    /* Please see man pages for details 
        

        

               
    */
    StackMemory() {}

    /* Please see man pages for details 
        

        

               

               
               

               

        
                        
        
                        
    */
    explicit StackMemory(void* pMem, size_t size) { Initialize(pMem, size); }


    /* Please see man pages for details 
        

        
        
        
        
        
    
        
                        
        
                        
        
    */
    Result TryInitialize(void* pMem, size_t size);

    /* Please see man pages for details 
        

        
        
    
        
                        
        
                        
    */
    void Initialize(void* pMem, size_t size);

    /* Please see man pages for details 
        

        
        
    */
    ~StackMemory() { Finalize(); }

    /* Please see man pages for details 
        

        
        
        
        
    */
    void* Finalize();

    /* Please see man pages for details 
        

        

        
    */
    uptr GetStackBottom() const { return GetAddress() + GetSize(); }
    
    /* Please see man pages for details 
        

        

        
    */
    size_t GetStackSize() const { return GetSize(); }

    void MoveFrom(StackMemory* pFrom);
};



}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosStackMemory, nn::os::StackMemory, 24, u32);


/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosStackMemoryProtect(nnosStackMemory* p, void* pMem, size_t size);

/*
  
*/
NN_EXTERN_C void nnosStackMemoryUnprotect(nnosStackMemory* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosStackMemoryGetAddress(nnosStackMemory* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C size_t nnosStackMemoryGetSize(nnosStackMemory* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosStackMemoryGetStackBottom(nnosStackMemory* p);

/*  



*/

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_STACKMEMORY_H_ */
