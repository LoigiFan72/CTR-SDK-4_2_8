/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Fog.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/gr/CTR/gr_Fog.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            void Fog::SetTable( const f32 table[ FOG_LOOKUP_TABLE_ELEMENT_NUM ],
                                const f32 lastDiffValue )
            {
                bit32* command = m_TableCommand;
                
                // 0x0e6
                *command++ = PICA_CMD_DATA_FOG_LUT_INDEX( 0 );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FOG_LUT_INDEX );
                
                // 0x0e8
                int i = 0;
                *command++ = ( Float32ToUnsignedFix11( table[ i ] ) << 13 ) | 
                               Float32ToFix13Fraction11( table[ i + 1 ] - table[ i ] );
                *command++ = PICA_CMD_HEADER_BURST( PICA_REG_FOG_LUT_DATA0, 128 );
                
                for ( ++i; i < 0x7F; ++i )
                {
                    *command++ = ( Float32ToUnsignedFix11( table[ i ] ) << 13 ) | 
                                   Float32ToFix13Fraction11( table[ i + 1 ] - table[ i ] );
                }

                *command++ = ( Float32ToUnsignedFix11( table[ i ] ) << 13 ) |
                               Float32ToFix13Fraction11( lastDiffValue );
                *command++ = 0;
            }

        } // namespace CTR
    } // namespace gr
} // namespace nn
