/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_Font.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_FONT_H_
#define NN_FONT_FONT_FONT_H_

#include <nn/types.h>
#include <nn/font/font_CharStrmReader.h>
#include <nn/font/font_ResourceFormat.h>
#include <climits>

#define NN_FONT_MIN_ASSERT(exp, min)            NN_ASSERT((exp) >= (min))

#define NN_FONT_MINMAX_ASSERT(exp, min, max)    NN_ASSERT((exp) >= (min) && (exp) <= (max))


namespace nn {
namespace font {

class Font;

//---- Texture format types
typedef u16     TexFmt;

namespace internal {

union TextureSize
{
    struct
    {
        u16                 height;   //
        u16                 width;    //
    } HW;
    u32                 size;   //
};

class TextureObject
{
public:
                            TextureObject();

    void                    Set(
                                u32         name,
                                const Font* pFont,
                                const void* pImage,
                                TexFmt      format,
                                u16         width,
                                u16         height);

    void                    Reset()
    {
        Set(0, NULL, NULL, FONT_SHEET_FORMAT_A8, 0, 0);
    }

    u32                     GetName() const
    {
        return m_Name;
    }

    const Font*             GetFont() const
    {
        return m_pFont;
    }

    void                    SetName(u32 texName)
    {
        m_Name = texName;
    }

    uptr                    GetImage() const
    {
        return m_pImage;
    }

    u8                      GetFormat() const
    {
        return m_Format;
    }

    const TextureSize       GetSize() const
    {
        return m_Size;
    }

    u32                     GetWrapFilter() const;

private:
    u32                     m_Name;     //
    const Font*             m_pFont;    //
    uptr                    m_pImage;   //
    TextureSize             m_Size;     //
    u8                      m_Format;   //
    NN_PADDING3;
};

}   // namespace internal


//---- Character code type
typedef u16     CharCode;

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
struct Glyph
{
    const void* pTexture;                   //
    CharWidths  widths;                     //
    u8          height;                     //
    u16         texWidth;                   //
    u16         texHeight;                  //
    u16         cellX;                      //
    u16         cellY;                      //
    u8          isSheetUpdated;             //
    NN_PADDING1;
    TexFmt      texFormat;                  //
    const internal::TextureObject*
                pTextureObject;             //

    //
                Glyph();
};

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class Font
{
public:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    enum Type
    {
        TYPE_NULL,          //
        TYPE_ROM,           // RomFont
        TYPE_RESOURCE,      // ResFont
        TYPE_PAIR           // PairFont
    };


    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    // Invalid character code
    static const CharCode   INVALID_CHARACTER_CODE = INVALID_CHAR_CODE;


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                            Font()  {}

    //
    virtual                 ~Font();

    //

    
    //
    //

    //
    //
    //
    //
    virtual int             GetWidth() const = 0;

    //
    //
    //
    //
    virtual int             GetHeight() const = 0;

    //
    //
    //
    //
    virtual int             GetAscent() const = 0;

    //
    //
    //
    //
    virtual int             GetDescent() const = 0;

    //
    //
    //
    //
    virtual int             GetMaxCharWidth() const = 0;

    //
    //
    //
    //
    virtual Type            GetType() const = 0;

    //
    //
    //
    //
    virtual TexFmt          GetTextureFormat() const = 0;

    //
    //
    //
    //
    virtual int             GetLineFeed() const = 0;

    //
    //
    //
    //
    virtual const CharWidths
                            GetDefaultCharWidths() const = 0;

    //


    //
    //

    //
    //
    //
    //
    virtual void            SetLineFeed(int linefeed) = 0;

    //
    //
    //
    //
    virtual void            SetDefaultCharWidths(
                                const CharWidths& widths
                            ) = 0;

    //
    //
    //
    //
    //
    //
    //
    virtual bool            SetAlternateChar(CharCode c) = 0;

    //


    //
    //

    //
    //
    //
    //
    //
    //
    virtual int             GetCharWidth(CharCode c) const = 0;

    //
    //
    //
    //
    //
    //
    virtual const CharWidths
                            GetCharWidths(CharCode c) const = 0;

    //
    //
    //
    //
    //
    virtual void            GetGlyph(
                                Glyph*      pGlyph,
                                CharCode    c
                            ) const = 0;

    //
    //
    //
    //
    //
    //
    virtual bool            HasGlyph(
                                CharCode    c
                            ) const = 0;

    //


    //
    //

    //
    //
    //
    //
    virtual CharacterCode   GetCharacterCode() const = 0;

    //
    //
    //
    //
    //
    //
    //
    //
    //
    const CharStrmReader    GetCharStrmReader(char dummy) const;

    //
    //
    //
    //
    //
    //
    //
    //
    //
    const CharStrmReader    GetCharStrmReader(wchar_t dummy) const;

    //


    //
    //

    //
    //
    //
    //
    virtual int             GetBaselinePos() const = 0;

    //
    //
    //
    //
    virtual int             GetCellHeight() const = 0;

    //
    //
    //
    //
    virtual int             GetCellWidth() const = 0;

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
    virtual void            EnableLinearFilter(
                                bool    atSmall,
                                bool    atLarge
                            ) = 0;

    //
    //
    //
    //
    //
    virtual bool            IsLinearFilterEnableAtSmall() const = 0;

    //
    //
    //
    //
    //
    virtual bool            IsLinearFilterEnableAtLarge() const = 0;

    //
    //
    //
    //
    virtual u32             GetTextureWrapFilterValue() const = 0;
    //
};

namespace internal {

inline
u32
TextureObject::GetWrapFilter() const
{
    return m_pFont->GetTextureWrapFilterValue();
}

void                    LoadTexture(
                            u16         texWidth,
                            u16         texHeight,
                            TexFmt      texFormat,
                            const void* pImage,
                            bool        isSmallLinearFilter,
                            bool        isLargeLinearFilter);

}   // namespace internal

}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_FONT_H_
