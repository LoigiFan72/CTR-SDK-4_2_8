/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     assert.h

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

#ifndef NN_ASSERT_H_
#define NN_ASSERT_H_

#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Break.h>
#include <nn/Result.h>
#include <nn/config.h>
//TORIAEZU
#include <nn/os/os_MemoryMapSelect.h>

#include <cfloat>



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
//---------------------------------------------------------------------------
#define NN_ASSERT(exp)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_ASSERTMSG(exp, ...)

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
#define NN_ASSERTMSG_WITH_RESULT(exp, result, ...)

//

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
#define NN_ALIGN_ASSERT(exp, align)

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
#define NN_EQUAL_ASSERT(exp, equ)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FLOAT_ASSERT(exp)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_MIN_ASSERT(exp, min)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_MAX_ASSERT(exp, max)

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
#define NN_MINMAX_ASSERT(exp, min, max)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_NOT_EQUAL_ASSERT(exp, equ)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_NULL_ASSERT(exp)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_POINTER_ASSERT(p)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_THIS_ASSERT()


//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_RESULT_ASSERT(exp)

//


#define NN_ASSERT_RESULT(exp)
#define NN_ASSERT_WITH_RESULT(exp, result)



//
//

//---------------------------------------------------------------------------
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_COMPILER_ASSERT(exp)

//



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
//---------------------------------------------------------------------------
#define NN_PANIC(...)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_PANIC_WITH_RESULT(result, ...)

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_PANIC_IF_FAILED(result)

//

//

#undef NN_ALIGN_ASSERT
#undef NN_ASSERT
#undef NN_ASSERTMSG
#undef NN_ASSERTMSG_WITH_RESULT
#undef NN_ASSERT_RESULT
#undef NN_ASSERT_WITH_RESULT
#undef NN_EQUAL_ASSERT
#undef NN_FLOAT_ASSERT
#undef NN_MAX_ASSERT
#undef NN_MINMAX_ASSERT
#undef NN_MIN_ASSERT
#undef NN_NOT_EQUAL_ASSERT
#undef NN_NULL_ASSERT
#undef NN_PANIC
#undef NN_PANIC_WITH_RESULT
#undef NN_POINTER_ASSERT
#undef NN_RESULT_ASSERT
#undef NN_THIS_ASSERT
#undef NN_PANIC_IF_FAILED
#undef NN_COMPILER_ASSERT






/* =======================================================================
        Definition entity
   ======================================================================== */

#ifndef NN_BUILD_DOCUMENT

    /* ------------------------------------------------------------------------
            assert
       ------------------------------------------------------------------------ */

    #ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
        #ifdef NN_SYSTEM_KERNEL
            #define NN_ASSERTMSG(exp, ...)                                                          \
                (void) ((exp) || ( NN_LOG("Failed assertion at %s:%d\n  ", NN_FILE_NAME, __LINE__), \
                                   NN_LOG(__VA_ARGS__),                                             \
                                   NN_LOG("\n"),                                                    \
                                   ::nn::dbg::Break(nn::dbg::BREAK_REASON_ASSERT),                  \
                                   0) )
            #define NN_ASSERTMSG_WITH_RESULT(exp, result, ...)  NN_ASSERTMSG(exp, __VA_ARGS__)
        #else
            #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
                // assert enabled; print enabled
                #define NN_ASSERTMSG(exp, ...)                                                  \
                    (void) ((exp) || (nndbgBreakWithMessage_(NN_DBG_BREAK_REASON_ASSERT, NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
                #define NN_ASSERTMSG_WITH_RESULT(exp, result, ...)                              \
                    (void) ((exp) || (nndbgBreakWithResultMessage_(NN_DBG_BREAK_REASON_ASSERT, (nnResult)(result), NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
            #else
                // assert enabled; print disabled
                #define NN_ASSERTMSG(exp, ...)                                                  \
                    (void) ((exp) || (nndbgBreak(NN_DBG_BREAK_REASON_ASSERT), 0))
                #define NN_ASSERTMSG_WITH_RESULT(exp, result, ...)                              \
                    (void) ((exp) || (nndbgBreak(NN_DBG_BREAK_REASON_ASSERT), 0))
            #endif
        #endif
    #else
        // assert disabled
        #define NN_ASSERTMSG(exp, ...)                      ((void)0)
        #define NN_ASSERTMSG_WITH_RESULT(exp, result, ...)  ((void)0)
    #endif // NN_SWITCH_DISABLE_ASSERT_WARNING

    #ifndef NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK
        #ifdef NN_SYSTEM_KERNEL
            #define NN_TASSERTMSG_(exp, ...)                        NN_ASSERTMSG(exp, __VA_ARGS__)
            #define NN_SASSERTMSG_(exp, ...)                        NN_ASSERTMSG(exp, __VA_ARGS__)
            #define NN_TASSERTMSG_WITH_RESULT_(exp, result, ...)    NN_ASSERTMSG(exp, __VA_ARGS__)
            #define NN_SASSERTMSG_WITH_RESULT_(exp, result, ...)    NN_ASSERTMSG(exp, __VA_ARGS__)
        #else
            #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
                // assert enabled; print enabled
                #define NN_TASSERTMSG_(exp, ...) \
                    (void) ((exp) || (nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT, NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
                #define NN_SASSERTMSG_(exp, ...) \
                    (void) ((exp) || (nndbgBreakWithMessage_(NN_DBG_BREAK_REASON_ASSERT, NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
                #define NN_TASSERTMSG_WITH_RESULT_(exp, result, ...) \
                    (void) ((exp) || (nndbgBreakWithResultTMessage_(NN_DBG_BREAK_REASON_ASSERT, (nnResult)(result), NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
                #define NN_SASSERTMSG_WITH_RESULT_(exp, result, ...) \
                    (void) ((exp) || (nndbgBreakWithResultMessage_(NN_DBG_BREAK_REASON_ASSERT, (nnResult)(result), NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
            #else
                // assert enabled; print disabled
                #define NN_TASSERTMSG_(exp, ...) \
                    (void) ((exp) || (nndbgBreak(NN_DBG_BREAK_REASON_ASSERT), 0))
                #define NN_SASSERTMSG_(exp, ...) \
                    (void) ((exp) || (nndbgBreak(NN_DBG_BREAK_REASON_ASSERT), 0))
                #define NN_TASSERTMSG_WITH_RESULT_(exp, result, ...) \
                    (void) ((exp) || (nndbgBreak(NN_DBG_BREAK_REASON_ASSERT), 0))
                #define NN_SASSERTMSG_WITH_RESULT_(exp, result, ...) \
                    (void) ((exp) || (nndbgBreak(NN_DBG_BREAK_REASON_ASSERT), 0))
            #endif
        #endif
    #else
        // assert disabled
        #define NN_TASSERTMSG_(exp, ...)                        ((void)0)
        #define NN_SASSERTMSG_(exp, ...)                        ((void)0)
        #define NN_TASSERTMSG_WITH_RESULT_(exp, result, ...)    ((void)0)
        #define NN_SASSERTMSG_WITH_RESULT_(exp, result, ...)    ((void)0)
    #endif // NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK


    #define NN_ANY_TO_UPTR(ptr)         ((uptr)((const void*)(ptr)))
    #define NN_IS_VALID_POINTER(ptr)    ( (NN_OS_ADDR_NULL_TRAP_END <= NN_ANY_TO_UPTR(ptr)) \
                                            && (NN_ANY_TO_UPTR(ptr) < NN_OS_ADDR_SPACE_END) )


    #define NN_ASSERT(  exp)                    NN_ASSERTMSG(  (exp), "%s", #exp)
    #define NN_TASSERT_(exp)                    NN_TASSERTMSG_((exp), "%s", #exp)
    #define NN_SASSERT_(exp)                    NN_SASSERTMSG_((exp), "%s", #exp)

    #define NN_RESULT_ASSERT(  exp)             NN_ASSERTMSG_WITH_RESULT(  (exp).IsSuccess(), (exp), "\"%s\" is Failure.", #exp)
    #define NN_RESULT_TASSERT_(exp)             NN_TASSERTMSG_WITH_RESULT_((exp).IsSuccess(), (exp), "\"%s\" is Failure.", #exp)

    #define NN_NULL_ASSERT(  exp)               NN_ASSERTMSG(   (exp) != NULL, "%s must not be NULL", #exp )
    #define NN_NULL_TASSERT_(exp)               NN_TASSERTMSG_( (exp) != NULL, "%s must not be NULL", #exp )

    #define NN_ALIGN_ASSERT(  exp, align)       NN_ASSERTMSG(   ((uptr)(exp)) % (align) == 0, "%s(=0x%08x) must be %d byte aligned.", #exp, (exp), align )
    #define NN_ALIGN_TASSERT_(exp, align)       NN_TASSERTMSG_( ((uptr)(exp)) % (align) == 0, "%s(=0x%08x) must be %d byte aligned.", #exp, (exp), align )

    #define NN_MIN_ASSERT(  exp, min)           NN_ASSERTMSG(   (exp) >= (min), "%s(=%d) must be >= %s(=%d).", #exp, (exp), #min, min )
    #define NN_MIN_TASSERT_(exp, min)           NN_TASSERTMSG_( (exp) >= (min), "%s(=%d) must be >= %s(=%d).", #exp, (exp), #min, min )

    #define NN_MAX_ASSERT(  exp, max)           NN_ASSERTMSG(   (exp) <= (max), "%s(=%d) must be <= %s(=%d).", #exp, (exp), #max, max )
    #define NN_MAX_TASSERT_(exp, max)           NN_TASSERTMSG_( (exp) <= (max), "%s(=%d) must be <= %s(=%d).", #exp, (exp), #max, max )

    #define NN_MINMAX_ASSERT(  exp, min, max)   NN_ASSERTMSG(   (exp) >= (min) && (exp) <= (max), "%s(=%d) must be >= %s(=%d) and <= %s(=%d).", #exp, (exp), #min, min, #max, max )
    #define NN_MINMAX_TASSERT_(exp, min, max)   NN_TASSERTMSG_( (exp) >= (min) && (exp) <= (max), "%s(=%d) must be >= %s(=%d) and <= %s(=%d).", #exp, (exp), #min, min, #max, max )

    #define NN_EQUAL_ASSERT(  exp, equ)         NN_ASSERTMSG(   (exp) == (equ), "%s(=%d) must be == %s(=%d).", #exp, (exp), #equ, equ )
    #define NN_EQUAL_TASSERT_(exp, equ)         NN_TASSERTMSG_( (exp) == (equ), "%s(=%d) must be == %s(=%d).", #exp, (exp), #equ, equ )

    #define NN_NOT_EQUAL_ASSERT(  exp, equ)     NN_ASSERTMSG(   (exp) != (equ), "%s(=%d) must be != %s(=%d).", #exp, (exp), #equ, equ )
    #define NN_NOT_EQUAL_TASSERT_(exp, equ)     NN_TASSERTMSG_( (exp) != (equ), "%s(=%d) must be != %s(=%d).", #exp, (exp), #equ, equ )

    #define NN_POINTER_ASSERT(  p)              NN_ASSERTMSG(  NN_IS_VALID_POINTER(p), "%s(=0x%08X) is invalid pointer", #p, (p))
    #define NN_POINTER_TASSERT_(p)              NN_TASSERTMSG_(NN_IS_VALID_POINTER(p), "%s(=0x%08X) is invalid pointer", #p, (p))

    #define NN_THIS_ASSERT(  )                  NN_POINTER_ASSERT(  this)
    #define NN_THIS_TASSERT_()                  NN_POINTER_TASSERT_(this)

    #define NN_ASSERT_WITH_RESULT(  exp, result)    NN_ASSERTMSG_WITH_RESULT(   (exp), (result), "%s", #exp )
    #define NN_TASSERT_WITH_RESULT_(exp, result)    NN_TASSERTMSG_WITH_RESULT_( (exp), (result), "%s", #exp )
    #define NN_SASSERT_WITH_RESULT_(exp, result)    NN_SASSERTMSG_WITH_RESULT_( (exp), (result), "%s", #exp )

    #define NN_FLOAT_ASSERT(exp)                NN_ASSERTMSG((-FLT_MAX <= (exp) && (exp) <= FLT_MAX), "Floating Point Value Error\n"#exp" is infinite or nan.")
    #define NN_FLOAT_TASSERT_(exp)              NN_TASSERTMSG_((-FLT_MAX <= (exp) && (exp) <= FLT_MAX), "Floating Point Value Error\n"#exp" is infinite or nan.")
    #define NN_FLOAT_SASSERT_(exp)              NN_FLOAT_TASSERT_exp)


    #define NN_ASSERT_RESULT(exp)               NN_RESULT_ASSERT(exp)
    #define NN_TASSERT_RESULT_(exp)             NN_RESULT_TASSERT_(exp)





    /* ------------------------------------------------------------------------
            panic
       ------------------------------------------------------------------------ */

    #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
        // print enabled
        #define NN_PANIC(...)   nndbgBreakWithMessage_ (NN_DBG_BREAK_REASON_PANIC, NN_FILE_NAME, __LINE__, __VA_ARGS__)
        #define NN_PANIC_WITH_RESULT(result, ...) \
            nndbgBreakWithResultMessage_(NN_DBG_BREAK_REASON_PANIC, (nnResult)(result), NN_FILE_NAME, __LINE__, __VA_ARGS__)
    #else
        // print disabled
        #define NN_PANIC(...)                       nndbgPanic()
        #define NN_PANIC_WITH_RESULT(result, ...)   (((void)(result)), nndbgPanic())
    #endif

    #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
        // print enabled
        #define NN_TPANIC_(...) nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_PANIC, NN_FILE_NAME, __LINE__, __VA_ARGS__)
        #define NN_SPANIC_(...) nndbgBreakWithMessage_ (NN_DBG_BREAK_REASON_PANIC, NN_FILE_NAME, __LINE__, __VA_ARGS__)
        #define NN_TPANIC_WITH_RESULT_(result, ...) \
            nndbgBreakWithResultTMessage_(NN_DBG_BREAK_REASON_PANIC, (nnResult)(result), NN_FILE_NAME, __LINE__, __VA_ARGS__)
    #else
        // print disabled
        #define NN_TPANIC_(...)                     nndbgPanic()
        #define NN_SPANIC_(...)                     nndbgPanic()
        #define NN_TPANIC_WITH_RESULT_(result, ...) (((void)(result)), nndbgPanic())
    #endif


    #define NN_PANIC_IF_FALSE(exp)      (void) ( (exp) || (NN_PANIC  ("Failed condition."), 0) )
    #define NN_TPANIC_IF_FALSE_(exp)    (void) ( (exp) || (NN_TPANIC_("Failed condition."), 0) )

    #define NN_PANIC_IF_NULL(  exp)     NN_PANIC_IF_FALSE(  exp)
    #define NN_TPANIC_IF_NULL_(exp)     NN_TPANIC_IF_FALSE_(exp)

    #define NN_PANIC_IF_FAILED(result)                      \
        do {                                                \
            ::nn::Result nn_result_try_result = (result);   \
            if (nn_result_try_result.IsFailure())           \
            {                                               \
                NN_PANIC_WITH_RESULT(nn_result_try_result, "\"%s\" is Failure.", #result);    \
            }                                               \
        } while (0)

    #define NN_TPANIC_IF_FAILED_(result)                    \
        do {                                                \
            ::nn::Result nn_result_try_result = (result);   \
            if (nn_result_try_result.IsFailure())           \
            {                                               \
                NN_TPANIC_WITH_RESULT_(nn_result_try_result, "\"%s\" is Failure.", #result);    \
            }                                               \
        } while (0)



    /* ------------------------------------------------------------------------
            warning
       ------------------------------------------------------------------------ */

    #ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
        #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
            #define NN_WARNING(exp, ...) \
                (void) ((exp) || (nndbgPrintWarning_(NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
        #else
            #define NN_WARNING(exp, ...)  ((void)0)
        #endif
    #else
        #define NN_WARNING(exp, ...)  ((void)0)
    #endif // NN_SWITCH_DISABLE_ASSERT_WARNING

    #ifndef NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK
        #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK
            #define NN_TWARNING_(exp, ...) \
                (void) ((exp) || (nndbgTPrintWarning_(NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
            #define NN_SWARNING_(exp, ...) \
                (void) ((exp) || (nndbgPrintWarning_(NN_FILE_NAME, __LINE__, __VA_ARGS__), 0))
        #else
            #define NN_TWARNING_(exp, ...)  ((void)0)
            #define NN_SWARNING_(exp, ...)  ((void)0)
        #endif
    #else
        #define NN_TWARNING_(exp, ...)  ((void)0)
        #define NN_SWARNING_(exp, ...)  ((void)0)
    #endif // NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK





    /* ------------------------------------------------------------------------
            static_assert
       ------------------------------------------------------------------------ */

    #ifdef __cplusplus

        namespace nn 
        {
            template <bool> struct STATIC_ASSERTION_FAILURE;
            template <> struct STATIC_ASSERTION_FAILURE<true> {};

            namespace detail 
            {
                template<int x> struct static_assert_test {};
            }
        }

        #define NN_ASSERT_H_STRING_JOIN_(X, Y)  NN_ASSERT_H_STRING_JOIN1_(X, Y)
        #define NN_ASSERT_H_STRING_JOIN1_(X, Y) X##Y

        /* Please see man pages for details 
            

            

                   
        */
        #define NN_STATIC_ASSERT(exp)                                           \
            typedef ::nn::detail::static_assert_test<                           \
                    sizeof(::nn::STATIC_ASSERTION_FAILURE<(exp) != 0>)          \
                > NN_ASSERT_H_STRING_JOIN_(nn_static_assert_typedef_, __LINE__)

        /* Please see man pages for details 
            

            

                   
        */
        #define NN_STATIC_ASSERT_IS_POD(T)                                              \
            typedef union                                                               \
            {                                                                           \
                T NN_ASSERT_H_STRING_JOIN_(nn_static_assert_is_pod_menber_, __LINE__);  \
            }                                                                           \
            NN_ASSERT_H_STRING_JOIN_(nn_static_assert_is_pod_, __LINE__)

    #else // __cplusplus

        #define NN_STATIC_ASSERT(expr)      void NN_ASSERT_H_STRING_JOIN_##__FILE__##__LINE__(int arg[(expr) ? 1 : -1])
        #define NN_STATIC_ASSERT_IS_POD(T)  ((void)0)

    #endif

    #define NN_COMPILER_ASSERT(x) NN_STATIC_ASSERT(x)


#endif





#endif /* NN_ASSERT_H_ */
