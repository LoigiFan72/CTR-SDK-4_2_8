/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Common.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_COMMON_H_
#define NN_SOCKET_SOCKET_COMMON_H_

#include <nn/types.h>
#include <nn/os/os_Event.h>
#include <nn/fnd/fnd_Allocator.h>
#include <nn/socket/socket_Types.h>

namespace nn {
namespace socket {

    const char PORT_NAME_USER[]         = "soc:U";
    const char PORT_NAME_PRIVILEGED[]   = "soc:P";

    namespace detail{
        void* Allocate(size_t size, s32 alignment = sizeof(int));
        Result Allocate(void*& p, size_t size, s32 alignment = sizeof(int));
        void Free(void* p);
    }

    /* Please see man pages for details 
      

      
     */

    /* Please see man pages for details 
      
                    
      
                                
                                

      
                                
                                
                                
                                
                                
                                
                                

      
                                
                                
                                
                                
                                
                                
                                

      
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                
      
      
    */
    Result Initialize(uptr bufferAddress, size_t bufferSize, s32 bufferSizeForSockets, s32 maxSessions);


    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    
      
                                

      
      
      
    */
    size_t GetRequiredMemorySize(size_t bufferSizeForSockets, s32 maxSessions);


    /* Please see man pages for details 
      

                    
    */
    Result Initialize(nn::fnd::IAllocator& allocator, size_t bufferSize, s32 maxSessions) NN_ATTRIBUTE_DEPRECATED;

    /* Please see man pages for details 
      

                    
                    
      
      
    */
    Result Initialize(void);


    /* Please see man pages for details 
      

                    
                    
      
    */
    Result Finalize(void);


    /* Please see man pages for details 
      
      
                    

                    

      
                                            

      
    */                    
    Result InitializePrivilegedControl(bool bUseSecondarySession = false);


    /* Please see man pages for details 
      
      
                     
      
    */  
    Result FinalizePrivilegedControl(void);

    /* Please see man pages for details 
      
      
      
                    
                    
                    
                    
                    

      

      
    */  
    Result Startup(const Config& config);

    /* Please see man pages for details 
      
      
                    
                    
                    
      
                    

      
    */  
    Result Cleanup(void);

    /* Please see man pages for details 
      
      

      
    */  
    Result AbortStartup(void);

    /* Please see man pages for details 
      

      

      
     */

    Result CloseAll(void);
    Result CloseAll(bit32 processId);

    Result SetMaxDescriptor(s32 number);
    Result AllowOtherProcess(s32 s);


    /* Please see man pages for details 
      
      
      
                    

      

      
    */
    Result GetConfigError(s32* err);

    /* Please see man pages for details 
      
      

                    
                    
      
                    

      
                            

      
    */
    Result GetErrorReportEvent(nn::os::Event& event);

    /*  

*/
}
}

#endif  // ifndef NN_SOCKET_SOCKET_COMMON_H_
