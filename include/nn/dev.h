/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dev.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/*  
    

    
*/

#ifndef NN_DEV_H_
#define NN_DEV_H_

/*  
    
*/
/*
    
    
           
*/

#if defined(NN_PLATFORM_CTR)
    #include <nn/dev/CTR/dev_Api.h>

#ifdef  __cplusplus
    namespace nn {
        namespace dev {
            using namespace nn::dev::CTR;
        }
    }
#endif // __cplusplus

#else
    #error no platform selected
#endif

#endif  // ifndef NN_DEV_H_
