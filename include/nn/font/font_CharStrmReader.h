/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_CharStrmReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_CHAR_STRM_READER_H_
#define NN_FONT_FONT_CHAR_STRM_READER_H_

#include <nn/types.h>
#include <nn/assert.h>

namespace nn {
namespace font {


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class CharStrmReader
{
    friend class Font;

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
                            CharStrmReader(const CharStrmReader& rhs)
    : mCharStrm(rhs.mCharStrm),
      mReadFunc(rhs.mReadFunc)
    {
    }

    //
                            ~CharStrmReader()
    {
    }

    //


    //
    //

    //
    //
    //
    //
    void                    Set(const char* stream)
    {
        NN_POINTER_ASSERT(stream);
        NN_ASSERT(  mReadFunc == &CharStrmReader::ReadNextCharUTF8
                   || mReadFunc == &CharStrmReader::ReadNextCharCP1252
                   || mReadFunc == &CharStrmReader::ReadNextCharSJIS   );
        mCharStrm = stream;
    }

    //
    //
    //
    //
    void                    Set(const wchar_t* stream)
    {
        NN_ALIGN_ASSERT(stream, 2);
        NN_POINTER_ASSERT(stream);
        NN_ASSERT(mReadFunc == &CharStrmReader::ReadNextCharUTF16);
        mCharStrm = stream;
    }

    //
    //
    //
    //
    const void*             GetCurrentPos() const   { return mCharStrm; }

    //
    //
    //
    //
    //
    u16                     Next()                  { return (this->*mReadFunc)(); }

    //

private:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    typedef u16 (CharStrmReader::*ReadNextCharFunc)();


    /* ------------------------------------------------------------------------
            Variables
       ------------------------------------------------------------------------ */
    const void*             mCharStrm;      // Pointer to the current stream position
    const ReadNextCharFunc  mReadFunc;      // Pointer to the stream interpretation function


    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */
    //---- Constructor
    explicit                CharStrmReader(ReadNextCharFunc func)
    : mCharStrm(NULL),
      mReadFunc(func)
    {
    }

    //---- Stream operations
    template <typename CharType>
    CharType                GetChar(int offset=0) const
    {
        const CharType* charStrm = reinterpret_cast<const CharType*>(mCharStrm);
        return *(charStrm + offset);
    }

    template <typename CharType>
    void                    StepStrm(int step=1)
    {
        const CharType*& charStrm = reinterpret_cast<const CharType*&>(mCharStrm);
        charStrm += step;
    }

    //
    //
    //
    //
    //
    u16                     ReadNextCharUTF8();

    //
    //
    //
    //
    //
    u16                     ReadNextCharUTF16();

    //
    //
    //
    //
    //
    u16                     ReadNextCharCP1252();

    //
    //
    //
    //
    //
    u16                     ReadNextCharSJIS();
};



}   // namespace font
}   // namespace nn

#endif  // NN_FONT_FONT_CHAR_STRM_READER_H_
