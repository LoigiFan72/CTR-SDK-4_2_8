/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_AuthenticatedDecryptor.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_AUTHENTICATEDDECRYPTOR_H_
#define NN_CRYPTO_CRYPTO_AUTHENTICATEDDECRYPTOR_H_

#include <nn/crypto/crypto_BlockCipher.h>
#include <nn/crypto/crypto_CipherMode.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    
    

    
    

*/
class AuthenticatedDecryptor : public CipherMode
{
public:
    AuthenticatedDecryptor(){}
    virtual ~AuthenticatedDecryptor(){}



    /* Please see man pages for details 
        

        

        
    */
    virtual size_t  GetMacSize() const = 0;

    
    
    /* Please see man pages for details 
        

        

        
        
        
        
        

        
        
    */
    virtual void    UpdateAdata(const void* pSrc, size_t size) = 0;
    
    /* Please see man pages for details 
        

        
        

        
        
    */
    virtual void    UpdateAdataFinal() = 0;
    
    /* Please see man pages for details 
        

        
        

        
        

        
        
        
        
        

        
        
        
        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        

        
        

        
        
        
        
        
    */
    virtual size_t  UpdateCdata(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize) = 0;
    
    /* Please see man pages for details 
        

        
        

        
        

        
        

        
        
        
        
        

        
        

        
        
        
    */
    virtual size_t  UpdateCdataFinal(void* pDst, size_t size) = 0;
    
    /* Please see man pages for details 
        

        
        
        

        
        

        
        
        

        
        
    */
    virtual void    GenerateMac(void* pDst, size_t size) = 0;

protected:
    bool DecryptAndVerify(
            void* pDst, size_t dstSize, const void* pAdata, size_t adataSize,
            const void* pCdata, size_t cdataSize, const void* pMac, size_t macSize);
};



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_AUTHENTICATEDDECRYPTOR_H_ */
