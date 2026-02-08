/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     enc_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ENC_ENC_TYPES_H_
#define NN_ENC_ENC_TYPES_H_

#ifdef __cplusplus

namespace nn { namespace enc {

    enum BreakType
    {
        BR_KEEP = 0,
        BR_CRLF,
        BR_CR,
        BR_LF
    };

}}

#endif // __cplusplus

#endif /* NN_ENC_ENC_TYPES_H_ */
