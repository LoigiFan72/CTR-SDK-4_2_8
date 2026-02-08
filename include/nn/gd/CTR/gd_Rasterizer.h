/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Rasterizer.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_RASTERIZER_H_
#define NN_GD_CTR_GD_RASTERIZER_H_

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

/*********************************************************************************************************/
/*************************************************** Enum ************************************************/

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    */
#else
/* Please see man pages for details 
    
    */
#endif
class Viewport
{
public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_X;

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    u32 m_Y;

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

public:
    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
    */
    #else
    /* Please see man pages for details 
    */
    #endif
    Viewport(): m_X(0), m_Y(0), m_Width(0), m_Height(0) {}

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    Viewport(u32 x, u32 y, u32 width, u32 height): m_X(x), m_Y(y), m_Width(width), m_Height(height) {}

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
    */
    #endif
    void Set(u32 x, u32 y, u32 width, u32 height){
        m_X = x;
        m_Y = y;
        m_Width = width;
        m_Height = height;
    }
};

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
*/
#endif
class RasterizerStage
{
public:

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum Culling
    {
        CULLING_NONE = 0,
        CULLING_CLOCKWISE = 2,
        CULLING_COUNTERCLOCKWISE = 1,

        CULLING_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details */
    #else
    /* Please see man pages for details */
    #endif
    enum EarlyDepthFunction
    {
        EARLYDEPTH_FUNCTION_GEQUAL = 0,
        EARLYDEPTH_FUNCTION_GREATER = 1,
        EARLYDEPTH_FUNCTION_LEQUAL = 2,
        EARLYDEPTH_FUNCTION_LESS = 3,

        EARLYDEPTH_FUNCTION_RESERVED_MAX_U32 = 0xffffffffu
    };

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        

        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    #endif
    static void SetCulling(Culling culling);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        
        
        
        
        
        
        
        
        
        
        

        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

        
    */
    #endif
    static void SetViewport(Viewport& viewport);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        

        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        

        
    */
    #endif
    static void EnableClippingPlane(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        

        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        

        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
    */
    #endif
    static void SetClippingPlane(f32 param1, f32 param2, f32 param3, f32 param4);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        

        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        

        
    */
    #endif
    static void EnableScissor(gdBool value);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
        
        

        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
        
        
        
        

        
    */
    #endif
    static void SetScissor(Viewport& area);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
        
        
        
    */
    #else
    /* Please see man pages for details 
        
        
        
        
        
    */
    #endif
    static void SetEarlyDepthTest(gdBool enable, EarlyDepthFunction func);

    #if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
    */
    #else
    /* Please see man pages for details 
        
    */
    #endif
    static void ClearEarlyDepth(f32 depthClearValue);

};  // RasterizerStage


}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_RASTERIZER_H_
