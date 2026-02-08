/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     jpeg.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_JPEG_H_
#define NN_JPEG_H_

/* Please see man pages for details 
    
*/

/* Please see man pages for details 
    
                
*/

#if defined(NN_PLATFORM_CTR)

    #ifdef  __cplusplus
        #include <nn/jpeg/CTR/jpeg_MpTypes.h>
        #include <nn/jpeg/CTR/jpeg_MpDecoder.h>
        #include <nn/jpeg/CTR/jpeg_MpEncoder.h>

        namespace nn {
            namespace jpeg {
                using namespace nn::jpeg::CTR;
            }
        }
    #endif // __cplusplus

#else
    #error no platform selected
#endif

/* NN_JPEG_H_ */
#endif
