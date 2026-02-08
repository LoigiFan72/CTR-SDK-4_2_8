/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_CcmMode.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_DETAIL_CRYPTO_CCMMODE_H_
#define NN_CRYPTO_DETAIL_CRYPTO_CCMMODE_H_

#include <nn/crypto/crypto_BlockCipher.h>


namespace nn {
namespace crypto {
namespace detail {



class CcmMode
{
public:
    static const size_t  BLOCK_SIZE     = 16;
    static const size_t  MAX_IV_SIZE    = 13;
    static const size_t  UNIT_SIZE      = 1;
    static const size_t  MAX_MAC_SIZE   = 16;

public:
    CcmMode() : m_pCipher(NULL) {}

    void    Initialize(const BlockCipher& c, const void* pIv, size_t ivSize,
                        size_t adataSize, size_t pdataSize, size_t macSize);
    void    Finalize();

    static size_t  GetIvSize()   { return MAX_IV_SIZE; }
    static size_t  GetUnitSize() { return 1; }
    static size_t  GetMacSize()  { return MAX_MAC_SIZE; }

    void    UpdateAdata(const void* pSrc, size_t size);
    void    UpdateAdataFinal();
    size_t  UpdatePdata(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize);
    size_t  UpdatePdataFinal(void* pDst, size_t size);
    size_t  UpdateCdata(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize);
    size_t  UpdateCdataFinal(void* pDst, size_t size);
    void    GenerateMac(void* pDst, size_t size);

private:
    const BlockCipher*  m_pCipher;
    s8      m_DataSize;
    s8      m_NonceSize;
    s8      m_MacSize;
    NN_PADDING1;
    bit8    m_Data[BLOCK_SIZE];
    bit32   m_CbcBuffer[ BLOCK_SIZE / sizeof(bit32) ];
    bit32   m_CtrBuffer[ BLOCK_SIZE / sizeof(bit32) ];
};



}   // namespace detail
}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_DETAIL_CRYPTO_CCMMODE_H_ */
