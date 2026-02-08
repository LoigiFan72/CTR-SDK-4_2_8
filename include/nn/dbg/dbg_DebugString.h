/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_DebugString.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47340 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_DBG_DBG_DEBUGSTRING_H_
#define NN_DBG_DBG_DEBUGSTRING_H_

#include <nn/config.h>
#include <nn/types.h>
#include <nn/Result.h>
#include <nn/dbg/dbg_Result.h>

//
//
//

//
//

//
#define NN_DBG_PRINTF_BUFFER_LENGTH     256

// Buffer size for TPrintf
#define NN_DBG_TPRINTF_BUFFER_LENGTH    128

//



/* ------------------------------------------------------------------------
        Dummy for reference use
   ------------------------------------------------------------------------ */

//
//

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_LOG( ... )


//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_LOGV( fmt, arg )


//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_PUT( text, length )

//

//

#undef NN_LOG
#undef NN_LOGV
#undef NN_PUT



/* ------------------------------------------------------------------------
        Definition entity
   ------------------------------------------------------------------------ */

#ifndef NN_BUILD_DOCUMENT
    #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
        #ifdef __cplusplus
            #define NN_LOG( ... )           (void)nn::dbg::detail::Printf(__VA_ARGS__)
            #define NN_LOGV( fmt, arg )     (void)nn::dbg::detail::VPrintf((fmt), (arg))
            #define NN_PUT( text, length )  (void)nn::dbg::detail::PutString((text), (length))
        #else   // ifdef __cplusplus
            #define NN_LOG( ... )           (void)nndbgDetailPrintf(__VA_ARGS__)
            #define NN_LOGV( fmt, arg )     (void)nndbgDetailVPrintf((fmt), (arg))
            #define NN_PUT( text, length )  (void)nndbgDetailPutString((text), (length))
        #endif  // ifdef __cplusplus else
    #else   // ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
        #define NN_LOG( ... )               ((void)0)
        #define NN_LOGV( ... )              ((void)0)
        #define NN_PUT( text, length )      ((void)0)
    #endif  // ifndef NN_SWITCH_DISABLE_DEBUG_PRINT else

    #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        #ifdef __cplusplus
            #define NN_TLOG_( ... )         (void)nn::dbg::detail::TPrintf(__VA_ARGS__)
            #define NN_SLOG_( ... )         (void)nn::dbg::detail::Printf(__VA_ARGS__)
            #define NN_TLOGV_( fmt, arg )   (void)nn::dbg::detail::TVPrintf((fmt), (arg))
        #else   // ifdef __cplusplus
            #define NN_TLOG_( ... )         (void)nndbgDetailTPrintf(__VA_ARGS__)
            #define NN_SLOG_( ... )         (void)nndbgDetailPrintf(__VA_ARGS__)
            #define NN_TLOGV_( fmt, arg )   (void)nndbgDetailTVPrintf((fmt), (arg))
        #endif  // ifdef __cplusplus else
    #else   // ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        #define NN_TLOG_( ... )             ((void)0)
        #define NN_SLOG_( ... )             ((void)0)
        #define NN_TLOGV_( ... )            ((void)0)
    #endif  // ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK else
#endif



//-------------------------------------------------------------------
// for C++

#ifdef __cplusplus
namespace nn { namespace dbg {
    namespace detail
    {
        void Printf(const char* fmt, ...);
        void TPrintf(const char* fmt, ...);
        void VPrintf(const char* fmt, ::std::va_list arg);
        void TVPrintf(const char* fmt, ::std::va_list arg);
        void PutString(const char* text, s32 length);
        void PutString(const char* text);
    }
}}
#endif  // ifdef __cplusplus



//-------------------------------------------------------------------
// for C / C++

#include <nn/dbg/dbg_Break.h>

#ifdef __cplusplus
extern "C" {
#endif  // ifdef __cplusplus

    void nndbgDetailPrintf(const char* fmt, ...);
    void nndbgDetailTPrintf(const char* fmt, ...);
    void nndbgDetailVPrintf(const char* fmt, va_list arg);
    void nndbgDetailTVPrintf(const char* fmt, va_list arg);
    void nndbgDetailPutString(const char* text, s32 length);

    void nndbgPrintWarning_ (const char* filename, int lineno, const char* fmt, ...);
    void nndbgTPrintWarning_(const char* filename, int lineno, const char* fmt, ...);

#ifdef __cplusplus
}
#endif  // ifdef __cplusplus

#endif  // NN_DBG_DBG_DEBUGSTRING_H_
