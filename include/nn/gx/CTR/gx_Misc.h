/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gx_Misc.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47467 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GX_CTR_GX_MISC_H_
#define NN_GX_CTR_GX_MISC_H_

#include <nn/types.h>
#include <nn/assert.h>

/*--------------------------------------------------------------------------
    C API
 *-------------------------------------------------------------------------*/
/* Please see man pages for details 
  
  
*/

#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

    typedef enum nngxMemAccessPrioMode
    {
        NN_GX_MEM_ACCESS_PRIO_MODE_0 = 0x00000000,
        NN_GX_MEM_ACCESS_PRIO_MODE_1 = 0x00000205,
        NN_GX_MEM_ACCESS_PRIO_MODE_2 = 0x00000203,
        NN_GX_MEM_ACCESS_PRIO_MODE_3 = 0x00000305,
        NN_GX_MEM_ACCESS_PRIO_MODE_4 = 0x00000105,
        
        NN_GX_MEM_ACCESS_PRIO_MODE_MAX = 0x7FFFFFFF
    } nngxMemAccessPrioMode;
    
    typedef enum nngxInternalDriverPrioMode
    {
        NN_GX_INTERNAL_DRIVER_PRIO_MODE_HIGH,
        NN_GX_INTERNAL_DRIVER_PRIO_MODE_LOW
    } nngxInternalDriverPrioMode;
    
    /*
      
                    
                    
                    
                    
      
      
     */
    void nngxSetMemAccessPrioMode( nngxMemAccessPrioMode mode );


    /*
      
                    
                    
                    
                    
      
     */
    bool nngxIsStereoVisionAllowed( void );


    /*
      
                   
                   
                   
                   
      
      
     */
    void nngxSetInternalDriverPrioMode( nngxInternalDriverPrioMode mode );

    /*---------------------------------------------------------------------------*
      :private
     *---------------------------------------------------------------------------*/
    void nngxSetAutoWaitMode( s32 paramIndex );

#ifdef  __cplusplus
} // extern "C"
#endif // __cplusplus

/*  

*/

/*--------------------------------------------------------------------------
    C++ API
 *-------------------------------------------------------------------------*/
#ifdef  __cplusplus
namespace nn {
namespace gx {
namespace CTR {

    /*
      
      
     */
    enum MemAccessPrioMode
    {
        /* Please see man pages for details */
        MEM_ACCESS_PRIO_MODE_0 = NN_GX_MEM_ACCESS_PRIO_MODE_0,
        /* Please see man pages for details */
        MEM_ACCESS_PRIO_MODE_1 = NN_GX_MEM_ACCESS_PRIO_MODE_1,
        /* Please see man pages for details */
        MEM_ACCESS_PRIO_MODE_2 = NN_GX_MEM_ACCESS_PRIO_MODE_2,
        /* Please see man pages for details */
        MEM_ACCESS_PRIO_MODE_3 = NN_GX_MEM_ACCESS_PRIO_MODE_3,
        /* Please see man pages for details */
        MEM_ACCESS_PRIO_MODE_4 = NN_GX_MEM_ACCESS_PRIO_MODE_4,
        
        MEM_ACCESS_PRIO_MODE_MAX = NN_GX_MEM_ACCESS_PRIO_MODE_MAX
    };

    /*
      
                    
      
      
     */
    inline void SetMemAccessPrioMode( MemAccessPrioMode mode )
    {
        nngxSetMemAccessPrioMode(static_cast<nngxMemAccessPrioMode>(mode));
    }

    /*
      
                    
      
     */
    inline bool IsStereoVisionAllowed( void )
    {
        return nngxIsStereoVisionAllowed();
    }

    /*
      
      
     */
    enum InternalDriverPrioMode
    {
        /* Please see man pages for details */
        INTERNAL_DRIVER_PRIO_MODE_HIGH = NN_GX_INTERNAL_DRIVER_PRIO_MODE_HIGH,
        /* Please see man pages for details */
        INTERNAL_DRIVER_PRIO_MODE_LOW  = NN_GX_INTERNAL_DRIVER_PRIO_MODE_LOW
    };

    /*
      
      
      
      
     */
    inline void SetInternalDriverPrioMode( InternalDriverPrioMode mode )
    {
        nngxSetInternalDriverPrioMode(static_cast<nngxInternalDriverPrioMode>(mode));
    }

    /*---------------------------------------------------------------------------*
      :private
     *---------------------------------------------------------------------------*/
    inline void SetAutoWaitMode( s32 paramIndex )
    {
        nngxSetAutoWaitMode(paramIndex);
    }

}}} // namespace nn::gx::CTR
#endif // __cplusplus

/*---------------------------------------------------------------------------*/

#endif /* NN_GX_CTR_GX_MISC_H_ */
