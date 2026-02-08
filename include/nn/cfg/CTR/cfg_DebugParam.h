/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_DebugParam.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_DEBUG_PARAM_H_
#define NN_CFG_CTR_CFG_DEBUG_PARAM_H_

/* Please see man pages for details 
    
*/

#include <nn/cfg/CTR/detail/cfg_DataStructures.h>

#ifdef __cplusplus

namespace nn {
namespace cfg {
namespace CTR {

/* Please see man pages for details 
    
    

    
*/
bool IsDlpDebug();

/* Please see man pages for details 
    
    
            
            

    
*/
bool IsDebugMode();

/* Please see man pages for details 
    
    

    
*/
u8 GetFsLatencyEmulationParam();

} // namespace CTR {
} // namespace cfg {
} // namespace nn {

#endif

#endif //   #ifndef NN_CFG_CTR_CFG_DEBUG_PARAM_H_
