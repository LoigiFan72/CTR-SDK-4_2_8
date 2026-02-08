/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_NsaDownloadAction.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46626 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_NSA_DOWNLOAD_ACTION_H_
#define NN_BOSS_BOSS_NSA_DOWNLOAD_ACTION_H_

#include <nn/boss/boss_TaskAction.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class NsaDownloadAction : public TaskAction
{
public:
/* Please see man pages for details 
  
*/
    explicit NsaDownloadAction(void);

/* Please see man pages for details 
  
*/
    virtual ~NsaDownloadAction(void);

/* Please see man pages for details 
  

                
                
                

                
                

  
  
  
  
  
*/
    nn::Result Initialize(const char* pUrl);

/* Please see man pages for details 
  

                
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result virtual SetProperty(PropertyType type, const void* pValue, size_t size);

/* Please see man pages for details 
  

                
        
        
        
        
        
        
        
        
        
        

  
  
  
  
  
  
  
  
*/
    nn::Result virtual GetProperty(PropertyType type, void* pValue, size_t size);

};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_NSA_DOWNLOAD_ACTION_H_ */

