/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Shader.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49968 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_Shader.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {
            Shader::Shader( void ) :
            m_VtxShaderIndex( 0 ),
            m_GeoShaderIndex( - 1 ),
            m_ExeImageInfoNum( 0 ),
            m_InstructionCount( 0 ),
            m_SwizzleCount( 0 ),
            m_DrawMode( PICA_DATA_DRAW_TRIANGLES ),
            m_VtxShaderBoolMapUniform( 0 ),
            m_GeoShaderBoolMapUniform( 0 ),
            m_CmdCacheOutAttrNum( 0 )
            {
                for ( s32 shader_index = 0; shader_index < EXE_IMAGE_MAX; shader_index++ )
                {
                    m_CmdCacheConstNumArray[ shader_index ] = 0;
                }
            }

            void Shader::SetupBinary( const void* shader_binary, const s32 vtx_shader_index, const s32 geo_shader_index )
            {
                const bit32* binary = reinterpret_cast< const bit32* >( shader_binary );
                NN_GR_ASSERT( binary != NULL );

                NN_GR_ASSERT( *binary == 0x424C5644 ); // DVLB
                ++binary;

                NN_GR_ASSERT( *binary < EXE_IMAGE_MAX );

                // Number of execution images in the shader binary.
                m_ExeImageInfoNum = *binary;
                ++binary;

                m_VtxShaderBoolMapUniform = 0;
                m_GeoShaderBoolMapUniform = 0;

                // Saves the pointer to the execution images in the shader binary
                for ( s32 i = 0; i < m_ExeImageInfoNum; ++i )
                {
                    m_ExeImageInfo[ i ] = 
                        reinterpret_cast< const ExeImageInfo* >( (u8*)shader_binary + *binary );
                    NN_GR_ASSERT( m_ExeImageInfo[ i ]->signature == 0x454c5644 ); // DVLP
                    ++binary;
                }
                
                const bit32* package_info = binary;
                NN_GR_ASSERT( *binary == 0x504C5644 ); // DVLP
                ++binary;
                ++binary;

                m_Instruction = reinterpret_cast< const bit32* >( (u8*)package_info + *binary );
                ++binary;

                m_InstructionCount = *binary;
                ++binary;

                const bit32* swizzle = reinterpret_cast< const bit32* >( (u8*)package_info + *binary );
                ++binary;

                m_SwizzleCount = *binary;
                NN_GR_ASSERT( m_SwizzleCount < SWIZZLE_PATTERN_MAX );
                ++binary;

                for ( s32 i = 0; i < m_SwizzleCount; i++ )
                {
                    m_Swizzle[ i ] = swizzle[ i * 2 ] ;
                }

                PicaDataDrawMode drawMode     = m_DrawMode;

                MakeShaderConstCommandCache_();
                SetShaderIndex( vtx_shader_index, geo_shader_index );
                
                if ( ! IsEnableGeoShader() )
                {
                    m_DrawMode                = drawMode;
                }
            }

            //------------------------------------------------------------------------
            
            void Shader::SetShaderIndex( const s32 vtx_shader_index, const s32 geo_shader_index )
            {
                // Test for the vertex shade and geometry shader        
                CheckVtxShaderIndex_( vtx_shader_index );
                // Geometry shader test
                CheckGeoShaderIndex_( geo_shader_index );
                
                m_VtxShaderIndex = vtx_shader_index;
                m_GeoShaderIndex = geo_shader_index;

                if ( IsEnableGeoShader() )
                {
                    m_DrawMode = PICA_DATA_DRAW_GEOMETRY_PRIMITIVE;
                }
               
                MakeShaderOutAttrCommandCache_();
            }

            //------------------------------------------------------------------------

            void Shader::MakeShaderConstCommandCache_( void )
            {
                for ( s32 shader_index = 0; shader_index < m_ExeImageInfoNum; shader_index++ )
                {
                    // Generates command cache for the constant register.
                    m_CmdCacheConstNumArray[ shader_index ] = 
                        MakeConstRgCommand_( m_CmdCacheConstArray[ shader_index ],
                                             shader_index ) - 
                                             m_CmdCacheConstArray[ shader_index ];

                    NN_GR_ASSERT( m_CmdCacheConstNumArray[ shader_index ] <= CONST_REG_COMMAND_MAX );
                }
            }

            //------------------------------------------------------------------------

            void Shader::MakeShaderOutAttrCommandCache_( void )
            {
                // Generates command cache for output attributes.
                m_CmdCacheOutAttrNum =
                    MakeOutAttrCommand_( m_CmdCacheOutAttrArray,
                                         m_VtxShaderIndex,
                                         m_GeoShaderIndex )
                    - m_CmdCacheOutAttrArray;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeFullCommand( bit32* command ) const
            {
                // Generates configuration commands using the geometry shader
                {
                    command = MakePrepareCommand( command );
                }

                // Generates geometry shader commands
                if ( IsEnableGeoShader() )
                {                     
                    command = MakeGeoProgramCommand( command );
                    command = MakeGeoSwizzleCommand( command );
                    command = MakeGeoConstRgCommand( command );
                    command = MakeGeoBoolMapCommand( command );
                }            

                // Generates vertex shader commands
                {
                    command = MakeVtxProgramCommand( command );
                    command = MakeVtxSwizzleCommand( command );
                    command = MakeVtxConstRgCommand( command );
                    command = MakeVtxBoolMapCommand( command );
                }

                // Generates output attribute (outmap) related commands
                {
                    command = MakeOutAttrCommand( command );
                }
                
                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeDisableCommand( bit32* command )
            {
                const bool isEnableGeometryShader = false;
                const PicaDataDrawMode drawMode   = PICA_DATA_DRAW_TRIANGLES;

                command = MakeShaderModeCommand_( command,
                                                  isEnableGeometryShader,
                                                  drawMode );

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeShaderCommand( bit32* command, const bool isMakePrepareCommand ) const
            {
                // Generates configuration commands using the geometry shader
                if ( isMakePrepareCommand )
                {
                    command = MakePrepareCommand( command );
                }

                // Generates commands for the geometry shader constant register
                if ( IsEnableGeoShader() )
                {
                    command = MakeGeoConstRgCommand( command );
                    command = MakeGeoBoolMapCommand( command );
                }

                // Generates commands for the vertex shader constant register
                {
                    command = MakeVtxConstRgCommand( command );
                    command = MakeVtxBoolMapCommand( command );
                }

                // Generates output attribute (outmap) related commands
                {
                    command = MakeOutAttrCommand( command );
                }

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakePrepareCommand( bit32* command ) const
            {
                bool isEnableGeoShader    = IsEnableGeoShader();
                PicaDataDrawMode drawMode = m_DrawMode;

                command = 
                    MakeShaderModeCommand_( command,
                                            isEnableGeoShader,
                                            drawMode );

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeVtxProgramCommand( bit32* command ) const
            {
                s32 shader_index   = GetVtxShaderIndex();
                bit32 reg_addr     = PICA_REG_VS_PROG_ADDR;        // 0x2cb
                bit32 reg_load     = PICA_REG_VS_PROG_DATA0;       // 0x2cc
                bit32 reg_end      = PICA_REG_VS_PROG_UPDATE_END;  // 0x2bf

                { // Sets the program code load address
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( reg_addr );
                }

                { // Loads program code
                    NN_GR_ASSERT( 0 <= shader_index && shader_index < m_ExeImageInfoNum );
                    
                    const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                    NN_UNUSED_VAR( exe_info );

                    u32 instructionCount = m_InstructionCount;
                    if ( instructionCount > 512 )
                    {
                        instructionCount = 512;
                    }

                    command = MakeLoadCommand_( command, reg_load,
                                                m_Instruction,
                                                m_InstructionCount < 512 ? m_InstructionCount : 512 );
                }

                { // Completes notification program updates
                    *command++ = 1;
                    *command++ = PICA_CMD_HEADER_SINGLE( reg_end );
                }

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeGeoProgramCommand( bit32* command ) const
            {
                s32 shader_index   = GetGeoShaderIndex();
                bit32 reg_addr     = PICA_REG_GS_PROG_ADDR;        // 0x29b
                bit32 reg_load     = PICA_REG_GS_PROG_DATA0;       // 0x29c
                bit32 reg_end      = PICA_REG_GS_PROG_UPDATE_END;  // 0x28f

                { // Sets the program code load address
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( reg_addr );
                }

                { // Loads program code
                    NN_GR_ASSERT( ( 0 <= shader_index ) && 
                                  ( shader_index < m_ExeImageInfoNum ) );
                    
                    const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                    NN_UNUSED_VAR( exe_info );

                    command = MakeLoadCommand_( command, reg_load,
                                                m_Instruction,
                                                m_InstructionCount );
                }

                { // Completes notification program updates
                    *command++ = 1;
                    *command++ = PICA_CMD_HEADER_SINGLE( reg_end );
                }

                return command;
            }

            //------------------------------------------------------------------------
            
            bit32* Shader::MakeShaderModeCommand_( bit32* command,
                                                   const bool isEnableGeoShader,
                                                   const PicaDataDrawMode drawMode )
            {
                // Sets to 0x25e[9:8]
                { 
                    if ( isEnableGeoShader )
                    {
                        *command++ = PICA_DATA_DRAW_GEOMETRY_PRIMITIVE << 8;
                    }
                    else
                    {
                        *command++ = drawMode << 8;
                    }
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_VS_OUT_REG_NUM3, 2 );
                }

                // Dummy command to 0x251
                {
                    command = MakeDummyCommand_( command, PICA_REG_VS_OUT_REG_NUM2, DUMMY_DATA_NUM_251 );
                }

                // Dummy command to 0x200
                {
                    command = MakeDummyCommand_( command, PICA_REG_VERTEX_ATTR_ARRAYS_BASE_ADDR, DUMMY_DATA_NUM_200 );
                }

                // 0x229[1:0] Sets whether to enable or disable the geometry shader
                {
                    *command++ = isEnableGeoShader ? 2 : 0;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE0, 1 );
                }

                // Dummy command to 0x200
                {
                    command = MakeDummyCommand_( command, PICA_REG_VERTEX_ATTR_ARRAYS_BASE_ADDR, DUMMY_DATA_NUM_200 );
                }

                // 0x244 Sets whether to share geometry shader settings with the vertex shader
                { 
                    *command++ = isEnableGeoShader ? 1 : 0;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_VS_COM_MODE, 1 );
                }

                return command;
            }

            //------------------------------------------------------------------------

            void Shader::CheckVtxShaderIndex_( const s32 vtx_shader_index )
            {
                NN_UNUSED_VAR( vtx_shader_index );

                // Vertex shader index range test
                NN_GR_ASSERT( ( 0 <= vtx_shader_index ) && ( vtx_shader_index < GetShaderNum() ) );

                // Shader binary compatibility test
                NN_GR_ASSERT( ! m_ExeImageInfo[ vtx_shader_index ]->isGeoShader );
            }

            //------------------------------------------------------------------------

            void Shader::CheckGeoShaderIndex_( const s32 geo_shader_index )
            {
                NN_UNUSED_VAR( geo_shader_index );

                // Geometry shader index range test
                NN_GR_ASSERT( m_GeoShaderIndex < GetShaderNum() );

                // Shader binary compatibility test
                if ( geo_shader_index > - 1 )
                {
                    NN_GR_ASSERT( m_ExeImageInfo[ geo_shader_index ]->isGeoShader );
                }
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeConstRgCommand_( bit32* command,
                                                const s32 shader_index )
            {
                bit32  reg_float     = PICA_REG_VS_FLOAT_ADDR; // 0x2c0
                bit32  reg_integer   = PICA_REG_VS_INT0;       // 0x2b1
                bit32* boolMap       = &m_VtxShaderBoolMapUniform;

                bool is_geometry_shader = m_ExeImageInfo[ shader_index ]->isGeoShader;
                if ( is_geometry_shader )
                {
                    reg_float    = PICA_REG_GS_FLOAT_ADDR; // 0x290
                    reg_integer  = PICA_REG_GS_INT0;       // 0x281
                    boolMap      = &m_GeoShaderBoolMapUniform;
                }

                // Program information
                NN_GR_ASSERT( ( 0 <= shader_index ) && 
                              ( shader_index < m_ExeImageInfoNum ) );
                const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                // Constant register information
                struct SetupInfo
                {
                    u16 type;
                    u16 index;
                    bit32 value[4];
                };

                const SetupInfo* setupInfo =
                    reinterpret_cast< const SetupInfo* >(
                        reinterpret_cast< const u8* >( exe_info ) + exe_info->setupOffset );

                // Constant register command generation
                for ( s32 i = 0; i < exe_info->setupCount; ++i )
                {
                    const SetupInfo& info = setupInfo[ i ];
                    const bit32* value = info.value;

                    switch ( info.type )
                    {
                    case 0 : // bool register setup
                        *boolMap |= ( info.value[ 0 ] << info.index ) & ( 1 << info.index );
                        break;

                    case 1 : // integer register setup
                        *command++ = value[ 0 ] | value[ 1 ] <<  8 | value[ 2 ] << 16 | value[ 3 ] << 24;
                        *command++ = PICA_CMD_HEADER_SINGLE( reg_integer + info.index );
                        break;

                    case 2 : // float register setup
                        *command++ = info.index;
                        *command++ = PICA_CMD_HEADER_BURSTSEQ( reg_float, 4 );
                        *command++ = ( value[ 3 ] <<  8 & 0xffffff00 ) | ( value[ 2 ] >> 16 & 0x000000ff );
                        *command++ = ( value[ 2 ] << 16 & 0xffff0000 ) | ( value[ 1 ] >>  8 & 0x0000ffff );
                        *command++ = ( value[ 1 ] << 24 & 0xff000000 ) | ( value[ 0 ] >>  0 & 0x00ffffff );
                        *command++ = PADDING_DATA; // Padding
                        break;
                    }
                }

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeOutAttrCommand_( bit32* command,
                                                const s32 vtx_shader_index,
                                                const s32 geo_shader_index )
            {
                s32 shader_index = vtx_shader_index;

                bool is_geometry_shader = false;
                if ( 0 <= GetGeoShaderIndex() )
                {
                    is_geometry_shader = true;

                    shader_index = geo_shader_index;
                }

                NN_GR_ASSERT(  0 <= shader_index && shader_index < m_ExeImageInfoNum );

                // Output attribute settings
                // When the geometry shader is enabled, output attributes perform settings for the geometry shader
                // 

                const s32 OUT_ATTR_INDEX_MAX     = 7;
                const s32 OUT_ATTR_DIMENTION_MAX = 4;
                const s32 OUT_ATTR_BUFFER_MAX    = 16 * 4;
                const s32 VS_OUT_ATTR_INDEX_MAX  = 16;

                // Output attribute information
                struct OutmapInfo
                {
                    u16 type;
                    u16 index;
                    u16 mask;
                    u16 reserve;
                };

                u32 outNum  = 0;
                bit32 useTex  = 0;
                bit32 clock   = 0;
                bit32 outMask = 0;
                bit32 attr[ OUT_ATTR_INDEX_MAX ];

                // Find output attribute settings
                {
                    // Program information
                    const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                    // Actual output attribute information
                    OutmapInfo outmap_buffer[ OUT_ATTR_BUFFER_MAX ];
                    s32 outMapBufferCount = 0;
                    
                    // Merge
                    if ( is_geometry_shader && exe_info->outputMaps )
                    {
                        bit32 gs_copy_mask = 0;
                        bit32 vs_copy_mask = 0;
                        // GS output attribute information
                        const OutmapInfo* outmapInfo =
                            reinterpret_cast< const OutmapInfo* >(
                                reinterpret_cast< const u8* >( exe_info ) + exe_info->outMapOffset );
                        // VS program information    
                        NN_GR_ASSERT(  0 <= vtx_shader_index && vtx_shader_index < m_ExeImageInfoNum );
                        const ExeImageInfo* vtx_exe_info = m_ExeImageInfo[ vtx_shader_index ];

                        // VS output attribute information
                        const OutmapInfo* vtxOutmapInfo =
                            reinterpret_cast< const OutmapInfo* >(
                                reinterpret_cast< const u8* >( vtx_exe_info ) + vtx_exe_info->outMapOffset );
                        
                        // Merge output attributes, other than generic, defined by both VS and GS
                        NN_GR_ASSERT( outMapBufferCount < OUT_ATTR_BUFFER_MAX );
                        for( s32 g = 0; g < exe_info->outMapCount; ++g )
                        {
                            // Excludes GS generic attributes (value 9)
                            if ( ( outmapInfo[ g ].type >= 0 ) &&
                                 ( outmapInfo[ g ].type <  9 ) && 
                                 ( outmapInfo[ g ].type != 7 ) )
                            {
                                for( s32 v = 0; v < vtx_exe_info->outMapCount; ++v )
                                {
                                    // Excludes VS generic attributes (value 9)
                                    if ( ( vtxOutmapInfo[ v ].type >= 0 ) &&
                                         ( vtxOutmapInfo[ g ].type <  9 ) && 
                                         ( vtxOutmapInfo[ g ].type != 7 ) )
                                    {
                                        if ( outmapInfo[ g ].type == vtxOutmapInfo[ v ].type )
                                        {
                                            NN_GR_ASSERT( outMapBufferCount < OUT_ATTR_INDEX_MAX );
                                            outmap_buffer[ outMapBufferCount ].type = outmapInfo[ g ].type;
                                            outmap_buffer[ outMapBufferCount ].index = outMapBufferCount;
                                            outmap_buffer[ outMapBufferCount ].mask = outmapInfo[ g ].mask;
                                            gs_copy_mask |= 1 << g;
                                            vs_copy_mask |= 1 << v;
                                            ++outMapBufferCount;
                                        }
                                    }
                                }
                            }
                        }
                        
                        // Next, sets output attributes defined only by GS
                        for( s32 g = 0; g < exe_info->outMapCount; ++g )
                        {
                            if ( ( !( gs_copy_mask & ( 1 << g ) )) && 
                                 ( outmapInfo[ g ].type >= 0  )    &&
                                 ( outmapInfo[ g ].type < 9 )      && 
                                 ( outmapInfo[ g ].type != 7 ) )
                            {
                                NN_GR_ASSERT( outMapBufferCount < OUT_ATTR_BUFFER_MAX );
                                outmap_buffer[ outMapBufferCount ].type = outmapInfo[ g ].type;
                                outmap_buffer[ outMapBufferCount ].index = outMapBufferCount;
                                outmap_buffer[ outMapBufferCount ].mask = outmapInfo[ g ].mask;
                                ++outMapBufferCount;
                            }
                        }

                        // Last, sets output attributes defined only by VS
                        for( s32 v = 0; v < vtx_exe_info->outMapCount; ++v )
                        {
                            if ( ( !( vs_copy_mask & ( 1 << v ) ) ) && 
                                 ( vtxOutmapInfo[ v ].type >= 0 )   &&
                                 ( vtxOutmapInfo[ v ].type < 9  )   && 
                                 ( vtxOutmapInfo[ v ].type != 7 ) )
                            {
                                NN_GR_ASSERT( outMapBufferCount < OUT_ATTR_BUFFER_MAX );
                                outmap_buffer[ outMapBufferCount ].type = vtxOutmapInfo[ v ].type;
                                outmap_buffer[ outMapBufferCount ].index = outMapBufferCount;
                                outmap_buffer[ outMapBufferCount ].mask = vtxOutmapInfo[ v ].mask;
                                ++outMapBufferCount;
                            }
                        }
                    }
                    else
                    {
                        // Output attribute information
                        const OutmapInfo* outmapInfo =
                            reinterpret_cast< const OutmapInfo* >(
                                reinterpret_cast< const u8* >( exe_info ) + exe_info->outMapOffset );
                        // Copies when not merging.
                        for( s32 i = 0; i < exe_info->outMapCount; ++i )
                        {
                            outmap_buffer[ i ] = outmapInfo[ i ];
                        }
                        outMapBufferCount = exe_info->outMapCount;
                    }

                    for ( s32 index = 0; index < OUT_ATTR_INDEX_MAX; ++index )
                    {
                        attr[ index ] = 0x1f1f1f1f;
                        for ( s32 i = 0; i <outMapBufferCount; ++i )
                        {
                            bit32 c = 0;
                            for ( s32 j = 0; outmap_buffer[ i ].index == index && j < OUT_ATTR_DIMENTION_MAX; ++j )
                            {
                                if ( ( outmap_buffer[ i ].mask & ( 1 << j ) ) == 0 ) continue;

                                s32 value = 0x1f;
                                switch ( outmap_buffer[ i ].type )
                                {
                                case 0  :            value = 0x00 + c++; if (c == 2) clock |= 1 <<  0; break; // Position
                                case 1  :            value = 0x04 + c++;             clock |= 1 << 24; break; // Quaternion
                                case 2  :            value = 0x08 + c++;             clock |= 1 <<  1; break; // color
                                case 3  : if (c < 2) value = 0x0c + c++; useTex = 1; clock |= 1 <<  8; break; // texcoord0
                                case 4  :            value = 0x10;       useTex = 1; clock |= 1 << 16; break; // texcoord0w
                                case 5  : if (c < 2) value = 0x0e + c++; useTex = 1; clock |= 1 <<  9; break; // texcoord1
                                case 6  : if (c < 2) value = 0x16 + c++; useTex = 1; clock |= 1 << 10; break; // texcoord2
                                case 8  : if (c < 3) value = 0x12 + c++;             clock |= 1 << 24; break; // view
                                }
                                attr[ index ] = attr[ index ] & ~( 0xff << ( j * 8 ) ) | value << ( j * 8 );
                            }
                        }
                        if ( attr[ index ] != 0x1f1f1f1f )
                        {
                            outMask |= ( 1 << index );
                            ++outNum;
                        }
                    }
                }

                if ( is_geometry_shader )
                {  
                    // Finds vertex shader output attribute settings
                    //m_DrawMode = PICA_DATA_DRAW_GEOMETRY_PRIMITIVE;

                    u32 vtxOutNum = 0;
                    bit32 vtxOutMask = 0;
                    bit32 vtxAttr[ VS_OUT_ATTR_INDEX_MAX ];

                    // Program information
                    const ExeImageInfo* exe_info = m_ExeImageInfo[ vtx_shader_index ];
                    const OutmapInfo* outmapInfo =
                        reinterpret_cast< const OutmapInfo* >(
                            reinterpret_cast< const u8* >( exe_info ) + exe_info->outMapOffset );

                    for ( s32 index = 0; index < VS_OUT_ATTR_INDEX_MAX; ++index )
                    {
                        vtxAttr[ index ] = 0x1f1f1f1f;
                        for ( s32 i = 0; i < exe_info->outMapCount; ++i )
                        {
                            u32 c = 0;
                            for ( s32 j = 0; outmapInfo[ i ].index == index && j < OUT_ATTR_DIMENTION_MAX; ++j )
                            {
                                if ( ( outmapInfo[ i ].mask & ( 1 << j ) ) == 0 ) continue;

                                s32 value = 0x1f;
                                switch ( outmapInfo[ i ].type )
                                {
                                case 0  :            value = 0x00 + c++; break; // Position
                                case 1  :            value = 0x04 + c++; break; // Quaternion
                                case 2  :            value = 0x08 + c++; break; // color
                                case 3  : if (c < 2) value = 0x0c + c++; break; // texcoord0
                                case 4  :            value = 0x10;       break; // texcoord0w
                                case 5  : if (c < 2) value = 0x0e + c++; break; // texcoord1
                                case 6  : if (c < 2) value = 0x16 + c++; break; // texcoord2
                                case 8  : if (c < 3) value = 0x12 + c++; break; // view
                                case 9  : value = 0xff;
                                }
                                vtxAttr[ index ] = vtxAttr[ index ] & ~( 0xff << ( j * 8 ) ) | value << ( j * 8 );
                            }
                        }
                        if ( vtxAttr[ index ] != 0x1f1f1f1f )
                        {
                            vtxOutMask |= ( 1 << index );
                            ++vtxOutNum;
                        }
                    }

                    bit32 gsDataMode = m_ExeImageInfo[ geo_shader_index ]->gsDataMode;

                    // GL_GEOMETRY_PRIMITIVE_DMP

                    // 0x229 [31:31], 
                    // For data mode 1
                    if ( gsDataMode == 1 )
                    {
                        *command++ = 0x80000000;
                    }
                    // For data mode 0 and data mode 2
                    else
                    {
                        *command++ = 0x00000000;
                    }
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE0, 0xa );
                    
                    // 0x253
                    *command++ = 0x00000000;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE1, 0x3 );

                    // 0x289 Vertex shader output count
                    *command++ = 0x08000000 | (gsDataMode == 0 ? 0x0000 : 0x0100) | vtxOutNum - 1;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_GS_ATTR_NUM, 0xb );

                    // 0x28a Geometry shader main label address
                    *command++ = 0x7fff0000 | m_ExeImageInfo[ geo_shader_index ]->mainAddress;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_START_ADDR );

                    // 0x28d Vertex shader output mask
                    *command++ = outMask;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_OUT_REG_MASK );

                    // 0x2ba Vertex shader main label address
                    *command++ = 0x7fff0000 | m_ExeImageInfo[ vtx_shader_index ]->mainAddress;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_START_ADDR );

                    // 0x2bd Vertex shader output register mask
                    *command++ = vtxOutMask;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_MASK );

                    // 0x251 Vertex shader output count
                    *command++ = vtxOutNum - 1;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_NUM2 );

                    // 0x28b It is assumed that the vertex shader output matches the geometry shader input
                    *command++ = 0x76543210;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_ATTR_IN_REG_MAP0 ); // 0x28b
                    
                    // 0x28c
                    *command++ = 0xfedcba98;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_ATTR_IN_REG_MAP1 );

                    // 0x254
                    if ( ( gsDataMode == 1 ) &&
                         ( m_ExeImageInfo[ geo_shader_index ]->gsPatchSize != 0 ) )
                    {
                        *command++ = m_ExeImageInfo[ geo_shader_index ]->gsPatchSize - 1;
                        *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_GS_MISC_REG1, 0x1 );
                    }

                    // Value for 0x252
                    if ( gsDataMode == 2 )
                    {
                        gsDataMode |= 0x01                                                       << 24;
                        gsDataMode |= ( m_ExeImageInfo[ geo_shader_index ]->gsVertexStartIndex ) << 16;
                        gsDataMode |= ( vtxOutNum - 1 )                                          << 12;
                        gsDataMode |= ( m_ExeImageInfo[ geo_shader_index ]->gsVertexNum - 1 )    <<  8;
                    }

                    // 0x252 data mode specification
                    *command++ = gsDataMode;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_MISC_REG0 );

                    // 0x24a
                    *command++ = vtxOutNum - 1;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_NUM1 );
                }
                else
                {
                    // 0x229 [31:31]
                    *command++ = 0x0;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE0, 0x8 );

                    // 0x253 [0:0]
                    *command++ = 0x0;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_DRAW_MODE1, 0x1 );
                    
                    // 0x289 [31:24], [15:8], [3:0] Geometry shader mode settings
                    *command++ = 0xa0000000;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_GS_ATTR_NUM, 0xb );

                    // 0x2ba Vertex shader main label address
                    *command++ = 0x7fff0000 | m_ExeImageInfo[ vtx_shader_index ]->mainAddress;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_START_ADDR );

                    // 0x2bd Vertex shader output register mask
                    *command++ = outMask;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_MASK );

                    // 0x251
                    *command++ = outNum - 1;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_NUM2 );

                    // 0x252
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_MISC_REG0 );

                    // 0x24a
                    *command++ = outNum - 1;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_NUM1 );
                }

                {
                    // 0x25e [3:0]
                    *command++ = outNum - 1;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_VS_OUT_REG_NUM3, 0x1 );
                    
                    // 0x04f
                    *command++ = outNum;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_REG_NUM0 );

                    // Output attribute command
                    outNum = 0;
                    for ( s32 index = 0; index < OUT_ATTR_INDEX_MAX; ++index )
                    {
                        if ( attr[ index ] != 0x1f1f1f1f )
                        {
                            *command++ = attr[ index ];
                            *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_ATTR0 + outNum );
                            ++outNum;
                        }
                    }
                    for ( s32 index = outNum; index < OUT_ATTR_INDEX_MAX; ++index )
                    {
                        *command++ = attr[ index ];
                        *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_ATTR0 + index );
                    }
                }

                // 0x064 Sets whether to use texture coordinates
                *command++ = useTex;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_ATTR_MODE );

                // 0x06f Sets output attribute clock control
                *command++ = clock;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_OUT_ATTR_CLK );

                if ( is_geometry_shader )
                {
                    // 0x25e
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_VS_OUT_REG_NUM3, 8 );
                }

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeLoadCommand_( bit32* command,
                                             const bit32  load_reg,
                                             const bit32* src_buffer_ptr,
                                             const u32  src_data_num ) const
            {
                const s32 WRITE_MAX = 128;

                u32 rest = src_data_num;

                while ( true )
                {
                    if ( rest <= WRITE_MAX )
                    {
                        *command++ = *src_buffer_ptr++;
                        *command++ = PICA_CMD_HEADER_BURST( load_reg, rest );
                        std::memcpy( command, src_buffer_ptr, ( rest - 1 ) * sizeof( bit32 ) );
                        command += rest - 1;

                        if ( ( rest & 1 ) == 0 ) *command++ = PADDING_DATA; // Padding
                        break;
                    }
                    else
                    {
                        *command++ = *src_buffer_ptr++;
                        *command++ = PICA_CMD_HEADER_BURST( load_reg, WRITE_MAX );
                        std::memcpy( command, src_buffer_ptr, ( WRITE_MAX - 1 ) * sizeof( bit32 ) );

                        command += WRITE_MAX - 1;
                        src_buffer_ptr += WRITE_MAX - 1;

                        rest -= WRITE_MAX;
                        if ( ( WRITE_MAX & 1 ) == 0 ) *command++ = PADDING_DATA; // Padding
                    }
                }

                return command;
            }

            //------------------------------------------------------------------------

            bit32* Shader::MakeDummyCommand_( bit32* command,
                                              const bit32 load_reg,
                                              const u32 dataNum )
            {
                *command++ = 0;
                *command++ = PICA_CMD_HEADER_BURST_BE( load_reg, dataNum, 0 );

                for ( s32 i = 0; i < dataNum - ( dataNum & 1 ); ++i)
                {
                    *command++ = PADDING_DATA;
                }

                return command;
            }

            //------------------------------------------------------------------------

            bool Shader::SearchBindSymbol( BindSymbol* symbol,
                                           const char* name ) const
            {
                const s32 shader_index = ( symbol->shaderType == BindSymbol::SHADER_TYPE_GEOMETRY )
                    ? GetGeoShaderIndex() : GetVtxShaderIndex();

                NN_GR_ASSERT(  0 <= shader_index && shader_index < m_ExeImageInfoNum );

                // Program information
                const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                // Symbol information
                struct BindSymbolInfo { u32 nameIndex; u32 regIndex; };
                const BindSymbolInfo* bind_symbol_info =
                    reinterpret_cast< const BindSymbolInfo* >(
                        reinterpret_cast< const u8* >( exe_info ) + exe_info->bindSymbolOffset );

                // Text string information
                const char* string =
                    reinterpret_cast< const char* >(
                        reinterpret_cast< const u8* >( exe_info ) + exe_info->stringOffset );

                // Search
                u32 namelen = std::strlen( name );
                for ( s32 i = 0; i < exe_info->bindSymbolCount; ++i )
                {
                    const BindSymbolInfo& info = bind_symbol_info[ i ];

                    if ( std::strncmp( name, &string[ info.nameIndex ], namelen ) != 0 ) continue;
                    if ( string[ info.nameIndex + namelen ] != '\0' &&  string[ info.nameIndex + namelen ] != '.' ) continue;

                    symbol->name  = &string[ info.nameIndex ];
                    symbol->start = (info.regIndex & 0x0000ffff);
                    symbol->end   = (info.regIndex & 0xffff0000) >> 16;

                    if ( 136 <= symbol->start )
                    {
                        return false;
                    }
                    else if ( 120 <= symbol->start )
                    {
                        symbol->start -= 120;
                        symbol->end   -= 120;

                        return symbol->symbolType == BindSymbol::SYMBOL_TYPE_BOOL;
                    }
                    else if ( 112 <= symbol->start )
                    {
                        symbol->start -= 112;
                        symbol->end   -= 112;

                        return symbol->symbolType == BindSymbol::SYMBOL_TYPE_INTEGER;
                    }
                    else if ( 16 <= symbol->start )
                    {
                        symbol->start -= 16;
                        symbol->end   -= 16;

                        return symbol->symbolType == BindSymbol::SYMBOL_TYPE_FLOAT;
                    }
                    else
                    {
                        return symbol->symbolType == BindSymbol::SYMBOL_TYPE_INPUT;
                    }
                }

                return false;
            }

            //------------------------------------------------------------------------

            u32 Shader::SearchBindSymbolNum(
                const BindSymbol::ShaderType shader_type,
                const BindSymbol::SymbolType symbol_type ) const
            {
                const s32 shader_index = ( shader_type == BindSymbol::SHADER_TYPE_GEOMETRY ) ? GetGeoShaderIndex() : GetVtxShaderIndex();
                NN_GR_ASSERT(  0 <= shader_index && shader_index < m_ExeImageInfoNum );

                // Program information
                const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                // Output attribute information
                struct BindSymbolInfo { u32 nameIndex; u32 regIndex; };
                const BindSymbolInfo* bind_symbol_info =
                    reinterpret_cast< const BindSymbolInfo* >(
                        reinterpret_cast< const u8* >( exe_info ) + exe_info->bindSymbolOffset );

                s32 num = 0;

                // Search
                for ( s32 i = 0; i < exe_info->bindSymbolCount; ++i )
                {
                    s32 regStart = bind_symbol_info[ i ].regIndex & 0x0000ffff;

                    if ( 120 <= regStart && regStart < 136 && 
                         symbol_type == BindSymbol::SYMBOL_TYPE_BOOL )
                    {
                        ++num;
                    }
                    else if ( 112 <= regStart && regStart < 115 && 
                              symbol_type == BindSymbol::SYMBOL_TYPE_INTEGER )
                    {
                        ++num;
                    }
                    else if ( 16 <= regStart && regStart < 111 && 
                              symbol_type == BindSymbol::SYMBOL_TYPE_FLOAT )
                    {
                        ++num;
                    }
                    else if ( regStart <  15 && 
                              symbol_type == BindSymbol::SYMBOL_TYPE_INPUT )
                    {
                        ++num;
                    }
                }

                return num;
            }

            //------------------------------------------------------------------------

            bool Shader::SearchBindSymbol(
                BindSymbol* symbol,
                const u8 symbol_index ) const
            {
                const BindSymbol::ShaderType shaderType = symbol->shaderType;

                const s32 shader_index = ( shaderType == BindSymbol::SHADER_TYPE_GEOMETRY )
                    ? GetGeoShaderIndex() : GetVtxShaderIndex();

                NN_GR_ASSERT(  0 <= shader_index && shader_index < m_ExeImageInfoNum );

                // Program information
                const ExeImageInfo* exe_info = m_ExeImageInfo[ shader_index ];

                // Symbol information
                struct BindSymbolInfo { u32 nameIndex; u32 regIndex; };
                const BindSymbolInfo* bind_symbol_info =
                    reinterpret_cast< const BindSymbolInfo* >(
                        reinterpret_cast< const u8* >( exe_info ) + exe_info->bindSymbolOffset );

                // Text string information
                const char* string =
                    reinterpret_cast< const char* >(
                        reinterpret_cast< const u8* >( exe_info ) + exe_info->stringOffset );

                s32 index = -1;
                
                // Search
                for ( s32 i = 0; i < exe_info->bindSymbolCount; ++i )
                {
                    s32 regStart = bind_symbol_info[ i ].regIndex & 0x0000ffff;

                    // Bool registers
                    if ( 120 <= regStart && regStart < 136 )
                    {
                        ++index;
                    }
                    // Integer registers
                    else if ( 112 <= regStart && regStart < 115 )
                    {
                        ++index;
                    }
                    // Constant registers
                    else if ( 16 <= regStart && regStart < 111 )
                    {
                        ++index;
                    }
                    // Input registers
                    else if ( regStart <  15 )
                    {
                        ++index;
                    }
                    else
                    {
                        return false;
                    }

                    if ( index == symbol_index )
                    {
                        const BindSymbolInfo& info = bind_symbol_info[ i ];

                        symbol->name  = &string[ info.nameIndex ];
                        symbol->start = (info.regIndex & 0x0000ffff);
                        symbol->end   = (info.regIndex & 0xffff0000) >> 16;

                        if ( 120 <= symbol->start )
                        { 
                            symbol->start -= 120;
                            symbol->end   -= 120; 

                            return symbol->symbolType == BindSymbol::SYMBOL_TYPE_BOOL;
                        }
                        else if ( 112 <= symbol->start )
                        { 
                            symbol->start -= 112;
                            symbol->end -= 112; 

                            return symbol->symbolType == BindSymbol::SYMBOL_TYPE_INTEGER;
                        }
                        else if (  16 <= symbol->start )
                        { 
                            symbol->start -=  16;
                            symbol->end -=  16; 

                            return symbol->symbolType == BindSymbol::SYMBOL_TYPE_FLOAT;
                        }
                        else
                        {
                            return symbol->symbolType == BindSymbol::SYMBOL_TYPE_INPUT;
                        }
                    }
                }

                return false;
            }

        } //namespace CTR
    } //namespace gr
} //namespace nn
