/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     err_Exception.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ERR_CTR_ERR_EXCEPTION_H_
#define NN_ERR_CTR_ERR_EXCEPTION_H_

#include <nn/os.h>

namespace nn {
namespace err {
namespace CTR {

    void ThrowException( nn::os::ExceptionInfo* pei, nn::os::ExceptionContext* pec );
    void ThrowResultFailureMessage( Result result, const char* message );

    void SetupExceptionHandler( void );
    //void SetupResultHandler( void );      // Move to err_Api.h

    const char* GetExceptionTypeString(nn::os::ExceptionType type);
    const char* GetAbortTypeString(bit32 fs);

#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
    void PrintGeneralRegisterInfo( const nn::os::ExceptionContext& ec );
    void PrintAbortStatus( uptr fa, bit32 fs );
    void PrintException(const nn::os::ExceptionInfo& ei, const nn::os::ExceptionContext& ec);
#endif

}}} // nn::err::CTR

#endif // NN_ERR_CTR_ERR_EXCEPTION_H_
