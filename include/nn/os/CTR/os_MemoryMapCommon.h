/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryMapCommon.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_CTR_OS_MEMORYMAPCOMMON_H_
#define NN_OS_CTR_OS_MEMORYMAPCOMMON_H_

#include <nn/os/os_MemoryMapSelect.h>

#define NN_OS_CONTINUOUS_TO_PHYSICAL(a) ((a) + (0x20000000 - NN_OS_ADDR_CONTINUOUS_BEGIN))
#define NN_OS_PHYSICAL_TO_CONTINUOUS(a) ((a) - (0x20000000 - NN_OS_ADDR_CONTINUOUS_BEGIN))

#endif /* NN_OS_CTR_OS_MEMORYMAPCOMMON_H_ */
