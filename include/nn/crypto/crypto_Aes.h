/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_Aes.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_AES_H_
#define NN_CRYPTO_CRYPTO_AES_H_

#include <nn/crypto/crypto_BlockCipher.h>
#include <nn/crypto/detail/crypto_AesImpl.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    

    
    
    

    
    

    
*/
template <size_t KeySize>
class Aes : public BlockCipher
{
private:
    // ARMCC 2819: class "~" has an implicitly instantiated key function "~"
    // AesImp is inserted in order to define all virtual functions inline for the purpose of avoiding
    typedef detail::AesImpl<KeySize> ImplT;

public:
    //
    static const size_t BLOCK_SIZE = ImplT::BLOCK_SIZE;

    //
    static const size_t KEY_SIZE   = ImplT::KEY_SIZE;

public:
    Aes(){}
    virtual ~Aes(){}

    /* Please see man pages for details 
        

        

        

        
                    
    */
    virtual size_t GetBlockSize() const { return BLOCK_SIZE; }

    /* Please see man pages for details 
        

        

        

        
    */
    virtual size_t GetKeySize()   const { return KEY_SIZE;   }

    /* Please see man pages for details 
        

        

        

        
        
                            
                            
    */
    virtual void SetKey(const void* pKey, size_t keySize)
    { return m_Impl.SetKey(pKey, keySize); }



    /* Please see man pages for details 
        

        

        
                            
                            
        
                            
                            
    */
    virtual void Encrypt(void* pDst, const void* pSrc) const
    { return m_Impl.Encrypt(pDst, pSrc); }

    /* Please see man pages for details 
        

        

        
                            
                            
        
                            
                            
    */
    virtual void Decrypt(void* pDst, const void* pSrc) const
    { return m_Impl.Decrypt(pDst, pSrc); }

private:
    mutable ImplT   m_Impl;
};


//
typedef Aes<16>    Aes128;

//
typedef Aes<24>    Aes192;

//
typedef Aes<32>    Aes256;



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_AES_H_ */
