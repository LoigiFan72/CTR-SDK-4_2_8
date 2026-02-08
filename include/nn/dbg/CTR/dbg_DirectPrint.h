/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_DirectPrint.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48011 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_DBG_CTR_DBG_DIRECTPRINT_H_
#define NN_DBG_CTR_DBG_DIRECTPRINT_H_

#ifdef  __cplusplus

#include <nn/util/util_Color.h>
#include <gles2/gl2.h>

namespace nn { namespace dbg { namespace CTR {

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
class DirectPrint
{
public:
    //----------------------------------------------------------------------
    //
    //----------------------------------------------------------------------
    static const int FONT_WIDTH  = 6;

    //----------------------------------------------------------------------
    //
    //----------------------------------------------------------------------
    static const int FONT_HEIGHT = 8;

public:
    DirectPrint();
    ~DirectPrint();

public:

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
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void ChangeDisplaybuffer( void* dispbuf, GLenum format, const nn::math::VEC2& size );

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
    //----------------------------------------------------------------------
    void ChangeDisplaybuffer( void* dispbuf );

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    void* GetDisplaybuffer() { return static_cast<void*>(m_CurBuffer); }

//

//
//

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    void Flush();

    //----------------------------------------------------------------------
    //
    //----------------------------------------------------------------------
    void Clear();

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
    //
    //
    //----------------------------------------------------------------------
    void Printf( const nn::math::VEC2& pos, bool autoLineFeed, bool fillBg, const char* format, ... );

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void Printf( const nn::math::VEC2& pos, const char* format, ... );

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
    //----------------------------------------------------------------------
    void VPrintf( const nn::math::VEC2& pos, bool autoLineFeed, bool fillBg, const char* format, va_list v );

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void VPrintf( const nn::math::VEC2& pos, const char* format, va_list v );

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
    //----------------------------------------------------------------------
    void PutString( const nn::math::VEC2& pos, bool autoLineFeed, bool fillBg, const char* str );

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void PutString( const nn::math::VEC2& pos, const char* str );

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void PutChar( const nn::math::VEC2& pos, bool fillBg, char c );

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void PutChar( const nn::math::VEC2& pos, char c );

//

//
//

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    void SetCharColor( const nn::util::Color8& c ) { m_CharColor = c; };

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    const nn::util::Color8& GetCharColor() const { return m_CharColor; };

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    void SetBgColor( const nn::util::Color8& c ) { m_BgColor = c; };

    //----------------------------------------------------------------------
    //
    //
    //
    //----------------------------------------------------------------------
    const nn::util::Color8& GetBgColor() const { return m_BgColor; };

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    const nn::math::VEC2& GetLastCursorPos() const { return m_LastCursorPos; };

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void SetFillSpace(bool fillSpace) { m_FillSpace = fillSpace; }

//



private:
    void ConvertColorFormat( bit8* data, const nn::util::Color8& src, GLenum format );
    void ConvertPositionUserOriginToDeviceOrigin( nn::math::VEC2* dst, const nn::math::VEC2& src );
    void PutDot( const nn::math::VEC2& bufPos, const bit8* data, s32 byteByDot );

private:
    bit8*               m_CurBuffer;     //
    GLenum              m_BufferFormat;  //
    nn::math::VEC2      m_BufferSize;    //
    nn::util::Color8    m_CharColor;     //
    nn::util::Color8    m_BgColor;       //
    nn::math::VEC2      m_LastCursorPos; //
    bool                m_FillSpace;
    NN_PADDING3;
};

}}}
#endif

#endif  // NN_DBG_CTR_DBG_DIRECTPRINT_H_
