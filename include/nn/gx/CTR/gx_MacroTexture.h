/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gx_MacroTexture.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GX_CTR_PICA_MACRO_TEXTURE_H_
#define NN_GX_CTR_PICA_MACRO_TEXTURE_H_

#include <nn/gx/CTR/gx_MacroCommon.h>

/* Please see man pages for details 
  
  
*/

///////////////////////////////////
// Texture address

// PICA_REG_TEXTURE0_ADDR1      0x085
// PICA_REG_TEXTURE0_ADDR2       0x086
// PICA_REG_TEXTURE0_ADDR3       0x087
// PICA_REG_TEXTURE0_ADDR4       0x088
// PICA_REG_TEXTURE0_ADDR5       0x089
// PICA_REG_TEXTURE0_ADDR6       0x08a
// PICA_REG_TEXTURE2_ADDR        0x09d
// PICA_REG_TEXTURE1_ADDR        0x095
#define PICA_CMD_DATA_TEXTURE_ADDR( addr ) \
    ( (u32)(addr) >> 3 )

/*
struct CommandTexCubeMap
{
    CMD_PADDING(22);
    u32 CubeMap   : 6;
    CMD_PADDING(4);
};
*/
    
/* Please see man pages for details 
    
*/
enum PicaDataTexture
{
    //
    PICA_DATA_TEXTURE_2D                  = 0x0,
    //
    PICA_DATA_TEXTURE_CUBE_MAP_POSITIVE_X = 0x0,
    //
    PICA_DATA_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x1,
    //
    PICA_DATA_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x2,
    //
    PICA_DATA_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x3,
    //
    PICA_DATA_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x4,
    //
    PICA_DATA_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x5
};

// PICA_REG_TEXTURE0_ADDR1      0x085
#define PICA_CMD_DATA_TEXTURE_CUBE_MAP_ADDR(cubeMapAddr) \
    ( (cubeMapAddr) & 0x3fffff )

///////////////////////////////////
// Texture combiner
// TexEnv

/*
struct CommandTexEnvSrc
{
    u32 srcRgb0   : 4;
    u32 srcRgb1   : 4;
    u32 srcRgb2   : 4;
    CMD_PADDING(4);
    u32 srcAlpha0 : 4;
    u32 srcAlpha1 : 4;
    u32 srcAlpha2 : 4;
    CMD_PADDING(4);
};
*/

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexEnvSrc
{
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_PRIMARY_COLOR                = 0x0,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_FRAGMENT_PRIMARY_COLOR_DMP   = 0x1,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_FRAGMENT_SECONDARY_COLOR_DMP = 0x2,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_TEXTURE0                     = 0x3,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_TEXTURE1                     = 0x4,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_TEXTURE2                     = 0x5,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_TEXTURE3                     = 0x6,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_PREVIOUS_BUFFER_DMP          = 0xd,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_CONSTANT                     = 0xe,
    //
    PICA_DATA_TEX_ENV_SRC_RGBA_PREVIOUS                     = 0xf
};

#define PICA_TEX_ENV_SRC_RGB0_SHIFT         0
#define PICA_TEX_ENV_SRC_RGB1_SHIFT         4
#define PICA_TEX_ENV_SRC_RGB2_SHIFT         8
#define PICA_TEX_ENV_SRC_ALPHA0_SHIFT      16
#define PICA_TEX_ENV_SRC_ALPHA1_SHIFT      20
#define PICA_TEX_ENV_SRC_ALPHA2_SHIFT      24

// PICA_REG_TEX_ENV0            0x0c0
// PICA_REG_TEX_ENV1            0x0c8
// PICA_REG_TEX_ENV2            0x0d0
// PICA_REG_TEX_ENV3            0x0d8
// PICA_REG_TEX_ENV4            0x0f0
// PICA_REG_TEX_ENV5            0x0f8
#define PICA_CMD_DATA_TEX_ENV_SRC( srcRgb0, srcRgb1, srcRgb2, \
                                   srcAlpha0, srcAlpha1, srcAlpha2 ) \
    ( (srcRgb0)   << PICA_TEX_ENV_SRC_RGB0_SHIFT   | \
      (srcRgb1)   << PICA_TEX_ENV_SRC_RGB1_SHIFT   | \
      (srcRgb2)   << PICA_TEX_ENV_SRC_RGB2_SHIFT   | \
      (srcAlpha0) << PICA_TEX_ENV_SRC_ALPHA0_SHIFT | \
      (srcAlpha1) << PICA_TEX_ENV_SRC_ALPHA1_SHIFT | \
      (srcAlpha2) << PICA_TEX_ENV_SRC_ALPHA2_SHIFT )

/*
struct CommandTexEnvOperand
{
    u32 operandRg0    : 4;
    u32 operandRg1    : 4;
    u32 operandRg2    : 4;
    u32 operandAlpha0 : 3;
    CMD_PADDING(1);
    u32 operandAlpha1 : 3;
    CMD_PADDING(1);
    u32 operandAlpha2 : 3;
    CMD_PADDING(9);
};
*/

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexEnvOperand
{
    //
    PICA_DATA_OPE_RGB_SRC_COLOR            = 0x0,
    //
    PICA_DATA_OPE_RGB_ONE_MINUS_SRC_COLOR  = 0x1,
    //
    PICA_DATA_OPE_RGB_SRC_ALPHA            = 0x2,
    //
    PICA_DATA_OPE_RGB_ONE_MINUS_SRC_ALPHA  = 0x3,
    //
    PICA_DATA_OPE_RGB_SRC_R_DMP            = 0x4,
    //
    PICA_DATA_OPE_RGB_ONE_MINUS_SRC_R_DMP  = 0x5,
    //
    PICA_DATA_OPE_RGB_SRC_G_DMP            = 0x8,
    //
    PICA_DATA_OPE_RGB_ONE_MINUS_SRC_G_DMP  = 0x9,
    //
    PICA_DATA_OPE_RGB_SRC_B_DMP            = 0xc,
    //
    PICA_DATA_OPE_RGB_ONE_MINUS_SRC_B_DMP  = 0xd,
    //
    PICA_DATA_OPE_ALPHA_SRC_ALPHA           = 0x0,
    //
    PICA_DATA_OPE_ALPHA_ONE_MINUS_SRC_ALPHA = 0x1,
    //
    PICA_DATA_OPE_ALPHA_SRC_R_DMP           = 0x2,
    //
    PICA_DATA_OPE_ALPHA_ONE_MINUS_SRC_R_DMP = 0x3,
    //
    PICA_DATA_OPE_ALPHA_SRC_G_DMP           = 0x4,
    //
    PICA_DATA_OPE_ALPHA_ONE_MINUS_SRC_G_DMP = 0x5,
    //
    PICA_DATA_OPE_ALPHA_SRC_B_DMP           = 0x6,
    //
    PICA_DATA_OPE_ALPHA_ONE_MINUS_SRC_B_DMP = 0x7
};


#define PICA_TEX_ENV_OPE_RGB0_SHIFT         0
#define PICA_TEX_ENV_OPE_RGB1_SHIFT         4
#define PICA_TEX_ENV_OPE_RGB2_SHIFT         8
#define PICA_TEX_ENV_OPE_ALPHA0_SHIFT      12
#define PICA_TEX_ENV_OPE_ALPHA1_SHIFT      16
#define PICA_TEX_ENV_OPE_ALPHA2_SHIFT      20

// PICA_REG_TEX_ENV0_OPERAND    0x0c1
// PICA_REG_TEX_ENV1_OPERAND    0x0c9
// PICA_REG_TEX_ENV2_OPERAND    0x0d1
// PICA_REG_TEX_ENV3_OPERAND    0x0d9
// PICA_REG_TEX_ENV4_OPERAND    0x0f1
// PICA_REG_TEX_ENV5_OPERAND    0x0f9
#define PICA_CMD_DATA_TEX_ENV_OPERAND(operandRgb0, operandRgb1, operandRgb2, \
                                      operandAlpha0, operandAlpha1, operandAlpha2) \
    ( (operandRgb0)   << PICA_TEX_ENV_OPE_RGB0_SHIFT   | \
      (operandRgb1)   << PICA_TEX_ENV_OPE_RGB1_SHIFT   | \
      (operandRgb2)   << PICA_TEX_ENV_OPE_RGB2_SHIFT   | \
      (operandAlpha0) << PICA_TEX_ENV_OPE_ALPHA0_SHIFT | \
      (operandAlpha1) << PICA_TEX_ENV_OPE_ALPHA1_SHIFT | \
      (operandAlpha2) << PICA_TEX_ENV_OPE_ALPHA2_SHIFT )

/*
struct CommandTexEnvCombine
{
    u32 combineRgb   : 4;
    CMD_PADDING(12);
    u32 combineAlpha : 4;
    CMD_PADDING(12);
};
*/

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexEnvCombine
{
    //
    PICA_DATA_TEX_ENV_COMBINE_REPLACE      = 0x0,
    //
    PICA_DATA_TEX_ENV_COMBINE_MODULATE     = 0x1,
    //
    PICA_DATA_TEX_ENV_COMBINE_ADD          = 0x2,
    //
    PICA_DATA_TEX_ENV_COMBINE_ADD_SIGNED   = 0x3,
    //
    PICA_DATA_TEX_ENV_COMBINE_INTERPOLATE  = 0x4,
    //
    PICA_DATA_TEX_ENV_COMBINE_SUBTRACT     = 0x5,
    //
    PICA_DATA_TEX_ENV_COMBINE_DOT3_RGB     = 0x6,
    //
    PICA_DATA_TEX_ENV_COMBINE_DOT3_RGBA    = 0x7,
    //
    PICA_DATA_TEX_ENV_COMBINE_MULT_ADD_DMP = 0x8,
    //
    PICA_DATA_TEX_ENV_COMBINE_ADD_MULT_DMP = 0x9
};

// PICA_REG_TEX_ENV0_COMBINE    0x0c2
// PICA_REG_TEX_ENV1_COMBINE    0x0ca
// PICA_REG_TEX_ENV2_COMBINE    0x0d2
// PICA_REG_TEX_ENV3_COMBINE    0x0da
// PICA_REG_TEX_ENV4_COMBINE    0x0f2
// PICA_REG_TEX_ENV5_COMBINE    0x0fa
#define PICA_CMD_DATA_TEX_ENV_COMBINE( combineRgb, combineAlpha ) \
    ( (combineRgb) | (combineAlpha) << 16 )

/*
struct CommandTexEnvConst
{
    u32 constRgb1  : 8;
    u32 constRgb2  : 8;
    u32 constRgb3  : 8;
    u32 constRgb4  : 8;
};
*/
// PICA_REG_TEX_ENV0_COLOR      0x0c3
// PICA_REG_TEX_ENV1_COLOR      0x0cb
// PICA_REG_TEX_ENV2_COLOR      0x0d3
// PICA_REG_TEX_ENV3_COLOR      0x0db
// PICA_REG_TEX_ENV4_COLOR      0x0f3
// PICA_REG_TEX_ENV5_COLOR      0x0fb
#define PICA_CMD_DATA_TEX_ENV_CONST( constRgb0, constRgb1, constRgb2, constRgb3 ) \
    ((constRgb0) | (constRgb1) << 8 | (constRgb2) << 16 | (constRgb3) << 24)

/*
struct CommandTexEnvScale
{
    u32 scaleRgb   : 2;
    CMD_PADDING(14);
    u32 scaleAlpha : 2;
    CMD_PADDING(14);
};
*/

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexEnvScale
{
    //
    PICA_DATA_TEX_ENV_SCALE_1 = 0x0,
    //
    PICA_DATA_TEX_ENV_SCALE_2 = 0x1,
    //
    PICA_DATA_TEX_ENV_SCALE_4 = 0x2
};

// PICA_REG_TEX_ENV0_SCALE      0x0c4
// PICA_REG_TEX_ENV1_SCALE      0x0cc
// PICA_REG_TEX_ENV2_SCALE      0x0d4
// PICA_REG_TEX_ENV3_SCALE      0x0dc
// PICA_REG_TEX_ENV4_SCALE      0x0f4
// PICA_REG_TEX_ENV5_SCALE      0x0fc
#define PICA_CMD_DATA_TEX_ENV_SCALE( scaleRgb, scaleAlpha ) \
    ( (scaleRgb) | (scaleAlpha) << 16 )

#define PICA_CMD_DATA_TEX_ENV_BUFFER_COLOR_WHITE 0xffffffff
#define PICA_CMD_DATA_TEX_ENV_BUFFER_COLOR_BLACK 0x00000000

// PICA_REG_TEX_ENV_BUF_COLOR    0x0fd
#define PICA_CMD_DATA_COLOR( color8 ) \
    ( (color8.r) | (color8.g) << 8 | (color8.b) << 16 | (color8.a) << 24 )

/*
struct CommandTexEnvBufInput
{
    CMD_PADDING(8);
    u32 bufInput1 : 4; // 1 bit in this field
    CMD_PADDING(4);
    u32 bufInput2 : 4; // 1 bin in this field
    CMD_PADDING(12);
};
*/


/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexEnvBufferInput
{
    //
    PICA_DATA_TEX_ENV_BUFFER_INPUT_PREVIOUS_BUFFER_DMP = 0x0,
    //
    PICA_DATA_TEX_ENV_BUFFER_INPUT_PREVIOUS            = 0x1
};

// PICA_REG_TEX_ENV_BUF_INPUT    0x0e0
// i is index of dmp_TexEnv[i]. The values are 1, 2, 3, 4 only.

#define PICA_CMD_DATA_TEX_ENV_BUFFER_INPUT(i, bufInput0, bufInput1) \
    ((bufInput0) << 7+(i) | (bufInput1) << 11+(i))

// 0x0e0 [15:8]
#define PICA_CMD_SET_TEX_ENV_BUFFER_INPUT(bufInput0_0, bufInput0_1,     \
                                          bufInput1_0, bufInput1_1,     \
                                          bufInput2_0, bufInput2_1,     \
                                          bufInput3_0, bufInput3_1)     \
  ( PICA_CMD_DATA_TEX_ENV_BUFFER_INPUT(1, bufInput0_0, bufInput0_1) |   \
    PICA_CMD_DATA_TEX_ENV_BUFFER_INPUT(2, bufInput1_0, bufInput1_1) |   \
    PICA_CMD_DATA_TEX_ENV_BUFFER_INPUT(3, bufInput2_0, bufInput2_1) |   \
    PICA_CMD_DATA_TEX_ENV_BUFFER_INPUT(4, bufInput3_0, bufInput3_1) ) , \
    PICA_CMD_HEADER_SINGLE_BE(PICA_REG_GAS_FOG_MODE, 0x2)
        
///////////////////////////////////
// Shadow Textrue
//
/*
struct CommandTextureShadow
{
    u32 perspectiveShadow : 1; 
    u32 shadowZBias       : 23; 
    u32 shadowZScale      : 8; 
};
*/

// PICA_REG_TEXTURE0_SHADOW      0x08b
#define PICA_CMD_DATA_TEXTURE_SHADOW(perspectiveShadow, shadowZBias, shadowZScale) \
    (( (perspectiveShadow) ? 0 : 1) | (shadowZBias) << 1 | (shadowZScale) << 24)

///////////////////////////////////
// Texture Sampler
// Texture Texcoord
// Texture Cache Clear
/*
struct CommandTextureFunc
{
    u32 type0_0 : 1;
    u32 type1   : 1;
    u32 type2   : 1;
    CMD_PADDING(1);   // 0x0
    CMD_PADDING(4);
    u32 texcoord3   : 2;
    u32 type3   : 1;
    CMD_PADDING(1);
    CMD_PADDING(1);   // 0x1
    u32 texcoord2   : 1;
    CMD_PADDING(2);
    u32 clear : 1;
    CMD_PADDING(15);

};
*/

//  Texture Sampler

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexture0SamplerType
{
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_2D              = 0x0,
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_CUBE_MAP        = 0x1,
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_SHADOW_2D_DMP   = 0x2,
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_PROJECTION_DMP  = 0x3,
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_SHADOW_CUBE_DMP = 0x4,    
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_FALSE           = 0x5,
    //
    PICA_DATA_TEXTURE0_SAMPLER_TYPE_FALSE                   = 0x5
};

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexture1SamplerType
{
    //
    PICA_DATA_TEXTURE1_SAMPLER_TYPE_FALSE      = 0x0,
    //
    PICA_DATA_TEXTURE1_SAMPLER_TYPE_TEXTURE_2D = 0x1
};

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexture2SamplerType
{
    //
    PICA_DATA_TEXTURE2_SAMPLER_TYPE_FALSE      = 0x0,
    //
    PICA_DATA_TEXTURE2_SAMPLER_TYPE_TEXTURE_2D = 0x1
};

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexture3SamplerType
{
    //
    PICA_DATA_TEXTURE3_SAMPLER_TYPE_FALSE                  = 0x0,
    //
    PICA_DATA_TEXTURE3_SAMPLER_TYPE_TEXTURE_PROCEDURAL_DMP = 0x1
};


/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexture2TexCoord
{        
    //
    PICA_DATA_TEXTURE2_TEXCOORD_TEXTURE1 = 0x1,
    //
    PICA_DATA_TEXTURE2_TEXCOORD_TEXTURE2 = 0x0
};

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTexture3TexCoord
{
    //
    PICA_DATA_TEXTURE3_TEXCOORD_TEXTURE0 = 0x0,
    //
    PICA_DATA_TEXTURE3_TEXCOORD_TEXTURE1 = 0x1,
    //
    PICA_DATA_TEXTURE3_TEXCOORD_TEXTURE2 = 0x2
};

// PICA_REG_TEXTURE_FUNC 0x080
#define PICA_CMD_DATA_TEXTURE_FUNC(texture0SamplerType, texture1SamplerType, texture2SamplerType, \
                                   texture3Texcoord, texture3SamplerType, \
                                   texture2Texcoord, clearTextureCache)   \
    ( ((texture0SamplerType == PICA_DATA_TEXTURE0_SAMPLER_TYPE_TEXTURE_FALSE) ? 0 : 1)  | \
      ((texture1SamplerType) ? 1 : 0)     <<  1  | \
      ((texture2SamplerType) ? 1 : 0)     <<  2  | \
      0                                   <<  3  | \
       (texture3Texcoord)                 <<  8  | \
      ((texture3SamplerType) ? 1 : 0)     << 10  | \
      1                                   << 12  | \
      ((texture2Texcoord) ? 1 : 0)        << 13  | \
      (clearTextureCache)                 << 16  | \
      0 << 17 )

#define PICA_CMD_SET_TEXTURE_FUNC_CLEAR(texture0SamplerType, texture1SamplerType, texture2SamplerType, \
                                        texture3SamplerType, texture2Texcoord, texture3Texcoord)       \
    PICA_CMD_DATA_TEXTURE_FUNC(texture0SamplerType, texture1SamplerType, texture2SamplerType,          \
                               texture3Texcoord, texture3SamplerType,                                  \
                               texture2Texcoord, 0x1),                                                 \
    PICA_CMD_HEADER_SINGLE_BE( PICA_REG_TEXTURE_FUNC, 0xB ),                                           \
    1 << 16,                                                                                           \
    PICA_CMD_HEADER_SINGLE_BE( PICA_REG_TEXTURE_FUNC, 0x4 )

#define PICA_CMD_SET_TEXTURE_FUNC(texture0SamplerType, texture1SamplerType, texture2SamplerType, \
                                        texture3SamplerType, texture2Texcoord, texture3Texcoord) \
    PICA_CMD_DATA_TEXTURE_FUNC(texture0SamplerType, texture1SamplerType, texture2SamplerType,    \
                               texture3Texcoord, texture3SamplerType,                            \
                               texture2Texcoord, 0x0),                                           \
    PICA_CMD_HEADER_SINGLE_BE( PICA_REG_TEXTURE_FUNC, 0xB )

///////////////////////////////////
// Procedural Texture
//
/*
struct CommandProcTex0
{
    u32 ptClampU        : 3;
    u32 ptClampV        : 4;
    u32 ptRgbMap        : 4;
    u32 ptAlphaMap      : 4;
    u32 ptAlphaSeparate : 1;
    u32 ptNoiseEnable   : 1;
    u32 ptShiftU        : 2;
    u32 ptShiftV        : 2;
    u32 ptTexBias1       : 8;
    CMD_PADDING(3);
};
*/

/* Please see man pages for details 
    
           
           
*/
enum PicaDataProcTexMap
{
    //
    PICA_DATA_PROCTEX_U_DMP        = 0x0,
    //
    PICA_DATA_PROCTEX_U2_DMP       = 0x1,
    //
    PICA_DATA_PROCTEX_V_DMP        = 0x2,
    //
    PICA_DATA_PROCTEX_V2_DMP       = 0x3,
    //
    PICA_DATA_PROCTEX_ADD_DMP      = 0x4,
    //
    PICA_DATA_PROCTEX_ADD2_DMP     = 0x5,
    //
    PICA_DATA_PROCTEX_ADDSQRT2_DMP = 0x6,
    //
    PICA_DATA_PROCTEX_MIN_DMP      = 0x7,
    //
    PICA_DATA_PROCTEX_MAX_DMP      = 0x8,
    //
    PICA_DATA_PROCTEX_RMAX_DMP     = 0x9
};

/* Please see man pages for details 
    
           
           
*/
enum PicaDataProcTexClamp
{
    //
    PICA_DATA_PROCTEX_CLAMP_TO_ZERO_DMP       = 0x0,
    //
    PICA_DATA_PROCTEX_CLAMP_TO_EDGE           = 0x1,
    //
    PICA_DATA_PROCTEX_SYMMETRICAL_REPEAT_DMP  = 0x2,
    //
    PICA_DATA_PROCTEX_MIRRORED_REPEAT         = 0x3,
    //
    PICA_DATA_PROCTEX_PULSE_DMP               = 0x4
};

/* Please see man pages for details 
    
           
           
*/
enum PicaDataProcTexShift
{
    //
    PICA_DATA_PROCTEX_NONE_DMP = 0x0,
    //
    PICA_DATA_PROCTEX_ODD_DMP  = 0x1,
    //
    PICA_DATA_PROCTEX_EVEN_DMP = 0x2
};

// PICA_REG_TEXTURE3_PROCTEX0     0x0a8
#define PICA_CMD_DATA_PROCTEX0(ptClampU, ptClampV, \
    ptRgbMap, ptAlphaMap, ptAlphaSeparate,         \
    ptNoiseEnable, ptShiftU, ptShiftV, ptTexBiasF16Low8) \
    ( (ptClampU)                         | \
      (ptClampV)                   <<  3 | \
      (ptRgbMap)                   <<  6 | \
      (ptAlphaMap)                 << 10 | \
      (ptAlphaSeparate ? 1 : 0)    << 14 | \
      (ptNoiseEnable ? 1 : 0)      << 15 | \
      (ptShiftU)                   << 16 | \
      (ptShiftV)                   << 18 | \
      (ptTexBiasF16Low8)           << 20 )
    


// PICA_REG_TEXTURE3_PROCTEX1    0x0a9
#define PICA_CMD_DATA_PROCTEX1(ptNoiseU1, ptNoiseU2) \
    ( (ptNoiseU1) << 16 | (ptNoiseU2) )
      
// PICA_REG_TEXTURE3_PROCTEX2    0x0aa
#define PICA_CMD_DATA_PROCTEX2(ptNoiseV1, ptNoiseV2) \
    ( (ptNoiseV1) << 16 | (ptNoiseV2) )

// PICA_REG_TEXTURE3_PROCTEX3    0x0ab
#define PICA_CMD_DATA_PROCTEX3(ptNoiseU0, ptNoiseV0) \
    ( (ptNoiseU0) | (ptNoiseV0) << 16 )

/*
struct CommandProcTex4   
{
    u32 ptMinFilter  : 3;
    CMD_PADDING(8);     // 0x60
    u32 ptTexWidth   : 8;
    u32 ptTexBias2   : 8;
    CMD_PADDING(5);
};
*/

/* Please see man pages for details 
    
           
           
*/
enum PicaDataProcTexFilter
{
    //
    PICA_DATA_PROCTEX_NEAREST                = 0x0,
    //
    PICA_DATA_PROCTEX_LINEAR                 = 0x1,
    //
    PICA_DATA_PROCTEX_NEAREST_MIPMAP_NEAREST = 0x2,
    //
    PICA_DATA_PROCTEX_LINEAR_MIPMAP_NEAREST  = 0x3,
    //
    PICA_DATA_PROCTEX_NEAREST_MIPMAP_LINEAR  = 0x4,
    //
    PICA_DATA_PROCTEX_LINEAR_MIPMAP_LINEAR   = 0x5
};

// PICA_REG_TEXTURE3_PROCTEX4    0x0ac
#define PICA_CMD_DATA_PROCTEX4(ptMinFilter, ptTexWidth, ptTexBiasF16Hi8) \
    ( (ptMinFilter)                 | \
       0x60                   <<  3 | \
      (ptTexWidth)            << 11 | \
      (ptTexBiasF16Hi8) << 19 )

/*
struct CommandProcTex5  
{
    u32 ptTexOffset  : 8;
    CMD_PADDING(24);   // 0xe0c080
};
*/

// PICA_REG_TEXTURE3_PROCTEX5    0x0ad
#define PICA_CMD_DATA_PROCTEX5(ptTexOffset) \
    ( (ptTexOffset) | 0xe0c08000 )

///////////////////////////////////
// Procedural texture Reference Table
/*
struct CommandProTexRefTab
{
    u32 index : 8;
    u32 attrib   : 4;
    CMD_PADDING(20);
};
*/


/* Please see man pages for details 
    
           
           
*/
enum PicaDataProcTexRefTable
{
    //
    PICA_DATA_PROCTEX_NOISE_REF_TABLE      = 0x0,
    //
    PICA_DATA_PROCTEX_RGB_MAP_REF_TABLE    = 0x2,
    //
    PICA_DATA_PROCTEX_ALPHA_MAP_REF_TABLE  = 0x3,
    //
    PICA_DATA_PROCTEX_COLOR_REF_TABLE      = 0x4,
    //
    PICA_DATA_PROCTEX_COLOR_DIFF_REF_TABLE = 0x5
};

// PICA_REG_PROCTEX_LUT         0x0af
#define PICA_CMD_DATA_PROCTEX_LUT(index, refTable) \
    ((index) | (refTable) << 8)

// PICA_REG_PROCTEX_LUT_DATA0  0x0b0
// PICA_REG_PROCTEX_LUT_DATA1  0x0b1
// PICA_REG_PROCTEX_LUT_DATA2  0x0b2
// PICA_REG_PROCTEX_LUT_DATA3  0x0b3
// PICA_REG_PROCTEX_LUT_DATA4  0x0b4
// PICA_REG_PROCTEX_LUT_DATA5  0x0b5
// PICA_REG_PROCTEX_LUT_DATA6  0x0b6
// PICA_REG_PROCTEX_LUT_DATA7  0x0b7
#define PICA_CMD_DATA_PROCTEX_LUT_DATA(data) (data)

///////////////////////////////////
// Texture Resolution
/*
struct CommandTexSize
{
    u32 height : 16;
    u32 width  : 16;
};
*/

// PICA_REG_TEXTURE0_SIZE        0x082
// PICA_REG_TEXTURE1_SIZE        0x092
// PICA_REG_TEXTURE2_SIZE        0x09a
#define PICA_CMD_DATA_TEXTURE_SIZE( width, height ) \
    ( (height) | (width) << 16 )

///////////////////////////////////
// Texture Format

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTextureFormat
{
    //
    PICA_DATA_TEXTURE_FORMAT_RGBA_UNSIGNED_BYTE                    = 0x0,
    //
    PICA_DATA_TEXTURE_FORMAT_SHADOW_UNSIGNED_INT                   = 0x0,
    //
    PICA_DATA_TEXTURE_FORMAT_GAS_DMP_UNSIGNED_SHORT                = 0x0,
    //
    PICA_DATA_TEXTURE_FORMAT_RGB_UNSIGNED_BYTE                     = 0x1,
    //
    PICA_DATA_TEXTURE_FORMAT_RGBA_UNSIGNED_SHORT_5_5_5_1           = 0x2,
    //
    PICA_DATA_TEXTURE_FORMAT_RGB_UNSIGNED_SHORT_5_6_5              = 0x3,
    //
    PICA_DATA_TEXTURE_FORMAT_RGBA_UNSIGNED_SHORT_4_4_4_4           = 0x4,
    //
    PICA_DATA_TEXTURE_FORMAT_LUMINANCE_ALPHA_UNSIGNED_BYTE         = 0x5,
    //
    PICA_DATA_TEXTURE_FORMAT_HILO8_DMP_UNSIGNED_BYTE               = 0x6,
    //
    PICA_DATA_TEXTURE_FORMAT_LUMINANCE_UNSIGNED_BYTE               = 0x7,
    //
    PICA_DATA_TEXTURE_FORMAT_ALPHA_UNSIGNED_BYTE                   = 0x8,
    //
    PICA_DATA_TEXTURE_FORMAT_LUMINANCE_ALPHA_UNSIGNED_BYTE_4_4_DMP = 0x9,
    //
    PICA_DATA_TEXTURE_FORMAT_LUMINANCE_UNSIGNED_4BITS_DMP          = 0xa,
    //
    PICA_DATA_TEXTURE_FORMAT_ALPHA_UNSIGNED_4BITS_DMP              = 0xb,
    //
    PICA_DATA_TEXTURE_FORMAT_ETC1_RGB8_NATIVE_DMP                  = 0xc,
    //
    PICA_DATA_TEXTURE_FORMAT_ETC1_ALPHA_RGB8_A4_NATIVE_DMP         = 0xd    
};

// PICA_REG_TEXTURE0_FORMAT      0x08e
// PICA_REG_TEXTURE1_FORMAT      0x096
// PICA_REG_TEXTURE2_FORMAT      0x09e
#define PICA_CMD_DATA_TEXTURE_FORMAT_TYPE( type ) (type)

///////////////////////////////////
// Texture Wrap Mode
// Texture Wrap Filter
// Texture Sampler
// Texture Format
// Texture Shadow Enable
/*
struct CommandTex0WrapFilter
{
    CMD_PADDING(1);
    u32 magFilter  : 1;
    u32 minFilter1 : 1;
    CMD_PADDING(1);
    u32 isETC1    : 2;
    CMD_PADDING(2);
    u32 wrapT     : 3;
    CMD_PADDING(1);
    u32 wrapS     : 3;
    CMD_PADDING(1);
    CMD_PADDING(2);       // set to 0 [17:16]
    CMD_PADDING(2);
    u32 enable    : 1;
    CMD_PADDING(3);
    u32 minFilter2 : 1;
    CMD_PADDING(3);
    u32 type1_1 : 3;
    CMD_PADDING(1);
};
*/


/* Please see man pages for details 
    
           
           
*/
enum PicaDataTextureMagFilter
{
    //
    PICA_DATA_TEXTURE_MAG_FILTER_NEAREST                = 0x0,
    //
    PICA_DATA_TEXTURE_MAG_FILTER_LINEAR                 = 0x1
};


/* Please see man pages for details 
    
           
           
*/
enum PicaDataTextureMinFilter
{
    //
    PICA_DATA_TEXTURE_MIN_FILTER_NEAREST                = 0x0,
    //
    PICA_DATA_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_NEAREST = 0x1,
    //
    PICA_DATA_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_LINEAR  = 0x2,
    //
    PICA_DATA_TEXTURE_MIN_FILTER_LINEAR                 = 0x3,
    //
    PICA_DATA_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_NEAREST  = 0x4,
    //
    PICA_DATA_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_LINEAR   = 0x5
};

#define PICA_CMD_DATA_TEXTURE_MIN_FILTER0(texture0MinFilter) \
    ( ( ( (texture0MinFilter) == PICA_DATA_TEXTURE_MIN_FILTER_LINEAR ) ||                \
        ( (texture0MinFilter) == PICA_DATA_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_NEAREST ) || \
        ( (texture0MinFilter) == PICA_DATA_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_LINEAR  ) )  \
        ? 1 : 0 )

#define PICA_CMD_DATA_TEXTURE_MIN_FILTER1(texture0MinFilter) \
    ( ( ( (texture0MinFilter) == PICA_DATA_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_LINEAR ) || \
        ( (texture0MinFilter) == PICA_DATA_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_LINEAR  ) )  \
        ? 1 : 0 )

/* Please see man pages for details 
    
           
           
*/
enum PicaDataTextureWrap
{
    //
    PICA_DATA_TEXTURE_WRAP_CLAMP_TO_EDGE   = 0,
    //
    PICA_DATA_TEXTURE_WRAP_CLAMP_TO_BORDER = 1,
    //
    PICA_DATA_TEXTURE_WRAP_REPEAT          = 2,
    //
    PICA_DATA_TEXTURE_WRAP_MIRRORED_REPEAT = 3
};


#define PICA_CMD_DATA_TEXTURE_WRAP_FILTER( textureMagFilter, textureMinFilter, \
    textureFormat, textureWrapT, textureWrapS, \
    useShadowTexture, textureSamplerType )     \
    (  (textureMagFilter)                                                         <<  1 | \
       PICA_CMD_DATA_TEXTURE_MIN_FILTER0(textureMinFilter)                        <<  2 | \
      ((textureFormat == PICA_DATA_TEXTURE_FORMAT_ETC1_RGB8_NATIVE_DMP) ? 2 : 0 ) <<  4 | \
       (textureWrapT)                                                             <<  8 | \
       (textureWrapS)                                                             << 12 | \
       0                                                                          << 16 | \
       (useShadowTexture)                                                         << 20 | \
       PICA_CMD_DATA_TEXTURE_MIN_FILTER1(textureMinFilter)                        << 24 | \
       (textureSamplerType) << 28 )

#define PICA_CMD_DATA_TEXTURE0_WRAP_FILTER( textureMagFilter, textureMinFilter,        \
                                            textureFormat, textureWrapT, textureWrapS, \
                                            useShadowTexture, textureSamplerType )     \
    PICA_CMD_DATA_TEXTURE_WRAP_FILTER( textureMagFilter, textureMinFilter,             \
                                       textureFormat, textureWrapT, textureWrapS,      \
                                       useShadowTexture, textureSamplerType )

#define PICA_CMD_DATA_TEXTURE1_WRAP_FILTER( textureMagFilter, textureMinFilter,    \
                                        textureFormat, textureWrapT, textureWrapS) \
    PICA_CMD_DATA_TEXTURE_WRAP_FILTER( textureMagFilter, textureMinFilter,         \
                                       textureFormat, textureWrapT, textureWrapS,  \
                                       0x0, 0x0)

#define PICA_CMD_DATA_TEXTURE2_WRAP_FILTER( textureMagFilter, textureMinFilter,     \
                                        textureFormat, textureWrapT, textureWrapS ) \
    PICA_CMD_DATA_TEXTURE_WRAP_FILTER( textureMagFilter, textureMinFilter,          \
                                       textureFormat, textureWrapT, textureWrapS,   \
                                       0x0, 0x0)

/*
struct CommandTex12WrapFilter
{
    CMD_PADDING(1);
    u32 magFilter  : 1;
    u32 minFilter1 : 1;
    CMD_PADDING(1);
    u32 isETC1    : 2;
    CMD_PADDING(2);
    u32 wrapT     : 3;
    CMD_PADDING(1);
    u32 wrapS     : 3;
    CMD_PADDING(2);       // set to 0 [17:16]
    CMD_PADDING(7);
    u32 minFilter2 : 1;
    CMD_PADDING(7);
};
*/

///////////////////////////////////
// Texture LOD Level
// Texture LOD Bias
/*
struct CommandTexLODLev
{
    u32 bias : 12;
    u32 max : 4;
    CMD_PADDING(4);
    u32 min : 4;
    CMD_PADDING(4);
};
*/

// PICA_REG_TEXTURE0_LOD         0x084
// PICA_REG_TEXTURE1_LOD         0x094
// PICA_REG_TEXTURE2_LOD         0x09c
#define PICA_CMD_DATA_TEXTURE_LOD_LEVEL(lodBias, maxLodLevel, minLodLevel) \
    (  (lodBias)                              | \
       (maxLodLevel)                    << 16 | \
      (((minLodLevel) < 0) ? 0 : (minLodLevel)) << 24 )

///////////////////////////////////
// Texture Border Color

// PICA_REG_TEXTURE0_BORDER_COLOR  0x081
// PICA_REG_TEXTURE1_BORDER_COLOR  0x091
// PICA_REG_TEXTURE2_BORDER_COLOR  0x099
#define PICA_CMD_DATA_BORDER_COLOR( color8 ) \
    ( (color8.r)       | \
      (color8.g) <<  8 | \
      (color8.b) << 16 | \
      (color8.a) << 24 )

/*  

*/

#endif  // NN_GX_CTR_PICA_MACRO_TEXTURE_H_
