/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mic_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIC_MIC_RESULT_H_
#define NN_MIC_MIC_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/


namespace nn {
namespace mic {
namespace CTR {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_MIC_SHELL_CLOSE = 1
    };

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
    
    
    
           
           
           


*/
    NN_DEFINE_RESULT_CONST(
        ResultShellClose,
        Result::LEVEL_STATUS, Result::SUMMARY_STATUS_CHANGED, Result::MODULE_NN_MIC, DESCRIPTION_MIC_SHELL_CLOSE
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_MIC, Result::DESCRIPTION_NOT_INITIALIZED
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_MIC, Result::DESCRIPTION_ALREADY_INITIALIZED
    );
/* Please see man pages for details 
    
    
    
           

*/
    NN_DEFINE_RESULT_CONST(
        ResultUsingOtherProcess,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_MIC, Result::DESCRIPTION_ALREADY_INITIALIZED
    );
/* Please see man pages for details 
    
    
    
           

*/
    NN_DEFINE_RESULT_CONST(
        ResultBusy,
        Result::LEVEL_STATUS, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_MIC, Result::DESCRIPTION_BUSY
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMisalignedSize,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_MIC, Result::DESCRIPTION_MISALIGNED_SIZE
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMisalignedAddress,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_MIC, Result::DESCRIPTION_MISALIGNED_ADDRESS
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultOutOfMemory,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_MIC, Result::DESCRIPTION_OUT_OF_MEMORY
    );

    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_MIC, Result::DESCRIPTION_OUT_OF_RANGE
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidSize,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_MIC, Result::DESCRIPTION_INVALID_SIZE
    );
/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidHandle,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_MIC, Result::DESCRIPTION_INVALID_HANDLE
    );

}
}
}

#endif /* NN_MIC_MIC_RESULT_H_ */
