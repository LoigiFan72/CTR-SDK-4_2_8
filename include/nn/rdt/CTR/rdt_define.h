/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_define.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49491 $
 *---------------------------------------------------------------------------*/

////#include <stdafx.h>

#ifndef NN_RDT_DEFINE_H_
#define NN_RDT_DEFINE_H_

namespace nn { namespace rdt { namespace CTR {


/* Please see man pages for details 
    
*/
enum SenderState{
    SENDER_STATE_OPEN_REQUESTED,     //
    SENDER_STATE_OPENING,            //
    SENDER_STATE_OPENED,             //
    SENDER_STATE_CLOSE_REQUESTED,    //
    SENDER_STATE_CLOSING,            //
    SENDER_STATE_CLOSED,             //
    SENDER_STATE_NOT_INITIALIZED     //
};

/* Please see man pages for details 
    
*/
enum ReceiverState{
    RECEIVER_STATE_WAITING,           //
    RECEIVER_STATE_OPENED,            //
    RECEIVER_STATE_WAITING_FINISHED,  //
    RECEIVER_STATE_FINISHED,          //
    RECEIVER_STATE_CLOSED,            //
    RECEIVER_STATE_NOT_INITIALIZED    //
};


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_DEFINE_H_
