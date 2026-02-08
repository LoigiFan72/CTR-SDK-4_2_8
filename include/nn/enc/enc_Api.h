/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     enc_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ENC_ENC_API_H_
#define NN_ENC_ENC_API_H_

#include <nn/Result.h>

#ifdef __cplusplus

namespace nn { namespace enc {

    /* Please see man pages for details 
    
                  
                  
                  
                  
                  
                  

    
    
    
    

    
    
    
    
    */
    Result ConvertStringUtf16NativeToUtf8(
        u8* pDst, s32* pDstSize, const u16* pSrc, s32* pSrcSize
    );

    /* Please see man pages for details 
    
                  
                  
                  
                  
                  
                  

    
    
    
    

    
    
    
    
    */
    Result ConvertStringUtf8ToUtf16Native(
        u16* pDst, s32* pDstSize, const u8* pSrc, s32* pSrcSize
    );

}}

#endif // __cplusplus

#endif /* NN_ENC_ENC_API_H_ */
