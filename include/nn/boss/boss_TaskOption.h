/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_TaskOption.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TASK_OPTION_H_
#define NN_BOSS_BOSS_TASK_OPTION_H_

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class TaskOption
{
public:
/* Please see man pages for details 
  
*/
    explicit TaskOption(void);

/* Please see man pages for details 
  
*/
    virtual ~TaskOption(void);

/* Please see man pages for details 
  
  
  
  

*/
    nn::Result Initialize(void);

/* Please see man pages for details 
  
  
  
  
  

*/
    nn::Result Initialize(ExecOption exec);

/* Please see man pages for details 
  
  
  
  
  
  
  

*/
    nn::Result SetConditional(u8 target, u32 param1, u32 param2);


/* Please see man pages for details 
  
        
        
        
  
  
  
  
  
  
  
  


*/
    nn::Result SetProperty(PropertyType type, const void* pValue, size_t size);

/* Please see man pages for details 
  
        
        
        
        
  
  
  
  
  
  
  
  


*/
    nn::Result GetProperty(PropertyType type, void* pValue, size_t size);

protected:
    friend class AccessConfig;
    TaskOptionConfig m_Option;
};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_TASK_OPTION_H_ */
