/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_Cipher.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_CRYPTO_CRYPTO_CIPHER_H_
#define NN_CRYPTO_CRYPTO_CIPHER_H_

namespace nn {
namespace crypto {

    /* Please see man pages for details 
        

        
        
        

        
        
    */
    const size_t ENCRYPT_HEADER_SIZE = 16;

    /* Please see man pages for details 
        

        
        
        

        
        
    */
    const size_t GENERATE_HEADER_SIZE = 32;
    
    /* Please see man pages for details 
        

        
        

        
        

        
        
        
        

        
                            
                            
        
        
        
                            
    */
    void EncryptAes128Ctr(void* pDst, const void* pSrc, size_t srcSize, const void* pKey);

    /* Please see man pages for details 
        

        

        
        
        
        

        
                            
                            
        
        
        
                            
    */
    void DecryptAes128Ctr(void* pDst, const void* pSrc, size_t srcSize, const void* pKey);


    
    /* Please see man pages for details 
        

        
        

        
        

        
        
        
        

        
                            
                            
        
        
        
                            
    */
    void EncryptAndGenerateAes128Ccm(void* pDst, const void* pSrc, size_t srcSize, const void* pKey);

    /* Please see man pages for details 
        

        
        

        
        
        
        

        
                            
                            
        
        
        
                            
        
                    
                    
    */
    bool DecryptAndVerifyAes128Ccm(void* pDst, const void* pSrc, size_t srcSize, const void* pKey);



    /* Please see man pages for details 
        

        
        
    */
    void GenerateRandomBytes(void* pDst, size_t size);

}
}

#endif /* NN_CRYPTO_CRYPTO_CIPHER_H_ */
