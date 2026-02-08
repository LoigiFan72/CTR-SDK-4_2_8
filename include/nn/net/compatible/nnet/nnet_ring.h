/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nnet_ring.h

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

#ifndef __NNET_RING_H__
#define __NNET_RING_H__

#include <nn/net/compatible/nos.h>    /* for NOSMessageBuf */

#ifdef __cplusplus
extern "C" {
#endif

/* Please see man pages for details 
 
 */
typedef struct NNETBlock {
    u8*   ptr;    /* Please see man pages for details */
    s32   len;    /* Please see man pages for details */
} NNETBlock;

/* Please see man pages for details 
 
 */
typedef struct NNETVec {
    void* data;    /* Please see man pages for details */
    s32   len;     /* Please see man pages for details */
} NNETVec;

u8*   NNET_RingIn ( u8* buf, s32 size, u8* head, s32 used, const u8* data, s32 len );
u8*   NNET_RingInMbuf ( u8* buf, s32 size, u8* head, s32 used, NOSMessageBuf *mbuf, s32 len );
u8*   NNET_RingInExMbuf( u8* buf, s32 size, u8* head, s32 used, s32 offset, NOSMessageBuf *mbuf, s32* plen, NNETBlock* blocks, s32 maxblock );
u8*   NNET_RingOut( u8* buf, s32 size, u8* head, s32 used, u8* data, s32 len );
int NNET_RingGet(u8* buf, s32 size, u8* head, s32 used, NNETVec* vec, s32 len);
int NNET_RingGetMbuf(u8* buf, s32 size, u8* head, s32 used, NOSMessageBuf *mbuf, s32 len);
u8*   NNET_RingPut( u8* buf, s32 size, u8* head, s32 used, s32 len );

#ifdef __cplusplus
}
#endif

#endif  /* __NNET_RING_H__ */
