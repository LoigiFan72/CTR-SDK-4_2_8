/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     pl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_PL_H_
#define NN_PL_H_

#if defined(NN_PLATFORM_CTR)
/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
    

    
*/

    #ifdef  __cplusplus
    #include <nn/pl/CTR/pl_SharedFont.h>

    namespace nn { namespace pl {
        using namespace nn::pl::CTR;
    }}
    #endif
#else
    #error no platform selected
#endif

#endif  // ifndef NN_PL_H_
