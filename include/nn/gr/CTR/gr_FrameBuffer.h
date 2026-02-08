/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_FrameBuffer.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47820 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_FRAME_BUFFER_H_
#define NN_GR_FRAME_BUFFER_H_

#include <nn/gr/CTR/gr_Utility.h>
#include <nn/gx/CTR/gx_CTRRaw.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class FrameBuffer
            {
            public :
                static const u32 COLOR_BUFFER_BIT         = 0x1; //
                static const u32 DEPTH_BUFFER_BIT         = 0x2; //
                static const u32 STENCIL_BUFFER_BIT       = 0x4; //
                static const u32 DEPTH_STENCIL_BUFFER_BIT = DEPTH_BUFFER_BIT | STENCIL_BUFFER_BIT; //

                /* Please see man pages for details 
                    
                 */
                enum BlockSize
                {
                    /* Please see man pages for details 
                        
                    */
                    BLOCK_SIZE8  = 0x0,

                    /* Please see man pages for details 
                        
                               
                    */
                    BLOCK_SIZE32 = 0x1
                };
                
                /* Please see man pages for details 
                    
                */
                class ColorBuffer
                {
                public :
                    /* Please see man pages for details 
                        
                    */
                    uptr  virtualAddr;

                    /* Please see man pages for details 
                        
                    */
                    PicaDataColor format;

                    /* Please see man pages for details 
                        
                    */
                    BlockSize blockSize;
                    NN_PADDING2;

                    /* Please see man pages for details 
                        
                    */
                    s32 width;

                    /* Please see man pages for details 
                        
                    */
                    s32 height;
                    
                    /* Please see man pages for details 
                        
                               
                     */
                    f32 clearColor[ 4 ];

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit ColorBuffer( const FrameBuffer& frameBuffer_ );

                    /* Please see man pages for details 
                        
                        
                        
                        
                        
                     */
                    bit32* MakeRenderBlockModeCommand( bit32* command ) const;
                    
                    /* Please see man pages for details 
                        
                        
                        
                        
                        
                        
                     */
                    bit32* MakeCommand( bit32* command, bool isAddRenderBlockMode = false ) const;

                protected :
                    const FrameBuffer& m_FrameBuffer;
                };

                /* Please see man pages for details 
                    
                */
                class DepthStencilBuffer
                {
                public :
                    /* Please see man pages for details 
                        
                    */
                    uptr  virtualAddr;

                    /* Please see man pages for details 
                        
                    */
                    PicaDataDepth format;
                    NN_PADDING3;

                    /* Please see man pages for details 
                        
                    */
                    s32 width;

                    /* Please see man pages for details 
                        
                    */
                    s32 height;

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    f32 clearDepth;

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    u8 clearStencil;
                    NN_PADDING3;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit DepthStencilBuffer( const FrameBuffer& frameBuffer_ );

                    /* Please see man pages for details 
                        
                        
                        
                        
                        
                     */
                    bit32* MakeCommand( bit32* command ) const;

                protected :
                    const FrameBuffer& m_FrameBuffer;
                };
            
            public :
                /* Please see man pages for details 
                    
                           
                 */
                ColorBuffer colorBuffer;

                /* Please see man pages for details 
                    
                           
                 */
                DepthStencilBuffer depthStencilBuffer;
                
                /* Please see man pages for details 
                    
                 */
                s32 width;

                /* Please see man pages for details 
                    
                 */
                s32 height;

            public :
                /* Please see man pages for details 
                    

                    
                         
                 */
                explicit FrameBuffer();

                /* Please see man pages for details 
                    
                           
                    
                    
                    
                    
                 */
                static bit32* MakeClearCacheCommand( bit32* command );

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                    

                    
                         
                 */
                bit32* MakeCommand( bit32* command, const u32 bufferBit, bool isClearCache = true ) const;

                /* Please see man pages for details 
                    
                           
                           

                    
                    
                 */
                void MakeClearRequest( const u32 bufferBit, bool isAddSplitDrawCmdlist = true );
                void MakeClearRequestRaw( nngxCommandList* commandList, const u32 bufferBit, bool isAddSplitDrawCmdlist = true );
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_FRAME_BUFFER_H_
