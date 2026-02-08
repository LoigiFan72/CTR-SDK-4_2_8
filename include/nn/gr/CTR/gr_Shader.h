/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Shader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_SHADER_H_
#define NN_GR_SHADER_H_

#include <nn/gr/CTR/gr_Utility.h>
#include <nn/gr/CTR/gr_BindSymbol.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class Shader
            {
            public :
                /* Please see man pages for details 
                    
                */
                Shader( void );

                /* Please see man pages for details 
                    
                           
                           
                           
                           
                           

                    
                    
                    
                */
                void SetupBinary( const void* shader_binary, const s32 vtx_shader_index, const s32 geo_shader_index );


                /* Please see man pages for details 
                    
                           
                           
                           
                           
                           
                    
                    
                    
                */
                void SetShaderIndex( const s32 vtx_shader_index, const s32 geo_shader_index );
            
            public :
                /* Please see man pages for details 
                    
                    
                    
                    
                 */
                void SetUniformBool( const BindSymbolVSBool& symbol, bool isEnable )
                {
                    m_VtxShaderBoolMapUniform = ( m_VtxShaderBoolMapUniform & ~( 1 << symbol.start ) ) | ( ( isEnable ? 1 : 0 ) << symbol.start );
                }

                /* Please see man pages for details 
                    

                    
                    
                 */
                void SetUniformBool( const BindSymbolGSBool& symbol, bool isEnable )
                {
                    m_GeoShaderBoolMapUniform = ( m_GeoShaderBoolMapUniform & ~( 1 << symbol.start ) ) | ( ( isEnable ? 1 : 0 ) << symbol.start );
                }
                
                /* Please see man pages for details 
                    
                           

                    
                 */
                void SetDrawMode( const PicaDataDrawMode draw_mode )
                {
                    m_DrawMode = draw_mode;
                }

            public :
                /* Please see man pages for details 
                    
                           

                    

                    
                 */
                bit32* MakeFullCommand( bit32* command ) const;


                /* Please see man pages for details 
                    
                           
                           
                           

                    
                    

                    
                 */
                bit32* MakeShaderCommand( bit32* command, const bool isMakePrepareCommand = true ) const;

                /* Please see man pages for details 
                    

                    

                    
                 */
                static bit32* MakeDisableCommand( bit32* command );

            public :
                /* Please see man pages for details 
                    
                           
                 
                    

                    
                 */
                bit32* MakeVtxBoolMapCommand( bit32* command ) const
                {
                    *command++ = 0x7fff0000 | m_VtxShaderBoolMapUniform;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_BOOL ); // 0x2b0
                    return command;
                }
                
                /* Please see man pages for details 
                    
                           
                 
                    
                    
                 */
                bit32* MakeGeoBoolMapCommand( bit32* command ) const
                {
                    *command++ = 0x7fff0000 | m_GeoShaderBoolMapUniform;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_BOOL ); // 0x280
                    return command;
                }
                
                /* Please see man pages for details 
                    
                           
                           
                           
                    
                    
                 */
                bit32* MakePrepareCommand( bit32* command ) const;

                /* Please see man pages for details 
                    
                           
                           
                 
                    
                    
                 */
                bit32* MakeVtxProgramCommand( bit32* command ) const;

                /* Please see man pages for details 
                    
                           
                           

                    

                    
                 */
                bit32* MakeGeoProgramCommand( bit32* command ) const;
                
                /* Please see man pages for details 
                    
                           
                 
                    

                    
                 */
                bit32* MakeVtxSwizzleCommand( bit32* command ) const
                {
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_PROG_SWIZZLE_ADDR );
                    return MakeLoadCommand_( command, PICA_REG_VS_PROG_SWIZZLE_DATA0, m_Swizzle, m_SwizzleCount );
                }
                
                /* Please see man pages for details 
                    
                           

                    

                    
                 */
                bit32* MakeGeoSwizzleCommand( bit32* command ) const
                {
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_PROG_SWIZZLE_ADDR );
                    return MakeLoadCommand_( command, PICA_REG_GS_PROG_SWIZZLE_DATA0, m_Swizzle, m_SwizzleCount );
                }

                /* Please see man pages for details 
                    
                           
                 
                    

                    
                 */
                bit32* MakeVtxConstRgCommand( bit32* command ) const
                {
                    std::memcpy( command, m_CmdCacheConstArray[ m_VtxShaderIndex ],
                                 m_CmdCacheConstNumArray[ m_VtxShaderIndex ] * sizeof( bit32 ) );
                    return command + m_CmdCacheConstNumArray[ m_VtxShaderIndex ];
                }
                
                /* Please see man pages for details 
                    
                           
                 
                    

                    
                 */
                bit32* MakeGeoConstRgCommand( bit32* command ) const
                {
                    std::memcpy( command, m_CmdCacheConstArray[ m_GeoShaderIndex ], 
                                 m_CmdCacheConstNumArray[ m_GeoShaderIndex ] * sizeof( bit32 ) );        
                    return command + m_CmdCacheConstNumArray[ m_GeoShaderIndex ];
                }

                /* Please see man pages for details 
                    
                           
                 
                    

                    
                 */
                bit32* MakeOutAttrCommand( bit32* command ) const
                {
                    // If the geometry shader mode and render mode do not match, ASSERT
                    NN_GR_ASSERT( ( ! IsEnableGeoShader() ) || ( m_DrawMode == PICA_DATA_DRAW_GEOMETRY_PRIMITIVE ) );

                    // Generate commands based on the triangle's render mode
                    // 0x229 [8:8]
                    bit32 value_229 = 0x0100;
                    if ( m_DrawMode != PICA_DATA_DRAW_TRIANGLES )
                    {
                        value_229 = 0x0;
                    }
                    *command++ = value_229;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE0, 0x2 );

                    // 0x253 [8:8]
                    bit32 value_253 = 0x0100;
                    if ( m_DrawMode != PICA_DATA_DRAW_TRIANGLES )
                    {
                        value_253 = 0x0;
                    }
                    *command++ = value_253;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE1, 0x2 );

                    std::memcpy( command, m_CmdCacheOutAttrArray,
                                 m_CmdCacheOutAttrNum * sizeof( bit32 ) );

                    return command + m_CmdCacheOutAttrNum;
                }

            public : // Get information from the binary
                /* Please see man pages for details 
                   
                         
                          
                          

                 
                 

                 
                 */
                bool SearchBindSymbol(
                    BindSymbol*      symbol,
                    const char*      name ) const;

                 /* Please see man pages for details 
                    
                           
                           
                           
                    
                    
                    

                    
                 */
                u32  SearchBindSymbolNum(
                    const BindSymbol::ShaderType shader_type,
                    const BindSymbol::SymbolType symbol_type ) const;
           
                /* Please see man pages for details 
                   
                          
                          
                          
                          

                   
                   

                   
                 */                
                bool SearchBindSymbol(
                    BindSymbol*      symbol,
                    const u8         symbol_index ) const;

            public : // Get settings
                /* Please see man pages for details 
                    
                    
                    
                 */
                u8 GetShaderNum()           const
                {
                    return m_ExeImageInfoNum;
                }
                
                /* Please see man pages for details 
                    
                    
                    
                    
                 */               
                bool IsEnableGeoShader()    const
                {
                    return ( 0 <= GetGeoShaderIndex() );
                }
                
                /* Please see man pages for details 
                    
                
                    
                    
                 */
                
                s32 GetVtxShaderIndex()     const
                {
                    return m_VtxShaderIndex;
                }
                
                /* Please see man pages for details 
                    
                    
                    
                    
                 */                
                s32 GetGeoShaderIndex()     const
                {
                    return m_GeoShaderIndex;
                }

                /* Please see man pages for details 
                    

                    
                 */
                bit32 GetVtxShaderBoolMapUniform() const
                {
                    return m_VtxShaderBoolMapUniform;
                }

                /* Please see man pages for details 
                    

                    
                 */
                bit32 GetGeoShaderBoolMap()    const
                {
                    return m_GeoShaderBoolMapUniform;
                }
                
            protected :
                /* Please see man pages for details 
                    
                 */
                 //
                 static const s32 EXE_IMAGE_MAX = 32;
                    
                 //
                 static const s32 SWIZZLE_PATTERN_MAX = 128;

                 //
                 static const s32 DUMMY_DATA_NUM_251 = 10;
                    
                 //
                 static const s32 DUMMY_DATA_NUM_200 = 30;
                    
                 //
                 static const u32 PADDING_DATA = 0xead0fead;

                 //
                 static const s32 OUT_ATTR_COMMAND_MAX = 48;

                 //
                 static const u32 CONST_REG_COMMAND_MAX = 96 * 6 + 5 * 2;

            protected :
                /* Please see man pages for details 
                    
                           
                       
                    
                    
                */
                void CheckVtxShaderIndex_( const s32 vtx_shader_index );

               /* Please see man pages for details 
                    
                           
                       
                    
                    
                */   
                void CheckGeoShaderIndex_( const s32 geo_shader_index );

                /* Please see man pages for details 
                    
                 */
                void MakeShaderConstCommandCache_( void );

                /* Please see man pages for details 
                    
                 */
                void MakeShaderOutAttrCommandCache_( void );

                /* Please see man pages for details 
                    
                           
                    
                    
                    

                    
                 */
                static bit32* MakeShaderModeCommand_( bit32* command, 
                                                      const bool isEnableGeoShader,
                                                      const PicaDataDrawMode drawMode );

                /* Please see man pages for details 
                    

                    
                    
                    
                    
                 */

                bit32* MakeConstRgCommand_( bit32* command,
                                            const s32 shader_index );
                
                /* Please see man pages for details 
                    
                 
                    
                    
                    

                    
                 */
                bit32* MakeOutAttrCommand_( bit32* command, const s32 vtx_shader_index, const s32 geo_shader_index );
                
                /* Please see man pages for details 
                    

                    
                    
                    
                    

                    
                 */
                bit32* MakeLoadCommand_( bit32* command,
                                         const bit32  load_reg,
                                         const u32* src_buffer_ptr,
                                         const u32  src_size ) const;

                /* Please see man pages for details 
                    
                
                    
                    
                    

                    
                 */
                 static bit32* MakeDummyCommand_( bit32* command,
                                                  const bit32 load_reg,
                                                  const u32 data_num );

                /* Please see man pages for details 
                    
                 */
                struct ExeImageInfo
                {
                    //
                    bit32 signature;
                    //
                    u16 version;
                    //
                    u8  isGeoShader;
                    //
                    u8  outputMaps;
                    //
                    uptr mainAddress;
                    //
                    uptr endAddress;
                    //
                    bit32 maskInputOutput;
                    //
                    u8  gsDataMode;
                    //
                    u8  gsVertexStartIndex;
                    //
                    u8  gsPatchSize;
                    //
                    u8  gsVertexNum;
                    //
                    u32 setupOffset;
                    //
                    u32 setupCount;
                    //
                    u32 labelOffset;
                    //
                    u32 labelCount;
                    //
                    u32 outMapOffset;
                    //
                    u32 outMapCount;
                    //
                    u32 bindSymbolOffset;
                    //
                    u32 bindSymbolCount;
                    //
                    u32 stringOffset;
                    //
                    u32 stringCount;
                };

                /* Please see man pages for details 
                    
                */
                s32 m_VtxShaderIndex;

                /* Please see man pages for details 
                    
                */
                s32 m_GeoShaderIndex;

                /* Please see man pages for details 
                    
                */
                u8 m_ExeImageInfoNum;
                NN_PADDING3;

                /* Please see man pages for details 
                    
                */
                const ExeImageInfo* m_ExeImageInfo[ EXE_IMAGE_MAX ];

                /* Please see man pages for details 
                    
                */
                const bit32* m_Instruction;

                /* Please see man pages for details 
                    
                */
                u32 m_InstructionCount;

                /* Please see man pages for details 
                    
                */
                bit32 m_Swizzle[ SWIZZLE_PATTERN_MAX ];

                /* Please see man pages for details 
                    
                */
                u32 m_SwizzleCount;

                /* Please see man pages for details 
                    
                */
                PicaDataDrawMode m_DrawMode;
                NN_PADDING3;

                /* Please see man pages for details 
                    
                */
                bit32 m_VtxShaderBoolMapUniform;

                /* Please see man pages for details 
                    
                */
                bit32 m_GeoShaderBoolMapUniform;

                /* Please see man pages for details 
                    
                */
                bit32 m_CmdCacheOutAttrArray[ OUT_ATTR_COMMAND_MAX ];

                /* Please see man pages for details 
                    
                */
                u32 m_CmdCacheOutAttrNum;

                /* Please see man pages for details 
                    
                */
                bit32 m_CmdCacheConstArray[ EXE_IMAGE_MAX ][ CONST_REG_COMMAND_MAX ];
                
                /* Please see man pages for details 
                    
                */
                u32 m_CmdCacheConstNumArray[ EXE_IMAGE_MAX ];
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_SHADER_H_
