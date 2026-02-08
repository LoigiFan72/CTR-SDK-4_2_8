/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Argument.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#include <nn.h>
#include <nn/dbg/dbg_Argument.h>
#include <nn/dbg/dbg_ArgumentPrivate.h>

#ifdef NN_CTR_ARG_AVAILABLE

using namespace nn::dbg::CTR;

namespace
{
    //---- argument buffer
    bit8 s_ArgBuffer[ NN_DBG_ARG_BUFFER_SIZE ] = {1}; // The default data is dummy data. So it won't be set to the bss region

    //---- current argument buffer
    const void* s_pCurrentArgBuffer;
    size_t      s_CurrentArgBufferSize;

    //---- argv[0] equivalent string
    const char* s_pApplicationStr = NN_DBG_ARG_ARGV0_STRING;

    //---- argumento information structure (fixed region)
    const nn::dbg::CTR::ArgArea s_ArgInfo __attribute__((section(".ARM.__at_0x100ff0"))) =
    {
        NN_DBG_ARG_MAGIC_NUM,
        reinterpret_cast<const void*>(&s_ArgBuffer),
        sizeof(s_ArgBuffer),
        NN_DBG_ARG_MAGIC_NUM,
    };

    //---- argc, argv information
    int         s_Argc = 0;
    const char* s_pArgv = NULL;
    bool        s_IsInitialized = false;

    //---- binary information
    const void* s_pBinaryArea = NULL;
    size_t      s_BinaryAreaSize = 0;

    //---- for option parsing
    const char* s_pOptArg = NULL;
    int         s_OptInd  = 1;
    int         s_OptOpt  = 0;
}

//#define offsetof(type, member) ((size_t)&(type*)0->member)

namespace nn {
namespace dbg {
namespace CTR {
    static const char *match_opt(int optchar, const char *optstring);

    //----------------------------------------------------------------
    static void Setup( const void* pBuffer, size_t size )
    {
        if ( ! s_IsInitialized )
        {
            s_Argc = 0;
            s_pArgv = NULL;
            s_pBinaryArea = NULL;
            s_BinaryAreaSize = 0;

            s_pOptArg = NULL;
            s_OptInd = 1;
            s_OptOpt = 0;

            s_pCurrentArgBuffer = pBuffer;
            s_CurrentArgBufferSize = size;

            // Magic number check
            const ArgInfoHeader* pHeader = reinterpret_cast<const ArgInfoHeader*>(pBuffer);
            if ( pHeader->magic == NN_DBG_ARG_MAGIC_NUM_ARG )
            {
                // Gets information from the obtained buffer
                s_pArgv = reinterpret_cast<const char*>( reinterpret_cast<const bit8*>(pHeader) + pHeader->argStart );
                s_Argc = pHeader->argNum + 1; // +1 since includes self
                s_pBinaryArea = reinterpret_cast<const void*>( reinterpret_cast<const bit8*>(pHeader) + pHeader->binaryStart );
                s_BinaryAreaSize = pHeader->binarySize;
            }

            s_IsInitialized = true;
        }
    }
    //----------------------------------------------------------------
    static void Setup(void)
    {
        if ( ! s_IsInitialized )
        {
            // Magic number check
            if ( s_ArgInfo.magic1 == NN_DBG_ARG_MAGIC_NUM && s_ArgInfo.magic2 == NN_DBG_ARG_MAGIC_NUM )
            {
                Setup( s_ArgInfo.pArgArea, s_ArgInfo.areaSize );
            }
        }
    }
    //----------------------------------------------------------------
    static void Reset(void)
    {
        s_IsInitialized = false;
    }

    //----------------------------------------------------------------
    // Gets as a binary
    const void* GetArgBinary( void )
    {
        Setup();
        return s_pBinaryArea;
    }
    //----------------------------------------------------------------
    // Gets as a binary
    size_t GetArgBinarySize( void )
    {
        Setup();
        return s_BinaryAreaSize;
    }

    //----------------------------------------------------------------
    // Gets the number of arguments
    //     For example, return value is 3 when "-T 123" is given
    //     1 when there are no arguments
    //     0 when there is no argument information region
    int GetArgc(void)
    {
        Setup();
        return s_Argc;
    }

    //----------------------------------------------------------------
    // Gets arguments
    //    For example, when "-T 123" is set in the arguments
    //    argv[0]=Arg0String argv[1]="-T" argv[2]="123"
    //    When there is no argument information region, NULL is returned regardless of the index
    const char* GetArgv( int index )
    {
        Setup();
        int argc = GetArgc();

        // When specification is outside the argument range or when there is no argument buffer
        if ( index < 0 || index >= argc || ! s_pArgv )
        {
            return NULL;
        }

        // When argv[0] is acquired
        if ( index == 0 )
        {
            return s_pApplicationStr;
        }

        const char* p = s_pArgv;
        for( index--; index>0; index-- )
        {
            int argsize = *(p + offsetof(ArgvFormat, size)) + *(p + offsetof(ArgvFormat, size) + 1)*256;
            p += 2 + argsize + 1; // Advances size information 2 bytes + string + "\0"
        }

        return (p + offsetof(ArgvFormat, string));
    }

    //----------------------------------------------------------------
    // Option analysis
    int GetOpt( const char *optstring )
    {
        Setup();

        static bool end_of_option = false;
        int     optchar;
        const char *arg;
        const char *opt;
        const char *optarg;

        s_pOptArg = NULL;
        s_OptOpt = 0;

        // Reset if optstring is NULL
        if (optstring == NULL)
        {
            s_OptInd = 1;
            end_of_option = false;
            return 0;
        }

        // Get command line arguments
        arg = GetArgv(s_OptInd);

        if (arg == NULL)
        {
            return -1;
        }

        if (optstring[0] == '-')           // Minus Mode
        {
            s_OptInd++;                  // Consume arguments

            // Normal argument when it does not start with '-'
            if (end_of_option || arg[0] != '-')
            {
                s_pOptArg = arg;          // Normal arguments are also set to OptArg.
                return 1;
            }

            // Option analysis
            optchar = arg[1];

            if (optchar == '-')            // End of options when '--' is encountered
            {
                end_of_option = true;      // Normal arguments from here on
                return GetOpt(optstring);
            }
        }
        else                               // normal mode
        {
            // Normal argument when it does not start with '-'
            if (end_of_option || arg[0] != '-')
            {
                return -1;                 // OptArg remains NULL
            }

            s_OptInd++;                  // Consume arguments

            // Option analysis
            optchar = arg[1];

            if (optchar == '-')            // End of options when '--' is encountered
            {
                end_of_option = true;      // Normal arguments from here on
                return -1;
            }

        }

        opt = match_opt(optchar, optstring);

        if (opt == NULL)
        {
            s_OptOpt = optchar;                // Unknown option
            return '?';
        }

        if (opt[1] == ':')                     // OptArg search specification?
        {
            // Continuously specified similar to -oAAA (gnu expansion)
            if ( arg[2] != '\0' )
            {
                s_pOptArg = &arg[2];           // Current options are viewed as-is
            }
            // Determine with the next argument
            else
            {
                optarg = GetArgv(s_OptInd);

                if (optarg == NULL || optarg[0] == '-')
                {
                    s_pOptArg = NULL;

                    if (opt[2] != ':')        // '::' Or not?
                    {
                        s_OptOpt = optchar;   // OptArg not present.
                        return '?';
                    }
                }
                else
                {
                    s_pOptArg = optarg;
                    s_OptInd++;              // Consume arguments
                }
            }
        }
        return optchar;
    }

    //----------------
    // GetOpt() sub-routine
    static const char *match_opt(int optchar, const char *optstring)
    {
        if (optstring[0] == '-' || optstring[0] == '+')
        {
            optstring++;
        }

        if (optchar != ':')
        {
            while (*optstring)
            {
                if (optchar == *optstring)
                {
                    return optstring;
                }
                optstring++;
            }
        }
        return NULL;
    }

    //----------------------------------------------------------------
    // Force assignment of the argument buffer
    void SetArgumentBuffer( const void *pBuffer, size_t size )
    {
        Reset();
        Setup( pBuffer, size );
    }
    //----------------------------------------------------------------
    // Get argument buffer row region
    const void *GetArgumentBuffer(void)
    {
        return s_pCurrentArgBuffer;
    }
    size_t GetArgumentBufferSize(void)
    {
        return s_CurrentArgBufferSize;
    }
    //----------------------------------------------------------------
    // Equivalent to option parsing optind
    int GetOptInd( void )
    {
        return s_OptInd;
    }
    //----------------------------------------------------------------
    // Equivalent to option parsing optarg
    const char* GetOptArg( void )
    {
        return s_pOptArg;
    }
    //----------------------------------------------------------------
    // Equivalent to option parsing optopt
    int GetOptOpt( void )
    {
        return s_OptOpt;
    }
}
}
}

#else

//----------------------------------------------------------------
// For Release ROM

namespace
{
    //---- argumento information structure (fixed region)
    const nn::dbg::CTR::ArgArea s_ArgInfo __attribute__((section(".ARM.__at_0x100ff0"))) =
    {
        0,
        NULL,
        NULL,
        1, // Set to a value different than the first member's
    };
}

namespace nn {
namespace dbg {
namespace CTR {

    const void* GetArgBinary( void )
    {
        return NULL;
    }
    size_t GetArgBinarySize( void )
    {
        return 0;
    }
    int GetArgc(void)
    {
        return 0;
    }
    const char* GetArgv( int )
    {
        return NULL;
    }
    int GetOpt(const char *)
    {
        return -1;
    }
    void SetArgumentBuffer( const void*,  size_t )
    {
    }
    const void *GetArgumentBuffer(void)
    {
        return NULL;
    }
    size_t GetArgumentBufferSize(void)
    {
        return 0;
    }
    int GetOptInd( void )
    {
        return -1;
    }
    const char* GetOptArg( void )
    {
        return NULL;
    }
    int GetOptOpt( void )
    {
        return -1;
    }
}
}
}
#endif
