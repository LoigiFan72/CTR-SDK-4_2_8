/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_QueryOptimalBucketCount.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#include <nn/fslow/fslow_QueryOptimalBucketCount.h>

namespace nn { namespace fslow {

u32 QueryOptimalBucketCount(u32 countEntries)
{
    if (countEntries <= 3)
    {
        // When the number of entries is extremely small, return a fixed size for the packet number.
        return 3;
    }
    if (countEntries <= 19)
    {
        // When the number of entries is less than 20, return an odd number
        return countEntries | 1;
    }

    // When the number of entries exceeds 20, prune with small value prime numbers.
    // 
    u32 i;
    for (i = 0; i < 100; i++)
    {
        u32 candidate = (countEntries + i);
        if (
            (candidate % 2) != 0 &&
            (candidate % 3) != 0 &&
            (candidate % 5) != 0 &&
            (candidate % 7) != 0 &&
            (candidate % 11) != 0 &&
            (candidate % 13) != 0 &&
            (candidate % 17) != 0
        )
        {
            return candidate;
        }
    }
    return countEntries | 1;
}

}}
