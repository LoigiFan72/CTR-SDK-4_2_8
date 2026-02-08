/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Entry.autogen.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_ENTRY_AUTOGEN_H_
#define NN_SOCKET_SOCKET_ENTRY_AUTOGEN_H_

#include <nn/socket/socket_User.autogen.h>	/* for NN_SOCKET_IP_ALEN, NN_SOCKET_ETH_ALEN */

namespace nn {
namespace socket {

/* Please see man pages for details 
 
 */
enum ArpState {
	ARP_STATE_INCOMPLETE              = 1, //
	ARP_STATE_REACHABLE               = 2, //
	ARP_STATE_PROBE                   = 3  //
};

/* Please see man pages for details 
 
 */
struct ArpEntry
{
    int             state;                      //
    u8              prAddr[NN_SOCKET_IP_ALEN];       //
    u8              hwAddr[NN_SOCKET_ETH_ALEN];      //
};


/* Please see man pages for details 
 
 */
struct IpAddrEntry
{
    u8              addr[NN_SOCKET_IP_ALEN];         //
    u8              netMask[NN_SOCKET_IP_ALEN];      //
    u8              bcastAddr[NN_SOCKET_IP_ALEN];    //
};

enum IpRouteFlag {
	IP_ROUTE_FLAG_G                   = 0x01,    //
	IP_ROUTE_FLAG_D                   = 0x02,    //
	IP_ROUTE_FLAG_M                   = 0x04     //
};

/* Please see man pages for details 
 
 */
struct IpRouteEntry
{
    u8           dst[NN_SOCKET_IP_ALEN];          //
    u8           netmask[NN_SOCKET_IP_ALEN];      //
    u8           gateway[NN_SOCKET_IP_ALEN];      //
    u32          flag;                       //
    s64      time;                       //
};

#ifdef NN_SOCKET_IP6_ENABLE
/* Please see man pages for details 
 
 */
struct Ip6RouteEntry
{
    u8              prefix[NN_SOCKET_IP6_ALEN];      //
    u32             prefixLen;                  //
    u32             flag;                       //
    u32             expireTime;                 //
};

/* Please see man pages for details 
 
 
 */
struct Ip6MyAddrEntry
{
    u8              addr[NN_SOCKET_IP6_ALEN];    //
    u32             preferredTime;          //
    u32             validTime;              //
    u32             state;                  //
    Bool            anycast;                //
};

/* Please see man pages for details 
 
 
 */
struct Ip6PrefixEntry
{
    u8              prefix[NN_SOCKET_IP6_ALEN];  //
    u32             prefixLen;              //
    u32             preferredTime;          //
    u32             validTime;              //
    u8              flags;                  //
};

/* Please see man pages for details 
 
 
 */
struct Ip6NeighborCacheEntry
{
    u8              addr[NN_SOCKET_IP6_ALEN];    //
    u32             state;                  //
    Bool            isRouter;               //
};

/* Please see man pages for details 
 
 
 */
struct Ip6DestinationCacheEntry
{
    u8              dst[NN_SOCKET_IP6_ALEN];     //
    u8              nextHop[NN_SOCKET_IP6_ALEN]; //
    u32             pmtu;                   //
};

/* Please see man pages for details 
 
 
 */
struct Ip6DefaultRouterEntry
{
    u8              addr[NN_SOCKET_IP6_ALEN];     //
};

#endif /* NN_SOCKET_IP6_ENABLE */

/* Please see man pages for details 
 
 */
struct UdpEntry
{
    SockAddrStorage    local;         //
    SockAddrStorage    remote;        //
};


#define TCP_STATE_CLOSED        1    //
#define TCP_STATE_LISTEN        2    //
#define TCP_STATE_SYN_SENT      3    //
#define TCP_STATE_SYN_RECEIVED  4    //
#define TCP_STATE_ESTABLISHED   5    //
#define TCP_STATE_FINWAIT1      6    //
#define TCP_STATE_FINWAIT2      7    //
#define TCP_STATE_CLOSE_WAIT    8    //
#define TCP_STATE_LAST_ACK      9    //
#define TCP_STATE_CLOSING       10   //
#define TCP_STATE_TIME_WAIT     11   //

/* Please see man pages for details 
 
 */
struct TcpEntry
{
    s32                    state;         //
    SockAddrStorage    local;         //
    SockAddrStorage    remote;        //
};


} // socket
} // nn
#endif  /* NN_SOCKET_SOCKET_ENTRY_AUTOGEN_H_ */
