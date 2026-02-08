/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Texture.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_TEXTURE_H_
#define NN_GD_CTR_GD_TEXTURE_H_

#include <limits>
#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>
#include <nn/gd/CTR/gd_Utils.h>

#include <nn/gd/CTR/gd_Memory.h>
#include <nn/gd/CTR/gd_Resource.h>

#include <nn/dbg/dbg_DebugString.h>

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


/*********************************************************************************************************/
/********************************************** Internal data ********************************************/
class TextureStage;
class CombinerStage;
class ProceduralTextureStage;
class VertexInputStage;
namespace internal
{

class TextureStage;
class LightingStage;
class CombinerStage;
class VertexInputStage;
class ProceduralTextureSettings
{
private:
    u32 m_Proctex0;  // 0xa8
    u32 m_Proctex1;  // 0xa9
    u32 m_Proctex2;  // 0xaa
    u32 m_Proctex3;  // 0xab
    u32 m_Proctex4;  // 0xac
    u32 m_Proctex5;  // 0xad

    u32 m_PaddingEndStruct;
    u32 m_DirtyFieldMask;

    enum
    {
        PTMASK_PROCTEX0 = 1 << 0,
        PTMASK_PROCTEX1 = 1 << 1,
        PTMASK_PROCTEX2 = 1 << 2,
        PTMASK_PROCTEX3 = 1 << 3,
        PTMASK_PROCTEX4 = 1 << 4,
        PTMASK_PROCTEX5 = 1 << 5,

        PTMASK_REGISTRY_COUNT = 6
    };

friend class nn::gd::CTR::internal::TextureStage;
friend class nn::gd::CTR::ProceduralTextureStage;
friend class nn::gd::CTR::TextureStage;
};  // ProceduralTextureSettings

class TextureSettings
{
private:
    u32 m_TextureUnitControl;  // 0x80

    //used by sampler states
    u32 m_FormatTextureUnit0; //0x83
    u32 m_FormatTextureUnit1; //0x93
    u32 m_FormatTextureUnit2; //0x9b
    u32 m_MipLevelsTextureUnit0; //0x84
    u32 m_MipLevelsTextureUnit1; //0x94
    u32 m_MipLevelsTextureUnit2; //0x9c
    u32 m_TypeTextureUnit0; //0x83
    u32 m_ShadowTextureSetting; //0x8b

    u32 m_ProcTexHardwareEnabled;
    u32 m_DirtyFieldMask;

    enum
    {
        TXMASK_SEND_TEXTURE_UNIT_CONTROL = 1 << 0,
        TXMASK_UPDATE_TEXTURE_UNIT_CONTROL = 1 << 0 | 1 << 1,
        TXMASK_UPDATE_TEXTURE_SHADOW_SETTINGS = 1 << 2
    };

friend class nn::gd::CTR::ProceduralTextureStage;
friend class nn::gd::CTR::internal::TextureStage;
friend class nn::gd::CTR::CombinerStage;
friend class nn::gd::CTR::TextureStage;
friend class nn::gd::CTR::internal::CombinerStage;
friend class nn::gd::CTR::internal::LightingStage;
friend class nn::gd::CTR::VertexInputStage;
friend class nn::gd::CTR::internal::VertexInputStage;
};  // TextureSettings

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
extern ProceduralTextureSettings g_proceduralTexture;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
extern TextureSettings g_texture;

}  // internal

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Texture2DDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class TextureCubeDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class SamplerStateDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Texture2DProperties;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class TextureCubeProperties;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Texture2D;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class TextureCube;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class SamplerState;


/**************************************************************************************************************************/
/****************************************************** Texture Stage *****************************************************/
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
    
 */
#else
/* Please see man pages for details 
    
    
    
    
    
    
    
*/
#endif
class TextureStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum TextureUnitId
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        TEXTURE_UNIT_0 = 0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        TEXTURE_UNIT_1 = 1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        TEXTURE_UNIT_2 = 2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        TEXTURE_UNIT_3_PROCEDURAL = 3,

        TEXTURE_UNIT_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum SamplerWrapMode
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_WRAP_CLAMP_TO_EDGE       = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_WRAP_CLAMP_TO_BORDER     = 0x1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_WRAP_REPEAT              = 0x2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_WRAP_MIRRORED_REPEAT     = 0x3,

        SAMPLER_WRAP_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum SamplerMinFilter
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MIN_FILTER_NEAREST                 = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MIN_FILTER_LINEAR                  = 0x1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MIN_FILTER_NEAREST_MIPMAP_NEAREST  = 0x2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MIN_FILTER_LINEAR_MIPMAP_NEAREST   = 0x3,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MIN_FILTER_NEAREST_MIPMAP_LINEAR   = 0x4,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MIN_FILTER_LINEAR_MIPMAP_LINEAR    = 0x5,

        SAMPLER_MIN_FILTER_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum SamplerMagFilter
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MAG_FILTER_NEAREST   = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        SAMPLER_MAG_FILTER_LINEAR    = 0x1,

        SAMPLER_MAG_FILTER_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum TextureCoordinateSourceUnit2
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        UNIT2_TEXTURE_COORDINATE_FROM_UNIT_2    = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        UNIT2_TEXTURE_COORDINATE_FROM_UNIT_1    = 0x1,

        UNIT2_TEXTURE_COORDINATE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum TextureCoordinateSourceUnit3Procedural
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        UNIT3_PROCEDURAL_TEXTURE_COORDINATE_FROM_UNIT_0         = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        UNIT3_PROCEDURAL_TEXTURE_COORDINATE_FROM_UNIT_1         = 0x1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        UNIT3_PROCEDURAL_TEXTURE_COORDINATE_FROM_UNIT_2         = 0x2,

        UNIT3_PROCEDURAL_TEXTURE_COORDINATE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    
        
        
        
        
        
        
		
		
		
		
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
    
        
        
        
        
        
        

        
        
        
        
        
        
        
        
    */
    #endif
    static nnResult CreateTexture2D(const Texture2DResource* tex2DResource, Texture2DDescription* desc, Texture2D** texture2D);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult GetTexture2DProperties(const Texture2D* texture2D, Texture2DProperties* properties);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseTexture2D(Texture2D* texture2D);


    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    
        
         
         
        
        
        
		
		
		
		
		
		
		
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
    
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        
        
                                                  
        
        
    */
    #endif
    static nnResult CreateTextureCube(Texture2DResource** tex2DResources, TextureCubeDescription* desc, TextureCube** textureCube);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult GetTextureCubeProperties(const TextureCube* TextureCube, TextureCubeProperties* properties);
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseTextureCube(TextureCube* textureCube);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        
    */
    #endif
    static nnResult SetTexture(TextureUnitId textureUnitId, Texture2D& texture2D);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
      */
    #endif
    static nnResult SetTextureUnit0(TextureCube& textureCube);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
     */
    #endif
    static void SetTexture2DProjectionForUnit0(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
     */
    #endif
    static void SetTextureCoordinateSourceForUnit2(TextureCoordinateSourceUnit2 u);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
     */
    #endif
    static void SetTextureCoordinateSourceForUnit3Procedural(TextureCoordinateSourceUnit3Procedural u);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        
        
    */
    #endif
    static nnResult CreateSamplerState(const SamplerStateDescription* desc, SamplerState** sampler);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        
        
    */
    #endif
    static nnResult SetSamplerState(TextureUnitId textureUnitId, SamplerState* sampler);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
    */
    #endif
    static nnResult ReleaseSamplerState(SamplerState* sampler);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetPerspectiveShadow(gdBool v);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetShadowZBias(f32 zBias);

};  // TextureStage

/*************************************************************************************************************************/
/**************************************************** Procedural Texture *************************************************/
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
 */
#else
/* Please see man pages for details 
    
    
    
    
    
    
 */
#endif
class ProceduralTextureStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details */
    #endif
    enum UvMap
    {
        UV_MAP_U           = 0x0,
        UV_MAP_U2          = 0x1,
        UV_MAP_V           = 0x2,
        UV_MAP_V2          = 0x3,
        UV_MAP_ADD         = 0x4,
        UV_MAP_ADD2        = 0x5,
        UV_MAP_ADDSQRT2    = 0x6,
        UV_MAP_MIN         = 0x7,
        UV_MAP_MAX         = 0x8,
        UV_MAP_RMAX        = 0x9,

        UV_MAP_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    enum Clamp
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        CLAMP_TO_ZERO               = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        CLAMP_TO_EDGE               = 0x1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        CLAMP_SYMMETRICAL_REPEAT    = 0x2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        CLAMP_MIRRORED_REPEAT       = 0x3,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        CLAMP_PULSE                 = 0x4,

        CLAMP_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details */
    #endif
    enum Shift
    {
        SHIFT_NONE      = 0x0,
        SHIFT_ODD       = 0x1,
        SHIFT_EVEN      = 0x2,

        SHIFT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum MinFilter
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MIN_FILTER_NEAREST                 = 0x0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MIN_FILTER_LINEAR                  = 0x1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MIN_FILTER_NEAREST_MIPMAP_NEAREST  = 0x2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MIN_FILTER_LINEAR_MIPMAP_NEAREST   = 0x3,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MIN_FILTER_NEAREST_MIPMAP_LINEAR   = 0x4,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MIN_FILTER_LINEAR_MIPMAP_LINEAR    = 0x5,

        MIN_FILTER_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetClampUV(Clamp u, Clamp v);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetRgbMap(UvMap rgbMap);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetAlphaMap(UvMap alphaMap);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetAlphaSeparate(gdBool alphaSeparate);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetNoiseEnable(gdBool noiseEnable);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetShiftUV(Shift u, Shift v);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetTexBias(f32 texBias);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetMinFilter(MinFilter minFilter);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetTexWidth(u8 texWidth);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetTexOffset(u8 texOffset);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetNoiseUV(f32 noiseU[3], f32 noiseV[3]);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableRgbMapFloat(u32 index, f32 *Map, f32 *MapDelta, u32 lutSize);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        






        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableRgbMapNative(u32 index, u32 *Map, u32 lutSize);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableAlphaMapFloat(u32 index, f32 *Map, f32 *MapDelta, u32 lutSize);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        

        
        
        
        
    */
    #endif
     static nnResult UploadLookUpTableAlphaMapNative(u32 index, u32 *Map, u32 lutSize);

     #if NN_GD_DOCUMENT_TYPE == ENGLISH
     /* Please see man pages for details 
         
         

         
         
         
         
		 
		 
		 
		 
		 
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableNoiseMapFloat(u32 index, f32 *Map, f32 *MapDelta, u32 lutSize);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
		
		
		
		
		
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableNoiseMapNative(u32 index, u32 *Map, u32 lutSize);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        

        
        
        
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableColorMapFloat(u32 index, f32 **Map, f32 **MapDelta, u32 lutSize);  

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        





        
    */
    #else
    /* Please see man pages for details 
        
        
          

        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableColorMapNative(u32 index, u32 *Map, u32 *MapDelta, u32 lutSize);   

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
      
    */
    #else
    /* Please see man pages for details 
      
    */
    #endif
    class Helper
    {
    public:
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
			
			
			
			
            
            
        */
        #else
        /* Please see man pages for details 
            
            
            
            

            
            
            
        */
        #endif
        static nnResult ConvertLookUpTableDataFloatToNative(f32 *valueData, f32 *deltaData, u32 lutSize, u32* destination);

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
            
            
            
            
            
			
			
			
			
            
        */
        #else
        /* Please see man pages for details 

            
            

            
            
            
            
            

            
            
            
        */
        #endif
        static nnResult ConvertColorLookUpTableDataFloatToNative(f32 **refArray, f32 **deltaArray, u32 lutSize, u32* destRef, u32* destDelta);
    };

};  // ProceduralTextureStage

/*****************************************************************************************************************************/
/********************************************* Descriptor/Properties class definition ****************************************/
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class Texture2DDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    s32 m_MinMipLevelIndex;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    s32 m_MaxMipLevelIndex;
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class Texture2DProperties
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
    u32 m_CountMipLevels;

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

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        

        
        
    */
    #endif
    MipmapResourceInfo GetMipmapAddress(u32 mipmapLevel)
    {
        MipmapResourceInfo mipmapInfo;
        mipmapInfo.m_Width = m_Width;
        mipmapInfo.m_Height = m_Height;
        mipmapInfo.m_MemAddr = m_MemAddr;
        for (u32 i=0; i<mipmapLevel; ++i)
        {
            mipmapInfo.m_MemAddr += (mipmapInfo.m_Width * mipmapInfo.m_Height * m_PixelSize) >> 3;
            mipmapInfo.m_Width >>= 1;
            mipmapInfo.m_Height >>= 1;
        }
        return mipmapInfo;
    }
};  // Texture2DProperties


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class TextureCubeDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    s32 m_MinMipLevelIndex[6];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    s32 m_MaxMipLevelIndex[6];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    TextureCubeDescription(){
        for (int i=0; i<6; ++i){
            m_MinMipLevelIndex[i] = 0;
            m_MaxMipLevelIndex[i] = -1;
        }
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    TextureCubeDescription(int minMipLevelIndex, int maxMipLevelIndex){
        for (int i=0; i<6; ++i){
            m_MinMipLevelIndex[i] = minMipLevelIndex;
            m_MaxMipLevelIndex[i] = maxMipLevelIndex;
        }
    }
};  // TextureCubeDescription


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class TextureCubeProperties
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
    u32 m_CountMipLevels;

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
    u8* m_MemAddr[6];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
    */
    #endif
    MipmapResourceInfo GetMipmapAddress(u32 faceIndex, u32 mipmapLevel)
    {
        MipmapResourceInfo mipmapInfo;
        mipmapInfo.m_Width = m_Width;
        mipmapInfo.m_Height = m_Height;
        mipmapInfo.m_MemAddr = m_MemAddr[faceIndex];
        for (u32 i=0; i<mipmapLevel; ++i)
        {
            mipmapInfo.m_MemAddr += (mipmapInfo.m_Width * mipmapInfo.m_Height * m_PixelSize) >> 3;
            mipmapInfo.m_Width >>= 1;
            mipmapInfo.m_Height >>= 1;
        }
        return mipmapInfo;
    }
};  // TextureCubeProperties


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class SamplerStateDescription
{
public: 

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    TextureStage::SamplerMinFilter m_MinFilter;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    TextureStage::SamplerMagFilter m_MagFilter;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    TextureStage::SamplerWrapMode m_WrapS;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    TextureStage::SamplerWrapMode m_WrapT;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u8 m_BorderColor[4];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 m_LodBias;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 m_MinLod;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u32 m_MaxLod;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */    
    #else
    /* Please see man pages for details 
        
    */   
    #endif
    void SetMinFilter(TextureStage::SamplerMinFilter filter) { m_MinFilter = filter; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */ 
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    void SetMagFilter(TextureStage::SamplerMagFilter filter) { m_MagFilter = filter; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */ 
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    void SetWrapS(TextureStage::SamplerWrapMode wrap) { m_WrapS = wrap; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */ 
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    void SetWrapT(TextureStage::SamplerWrapMode wrap) { m_WrapT = wrap; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */ 
    #else
    /* Please see man pages for details 
        
        
        
        
    */ 
    #endif
    void SetBorderColor(u8 colorR, u8 colorG, u8 colorB, u8 colorA) 
    {
        m_BorderColor[0] = colorR;
        m_BorderColor[1] = colorG;
        m_BorderColor[2] = colorB;
        m_BorderColor[3] = colorA;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */    
    #else
    /* Please see man pages for details 
        
        
        
        
    */    
    #endif
    void SetBorderColor(f32 colorR, f32 colorG, f32 colorB, f32 colorA) 
    {
        m_BorderColor[0] = Utils::FloatToUnsignedByte(colorR);
        m_BorderColor[1] = Utils::FloatToUnsignedByte(colorG);
        m_BorderColor[2] = Utils::FloatToUnsignedByte(colorB); 
        m_BorderColor[3] = Utils::FloatToUnsignedByte(colorA); 
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */ 
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    void SetLodBias(f32 biasValue) { m_LodBias = Utils::Float32ToFix13Fraction8(biasValue); }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */ 
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    void SetMinLod(u32 lodValue)   { m_MinLod = lodValue; }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */ 
    #else
    /* Please see man pages for details 
        
    */
    #endif
    void SetMaxLod(u32 lodValue)   { m_MaxLod = lodValue; }

    SamplerStateDescription() { ToDefault(); }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */ 
    #else
    /* Please see man pages for details 
    */ 
    #endif
    void ToDefault() 
    {
        m_MinFilter = TextureStage::SAMPLER_MIN_FILTER_NEAREST;
        m_MagFilter = TextureStage::SAMPLER_MAG_FILTER_NEAREST;
        m_WrapS     = TextureStage::SAMPLER_WRAP_REPEAT;
        m_WrapT     = TextureStage::SAMPLER_WRAP_REPEAT;
        m_BorderColor[0] = m_BorderColor[1] = m_BorderColor[2] = m_BorderColor[3] = 0;
        m_LodBias = 0;
        m_MinLod  = 0;
        m_MaxLod = UINT_MAX;
    }
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    void SetShadow()
    {
        m_MinFilter = TextureStage::SAMPLER_MIN_FILTER_LINEAR;
        m_MagFilter = TextureStage::SAMPLER_MAG_FILTER_LINEAR;
        m_WrapS     = TextureStage::SAMPLER_WRAP_CLAMP_TO_BORDER;
        m_WrapT     = TextureStage::SAMPLER_WRAP_CLAMP_TO_BORDER;
        m_BorderColor[0] = m_BorderColor[1] = m_BorderColor[2] = m_BorderColor[3] = 0;
        m_LodBias = 0;
        m_MinLod  = 0;
        m_MaxLod = UINT_MAX;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    void SetShadowCube()
    {
        m_MinFilter = TextureStage::SAMPLER_MIN_FILTER_LINEAR;
        m_MagFilter = TextureStage::SAMPLER_MAG_FILTER_LINEAR;
        m_WrapS     = TextureStage::SAMPLER_WRAP_CLAMP_TO_EDGE;
        m_WrapT     = TextureStage::SAMPLER_WRAP_CLAMP_TO_EDGE;
        m_BorderColor[0] = m_BorderColor[1] = m_BorderColor[2] = m_BorderColor[3] = 0;
        m_LodBias = 0;
        m_MinLod  = 0;
        m_MaxLod = UINT_MAX;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    void SetGas()
    {
        m_MinFilter = TextureStage::SAMPLER_MIN_FILTER_NEAREST;
        m_MagFilter = TextureStage::SAMPLER_MAG_FILTER_NEAREST;
        m_WrapS     = TextureStage::SAMPLER_WRAP_CLAMP_TO_EDGE;
        m_WrapT     = TextureStage::SAMPLER_WRAP_CLAMP_TO_EDGE;
        m_BorderColor[0] = m_BorderColor[1] = m_BorderColor[2] = m_BorderColor[3] = 0;
        m_LodBias = 0;
        m_MinLod  = 0;
        m_MaxLod = UINT_MAX;
    }
}; // SamplerStateDescription


/**************************************************************************************************************************/
/******************************************* TextureStage inline functions *************************************************/
NN_FORCE_INLINE void TextureStage::SetPerspectiveShadow(gdBool v)
{
    // 0x8b[0:0]
    internal::g_texture.m_ShadowTextureSetting &= ~(0x1);
    if (!v) internal::g_texture.m_ShadowTextureSetting |= 0x1;
    internal::g_texture.m_DirtyFieldMask |= internal::TextureSettings::TXMASK_UPDATE_TEXTURE_SHADOW_SETTINGS;
}

NN_FORCE_INLINE void TextureStage::SetShadowZBias(f32 zBias)
{
    u32 bias = Utils::Float32ToUnsignedFix24(zBias);

    // Bias: 0x8b[23:1]
    internal::g_texture.m_ShadowTextureSetting &= ~(0x7fffff << 1);
    internal::g_texture.m_ShadowTextureSetting |= bias & 0xfffffe;

    // Scale: 0x8b[31:24]
    /*u32 scale = ((((*(u32*)&zScale) >> 23) & 0xff) - 127);
    internal::g_texture.m_ShadowTextureSetting &= ~(0xff000000);
    internal::g_texture.m_ShadowTextureSetting |= scale << 24;*/

    internal::g_texture.m_DirtyFieldMask |= internal::TextureSettings::TXMASK_UPDATE_TEXTURE_SHADOW_SETTINGS;
}

NN_FORCE_INLINE void TextureStage::SetTextureCoordinateSourceForUnit2(TextureCoordinateSourceUnit2 u)
{
    internal::g_texture.m_TextureUnitControl &= ~(0x1 << 13);
    internal::g_texture.m_TextureUnitControl |= (u & 0x1) << 13;
    internal::g_texture.m_DirtyFieldMask |= internal::TextureSettings::TXMASK_SEND_TEXTURE_UNIT_CONTROL;
}

/**************************************************************************************************************************/
/**************************************** ProceduralTextureStage inline functions **********************************************/

NN_FORCE_INLINE void TextureStage::SetTextureCoordinateSourceForUnit3Procedural(TextureCoordinateSourceUnit3Procedural u)
{
    internal::g_texture.m_TextureUnitControl &= ~(0x3 << 8);
    internal::g_texture.m_TextureUnitControl |= (u & 0x3) << 8;
    internal::g_texture.m_DirtyFieldMask |= internal::TextureSettings::TXMASK_SEND_TEXTURE_UNIT_CONTROL;
}


NN_FORCE_INLINE void ProceduralTextureStage::SetClampUV(Clamp u, Clamp v)
{
    internal::g_proceduralTexture.m_Proctex0 &= ~(0x3f);
    internal::g_proceduralTexture.m_Proctex0 |= (u & 0x7) | ((v & 0x7) << 3);
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX0;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetRgbMap(UvMap rgbMap)
{
    internal::g_proceduralTexture.m_Proctex0 &= ~(0xf << 6);
    internal::g_proceduralTexture.m_Proctex0 |= (rgbMap & 0xf) << 6;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX0;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetAlphaMap(UvMap alphaMap)
{
    internal::g_proceduralTexture.m_Proctex0 &= ~(0xf << 10);
    internal::g_proceduralTexture.m_Proctex0 |= (alphaMap & 0xf) << 10;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX0;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetAlphaSeparate(gdBool alphaSeparate)
{
    internal::g_proceduralTexture.m_Proctex0 &= ~(1 << 14);
    if (alphaSeparate) internal::g_proceduralTexture.m_Proctex0 |= 1 << 14;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX0;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetNoiseEnable(gdBool noiseEnable)
{
    internal::g_proceduralTexture.m_Proctex0 &= ~(1 << 15);
    if (noiseEnable) internal::g_proceduralTexture.m_Proctex0 |= 1 << 15;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX0;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetShiftUV(Shift u, Shift v)
{
    internal::g_proceduralTexture.m_Proctex0 &= ~(0xf << 16);
    internal::g_proceduralTexture.m_Proctex0 |= ((u & 0x3) << 16) | ((v & 0x3) << 18);
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX0;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetTexBias(f32 texBias)
{
    u32 v = Utils::Float32ToFloat16(texBias);

    internal::g_proceduralTexture.m_Proctex0 &= ~(0xff << 20);
    internal::g_proceduralTexture.m_Proctex0 |= (v & 0xff) << 20 ;
    internal::g_proceduralTexture.m_Proctex4 &= ~(0xff << 19);  
    internal::g_proceduralTexture.m_Proctex4 |= ((v>>8) & 0xff) << 19 ;

    internal::g_proceduralTexture.m_DirtyFieldMask |=   internal::ProceduralTextureSettings::PTMASK_PROCTEX0 |
                                                        internal::ProceduralTextureSettings::PTMASK_PROCTEX4;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetMinFilter(MinFilter minFilter)
{
    internal::g_proceduralTexture.m_Proctex4 &= ~0x7;
    internal::g_proceduralTexture.m_Proctex4 |= minFilter & 0x7;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX4;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetTexWidth(u8 texWidth)
{
    internal::g_proceduralTexture.m_Proctex4 &= ~(0xff << 11);
    internal::g_proceduralTexture.m_Proctex4 |= texWidth << 11;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX4;
}

NN_FORCE_INLINE void ProceduralTextureStage::SetTexOffset(u8 texOffset)
{
    internal::g_proceduralTexture.m_Proctex5 = texOffset | 0xe0c08000;
    internal::g_proceduralTexture.m_DirtyFieldMask |= internal::ProceduralTextureSettings::PTMASK_PROCTEX5;
}

}  // namespace CTR
}  // gd
}  // nn


#endif // NN_GD_CTR_GD_TEXTURE_H_
