/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Logger.h

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

#ifndef NN_DBG_DBG_LOGGER_H_
#define NN_DBG_DBG_LOGGER_H_

#ifdef __cplusplus

#include <nn/types.h>
#include <nn/dbg/dbg_DebugString.h>
#include <nn/config.h>

#define NN_LOG_LEVEL_DEBUG      0
#define NN_LOG_LEVEL_INFO       1
#define NN_LOG_LEVEL_WARN       2
#define NN_LOG_LEVEL_ERROR      3
#define NN_LOG_LEVEL_FATAL      4
#define NN_LOG_LEVEL_FORCE      5
#define NN_LOG_LEVEL_DISABLE    6

#define NN_LOG_LEVEL_DEFAULT NN_LOG_LEVEL_WARN

#ifndef NN_LOG_LEVEL
#define NN_LOG_LEVEL NN_LOG_LEVEL_DEFAULT
#endif 

#ifdef NN_SWITCH_DISABLE_DEBUG_PRINT
#undef NN_LOG_LEVEL
#define NN_LOG_LEVEL NN_LOG_LEVEL_DISABLE
#endif

#if NN_LOG_LEVEL <= NN_LOG_LEVEL_DEBUG
    #define NN_LOG_DEBUG_ENABLE
#endif

#if NN_LOG_LEVEL <= NN_LOG_LEVEL_INFO
    #define NN_LOG_INFO_ENABLE
#endif

#if NN_LOG_LEVEL <= NN_LOG_LEVEL_WARN
    #define NN_LOG_WARN_ENABLE
#endif

#if NN_LOG_LEVEL <= NN_LOG_LEVEL_ERROR
    #define NN_LOG_ERROR_ENABLE
#endif

#if NN_LOG_LEVEL <= NN_LOG_LEVEL_FATAL
    #define NN_LOG_FATAL_ENABLE
#endif

#ifndef NN_LOG_BASE
#define NN_LOG_BASE(level, ...)                                     \
    ::nn::dbg::detail::Logger::PrintLog(::nn::dbg::detail::Logger::LEVEL_ ## level,   \
        NN_FUNCTION, NN_FILE_NAME, __LINE__, __VA_ARGS__)
#endif

/*
    

    

    
*/
#define NN_LOG_NAMESPACE(x)             ::nn::dbg::detail::Logger::SetNameSpace(x)

/*
    

    

    
*/
#define NN_LOG_SIGNATURE(x)             ::nn::dbg::detail::Logger::SetSignature(x)

/*
    

    

    
*/
#define NN_LOG_LONGPATH(x)              ::nn::dbg::detail::Logger::SetLongpath(x)

#define NN_LOG_SET_UPPER_LOG_LEVEL(x)   ::nn::dbg::detail::Logger::SetUpperLevel(x)
#define NN_LOG_SET_LOWER_LOG_LEVEL(x)   ::nn::dbg::detail::Logger::SetLowerLevel(x)
#define NN_LOG_SET_LOG_LEVEL(x)         NN_LOG_SET_LOWER_LOG_LEVEL(x)

/*
    

    
*/
#ifdef NN_LOG_DEBUG_ENABLE
#define NN_LOG_DEBUG(...)  NN_LOG_BASE(DEBUG, __VA_ARGS__)
#else
#define NN_LOG_DEBUG(...) ((void)0)
#endif

/*
    

    
*/
#ifdef NN_LOG_INFO_ENABLE
#define NN_LOG_INFO(...)  NN_LOG_BASE(INFO, __VA_ARGS__)
#else
#define NN_LOG_INFO(...) ((void)0)
#endif

/*
    

    
*/
#ifdef NN_LOG_WARN_ENABLE
#define NN_LOG_WARN(...)  NN_LOG_BASE(WARN, __VA_ARGS__)
#else
#define NN_LOG_WARN(...) ((void)0)
#endif

/*
    

    
*/
#ifdef NN_LOG_ERROR_ENABLE
#define NN_LOG_ERROR(...)  NN_LOG_BASE(ERROR, __VA_ARGS__)
#else
#define NN_LOG_ERROR(...) ((void)0)
#endif

/*
    

    
*/
#ifdef NN_LOG_FATAL_ENABLE
#define NN_LOG_FATAL(...)  NN_LOG_BASE(FATAL, __VA_ARGS__)
#else
#define NN_LOG_FATAL(...) ((void)0)
#endif

/*
    

    
*/
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
#define NN_LOG_FORCE(...)   NN_LOG_BASE(FORCE, __VA_ARGS__)
#else
#define NN_LOG_FORCE(...) ((void)0)
#endif

namespace nn { namespace dbg { namespace detail {

class Logger
{
private:
    static u32 s_UpperLevel;                 //
    static u32 s_LowerLevel;                 //
    static u8 s_ShowFlag;                    //
    static bool s_Initialized;               //
    static const u8 ENABLE_NAMESPACE = 1;    //
    static const u8 ENABLE_SIGNATURE = 2;    //
    static const u8 ENABLE_LONGPATH  = 4;    //
#ifdef NN_SYSTEM_KERNEL
    static const u32 BUF_SIZE = NN_DBG_TPRINTF_BUFFER_LENGTH;
#else
    static const u32 BUF_SIZE = NN_DBG_PRINTF_BUFFER_LENGTH;
#endif

public:
    static const u32 LEVEL_DEBUG = NN_LOG_LEVEL_DEBUG;     //
    static const u32 LEVEL_INFO  = NN_LOG_LEVEL_INFO;      //
    static const u32 LEVEL_WARN  = NN_LOG_LEVEL_WARN;      //
    static const u32 LEVEL_ERROR = NN_LOG_LEVEL_ERROR;     //
    static const u32 LEVEL_FATAL = NN_LOG_LEVEL_FATAL;     //
    static const u32 LEVEL_FORCE = NN_LOG_LEVEL_FORCE;     //

    /*
        

        
        
        
        
        
    */
    static void PrintLog(const u32 level, const char8* funcName, const char8* fileName,
                            const int line, const char8* fmt, ...);
    
    /*
        

        
        
        

        

        
    */
    static size_t MakeFuncName(const char8* src, char8* dest, size_t length);

    /*
        

        
    */
    static void SetUpperLevel(u32 level) { s_UpperLevel = level; s_Initialized = true; }

    /*
        

        
    */
    static void SetLowerLevel(u32 level) { s_LowerLevel = level; s_Initialized = true; }

    /*
        

        
    */
    static void SetLevel(u32 level) { SetLowerLevel(level); }

    /*
        

        
                        
                        

        
    */
    static void SetFlag(u8 type, bool value)
    {
        if(value)
        {
            s_ShowFlag |= type;
        }
        else
        {
            s_ShowFlag &= (0xff ^ type);
        }
    }

    /*
        

        
    */
    static void SetNameSpace(bool f) { SetFlag(ENABLE_NAMESPACE, f); }

    /*
        

        
    */
    static void SetSignature(bool f) { SetFlag(ENABLE_SIGNATURE, f); }

    /*
        

        
    */
    static void  SetLongpath(bool f) { SetFlag(ENABLE_LONGPATH , f); }
    

    static char8* s_LevelStrings[];    //
};
    
}}}


#endif // __cplusplus

#endif
