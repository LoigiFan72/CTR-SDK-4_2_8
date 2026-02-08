/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ndm_UserControl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47766 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NDM_NDM_USERCONTROL_H_
#define NN_NDM_NDM_USERCONTROL_H_

#include <nn/ndm/CTR/ndm_Types.h>

#ifdef __cplusplus

namespace nn{
namespace ndm{
    using namespace CTR;

    namespace {
        const char PORT_NAME_USER[]         = "ndm:u";
    }
    
    /* Please see man pages for details 
      

                    
                    
                    
                    
      
    */
    Result Initialize(void);

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    
                    

      
      
    */
    Result Finalize(void);

    /* Please see man pages for details 
      

      

                    
                    

                    
                    
                    
                    

                    
                    

      
                            

      
      
      
      
      
      
    */
    Result EnterExclusiveState(ExclusiveMode mode);

    /* Please see man pages for details 
      

      
                    

      
      
      

    */
    Result QueryExclusiveMode(ExclusiveMode& mode);

    /* Please see man pages for details 
      

      

                    
                    

      
      
    */
    Result LeaveExclusiveState(void);

    /* Please see man pages for details 
      

      

                    
                    
                    

                    

      
      
    */
    Result LockState(void);

    /* Please see man pages for details 
      

      

                    

      
      
      
    */
    Result UnlockState(void);

    /* Please see man pages for details 
      

                    

      

      
      
    */
    Result SuspendDaemons(bit32 mask = CONTROL_MASK_DEFAULT);

    /* Please see man pages for details 
      
 
                    

      

      
      
    */
    Result ResumeDaemons(bit32 mask = CONTROL_MASK_DEFAULT);

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    

      

      
      
                                                    
      
    */
    Result Suspend(DaemonName name);

    /* Please see man pages for details 
      

                    
      
      

      
      
    */
    Result Resume(DaemonName name);

    /* Please see man pages for details 
      
                    
                    
                    
                    
                    
                    
                    
                    
                    

                    
                    
                    
                    
                    
                    
                    

      
                                
                                

      
      
    */
    Result SuspendScheduler(bool bAsync = false);

    /* Please see man pages for details 
      

                    
                    
                    
                    

      
      
    */
    Result ResumeScheduler(void);

    /* Please see man pages for details 
      

                    
                    

                    

                    

      
    */
    void SetupDaemonsDefault(void);

    /* Please see man pages for details 
      
                    

      
    */
    bool IsDaemonStartEnable(void);
}
}

#endif // __cplusplus

#endif // NN_NDM_NDM_USERCONTROL_H_
