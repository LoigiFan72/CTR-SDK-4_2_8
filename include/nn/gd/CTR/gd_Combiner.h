/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Combiner.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/


#ifndef NN_GD_CTR_GD_COMBINER_H_
#define NN_GD_CTR_GD_COMBINER_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>

#include <string.h>

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

class CombinerState;
class CombinerDescription;
class LightingStage;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
    
    
*/
#endif
class CombinerStage
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else   
    /* Please see man pages for details */
    #endif  
    static const u32 COUNT_TEXTURE_COMBINER_UNITS = 6;
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum UnitId
    {
        UNIT0   = 0,
        UNIT1   = 1,
        UNIT2   = 2,
        UNIT3   = 3,
        UNIT4   = 4,
        UNIT5   = 5,

        UNIT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details 
    
    */
    #endif
    enum Source
    {
        SOURCE_PRIMARY_COLOR                 = 0x0,
        SOURCE_FRAGMENT_PRIMARY_COLOR        = 0x1,
        SOURCE_FRAGMENT_SECONDARY_COLOR      = 0x2,
        SOURCE_TEXTURE0                      = 0x3,
        SOURCE_TEXTURE1                      = 0x4,
        SOURCE_TEXTURE2                      = 0x5,
        SOURCE_TEXTURE3                      = 0x6,
        SOURCE_PREVIOUS_BUFFER               = 0xd,
        SOURCE_CONSTANT                      = 0xe,
        SOURCE_PREVIOUS                      = 0xf,

        SOURCE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum OperandRgb
    {
        OPERAND_RGB_SRC_COLOR            = 0x0,
        OPERAND_RGB_ONE_MINUS_SRC_COLOR  = 0x1,
        OPERAND_RGB_SRC_ALPHA            = 0x2,
        OPERAND_RGB_ONE_MINUS_SRC_ALPHA  = 0x3,
        OPERAND_RGB_SRC_R                = 0x4,
        OPERAND_RGB_ONE_MINUS_SRC_R      = 0x5,
        OPERAND_RGB_SRC_G                = 0x8,
        OPERAND_RGB_ONE_MINUS_SRC_G      = 0x9,
        OPERAND_RGB_SRC_B                = 0xc,
        OPERAND_RGB_ONE_MINUS_SRC_B      = 0xd,

        OPERAND_RGB_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum OperandAlpha
    {
        OPERAND_ALPHA_SRC_ALPHA             = 0x0,
        OPERAND_ALPHA_ONE_MINUS_SRC_ALPHA   = 0x1,
        OPERAND_ALPHA_SRC_R                 = 0x2,
        OPERAND_ALPHA_ONE_MINUS_SRC_R       = 0x3,
        OPERAND_ALPHA_SRC_G                 = 0x4,
        OPERAND_ALPHA_ONE_MINUS_SRC_G       = 0x5,
        OPERAND_ALPHA_SRC_B                 = 0x6,
        OPERAND_ALPHA_ONE_MINUS_SRC_B       = 0x7,

        OPERAND_ALPHA_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum CombineRgb
    {
        COMBINE_RGB_REPLACE      = 0x0,
        COMBINE_RGB_MODULATE     = 0x1,
        COMBINE_RGB_ADD          = 0x2,
        COMBINE_RGB_ADD_SIGNED   = 0x3,
        COMBINE_RGB_INTERPOLATE  = 0x4,
        COMBINE_RGB_SUBTRACT     = 0x5,
        COMBINE_RGB_DOT3_RGB     = 0x6,
        COMBINE_RGB_DOT3_RGBA    = 0x7,
        COMBINE_RGB_MULT_ADD     = 0x8,
        COMBINE_RGB_ADD_MULT     = 0x9,

        COMBINE_RGB_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum CombineAlpha
    {
        COMBINE_ALPHA_REPLACE      = 0x0,
        COMBINE_ALPHA_MODULATE     = 0x1,
        COMBINE_ALPHA_ADD          = 0x2,
        COMBINE_ALPHA_ADD_SIGNED   = 0x3,
        COMBINE_ALPHA_INTERPOLATE  = 0x4,
        COMBINE_ALPHA_SUBTRACT     = 0x5,
        COMBINE_ALPHA_DOT3_RGBA    = 0x7,
        COMBINE_ALPHA_MULT_ADD     = 0x8,
        COMBINE_ALPHA_ADD_MULT     = 0x9,

        COMBINE_ALPHA_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum Scale
    {
        SCALE_1 = 0x0,
        SCALE_2 = 0x1,
        SCALE_4 = 0x2,

        SCALE_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum BufferInput
    {
        INPUT_PREVIOUS_BUFFER   = 0x0,
        INPUT_PREVIOUS_UNIT     = 0x1,

        INPUT_PREVIOUS_RESERVED_MAX_U32 = 0xffffffffu
    };


    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 

        
        

        
        
        
        
        
                                       

    */
    #endif
    static nnResult CreateTextureCombinerState(const CombinerDescription* description, CombinerState** textureCombinerState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 

        

        
        
        
        
    */
    #endif
    static nnResult ReleaseTextureCombinerState(CombinerState* textureCombinerState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult SetTextureCombinerState(CombinerState* textureCombinerState);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
		
		
		
		
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        

        
        
        
    */
    #endif
    static nnResult SetTextureCombinerUnitConstantColor(UnitId unit, u8 colorR, u8 colorG, u8 colorB, u8 colorA);

};  // CombinerStage


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class CombinerUnitDescription
{
public:
    
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
     */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    CombinerStage::Source       m_SrcRGB[3];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
     */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    CombinerStage::Source       m_SrcAlpha[3];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerStage::OperandRgb   m_OperandRgb[3];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerStage::OperandAlpha m_OperandAlpha[3];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerStage::CombineRgb   m_CombineRgb;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
      */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerStage::CombineAlpha m_CombineAlpha;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerStage::Scale        m_ScaleRgb;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerStage::Scale        m_ScaleAlpha;
};

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
*/
#endif
class CombinerDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    CombinerUnitDescription m_CombinerUnit[CombinerStage::COUNT_TEXTURE_COMBINER_UNITS];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    u8 m_BufferColor[4];

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
      
      
      
      
      

          
          
          
          
          
          

          
          
          
          
          
          

          
          
          
          
          
          
          
          
          
          
    */
    #else
    /* Please see man pages for details 
      
      
      
      
      
      

          
          
          
          
          
          

          
          
          
          
          
          

          
          
          
          
          
          
          
          
          
          
       
    */
    #endif
    u32 m_CombinerInUse;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else   
    /* Please see man pages for details 
        
        
        
    */
    #endif  
    struct BufferInput
    {
        //! Texture combiner unit 1 color
        CombinerStage::BufferInput m_Rgb1; 
        //! Texture combiner unit 2 color
        CombinerStage::BufferInput m_Rgb2;
        //! Texture combiner unit 3 color
        CombinerStage::BufferInput m_Rgb3;
        //! Texture combiner unit 4 color
        CombinerStage::BufferInput m_Rgb4;
        //! Texture combiner unit 1 alpha
        CombinerStage::BufferInput m_Alpha1;
        //! Texture combiner unit 2 alpha
        CombinerStage::BufferInput m_Alpha2;
        //! Texture combiner unit 3 alpha
        CombinerStage::BufferInput m_Alpha3;
        //! Texture combiner unit 4 alpha
        CombinerStage::BufferInput m_Alpha4;
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else  
    /* Please see man pages for details 
        
        
    */
    #endif
    struct BufferInput m_BufferInput;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #endif
    void SetSourceRGB(CombinerStage::UnitId unit, CombinerStage::Source sourceRGB1, CombinerStage::Source sourceRGB2, CombinerStage::Source sourceRGB3)
    {
        m_CombinerUnit[unit].m_SrcRGB[0] = sourceRGB1;
        m_CombinerUnit[unit].m_SrcRGB[1] = sourceRGB2;
        m_CombinerUnit[unit].m_SrcRGB[2] = sourceRGB3;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */ 
    #endif
    void SetOperandRGB(CombinerStage::UnitId unit, CombinerStage::OperandRgb opRGB1, CombinerStage::OperandRgb opRGB2, CombinerStage::OperandRgb opRGB3)
    {
        m_CombinerUnit[unit].m_OperandRgb[0] = opRGB1;
        m_CombinerUnit[unit].m_OperandRgb[1] = opRGB2;
        m_CombinerUnit[unit].m_OperandRgb[2] = opRGB3;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */   
    #endif
    void SetSourceAlpha(CombinerStage::UnitId unit, CombinerStage::Source sourceA1, CombinerStage::Source sourceA2, CombinerStage::Source sourceA3)
    {
        m_CombinerUnit[unit].m_SrcAlpha[0] = sourceA1;
        m_CombinerUnit[unit].m_SrcAlpha[1] = sourceA2;
        m_CombinerUnit[unit].m_SrcAlpha[2] = sourceA3;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
    */  
    #endif
    void SetOperandAlpha(CombinerStage::UnitId unit, CombinerStage::OperandAlpha opA1, CombinerStage::OperandAlpha opA2, CombinerStage::OperandAlpha opA3)
    {
        m_CombinerUnit[unit].m_OperandAlpha[0] = opA1;
        m_CombinerUnit[unit].m_OperandAlpha[1] = opA2;
        m_CombinerUnit[unit].m_OperandAlpha[2] = opA3;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */
    #endif
    void SetCombineRGB(CombinerStage::UnitId unit, CombinerStage::CombineRgb combineRgb)
    {
        m_CombinerUnit[unit].m_CombineRgb = combineRgb;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */  
    #endif
    void SetCombineAlpha(CombinerStage::UnitId unit, CombinerStage::CombineAlpha combineAlpha)
    {
        m_CombinerUnit[unit].m_CombineAlpha = combineAlpha;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */
    #endif
    void SetScaleRGB(CombinerStage::UnitId unit, CombinerStage::Scale scaleRgb)
    {
        m_CombinerUnit[unit].m_ScaleRgb = scaleRgb;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */ 
    #endif
    void SetScaleAlpha(CombinerStage::UnitId unit, CombinerStage::Scale scaleAlpha)
    {
        m_CombinerUnit[unit].m_ScaleAlpha = scaleAlpha;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else  
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    void SetBufferColor(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
    {
        m_BufferColor[0] = colorR;
        m_BufferColor[1] = colorG;
        m_BufferColor[2] = colorB;
        m_BufferColor[3] = colorA;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */ 
    #endif
    void SetCombinerInUse(CombinerStage::UnitId unit, gdBool mode)
    {
        u32 UseId = 1<<unit;

        m_CombinerInUse &= ~(UseId);
        if (mode == GD_TRUE) m_CombinerInUse |= UseId;
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
   /* Please see man pages for details 
    */
    #endif
    CombinerDescription()
    {
        ToDefault();
    }

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
         
         
           
         
         
         
         
         
         
         
         
         
         
         
         
    */
    #else  
    /* Please see man pages for details 
        
        
         
         
         
           

         

         

         

         

         

         

         

         

         

         

         

         
    */
    #endif
    void ToDefault()
    {
        memset(m_CombinerUnit, 0, sizeof(m_CombinerUnit));

        m_CombinerUnit[0].m_SrcRGB[0] = m_CombinerUnit[0].m_SrcRGB[1] = m_CombinerUnit[0].m_SrcRGB[2] = CombinerStage::SOURCE_CONSTANT;
        m_CombinerUnit[0].m_SrcAlpha[0] = m_CombinerUnit[0].m_SrcAlpha[1] = m_CombinerUnit[0].m_SrcAlpha[2] = CombinerStage::SOURCE_CONSTANT;

        for (int i = 1; i < CombinerStage::COUNT_TEXTURE_COMBINER_UNITS; i++)
        {
            m_CombinerUnit[i].m_SrcRGB[0] = m_CombinerUnit[i].m_SrcRGB[1] = m_CombinerUnit[i].m_SrcRGB[2] = CombinerStage::SOURCE_PREVIOUS;
            m_CombinerUnit[i].m_SrcAlpha[0] = m_CombinerUnit[i].m_SrcAlpha[1] = m_CombinerUnit[i].m_SrcAlpha[2] = CombinerStage::SOURCE_PREVIOUS;
        }
        m_BufferInput.m_Rgb1 = m_BufferInput.m_Rgb2 = m_BufferInput.m_Rgb3 = m_BufferInput.m_Rgb4 = 
            m_BufferInput.m_Alpha1 = m_BufferInput.m_Alpha2 = m_BufferInput.m_Alpha3 = m_BufferInput.m_Alpha4 = CombinerStage::INPUT_PREVIOUS_BUFFER;
        m_BufferColor[0] = m_BufferColor[1] = m_BufferColor[2] = m_BufferColor[3] = 0;
        m_CombinerInUse = 0;
    }

};  // CombinerDescription;

}  // namespace CTR
}  // namespace gd
}  // namespace nn


#endif // NN_GD_CTR_GD_COMBINER_H_
