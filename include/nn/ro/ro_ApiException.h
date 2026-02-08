/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ro_ApiException.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_RO_RO_APIEXCEPTION_H_
#define NN_RO_RO_APIEXCEPTION_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/ro/ro_Types.h>

namespace nn {
namespace ro {

    class Module;

    namespace detail
    {
        Result RegisterEit(Module* pModule);
        Result UnregisterEit(Module* pModule);
    }

} // end of namespace ro
} // end of namespace nn



#endif  // ifndef NN_RO_RO_APIEXCEPTION_H_
