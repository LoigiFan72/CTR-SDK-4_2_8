/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio.h

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

#ifndef NN_HIO_H_
#define NN_HIO_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
           
*/

#if defined(NN_PLATFORM_CTR)
    #include <nn/hio/CTR/hio_Api.h>
    #include <nn/hio/CTR/hio_Result.h>
    #include <nn/hio/CTR/hio_HostDirectory.h>
    #include <nn/hio/CTR/hio_HostFile.h>
    #include <nn/hio/CTR/hio_SerialChannel.h>
    #include <nn/hio/CTR/hio_SharedMemoryChannel.h>

#ifdef  __cplusplus
    namespace nn {
        namespace hio {
            namespace CTR {}
            using namespace nn::hio::CTR;
        }
    }
#endif // __cplusplus

#else
    #error no platform selected
#endif

#endif  // ifndef NN_HIO_H_
