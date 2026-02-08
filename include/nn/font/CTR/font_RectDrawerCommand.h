/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_RectDrawerCommand.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_RECT_DRAWER_COMMAND_H_
#define NN_FONT_CTR_FONT_RECT_DRAWER_COMMAND_H_

#include <nn/util/util_Float24.h>

// Accumulate on the command list.
#define NN_FONT_ADD_COMMANDS_PTR( ptr, command, size )          \
    std::memcpy( ptr, command, size );                          \
    (ptr) += (size) >> 2

#define NN_FONT_ADD_SINGLE_COMMAND_PTR( ptr, header, data )     \
    *(ptr)++ = (data);                                          \
    *(ptr)++ = (header)

#define NN_FONT_RECTDRAWER_ADD_COMMAND( command, size )         \
    std::memcpy( __cb_current_command_buffer, command, size );  \
    __cb_current_command_buffer += (size) >> 2

#define NN_FONT_RECTDRAWER_ADD_SINGLE_COMMAND( header, data )   \
    *__cb_current_command_buffer++ = (data);                    \
    *__cb_current_command_buffer++ = (header)


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
enum
{
    NN_FONT_CMD_CULL_FACE_DISABLE,
    NN_FONT_CMD_CULL_FACE_FRONT,
    NN_FONT_CMD_CULL_FACE_BACK,

    NN_FONT_CMD_CULL_FACE_MASK      = 0x3
};


namespace nn {
namespace font {
namespace CTR {

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
struct ColorBufferInfo
{
    u16         width;    //
    u16         height;   //
    u8          depth;    //
    NN_PADDING3;
};

}   // namespace CTR
}   // namespace font
}   // namespace nn

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_BEGIN_COMMAND_BLOCK                                 \
    {                                                                   \
        const u32 commands[] = {

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_END_COMMAND_BLOCK                                   \
        };                                                              \
        NN_FONT_RECTDRAWER_ADD_COMMAND( commands, sizeof(commands) );   \
    }

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_VIEWPORT( x, y, width, height )                     \
    nn::util::Float24::Float32ToBits24( (width) / 2.0f ),                   \
    PICA_CMD_HEADER_BURSTSEQ( PICA_REG_VIEWPORT_WIDTH1, 4 ),                \
    nn::util::Float31::Float32ToBits31( 2.0f / (width)  ) << 1,             \
    nn::util::Float24::Float32ToBits24( (height) / 2.0f ),                  \
    nn::util::Float31::Float32ToBits31( 2.0f / (height) ) << 1,             \
    0,  /* Alignment adjustment */                                              \
    PICA_CMD_DATA_VIEWPORT_XY( static_cast<u16>(x), static_cast<u16>(y) ),  \
    PICA_CMD_HEADER_SINGLE( PICA_REG_VIEWPORT_XY )

//---------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_CULL_FACE( mode )    PICA_CMD_SET_CULL_FACE( mode )


#define NN_FONT_CMD_SCISSOR_VAL( s, c )                                \
            static_cast<u16>( (s) >= (c) ? (c) - 1: ((s) < 0 ? 0: (s)) )

//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_SCISSOR( x, y, w, h, cbSz )                     \
    PICA_CMD_DATA_SCISSOR( true ),                                      \
    PICA_CMD_HEADER_BURSTSEQ( PICA_REG_SCISSOR, 3 ),                    \
    NN_FONT_CMD_SCISSOR_VAL( x, (cbSz).width )                          \
        | NN_FONT_CMD_SCISSOR_VAL( y, (cbSz).height ) << 16,            \
    NN_FONT_CMD_SCISSOR_VAL( (x) + (w) - 1, (cbSz).width )              \
        | NN_FONT_CMD_SCISSOR_VAL( (y) + (h) - 1, (cbSz).height ) << 16

//---------------------------------------------------------------------------
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_DISABLE_SCISSOR( cbSz )         \
    PICA_CMD_DATA_SCISSOR( false ),                     \
    PICA_CMD_HEADER_BURSTSEQ( PICA_REG_SCISSOR, 3 ),    \
    0                  | 0 << 16,                       \
    ((cbSz).width - 1) | ((cbSz).height - 1) << 16

//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_WBUFFER_DEPTHRANGE_POLYGONOFFSET(                                   \
            wScale, near, far, units, cbSz )                                                \
    ((wScale) == 0.0f ? 1: 0) << 0,                                                         \
    PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_OP_WSCALE ),                                      \
    nn::util::Float24::Float32ToBits24(                                                     \
        (wScale) != 0.0f ? -(wScale): (near) - (far) ),                                     \
    PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_OP_WSCALE_DATA1 ),                                \
    nn::util::Float24::Float32ToBits24(                                                     \
        (near)                                                                              \
            - ((near) - (far)) * static_cast<f32>(units)                                    \
                  / ((1 << ((cbSz).depth == PICA_DATA_DEPTH_COMPONENT16 ? 16: 24)) - 1) ),  \
    PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_OP_WSCALE_DATA2 )

//---------------------------------------------------------------------------
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_ENABLE_EARLY_DEPTH_TEST( isEnabled )        \
    PICA_CMD_DATA_EARLY_DEPTH_TEST( isEnabled ),                    \
    PICA_CMD_HEADER_SINGLE_BE( PICA_REG_EARLY_DEPTH_TEST1, 0x1 ),   \
    PICA_CMD_DATA_EARLY_DEPTH_TEST( isEnabled ),                    \
    PICA_CMD_HEADER_SINGLE( PICA_REG_EARLY_DEPTH_TEST2 )

//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_STENCIL_FUNC_MASK( func, ref, andBits, writableBits )           \
    PICA_CMD_DATA_STENCIL_TEST( true/*isEnabled*/, func, writableBits, ref, andBits ),  \
    PICA_CMD_HEADER_SINGLE( PICA_REG_STENCIL_TEST )

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_STENCIL_OP( sfail, zfail, zpass )       \
    PICA_CMD_DATA_STENCIL_OP( sfail, zfail, zpass ),            \
    PICA_CMD_HEADER_SINGLE( PICA_REG_STENCIL_OP )

//---------------------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_DISABLE_STENCIL_TEST()                      \
    PICA_CMD_DATA_STENCIL_TEST( false/*isEnabled*/, 0, 0, 0, 0 ),   \
    PICA_CMD_HEADER_SINGLE( PICA_REG_STENCIL_TEST )

//---------------------------------------------------------------------------
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
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_DEPTH_FUNC_COLOR_MASK(                                  \
            isDepthTestEnabled, depthFunc, depthMask, red, green, blue, alpha ) \
    PICA_CMD_DATA_DEPTH_COLOR_MASK( isDepthTestEnabled, depthFunc,              \
        red, green, blue, alpha, depthMask ),                                   \
    PICA_CMD_HEADER_SINGLE( PICA_REG_DEPTH_COLOR_MASK )

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_DEPTH_FUNC2( func )                                                     \
    PICA_CMD_DATA_GAS_DELTAZ_DEPTH( 0 /*deltaZ*/,                                               \
        (func) >= PICA_DATA_DEPTH_TEST_GREATER ? PICA_DATA_DEPTH_TEST2_GREATER:                 \
            ( (func) >= PICA_DATA_DEPTH_TEST_EQUAL ? PICA_DATA_DEPTH_TEST2_OTHER: (func) ) ),   \
    PICA_CMD_HEADER_SINGLE_BE( PICA_REG_GAS_DELTAZ_DEPTH, 0x4 )

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_FONT_CMD_SET_FBACCESS(                                                   \
        colorRead, colorWrite, depthRead, depthWrite, stencilRead, stencilWrite)    \
    (colorRead ) ? 0xF: 0,                                                          \
    PICA_CMD_HEADER_BURSTSEQ( PICA_REG_COLOR_BUFFER_READ, 4 ),                      \
    (colorWrite) ? 0xF: 0,                                                          \
    ((depthRead ) ? 1: 0) << 1 | ((stencilRead ) ? 1: 0) << 0,                      \
    ((depthWrite) ? 1: 0) << 1 | ((stencilWrite) ? 1: 0) << 0,                      \
    0   // Alignment adjustment


#endif //  NN_FONT_CTR_FONT_RECT_DRAWER_COMMAND_H_
