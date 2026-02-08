/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Viewport.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_VIEWPORT_H_
#define NN_GR_VIEWPORT_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
                       
            */
            class Viewport
            {
            public:
                /* Please see man pages for details 
                    
                */
                Viewport( void ) :
                x( 0 ),
                y( 0 ),
                width( 240 ),
                height( 320 )
                {
                }

                /* Please see man pages for details 
                    

                    
                    
                    
                    
                 */
                Viewport( s32 x_, s32 y_, u32 width_, u32 height_ ) :
                x( x_ ),
                y( y_ ),
                width( width_ ),
                height( height_ )
                {
                }
            
            public:
                /* Please see man pages for details 
                    
                
                    

                    
                */
                bit32* MakeCommand( bit32* command ) const;
            
            public:
                /* Please see man pages for details 
                    
                           

                    
                    
                    
                    
                */
                void Set( s32 x_, s32 y_, u32 width_, u32 height_ )
                {
                    x = x_; y = y_; width = width_; height = height_;
                }
            
            public:
                /* Please see man pages for details 
                    
                */
                s32 x;

                /* Please see man pages for details 
                    
                */
                s32 y;

                /* Please see man pages for details 
                    
                */
                u32 width;

                /* Please see man pages for details 
                    
                */
                u32 height;
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_VIEWPORT_H_
