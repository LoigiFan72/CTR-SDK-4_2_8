/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_TinyMt.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47727 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/assert.h>
#include <nn/math/math_TinyMt.h>
#include <nn/crypto.h>
#include <algorithm>

namespace nn { namespace math {

    namespace
    {
        inline bit32 MixMsb2(bit32 v)
        {
            return v ^ (v >> 30);
        }

        inline bit32 MixMsb5(bit32 v)
        {
            return v ^ (v >> 27);
        }
    }
    // anonymous namespace



    /* ------------------------------------------------------------------------
            public
       ------------------------------------------------------------------------ */

    void TinyMt::Initialize()
    {
        crypto::GenerateRandomBytes(m_State, sizeof(m_State));
    }

    void TinyMt::Initialize(bit32 seed)
    {
        m_State[0] = seed;
        m_State[1] = PARAMETER_MAT1;
        m_State[2] = PARAMETER_MAT2;
        m_State[3] = PARAMETER_TMAT;;

        {
            for( int i = 1; i < MIN_LOOP; ++i )
            {
                const bit32 v = MixMsb2(m_State[(i - 1) % PARAMETER_N]);
                m_State[i % PARAMETER_N] ^= v * 0x6c078965 + i;
            }
        }

        FinalizeInitialization();
    }

    void TinyMt::Initialize(const bit32* pSeed, int numSeed)
    {
        m_State[0] = 0;
        m_State[1] = PARAMETER_MAT1;
        m_State[2] = PARAMETER_MAT2;
        m_State[3] = PARAMETER_TMAT;;

        {
            const int numLoop = Max(numSeed + 1, MIN_LOOP) - 1;

            GenerateInitialValuePlus(m_State, 0, numSeed);

            int offset = 1;
            for( int i = 0; i < numLoop; ++i )
            {
                const bit32 seed = (i < numSeed) ? pSeed[i]: 0;
                GenerateInitialValuePlus(m_State, (offset + i) % PARAMETER_N, seed);
            }

            offset = numLoop + 1;
            for( int i = 0; i < PARAMETER_N; ++i )
            {
                GenerateInitialValueXor(m_State, (offset + i) % PARAMETER_N);
            }
        }

        FinalizeInitialization();
    }

    void TinyMt::SaveState(TinyMt::State* pStateBuffer)
    {
        NN_POINTER_TASSERT_(pStateBuffer);

        std::memcpy(pStateBuffer->state, m_State, sizeof(pStateBuffer->state));
    }

    void TinyMt::RestoreState(const TinyMt::State* pStateBuffer)
    {
        NN_POINTER_TASSERT_(pStateBuffer);

        std::memcpy(m_State, pStateBuffer->state, sizeof(m_State));
    }

    u32 TinyMt::GenerateRandomU32()
    {
        // Update the state
        const bit32 a = (m_State[0] & BIT31_MASK) ^ m_State[1] ^ m_State[2];
        const bit32 b = m_State[3];
        const bit32 c = a ^ (a << 1);
        const bit32 d = b ^ (b >> 1) ^ c;

        const bit32 s0 = m_State[1];
              bit32 s1 = m_State[2];
              bit32 s2 = c ^ (d << 10);
        const bit32 s3 = d;

        if( (d & 1) != 0 )
        {
            s1 ^= PARAMETER_MAT1;
            s2 ^= PARAMETER_MAT2;
        }

        m_State[0] = s0;
        m_State[1] = s1;
        m_State[2] = s2;
        m_State[3] = s3;

        // tempering
        bit32 t = s0 + (s2 >> 8);
        bit32 v = s3 ^ t;

        if( (t & 1) != 0 )
        {
            v ^= PARAMETER_TMAT;
        }

        return v;
    }

    void TinyMt::GenerateRandomBytes(void* p, size_t size)
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

    void TinyMt::GenerateInitialValuePlus(bit32* p, int d, bit32 k)
    {
        bit32& s0 = p[d];
        bit32& s1 = p[(d + 1) % PARAMETER_N];
        bit32& s2 = p[(d + 2) % PARAMETER_N];
        bit32& s3 = p[(d + 3) % PARAMETER_N];

        const bit32 a = MixMsb5(s0 ^ s1 ^ s3) * 0x0019660d;
        const bit32 b = a + d + k;

        s0 = b;
        s1 += a;
        s2 += b;
    }

    void TinyMt::GenerateInitialValueXor(bit32* p, int d)
    {
        bit32& s0 = p[d];
        bit32& s1 = p[(d + 1) % PARAMETER_N];
        bit32& s2 = p[(d + 2) % PARAMETER_N];
        bit32& s3 = p[(d + 3) % PARAMETER_N];

        const bit32 a = MixMsb5(s0 + s1 + s3) * 0x5d588b65;
        const bit32 b = a - d;

        s0 = b;
        s1 ^= a;
        s2 ^= b;
    }

    void TinyMt::FinalizeInitialization()
    {
        const bit32 state031 = (m_State[0] & BIT31_MASK);

        if( (state031   == 0) && (m_State[1] == 0)
         && (m_State[2] == 0) && (m_State[3] == 0) )
        {
            m_State[0] = 'T';
            m_State[1] = 'I';
            m_State[2] = 'N';
            m_State[3] = 'Y';
        }

        for( int i = 0; i < NUM_SKIP; ++i )
        {
            GenerateRandomU32();
        }
    }



}}

