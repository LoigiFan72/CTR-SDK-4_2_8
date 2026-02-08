/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Vertex.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_VERTEX_H_
#define NN_GR_VERTEX_H_

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
            class Vertex
            {
            public :
                //
                static const u32 VERTEX_ATTRIBUTE_MAX           = 12;
                    
                //
                static const u32 VERTEX_ATTRIBUTE_DIMENSION_MAX = 4;
                    
                //
                static const u32 VERTEX_ENABLE_COMMAND_MAX = 12 + VERTEX_ATTRIBUTE_MAX * 6;

                /* Please see man pages for details 
                    
                */
                class InterleaveInfo
                {
                public:
                    /* Please see man pages for details 
                        
                    */
                    InterleaveInfo()
                    { 
                        dataNum = 0;

                        for ( u32 index = 0; index < VERTEX_ATTRIBUTE_MAX; index++ )
                        {
                            // Initialize with 0x0.
                            dataType[ index ] = PICA_DATA_SIZE_1_BYTE;
                        }

                        for ( u32 index = 0; index < VERTEX_ATTRIBUTE_MAX; index++ )
                        {
                            // Initialize with NULL.
                            symbol[ index ] = NULL;
                        }
                    }

                    /* Please see man pages for details 
                        
                    */
                    u8                            dataNum;
                    NN_PADDING3;

                    /* Please see man pages for details 
                        
                               
                    */
                    PicaDataVertexAttrType       dataType[ VERTEX_ATTRIBUTE_MAX ];

                    /* Please see man pages for details 
                        
                               
                    */
                    const nn::gr::CTR::BindSymbolVSInput* symbol[ VERTEX_ATTRIBUTE_MAX ];                  
                };

            public :
                /* Please see man pages for details 
                    
                 */
                class IndexStream
                {
                public :
                    /* Please see man pages for details 
                        
                    */
                    IndexStream() :
                    physicalAddr( 0 ),
                    drawVtxNum( 0 ),
                    isUnsignedByte( false )
                    {
                    }

                    /* Please see man pages for details 
                        
                    */
                    uptr  physicalAddr;

                    /* Please see man pages for details 
                        
                    */
                    u32  drawVtxNum;

                    /* Please see man pages for details 
                        
                    */
                    bool isUnsignedByte;
                    NN_PADDING3;
                };

            public: // Set vertex attributes      
                /* Please see man pages for details 
                    

                    
                    
                    
                 */
                void EnableAttrAsArray( const nn::gr::CTR::BindSymbolVSInput& symbol, const uptr physical_addr, const PicaDataVertexAttrType type );
              
                /* Please see man pages for details 
                    
                           

                    
                    
                    

                    
                */
                void EnableAttrAsConst( const nn::gr::CTR::BindSymbolVSInput& symbol, const u8 dimension, const f32 param[] );

                /* Please see man pages for details 
                    

                    
                    
                */
                void EnableInterleavedArray( const nn::gr::CTR::Vertex::InterleaveInfo& interleave_info, const uptr physical_addr );
                
            public : // Generate commands from settings
                /* Please see man pages for details 
                    
                    
                    
                    
                    
                 */

                bit32* MakeEnableAttrCommand( bit32* command ) const
                {
                    if ( m_CmdCacheVertexNum == 0 )
                    { 
                        // Generate cache
                        m_CmdCacheVertexNum = MakeEnableAttrCommand_( m_CmdCacheVertex ) - m_CmdCacheVertex;
                    }

                    std::memcpy( command, m_CmdCacheVertex, m_CmdCacheVertexNum * sizeof( bit32 ) );
                    return command + m_CmdCacheVertexNum;
                }

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                bit32* MakeDrawCommand( bit32* command, const IndexStream& index_stream ) const;

                /* Please see man pages for details 
                    
                 
                    
                    
                    
                 */
                bit32* MakeDisableAttrCommand( bit32* command ) const
                {
                    for ( int index = 0; index < VERTEX_ATTRIBUTE_MAX; ++index )
                    {
                        // Generate commands to disable valid load arrays
                        if ( m_LoadArray[ index ].IsEnable() )
                        {
                            // 0x203 + 3N, Generate commands to disable load array address offsets
                            *command++ = 0;
                            *command++ = 
                                PICA_CMD_HEADER_BURSTSEQ( PICA_REG_LOAD_ARRAY0_ATTR_OFFSET + 3 * index, 0x3 );
                            // 0x204 + 3N, Generate commands to disable load array 0th - 7th elements
                            *command++ = 0;
                            // 0x205 + 3N [15: 0] Generate commands to disable load array 8th - 11th elements
                            //            [23:16] Generate command to disable one-vertex byte count for the load array
                            //            [31:28] Generate command to disable the load array element count
                            *command++ = 0;
                        }
                        else
                        {
                            *command++ = 0;
                            // 0x205 + 3N [23:16] Generate command to disable one-vertex byte count for the load array                   
                            //            [31:28] Generate command to disable the load array element count                            
                            *command++ =
                                PICA_CMD_HEADER_SINGLE( PICA_REG_LOAD_ARRAY0_ELEMENT1 + 3 * index );
                        }

                        // Generate commands to disable valid fixed vertex attributes
                        if ( m_AttrConst[ index ].IsEnable() )
                        {
                            *command++ = index;
                            *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_VS_FIXED_ATTR, 4 );
                            *command++ = 0;
                            *command++ = 0;
                            *command++ = 0;
                            // Padding
                            *command++ = 0;
                        }
                    }

                    return command;
                }

                /* Please see man pages for details 
                    
                 
                    
                    
                    
                 */
                static bit32* MakeDisableCommand( bit32* command )
                {
                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( 0x201 );

                    *command++ = 0;
                    *command++ = PICA_CMD_HEADER_SINGLE( 0x202 );

                    // Generate commands to disable all 0x203 + 3N, 0x204 + 3N, 0x205 + 3N (N = 0-11)
                    const int size = ( 2 + 3 * VERTEX_ATTRIBUTE_MAX ) * sizeof( bit32 );
                    std::memset( command, 0, size );
                    command[ 1 ] = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_LOAD_ARRAY0_ATTR_OFFSET, VERTEX_ATTRIBUTE_MAX * 3 );
                    command += size / sizeof( bit32 );
                    
                    for ( int i = 0; i < VERTEX_ATTRIBUTE_MAX; ++i )
                    {
                        // 0x232
                        *command++ = i;
                        *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_VS_FIXED_ATTR, 4 );

                        // 0x233
                        *command++ = 0;
                        // 0x234
                        *command++ = 0;

                        // 0x235
                        *command++ = 0;
                        // Padding
                        *command++ = 0;
                    }

                    return command;
                }

            public : // disable

                /* Please see man pages for details 
                    
                    
                    
                 */
                void DisableAttr( const nn::gr::CTR::BindSymbolVSInput& symbol )
                {
                    DisableAttr_( symbol.start );
                }

                /* Please see man pages for details 
                    
                 */
                void DisableAll()
                {
                    m_CmdCacheVertexNum = 0;

                    for ( u32 index = 0; index < VERTEX_ENABLE_COMMAND_MAX; index++ )
                    {
                        m_CmdCacheVertex[ index ] = 0;
                    }

                    for ( u32 index = 0; index < VERTEX_ATTRIBUTE_MAX; index++ )
                    {
                        m_IsEnableReg[ index ] = false;
                        m_LoadArray[ index ].DisableAll();
                        m_AttrConst[ index ].DisableAll();
                    }
                }

            public :
                /* Please see man pages for details 
                    
                 */
                explicit Vertex()
                {
                    DisableAll();
                }

            protected :
                /* Please see man pages for details 
                    
                 */
                class LoadArray
                {
                public:
                    LoadArray() :
                    physicalAddr( 0 )
                    {
                    }

                    /* Please see man pages for details 
                        
                    */
                    uptr physicalAddr;
                    
                    /* Please see man pages for details 
                        
                               
                    */
                    PicaDataVertexAttrType type[ VERTEX_ATTRIBUTE_MAX ];
                    
                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u32 byte[ VERTEX_ATTRIBUTE_MAX ];

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    s32 bind[ VERTEX_ATTRIBUTE_MAX ];

                    /* Please see man pages for details 
                        

                        
                    */
                    bool IsEnable() const { return physicalAddr != 0; }

                    /* Please see man pages for details 
                        
                    */
                    void CheckDisable();

                    /* Please see man pages for details 
                        
                    */
                    void DisableAll();
                };

                /* Please see man pages for details 
                    
                 */
                class AttrConst
                {
                public :
                    /* Please see man pages for details 
                        
                    */
                    AttrConst() :
                    dimension( 0 )
                    {
                    }

                    /* Please see man pages for details 
                        
                               
                    */
                    u8 dimension;
                    NN_PADDING3;

                    /* Please see man pages for details 
                        
                               
                    */
                    f32 param[ VERTEX_ATTRIBUTE_DIMENSION_MAX ];

                    /* Please see man pages for details 
                        
                    */
                    bool IsEnable() const { return dimension != 0; }

                    /* Please see man pages for details 
                        
                    */
                    void Disable()
                    {
                        dimension = 0;
                    }

                    /* Please see man pages for details 
                        
                    */
                    void DisableAll()
                    {
                        dimension = 0;

                        for ( u32 index = 0; index < VERTEX_ATTRIBUTE_DIMENSION_MAX; index++ )
                        {
                            param[ index ] = 0;
                        }
                    }
                };

            protected :
                /* Please see man pages for details 
                    

                    
                */
                void DisableAttr_( const bit32 bind_reg );

                /* Please see man pages for details 
                    

                    

                    
                */
                bit32* MakeEnableAttrCommand_( bit32* command ) const;

            protected :
                mutable u32 m_CmdCacheVertexNum;
                mutable bit32 m_CmdCacheVertex[ VERTEX_ENABLE_COMMAND_MAX ];

                bool        m_IsEnableReg[ VERTEX_ATTRIBUTE_MAX ];

                LoadArray   m_LoadArray[ VERTEX_ATTRIBUTE_MAX ];
                AttrConst   m_AttrConst[ VERTEX_ATTRIBUTE_MAX ];
            };
          
        }  // namespace CTR
    }  // namespace gr
} // namespace nn
    

#endif // NN_GR_VERTEX_H_
