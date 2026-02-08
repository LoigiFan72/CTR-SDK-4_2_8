/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_BindSymbol.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_BIND_SYMBOL_H_
#define NN_GR_BIND_SYMBOL_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
            */
            class BindSymbol
            {
            public :
                /* Please see man pages for details 
                    
                 */
                enum SymbolType
                {
                    //
                    SYMBOL_TYPE_INVALID, 
                    //
                    SYMBOL_TYPE_INPUT,   
                    //
                    SYMBOL_TYPE_FLOAT,
                    //
                    SYMBOL_TYPE_INTEGER, 
                    //
                    SYMBOL_TYPE_BOOL
                };
               
                /* Please see man pages for details 
                    
                 */
                enum ShaderType
                {
                    //
                    SHADER_TYPE_VERTEX,  
                    //
                    SHADER_TYPE_GEOMETRY 
                };

                /* Please see man pages for details 
                    
                           
                 */
                const ShaderType shaderType;

                /* Please see man pages for details 
                    
                           
                 */
                const SymbolType symbolType;

                /* Please see man pages for details 
                    
                           
                */
                u8 start;

                /* Please see man pages for details 
                    
                           
                */
                u8 end;
         
                /* Please see man pages for details 
                    
                           
                */
                const char* name;

            protected :
                /* Please see man pages for details 
                    

                    
                    
                */
                explicit BindSymbol( const ShaderType shader_type, const SymbolType symbol_type )
                    : shaderType( shader_type ),
                      symbolType( symbol_type ),
                      start( 0xff ),
                      end( 0xff ),
                      name( NULL )
                {
                }
            };

            /* Please see man pages for details 
                
             */
            class BindSymbolVSInput : public BindSymbol
            {
            public :
                /* Please see man pages for details 
                    
                */
                explicit BindSymbolVSInput() : 
                BindSymbol( SHADER_TYPE_VERTEX, SYMBOL_TYPE_INPUT )
                {
                }
            };

            /* Please see man pages for details 
                
             */
            class BindSymbolVSFloat : public BindSymbol
            {
            public :
                /* Please see man pages for details 
                    
                */
                explicit BindSymbolVSFloat() : 
                BindSymbol( SHADER_TYPE_VERTEX, SYMBOL_TYPE_FLOAT )
                {
                }

                /* Please see man pages for details 
                    
                    
                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::MTX34& mtx34 ) const
                {
                    return MakeUniformCommandVS( command, start, mtx34 );
                }

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::MTX44& mtx44 ) const
                {
                    return MakeUniformCommandVS( command, start, mtx44 );
                }

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::VEC4& vec4 ) const
                {
                    return MakeUniformCommandVS( command, start, vec4 );
                }
                
                /* Please see man pages for details 
                    

                    

                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::VEC4 vec4[], const int num ) const
                {
                    return MakeUniformCommandVS( command, start, vec4, num );
                }
            };

            /* Please see man pages for details 
                
             */
            class BindSymbolVSInteger : public BindSymbol
            {
            public :
                explicit BindSymbolVSInteger() :
                BindSymbol( SHADER_TYPE_VERTEX, SYMBOL_TYPE_INTEGER )
                {
                }

                /* Please see man pages for details 
                    

                    
                    
                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, u8 x, u8 y, u8 z ) const
                {
                    return MakeUniformCommandVS( command, start, x, y, z );
                }
            };

            /* Please see man pages for details 
                
             */
            class BindSymbolVSBool : public BindSymbol
            {
            public :
                /* Please see man pages for details 
                    
                */
                explicit BindSymbolVSBool( void ) :
                BindSymbol( SHADER_TYPE_VERTEX, SYMBOL_TYPE_BOOL )
                {
                }
            };

            /* Please see man pages for details 
                
             */
            class BindSymbolGSFloat : public BindSymbol
            {
            public :
                /* Please see man pages for details 
                    
                */
                explicit BindSymbolGSFloat( void ) : 
                BindSymbol( SHADER_TYPE_GEOMETRY, SYMBOL_TYPE_FLOAT )
                {
                }

                /* Please see man pages for details 
                    
                    
                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::MTX34& mtx34 ) const
                {
                    return MakeUniformCommandGS( command, start, mtx34 );
                }

                /* Please see man pages for details 
                    
                    
                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::MTX44& mtx44 ) const
                {
                    return MakeUniformCommandGS( command, start, mtx44 );
                }

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::VEC4& vec4 ) const
                {
                    return MakeUniformCommandGS( command, start, vec4 );
                }

                /* Please see man pages for details 
                    
                    
                    
                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, const nn::math::VEC4 vec4[], const int num ) const
                {
                    return MakeUniformCommandGS( command, start, vec4, num );
                }
                
                /* Please see man pages for details 
                    

                    
                    
                    
                    

                    
                 */
                bit32* MakeUniformCommand( bit32* command, u8 x, u8 y, u8 z ) const
                {
                    return MakeUniformCommandGS( command, start, x, y, z );
                }
            };

            /* Please see man pages for details 
                
             */
            class BindSymbolGSBool : public BindSymbol
            {
            public :
                /* Please see man pages for details 
                    
                */
                explicit BindSymbolGSBool() : 
                BindSymbol( SHADER_TYPE_GEOMETRY, SYMBOL_TYPE_BOOL )
                {
                }
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_BIND_SYMBOL_H_
