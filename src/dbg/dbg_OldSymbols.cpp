/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_OldSymbols.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/dbg.h>
#include <nn/os.h>
#include <cstdarg>

using namespace nn::dbg;

extern "C" 
{
    int nndbgAssertionFailureHandler(bool print, const char* filename, int lineno, const char* fmt, ...)
    {
        if (print)
        {
            va_list arg;
            va_start(arg, fmt);
            detail::TPrintf("Assertion failure at %s:%d\n  ", filename, lineno);
            detail::TVPrintf(fmt, arg);
            detail::TPrintf("\n");
            va_end(arg);
        }

        Break(BREAK_REASON_ASSERT);
        return 0;
    }
    int nndbgTAssertionFailureHandler(bool print, const char* filename, int lineno, const char* fmt, ...)
    {
        if (print)
        {
            va_list arg;
            va_start(arg, fmt);
            detail::TPrintf("Assertion failure at %s:%d\n  ", filename, lineno);
            detail::VPrintf(fmt, arg);
            detail::TPrintf("\n");
            va_end(arg);
        }

        Break(BREAK_REASON_ASSERT);
        return 0;
    }
    int nnResultFailureHandler  (nnResult result, const char* filename, int lineno, const char* fmt, ...)
    {
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        va_list arg;
        va_start(arg, fmt);
        detail::TPrintf("Assertion failure at %s:%d\n  ", filename, lineno);
        detail::TPrintf("RESULT FAILURE [%x]: ", nn::Result(result).GetPrintableBits());
        detail::VPrintf(fmt, arg);
        detail::PrintResult(result);
        va_end(arg);
#else
        NN_UNUSED_VAR(result);
        NN_UNUSED_VAR(filename);
        NN_UNUSED_VAR(lineno);
        NN_UNUSED_VAR(fmt);
#endif

        Break(BREAK_REASON_ASSERT);
        return 0;
    }
    int nnResultTFailureHandler (nnResult result, const char* filename, int lineno, const char* fmt, ...)
    {
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        va_list arg;
        va_start(arg, fmt);
        detail::TPrintf("Assertion failure at %s:%d\n  ", filename, lineno);
        detail::TPrintf("RESULT FAILURE [%x]: ", nn::Result(result).GetPrintableBits());
        detail::TVPrintf(fmt, arg);
        detail::PrintResult(result);
        va_end(arg);
#else
        NN_UNUSED_VAR(result);
        NN_UNUSED_VAR(filename);
        NN_UNUSED_VAR(lineno);
        NN_UNUSED_VAR(fmt);
#endif

        Break(BREAK_REASON_ASSERT);
        return 0;
    }
    int nnResultPanicHandler   (nnResult result, const char* filename, int lineno, const char* fmt, ...)
    {
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        va_list arg;
        va_start(arg, fmt);
        detail::TPrintf("Panic at %s:%d\n  ", filename, lineno);
        detail::TPrintf("RESULT FAILURE [%x]: ", nn::Result(result).GetPrintableBits());
        detail::VPrintf(fmt, arg);
        detail::PrintResult(result);
        va_end(arg);
#else
        NN_UNUSED_VAR(result);
        NN_UNUSED_VAR(filename);
        NN_UNUSED_VAR(lineno);
        NN_UNUSED_VAR(fmt);
#endif
        return 0;
    }
    int nnResultTPanicHandler  (nnResult result, const char* filename, int lineno, const char* fmt, ...)
    {
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        va_list arg;
        va_start(arg, fmt);
        detail::TPrintf("Panic at %s:%d\n  ", filename, lineno);
        detail::TPrintf("RESULT FAILURE [%x]: ", nn::Result(result).GetPrintableBits());
        detail::TVPrintf(fmt, arg);
        detail::PrintResult(result);
        va_end(arg);
#else
        NN_UNUSED_VAR(result);
        NN_UNUSED_VAR(filename);
        NN_UNUSED_VAR(lineno);
        NN_UNUSED_VAR(fmt);
#endif
        return 0;
    }
}

namespace nn
{
    namespace dbg
    {
        void PrintResult(nn::Result result)
        {
#ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
            detail::PrintResult(result);
#else
            NN_UNUSED_VAR(result);
#endif
        }

        void TPrintResult(nn::Result result)
        {
#ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
            detail::PrintResult(result);
#else
            NN_UNUSED_VAR(result);
#endif
        }
    }

    namespace os
    {
        namespace CTR
        {
            namespace detail
            {
                void InternalErrorHandler( Result result, const char* filename, int lineno )
                {
                    HandleInternalError(result, filename, lineno);
                }
                void InternalErrorHandler( Result result )
                {
                    HandleInternalError(result);
                }
            }
        }
    }
}
