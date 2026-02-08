/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ExceptionHandlerSelect.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47384 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_EXCEPTIONHANDLERSELECT_H_
#define NN_OS_OS_EXCEPTIONHANDLERSELECT_H_

#ifdef __cplusplus

#ifdef NN_PROCESSOR_ARM
    #include <nn/os/ARM/os_ExceptionHandler.h>

    namespace nn { namespace os {
        using namespace nn::os::ARM;
    }}

#else
    #error NN_PROCESSOR not specified
#endif

#endif

#endif /* NN_OS_OS_EXCEPTIONHANDLERSELECT_H_ */
