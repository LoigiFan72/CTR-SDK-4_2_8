/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gx_Vram.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GX_CTR_GX_VRAM_H_
#define NN_GX_CTR_GX_VRAM_H_

#include <nn/types.h>
#include <nn/assert.h>

/*--------------------------------------------------------------------------
    C functions
 *-------------------------------------------------------------------------*/
/* Please see man pages for details 
  
  
*/

#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef NN_GX_MEM_VRAMA
#define NN_GX_MEM_VRAMA     0x00020000
#endif // NN_GX_MEM_VRAMA

#ifndef NN_GX_MEM_VRAMB
#define NN_GX_MEM_VRAMB     0x00030000
#endif // NN_GX_MEM_VRAMB
    
    /*
      
                    
      
      
     */
    uptr nngxGetVramStartAddr( s32 area );
    
    /*
      
                    
      
      
     */
    uptr nngxGetVramEndAddr( s32 area );
    
    /*
      
                    
      
      
     */
    size_t nngxGetVramSize( s32 area );
    
#ifdef  __cplusplus
} // extern "C"
#endif // __cplusplus

/*  

*/

/*--------------------------------------------------------------------------
    C++ functions
 *-------------------------------------------------------------------------*/
#ifdef  __cplusplus
namespace nn {
namespace gx {
namespace CTR {

    /*
      
      
     */
    enum VramArea
    {
        /* Please see man pages for details */
        MEM_VRAMA = NN_GX_MEM_VRAMA,
        /* Please see man pages for details */
        MEM_VRAMB = NN_GX_MEM_VRAMB
    };
    
    /*
      
      
                    
                    
                    
      
      
     */
    inline uptr GetVramStartAddr( VramArea area )
    {
        return nngxGetVramStartAddr(area);
    }
    
    /*
      
      
                    
                    
                    
      
      
     */
    inline uptr GetVramEndAddr( VramArea area )
    {
        return nngxGetVramEndAddr(area);
    }
    
    /*
      
      
                    
                    
                    
      
      
     */
    inline size_t GetVramSize( VramArea area )
    {
        return nngxGetVramSize(area);
    }

}}} // namespace nn::gx::CTR
#endif // __cplusplus


#endif /* NN_GX_CTR_GX_VRAM_H_ */
