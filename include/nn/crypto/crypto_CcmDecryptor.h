/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_CcmDecryptor.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_CCMDECRYPTOR_H_
#define NN_CRYPTO_CRYPTO_CCMDECRYPTOR_H_


#include <nn/crypto/crypto_AuthenticatedDecryptor.h>
#include <nn/crypto/detail/crypto_CcmMode.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    
    
    
    

    
*/
class CcmDecryptor : public AuthenticatedDecryptor
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
    CcmDecryptor(){}
    virtual ~CcmDecryptor(){}

    /* Please see man pages for details 
        

        
        
        
        
        
        

        

        
        
        
        
        
        
    */
    void            Initialize(const BlockCipher& c, const void* pIv, size_t ivSize,
                                size_t adataSize, size_t cdataSize, size_t macSize)
        { return m_Impl.Initialize(c, pIv, ivSize, adataSize, cdataSize, macSize); }

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
    virtual size_t  UpdateCdata(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
        { return m_Impl.UpdateCdata(pDst, dstSize, pSrc, srcSize); }

    /* Please see man pages for details 
        

        

        
        
        
    */
    virtual size_t  UpdateCdataFinal(void* pDst, size_t size)
        { return m_Impl.UpdateCdataFinal(pDst, size); }

    /* Please see man pages for details 
        

        

        
        
    */
    virtual void    GenerateMac(void* pDst, size_t size)
        { return m_Impl.GenerateMac(pDst, size); }

    
    
    /* Please see man pages for details 
        

        
        

        
        
        
        
        
        

        

        
        
        
        
        
        
        
        
        
        
        
        
                    
                    
    */
    static bool DecryptAndVerify(
            void* pDst, size_t dstSize, const void* pAdata, size_t adataSize,
            const void* pCdata, size_t cdataSize, const void* pIv, size_t ivSize,
            const void* pMac, size_t macSize, const BlockCipher& c)
    {
        CcmDecryptor e;
        e.Initialize(c, pIv, ivSize, adataSize, cdataSize, macSize);
        bool ret = e.AuthenticatedDecryptor::DecryptAndVerify(
                        pDst, dstSize, pAdata, adataSize,
                        pCdata, cdataSize, pMac, macSize);
        e.Finalize();
        return ret;
    }

private:
    ImplT   m_Impl;
};



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_CCMDECRYPTOR_H_ */
