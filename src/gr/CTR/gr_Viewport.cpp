/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Viewport.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_Viewport.h>
#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            bit32* Viewport::MakeCommand( bit32* command ) const
            {
                // Converts to values to pack in commands
                u32 width24 = Float32ToFloat24( width / 2.f );
                u32 width31 = Float32ToFloat31( 2.f / width ) << 1;
                u32 height24 = Float32ToFloat24( height / 2.f );
                u32 height31 = Float32ToFloat31( 2.f / height ) << 1;

                // 0x41
                *command++ = width24;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_VIEWPORT_WIDTH1, 0x7 );

                // 0x42
                *command++ = width31;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VIEWPORT_WIDTH2 );

                // 0x43
                *command++ = height24;
                *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_VIEWPORT_HEIGHT1, 0x7 );

                // 0x44
                *command++ = height31;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VIEWPORT_HEIGHT2 );

                // 0x68
                *command++ = PICA_CMD_DATA_VIEWPORT_XY( x, y );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VIEWPORT_XY );
            
                return command;
            }

        } // namespace CTR
    } // namespace gr
} // namespace nn
