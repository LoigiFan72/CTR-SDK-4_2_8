/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_PairFont.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_PAIR_FONT_H_
#define NN_FONT_FONT_PAIR_FONT_H_

#include <nn/types.h>
#include <nn/font/font_Font.h>


namespace nn {
namespace font {


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class PairFont
    : public Font
{
public:
    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
    //
    //
    //
    //
                                PairFont(
                                    Font*   primary,
                                    Font*   secondary);

    //
    virtual                     ~PairFont();

    //

    //
    //  @{

    virtual int                 GetWidth() const;

    virtual int                 GetHeight() const;

    virtual int                 GetAscent() const;

    virtual int                 GetDescent() const;

    virtual int                 GetMaxCharWidth() const;

    virtual Type                GetType() const;

    virtual TexFmt              GetTextureFormat() const;

    virtual int                 GetLineFeed() const;

    virtual const CharWidths    GetDefaultCharWidths() const;

    //  @}

    //
    //  @{

    virtual void                SetDefaultCharWidths(
                                    const CharWidths& widths        // New default width
                                );

    virtual bool                SetAlternateChar(
                                    CharCode c );                   // New alternate character

    virtual void                SetLineFeed(
                                    int linefeed );                 // New line feed width

    //  @}


    //
    //  @{

    virtual int                 GetCharWidth(
                                    CharCode c                      // Character whose width is to be found
                                ) const;

    virtual const CharWidths    GetCharWidths(
                                    CharCode c                      // Character whose width is to be found
                                ) const;

    virtual void                GetGlyph(
                                    Glyph*      glyph,              // Buffer used to receive glyph information
                                    CharCode    c                   // Character to obtain glyph information for.
                                ) const;
    virtual bool                HasGlyph(
                                    CharCode    c                   // Character for which to get whether glyph information is present
                                ) const;

    //  @}


    //
    //  @{

    virtual CharacterCode       GetCharacterCode() const;

    //  @}


    //
    //  @{

    virtual int                 GetBaselinePos() const;

    virtual int                 GetCellHeight() const;

    virtual int                 GetCellWidth() const;

    //  @}

    //
    //  @{

    virtual void            EnableLinearFilter(
                                bool    atSmall,
                                bool    atLarge);

    virtual bool            IsLinearFilterEnableAtSmall() const;

    virtual bool            IsLinearFilterEnableAtLarge() const;

    virtual u32             GetTextureWrapFilterValue() const;

    //  @}

private:
    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    // Pointer to font instance.
    Font*                       m_Primary;
    Font*                       m_Secondary;
    // Whether to get the alternate character from the first font.
    bool                        m_AlternateWithPrimary;
    u8                          m_Padding[3];
};




}   // namespace font
}   // namespace nn
#endif //  NN_FONT_FONT_PAIR_FONT_H_
