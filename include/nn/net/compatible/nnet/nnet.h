/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nnet.h

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

#ifndef NNET_H
#define NNET_H

#include <nn/net/compatible/nos.h>            /* for NOS*** */

#ifdef  __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/

#define NNET_ERROR_BASE                          0xfff70000
#define NNET_ERROR_CODE(code)                    ((s32)(NNET_ERROR_BASE|(code)))

/* Please see man pages for details 
 
 */
enum {
    NNET_ERR_PARAM        = NNET_ERROR_CODE(1),     /* Please see man pages for details */
    NNET_ERR_EXIST        = NNET_ERROR_CODE(2),     /* Please see man pages for details */
    NNET_ERR_NOMEM        = NNET_ERROR_CODE(3),     /* Please see man pages for details */
    NNET_ERR_RECEIVE      = NNET_ERROR_CODE(4),     /* Please see man pages for details */
    NNET_ERR_SEND         = NNET_ERROR_CODE(5),     /* Please see man pages for details */
    NNET_ERR_RESOURCE     = NNET_ERROR_CODE(6),     /* Please see man pages for details */
    NNET_ERR_CANCEL       = NNET_ERROR_CODE(7),     /* Please see man pages for details */
    NNET_ERR_BUSY         = NNET_ERROR_CODE(8),     /* Please see man pages for details */
    NNET_ERR_STATE        = NNET_ERROR_CODE(9),     /* Please see man pages for details */
    NNET_ERR_NONE         = 0                       /* Please see man pages for details */
};

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/
#define NNET_TMO_WAITFOREVER    (-1L)   /* Infinite wait */

#define NNET_ETH_ALEN       6       /* MAC address length */
#define NNET_IP_ALEN        4       /* IPv4 address length */

#define NNET_MIN(a, b)   (((a) < (b)) ? (a) : (b))    /* Please see man pages for details */
#define NNET_MAX(a, b)   (((a) > (b)) ? (a) : (b))    /* Please see man pages for details */


/* Please see man pages for details 
 
 */
typedef struct NNETAllocator {
    void*    (* alloc) (u32 name, u32 size, u32 align); /* Please see man pages for details */
    void     (* free) (u32 name, void* ptr);            /* Please see man pages for details */
} NNETAllocator;

/* Please see man pages for details 
 
 */
typedef struct NNETInstance {
    struct NNETInstance *lower_ins; /* Please see man pages for details */
    s32 (* startup) (struct NNETInstance *ins, s32 timeout);    /* Please see man pages for details */
    s32 (* cleanup) (struct NNETInstance *ins, s32 timeout);    /* Please see man pages for details */
    s32 (* abort)   (struct NNETInstance *ins);                 /* Please see man pages for details */
} NNETInstance;

/* Please see man pages for details 
 
 */
typedef struct NNETConfig {
    u8 addr[NNET_IP_ALEN];      /* Please see man pages for details */
    u8 gateway[NNET_IP_ALEN];   /* Please see man pages for details */
    u8 dns1[NNET_IP_ALEN];      /* Please see man pages for details */
    u8 dns2[NNET_IP_ALEN];      /* Please see man pages for details */
    s32 mtu;                    /* Please see man pages for details */
} NNETConfig;


#define NNET_L2TYPE_ETHERNET    1   /* Please see man pages for details */
#define NNET_L2TYPE_PPP         2   /* Please see man pages for details */

/* Please see man pages for details 
 
 */
typedef struct NNETEthernetAPI {
    NNETInstance *ins;
    s32 (* eth_send) (NNETInstance *ins, u8 *dstMAC, NOSMessageBuf *mbuf);           /* Please see man pages for details */
    s32 (* eth_receive) (NNETInstance *ins, u32 receive_id, NOSMessageBuf **mbuf);   /* Please see man pages for details */
    s32 (* eth_setupper) (NNETInstance *ins, NNETInstance *upper_ins, u32 *receive_id, u16 list[]); /* Please see man pages for details */
    s32 (* eth_clearupper) (NNETInstance *ins, NNETInstance *upper_ins);             /* Please see man pages for details */
    u8  eth_type;                                                                    /* Please see man pages for details */
    s32 (* eth_getmacaddr) (NNETInstance *ins, u8 *mac);                             /* Please see man pages for details */
    s32 (* eth_setmulticast) (NNETInstance *ins, u8 *mac);                           /* Please see man pages for details */
    s32 (* eth_clearmulticast) (NNETInstance *ins, u8 *mac);                         /* Please see man pages for details */
    s32 (* eth_cancel_receive) (NNETInstance *ins, u32 receive_id);                  /* Please see man pages for details */
    s32 (* eth_getconfig) (NNETInstance *ins, NNETConfig *config);                   /* Please see man pages for details */
} NNETEthernetAPI;


/* Please see man pages for details 
 
 */
typedef struct NNETPPPAPI {
    NNETInstance *ins;
    s32 (* ppp_send) (NNETInstance *ins, NOSMessageBuf *mbuf);                       /* Please see man pages for details */
    s32 (* ppp_receive) (NNETInstance *ins, NOSMessageBuf **mbuf);                   /* Please see man pages for details */
    s32 (* ppp_setupper) (NNETInstance *ins, NNETInstance *upper_ins);               /* Please see man pages for details */
    s32 (* ppp_clearupper) (NNETInstance *ins, NNETInstance *upper_ins);             /* Please see man pages for details */
    s32 (* ppp_cancel_receive) (NNETInstance *ins);                                  /* Please see man pages for details */
} NNETPPPAPI;

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
extern NNETInstance *NNET_GetBottomIF(const NNETInstance *upper_ins);
extern NNETInstance *NNET_GetUpperIFByTop(const NNETInstance *top_ins, const NNETInstance *low_ins);
extern NNETInstance *NNET_GetLowerIF(NNETInstance *upper_ins);
extern s32 NNET_StartupIF(NNETInstance *ins, s32 timeout);
extern s32 NNET_CleanupIF(NNETInstance *ins, s32 timeout);
extern s32 NNET_AbortIF(NNETInstance *ins);

#ifdef NNET_BIG_ENDIAN
#define NNET_Swp2( _d )  d
#else
#define NNET_Swp2( _d )  ((u16)((((_d)>>8)&0x00FF)|(((_d)<<8)&0xFF00)))
#endif
extern u16 NNET_Get2( const void* ptr );
extern u16 NNET_Set2( void* ptr, u16 dat );
extern u16 NNET_And2( void* ptr, u16 dat );
extern u16 NNET_Orr2( void* ptr, u16 dat );
extern u16 NNET_Inc2( void* ptr );
extern u16 NNET_Dec2( void* ptr );
extern u16 NNET_Sub2( void* ptr, u16 dat );

extern u32 NNET_Get4( const void* ptr );
extern u32 NNET_Get4( const void* ptr );
extern u32 NNET_Set4( void* ptr, u32 dat );
extern u32 NNET_Inc4( void* ptr );
extern u32 NNET_Add4( void* ptr, u32 dat );

#include <nn/net/compatible/nnet/nnet_ring.h>


/*
    Definitions for debugging
*/
#include <nn/net/compatible/ndebug.h>

#ifdef NDEBUG_ENABLE

#define NNET_DBGASSERT(cond)  NDEBUG_Assert(cond)

#else  /* NDEBUG_ENABLE */

#define NNET_DBGASSERT(cond)

#endif  /* NDEBUG_ENABLE */


#ifdef NDEBUG_PRINT_ENABLE

extern u32 ndebug_mask_nnet;

#define NNET_DBGREPORT(level, log)         \
    do {                                  \
        if( level & ndebug_mask_nnet ) {   \
            NDEBUG_Printf ("[NNET] ");    \
            NDEBUG_Printf log;            \
            NDEBUG_Printf ("\n");         \
        }                                 \
    } while (0)

#define NNET_DBGFUNC(level, func)          \
    do {                                  \
        if( level & ndebug_mask_nnet ) {   \
            func;                         \
        }                                 \
    } while (0)

#else /* NDEBUG_PRINT_ENABLE */

#define NNET_DBGREPORT(level, log)
#define NNET_DBGFUNC(level, func)

#endif /* NDEBUG_PRINT_ENABLE */


#ifdef  __cplusplus
}
#endif

/* NNET_H */
#endif
