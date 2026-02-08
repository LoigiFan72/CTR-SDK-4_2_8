/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_PackedFont.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_PACKED_FONT_H_
#define NN_FONT_FONT_PACKED_FONT_H_

#include <nn/types.h>
#include <nn/font/font_ArchiveFontBase.h>

namespace nn {
namespace font {


//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------
class PackedFont : public ArchiveFontBase
{
public:
    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //
    //

    //
                        PackedFont();

    //
    virtual             ~PackedFont();

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
    static u32      GetRequireBufferSize(
                        const void* bfnt,
                        int         numSheetCache
    )
    {
        return GetRequireBufferSize(bfnt, LOAD_GLYPH_ALL, numSheetCache);
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
    //
    //
    //
    //
    //
    static u32      GetRequireBufferSize(
                        const void* bfnt,
                        const char* glyphGroups,
                        int         numSheetCache);

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
                        const void* bfnt,
                        f32         rateSheetCache
    )
    {
        return GetRequireBufferSize(bfnt, LOAD_GLYPH_ALL, rateSheetCache);
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
    //
    //
    //
    //
    static u32      GetRequireBufferSize(
                        const void* bfnt,
                        const char* glyphGroups,
                        f32         rateSheetCache
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
    void            InitStreamingConstruct(
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
    int             GetNumCache() const { return m_NumSheetCache; }

    //
    //
    //
    //
    //
	//
    //
    bool            PreloadSheet(CharCode c);

    //
    //
    //
    //
    //
    //
    //
    //
    bool            LockSheet(CharCode c);

    //
    //
    //
    //
    //
    //
    //
    bool            UnlockSheet(
                        CharCode    c,
                        bool        bUnload = true
                    );

    //
    //
    void            UnlockSheetAll();

    //


    //
    //

    //
    //
    //
    //
    //
    virtual void    GetGlyph(
                        Glyph*      glyph,
                        CharCode    c
                    ) const;

    //


protected:

    //
    //

    virtual int             GetActiveSheetNum() const;

    //


private:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    // Class for managing Least Recently Used
    class LRUManager
    {
    public:
        struct OrderNode
        {
            u16 prevIndex;
            u16 nextIndex;
        };

        static u32          GetRequireBufferSize(int numNode)
        {
            return sizeof(OrderNode) * (numNode + 1);
        }

        //
        //
        //
        //
        //
        void                Init(
                                void*   buffer,
                                int     numOrderNode);

        //
        //
        //
        //
        void                Use(int index);

        //
        //
        //
        //
        void                Unuse(int index);

        //
        //
        //
        //
        void                Lock(int index);

        //
        //
        //
        //
        void                Unlock(int index);

        int                 GetLastIndex() const    { return GetRootNode().prevIndex; }

        bool                IsLocked(int index) const
        {
            const OrderNode& node = GetNode(index);
            return IsLockedNode(node);
        }

        int                 GetNumLocked() const    { return mNumLockedNode; }

    private:
        bool                IsLockedNode(const OrderNode& node) const
        {
            NN_ASSERT( ! (node.prevIndex == LOCKED_INDEX) ^ (node.nextIndex == LOCKED_INDEX) );
            return (node.prevIndex == LOCKED_INDEX);
        }

        void                MarkLocked(OrderNode& node) const
        {
            node.prevIndex = LOCKED_INDEX;
            node.nextIndex = LOCKED_INDEX;
        }

        void                Unlink(OrderNode& node)
        {
            OrderNode& prev = GetNode(node.prevIndex);
            OrderNode& next = GetNode(node.nextIndex);
            prev.nextIndex = node.nextIndex;
            next.prevIndex = node.prevIndex;
        }

        OrderNode&          GetRootNode()           { return GetNode(mNumOrderNode); }

        const OrderNode&    GetRootNode() const     { return GetNode(mNumOrderNode); }

        OrderNode& GetNode(int index)               { return mpOrderNodeArray[index]; }

        const OrderNode& GetNode(int index) const   { return mpOrderNodeArray[index]; }

    private:
        static const u16    LOCKED_INDEX  = 0xFFFF;

        OrderNode*          mpOrderNodeArray;
        u16                 mNumOrderNode;
        u16                 mNumLockedNode;
    };


    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const u16 SHEET_INDEX_NOT_LOADED = 0xFFFF;


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //---- Gets glyphs

    //
    //
    //
    //
    //
    //
    //
    void                MakeGlyph(
                            Glyph*      glyph,
                            GlyphIndex  gindex,
                            int         cacheIndex
                        ) const;

    //---- Decompresses sheet

    //
    //
    //
    //
    //
    //
    int                 LoadSheet(int compIndex) const;

    //
    //
    //
    //
    void                UnloadSheet(int compIndex) const;

    //---- Manages sheet state

    //
    //
    //
    //
    //
    //
    //
    int                 GetSheetIndex(CharCode c) const;

    //
    //
    //
    //
    //
    //
    //
    int                 CalcSheetIndex(GlyphIndex index) const;

    //
    //
    //
    //
    //
    //
    //
    //
    //
    int                 GetCacheIndex(int compIndex) const;

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
    int                 GetCacheUser(int cacheIndex) const;

    //
    //
    //
    //
    //
    //
    //
    void                SetCacheUser(
                            int compIndex,
                            int cacheIndex
                        ) const;

    //
    //
    //
    //
    //
    //
    void                ResetCacheUser(
                            int compIndex, 
                            int cacheIndex
                        ) const;

    //---- Gets sheet

    //
    //
    //
    //
    //
    //
    u8*                 GetLoadedSheet(int cacheIndex) const;

    //
    //
    //
    //
    //
    //
    const u8*           GetCompSheet(int compIndex) const;

    //---- Memory allocation

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
    u16*                AssignMemory(
                            u8* buffer,
                            u32 bufferSize,
                            u32 numResSheet,
                            u32 numLoadSheet,
                            u32 sheetSize);


    //---- Necessary memory size calculation

    //
    //
    //
    //
    //
    //
    //
    //
    //
    static u32          CalcCopySize(
                            const FontGlyphGroupsAcs&   gg,
                            const char*                 glyphGroups,
                            int*                        pNumLoadSheet);

    //
    //
    //
    //
    //
    //
    //
    static u32          CalcCacheSize(
                            const FontGlyphGroupsAcs&   gg,
                            int                         numSheetCache);

    //---- Streaming process

    //
    //
    //
    //
    //
    //
    //
    ConstructResult     ConstructOpAnalyzeGLGRPacked(
                            ConstructContext*   pContext,
                            CachedStreamReader* pStream);

    //
    //
    //
    //
    //
    //
    //
    static ConstructResult
                        ConstructOpPrepairCopyPackedSheet(
                            ConstructContext*   pContext,
                            CachedStreamReader* pStream);

    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    //
    mutable LRUManager  m_LRUMan;

    u16                 m_NumCompSheet;         //
    u16                 m_NumSheetCache;        //

    //
    u16*                m_pCacheIndexArray;     // mNumLoadedSheet

    //
    u16*                m_pCacheUserArray;      // m_NumSheetCache

    //
    const u8**          m_pCompSheetArray;      // mNumLoadedSheet

    //
    u8*                 m_pSheetCache;          // sheetSize * m_NumSheetCache
};

}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_PACKED_FONT_H_
