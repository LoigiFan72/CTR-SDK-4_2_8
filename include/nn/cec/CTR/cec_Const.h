/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_Const.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47558 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_CONST_H_
#define NN_CEC_CTR_CEC_CONST_H_

#include <nn/types.h>

namespace nn {
namespace cec {
namespace CTR {

    static const u8 CEC_SIZEOF_SENDERID             = 16;
    static const u8 CEC_SIZEOF_HASH                 = 32;

    static const u8 MESSAGE_HMAC_KEYLEN             = 32;
    
    /* Please see man pages for details */
    static const s32 CEC_SIZEOF_MESSAGEID = (8);
/*
    static const size_t MESSAGE_ID_SIZE             = CEC_SIZEOF_MESSAGEID;
    static const size_t MESSAGE_HEADER_SIZE         = 128;
    static const size_t MESSAGE_ICON_SIZE           = 3200;
    static const size_t MODULE_FILTER_HEADER_SIZE   = 5; 
    static const size_t MODULE_FILTER_SIZE_MAX      = 0x10; 
*/
    /* Please see man pages for details */
    static const size_t MESSAGE_BODY_SIZE_MAX       = 96*1024; 

    //
    //

    /* Please see man pages for details 
    
                */
    static const u8 MESSAGE_SENDCOUNT_ONCE             = (0x01);

    /* Please see man pages for details 
    
                */
    static const u8 MESSAGE_SENDCOUNT_UNLIMITED        = (0xFF);

    /* Please see man pages for details 
    
                */
    static const u8 MESSAGE_PROPAGATIONCOUNT_ONCE      = (0x01);

    //

} // namespace CTR
} // namespace cec
} // namespace nn


#endif  //NN_CEC_CTR_CEC_CONST_H_

