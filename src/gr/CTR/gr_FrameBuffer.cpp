/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_FrameBuffer.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47820 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_FrameBuffer.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {
            
            bit32* FrameBuffer::ColorBuffer::MakeRenderBlockModeCommand( bit32* command ) const
            {
                // 0x11b
                *command++ = blockSize;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BLOCK_FORMAT );
                
                return command;
            }

            bit32* FrameBuffer::ColorBuffer::MakeCommand( bit32* command, bool isAddRenderBlockModeCommand ) const
            {
                // 0x117 
                //  [1:0] color buffer pixel size format
                //   [18:16] color buffer format
                *command++ = 
                    PICA_CMD_DATA_RENDER_BUFFER_COLOR_MODE( 
                        ( ( format == PICA_DATA_COLOR_RGBA8_OES ) ||
                          ( format == PICA_DATA_COLOR_GAS_DMP   ) ) ?
                          PICA_DATA_COLOR_PIXEL_SIZE32 : PICA_DATA_COLOR_PIXEL_SIZE16,
                          format );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BUFFER_COLOR_MODE );

                // 0x11d
                //    [27:0] color buffer physical address
                *command++ = PICA_CMD_DATA_RENDER_BUFFER_COLOR_ADDR( nngxGetPhysicalAddr( virtualAddr ) );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BUFFER_COLOR_ADDR );

                if ( isAddRenderBlockModeCommand )
                {
                    command = MakeRenderBlockModeCommand( command );
                }

                return command;
            }

            //------------------------------------------------------------------------------

            bit32* FrameBuffer::DepthStencilBuffer::MakeCommand( bit32* command ) const
            {
                // 0x116
                //   [1:0] depth buffer format
                *command++ = PICA_CMD_DATA_RENDER_BUFFER_DEPTH_MODE( format );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BUFFER_DEPTH_MODE );
                
                // 0x11c
                //    [27:0] depth buffer physical address
                *command++ = PICA_CMD_DATA_RENDER_BUFFER_DEPTH_ADDR( nngxGetPhysicalAddr( virtualAddr ) );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BUFFER_DEPTH_ADDR );
                
                return command;
            }

            //------------------------------------------------------------------------------
            
            bit32* FrameBuffer::FrameBuffer::MakeCommand( bit32* command, const u32 bufferBit,
                                                          bool isClearCache ) const
            {   
                // Clear the framebuffer cache
                if ( isClearCache )
                {
                    command = MakeClearCacheCommand( command );
                }

                // Generate color buffer command
                if ( bufferBit & COLOR_BUFFER_BIT )
                {
                    command = colorBuffer.MakeCommand( command );
                }

                // Generate depth buffer command
                if ( ( bufferBit & DEPTH_BUFFER_BIT ) || ( bufferBit & STENCIL_BUFFER_BIT ) )
                {
                    command = depthStencilBuffer.MakeCommand( command );
                }

                // 0x11e 
                //   [27:12] framebuffer height
                //    [10:0] framebuffer width
                *command++ = PICA_CMD_DATA_RENDER_BUFFER_RESOLUTION( width, height );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BUFFER_RESOLUTION0 );

                // 0x6e
                //   [27:12] framebuffer height
                //   [10: [10:0] frame buffer width
                *command++ = PICA_CMD_DATA_RENDER_BUFFER_RESOLUTION( width, height );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BUFFER_RESOLUTION1 );

                command = MakeClearCacheCommand( command );

                return command;
            }
            
            //------------------------------------------------------------------------------

            FrameBuffer::ColorBuffer::ColorBuffer( const FrameBuffer& frameBuffer_ )
                : virtualAddr( 0 ),
                  format( PICA_DATA_COLOR_RGBA8_OES ),
                  blockSize( BLOCK_SIZE8 ),
                  width( 240 ), height( 400 ),
                  m_FrameBuffer( frameBuffer_ )
            {
                for (u32 index = 0; index < 4; index++)
                {
                    clearColor[ index ] = 0.0f;
                }
            }

            //------------------------------------------------------------------------------

            FrameBuffer::DepthStencilBuffer::DepthStencilBuffer( const FrameBuffer& frameBuffer_ )
                : virtualAddr( 0 ),
                format( PICA_DATA_DEPTH24_STENCIL8_EXT ),
                width( 240 ), height( 400 ),
                clearDepth( 1.0f ),
                clearStencil( 0 ),
                m_FrameBuffer( frameBuffer_ )
            {
            }
       
            //------------------------------------------------------------------------------

            FrameBuffer::FrameBuffer() :
                  colorBuffer( *this ),
                  depthStencilBuffer( *this ),
                  width( 240 ), height( 400 )
            {
            }

            //------------------------------------------------------------------------------

            bit32* FrameBuffer::MakeClearCacheCommand( bit32* command )
            {
                // 0x111
                *command++ = 0x1;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COLOR_DEPTH_BUFFER_CLEAR1 );

                // 0x110
                *command++ = 0x1;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COLOR_DEPTH_BUFFER_CLEAR0 );

                return command;
            }

            void FrameBuffer::FrameBuffer::MakeClearRequest( const u32 bufferBit, bool isAddSplitDrawCmdlist )
            { 
                // The colorByteSize fill size must be a multiple of 16.
                u32 colorByteSize = 0;
                u32 colorWidth    = 0;
                u32 clearColor    = 0;

                if ( bufferBit & COLOR_BUFFER_BIT )
                {
                    u8 red   = FloatToUnsignedByte( colorBuffer.clearColor[ 0 ] );
                    u8 green = FloatToUnsignedByte( colorBuffer.clearColor[ 1 ] );
                    u8 blue  = FloatToUnsignedByte( colorBuffer.clearColor[ 2 ] );
                    
                    if ( colorBuffer.format == PICA_DATA_COLOR_RGBA8_OES )
                    {
                        u8 alpha = FloatToUnsignedByte( colorBuffer.clearColor[ 3 ] );

                        colorByteSize = colorBuffer.width * colorBuffer.height * 4;
                        colorWidth    = 32;
                        // Clamp float32, and convert to u8.
                        clearColor    = ( red   << 24 ) |
                                        ( green << 16 ) |
                                        ( blue  <<  8 ) |
                                        ( alpha <<  0 ) ;
                    }
                    else if ( colorBuffer.format == PICA_DATA_COLOR_RGB5_A1 )
                    {
                        u8 alpha = FloatToUnsignedByte( colorBuffer.clearColor[ 3 ] );

                        colorByteSize = colorBuffer.width * colorBuffer.height * 2;
                        colorWidth    = 16;
                        clearColor    = ( ( ( red   >> 3 ) & 0x1f )      << 11 ) |
                                        ( ( ( green >> 3 ) & 0x1f )      <<  6 ) |
                                        ( ( ( blue  >> 3 ) & 0x1f )      <<  1 ) |
                                        ( ( ( alpha > 0x7f ) ? 0x1 : 0 ) <<  0 );
                    }
                    else if ( colorBuffer.format == PICA_DATA_COLOR_RGB565 )
                    {
                        colorByteSize = colorBuffer.width * colorBuffer.height * 2;
                        colorWidth    = 16;
                        clearColor    = ( ( ( red   >> 3 ) & 0x1f ) << 11 ) |
                                        ( ( ( green >> 2 ) & 0x3f ) <<  5 ) |
                                        ( ( ( blue  >> 3 ) & 0x1f ) <<  0 );
                    }
                    else if ( colorBuffer.format == PICA_DATA_COLOR_RGBA4 )
                    {
                        u8 alpha = FloatToUnsignedByte( colorBuffer.clearColor[ 3 ] );

                        colorByteSize = colorBuffer.width * colorBuffer.height * 2;
                        colorWidth    = 16;
                        clearColor    = ( ( ( red   >> 4 ) & 0xf ) << 12 ) |
                                        ( ( ( green >> 4 ) & 0xf ) <<  8 ) |
                                        ( ( ( blue  >> 4 ) & 0xf ) <<  4 ) |
                                        ( ( ( alpha >> 4 ) & 0xf ) <<  0 );
                    }
                }

                // The depthByteSize fill size must be a multiple of 16.
                u32 depthByteSize = 0;
                u32 clearDepth    = 0;
                u32 depthWidth    = 0;
                
                if ( ( bufferBit & DEPTH_BUFFER_BIT ) || ( bufferBit & STENCIL_BUFFER_BIT ) )
                {
                    depthStencilBuffer.clearDepth = 
                        ( depthStencilBuffer.clearDepth > 1.0f ) ? 1.0f :
                        ( ( depthStencilBuffer.clearDepth < 0.0f ) ? 0.0f : depthStencilBuffer.clearDepth );

                    if ( depthStencilBuffer.format == PICA_DATA_DEPTH24_STENCIL8_EXT )
                    {
                        depthByteSize = depthStencilBuffer.width * depthStencilBuffer.height * 4;
                        clearDepth    = ( depthStencilBuffer.clearStencil ) << 24 |
                                        Float32ToUnsignedFix24( depthStencilBuffer.clearDepth );
                        depthWidth    = 32;
                    }
                    else if ( depthStencilBuffer.format == PICA_DATA_DEPTH_COMPONENT16 )
                    {
                        depthByteSize = depthStencilBuffer.width * depthStencilBuffer.height * 2;
                        clearDepth    = Float32ToUnsignedFix16( depthStencilBuffer.clearDepth );
                        depthWidth    = 16;
                    }
                    else if ( depthStencilBuffer.format == PICA_DATA_DEPTH_COMPONENT24_OES )
                    {
                        depthByteSize = depthStencilBuffer.width * depthStencilBuffer.height * 3;
                        clearDepth    = Float32ToUnsignedFix24( depthStencilBuffer.clearDepth );
                        depthWidth    = 24;
                    }
                }
                
                if ( ( bufferBit & COLOR_BUFFER_BIT ) || ( bufferBit & DEPTH_BUFFER_BIT ) )
                {       
                    if ( isAddSplitDrawCmdlist )
                    {
                        nngxSplitDrawCmdlist();
                    }

                    nngxAddMemoryFillCommand( 
                        ( bufferBit & COLOR_BUFFER_BIT ) ? reinterpret_cast<GLvoid*>( colorBuffer.virtualAddr ) : 0,
                        colorByteSize, clearColor, colorWidth,
                        ( ( bufferBit & DEPTH_BUFFER_BIT ) || 
                          ( bufferBit & STENCIL_BUFFER_BIT ) ||
                          ( bufferBit & DEPTH_STENCIL_BUFFER_BIT ) ) ?
                        reinterpret_cast<GLvoid*>( depthStencilBuffer.virtualAddr ) : 0,
                        depthByteSize, clearDepth, depthWidth );
                }
            }

            void FrameBuffer::FrameBuffer::MakeClearRequestRaw( nngxCommandList* commandList, const u32 bufferBit, bool isAddSplitDrawCmdlist )
            { 
                // The colorByteSize fill size must be a multiple of 16.
                u32 colorByteSize = 0;
                u32 colorWidth    = 0;
                u32 clearColor    = 0;

                if ( bufferBit & COLOR_BUFFER_BIT )
                {
                    u8 red   = FloatToUnsignedByte( colorBuffer.clearColor[ 0 ] );
                    u8 green = FloatToUnsignedByte( colorBuffer.clearColor[ 1 ] );
                    u8 blue  = FloatToUnsignedByte( colorBuffer.clearColor[ 2 ] );
                    
                    if ( colorBuffer.format == PICA_DATA_COLOR_RGBA8_OES )
                    {
                        u8 alpha = FloatToUnsignedByte( colorBuffer.clearColor[ 3 ] );

                        colorByteSize = colorBuffer.width * colorBuffer.height * 4;
                        colorWidth    = 32;
                        // Clamp float32, and convert to u8.
                        clearColor    = ( red   << 24 ) |
                                        ( green << 16 ) |
                                        ( blue  <<  8 ) |
                                        ( alpha <<  0 ) ;
                    }
                    else if ( colorBuffer.format == PICA_DATA_COLOR_RGB5_A1 )
                    {
                        u8 alpha = FloatToUnsignedByte( colorBuffer.clearColor[ 3 ] );

                        colorByteSize = colorBuffer.width * colorBuffer.height * 2;
                        colorWidth    = 16;
                        clearColor    = ( ( ( red   >> 3 ) & 0x1f )      << 11 ) |
                                        ( ( ( green >> 3 ) & 0x1f )      <<  6 ) |
                                        ( ( ( blue  >> 3 ) & 0x1f )      <<  1 ) |
                                        ( ( ( alpha > 0x7f ) ? 0x1 : 0 ) <<  0 );
                    }
                    else if ( colorBuffer.format == PICA_DATA_COLOR_RGB565 )
                    {
                        colorByteSize = colorBuffer.width * colorBuffer.height * 2;
                        colorWidth    = 16;
                        clearColor    = ( ( ( red   >> 3 ) & 0x1f ) << 11 ) |
                                        ( ( ( green >> 2 ) & 0x3f ) <<  5 ) |
                                        ( ( ( blue  >> 3 ) & 0x1f ) <<  0 );
                    }
                    else if ( colorBuffer.format == PICA_DATA_COLOR_RGBA4 )
                    {
                        u8 alpha = FloatToUnsignedByte( colorBuffer.clearColor[ 3 ] );

                        colorByteSize = colorBuffer.width * colorBuffer.height * 2;
                        colorWidth    = 16;
                        clearColor    = ( ( ( red   >> 4 ) & 0xf ) << 12 ) |
                                        ( ( ( green >> 4 ) & 0xf ) <<  8 ) |
                                        ( ( ( blue  >> 4 ) & 0xf ) <<  4 ) |
                                        ( ( ( alpha >> 4 ) & 0xf ) <<  0 );
                    }
                }

                // The depthByteSize fill size must be a multiple of 16.
                u32 depthByteSize = 0;
                u32 clearDepth    = 0;
                u32 depthWidth    = 0;
                
                if ( ( bufferBit & DEPTH_BUFFER_BIT ) || ( bufferBit & STENCIL_BUFFER_BIT ) )
                {
                    depthStencilBuffer.clearDepth = 
                        ( depthStencilBuffer.clearDepth > 1.0f ) ? 1.0f :
                        ( ( depthStencilBuffer.clearDepth < 0.0f ) ? 0.0f : depthStencilBuffer.clearDepth );

                    if ( depthStencilBuffer.format == PICA_DATA_DEPTH24_STENCIL8_EXT )
                    {
                        depthByteSize = depthStencilBuffer.width * depthStencilBuffer.height * 4;
                        clearDepth    = ( depthStencilBuffer.clearStencil ) << 24 |
                                        Float32ToUnsignedFix24( depthStencilBuffer.clearDepth );
                        depthWidth    = 32;
                    }
                    else if ( depthStencilBuffer.format == PICA_DATA_DEPTH_COMPONENT16 )
                    {
                        depthByteSize = depthStencilBuffer.width * depthStencilBuffer.height * 2;
                        clearDepth    = Float32ToUnsignedFix16( depthStencilBuffer.clearDepth );
                        depthWidth    = 16;
                    }
                    else if ( depthStencilBuffer.format == PICA_DATA_DEPTH_COMPONENT24_OES )
                    {
                        depthByteSize = depthStencilBuffer.width * depthStencilBuffer.height * 3;
                        clearDepth    = Float32ToUnsignedFix24( depthStencilBuffer.clearDepth );
                        depthWidth    = 24;
                    }
                }
                
                if ( ( bufferBit & COLOR_BUFFER_BIT ) || ( bufferBit & DEPTH_BUFFER_BIT ) )
                {       
                    if ( isAddSplitDrawCmdlist )
                    {
                        nngxSplitDrawCmdlistRaw(commandList);
                    }

                    nngxAddMemoryFillCommandRaw( 
                        commandList,
                        ( bufferBit & COLOR_BUFFER_BIT ) ? reinterpret_cast<GLvoid*>( colorBuffer.virtualAddr ) : 0,
                        colorByteSize, clearColor, colorWidth,
                        ( ( bufferBit & DEPTH_BUFFER_BIT ) || 
                          ( bufferBit & STENCIL_BUFFER_BIT ) ||
                          ( bufferBit & DEPTH_STENCIL_BUFFER_BIT ) ) ?
                        reinterpret_cast<GLvoid*>( depthStencilBuffer.virtualAddr ) : 0,
                        depthByteSize, clearDepth, depthWidth );
                }
            }

        } // namespace CTR
    } // namespace gr
} // namespace nn
