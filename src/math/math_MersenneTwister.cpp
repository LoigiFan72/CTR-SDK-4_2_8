/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_MersenneTwister.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47665 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/assert.h>
#include <nn/math/math_MersenneTwister.h>
#include <nn/crypto.h>

namespace nn { namespace math {

    const int   MersenneTwister::PARAMETER_N;

    namespace
    {
        inline bit32 MixMsb2(bit32 v)
        {
            return v ^ (v >> 30);
        }

        bit32 GenerateInitialValue(const bit32* pState, int index, bit32 d)
        {
            const bit32 s0 = pState[index + 0];
            const bit32 s1 = pState[index + 1];

            const bit32 a = MixMsb2(s0);
            const bit32 b = s1 ^ (a * d);

            return b;
        }
    }
    // anonymous namespace



    /* ------------------------------------------------------------------------
            public
       ------------------------------------------------------------------------ */

    void MersenneTwister::Initialize()
    {
        crypto::GenerateRandomBytes(m_State, sizeof(m_State));
        m_Index = 0;
    }

    void MersenneTwister::Initialize(bit32 seed)
    {
        m_State[0] = seed;

        for( int i = 1; i < PARAMETER_N; i++ )
        {
            const bit32 v = MixMsb2(m_State[i - 1]);
            m_State[i] = v * 0x6c078965 + i;
        }

        m_Index = 0;
    }

    void MersenneTwister::Initialize(const bit32* pSeed, int num)
    {
        Initialize(0x012bd6aa);

        int stateIndex = 0;

        {
            const int numLoop = Max(PARAMETER_N, num);
            int seedIndex = 0;

            for( int i = 0; i < numLoop; ++i )
            {
                const bit32 v = GenerateInitialValue(m_State, stateIndex, 0x0019660d);

                stateIndex++;

                m_State[stateIndex] = v + pSeed[seedIndex] + seedIndex;

                if( stateIndex >= PARAMETER_N - 1 )
                {
                    m_State[0] = m_State[PARAMETER_N - 1];
                    stateIndex = 0;
                }

                seedIndex++;
                if( seedIndex >= num )
                {
                    seedIndex = 0;
                }
            }
        }

        for( int i = 0; i < PARAMETER_N - 1; ++i )
        {
            const bit32 v = GenerateInitialValue(m_State, stateIndex, 0x5d588b65);

            stateIndex++;

            m_State[stateIndex] = v - stateIndex;

            if( stateIndex >= PARAMETER_N - 1 )
            {
                m_State[0] = m_State[PARAMETER_N - 1];
                stateIndex = 0;
            }
        }

        m_State[0] = 0x80000000;
    }

    void MersenneTwister::SaveState(MersenneTwister::State* pStateBuffer)
    {
        NN_POINTER_TASSERT_(pStateBuffer);

        for( int i = 0; i < PARAMETER_N; ++i )
        {
            pStateBuffer->state[i] = m_State[i];
        }

        pStateBuffer->index = m_Index;
    }

    void MersenneTwister::RestoreState(const MersenneTwister::State* pStateBuffer)
    {
        NN_POINTER_TASSERT_(pStateBuffer);
        NN_MINMAX_TASSERT_(pStateBuffer->index, 0, PARAMETER_N - 1);

        for( int i = 0; i < PARAMETER_N; ++i )
        {
            m_State[i] = pStateBuffer->state[i];
        }

        m_Index = pStateBuffer->index;
    }

    u32 MersenneTwister::GenerateRandomU32()
    {
        u32 v;

        // Updates the state
        {
            int currIndex = m_Index;
            int nextIndex = currIndex + 1;
            int baseIndex = currIndex + PARAMETER_M;

            if( nextIndex >= PARAMETER_N )
            {
                nextIndex -= PARAMETER_N;
            }
            if( baseIndex >= PARAMETER_N )
            {
                baseIndex -= PARAMETER_N;
            }

            v = GenerateXkn(m_State[baseIndex], m_State[currIndex], m_State[nextIndex]);

            m_State[currIndex] = v;
            m_Index = nextIndex;
        }


        // tempering
        v ^= (v >> PARAMETER_U);
        v ^= (v << PARAMETER_S) & PARAMETER_B;
        v ^= (v << PARAMETER_T) & PARAMETER_C;
        v ^= (v >> PARAMETER_L);

        return v;
    }

    void MersenneTwister::GenerateRandomBytes(void* p, size_t size)
    {
        uptr begin  = reinterpret_cast<uptr>(p);
        uptr end    = begin + size;
        uptr begin4 = RoundUp(begin, 4);
        uptr end4   = RoundDown(end, 4);

        if( begin < begin4 )
        {
            bit32 v = GenerateRandomU32();
            std::memcpy(reinterpret_cast<void*>(begin), &v, begin4 - begin);
        }

        {
            bit32* p32  = reinterpret_cast<bit32*>(begin4);
            bit32* pEnd = reinterpret_cast<bit32*>(end4);

            while( p32 < pEnd )
            {
                *p32++ = GenerateRandomU32();
            }
        }

        if( end4 < end )
        {
            bit32 v = GenerateRandomU32();
            std::memcpy(reinterpret_cast<void*>(end4), &v, end - end4);
        }
    }



    /* ------------------------------------------------------------------------
            private
       ------------------------------------------------------------------------ */

    inline bit32 MersenneTwister::MixBits(bit32 u, bit32 l)
    {
        return (u & MIX_MASK) | (l & ~MIX_MASK);
    }

    inline bit32 MersenneTwister::GenerateXkn(bit32 xkm, bit32 xk, bit32 xk1)
    {
        bit32 v = (MixBits(xk, xk1) >> 1);

        if( (xk1 & 1) != 0 )
        {
            v ^= PARAMETER_A;
        }

        return xkm ^ v;
    }



}}

