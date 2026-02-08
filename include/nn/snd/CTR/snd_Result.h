/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_CTR_SND_RESULT_H_
#define NN_SND_CTR_SND_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
 */

namespace nn {
namespace snd {
namespace CTR {

/* Please see man pages for details 
    
 */
enum Description
{
    DESCRIPTION_SND_NO_DSP_COMPONENT_LOADED = 1
};

/* Please see man pages for details 
    
    
 */

/* Please see man pages for details 
    
    
 */
NN_DEFINE_RESULT_CONST(
    ResultAlreadyInitialized,
    Result::LEVEL_INFO,
    Result::SUMMARY_NOTHING_HAPPENED,
    Result::MODULE_NN_SND,
    Result::DESCRIPTION_ALREADY_INITIALIZED
);

/* Please see man pages for details 
    
    
 */
NN_DEFINE_RESULT_CONST(
    ResultNoDspComponentLoaded,
    Result::LEVEL_STATUS,
    Result::SUMMARY_INVALID_STATE,
    Result::MODULE_NN_SND,
    DESCRIPTION_SND_NO_DSP_COMPONENT_LOADED
);

/* Please see man pages for details 
    
    
 */
NN_DEFINE_RESULT_CONST(
    ResultInvalidUsage,
    Result::LEVEL_USAGE,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_SND,
    Result::DESCRIPTION_INVALID_COMBINATION
);

/*  

*/

} // namespace CTR
} // namespace snd
} // namespace nn

#endif // NN_SND_CTR_SND_RESULT_H_
