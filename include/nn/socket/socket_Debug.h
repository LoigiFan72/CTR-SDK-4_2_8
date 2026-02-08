/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Debug.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_DEBUG_H_
#define NN_SOCKET_SOCKET_DEBUG_H_

#include <nn/types.h>

namespace nn {
namespace socket {

    enum DebugInfoType
    {
        DIT_IP_INFO,
        DIT_TCP_OBJ,
        DIT_UDP_OBJ
    };

    Result GetDebugInformation( s32 s, DebugInfoType type, void* pInfo, size_t len );
}
}

#endif  // ifndef NN_SOCKET_SOCKET_DEBUG_H_
