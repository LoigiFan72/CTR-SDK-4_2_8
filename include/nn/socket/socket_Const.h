/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Const.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_CONST_H_
#define NN_SOCKET_SOCKET_CONST_H_

#include <nn/types.h>
#include <nn/socket/socket_Types.h>

namespace nn {
namespace socket {

    const size_t ETH_ALEN               = NN_SOCKET_ETH_ALEN;
    const size_t IP_ALEN                = NN_SOCKET_IP_ALEN;
    const size_t IP6_ALEN               = NN_SOCKET_IP6_ALEN;
    const size_t INET_ADDRSTRLEN        = NN_SOCKET_INET_ADDRSTRLEN;
    const size_t INET6_ADDRSTRLEN       = NN_SOCKET_INET6_ADDRSTRLEN;

    const s32 DNS_NAME_MAX              = NN_SOCKET_DNS_NAME_MAX;
    const s32 MAXDNAME                  = NN_SOCKET_MAXDNAME;
    const s32 DNS_RESOLV_ADDRESS_MAX    = NN_SOCKET_DNS_RESOLV_ADDRESS_MAX;
    const s32 DNS_RESOLV_ALIASNAME_MAX  = NN_SOCKET_DNS_RESOLV_ALIASNAME_MAX;
    const s32 DNSSERVER_NUM_MAX         = NN_SOCKET_DNSSERVER_NUM_MAX;

    const s32 SOCKET_MAX_PER_PROCESS    = 16;
    const s32 INFTIM                    = -1;
    
    namespace detail{
        const size_t    COPY_OR_MAP_THRESHOLD               = 4096*2;
        const s32       SEND_TO_MULTI_ADDRESS_ARRAY_SIZE    = 512;
        const s32       SEND_TO_MULTI_BUFFER_SIZE           = COPY_OR_MAP_THRESHOLD - SEND_TO_MULTI_ADDRESS_ARRAY_SIZE;

        // Resources required when assuming the concurrent use of DEFAULT_SOCKET_MAX number of sockets
        const size_t    DEFAULT_SOCKET_MAX                  = 10;
        // If you expect concurrent Read/Write operations, double the number of sockets
        const size_t    DEFAULT_SESSION_MAX                 = DEFAULT_SOCKET_MAX * 2;
        // Default size of the socket send/receive buffer
        const size_t    DEFAULT_SOCKET_BUFFER_SIZE          = 32768;
        // If a send/receive buffer having the default size is used, double the number of sockets for send/receive
        const size_t    DEFAULT_SOCKET_BUFFER_TOTAL_SIZE    = (DEFAULT_SOCKET_BUFFER_SIZE * 2) * DEFAULT_SOCKET_MAX;
    }

    const u8 IpAddrAny[] = {   0,   0,   0,   0 };
}
}

#endif  // ifndef NN_SOCKET_SOCKET_CONST_H_
