/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Combiner.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_COMBINER_H_
#define NN_GR_COMBINER_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class Combiner
            {
            public :
                /* Please see man pages for details 
                    
                 */
                class Stage
                {
                public :
                    /* Please see man pages for details 
                        
                     */ 
                    struct CombineFunction
                    {
                        /* Please see man pages for details 
                            
                                   
                                   
                                   
                                   
                        */
                        PicaDataTexEnvCombine combine;

                        /* Please see man pages for details 
                            
                                   
                                   
                                   
                                   
                                   
                                   
                        */
                        PicaDataTexEnvOperand operand[3];
                          
                        /* Please see man pages for details 
                            
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                        */
                        PicaDataTexEnvSrc source[3];

                        /* Please see man pages for details 
                            
                                   
                                   
                                   
                                   
                                   
                        */
                        PicaDataTexEnvScale scale;
                       
                        /* Please see man pages for details 
                            
                                   
                                   
                                   
                                   
                                   
                        */
                        PicaDataTexEnvBufferInput bufferInput;
                 
                        /* Please see man pages for details 
                            

                            
                            
                        */
                        explicit CombineFunction( const u8 stage_index, bool is_rgb );

                    protected :
                        /* Please see man pages for details 
                            
                        */
                        friend class Stage;

                        /* Please see man pages for details 
                            
                        */
                        explicit CombineFunction(){};
                    };

                    /* Please see man pages for details 
                        
                               
                    */
                    CombineFunction rgb;

                    /* Please see man pages for details 
                        
                               
                    */
                    CombineFunction alpha;

                    /* Please see man pages for details 
                        
                               
                    */
                    u8 constColorR;

                    /* Please see man pages for details 
                        
                               
                    */
                    u8 constColorG;

                    /* Please see man pages for details 
                        
                               
                    */
                    u8 constColorB;

                    /* Please see man pages for details 
                        
                               
                    */
                    u8 constColorA;
                    
                    /* Please see man pages for details 
                        
                               
                    */
                    PicaReg headRegister;

                public :
                    /* Please see man pages for details 
                        
                    */
                    void SetupPrimary( void );
                    
                    /* Please see man pages for details 
                        
                    */
                    void SetupFragmentPrimary( void );

                    /* Please see man pages for details 
                        
                    */
                    void SetupTexture0( void );

                    /* Please see man pages for details 
                        
                    */
                    void SetupPrevious( void );

                    /* Please see man pages for details 
                        
                    */
                    void SetupPrimaryModulateTexture0( void );

                    /* Please see man pages for details 
                        
                    */
                    void SetupFragmentPrimaryModulateTexture0( void );

                    /* Please see man pages for details 
                        
                        
                        
                    */
                    explicit Stage( const int stage_index );
                    
                    /* Please see man pages for details 
                        
                               

                        
                        
                        
                        
                    */
                    bit32* MakeCommand( bit32* command ) const;

                    /* Please see man pages for details 
                        

                        
                        
                        
                    */
                    bit32* MakeConstantColorCommand( bit32* command ) const
                    {
                        NN_GR_ASSERT( ( PICA_REG_TEX_ENV0 <= headRegister ) &&
                                      ( PICA_REG_TEX_ENV5 >= headRegister ) );

                        u32 constColorReg = headRegister + 3;
                        
                        *command++ = PICA_CMD_DATA_TEX_ENV_CONST(
                                        constColorR, constColorG,
                                        constColorB, constColorA );
                                        
                        *command++ = PICA_CMD_HEADER_SINGLE( constColorReg );

                        return command;
                    }

                protected :
                    /* Please see man pages for details 
                        
                    */
                    friend class Combiner;

                    /* Please see man pages for details 
                        
                    */
                    explicit Stage( void )
                    {
                    };
                };

            public :
                //
                static const u32 COMBINER_STAGE_MAX = 6;

                /* Please see man pages for details 
                    
                           
                           
                           
                           
                */
                Stage stage[ COMBINER_STAGE_MAX ];

            public :
                /* Please see man pages for details 
                    
                           
                */
                u8 bufferColorR;

                /* Please see man pages for details 
                     
                            
                 */
                u8 bufferColorG;

                /* Please see man pages for details 
                     
                            
                 */
                u8 bufferColorB;

                /* Please see man pages for details 
                     
                            
                 */
                u8 bufferColorA;
                
                /* Please see man pages for details 
                     
                 */
                explicit Combiner();

                /* Please see man pages for details 
                    
                           
                    
                    

                    

                    
                */
                bit32* MakeCommand( bit32* command ) const;


                /* Please see man pages for details 
                    
                    
                    

                    
                 */
                bit32* MakeCombinerBufferCommand( bit32* command ) const;
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_COMBINER_H_
