/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_GasFog.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

#ifndef NN_GD_CTR_GD_GASFOG_H_
#define NN_GD_CTR_GD_GASFOG_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>
#include <nn/gd/CTR/gd_Utils.h>
#include <nn/dbg.h>

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
class FogStage;
class System;
namespace internal
{

class System;
class FogStage;
class OutputStage;
class GasFogSettings
{
private:
    // 0x0e0 (Fog/Gas mode, shading density, zFlip)
    u32 m_ModeShadingZFlip;

    // 0x0e1
    u32 m_FogColor;

    // 0x0e4
    u32 m_GasAttenuation;

    // 0x0e5
    u32 m_GasMaxAcc;

    // 0x120 - 0x122
    u32 m_GasLightXY;
    u32 m_GasLightZ;
    u32 m_GasLightZ4ColorLut;

    // 0x126
    u32 m_GasDeltaZ;

    // Mask for dirty attributes
    u32 m_DirtyFieldMask;
    u32 m_GasAutoAcc;

    enum
    {
        MASK_FOG_GAS_MODE_UPDATED               = 1 << 0,
        MASK_FOG_COLOR_UPDATED                  = 1 << 1,
        MASK_GAS_ATTENUATION_UPDATED            = 1 << 2,
        MASK_GAS_MAX_ACC_UPDATED                = 1 << 3,
        MASK_GAS_LIGHT_XY_UPDATED               = 1 << 4,
        MASK_GAS_LIGHT_Z_UPDATED                = 1 << 5,
        MASK_GAS_LIGHT_Z4_COLOR_LUT_UPDATED     = 1 << 6,
        MASK_GAS_DELTA_Z_UPDATED                = 1 << 7,

        MASK_RESERVED_MAX_U32 = 0xffffffffu
    };

friend class nn::gd::CTR::FogStage;
friend class nn::gd::CTR::internal::System;
friend class nn::gd::CTR::System;
friend class nn::gd::CTR::internal::FogStage;
friend class nn::gd::CTR::internal::OutputStage;
};  // GasFogSettings

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
extern GasFogSettings g_gasFogSettings;
}  // internal
        

/*********************************************************************************************************/
/************************************************* FogStage ************************************************/
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
    
    
*/
#endif
class FogStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum Mode
    {
        MODE_NONE    = 0x0,
        MODE_FOG     = 0x5,
        MODE_GAS     = 0x7,

        MODE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum GasColorLookUpTableInput
    {
        GAS_COLOR_INPUT_DENSITY      = 0,
        GAS_COLOR_INPUT_LIGHT_FACTOR = 1,

        GAS_COLOR_INPUT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum GasShadingDensitySource
    {
        GAS_SHADING_DENSITY_SOURCE_PLAIN = 0,
        GAS_SHADING_DENSITY_SOURCE_DEPTH = 1,

        GAS_SHADING_DENSITY_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetGasFogMode(Mode mode);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetGasShadingDensity(GasShadingDensitySource shadingDensitySrc);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetFogZFlip(gdBool zFlip);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
    */
    #endif
    static void SetFogColor(u8 R, u8 G, u8 B);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetGasAttenuation(f32 attenuation);
       
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetGasAccumulationMax(f32 maxAccumulation);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetGasAutoAccumulation(gdBool enableAutoAccumulation);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
    */  
    #else
    /* Please see man pages for details 
        
        
        
    */  
    #endif
    static void SetGasLightXY(u8 lightMinimum, u8 lightMaximum, u8 lightAttenuation);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    static void SetGasLightZ(u8 scattMinimum, u8 scattMaximum, u8 scattAttenuation, u8 lz);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void SetGasLightColorLutInput(GasColorLookUpTableInput colorLutInput);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetGasDeltaZ(f32 deltaZ);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        

        
        
		
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        

        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult UploadFogLookUpTableNative(u32 lutStartIndex, u32* data, u32 countData);
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
        
		
		
		
		
		
		
        
    */
   #else
    /* Please see man pages for details 
        
        

        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult UploadFogLookUpTableFloat(u32 lutStartIndex, const f32* dataValue, const f32* dataDelta, u32 countData);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        

        
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        

        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult UploadGasLookUpTableNative(u32 lutStartIndex, u32* data, u32 countData);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        

        
        
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        

        
        
        
        

        
        
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UploadGasLookUpTableFloat(u32 lutStartIndex, f32* dataValue, f32* dataDelta, u32 countData);

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
        static nnResult ConvertFogLookUpTableDataFloatToNative(const f32* dataValue, const f32* dataDelta, u32 countData, u32 *__restrict dest);

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            

            
            
            
			
			
			
			
            
        */
        #else
        /* Please see man pages for details 
            
            

            
            
            
            

            
            
            
        */
        #endif
        static nnResult ConvertGasLookUpTableDataFloatToNative(const f32* dataValue, const f32* dataDelta, u32 countData, u32 *__restrict dest);
    };

};  // class FogStage



/*-------------------------------------------------------------
    FogStage inline functions implementation
---------------------------------------------------------------*/

NN_FORCE_INLINE void FogStage::SetGasFogMode(Mode mode)
{
    internal::g_gasFogSettings.m_ModeShadingZFlip &= ~(0x7);
    internal::g_gasFogSettings.m_ModeShadingZFlip |= (mode & 0x7);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_FOG_GAS_MODE_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasShadingDensity(GasShadingDensitySource shadingDensitySrc)
{
    internal::g_gasFogSettings.m_ModeShadingZFlip &= ~(1 << 3);
    if (shadingDensitySrc) internal::g_gasFogSettings.m_ModeShadingZFlip |= (1<<3);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_FOG_GAS_MODE_UPDATED; 
}

NN_FORCE_INLINE void FogStage::SetFogZFlip(gdBool zFlip)
{
    internal::g_gasFogSettings.m_ModeShadingZFlip &= ~(1 << 16);
    if (zFlip) internal::g_gasFogSettings.m_ModeShadingZFlip |= (1 << 16);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_FOG_GAS_MODE_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetFogColor(u8 R, u8 G, u8 B)
{
    internal::g_gasFogSettings.m_FogColor = R | (G << 8) | (B << 16);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_FOG_COLOR_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasAttenuation(f32 atte)
{
    internal::g_gasFogSettings.m_GasAttenuation = Utils::Float32ToFloat16(atte);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_ATTENUATION_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasAccumulationMax(f32 maxAcc)
{   
    // Convert to f16
    internal::g_gasFogSettings.m_GasMaxAcc = Utils::Float32ToFloat16(maxAcc);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_MAX_ACC_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasAutoAccumulation(gdBool autoAcc)
{
    internal::g_gasFogSettings.m_GasAutoAcc = autoAcc;
    //internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_AUTO_ACC_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasLightXY(u8 lightMin, u8 lightMax, u8 lightAtt)
{   
    internal::g_gasFogSettings.m_GasLightXY = lightMin  | (lightMax << 8) | (lightAtt << 16);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_LIGHT_XY_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasLightZ(u8 scattMin, u8 scattMax, u8 scattAtt, u8 lz)
{
    internal::g_gasFogSettings.m_GasLightZ = scattMin | (scattMax << 8) | (scattAtt << 16);
    internal::g_gasFogSettings.m_GasLightZ4ColorLut &= ~(0xff);
    internal::g_gasFogSettings.m_GasLightZ4ColorLut |= lz;
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_LIGHT_Z_UPDATED | internal::GasFogSettings::MASK_GAS_LIGHT_Z4_COLOR_LUT_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasLightColorLutInput(GasColorLookUpTableInput colorLutInput)
{
    internal::g_gasFogSettings.m_GasLightZ4ColorLut &= ~(1 << 8);
    if (colorLutInput) internal::g_gasFogSettings.m_GasLightZ4ColorLut |= (1<<8);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_LIGHT_Z4_COLOR_LUT_UPDATED;
}

NN_FORCE_INLINE void FogStage::SetGasDeltaZ(f32 deltaZ)
{
    internal::g_gasFogSettings.m_GasDeltaZ = Utils::Float32ToUnsignedFix24Fraction8(deltaZ);
    internal::g_gasFogSettings.m_DirtyFieldMask |= internal::GasFogSettings::MASK_GAS_DELTA_Z_UPDATED;
}

}  // namespace CTR
}  // namespace gd
}  // namespace nn


#endif // NN_GD_CTR_GD_GASFOG_H_
