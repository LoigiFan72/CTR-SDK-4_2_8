/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_FONT_TYPES_H_
#define NN_FONT_FONT_TYPES_H_

#include <nn/types.h>
#include <nn/util/util_Color.h>
#include <nn/font/font_DrawerTypes.h>

namespace nn {
namespace font {
namespace internal {

enum
{
    VERTEX_ATTR_POS,
    VERTEX_ATTR_POS_Z,
    VERTEX_ATTR_COLOR,
    VERTEX_ATTR_TEXCOORD,

    VERTEX_ATTR_NUM
};

enum
{
    POS_X,
    POS_Y,

    POS_NUM
};

enum
{
    COLOR_R,
    COLOR_G,
    COLOR_B,
    COLOR_A,

    COLOR_NUM
};

enum
{
    TEXCOORD_X,
    TEXCOORD_Y,

    TEXCOORD_NUM
};

enum
{
    TRIFAN_VTX_RT,
    TRIFAN_VTX_LT,
    TRIFAN_VTX_LB,
    TRIFAN_VTX_RB,

    TRIFAN_VTX_MAX
};

enum
{
    LOC_PROJECTION,
    LOC_MODELVIEW,

    LOC_FRAGMENTLIGHTING_ENABLED,
    LOC_TEXTURE0_SAMPLERTYPE,
    LOC_FOG_MODE,
    LOC_FRAGOPERATION_ENABLEALPHATEST,

    LOC_MAX
};

enum
{
    TCLOC_SRCRGB,
    TCLOC_SRCALPHA,
    TCLOC_OPERANDRGB,
    TCLOC_OPERANDALPHA,
    TCLOC_COMBINERGB,
    TCLOC_COMBINEALPHA,
    TCLOC_SCALERGB,
    TCLOC_SCALEALPHA,
    TCLOC_CONSTRGBA,

    TCLOC_MAX
};

enum
{
    TEXENV_3,
    TEXENV_4,
    TEXENV_5,

    TEXENV_MAX
};

enum TextColor
{
    TEXTCOLOR_START,        //
    TEXTCOLOR_END,          //

    TEXTCOLOR_MAX           //
};

//
const int               VERTEX_INDEX_NUM = 6;

struct VertexAttribute
{
    f32                 pos[POS_NUM];
    util::Color8        color;
    f32                 tex[TEXCOORD_NUM];
};

}   // namespace internal
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_FONT_TYPES_H_
