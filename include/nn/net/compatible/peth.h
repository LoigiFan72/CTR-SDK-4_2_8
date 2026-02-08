/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     peth.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NETWORK_PETH_H
#define NN_NETWORK_PETH_H

#include <nnet.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/
#define PETH_DEVICE_1               0           /* Only 1 interface can be used with this driver */

#define PETH_VENDOR_NINTENDO        0x0000
#define PETH_COMMON_CONF_VERSION    0x1100
#define PETH_INS_CONF_VERSION       0x2100

/* Please see man pages for details 
 
 */
#define PETH_ERROR_BASE                          0xffff9000
#define PETH_ERROR_CODE(code)                    ((s32)(PETH_ERROR_BASE|(code)))
enum {
    PETH_ERR_PARAM        = PETH_ERROR_CODE(1),     /* Parameter error */
    PETH_ERR_INIT         = PETH_ERROR_CODE(2),     /* Cannot run because it is in initialized state */
    PETH_ERR_FINISH       = PETH_ERROR_CODE(3),     /* Cannot run because it is in terminated state */
    PETH_ERR_CONFVER      = PETH_ERROR_CODE(4),     /* Setting version error */
    PETH_ERR_STATE        = PETH_ERROR_CODE(5),     /* State error */
    PETH_ERR_EXIST        = PETH_ERROR_CODE(6),     /* Already created */
    PETH_ERR_NOMEM        = PETH_ERROR_CODE(7),     /* Insufficient memory */
    PETH_ERR_TIMEOUT      = PETH_ERROR_CODE(8),     /* timeout */
    PETH_ERR_NONE         = 0                       /* Normal end */
};

/* Please see man pages for details 
 
 */
#define PETH_MEM_BASE                            0x00050000
#define PETH_MEM_NAME(name)                    ((s32)(PETH_MEM_BASE|(name)))
enum {
    PETH_MEM_INSTANCE = PETH_MEM_NAME(1)
};

/* Please see man pages for details 
 
 */
enum {
    PETH_STATE_INIT = 0,        /* Initial state */
    PETH_STATE_ACTIVE,          /* Connection completed state */
    PETH_STATE_ABORT            /* Connection completed state */
};

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/
#define PETH_MAC_LEN            6

/* Please see man pages for details 
 
 */
typedef struct PETHProtocolList {
    u16 protocol;                   /* IP, ARP, etc. */
    NNETInstance *upper_ins;            /* Upper instance */
    NOSMessageQueueId mq_receive;   /* Queue to insert packet when above protocol is received */
} PETHProtocolList;

/* Please see man pages for details 
 
 */
#define PETH_PROTOCOL_NUM   8   /* ARP, RARP, IP, PPPoE Discovery, PPPoE Session */
#define PETH_UPPER_NUM      2   /* Number of upper layers   */
#define PETH_MQ_NUM         16  /* Size of queue to pass to upper layers */
#define PETH_MAX_SEND_LEN   1600
typedef struct PETHMessage {
    NOSMessageQueue mq; /* Receive queue for upper layers */
    NOSMessage  mqarray[PETH_MQ_NUM];   /* Receive queue instance for upper layers */
} PETHMessage;

typedef struct PETHInstance {
    NNETInstance ins;                   /* Instance information common to all layers */

    PETHProtocolList upper_protocol[PETH_PROTOCOL_NUM]; /* Upper protocol and message queue for sending */
    s32 upper_protocol_count;

    PETHMessage upper_mq[PETH_UPPER_NUM];   /* Receive queue for upper layers */

    s32 upper_ins_count;

    s32 state;

    u8 macaddr[PETH_MAC_LEN];   /* Local MAC address */
    u16 pad;
    u8 sendBuf[PETH_MAX_SEND_LEN];  /* Send buffer */

} PETHInstance;

/*
    Get NNETInstance from WCM instance
*/
static inline NNETInstance *PETH_GetNNETInstance(PETHInstance *peth_ins)
{
    return &peth_ins->ins;
}

/*
    Get WCM instance from NNETInstance
*/
static inline PETHInstance *PETH_GetPETHInstance(NNETInstance *ins)
{
    return (PETHInstance *)ins;
}

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
/* PETH_main.c */
extern s32 PETH_Init(const NNETAllocator *allocator);
extern s32 PETH_Finish(void);
extern s32 PETH_StartupIns(NNETInstance *ins, s32 timeout);
extern s32 PETH_CleanupIns(NNETInstance *ins, s32 timeout);
extern s32 PETH_AbortIns(NNETInstance *ins);
extern s32 PETH_CreateIns(PETHInstance **peth_ins);
extern s32 PETH_DestroyIns(PETHInstance *peth_ins);
extern s32 PETH_GetStateIns(PETHInstance *peth_ins);
extern s32 PETH_GetUpperAPI(NNETEthernetAPI *wcm_api, PETHInstance *peth_ins);
extern s32 PETH_SetUpper(NNETInstance *ins, NNETInstance *upper_ins, u32 *receive_id, u16 entry[]);
extern s32 PETH_ClearUpper(NNETInstance *ins, NNETInstance *upper_ins);
extern s32 PETH_GetMacAddr(NNETInstance *ins, u8 *macaddr);
extern s32 PETH_SetMulticastAddr(NNETInstance *ins, u8 *macaddr);
extern s32 PETH_ClearMulticastAddr(NNETInstance *ins, u8 *macaddr);
extern s32 PETH_Send(NNETInstance *ins, u8 *dstMAC, NOSMessageBuf *mbuf);
extern s32 PETH_Receive(NNETInstance *ins, u32 receive_id, NOSMessageBuf **mbuf);
extern s32 PETH_CancelReceive(NNETInstance *ins, u32 receive_id);


#ifdef  __cplusplus
}
#endif

/* NN_NETWORK_PETH_H */
#endif
