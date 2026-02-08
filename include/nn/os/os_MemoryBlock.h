/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryBlock.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_MEMORYBLOCK_H_
#define NN_OS_OS_MEMORYBLOCK_H_

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

    class MemoryBlock;

    namespace detail
    {
        uptr AllocateFromMemoryBlockSpace(MemoryBlockBase* p, size_t s);
        void FreeToMemoryBlockSpace(MemoryBlockBase* p);
        void Switch(MemoryBlock* pTo, MemoryBlock* pFrom);

        bool IsMemoryBlockEnabled();
    }

    
/* Please see man pages for details 
    

    

    
    

    

*/
class MemoryBlock : public MemoryBlockBase
{
public:
    /* Please see man pages for details 
        

        

               
    */
    MemoryBlock() {}

    /* Please see man pages for details 
        

        

               

        
                        
    */
    explicit MemoryBlock(size_t size) { Initialize(size); }

    /* Please see man pages for details 
        

        
        
    
        
                        
    */
    void Initialize(size_t size);

    /* Please see man pages for details 
        

        
        
    */
    ~MemoryBlock() { Finalize(); }

    /* Please see man pages for details 
        
    */
    void Finalize();

    /* Please see man pages for details 
         

         
    */
    void SetReadOnly(bool readOnly = true);

    static size_t GetPageAlignedSize(size_t size) { return (size + NN_OS_MEMORY_PAGE_SIZE - 1) & ~(NN_OS_MEMORY_PAGE_SIZE - 1); }
};

/*
  
                

                
                
                
                
                
                
    

  
                        
  
                        
                        

  

 */
void InitializeMemoryBlock(uptr begin, size_t size);


}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
  
  
  
  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosMemoryBlock, nn::os::MemoryBlock, 20, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosMemoryBlockAllocate(nnosMemoryBlock* p, size_t size);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosMemoryBlockSetReadOnly(nnosMemoryBlock* p, bool readOnly);

/*
  
*/
NN_EXTERN_C void nnosMemoryBlockFree(nnosMemoryBlock* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosMemoryBlockGetAddress(nnosMemoryBlock* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C size_t nnosMemoryBlockGetSize(nnosMemoryBlock* p);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosMemoryBlockIsReadOnly(nnosMemoryBlock* p);

/*  



*/

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_MEMORYBLOCK_H_ */
