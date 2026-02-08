/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nwmeth.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_NETWORK_NWMETH_H
#define NN_NETWORK_NWMETH_H

#include <nnet.h>
#include <nnet/nnet_ext.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/
#define NWMETH_DEVICE_1               0           /* Only 1 interface can be used with this driver */

#define NWMETH_USE_MBUF               1

#define NWMETH_VENDOR_NINTENDO        0x0000
#define NWMETH_COMMON_CONF_VERSION    0x1100
#define NWMETH_INS_CONF_VERSION       0x2100

/* Please see man pages for details 
 
 */
#define NWMETH_ERROR_BASE                          0xffff9000
#define NWMETH_ERROR_CODE(code)                    ((s32)(NWMETH_ERROR_BASE | (code)))
enum
{
    NWMETH_ERR_PARAM = NWMETH_ERROR_CODE(1),            /* Parameter error */
    NWMETH_ERR_INIT = NWMETH_ERROR_CODE(2),             /* Cannot run because it is in initialized state */
    NWMETH_ERR_FINISH = NWMETH_ERROR_CODE(3),           /* Cannot run because it is in terminated state */
    NWMETH_ERR_CONFVER = NWMETH_ERROR_CODE(4),          /* Setting version error */
    NWMETH_ERR_STATE = NWMETH_ERROR_CODE(5),            /* State error */
    NWMETH_ERR_EXIST = NWMETH_ERROR_CODE(6),            /* Already created */
    NWMETH_ERR_NOMEM = NWMETH_ERROR_CODE(7),            /* Insufficient memory */
    NWMETH_ERR_TIMEOUT = NWMETH_ERROR_CODE(8),          /* timeout */
    NWMETH_ERR_IO = NWMETH_ERROR_CODE(9),            
    NWMETH_ERR_NONE = 0                                 /* Normal end */
};

/* Please see man pages for details 
 
 */
#define NWMETH_MEM_BASE                            0x00050000
#define NWMETH_MEM_NAME(name)                    ((s32)(NWMETH_MEM_BASE | (name)))
enum
{
    NWMETH_MEM_INSTANCE = NWMETH_MEM_NAME(1)
};

/* Please see man pages for details 
 
 */
enum
{
    NWMETH_STATE_INIT = 0,        /* Initial state */
    NWMETH_STATE_ACTIVE,          /* Connection completed state */
    NWMETH_STATE_DESTROY,
    NWMETH_STATE_ABORT            /* Connection completed state */
};

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 
 */
#define NWMETH_UPPER_NUM            2                       /* Number of upper layers   */
#define NWMETH_RXFRAME_BUFFUR_COUNT 16                      /* Size of queue to pass to upper layers */
#define NWMETH_STACK_SIZE           4096

#define NWMETH_PROTOCOL_ENTRY_MAX   16

typedef struct NWMETHQueuePair
{
    NOSMessageQueue mq;                                     /* Receive queue for upper layers */
    NOSMessage      msg[NWMETH_RXFRAME_BUFFUR_COUNT];       /* Receive queue instance for upper layers */
} NWMETHQueuePair;

typedef struct NWMETHInstance
{
    NNETInstance        netIns;                             /* Instance information common to all layers */
    NNETProtocolList    protocolList;

    NWMETHQueuePair     upper_mq[NWMETH_UPPER_NUM];          /* Receive queue for upper layers */
    s32 upper_ins_count;

    s32 state;

    u8  macaddr[NNET_ETH_ALEN];                             /* Local MAC address */
    u16 pad;

    u8  sendBuf[NNET_MAX_SEND_LEN];                         /* Send buffer */
    u8  recvBuf[NNET_MAX_RECV_LEN];                      
    NOSThread   thread;
    NOSThreadId threadId;
    u8 stack[NWMETH_STACK_SIZE];

} NWMETHInstance;

/*
    Get NNETInstance from WCM instance
*/
static inline NNETInstance* NWMETH_GetNNETInstance(NWMETHInstance* pNwmIns)
{
    return &pNwmIns->netIns;
}

/*
    Get WCM instance from NNETInstance
*/
static inline NWMETHInstance* NWMETH_GetNWMETHInstance(NNETInstance* pNetIns)
{
    return (NWMETHInstance*)pNetIns;
}

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
/* nwmeth_Main.cpp */
void* NWMETHi_Alloc(u32 name, u32 size, u32 align);
void  NWMETHi_Free(u32 name, void* ptr);

s32 NWMETH_Init(const NNETAllocator* allocator);
s32 NWMETH_Finish(void);
s32 NWMETH_GetMacAddr(NNETInstance* ins, u8* macaddr);

void NWMETHi_HandleFrame(NWMETHInstance* pNwmIns, NOSMessageBuf* mbuf);
void NWMETHi_HandleFrameRaw(NWMETHInstance* pNwmIns, const u8* pFrame, int len);

/* nwmeth_Direct.cpp */
s32 NWMETH_CreateInsDirect(NWMETHInstance** pNwmEth);
s32 NWMETH_DestroyInsDirect(NWMETHInstance* pNwmEth);
s32 NWMETH_GetUpperDirectAPI(NNETEthernetAPI* pEtherAPI, NWMETHInstance* pNwmEth);

/* nwmeth_Ipc.cpp */
s32 NWMETH_CreateIns(NWMETHInstance** pNwmEth);
s32 NWMETH_DestroyIns(NWMETHInstance* pNwmEth);
s32 NWMETH_GetUpperAPI(NNETEthernetAPI* pEtherAPI, NWMETHInstance* pNwmEth);


#ifdef  __cplusplus
}
#endif

/* NN_NETWORK_NWMETH_H */
#endif
