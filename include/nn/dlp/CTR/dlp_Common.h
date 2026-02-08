/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_Common.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_COMMON_H_
#define NN_DLP_CTR_DLP_COMMON_H_

#include <nn/dlp/CTR/dlp_Type.h>

#ifdef __cplusplus

namespace nn {
namespace dlp {
namespace CTR {

/*
  

  
 */

/*
    

                  

    

    
    

 */
    nn::Result  GetRebootInfo(RebootInfo* pRebootInfo);


 /*
    

                  

    
    
    

 */
    bool  IsChild();


/*!--------------------------------------------------------------------------*
    @}
 *---------------------------------------------------------------------------*/

} // namespace CTR
} // namespace dlp
} // namespace nn

#endif // __cplusplus
#endif  // ifndef NN_DLP_CTR_DLP_COMMON_H_
