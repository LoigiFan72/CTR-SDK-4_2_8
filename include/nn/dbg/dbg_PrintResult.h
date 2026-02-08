/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_PrintResult.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_DBG_DBG_PRINTRESULT_H_
#define NN_DBG_DBG_PRINTRESULT_H_

#include <nn/Result.h>
#include <nn/assert.h>

#ifdef __cplusplus


//
//


/* =======================================================================
        Dummy for reference use
   ======================================================================== */

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
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_DBG_CHECK_RESULT(exp)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_DBG_PRINT_RESULT(exp)

//

//

#undef NN_DBG_CHECK_RESULT
#undef NN_DBG_PRINT_RESULT




/* =======================================================================
        Definition entity
   ======================================================================== */

#ifndef NN_BUILD_DOCUMENT
    namespace nn { namespace dbg { namespace detail {

        void PrintResult(Result result);
        const char* GetLevelString(nn::Result result);
        const char* GetModuleString(nn::Result result);
        const char* GetSummaryString(nn::Result result);
        const char* GetDescriptionString(nn::Result result);

    }}}

    #ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
        #define NN_DBG_DECLARE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname) \
            namespace nn { namespace libname { namespace detail { \
                void GetResultDescriptionStringImplKeeper(); \
            }}}
        #define NN_DBG_DECLARE_ADDITIONAL_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname, option) \
            namespace nn { namespace libname { namespace detail { \
                void GetResult##option##DescriptionStringImplKeeper(); \
            }}}
        #define NN_DBG_USE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname) \
            (::nn::libname::detail::GetResultDescriptionStringImplKeeper())
        #define NN_DBG_USE_ADDITIONAL_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname, option) \
            (::nn::libname::detail::GetResult##option##DescriptionStringImplKeeper())
    #else
        #define NN_DBG_DECLARE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname)
        #define NN_DBG_DECLARE_ADDITIONAL_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname, option)
        #define NN_DBG_USE_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname) (void)0
        #define NN_DBG_USE_ADDITIONAL_GET_RESULT_DESCRIPTION_STRING_IMPL_KEEPER(libname, option) (void)0
    #endif

    #ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
        #define NN_DBG_CHECK_RESULT(exp)    NN_PANIC_IF_FAILED(exp)
    #else
        #define NN_DBG_CHECK_RESULT(exp)    ((void)(exp))
    #endif
    
    #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
        #define NN_DBG_PRINT_RESULT(exp)    ::nn::dbg::detail::PrintResult(exp)
    #else
        #define NN_DBG_PRINT_RESULT(exp)    ((void)(exp))
    #endif

    #define NN_DBG_TPRINT_RESULT_(exp)      NN_DBG_PRINT_RESULT(exp)
#endif

#endif  // ifdef __cplusplus

#endif /* NN_DBG_DBG_RESULT_H_ */
