/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_ResFontBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_RES_FONT_BASE_H_
#define NN_FONT_FONT_RES_FONT_BASE_H_

#include <nn/types.h>
#include <nn/font/font_Font.h>
#include <nn/font/font_ResourceFormat.h>


namespace nn {
namespace font {

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class ResFontBase : public Font
{
public:
    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                            ResFontBase();

    //
    virtual                 ~ResFontBase();

    //

    //
    //

    virtual int             GetWidth() const;

    virtual int             GetHeight() const;

    virtual int             GetAscent() const;

    virtual int             GetDescent() const;

    virtual int             GetMaxCharWidth() const;

    virtual Type            GetType() const;

    virtual TexFmt          GetTextureFormat() const;

    virtual int             GetLineFeed() const;

    virtual const CharWidths
                            GetDefaultCharWidths() const;

    //
    //

    virtual void            SetLineFeed(int linefeed);

    virtual void            SetDefaultCharWidths(const CharWidths& widths);

    virtual bool            SetAlternateChar(CharCode c);

    //

    //
    //

    virtual int             GetCharWidth(CharCode c) const;

    virtual const CharWidths
                            GetCharWidths(CharCode c) const;

    virtual void            GetGlyph(
                                Glyph*      pGlyph,
                                CharCode    c
                            ) const;

    virtual bool            HasGlyph(CharCode c) const;

    //

    //
    //

    virtual CharacterCode   GetCharacterCode() const;

    //

    //
    //

    virtual int             GetBaselinePos() const;
    virtual int             GetCellHeight() const;
    virtual int             GetCellWidth() const;

    //


    //
    //

    virtual void            EnableLinearFilter(
                                bool    atSmall,
                                bool    atLarge);

    virtual bool            IsLinearFilterEnableAtSmall() const;

    virtual bool            IsLinearFilterEnableAtLarge() const;

    virtual u32             GetTextureWrapFilterValue() const;

    //

protected:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    typedef u16             GlyphIndex;

    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const GlyphIndex GLYPH_INDEX_NOT_FOUND = INVALID_GLYPH_INDEX;


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //---- Member access

    FontInformation*        GetFINF()       { return m_pFontInfo; }

    const FontInformation*  GetFINF() const { return m_pFontInfo; }

    //
    //
    //
    //
    //
    //
    //
    bool                    IsManaging(const void* ptr) const { return m_pResource == ptr; }

    //
    //
    //
    //
    //
    //
    void                    SetResourceBuffer(
                                void*               pUserBuffer,
                                FontInformation*    pFontInfo);

    //
    //
    //
    //
    //
    void*                   RemoveResourceBuffer();


    //---- glyph index


    //
    //
    //
    //
    //
    //
    //
    //
    GlyphIndex              GetGlyphIndex(CharCode c) const;

    //
    //
    //
    //
    //
    //
    //
    //
    GlyphIndex              FindGlyphIndex(CharCode c) const;

    //
    //
    //
    //
    //
    //
    //
    //
    //
    GlyphIndex              FindGlyphIndex(
                                const FontCodeMap*  pMap,
                                CharCode            c
                            ) const;

    //
    //
    //
    //
    //
    //
    const CharWidths&       GetCharWidthsFromIndex(GlyphIndex index) const;

    //
    //
    //
    //
    //
    //
    //
    //
    const CharWidths&       GetCharWidthsFromIndex(
                                const FontWidth*    pWidth,
                                GlyphIndex          index
                            ) const;

    //
    //
    //
    //
    //
    void                    GetGlyphFromIndex(
                                Glyph*      glyph,
                                GlyphIndex  index
                            ) const;


    //
    //
    //
    //
    //
    //
    static void             SetGlyphMember(
                                Glyph*                  glyph,
                                GlyphIndex              index,
                                const FontTextureGlyph& tg);


    //
    //

    //
    //
    //
    //
    virtual int             GetActiveSheetNum() const;

    //
    //
    //
    //
    internal::TextureObject*
                            GetTextureObjectsBufferPtr()
    {
        return m_pTexObjs;
    }

    //
    //
    //
    //
    const internal::TextureObject*
                            GetTextureObjectsBufferPtr() const
    {
        return m_pTexObjs;
    }

    //
    //
    //
    //
    void                    SetTextureObjectsBufferPtr(void* buffer)
    {
        m_pTexObjs = static_cast<internal::TextureObject*>(buffer);
    }

    //
    //
    //
    //
    //
    //
    const internal::TextureObject*
                            GetTextureObject(int index) const
    {
        NN_POINTER_ASSERT(GetTextureObjectsBufferPtr());
        return &GetTextureObjectsBufferPtr()[index];
    }

    //
    void                    GenTextureNames();

    // Destroys the texture name.
    void                    DeleteTextureNames();

    //

private:
    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    
    void*                   m_pResource;    //

    //
    FontInformation*        m_pFontInfo;

    internal::TextureObject*
                            m_pTexObjs;     //
    u32                     m_WrapFilter;   //

    //
    mutable CharCode        m_LastCharCode;

    //
    mutable GlyphIndex      m_LastGlyphIndex;
};

namespace internal {

//---------------------------------------------------------------------------
//
//
//
//
//
//---------------------------------------------------------------------------
inline
u32
GetCellsInASheet(const FontTextureGlyph& tg)
{
    return static_cast<u32>(tg.sheetRow * tg.sheetLine);
}


}   // namespace internal

}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_RES_FONT_BASE_H_
