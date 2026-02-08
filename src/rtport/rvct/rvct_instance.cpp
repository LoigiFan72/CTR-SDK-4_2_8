/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rvct_string.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48158 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/config.h>
#include <nn/assert.h>
#include <string>

#ifndef NN_DEBUGGER_ARM_REALVIEW

namespace std
{
    template class basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
    template class basic_string<char, char_traits<char>, allocator<char> >;
}


#else



#endif
