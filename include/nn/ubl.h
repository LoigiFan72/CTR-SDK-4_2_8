/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ubl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UBL_H_
#define NN_UBL_H_

/* Please see man pages for details 
    
           
           

           
*/

#if defined(NN_PLATFORM_CTR)

    #ifdef  __cplusplus
//nakatat
//        #include <nn/ugc/ubl_Api.h>
        #include <nn/ubl/ubl_Api.h>
    #endif // __cplusplus
#else //defined(NN_PLATFORM_CTR)
    #error no platform selected
#endif

#endif /* NN_UBL_H_ */
