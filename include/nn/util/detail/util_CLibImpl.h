/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_CLibImpl.h

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

#ifndef NN_UTIL_DETAIL_UTIL_CLIBIMPL_H_
#define NN_UTIL_DETAIL_UTIL_CLIBIMPL_H_

#include <nn/types.h>
#include <nn/util/util_StaticAssert.h>
#include <nn/util/util_TypeTraits.h>

#ifdef __cplusplus
    /* Please see man pages for details 
        
    */
    #define NN_EXTERN_C extern "C"
    #define NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(cname, cppname, size, alignment_holder_type) \
        typedef union cname \
        { \
            char buf[size]; \
            alignment_holder_type alignment_holder; \
            NN_STATIC_ASSERT((size) == sizeof(cppname) && ::nn::util::alignment_of<alignment_holder_type>::value == ::nn::util::alignment_of<cppname>::value); \
        } cname

#else
    #define NN_EXTERN_C extern
    #define NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(cname, cppname, size, alignment_holder_type) \
        typedef union cname \
        { \
            char buf[size]; \
            alignment_holder_type alignment_holder; \
        } cname
#endif

#define NN_UTIL_DETAIL_CLIBIMPL_DEFINE_ABSTRACT_BUFFER_CLASS(name) typedef struct { bit8 dummy; } name;

#define NN_UTIL_DETAIL_CLIBIMPL_DECLARE_CONVERSION(name, fromC, toC) \
    NN_EXTERN_C toC* name(fromC*); \
    NN_EXTERN_C const toC* name##Const(const fromC*)

#define NN_UTIL_DETAIL_CLIBIMPL_DEFINE_CONVERSION(name, fromC, toC, fromCpp, toCpp) \
    NN_EXTERN_C toC* name(fromC* p) { return reinterpret_cast<toC*>(static_cast<toCpp*>(reinterpret_cast<fromCpp*>(p))); } \
    NN_EXTERN_C const toC* name##Const(const fromC* p) { return reinterpret_cast<const toC*>(static_cast<const toCpp*>(reinterpret_cast<const fromCpp*>(p))); }

#endif

/* 
    
    
    






    


















    
    




	
*/
