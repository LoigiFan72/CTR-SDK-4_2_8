/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_Lib.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50072 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_LIB_H_
#define NN_BOSS_BOSS_LIB_H_

#include <nn/os/os_Event.h>
#include <nn/fs/fs_Parameters.h>

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#include <nn/boss/boss_TaskPolicy.h>
#include <nn/boss/boss_TaskStatus.h>
#include <nn/boss/boss_TaskOption.h>
#include <nn/boss/boss_TaskError.h>
#include <nn/boss/boss_TaskAction.h>
#include <nn/boss/boss_Task.h>
#include <nn/boss/boss_TaskIdList.h>
#include <nn/boss/boss_StepIdList.h>
#include <nn/boss/boss_NsDataIdList.h>


#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  

  
  
  
  
*/
    nn::Result Initialize(void);

/* Please see man pages for details 
  

  
  
  
*/
    nn::Result Finalize(void);

/* Please see man pages for details 
  
                

                

                
                
                

                

  
  
  
  
  
                                                
                                                
  
*/
    nn::Result RegisterPrivateRootCa(const u8* pCertData, size_t certDataSize);

/* Please see man pages for details 
  
                

                

                
                
                

                

  
  
  
  
  
  
  
                                                
                                                
  
*/
    nn::Result RegisterPrivateClientCert(const u8* pCertData, size_t certDataSize
                                        , const u8* pPrivateKeyData, size_t privateKeyDataSize);

/* Please see man pages for details 
  

                
                

                
                

                  

                

                
                

                
                


  
  
  
  
                                
  
                                
  
  
  
                                                    
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
                                                    
                                                    
  
*/
    nn::Result RegisterTask(Task* pTask, TaskPolicy* pPolicy  , TaskAction* pAction
                            , TaskOption* pOption=NULL
                            , u8 taskStep=DEFAULT_STEP_ID);

/* Please see man pages for details 
  

  
  
  
  
  
                                
  
                                
  
  
  
                                                    
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
                                                    
                                                    
  
  
*/
    nn::Result RegisterTask(Task* pTask, TaskPolicy* pPolicy, TaskAction* pAction, const char* pFilePath
                            , TaskOption* pOption=NULL
                            , u8 taskStep=DEFAULT_STEP_ID);

/* Please see man pages for details 
  

                
                

                
                

                  

                

                
                

  
  
  
  
                                
  
                                
  
  
  
                                                    
  
  
  
  
  
  
  
  
  
  
                                                    
  
                                                    
                                                    
  
*/
    nn::Result RegisterImmediateTask(Task* pTask, TaskAction* pAction
                                     , TaskPolicy* pPolicy=NULL
                                     , TaskOption* pOption=NULL
                                     , u8 taskStep=DEFAULT_STEP_ID);

/* Please see man pages for details 
  

  
  
  
  
  
                                
  
                                
  
  
  
                                                    
  
  
  
  
  
  
  
  
  
  
                                                    
  
                                                    
                                                    
  
  
*/
    nn::Result RegisterImmediateTask(Task* pTask, TaskAction* pAction, const char* pFilePath
                                     , TaskPolicy* pPolicy=NULL
                                     , TaskOption* pOption=NULL
                                     , u8 taskStep=DEFAULT_STEP_ID);

/* Please see man pages for details 
  

                
                

                
                
                
                
                

  
  
                                
  
  
  
                                                
  
  
  
                                                
                                                
  

*/
    nn::Result UnregisterTask(Task* pTask, u8 taskStep=DEFAULT_STEP_ID);

/* Please see man pages for details 
  

                

  
  
  
                                
  
  
  
                                                    
  
  
  
  
  
  
  
                                                    
                                                    
  
*/
    nn::Result ReconfigureTask(Task* pTask, TaskPolicy* pPolicy, u8 taskStep=DEFAULT_STEP_ID);

/* Please see man pages for details 
  

                
                

  
  
  
  
  
                                                
                                                
  

*/
    nn::Result GetTaskIdList(TaskIdList* pTaskIdList);

/* Please see man pages for details 
  

                
                

                

  
  
  
  
  
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetStepIdList(const char* pTaskId, StepIdList* pStepIdList);

/* Please see man pages for details 
  

                
                

                
                
                

                
                

                
                
                

                
                
                
                

                
                
                
                
                

  
  
  
                                
  
  
  
  
                                                
                                                
  
*/
    nn::Result RegisterStorage(bit32 storageId, size_t storageSize, nn::boss::StorageType storageType=nn::boss::USER_EXT_SAVEDATA_STORAGE);

/* Please see man pages for details 
  

                
                

                
                
                

                
                
                
                

                
                
                

                
                
                
                

                
                
                
                
                

  
  
  
  
                                
  
  
  
  
  
*/
    nn::Result RegisterStorage(bit32 storageId, size_t storageSize, u16 entryCount, nn::boss::StorageType storageType=nn::boss::USER_EXT_SAVEDATA_STORAGE);

/* Please see man pages for details 
  

                

  
  
  
  
                                                
                                                
  
*/
    nn::Result UnregisterStorage(void);


/* Please see man pages for details 
  
                

  
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetStorageInfo(size_t* pStorageSize=NULL);

/* Please see man pages for details 
  
                

  
  
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetStorageInfo(size_t* pStorageSize, u16* pEntryCount);

/* Please see man pages for details 
  
                

                
                
                

  
  
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetNewArrivalFlag(bool* pFlag);

/* Please see man pages for details 
  

                
                
                

  
  
  
  
  
                                                
                                                
  
*/
    nn::Result RegisterNewArrivalEvent(nn::os::Event* event);

/* Please see man pages for details 
  
                
*/
    nn::Result GetNewArrivalEvent(nn::os::Event* event) NN_ATTRIBUTE_DEPRECATED;

/* Please see man pages for details 
  

                

  
  
  
  
  
                                                
                                                
  
*/
    nn::Result SetOptoutFlag(bool flag);

/* Please see man pages for details 
  

  
  
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetOptoutFlag(bool* pFlag);

/* Please see man pages for details 
  
                

                
                
                
                
                


                  

                

                
                
                

                

                
                
                

                
                
                
                
                

  
                                
  
  
  
  
                                                
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetNsDataIdList(u32 dataType, NsDataIdList* pNsDataId);

/* Please see man pages for details 
  
                

                

                
                
                
                
                

                  

                

                

  
  
  
  
  
                                                
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetOwnNsDataIdList(u32 dataType, NsDataIdList* pNsDataId);

/* Please see man pages for details 
  
                

                
                
                
                
                

                  

                

                

  
  
  
  
  
                                                
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetNewDataNsDataIdList(u32 dataType, NsDataIdList* pNsDataId);

/* Please see man pages for details 
  
                

                

                
                
                
                
                

                  

                

                

  
                                
  
  
  
  
                                                
  
  
  
  
                                                
                                                
  
*/
    nn::Result GetOwnNewDataNsDataIdList(u32 dataType, NsDataIdList* pNsDataId);


/* Please see man pages for details 
  

                

                
                
                

  
  
  
  
  
                                                
  
                                                
                                                
  
*/
    nn::Result GetErrorCode( u32* pOut, TaskResultCode targetResult );

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_LIB_H_ */
