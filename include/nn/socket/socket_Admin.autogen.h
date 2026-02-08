/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Admin.autogen.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_ADMIN_AUTOGEN_H_
#define NN_SOCKET_SOCKET_ADMIN_AUTOGEN_H_

#ifndef NN_SOCKET_NO_DEPEND_HEADER
#include <nn/types.h>			/* for NOSxxxx */
#include <nn/net/compatible/nnet/nnet.h>			/* for NNETxxxx */
#include <nn/socket/socket_User.autogen.h>		/* for InAddr, DnsServerInfo */
#endif

namespace nn {
namespace socket {

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/

#define NN_SOCKET_VENDOR_NINTENDO        0x0000  //
#define NN_SOCKET_COMMON_CONF_VERSION    0x3100  //
#define NN_SOCKET_INS_CONF_VERSION       0x4100  //

/* Please see man pages for details 
 
 */
#define ERROR_BASE                          0xffff8000
#define ERROR_CODE(code)                    ((s32)(ERROR_BASE|(code)))

enum ErrorCode {
    ERR_PARAM          = ERROR_CODE(1),       //
    ERR_INIT           = ERROR_CODE(2),       //
    ERR_FINISH         = ERROR_CODE(3),       //
    ERR_CONFVER        = ERROR_CODE(4),       //
    ERR_STATE          = ERROR_CODE(5),       //
    ERR_EXIST          = ERROR_CODE(6),       //
    ERR_NOMEM          = ERROR_CODE(7),       //
    ERR_NOS            = ERROR_CODE(8),       //
    ERR_LOWER          = ERROR_CODE(9),       //
    ERR_TIMEOUT        = ERROR_CODE(10),      //
    ERR_INS_RESOURCES  = ERROR_CODE(11),      //
    ERR_MAXSOCKET      = ERROR_CODE(12),      //
    ERR_ABORT          = ERROR_CODE(13),      //

    ERR_IP_UNREACHABLE = ERROR_CODE(21),      //
    ERR_IP_DATASIZE    = ERROR_CODE(22),      //
    ERR_IP_NETDOWN     = ERROR_CODE(23),      //
    ERR_IP_INVALID     = ERROR_CODE(24),      //
    ERR_IP_REFUSED     = ERROR_CODE(25),      //
    ERR_IP_TIMEOUT     = ERROR_CODE(26),      //
    ERR_IP_CANCELED    = ERROR_CODE(27),      //
    ERR_IP_BUSY        = ERROR_CODE(28),      //
    ERR_IP_CLOSING     = ERROR_CODE(29),      //
    ERR_IP_EXIST       = ERROR_CODE(30),      //
    ERR_IP_RESET       = ERROR_CODE(31),      //
    ERR_IP_NOT_EXIST   = ERROR_CODE(32),      //
    ERR_IP_INV_SOCKET  = ERROR_CODE(33),      //
    ERR_IP_AGAIN       = ERROR_CODE(34),      //
    ERR_IP_SOCKET_UNSPECIFIED = ERROR_CODE(35),   //
    ERR_IP_SOURCE_QUENCH = ERROR_CODE(36),    //
    ERR_IP_INV_OPTION  = ERROR_CODE(37),      //
    ERR_IP_ADDR_COLLISION = ERROR_CODE(38),   //
    ERR_IP_SHUTDOWN    = ERROR_CODE(39),      //
    ERR_IP_INV_HEADER  = ERROR_CODE(40),      //
    ERR_IP_INV_ADDR    = ERROR_CODE(41),      //
    ERR_IP_INV_DATA    = ERROR_CODE(42),      //

    ERR_DHCP_EXPIRED   = ERROR_CODE(51),      //
    ERR_DHCP_TIMEOUT   = ERROR_CODE(52),      //
    ERR_DHCP_NAK       = ERROR_CODE(53),      //

    ERR_IP6_ADDR_COLLISION = ERROR_CODE(60),  //

    ERR_NONE           = 0                         //
};

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/
/* Please see man pages for details 
 
 */
struct CommonConfig {
    u16         vendor;             //
    u16         version;            //

    s32         timeWaitBuffer;     //

    s32         reassembleMtu;      //

    // TCP
    s32         rwin;               //
    s32         r2;                 //

    // UDP
    s32         udpRecvBuff;        //

    // DHCP
    const char* hostName;           //
    s32         rdhcp;              //

};

/*
 *Flag that sets InstanceConfig flag
 */
enum InstanceConfigFlag {
	FLAG_DHCP         =  0x0001, //
	FLAG_PPP          =  0x0002, //
	FLAG_IP4          =  0x0004, //
	FLAG_IP6          =  0x0008, //
	FLAG_DHCP6        =  0x0010, //
	FLAG_NORA_DHCP6   =  0x0020, //
	FLAG_DHCP_REBOOT  =  0x0100, //
	FLAG_DHCP_RELEASE =  0x0200, //
	FLAG_DNS_AUTO     =  0x1000, //
	FLAG_ZEROCONF     =  0x8000  //
}; 

/* Please see man pages for details 
 
 */
struct InstanceConfig {
    u16         vendor;             //
    u16         version;            //

    u32         flag;               //
    InAddr  addr;               //
    InAddr  netmask;            //
    InAddr  router;             //
    s32         mtu;                //

    DnsServerInfo dnsserver;    //

#ifdef NN_SOCKET_IP6_ENABLE
    u8          curHopLimit;     /* Hop limit */
    u32         retransTimer;    /* NS retransmission interval (msec) */
    u32         dadNSTransmits;  /* Number of NS transmissions for duplicate address detection */
    u8          interfaceId[8];  /* Interface ID */
#endif /* NN_SOCKET_IP6_ENABLE */
};

/* Please see man pages for details 
 
 */
typedef void (* ConfigErrorCallback )(InstancePtr insP, s32 err);

#ifndef NN_SOCKET_NO_DEPEND_HEADER
/* Please see man pages for details 
 
 */
typedef Bool (* Filter)(InstancePtr insP, NOSMessageBuf *mbuf);

/* Please see man pages for details 
 
 */
NN_INLINE NNETInstance *GetNNETInstance(InstancePtr insP)
{
    return (NNETInstance *)insP;
}

/* Please see man pages for details 
 
 */
NN_INLINE InstancePtr GetInstance(NNETInstance *ins)
{
    return (InstancePtr)ins;
}
#endif

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
/* nsoc_main.c */

/* nsoc_socket.c */




} // socket
} // nn
/* NN_SOCKET_SOCKET_ADMIN_AUTOGEN_H_ */
#endif


