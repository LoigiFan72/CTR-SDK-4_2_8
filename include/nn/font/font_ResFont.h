/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_ResFont.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_RES_FONT_H_
#define NN_FONT_FONT_RES_FONT_H_

#include <nn/types.h>
#include <nn/font/font_ResFontBase.h>

namespace nn {
namespace font {

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class ResFont : public ResFontBase
{
public:
    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                            ResFont();

    //
    virtual                 ~ResFont();

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
    bool                    SetResource(void* bfnt);

    //
    //
    //
    //
    //
    //
    void*                   RemoveResource();

    using ResFontBase::IsManaging;

    //
    //
    //
    //
    //
    //
    static u32              GetDrawBufferSize(const void* bfnt);

    //
    //
    //
    //
    void*                   GetDrawBuffer()
    {
        return GetTextureObjectsBufferPtr();
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
    void*                   SetDrawBuffer(void* buffer);

    //


private:
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
    //
    //
    static FontInformation* Rebuild(detail::BinaryFileHeader* fileHeader);
};

}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_RES_FONT_H_
