/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_ResourceFormat.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_RESOURCE_FORMAT_H_
#define NN_FONT_FONT_RESOURCE_FORMAT_H_

#include <nn/types.h>
#include <nn/font/detail/font_BinaryFileFormat.h>

namespace nn {
namespace font {


const int   GlyphDataAlignment   = 128;


/* ------------------------------------------------------------------------
        Signature Definitions
   ------------------------------------------------------------------------ */

// Standard font resource file signature
const detail::SigWord BINFILE_SIG_FONT              = NN_FONT_MAKE_SIGWORD('C','F','N','T');

// Binary file signature with already resolved offset
const detail::SigWord BINFILE_SIG_FONT_RESOLEVED    = NN_FONT_MAKE_SIGWORD('C','F','N','U');

// Archive font resource file signature
const detail::SigWord BINFILE_SIG_FONTA             = NN_FONT_MAKE_SIGWORD('C','F','N','A');

// Binary block signature
const detail::SigWord BINBLOCK_SIG_FINF             = NN_FONT_MAKE_SIGWORD('F','I','N','F');
const detail::SigWord BINBLOCK_SIG_CGLP             = NN_FONT_MAKE_SIGWORD('C','G','L','P');
const detail::SigWord BINBLOCK_SIG_TGLP             = NN_FONT_MAKE_SIGWORD('T','G','L','P');
const detail::SigWord BINBLOCK_SIG_CWDH             = NN_FONT_MAKE_SIGWORD('C','W','D','H');
const detail::SigWord BINBLOCK_SIG_CMAP             = NN_FONT_MAKE_SIGWORD('C','M','A','P');

const detail::SigWord BINBLOCK_SIG_GLGR             = NN_FONT_MAKE_SIGWORD('G','L','G','R');
const detail::SigWord BINBLOCK_SIG_HTGL             = NN_FONT_MAKE_SIGWORD('H','T','G','L');





/* ------------------------------------------------------------------------
        Resource version definitions
   ------------------------------------------------------------------------ */

const u32 FONT_FILE_VERSION             = NN_FONT_MAKE_VERSION(3, 0, 0, 0);



/* ------------------------------------------------------------------------
        Constant definitions
   ------------------------------------------------------------------------ */
const u16 INVALID_CHAR_CODE   = 0xFFFF;
const u16 INVALID_GLYPH_INDEX = 0xFFFF;





/* ------------------------------------------------------------------------
        enum Definitions
   ------------------------------------------------------------------------ */

/*---------------------------------------------------------------------------*
  Name:         FontType
  Description:  Font type
 *---------------------------------------------------------------------------
*/
enum FontType
{
    FONT_TYPE_GLYPH,            // BMP
    FONT_TYPE_TEXTURE,          // Texture
    NUM_OF_FONT_TYPE
};

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
enum CharacterCode
{
    CHARACTER_CODE_UNICODE = 1,  //
    CHARACTER_CODE_SJIS,         //
    CHARACTER_CODE_CP1252,       //

    CHARACTER_CODE_MAX
};

/*---------------------------------------------------------------------------*
  Name:         FontMapMethod
  Description:  character code mapping type
 *---------------------------------------------------------------------------
*/
enum FontMapMethod
{
    FONT_MAPMETHOD_DIRECT,      // index = character code - offset
    FONT_MAPMETHOD_TABLE,       // index = mapInfo[character code - offset]
    FONT_MAPMETHOD_SCAN,        // index = search(mapInfo, character code)
    NUM_OF_FONT_MAPMETHOD
};


/*---------------------------------------------------------------------------*
  Name:         FontSheetFormat
  Description:  Sheet format (texture format)
 *---------------------------------------------------------------------------
*/
enum FontSheetFormat
{
    FONT_SHEET_FORMAT_RGBA8,
    FONT_SHEET_FORMAT_RGB8,
    FONT_SHEET_FORMAT_RGB5A1,
    FONT_SHEET_FORMAT_RGB565,
    FONT_SHEET_FORMAT_RGBA4,
    FONT_SHEET_FORMAT_LA8,


    FONT_SHEET_FORMAT_A8 = 8,
    FONT_SHEET_FORMAT_LA4,

    FONT_SHEET_FORMAT_A4 = 11,



    FONT_SHEET_FORMAT_MASK              = 0x7FFF,
    FONT_SHEET_FORMAT_COMPRESSED_FLAG   = 0x8000    // Compressed if 1.
};




/* ------------------------------------------------------------------------
        Structure definitions
   ------------------------------------------------------------------------ */

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
struct CharWidths
{
    s8  left;                   //
    u8  glyphWidth;             //
    s8  charWidth;              //
};

/*---------------------------------------------------------------------------*
  Name:         CMapScanEntry
  Description:  Character code and glyph index pair
 *---------------------------------------------------------------------------
*/
struct CMapScanEntry
{
    u16 ccode;                  // Character code
    u16 index;                  // Glyph index
};

/*---------------------------------------------------------------------------*
  Name:         CMapInfoScan
  Description:  FontCodeMap.mapInfo when using MAPMETHOD_SCAN
 *---------------------------------------------------------------------------
*/
struct CMapInfoScan
{
    u16 num;                    // number of elements in "entries"
    CMapScanEntry* GetEntries() const // mapping list to the glyph index from the character code
    {
        return reinterpret_cast<CMapScanEntry*>( reinterpret_cast<uptr>(this) + sizeof(*this) );
    }
};





/* ------------------------------------------------------------------------
        Block definition
   ------------------------------------------------------------------------ */

/*---------------------------------------------------------------------------*
  Name:         FontGlyphGroups
  Description:  Stores the information for partially loading font.
 *---------------------------------------------------------------------------
*/
struct FontGlyphGroups
{
    u32 sheetSize;
    u16 glyphsPerSheet;
    u16 numSet;
    u16 numSheet;
    u16 numCWDH;
    u16 numCMAP;

    u16 nameOffsets[1];  // numSet
/*
    A variable length data follows from here
    (4 byte align)
    u32 sizeSheets[numSheet];       // size of the compressed sheet
    u32 sizeCWDH[numCWDH];          // size of the CWDH block
    u32 sizeCMAP[numCMAP];          // size of the CMAP block
    u32 useSheets[numSet][numSheet/32];
    u32 useCWDH[numSet][numCWDH/32];
    u32 useCMAP[numSet][numCMAP/32];
    char names[numSet][name length];



*/
};



/*---------------------------------------------------------------------------*
  Name:         FontTextureGlyph
  Description:  Stores the glyph texture of the font.
 *---------------------------------------------------------------------------
*/
struct FontTextureGlyph
{
    u8  cellWidth;              // Cell width = maximum glyph width
    u8  cellHeight;             // Cell height
    s8  baselinePos;            // Baseline position
    u8  maxCharWidth;           // Maximum character width
    u32 sheetSize;              // Texture sheet data size (in bytes)
    u16 sheetNum;               // Number of sheets
    u16 sheetFormat;            // FontSheetFormat
    u16 sheetRow;               // Number of horizontal cells on a sheet
    u16 sheetLine;              // Number of vertical cells on a sheet
    u16 sheetWidth;             // Sheet width (in pixels)
    u16 sheetHeight;            // Sheet height (in pixels)
    u8* sheetImage;             // The pointer to the texture data
};



/*---------------------------------------------------------------------------*
  Name:         FontWidth
  Description:  Stores the character width information for each character.
 *---------------------------------------------------------------------------
*/
struct FontWidth
{
    u16                 indexBegin;     // glyph index corresponding to the first entry in widthTable
    u16                 indexEnd;       // glyph index corresponding to the last entry in widthTable
    FontWidth*          pNext;          // Pointer to the next FontWidth
    CharWidths*         GetWidthTable() const // width information array
    {
        return reinterpret_cast<CharWidths*>( reinterpret_cast<uptr>(this) + sizeof(*this) );
    }
};



/*---------------------------------------------------------------------------*
  Name:         FontCodeMap
  Description:  Given a character code, specifies the mapping to the index of the glyph in the glyph image arrangment that matches the character code.
                
 *---------------------------------------------------------------------------
*/
struct FontCodeMap
{
    u16                 ccodeBegin;     // First character code in the character code range that this block manages
    u16                 ccodeEnd;       // Last character code in the character code range that this block manages
    u16                 mappingMethod;  // Mapping method (FontMappingMethod type)
    u16                 reserved;       // Reserved
    FontCodeMap*        pNext;          // Pointer to the next FontCodeMap
    u16*                GetMapInfo() const // The specific details of the character code mapping information depend on the mappingMethod
    {
        return reinterpret_cast<u16*>( reinterpret_cast<uptr>(this) + sizeof(*this) );
    }
};



/*---------------------------------------------------------------------------*
  Name:         FontInformation
  Description:  Stores the information related to the overall font.
 *---------------------------------------------------------------------------
*/
struct FontInformation
{
    u8                  fontType;       // glyph data type (FontType)
    s8                  linefeed;       // (*)== leading
    u16                 alterCharIndex; // (*) glyph index of the glyph for characters not contained in the font
    CharWidths          defaultWidth;   // (*) character width information for glyphs that have no character width information
    u8                  characterCode;  // Corresponding character code (CharacterCode type)
    FontTextureGlyph*   pGlyph;         // Pointer to a unique FontGlyph
    FontWidth*          pWidth;         // Pointer to the first FontWidth
    FontCodeMap*        pMap;           // Pointer to the first FontCodeMap
    u8                  height;         // Font height
    u8                  width;          // Font width
    u8                  ascent;         // Ascent
    u8                  padding_[1];
};



/* ------------------------------------------------------------------------
        Block definition
   ------------------------------------------------------------------------ */

/*---------------------------------------------------------------------------*
  Name:         BinaryBlock
  Description:  NintendoWare standard binary block
 *---------------------------------------------------------------------------
*/
template <typename BlockBodyType>
struct BinaryBlock
{
    detail::BinaryBlockHeader       header;     // Block header
    BlockBodyType                   body;       // Block body
};

typedef BinaryBlock<FontGlyphGroups>    FontGlyphGroupsBlock;
typedef BinaryBlock<FontInformation>    FontInformationBlock;
typedef BinaryBlock<FontTextureGlyph>   FontTextureGlyphBlock;
typedef BinaryBlock<FontWidth>          FontWidthBlock;
typedef BinaryBlock<FontCodeMap>        FontCodeMapBlock;



} // namespace font
} // namespace nn


#endif //  NN_FONT_FONT_RESOURCE_FORMAT_H_
