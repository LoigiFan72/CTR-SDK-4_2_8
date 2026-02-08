/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_H_
#define NN_CRYPTO_H_

/*!
    @namespace  nn::crypto
*/

#ifdef  __cplusplus
    #include <nn/crypto/crypto_Aes.h>
    #include <nn/crypto/crypto_AuthenticatedDecryptor.h>
    #include <nn/crypto/crypto_AuthenticatedEncryptor.h>
    #include <nn/crypto/crypto_BlockCipher.h>
    #include <nn/crypto/crypto_CcmDecryptor.h>
    #include <nn/crypto/crypto_CcmEncryptor.h>
    #include <nn/crypto/crypto_Cipher.h>
    #include <nn/crypto/crypto_CipherMode.h>
    #include <nn/crypto/crypto_CtrDecryptor.h>
    #include <nn/crypto/crypto_CtrEncryptor.h>
    #include <nn/crypto/crypto_Decryptor.h>
    #include <nn/crypto/crypto_Encryptor.h>
    #include <nn/crypto/crypto_Hash.h>
    #include <nn/crypto/crypto_RsaContext.h>
    #include <nn/crypto/crypto_RsaKey.h>
#endif // __cplusplus

#endif /* NN_CRYPTO_H_ */
