/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_H_
#define NN_DLP_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
           
*/

#if defined(NN_PLATFORM_CTR)
    #include <nn/dlp/CTR/dlp_Type.h>
    #include <nn/dlp/CTR/dlp_Result.h>
    #include <nn/dlp/CTR/dlp_Server.h>
    #include <nn/dlp/CTR/dlp_FakeClient.h>
    #include <nn/dlp/CTR/dlp_DlpVersion.h>
    #include <nn/dlp/CTR/dlp_Common.h>

#ifdef  __cplusplus
    namespace nn {
        namespace dlp {
            using namespace nn::dlp::CTR;
        }
    }
#endif // __cplusplus

#else
    #error no platform selected
#endif

#endif  // ifndef NN_DLP_H_
