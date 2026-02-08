/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_H_
#define NN_CFG_H_

/* Please see man pages for details 
    
*/

/* Please see man pages for details 
    
    
                
                
                
*/

#if defined(NN_PLATFORM_CTR)
    #ifdef  __cplusplus
    #include <nn/cfg/CTR/cfg_Api.h>
    #include <nn/cfg/cfg_Result.h>

        namespace nn {
            namespace cfg {
                using namespace nn::cfg::CTR;
            }
        }
    #endif
#else
    #error no platform selected
#endif

/* Please see man pages for details 
    
    
    
*/

/*  

*/

#endif  // ifndef NN_CFG_H_
