/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_LookUpTable.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_LOOK_UP_TABLE_H_
#define NN_GR_LOOK_UP_TABLE_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class LookUpTable
            {
            public :
                //
                static const u32 LOOKUP_TABLE_ELEMENT_NUM = 256;

                //
                static const u32 LOOKUP_TABLE_CMD_NUM     = LOOKUP_TABLE_ELEMENT_NUM + 2;
                
                /* Please see man pages for details 
                    
                */
                LookUpTable()
                {
                }
  
            public :
                /* Please see man pages for details 
                    
                    
                    
                    
                    
                 */
                void SetTable( const f32 table[ LOOKUP_TABLE_ELEMENT_NUM ],
                               const f32 lastDiffValue = 0.0f,
                               const bool isInputAbs   = true );

                /* Please see man pages for details 
                    
                    
                    
                    
                 */
                void SetAbsTable( const f32 table[ LOOKUP_TABLE_ELEMENT_NUM ],
                                  const f32 lastDiffValue = 0.0f );

                /* Please see man pages for details 
                    
                    
                    
                    
                 */
                void SetNotAbsTable( const f32 table[ LOOKUP_TABLE_ELEMENT_NUM ],
                                     const f32 lastDiffValue = 0.0f );


                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                */

                bit32* MakeCommand( bit32* command, const PicaDataFragLightSampler type ) const
                {
                    // 0x1c5
                    *command++ = PICA_CMD_DATA_FRAG_LIGHT_LUT( 0, type );
                    *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_FRAG_LIGHT_LUT );

                    std::memcpy( command, m_TableCommand, sizeof( m_TableCommand ) );

                    return command + LOOKUP_TABLE_CMD_NUM;
                };

                /* Please see man pages for details 
                    
                 
                    
                    
                    
                    
                 */
                bit32* MakeSpotTableCommand( bit32* command, u8 light_id ) const
                {
                    return MakeCommand( command, static_cast< PicaDataFragLightSampler >( PICA_DATA_SAMPLER_SP + light_id  ) );
                }

                /* Please see man pages for details 
                    
                 
                    
                    
                    
                    
                 */
                bit32* MakeDistAttnTableCommand( bit32* command, u8 light_id ) const
                {
                    return MakeCommand( command, static_cast< PicaDataFragLightSampler >( PICA_DATA_SAMPLER_DA + light_id  ) );
                }

            protected :
                /* Please see man pages for details 
                    
                           
                           
                */
                bit32 m_TableCommand[ LOOKUP_TABLE_CMD_NUM ];
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_LOOK_UP_TABLE_H_
