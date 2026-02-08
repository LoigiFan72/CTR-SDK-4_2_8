/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_TextWriterBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_TEXT_WRITER_BASE_H_
#define NN_FONT_CTR_FONT_TEXT_WRITER_BASE_H_

#include <cstddef>
#include <cwchar>
#include <cstdio>
#include <cstring>
#include <cfloat>
#include <nn/types.h>
#include <nn/font/font_Font.h>
#include <nn/font/CTR/font_TagProcessorBase.h>
#include <nn/font/CTR/font_CharWriter.h>
#include <nn/util/util_Rect.h>


namespace nn {
namespace font {
namespace CTR {


//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
template <typename CharType>
class TextWriterBase: public CharWriter
{
public:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */

    //
    enum PositionFlag
    {
        //Horizontal positioning
        HORIZONTAL_ALIGN_LEFT       = 0x0,      //
        HORIZONTAL_ALIGN_CENTER     = 0x1,      //
        HORIZONTAL_ALIGN_RIGHT      = 0x2,      //
        HORIZONTAL_ALIGN_MASK       = 0x3,

        // Horizontal position of the origin
        HORIZONTAL_ORIGIN_LEFT      = 0x00,     //
        HORIZONTAL_ORIGIN_CENTER    = 0x10,     //
        HORIZONTAL_ORIGIN_RIGHT     = 0x20,     //
        HORIZONTAL_ORIGIN_MASK      = 0x30,

        // Vertical position of the origin
        VERTICAL_ORIGIN_TOP         = 0x000,    //
        VERTICAL_ORIGIN_MIDDLE      = 0x100,    //
        VERTICAL_ORIGIN_BOTTOM      = 0x200,    //
        VERTICAL_ORIGIN_BASELINE    = 0x300,    //
        VERTICAL_ORIGIN_MASK        = 0x300
    };

    enum ContextFlag
    {
        //
        CONTEXT_NO_CHAR_SPACE       = 0x1
    };

    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    //
    static const u32 DEFAULT_DRAWFLAG =
        HORIZONTAL_ALIGN_LEFT | HORIZONTAL_ORIGIN_LEFT | VERTICAL_ORIGIN_TOP;


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                        TextWriterBase();

    //
                        ~TextWriterBase();

    //

    //
    //

    //
    //
    //
    //
    void                SetLineSpace(f32 space)     { m_LineSpace = space; }

    //
    //
    //
    //
    f32                 GetLineSpace() const        { return m_LineSpace; }

    //
    //
    //
    //
    void                SetLineHeight(f32 height);

    //
    //
    //
    //
    f32                 GetLineHeight() const;

    //
    //
    //
    //
    void                SetCharSpace(f32 space)     { m_CharSpace = space; }

    //
    //
	//
    //
    f32                 GetCharSpace() const        { return m_CharSpace; }

    //
    //
    //
    //
    void                SetTabWidth(int tabWidth)   { m_TabWidth = tabWidth; }

    //
    //
    //
    //
    int                 GetTabWidth() const         { return m_TabWidth; }

    //

    //
    //

    //
    //
    //
    //
    void                SetWidthLimit(f32 limit)    { m_WidthLimit  = limit; }

    //
    //
    //
    //
    //
    f32                 GetWidthLimit() const       { return m_WidthLimit; }

    //
    void                ResetWidthLimit()           { SetWidthLimit(FLT_MAX); }

    //


    //
    //

	//
    //
    //
    //
    void                SetDrawFlag(u32 flags)      { m_DrawFlag = flags; }

    //
    //
    //
    //
    u32                 GetDrawFlag() const         { return m_DrawFlag; }

    //


    //
    //

    //
    //
    //
    //
    void                SetTagProcessor(TagProcessorBase<CharType>* tagProcessor)
    {
        NN_POINTER_ASSERT(tagProcessor);

        m_TagProcessor = tagProcessor;
    }

    //
    //
    //
    //
    TagProcessorBase<CharType>&
                        GetTagProcessor() const     { return *m_TagProcessor; }

    //
    void                ResetTagProcessor()         { m_TagProcessor = &s_DefaultTagProcessor; }

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
    f32                 CalcFormatStringWidth(
                            const CharType* format,
                            ...
                        ) const;

    //
    //
    //
    //
    //
    //
    f32                 CalcStringWidth(
                            const CharType* str
                        ) const
    {
        NN_POINTER_ASSERT(str);

        return CalcStringWidth(str, StrLen(str));
    }

    //
    //
    //
    //
    //
    //
    //
    f32                 CalcStringWidth(
                            const CharType* str,
                            int             length
                        ) const;


    //
    //
    //
    //
    //
    //
    //
    //
    //
    f32                 CalcFormatStringHeight(
                            const CharType* format,
                            ...
                        ) const;

    //
    //
    //
    //
    //
    //
    f32                 CalcStringHeight(
                            const CharType* str
                        ) const
    {
        NN_POINTER_ASSERT(str);

        return CalcStringHeight(str, StrLen(str));
    }

    //
    //
    //
    //
    //
    //
    //
    f32                 CalcStringHeight(
                            const CharType* str,
                            int             length
                        ) const;

    //
    //
    //
    //
    //
    //
    void                CalcFormatStringRect(
                            util::Rect*     pRect,
                            const CharType* format,
                            ...
                        ) const;


    //
    //
    //
    //
    //
    //
    void                CalcVStringRect(
                            util::Rect*     pRect,
                            const CharType* format,
                            std::va_list    args
                        ) const;


    //
    //
    //
    //
    //
    void                CalcStringRect(
                            util::Rect*     pRect,
                            const CharType* str
                        ) const
    {
        NN_POINTER_ASSERT(pRect);
        NN_POINTER_ASSERT(str);

        CalcStringRect(pRect, str, StrLen(str));
    }

    //
    //
    //
    //
    //
    //
    void                CalcStringRect(
                            util::Rect*     pRect,
                            const CharType* str,
                            int             length
                        ) const;

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
    f32                 Printf(
                            const CharType* format,
                            ... );

    //
    //
    //
    //
    //
    //
    //
    f32                 VPrintf(
                            const CharType* format,
                            std::va_list    args);

    //
    //
    //
    //
    //
    //
    f32                 Print(
                            const CharType* str
                        )
    {
        NN_POINTER_ASSERT(str);

        return Print(str, StrLen(str));
    }

    //
    //
    //
    //
    //
    //
    //
    f32                 Print(
                            const CharType* str,
                            int             length);

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
    static void*        SetBuffer(
                            std::size_t size
                        )
    {
        NN_FONT_MIN_ASSERT(size, 1);
        void* oldBuffer = s_FormatBuffer;

        s_FormatBuffer       = NULL;
        s_FormatBufferSize   = size;

        return oldBuffer;
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
    static void*        SetBuffer(
                            CharType*   buffer,
                            std::size_t size
                        )
    {
        NN_POINTER_ASSERT(buffer);
        NN_FONT_MIN_ASSERT(size, 1);
        void* oldBuffer = s_FormatBuffer;

        s_FormatBuffer       = buffer;
        s_FormatBufferSize   = size;

        return oldBuffer;
    }

    //
    //
    //
    //
    static const void*  GetBuffer()
    {
        return s_FormatBuffer;
    }

    //
    //
    //
    //
    static std::size_t  GetBufferSize()
    {
        return s_FormatBufferSize;
    }

    //


    //---- vsnprintf branch
    static int          VSNPrintf(
                            char*           buffer,
                            std::size_t     count,
                            const char*     format,
                            std::va_list    arg
                        )
    {
        #if ! defined(_MSC_VER)
            using namespace std;
        #endif

        return vsnprintf(buffer, count, format, arg);
    }

    static int          VSNPrintf(
                            wchar_t*        buffer,
                            std::size_t     count,
                            const wchar_t*  format,
                            std::va_list    arg
                        )
    {
        #if ! defined(_MSC_VER)
            using namespace std;
        #endif

        return vswprintf(buffer, count, format, arg);
    }

    static int          StrLen(const char* str)
    {
        return static_cast<int>(std::strlen(str));
    }

    static int          StrLen(const wchar_t* str)
    {
        return static_cast<int>(std::wcslen(str));
    }


    using CharWriter::Print;

private:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    typedef TagProcessorBase<CharType>  TagProcessor;
    typedef const CharType*             StreamType;

    /* ------------------------------------------------------------------------
            Constants
       ------------------------------------------------------------------------ */
    static const int DEFAULT_FORMAT_BUFFER_SIZE = 256;

    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //
    //
    //
    //
    f32                 CalcLineWidth(
                            StreamType  str,
                            int         length);

    //
    //
    //
    //
    //
    //
    //
    //
    bool                CalcLineRectImpl(
                            util::Rect* pRect,
                            StreamType* pStr,
                            int         length);

    //
    //
    //
    //
    //
    //
    void                CalcStringRectImpl(
                            util::Rect* pRect,
                            StreamType  str,
                            int         length);

    //
    //
    //
    //
    //
    f32                 PrintImpl(
                            StreamType  str,
                            int         length);


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
    f32                 AdjustCursor(
                            f32*        pXOrigin,
                            f32*        pYOrigin,
                            StreamType  str,
                            int         length);

    //
    //
    //
    //
    //
    //
    //
    bool                IsDrawFlagSet(
                            u32 mask,
                            u32 flag
                        ) const
    {
        return (m_DrawFlag & mask) == flag;
    }

    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */

    static CharType*        s_FormatBuffer;         //
    static std::size_t      s_FormatBufferSize;     //

    //
    static TagProcessor     s_DefaultTagProcessor;

    f32                     m_WidthLimit;           //
    f32                     m_CharSpace;            //
    f32                     m_LineSpace;            //
    int                     m_TabWidth;             //
    u32                     m_DrawFlag;             //
    TagProcessor*           m_TagProcessor;         //
};

}   // namespace CTR
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_CTR_FONT_TEXT_WRITER_BASE_H_
