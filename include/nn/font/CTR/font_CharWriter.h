/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_CharWriter.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_CHAR_WRITER_H_
#define NN_FONT_CTR_FONT_CHAR_WRITER_H_

// Upper left origin
#define COORDINATE_LT 1

#include <cstddef>
#include <cstdio>
#include <GLES2/gl2.h>
#include <nn/types.h>
#include <nn/math.h>
#include <nn/util/util_Color.h>
#include <nn/font/font_Font.h>
#include <nn/font/CTR/font_TextWriterResource.h>

namespace nn {
namespace font {
namespace CTR {

struct DispStringBuffer;

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class CharWriter
{
public:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */

    //
    enum GradationMode
    {
        GRADMODE_NONE,                          //
        GRADMODE_H,                             //
        GRADMODE_V,                             //

        NUM_OF_GRADMODE
    };



    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const u32 DEFAULT_COLOR_MAPPING_MIN = 0x00000000UL;
    static const u32 DEFAULT_COLOR_MAPPING_MAX = 0xFFFFFFFFUL;


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                        CharWriter();

    //
                        ~CharWriter();

    //

    //
    //

    //
    //
    //
    //
    void                SetFont(const Font* pFont)  { m_pFont = pFont; }

    //
    //
    //
    //
    //
    const Font*         GetFont() const             { return m_pFont; }

    //

    //
    //

    //
    void                SetupGX();

    //
    static void         FinalizeGX()
    {
        TextWriterResource::FinalizeGX();
    }

    //

    //
    //

    //
    //
    //
    //
    //
    void                SetColorMapping(
                            util::Color8  min,
                            util::Color8  max
    )
    {
        m_ColorMapping.min = min;
        m_ColorMapping.max = max;
    }

    //
    //
    //
    //
    const util::Color8  GetColorMappingMin() const { return m_ColorMapping.min; }

    //
    //
    //
    //
    const util::Color8  GetColorMappingMax() const { return m_ColorMapping.max; }

    //
    void                ResetColorMapping()
    {
        SetColorMapping(DEFAULT_COLOR_MAPPING_MIN, DEFAULT_COLOR_MAPPING_MAX);
    }

    //

    //
    //

    //
    //
    //
    //
    void                SetAlpha(u8 alpha)
    {
        m_Alpha = alpha;
    }

    //Gets the additional alpha value used during text rendering.

    //
    //
    //
    //
    u8                  GetAlpha() const    { return m_Alpha; }

    //
    //
    //
    //
    void                SetGradationMode(GradationMode mode)
    {
        NN_FONT_MINMAX_ASSERT(mode, GRADMODE_NONE, NUM_OF_GRADMODE - 1);
        m_GradationMode = mode;
        UpdateVertexColor();
    }

    //
    //
    //
    //
    GradationMode       GetGradationMode() const    { return m_GradationMode; }

    //
    //
    //
    //
    void                SetTextColor(util::Color8 color)
    {
        m_TextColors[internal::TEXTCOLOR_START] = color;
        UpdateVertexColor();
    }

    //
    //
    //
    //
    //
    void                SetTextColor(
                            util::Color8  start,
                            util::Color8  end
    )
    {
        m_TextColors[internal::TEXTCOLOR_START] = start;
        m_TextColors[internal::TEXTCOLOR_END  ] = end;
        UpdateVertexColor();
    }

    //
    //
    //
    //
    const util::Color8   GetTextColor() const           { return m_TextColors[internal::TEXTCOLOR_START]; }

    //
    //
    //
    //
    const util::Color8   GetGradationStartColor() const { return m_TextColors[internal::TEXTCOLOR_START]; }

    //
    //
    //
    //
    const util::Color8   GetGradationEndColor() const   { return m_TextColors[internal::TEXTCOLOR_END]; }

    //

    //
    //

    //
    //
    //
    //
    //
    void                SetScale(
                            f32 hScale,
                            f32 vScale
    )
    {
        m_Scale.x = hScale;
        m_Scale.y = vScale;
    }

    //
    //
    //
    //
    void                SetScale(f32 hvScale)
    {
        m_Scale.x = hvScale;
        m_Scale.y = hvScale;
    }

    //
    //
    //
    //
    f32                 GetScaleH() const   { return m_Scale.x; }

    //
    //
    //
    //
    f32                 GetScaleV() const   { return m_Scale.y; }

    //
    //
    //
    //
    //
    void                SetFontSize(
                            f32 width,
                            f32 height);

    //
    //
    //
    //
    void                SetFontSize(f32 height);

    //
    //
    //
    //
    //
    f32                 GetFontWidth() const;

    //
    //
    //
    //
    //
    f32                 GetFontHeight() const;

    //
    //
    //
    //
    f32                 GetFontAscent() const;

    //
    //
    //
    //
    f32                 GetFontDescent() const;

    //

    //
    //

    //
    //
    //
    //
    void                EnableFixedWidth(bool isFixed)  { m_IsWidthFixed = isFixed; }

    //
    //
    //
    //
    bool                IsWidthFixed() const            { return m_IsWidthFixed; }

    //
    //
    //
    //
    void                SetFixedWidth(f32 width)        { m_FixedWidth = width; }

    //
    //
    //
    //
    f32                 GetFixedWidth() const           { return m_FixedWidth; }

    //

    //
    //

    //
    //
    //
    //
    //
    //
    f32                 Print(CharCode code);

    //
    //
    //
    //
    void                DrawGlyph(const Glyph& glyph);

    //

    //
    //

    //
    //
    //
    //
    //
    void                SetCursor(
                            f32 x,
                            f32 y
    )
    {
        m_CursorPos.x = x;
        m_CursorPos.y = y;
    }

    //
    //
    //
    //
    //
    //
    void                SetCursor(
                            f32 x,
                            f32 y,
                            f32 z
    )
    {
        m_CursorPos.x = x;
        m_CursorPos.y = y;
        m_CursorPos.z = z;
    }

    //
    //
    //
    //
    //
    void                MoveCursor(
                            f32 dx,
                            f32 dy
    )
    {
        m_CursorPos.x += dx;
        m_CursorPos.y += dy;
    }

    //
    //
    //
    //
    //
    //
    void                MoveCursor(
                            f32 dx,
                            f32 dy,
                            f32 dz
    )
    {
        m_CursorPos.x += dx;
        m_CursorPos.y += dy;
        m_CursorPos.z += dz;
    }

    //
    //
    //
    //
    void                SetCursorX(f32 x)           { m_CursorPos.x = x; }

    //
    //
    //
    //
    void                SetCursorY(f32 y)           { m_CursorPos.y = y; }

    //
    //
    //
    //
    void                SetCursorZ(f32 z)           { m_CursorPos.z = z; }

    //
    //
    //
    //
    void                MoveCursorX(f32 dx)         { m_CursorPos.x += dx; }

    //
    //
    //
    //
    void                MoveCursorY(f32 dy)         { m_CursorPos.y += dy; }

    //
    //
    //
    //
    void                MoveCursorZ(f32 dz)         { m_CursorPos.z += dz; }

    //
    //
    //
    //
    f32                 GetCursorX() const          { return m_CursorPos.x; }

    //
    //
    //
    //
    f32                 GetCursorY() const          { return m_CursorPos.y; }

    //
    //
    //
    //
    f32                 GetCursorZ() const          { return m_CursorPos.z; }

    //

    //
    //

    //
    //
    //
    //
    TextWriterResource* GetTextWriterResource() const
    {
        return m_pTextWriterResource;
    }

    //
    //
    //
    //
    void                SetTextWriterResource(TextWriterResource* pTextWriterResource)
    {
        m_pTextWriterResource = pTextWriterResource;
    }

    //

    //
    //

    //
    //
    //
    //
    //
    //
    static u32          GetDispStringBufferSize(u32 charNum);

    //
    //
    //
    //
    //
    //
    //
    static DispStringBuffer*
                        InitDispStringBuffer(
                            void*   drawBuffer,
                            u32     charNum);

    //
    //
    //
    //
    DispStringBuffer*   GetDispStringBuffer() const
    {
        return m_pDispStringBuffer;
    }

    //
    //
    //
    //
    //
    void                SetDispStringBuffer(DispStringBuffer* buffer)
    {
        m_pDispStringBuffer = buffer;
    }

    //
    //
    //
    void                StartPrint();

    //
    //
    //
    void                EndPrint();

    //
    //
    void                UseCommandBuffer();

    //

private:

    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    typedef math::VEC2      CharScale;
    typedef math::VEC3      CursorPos;

    struct ColorMapping
    {
        util::Color8        min;
        util::Color8        max;
    };

    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //---- Prepare to draw

    //
    //
    //
    //
    void                SetupGXDefault(bool bAlphaTex = false);

    //
    //
    //
    //
    //
    void                SetupGXWithColorMapping(bool bAlphaTex = false);

    //
    void                SetupVertexFormat();

    //
    void                SetupGXCommon();

    //
    //
    //
    //
    //
    //
    void                PrintGlyph(
                            f32             x,
                            const Glyph&    glyph);

    //
    void                UpdateVertexColor();

    //
    //
    //
    //
    void                LoadTexture(const Glyph& glyph);

    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    static const GLushort       s_VertexIndexs[];

    ColorMapping                m_ColorMapping;         //
    NN_PADDING3;
    util::Color8                m_VertexColors[internal::TRIFAN_VTX_MAX];
                                                        //
    util::Color8                m_TextColors[internal::TEXTCOLOR_MAX];  //
    GradationMode               m_GradationMode;
    CharScale                   m_Scale;                //
    CursorPos                   m_CursorPos;            //
    f32                         m_FixedWidth;           //
    const Font*                 m_pFont;                //

    //
    TextWriterResource*         m_pTextWriterResource;

    //
    DispStringBuffer*           m_pDispStringBuffer;

    bool                        m_IsWidthFixed;         //
    u8                          m_Alpha;                //
    NN_PADDING2;
};

}   // namespace CTR
}   // namespace font
}   // namespace nn
#endif //  NN_FONT_CTR_FONT_CHAR_WRITER_H_
