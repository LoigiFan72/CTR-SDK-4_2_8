/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Utility.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48274 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_Utility.h>

#include <nn/gr/CTR/gr_Shader.h>
#include <nn/gr/CTR/gr_Vertex.h>
#include <nn/gr/CTR/gr_Fog.h>
#include <nn/gr/CTR/gr_FragmentLight.h>
#include <nn/gr/CTR/gr_Texture.h>
#include <nn/gr/CTR/gr_RenderState.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            CommandBufferJumpHelper::CommandBufferJumpHelper(bit32* address)
                : m_CurrentPtr(address)
                , m_StartPtr(address)
                , m_ReturnPtr(address)
                , m_CmdSizePtr(0)
                , m_SizeToFirstJump(0)
            {
            }

            CommandBufferJumpHelper::~CommandBufferJumpHelper()
            {
            }

            void CommandBufferJumpHelper::FinalizeJump(bit32* endAddress)
            {
                m_CurrentPtr      = endAddress;

                if ( m_CmdSizePtr )
                {
                    *(reinterpret_cast<u32*>(m_CmdSizePtr)) = GetOffsetFromPtr(m_ReturnPtr, m_CurrentPtr) >> 3;
                }

                m_StartPtr        = m_CurrentPtr;
                m_ReturnPtr       = m_CurrentPtr;
                m_CmdSizePtr      = 0;
                m_SizeToFirstJump = 0;
            }

            bit32* AddDummyDataForCommandBuffer( bit32* command, const size_t addSize )
            {
                if ( addSize % 16 )
                {
                    int num = (addSize >> 2) % 4;

                    for ( int i=4; i>num; --i )
                    {
                        *command++ = 0;
                    }
                }
                return command;
            }

            // Compiles with ARM code
            #include <nn/hw/ARM/code32.h>

            //--------------------------------------------------------------------------------
            asm void CopyMtx34WithHeader(
                f32*                   /* dst */,
                const nn::math::MTX34* /* src */,
                u32                    /* header */ )
            {
                VLDMIA      r1!,{s0-s11}
                STR         r2,[r0,#4]
                VSTR.F32    s0,[r0,#16]
                VSTR.F32    s1,[r0,#12]
                VSTR.F32    s2,[r0,#8]
                VSTR.F32    s3,[r0,#0]
                VSTR.F32    s4,[r0,#32]
                VSTR.F32    s5,[r0,#28]
                VSTR.F32    s6,[r0,#24]
                VSTR.F32    s7,[r0,#20]
                VSTR.F32    s8,[r0,#48]
                VSTR.F32    s9,[r0,#44]
                VSTR.F32    s10,[r0,#40]
                VSTR.F32    s11,[r0,#36]
                BX      lr
            }

            //--------------------------------------------------------------------------------

            asm void CopyMtx44WithHeader(
                f32*                    /* dst */,
                const nn::math::MTX44*  /* src */,
                u32                     /* header */ )
            {
                VLDMIA      r1!,{s0-s15}
                STR     r2,[r0,#4]
                VSTR.F32    s0,[r0,#16]
                VSTR.F32    s1,[r0,#12]
                VSTR.F32    s2,[r0,#8]
                VSTR.F32    s3,[r0,#0]
                VSTR.F32    s4,[r0,#32]
                VSTR.F32    s5,[r0,#28]
                VSTR.F32    s6,[r0,#24]
                VSTR.F32    s7,[r0,#20]
                VSTR.F32    s8,[r0,#48]
                VSTR.F32    s9,[r0,#44]
                VSTR.F32    s10,[r0,#40]
                VSTR.F32    s11,[r0,#36]
                VSTR.F32    s12,[r0,#64]
                VSTR.F32    s13,[r0,#60]
                VSTR.F32    s14,[r0,#56]
                VSTR.F32    s15,[r0,#52]
                BX      lr
            }
            
            // Restores the original settings
            #include <nn/hw/ARM/codereset.h>

            //--------------------------------------------------------------------------------

            bit32* MakeDisableAllCommand( bit32* command )
            {
                // Disable Shader
                command = nn::gr::CTR::Shader::MakeDisableCommand( command );

                // Disable Vertex
                command = nn::gr::CTR::Vertex::MakeDisableCommand( command );

                // Disable Fog/Gas
                command = nn::gr::CTR::Fog::MakeDisableCommand( command );

                // Disable FragmentLight
                command = nn::gr::CTR::FragmentLight::MakeDisableCommand( command );

                // Disable Texture
                command = nn::gr::CTR::Texture::MakeDisableCommand( command );

                // Disable Early depth 0x62[0:0]
                *command++ = 0x0;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_EARLY_DEPTH_TEST1, 0x1 );
                // Disable Early depth 0x118[0:0]
                *command++ = 0x0;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_EARLY_DEPTH_TEST2, 0x1 );

                // Disable Clipping Plane 0x47[0:0]
                *command++ = 0x0;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_FRAGOP_CLIP, 0x1 );

                // Disable RenderState
                command = nn::gr::CTR::RenderState::MakeDisableCommand( command );

                // Set 8x8 RenderBlockMode 0x11b[0:0]
                *command++ = 0x0;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_RENDER_BLOCK_FORMAT );

                return command;
            }

            //--------------------------------------------------------------------------------

            bit32* MakeChannelKickCommand( bit32* command, const CommandBufferChannel channel )
            {
                NN_GR_ASSERT( channel == CMD_BUF_CH0 || channel == CMD_BUF_CH1 );
                
                // Kick register  0x23c or 0x23d [31:0] (any value is OK)
                *command++ = 0x1;
                *command++ = PICA_CMD_HEADER_SINGLE( channel == CMD_BUF_CH0 ? PICA_REG_COMMAND_BUF_KICK_CH0 : PICA_REG_COMMAND_BUF_KICK_CH1 );
                
                return command;
            }
            
            //------------------------------------------------------------------------------------
            
            bit32* MakeChannel0SubroutineCommand( bit32* command, uptr* bufferSizePtr,
                                                  const uptr commandBufferPtr, const size_t commandBufferSize )
            {
                // The address of the command buffer specified as the subroutine is 16-byte aligned and the byte size is a multiple of 16
                NN_GR_ASSERT( (commandBufferPtr >> 3) % 2 == 0 && (commandBufferSize >> 3) % 2 == 0 );
                
                // When executed with the subroutine as channel 0 and the return destination as channel 1, all required registers can be set with burst access.

                // Subroutine command buffer size 0x238[20:0]
                *command++ = commandBufferSize >> 3;
                *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_COMMAND_BUF_SIZE_CH0, 5 );
                
                // Buffer size after returning from the subroutine 0x239[20:0]
                // Since it is unknown at this time, enter dummy data and return an address
                *bufferSizePtr = reinterpret_cast<uptr>(command);
                *command++ = 0;
                
                // Subroutine address 0x23a[28:0]
                *command++ = nngxGetPhysicalAddr(commandBufferPtr) >> 3;
                
                // Return destination from the subroutine 0x23b[28:0]
                *command++ = nngxGetPhysicalAddr(reinterpret_cast<uptr>(command + 2)) >> 3;
                
                // Subroutine kick command 0x23c[31:0] (any value is OK)
                *command++ = 0x1;
                
                return command;
            }

            bit32* MakeChannel1SubroutineCommand( bit32* command, uptr* bufferSizePtr,
                                                  const uptr commandBufferPtr, const size_t commandBufferSize )
            {
                // Buffer size after returning from the subroutine 0x238[20:0]
                // Since it is unknown at this time, enter dummy data and return an address
                *bufferSizePtr = reinterpret_cast<uptr>(command);
                *command++ = 0;
                *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_COMMAND_BUF_SIZE_CH0, 3 );
                
                // Subroutine command buffer size 0x239[20:0]
                *command++ = commandBufferSize >> 3;
                
                // Return destination address from the subroutine 0x23a[28:0]
                *command++ = nngxGetPhysicalAddr(reinterpret_cast<uptr>(command + 5)) >> 3;
                
                // Subroutine address 0x23b[28:0]
                *command++ = nngxGetPhysicalAddr(commandBufferPtr) >> 3;
                
                // Dummy data (for 64-bit alignment)
                *command++ = 0;
                
                // Kick register  0x23d [31:0] (any value is OK)
                *command++ = 0x1;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COMMAND_BUF_KICK_CH1 );
                
                return command;
            }

            //------------------------------------------------------------------------------------
            
            bit32* MakeChannel0JumpCommand( bit32* command, const uptr commandBufferPtr, const size_t commandBufferSize )
            {
                // The address of the command buffer specified as the subroutine is 16-byte aligned and the byte size is a multiple of 16
                NN_GR_ASSERT( (commandBufferPtr >> 3) % 2 == 0 && (commandBufferSize >> 3) % 2 == 0 );
                
                // Command buffer size 0x238 or 0x239[20:0]
                *command++ = commandBufferSize >> 3;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_COMMAND_BUF_SIZE_CH0, 0x7 );
                
                // Command buffer address 0x23a or 0x23b[28:0]
                *command++ = nngxGetPhysicalAddr(commandBufferPtr) >> 3;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COMMAND_BUF_ADDR_CH0 );
                
                // Kick register  0x23c or 0x23d [31:0] (any value is OK)
                *command++ = 0x1;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COMMAND_BUF_KICK_CH0 );
                
                return command;
            }

            //------------------------------------------------------------------------------------
            
            bit32* MakeChannel1JumpCommand( bit32* command, const uptr commandBufferPtr, const size_t commandBufferSize )
            {
                // The address of the command buffer specified as the subroutine is 16-byte aligned and the byte size is a multiple of 16
                NN_GR_ASSERT( (commandBufferPtr >> 3) % 2 == 0 && (commandBufferSize >> 3) % 2 == 0 );
                
                // Command buffer size 0x238 or 0x239[20:0]
                *command++ = commandBufferSize >> 3;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_COMMAND_BUF_SIZE_CH1, 0x7 );
                
                // Command buffer address 0x23a or 0x23b[28:0]
                *command++ = nngxGetPhysicalAddr(commandBufferPtr) >> 3;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COMMAND_BUF_ADDR_CH1 );
                
                // Kick register  0x23c or 0x23d [31:0] (any value is OK)
                *command++ = 0x1;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_COMMAND_BUF_KICK_CH1 );
                
                return command;
            }

            bit32* MakePostVertexCacheEntryTypeCommand( bit32* command, const PostVertexCacheEntryType type )
            {
                NN_GR_ASSERT( type == POST_VERTEX_CACHE_ENTRY_TYPE_32 || type == POST_VERTEX_CACHE_ENTRY_TYPE_16 );
                
                // Register 0x22d [7:0] specifies number of entries in the post-vertex cache (do not access other bits)
                *command++ = ( type == POST_VERTEX_CACHE_ENTRY_TYPE_32 ? 0x04 : 0x84 );
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_POST_VERTEX_CACHE_NUM, 0x1 );
                
                return command;
            }
        } // namespace CTR
    } // namespace gr
} // namespace nn
