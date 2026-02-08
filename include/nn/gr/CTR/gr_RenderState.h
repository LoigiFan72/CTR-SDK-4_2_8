/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_RenderState.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47904 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_RENDER_STATE_H_
#define NN_GR_RENDER_STATE_H_

#include <nn/gr/CTR/gr_Utility.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {

            /* Please see man pages for details 
                
             */
            class RenderState
            {
            public :
                /* Please see man pages for details 
                    
                 */
                enum ColorMask
                {
                    //
                    COLOR_MASK_R    = 1 << 0,
                    //
                    COLOR_MASK_G    = 1 << 1,
                    //
                    COLOR_MASK_B    = 1 << 2,
                    //
                    COLOR_MASK_A    = 1 << 3, 
                    //
                    COLOR_MASK_RGBA = COLOR_MASK_R | COLOR_MASK_G | COLOR_MASK_B | COLOR_MASK_A 
                };

                /* Please see man pages for details 
                    
                 */
                /*
                    By setting each value and calling the MakeCommand function, the render command can be generated.
                */
                class AlphaTest
                {
                public :
                    /* Please see man pages for details 
                        
                               
                               
                               
                     */
                    bool isEnable;

                    /* Please see man pages for details 
                        
                               
                               
                               
                     */
                    u8 refValue;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataAlphaTest func;

                    NN_PADDING1;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit AlphaTest( const RenderState& renderState_ );

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool isUpdateFBAccess = true ) const;


                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );

                protected:
                    const RenderState& m_RenderState;
                };

                /* Please see man pages for details 
                    
                           
                           
                */
                class Blend
                {
                public :
                    /* Please see man pages for details 
                        
                               
                               
                     */
                    bool isEnable;
             /* Please see man pages for details 
                        
                               
                    */
                    PicaDataBlendEquation eqRgb;


                    /* Please see man pages for details 
                        
                               
                    */
                    PicaDataBlendEquation eqAlpha;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataBlendFunc srcRgb;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataBlendFunc srcAlpha;


                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataBlendFunc dstRgb;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataBlendFunc dstAlpha;


                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 colorR;


                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 colorG;


                    /* Please see man pages for details 
                        
                               
                               
                    */
                    u8 colorB;


                    /* Please see man pages for details 
                        
                        
                    */
                    u8 colorA;

                    NN_PADDING1;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit Blend( const RenderState& renderState_ );


                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool isUpdateFBAccess = true ) const;

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );

                protected:
                    const RenderState& m_RenderState;

                };

                /* Please see man pages for details 
                    
                           
                           
                */
                class LogicOp
                {
                public :
                    /* Please see man pages for details 
                        
                               
                     */
                    bool isEnable;

                    /* Please see man pages for details 
                        
                        
                        
                    */
                    PicaDataLogicOp opCode;

                    NN_PADDING2;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit LogicOp( const RenderState& renderState_ );

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool isUpdateFBAccess = true ) const;

                protected:
                    const RenderState& m_RenderState;
                };

                /* Please see man pages for details 
                    
                           
                           
                */
                class ShadowMap
                {
                public :
                    /* Please see man pages for details 
                        

                        
                    */
                    explicit ShadowMap( const RenderState& renderState_ );

                    /* Please see man pages for details 
                        

                        
                        
                        

                    
                 */
                    bit32* MakeCommand( bit32* command,
                                        bool isUpdateFBAccess = true,
                                        bool isAddDummyCommand = true ) const;

                    /* Please see man pages for details 
                        

                        
                        

                        
                    */
                    bit32* MakeTextureCommand( bit32* command,
                                               bool isAddDummyCommand = true ) const;

                    /* Please see man pages for details 
                        

                        

                        
                    */
                    bit32* MakeAttenuationCommand( bit32* command ) const;

                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                               
                     */
                    bool isEnable;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    bool isPerspective;
                    NN_PADDING2;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    f32 zBias;


                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    f32 zScale;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    f32 penumbraScale;

                    /* Please see man pages for details 
                        
                                
                                
                    */
                    f32 penumbraBias;

                protected:
                    const RenderState& m_RenderState;
                };

                /* Please see man pages for details 
                    
                 */
                class StencilTest
                {
                public :
                    /* Please see man pages for details 
                        
                     */
                    bool isEnable;

                    /* Please see man pages for details 
                        
                               

                     */
                    bit8 maskOp;
                    NN_PADDING2;

                    /* Please see man pages for details 
                        
                               
                               
                               
                    */
                    PicaDataStencilTest func;
                    NN_PADDING3;

                    /* Please see man pages for details 
                        
                               
                    */
                    bit32  ref;


                    /* Please see man pages for details 
                        
                               
                               
                    */
                    /*
                        When the stencil buffer value is set to stencil, a comparison is performed between ( stencil & mask ) and ( ref & mask ).
                        
                     */
                    bit32  mask;

                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                    */
                    PicaDataStencilOp opFail;


                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                    */
                    PicaDataStencilOp  opZFail;

                    /* Please see man pages for details 
                            
                                   
                                   
                                   
                    */
                    PicaDataStencilOp  opZPass;

                    NN_PADDING1;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit StencilTest( const RenderState& renderState_ );

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool isUpdateFBAccess = true ) const;

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );

                protected:
                    const RenderState& m_RenderState;
                };

                /* Please see man pages for details 
                    
                 */
                class DepthTest
                {
                public :
                    /* Please see man pages for details 
                        
                               
                               
                               
                     */
                    bool             isEnable;


                    /* Please see man pages for details 
                        
                               
                               
                     */
                    bool             isEnableWrite;

                    /* Please see man pages for details 
                        
                               
                               
                    */
                    PicaDataDepthTest func;

                    NN_PADDING1;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit DepthTest( const RenderState& renderState_ );


                    /* Please see man pages for details 
                        
                               
                               

                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool isUpdateFBAccess = true ) const;

                    /* Please see man pages for details 
                        
                               

                        
                        

                        
                     */
                    static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );

                protected:
                    const RenderState& m_RenderState;
                };

                /* Please see man pages for details 
                    
                 */
                class WBuffer
                {
                public :

                    /* Please see man pages for details 
                        
                               
                     */
                    f32 wScale;

                    /* Please see man pages for details 
                        
                               
                     */
                    bool isEnablePolygonOffset;

                    NN_PADDING3;

                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                               
                               

                        
                     */

                    f32  polygonOffsetUnit;

                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                     */
                    f32  depthRangeNear;

                    /* Please see man pages for details 
                        
                               
                               
                               
                               
                     */
                    f32  depthRangeFar;

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    u8   depthRangeBit;

                    NN_PADDING3;

                public :
                    /* Please see man pages for details 
                        
                     */
                    explicit WBuffer( );

                    /* Please see man pages for details 
                        

                        

                        
                     */
                    bit32* MakeCommand( bit32* command ) const;
                };

                /* Please see man pages for details 
                    
                 */
                class Culling
                {
                public :
                    /* Please see man pages for details 
                        
                               
                               
                               
                     */
                    bool isEnable;

                    /* Please see man pages for details 
                        
                     */
                    enum FrontFace
                    {
                        /* Please see man pages for details 
                            
                        */
                        FRONT_FACE_CW , 

                        /* Please see man pages for details 
                            
                        */
                        FRONT_FACE_CCW
                    };

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    FrontFace frontFace;

                    /* Please see man pages for details 
                        
                     */
                    enum CullFace
                    {
                        /* Please see man pages for details 
                            
                        */
                        CULL_FACE_FRONT,
                         /* Please see man pages for details 
                            
                        */
                        CULL_FACE_BACK
                    };

                    /* Please see man pages for details 
                        
                               
                               
                     */
                    CullFace cullFace;

                    NN_PADDING1;

                public :
                    /* Please see man pages for details 
                        

                        
                     */
                    explicit Culling( const RenderState& renderState_ );


                    /* Please see man pages for details 
                        

                        
                        
                        
                     */
                    bit32* MakeCommand( bit32* command, bool isUpdateFBAccess = true ) const;

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );

                protected:
                    const RenderState& m_RenderState;
                };

                /* Please see man pages for details 
                    
                */
                /*
                    The frame buffer access setting depends on the color mask, blend, logical operations, depth test, and stencil test settings, so specify referencing with the constructor.
                    
                    A command must be generated with FBAccess::MakeCommand function if a change occurs in frame buffer access after generating a command to change the above setting.
                    
                    
                */
                class FBAccess
                {
                public :
                    /* Please see man pages for details 
                        
                               

                        
                     */
                    explicit FBAccess( const RenderState& renderState_ );

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    bit32* MakeCommand( bit32* command, bool isClearFrameBufferCache = true ) const;

                    /* Please see man pages for details 
                        

                        
                        

                        
                     */
                    static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );

                    /* Please see man pages for details 
                        

                        

                        
                     */
                    static bit32* MakeClearCacheCommand( bit32* command );

                protected:
                    const RenderState& m_RenderState;
                };

            public :
                /* Please see man pages for details 
                    
                           
                           
                           
                 */
                Blend       blend;

                /* Please see man pages for details 
                    
                           
                           
                           
                 */
                LogicOp     logicOp;

                /* Please see man pages for details 
                    
                           
                           
                 */
                ShadowMap  shadowMap;

                /* Please see man pages for details 
                    
                           
                 */
                AlphaTest   alphaTest;

                /* Please see man pages for details 
                    
                           
                 */
                StencilTest stencilTest;

                /* Please see man pages for details 
                    
                           
                 */
                ColorMask   colorMask;
                NN_PADDING3;

                /* Please see man pages for details 
                    
                           

                    
                 */
                DepthTest   depthTest;

                /* Please see man pages for details 
                    
                           

                    
                 */
                Culling     cullingTest;

                /* Please see man pages for details 
                    
                           

                    
                 */
                WBuffer     wBuffer;

                /* Please see man pages for details 
                    
                           

                 */
                FBAccess    fbAccess;

            public :
                /* Please see man pages for details 
                    

                    
                         
                         
                         
                         
                         
                         
                         
                         
                 */
                explicit RenderState();

                /* Please see man pages for details 
                    

                    
                    

                    

                    
                         
                         
                         
                         
                         
                         
                         
                         
                 */
                bit32* MakeCommand( bit32* command, bool isClearFrameBufferCache = true ) const;

                /* Please see man pages for details 
                    

                    
                    

                    
                 */
                static bit32* MakeDisableCommand( bit32* command, bool isClearFrameBufferCache = true );
            };

        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_RENDER_STATE_H_
