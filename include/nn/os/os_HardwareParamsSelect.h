/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_HardwareParamsSelect.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_HARDWAREPARAMSSELECT_H_
#define NN_OS_OS_HARDWAREPARAMSSELECT_H_


#if defined NN_PLATFORM_CTR
    #include <nn/os/CTR/os_HardwareParamsSelect.h>

    #ifdef __cplusplus
        namespace nn { namespace os {
            using namespace nn::os::CTR;
        }}
    #endif  // ifdef __cplusplus
#else
    #error platform not selected
#endif


#endif  // ifndef NN_OS_OS_HARDWAREPARAMSSELECT_H_
