/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_System.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_SYSTEM_H_
#define NN_GD_CTR_GD_SYSTEM_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>

#include <nn/gd/CTR/gd_VertexInput.h>
#include <nn/gd/CTR/gd_Memory.h>

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
  
*/
#else
/* Please see man pages for details 
  
*/
#endif

#ifndef NN_UNUSED_VAR
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
#define NN_UNUSED_VAR(var)  ((void)&var);
#endif

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
typedef void (*gdCallbackfunctionErrorPtr)(nnResult result, const char* functionName);

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
class RecordedPacketId;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
/*  */ // defgroup systemFunction
#else
/* Please see man pages for details 
    
    
*/
/*  */ // defgroup systemFunction
#endif

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
*/
#endif
class System
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum Module
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_RASTERIZER = 1 << 0,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_LIGHTING = 1 << 1,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_OUTPUT = 1 << 2,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_TEXTURE_COMBINER = 1 << 3,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_GAS_FOG = 1 << 4,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_TEXTURE = 1 << 6,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_TEXTURE_PROCEDURAL = 1 << 7,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_VERTEX_INPUT = 1 << 8,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_SHADER = 1 << 9,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        MODULE_ALL = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum RecordingPacketUsage
    {
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        RECORD_COMMAND_LIST_COPY = 1 << 8,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        RECORD_COMMAND_LIST_NO_COPY = 1 << 9,

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        RECORD_3D_COMMAND_BUFFER_FOR_JUMP = 1 << 10,
        
        RECORD_PACKET_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void SetCallbackFunctionError(gdCallbackfunctionErrorPtr callbackFunctionError);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static char* GetErrorStringFromResult(nnResult result);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
        
    */
    #endif
    static nnResult Initialize();

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
    */
    #else
    /* Please see man pages for details 
        

        
    */
    #endif
    static void Finalize();

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
    */
    #endif
    static void ForceDirty(u32 flag);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 

        
        
    */
    #else
    /* Please see man pages for details 

        
        
    */
    #endif
    static void SetDefault(u32 flag);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */
    #endif
    static void FlushDirtyModule(u32 flag);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void Draw(u32 vertexCount, u32 startVertexLocation);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
    #else
    /* Please see man pages for details 
        
        
    */
    #endif
    static void DrawIndexed(u32 indexCount, u32 startIndexLocation);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        

        
        
        
         
        
         
    */
    #else
    /* Please see man pages for details 
        
        
        
        

        
        

        
        
        
         
        
         
    */
    #endif
    static void DrawImmediate(u32 vertexCount, u32 startVertexLocation, void** vertexBuffers, u32* offsets);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        

        
        
         
         
        
         
        
         
        
        
        
         
         
         
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        

        
        

        
        
         
         
        
         
        
         
        
        
        
         
         
         
    */
    #endif
    static void DrawImmediateIndexed(u32 indexCount, u32 startIndexLocation, void** vertexBuffers, u32* offsets, void* indexBuffer, nn::gd::CTR::VertexInputStage::IndexFormat format, u32 indexOffset);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    static void Execute3DCommandList();

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        

        
        
        
        

        
        

        
        
        
        
        
        

        
        
        
        
        
        
        

        
        
        
        
        

        
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        

        
        
       
        
        
        
        
        

        
        
        
        
        
        
        
        
        
        
 
        
        
        
        
        

        
        
        
        
        
        
      */
    #endif
    static nnResult StartRecordingPackets(u32* forceDirtyModuleFlag, RecordingPacketUsage usage = RECORD_COMMAND_LIST_COPY);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        

        

        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        

        
        

        
        
        
        
        
      */
    #endif
    static nnResult GetCommandBufferOffset(u32* offset);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        

        
        
        
        
        
                                               
      */
    #endif
    static nnResult GetCommandBufferBaseAddress(RecordedPacketId* packetId, u32** commandBufferAddr);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 

        
        
        
        
        

        

        
        
        
        
        
        
        
        
        
                                                
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        
        
        
        
    */
    #endif
    static nnResult StopRecordingPackets(RecordedPacketId** packetId);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        

        
        
        
        
        
        
        

        
        
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        
        
        
        
        
        
       
        
        
        

        
        
        
        
        
    */
    #endif
    static nnResult ReplayPackets(RecordedPacketId* packetId, u32* forceDirtyModuleFlag);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        

        
        
        

        
        
        
        
        
                                                
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
    */
    #endif
    static nnResult CopyPacket(RecordedPacketId* source, RecordedPacketId** packetId, Memory::MemoryLocation memory);


    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
    */
    #endif
    static nnResult ReleasePackets(RecordedPacketId* packetId);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        

        
    */
    #else
    /* Please see man pages for details 
        
        

        
    */
    #endif
    static void AddDummyCommands(u32 countDummyCommands);


    /* Please see man pages for details 
      
    */
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
      
    */
    #else
    /* Please see man pages for details 
      
    */
    #endif
    class Debug
    {
    public:
        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details */
        #else
        /* Please see man pages for details */
        #endif
        enum Filter
        {
            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_NONE = 0,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details 
                
            */
            #else
            /* Please see man pages for details 
                
            */
            #endif
            FILTER_TEXTURE_8X8 = 1 << 0,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details 
                
                
            */
            #else
            /* Please see man pages for details 
                
                
            */
            #endif
            FILTER_TEXTURE_CUSTOM = 1 << 1,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details 
            */
            #else
            /* Please see man pages for details 
            */
            #endif
            FILTER_SAMPLER_STATE_FILTER_NEAREST_MIPMAP_NEAREST = 1 << 2,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details 
            */
            #else
            /* Please see man pages for details 
            */
            #endif
            FILTER_SAMPLER_STATE_FILTER_LINEAR_MIPMAP_NEAREST = 1 << 3,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_VIEWPORT_1X1 = 1 << 4,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details 
            */
            #endif
            FILTER_SIMPLE_COMBINER = 1 << 5,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_DISABLE_BLENDING = 1 << 6,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_DISABLE_DEPTH_STENCIL_TEST = 1 << 7,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_DISABLE_ALPHA_TEST = 1 << 8,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_LIGHTING_STAGE_1_LIGHT_MAX = 1 << 9,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details 
                
            */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_LIGHTING_STAGE_SIMPLE_LAYER_CONFIGURATION = 1 << 10,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_DISABLE_DRAW = 1 << 11,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details 
                
                
            */
            #else
            /* Please see man pages for details 
                
                
            */
            #endif
            FILTER_VISUALIZE_OVERDRAW = 1 << 12,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_DISABLE_CULLING = 1 << 13,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_ENABLE_CULLING_CLOCKWISE = 1 << 14,

            #if NN_GD_DOCUMENT_TYPE == ENGLISH
            /* Please see man pages for details */
            #else
            /* Please see man pages for details */
            #endif
            FILTER_ENABLE_CULLING_COUNTERCLOCKWISE = 1 << 15,

            FILTER_RESERVED_MAX_U32 = 0xffffffffu
        };

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
            
            

            
            
            

            
            
        */
        #else
        /* Please see man pages for details 
            
            
            
            
            
            
            
            

            
            
        */
        #endif
        static nnResult SetFilter(u32 filterFlag, u32 drawStartIndex, s32 drawCount);

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
            
            
            
            
            
            

            
            
            
            
            
            
        */
        #else
        /* Please see man pages for details 
            
            
            
            
            
            
            
            
            

            
            
            
            
            
            
        */
        #endif
        static nnResult ColorizeMipmaps(Texture2DResource* texture2DResource, s32 minMipLevelIndex, s32 maxMipLevelIndex, u8 colors[][4]);

        #if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            

            
        */
        #else
        /* Please see man pages for details 
            

            
        */
        #endif
        static void SetCustomTexture(Texture2D* customTexture);
    };
    /*  */ // name

};  // System

/*  */ // addtogroup systemFunction

}  // namespace CTR
}  // namespace gd
}  // namespace nn


#endif // NN_GD_CTR_GD_SYSTEM_H_
