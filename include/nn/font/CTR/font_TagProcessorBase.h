/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_TagProcessorBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_TAG_PROCESSOR_BASE_H_
#define NN_FONT_CTR_FONT_TAG_PROCESSOR_BASE_H_

#include <nn/types.h>
#include <nn/util/util_Rect.h>

namespace nn {
namespace font {
namespace CTR {



template <typename CharType>
class TextWriterBase;


template <typename CharType>
struct PrintContext
{
    TextWriterBase<CharType>*   writer;     //
    const CharType*             str;        //
    const f32                   xOrigin;    //
    const f32                   yOrigin;    //
    u32                         flags;      //

    PrintContext(
        TextWriterBase<CharType>*   aWriter,
        const CharType*             aStr,
        const f32                   aXOrigin,
        const f32                   aYOrigin,
        u32                         aFlags
    )
    :   writer(aWriter),
        str(aStr),
        xOrigin(aXOrigin),
        yOrigin(aYOrigin),
        flags(aFlags)
    {}
};

#if defined( __CC_ARM ) || defined( __ARMCC_VERSION )
#pragma push
#pragma diag_suppress 2819  // class XXX has an implicitly instantiated key function YYY
#endif

//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
template <typename CharType>
class TagProcessorBase
{
public:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    
    //
    enum Operation
    {
        //
        //
        //
        OPERATION_DEFAULT,

        //
        //
        //
        //
        OPERATION_NO_CHAR_SPACE,

        //
        //
        //
        //
        OPERATION_CHAR_SPACE,

        //
        //
        //
        //
        OPERATION_NEXT_LINE,

        //
        //
        OPERATION_END_DRAW,

        //
        NUM_OF_OPERATION
    };

    /* ------------------------------------------------------------------------
            Functions
       ------------------------------------------------------------------------ */

    //
    //

    //
                        TagProcessorBase();

    //
    virtual             ~TagProcessorBase();

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
    virtual Operation   Process(
                            u16                     code,
                            PrintContext<CharType>* pContext);

    //
    //
    //
    //
    //
    //
    //
    //
    //
    virtual Operation   CalcRect(
                            util::Rect*             pRect,
                            u16                     code,
                            PrintContext<CharType>* pContext);

    //

private:
    /* ------------------------------------------------------------------------
            Types
       ------------------------------------------------------------------------ */
    typedef PrintContext<CharType>  ContextType;

    void                ProcessLinefeed(ContextType* pContext);
    void                ProcessTab(ContextType* pContext);
};

#if defined( __CC_ARM ) || defined( __ARMCC_VERSION )
#pragma pop
#endif

}   // namespace CTR
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_CTR_FONT_TAG_PROCESSOR_BASE_H_
