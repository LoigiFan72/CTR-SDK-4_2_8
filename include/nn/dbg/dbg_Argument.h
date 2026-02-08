/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Argument.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/
/* Please see man pages for details 
    


    
*/

#ifndef DBG_ARGUMENT_H_
#define DBG_ARGUMENT_H_

#ifdef NN_BUILD_VERBOSE
#define NN_CTR_ARG_AVAILABLE
#else
#ifdef NN_CTR_ARG_AVAILABLE
#undef NN_CTR_ARG_AVAILABLE
#endif
#endif

// Magic number
#define NN_DBG_ARG_MAGIC_NUM         (0x597dfbd9UL)  // For confirming buffer existence
#define NN_DBG_ARG_MAGIC_NUM_ARG     (0xfddb597dUL)  // For argument

#ifdef __cplusplus
namespace nn {
namespace dbg {
namespace CTR {

    /* Please see man pages for details 
      
    */
    const size_t ArgBufferSize = 0x1000;

    /* Please see man pages for details 
      
    */
    const char Argv0String[] = "application";


    // Start argument buffer information (placed at 0x00100ff0, 16 bytes)
    struct ArgArea
    {
        bit32       magic1;      // Magic number
        const void* pArgArea;    // Pointer to the buffer region
        size_t      areaSize;    // Buffer region size
        bit32       magic2;      // Magic number
    };

    // Header for the start argument buffer
    struct ArgInfoHeader
    {
        bit32       magic;       // Magic number
        bit16       argStart;    // Position where argument starts
        bit16       argNum;      // Number of arguments
        bit16       binaryStart; // Position where binary starts
        bit16       binarySize;  // binary size
        bit32       reserved;
    };

    // The argument format is size (2 bytes) and string (including \0)
    struct ArgvFormat
    {
        bit16       size;
        char        string[2]; // The size of 2 is provisional
    };

/* Please see man pages for details 
    
    
 */
    //---------------- Acquisition with binary
    /* Please see man pages for details 
        
    */
    const void* GetArgBinary( void );
    /* Please see man pages for details 
        
    */
    size_t      GetArgBinarySize( void );

    //---------------- Argument acquisition
    /* Please see man pages for details 
        
    */
    int         GetArgc( void );
    /* Please see man pages for details 
        
        
    */
    const char* GetArgv( int n );

    //---------------- Option string
    /* Please see man pages for details 
        
        
    */
    int         GetOpt( const char* optstring );
    /* Please see man pages for details 
        
    */
    int         GetOptInd( void );
    /* Please see man pages for details 
        
    */
    const char* GetOptArg( void );
    /* Please see man pages for details 
        
    */
    int         GetOptOpt( void );
/*  

*/
}
}
}

#define NN_DBG_ARG_BUFFER_SIZE   (nn::dbg::CTR::ArgBufferSize)
#define NN_DBG_ARG_ARGV0_STRING  (nn::dbg::CTR::Argv0String)

#endif  // ifdef __cplusplus


#endif  // DBG_ARGUMENT_H_

