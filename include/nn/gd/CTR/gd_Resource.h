/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Resource.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_RESOURCE_H_
#define NN_GD_CTR_GD_RESOURCE_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>

#include <nn/gd/CTR/gd_Memory.h>

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

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class VertexBufferResourceDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class VertexBufferResourceProperties;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class VertexBufferResource;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Texture2DResourceDescription;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Texture2DResourceProperties;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
*/
#else
/* Please see man pages for details 
*/
#endif
class Texture2DResource;


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
#else
/* Please see man pages for details 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
#endif
class Resource
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    enum NativeFormat
    {
       NATIVE_FORMAT_RGBA_8888            = 0,
       NATIVE_FORMAT_RGB_888              = 1,
       NATIVE_FORMAT_RGBA_5551            = 2,
       NATIVE_FORMAT_RGB_565              = 3,
       NATIVE_FORMAT_RGBA_4444            = 4,
       NATIVE_FORMAT_LUMINANCE_ALPHA_88   = 5,
       NATIVE_FORMAT_HILO_88              = 6,
       NATIVE_FORMAT_LUMINANCE_8          = 7,
       NATIVE_FORMAT_ALPHA_8              = 8,
       NATIVE_FORMAT_LUMINANCE_ALPHA_44   = 9,
       NATIVE_FORMAT_LUMINANCE_4          = 10,
       NATIVE_FORMAT_ALPHA_4              = 11,
       NATIVE_FORMAT_ETC1_RGB8            = 12,
       NATIVE_FORMAT_ETC1_A4              = 13,
       NATIVE_FORMAT_GAS                  = 14,
       NATIVE_FORMAT_SHADOW               = 15,
       NATIVE_FORMAT_DEPTH_16             = 16,
       NATIVE_FORMAT_DEPTH_24             = 17,
       NATIVE_FORMAT_DEPTH_24_STENCIL_8   = 18,

       NATIVE_FORMAT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    enum Format
    {
        FORMAT_RGBA_8888             = 100,
        FORMAT_RGB_888               = 101,
        FORMAT_RGBA_5551             = 102,
        FORMAT_RGB_565               = 103,
        FORMAT_RGBA_4444             = 104,
        FORMAT_LUMINANCE_ALPHA_88    = 105,
        FORMAT_LUMINANCE_8           = 106,
        FORMAT_ALPHA_8               = 107,
        FORMAT_LUMINANCE_ALPHA_44    = 108,
        FORMAT_LUMINANCE_4           = 109,
        FORMAT_ALPHA_4               = 110,
        FORMAT_HILO_88               = 111,

        FORMAT_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum CompressedFormat
    {
        FORMAT_ETC1_RGB8        = 111,
        FORMAT_ETC1_A4          = 112,

        FORMAT_ETC1_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum MapUsage
    {
        MAP_READ_ONLY = 0,
        MAP_WRITE_ONLY = 1,
        MAP_READ_WRITE = 2,
        
        MAP_RESERVED_MAX_U32 = 0xffffffffu
    };

    /* Please see man pages for details 
      
    */
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
      
    */
    #else
    /* Please see man pages for details 
      
    */
    #endif
    class Helper
    {
    public:
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
            
            
            
            
            
			
			
			
			
			
			
			
            
            
        */
        #else
        /* Please see man pages for details 
            
            
              
              
              
              
              
              
              
              
              
              
              
              

            
            
            
            
            
            
            

            
            
            
            
            
            
            
        */
        #endif
        static nnResult ConvertTextureResourceToNativeFormat(Format format, u32 width, u32 height, const u8* dataSrc, u8* dataDst, NativeFormat* pnativeFormat = NULL);

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
            
             
             
            
            
            
            
           
           
           
           
           
           
           
           
           
           

            
            
            
            
            
            

            
            
            
            
			
			
			
			
			
			
			
            
            
        */
        #else
        /* Please see man pages for details 
            
            
            
             
             
             
            
            
            
           
           
           
           
           
           
           
           
           
           

            
            
            
            
            
            

            
            
            
            
            
            

            
            
            
            
            
            
        */
        #endif
        static nnResult GenerateMipMapsCPU(NativeFormat format, u32 width, u32 height, const u8* dataSrc, u8* dataDst, u32 countMipLevelToGenerate);

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
            
            
            
            
			
			
			
			
			
			
			
            
            
            
        */
        #else
        /* Please see man pages for details 
            
            
            
            
            
            
            
            
            

            
            
            
            
            
            
        */
        #endif
        static nnResult ConvertCompressedTextureResourceToNativeFormat(CompressedFormat format, u32 width, u32 height, u8* dataSrc, u8* dataDst, NativeFormat* pnativeFormat = NULL);
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
         
         
         
        
         
         
         
        
         
         
         
         
         
        
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
        
        
        
    */
    #else
    /* Please see man pages for details 
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

      
      
      
      
                                             
      
      
      
      
      
      
      
                                             
                                             
    */
    #endif
    static nnResult CreateTexture2DResource(const Texture2DResourceDescription* description, const void* initialData, gdBool autoGenerateMipMapsFromData, Texture2DResource** texture2DResource, gdBool copyInitialData = GD_TRUE);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
         
         
         
         
        
		
		
		
		
		
		
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
         
         
         
        
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult CreateTexture2DResourceCastFrom(const Texture2DResource* initialTexture2DResource, Resource::NativeFormat format, Memory::MemoryLayout layout, Texture2DResource** texture2DResource);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult GetTexture2DResourceProperties(const Texture2DResource* texture2DResource, Texture2DResourceProperties* properties);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
    */
    #endif
    static nnResult ReleaseTexture2DResource(Texture2DResource* texture2DResource);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
         
        
        
        
		
		
		
		
		
		
		
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        

        
        
        
        
        
        
    */
    #endif
    static nnResult MapTexture2DResource(Texture2DResource* texture2DResource, s32 mipLevelIndex, MapUsage usage, void** data);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UnmapTexture2DResource(Texture2DResource* texture2DResource);
    /*  */ // name


    /* Please see man pages for details 
      
    */
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
         
         
         
         
		 
		 
		 
		 
		 
		 
		 
		 
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        
    */
    #endif
    static nnResult CreateVertexBufferResource(const VertexBufferResourceDescription* description, const void* initialData, VertexBufferResource** buffer, gdBool copyInitialData = GD_TRUE);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        

        
        
        
    */
    #endif
    static nnResult GetVertexBufferResourceProperties(const VertexBufferResource* buffer, VertexBufferResourceProperties* properties);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
		
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        

        
        
        
        
                                            
        
    */
    #endif
    static nnResult MapVertexBufferResource(VertexBufferResource* buffer, MapUsage usage, void** data);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
		
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        
        
        

        
        
        
        
    */
    #endif
    static nnResult UnmapVertexBufferResource(VertexBufferResource* buffer);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
		
		
		
		
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleaseVertexBufferResource(VertexBufferResource* buffer);
    /*  */ // name

};  // Resource


/*****************************************************************************************************************************/
/********************************************* Descriptor/Properties class definition ****************************************/
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class Texture2DResourceDescription
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Width;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Height;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif 
    u32 m_CountMipLevels;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Resource::NativeFormat m_Format;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Memory::MemoryLayout m_MemLayout;
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Memory::MemoryLocation m_MemLocation;
};  // Texture2DResourceDescription


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class MipmapResourceInfo
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Width;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Height;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u8* m_MemAddr;
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class Texture2DResourceProperties
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Width;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Height;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_CountMipLevels;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_PixelSize;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Resource::NativeFormat m_Format;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Memory::MemoryLayout m_MemLayout;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    Memory::MemoryLocation m_MemLocation;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u8* m_MemAddr;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    MipmapResourceInfo GetMipmapAddress(u32 mipmapLevel)
    {
        MipmapResourceInfo mipmapInfo;
        mipmapInfo.m_Width = m_Width;
        mipmapInfo.m_Height = m_Height;
        mipmapInfo.m_MemAddr = m_MemAddr;
        for (u32 i=0; i<mipmapLevel; ++i)
        {
            mipmapInfo.m_MemAddr += (mipmapInfo.m_Width * mipmapInfo.m_Height * m_PixelSize) >> 3;
            mipmapInfo.m_Width >>= 1;
            mipmapInfo.m_Height >>= 1;
        }
        return mipmapInfo;
    }
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class VertexBufferResourceDescription
{
public:
#if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
#else
    /* Please see man pages for details */
#endif
    u32 m_ByteSize;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
#else
    /* Please see man pages for details */
#endif
    Memory::MemoryLocation m_MemLocation;
};


#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
class VertexBufferResourceProperties
{
public:
#if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
#else
    /* Please see man pages for details */
#endif
    u32 m_ByteSize;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
#else
    /* Please see man pages for details */
#endif
    Memory::MemoryLocation m_MemLocation;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
#else
    /* Please see man pages for details */
#endif
    u8* m_MemAddr;
};


}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_RESOURCE_H_
