/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Result.h

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

#ifndef NN_FND_FND_RESULT_H_
#define NN_FND_FND_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn { namespace fnd {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_INVALID_NODE                        = 1,        //
        DESCRIPTION_ALREADY_LISTED                      = 2,        //
        DESCRIPTION_OUT_OF_RANGE                        = 3,        //
        DESCRIPTION_OBSOLETE_RESULT                     = 1023      //
    };
    
    NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_FND);

    NN_DEFINE_RESULT_CONST(
        MakeResultInvalidNode,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FND, nn::fnd::DESCRIPTION_INVALID_NODE
    );
    
    NN_DEFINE_RESULT_CONST(
        MakeResultAlreadyListed,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FND, nn::fnd::DESCRIPTION_ALREADY_LISTED
    );
    
    NN_DEFINE_RESULT_CONST(
        MakeResultInvalidAddress,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FND, nn::Result::DESCRIPTION_INVALID_ADDRESS
    );

    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FND, nn::fnd::DESCRIPTION_OUT_OF_RANGE
    );
}}

#endif // __cplusplus

#endif /* NN_FND_FND_RESULT_H_ */
