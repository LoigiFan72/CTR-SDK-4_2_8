/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Texture.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_TEXTURE_H_
#define NN_GR_TEXTURE_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {        
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class Texture
            {
            public :

                /* Please see man pages for details 
                    
                 */
                class UnitBase
                {
                public :
                    /* Please see man pages for details 
                        
                     */
                    uptr physicalAddr;


                    /* Please see man pages for details 
                        
                     */
                    u16 width;


                    /* Please see man pages for details 
                        
                     */
                    u16 height;

                    /* Please see man pages for details 
                        
                               
                    */
                    PicaDataTextureFormat format;
                  
                    /* Please see man pages for details 
                        
                               
                               
                     */
                    PicaDataTextureWrap wrapT;
                
                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataTextureWrap wrapS;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataTextureMagFilter magFilter;


                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataTextureMinFilter minFilter;
                    NN_PADDING3;
   
                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                               
                               
                    */
                    f32 lodBias;
                   
                    /* Please see man pages for details 
                        
                               
                               
                               
                        
                     */
                    u8 minLodLevel;


                    /* Please see man pages for details 
                        
                               
                               
                               
                        
                    */
                    u8 maxLodLevel;


                    /* Please see man pages for details 
                        
                               
                               
                     */
                    u8 borderColorR;

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    u8 borderColorG;


                    /* Please see man pages for details 
                        
                               
                               
                     */
                    u8 borderColorB;


                    /* Please see man pages for details 
                        
                               
                               
                     */
                    u8 borderColorA;

                    NN_PADDING2;

                protected :
                    /* Please see man pages for details 
                        

                        
                    */
                    bool IsEnableMipMap() const
                    {
                        if ( minFilter == PICA_DATA_TEXTURE_MIN_FILTER_LINEAR  ) 
                        {
                            return false;
                        }

                        if ( minFilter == PICA_DATA_TEXTURE_MIN_FILTER_NEAREST )
                        {
                            return false;
                        }

                        return true;
                    }

                    /* Please see man pages for details 
                        
                     */
                    UnitBase();
                };

            public :

                /* Please see man pages for details 
                    
                 */
                class Unit0 : public UnitBase
                {
                public :
                     /* Please see man pages for details 
                        
                               
                               
                     */
                    PicaDataTexture0SamplerType texType;
                    NN_PADDING3;

                    /* Please see man pages for details 
                        
                               
                    */
                    uptr cubeMapAddrPosX;
                    
                    /* Please see man pages for details 
                        
                               
                    */
                    uptr cubeMapAddrNegX;

                    /* Please see man pages for details 
                        
                               
                    */
                    uptr cubeMapAddrPosY;

                    /* Please see man pages for details 
                        
                               
                    */
                    uptr cubeMapAddrNegY;

                    /* Please see man pages for details 
                        
                               
                    */
                    uptr cubeMapAddrPosZ;

                    /* Please see man pages for details 
                        
                               
                    */
                    uptr cubeMapAddrNegZ;

                public :
                    /* Please see man pages for details 
                        
                     
                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool is_update_texture_func = true ) const;

                    /* Please see man pages for details 
                        

                        
                     */
                    explicit Unit0( const Texture& texture_ );

                protected :
                    const Texture& m_Texture;
                };

                /* Please see man pages for details 
                    
                 */
                class Unit1 : public UnitBase
                {
                public :
                    /* Please see man pages for details 
                        
                               
                               
                     */
                    PicaDataTexture1SamplerType texType;
                    NN_PADDING3;

                public :
                    /* Please see man pages for details 
                        
                        
                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool is_update_texture_func = true ) const;

                    /* Please see man pages for details 
                        

                        
                     */
                    explicit Unit1( const Texture& texture_ );
                    
                protected :
                    const Texture& m_Texture;
                };

                /* Please see man pages for details 
                    
                 */
                class Unit2 : public UnitBase
                {
                public :
                    /* Please see man pages for details 
                        
                               
                     */
                    PicaDataTexture2SamplerType texType;

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    PicaDataTexture2TexCoord    texCoord;

                    NN_PADDING2;

                public :
                    /* Please see man pages for details 
                        

                        
                        
                        
                        
                     */
                     bit32* MakeCommand( bit32* command, bool is_update_texture_func = true ) const;
                    
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit Unit2( const Texture& texture_ );

                protected :
                    const Texture& m_Texture;
                };

                /* Please see man pages for details 
                    
                 */
                class Unit3 : protected UnitBase
                {
                public :   
                    /* Please see man pages for details 
                        
                               
                               
                     */
                    PicaDataTexture3SamplerType texType;
                    
                     /* Please see man pages for details 
                        
                               
                               
                     */
                    PicaDataTexture3TexCoord    texCoord;

                    NN_PADDING2;

                public :
                    /* Please see man pages for details 
                        
                     
                        
                        
                     
                        
                     */
                    bit32* MakeCommand( bit32* command, bool is_update_texture_func = true ) const;

                    /* Please see man pages for details 
                        

                        
                     */
                    explicit Unit3( const Texture& texture_ );

                protected :
                    const Texture& m_Texture;
                };

            public :
                /* Please see man pages for details 
                    
                           
                */
                Unit0 unit0;

                /* Please see man pages for details 
                    
                           
                */
                Unit1 unit1;

                /* Please see man pages for details 
                    
                           
                */
                Unit2 unit2;

                /* Please see man pages for details 
                    
                           
                */
                Unit3 unit3;

            public :
                /* Please see man pages for details 
                    
                */
                Texture();

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                bit32* MakeCommand( bit32* command, bool isAddDummyCommand = true ) const;

                /* Please see man pages for details 
                    
                    
                    
                    
                    
                    
                 */
                bit32* MakeFuncCommand( bit32* command, bool isAddDummyCommand = true ) const;

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                static bit32* MakeDisableCommand( bit32* command, bool isAddDummyCommand = true );

            protected:
                /* Please see man pages for details 
                    

                    
                    
                    
                 */
                 static bit32* MakeDummyCommand_( bit32* command );
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_TEXTURE_H_
