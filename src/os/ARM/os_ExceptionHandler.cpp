/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ExceptionHandler.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47384 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/os.h>
#include <nn/os/os_Private.h>

namespace nn {
namespace os {
namespace ARM {

    void SetUserExceptionHandler(UserExceptionHandler pHandler, uptr stackBottom)
    {
        SetUserExceptionHandler(pHandler, stackBottom, EXCEPTION_BUFFER_USE_HANDLER_STACK);
    }

    void SetUserExceptionHandler(UserExceptionHandler pHandler, uptr stackBottom,
                                    ExceptionBuffer* pExceptionBuffer)
    {
        ThreadLocalRegion* pTlr = os::detail::GetMainThreadThreadLocalRegion();
        NN_TASSERT_( pTlr != NULL );

        pTlr->handlerAddress              = reinterpret_cast<uptr>(pHandler);
        pTlr->handlerStackBottomAddress   = stackBottom;
        pTlr->exceptionBufferAddress      = reinterpret_cast<uptr>(pExceptionBuffer);
    }

    void SetUserExceptionHandlerLocal(UserExceptionHandler pHandler, uptr stackBottom,
                                        ExceptionBuffer* pExceptionBuffer)
    {
        ThreadLocalRegion* pTlr = GetThreadLocalRegion();

        pTlr->handlerAddress              = reinterpret_cast<uptr>(pHandler);
        pTlr->handlerStackBottomAddress   = stackBottom;
        pTlr->exceptionBufferAddress      = reinterpret_cast<uptr>(pExceptionBuffer);
    }



}
}
}
