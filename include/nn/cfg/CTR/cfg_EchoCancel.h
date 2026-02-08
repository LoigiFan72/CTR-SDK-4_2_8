/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_EchoCancel.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_ECHOCANCEL_H_
#define NN_CFG_CTR_CFG_ECHOCANCEL_H_

namespace nn {
namespace cfg {
namespace CTR {

/* 
    
*/
struct EchoCancelParam
{
    u8 rsv[8];
};

/* 
    
    
             
*/
nn::Result GetEchoCancelParam(EchoCancelParam* pParam);

} // end of namespace CTR
} // end of namespace cfg
} // end of namespace nn

#endif      // NN_CFG_CTR_CFG_ECHOCANCEL_H_
