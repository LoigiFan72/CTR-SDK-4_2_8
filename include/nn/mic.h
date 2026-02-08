/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mic.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIC_H_
#define NN_MIC_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
                
*/
/* Please see man pages for details 
    

    
  
*/
#if defined(NN_PLATFORM_CTR)
#ifdef  __cplusplus
    #include <nn/mic/CTR/mic_Result.h>
    #include <nn/mic/CTR/mic_Api.h>

    namespace nn {
        namespace mic {
            using namespace nn::mic::CTR;
        }
    }
#endif // __cplusplus
#else
    #error no platform selected
#endif

/*  

*/

#endif  // ifndef NN_MIC_H_
