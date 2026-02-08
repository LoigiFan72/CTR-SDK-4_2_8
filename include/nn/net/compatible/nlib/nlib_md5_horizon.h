/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nlib_md5_horizon.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NET_COMPATIBLE_NLIB_NLIB_H_
#define NN_NET_COMPATIBLE_NLIB_NLIB_H_

/* Please see man pages for details 
 
 */

#include <nn/types.h>

#ifdef  __cplusplus
extern "C" {
#endif

/* Please see man pages for details 
 
 */
typedef struct NLIBMD5Context
{
    union
    {
        struct
        {
            unsigned long a, b, c, d;
        } p;
        unsigned long state[4];
    } x;
    unsigned long long length;
    union
    {
        unsigned long buffer32[16];
        unsigned char buffer8[64];
    } y;
} NLIBMD5Context;

/*
	Prepare the following functions.
	・Init
	・Update
	・Final
*/
void NLIB_MD5Init(NLIBMD5Context* context);
void NLIB_MD5Update(NLIBMD5Context* context, const void* input, u32 length);
void NLIB_MD5Final(u8 digest[20], NLIBMD5Context* context); 

#ifdef  __cplusplus
}
#endif

#endif
