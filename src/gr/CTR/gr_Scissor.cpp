/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Scissor.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_Scissor.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            bit32* Scissor::MakeCommand( bit32* command ) const
            {
                s32 temp_width  = x + width  - 1;
                s32 temp_height = y + height - 1;
                
                *command++ = PICA_CMD_DATA_SCISSOR( isEnable );
                *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_SCISSOR, 3 );
                *command++ = PICA_CMD_DATA_SCISSOR_XY( x, y, bufferWidth, bufferHeight );
                *command++ = PICA_CMD_DATA_SCISSOR_SIZE( temp_width, temp_height );
                
                return command;
            }

        } // namespace CTR
    } // namespace gr
} // namespace nn
