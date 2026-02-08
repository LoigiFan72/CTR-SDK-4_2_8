/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_Hmac.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

*/

#ifndef NN_CRYPTO_CRYPTO_HMAC_H_
#define NN_CRYPTO_CRYPTO_HMAC_H_

#ifdef __cplusplus

namespace nn{ namespace crypto{

/* Please see man pages for details 
    
    
    
    
    
    
    
    
    
*/
void CalculateHmacSha1(
    void*                   pOut,
    const void*             pData,
    size_t                  size,
    const void*             pKeyData,
    size_t                  keySize
);

/* Please see man pages for details 
    
    
    
    
    
    
    
    
    
*/
void CalculateHmacSha256(
    void*                   pOut,
    const void*             pData,
    size_t                  size,
    const void*             pKeyData,
    size_t                  keySize
);

}} // namespace nn::crypto

#endif // __cplusplus


#endif /* NN_CRYPTO_CRYPTO_HMAC_H_ */
