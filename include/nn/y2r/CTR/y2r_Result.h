/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     y2r_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_Y2R_Y2R_RESULT_H_
#define NN_Y2R_Y2R_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/


namespace nn {
namespace y2r {
namespace CTR {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_Y2R_IS_SLEEPING = 1
    };

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultIsSleeping,
        Result::LEVEL_STATUS, Result::SUMMARY_STATUS_CHANGED, Result::MODULE_NN_CAMERA, DESCRIPTION_Y2R_IS_SLEEPING
    );

    // For internal use
    // If sim layer's GetOutputFormatBytes function indicates that the specified format type is invalid, this error causes PANIC
    NN_DEFINE_RESULT_CONST(
        ResultInvalidEnumValue,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_INVALID_ENUM_VALUE
    );

    // For internal use
    // If the sim layer's GetOutputBlockSize function indicates that the calculation result is larger than the output buffer size, this error causes PANIC.
    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_OUT_OF_RANGE
    );

    // For internal use
    // Indicates that initialization was already performed in the process.
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_ALREADY_INITIALIZED
    );

    // For internal use
    // Indicates that it was not initialized in the process.
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_CAMERA, Result::DESCRIPTION_NOT_INITIALIZED
    );

}
}
}

#endif /* NN_Y2R_Y2R_RESULT_H_ */
