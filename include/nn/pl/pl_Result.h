/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     pl_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47250 $
 *---------------------------------------------------------------------------*/

#ifndef NN_PL_CTR_PL_RESULT_H_
#define NN_PL_CTR_PL_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn {
namespace pl {

enum Description
{
    DESCRIPTION_SHAREDFONT_NOT_FOUND    = 2,
    DESCRIPTION_GAMECOIN_DATA_RESET     = 100,  //
    DESCRIPTION_LACK_OF_GAMECOIN        = 101   //
};

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultSharedFontNotFound,
    Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_PL, DESCRIPTION_SHAREDFONT_NOT_FOUND
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultGameCoinDataReset,
    Result::LEVEL_SUCCESS,
    Result::SUMMARY_SUCCESS,
    Result::MODULE_NN_PL,
    DESCRIPTION_GAMECOIN_DATA_RESET
);

/* Please see man pages for details 
    
    
*/
NN_DEFINE_RESULT_CONST(
    ResultLackOfGameCoin,
    Result::LEVEL_STATUS,
    Result::SUMMARY_INVALID_STATE,
    Result::MODULE_NN_PL,
    DESCRIPTION_LACK_OF_GAMECOIN
);

} // end of namespace pl
} // end of namespace nn

#endif // #ifdef __cplusplus
#endif // #ifndef NN_PL_CTR_PL_RESULT_H_
