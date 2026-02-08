/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     y2r.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_Y2R_H_
#define NN_Y2R_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
                
*/

#if defined(NN_PLATFORM_CTR)
#ifdef __cplusplus
    #include <nn/y2r/CTR/y2r_Api.h>
    #include <nn/y2r/CTR/y2r_Result.h>

    namespace nn {
        namespace y2r {
            using namespace nn::y2r::CTR;
        }
    }
#endif  // ifdef __cplusplus
#else
    #error no platform selected
#endif



#endif  // ifndef NN_Y2R_H_
