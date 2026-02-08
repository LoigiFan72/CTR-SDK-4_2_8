/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_TaskAction.h

  Copyright (C)2009-2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47513 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TASK_ACTION_H_
#define NN_BOSS_BOSS_TASK_ACTION_H_

#include <nn/types.h>

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {


/* Please see man pages for details 
  
*/
class TaskActionBase
{
protected:
/* Please see man pages for details 
  
*/
    explicit TaskActionBase(void);

/* Please see man pages for details 
  
*/
    virtual ~TaskActionBase(void);

public:
/* Please see man pages for details 
  

                

  
  
  
*/
    nn::Result SetPrivateRootCa(void);

/* Please see man pages for details 
  

                
                
                
                

  
  
  
  
  
*/
    nn::Result SetRootCa(u32 inCaCertId);

/* Please see man pages for details 
  

  
  
  
*/
    nn::Result ClearRootCaSetting( void );

/* Please see man pages for details 
  

                

  
  
  
*/
    nn::Result SetPrivateClientCert(void);



/* Please see man pages for details 
  

                
                

  
  
  
  
  
*/
    nn::Result SetClientCert(u32 inClientCertId);


/* Please see man pages for details 
  

  
  
  
  
*/
    nn::Result SetApInfo(ApInfoType info);


/* Please see man pages for details 
  

                
                

                
                
                

  
  
  
  
*/
    nn::Result SetCfgInfo(CfgInfoType info);


/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result AddHeaderField(const char* pLabel, const char* pValue);

/* Please see man pages for details 
  

  
  
  
  
  
*/
    nn::Result SetLastModifiedTime(const char* pLastModifiedTime);

protected:
/* Please see man pages for details 
  

        
        
        
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result SetHttpProperty(PropertyType type, const void* pValue, size_t size) ;

/* Please see man pages for details 
  

        
        
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result GetHttpProperty(PropertyType type, void* pValue, size_t size) ;

/* Please see man pages for details 
  

        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result SetFileProperty(PropertyType type, const void* pValue, size_t size) ;

/* Please see man pages for details 
  

        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result GetFileProperty(PropertyType type, void* pValue, size_t size) ;


    friend class AccessConfig;
    TaskActionConfig    m_Action;
};


/* Please see man pages for details 
  
                
*/
class TaskAction : public TaskActionBase
{
public:
/* Please see man pages for details 
  
*/
    explicit TaskAction(void);

/* Please see man pages for details 
  
*/
    virtual ~TaskAction(void);

/* Please see man pages for details 
  

        
        
        
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result virtual GetProperty(PropertyType type, void* pValue, size_t size);

};


} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_TASK_ACTION_H_ */

