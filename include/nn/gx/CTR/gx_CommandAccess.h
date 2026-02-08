/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gx_CommandAccess.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47826 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GX_CTR_GX_COMMAND_ACCESS_H_
#define NN_GX_CTR_GX_COMMAND_ACCESS_H_

#include <nn/types.h>

#include <nn/gx/CTR/gx_MacroReg.h>
#include <nn/gx/CTR/gx_MacroCommon.h>
#include <nn/gx/CTR/gx_MacroFragment.h>
#include <nn/gx/CTR/gx_MacroTexture.h>
#include <nn/gx/CTR/gx_MacroShader.h>
#include <nn/gx/CTR/gx_MacroMisc.h>
#include <nn/gx/CTR/gx_MacroOld.h>

/*--------------------------------------------------------------------------
    C API
 *-------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

    /*
      
                    
                    
                    
                    
      
      
     */
    uptr nngxGetPhysicalAddr( uptr virtualAddr );

    /*
      
                    
                    
                    
                    
                    
      
      
      
     */
    void nngxUpdateBuffer( const void* pBuffer, size_t size );

#ifdef  __cplusplus
} // extern "C"
#endif // __cplusplus


/*--------------------------------------------------------------------------
    C++ API
 *-------------------------------------------------------------------------*/
#ifdef  __cplusplus
namespace nn {
namespace gx {
namespace CTR {

    /*
      
                    
      
      
     */
    inline uptr GetPhysicalAddr( uptr virtualAddr )
    {
        return nngxGetPhysicalAddr(virtualAddr);
    }

    /*
      
                    
                    
      
      
      
     */
    inline void UpdateBuffer( const void* pBuffer, size_t size )
    {
        nngxUpdateBuffer(pBuffer, size);
    }

}}} // namespace nn::gx::CTR
#endif // __cplusplus


#endif /* NN_GX_CTR_GX_COMMAND_ACCESS_H_ */
