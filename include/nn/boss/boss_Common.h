/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_Common.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_COMMON_H_
#define NN_BOSS_BOSS_COMMON_H_

#include <nn/Result.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

    namespace {
        /* Please see man pages for details 
         
         */
        const char PORT_NAME_USER[]           = "boss:U";
        const char PORT_NAME_PRIVILEGED[]     = "boss:P";
        const char PORT_NAME_NDM[]            = "boss:M";

    }
} // end of namespace boss
} // end of namespace nn

#endif /*__cplusplus*/

#endif /* NN_BOSS_BOSS_COMMON_H_ */
