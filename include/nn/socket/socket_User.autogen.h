/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_User.autogen.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_USER_AUTOGEN_H_
#define NN_SOCKET_SOCKET_USER_AUTOGEN_H_

#include <nn/types.h>	/* for NOSxxxx */

namespace nn {
namespace socket {

//#undef NN_SOCKET_IP6_ENABLE     //!< Use IPv6


/* Please see man pages for details 
 
 */
enum ProtocolFamily {
	PF_UNSPEC  = 0,           //
	PF_INET    = 2,           //
	PF_INET6   = 23           //
};

/* Please see man pages for details 
 
 */
enum AddressFamily {
	AF_UNSPEC  = PF_UNSPEC,   //
	AF_INET    = PF_INET,     //
	AF_INET6   = PF_INET6     //
};

/* Please see man pages for details 
 
 */
enum SocketType {
	SOCK_STREAM    = 1,           //
	SOCK_DGRAM     = 2            //
};

/* Please see man pages for details 
 
 */
enum MessageFlag {
	MSG_OOB        = 0x01,        //
	MSG_PEEK       = 0x02,        //
	MSG_DONTWAIT   = 0x04         //
};

/* Please see man pages for details 
 
 */
enum PollType {
	POLLRDNORM     = 0x0001,     //
	POLLRDBAND     = 0x0002,     //
	POLLPRI        = 0x0004,     //
	POLLWRNORM     = 0x0008,     //
	POLLWRBAND     = 0x0010,     //
	POLLERR        = 0x0020,     //
	POLLHUP        = 0x0040,     //
	POLLNVAL       = 0x0080,     //
	POLLIN         = (POLLRDNORM | POLLRDBAND), //
	POLLOUT        = POLLWRNORM //
};

/* Please see man pages for details 
 
 */
enum SocketLevel {
	SOL_SOCKET     = 0xffff,      //
	SOL_CONFIG     = 0xfffe,      //
	SOL_IP         = 0,           //
	SOL_ICMP       = 1,           //
	SOL_TCP        = 6,           //
	SOL_UDP        = 17,          //
	SOL_IP6        = 41           //
};

/* Please see man pages for details 
 
 */
enum SocketOptionType {
	IP_TOS             = 0x00000007, //
	IP_TTL             = 0x00000008, //
	IP_MULTICAST_LOOP  = 0x00000009, //
	IP_MULTICAST_TTL   = 0x0000000a, //
	IP_ADD_MEMBERSHIP  = 0x0000000b, //
	IP_DROP_MEMBERSHIP = 0x0000000c, //
	SO_REUSEADDR       = 0x00000004, //
	SO_LINGER          = 0x00000080, //
	SO_OOBINLINE       = 0x00000100, //
	SO_SNDBUF          = 0x00001001, //
	SO_RCVBUF          = 0x00001002, //
	SO_SNDLOWAT        = 0x00001003, //
	SO_RCVLOWAT        = 0x00001004, //
	SO_TYPE            = 0x00001008, //
	SO_ERROR           = 0x00001009, //
	TCP_NODELAY        = 0x00002001, //
	TCP_MAXSEG         = 0x00002002, //
	TCP_STDURG         = 0x00002003, //
	TCP_R2             = 0x00002004, //
	TCP_R2_SYN         = 0x00002005  //
#ifdef NN_SOCKET_IP6_ENABLE
	,
	IP6_MULTICAST_LOOP = 0x00010009, //
	IP6_HOPLIMIT       = 0x0001000a, //
	IP6_ADD_MEMBERSHIP = 0x0001000b, //
	IP6_DROP_MEMBERSHIP= 0x0001000c  //
#endif
};

/* Please see man pages for details 
 
 */
enum ShutdownType {
	SHUT_RD        = 0,           //
	SHUT_WR        = 1,           //
	SHUT_RDWR      = 2            //
};

/* Please see man pages for details 
 
 */
enum FcntlFlag {
	F_GETFL        = 3,            //
	F_SETFL        = 4             //
};

/* Please see man pages for details 
 
 */
enum FcntlOperation {
	O_NONBLOCK     = 0x04          //
};

/* Please see man pages for details 
 
 */
enum AddrInfoType {
	AI_PASSIVE     = 0x01,         //
	AI_CANONNAME   = 0x02,         //
	AI_NUMERICHOST = 0x04,         //
	AI_NUMERICSERV = 0x08          //
};

/* Please see man pages for details 
 
 */
enum NameInfoType {
	NI_NOFQDN      = 0x01,         //
	NI_NUMERICHOST = 0x02,         //
	NI_NAMEREQD    = 0x04,         //
	NI_NUMERICSERV = 0x08,         //
	NI_DGRAM       = 0x10          //
};

/* Please see man pages for details 
 
 */
enum AddrInfoError {
	EAI_BADFLAGS   = -301,         //
	EAI_FAIL       = -302,         //
	EAI_FAMILY     = -303,         //
	EAI_MEMORY     = -304,         //
	EAI_NONAME     = -305,         //
	EAI_SOCKTYPE   = -307,         //
	EAI_SYSTEM     = -308          //
};

/* Please see man pages for details 
 
 */
enum RRsetError {
	ERRSET_NONAME  = -350,
	ERRSET_NODATA  = -351,
	ERRSET_NOMEMORY= -352,         //
	ERRSET_INVAL   = -353,         //
	ERRSET_FAIL    = -354
};

/* Please see man pages for details 
 
 */
enum SocketError {
	E2BIG          = -1,
	EACCES         = -2,     //
	EADDRINUSE     = -3,     //
	EADDRNOTAVAIL  = -4,     //
	EAFNOSUPPORT   = -5,     //
	EAGAIN         = -6,     //
	EALREADY       = -7,
	EBADF          = -8,     //
	EBADMSG        = -9,
	EBUSY          = -10,
	ECANCELED      = -11,
	ECHILD         = -12,
	ECONNABORTED   = -13,    //
	ECONNREFUSED   = -14,    //
	ECONNRESET     = -15,    //
	EDEADLK        = -16,
	EDESTADDRREQ   = -17,    //
	EDOM           = -18,
	EDQUOT         = -19,
	EEXIST         = -20,
	EFAULT         = -21,
	EFBIG          = -22,
	EHOSTUNREACH   = -23,
	EIDRM          = -24,
	EILSEQ         = -25,
	EINPROGRESS    = -26,    //
	EINTR          = -27,    //
	EINVAL         = -28,    //
	EIO            = -29,    //
	EISCONN        = -30,    //
	EISDIR         = -31,
	ELOOP          = -32,
	EMFILE         = -33,    //
	EMLINK         = -34,
	EMSGSIZE       = -35,    //
	EMULTIHOP      = -36,
	ENAMETOOLONG   = -37,
	ENETDOWN       = -38,    //
	ENETRESET      = -39,    //
	ENETUNREACH    = -40,    //
	ENFILE         = -41,
	ENOBUFS        = -42,    //
	ENODATA        = -43,
	ENODEV         = -44,
	ENOENT         = -45,
	ENOEXEC        = -46,
	ENOLCK         = -47,
	ENOLINK        = -48,
	ENOMEM         = -49,    //
	ENOMSG         = -50,
	ENOPROTOOPT    = -51,    //
	ENOSPC         = -52,
	ENOSR          = -53,
	ENOSTR         = -54,
	ENOSYS         = -55,
	ENOTCONN       = -56,    //
	ENOTDIR        = -57,
	ENOTEMPTY      = -58,
	ENOTSOCK       = -59,
	ENOTSUP        = -60,
	ENOTTY         = -61,
	ENXIO          = -62,
	EOPNOTSUPP     = -63,    //
	EOVERFLOW      = -64,
	EPERM          = -65,
	EPIPE          = -66,
	EPROTO         = -67,
	EPROTONOSUPPORT= -68,    //
	EPROTOTYPE     = -69,    //
	ERANGE         = -70,
	EROFS          = -71,
	ESPIPE         = -72,
	ESRCH          = -73,
	ESTALE         = -74,
	ETIME          = -75,
	ETIMEDOUT      = -76,    //
	ETXTBSY        = -77,
	EWOULDBLOCK    = EAGAIN,   //
	EXDEV          = -78
};

/* Please see man pages for details 
 
 */
enum InstanceOptionType {
	CONFIG_FILTER_INPUT                   =  0x1001,    //
	CONFIG_FILTER_OUTPUT                  =  0x1002,    //
	CONFIG_ERROR                          =  0x1003,    //
	CONFIG_MAC_ADDRESS                    =  0x1004,    //
	CONFIG_LINK_STATE                     =  0x1005,    //
	CONFIG_INTERFACE_STATISTICS           =  0x1006,    //
	CONFIG_MUTE                           =  0x1007,    //
	CONFIG_ARP_NUMBER                     =  0x3001,    //
	CONFIG_ARP_TABLE                      =  0x3002,    //
	CONFIG_ARP_REFRESH                    =  0x3003,    //
	CONFIG_ARP_ADD                        =  0x3004,    //
	CONFIG_ARP_REMOVE                     =  0x3005,    //
	CONFIG_IP_STATISTICS                  =  0x4001,    //
	CONFIG_IP_ADDR_NUMBER                 =  0x4002,    //
	CONFIG_IP_ADDR_TABLE                  =  0x4003,    //
	CONFIG_IP_MTU                         =  0x4004,    //
	CONFIG_IP_ROUTING_NUMBER              =  0x4005,    //
	CONFIG_IP_ROUTING_TABLE               =  0x4006,    //
	CONFIG_IP_ADD_ROUTE                   =  0x4007,    //
	CONFIG_IP_REMOVE_ROUTE                =  0x4008,    //
	CONFIG_IP_ADDR                        =  0x400a,    //
	CONFIG_IP_GATEWAY                     =  0x400b,    //
	CONFIG_IP_NETMASK                     =  0x400c,    //
	CONFIG_IP_REFRESH_ROUTE               =  0x400d,    //
	CONFIG_ICMP_STATISTICS                =  0x5001,    //
#ifdef NN_SOCKET_IP6_ENABLE
	CONFIG_IP6_STATISTICS                 =  0x6001,    //
	CONFIG_IP6_MTU                        =  0x6002,    //
	CONFIG_IP6_PREFIX_NUMBER              =  0x6003,    //
	CONFIG_IP6_PREFIX_TABLE               =  0x6004,    //
	CONFIG_IP6_ADD_ROUTE                  =  0x6005,    //
	CONFIG_IP6_REMOVE_ROUTE               =  0x6006,    //
	CONFIG_IP6_ADD_ADDRESS                =  0x6007,    //
	CONFIG_IP6_REMOVE_ADDRESS             =  0x6008,    //
	CONFIG_IP6_HOPLIMIT                   =  0x6009,    //
	CONFIG_IP6_RETRANSMIT_TIMER           =  0x600a,    //
	CONFIG_IP6_DUP_ADDR_DETECT_TRANSMITS  =  0x600b,    //
	CONFIG_IP6_INTERFACE_ID               =  0x600c,    //
	CONFIG_IP6_DESTINATION_CACHE_NUMBER   =  0x600d,    //
	CONFIG_IP6_DESTINATION_CACHE_TABLE    =  0x600e,    //
	CONFIG_IP6_ADDR_NUMBER                =  0x600f,    //
	CONFIG_IP6_ADDR_TABLE                 =  0x6010,    //
	CONFIG_IP6_ROUTE_NUMBER               =  0x6011,    //
	CONFIG_IP6_ROUTE_TABLE                =  0x6012,    //
	CONFIG_IP6_NEIGHBOR_CACHE_NUMBER      =  0x6013,    //
	CONFIG_IP6_NEIGHBOR_CACHE_TABLE       =  0x6014,    //
	CONFIG_IP6_DEFAULT_ROUTER_NUMBER      =  0x6015,    //
	CONFIG_IP6_DEFAULT_ROUTER_TABLE       =  0x6016,    //
	CONFIG_IP6_ADD_PREFIX                 =  0x6017,    //
	CONFIG_IP6_REMOVE_PREFIX              =  0x6018,    //
	CONFIG_ICMP6_STATISTICS               =  0x7001,    //
#endif /* NN_SOCKET_IP6_ENABLE */
	CONFIG_UDP_STATISTICS                 =  0x8001,    //
	CONFIG_UDP_NUMBER                     =  0x8002,    //
	CONFIG_UDP_TABLE                      =  0x8003,    //
	CONFIG_TCP_STATISTICS                 =  0x9001,    //
	CONFIG_TCP_NUMBER                     =  0x9002,    //
	CONFIG_TCP_TABLE                      =  0x9003,    //
	CONFIG_TCP_MSL                        =  0x9006,    //
	CONFIG_TCP_RTO_MIN                    =  0x9007,    //
	CONFIG_TCP_RTO_MAX                    =  0x9008,    //
	CONFIG_TCP_RTO_DEFAULT                =  0x9009,    //
	CONFIG_IGMP_MODE                      =  0xA001,    //
	CONFIG_DNS_DOMAIN_NAME                =  0xB001,    //
	CONFIG_DNS_SERVER_NUMBER              =  0xB002,    //
	CONFIG_DNS_SERVER_TABLE               =  0xB003,    //
	CONFIG_DHCP_REMAINING_LEASE_TIME      =  0xC001     //
};

/* Please see man pages for details 
 
 */
enum InstanceState {
    STATE_INIT = 0,        //
    STATE_WAIT_LINKUP,     //
    STATE_ACTIVE,          //
    STATE_MORIBUND         //
};

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 
 */
typedef void * InstancePtr; 
  
/*
 * Address length
 */
#define NN_SOCKET_ETH_ALEN           6       //
#define NN_SOCKET_IP_ALEN            4       //
#define NN_SOCKET_IP6_ALEN           16      //

/* Please see man pages for details 
 
 
 
 
 
 
 */
#define NN_SOCKET_INET_ADDRSTRLEN    16
#define NN_SOCKET_INET6_ADDRSTRLEN   46

/* Please see man pages for details 
 
 */
#define NN_SOCKET_INADDR_ANY           ((u32) 0x00000000)  //

struct InAddr
{
    u32         addr;   //
};

/* Please see man pages for details 
 
 */
struct SockAddrIn
{
    u8          len;            //
    u8          family;         //
    u16         port;           //
    InAddr  addr;           //
};

/* Please see man pages for details 
 
 */
struct In6Addr
{
    u8         addr[NN_SOCKET_IP6_ALEN];    //
};

/* Please see man pages for details 
 
 */
struct SockAddrIn6
{
    u8          len;            //
    u8          family;         //
    u16         port;           //
    In6Addr addr;           //
    u32         flowInfo;       //
    u32         scopeId;        //
};

/* Please see man pages for details 
 
 */
struct SockAddr
{
    u8          len;            //
    u8          family;         //
    u16         pad1;           //
    u32         pad2[6];        //
};

/* Please see man pages for details 
 
 */
struct SockAddrStorage
{
    u8          len;            //
    u8          family;         //
    u16         pad1;           //
    u32         pad2[6];        //
};

/* Please see man pages for details 
 
 */
struct Linger
{
    int         onoff;          //
    int         linger;         //
};

/* Please see man pages for details 
 
 */
struct IpMreq
{
   InAddr     multiaddr;      //
   InAddr     interface;      //
};

/* Please see man pages for details 
 
 */
struct Ip6Mreq
{
   u32            scopeId;                  //
   u8             maddr[NN_SOCKET_IP6_ALEN];     //
   u8             filterType;               //
   u32            srcNum;                   //
   u8             srcList[NN_SOCKET_IP6_ALEN];   //
};

enum IP6MreqType {
	IP6MREQ_INCLUDE = 0,   //
	IP6MREQ_EXCLUDE = 1    //
};

/* Please see man pages for details 
 
 */
struct PollFd
{
    int         fd;             //
    int         events;         //
    int         revents;        //
};



/* Please see man pages for details 
 
 */
struct AddrInfo
{
    int             flags;         //
    int             family;        //
    int             sockType;      //
    int             protocol;      //
    unsigned        addrLen;       //
    char*           canonName;     //
    void*           addr;          //
    AddrInfo*   next;          //
};

struct RDataInfo {
    u32 length;
    u8 *data;
};

/* Please see man pages for details 
 
 */
struct RRSetInfo {
    u16 rdClass;
    u16 rdType;
    u32 ttl;
    u32 nrDatas;
    char *name;
    RDataInfo *rDatas;
};

/* Please see man pages for details 
 
 */
struct HostEnt
{
    char*       name;           //
    char**      aliases;        //
    s16         addrType;       //
    s16         length;         //
    u8**        addrList;       //
};


/* Please see man pages for details 
 
 */
struct DnsAddr {
    int af;                 //
    u8 addr[NN_SOCKET_IP6_ALEN];  //
};

/* Please see man pages for details 
 
 */
#define NN_SOCKET_DNSSERVER_NUM_MAX          4      //
#define NN_SOCKET_DOMAIN_NAME_LEN_MAX        255
struct DnsServerInfo {
    DnsAddr entry[NN_SOCKET_DNSSERVER_NUM_MAX];         //

    char domain[NN_SOCKET_DOMAIN_NAME_LEN_MAX + 1];        //

};

#define NN_SOCKET_DNS_NAME_MAX               255 //
#define NN_SOCKET_MAXDNAME                   (NN_SOCKET_DNS_NAME_MAX + 1) //
#define NN_SOCKET_DNS_RESOLV_ADDRESS_MAX     24  //
#define NN_SOCKET_DNS_RESOLV_ALIASNAME_MAX   24  //

/*
 * Definitions for well-known address initialization
 */
#define NN_SOCKET_IN6ADDR_UNSPECIFIED_INIT               {0}
#define NN_SOCKET_IN6ADDR_LOOPBACK_INIT                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
#define NN_SOCKET_IN6ADDR_LINKLOCAL_ALL_NODES_INIT       {0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
#define NN_SOCKET_IN6ADDR_LINKLOCAL_ALL_ROUTERS_INIT     {0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,2}
#define NN_SOCKET_IN6ADDR_MULTICAST_SOLICITED_NODE_INIT  {0xff,0x02,0,0,0,0,0,0,0,0,0,0x01,0xff,0,0,0}
#define NN_SOCKET_IN6ADDR_LINKLOCAL_UNICAST_INIT         {0xfe,0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define NN_SOCKET_IN6ADDR_MULTICAST_ALL_ROUTERS_INIT     {0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,16}

#ifdef SWITCH_SO_ENDIAN_BIG
// Big Endian environment
#define NN_SOCKET_NtoHl(netlong)        ((u32) (netlong))
#define NN_SOCKET_NtoHs(netshort)       ((u16) (netshort))
#define NN_SOCKET_HtoNl(hostlong)       ((u32) (hostlong))
#define NN_SOCKET_HtoNs(hostshort)      ((u16) (hostshort))

#else
// Little Endian environment
/* Please see man pages for details 
 
 */
#define NN_SOCKET_NtoHl(netlong)        ( (u32)( (((u32)(netlong)>>24)&0x000000FF) | (((u32)(netlong)>> 8)&0x0000FF00) | (((u32)(netlong)<< 8)&0x00FF0000) | (((u32)(netlong)<<24)&0xFF000000) ) )

/* Please see man pages for details 
 
 */
#define NN_SOCKET_NtoHs(netshort)       ( (u16)( (((u16)(netshort)>>8)&0x00FF) | (((u16)(netshort)<<8)&0xFF00) ) )

/* Please see man pages for details 
 
 */
#define NN_SOCKET_HtoNl(hostlong)       ( (u32)( (((u32)(hostlong)>>24)&0x000000FF) | (((u32)(hostlong)>> 8)&0x0000FF00) | (((u32)(hostlong)<< 8)&0x00FF0000) | (((u32)(hostlong)<<24)&0xFF000000) ) )

/* Please see man pages for details 
 
 */
#define NN_SOCKET_HtoNs(hostshort)      ( (u16)( (((u16)(hostshort)>>8)&0x00FF) | (((u16)(hostshort)<<8)&0xFF00) ) )

#endif

/* Please see man pages for details 
 
 */
/* nsoc_socket.c */

/* nsoc_dns.c */

/* nsoc_inet.c */
#ifdef NN_SOCKET_IP6_ENABLE
#endif

/* nsoc_main.c */

/* nsoc_state.c */




} // socket
} // nn
/* NN_SOCKET_SOCKET_USER_AUTOGEN_H_ */
#endif
