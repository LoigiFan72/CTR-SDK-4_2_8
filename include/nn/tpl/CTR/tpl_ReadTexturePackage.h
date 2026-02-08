/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     tpl_ReadTexturePackage.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_TPL_CTR_TPL_READTEXTUREPACKAGE_H_
#define NN_TPL_CTR_TPL_READTEXTUREPACKAGE_H_

#include <nn/types.h>
#include <nn/tpl/CTR/tpl_PackagerType.h>


#ifdef __cplusplus
extern "C" {
#endif


namespace nn { namespace tpl { namespace CTR {

    /* Please see man pages for details 
        
        
        
        
    */
    u16 GetTextureNum(const void* pTexPackage);

    /* Please see man pages for details 
        
        
        
        
        

        
    */
    s16 GetTextureIndex(const void* pTexPackage, const char* texPath);

    /* Please see man pages for details 
        
        
        
        
        
        
        

        
        
        
    */
    void* GetTexture(s32* mipLevel, u32* mipmapSize, const void* pTexPackage, const s16 texIndex);

    /* Please see man pages for details 
        
        
        
        
        
        

        
    */
    bool GetTextureInfo(CtrTextureInfo* pTexInfo, const void* pTexPackage, const s16 texIndex);

    /* Please see man pages for details 
        
        
        
        

        
        
    */
    bool CheckTexturePackageHeader(const void* pTexPackage);


}}} // namespace


#ifdef __cplusplus
}
#endif

#endif // NN_TPL_CTR_TPL_READTEXTUREPACKAGE_H_
