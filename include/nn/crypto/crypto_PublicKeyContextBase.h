/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_PublicKeyContextBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_PUBLICKEYCONTEXTBASE_H_
#define NN_CRYPTO_CRYPTO_PUBLICKEYCONTEXTBASE_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/Result.h>

#ifdef __cplusplus

namespace nn{ namespace crypto{

/*
    

            
            
*/
class PublicKeyContextBase
{
public:

    /*
        

        
    */
    virtual nn::Result Decrypt(void* pDest, const void* pSrc, size_t size) = 0;

    /*
        

        
    */
    virtual nn::Result Encrypt(void* pDest, const void* pSrc, size_t size) = 0;

protected:

    // Prohibit individual instantiation
    PublicKeyContextBase() {}
    virtual ~PublicKeyContextBase() {}

};


}} // namespace nn::crypto

#endif // __cplusplus


#endif /* NN_CRYPTO_CRYPTO_PUBLICKEYCONTEXTBASE_H_ */
