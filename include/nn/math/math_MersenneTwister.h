/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_MersenneTwister.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47802 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_MATH_MATH_MERSENNETWISTER_H_
#define NN_MATH_MATH_MERSENNETWISTER_H_

#include <nn/types.h>

namespace nn { namespace math {

    /* ------------------------------------------------------------------------
            Class definitions
       ------------------------------------------------------------------------ */

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    class MersenneTwister
    {
    private:
        static const int   PARAMETER_W  =  32;
        static const int   PARAMETER_N  = 624;
        static const int   PARAMETER_M  = 397;
        static const int   PARAMETER_R  =  31;
        static const int   PARAMETER_U  =  11;
        static const int   PARAMETER_S  =   7;
        static const int   PARAMETER_T  =  15;
        static const int   PARAMETER_L  =  18;

        static const bit32 PARAMETER_A  = 0x9908b0df;
        static const bit32 PARAMETER_B  = 0x9d2c5680;
        static const bit32 PARAMETER_C  = 0xefc60000;

        static const bit32 MIX_MASK = (~0u << PARAMETER_R);

    public:
        //----------------------------------------------------------------------
        //
        //----------------------------------------------------------------------
        struct State
        {
            //----------------------------------------------------------------------
            //
            //----------------------------------------------------------------------
            int     index;

            //----------------------------------------------------------------------
            //
            //----------------------------------------------------------------------
            bit32   state[PARAMETER_N];
        };

    private:
        int     m_Index;
        bit32   m_State[PARAMETER_N];

    public:

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void Initialize();

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void Initialize(bit32 seed);

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void Initialize(const bit32* pSeed, int numSeed);

        //----------------------------------------------------------------------
        //
        //----------------------------------------------------------------------
        void Finalize(){}

    //

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void SaveState(MersenneTwister::State* pStateBuffer);

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void RestoreState(const MersenneTwister::State* pStateBuffer);

    //

    //
    //

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        u32 GenerateRandomU32();

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        u64 GenerateRandomU64();

        //----------------------------------------------------------------------
        //
        //
        //
        //----------------------------------------------------------------------
        f32 GenerateRandomF32();

        //----------------------------------------------------------------------
        //
        //
        //
        //----------------------------------------------------------------------
        f64 GenerateRandomF64();

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        u32 GenerateRandomN(u16 num);

        //----------------------------------------------------------------------
        //
        //
        //
        //
        //
        //
        //
        //----------------------------------------------------------------------
        void GenerateRandomBytes(void* p, size_t size);

    //


    private:
        u32 GenerateRandomU24()
        {
            return GenerateRandomU32() >> 8;
        }

        static inline bit32 MixBits(bit32 u, bit32 l);
        static inline bit32 GenerateXkn(bit32 xkm, bit32 xk, bit32 xk1);
    };



    /* ------------------------------------------------------------------------
            Inline member function definitions
       ------------------------------------------------------------------------ */

    inline u64 MersenneTwister::GenerateRandomU64()
    {
        const u32 lo = GenerateRandomU32();
        const u32 hi = GenerateRandomU32();
        return (static_cast<u64>(hi) << 32) | lo;
    }

    inline f32 MersenneTwister::GenerateRandomF32()
    {
        return GenerateRandomU24() * (1.0f / (1ull << 24));
    }

    inline f64 MersenneTwister::GenerateRandomF64()
    {
        static const int RESOLUTION = 53;
        static const int U32_BITS   = 32;
        static const int A_SHIFT    = (2 * U32_BITS - RESOLUTION) / 2;
        static const int B_SHIFT    = (2 * U32_BITS - RESOLUTION) - A_SHIFT;
        //static const int A_BITS     = U32_BITS - A_SHIFT;
        static const int B_BITS     = U32_BITS - B_SHIFT;

        u32 a = (GenerateRandomU32() >> A_SHIFT);
        u32 b = (GenerateRandomU32() >> B_SHIFT);

        return (1.0 * a * (1u << B_BITS) + b) * (1.0 / (1ull << RESOLUTION));
    }

    inline u32 MersenneTwister::GenerateRandomN(u16 max)
    {
        return static_cast<u32>((static_cast<u64>(GenerateRandomU32()) * max) >> 32);
    }



}}


/* NN_MATH_MATH_MERSENNETWISTER_H_ */
#endif
