/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ir_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_IR_CTR_IR_TYPES_H_
#define NN_IR_CTR_IR_TYPES_H_

#include <nn/fnd/fnd_TimeSpan.h>

namespace nn {
namespace ir {
namespace CTR {

    /* Delimiter, session ID, data size (1-byte or 2-byte), CRC */
    const size_t FREE_PACKET_BORDER_SIZE = 64;      //
    const size_t FREE_PACKET_HEADER_FOOTER_SIZE_UNDER_BORDER = 4;   //
    const size_t FREE_PACKET_HEADER_FOOTER_SIZE_OVER_BORDER  = 5;   //

    const size_t PAYLOAD_SIZE_MAX = 0x3FFF;     //
    const size_t NECESSARY_BUFFER_SIZE_FOR_CONNECTION = 8;  //

    const size_t CONNECTION_REQUEST_PACKET_SIZE = 8;    //
    const size_t CONNECTION_REPLY_PACKET_SIZE = 5;      //

    const size_t MANAGEMENT_BUFFER_ALLIGNMENT_SIZE = 8;     //

    /* Please see man pages for details

    */
    enum BaudRate
    {
        /*
         * Defined as constants to maintain compatibility with the previous APIs.
         * You must be careful not to change the constants when you edit them.
         */
        BAUD_RATE_115200 = 3,
        BAUD_RATE_96000 = 4,
        BAUD_RATE_72000 = 5,
        BAUD_RATE_48000 = 6,
        BAUD_RATE_36000 = 7,
        BAUD_RATE_24000 = 8,
        BAUD_RATE_18000 = 9,
        BAUD_RATE_12000 = 10,
        BAUD_RATE_9600 = 11,
        BAUD_RATE_6000 = 12,
        BAUD_RATE_3000 = 13,
        BAUD_RATE_57600 = 14,
        BAUD_RATE_38400 = 15,
        BAUD_RATE_19200 = 16,
        BAUD_RATE_7200  = 17,
        BAUD_RATE_4800  = 18
    };



    /* Please see man pages for details

    */
    enum ConnectionStatus
    {
        CONNECTION_STATUS_STOPPED,              //
        CONNECTION_STATUS_TRYING_TO_CONNECT,    //
        CONNECTION_STATUS_CONNECTED,            //
        CONNECTION_STATUS_DISCONNECTING,        //
        CONNECTION_STATUS_FATAL_ERROR           //
    };

    /* Please see man pages for details

    */
    enum TryingToConnectStatus
    {
        TRYING_TO_CONNECT_STATUS_NONE,              //
        TRYING_TO_CONNECT_STATUS_SENDING_REQUEST,   //
        TRYING_TO_CONNECT_STATUS_WAITING_REPLY,     //
        TRYING_TO_CONNECT_STATUS_WAITING_REQUEST,   //
        TRYING_TO_CONNECT_STATUS_SENDING_REPLY      //
    };

    /* Please see man pages for details

    */
    enum MachineId
    {
        MACHINE_ID_CTR = 0x00       //
    };

    /* Please see man pages for details

    */
    enum ConnectionRole
    {
        CONNECTION_ROLE_NONE,       //
        CONNECTION_ROLE_TO_REQUIRE, //
        CONNECTION_ROLE_TO_WAIT      //
    };
}
}
}

#endif  //NN_IR_CTR_IR_TYPES_H_

