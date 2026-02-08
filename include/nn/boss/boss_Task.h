/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_Task.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TASK_H_
#define NN_BOSS_BOSS_TASK_H_

#include <nn/fnd/fnd_TimeSpan.h>
#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>
#include <nn/boss/boss_TaskAction.h>
#include <nn/boss/boss_TaskPolicy.h>
#include <nn/boss/boss_TaskStatus.h>
#include <nn/boss/boss_TaskError.h>
#include <nn/boss/boss_TaskOption.h>
#include <nn/boss/boss_TaskQuery.h>


#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class Task
{
public:
/* Please see man pages for details 
  
*/
    explicit Task(void);

/* Please see man pages for details 
  
*/
    virtual ~Task(void);

/* Please see man pages for details 
  

  
  
  
  
  
*/
    nn::Result Initialize(const char* pTaskId);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
*/
    inline nn::Result UpdateInterval(u32 interval){return UpdateIntervalWithSec(interval*60*60);}

/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result UpdateIntervalWithSec(u32 intervalSec);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result UpdateCount(u32 count);

/* Please see man pages for details 
  

  
*/
    inline u32 GetInterval(void)
    {
        const u32 intervalSec = GetIntervalSec();
        if(intervalSec > 0)
        {
            return (intervalSec / (60*60));
        }
        else
        {
            return 0;
        }
    }

/* Please see man pages for details 
  

  
*/
    u32 GetIntervalSec(void);

/* Please see man pages for details 
  

  
  
*/
    u32 GetCount(void);

/* Please see man pages for details 
  

                
                

  
*/
    TaskServiceStatus GetServiceStatus(void);

/* Please see man pages for details 
  

                
                
                

                
                
                
                
                
                
                
                
                
                
                
                
                
         
                
                
                
                
                
                
                
                
                
         

  
  
  
  
  
  
*/
    nn::Result Start(void);

/* Please see man pages for details 
  

                
                
                
                
                
                

  
  
  
  
  
  
*/
    nn::Result StartImmediate(void);

/* Please see man pages for details 
  

                
                
                
                
                

                
                

                
                
                
                
                
                
                
                
                
                
                
                
                
         
                
                
                
                
                
                
                
                
         

  
  
  
  
  
  
*/
    nn::Result StartBgImmediate(void);

/* Please see man pages for details 
  

                
                
                

  
  
  
  
  
  
*/
    nn::Result Cancel(void);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
  
  
*/
    nn::Result WaitFinish(const nn::fnd::TimeSpan& timeout);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
*/
    nn::Result WaitFinish(void);

/* Please see man pages for details 
  

                
                
                
                
                
                
                
                

  
                             
                             
                             
  
  
  
*/
    TaskStateCode GetState(bool acknowledge=false, u32* pCount=NULL, u8* pStepId=NULL);

/* Please see man pages for details 
  

                
                
                
                
                
                
                

  
  
  
        
*/
    u32 GetHttpStatusCode(u32* pCount=NULL, u8* pStepId=NULL);

/* Please see man pages for details 
  
                 
*/
    u32 GetCommErrorCode(u32* pCount=NULL, u8* pStepId=NULL) NN_ATTRIBUTE_DEPRECATED;

/* Please see man pages for details 
  

                
         
                
                
                  
                  
                
                  
                
                  
                  
                  
                  
                  
                
                  
                
                  
                  
                  
                  
                  
                  
         

  
  
  
*/
    TaskResultCode GetResult(u32* pCount=NULL, u8* pStepId=NULL);

/* Please see man pages for details 
  

                
                

  
  
                             
                             
                             
                             
  
  
  
  
  
  
  
  
  
*/
    nn::Result GetStateDetail(TaskStatus* pStatus, bool acknowledge=false, u8* pStepId=NULL, u8 taskStep=CURRENT_STEP_ID);

/* Please see man pages for details 
  
                 
*/
    nn::Result GetStatus(TaskStatus* pStatus, u8* pStepId=NULL, u8 taskStep=CURRENT_STEP_ID) NN_ATTRIBUTE_DEPRECATED;

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
  
  
  
*/
    nn::Result GetError(TaskError* pTaskError, u8* pStepId=NULL, u8 taskStep=CURRENT_STEP_ID);

/* Please see man pages for details 
  

                
                
                

  
  
  
  
  
  
  
  
  
  
  
  
  
*/
    nn::Result GetInfo(TaskPolicy* pPolicy, TaskAction* pAction, TaskOption* pOption, u8 taskStep=CURRENT_STEP_ID);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result GetActivePriority(TaskPriority* pPriority);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result SetQuery(TaskQuery* pQuery);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result GetQuery(TaskQuery* pQuery);

/* Please see man pages for details 
  

  
*/
    char*               GetTaskId(void);

protected:
    friend class AccessConfig;
    TaskConfig          m_Task;
private:
    bool                CheckTaskId(void);

};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_TASK_H_ */
