/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_VertexInput.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_VERTEXINPUT_H_
#define NN_GD_CTR_GD_VERTEXINPUT_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>

#include <nn/gd/CTR/gd_Resource.h>
#include <nn/gd/CTR/gd_Shader.h>

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
*/
#else
/* Please see man pages for details 
    
*/
#endif

namespace nn {
namespace gd {
namespace CTR {

class InputElementDescription;
class InputLayout;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
    
    
*/
#endif
class VertexInputStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum ShaderStreamFormatType
    {
        STREAM_TYPE_BYTE = 0,
        STREAM_TYPE_UNSIGNED_BYTE = 1,
        STREAM_TYPE_SHORT = 2,
        STREAM_TYPE_FLOAT = 3,

        STREAM_TYPE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum IndexFormat
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        INDEX_FORMAT_UBYTE  = 0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        INDEX_FORMAT_USHORT = 1,

        INDEX_FORMAT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif 
    enum PrimitiveTopology
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        PRIMITIVE_TOPOLOGY_TRIANGLELIST     = 0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        PRIMITIVE_TOPOLOGY_TRIANGLESTRIP    = 1,
        
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        PRIMITIVE_TOPOLOGY_TRIANGLEFAN      = 2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        PRIMITIVE_TOPOLOGY_GEOMETRY         = 3,

        PRIMITIVE_TOPOLOGY_RESERVED_MAX_U32 = 0xffffffffu

    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        

        
        
        
    */
    #endif
    static nnResult SetIndexBuffer(VertexBufferResource* indexBuffer, IndexFormat format, u32 offset);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        
    */
    #endif
    static nnResult SetInputLayout(InputLayout* inputLayout);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult SetPrimitiveTopology(PrimitiveTopology primitiveTopology);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        

        
        
        
    */
    #endif
    static nnResult SetVertexBuffers(u32 startSlot, u32 numBuffers, VertexBufferResource** vertexBuffers, u32* offsets);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        

        
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        

        
        
        
        
        
        
        
        
    */
    #endif
    static nnResult CreateInputLayout(InputElementDescription* inputElementDescs, u32 numElements, u32* strides, Shader* vertexShader, InputLayout** inputLayout);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
    */
    #endif
    static nnResult ReleaseInputLayout(InputLayout *inputLayout);
};  // VertexInputStage


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class InputElementDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    u32 m_StreamSlot;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    const char* m_SemanticName;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    VertexInputStage::ShaderStreamFormatType m_Format;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    u32 m_Count;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 m_AlignedByteOffset;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    static const u32 Append = 0x00080000;
};

/*  */ // addtogroup VertexInputStage

}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_VERTEXINPUT_H_
