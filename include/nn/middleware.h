/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     middleware.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47706 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIDDLEWARE_H_
#define NN_MIDDLEWARE_H_

#include <nn/config.h>
#include <nn/util/detail/util_Symbol.h>

#define NN_MAKE_MIDDLEWARE_STRING(vender, module)   \
    "[SDK+" vender ":" module "]"

#define NN_DEFINE_MIDDLEWARE(name, vender, module)  \
    static NN_DEFINE_MODULE_ID_STRING(name, NN_MAKE_MIDDLEWARE_STRING(vender, module))

#define NN_USING_MIDDLEWARE(name)                   \
    NN_UTIL_REFER_SYMBOL(name)


#endif /* NN_MIDDLEWARE_H_ */
