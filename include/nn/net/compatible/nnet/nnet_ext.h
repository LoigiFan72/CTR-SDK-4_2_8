/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nnet_ext.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NNET_EXT_H_
#define NNET_EXT_H_

#include <nn/net/compatible/nnet.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NNET_CANCEL_MESSAGE     ((void*)0xffffffff)
#define NNET_MAX_SEND_LEN       1600
#define NNET_MAX_RECV_LEN       1600

/* Please see man pages for details 
 
 */

#define NNET_PROTOCOL_NUM   8                             /* ARP, RARP, IP, PPPoE Discovery, PPPoE Session */

typedef struct NNETProtocolInfo
{
    u16               protocolId;                           /* IP, ARP, etc. */
    NNETInstance*     pUpperNetIns;                         /* Upper instance */
    u32               rxId;                                 /* identification ID when registered (user usage area) */
} NNETProtocolInfo;

typedef struct NNETProtocolList
{
    NNETProtocolInfo    protocols[NNET_PROTOCOL_NUM];
    s32                 protocol_count;
} NNETProtocolList;

typedef struct NNETEthHeader
{
    u8      dst[NNET_ETH_ALEN];
    u8      src[NNET_ETH_ALEN];
    u16     type; 
} NNETEthHeader;

#define NNET_ETH_HLEN       sizeof(NNETEthHeader)

typedef struct NNETIeeeHeader
{
    u8      dst[NNET_ETH_ALEN];
    u8      src[NNET_ETH_ALEN];
    u16     length;
	u8      dsap;      /* destination SAP type */
	u8      ssap;      /* source SAP type */
	u8      control;   /* control */
	u8      id[3];     /* ID */
	u16     type;      /* type */
} NNETIeeeHeader;

#define NNET_IEEE_HLEN       sizeof(NNETIeeeHeader)


extern const u8 NNETETHAddrBroadcast[NNET_ETH_ALEN];
extern const u8 NNETETHAddrAny[NNET_ETH_ALEN];

BOOL NNET_RegisterProtocols(NNETProtocolList* pProtocolList, const u16 protocols[], NNETInstance* pUpperNetIns, u32 rxId);
BOOL NNET_UnregisterProtocols(NNETProtocolList* pProtocolList, const NNETInstance* pUpperNetIns, u32* pRxId);
NNETProtocolInfo* NNET_GetProtocolInfo(NNETProtocolList* pProtocolList, u16 protocol);

NOSMessageBuf* NNET_ConvertFrameToMbuf(const u8* dstMac, const u8* srcMac, u16 protocol, const u8* pBody, int bodyLen, u8 tag);
s32  NNET_HandleLoopback(NNETProtocolList* pProtocolList, NOSMessageBuf* mbuf, BOOL* bContinue);
void NNET_DumpProtocolList(const NNETProtocolList* pProtocolList);
void NNET_FreeBuffersInQueue(NOSMessageQueueId mqId);

void NNET_HandleDixFrameRaw(NNETProtocolList* pProtocolList, const u8* pFrame, int len, u8 tag);
void NNET_HandleIeeeFrameRaw(NNETProtocolList* pProtocolList, const u8* pFrame, int len, u8 tag);
void NNET_HandleIeeeFrame(NNETProtocolList* pProtocolList, NOSMessageBuf* mbuf);
s32 NNET_SendPreProcess(NOSMessageBuf** ppMbuf, u16* pLength, const u8* pSrcMac, const u8* pDstMac);


#ifdef __cplusplus
}
#endif

 /* NNET_EXT_H_ */
#endif
