/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_DirectPrint.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48011 $
 *---------------------------------------------------------------------------*/

#include <nn/nstd.h>
#include <nn/nstd/nstd_String.h>
#include <nn/dbg/CTR/dbg_DirectPrint.h>
#include <gles2/gl2ext.h>
#include <nn/gx.h>
#include <nn/gx/CTR/gx_CommandAccess.h>
#include <nn/os.h>


namespace nn { namespace dbg { namespace CTR {

    namespace
    {
        //------------------------------------------------------------------------------
        const bool FONT_BITMAP[ 96 ][ DirectPrint::FONT_HEIGHT ][ DirectPrint::FONT_WIDTH ] =
        {
            #include "dbg_DirectPrintResource.inc"
        };

        s32 GetByteByDot( GLenum format )
        {
            switch( format )
            {
            case GL_RGBA8_OES:
                return 4;
            case GL_RGB8_OES:
                return 3;
            case GL_RGBA4:
                return 2;
            case GL_RGB5_A1:
                return 2;
            case GL_RGB565:
                return 2;
            default:
                {
                    NN_TPANIC_("Undefined format.");
                }
                return 0;
            }
        }

        //------------------------------------------------------------------------------
    }

//------------------------------------------------------------------------------

DirectPrint::DirectPrint()
    : m_CurBuffer( NULL )
    , m_BufferFormat( 0 )
    , m_BufferSize( 0 , 0 )
    , m_CharColor( 0xff , 0xff , 0xff , 0xff )
    , m_BgColor  ( 0x00 , 0x00 , 0x00 , 0xff )
    , m_LastCursorPos( 0 , 0 )
    , m_FillSpace(true)
{
}

//------------------------------------------------------------------------------

DirectPrint::~DirectPrint()
{
}

//------------------------------------------------------------------------------

void DirectPrint::ChangeDisplaybuffer( void* dispbuf, GLenum format, const nn::math::VEC2& size )
{
    ChangeDisplaybuffer( dispbuf );
    m_BufferFormat = format;
    m_BufferSize = size;
}

//------------------------------------------------------------------------------

void DirectPrint::Flush()
{
    s32 byteByDot = GetByteByDot( m_BufferFormat );
    nn::gx::UpdateBuffer( m_CurBuffer, byteByDot * m_BufferSize.x * m_BufferSize.y );
}

//------------------------------------------------------------------------------

void DirectPrint::ChangeDisplaybuffer( void* dispbuf )
{
    NN_TASSERTMSG_( os::GetDeviceMemoryAddress() <= reinterpret_cast<uptr>(dispbuf)
        && reinterpret_cast<uptr>(dispbuf) < os::GetDeviceMemoryAddress() + os::GetDeviceMemorySize(),
        "'dispbuf' must be on DeviceMemory." );

    m_CurBuffer = reinterpret_cast<bit8*>( dispbuf );
}

//------------------------------------------------------------------------------

void DirectPrint::Printf( const nn::math::VEC2& pos, const char* format, ... )
{
    va_list v;
    va_start( v, format );
    VPrintf( pos, format, v );
    va_end( v );
}

//------------------------------------------------------------------------------

void DirectPrint::Printf( const nn::math::VEC2& pos, bool autoLineFeed, bool fillBg, const char* format, ... )
{
    va_list v;
    va_start( v, format );
    VPrintf( pos, autoLineFeed, fillBg, format, v );
    va_end( v );
}

//------------------------------------------------------------------------------

void DirectPrint::VPrintf( const nn::math::VEC2& pos, const char* format, va_list v )
{
    VPrintf( pos, true, true, format, v );
}

//------------------------------------------------------------------------------

void DirectPrint::VPrintf( const nn::math::VEC2& pos, bool autoLineFeed, bool fillBg, const char* format, va_list v )
{
    char buf[ 256 ] = {};
    nn::nstd::TVSNPrintf( buf , sizeof( buf ) , format , v );
    PutString( pos, autoLineFeed, fillBg, buf );
}

//------------------------------------------------------------------------------

void DirectPrint::PutString( const nn::math::VEC2& pos, const char* str )
{
    PutString( pos, true, true, str );
}

//------------------------------------------------------------------------------

void DirectPrint::PutString( const nn::math::VEC2& pos, bool autoLineFeed, bool fillBg, const char* str )
{
    nn::math::VEC2 cursor = pos;
    const s32 boxWidth = 320; // Assumed to appear only on the lower screen
    int offset = 0;

    while ( str[ offset ] != '\0' )
    {
        char c = str[ offset ];
        if ( c == '\0' )
        {
            break;
        }
        if ( c != '\n' )
        {
            // 1 character display.
            PutChar( cursor, fillBg, c );
            // Move cursor.
            cursor.x += FONT_WIDTH;
        }
        // Move to next character here to make processing convenient.
        ++ offset;
        // Newline
        if ( c == '\n' || ( autoLineFeed && str[ offset ] != '\n' && cursor.x + FONT_WIDTH >= boxWidth ) )
        {
            cursor.x = 0;
            cursor.y += FONT_HEIGHT;
        }
    }
    m_LastCursorPos = cursor;
}

//------------------------------------------------------------------------------

void DirectPrint::PutChar( const nn::math::VEC2& pos, char c )
{
    PutChar( pos, true, c );
}

//------------------------------------------------------------------------------

void DirectPrint::PutChar( const nn::math::VEC2& pos, bool fillBg, char c )
{
    // Convert to data format already in memory.
    s32 byteByDot = GetByteByDot( m_BufferFormat );
    bit8 charColorData[ 4 ];
    bit8 bgColorData[ 4 ];
    ConvertColorFormat( charColorData, m_CharColor, m_BufferFormat );
    ConvertColorFormat( bgColorData, m_BgColor, m_BufferFormat );
    // Recalculate to coordinates in buffer.
    nn::math::VEC2 bufPos;
    ConvertPositionUserOriginToDeviceOrigin( &bufPos, pos + nn::math::VEC2( 0, FONT_HEIGHT ) );
    // Printing possible?
    bool printable;
    if ( ( 0 <= c && c <= 0x20 ) || c == 0x7f )
    {
        printable = false;
    }
    else
    {
        printable = true;
    }

    // Fill in starting from bottom left
    for( s32 y = 0; y < FONT_WIDTH; y++ )
    {
        // Skip if outside screen
        if ( bufPos.y + y >= m_BufferSize.x || bufPos.y + y < 0 )
        {
            continue;
        }
        for( s32 x = 0; x < FONT_HEIGHT; x++ )
        {
            // Skip if outside screen
            if ( bufPos.x + x >= m_BufferSize.y || bufPos.x + x < 0 )
            {
                continue;
            }
            if( printable && FONT_BITMAP[ c - ' ' ][ int( FONT_HEIGHT ) - x - 1 ][ y ] )
            {
                PutDot( nn::math::VEC2( bufPos.x + x, bufPos.y + y ), charColorData, byteByDot );
            }
            else if( fillBg )
            {
                if( printable || m_FillSpace )
                {
                    PutDot( nn::math::VEC2( bufPos.x + x, bufPos.y + y ), bgColorData, byteByDot );
                }
            }
        }
    }
}

//------------------------------------------------------------------------------

void DirectPrint::Clear()
{
    nn::math::VEC2 pos( 0 , 0 );
    nn::math::VEC2 size( 320 , 240 );

    // Convert to data format already in memory
    s32 byteByDot = GetByteByDot( m_BufferFormat );
    bit8 bgColorData[ 4 ];
    ConvertColorFormat( bgColorData, m_BgColor, m_BufferFormat );

    // Recalculate to coordinates in buffer.
    nn::math::VEC2 bufPos;
    ConvertPositionUserOriginToDeviceOrigin( &bufPos, pos + nn::math::VEC2( 0, size.y ) );
    // Fill in starting from bottom left
    for( s32 y = 0; y < size.x; y++ )
    {
        // Skip if outside screen
        if ( bufPos.y + y >= m_BufferSize.x || bufPos.y + y < 0 )
        {
            continue;
        }
        for( s32 x = 0; x < size.y; x++ )
        {
            // Skip if outside screen
            if ( bufPos.x + x >= m_BufferSize.y || bufPos.x + x < 0 )
            {
                continue;
            }
            PutDot( nn::math::VEC2( bufPos.x + x, bufPos.y + y ), bgColorData, byteByDot );
        }
    }
}

//------------------------------------------------------------------------------

void DirectPrint::ConvertColorFormat( bit8* data, const nn::util::Color8& src, GLenum format )
{
    // Actually, sometimes not all data is filled in because only up to the range returned by GetByteByDot is used.
    switch( format )
    {
    case GL_RGB8_OES:
        {
            data[ 0 ] = src.b;
            data[ 1 ] = src.g;
            data[ 2 ] = src.r;
        }
        break;
    case GL_RGBA4:
        {
            data[ 0 ] = ( src.b & 0xf0 ) | ( src.a >> 4 );
            data[ 1 ] =( src.r & 0xf0 ) | ( src.g >> 4 );
        }
        break;
    case GL_RGB5_A1:
        {
            data[ 0 ] = ( ( src.a & 0x80 ) >> 7 ) | ( ( src.b & 0xf8 ) >> 2 ) | ( ( src.g & 0x3 ) << 6 );
            data[ 1 ] = ( ( src.g & 0x38 ) >> 3 ) | ( src.r & 0xf8 );
        }
        break;
    case GL_RGB565:
        {
            data[ 0 ] = ( ( src.g & 0x1c ) << 5 ) | ( src.b >> 3 );
            data[ 1 ] = ( ( src.r & 0xf8 ) | ( ( src.g & 0xe0 ) >> 5 ) );
        }
        break;
    default:
        return;
    }
}

//------------------------------------------------------------------------------

void DirectPrint::ConvertPositionUserOriginToDeviceOrigin( nn::math::VEC2* dst, const nn::math::VEC2& src )
{
    dst->x = m_BufferSize.y - src.y;
    dst->y = src.x;
}

//------------------------------------------------------------------------------

void DirectPrint::PutDot( const nn::math::VEC2& bufPos, const bit8* data, s32 byteByDot )
{
    s32 linearPos = int( bufPos.y ) * int( m_BufferSize.y ) + int( bufPos.x );
    bit8* startAddr = m_CurBuffer + linearPos * byteByDot;
    nn::nstd::MemCpy( startAddr, data, byteByDot );
}

}}}
