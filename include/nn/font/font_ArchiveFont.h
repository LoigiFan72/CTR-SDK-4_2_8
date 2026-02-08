/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_ArchiveFont.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_ARCHIVE_FONT_H_
#define NN_FONT_FONT_ARCHIVE_FONT_H_

#include <nn/types.h>
#include <nn/font/font_ArchiveFontBase.h>


namespace nn {
namespace font {

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------
class ArchiveFont : public ArchiveFontBase
{
public:
    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                    ArchiveFont();

    //
    virtual         ~ArchiveFont();

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
    static u32      GetRequireBufferSize(
                        const void*         bfnt,
                        const char*         glyphGroups = LOAD_GLYPH_ALL
                    );

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
    bool            Construct(
                        void*               pBuffer,
                        u32                 bufferSize,
                        const void*         bfnt,
                        const char*         glyphGroups = LOAD_GLYPH_ALL
                    );

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
    bool            InitStreamingConstruct(
                        ConstructContext*   pContext,
                        void*               pBuffer,
                        u32                 bufferSize,
                        const char*         glyphGroups = LOAD_GLYPH_ALL
                    );

    //
    //
    //
    //
    //
    //
    //
    //
    //
    ConstructResult StreamingConstruct(
                        ConstructContext*   pContext,
                        const void*         stream,
                        u32                 streamSize);

    //
    //
    //
    //
    //
    void*           Destroy();

    //

    //
    //

    //
    //
    //
    //
    //
    virtual void    GetGlyph(
                        Glyph*      pGlyph,
                        CharCode    c
                    ) const;

    //

private:
    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //---- glyph index

    //
    //
    //
    //
    //
    void            GetGlyphFromIndex(
                        Glyph*      pGlyph,
                        GlyphIndex  index
                    ) const;
};

}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_ARCHIVE_FONT_H_
