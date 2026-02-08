/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Misc.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47344 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_MISC_H_
#define NN_UTIL_UTIL_MISC_H_

#include <nn/dbg/dbg_SmallSet.h>

#ifdef __cplusplus

namespace nn { namespace util {

    // int array[10];
    // GetArraySize(array) -> 10
    template <typename T, size_t Num>
    size_t GetArraySize(T (&a)[Num])
    {
        NN_UNUSED_VAR(a);
        return Num;
    }

    template <size_t V>
    struct SizeTValue
    {
        enum { value = V };
    };

    // int array[10];
    // GetArraySizeT(array).value -> 10
    template <typename T, size_t Num>
    const SizeTValue<Num>& GetArraySizeT(T (&a)[Num])
    {
        NN_UNUSED_VAR(a);
        return *reinterpret_cast<SizeTValue<Num>*>(1);
    }

    // int array[10];
    // sizeof(*NumOfElementsT(array)) -> 10
    template <typename T, size_t Num>
    char (*NumOfElementsT(T (&a)[Num]))[Num];
}}

#endif // __cplusplus


#endif // ifndef NN_UTIL_UTIL_MISC_H_
