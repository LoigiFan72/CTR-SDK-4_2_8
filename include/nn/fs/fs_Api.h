/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_API_H_
#define NN_FS_FS_API_H_

#include <nn/Result.h>
#include <nn/os.h>

namespace nn {
namespace fs {

//----------------------------------------
//
//

/* Please see man pages for details 
    

            
*/
void  Initialize();
bool  IsInitialized();

//

//----------------------------------------
//
//
/* Please see man pages for details 
    

           

    

    
    
    
*/
Result SetPriority( s32 priority );

/* Please see man pages for details 
    
    
    

    

    
    
    
*/
Result GetPriority( s32 *pOut );
//

//----------------------------------------
//
//

/* Please see man pages for details 
    

            

    
*/
void RegisterSdmcInsertedEvent(nn::os::LightEvent* p);

/* Please see man pages for details 
    
*/
void UnregisterSdmcInsertedEvent();

/* Please see man pages for details 
    

    
*/
void RegisterSdmcEjectedEvent(nn::os::LightEvent* p);

/* Please see man pages for details 
    
*/
void UnregisterSdmcEjectedEvent();

/* Please see man pages for details 
    

            
            

            

    
*/
bool IsSdmcInserted();

/* Please see man pages for details 
    

            

    
*/
bool IsSdmcWritable();

/* Please see man pages for details 
    

    
    

    
    
    
                                
    
*/

Result GetSdmcSize( s64* pTotal, s64* pFree );

/* Please see man pages for details 
    
                
                

                
                
                

    

    
    
    
    
                                        
    
    
    
    
*/
Result MountSdmcWriteOnly(const char* archiveName = "sdmcwo:");

//

}
}

#endif /* NN_FS_FS_API_H_ */
