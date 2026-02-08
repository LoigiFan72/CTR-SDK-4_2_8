/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_RectDrawer.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_RECT_DRAWER_H_
#define NN_FONT_CTR_FONT_RECT_DRAWER_H_

//--------------------------------------
// Operation Settings

// Faster to render using glDrawArrays?
#define NN_FONT_RECTDRAWER_USE_DRAW_ARRAYS 1

// If it can be stored in the Buffer, store it and render simultaneously
#define NN_FONT_RECTDRAWER_USE_DRAW_BUFFER 1


#include <nn/assert.h>
#include <nn/font/CTR/font_RectDrawerCommand.h>
#include <nn/font/CTR/font_CmdCache.h>
#if defined(NN_PLATFORM_CTR)
    #include <nn/gx/CTR/gx_CommandAccess.h>
#endif
#include <nn/util/util_Color.h>

#define NN_FONT_COMMAND_SET_BLEND_FUNC( eq, src, dst ) \
    PICA_CMD_DATA_COLOR_OPERATION( \
        PICA_DATA_FRAGOP_MODE_DMP, \
        PICA_DATA_ENABLE_BLEND ), \
    PICA_CMD_HEADER_SINGLE( PICA_REG_COLOR_OPERATION ), \
    PICA_CMD_DATA_BLEND_FUNC( eq, src, dst ), \
    PICA_CMD_HEADER_SINGLE( PICA_REG_BLEND_FUNC )

#define NN_FONT_COMMAND_SET_BLEND_DEFAULT \
    NN_FONT_COMMAND_SET_BLEND_FUNC( \
        PICA_DATA_BLEND_EQUATION_ADD, \
        PICA_DATA_BLEND_FUNC_SRC_ALPHA, \
        PICA_DATA_BLEND_FUNC_ONE_MINUS_SRC_ALPHA )

namespace nn {
namespace font {
namespace CTR {

struct DispStringBuffer;
class CharWriter;

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class RectDrawer
{
public:
    enum
    {
        DONT_USE_SETUP_COMMAND = 0x1
    };

    //
    //
    //
    //
    //
    //
    //
    static u32          GetVertexBufferCommandBufferSize(
                            const void* shaderBinary,
                            u32         size);

    //
    //
    //
    //
    static void*        GetVertexBufferData();

    //
    //
    //
    //
    static u32          GetVertexBufferSize();

    //
    //
    //
    //
    //
    //
    //
    static u32          GetCommandBufferSize(
                            const void* shaderBinary,
                            u32         size);

    //
    //

    //
                        RectDrawer();

    //
    //
    //
    //
    //
    //
    //
    //
    virtual             ~RectDrawer();

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
    void                Initialize(
                            void*       vtxBufCmdBuf,
                            const void* shaderBinary,
                            u32         size);

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
    void                Initialize(
                            void*       vertexBuffer,
                            void*       commandBuffer,
                            const void* shaderBinary,
                            u32         size);

    //
    //
    //
    //
    //
    //
    virtual void        Finalize();

    //

    //
    //
    //
    //
    //
    //
    //
    //
    virtual void        DrawBegin(u32 flag = 0);

    //
    //
    //
    //
    //
    //
    //
    //
    virtual void        DrawEnd(u32 flag = 0);

    //
    //
    //
    //
    void                SetProjectionMtx(const nn::math::MTX44& mtx);

    //
    //
    //
    //
    void                SetViewMtxForText(const nn::math::MTX34& mtx);

    //
    //
    //
    //
    //
    //
    void                SetParallax(
                            f32     parallax,
                            f32     dLevel,
                            f32     addDist     = 0.0f
                        );

    //
    //
    //
    //
    void                BuildTextCommand(CharWriter* pCharWriter);

    //
    void                UniformAndDrawText(DispStringBuffer* pDispStringBuffer);

    //
    void                UseBeginCommand();

    //
    void                UseEndCommand();

protected:

    //
    static u32          SetUniformCommand(
                            u32*    buffer,
                            u32     num
                        )
    {
#if defined(NN_PLATFORM_CTR)
        buffer[2] = buffer[3];
        buffer[3] = PICA_CMD_HEADER_VS_F32(num);
#else
        NN_ASSERT(false);
        (void)buffer;
#endif
        return sizeof(u32) * (4 + 4 * num);
    }

    //
    void                DisableTextures();

    //
    void                AddUniformMtx();

#if defined(NN_FONT_RECTDRAWER_USE_DRAW_ARRAYS)
    //
    u32                 GetVertexIndexAddressOffset(u32 vtxNum) const;
#endif

    //
    const u32*          GetDrawCommands() const;

    //
    u32                 GetDrawCommandSize() const;

private:
    static void         InitializeStatic();

    void                InitializeCMD(
                            void*       vertexBuffer,
                            void*       commandBuffer,
                            const void* shaderBinary,
                            u32         size,
                            bool        initVertexBuffer);

    void                InitUniformBuffer(
                            u32* __restrict buf,
                            u32             addr);

    void                AddTextColor(
                            math::VEC4* __restrict          dst,
                            const util::Color8* __restrict  src,
                            int                             mode);

protected:
    ////////////////////////////// Vertex Shader Info

    //
    enum
    {
        UNIFORM_MTX_USE_MAX     =  3 /* mtx row */ + 4 /* vtx color */,
        UNIFORM_DATA_USE_MAX    =  1 /* rect */ + 3/* TexMapMax */ * 2,

        UNIFORM_TEXT_MTX_MAX    =  3,   // mtx34 row

        UNIFORM_PROJ_NUM        =  4,   // mtx44 row

        UNIFORM_PROJ_START      =  0,
        UNIFORM_ULCDDATA_START  = UNIFORM_PROJ_START + UNIFORM_PROJ_NUM,
        UNIFORM_CONST_START,
        UNIFORM_ADDR_START,
        UNIFORM_MTX_START       = 32,
        UNIFORM_DATA_START      = 64,

        UNIFORM_TEXTCOLOR_START = UNIFORM_MTX_START + UNIFORM_TEXT_MTX_MAX,

        UNIFORM_MAX             = 96
    };

    //
    enum
    {
#ifdef NN_FONT_RECTDRAWER_USE_DRAW_BUFFER

        UNIFORM_ADDR_NUM        = UNIFORM_MTX_START  - UNIFORM_ADDR_START,
        UNIFORM_MTX_NUM         = UNIFORM_DATA_START - UNIFORM_MTX_START,
        UNIFORM_DATA_NUM        = UNIFORM_MAX        - UNIFORM_DATA_START,

        UNIFORM_TEXTCOLOR_NUM   = (UNIFORM_DATA_START - UNIFORM_TEXTCOLOR_START) & ~((1 << 2) - 1),
#else

        UNIFORM_RESISTER_ADDR = 5,

        // If they cannot be rendered together, maximum of 8 registers
        UNIFORM_DATA_NUM  = 8,

        UNIFORM_ADDR_NUM      = UNIFORM_DATA_NUM - UNIFORM_RESISTER_ADDR,
#endif

        DRAW_VTX_NUM          = 6,
        BIND_ATTRIB_LOCATION  = 0
    };


    ////////////////////////////// Command

    //
    CmdCache            m_CmdCacheDrawBegin;

    //
    CmdCache            m_CmdCacheDrawEnd;

    //
    u8                  m_UniformAddrIndex;

    //
    u8                  m_UniformMtxIndex;

    //
    u8                  m_UniformDataIndex;

    //
    u8                  m_UniformTextColorIndex;

    //
    u32                 m_UniformProjBuffer[ 4 + 4 * (UNIFORM_PROJ_NUM + 1) ];

    //
    u32                 m_UniformAddrBuffer[ 4 + 4 * UNIFORM_ADDR_NUM ];

    //
    union
    {
        //
        u32                 buffer[ 4 + 4 * UNIFORM_MTX_NUM  ];

        //
        struct
        {

            //
            u32                 mtx  [ 4 + 4 * UNIFORM_TEXT_MTX_MAX ];

            //
            u32                 color[ 4 + 4 * UNIFORM_TEXTCOLOR_NUM ];
        } text;
    } m_UniformMtxBuffer;

    //
    u32                 m_UniformDataBuffer[ 4 + 4 * UNIFORM_DATA_NUM ];

    //
    struct UniformAddress
    {
        //
                            UniformAddress()
                            :   addrMtx(0.f),
                                addrSizeAndVtx(0.f),
                                addrTexCoord(0.f),
                                addrColor(0.f)
                            {}

        //
        f32                 addrMtx;

        //
        f32                 addrSizeAndVtx;

        //
        f32                 addrTexCoord;

        //
        f32                 addrColor;
    };

    //
    UniformAddress      m_UniformAddress;

    //
    UniformAddress *const
                        m_UniformAddr;

    //
    math::VEC4 *const   m_UniformMtx;

    //
    math::VEC4 *const   m_UniformData;

    //
    math::VEC4 *const   m_UniformTextColor;

    //
    void*               m_CommandBuffer;

    ////////////////////////////// Vertex Buffer Object

    //
    void*               m_VertexBufferArray;

    ////////////////////////////// Uniform

#if defined(NN_FONT_RECTDRAWER_USE_DRAW_ARRAYS)
    //
    u32                 m_VertexBufferBaseAddr;
#endif

    //
    //
    bool                m_IsColorDirty;
    NN_PADDING3;

private:
    struct VertexBuffer
    {
#if defined(NN_FONT_RECTDRAWER_USE_DRAW_ARRAYS)
        f32                 position[UNIFORM_ADDR_NUM][DRAW_VTX_NUM][4];
#else
        f32                 position[UNIFORM_ADDR_NUM][VERTEX_MAX][4];
        u16                 indexes[UNIFORM_ADDR_NUM][DRAW_VTX_NUM];
#endif
    };

    static bool         s_StaticInitialized;
    static VertexBuffer s_VertexBuffer;
};

inline
u32
RectDrawer::GetVertexBufferSize()
{
    return sizeof(s_VertexBuffer);
}


#if defined(NN_PLATFORM_CTR)
inline
u32*
SetVertexNumCmd(
    u32**   pCmdPtr,
    u32     addrOffset,
    u32     vtxNum
    )
{
#if defined(NN_FONT_RECTDRAWER_USE_DRAW_ARRAYS)
    // Address/type of vertex index
    // 0x227
    NN_FONT_ADD_SINGLE_COMMAND_PTR(
        *pCmdPtr,
        PICA_CMD_HEADER_SINGLE( PICA_REG_INDEX_ARRAY_ADDR_OFFSET ),
        PICA_CMD_DATA_INDEX_ARRAY_ADDR_OFFSET( addrOffset, 1 /* type */ ));
#else
    (void)addrOffset;
#endif

    // Number of vertices to render
    // 0x228
    NN_FONT_ADD_SINGLE_COMMAND_PTR(
        *pCmdPtr,
        PICA_CMD_HEADER_SINGLE( PICA_REG_DRAW_VERTEX_NUM ),
        PICA_CMD_DATA_DRAW_VERTEX_NUM( vtxNum ));

    return *pCmdPtr;
}
#endif

}   // namespace CTR
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_CTR_FONT_RECT_DRAWER_H_
