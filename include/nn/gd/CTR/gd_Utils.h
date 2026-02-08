/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Utils.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_UTILS_H_
#define NN_GD_CTR_GD_UTILS_H_

#include <nn/config.h>
#include <nn/gd/CTR/gd_Types.h>

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
*/
#else
/* Please see man pages for details 
    
*/
#endif

namespace nn {
namespace gd {
namespace CTR {

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
/*  */ // defgroup utilityFunction
#else
/* Please see man pages for details 
    
    
*/
/*  */ // defgroup utilityFunction
#endif

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
*/
#endif
class Utils
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    static void ConvertStartEndToScaleBias(f32 start, f32 end, f32& scale, f32& bias);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u8 FloatToUnsignedByte(f32 val);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u8 FloatToUnsignedByteNoClamp(f32 val);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static s8 FloatToSignedByte(f32 val);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u16 Float32ToFloat16( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFix13Fraction11( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToUnsignedFix12( f32 val );
 
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else   
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFix12( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFix12Fraction11( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToUnsignedFix11( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u8 Float32ToFix8Fraction7( f32 val );
 
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else    
    /* Please see man pages for details 
        
        
    */
    #endif
    static u16 Float32ToFix16( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFloat24( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFloat31( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFloat20( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToFix13Fraction8( f32 val );
 
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else        
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToUnsignedFix16( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToUnsignedFix24( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static u32 Float32ToUnsignedFix8Fraction0( f32 val );

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
*/
    #endif
    static u32 Float32ToUnsignedFix24Fraction8( f32 val );

};  // Utils


NN_FORCE_INLINE void Utils::ConvertStartEndToScaleBias(f32 start, f32 end, f32& scale, f32& bias)
{
    scale = 1.f / ( end - start );
    bias = -start * scale;
}

NN_FORCE_INLINE u8 Utils::FloatToUnsignedByte(f32 val)
{
    return ( u8 )( 0.5f + ( val < 0.f ? 0.f : ( 1.f < val ? 1.f : val ) )  * ( 0xff ) );
}

NN_FORCE_INLINE u8 Utils::FloatToUnsignedByteNoClamp(f32 val)
{
    return ( u8 )( 0.5f + val * 0xff );
}

NN_FORCE_INLINE s8 Utils::FloatToSignedByte(f32 val)
{
    f32 u = 127.f * (val);
    u = u < 0.f? -u: u;
    return ( s8 )( ((u32)u & 0x7f) | (val < 0.f ? 0x80 : 0) );
}

NN_FORCE_INLINE u16 Utils::Float32ToFloat16( f32 val )
{
    static const int bias_ = 128 - (1 << (5 - 1));

    u32 uval_ = *( reinterpret_cast<u32*>( &val ) );
    int e_ = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;
    if (e_ >= 0)
    {
        return ( u16 )( ((uval_ & 0x7fffff) >> (23 - 10)) | (e_ << 10) | ((uval_ >> 31) << (10 + 5)) );
    }
    return ( u16 )((uval_ >> 31) << (10 + 5));
}

NN_FORCE_INLINE u32 Utils::Float32ToFix13Fraction11( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if( val == 0.f || (v_ & 0x7f800000) == 0x7f800000 )
        return 0;

    val += 0.5f * (1 << 2);
    val *= 1 << (13 - 2);
    if (val < 0)
        val = 0;
    else if (val >= (1 << 13))
        val = (1 << 13) - 1;

    return (val >= (1 << (13 - 1))) ? (unsigned)(val - (1 << (13 - 1))) : (unsigned)(val + (1 << (13 - 1)));
}

NN_FORCE_INLINE u32 Utils::Float32ToUnsignedFix12( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if( val <= 0 || (v_ & 0x7f800000) == 0x7f800000 )
    {
        return 0;
    }
    else
    {
        unsigned uval_;

        val *= 1 << (12 - 0);
        if (val >= (1 << 12))
        {
            uval_ = (1 << 12) - 1;
        }
        else
        {
            uval_ = (unsigned)(val);
        }

        return uval_;
    }
}

NN_FORCE_INLINE u32 Utils::Float32ToFix12( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if( val == 0.f || (v_ & 0x7f800000) == 0x7f800000 )
        return 0;

    int ret;

    val *= (1 << (12 - 1));

    if( val < 0 )
    {
        ret = 1 << (12 - 1);
        val = -val;
    }
    else
        ret = 0;

    if( val >= (1 << (12 - 1)) )
        val  = (1 << (12 - 1)) - 1;

    ret |= (unsigned)(val);
    return ret;
}

NN_FORCE_INLINE u32 Utils::Float32ToFix12Fraction11( f32 val )
{                                
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

    if (val == 0.f || (v_ & 0x7f800000) == 0x7f800000)
    {
        return 0;
    }
    else
    {
        val += 0.5f * (1 << 1);
        val *= 1 << (12 - 1);

        if (val < 0)
        {
            val = 0;
        }
        else if (val >= (1 << 12))
        {
            val = (1 << 12) - 1;
        }

        if (val >= (1 << (12 - 1)))
        {
            return (unsigned)(val - (1 << (12 - 1)));
        }
        else
        {
            return (unsigned)(val + (1 << (12 - 1)));
        }
    }
}

NN_FORCE_INLINE u32 Utils::Float32ToUnsignedFix11( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if( val <= 0 || (v_ & 0x7f800000) == 0x7f800000 )
        return 0;

    unsigned uval_;

    val *= 1 << (11 - 0);
    if (val >= (1 << 11))
        uval_ = (1 << 11) - 1;
    else
        uval_ = (unsigned)(val);

    return uval_;
}

NN_FORCE_INLINE u8 Utils::Float32ToFix8Fraction7( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

    if (val == 0.f || (v_ & 0x7f800000) == 0x7f800000)
    {
        return 0;
    }
    else
    {
        val += 0.5f * (1 << 1);
        val *= 1 << (8 - 1);

        if (val < 0)
        {
            val = 0;
        }
        else if (val >= (1 << 8))
        {
            val = (1 << 8) - 1;
        }

        if (val >= (1 << (8 - 1)))
        {
            return (unsigned)(val - (1 << (8 - 1)));
        }
        else
        {
            return (unsigned)(val + (1 << (8 - 1)));
        }
    }
}

NN_FORCE_INLINE u16 Utils::Float32ToFix16( f32 val )
{                
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

    if ( (val == 0.f) || ( (v_ & 0x7f800000) == 0x7f800000 ) )
    {
        return 0;
    }
    else
    {
        val += 0.5f * (1 << 4);
        val *= 1 << (16 - 4);
        if (val < 0)
        {
            val = 0;
        }
        else if (val >= (1 << 16))
        {
            val = (1 << 16) - 1;
        }

        if (val >= (1 << (16 - 1)))
        {
            return (unsigned)(val - (1 << (16 - 1)));
        }
        else
        {
            return (unsigned)(val + (1 << (16 - 1)));
        }
    }
}

NN_FORCE_INLINE u32 Utils::Float32ToFloat24( f32 val )
{
    static const int bias_ = 128 - (1 << (7 - 1));
    u32 uval_   = *( reinterpret_cast<unsigned*>( &val ) );
    s32 e_      = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;

    return e_ >= 0 ? ((uval_ & 0x7fffff) >> (23 - 16)) | (e_ << 16) | ((uval_ >> 31) << (16 + 7)) : ((uval_ >> 31) << (16 + 7));
}

NN_FORCE_INLINE u32 Utils::Float32ToFloat31( f32 val )
{
    unsigned uval_, m_;
    int e_;
    float f_ = val;
    static const int bias_ = 128 - (1 << (7 - 1));
    uval_ = *( reinterpret_cast<unsigned*>( &f_ ) );
    e_ = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;
    m_ = (uval_ & 0x7fffff) >> (23 - 23);
    return e_ >= 0 ? m_ | (e_ << 23) | ((uval_ >> 31) << (23 + 7)) : ((uval_ >> 31) << (23 + 7));
}

NN_FORCE_INLINE u32 Utils::Float32ToFloat20( f32 val )
{
    static const int bias_ = 128 - (1 << (7 - 1));
    u32 uval_   = *( reinterpret_cast<unsigned*>( &val ) );
    s32 e_      = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;

    return e_ >= 0 ? ((uval_ & 0x7fffff) >> (23 - 12)) | (e_ << 12) | ((uval_ >> 31) << (12 + 7)) : ((uval_ >> 31) << (12 + 7));
}

NN_FORCE_INLINE u32 Utils::Float32ToFix13Fraction8( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if ( ( val == 0.0f ) || 
        ( (v_ & 0x7f800000) == 0x7f800000 ) )
    {
        return 0;
    }

    val += 0.5f * (1 << 5);
    val *= 1 << (13 - 5);
    if (val < 0)
    {
        val = 0;
    }
    else if (val >= (1 << 13))
    {
        val = (1 << 13) - 1;
    }

    return (val >= (1 << (13 - 1))) ? (unsigned)(val - (1 << (13 - 1))) : (unsigned)(val + (1 << (13 - 1)));
}

NN_FORCE_INLINE u32 Utils::Float32ToUnsignedFix16( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val) );

    if (val <= 0 || (v_ & 0x7f800000) == 0x7f800000)
    {
        return 0;
    }
    else
    {
        val *= 1 << (16 - 0);
        if ( val >= (1 << 16) )
        {
            return (1 << 16) - 1;
        }
        else
        {
            return (unsigned)( val );
        }
    }
}

NN_FORCE_INLINE u32 Utils::Float32ToUnsignedFix24( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

    if (val <= 0 || (v_ & 0x7f800000) == 0x7f800000)
    {
        return 0;
    }
    else
    {
        val *= 1 << (24 - 0);

        if ( val >= (1 << 24) )
        {
            return (1 << 24) - 1;
        }
        else
        {
            return (unsigned)(val);
        }
    }
}

NN_FORCE_INLINE u32 Utils::Float32ToUnsignedFix8Fraction0( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if( val <= 0 || (v_ & 0x7f800000) == 0x7f800000 )
    {
        return 0;
    }
    else
    {
        unsigned uval_;

        val *= 1 << (8 - 8);
        if (val >= (1 << 8))
        {
            uval_ = (1 << 8) - 1;
        }
        else
        {
            uval_ = (unsigned)(val);
        }

        return uval_;
    }
}

NN_FORCE_INLINE u32 Utils::Float32ToUnsignedFix24Fraction8( f32 val )
{
    unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
    if( val <= 0 || (v_ & 0x7f800000) == 0x7f800000 )
    {
        return 0;
    }
    else
    {
        unsigned uval_;

        val *= 1 << (24 - 16);
        if (val >= (1 << 24))
        {
            uval_ = (1 << 24) - 1;
        }
        else
        {
            uval_ = (unsigned)(val);
        }

        return uval_;
    }
}

}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_UTILS_H_
