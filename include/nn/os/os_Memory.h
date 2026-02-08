/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Memory.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47391 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_MEMORY_H_
#define NN_OS_OS_MEMORY_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/svc.h>
#include <nn/os/CTR/os_MemoryConfig.h>

#ifdef __cplusplus

#include <nn/util/util_NonCopyable.h>
#include <nn/os/os_SvcTypes.autogen.h>
#include <nn/util/util_Result.h>


namespace nn{ namespace os{


/*
  
                

  

  
 */
void SetupHeapForMemoryBlock(size_t heapSize);




/*
  

                
                

  

 */
uptr GetDeviceMemoryAddress();



/*
  

  
                        
                        
                        

  

 */
Result SetDeviceMemorySize(size_t size);



/*
  

  

 */
size_t GetDeviceMemorySize();



/*
  

  
  

  
  
  
  

  

  
 */
uptr GetHeapAddress();



/*
  

  
  
  
  

  
                        

  

  
 */
Result SetHeapSize(size_t size);



/*
  

  
  
  
  

  

  
 */
size_t GetHeapSize();



//--------------------------------------------------------------------------- 
//
//
//
//
//
//
//--------------------------------------------------------------------------- 
uptr GetCodeRegionAddress();



//--------------------------------------------------------------------------- 
//
//
//
//
//
//
//--------------------------------------------------------------------------- 
size_t GetCodeRegionSize();



    namespace detail
    {
        inline uptr GetHeapAddressWithoutCheck()
        {
            return NN_OS_ADDR_HEAP_BEGIN;
        }
    }
}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
  
*/
NN_EXTERN_C uptr nnosGetDeviceMemoryAddress(void);

/*  

*/

/* NN_OS_MEMORY_H_ */
#endif /* NN_OS_OS_MEMORY_H_ */
