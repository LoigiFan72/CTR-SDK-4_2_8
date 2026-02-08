/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ir_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47249 $
 *---------------------------------------------------------------------------*/

#ifndef NN_IR_IR_RESULT_H_
#define NN_IR_IR_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/


namespace nn {
namespace ir {
namespace CTR {

    /*
        
    */
    enum Description
    {
        DESCRIPTION_MACHINE_SLEEP = 1,      //
        DESCRIPTION_FATAL_ERROR,            //

        // Protocol
        DESCRIPTION_SIGNATURE_NOT_FOUND,    //
        DESCRIPTION_DIFFERENT_SESSIONID,    //
        DESCRIPTION_INVALID_CRC,            //
        DESCRIPTION_FOLLOWING_DATA_NOT_EXIST,   //

        // Ir module error
        DESCRIPTION_FRAMING_ERROR,          //
        DESCRIPTION_OVERRUN_ERROR,          //
        DESCRIPTION_PERFORMANCE_ERROR,      //
        DESCRIPTION_MODULE_OTHER_ERROR,     //

        // Ir library state error
        DESCRIPTION_ALREADY_CONNECTED,          //
        DESCRIPTION_ALREADY_TRYING_TO_CONNECT,  //
        DESCRIPTION_NOT_CONNECTED,              //

        // Send/Receive buffer error
        DESCRIPTION_BUFFER_FULL,            //
        DESCRIPTION_BUFFER_INSUFFICIENT,    //
        DESCRIPTION_PACKET_FULL,            //

        // Error used by other libraries
        DESCRIPTION_TIMEOUT,                //
        DESCRIPTION_PERIPHERAL,             //
        DESCRIPTION_PERIPHERAL_DATA_NOT_EXIST,   //
        DESCRIPTION_CANNOT_CONFIRM_ID,      //
        DESCRIPTION_INVALID_DATA,           //


        DESCRIPTION_END
    };

/* Please see man pages for details 
  
  
*/

    /* Basic error */

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_IR, Result::DESCRIPTION_NOT_INITIALIZED
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_IR, Result::DESCRIPTION_ALREADY_INITIALIZED
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidSize,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_IR, Result::DESCRIPTION_INVALID_SIZE
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidEnumValue,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_IR, Result::DESCRIPTION_INVALID_ENUM_VALUE
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultOutOfRange,
        Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_IR, Result::DESCRIPTION_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNoData,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_IR, Result::DESCRIPTION_NO_DATA
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultOutOfResource,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, Result::DESCRIPTION_OUT_OF_MEMORY
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultFatalError,
        Result::LEVEL_FATAL, Result::SUMMARY_INTERNAL, Result::MODULE_NN_IR, DESCRIPTION_FATAL_ERROR
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultPerformanceError,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, DESCRIPTION_PERFORMANCE_ERROR
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultFramingError,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, DESCRIPTION_FRAMING_ERROR
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultOverrunError,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, DESCRIPTION_OVERRUN_ERROR
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultModuleOtherError,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_MODULE_OTHER_ERROR
    );


/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultMachineSleep,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_MACHINE_SLEEP
    );

    /* IRNOP-releated errors */

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultSignatureNotFound,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_IR, DESCRIPTION_SIGNATURE_NOT_FOUND
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultdifferentSessionId,
        Result::LEVEL_STATUS, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_IR, DESCRIPTION_DIFFERENT_SESSIONID
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultInvalidCrc,
        Result::LEVEL_STATUS, Result::SUMMARY_WRONG_ARGUMENT, Result::MODULE_NN_IR, DESCRIPTION_INVALID_CRC
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultFollowingDataNotExist,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_IR, DESCRIPTION_FOLLOWING_DATA_NOT_EXIST
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyConnected,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_ALREADY_CONNECTED
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyTryingToConnect,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_ALREADY_TRYING_TO_CONNECT
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultNotConnected,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_NOT_CONNECTED
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultBufferFull,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, DESCRIPTION_BUFFER_FULL
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultPacketFull,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, DESCRIPTION_PACKET_FULL
    );

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultBufferInsufficient,
        Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_IR, DESCRIPTION_BUFFER_INSUFFICIENT
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultTimeout,
        Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_IR, DESCRIPTION_TIMEOUT
    );

    /* Please see man pages for details 
    
    
     */
    NN_DEFINE_RESULT_CONST(
        ResultPeripheral,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_PERIPHERAL
    );

    /* Please see man pages for details 
        
        
     */
    NN_DEFINE_RESULT_CONST(
        ResultCannotConfirmId,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_CANNOT_CONFIRM_ID
    );

    /* Please see man pages for details 
        
        
     */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidData,
        Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_IR, DESCRIPTION_CANNOT_CONFIRM_ID
    );

}
}
}

#endif /* NN_IR_IR_RESULT_H_ */
