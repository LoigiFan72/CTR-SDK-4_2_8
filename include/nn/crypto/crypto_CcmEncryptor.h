/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_CcmEncryptor.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_CCMENCRYPTOR_H_
#define NN_CRYPTO_CRYPTO_CCMENCRYPTOR_H_

#include <nn/crypto/crypto_AuthenticatedEncryptor.h>
#include <nn/crypto/detail/crypto_CcmMode.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    
    
    
    

    
*/
class CcmEncryptor : public AuthenticatedEncryptor
{
private:
    typedef detail::CcmMode ImplT;

public:
    //
    //
    //
    static const size_t  BLOCK_SIZE = ImplT::BLOCK_SIZE;

    //
    //
    //
    static const size_t  IV_SIZE    = ImplT::MAX_IV_SIZE;

    //
    //
    //
    static const size_t  UNIT_SIZE  = ImplT::UNIT_SIZE;

    //
    //
    //
    static const size_t  MAC_SIZE   = ImplT::MAX_MAC_SIZE;

public:
    CcmEncryptor(){}
    virtual ~CcmEncryptor(){}

    /* Please see man pages for details 
        

        
        
        
        
        
        
        
        
        
        
        

        
        

        
        
        
        
        
        
    */
    void            Initialize(const BlockCipher& c, const void* pIv, size_t ivSize,
                                size_t adataSize, size_t pdataSize, size_t macSize)
        { return m_Impl.Initialize(c, pIv, ivSize, adataSize, pdataSize, macSize); }

    /* Please see man pages for details 
        

        
    */
    virtual void    Finalize()
        { return m_Impl.Finalize(); }

    /* Please see man pages for details 
        

        

        
    */
    virtual size_t  GetIvSize() const   { return ImplT::GetIvSize(); }

    /* Please see man pages for details 
        

        

        
    */
    virtual size_t  GetUnitSize() const { return ImplT::GetUnitSize(); }

    /* Please see man pages for details 
        

        

        
    */
    virtual size_t  GetMacSize() const  { return ImplT::GetMacSize(); }

    /* Please see man pages for details 
        

        

        
        
    */
    virtual void    UpdateAdata(const void* pSrc, size_t size)
        { return m_Impl.UpdateAdata(pSrc, size); }

    /* Please see man pages for details 
        

        
    */
    virtual void    UpdateAdataFinal()
        { return m_Impl.UpdateAdataFinal(); }

    /* Please see man pages for details 
        

        

        
        
        
        
        
    */
    virtual size_t  UpdatePdata(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
        { return m_Impl.UpdatePdata(pDst, dstSize, pSrc, srcSize); }

    /* Please see man pages for details 
        

        

        
        
        
    */
    virtual size_t  UpdatePdataFinal(void* pDst, size_t size)
        { return m_Impl.UpdatePdataFinal(pDst, size); }

    /* Please see man pages for details 
        

        

        
        
    */
    virtual void    GenerateMac(void* pDst, size_t size)
        { return m_Impl.GenerateMac(pDst, size); }


    
    /* Please see man pages for details 
        

        
        

        
        
        
        

        
        
        
        
        
        

        
        

        
        
        
        
        
        
        
        
        
        
        
    */
    static void EncryptAndGenerate(
            void* pMac, void* pDst, size_t dstSize, const void* pAdata, size_t adataSize,
            const void* pPdata, size_t pdataSize, const void* pIv, size_t ivSize,
            size_t macSize, const BlockCipher& c)
    {
        CcmEncryptor e;
        e.Initialize(c, pIv, ivSize, adataSize, pdataSize, macSize);
        e.AuthenticatedEncryptor::EncryptAndGenerate(
            pMac, pDst, dstSize, pAdata, adataSize,
            pPdata, pdataSize, macSize);
        e.Finalize();
    }

private:
    ImplT   m_Impl;
};



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_CCMENCRYPTOR_H_ */
