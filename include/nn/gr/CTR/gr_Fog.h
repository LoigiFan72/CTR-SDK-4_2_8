/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Fog.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_FRAGMENT_FOG_H_
#define NN_GR_FRAGMENT_FOG_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class Fog
            {
            public :
                //
                static const u32 FOG_LOOKUP_TABLE_ELEMENT_NUM = 128;

            public :
                /* Please see man pages for details 
                    
                           
                */
                bool isEnable;

                /* Please see man pages for details 
                    
                           
                */
                bool isEnableZFlip;

                /* Please see man pages for details 
                    
                           
                */
                u8 colorR;

                /* Please see man pages for details 
                    
                           
                */
                u8 colorG;

                /* Please see man pages for details 
                    
                           
                */
                u8 colorB;
                NN_PADDING3;
                
            public :
                /* Please see man pages for details 
                    
                    
                    
                    
                */
                void SetTable( const f32 table[ FOG_LOOKUP_TABLE_ELEMENT_NUM ],
                               const f32 lastDiffValue = 0.0f );

                /* Please see man pages for details 
                    
                    
                    

                    
                 */
                bit32* MakeAllCommand( bit32* command ) const
                {
                    // Set command
                    command = MakeConfigCommand( command );

                    // Fog lookup table commands
                    if ( isEnable )
                    {
                        command = MakeTableCommand( command );
                    }
                    return command;
                }


                /* Please see man pages for details 
                    
                    
                    

                    
                 */
                static bit32* MakeDisableCommand( bit32* command )
                {
                    // 0x0e0
                    *command++ = PICA_DATA_FOG_FALSE;
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_GAS_FOG_MODE, 0x1 );
   
                    return command;
                }

                /* Please see man pages for details 
                    
                    
                    

                    
                 */
                bit32* MakeConfigCommand( bit32* command ) const
                {
                    // 0x0e0
                    *command++ = ( isEnable ? PICA_DATA_FOG : PICA_DATA_FOG_FALSE ) | ( ( isEnableZFlip ? 1 : 0 ) << 16 );
                    *command++ = PICA_CMD_HEADER_SINGLE_BE( PICA_REG_GAS_FOG_MODE, 0x5 );

                    // 0x0e1
                    *command++ = colorR | colorG << 8 | colorB << 16;
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FOG_COLOR );

                    return command;
                }

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                 */
                bit32* MakeTableCommand( bit32* command ) const
                {
                    std::memcpy( command, m_TableCommand, sizeof( m_TableCommand ) );
                    return command + ( FOG_LOOKUP_TABLE_ELEMENT_NUM + 4 );
                }

            public :
                /* Please see man pages for details 
                    
                */
                Fog() : 
                isEnable( false ),
                isEnableZFlip( false ),
                colorR( 0 ),
                colorG( 0 ),
                colorB( 0 )
                {
                    for ( u32 index = 0; index < (  FOG_LOOKUP_TABLE_ELEMENT_NUM + 4 ); index++ )
                    {
                        m_TableCommand[ index ] = 0;
                    }
                }
                
            protected :
                /* Please see man pages for details 
                    
                           
                */
                u32 m_TableCommand[ FOG_LOOKUP_TABLE_ELEMENT_NUM + 4 ];
            };

        } // namespace CTR
    } // namespace gr
} //namespace nn

#endif // NN_GR_FRAGMENT_FOG_H_
