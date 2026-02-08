/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_OutputStage.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_OUTPUTSTAGE_H_
#define NN_GD_CTR_GD_OUTPUTSTAGE_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>

#include <nn/gd/CTR/gd_Memory.h>
#include <nn/gd/CTR/gd_Resource.h>

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
class BlendState;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class DepthStencilState;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class RenderTarget;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class DepthStencilTarget;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class DepthStencilStateDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class BlendStateDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class RenderTargetDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class DepthStencilTargetDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class TargetProperties;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
    
    
*/
#endif
class OutputStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum DepthBufferType
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        DEPTHBUFFER_LINEAR = 0, 

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif        
        DEPTHBUFFER_RECIPROCAL_FUNCTION = 1,

        DEPTHBUFFER_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum FragmentOperationMode
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        FRAGMENT_OPERATION_MODE_FRAGMENT_COLOR = 0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        FRAGMENT_OPERATION_MODE_GAS_ACCUMULATION = 1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        FRAGMENT_OPERATION_MODE_SHADOW_MAP = 3,  

        FRAGMENT_OPERATION_MAPRESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum BlendType
    {
        BLEND_TYPE_LOGICOP = 0,
        BLEND_TYPE_BLENDING = 1,

        BLEND_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum BlendFunction
    {
        BLEND_FUNCTION_ZERO                      = 0,
        BLEND_FUNCTION_ONE                       = 1,
        BLEND_FUNCTION_SRC_COLOR                 = 2,
        BLEND_FUNCTION_ONE_MINUS_SRC_COLOR       = 3,
        BLEND_FUNCTION_DST_COLOR                 = 4,
        BLEND_FUNCTION_ONE_MINUS_DST_COLOR       = 5,
        BLEND_FUNCTION_SRC_ALPHA                 = 6,
        BLEND_FUNCTION_ONE_MINUS_SRC_ALPHA       = 7,
        BLEND_FUNCTION_DST_ALPHA                 = 8,
        BLEND_FUNCTION_ONE_MINUS_DST_ALPHA       = 9,
        BLEND_FUNCTION_CONSTANT_COLOR            = 10,
        BLEND_FUNCTION_ONE_MINUS_CONSTANT_COLOR  = 11,
        BLEND_FUNCTION_CONSTANT_ALPHA            = 12,
        BLEND_FUNCTION_ONE_MINUS_CONSTANT_ALPHA  = 13,
        BLEND_FUNCTION_SRC_ALPHA_SATURATE        = 14,

        BLEND_FUNCTION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum BlendEquation
    {
        BLEND_EQUATION_ADD               = 0,
        BLEND_EQUATION_SUBTRACT          = 1,
        BLEND_EQUATION_REV_SUBTRACT      = 2,
        BLEND_EQUATION_MIN               = 3,
        BLEND_EQUATION_MAX               = 4,

        BLEND_EQUATION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum LogicOperator
    {
        LOGIC_OPERATOR_CLEAR             = 0,
        LOGIC_OPERATOR_AND               = 1,
        LOGIC_OPERATOR_AND_REVERSE       = 2,
        LOGIC_OPERATOR_COPY              = 3,
        LOGIC_OPERATOR_SET               = 4,
        LOGIC_OPERATOR_COPY_INVERTED     = 5,
        LOGIC_OPERATOR_NOOP              = 6,
        LOGIC_OPERATOR_INVERT            = 7,
        LOGIC_OPERATOR_NAND              = 8,
        LOGIC_OPERATOR_OR                = 9,
        LOGIC_OPERATOR_NOR               = 10,
        LOGIC_OPERATOR_XOR               = 11,
        LOGIC_OPERATOR_EQUIV             = 12,
        LOGIC_OPERATOR_AND_INVERTED      = 13,
        LOGIC_OPERATOR_OR_REVERSE        = 14,
        LOGIC_OPERATOR_OR_INVERTED       = 15,

        LOGIC_OPERATOR_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum ColorWriteMask
    {
        COLOR_WRITE_MASK_ENABLE_RED      = 0x1,
        COLOR_WRITE_MASK_ENABLE_GREEN    = 0x2,
        COLOR_WRITE_MASK_ENABLE_BLUE     = 0x4,
        COLOR_WRITE_MASK_ENABLE_ALPHA    = 0x8,
        COLOR_WRITE_MASK_ENABLE_ALL      = ( COLOR_WRITE_MASK_ENABLE_RED | COLOR_WRITE_MASK_ENABLE_GREEN |
                                                COLOR_WRITE_MASK_ENABLE_BLUE | COLOR_WRITE_MASK_ENABLE_ALPHA ),
        COLOR_WRITE_MASK_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum DepthFunction
    {
        DEPTH_FUNCTION_NEVER     = 0,
        DEPTH_FUNCTION_ALWAYS    = 1,
        DEPTH_FUNCTION_EQUAL     = 2,
        DEPTH_FUNCTION_NOTEQUAL  = 3,
        DEPTH_FUNCTION_LESS      = 4,
        DEPTH_FUNCTION_LEQUAL    = 5,
        DEPTH_FUNCTION_GREATER   = 6,
        DEPTH_FUNCTION_GEQUAL    = 7,

        DEPTH_FUNCTION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum DepthWriteMask
    {
        DEPTH_WRITE_MASK_ZERO    = 0,
        DEPTH_WRITE_MASK_ALL     = 1,

        DEPTH_WRITE_MASK_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum StencilFunction
    {
        STENCIL_FUNCTION_NEVER       = 0,
        STENCIL_FUNCTION_ALWAYS      = 1,
        STENCIL_FUNCTION_EQUAL       = 2,
        STENCIL_FUNCTION_NOTEQUAL    = 3,
        STENCIL_FUNCTION_LESS        = 4,
        STENCIL_FUNCTION_LEQUAL      = 5,
        STENCIL_FUNCTION_GREATER     = 6,
        STENCIL_FUNCTION_GEQUAL      = 7,

        STENCIL_FUNCTION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum StencilOperation
    {
        STENCIL_OPERATION_KEEP       = 0,
        STENCIL_OPERATION_ZERO       = 1,
        STENCIL_OPERATION_REPLACE    = 2,
        STENCIL_OPERATION_INCR       = 3,
        STENCIL_OPERATION_DECR       = 4,
        STENCIL_OPERATION_INVERT     = 5,
        STENCIL_OPERATION_INCR_WRAP  = 6,
        STENCIL_OPERATION_DECR_WRAP  = 7,

        STENCIL_OPERATION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum AlphaFunction
    {
        ALPHA_FUNCTION_NEVER     = 0,
        ALPHA_FUNCTION_ALWAYS    = 1,
        ALPHA_FUNCTION_EQUAL     = 2,
        ALPHA_FUNCTION_NOTEQUAL  = 3,
        ALPHA_FUNCTION_LESS      = 4,
        ALPHA_FUNCTION_LEQUAL    = 5,
        ALPHA_FUNCTION_GREATER   = 6,
        ALPHA_FUNCTION_GEQUAL    = 7,

        ALPHA_FUNCTION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
          
          
          
          
          
          
        
        
        
        
        

        
        
        
        
        
        
                                                    
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
         
         
         
         
         
         
         
         
      
      
      
      

      
      
      
      
      
                                                
      
      
      
      
    */
    #endif
    static nnResult CreateRenderTarget(const Texture2DResource *texture2DResource, const RenderTargetDescription *desc, RenderTarget **renderTarget);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult GetRenderTargetProperties(const RenderTarget* renderTarget, TargetProperties* properties);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseRenderTarget(RenderTarget *renderTarget);


    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
           
           
           

        
        
        
        

        
        
        
        
        
        
                                                    
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
         
           
           
           
        
        
        
        
        

        
        
        
        
        
                                                  
        
        
        
        
    */
    #endif
    static nnResult CreateDepthStencilTarget(const Texture2DResource *texture2DResource, const DepthStencilTargetDescription *desc, DepthStencilTarget **depthStencil);
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult GetDepthStencilTargetProperties(const DepthStencilTarget* depthStencil, TargetProperties* properties);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseDepthStencilTarget(DepthStencilTarget *depthStencil);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult SetRenderTarget(const RenderTarget *renderTarget);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult SetDepthStencilTarget(const DepthStencilTarget *depthStencil);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetFragOpMode(FragmentOperationMode fragOpMode);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        
        
    */
    #endif
    static nnResult CreateBlendState(const BlendStateDescription *desc, BlendState **blendState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
    */
    #endif
    static nnResult ReleaseBlendState(BlendState *blendState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult SetBlendState(const BlendState *blendState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    static void SetBlendColor(u8 R, u8 G, u8 B, u8 A);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
    */
    #endif
    static void SetAlphaTest(gdBool enable, AlphaFunction func, u8 alphaRef);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        
        
    */
    #endif
    static nnResult CreateDepthStencilState(const DepthStencilStateDescription *desc, DepthStencilState **DepthStencilState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
    */
    #endif
    static nnResult ReleaseDepthStencilState(DepthStencilState *DepthStencilState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult SetDepthStencilState(const DepthStencilState* state, u8 stencilRef);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */  
    #else
    /* Please see man pages for details 
        
    */  
    #endif
    static void SetColorWriteMask(u32 mask);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetPenumbraScaleBias(f32 Scale, f32 Bias);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    static void SetDepthRangeMode(DepthBufferType type, f32 depthRangeNear, f32 depthRangeFar, s32 offset);

};  // class OutputStage


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class RenderTargetDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_MipLevelIndex;
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class DepthStencilTargetDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_MipLevelIndex;
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class TargetProperties
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Width;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Height;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_PixelSize;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Resource::NativeFormat m_Format;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Memory::MemoryLayout m_MemLayout;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Memory::MemoryLocation m_MemLocation;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u8* m_MemAddr;
};  // TargetProperties


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class BlendStateDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendType m_BlendType;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::LogicOperator m_LogicOp;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendFunction m_SrcRgb;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendFunction m_DstRgb;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendFunction m_SrcAlpha;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendFunction m_DstAlpha;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendEquation m_EqRgb;
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::BlendEquation m_EqAlpha;

public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
   /* Please see man pages for details 
       
       
       
       
       
    */
    #endif
    void SetBlendFunc(OutputStage::BlendFunction src, OutputStage::BlendFunction dst, OutputStage::BlendEquation eq)
    {
        m_SrcRgb = m_SrcAlpha = src;
        m_DstRgb = m_DstAlpha = dst;
        m_EqRgb = m_EqAlpha = eq;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
    */
    #endif
    void SetBlendFunc(OutputStage::BlendFunction srcRgb, OutputStage::BlendFunction dstRgb, OutputStage::BlendFunction srcAlpha,
        OutputStage::BlendFunction dstAlpha, OutputStage::BlendEquation eqRgb, OutputStage::BlendEquation eqAlpha)
    {
        m_SrcRgb = srcRgb;
        m_DstRgb = dstRgb;
        m_SrcAlpha = srcAlpha;
        m_DstAlpha = dstAlpha;
        m_EqRgb = eqRgb;
        m_EqAlpha = eqAlpha;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetBlendMode_DefaultBlending()
    {
        m_BlendType = OutputStage::BLEND_TYPE_BLENDING;
        m_LogicOp   = OutputStage::LOGIC_OPERATOR_COPY;
        SetBlendFunc(OutputStage::BLEND_FUNCTION_SRC_ALPHA, OutputStage::BLEND_FUNCTION_ONE_MINUS_SRC_ALPHA, OutputStage::BLEND_EQUATION_ADD);
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetBlendMode_NoBlend()
    {
        m_BlendType = OutputStage::BLEND_TYPE_BLENDING;
        m_LogicOp   = OutputStage::LOGIC_OPERATOR_COPY;
        SetBlendFunc(OutputStage::BLEND_FUNCTION_ONE, OutputStage::BLEND_FUNCTION_ZERO, OutputStage::BLEND_EQUATION_ADD);
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
   /* Please see man pages for details 
       
       
       
       
       
       
       
    */
    #endif
    void SetLogicOperatorMode_Default()
    {
        m_BlendType = OutputStage::BLEND_TYPE_LOGICOP;
        m_LogicOp   = OutputStage::LOGIC_OPERATOR_COPY;
        SetBlendFunc(OutputStage::BLEND_FUNCTION_ONE, OutputStage::BLEND_FUNCTION_ZERO, OutputStage::BLEND_EQUATION_ADD);
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
    */
    #else
    /* Please see man pages for details 
        
        
          
          
          
          
          

        
    */   
    #endif
    void SetLogicOperatorMode(OutputStage::LogicOperator logicOp)
    {
        m_BlendType = OutputStage::BLEND_TYPE_LOGICOP;
        m_LogicOp   = logicOp;
        SetBlendFunc(OutputStage::BLEND_FUNCTION_ONE, OutputStage::BLEND_FUNCTION_ZERO, OutputStage::BLEND_EQUATION_ADD);
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    void ToDefault()
    {
        SetBlendMode_NoBlend();
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */   
    #endif
    BlendStateDescription()
    {
        ToDefault();
    }

};  // BlendStateDescription


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif

/*
Default value
m_DepthEnable       GD_FALSE (0x0)
m_DepthMask         DEPTH_WRITE_MASK_ALL (0x1)
m_DepthFunc         DEPTH_FUNCTION_LESS (0x4)
m_StencilEnable     GD_FALSE (0x0)
m_StencilWriteMask  (0xff)
m_StencilReadMask   (0xff)
m_StencilFunc       STENCIL_FUNCTION_NEVER (0x0)
m_StencilFail       STENCIL_OPERATION_KEEP (0x0)
m_StencilZFail      STENCIL_OPERATION_KEEP (0x0)
m_StencilZPass      STENCIL_OPERATION_KEEP (0x0)
*/
class DepthStencilStateDescription
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    gdBool                             m_DepthEnable;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    gdBool                             m_StencilEnable;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u8                                 m_StencilWriteMask;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u8                                 m_StencilReadMask;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::DepthWriteMask        m_DepthMask;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::DepthFunction         m_DepthFunc;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::StencilFunction       m_StencilFunc;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::StencilOperation  m_StencilFail;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::StencilOperation  m_StencilZFail;
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    OutputStage::StencilOperation  m_StencilZPass;

public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */   
    #endif
    DepthStencilStateDescription()
    {
        ToDefault();
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    void ToDefault()
    {
        m_StencilWriteMask = m_StencilReadMask = 0xff;
        m_DepthMask = OutputStage::DEPTH_WRITE_MASK_ALL;
        m_DepthFunc = OutputStage::DEPTH_FUNCTION_LESS;

        m_DepthEnable = m_StencilEnable = GD_FALSE;
        m_StencilFunc = OutputStage::STENCIL_FUNCTION_NEVER;
        m_StencilFail = m_StencilZFail = m_StencilZPass = OutputStage::STENCIL_OPERATION_KEEP;
    }
};  // DepthStencilStateDescription


}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_OUTPUTSTAGE_H_
