/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     init_Allocator.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_INIT_INIT_ALLOCATOR_H_
#define NN_INIT_INIT_ALLOCATOR_H_

#ifdef __cplusplus

#include <nn/types.h>

namespace nn { namespace fnd {
    class IAllocator;
}}

namespace nn { namespace init {

    /* Please see man pages for details 
        

        
        

        
        
        

        
        

        
        
        
        

        
        

        

        
    */
    void InitializeAllocator(size_t size);
    
    void InitializeAllocator(uptr addr, size_t size);

    /* Please see man pages for details 
        

        
        

        
    */
    nn::fnd::IAllocator* GetAllocator(void);

}} // namespace nn::init


#endif  // ifdef __cplusplus

#endif // NN_INIT_INIT_ALLOCATOR_H_
