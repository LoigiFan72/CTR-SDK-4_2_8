/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_TYPES_H_
#define NN_SOCKET_SOCKET_TYPES_H_

#include <nn/types.h>
#include <nn/config.h>

#pragma push
#pragma diag_suppress 1301,2530
#include <nn/socket/socket_User.autogen.h>
#include <nn/socket/socket_Entry.autogen.h>
#pragma diag_default 1301,2530 // Not needed originally
#pragma pop

namespace nn {
namespace socket {
    typedef s32             Bool;
    typedef s64             Tick;

    namespace detail {
        /* Please see man pages for details 
         
         
         */
        typedef In6Addr     InAddrStorage;

        /* Please see man pages for details 
         
         */
        struct HostEntExCarrier
        {
            s16      addrType;             /* Please see man pages for details */
            s16      length;               /* Please see man pages for details */
            s16      addrNum;              /* Please see man pages for details */
            s16      aliasNum;             /* Please see man pages for details */
            char8    name[NN_SOCKET_MAXDNAME];  /* Please see man pages for details */
            char8    aliases[NN_SOCKET_DNS_RESOLV_ALIASNAME_MAX][NN_SOCKET_MAXDNAME]; /* Please see man pages for details */
            InAddrStorage   addrList[NN_SOCKET_DNS_RESOLV_ADDRESS_MAX];      /* Please see man pages for details */
        };


        /* Please see man pages for details 
         
         */
        struct AddrInfoCarrier
        {
            s32             flags;                /* Please see man pages for details */
            s32             family;               /* Please see man pages for details */
            s32             sockType;             /* Please see man pages for details */
            s32             protocol;             /* Please see man pages for details */
            s32             addrLen;              /* Please see man pages for details */
            char8           canonName[NN_SOCKET_MAXDNAME];  /**< Canonical host name  */
            SockAddr        addr;                 /* Please see man pages for details */
        };

    } // end of namespace detail

    /* Please see man pages for details 
        
    */
    struct Config
    {
        // HOST
        InAddr      address;
        InAddr      netmask;
        InAddr      defaultRouter;
        InAddr      nameServer[2];
        // DHCP
        bool        useDhcp;
        bool        useDhcpForDns;
        s8          dhcpRetryCount;
        bool        sendDhcpRelease;

        // PHY
        s16         mtu;
        NN_PADDING2;

        // TCP
        s32         rwin;               /* Please see man pages for details */
        s32         r2;                 /* Please see man pages for details */
        // UDP
        s32         udpRecvBuff;        /* Please see man pages for details */
    };

} // end of namespace socket
} // end of namespace nn

#endif  // ifndef NN_SOCKET_SOCKET_TYPES_H_
