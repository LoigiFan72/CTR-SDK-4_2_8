/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     codereset.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#if     defined(NN_EFFORT_FAST)
    #include <nn/hw/ARM/code32.h>
#elif   defined(NN_EFFORT_SMALL)
    #include <nn/hw/ARM/code16.h>
#else
    #error NN_EFFORT_* is not defined
#endif
