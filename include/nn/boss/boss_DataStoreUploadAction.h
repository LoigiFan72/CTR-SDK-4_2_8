/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_DataStoreUploadAction.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47465 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_DATASTORE_UPLOAD_ACTION_H_
#define NN_BOSS_BOSS_DATASTORE_UPLOAD_ACTION_H_

#include <nn/Handle.h>
#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Types.h>
#include <nn/boss/boss_TaskAction.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  

                
                
                
                

                
                
                

                
                
                
                
                
                
*/
class DataStoreUploadAction : public TaskAction
{
public:
/* Please see man pages for details 
  
*/
    explicit DataStoreUploadAction(void);

/* Please see man pages for details 
  
*/
    virtual ~DataStoreUploadAction(void);

/* Please see man pages for details 
  
  
                
                  
                      
                  
                      

  
  
  
  
  
  
  
  
  
  
*/
    nn::Result Initialize(u32 gameId, const wchar_t* pAccessKey, DstKind dstKind, u16 dataType, u16 period);

/* Please see man pages for details 
  

                
                  
                

  
  
  
  
  
  
  
  
  
  
  
*/
    nn::Result Initialize(u32 gameId, const wchar_t* pAccessKey, nn::Handle fileHandle, DstKind dstKind, u16 dataType, u16 period);

/* Please see man pages for details 
  

  
*/
    u16 GetDstCount(void);

/* Please see man pages for details 
  

                
                
                

                
                

  
  
  
  
  
*/
    nn::Result AddDstPrincipalId(u32 principalId);

/* Please see man pages for details 
  

  
  
  
*/
    nn::Result ClearDstPrincipalId(void);

/* Please see man pages for details 
  

        
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    virtual nn::Result GetProperty(PropertyType type, void* pValue, size_t size);

private:
    DataStoreUploadConfig* GetConfig(void);
};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_DATASTORE_UPLOAD_ACTION_H_ */

