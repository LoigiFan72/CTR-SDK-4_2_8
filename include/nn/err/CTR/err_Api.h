/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     err_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ERR_CTR_ERR_API_H_
#define NN_ERR_CTR_ERR_API_H_

#include <nn/types.h>
#include <nn/Result.h>

#ifdef __cplusplus
    namespace nn {
    namespace err {
    namespace CTR {

        // Do not directly call the following function. Use the NN_ERR_THROW_* macro.
        void ThrowFatalErr( Result result, uptr pc );
        void ThrowFatalErrAll( Result result, uptr pc );
        
        void AddToErrLog( Result result );
        void AddToErrLog( Result result, const char* fileName, int lineno );

        void LogAndPanic( Result result, uptr pc );
        void LogAndPanic( Result result, const char* fileName, int lineno, uptr pc );

        namespace detail
        {
            template <bool(*IsTarget)(Result), void (*TargetFunc)(Result,uptr)>
            inline void CallIf(Result r, uptr pc)
            {
                if( IsTarget(r) )
                {
                    TargetFunc(r, pc);
                }
            }

            template <bool(*IsTarget)(Result), void (*TargetFunc)(Result,const char*,int,uptr)>
            inline void CallIf(Result r, const char* fileName, int lineno, uptr pc )
            {
                if( IsTarget(r) )
                {
                    TargetFunc(r, fileName, lineno, pc);
                }
            }

            inline bool IsResultFailure(Result r)   { return r.IsFailure(); }
            inline bool IsResultFatal(Result r)     { return r.GetLevel() == ::nn::Result::LEVEL_FATAL; }
        }
    }}} // namespace nn::err::CTR

    #ifndef NN_HARDWARE_CTR_LEGACY
        #ifdef NN_PROCESSOR_ARM11MPCORE
            #define NN_ERR_CTR_ERR_API_H_CALL_IF(result, test, f)   \
                ::nn::err::CTR::detail::CallIf                      \
                    < ::nn::err::CTR::detail::test,                 \
                      ::nn::err::CTR::f >(result, __current_pc())

            #define NN_ERR_CTR_ERR_API_H_CALL_IF2(result, test, f)  \
                ::nn::err::CTR::detail::CallIf                      \
                    < ::nn::err::CTR::detail::test,                 \
                      ::nn::err::CTR::f >(result, NN_FILE_NAME, __LINE__, __current_pc())

            /*
                Throw a fatal error and display the error screen.
                An actual notification occurs only when the Result's LEVEL is FATAL.
             */
            #define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result) \
                NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFatal, ThrowFatalErrAll)

            /*
                Throw a fatal error and display the error screen.
                An actual notification occurs when the Result LEVEL is not SUCCESS/STATUS/INFO (not recommended) (for fatal errors or errors that should not occur in the retail product).
 

             */
            #define NN_ERR_THROW_FATAL(result) \
                NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFailure, ThrowFatalErr)

            /*
                Throw a fatal error and display the error screen.
                Notifies for all Results that are errors.
             */
            #define NN_ERR_THROW_FATAL_ALL(result) \
                NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFailure, ThrowFatalErrAll)

            #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
                #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result) \
                    NN_ERR_CTR_ERR_API_H_CALL_IF2(result, IsResultFailure, LogAndPanic)
            #else /* NN_SWITCH_DISABLE_DEBUG_PRINT */
                #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result) \
                    NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFailure, LogAndPanic)
            #endif  /* NN_SWITCH_DISABLE_DEBUG_PRINT */


            //#define NN_ERR_CTR_ERR_API_H_CALL_IF(result, test, f) \
            //    do                                          \
            //    {                                           \
            //        ::nn::Result resultLocal = (result);    \
            //        if ( resultLocal.test )                 \
            //        {                                       \
            //            ::nn::err::f(resultLocal);          \
            //        }                                       \
            //    } while(0)
            //
            //#define NN_ERR_CTR_ERR_API_H_CALL_IF2(result, test, f)            \
            //    do                                                            \
            //    {                                                             \
            //        ::nn::Result resultLocal = (result);                      \
            //        if ( resultLocal.test )                                   \
            //        {                                                         \
            //            ::nn::err::f(resultLocal, NN_FILE_NAME, __LINE__);    \
            //        }                                                         \
            //    } while(0)
            //
            //#define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result) \
            //    NN_ERR_CTR_ERR_API_H_CALL_IF(result, GetLevel() == ::nn::Result::LEVEL_FATAL, ThrowFatalErrAll)
            //#define NN_ERR_THROW_FATAL(result) \
            //    NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsFailure(), ThrowFatalErr)
            //#define NN_ERR_THROW_FATAL_ALL(result) \
            //    NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsFailure(), ThrowFatalErrAll)
            //
            //#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
            //    #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result) \
            //        NN_ERR_CTR_ERR_API_H_CALL_IF2(result, IsFailure(), LogAndPanic)
            //#else /* NN_SWITCH_DISABLE_DEBUG_PRINT */
            //    #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result) \
            //        NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsFailure(), LogAndPanic)
            //#endif  /* NN_SWITCH_DISABLE_DEBUG_PRINT */

        #else /* NN_PROCESSOR_ARM11MPCORE */

            #define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result)    NN_UTIL_PANIC_IF_FAILED(result)
            #define NN_ERR_THROW_FATAL(result)                  NN_UTIL_PANIC_IF_FAILED(result)
            #define NN_ERR_THROW_FATAL_ALL(result)              NN_UTIL_PANIC_IF_FAILED(result)
            #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result)      NN_UTIL_PANIC_IF_FAILED(result)

        #endif /* NN_PROCESSOR_ARM11MPCORE */
    #else /* NN_HARDWARE_CTR_LEGACY */

        #define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result)    ((void)(result))
        #define NN_ERR_THROW_FATAL(result)                  ((void)(result))
        #define NN_ERR_THROW_FATAL_ALL(result)              ((void)(result))
        #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result)      ((void)(result))

    #endif /* NN_HARDWARE_CTR_LEGACY */
#endif // __cplusplus


#endif /* NN_ERR_CTR_ERR_API_H_ */
