/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Lighting.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

#ifndef NN_GD_CTR_GD_LIGHTING_H_
#define NN_GD_CTR_GD_LIGHTING_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>
#include <nn/gd/CTR/gd_Utils.h>

#include <nn/gd/CTR/gd_Texture.h>

#include <nn/gx/CTR/gx_MacroFragment.h>

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

namespace internal{ class LightingStage; class System; }

/*********************************************************************************************************/
/********************************************** Internal data ********************************************/
class Light;
class System;
class LightingStage;
class CombinerStage;
namespace internal
{

class System;
class LightingStage;
class CombinerStage;
class LightingStageSettings
{
private:
    u32 m_GlobalAmbient;            //1c0
    u32 m_MiscReg1c3;               //1c3
    u32 m_MiscReg1c4;               //1c4
    u32 m_RegLutAbsSettings;        //1d0
    u32 m_RegLutInputValues;        //1d1
    u32 m_RegLutOutputScale;        //1d2

    u32 m_FragmentLightingEnabled;
    u32 m_FragmentLightingCountEnabledLights;
    u32 m_DirtyFieldMask;
    u32 m_BumpMode;
    u32 m_BumpSelectorTexture;
    u32 m_ShadowSelectorTexture;
    u32 m_LayerConfiguration;
    u32 m_TextureUnitControl_LightEnv;

    u32 m_LayerConfiguration_User;

    enum
    {
        MASK_FRAGMENT_LIGHTING_UPDATED = 1 << 0,
        MASK_LIGHT_ENABLED_UPDATED = 1 << 1,
        MASK_REG_01C3_UPDATED = 1 << 2,
        MASK_REG_01C4_UPDATED = 1 << 3,
        MASK_REG_LUT_ABS_SETTINGS_UPDATED = 1 << 4,
        MASK_REG_LUT_INPUT_VALUES_UPDATED = 1 << 5,
        MASK_REG_LUT_OUTPUT_SCALING_UPDATED = 1 << 6,
        MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL = 1 << 7
    };

friend class nn::gd::CTR::Light;
friend class nn::gd::CTR::LightingStage;
friend class nn::gd::CTR::internal::System;
friend class nn::gd::CTR::System;
friend class nn::gd::CTR::internal::LightingStage;
friend class nn::gd::CTR::CombinerStage;
friend class nn::gd::CTR::internal::CombinerStage;
friend class nn::gd::CTR::internal::TextureStage;
};  // LightingStageSettings

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
extern LightingStageSettings g_lightingStageSettings;
}  // internal

/*********************************************************************************************************/
/************************************************* Light *************************************************/

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
    
    
*/
#endif
class Light
{
private:
    u32 m_MiscellanousFields;
    u32 m_LightId;
    u32 m_LightEnabled;
    u32 m_LightEnabled_User;

public:
    Light();
    ~Light(){};

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum SourceType
    {
        SOURCE_TYPE_POINT = 0,

        SOURCE_TYPE_DIRECTIONAL = 1,

        SOURCE_TYPE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum LightLookUpTableUploadId
    {
        LOOKUP_TABLE_UPLOAD_SP = 8,
        LOOKUP_TABLE_UPLOAD_DA = 16,

        LOOKUP_TABLE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    void EnableLight(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetColorAmbient(u8 R, u8 G, u8 B);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetColorDiffuse(u8 R, u8 G, u8 B);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetColorSpecular0(u8 R, u8 G, u8 B);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */  
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetColorSpecular1(u8 R, u8 G, u8 B);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
         
         
        
        
        
        
        
        
        
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
         
         
        
        
        
        
        
        
        
        
        
        
        
        
        
    */
    #endif
    void SetPosition(f32 X, f32 Y, f32 Z);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
         
         
        
        
        
        
        
        
        
        
        

        
        
        
    */
    #else
   /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    */
    #endif
    void SetDirection(f32 X, f32 Y, f32 Z);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        
    */
    #endif
    void SetSpotDirection(f32 X, f32 Y, f32 Z);

     #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #endif
    void SetLightType(SourceType sourceType);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
    */
    #endif
    void SetDistanceAttenuationScaleBias(f32 attenuationScale, f32 attenuationBias);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #endif
    void EnableTwoSideDiffuse(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #endif
    void EnableGeomFactor0(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #endif
    void EnableGeomFactor1(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    void EnableSpotLight(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    void EnableDistanceAttenuation(gdBool value);
  
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
         
    */
    #endif
    void EnableShadowed(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
		
		
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
        
        

        
        
        
        
        

    */
    #endif
    nnResult UploadLookUpTableFloat(LightLookUpTableUploadId lightLutID, u32 lutStartIndex, const f32* valueData, const f32* deltaData, u32 dataCount);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        







        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        

        
        
        
        
        
    */
    #endif
    nnResult UploadLookUpTableNative(LightLookUpTableUploadId lightLutID, u32 lutStartIndex, const u32* data, u32 dataCount);

friend class nn::gd::CTR::internal::LightingStage;
friend class nn::gd::CTR::internal::System;
};  // Light

/*********************************************************************************************************/
/*********************************************** LightingStage ************************************************/

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
    
    
*/
#endif
class LightingStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    static const u32 COUNT_LIGHTS = 8;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    static Light light[COUNT_LIGHTS];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum LayerConfiguration
    {
        LAYER_CONFIGURATION_0 = 0,
        LAYER_CONFIGURATION_1 = 1,
        LAYER_CONFIGURATION_2 = 2,
        LAYER_CONFIGURATION_3 = 3,
        LAYER_CONFIGURATION_4 = 4,
        LAYER_CONFIGURATION_5 = 5,
        LAYER_CONFIGURATION_6 = 6,
        LAYER_CONFIGURATION_7 = 8,

        LAYER_CONFIGURATION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum FresnelSelectorType
    {
        FRESNEL_SELECTOR_TYPE_NO_FRESNEL                        = 0,
        FRESNEL_SELECTOR_TYPE_PRIMARY_ALPHA_FRESNEL             = 1,
        FRESNEL_SELECTOR_TYPE_SECONDARY_ALPHA_FRESNEL           = 2,
        FRESNEL_SELECTOR_TYPE_PRIMARY_SECONDARY_ALPHA_FRESNEL   = 3,

        FRESNEL_SELECTOR_TYPE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum BumpMode
    {
        BUMPMODE_NOT_USED   = 0,
        BUMPMODE_AS_BUMP    = 1,
        BUMPMODE_AS_TANG    = 2,

        BUMPMODE_RESERVED_MAX_U32 = 0xffffffffu
    } ;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum LookUpTableUploadId
    {
        LOOKUP_TABLE_UPLOAD_ID_D0 = 0,
        LOOKUP_TABLE_UPLOAD_ID_D1 = 1,
        LOOKUP_TABLE_UPLOAD_ID_FR = 3,
        LOOKUP_TABLE_UPLOAD_ID_RB = 4,
        LOOKUP_TABLE_UPLOAD_ID_RG = 5,
        LOOKUP_TABLE_UPLOAD_ID_RR = 6,

        LOOKUP_TABLE_UPLOAD_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum LookUpTableId
    {
        LOOKUP_TABLE_ID_D0 = 0,
        LOOKUP_TABLE_ID_D1 = 1,
        LOOKUP_TABLE_ID_SP = 2,
        LOOKUP_TABLE_ID_FR = 3,
        LOOKUP_TABLE_ID_RB = 4,
        LOOKUP_TABLE_ID_RG = 5,
        LOOKUP_TABLE_ID_RR = 6,

        LOOKUP_TABLE_ID_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum LookUpTableInputValue
    {
        INPUT_VALUE_NH = 0,
        INPUT_VALUE_VH = 1,
        INPUT_VALUE_NV = 2,
        INPUT_VALUE_LN = 3,
        INPUT_VALUE_SP = 4,
        INPUT_VALUE_CP = 5,

        INPUT_VALUE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    enum LookUpTableOutputScaleValue
    #endif
    {
        OUTPUT_SCALE_VALUE_1 = 0,
        OUTPUT_SCALE_VALUE_2 = 1,
        OUTPUT_SCALE_VALUE_4 = 2,
        OUTPUT_SCALE_VALUE_8 = 3,
        OUTPUT_SCALE_VALUE_0_25 = 6,
        OUTPUT_SCALE_VALUE_0_5 = 7,

        OUTPUT_SCALE_VALUE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    static void SetGlobalColorAmbient(u8 R, u8 G, u8 B);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    static void SetShadowPrimary(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    static void SetShadowSecondary(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    static void SetInvertShadow(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */ 
    #endif
    static void SetShadowAlpha(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void EnableLookUpTableD0(gdBool value);
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void EnableLookUpTableD1(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void EnableLookUpTableReflection(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetLayerConfiguration(LayerConfiguration layerConfiguration);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetFresnelSelector(FresnelSelectorType fresnelSelectorType);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetShadowSelectorTexture(TextureStage::TextureUnitId textureUnit);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetBumpSelectorTexture(TextureStage::TextureUnitId textureUnit);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetBumpMode(BumpMode bumpMode, gdBool bumpRenorm);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetClampHightlight(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetLookUpTableAbsInput(LookUpTableId lutId, gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetLookUpTableInputValue(LookUpTableId lutId, LookUpTableInputValue lutInputValue);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetLookUpTableOutputScaling(LookUpTableId lutId, LookUpTableOutputScaleValue outputScalingValue);

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
        static nnResult ConvertLookUpTableDataFloatToNative(const f32* valueData, const f32* deltaData, u32 dataCount, u32* __restrict destination);
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
		
		
		
		
		
		
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableFloat(LightingStage::LookUpTableUploadId lutID, u32 lutStartIndex, const f32* valueData, const f32* deltaData, u32 dataCount);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
		
		
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult UploadLookUpTableNative(LightingStage::LookUpTableUploadId lutID, u32 lutStartIndex, const u32* data, u32 dataCount);

};  // LightingStage


/**************************************************************************************************************/
/********************************** LightingStage inline functions implementation *****************************/

NN_FORCE_INLINE void LightingStage::SetShadowPrimary(gdBool value)
{
    //shadowPrimary: 0x1c3, bit [16:16]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1 << 16);
    if(value) internal::g_lightingStageSettings.m_MiscReg1c3 |= 1 << 16;
    
    // common: 0x1c3, bit [0:0]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1);
    if (internal::g_lightingStageSettings.m_MiscReg1c3 & (1<<16 | 1<<17 | 1<<19)) internal::g_lightingStageSettings.m_MiscReg1c3 |= 1;

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED
        | internal::LightingStageSettings::MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL;
}

NN_FORCE_INLINE void LightingStage::SetShadowSecondary(gdBool value)
{
    //shadowSecondary: 0x1c3, bit [17:17]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1 << 17);
    if(value) internal::g_lightingStageSettings.m_MiscReg1c3 |= (1 << 17);

    // common: 0x1c3, bit [0:0]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1);
    if (internal::g_lightingStageSettings.m_MiscReg1c3 & (1<<16 | 1<<17 | 1<<19)) internal::g_lightingStageSettings.m_MiscReg1c3 |= 1;

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED
        | internal::LightingStageSettings::MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL;
}

NN_FORCE_INLINE void LightingStage::SetShadowSelectorTexture(TextureStage::TextureUnitId textureUnit)
{
    //shadowSelector 0x1c3, bits [25:24]
    internal::g_lightingStageSettings.m_ShadowSelectorTexture = textureUnit & 0x3;
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(0x3 << 24);
    internal::g_lightingStageSettings.m_MiscReg1c3 |= (internal::g_lightingStageSettings.m_ShadowSelectorTexture << 24);

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED
        | internal::LightingStageSettings::MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL;
}

NN_FORCE_INLINE void LightingStage::SetInvertShadow(gdBool value)
{
    //invertShadow: 0x1c3, bit [18:18]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1 << 18);
    if(value) internal::g_lightingStageSettings.m_MiscReg1c3 |= (1 << 18);
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED;
}

NN_FORCE_INLINE void LightingStage::SetShadowAlpha(gdBool value)
{
    //shadowAlpha: 0x1c3, bit [19:19]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1 << 19);
    if(value) internal::g_lightingStageSettings.m_MiscReg1c3 |= (1 << 19);

    // common: 0x1c3, bit [0:0]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1);
    if (internal::g_lightingStageSettings.m_MiscReg1c3 & (1<<16 | 1<<17 | 1<<19)) internal::g_lightingStageSettings.m_MiscReg1c3 |= 1;

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED
        | internal::LightingStageSettings::MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL;
}

NN_FORCE_INLINE void LightingStage::EnableLookUpTableD0(gdBool value)
{
    //lutEnabledD0: 0x1c4, bit [16:16]

    //g_gdFLLightingGlobalSettings.lutEnabledD0 = !value;
    //m_MiscReg1c4 = (m_MiscReg1c4 & ~(1 << 16)) | ((~value) << 16);

    //m_MiscReg1c4= (m_MiscReg1c4 & ~(1 << 16)) | ((~value) << 16);

    //m_MiscReg1c4= (m_MiscReg1c4 & ~(1 << 16)) | ~(value << 16);

    internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(1 << 16);
    if(!value) internal::g_lightingStageSettings.m_MiscReg1c4 |= (1 << 16);
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}

NN_FORCE_INLINE void LightingStage::EnableLookUpTableD1(gdBool value)
{
    //lutEnabledD1: 0x1c4, bit [17:17]
    internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(1 << 17);
    if(!value) internal::g_lightingStageSettings.m_MiscReg1c4 |= (1 << 17);
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}

NN_FORCE_INLINE void LightingStage::EnableLookUpTableReflection(gdBool value)
{
    //lutEnabledRefl: 0x1c4, bits [22:20]
    internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(7 << 20);
    if(!value) internal::g_lightingStageSettings.m_MiscReg1c4 |= (7 << 20);
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}

NN_FORCE_INLINE void LightingStage::SetLayerConfiguration(LayerConfiguration layerConfiguration)
{
    //layerConfiguration: 0x1c3, bits [7:4]
    internal::g_lightingStageSettings.m_LayerConfiguration = layerConfiguration & 0xf;
    internal::g_lightingStageSettings.m_LayerConfiguration_User = internal::g_lightingStageSettings.m_LayerConfiguration;
    if (internal::g_lightingStageSettings.m_FragmentLightingEnabled)
    {
        internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(0xf << 4);
        internal::g_lightingStageSettings.m_MiscReg1c3 |= (internal::g_lightingStageSettings.m_LayerConfiguration << 4);
        internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED;
    }
}

NN_FORCE_INLINE void LightingStage::SetFresnelSelector(FresnelSelectorType fresnelSelectorType)
{
    u32 fresnelValue = fresnelSelectorType & 0x3;

    //fresnelSelectorType: 0x1c3, bits [3:2]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(0x3 << 2);
    internal::g_lightingStageSettings.m_MiscReg1c3 |= (fresnelValue << 2);

    //fresnelSelectorType: 0x1c4, bits [19:19]
    internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(1 << 19);
    if(fresnelValue == FRESNEL_SELECTOR_TYPE_NO_FRESNEL) internal::g_lightingStageSettings.m_MiscReg1c4 |= (1 << 19);

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED | internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}

NN_FORCE_INLINE void LightingStage::SetBumpSelectorTexture(TextureStage::TextureUnitId textureUnit)
{
    //bumpSelector 0x1c3, bits [23:22]
    internal::g_lightingStageSettings.m_BumpSelectorTexture = textureUnit & 0x3;
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(0x3 << 22);
    internal::g_lightingStageSettings.m_MiscReg1c3 |= (internal::g_lightingStageSettings.m_BumpSelectorTexture << 22);

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED
        | internal::LightingStageSettings::MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL;
}

NN_FORCE_INLINE void LightingStage::SetBumpMode(BumpMode bumpMode, gdBool bumpRenorm)
{
    //bumpMode 0x1c3, bits [29:28]
    //bumpRenorm 0x1c3, bit [30:30]
    internal::g_lightingStageSettings.m_BumpMode = bumpMode & 0x3;
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(7 << 28);
    if (bumpRenorm || internal::g_lightingStageSettings.m_BumpMode == BUMPMODE_NOT_USED) internal::g_lightingStageSettings.m_MiscReg1c3 |= internal::g_lightingStageSettings.m_BumpMode << 28;
    else internal::g_lightingStageSettings.m_MiscReg1c3 |= ((1 << 30) | (internal::g_lightingStageSettings.m_BumpMode << 28));
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED
        | internal::LightingStageSettings::MASK_UPDATE_LIGHTENV_TEXTURE_UNIT_CONTROL;
}

NN_FORCE_INLINE void LightingStage::SetClampHightlight(gdBool value)
{
    //clampHighlights 0x1c3, bit [27:27]
    internal::g_lightingStageSettings.m_MiscReg1c3 &= ~(1 << 27);
    if(value) internal::g_lightingStageSettings.m_MiscReg1c3 |= 1 << 27;
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C3_UPDATED;
}

NN_FORCE_INLINE void LightingStage::SetLookUpTableAbsInput(LookUpTableId lutId, gdBool value)
{
    u32 bit = 1 << (lutId*4 + 1);
    internal::g_lightingStageSettings.m_RegLutAbsSettings &= ~bit;
    if(!value) internal::g_lightingStageSettings.m_RegLutAbsSettings |= bit;

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_LUT_ABS_SETTINGS_UPDATED;
}

NN_FORCE_INLINE void LightingStage::SetLookUpTableInputValue(LookUpTableId lutId, LookUpTableInputValue lutInputValue)
{
    u32 lutInputV = lutInputValue & 0x7;
    internal::g_lightingStageSettings.m_RegLutInputValues &= ~(0x7 << (lutId<<2)); 
    internal::g_lightingStageSettings.m_RegLutInputValues |= lutInputV << (lutId<<2);

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_LUT_INPUT_VALUES_UPDATED;
}

NN_FORCE_INLINE void LightingStage::SetLookUpTableOutputScaling(LookUpTableId lutId, LookUpTableOutputScaleValue outputScalingValue)
{
    u32 outputScalingV = outputScalingValue & 0x7;
    internal::g_lightingStageSettings.m_RegLutOutputScale &= ~(0x7 << (lutId<<2)); 
    internal::g_lightingStageSettings.m_RegLutOutputScale |= outputScalingV << (lutId<<2);

    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_LUT_OUTPUT_SCALING_UPDATED;
}


/*********************************************************************************************************/
/************************************ Light inline functions implementation ******************************/

NN_FORCE_INLINE void Light::EnableLight(gdBool value)
{
    m_LightEnabled_User = value;
    if (m_LightEnabled == value) return;
    m_LightEnabled = value;
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_LIGHT_ENABLED_UPDATED;
}


NN_FORCE_INLINE void Light::EnableSpotLight(gdBool value)
{
    //lightsSpotEnabled: 0x1c4, bit [ 8+id : 8+id ]
    if (value) internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(1 << (8 + m_LightId));
    else internal::g_lightingStageSettings.m_MiscReg1c4 |= 1 << (8 + m_LightId);
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}

NN_FORCE_INLINE void Light::EnableDistanceAttenuation(gdBool value)
{
    //AttDistEnabled: 0x1c4, bit [ 24+id : 24+id ]
    if (value) internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(1 << (24 + m_LightId));
    else internal::g_lightingStageSettings.m_MiscReg1c4 |= 1 << (24 + m_LightId);
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}
  
NN_FORCE_INLINE void Light::EnableShadowed(gdBool value)
{
    //lightsShadowEnabled: 0x1c4, bit [ id : id ]
    if (value) internal::g_lightingStageSettings.m_MiscReg1c4 &= ~(1 << m_LightId);
    else internal::g_lightingStageSettings.m_MiscReg1c4 |= 1 << m_LightId;
    internal::g_lightingStageSettings.m_DirtyFieldMask |= internal::LightingStageSettings::MASK_REG_01C4_UPDATED;
}

}  // namespace CTR
}  // namespace gd
}  // namespace nn


#endif //NN_GD_CTR_GD_LIGHTING_H_
