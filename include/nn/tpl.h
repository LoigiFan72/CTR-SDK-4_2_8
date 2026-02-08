/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     tpl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
*/

#ifndef NN_TPL_H_
#define NN_TPL_H_

/* Please see man pages for details 
    
*/

/* Please see man pages for details 
    
                
                
*/

#if defined(NN_PLATFORM_CTR)
    #include <nn/tpl/CTR/tpl_PackagerType.h>
    #include <nn/tpl/CTR/tpl_ReadTexturePackage.h>
    
    #ifdef  __cplusplus
        namespace nn {
            namespace tpl {
                using namespace nn::tpl::CTR;
            }
        }
    #endif // __cplusplus
#else
    #error no platform selected
#endif

#endif  // ifndef NN_TPL_H_
