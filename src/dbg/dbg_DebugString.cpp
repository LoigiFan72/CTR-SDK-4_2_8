/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_DebugString.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <cstdio>
#include <cstdarg>
#include <cstring>

#include <nn/Result.h>
#include <nn/config.h>
#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Result.h>
#include <nn/svc.h>
#include <nn/nstd.h>
#include <nn/middleware.h>

namespace nn { namespace dbg {
    namespace detail {

        namespace
        {
            NN_DEFINE_MIDDLEWARE(s_UsePutString, "NINTENDO", "DebugPrint");
        }

        NN_WEAK_SYMBOL void PutString(const char* text, s32 length)
        {
            NN_UTIL_REFER_SYMBOL(s_UsePutString);
            nn::svc::OutputDebugString(text, length);
        }

        void PutString(const char* text)
        {
            PutString(text, std::strlen(text));
        }

        NN_WEAK_SYMBOL void VPrintf(const char* fmt, ::std::va_list arg)
        {
            char buf[NN_DBG_PRINTF_BUFFER_LENGTH];
            int length = ::std::vsnprintf(buf, sizeof(buf), fmt, arg);
            if (length >= NN_DBG_PRINTF_BUFFER_LENGTH)
            {
                length = NN_DBG_PRINTF_BUFFER_LENGTH - 1;   // need not count \0 of tail end
            }
            PutString(buf, length);
        }

        NN_WEAK_SYMBOL void TVPrintf(const char* fmt, ::std::va_list arg)
        {
            char buf[NN_DBG_TPRINTF_BUFFER_LENGTH];
            int length = nstd::TVSNPrintf(buf, sizeof(buf), fmt, arg);
            if (length >= NN_DBG_TPRINTF_BUFFER_LENGTH)
            {
                length = NN_DBG_TPRINTF_BUFFER_LENGTH - 1;   // need not count \0 of tail end
            }
            PutString(buf, length);
        }

        void Printf(const char* fmt, ...)
        {
            va_list vlist;

            va_start(vlist, fmt);
            nn::dbg::detail::VPrintf(fmt, vlist);
            va_end(vlist);
        }

        void TPrintf(const char* fmt, ...)
        {
            va_list vlist;

            va_start(vlist, fmt);
            nn::dbg::detail::TVPrintf(fmt, vlist);
            va_end(vlist);
        }

    }
}}


extern "C" {

    void nndbgDetailPrintf(const char* fmt, ...)
    {
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::VPrintf(fmt, vlist);
        va_end(vlist);
    }

    void nndbgDetailTPrintf(const char* fmt, ...)
    {
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::TVPrintf(fmt, vlist);
        va_end(vlist);
    }

    NN_WEAK_SYMBOL void nndbgDetailVPrintf(const char* fmt, va_list arg)
    {
        nn::dbg::detail::VPrintf(fmt, arg);
    }

    NN_WEAK_SYMBOL void nndbgDetailTVPrintf(const char* fmt, va_list arg)
    {
        nn::dbg::detail::TVPrintf(fmt, arg);
    }

    NN_WEAK_SYMBOL void nndbgDetailPutString(const char* text, s32 length)
    {
        nn::dbg::detail::PutString(text, length);
    }

    void nndbgPrintWarning_ (const char* filename, int lineno, const char* fmt, ...)
    {
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::TPrintf("%s:%d [WARN] ", filename, lineno);
        nn::dbg::detail::VPrintf(fmt, vlist);
        nn::dbg::detail::TPrintf("\n");
        va_end(vlist);
    }

    void nndbgTPrintWarning_(const char* filename, int lineno, const char* fmt, ...)
    {
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::TPrintf("%s:%d [WARN] ", filename, lineno);
        nn::dbg::detail::TVPrintf(fmt, vlist);
        nn::dbg::detail::TPrintf("\n");
        va_end(vlist);
    }

}
