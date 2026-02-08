/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     err.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ERR_H_
#define NN_ERR_H_

/*
    
    
*/
/*
    
    
           
*/

#if defined(NN_PLATFORM_CTR)

    #ifdef  __cplusplus
        #include <nn/err/CTR/err_Api.h>

        namespace nn {
            namespace err {
                using namespace nn::err::CTR;
            }
        }
    #endif // __cplusplus

#else
    #error no platform selected
#endif

#endif  // ifndef NN_HID_H_
