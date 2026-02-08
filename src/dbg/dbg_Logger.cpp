/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Logger.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/dbg/dbg_Logger.h>
#include <nn/nstd.h>
#include <nn/os.h>
#include <cstring>
#include <cstdio>
#include <algorithm>

/****************************************************************************/
namespace nn {
namespace dbg {
namespace detail {
/****************************************************************************/

/*
    Switches to a log output format appropriate for network system operation confirmation
    - Displays absolute time
    - Makes WARN, ERROR, and FATAL stand out
    - Displays only module name at the start
    - Aligns the position of the free description portion
    - Omit the middle of long function names
 */
//#define ANOTHER_FORMAT

namespace {
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
    size_t SafeTVSNPrintf(char* dst, size_t bufferLength, const char* fmt, va_list vlist)
    {
        size_t length = std::min<size_t>(nn::nstd::TVSNPrintf(dst, bufferLength, fmt, vlist), bufferLength);
        return length;
    }

    size_t SafeTSNPrintf(char* dst, size_t bufferLength, const char* fmt, ...)
    {
        va_list vlist;
        va_start(vlist, fmt);
        size_t length = std::min<size_t>(nn::nstd::TVSNPrintf(dst, bufferLength, fmt, vlist), bufferLength);
        va_end(vlist);
        return length;
    }

#ifdef ANOTHER_FORMAT
    size_t AddSpace(char* dst, size_t len)
    {
        for(size_t i = 0; i < len; ++i)
        {
            dst[i] = ' ';
        }
        return len;
    }

    size_t AddSpaceUsingTab(char* dst, s32 width)
    {
        const s32 TAB_WIDTH = 8;
        size_t len = 0;
        for(s32 i = 0; i < width % TAB_WIDTH; ++i, ++len)
        {
            dst[len] = ' ';
        }
        for(s32 i = 0; i < width / TAB_WIDTH; ++i, ++len)
        {
            dst[len] = '\t';
        }
        return len;
    }
#endif

    char* GetBaseName(const char* path)
    {
        char* pFileNameTop = (char8*)std::strrchr(path, '\\');
        if (!pFileNameTop)
        {
            return const_cast<char*>(path);
        }
        return pFileNameTop + 1;
    }
#endif
}

char8* Logger::s_LevelStrings[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
    "FORCE"
};

u32 Logger::s_UpperLevel    = Logger::LEVEL_FATAL;
u32 Logger::s_LowerLevel    = NN_LOG_LEVEL;
bool Logger::s_Initialized  = false;
u8 Logger::s_ShowFlag       = 0;

size_t Logger::MakeFuncName(const char8* src, char8* dest, size_t length)
{
	// TODO: src NULL check
	// TODO: dest NULL check
    char8* pSrcTop = const_cast<char8*>(src);
    char8* pSrcSigHead = ::std::strrchr(pSrcTop, '(');
    // Determine end
    // If ENABLE_SIGNATURE, end of src
    // if not, the ( position of the function
    char8* pSrcLast = (s_ShowFlag & ENABLE_SIGNATURE) ?
                pSrcTop + ::std::strlen(src) :
                pSrcSigHead;

    // Determine start
    // If ENABLE_NAMESPACE, use the start of src. If not, use the position of the third ":" from the end + 1.
    //
    if(!(s_ShowFlag & ENABLE_NAMESPACE))
    {
#ifndef ANOTHER_FORMAT
        pSrcTop = pSrcSigHead;
        for(int count = 0;pSrcTop != src && count < 3; pSrcTop--)
        {
            count = (*pSrcTop == ':') ? count + 1 : count;
        }
        pSrcTop += 2;
#else
        char* p;
        for(p = pSrcSigHead; p > pSrcTop; --p)
        {
            if (std::strncmp(p, "::", 2) == 0)
            {
                break;
            }
        }
        if (p != pSrcTop)
        {
            pSrcTop = p + 2;
        }
        else
        {
            for(p = pSrcSigHead; p > pSrcTop; --p)
            {
                if (*p == ' ')
                {
                    break;
                }
            }
            if (p != pSrcTop)
            {
                pSrcTop = p + 1;
            }
        }
#endif
    }
    size_t copyLength = ::std::min<size_t>(pSrcLast - pSrcTop, length - 1);
    ::std::memcpy(dest, pSrcTop, copyLength);
    dest[copyLength] = '\0';
    return copyLength;
}

void Logger::PrintLog(const u32 level, const char8* funcName, const char8* fileName, const int line,
                            const char8* fmt, ...)
{
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
//    static int count = 0;
    // Exit if outside of the setting level range
    if(!s_Initialized)
    {
        s_LowerLevel = NN_LOG_LEVEL;
    }

    if(level != LEVEL_FORCE && (level < s_LowerLevel || s_UpperLevel < level))
    {
        return;
    }

    char8 buffer[BUF_SIZE];
    size_t len = 0;

#ifndef ANOTHER_FORMAT
    {
        // Process funcName
        len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, "[%s] ", s_LevelStrings[level]);
        
        len += MakeFuncName(funcName, &buffer[len], BUF_SIZE - len - 3);

        ::std::strncat(&buffer[len], " : ", sizeof(buffer) - len - 3);
        len += 3;
    }
#else
    const size_t MODULE_LENGTH          = 3;
    const size_t FUNCTION_LENGTH        = 22;
    const size_t FUNCTION_TAIL_LENGTH   = 9;
    const s32 PREFIX1_POSITION          = 11 + MODULE_LENGTH;
    const s32 PREFIX2_POSITION          = PREFIX1_POSITION + 8;
    const s32 PREFIX3_POSITION          = PREFIX2_POSITION + FUNCTION_LENGTH + 2/* ": " */;
    const s32 SUFFIX_POSITION           = 104;
    {
        //  012345678901234567890123456
        // "12345.67 [soc]<WARNING> Startup..ocket: HOGEHOGE                    (socket_Main.cpp:175)"
        //            ~~~                               MODULE_LENGTH
        //                          ~~~~~~~~~~~~~~~     FUNCTION_LENGTH
        //                                    ~~~~~     FUNCTION_TAIL_LENGTH
        //                ^                             PREFIX1_POSITION            
        //                          ^                   PREFIX2_POSITION
        //                                          ^   PREFIX3_POSITION
        //                                              SUFFIX_POSITION        ^
        {
#ifndef NN_SYSTEM_KERNEL
            s64 msec    = nn::os::Tick::GetSystemCurrent().ToTimeSpan().GetMilliSeconds();
            s32 sec     = static_cast<s32>(msec/1000);
            if (sec < 10000)
            {
                len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, "%4ld.%02ld ", sec, static_cast<s32>(msec % 1000 / 10));
            }
            else
            {
                len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, "%7ld ", sec);
            }
#else
            len += AddSpace(&buffer[len], 8);
#endif
        }

        {
            char* pFileNameTop    = GetBaseName(fileName);
            char* pModulePosition = std::strchr(pFileNameTop, '_');

            if (pModulePosition)
            {
                size_t moduleLength = std::min<size_t>(MODULE_LENGTH, reinterpret_cast<uptr>(pModulePosition) - reinterpret_cast<uptr>(pFileNameTop));
                len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, "[%0.*s]", moduleLength, pFileNameTop);
            }
            if (len < PREFIX1_POSITION)
            {
                len += AddSpace(&buffer[len], PREFIX1_POSITION - len);
            }
            if (level >= LEVEL_WARN && level <= Logger::LEVEL_FATAL)
            {
                len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, "<%s>", s_LevelStrings[level]);
            }

            if (len < PREFIX2_POSITION)
            {
                len += AddSpace(&buffer[len], PREFIX2_POSITION - len);
            }
        }

        {
            // Gets method name and function name
            size_t funcNameLen = MakeFuncName(funcName, &buffer[len], sizeof(buffer) - len);
            if (funcNameLen > FUNCTION_LENGTH)
            {
                // Indicate maximum length exceeded by ".." in the middle
                std::strcpy(&buffer[len + FUNCTION_LENGTH - FUNCTION_TAIL_LENGTH - 2], "..");
                std::memmove(&buffer[len + FUNCTION_LENGTH - FUNCTION_TAIL_LENGTH], &buffer[len + funcNameLen - FUNCTION_TAIL_LENGTH], FUNCTION_TAIL_LENGTH);
                funcNameLen = FUNCTION_LENGTH;
            }
            len += funcNameLen;
            len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, ": ");
            if (len < PREFIX3_POSITION)
            {
                len += AddSpace(&buffer[len], PREFIX3_POSITION - len);
            }

        }
    }
#endif
    {
        // Expand long message
        // To prevent displaying a jumble between threads, output all at once sacrificing the maximum string length
        va_list vlist;
        va_start(vlist, fmt);
        len += SafeTVSNPrintf(&buffer[len], sizeof(buffer) - len, fmt, vlist);
        va_end(vlist);

        // Delete when \n is at the end of the userMessage
        for (; len > 0 && buffer[len - 1] == '\n'; --len)
        {
            buffer[len - 1] = '\0';
        }
    }

    {
        // Process fileName
        char8* pFileNameTop;
        if(!(s_ShowFlag & ENABLE_LONGPATH))
        {
            pFileNameTop = GetBaseName(fileName);
        }
        else
        {
            pFileNameTop = (char8*)fileName;
        }

#ifdef ANOTHER_FORMAT
        {
            if (len < SUFFIX_POSITION)
            {
                len += AddSpaceUsingTab(&buffer[len], SUFFIX_POSITION - len);
            }
        }
#endif
        len += SafeTSNPrintf(&buffer[len], sizeof(buffer) - len, " (%s:%d)",  pFileNameTop, line);
    }

    // Always set a newline even for an overflow
    len = std::min<size_t>(len, sizeof(buffer) - 2);
    buffer[len++] = '\n';
    buffer[len] = '\0'; // Just in case even though the length is specified

    // Output once
    nn::dbg::detail::PutString(buffer, len);
#else
    NN_UNUSED_VAR(level);
    NN_UNUSED_VAR(funcName);
    NN_UNUSED_VAR(fileName);
    NN_UNUSED_VAR(line);
    NN_UNUSED_VAR(fmt);
#endif
}

/****************************************************************************/


/****************************************************************************/
}
}  // namespace dbg
}  // namespace nn
