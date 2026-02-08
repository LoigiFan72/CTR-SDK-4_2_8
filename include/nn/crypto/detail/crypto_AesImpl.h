/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_AesImpl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_DETAIL_CRYPTO_AESIMPL_H_
#define NN_CRYPTO_DETAIL_CRYPTO_AESIMPL_H_

#include <nn/config.h>
#include <nn/types.h>

namespace nn {
namespace crypto {
namespace detail {



template <size_t KeySize>
class AesImpl
{
public:
    static const size_t BLOCK_SIZE = 16;
    static const size_t KEY_SIZE   = KeySize;

private:
    static const int NUM_ROUND = (KEY_SIZE / 4) + 6;

public:
    void SetKey(const void* pKey, size_t keySize);
    void Encrypt(void* pDst, const void* pSrc);
    void Decrypt(void* pDst, const void* pSrc);

private:
    bit32   m_Key[ BLOCK_SIZE * (NUM_ROUND + 1) / sizeof(bit32) ];
    bool    m_IsEncryptKey;
    NN_PADDING3;
};



}   // namespace detail
}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_DETAIL_CRYPTO_AESIMPL_H_ */
