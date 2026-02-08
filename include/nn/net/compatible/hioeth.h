/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hioeth.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_NETWORK_HIOETH_H
#define NN_NETWORK_HIOETH_H

#include <nnet.h>
#include <nnet/nnet_ext.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/
#define HIOETH_DEVICE_1               0           /* Only 1 interface can be used with this driver */

#define HIOETH_VENDOR_NINTENDO        0x0000
#define HIOETH_COMMON_CONF_VERSION    0x1100
#define HIOETH_INS_CONF_VERSION       0x2100

/* Please see man pages for details 
 
 */
#define HIOETH_ERROR_BASE                          0xffff9000
#define HIOETH_ERROR_CODE(code)                    ((s32)(HIOETH_ERROR_BASE | (code)))
enum
{
    HIOETH_ERR_PARAM = HIOETH_ERROR_CODE(1),            /* Parameter error */
    HIOETH_ERR_INIT = HIOETH_ERROR_CODE(2),             /* Cannot run because it is in initialized state */
    HIOETH_ERR_FINISH = HIOETH_ERROR_CODE(3),           /* Cannot run because it is in terminated state */
    HIOETH_ERR_CONFVER = HIOETH_ERROR_CODE(4),          /* Setting version error */
    HIOETH_ERR_STATE = HIOETH_ERROR_CODE(5),            /* State error */
    HIOETH_ERR_EXIST = HIOETH_ERROR_CODE(6),            /* Already created */
    HIOETH_ERR_NOMEM = HIOETH_ERROR_CODE(7),            /* Insufficient memory */
    HIOETH_ERR_TIMEOUT = HIOETH_ERROR_CODE(8),          /* timeout */
    HIOETH_ERR_IO = HIOETH_ERROR_CODE(8),            
    HIOETH_ERR_NONE = 0                                 /* Normal end */
};

/* Please see man pages for details 
 
 */
#define HIOETH_MEM_BASE                            0x00050000
#define HIOETH_MEM_NAME(name)                    ((s32)(HIOETH_MEM_BASE | (name)))
enum
{
    HIOETH_MEM_INSTANCE = HIOETH_MEM_NAME(1)
};

/* Please see man pages for details 
 
 */
enum
{
    HIOETH_STATE_INIT = 0,        /* Initial state */
    HIOETH_STATE_ACTIVE,          /* Connection completed state */
    HIOETH_STATE_DESTROY,
    HIOETH_STATE_ABORT            /* Connection completed state */
};

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 
 */
#define HIOETH_UPPER_NUM      2                             /* Number of upper layers   */
#define HIOETH_MQ_NUM         16                            /* Size of queue to pass to upper layers */
#define HIOETH_MAX_SEND_LEN   1600
#define HIOETH_MAX_RECV_LEN   1600
#define HIOETH_STACK_SIZE     4096

typedef struct HIOETHQueuePair
{
    NOSMessageQueue mq;                                     /* Receive queue for upper layers */
    NOSMessage      msg[HIOETH_MQ_NUM];                     /* Receive queue instance for upper layers */
} HIOETHQueuePair;

typedef struct HIOETHInstance
{
    NNETInstance        netIns;                             /* Instance information common to all layers */
    NNETProtocolList    protocolList;

    HIOETHQueuePair     upper_mq[HIOETH_UPPER_NUM];          /* Receive queue for upper layers */
    s32 upper_ins_count;

    s32 state;
    s32 handleHostToTarget;
    s32 handleTargetToHost;

    u8  macaddr[NNET_ETH_ALEN];                             /* Local MAC address */
    u16 pad;

    u8  sendBuf[HIOETH_MAX_SEND_LEN];                       /* Send buffer */
    u8  recvBuf[HIOETH_MAX_RECV_LEN];                      
    u32 recvBufPos;
    NOSThread   thread;
    NOSThreadId threadId;
    u8 stack[HIOETH_STACK_SIZE];

} HIOETHInstance;

/*
    Get NNETInstance from WCM instance
*/
static inline NNETInstance* HIOETH_GetNNETInstance(HIOETHInstance* pHioIns)
{
    return &pHioIns->netIns;
}

/*
    Get WCM instance from NNETInstance
*/
static inline HIOETHInstance* HIOETH_GetHIOETHInstance(NNETInstance* pNetIns)
{
    return (HIOETHInstance*)pNetIns;
}

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
/* HIOETH_main.c */
extern s32 HIOETH_Init(const NNETAllocator* allocator);
extern s32 HIOETH_Finish(void);
extern s32 HIOETH_StartupIns(NNETInstance* ins, s32 timeout);
extern s32 HIOETH_CleanupIns(NNETInstance* ins, s32 timeout);
extern s32 HIOETH_AbortIns(NNETInstance* ins);
extern s32 HIOETH_CreateIns(HIOETHInstance** peth_ins);
extern s32 HIOETH_DestroyIns(HIOETHInstance* peth_ins);
extern s32 HIOETH_GetStateIns(HIOETHInstance* peth_ins);
extern s32 HIOETH_GetUpperAPI(NNETEthernetAPI* wcm_api, HIOETHInstance* peth_ins);
extern s32 HIOETH_SetUpper(NNETInstance * ins, NNETInstance * upper_ins, u32* receive_id, u16 entry[]);
extern s32 HIOETH_ClearUpper(NNETInstance* ins, NNETInstance* upper_ins);
extern s32 HIOETH_GetMacAddr(NNETInstance* ins, u8* macaddr);
extern s32 HIOETH_SetMulticastAddr(NNETInstance* ins, u8* macaddr);
extern s32 HIOETH_ClearMulticastAddr(NNETInstance* ins, u8* macaddr);
extern s32 HIOETH_Send(NNETInstance* ins, u8* dstMAC, NOSMessageBuf* mbuf);
extern s32 HIOETH_Receive(NNETInstance* ins, u32 receive_id, NOSMessageBuf** mbuf);
extern s32 HIOETH_CancelReceive(NNETInstance* ins, u32 receive_id);


#ifdef  __cplusplus
}
#endif

/* NN_NETWORK_HIOETH_H */
#endif
