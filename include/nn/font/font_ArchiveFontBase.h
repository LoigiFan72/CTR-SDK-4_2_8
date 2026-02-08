/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_ArchiveFontBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_ARCHIVE_FONT_BASE_H_
#define NN_FONT_FONT_ARCHIVE_FONT_BASE_H_

#include <nn/types.h>
#include <nn/os.h>
#include <nn/math.h>
#include <nn/cx.h>
#include <nn/font/font_ResFontBase.h>


#define NN_FONT_FLOAT_ASSERT(exp)       ((void)0)

#define NN_FONT_BUFFERSIZE_ASSERT(size) ((void)0)

namespace nn {
namespace font {

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class ArchiveFontBase : public ResFontBase
{
public:
    struct ConstructContext;

protected:
    struct CachedStreamReader
    {
        friend struct ConstructContext;

    public:
        //
        //
        //
        //
        u32                 GetRemain() const;

        //
        //
        //
        //
        void                Advance(u32 dx);

        //
        //
        //
        //
        //
        void                CopyTo(
                                ConstructContext*   pContext,
                                u32                 size);

        //
        //
        //
        //
        //
        void                CopyTo(
                                void*   buf,
                                u32     size);

        //
        //
        //
        //
        //
        //
        //
        void                MoveTo(
                                void*   buf,
                                u32     size);

        //
        //
        //
        //
        //
        //
        u32                 ManagedCopy(ConstructContext* pContext);

        //
        //
        //
        //
        bool                HasBufData() const  { return mpTempStrmBufPos < mpTempStrmBufEnd; }

        //
        //
        //
        //
        //
        //
        //
        //
        const void*         Get(u32 size);

        //
        //
        //
        //
        //
        void                Attach(
                                const void* stream,
                                u32         streamSize);

        //
        //
        //
        //
        //
        //
        //
        bool                RequestData(
                                ConstructContext*   pContext,
                                u32                 size);

        //
        //
        //
        //
        u32                 GetOffset() const;

    private:
        //
        void                Init();

    private:
        const u8*           mStreamBegin;
        const u8*           mStreamPos;
        const u8*           mStreamEnd;
        u8*                 mpTempStrmBuf;
        u8*                 mpTempStrmBufPos;
        u8*                 mpTempStrmBufEnd;

        u32                 mRequireSize;
    };

public:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    // Return value of the construction process
    enum ConstructResult
    {
        CONSTRUCT_MORE_DATA,
        CONSTRUCT_FINISH,
        CONSTRUCT_ERROR,
        CONSTRUCT_CONTINUE,
        NUM_OF_CONSTRUCT_RESULT
    };

    struct ConstructContext
    {
    public:
        enum Operation
        {
            DISPATCH,               // 0
            ANALYZE_FILE_HEADER,    // 1
            ANALYZE_GLGR,           // 2
            ANALYZE_FINF,           // 3
            ANALYZE_CMAP,           // 4
            ANALYZE_CWDH,           // 5
            ANALYZE_TGLP,           // 6
            PREPAIR_COPY_SHEET,     // 7
            PREPAIR_EXPAND_SHEET,   // 8
            COPY,                   // 9
            SKIP,                   // 10
            EXPAND,                 // 11
            FATAL_ERROR,            // 12
            NUM_OF_OPERATION,       //
            INVALID_OPERATION
        };

    public:
        void                Init(
                                void*   outBuffer,
                                u32     outBufferSize,
                                u16*    pAdjustTable,
                                u16     nSheets,
                                u16     nPerSheet,
                                u32     numBlock
                            )
        {
            Init(outBuffer, outBufferSize, NULL);
            SetGLGR(pAdjustTable, nSheets, nPerSheet, numBlock);
        }

        void                Init(
                                void*       outBuffer,
                                u32         outBufferSize,
                                const char* glyphGroups);

        void                SetGLGR(
                                u16*        pAdjustTable,
                                u16         nSheets,
                                u16         nPerSheet,
                                u32         numBlock);

        // Output buffer location scan
        template <typename PtrT>
        PtrT                GetCurrentPtr()
        {
            return reinterpret_cast<PtrT>(targetBufferCur);
        }

        u32                 GetRemain() const
        {
            return static_cast<u32>(targetBufferEnd - targetBufferCur);
        }

        void                Align(u32 align)
        {
            targetBufferCur = reinterpret_cast<u8*>(nn::math::RoundUp(reinterpret_cast<uptr>(targetBufferCur), align));
        }

        void                Advance(u32 dx) { targetBufferCur += dx; }

#ifdef NN_DEBUG
        u32                 offset() const
        {
            return static_cast<u32>(targetBufferCur - targetBuffer);
        }

        u32                 sIndex() const  { return sheetIndex; }
#endif

        // Expansion completion
        void                Finish(
                                void**              ppData,
                                FontInformation**   ppFontInfo,
                                u16**               ppAdjustTable);

        // Get members
        u16                 GetNumSheets() const            { return numSheets; }

        u16                 GetNumGlyphsPerSheet() const    { return glyphsPerSheet; }

        CachedStreamReader& GetStreamReader()               { return streamReader; }

        cx::UncompContextHuffman*
                            GetUncompContext()              { return extendContext; }

        const char*         GetGlyphGroups() const          { return pGlyphGroups; }

        // Member increment
        void                NextBlock()                     { currentBlock++; }

        void                NextSheet()                     { sheetIndex++; }

        // Condition tests
        bool                IsRequireSheet(int sheetNo) const
        {
            NN_ASSERT( sheetNo < numSheets );
            return pGlyphIndexAdjustTable[sheetNo] != ADJUST_OFFSET_SHEET_NOT_LOADED;
        }

        bool                IsRequireSheet() const  { return IsRequireSheet(sheetIndex); }

        bool                HasMoreSheet()   const  { return sheetIndex < numSheets; }

        bool                HasMoreBlock()   const  { return currentBlock < resNumBlock; }

        // Common tasks
        void                SetupCopyTask(
                                u32         copySize,
                                Operation   nextOp      = DISPATCH
                            )
        {
            NN_FONT_BUFFERSIZE_ASSERT( copySize );
            opSize = copySize;
            op     = ConstructContext::COPY;
            op2    = nextOp;
        }

        void                SetupSkipTask(
                                u32         skipSize,
                                Operation   nextOp      = DISPATCH
                            )
        {
            NN_FONT_BUFFERSIZE_ASSERT( skipSize );
            opSize = skipSize;
            op     = ConstructContext::SKIP;
            op2    = nextOp;
        }

        void                SetupExtendTask(
                                u32         extendSize,
                                Operation   nextOp      = DISPATCH
                            )
        {
            NN_FONT_BUFFERSIZE_ASSERT( extendSize );
            opSize = extendSize;
            op     = ConstructContext::EXPAND;
            op2    = nextOp;
        }

        void                EndTask()               { op = op2; }

        u32                 TaskRemain() const      { return opSize; }

        void                TaskProceed(u32 size)   { opSize -= nn::math::Min(size, opSize); }


    public:
        FontInformation*    pFINF;
        FontWidth*          pPrevCWDH;
        FontCodeMap*        pPrevCMAP;

        Operation           op;
        NN_PADDING3;
        detail::BinaryBlockHeader
                            header;

        u32                 streamOffset;

    private:
        CachedStreamReader streamReader;
        cx::UncompContextHuffman*
                            extendContext;

        const char*         pGlyphGroups;
        u16*                pGlyphIndexAdjustTable;
        u8*                 targetBuffer;
        u8*                 targetBufferEnd;
        u8*                 targetBufferCur;

        Operation           op2;
        NN_PADDING3;
        u32                 opSize;
        u32                 resNumBlock;
        u32                 currentBlock;

        u16                 sheetIndex;
        u16                 numSheets;
        u16                 glyphsPerSheet;
        u16                 padding[1];
    };


    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const char       LOAD_GLYPH_ALL[1];
    static const int        HEADER_SIZE = 16 * 1024;




    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                            ArchiveFontBase();

    //
    virtual                 ~ArchiveFontBase();

    //


    //
    //

    //---- ResFontBase override
    virtual const CharWidths
                            GetCharWidths(CharCode c) const;

    virtual bool            HasGlyph(CharCode c) const;

    //


protected:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    class FontGlyphGroupsAcs
    {
    public:
        explicit            FontGlyphGroupsAcs(const void* brfnt);

        u16                 GetNumBlock() const     { return mpHeader->dataBlocks; }

        u32                 GetFileSize() const     { return mpHeader->fileSize; }

        u32                 GetGLGRSize() const     { return mpData->header.size; }

        const char*         GetSetName(int setNo) const
        {
            return reinterpret_cast<const char*>(
                reinterpret_cast<uptr>(mpHeader) + mpData->body.nameOffsets[setNo]
            );
        }

        u32                 GetSizeCompSheet(int sheetNo) const
                                { return mpSizeSheetsArray[sheetNo]; }

        u32                 GetSizeCWDH(int cwdhNo) const   { return mpSizeCWDHArray[cwdhNo]; }

        u32                 GetSizeCMAP(int cmapNo) const   { return mpSizeCMAPArray[cmapNo]; }

        bool                IsUseSheet(
                                int setNo,
                                int sheetNo
                            ) const
        {
            return GetBit(mpUseSheetArray, setNo * mSizeSheetFlags * 8 + sheetNo);
        }

        bool                IsUseCWDH(
                                int setNo,
                                int cwdhNo
                            ) const
        {
            return GetBit(mpUseCWDHArray,  setNo * mSizeCWDHFlags  * 8 + cwdhNo);
        }

        bool                IsUseCMAP(
                                int setNo,
                                int cmapNo
                            ) const
        {
            return GetBit(mpUseCMAPArray,  setNo * mSizeCMAPFlags  * 8 + cmapNo);
        }

        u32                 GetUseSheetFlags(
                                int setNo,
                                int flagSetNo
                            ) const
        {
            return mpUseSheetArray[setNo * mSizeSheetFlags / 4 + flagSetNo];
        }

        u32                 GetUseCWDHFlags(
                                int setNo,
                                int flagSetNo
                            ) const
        {
            return mpUseCWDHArray [setNo * mSizeCWDHFlags  / 4 + flagSetNo];
        }

        u32                 GetUseCMAPFlags(
                                int setNo,
                                int flagSetNo
                            ) const
        {
            return mpUseCMAPArray [setNo * mSizeCMAPFlags  / 4 + flagSetNo];
        }

        u32                 GetSheetSize() const        { return mpData->body.sheetSize; }

        u16                 GetNumGlyphsPerSheet() const { return mpData->body.glyphsPerSheet; }

        u16                 GetNumSheet() const         { return mpData->body.numSheet; }

        u16                 GetNumSet() const           { return mpData->body.numSet; }

        u16                 GetNumCWDH() const          { return mpData->body.numCWDH; }

        u16                 GetNumCMAP() const          { return mpData->body.numCMAP; }

        const detail::BinaryBlockHeader*
                            GetNextBlock() const
        {
            return reinterpret_cast<const detail::BinaryBlockHeader*>(
                reinterpret_cast<uptr>(mpData) + mpData->header.size);
        }

    private:
        static bool         GetBit(const u32* bits, u32 index)
        {
            u32 wordIndex = index / 32;
            u32 bitIndex  = index % 32;
            return ((bits[wordIndex] << bitIndex) & (1u << 31)) != 0;
        }

        const detail::BinaryFileHeader*
                            mpHeader;
        const FontGlyphGroupsBlock*
                            mpData;
        const u16*          mpNameOffsetArray;
        const u32*          mpSizeSheetsArray;
        const u32*          mpSizeCWDHArray;
        const u32*          mpSizeCMAPArray;
        const u32*          mpUseSheetArray;
        const u32*          mpUseCWDHArray;
        const u32*          mpUseCMAPArray;
        u32                 mSizeSheetFlags;
        u32                 mSizeCWDHFlags;
        u32                 mSizeCMAPFlags;
    };


    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const u16        ADJUST_OFFSET_SHEET_NOT_LOADED = 0xFFFF;


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //---- Construct/Destruct

    //
    //
    //
    //
    //
    //
    //
    void                    SetResourceBuffer(
                                void*               pUserBuffer,
                                FontInformation*    pFontInfo,
                                u16*                pAdjustTable);

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
    //
    //
    //
    //
    u16                     AdjustIndex(u16 index) const;

    //---- For searching GLGR block

    static bool             IsNullString(const char* str)   { return *str == '\0'; }

    //
    //
    //
    //
    //
    //
    //
    static bool             IncludeName(
                                const char* nameList,
                                const char* name);

    //
    //
    //
    //
    //

    //
    //
    //
    static bool             IsValidResource(
                                const void* brfnt,
                                u32         dataSize);

    //---- Construction

    //
    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  RequestData(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream,
                                u32                 size);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpDispatch(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpAnalyzeFileHeader(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpAnalyzeGLGR(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult ConstructOpAnalyzeFINF(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult ConstructOpAnalyzeCMAP(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpAnalyzeCWDH(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpAnalyzeTGLP(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpPrepairCopySheet(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpPrepairExpandSheet(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpCopy(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpSkip(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    //
    static ConstructResult ConstructOpExpand(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    //
    static ConstructResult  ConstructOpFatalError(
                                ConstructContext*   pContext,
                                CachedStreamReader* pStream);

private:
    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    u16*                    m_pGlyphIndexAdjustArray;
};

}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_ARCHIVE_FONT_BASE_H_
