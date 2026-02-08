/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Break.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48011 $
 *---------------------------------------------------------------------------*/

#include <nn/Result.h>
#include <nn/dbg/dbg_Break.h>
#include <nn/dbg/dbg_DebugString.h>
#include <nn/svc.h>
#include <nn/config.h>
#include <cstdarg>

using namespace nn::dbg;

namespace
{
    nn::dbg::BreakHandler  s_pBreakHandler = NULL;

    void PrintErrorMessageHeader(nndbgBreakReason reason, const char* filename, int lineno)
    {
        detail::TPrintf("----\n");
        if( reason == NN_DBG_BREAK_REASON_ASSERT )
        {
            detail::TPrintf("Assertion failure at %s:%d\n  ", filename, lineno);
        }
        else
        {
            detail::TPrintf("Panic at %s:%d\n  ", filename, lineno);
        }
    }

    void CallBreakHandler(BreakReason reason, nn::Result* pResult, const char* filename, int lineno, const char* fmt, std::va_list args)
    {
        nn::dbg::BreakHandler  pBreakHandler = s_pBreakHandler;

        if( pBreakHandler != NULL )
        {
            s_pBreakHandler = NULL;
            pBreakHandler(reason, pResult, filename, lineno, fmt, args);
        }
    }

    void CallBreakHandler(nndbgBreakReason reason, nnResult result, const char* filename, int lineno, const char* fmt, std::va_list args)
    {
        nn::Result resultCpp = result;
        CallBreakHandler(static_cast<BreakReason>(reason), &resultCpp, filename, lineno, fmt, args);
    }

    void CallBreakHandler(nndbgBreakReason reason, const char* filename, int lineno, const char* fmt, std::va_list args)
    {
        CallBreakHandler(static_cast<BreakReason>(reason), NULL, filename, lineno, fmt, args);
    }

    void CallBreakHandler(BreakReason reason)
    {
        std::va_list args;
        CallBreakHandler(reason, NULL, NULL, 0, NULL, args);
    }
}

extern "C" {

    nnResult nndbgBreak(int reason)
    {
        return nn::dbg::Break(static_cast<nn::dbg::BreakReason>(reason));
    }

    void nndbgPanic()
    {
        Panic();
    }

    void nndbgBreakWithMessage_ (nndbgBreakReason reason, const char* filename, int lineno, const char* fmt, ...)
    {
        va_list arg;
        va_start(arg, fmt);
        PrintErrorMessageHeader(reason, filename, lineno);
        detail::VPrintf(fmt, arg);
        detail::TPrintf("\n");
        va_end(arg);

        va_start(arg, fmt);
        CallBreakHandler(reason, filename, lineno, fmt, arg);
        va_end(arg);

        Break(static_cast<BreakReason>(reason));
    }

    void nndbgBreakWithTMessage_(nndbgBreakReason reason, const char* filename, int lineno, const char* fmt, ...)
    {
        va_list arg;
        va_start(arg, fmt);
        PrintErrorMessageHeader(reason, filename, lineno);
        detail::TVPrintf(fmt, arg);
        detail::TPrintf("\n");
        va_end(arg);

        va_start(arg, fmt);
        CallBreakHandler(reason, filename, lineno, fmt, arg);
        va_end(arg);

        Break(static_cast<BreakReason>(reason));
    }

    void nndbgBreakWithResultMessage_ (nndbgBreakReason reason, nnResult result, const char* filename, int lineno, const char* fmt, ...)
    {
        va_list arg;
        va_start(arg, fmt);
        PrintErrorMessageHeader(reason, filename, lineno);
        detail::VPrintf(fmt, arg);
        detail::TPrintf("\n");
        detail::PrintResult(result);
        va_end(arg);

        va_start(arg, fmt);
        CallBreakHandler(reason, result, filename, lineno, fmt, arg);
        va_end(arg);

        Break(static_cast<BreakReason>(reason));
    }

    void nndbgBreakWithResultTMessage_(nndbgBreakReason reason, nnResult result, const char* filename, int lineno, const char* fmt, ...)
    {
        va_list arg;
        va_start(arg, fmt);
        PrintErrorMessageHeader(reason, filename, lineno);
        detail::TVPrintf(fmt, arg);
        detail::TPrintf("\n");
        detail::PrintResult(result);
        va_end(arg);

        va_start(arg, fmt);
        CallBreakHandler(reason, result, filename, lineno, fmt, arg);
        va_end(arg);

        Break(static_cast<BreakReason>(reason));
    }
}

namespace nn { namespace dbg {

    Result Break(BreakReason reason)
    {
        CallBreakHandler(reason);
        return nn::svc::Break(reason, NULL, 0);
    }

    void Panic()
    {
        Break(BREAK_REASON_PANIC);
    }

    void SetBreakHandler(BreakHandler handler)
    {
        NN_POINTER_TASSERT_(handler);
        s_pBreakHandler = handler;
    }

    namespace detail
    {
        Result NotifyDllLoadedToDebugger(const void* pDllInfo, size_t size)
        {
            return nn::svc::Break(BREAK_REASON_LOAD_RO, pDllInfo, size);
        }

        Result NotifyDllUnloadingToDebugger(const void* pDllInfo, size_t size)
        {
            return nn::svc::Break(BREAK_REASON_UNLOAD_RO, pDllInfo, size);
        }
    }

}}
