/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dsp_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DSP_CTR_DSP_RESULT_H_
#define NN_DSP_CTR_DSP_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
 */

namespace nn {
namespace dsp {
namespace CTR {

/* Please see man pages for details 
    
    
 */

/* Please see man pages for details 
    
    
 */
NN_DEFINE_RESULT_CONST(
    ResultNotInitialized,
    Result::LEVEL_STATUS,
    Result::SUMMARY_INVALID_STATE,
    Result::MODULE_NN_DSP,
    Result::DESCRIPTION_NOT_INITIALIZED
);

/* Please see man pages for details 
    
    
 */
NN_DEFINE_RESULT_CONST(
    ResultAlreadyExists,
    Result::LEVEL_STATUS,
    Result::SUMMARY_INVALID_STATE,
    Result::MODULE_NN_DSP,
    Result::DESCRIPTION_ALREADY_EXISTS
);

/*  

*/

} // namespace CTR
} // namespace dsp
} // namespace nn

#endif // NN_DSP_CTR_DSP_RESULT_H_
