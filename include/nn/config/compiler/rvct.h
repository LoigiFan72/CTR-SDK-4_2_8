/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rvct.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47706 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_CONFIG_COMPILER_RVCT_H_
#define NN_CONFIG_COMPILER_RVCT_H_


//
//
//

//---------------------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FILE_NAME            __MODULE__

//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
#define NN_FUNCTION             __PRETTY_FUNCTION__


//---------------------------------------------------------------------------
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_ATTRIBUTE_ALIGN(n)   __attribute__ ((aligned(n)))



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
#define NN_UNUSED_VAR(var)      ((void)&var);

//



//
//

//---------------------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------------------
#define NN_DLL_IMPORT           __declspec(dllimport)

//---------------------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------------------
#define NN_DLL_EXPORT           __declspec(dllexport)

//



#define NN_IS_UNUSED_VAR        __attribute__((unused))
#define NN_IS_UNUSED_FUNC       __attribute__((unused))

#define NN_WEAK_SYMBOL          __weak
#define NN_ASM                  __asm
#define NN_PACKED               __packed

#define NN_FORCE_INLINE         __forceinline
#define NN_ATTRIBUTE_PACK       __attribute__ ((packed))
#define NN_ATTRIBUTE_DEPRECATED __attribute__ ((deprecated))
#define NN_ATTRIBUTE_FORMAT(type, m, n) \
                                __attribute__ ((format(type,m,n)))
#define NN_ATTRIBUTE_NORETURN   __attribute__ ((noreturn))

#define NN_LSYM( no )           no
#define NN_BSYM( no )           %b##no
#define NN_FSYM( no )           %f##no

#define NN_DEFINE_MODULE_ID_STRING(name, value) \
    const char name[] __attribute__((section(".module_id"))) = (value)

#define NN_DEFINE_STATIC_INIT_ARRAY(array, symbol) \
static void (*const array[])() __attribute__((used, section(".static_init"))) = { &symbol }


#define NN_ATTR_PRIVATE_SECTION_2(a, b) \
    __attribute__((section(#a "." #b)))

#define NN_ATTR_PRIVATE_SECTION_1(a, b) \
    NN_ATTR_PRIVATE_SECTION_2(a, b)

#define NN_ATTR_PRIVATE_SECTION \
    NN_ATTR_PRIVATE_SECTION_1(NN_FILE_NAME, __LINE__)

#define NN_FUNC_ATTR_PRIVATE_SECTION NN_ATTR_PRIVATE_SECTION

// TORIAEZU: Strange for it to be here since there is no compiler dependency
#define NN_PADDING1             int :  8
#define NN_PADDING2             int : 16
#define NN_PADDING3             int : 24
#define NN_PADDING4             int : 32



/* NN_CONFIG_COMPILER_RVCT_H_ */
#endif
