/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_FragmentLight.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_FragmentLight.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            bit32* FragmentLight::Source::MakeAllCommand( bit32* command ) const
            {
                bit32 reg = PICA_REG_FRAG_LIGHT_START + id * PICA_FRAG_LIGHT_STRIDE;

                *command++ = specular0B | specular0G << 10 | specular0R << 20;     // specular0
                *command++ = PICA_CMD_HEADER_BURSTSEQ( reg, 12 );                  // Header
                *command++ = specular1B | specular1G << 10 | specular1R << 20;     // specular1
                *command++ = diffuseB   | diffuseG   << 10 | diffuseR   << 20;     // Diffuse
                *command++ = ambientB   | ambientG   << 10 | ambientR   << 20;     // Ambient   
                *command++ = posXY;
                *command++ = posZ;
                *command++ = spotDirectionXY;
                *command++ = spotDirectionZ;
                *command++ = 0;
                *command++ = isInfinity | ( isEnableTwoSideDiffuse ? 1 : 0 ) << 1 |
                             ( isEnableGeomFactor0 ? 1 : 0 ) << 2 | ( isEnableGeomFactor1 ? 1 : 0 ) << 3;
                *command++ = distAttnBias;
                *command++ = distAttnScale;
                *command++ = 0;

                return command;
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::Source::MakeCommand( bit32* command ) const
            {
                return MakeAllCommand( command );
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::Source::MakeColorCommand( bit32* command ) const
            {
                bit32 reg = PICA_REG_FRAG_LIGHT_START + id * PICA_FRAG_LIGHT_STRIDE;

                *command++ = specular0B | specular0G << 10 | specular0R << 20; // specular0
                *command++ = PICA_CMD_HEADER_BURSTSEQ( reg, 4 );               // Header

                *command++ = specular1B | specular1G << 10 | specular1R << 20; // specular1
                *command++ = diffuseB   | diffuseG   << 10 | diffuseR   << 20; // Diffuse

                *command++ = ambientB   | ambientG   << 10 | ambientR   << 20; // Ambient
                *command++ = 0;
                
                return command;
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::Source::MakeGeometryCommand( bit32* command ) const
            {
                bit32 reg = PICA_REG_FRAG_LIGHT_START + id * PICA_FRAG_LIGHT_STRIDE + 0x4;
                                
                *command++ = posXY;
                *command++ = PICA_CMD_HEADER_BURSTSEQ( reg, 8 );

                *command++ = posZ;
                *command++ = spotDirectionXY;    

                *command++ = spotDirectionZ;
                *command++ = 0;

                *command++ = isInfinity                              | 
                             ( isEnableTwoSideDiffuse ? 1 : 0 ) << 1 |
                             ( isEnableGeomFactor0 ? 1 : 0 )    << 2 | 
                             ( isEnableGeomFactor1 ? 1 : 0 )    << 3;
                *command++ = distAttnBias;

                *command++ = distAttnScale;
                *command++ = 0;

                return command;
            }

            //------------------------------------------------------------------------------

            FragmentLight::Source::Source()
                : id( 0 ),
                  isEnableTwoSideDiffuse( false ),
                  isEnableGeomFactor0( false ),
                  isEnableGeomFactor1( false ),
                  diffuseR( 255 ),
                  diffuseG( 255 ),
                  diffuseB( 255 ),
                  ambientR(   0 ),
                  ambientG(   0 ),
                  ambientB(   0 ),
                  specular0R( 255 ),
                  specular0G( 255 ),
                  specular0B( 255 ),
                  specular1R( 255 ),
                  specular1G( 255 ),
                  specular1B( 255 ),
                  posXY( 0 ),
                  posZ( 0 ),
                  isInfinity( 0 ),
                  distAttnBias( 0 ),
                  distAttnScale( 0 ),
                  spotDirectionXY( 0 ),
                  spotDirectionZ( 0 )
            {
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::MakeLutConfigCommand( bit32* command ) const
            {
                // 0x1d0
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_ABSLUTINPUT(
                    lutConfigD0.isAbs,
                    lutConfigD1.isAbs,
                    lutConfigSP.isAbs,
                    lutConfigFR.isAbs,
                    lutConfigRB.isAbs,
                    lutConfigRG.isAbs,
                    lutConfigRR.isAbs );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_ABSLUTINPUT );

                // 0x1d1
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_LUTINPUT(
                    lutConfigD0.input,
                    lutConfigD1.input,
                    lutConfigSP.input,
                    lutConfigFR.input,
                    lutConfigRB.input,
                    lutConfigRG.input,
                    lutConfigRR.input );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_LUTINPUT );

                // 0x1d2
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_LUTSCALE(
                    lutConfigD0.scale,
                    lutConfigD1.scale,
                    lutConfigSP.scale,
                    lutConfigFR.scale,
                    lutConfigRB.scale,
                    lutConfigRG.scale,
                    lutConfigRR.scale );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_LUTSCALE );

                return command;
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::MakeLightEnvCommand( bit32* command, bool isAddDummyCommand ) const
            {
                bit32 regLightEnable     = 0xff00ffff;
                bit32 regLightEnableEach = 0;
                s32 count = 0;

                regLightEnable |= PICA_CMD_DATA_FRAG_LIGHT_FUNC_MODE1_LUT(
                    isEnableLutD0,
                    isEnableLutD1,
                    fresnelSelector,
                    isEnableLutRefl );
                    
                for ( int i = 0; i < LIGHT_SOURCE_MAX; ++i )
                {
                    if ( isEnable[ i ] == false )
                    {
                        continue;
                    }

                    if ( isShadowed[ i ] )
                    {
                        regLightEnable &= ~( 1 << i );
                    }

                    if ( isEnableSpot[ i ] )
                    {
                        regLightEnable &= ~( 1 << ( 8 + i ) );
                    }

                    if ( isEnableDistAttn[ i ] )
                    {
                        regLightEnable &= ~( 1 << ( 24 + i ) );
                    }

                    regLightEnableEach |= ( i << ( count++ * 4 ) );
                }

                // Before converting 0x08f, send dummy command
                if ( isAddDummyCommand )
                {
                    *command++ = 0x0;
                    *command++ = PICA_CMD_HEADER_BURST_BE( PICA_REG_TEXTURE_FUNC, 0x3, 0x0 );
                    *command++ = 0x0;
                    *command++ = 0x0;
                }

                // Set whether the 0x08f light is enabled or disabled
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_EN( count );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_EN0 );

                // 0x1c0 global ambient settings
                *command++ = globalAmbientB | globalAmbientG << 10 | globalAmbientR << 20;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_AMBIENT );

                // 0x1c2 number of light source setting
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_NUM( count );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_SRC_NUM );

                // 0x1c3
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_FUNC_MODE0(
                    fresnelSelector,
                    layerConfig,
                    isEnableShadowPrimary,
                    isEnableShadowSecondary,
                    isInvertShadow,
                    isEnableShadowAlpha,
                    bumpSelector,
                    shadowSelector,
                    isEnableClampHighLights,
                    bumpMode,
                    isEnableBumpRenorm );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_FUNC_MODE0 );

                // 0x1c4
                *command++ = regLightEnable;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_FUNC_MODE1 );

                // Set whether the 0x1c6 light is enabled or disabled
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_EN_INV( count );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_EN1 );

                // 0x1d9
                *command++ = regLightEnableEach;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_SRC_EN_ID );
                return command;
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::MakeLightSourceCommand( bit32* command ) const
            {
                // Sets for each light source
                for ( int i = 0; i < LIGHT_SOURCE_MAX; ++i )
                {
                    if ( isEnable[ i ] == false ) continue;

                    command = source[ i ].MakeCommand( command );
                }

                return command;
            }

            //------------------------------------------------------------------------------

            bit32* FragmentLight::MakeAllCommand( bit32* command, bool isAddDummyCommand ) const
            {
            #if defined( NN_GR_FRAGMENT_LIGHT_DUMP ) // For debugging
                bit32 * start = command;
            #endif

                command = MakeLutConfigCommand( command );

                command = MakeLightEnvCommand( command, isAddDummyCommand );

                command = MakeLightSourceCommand( command );


            #if defined( NN_GR_FRAGMENT_LIGHT_DUMP ) // For debugging
                static int a = 0;
                if ( ++a == 10 )
                {
                    for ( u32* i = start; i != command; i +=2 )
                    {
                        NN_LOG( "0x%08x 0x%08x\n", *i, *(i+1) );
                    }
                }
            #endif
                
                return command;
            }

                //------------------------------------------------------------------------------

            bit32* FragmentLight::MakeDisableCommand( bit32* command, bool isAddDummyCommand )
            {
                const u32 lightNum = 0;

                // Before converting 0x08f, send dummy command
                if ( isAddDummyCommand )
                {
                    *command++ = 0x0;
                    *command++ = PICA_CMD_HEADER_BURST_BE( PICA_REG_TEXTURE_FUNC, 0x3, 0x0 );

                    *command++ = 0x0;
                    *command++ = 0x0;
                }

                // Sets 0x08f light to disabled
                *command++ = 0;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_EN0 );

                // Sets 0x1c6 light to disabled     
                *command++ = PICA_CMD_DATA_FRAG_LIGHT_EN_INV( lightNum );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_EN1 );
                
                // Sets the number of 0x1c2 light sources to 0
                *command++ = lightNum;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_SRC_NUM );

                return command;
            }

            //------------------------------------------------------------------------------

            FragmentLight::FragmentLight()
                : globalAmbientR( 0 ),
                  globalAmbientG( 0 ),
                  globalAmbientB( 0 ),
                  layerConfig( PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG0 ),
                  fresnelSelector( PICA_DATA_FRAG_LIGHT_ENV_NO_FRESNEL ),
                  shadowSelector( PICA_DATA_FRAG_LIGHT_ENV_TEXTURE0 ),
                  bumpMode( PICA_DATA_FRAG_LIGHT_ENV_BUMP_NOT_USED_DMP ),
                  bumpSelector( PICA_DATA_FRAG_LIGHT_ENV_TEXTURE0 ),
                  isEnableShadowPrimary( false ),
                  isEnableShadowSecondary( false ),
                  isEnableShadowAlpha( false ),
                  isInvertShadow( false ),
                  isEnableBumpRenorm( false ),
                  isEnableClampHighLights( true ),
                  isEnableLutD0( false ),
                  isEnableLutD1( false ),
                  isEnableLutRefl( true )
            {
                for ( int i = 0; i < LIGHT_SOURCE_MAX; ++i )
                {
                    isEnable[ i ]         = false;
                    isEnableSpot[ i ]     = false;
                    isEnableDistAttn[ i ] = false;
                    isShadowed[ i ]       = false;
                    source[ i ].id        = i;
                }
            }

            //------------------------------------------------------------------------------

            FragmentLight::LutConfig::LutConfig()
                : input( PICA_DATA_FRAG_LIGHT_ENV_NH_DMP ),
                  isAbs( false ),
                  scale( PICA_DATA_FRAG_LIGHT_ENV_LUTSCALE_1_0 )
            {
            }

        } // namespace CTR
    } // namespace gr
} // namespace nn
