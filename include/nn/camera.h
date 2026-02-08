/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     camera.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CAMERA_H_
#define NN_CAMERA_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
                
*/

/* Please see man pages for details 
    

    
*/


#if defined(NN_PLATFORM_CTR)
#ifdef __cplusplus
    #include <nn/camera/CTR/camera_Api.h>
    #include <nn/camera/CTR/camera_Result.h>

    namespace nn {
        namespace camera {
            using namespace nn::camera::CTR;
        }
    }
#endif  // ifdef __cplusplus
#else
    #error no platform selected
#endif

#endif  // ifndef NN_CAMERA_H_
