/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_H_
#define NN_GD_H_

#include <nn/gd/CTR/gd_Types.h>
#include <nn/gd/CTR/gd_Result.h>
#include <nn/gd/CTR/gd_Memory.h>
#include <nn/gd/CTR/gd_System.h>
#include <nn/gd/CTR/gd_Resource.h>
#include <nn/gd/CTR/gd_VertexInput.h>
#include <nn/gd/CTR/gd_Texture.h>
#include <nn/gd/CTR/gd_Rasterizer.h>
#include <nn/gd/CTR/gd_Shader.h>
#include <nn/gd/CTR/gd_Lighting.h>
#include <nn/gd/CTR/gd_OutputStage.h>
#include <nn/gd/CTR/gd_GasFog.h>
#include <nn/gd/CTR/gd_Combiner.h>

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
/*  */ // defgroup pipelineStages

/* Please see man pages for details 
    
    
*/
/*  */ // defgroup Resources
#else
/* Please see man pages for details 
    
    
*/
/*  */ // defgroup pipelineStages

/* Please see man pages for details 
    
    
*/
/*  */ // defgroup Resources
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(NN_PLATFORM_CTR)
#ifdef  __cplusplus
namespace nn
{
#if NN_GD_DOCUMENT_TYPE == ENGLISH
    /* Please see man pages for details 
        
        
    */
#else
    /* Please see man pages for details 
        
    */
#endif
    namespace gd
    {
        // Namespace nn::gd::CTR will be automatically used inside namespace nn::gd
        using namespace nn::gd::CTR;

#if NN_GD_DOCUMENT_TYPE == ENGLISH
        /* Please see man pages for details 
            
                        
        */
#else
        /* Please see man pages for details 
            
                        
        */
#endif
        namespace CTR {
        }
    }
}
#endif // __cplusplus
#endif // defined(NN_PLATFORM_CTR)


#endif // NN_GD_H_
