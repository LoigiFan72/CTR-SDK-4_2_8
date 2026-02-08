/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_AutoStackManager.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_AUTOSTACKMANAGER_H_
#define NN_OS_OS_AUTOSTACKMANAGER_H_

#ifdef __cplusplus

#include <nn/os/os_Mutex.h>

namespace nn { namespace os {


    /* Please see man pages for details 
        

        

        
        

        
        

        

        

        
    */
    class AutoStackManager
    {
    public:
        /* Please see man pages for details 
        
        */
        virtual ~AutoStackManager() {}



        /* Please see man pages for details 
            

            
            
            

            
            
            
            

            
            

            
            
            

            

            
        */
        virtual void* Construct(size_t stackSize) = 0;



        /* Please see man pages for details 
            

            
            
            

            
            
            

            
            
            
            
            

            
            

            
            
            
            
            
            

            
            
            
            
            
            

            
            

            
        */
        virtual void Destruct(void* pStackBottom, bool isError) = 0;
    };



}} // namespace nn::os

#endif // __cplusplus

#endif /* NN_OS_OS_AUTOSTACKMANAGER_H_ */
