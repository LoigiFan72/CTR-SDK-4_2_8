/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     egcc.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CONFIG_COMPILER_EGCC_H_
#define NN_CONFIG_COMPILER_EGCC_H_

#include <stdarg.h>

#define NN_IS_UNUSED_VAR        __attribute__((unused))
#define NN_IS_UNUSED_FUNC       __attribute__((unused))

#define NN_UNUSED_VAR(var)      ((void)&var);

#define NN_FILE_NAME            __FILE__
#define NN_FUNCTION             __PRETTY_FUNCTION__

#define NN_WEAK_SYMBOL          __weak
#define NN_ASM                  __asm

#define NN_FORCE_INLINE         __forceinline
#define NN_ATTRIBUTE_ALIGN(n)   __attribute__ ((aligned(n)))
#define NN_ATTRIBUTE_PACK       __attribute__ ((packed))

#define NN_LSYM( no )           no
#define NN_BSYM( no )           %b##no
#define NN_FSYM( no )           %f##no

#define NN_DEFINE_MODULE_ID_STRING(name, value) \
    static const char name[] __attribute__((section(".module_id"))) = (value)


#ifdef __cplusplus
namespace std
{
    using ::va_list;
}
#endif

// TORIAEZU: Shouldn't be here because it's not compiler dependent
#define NN_PADDING1             int :  8
#define NN_PADDING2             int : 16
#define NN_PADDING3             int : 24
#define NN_PADDING4             int : 32



/* NN_CONFIG_COMPILER_EGCC_H_ */
#endif
