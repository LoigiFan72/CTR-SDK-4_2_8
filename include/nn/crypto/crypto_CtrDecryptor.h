/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_CtrDecryptor.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_CTRDECRYPTOR_H_
#define NN_CRYPTO_CRYPTO_CTRDECRYPTOR_H_

#include <nn/crypto/crypto_Decryptor.h>
#include <nn/crypto/detail/crypto_CtrMode.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    
    
    

    
    

    

*/
template <size_t BlockSize>
class CtrDecryptor : public Decryptor
{
private:
    typedef detail::CtrMode<BlockSize>  ImplT;

public:
    //
    //
    //
    static const size_t  BLOCK_SIZE = ImplT::BLOCK_SIZE;

    //
    //
    //
    static const size_t  IV_SIZE    = ImplT::IV_SIZE;

    //
    //
    //
    static const size_t  UNIT_SIZE  = ImplT::UNIT_SIZE;

public:
    CtrDecryptor(){}
    virtual ~CtrDecryptor(){}

    /* Please see man pages for details 
        

        

        
                    
    */
    virtual size_t  GetIvSize() const { return ImplT::GetIvSize(); }

    /* Please see man pages for details 
        

        

        
    */
    virtual size_t  GetUnitSize() const { return ImplT::GetUnitSize(); }


    
    /* Please see man pages for details 
        

        

        
        
        
    */
    virtual void    Initialize(const BlockCipher& c, const void* pIv, size_t ivSize)
        { return m_Impl.Initialize(c, pIv, ivSize); }

    /* Please see man pages for details 
        

        
    */
    virtual void    Finalize()
        { return m_Impl.Finalize(); }

    /* Please see man pages for details 
        

        

        
        
        
        
        
    */
    virtual size_t  Update(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
        { return m_Impl.Update(pDst, dstSize, pSrc, srcSize); }

    /* Please see man pages for details 
        

        

        
        
        
    */
    virtual size_t  UpdateFinal(void* pDst, size_t size)
        { return m_Impl.UpdateFinal(pDst, size); }

    
    
    /* Please see man pages for details 
        

        
        

        
        

        
        

        
        
        
        
        

        
        

        
        
        
        
        
        
        
        
    */
    static size_t Decrypt(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize,
                            const void* pIv, size_t ivSize, const BlockCipher& c)
    {
        CtrDecryptor<BlockSize> e;
        return e.Decryptor::Decrypt(pDst, dstSize, pSrc, srcSize, pIv, ivSize, c);
    }

private:
    ImplT   m_Impl;
};

/* Please see man pages for details 
    
*/
typedef CtrDecryptor<16>    CtrDecryptor128;



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_CTRDECRYPTOR_H_ */
