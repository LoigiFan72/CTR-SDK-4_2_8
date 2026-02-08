/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_ProcedureTexture.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_PROCEDURE_TEXTURE_H_
#define NN_GR_PROCEDURE_TEXTURE_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class ProcedureTexture
            {
            public:
                static const u32 PROCTEX_LOOKUP_TABLE_ELEMENT_NUM       = 128; //
                static const u32 PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM = 256; //

            public :
                /* Please see man pages for details 
                    
                           
                           
                */
                PicaDataProcTexMap rgbMap;

                /* Please see man pages for details 
                    
                           
                           
                */

                PicaDataProcTexMap alphaMap;

                /* Please see man pages for details 
                    
                           
                           
                */
                bool alphaSeparate;

                /* Please see man pages for details 
                    
                           
                           
                */
                PicaDataProcTexClamp clampU;

                /* Please see man pages for details 
                    
                           
                           
                */
                PicaDataProcTexClamp clampV;

                /* Please see man pages for details 
                    
                           
                           
                */
                PicaDataProcTexShift shiftU;

                /* Please see man pages for details 
                    
                           
                           
                */
                PicaDataProcTexShift shiftV;

                /* Please see man pages for details 
                    
                           
                           
                */
                PicaDataProcTexFilter minFilter;

                /* Please see man pages for details 
                    
                           
                           
                */
                f32 texBias;

                /* Please see man pages for details 
                    
                           
                           
                */
                u8  texOffset;

                /* Please see man pages for details 
                    
                           
                           
                */
                u8  texWidth;

                /* Please see man pages for details 
                    
                           
                           
                */
                bool isEnableNoise;
                NN_PADDING1;
                
                /* Please see man pages for details 
                    
                           
                           
                */
                f32 noiseUAmplitude;

                /* Please see man pages for details 
                    
                           
                           
                */
                f32 noiseVAmplitude;

                /* Please see man pages for details 
                    
                           
                           
                */
                f32 noiseUFrequency;

                /* Please see man pages for details 
                    
                           
                           
                */
                f32 noiseVFrequency;

                /* Please see man pages for details 
                    
                           
                           
                */
                f32 noiseUPhase;

                /* Please see man pages for details 
                    
                           
                           
                */
                f32 noiseVPhase;

            public :                
                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void SetNoiseLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const u32 lookUpTableIndex = 0,
                                          const f32 lastDiffValue    = 0.0f );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void SetNoiseLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void SetRgbMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                           const u32 lookUpTableIndex = 0,
                                           const f32 lastDiffValue    = 0.0f );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void SetRgbMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                           const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                           const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void SetAlphaMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                             const u32 lookUpTableIndex = 0,
                                             const f32 lastDiffValue    = 0.0f );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void SetAlphaMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                             const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                             const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                */
                void SetRedLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                        const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                */
                void SetRedLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                        const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                        const u32 lookUpTableIndex = 0,
                                        const u32 diffLookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                */
                void SetGreenLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                */
                void SetGreenLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const u32 lookUpTableIndex = 0,
                                          const u32 diffLookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                */
                void SetBlueLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                         const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                */
                void SetBlueLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                         const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                         const u32 lookUpTableIndex = 0,
                                         const u32 diffLookUpTableIndex = 0 );

               /* Please see man pages for details 
                    
                    
                    
                    
                */
                void SetAlphaLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                */
                void SetAlphaLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                          const u32 lookUpTableIndex = 0,
                                          const u32 diffLookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                 
*/
                bit32* MakeAllCommand( bit32* command, bool isAddDummyCommand = true ) const
                {
                    // Set command
                    command = MakeConfigCommand( command, isAddDummyCommand );
                    
                    // Procedural texture lookup table command 
                    command = MakeTableCommand( command ); 

                    return command;
                }

                /* Please see man pages for details 
                    
                   
                    
                    
                    
                 
*/
                bit32* MakeConfigCommand( bit32* command, bool isAddDummyCommand = true ) const
                {                                        
                    command = MakeProcedureTextureModeCommand( command, isAddDummyCommand );
                    command = MakeTextureCommand( command, false, false );
                    command = MakeNoiseCommand( command, false, false );

                    return command;
                }

                /* Please see man pages for details 
                    
                   
                    
                    
                    
                 
*/
                bit32* MakeProcedureTextureModeCommand( bit32* command, bool isAddDummyCommand = true ) const
                {
                    if ( isAddDummyCommand )
                    {
                        command = MakeDummyCommand( command );
                    }

                    // f32 -> f16 
                    u16 texBiasFloat16 = Float32ToFloat16( texBias );
                    u8  texBiasFloat16Low8 = ( texBiasFloat16          & 0xFF );
             
                    // 0x0a8
                    *command++ = PICA_CMD_DATA_PROCTEX0( clampU, clampV,
                                                         rgbMap, alphaMap,
                                                         ( alphaSeparate ? 1 : 0),
                                                         ( isEnableNoise ? 1 : 0 ),
                                                         shiftU, shiftV,
                                                         texBiasFloat16Low8 );
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_TEXTURE3_PROCTEX0 );

                    return command;
                }

                /* Please see man pages for details 
                    
                   
                    
                    
                    
                    
                 
*/
                bit32* MakeTextureCommand( bit32* command, bool isAddProcedureTextureModeCommand = true, bool isAddDummyCommand = true ) const
                {
                    if ( isAddProcedureTextureModeCommand )
                    {
                        command = MakeProcedureTextureModeCommand( command, isAddDummyCommand );
                    }
                    else if ( isAddDummyCommand )
                    {
                        command = MakeDummyCommand( command );
                    }

                    // f32 -> f16 
                    u16 texBiasFloat16 = Float32ToFloat16( texBias );
                    u8  texBiasFloat16Hi8 =  ( ( texBiasFloat16 >> 8 ) & 0xFF );

                    // 0x0ac
                    *command++ = PICA_CMD_DATA_PROCTEX4( minFilter, texWidth, texBiasFloat16Hi8 );
                    *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_TEXTURE3_PROCTEX4, 0x2 );

                    // 0x0ad
                    *command++ = PICA_CMD_DATA_PROCTEX5( texOffset );
                    // Padding
                    *command++ = 0x0;

                    return command;
                }
                
                /* Please see man pages for details 
                    
                   
                    
                    
                    
                    
                 
*/
                bit32* MakeNoiseCommand( bit32* command, bool isAddProcedureTextureModeCommand = true, bool isAddDummyCommand = true ) const
                {
                    if ( isAddProcedureTextureModeCommand )
                    {
                        command = MakeProcedureTextureModeCommand( command, isAddDummyCommand );
                    }     
                    else if ( isAddDummyCommand )
                    {
                        command = MakeDummyCommand( command );
                    }
                    
                    // 0x0a9
                    *command++ = PICA_CMD_DATA_PROCTEX1( Float32ToFloat16( noiseUPhase ),
                                                         Float32ToFix16( noiseUAmplitude ) );
                    *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_TEXTURE3_PROCTEX1, 0x3 );

                    // 0x0aa
                    *command++ = PICA_CMD_DATA_PROCTEX2( Float32ToFloat16( noiseVPhase ),
                                                         Float32ToFix16( noiseVAmplitude ) );
                    // 0x0ab
                    *command++ = PICA_CMD_DATA_PROCTEX3( Float32ToFloat16( noiseUFrequency ), 
                                                         Float32ToFloat16( noiseVFrequency ) );

                    return command;
                }

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                 */
                bit32* MakeTableCommand( bit32* command ) const;
                
 
                /* Please see man pages for details 
                    
                   
                    
                    
                    
                 */
                static bit32* MakeDummyCommand( bit32* command )
                {
                    *command++ = 0x0;
                    *command++ = PICA_CMD_HEADER_BURST_BE( PICA_REG_TEXTURE_FUNC, 0x3, 0x0 );

                    *command++ = 0x0;
                    *command++ = 0x0;

                    return command;
                }

            public :
                /* Please see man pages for details 
                    
                */
                ProcedureTexture() : 
                   rgbMap( PICA_DATA_PROCTEX_U_DMP ),
                   alphaMap( PICA_DATA_PROCTEX_U_DMP ),
                   alphaSeparate( false ),
                   clampU( PICA_DATA_PROCTEX_CLAMP_TO_EDGE ), clampV( PICA_DATA_PROCTEX_CLAMP_TO_EDGE ),
                   shiftU( PICA_DATA_PROCTEX_NONE_DMP ), shiftV( PICA_DATA_PROCTEX_NONE_DMP ), 
                   minFilter( PICA_DATA_PROCTEX_LINEAR ),
                   texBias( 0.5f ), texOffset( 0 ), texWidth( 0 ),
                   isEnableNoise( false ),
                   noiseUAmplitude( 0.0f ), noiseVAmplitude( 0.0f ),
                   noiseUFrequency( 0.0f ), noiseVFrequency( 0.0f ),
                   noiseUPhase( 0.0f ), noiseVPhase( 0.0f )
                   {
                   }

            protected:
                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                
*/
                void SetLookUpDualTables_( bit32* command, 
                                           PicaDataProcTexRefTable procTexLookUpTable, 
                                           const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                           const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                           const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                
*/
                void SetColorLookUpDualTables_( const u32 colorShiftNum,
                                                const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                                const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                
*/
                void SetColorLookUpTable_( const u32 colorShiftNum,
                                           const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                           const u32 lookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                
*/
                void SetColorDiffLookUpTable_( const u32 colorShiftNum,
                                               const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                               const u32 diffLookUpTableIndex = 0 );

                /* Please see man pages for details 
                    
                    
                    
                    
                */
                void GetColorDiffLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                              f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ] );
            
                /* Please see man pages for details 
                    
                    
                    
                    
                    
                */
                void GetDiffLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                         f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                         const f32 lastDiffValue = 0.0f );

            protected :
                //
                static const u32  PROCTEX_LOOKUP_TABLE_OPTION_CMD_NUM      = 4;

                //
                static const u32 PROCTEX_LOOKUP_TABLE_CMD_NUM              = PROCTEX_LOOKUP_TABLE_ELEMENT_NUM  + PROCTEX_LOOKUP_TABLE_OPTION_CMD_NUM;

                //
                static const u32 PROCTEX_COLOR_LOOKUP_TABLE_OPTION_CMD_NUM = 6;

                //
                static const u32 PROCTEX_COLOR_LOOKUP_TABLE_CMD_NUM        = PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM + PROCTEX_COLOR_LOOKUP_TABLE_OPTION_CMD_NUM;

                /* Please see man pages for details 
                    
                */
                enum ProcedureTextureColorShift
                {
                    //
                    PROCTEX_RED_COLOR_SHIFT_NUM   =  0,
                    //
                    PROCTEX_GREEN_COLOR_SHIFT_NUM =  8,
                    //
                    PROCTEX_BLUE_COLOR_SHIFT_NUM  = 16,
                    //
                    PROCTEX_ALPHA_COLOR_SHIFT_NUM = 24
                };

                /* Please see man pages for details 
                    
                           
                */
                u32 m_NoiseLookUpTableCommand[ PROCTEX_LOOKUP_TABLE_CMD_NUM ];

                /* Please see man pages for details 
                    
                           
                */
                u32 m_RgbMapLookUpTableCommand[ PROCTEX_LOOKUP_TABLE_CMD_NUM ];

                /* Please see man pages for details 
                    
                           
                */
                u32 m_AlphaMapLookUpTableCommand[ PROCTEX_LOOKUP_TABLE_CMD_NUM ];

                /* Please see man pages for details 
                    
                           
                */
                u32 m_ColorLookUpTableCommand[ PROCTEX_COLOR_LOOKUP_TABLE_CMD_NUM ];

                /* Please see man pages for details 
                    
                           
                */
                u32 m_ColorDiffLookUpTableCommand[ PROCTEX_COLOR_LOOKUP_TABLE_CMD_NUM ];
            };

        } // namespace CTR
    } // namespace gr
} //namespace nn

#endif // NN_GR_PROCEDURE_TEXTURE_H_
