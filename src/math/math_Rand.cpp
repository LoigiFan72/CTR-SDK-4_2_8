/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Rand.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Rand.h>
#include <nn/types.h>

namespace nn { namespace math {

void RandomGenerator::SetSeed(u64 seed)
{
    m_x = seed;
    m_mul = (1566083941LL << 32) + 1812433253LL;
    m_add = 2531011;
}

u32 RandomGenerator::Generate(u32 max)
{
    m_x = m_mul * m_x + m_add;
    if (max == 0)
    {
        return static_cast<u32>(m_x >> 32);
    }
    else
    {
        return static_cast<u32>(((m_x >> 32) * max) >> 32);
    }
}

// Function definition of private RandomGenerator class.
void RamdomGenerator::SetSeed(u64 seed)
{
    m_x = seed;
    m_mul = (1566083941LL << 32) + 1812433253LL;
    m_add = 2531011;
}

u32 RamdomGenerator::Generate(u32 max)
{
    m_x = m_mul * m_x + m_add;
    if (max == 0)
    {
        return static_cast<u32>(m_x >> 32);
    }
    else
    {
        return static_cast<u32>(((m_x >> 32) * max) >> 32);
    }
}


}}  // math
