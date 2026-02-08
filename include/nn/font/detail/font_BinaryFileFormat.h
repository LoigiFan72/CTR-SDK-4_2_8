/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_BinaryFileFormat.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_DETAIL_FONT_BINARY_FILE_FORMAT_H_
#define NN_FONT_DETAIL_FONT_BINARY_FILE_FORMAT_H_

#include <nn/types.h>

#if ( NN_ENDIAN == NN_ENDIAN_VALUE_LITTLE )
//---- little endian
#define NN_FONT_MAKE_SIGWORD(a, b, c, d)                        \
    static_cast<nn::font::detail::SigWord>(                     \
        (static_cast<u8>(a) <<  0) | (static_cast<u8>(b) <<  8) \
      | (static_cast<u8>(c) << 16) | (static_cast<u8>(d) << 24) \
    )
#else
//---- big endian
#define NN_FONT_MAKE_SIGWORD(a, b, c, d)                        \
    static_cast<nn::font::detail::SigWord>(                     \
        (static_cast<u8>(a) << 24) | (static_cast<u8>(b) << 16) \
      | (static_cast<u8>(c) <<  8) | (static_cast<u8>(d) <<  0) \
    )
#endif
#define NN_FONT_MAKE_VERSION(major, minor, micro, binaryBugFix)          \
    static_cast<u32>(                                                    \
        (static_cast<u8>(major) << 24) | (static_cast<u8>(minor) << 16)  \
      | (static_cast<u8>(micro) <<  8) | (static_cast<u8>(binaryBugFix)) \
    )

#define NN_FONT_VERSION_MAJOR(version)        (((version) >> 24) & 0xff)
#define NN_FONT_VERSION_MINOR(version)        (((version) >> 16) & 0xff)
#define NN_FONT_VERSION_MICRO(version)        (((version) >>  8) & 0xff)
#define NN_FONT_VERSION_BINARYBUGFIX(version) (((version) >>  0) & 0xff)

namespace nn { namespace font { namespace detail {

// #define NN_SWAP_ENDIAN

#if !defined( NN_SWAP_ENDIAN )
    typedef u8  ResU8;          //
    typedef s8  ResS8;          //
    typedef u16 ResU16;         //
    typedef s16 ResS16;         //
    typedef u32 ResU32;         //
    typedef s32 ResS32;         //
    typedef f32 ResF32;         //
    typedef u32 ResU64;         //
    typedef s32 ResS64;         //
    typedef f32 ResF64;         //
#else // if defined( NN_SWAP_ENDIAN )
namespace Endian {
    typedef union
    {
        u64 UInt64;
        s64 SInt64;
#if defined( NN_ENABLE_FLOAT64 )
        f64 Float64;
#endif
    } Type64;

    typedef union
    {
        u32 UInt32;
        s32 SInt32;
        f32 Float32;
    } Type32;

    typedef union
    {
        u16 UInt16;
        s16 SInt16;
    } Type16;

    static u64 BSwap( u64 val )
    {
        const u64 MASK  = 0xFF00FF00FF00FF00ULL;
        const u64 MASK2 = 0xFFFF0000FFFF0000ULL;
        val = ( (val & MASK) >> 8 ) | ( (val << 8) & MASK );
        val = ( (val & MASK2) >> 16 ) | ( (val << 16) & MASK2 );
        return (val >> 32) | (val << 32);
    }

    static s64 BSwap( s64 val )
    {
        Type64 data;
        data.SInt64 = val;
        data.UInt64 = BSwap( data.UInt64 );
        return data.SInt64;
    }

#if defined( NN_ENABLE_FLOAT64 )
    static f64 BSwap( f64 val )
    {
        Type64 data;
        data.Float64 = val;
        data.UInt64 = BSwap( data.UInt64 );
        return data.Float64;
    }
#endif

    static u32 BSwap( u32 val )
    {
        const u32 MASK = 0xFF00FF00;
        val = ( (val & MASK) >> 8 ) | ( (val << 8) & MASK );
        return (val >> 16) | (val << 16);
    }

    static s32 BSwap( s32 val )
    {
        Type32 data;
        data.SInt32 = val;
        data.UInt32 = BSwap( data.UInt32 );
        return data.SInt32;
    }

    static f32 BSwap( f32 val )
    {
        Type32 data;
        data.Float32 = val;
        data.UInt32 = BSwap( data.UInt32 );
        return data.Float32;
    }

    static u16 BSwap( u16 val )
    {
        return (u16)( (val >> 8) | (val << 8) );
    }

    static s16 BSwap( s16 val )
    {
        return (s16)( ((u16)val >> 8) | ((u16)val << 8) );
    }
} /* namespace Endian */

    template <typename T>
    class ResNum
    {
    public:
        /* ctor */ ResNum() {}
        /* ctor */ ResNum(const ResNum& other) : bits(other.bits) {}
        /* ctor */ explicit ResNum(const T val ) : bits( Endian::BSwap( val ) ) {}

        void operator = (const ResNum& other) { bits = other.bits; }
        /* T */ operator T () const { return Endian::BSwap( bits ); }
        void operator = (T val) { bits = Endian::BSwap( val ); }
    private:
        T   bits;
    };

    typedef u8          ResU8;      //
    typedef s8          ResS8;      //
    typedef ResNum<u16> ResU16;     //
    typedef ResNum<s16> ResS16;     //
    typedef ResNum<u32> ResU32;     //
    typedef ResNum<s32> ResS32;     //
    typedef ResNum<f32> ResF32;     //
    typedef ResNum<u64> ResU64;     //
    typedef ResNum<s64> ResS64;     //
    typedef ResNum<f64> ResF64;     //
#endif // define( NN_SWAP_ENDIAN )


//---- Signature type
typedef u32 SigWord;

namespace
{
    const u16 BYTE_ORDER_MARK = 0xFEFF;
}

/*
  
  
 */
struct BinaryFileHeader
{
    SigWord signature;                  // File signature  : 4 Bytes
    u16     byteOrder;                  // Byte order mark : 2 Bytes
    ResU16  headerSize;                 // Header size  : 2 Bytes
    ResU32  version;                    // File version  : 4 Bytes
    ResU32  fileSize;                   // File size   : 4 Bytes
    ResU16  dataBlocks;                 // Number of blocks   : 2 Bytes
    u16     reserved;                   // Reserved    : 2 Bytes
};

/*
  
  
 */
struct BinaryBlockHeader
{
    SigWord kind;                       // Block type name
    u32     size;                       // Total block size
};

bool IsValidBinaryFile(
    const BinaryFileHeader* /*pHeader*/,
    u32                     /*signature*/,
    u32                     /*version*/,
    u16                     /*minBlocks   = 1*/ );

}}} // namespace nn::font::detail

#endif // NN_FONT_DETAIL_FONT_BINARY_FILE_FORMAT_H_
