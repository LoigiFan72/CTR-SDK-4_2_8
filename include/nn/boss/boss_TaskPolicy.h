/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_TaskPolicy.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TASK_POLICY_H_
#define NN_BOSS_BOSS_TASK_POLICY_H_

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class TaskPolicy
{
public:
/* Please see man pages for details 
  
*/
    explicit TaskPolicy(void);

/* Please see man pages for details 
  
*/
    virtual ~TaskPolicy(void);

/* Please see man pages for details 
  

                

  
  
  
  
  
*/
    inline nn::Result Initialize(u32 interval, u32 count){return InitializeWithSecInterval(interval*60*60, count);}

    /* Please see man pages for details 
      

      

      
      
  
  
  
    */
    nn::Result InitializeWithSecInterval(u32 intervalSec, u32 count);

/* Please see man pages for details 
  

  
  
  
  
  
  
*/
    inline nn::Result Initialize(TaskPriority priority, u32 interval, u32 count){return InitializeWithSecInterval(priority, interval*60*60, count);}

/* Please see man pages for details 
  

      

  
  
  
  
  
  
*/
    nn::Result InitializeWithSecInterval(TaskPriority priority, u32 intervalSec, u32 count);

/* Please see man pages for details 
  

  
  
  
  
  
*/
    nn::Result SetDuration(u32 duration);

/* Please see man pages for details 
  

                
                
                
                

  
  
  
  
*/
    nn::Result SetPriority(TaskPriority priority);


/* Please see man pages for details 
  

        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result SetProperty(PropertyType type, const void* pValue, size_t size);

/* Please see man pages for details 
  

        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result GetProperty(PropertyType type, void* pValue, size_t size);

protected:
    friend class AccessConfig;
    TaskPolicyConfig    m_Policy;
  private:
};

}
}

#endif

#endif /* NN_BOSS_BOSS_TASK_POLICY_H_ */
