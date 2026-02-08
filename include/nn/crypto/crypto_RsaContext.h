/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_RsaContext.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47645 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_RSACONTEXT_H_
#define NN_CRYPTO_CRYPTO_RSACONTEXT_H_

#include <nn/os.h>
#include <nn/types.h>
#include <nn/config.h>
#include <nn/Result.h>
#include <nn/crypto/crypto_RsaKey.h>
#include <nn/crypto/crypto_PublicKeyContextBase.h>

#ifdef __cplusplus

namespace nn{ namespace crypto{

/* Please see man pages for details 
    

    
*/
class RsaContext : public PublicKeyContextBase
{
public:
    RsaContext() : m_pRsaKeyBuf(NULL) {}
    virtual ~RsaContext() {}

    static const size_t SIZE_STRING_LENGTH = static_cast<size_t>(-1);

    /* Please see man pages for details 
      

      

      

            

    */
    void Initialize();

    /*
      

            
            

      
        
      
    */
    void Initialize(const RsaKey& rsaKey) { NN_UNUSED_VAR(rsaKey); nn::dbg::Panic(); }

    /* Please see man pages for details 
      

            

      
      

      
    */
    void Initialize(const void* pKey, size_t keyLength);

    /* Please see man pages for details 
      

            

      
    */
    void Finalize();

    /*
      

            

      

      
    */
    nn::Result SetKey(const RsaKey& rsaKey) { NN_UNUSED_VAR(rsaKey); return nn::Result(Result::LEVEL_STATUS, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_FS, Result::DESCRIPTION_NOT_IMPLEMENTED); }

    /* Please see man pages for details 
      

      
      
                 

      
    */
    nn::Result SetKey(const void* pKey, size_t keyLength);

    /* Please see man pages for details 
      

      
    */
    void SetKeyLength(size_t keyLength);

    /* Please see man pages for details 
      

      
    */
    size_t GetKeyLength(size_t keyLength);

    /* Please see man pages for details 
      

                
                

      
      
      
      
      

      
    */
    nn::Result Decrypt(size_t* pDecrptLength, void* pDest, size_t destSize, const void* pSrc, size_t srcLength = SIZE_STRING_LENGTH);

    nn::Result Decrypt(void* pDest, size_t destSize, const void* pSrc, size_t srcLength = SIZE_STRING_LENGTH);
    virtual nn::Result Decrypt(void* pDest, const void* pSrc, size_t length);

    /* Please see man pages for details 
      

      
      
      
      
      

      
    */
    nn::Result Encrypt(size_t* pEncryptLength, void* pDest, size_t destSize, const void* pSrc, size_t srcLength = SIZE_STRING_LENGTH);

    nn::Result Encrypt(void* pDest, size_t destSize, const void* pSrc, size_t srcLength = SIZE_STRING_LENGTH);
    virtual nn::Result Encrypt(void* pDest, const void* pSrc, size_t length);

    /* Please see man pages for details 
      

      
      
      
      
      

      
    */
    nn::Result Sign(size_t* pSignLength, void* pDest, size_t destSize, const void* pSrc, size_t srcLength = SIZE_STRING_LENGTH);

    nn::Result Sign(void* pDest, size_t destSize, const void* pSrc, size_t srcLength = SIZE_STRING_LENGTH);

    /* Please see man pages for details 
      

      
      
      
      

      
    */
    nn::Result SignSha256(size_t* pSignLength, void* pDest, size_t destSize, const void* pSrc);

    nn::Result SignSha256(void* pDest, size_t destSize, const void* pSrc);

    /* Please see man pages for details 
      

      
      
      
      

      
    */
    nn::Result Verify(const void* pSrc, size_t srcLength, const void* pSign, size_t signLength);

    /* Please see man pages for details 
      

      
      
      

      
    */
    nn::Result VerifySha256(const void* pSrc, const void* pSign, size_t signLength);

    /* Please see man pages for details 
      

                
                

      
      
      

      
    */
    nn::Result VerifySha1(const void* pSrc, const void* pSign, size_t signLength);

private:
    nn::Result SetKeyImpl(const void* pKey, size_t keyLength);

private:
    RsaKey* m_pRsaKey;
    void*   m_pRsaKeyBuf;
    size_t  m_RsaKeyLength;
};

inline nn::Result RsaContext::Encrypt(void* pDest, size_t destSize, const void* pSrc, size_t srcLength)
{
    return Encrypt(NULL, pDest, destSize, pSrc, srcLength);
}

inline nn::Result RsaContext::Encrypt(void* pDest, const void* pSrc, size_t length)
{
    return Encrypt(NULL, pDest, 0, pSrc, length);
}

inline nn::Result RsaContext::Decrypt(void* pDest, size_t destSize, const void* pSrc, size_t srcLength)
{
    return Decrypt(NULL, pDest, destSize, pSrc, srcLength);
}

inline nn::Result RsaContext::Decrypt(void* pDest, const void* pSrc, size_t length)
{
    return Decrypt(NULL, pDest, 0, pSrc, length);
}

inline nn::Result RsaContext::Sign(void* pDest, size_t destSize, const void* pSrc, size_t srcLength)
{
    return Sign(NULL, pDest, destSize, pSrc, srcLength);
}

inline nn::Result RsaContext::SignSha256(void* pDest, size_t destSize, const void* pSrc)
{
    return SignSha256(NULL, pDest, destSize, pSrc);
}


}} // namespace nn::crypto

#endif	// __cplusplus

#endif // #ifndef NN_CRYPTO_CRYPTO_RSACONTEXT_H_
