/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_CtrMode.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_DETAIL_CRYPTO_CTRMODE_H_
#define NN_CRYPTO_DETAIL_CRYPTO_CTRMODE_H_

#include <nn/crypto/crypto_BlockCipher.h>


namespace nn {
namespace crypto {
namespace detail {



template <size_t BlockSize>
class CtrMode
{
public:
    static const size_t  BLOCK_SIZE     = BlockSize;
    static const size_t  IV_SIZE        = BlockSize;
    static const size_t  UNIT_SIZE      = 1;

public:
    CtrMode() : m_pCipher(NULL) {}

    static size_t  GetIvSize() { return IV_SIZE; }
    static size_t  GetUnitSize() { return 1; }

    void    Initialize(const BlockCipher& c, const void* pIv, size_t ivSize);
    void    Finalize();
    size_t  Update(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize);
    size_t  UpdateFinal(void* pDst, size_t dstSize);

public:
    static void ProcessBlocks(void* pDst, void* pCounter, const void* pSrc,
                int numBlocks, const BlockCipher& c);
    static void IncrementCounter(void* p);

private:
    const BlockCipher*  m_pCipher;
    bit32               m_Counter[IV_SIZE/sizeof(bit32)];
    bit8                m_Data[BLOCK_SIZE];
    s32                 m_DataSize;
};



}   // namespace detail
}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_DETAIL_CRYPTO_CTRMODE_H_ */
