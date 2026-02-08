/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_DataStoreDownloadAction.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50072 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_DATASTORE_DOWNLOAD_ACTION_H_
#define NN_BOSS_BOSS_DATASTORE_DOWNLOAD_ACTION_H_

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Types.h>
#include <nn/boss/boss_TaskAction.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  

                
                
                
                

                
                
                
                
                

*/
class DataStoreDownloadAction : public TaskAction
{
public:
/* Please see man pages for details 
  
*/
    explicit DataStoreDownloadAction(void);

/* Please see man pages for details 
  
*/
    virtual ~DataStoreDownloadAction(void);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
*/
    nn::Result Initialize(u32 gameId, const wchar_t* pAccessKey);

/* Please see man pages for details 
  
                
                
                
                

  
  
  
  
  
  
  
  
  




*/
    nn::Result SetNewsPublication(bit32 serialId, const wchar_t* pSubject, const wchar_t* pMessage, const u8 jumpParam[8]);

/* Please see man pages for details 
  

  
  
  
*/
    nn::Result ClearNewsPublication(void);

/* Please see man pages for details 
  

        
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    virtual nn::Result GetProperty(PropertyType type, void* pValue, size_t size);

private:
    DataStoreDownloadConfig* GetConfig(void);
};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_DATASTORE_DOWNLOAD_ACTION_H_ */

