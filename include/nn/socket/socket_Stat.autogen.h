/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Stat.autogen.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 
 */

#ifndef NN_SOCKET_SOCKET_STAT_AUTOGEN_H_
#define NN_SOCKET_SOCKET_STAT_AUTOGEN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Please see man pages for details 
 
 */
struct InstanceStat
{
    u64             inOctets;           //
    u32             inUcastPkts;        //
    u32             inNUcastPkts;       //
    u32             inDiscards;         //
    u32             inErrors;           //
    u32             inUnknownProtos;    //
    u32             outUcastPkts;       //
    u64             outOctets;          //
    u32             outNUcastPkts;      //
    u32             outDiscards;        //
    u32             outErrors;          //
    u32             outCollisions;      //
};


/* Please see man pages for details 
 
 */
struct IpStat
{
    u32             inReceives;         //
    u32             inHdrErrors;        //
    u32             inAddrErrors;       //
    u32             inUnknownProtos;    //
    u32             inDiscards;         //
    u32             inDelivers;         //
    u32             outRequests;        //
    u32             outDiscards;        //
    u32             outNoRoutes;        //
    u32             reasmTimeout;       //
    u32             reasmReqds;         //
    u32             reasmOKs;           //
    u32             reasmFails;         //
    u32             fragOKs;            //
    u32             fragFails;          //
    u32             fragCreates;        //
};

/* Please see man pages for details 
 
 */
struct IcmpStat
{
    u32             inMsgs;             //
    u32             inErrors;           //
    u32             inDestUnreachs;     //
    u32             inTimeExcds;        //
    u32             inParmProbs;        //
    u32             inSrcQuenchs;       //
    u32             inRedirects;        //
    u32             inEchos;            //
    u32             inEchoReps;         //
    u32             inTimestamps;       //
    u32             inTimestampReps;    //
    u32             inAddrMasks;        //
    u32             inAddrMaskReps;     //
    u32             outMsgs;            //
    u32             outErrors;          //
    u32             outDestUnreachs;    //
    u32             outTimeExcds;       //
    u32             outParmProbs;       //
    u32             outSrcQuenchs;      //
    u32             outRedirects;       //
    u32             outEchos;           //
    u32             outEchoReps;        //
    u32             outTimestamps;      //
    u32             outTimestampReps;   //
    u32             outAddrMasks;       //
    u32             outAddrMaskReps;    //
};

/* Please see man pages for details 
 
 */
struct UdpStat
{
    u32             inDatagrams;         //
    u32             inErrors;            //
    u32             noPorts;             //
    u32             outDatagrams;        //
    u32             outErrors;          //
};

/* Please see man pages for details 
 
 */
struct TcpStat
{
    u32             activeOpens;         //
    u32             passiveOpens;        //
    u32             attemptFails;        //
    u32             estabResets;         //
    u32             currEstab;           //
    u32             inSegs;              //
    u32             outSegs;             //
    u32             retransSegs;         //
    u32             inErrs;              //
    u32             outErrs;             //
    u32             outRsts;             //
};

#ifdef NN_SOCKET_IP6_ENABLE
struct Ip6Stat
{
    u32             inReceives;         //
    u32             inHdrErrors;        //
    u32             inAddrErrors;       //
    u32             inUnknownProtos;    //
    u32             inTruncatedPkts;    //
    u32             inDiscards;         //
    u32             inDelivers;         //
    u32             outRequests;        //
    u32             outDiscards;        //
    u32             outFragOKs;         //
    u32             outFragFails;       //
    u32             outFragCreates;     //
    u32             reasmReqds;         //
    u32             reasmOKs;           //
    u32             reasmFails;         //
    u32             inMcastPkts;        //
    u32             outMcastPkts;       //
};

struct Icmp6Stat
{
    u32             inMsgs;             //
    u32             inErrors;           //
    u32             inDestUnreachs;     //
    u32             inAdminProhibs;     //
    u32             inTimeExcds;        //
    u32             inParmProblems;     //
    u32             inPktTooBigs;       //
    u32             inEchos;            //
    u32             inEchoReplies;      //
    u32             inRouterSolicits;   //
    u32             inRouterAdvertisements; //
    u32             inNeighborSolicits; //
    u32             inNeighborAdvertisements; //
    u32             inRedirects;        //
    u32             inGroupMembQueries; //
    u32             inGroupMembResponses; //
    u32             inGroupMembResponsesV1; //
    u32             inGroupMembReductions; //
    u32             outMsgs;            //
    u32             outErrors;          //
    u32             outDestUnreachs;    //
    u32             outAdminProhibs;    //
    u32             outTimeExcds;       //
    u32             outParmProblems;    //
    u32             outPktTooBigs;      //
    u32             outEchos;           //
    u32             outEchoReplies;     //
    u32             outRouterSolicits;  //
    u32             outRouterAdvertisements; //
    u32             outNeighborSolicits; //
    u32             outNeighborAdvertisements; //
    u32             outRedirects;       //
    u32             outGroupMembQueries; //
    u32             outGroupMembResponses; //
    u32             outGroupMembResponsesV1; //
    u32             outGroupMembReductions; //
};
#endif

#ifdef __cplusplus
}
#endif

#endif  /* NN_SOCKET_SOCKET_STAT_AUTOGEN_H_ */
