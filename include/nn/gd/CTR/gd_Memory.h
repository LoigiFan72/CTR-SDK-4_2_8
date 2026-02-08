/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Memory.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_MEMORY_H_
#define NN_GD_CTR_GD_MEMORY_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
*/
#else
/* Please see man pages for details 
    
*/
#endif
namespace nn {
namespace gd {
namespace CTR {

class RenderTarget;
class DepthStencilTarget;
class Texture2DResource;
class VertexBufferResource;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
*/
/*  */ // defgroup memoryOperation

/* Please see man pages for details 
    
    
    
    
    
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
 
*/
/*  */ // defgroup memoryOperation

/* Please see man pages for details 
    
    
    
    
    
    
 */
#endif
class Memory
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum MemoryLocation
    {
        FCRAM = 1 << 0,     //
        VRAMA = 1 << 1,     //
        VRAMB = 1 << 2,     //

        MEMORY_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum MemoryLayout
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        LAYOUT_LINEAR = 0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        LAYOUT_BLOCK_8 = 8,     

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        LAYOUT_BLOCK_32 = 32,

        MEMORYLAYOUT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum DownScalingMode
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        //
        #else
        //
        #endif
        DOWNSCALING_NONE = 0,
 
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        //
        #else
        //
        #endif
        DOWNSCALING_2X1 = 1,
       
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        //
        #else
        //
        #endif
        DOWNSCALING_2X2 = 2,

        DOWNSCALING_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    class Rect
    {
    public:
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        s32 m_PosX;
        
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        s32 m_PosY; 

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        s32 m_Width;

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        s32 m_Height;

    public:
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        Rect(s32 x, s32 y, s32 w, s32 h): m_PosX(x), m_PosY(y), m_Width(w), m_Height(h) {}
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
		
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
    */
    #endif
    static nnResult ClearTexture2DResource(const Texture2DResource* tex2DResource, s32 mipLevelIndexStart, s32 mipLevelIndexEnd, const u8 Components[4]);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
     */
    #endif
    static nnResult ClearTexture2DResource(const Texture2DResource* tex2DResource, s32 mipLevelIndexStart, s32 mipLevelIndexEnd, u32 value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        
           
           
           
           
           
           
           
           

           
           
           
           
           
           
        
        
        
        
        
        
        
        

        
        
        
    */
    #endif
    static nnResult ClearTargets(const RenderTarget* renderTarget, const DepthStencilTarget* depthStencilTarget, const u8 ColorRGBA[4], float depth, u8 stencil);
    /*  */ // name

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
		
		
		
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
                                                  
                                                  
        
        
    */
    #endif
    static nnResult CopyTextureSubResource(const Texture2DResource* source, s32 srcMipLevelIndex, const Rect& rect,
        const Texture2DResource* dest, s32 dstMipLevelIndex, s32 destPosX, s32 destPosY);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
		
		
		
		
		
		
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult CopyVertexBufferSubResource(const VertexBufferResource* source, u32 sourceOffset, u32 size, const VertexBufferResource* dest, u32 destOffset);
    /*  */ // name

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
            
            
            
            
            
            
            
            
            
            
            
            
            
            
        
        
        
        
            
            
        
        
        
        
        
        
		
		
		
		
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
       
    
       
       
       
           
           
           
           
           
           
           
           
           
           
           
           
           
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
                                                  
        
        
        
    */
    #endif
    static nnResult CopyTexture2DResourceBlockToLinear(const Texture2DResource* source, s32 srcMipLevelIndex, u32 srcOffsetY, s32 srcCountRow,
        const Texture2DResource* dest, s32 dstMipLevelIndex, u32 dstOffestY, DownScalingMode downScalingMode, gdBool yFlip);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    
        
        
        
            
            
            
            
            
            
            
            
            
            
            
            
            
            
        
        
        
        
        
        
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
    
        
        
        
           
           
           
           
           
           
           
           
           
           
           
           
           
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
                                                  
        
        
        
    */
    #endif
    static nnResult CopyTexture2DResourceBlockToLinear(const Texture2DResource* source, s32 srcMipLevelIndex, u32 srcOffsetY,
        u8* dstAddr, u32 dstWidth, u32 dstHeight, u32 dstFormat, DownScalingMode downScalingMode, gdBool yFlip);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
            
            
            
            
            
            
            
            
            
            
            
            
        
        
        
        
            
            
        
        
        
        
		
		
		
		
		
		
		
		
		
		
		
		
		
		
        */
    #else
    /* Please see man pages for details 
       
       
       
       
       
           
           
           
           
           
           
           
           
           
           
           
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        
        
                                                  
        
                                                  
        
        */
    #endif
    static nnResult CopyTexture2DResourceLinearToBlock(const Texture2DResource* source, s32 srcMipLevelIndex, u32 srcOffsetY, s32 srcCountRow,
        const Texture2DResource* dest, s32 dstMipLevelIndex, u32 dstOffestY);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
            
            
            
            
            
            
            
            
            
            
            
        
        
        
		
		
		
		
		
		
		
		
		
		
		
		
        
        
        
        
        */
    #else
    /* Please see man pages for details 
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
        
        
        
        
        
        
        
        

        
        
        
        
        
        
                                                  
                                                  
        
        
    */
    #endif
    static nnResult CopyTexture2DResourceLinearToBlock(u8* srcAddr, u32 width, u32 height, const Texture2DResource* dest, s32 dstMipLevelIndex, u32 dstOffestY);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
         
         
         
        
        
        
		
		
		
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        
        
           
           
           
           
           
           
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        
                                                  
                                                  
    */
    #endif
    static nnResult GenerateMipMaps(const Texture2DResource* tex2DResource, u32 mipLevelSourceIndex, s32 mipLevelLastDestinationIndex);
    /*  */ // name

};  // Memory

}  // namespace CTR
}  // gd
}  // nn

#endif // NN_GD_CTR_GD_MEMORY_H_
