/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     compiler.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CONFIG_COMPILER_H_
#define NN_CONFIG_COMPILER_H_


#if     defined(__ARMCC_VERSION)
    #include <nn/config/compiler/rvct.h>
#elif   defined(__GNUC__ )
    #include <nn/config/compiler/egcc.h>
#else
    #error no compiler selected
#endif

/* NN_CONFIG_COMPILER_H_ */
#endif
