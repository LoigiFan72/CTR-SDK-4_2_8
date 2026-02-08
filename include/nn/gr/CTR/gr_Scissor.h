/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Scissor.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_SCISSOR_H_
#define NN_GR_SCISSOR_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
            */
            class Scissor
            {
            public:
                /* Please see man pages for details 
                    
                 */
                Scissor():
                isEnable( true ),
                x( 0 ),
                y( 0 ),
                width( 240 ),
                height( 320 ),
                bufferWidth( 256 ),
                bufferHeight( 320 )
                {
                }

                /* Please see man pages for details 
                    

                    
                    
                    
                    
                    
                    
                    
                */
                Scissor( bool isEnable_, s32 x_, s32 y_, u32 width_, u32 height_, s32 bufferWidth_, s32 bufferHeight_ ) :
                isEnable( isEnable_ ),
                x( x_ ),
                y( y_ ),
                width( width_ ),
                height( height_ ),
                bufferWidth( bufferWidth_ ),
                bufferHeight( bufferHeight_ )
                {
                }
                
            public:
                /* Please see man pages for details 
                    
                 
                    

                    
                 */
                bit32* MakeCommand( bit32* command ) const;

                /* Please see man pages for details 
                    

                    
                    
                    

                    
                 */
                static bit32* MakeDisableCommand( bit32* command,
                    const s32 colorBufferWidth,
                    const s32 colorBufferHeight )
                {
                    s32 temp_width  = colorBufferWidth  - 1;
                    s32 temp_height = colorBufferHeight - 1;
                
                    // 0x65-0x67
                    *command++ = PICA_CMD_DATA_SCISSOR( false );
                    *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_SCISSOR, 3 );
                    *command++ = 0;
                    *command++ = PICA_CMD_DATA_SCISSOR_SIZE( temp_width, temp_height );

                    return command;
                }
               
            public:
                /* Please see man pages for details 
                    

                    
                    
                    
                    
                 */
                void Set( s32 x_, s32 y_, u32 width_, u32 height_ )
                {
                    x = x_; y = y_; width = width_; height = height_;
                }
                
                /* Please see man pages for details 
                    

                    
                    
                 */
                void SetBufferSize( s32 bufferWidth_, s32 bufferHeight_ )
                {
                    bufferWidth = bufferWidth_; bufferHeight = bufferHeight_;
                }
                
            public:
                /* Please see man pages for details 
                    
                */
                bool    isEnable;
                NN_PADDING3;

                /* Please see man pages for details 
                    
                */
                s32        x;

                /* Please see man pages for details 
                    
                */
                s32        y;

                /* Please see man pages for details 
                    
                */
                u32        width;

                /* Please see man pages for details 
                    
                */
                u32        height;

                /* Please see man pages for details 
                    
                */
                s32        bufferWidth;

                /* Please see man pages for details 
                    
                */
                s32        bufferHeight;
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_SCISSOR_H_
