/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ndebug_horizon.h

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


#ifndef NDEBUG_HORIZON_H
#define NDEBUG_HORIZON_H

#include <nn/dbg.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef NN_BUILD_VERBOSE
/*
	If TWL_DEBUG=TRUE is specified at compile time, this is enabled.
*/

#define NDEBUG_ENABLE	/* Please see man pages for details */
#define NDEBUG_PRINT_ENABLE

#define NDEBUG_Printf	NN_TLOG_    /* Please see man pages for details */
#define NDEBUG_Assert(...)	NN_TASSERT_(__VA_ARGS__)    /* Please see man pages for details */

extern void NDEBUG_Dump(const void *ptr, s32 len);   /* Please see man pages for details */

#else

#undef NDEBUG_ENABLE
/*
	If TWL_DEBUG=TRUE is not specified at compile time, this is enabled.
	The following functions and functions surrounded by NDEBUG_ENABLE become disabled.
*/

#define NDEBUG_Printf(...)
#define NDEBUG_Assert(cond)
#define NDEBUG_Dump(ptr, len)

#endif

#ifdef  __cplusplus
}
#endif

/* NDEBUG_HORIZON_H */
#endif
