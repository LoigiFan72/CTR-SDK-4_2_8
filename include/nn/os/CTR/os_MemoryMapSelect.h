/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryMapSelect.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_CTR_OS_MEMORYMAPSELECT_H_
#define NN_OS_CTR_OS_MEMORYMAPSELECT_H_


#if     defined(NN_PROCESSOR_ARM_V6)
    #include <nn/os/CTR/MPCore/os_MemoryMap.h>
#elif   defined(NN_PROCESSOR_ARM_V5)
    #include <nn/os/CTR/ARM946ES/os_MemoryMap.h>
#else
    #error not implemented
#endif


#endif /* NN_OS_CTR_OS_MEMORYMAPSELECT_H_ */
