/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nstd_Printf.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NSTD_PRINTF_H_
#define NN_NSTD_PRINTF_H_

#include <nn/types.h>

#ifdef __cplusplus

namespace nn { namespace nstd {

/* Please see man pages for details 
    
    
    
    
    

    
*/
s32 TVSNPrintf(char *dst, size_t len, const char *fmt, va_list vlist);

/* Please see man pages for details 
    
    
    
    
    
    
    
    

    
*/
s32 TVSNPrintf(wchar_t *dst, size_t len, const wchar_t *fmt, va_list vlist);

/* Please see man pages for details 
    
    
    
    
    

    
*/
s32 TSNPrintf(char *dst, size_t len, const char *fmt, ...);

/* Please see man pages for details 
    
    
    
    
    
    
    
    

    
*/
s32 TSNPrintf(wchar_t *dst, size_t len, const wchar_t *fmt, ...);

/* Please see man pages for details 
    
    
    
    

    
*/
s32 TSPrintf(char *dst, const char *fmt, ...);

/* Please see man pages for details 
    
    
    
    
    
    
    

    
*/
s32 TSPrintf(wchar_t *dst, const wchar_t *fmt, ...);

}}

#endif

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

NN_EXTERN_C s32 nnnstdTVSNPrintf(char *dst, size_t len, const char *fmt, va_list vlist);
NN_EXTERN_C s32 nnnstdTSNPrintf(char *dst, size_t len, const char *fmt, ...);
NN_EXTERN_C s32 nnnstdTSPrintf(char *dst, const char *fmt, ...);
NN_EXTERN_C s32 nnnstdTVSNWPrintf(wchar_t *dst, size_t len, const wchar_t *fmt, va_list vlist);
NN_EXTERN_C s32 nnnstdTSNWPrintf(wchar_t *dst, size_t len, const wchar_t *fmt, ...);
NN_EXTERN_C s32 nnnstdTSWPrintf(wchar_t *dst, const wchar_t *fmt, ...);

#endif /* NN_NSTD_PRINTF_H_ */
