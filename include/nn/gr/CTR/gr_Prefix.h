/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Prefix.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47511 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_PREFIX_H_
#define NN_GR_PREFIX_H_

#include <nn/types.h>
#include <nn/gx.h>
#include <nn/gx/CTR/gx_CommandAccess.h>

#define NN_GR_ASSERT   NN_ASSERT
#define NN_GR_ERR(...) do { NN_LOG(__VA_ARGS__); int* a = NULL; *a = 1; } while(0)

namespace nn
{
    namespace gr
    {
        namespace CTR
        {
            /* Please see man pages for details 
                
            */
            typedef PicaDataVertexAttrType PicaDataVertexArrayType;

            /* Please see man pages for details 
                
                
            */
            typedef PicaDataFragLightSampler PicaDataLookUpTableType;

            /* Please see man pages for details 
                
            */
            typedef PicaDataFragLightEnvTexture PicaDataFragLightTexture;

            /* Please see man pages for details 
                
            */
            typedef PicaDataFragLightEnvLayerConfig PicaDataFragLightLayerConfig;

            /* Please see man pages for details 
                
            */
            typedef PicaDataFragLightEnvBump PicaDataFragLightBump;

            /* Please see man pages for details 
                
            */
            typedef PicaDataFragLightEnvLutInput PicaDataLutInput;

            /* Please see man pages for details 
                
            */
            typedef PicaDataFragLightEnvLutScale PicaDataLutScale;

        } // namespace CTR
    } // namespace gr
}  // namespace nn

#endif // NN_GR_PREFIX_H_
