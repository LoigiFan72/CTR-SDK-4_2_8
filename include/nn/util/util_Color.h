/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Color.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_COLOR_H_
#define NN_UTIL_UTIL_COLOR_H_

#include <nn/math.h>

#ifdef __cplusplus

namespace nn {
namespace util {

struct FloatColor;

//--------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
struct Color8
{
public:
    typedef Color8  SelfType;   //

    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const int ELEMENT_MIN         = 0;           //
    static const int ELEMENT_MAX         = 255;         //
    static const int ALPHA_MIN           = ELEMENT_MIN; //
    static const int ALPHA_MAX           = ELEMENT_MAX; //
    static const int ALPHA_OPACITY       = ALPHA_MAX;   //
    static const int ALPHA_TRANSPARENT   = ALPHA_MIN;   //

    static const u32 BLACK      = 0x000000FF;   //
    static const u32 GRAY       = 0x808080FF;   //
    static const u32 WHITE      = 0xFFFFFFFF;   //
    static const u32 RED        = 0xFF0000FF;   //
    static const u32 GREEN      = 0x00FF00FF;   //
    static const u32 BLUE       = 0x0000FFFF;   //
    static const u32 YELLOW     = 0xFFFF00FF;   //
    static const u32 MAGENTA    = 0xFF00FFFF;   //
    static const u32 CYAN       = 0x00FFFFFF;   //


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //----------------------------------------
    //
    //

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    /* ctor */ Color8() { this->SetU32(WHITE); }

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    /* ctor */ /*implicit*/ Color8(u32 color) { this->SetU32(color); }

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    /* ctor */ /*implicit*/ Color8(s32 red, s32 green, s32 blue, s32 alpha)
     : r(static_cast<u8>(red)),
       g(static_cast<u8>(green)),
       b(static_cast<u8>(blue)),
       a(static_cast<u8>(alpha))
    {
    }

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    /* dtor */ ~Color8() {}

    //

    //----------------------------------------
    //
    //

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType&      operator =(u32 color)
    {
        this->SetU32(color);
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType&      operator =(FloatColor& color);

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    operator u32() const { return ToU32(); }

    //---- The Four Arithmetic Operations
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator +(const SelfType& right) const
    {
        SelfType color(
            nn::math::Min(this->r + right.r, ELEMENT_MAX),
            nn::math::Min(this->g + right.g, ELEMENT_MAX),
            nn::math::Min(this->b + right.b, ELEMENT_MAX),
            nn::math::Min(this->a + right.a, ELEMENT_MAX)
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator -(const SelfType& right) const
    {
        SelfType color(
            nn::math::Max(this->r - right.r, ELEMENT_MIN),
            nn::math::Max(this->g - right.g, ELEMENT_MIN),
            nn::math::Max(this->b - right.b, ELEMENT_MIN),
            nn::math::Max(this->a - right.a, ELEMENT_MIN)
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator *(const SelfType& right) const
    {
        SelfType color(
            this->r * right.r / ELEMENT_MAX,
            this->g * right.g / ELEMENT_MAX,
            this->b * right.b / ELEMENT_MAX,
            this->a * right.a / ELEMENT_MAX
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator /(const SelfType& right) const
    {
        SelfType color(
            (this->r < right.r) ? this->r * ELEMENT_MAX / right.r : ELEMENT_MAX,
            (this->g < right.g) ? this->g * ELEMENT_MAX / right.g : ELEMENT_MAX,
            (this->b < right.b) ? this->b * ELEMENT_MAX / right.b : ELEMENT_MAX,
            (this->a < right.a) ? this->a * ELEMENT_MAX / right.a : ELEMENT_MAX
        );
        return color;
    }

    //---- Increment, Decrement
    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator ++()
    {
        if (r < ELEMENT_MAX) { r++; }
        if (g < ELEMENT_MAX) { g++; }
        if (b < ELEMENT_MAX) { b++; }
        if (a < ELEMENT_MAX) { a++; }

        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator ++(int)
    {
        SelfType old = *this;
        if (r < ELEMENT_MAX) { r++; }
        if (g < ELEMENT_MAX) { g++; }
        if (b < ELEMENT_MAX) { b++; }
        if (a < ELEMENT_MAX) { a++; }

        return old;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator --()
    {
        if (r > ELEMENT_MIN) { r--; }
        if (g > ELEMENT_MIN) { g--; }
        if (b > ELEMENT_MIN) { b--; }
        if (a > ELEMENT_MIN) { a--; }

        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator --(int)
    {
        SelfType old = *this;
        if (r > ELEMENT_MIN) { r--; }
        if (g > ELEMENT_MIN) { g--; }
        if (b > ELEMENT_MIN) { b--; }
        if (a > ELEMENT_MIN) { a--; }

        return old;
    }

    //---- Bitwise OR and AND
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator |(const SelfType& right) const
    {
        return U32RawToColor(this->ToU32Raw() | right.ToU32Raw());
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator &(const SelfType& right) const
    {
        return U32RawToColor(this->ToU32Raw() & right.ToU32Raw());
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator +=(const SelfType& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator -=(const SelfType& rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator *=(const SelfType& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator /=(const SelfType& rhs)
    {
        *this = *this / rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator +(u32 rhs) const
    {
        const SelfType right = SelfType(rhs);
        SelfType color(
            nn::math::Min(this->r + right.r, ELEMENT_MAX),
            nn::math::Min(this->g + right.g, ELEMENT_MAX),
            nn::math::Min(this->b + right.b, ELEMENT_MAX),
            nn::math::Min(this->a + right.a, ELEMENT_MAX)
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator -(u32 rhs) const
    {
        const SelfType right = SelfType(rhs);
        SelfType color(
            nn::math::Max(this->r - right.r, ELEMENT_MIN),
            nn::math::Max(this->g - right.g, ELEMENT_MIN),
            nn::math::Max(this->b - right.b, ELEMENT_MIN),
            nn::math::Max(this->a - right.a, ELEMENT_MIN)
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator *(u32 rhs) const
    {
        const SelfType right = SelfType(rhs);
        SelfType color(
            this->r * right.r / ELEMENT_MAX,
            this->g * right.g / ELEMENT_MAX,
            this->b * right.b / ELEMENT_MAX,
            this->a * right.a / ELEMENT_MAX
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator /(u32 rhs) const
    {
        const SelfType right = SelfType(rhs);
        SelfType color(
            (this->r < right.r) ? this->r * ELEMENT_MAX / right.r : ELEMENT_MAX,
            (this->g < right.g) ? this->g * ELEMENT_MAX / right.g : ELEMENT_MAX,
            (this->b < right.b) ? this->b * ELEMENT_MAX / right.b : ELEMENT_MAX,
            (this->a < right.a) ? this->a * ELEMENT_MAX / right.a : ELEMENT_MAX
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator |(u32 right) const
    {
        return *this | SelfType( right );
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator &(u32 right) const
    {
        return *this & SelfType( right );
    }

    //

    //----------------------------------------
    //
    //

    //---- Accessor
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    void        Set(
                    s32 red,
                    s32 green,
                    s32 blue,
                    s32 alpha = ALPHA_OPACITY )
    {
        r = static_cast<u8>(red);
        g = static_cast<u8>(green);
        b = static_cast<u8>(blue);
        a = static_cast<u8>(alpha);
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    void        Set(SelfType color)
    {
        operator =(color);
    }

    //---- Explicit Type Conversion
  #if ( NN_ENDIAN == NN_ENDIAN_VALUE_LITTLE )
    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    u32         ToU32() const
    {
        u32 val = *reinterpret_cast<const u32*>(this);
        return (u32)( (((val) >> 24UL) & 0x000000FFUL) |
                      (((val) >>  8UL) & 0x0000FF00UL) |
                      (((val) <<  8UL) & 0x00FF0000UL) |
                      (((val) << 24UL) & 0xFF000000UL) );
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    void        SetU32(u32 value)
    {
        this->ToU32RawRef() = (u32)( (((value) >> 24UL) & 0x000000FFUL) |
                                     (((value) >>  8UL) & 0x0000FF00UL) |
                                     (((value) <<  8UL) & 0x00FF0000UL) |
                                     (((value) << 24UL) & 0xFF000000UL) );
    }

  #else
    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    u32         ToU32() const
    {
        return this->ToU32RawRef();
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    void        SetU32(u32 value) { this->ToU32RawRef() = value; }

  #endif

    //

protected:

    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //
    static SelfType U32RawToColor(u32 value)
    {
        return *reinterpret_cast<SelfType*>(&value);
    }

    //
    u32&        ToU32RawRef()
    {
        return *reinterpret_cast<u32*>(this);
    }

    //
    const u32&  ToU32RawRef() const
    {
        return *reinterpret_cast<const u32*>(this);
    }

    //
    u32         ToU32Raw() const
    {
        return *reinterpret_cast<const u32*>(this);
    }

public:
    u8 r; //
    u8 g; //
    u8 b; //
    u8 a; //
};

//
typedef Color8   Color;

//--------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
struct FloatColor
{
public:
    typedef FloatColor SelfType;    //

    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const int ELEMENT_MIN         = 0;   //
    static const int ELEMENT_MAX         = 1;   //
    static const int ALPHA_MIN           = ELEMENT_MIN; //
    static const int ALPHA_MAX           = ELEMENT_MAX; //
    static const int ALPHA_OPACITY       = ALPHA_MAX;   //
    static const int ALPHA_TRANSPARENT   = ALPHA_MIN;   //

    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //----------------------------------------
    //
    //

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    /* ctor */ FloatColor()
    : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
    {
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //--------------------------------------------------------------------------
    /* ctor */ /* implicit */  FloatColor(const nn::math::VEC4& vec)
     : r(vec.x), g(vec.y), b(vec.z), a(vec.w)
    {
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //--------------------------------------------------------------------------
    /* ctor */ /* implicit */  FloatColor(Color8 color) { operator =(color); }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //--------------------------------------------------------------------------
    /* ctor */ FloatColor(f32 red, f32 green, f32 blue, f32 alpha)
    : r(red), g(green), b(blue), a(alpha)
    {
    }

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    /* dtor */ ~FloatColor() {}

    //

    //----------------------------------------
    //
    //

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //--------------------------------------------------------------------------
    SelfType&      operator =(Color8 color)
    {
        this->Set(
            static_cast<s32>(color.r),
            static_cast<s32>(color.g),
            static_cast<s32>(color.b),
            static_cast<s32>(color.a) );
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType&      operator =(const nn::math::VEC4& vec)
    {
        this->Set( vec.x, vec.y, vec.z, vec.w );
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    operator f32*() { return &r; }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    operator const f32*() const { return &r; }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    operator Color8() const
    {
        return Color8( static_cast<u8>( 0.5f + nn::math::Clamp(r, 0.0f, 1.0f) * 255.f ),
                       static_cast<u8>( 0.5f + nn::math::Clamp(g, 0.0f, 1.0f) * 255.f ),
                       static_cast<u8>( 0.5f + nn::math::Clamp(b, 0.0f, 1.0f) * 255.f ),
                       static_cast<u8>( 0.5f + nn::math::Clamp(a, 0.0f, 1.0f) * 255.f ));
    }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    operator nn::math::VEC4&()
    {
        return this->ToVEC4();
    }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    operator const nn::math::VEC4&() const
    {
        return this->ToVEC4();
    }

    //---- The Four Arithmetic Operations
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator +(const SelfType& right) const
    {
        SelfType color(
            this->r + right.r,
            this->g + right.g,
            this->b + right.b,
            this->a + right.a
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator -(const SelfType& right) const
    {
        SelfType color(
            this->r - right.r,
            this->g - right.g,
            this->b - right.b,
            this->a - right.a
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator *(const SelfType& right) const
    {
        SelfType color(
            this->r * right.r,
            this->g * right.g,
            this->b * right.b,
            this->a * right.a
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const SelfType operator /(const SelfType& right) const
    {
        SelfType color(
            (right.r != 0) ? (this->r / right.r) : ELEMENT_MAX,
            (right.g != 0) ? (this->g / right.g) : ELEMENT_MAX,
            (right.b != 0) ? (this->b / right.b) : ELEMENT_MAX,
            (right.a != 0) ? (this->a / right.a) : ELEMENT_MAX
        );
        return color;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator +=(const SelfType& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator -=(const SelfType& rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator *=(const SelfType& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator /=(const SelfType& rhs)
    {
        *this = *this / rhs;
        return *this;
    }

    //---- The Four Arithmetic Operations
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator +=(f32 right)
    {
        this->r += right;
        this->g += right;
        this->b += right;
        this->a += right;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator -=(f32 right)
    {
        this->r -= right;
        this->g -= right;
        this->b -= right;
        this->a -= right;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator *=(f32 right)
    {
        this->r *= right;
        this->g *= right;
        this->b *= right;
        this->a *= right;
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    SelfType& operator /=(f32 right)
    {
        if (right != 0.0f)
        {
            this->r /= right;
            this->g /= right;
            this->b /= right;
            this->a /= right;
        }
        else
        {
            this->r = ELEMENT_MAX;
            this->g = ELEMENT_MAX;
            this->b = ELEMENT_MAX;
            this->a = ELEMENT_MAX;
        }
        return *this;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    bool        operator ==(const SelfType& rhs) const
    {
        return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    bool        operator !=(const SelfType& rhs) const
    {
        return !(*this == rhs);
    }

    //

    //----------------------------------------
    //
    //

    //---- Accessor
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    void        Set(
                    f32 red,
                    f32 green,
                    f32 blue,
                    f32 alpha = ALPHA_OPACITY )
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    //---- Accessor
    //--------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    void        Set(
                    s32 red,
                    s32 green,
                    s32 blue,
                    s32 alpha = Color8::ALPHA_OPACITY )
    {
        r = static_cast<f32>( red ) / 255.f;
        g = static_cast<f32>( green ) / 255.f;;
        b = static_cast<f32>( blue ) / 255.f;;
        a = static_cast<f32>( alpha ) / 255.f;;
    }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    void        Set(const SelfType& color) { operator =(color); }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    void        Clamp() { this->Clamp( 0.0f, 1.0f ); }

    //--------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    void        Clamp( f32 low, f32 high )
    {
        r = nn::math::Clamp( r, low, high );
        g = nn::math::Clamp( g, low, high );
        b = nn::math::Clamp( b, low, high );
        a = nn::math::Clamp( a, low, high );
    }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    f32*        ToArray()       { return reinterpret_cast<f32*>( this ); }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    const f32*  ToArray() const { return reinterpret_cast<const f32*>( this ); }

    //--------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    u32 ToPicaU32() const
    {
        u8 red   = static_cast<u8>( 0.5f + nn::math::Clamp(r, 0.0f, 1.0f) * 255.f );
        u8 green = static_cast<u8>( 0.5f + nn::math::Clamp(g, 0.0f, 1.0f) * 255.f );
        u8 blue  = static_cast<u8>( 0.5f + nn::math::Clamp(b, 0.0f, 1.0f) * 255.f );
        u8 alpha = static_cast<u8>( 0.5f + nn::math::Clamp(a, 0.0f, 1.0f) * 255.f );

        return (alpha << 24) | (blue << 16) | (green << 8) | (red);
    }

    //

protected:
    //
    nn::math::VEC4&        ToVEC4()
    {
        return *reinterpret_cast<nn::math::VEC4*>(this);
    }

    //
    const nn::math::VEC4&  ToVEC4() const
    {
        return *reinterpret_cast<const nn::math::VEC4*>(this);
    }

public:
    f32 r; //
    f32 g; //
    f32 b; //
    f32 a; //

};

#if !defined( NN_SWAP_ENDIAN )
    //
    typedef FloatColor ResFloatColor;
#else
    //
    typedef struct
    {
        nw::ut::ResF32 r;
        nw::ut::ResF32 g;
        nw::ut::ResF32 b;
        nw::ut::ResF32 a;

        operator FloatColor() const
            { FloatColor color; color.r = r; color.g = g; color.b = b; color.a = a; return color; }
        void operator = (const FloatColor& val) { r = val.r; g = val.g; b = val.b; a = val.a; }
    } ResFloatColor;
#endif

} /* namespace util */
} /* namespace nn */

#endif // __cplusplus

#endif //  NN_UTIL_UTIL_COLOR_H_
