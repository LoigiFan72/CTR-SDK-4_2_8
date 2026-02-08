/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ErrorHandlerSelect.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_ERRORHANDLERSELECT_H_
#define NN_OS_OS_ERRORHANDLERSELECT_H_

#ifdef __cplusplus

#ifdef NN_PLATFORM_CTR
    #include <nn/os/CTR/os_ErrorHandler.h>

    namespace nn { namespace os { namespace detail {
        using nn::os::CTR::detail::HandleInternalError;
        using nn::os::CTR::detail::SetInternalErrorHandlingMode;
    }}}

#else
    #error NN_PROCESSOR not specified
#endif

#endif /* __cplusplus */



#ifdef NN_SWITCH_DISABLE_DEBUG_PRINT
#define NN_OS_ERROR_IF_FAILED(result)           \
    do                                          \
    {                                           \
        ::nn::Result nn_os_result = (result);   \
        if ( nn_os_result.IsFailure() )         \
        {                                       \
            ::nn::os::detail::HandleInternalError(nn_os_result); \
        }                                       \
    } while(0)

#else  /* NN_SWITCH_DISABLE_DEBUG_PRINT */
#define NN_OS_ERROR_IF_FAILED(result)           \
    do                                          \
    {                                           \
        ::nn::Result nn_os_result = (result);   \
        if ( nn_os_result.IsFailure() )         \
        {                                       \
            ::nn::os::detail::HandleInternalError(nn_os_result, NN_FILE_NAME, __LINE__); \
        }                                       \
    } while(0)

#endif /* NN_SWITCH_DISABLE_DEBUG_PRINT */


#endif /* NN_OS_OS_ERRORHANDLERSELECT_H_ */
