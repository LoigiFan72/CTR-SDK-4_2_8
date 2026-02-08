/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_Util.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <cstdarg>
#include <cstdio>
#include <algorithm>

namespace nn{ namespace test{

void
FillBytesRandom(u8* pBuffer, size_t len)
{
    while( len > 0 )
    {
        int data = ::std::rand();

        size_t copyLen = ::std::min(sizeof(data), len);
        ::std::memcpy(pBuffer, &data, copyLen);
        len -= copyLen;
        pBuffer += copyLen;
    }
}

}}  // namespace nn::test

