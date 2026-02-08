/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     types.h

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

#ifndef NN_TYPES_H_
#define NN_TYPES_H_


// TORIAEZU: Transition period provision
#ifdef  SDK_ASM
    #define NN_SWITCH_INCLUDE_FROM_NON_C
#endif


#ifdef  NN_SWITCH_INCLUDE_FROM_NON_C
#else  // ifdef NN_SWITCH_INCLUDE_FROM_NON_C

	#if !defined(_MSC_VER) || (_MSC_VER >= 1500)
	    #include <inttypes.h>
	#endif

    #include <stddef.h>
    #include <stdarg.h>

    #ifndef __cplusplus
        #include <stdbool.h>
    #endif


//
//
//

    //
    typedef unsigned char           u8;
    //
    typedef unsigned short int      u16;
    //
    typedef unsigned int            u32;
    //
    typedef unsigned long long int  u64;

    //
    typedef signed char             s8;
    //
    typedef signed short int        s16;
    //
    typedef signed int              s32;
    //
    typedef signed long long int    s64;

    //
    typedef intptr_t                sptr;
    //
    typedef uintptr_t               uptr;

    //
    typedef char                    char8;
    //
    typedef wchar_t                 char16;

    typedef volatile u8             vu8;
    typedef volatile u16            vu16;
    typedef volatile u32            vu32;
    typedef volatile u64            vu64;

    typedef volatile s8             vs8;
    typedef volatile s16            vs16;
    typedef volatile s32            vs32;
    typedef volatile s64            vs64;

    //
    typedef float                   f32;
    //
    typedef double                  f64;

    typedef volatile f32            vf32;
    typedef volatile f64            vf64;

    //
    typedef unsigned char           bit8;
    //
    typedef unsigned short          bit16;
    //
    typedef unsigned int            bit32;
    //
    typedef unsigned long long int  bit64; 

//


    /*
        Macros and types used with io_register_list_XX.h
     */

    typedef u8      REGType8;
    typedef u16     REGType16;
    typedef u32     REGType32;
    typedef u64     REGType64;

    typedef vu8     REGType8v;
    typedef vu16    REGType16v;
    typedef vu32    REGType32v;
    typedef vu64    REGType64v;

    #ifdef __cplusplus
    namespace nn
    {
        typedef bit64 ProgramID;    // TODO: Delete
        typedef bit64 ProgramId;

        struct ProductCode
        {
            char    code[16];
        };

        struct ProductInfo
        {
            char    productCode[16];
            bit16   companyCode;
            u16     remasterVersion;
        };
    }
    #endif

    #if defined(SDK_128M) || defined(SDK_64M) || defined(SDK_WIN32)
        typedef int     BOOL;
        #define TRUE    1
        #define FALSE   0

        typedef struct
        {
            u32 w[3];
        }
        u96;

        typedef struct
        {
            u32 w[4];
        }
        u128;

        typedef volatile u96    vu96;
        typedef volatile u128   vu128;

        typedef u96     REGType96;
        typedef u128    REGType128;
        typedef vu96    REGType96v;
        typedef vu128   REGType128v;
    #endif

#endif // ifdef NN_SWITCH_INCLUDE_FROM_NON_C else


/* NN_TYPES_H_ */
#endif
