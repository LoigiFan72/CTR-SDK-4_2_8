/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_ProcedureTexture.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_ProcedureTexture.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            void ProcedureTexture::SetNoiseLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const u32 lookUpTableIndex,
                                                        const f32 lastDiffValue )
            {
                f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ];
                GetDiffLookUpTable( lookUpTable, diffLookUpTable, lastDiffValue );
                
                SetNoiseLookUpTable( lookUpTable, diffLookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetNoiseLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const u32 lookUpTableIndex )
            {
                SetLookUpDualTables_( m_NoiseLookUpTableCommand, PICA_DATA_PROCTEX_NOISE_REF_TABLE,
                                      lookUpTable, diffLookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetRgbMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                         const u32 lookUpTableIndex,
                                                         const f32 lastDiffValue )
            {
                f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ];
                GetDiffLookUpTable( lookUpTable, diffLookUpTable, lastDiffValue );
            
                SetRgbMapLookUpTable( lookUpTable, diffLookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetRgbMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                         const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                         const u32 lookUpTableIndex )
            {
                SetLookUpDualTables_( m_RgbMapLookUpTableCommand, PICA_DATA_PROCTEX_RGB_MAP_REF_TABLE, 
                                   lookUpTable, diffLookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetAlphaMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                           const u32 lookUpTableIndex,
                                                           const f32 lastDiffValue )
            {
                f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ];
                GetDiffLookUpTable( lookUpTable, diffLookUpTable, lastDiffValue );

                SetAlphaMapLookUpTable( lookUpTable, diffLookUpTable, lookUpTableIndex );
            }

             void ProcedureTexture::SetAlphaMapLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                            const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                            const u32 lookUpTableIndex )
            {
                SetLookUpDualTables_( m_AlphaMapLookUpTableCommand, PICA_DATA_PROCTEX_ALPHA_MAP_REF_TABLE, 
                                   lookUpTable, diffLookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetRedLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                      const u32 lookUpTableIndex )
            {
                SetColorLookUpDualTables_( PROCTEX_RED_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
            }
         
            void ProcedureTexture::SetRedLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                      const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                      const u32 lookUpTableIndex, const u32 diffLookUpTableIndex )
            {
                SetColorLookUpTable_( PROCTEX_RED_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
                SetColorDiffLookUpTable_( PROCTEX_RED_COLOR_SHIFT_NUM, diffLookUpTable, diffLookUpTableIndex );
            }

            void ProcedureTexture::SetGreenLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const u32 lookUpTableIndex )
            {
                SetColorLookUpDualTables_( PROCTEX_GREEN_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetGreenLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const u32 lookUpTableIndex, const u32 diffLookUpTableIndex )
            {
                SetColorLookUpTable_( PROCTEX_GREEN_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
                SetColorDiffLookUpTable_( PROCTEX_GREEN_COLOR_SHIFT_NUM, diffLookUpTable, diffLookUpTableIndex );
            }
 
            void ProcedureTexture::SetBlueLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                       const u32 lookUpTableIndex )
            {
                SetColorLookUpDualTables_( PROCTEX_BLUE_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetBlueLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                       const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                       const u32 lookUpTableIndex, const u32 diffLookUpTableIndex )
            {
                SetColorLookUpTable_( PROCTEX_BLUE_COLOR_SHIFT_NUM, lookUpTable,  lookUpTableIndex );
                SetColorDiffLookUpTable_( PROCTEX_BLUE_COLOR_SHIFT_NUM, diffLookUpTable,  diffLookUpTableIndex );
            }
            
            void ProcedureTexture::SetAlphaLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const u32 lookUpTableIndex )
            {
                SetColorLookUpDualTables_( PROCTEX_ALPHA_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetAlphaLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                        const u32 lookUpTableIndex, const u32 diffLookUpTableIndex )
            {                
                SetColorLookUpTable_( PROCTEX_ALPHA_COLOR_SHIFT_NUM, lookUpTable, lookUpTableIndex );
                SetColorDiffLookUpTable_( PROCTEX_ALPHA_COLOR_SHIFT_NUM, diffLookUpTable, diffLookUpTableIndex );
            }
         
            bit32* ProcedureTexture::MakeTableCommand( bit32* command ) const
            {
                if ( isEnableNoise )
                {
                    std::memcpy( command, m_NoiseLookUpTableCommand, sizeof( m_NoiseLookUpTableCommand ) );
                    command += PROCTEX_LOOKUP_TABLE_CMD_NUM;
                }
                
                std::memcpy( command, m_RgbMapLookUpTableCommand, sizeof( m_RgbMapLookUpTableCommand ) );
                command += PROCTEX_LOOKUP_TABLE_CMD_NUM;

                if ( alphaSeparate )
                {
                    std::memcpy( command, m_AlphaMapLookUpTableCommand, sizeof( m_AlphaMapLookUpTableCommand ) );
                    command += PROCTEX_LOOKUP_TABLE_CMD_NUM;
                }

                std::memcpy( command, m_ColorLookUpTableCommand, sizeof( m_ColorLookUpTableCommand ) );
                command += PROCTEX_COLOR_LOOKUP_TABLE_CMD_NUM;

                std::memcpy( command, m_ColorDiffLookUpTableCommand, sizeof( m_ColorDiffLookUpTableCommand ) );
                command += PROCTEX_COLOR_LOOKUP_TABLE_CMD_NUM;
                
                return command;
            }
       
            void ProcedureTexture::SetLookUpDualTables_( bit32* command, PicaDataProcTexRefTable procTexLookUpTable,
                                                         const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                         const f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                         const u32 lookUpTableIndex )
            {              
                *command++ = PICA_CMD_DATA_PROCTEX_LUT( lookUpTableIndex, procTexLookUpTable );
                
                // 0xaf
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_PROCTEX_LUT );
             
                u32 index = 0;
                // [11: 0] Converts to a 12-bit fixed-point number (the decimal part is unsigned 12 bits)
                // [23:12] Converts to a 12-bit fixed-point number (the decimal part is signed 12 bits)
                *command++ = Float32ToUnsignedFix12( lookUpTable[ index ] ) | 
                             ( Float32ToFix12Fraction11( diffLookUpTable[ index ] ) << 12 );
                
                *command++ = PICA_CMD_HEADER_BURST( PICA_REG_PROCTEX_LUT_DATA0, 0x80 );

                for ( index = 1; index < 0x80; index++ )
                {
                    // [11: 0] Converts to a 12-bit fixed-point number (the decimal part is unsigned 12 bits)
                    // [23:12] Converts to a 12-bit fixed-point number (the decimal part is signed 12 bits)
                    *command++ = Float32ToUnsignedFix12( lookUpTable[ index ] ) | 
                                 ( Float32ToFix12Fraction11( diffLookUpTable[ index ] ) << 12 );
                }

                // Padding
                *command++ = 0;
            }
        
            void ProcedureTexture::SetColorLookUpDualTables_( const u32 colorShiftNum,
                                                              const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                                              const u32 lookUpTableIndex )
            {
                // Sets the color reference table
                SetColorLookUpTable_( colorShiftNum, lookUpTable, lookUpTableIndex );

                // Sets the difference value for the color reference table.
                f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ];
                GetColorDiffLookUpTable( lookUpTable, diffLookUpTable );
                SetColorDiffLookUpTable_( colorShiftNum, diffLookUpTable, lookUpTableIndex );
            }

            void ProcedureTexture::SetColorLookUpTable_( const u32 colorShiftNum,
                                                         const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                                         const u32 lookUpTableIndex )
            {
                bit32* command = m_ColorLookUpTableCommand;

                *command++ = PICA_CMD_DATA_PROCTEX_LUT( lookUpTableIndex, PICA_DATA_PROCTEX_COLOR_REF_TABLE );
                // 0xaf
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_PROCTEX_LUT );
                
                u32 index = 0;
                bit32 clearMask = ~(0xff << colorShiftNum);
                for ( u32 burstIndex = 0; burstIndex < 2; burstIndex++ )
                {
                    // Converts from float32 to unsigned int8
                    *command   &= clearMask;
                    *command++ |= ( FloatToUnsignedByte( lookUpTable[ index ] ) << colorShiftNum );
                    index++;

                    // 0xb0
                    *command++ = PICA_CMD_HEADER_BURST( PICA_REG_PROCTEX_LUT_DATA0, 0x80 );

                    for ( u32 burstDataIndex = 0; burstDataIndex < 0x7F; burstDataIndex++ )
                    {
                        // Converts from float32 to unsigned int8
                        *command   &= clearMask;
                        *command++ |= ( FloatToUnsignedByte( lookUpTable[ index ] ) << colorShiftNum );
                        index++;
                    }

                    // Padding
                    *command++ = 0;
                }
            }

            void ProcedureTexture::SetColorDiffLookUpTable_( const u32 colorShiftNum,
                                                             const f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                                             const u32 diffLookUpTableIndex )
            {                
                bit32* command = m_ColorDiffLookUpTableCommand;

                *command++ = PICA_CMD_DATA_PROCTEX_LUT( diffLookUpTableIndex, PICA_DATA_PROCTEX_COLOR_DIFF_REF_TABLE );
                // 0xaf
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_PROCTEX_LUT );
                
                u32 index = 0;
                bit32 clearMask = ~(0xff << colorShiftNum);
                for ( u32 burstIndex = 0; burstIndex < 2; burstIndex++ )
                {
                    // Converts from float32 to signed fixed8 (7-bit fraction)
                    *command   &= clearMask;
                    *command++ |= ( ( Float32ToFix8Fraction7( diffLookUpTable[ index ] )) << colorShiftNum );
                    index++;

                    // 0xb0
                    *command++ = PICA_CMD_HEADER_BURST( PICA_REG_PROCTEX_LUT_DATA0, 0x80 );

                    for ( u32 burstDataIndex = 0; burstDataIndex < 0x7F; burstDataIndex++ )
                    {
                        // Converts from float32 to signed fixed8 (7-bit fraction)
                        *command   &= clearMask;
                        *command++ |= ( Float32ToFix8Fraction7( diffLookUpTable[ index ] ) << colorShiftNum );
                        
                        index++;
                    }

                    // Padding
                    *command++ = 0;
                }
            }

            void ProcedureTexture::GetColorDiffLookUpTable( const f32 lookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ],
                                                            f32 diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM ] )
            {
                for (u32 index = 0; index < ( PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM - 1); index++)
                {
                    diffLookUpTable[ index ] = lookUpTable[ index + 1 ] - lookUpTable[ index ];
                }

                // Since the last difference value in the procedural texture color reference table is not used, it is set to 0.0f.
                diffLookUpTable[ PROCTEX_COLOR_LOOKUP_TABLE_ELEMENT_NUM - 1 ] = 0.0f;
            }

            void ProcedureTexture::GetDiffLookUpTable( const f32 lookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                       f32 diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM ],
                                                       const f32 lastDiffValue )
            {
                for (u32 index = 0; index < ( PROCTEX_LOOKUP_TABLE_ELEMENT_NUM - 1); index++)
                {
                    diffLookUpTable[ index ] = lookUpTable[ index + 1 ] - lookUpTable[ index ];
                }

                diffLookUpTable[ PROCTEX_LOOKUP_TABLE_ELEMENT_NUM - 1 ] = lastDiffValue;
            }


        } // namespace CTR
    } // namespace gr
} // namespace nn
