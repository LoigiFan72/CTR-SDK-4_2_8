/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Limits.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_LIMITS_H_
#define NN_OS_OS_LIMITS_H_

#include <nn/config.h>
#if NN_PLATFORM_HAS_MMU

#include <nn/os.h>

namespace nn { namespace os { namespace detail {

    s32 GetLimitCurrentCount(LimitableResource res);
    s32 GetLimitMaxCount(LimitableResource res);

}}}

#endif  // if NN_PLATFORM_HAS_MMU
#endif /* NN_OS_OS_LIMITS_H__ */
