/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_TaskStatus.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TASK_STATUS_H_
#define NN_BOSS_BOSS_TASK_STATUS_H_

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class TaskStatus
{
public:
/* Please see man pages for details 
  
*/
    explicit TaskStatus(void);

/* Please see man pages for details 
  
*/
    virtual ~TaskStatus(void);

/* Please see man pages for details 
  

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    Result GetProperty(PropertyType type, void* pValue, size_t size);

protected:
    friend class AccessConfig;
    NN_PADDING4;
    TaskStatusInfo      m_Status;
};





} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_TASK_STATUS_H_ */

