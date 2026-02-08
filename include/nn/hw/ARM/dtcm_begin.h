/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dtcm_begin.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

//
// include this instead of using C99 pragma extensions for compatibility
//
#if	defined(__CC_ARM)
#pragma arm section rodata=".dtcm", rwdata=".dtcm", zidata=".dtcm.bss"

#elif	defined(__MWERKS__)
#include <nn/section.h>
#pragma section DTCM begin

#elif	defined(__GNUC__)
TO BE   DEFINED
#endif
