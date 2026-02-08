/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_TextWriterResource.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_TEXT_WRITER_RESOURCE_H_
#define NN_FONT_CTR_FONT_TEXT_WRITER_RESOURCE_H_

#include <nn/types.h>
#include <nn/math.h>
#include <nn/util.h>
#include <nn/font/font_Types.h>

namespace nn {
namespace font {
namespace CTR {

struct DispStringBuffer;
class CharWriter;

class TextWriterResource : private nn::util::NonCopyable<TextWriterResource>
{
    friend class CharWriter;

public:

    //
    //

    //
                        TextWriterResource();

    //
                        ~TextWriterResource();

    //


    //
    //

    //
    //
    //
    //
    //
    void                InitResource(
                            const void* shaderBinary,
                            u32         size);

    //
    void                Finalize();

    //
    void                DeleteResource()    { Finalize(); }

    //
    static void         FinalizeGX();

    //


    //
    //

    //
    //
    //
    //
    void                SetProjectionMtx(const nn::math::MTX44& mtx) const;

    //
    //
    //
    //
    void                SetViewMtx(const nn::math::MTX34& mtx) const;

    //


    //
    //

    //
    void                ActiveGlProgram() const
    {
        glUseProgram(m_ProgramId);
    }

    //
    //
    //
    //
    u32                 GetGlProgram() const                { return m_ProgramId; }

    //

private:
    enum
    {
        VBO_ARRAY,
        VBO_ELEMENT_ARRAY,

        VBO_NUM
    };

    typedef const int   (*TexEnvUniformLocationSquareArray)[internal::TCLOC_MAX];

    GLuint              GetTextureID() const                { return m_TextureId; }

    internal::VertexAttribute*
                        GetVertexAttributeArray()           { return m_VtxAttrs; }

    //
    //
    //
    //
    const int*          GetUniformLocations() const         { return m_UniformLocations; }

    //
    //
    //
    //
    TexEnvUniformLocationSquareArray
                        GetTexEnvUniformLocations() const   { return m_TexEnvUniformLocations; }

    //
    void                ResetLoadingTexture()     { m_LoadingTexture = NULL; }

    //
    //
    //
    //
    bool                SetLoadingTexture(const void* pTexture)
    {
        const bool isChanged = m_LoadingTexture != pTexture;
        m_LoadingTexture = pTexture;
        return isChanged;
    }

    void                SetPosZ(f32 posZ);

    void                UpdatePosZ(f32 posZ)
    {
        if (m_PosZ != posZ)
        {
            SetPosZ(posZ);
        }
    }

    u32                 m_ProgramId;            //
    GLuint              m_TextureId;            //
    internal::VertexAttribute
                        m_VtxAttrs[internal::TRIFAN_VTX_MAX];
    int                 m_UniformLocations[internal::LOC_MAX];
    int                 m_TexEnvUniformLocations[internal::TEXENV_MAX][internal::TCLOC_MAX];
    const void*         m_LoadingTexture;       //
    f32                 m_PosZ;                 //

    bool                m_IsInitialized;        //
    NN_PADDING3;
};

}   // namespace CTR
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_TEXT_WRITER_RESOURCE_H_
