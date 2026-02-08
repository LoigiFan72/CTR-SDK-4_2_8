/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Utility.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_MATH_UTILITY_H_
#define NN_MATH_MATH_UTILITY_H_

#include <nn/types.h>

namespace nn { namespace math {

/* Please see man pages for details 
    
    
*/

    /* Please see man pages for details 
        
    
        
        
        
    */
    template <typename T>
    inline T Abs(T x)
    {
        return (x >= 0) ? x: -x;
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
        
        
    */
    template <typename T, typename U, typename S>
    inline S Max(T a, U b)
    {
        return (a >= b) ? a: b;
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
    */
    template <typename T>
    inline T Max(T a, T b)
    {
        return (a >= b) ? a: b;
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
        
        
    */
    template <typename T, typename U, typename S>
    inline S Min(T a, U b)
    {
        return (a <= b) ? a: b;
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
    */
    template <typename T>
    inline T Min(T a, T b)
    {
        return (a <= b) ? a: b;
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
        
        
        
        
    */
    template <typename T, typename U, typename R, typename S>
    inline S Max(T a, U b, R c)
    {
        return (a >= b) ? ((a >= c) ? a: c) : ((b >= c) ? b: c);
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
        
    */
    template <typename T>
    inline T Max(T a, T b, T c)
    {
        return (a >= b) ? ((a >= c) ? a: c) : ((b >= c) ? b: c);
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
        
        
        
        
    */
    template <typename T, typename U, typename R, typename S>
    inline S Min(T a, U b, R c)
    {
        return (a <= b) ? ((a <= c) ? a: c) : ((b <= c) ? b: c);
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
        
    */
    template <typename T>
    inline T Min(T a, T b, T c)
    {
        return (a <= b) ? ((a <= c) ? a: c) : ((b <= c) ? b: c);
    }

    /* Please see man pages for details 
        
    
        
    
        
        
        
        
        
    */
    template <typename T>
    inline T Clamp(T x, T low, T high)
    {
        return (x >= high) ? high : ((x <= low) ? low: x);
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
    */
    template <typename T>
    inline T RoundUp(T x, u32 base)
    {
        return static_cast<T>( (x + (base - 1)) & ~(base - 1) );
    }

    /* Please see man pages for details 
        
        
    
        
        
        
    */
    template <>
    inline void* RoundUp(void* x, u32 base)
    {
        return reinterpret_cast<void*>( RoundUp(reinterpret_cast<uptr>(x), base) );
    }

    /* Please see man pages for details 
        
        
    
        
        
        
    */
    template <>
    inline const void* RoundUp(const void* x, u32 base)
    {
        return reinterpret_cast<const void*>( RoundUp(reinterpret_cast<uptr>(x), base) );
    }

    /* Please see man pages for details 
        
        
    
        
        
        
        
    */
    template <typename T>
    inline T RoundDown(T x, u32 base)
    {
        return static_cast<T>( x & ~(base - 1) );
    }

    /* Please see man pages for details 
        
        
    
        
        
        
    */
    template <>
    inline void* RoundDown(void* x, u32 base)
    {
        return reinterpret_cast<void*>( RoundDown(reinterpret_cast<uptr>(x), base) );
    }

    /* Please see man pages for details 
        
        
    
        
        
        
    */
    template <>
    inline const void* RoundDown(const void* x, u32 base)
    {
        return reinterpret_cast<const void*>( RoundDown(reinterpret_cast<uptr>(x), base) );
    }

    /* Please see man pages for details 
        
    
        
        
        
        
    */
    template <typename T>
    inline T DivUp(T x, T y)
    {
        return static_cast<T>( (x + (y - 1)) / y );
    }
/*  

*/

/* Please see man pages for details 
    
    
*/

    /* Please see man pages for details 
        

        

        
        

        

        
        
        
        

        
    */
    template <typename T>
    inline T ExtractBits(bit32 v, int pos, int len)
    {
        return static_cast<T>( v & (((1u << len) - 1) << pos) );
    }

    /* Please see man pages for details 
        

        

        
        

        
    
        
        
        
        

        
    */
    template <typename T>
    inline T ExtractBits(bit64 v, int pos, int len)
    {
        return static_cast<T>( v & (((1ull << len) - 1) << pos) );
    }
    
    /* Please see man pages for details 
        

        

        
        
        
    
        
        
        
        

        
    */
    template <typename T>
    inline T GetBits(bit32 v, int pos, int len)
    {
        return static_cast<T>( (v >> pos) & ((1u << len) - 1) );
    }
    
    /* Please see man pages for details 
        

        

        
        
        
    
        
        
        
        

        
    */
    template <typename T>
    inline T GetBits(bit64 v, int pos, int len)
    {
        return static_cast<T>( (v >> pos) & ((1ull << len) - 1) );
    }

    /* Please see man pages for details 
        

        

        

        
        
        
        

        
    */
    template <typename T>
    inline bit32 MakeBits(T v, int width, int shift)
    {
        return (static_cast<bit32>(v) & ((1u << width) - 1)) << shift;
    }

/*  

*/
}}


#endif  // ifndef NN_MATH_MATH_UTILITY_H_
