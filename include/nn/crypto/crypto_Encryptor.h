/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_Encryptor.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_ENCRYPTOR_H_
#define NN_CRYPTO_CRYPTO_ENCRYPTOR_H_

#include <nn/crypto/crypto_BlockCipher.h>
#include <nn/crypto/crypto_CipherMode.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    
    

    
    

*/
class Encryptor : public CipherMode
{
public:
    Encryptor(){}
    virtual ~Encryptor(){}


    
    /* Please see man pages for details 
        

        
        
        
        

        
        
        

        
        
        
    */
    virtual void    Initialize(const BlockCipher& c, const void* pIv, size_t ivSize) = 0;

    /* Please see man pages for details 
        

        
        
        
        
        

        
        
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        

        
        

        
        
        
        
        
    */
    virtual size_t  Update(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize) = 0;
    
    /* Please see man pages for details 
        

        
        

        
        

        
        
        
        
        

        
        

        
        
        
    */
    virtual size_t  UpdateFinal(void* pDst, size_t dstSize) = 0;

protected:
    size_t Encrypt(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize,
                        const void* pIv, size_t ivSize, const BlockCipher& c);
};



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_ENCRYPTOR_H_ */
