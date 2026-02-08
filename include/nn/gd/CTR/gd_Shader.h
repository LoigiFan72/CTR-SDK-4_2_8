/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Shader.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_SHADER_H_
#define NN_GD_CTR_GD_SHADER_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>
#include <nn/gd/CTR/gd_Texture.h>

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

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Shader;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class ShaderPipeline;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class ShaderBinary;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class ShaderPipelineUnmanagedRegisters;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class ShaderStage;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
*/
#endif
class UniformLocation
{
private:
    u32 m_Data;

public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    enum UniformType
    {
        Undefined = 0,
        Boolean = 1,
        Integer3 = 2,
        Float = 8,
        Float2 = 9,
        Float3 = 10,
        Float4 = 11,
        FloatMatrix2 = 12,
        FloatMatrix3 = 13,
        FloatMatrix4 = 14,
        UniformType_RESERVED_MAX_U32 = 0xffffffff
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */    
    #endif
    UniformLocation()
    {
        m_Data = 0xFFFFFFFF;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */
    #endif
    UniformLocation(u8 shaderType, u16 managedLocation, u8 registerLocation, u8 size, UniformType type)
    {
        m_Data = registerLocation | (size << 8) | ((managedLocation & 0x1FF) << 16) | ((type & 0xF) << 26) | (shaderType << 31);
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    UniformLocation(u32 data)
    {
        this->m_Data = data;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    static UniformLocation invalidValue;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
    */
    #endif
    u32 GetRegister() { return m_Data & 0xFF; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
    */
    #endif
    u32 GetSize() { return (m_Data >> 8) & 0xFF; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 GetShaderType() { return (m_Data >> 31); }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 IsValid() { return m_Data != 0xFFFFFFFF; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 GetUniformType() { return (m_Data >> 26) & 0xF; }

friend class ShaderStage;
};  // UniformLocation

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
*/
#endif
class ShaderStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum ShaderType
    {
        SHADER_TYPE_VERTEX = 0,
        SHADER_TYPE_GEOMETRY = 1,

        SHADER_RESERVED_MAX_U32 = 0xffffffff
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        
        
        

    */
    #endif
    static nnResult CreateShaderBinary(const void* shaderBytecode, u32 bytecodeLength, ShaderBinary** shaderBinary);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        

    */
    #endif
    static nnResult CreateShader(ShaderBinary* shaderBinary, u32 shaderBinaryIndex, Shader** shader);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult CreateShaderPipeline(Shader* vertexShader, Shader* geometryShader, ShaderPipeline** shaderPipeline, ShaderPipelineUnmanagedRegisters* unmanagedRegister = NULL);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult SetShaderPipeline(ShaderPipeline* shaderPipeline);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
    */
    #endif
    static nnResult GetShader(ShaderPipeline* shaderPipeline, ShaderType shaderType, Shader** shader);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseShaderBinary(ShaderBinary* shaderBinary);

     #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseShader(Shader* shader);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif 
    static nnResult ReleaseShaderPipeline(ShaderPipeline* shaderPipeline);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        
    */
    #endif
    static nnResult SetShaderPipelineConstantFloat(ShaderPipeline* shaderPipeline, UniformLocation uniformLocation, f32* v);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
		
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult SetShaderPipelineConstantBoolean(ShaderPipeline* shaderPipeline, UniformLocation uniformLocation, u16 v, u32 count);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        
    */
    #endif
    static nnResult SetShaderPipelineConstantInteger(ShaderPipeline* shaderPipeline, UniformLocation uniformLocation, u8* v);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         

        
        
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        

        
        
        
        

        
    */
    #endif
    static nnResult SetFloatConstantBuffer(ShaderType shaderType, u32 firstRegisterIndex, u32 registerCount, f32* constantBufferSrc);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
    */  
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static UniformLocation GetShaderUniformLocation(ShaderPipeline* shaderPipeline, const char* name);

}; // ShaderStage


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class UnmanagedRegistersInterval
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    ShaderStage::ShaderType m_ShaderType;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_FirstUnmanagedRegister;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_RegisterCount;
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class ShaderPipelineUnmanagedRegisters
{
public:
     #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    UnmanagedRegistersInterval* m_ArrayUnmanagedRegistersInterval;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_CountUnmanagedRegistersInterval;
};

}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_SHADER_H_
