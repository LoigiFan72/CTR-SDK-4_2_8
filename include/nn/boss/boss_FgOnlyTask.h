/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_FgOnlyTask.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46807 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_FG_ONLY_TASK_H_
#define NN_BOSS_BOSS_FG_ONLY_TASK_H_

#include <nn/boss/boss_Task.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  

                
                
                
                
                

                

                
                
*/
class FgOnlyTask : public Task
{
public:
/* Please see man pages for details 
  
*/
    explicit FgOnlyTask(void);

/* Please see man pages for details 
  
*/
    virtual ~FgOnlyTask(void);

/* Please see man pages for details 
  

  
  
*/
    nn::Result Start(void);

/* Please see man pages for details 
  

  
  
*/
    nn::Result StartBgImmediate(void);

protected:
/* Please see man pages for details 
  

  
  
*/
    nn::Result Initialize(const char* pTaskId);
};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_FG_ONLY_TASK_H_ */
