/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nlib_horizon.h

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


#include <string.h>
#include <stdio.h>
#include <nn/nstd.h>
#include <nn/nstd/nstd_String.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
/*
	Prepare the following functions.
	・NLIB_memcpy
	・NLIB_memcmp
	・NLIB_memmove
	・NLIB_memset
	・NLIB_strcmp
	・NLIB_strncmp
	・NLIB_strlcmp
	・NLIB_strlen
	・NLIB_strcat
	・NLIB_strlcat
	・NLIB_strcpy
	・NLIB_strlcpy
	・NLIB_strchr
	・NLIB_strrchr
	・NLIB_strstr
	・NLIB_strnlen
	・NLIB_snprintf
	・NLIB_strtok_r
*/

#define NLIB_memcpy          nnnstdMemCpy
#define NLIB_memcmp          memcmp
#define NLIB_memmove         nnnstdMemMove
#define NLIB_memset          memset
#define NLIB_strcmp          strcmp
#define NLIB_strncmp         strncmp
#define NLIB_strlcmp         strlcmp
#define NLIB_strlen          strlen
#define NLIB_strcat          strcat
#define NLIB_strlcat         strlca
#define NLIB_strcpy          strcpy
#define NLIB_strlcpy         strlcpy
#define NLIB_strchr          strchr
#define NLIB_strrchr         strrchr
#define NLIB_strstr          strstr

int NLIB_strnlen(const char *str, int len);

#define NLIB_sprintf         nnnstdTSPrintf
#define NLIB_snprintf        nnnstdTSNPrintf
char *NLIB_strtok_r(char *str, const char *delim, char **last);	/* strtok_r function is not in TWL. Accordingly, it has been implemented separately.  */


#ifdef  __cplusplus
}
#endif
