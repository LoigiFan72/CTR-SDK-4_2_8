/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_DispStringBuffer.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_DISP_STRING_BUFFER_H_
#define NN_FONT_CTR_FONT_DISP_STRING_BUFFER_H_

#include <nn/font/font_Types.h>

namespace nn {
namespace font {
namespace CTR {

struct CharAttribute
{
    math::VEC4          pos;
    util::Color8        color[internal::TEXTCOLOR_MAX];
    math::VEC4          tex;
    const internal::TextureObject*
                        pTexObj;        //
};

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
struct DispStringBuffer
{
    const u32           charCountMax;           //

    u16                 charCount;              //
    u16                 drawCharCount;          //
    
    u8                  generatedCommand;       //
    u8                  padding[3];

    u8*                 drawFlags;              //
    u32*                commandBuffer;          //
    u32                 commandBufferSize;      //
    u32                 commandBufferCapacity;  //
    u32                 textColorCommandOffset; //

    //
    CharAttribute* GetCharAttrs() const
    {
        return reinterpret_cast<CharAttribute*>( reinterpret_cast<uptr>(this) + sizeof(*this) );
    }

    static u32          CalcCommandBufferCapacity(u32 charNum);

    //
    explicit            DispStringBuffer(u32 charNum);

    //
    void                ClearCommand()
    {
        generatedCommand = false;
    }

    //
    bool                IsGeneratedCommand()
    {
        return 0 != generatedCommand;
    }

    //
    bool                IsCommandEmpty()
    {
        return 0 == commandBufferSize;
    }

    //
    u16                 GetDrawCharCount() const    { return drawCharCount; }

    //
    void                SetDrawCharCount(u16 count)
    {
        drawCharCount = count;
    }

    //
    void                ResetDrawCharCount()
    {
        SetDrawCharCount(0xFFFF);
    }
};

}   // namespace CTR
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_CTR_FONT_DISP_STRING_BUFFER_H_
