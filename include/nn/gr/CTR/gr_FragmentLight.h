/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_FragmentLight.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_FRAGMENT_LIGHT_H_
#define NN_GR_FRAGMENT_LIGHT_H_

#include <nn/gr/CTR/gr_Utility.h>
#include <nn/gr/CTR/gr_LookUpTable.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class FragmentLight
            {
            public :
                /* Please see man pages for details 
                    
                 */
                class Source
                {
                public :

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 id;
                    
                    /* Please see man pages for details 
                        
                               
                    */
                    bool isEnableTwoSideDiffuse;

                    /* Please see man pages for details 
                        
                               
                    */
                    bool isEnableGeomFactor0;

                    /* Please see man pages for details 
                        
                               
                    */
                    bool isEnableGeomFactor1;

                    /* Please see man pages for details 
                        
                
                        
                    */
                    u8 diffuseR;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */    
                    u8 diffuseG;
                    
                    /* Please see man pages for details 
                        
                       
                               
                               
                    */
                    u8 diffuseB;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    u8 ambientR;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 ambientG;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 ambientB;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 specular0R;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 specular0G;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 specular0B;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    u8 specular1R;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    u8 specular1G;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    u8 specular1B;

                protected :
                    /* Please see man pages for details 
                        
                               
                    */
                    bit32  posXY;

                    /* Please see man pages for details 
                         
                                
                     */
                    bit32  posZ;

                    /* Please see man pages for details 
                         
                                
                     */
                    u8   isInfinity;
                    NN_PADDING3;

                    /* Please see man pages for details 
                         
                                
                     */
                    bit32 distAttnBias;

                    /* Please see man pages for details 
                         
                                
                     */
                    bit32 distAttnScale;

                    /* Please see man pages for details 
                         
                                
                     */
                    bit32 spotDirectionXY;

                    /* Please see man pages for details 
                         
                                
                     */
                    bit32 spotDirectionZ;


                public :

                    /* Please see man pages for details 
                        
                        
                        
                     
*/
                    void SetPosition( const nn::math::VEC3& position, const bool is_infinity )
                    {
                        posXY = PICA_CMD_DATA_FRAG_LIGHT_POSITION_XY( Float32ToFloat16( position.x ),
                                                                      Float32ToFloat16( position.y ) );
                        posZ  = PICA_CMD_DATA_FRAG_LIGHT_POSITION_Z(  Float32ToFloat16( position.z ) );
                        isInfinity = is_infinity ? 1 : 0;
                    }

                    /* Please see man pages for details 
                        
                        
                        
                        
                        
                     
*/
                    void SetPosition( const f32 position_x, const f32 position_y, const f32 position_z, const bool is_infinity )
                    {
                        posXY = PICA_CMD_DATA_FRAG_LIGHT_POSITION_XY( Float32ToFloat16( position_x ),
                                                                      Float32ToFloat16( position_y ) );
                        posZ  = PICA_CMD_DATA_FRAG_LIGHT_POSITION_Z(  Float32ToFloat16( position_z ) );
                        isInfinity = is_infinity ? 1 : 0;
                    }


                    /* Please see man pages for details 
                        
                        
                     
*/
                    void SetSpotDirection( const nn::math::VEC3& spot_direction )
                    {
                        spotDirectionXY = PICA_CMD_DATA_FRAG_LIGHT_SPOT_XY( Float32ToFix13Fraction11( -spot_direction.x ),
                                                                            Float32ToFix13Fraction11( -spot_direction.y ) );
                        spotDirectionZ  = PICA_CMD_DATA_FRAG_LIGHT_SPOT_Z(  Float32ToFix13Fraction11( -spot_direction.z ) );
                    }


                    /* Please see man pages for details 
                        
                        
                        
                        
                        
                     */
                    void SetSpotDirection( const f32& spot_direction_x, const f32& spot_direction_y, const f32& spot_direction_z )
                    {
                        spotDirectionXY = PICA_CMD_DATA_FRAG_LIGHT_SPOT_XY( Float32ToFix13Fraction11( - spot_direction_x ),
                                                                            Float32ToFix13Fraction11( - spot_direction_y ) );
                        spotDirectionZ  = PICA_CMD_DATA_FRAG_LIGHT_SPOT_Z(  Float32ToFix13Fraction11( - spot_direction_z ) );
                    }


                    /* Please see man pages for details 
                        
                        
                        
                        
                     */
                    void SetDistAttnScaleBias( const f32 scale, const f32 bias )
                    {
                        distAttnScale = Float32ToFloat20( scale );
                        distAttnBias  = Float32ToFloat20( bias );
                    };

                    /* Please see man pages for details 
                        
                     
                        
                        
                     */
                    void SetDistAttnStartEnd( const f32 start, const f32 end )
                    {
                        f32 r = 1.f / ( end - start );
                        SetDistAttnScaleBias( r, -start * r );
                    };

                public :
                    /* Please see man pages for details 
                        
                        
                        
                        
                     */
                    bit32* MakeAllCommand( bit32* command ) const;

                    /* Please see man pages for details 
                        
                               
                        
                        
                        
                     */
                    bit32* MakeCommand( bit32* command ) const;

                    /* Please see man pages for details 
                        
                        
                        
                        
                     */
                    bit32* MakeColorCommand( bit32* command ) const;

                    /* Please see man pages for details 
                        
                        
                        
                        
                     */
                    bit32* MakeGeometryCommand( bit32* command ) const;

                public :
                    /* Please see man pages for details 
                        
                    */
                    explicit Source();
                };

            public :
                //
                static const u32 LIGHT_SOURCE_MAX = 8;
                
                /* Please see man pages for details 
                    
                           
                           
                */
                // The value of dmp_FragmentMaterial.emission+dmp_FragmentMaterial.ambient×dmp_FragmentLighting.ambient [0.f, 1.f] is mapped to [0, 255] and set.
                //     
                u8 globalAmbientR;


                /* Please see man pages for details 
                    
                           
                           
                 */
                 // The value of dmp_FragmentMaterial.emission+dmp_FragmentMaterial.ambient×dmp_FragmentLighting.ambient [0.f, 1.f] is mapped to [0, 255] and set.
                 //
                u8 globalAmbientG;


                /* Please see man pages for details 
                    
                           
                           
                 */
                 // The value of dmp_FragmentMaterial.emission+dmp_FragmentMaterial.ambient×dmp_FragmentLighting.ambient [0.f, 1.f] is mapped to [0, 255] and set.
                 // 
                u8 globalAmbientB;
                NN_PADDING1;
                

                /* Please see man pages for details 
                    
                           
                */
                Source source[ LIGHT_SOURCE_MAX ];

                /* Please see man pages for details 
                    
                           
                           
                */
                bool isEnable[ LIGHT_SOURCE_MAX ];

                /* Please see man pages for details 
                    
                           
                           
                */
                bool isEnableSpot[ LIGHT_SOURCE_MAX ];

                /* Please see man pages for details 
                    
                           
                           
                */
                bool isEnableDistAttn[ LIGHT_SOURCE_MAX ];

                /* Please see man pages for details 
                    
                           
                           
                */
                bool isShadowed[ LIGHT_SOURCE_MAX ];
                              
                /* Please see man pages for details 
                    
                           
                */
                /*
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG0
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG1
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG2
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG3
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG4
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG5
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG6
                 PICA_DATA_FRAG_LIGHT_ENV_LAYER_CONFIG7
                 Set one of the above.
                 */
                PicaDataFragLightEnvLayerConfig layerConfig;

                /* Please see man pages for details 
                    
                           
                */
                /*
                 PICA_DATA_FRAG_LIGHT_ENV_NO_FRESNEL
                 PICA_DATA_FRAG_LIGHT_ENV_PRI_ALPHA_FRESNEL
                 PICA_DATA_FRAG_LIGHT_ENV_SEC_ALPHA_FRESNEL
                 PICA_DATA_FRAG_LIGHT_ENV_PRI_SEC_ALPHA_FRESNEL
                 Specify one of the above.
                 */
                PicaDataFragLightEnvFresnel  fresnelSelector;
            
                /* Please see man pages for details 
                    
                           
                */
                /*
                 PICA_DATA_FRAG_LIGHT_TEXTURE0
                 PICA_DATA_FRAG_LIGHT_TEXTURE1
                 PICA_DATA_FRAG_LIGHT_TEXTURE2
                 PICA_DATA_FRAG_LIGHT_TEXTURE3
                 Set one of the above.
                 */
                PicaDataFragLightEnvTexture     shadowSelector;

                /* Please see man pages for details 
                    
                           
                */
                /*
                 PICA_DATA_FRAG_LIGHT_ENV_BUMP_NOT_USED_DMP
                 PICA_DATA_FRAG_LIGHT_ENV_BUMP_AS_BUMP_DMP
                 PICA_DATA_FRAG_LIGHT_ENV_BUMP_AS_TANG_DMP
                 Set one of the above.
                 */
                PicaDataFragLightEnvBump        bumpMode;
             
                /* Please see man pages for details 
                    
                           
                */
                /*
                 PICA_DATA_FRAG_LIGHT_TEXTURE0
                 PICA_DATA_FRAG_LIGHT_TEXTURE1
                 PICA_DATA_FRAG_LIGHT_TEXTURE2
                 PICA_DATA_FRAG_LIGHT_TEXTURE3
                 Set one of the above.
                 */
                PicaDataFragLightEnvTexture     bumpSelector;

                /* Please see man pages for details 
                    
                           
                */
                bool                         isEnableShadowPrimary;

                /* Please see man pages for details 
                    
                           
                */
                bool                         isEnableShadowSecondary;

                /* Please see man pages for details 
                    
                           
                */
                bool                         isEnableShadowAlpha;

                /* Please see man pages for details 
                    
                           
                */
                bool                         isInvertShadow;

                /* Please see man pages for details 
                    
                           
                */
                bool                         isEnableBumpRenorm;

                /* Please see man pages for details 
                    
                           
                */
                bool                         isEnableClampHighLights;
    
                /* Please see man pages for details 
                    
                    
                    
                */
                /*
                 * If this flag is set to "true",
                 * if layer config is set to use D0, lookup table values are applied to the "distribution 0" term.
                 * If layer config is not set to use D0, 1 is used.
                 * If this flag is set to "false", 0 is used, regardless of the layer config settings.
                 * The default value is "false".
                 */
                bool                         isEnableLutD0;

                /* Please see man pages for details 
                    
                           
                           
                */
                /*
                 * If this flag is set to "true",
                 *If layer config is set to use D1, lookup table values are applied to the "distribution 1" term.
                 * if layer config is not set to use D1, 1 is used.
                 * If this flag is set to "false", 0 is used, regardless of the layer config settings.
                 * The default value is "false".
                 */
                bool                         isEnableLutD1;
                
                /* Please see man pages for details 
                    
                           
                           
                */
                /*
                 * If this flag is set to "true",
                 *if layer config is set to use RR, RG, and RB, then lookup table values are applied to the respective "reflection" terms.
                 * if layer config is not set to use RR, RG, and RB, then 1 is used.
                 * If this flag is set to "false", 0 is used, regardless of the layer config settings.
                 * The default value is "true".
                 */

                bool                         isEnableLutRefl;
                NN_PADDING2;



                /* Please see man pages for details 
                    
                */
                class LutConfig
                {
                public :
                    /* Please see man pages for details 
                        
                               
                    */
                    /*
                     Any of the following values can be set.
                     PICA_DATA_FRAG_LIGHT_ENV_NH_DMP
                     PICA_DATA_FRAG_LIGHT_ENV_VH_DMP
                     PICA_DATA_FRAG_LIGHT_ENV_NV_DMP
                     PICA_DATA_FRAG_LIGHT_ENV_LN_DMP
                     PICA_DATA_FRAG_LIGHT_ENV_SP_DMP
                     PICA_DATA_FRAG_LIGHT_ENV_CP_DMP
                      
                     */
                    PicaDataFragLightEnvLutInput input;
                    
                    /* Please see man pages for details 
                        
                               
                    */
                    /*
                     * Set to "true" to set the lookup table argument range to [0, 1]. Set to "false" to set the range to [-1, 1].
                     */
                    bool isAbs;
                    
                    /* Please see man pages for details 
                        
                            
                     */
                    PicaDataFragLightEnvLutScale scale;

                    NN_PADDING1;

                    /* Please see man pages for details 
                        
                    */
                    explicit LutConfig();
                };

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigD0;

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigD1;

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigSP;

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigFR;

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigRB;

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigRG;

                /* Please see man pages for details 
                    
                           
                */
                LutConfig lutConfigRR;
                    
            public :
                /* Please see man pages for details 
                    
                */
                FragmentLight();

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                 */
                bit32* MakeLightSourceCommand( bit32* command ) const;

                /* Please see man pages for details 
                    
                    
                    
                    
                 
*/
                bit32* MakeLutConfigCommand( bit32* command ) const;

                /* Please see man pages for details 
                    
                    
                    
                    
                 

*/
                bit32* MakeLightEnvCommand( bit32* command, bool isAddDummyCommand = true ) const;
                
                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                 */
                bit32* MakeAllCommand( bit32* command, bool isAddDummyCommand = true ) const;

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                 */
                static bit32* MakeDisableCommand( bit32* command, bool isAddDummyCommand = true );
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_FRAGMENT_LIGHT_H_
