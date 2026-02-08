/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_ShaBlock512BitContext.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/*  
    API declaration concerning SHA-X (Blocksize = 512bit)
*/

#ifndef NN_CRYPTO_CRYPTO_SHABLOCK512BITCONTEXT_H_
#define NN_CRYPTO_CRYPTO_SHABLOCK512BITCONTEXT_H_

#include <nn/crypto/crypto_HashContextBase.h>

#ifdef __cplusplus

namespace nn{ namespace crypto{

/* Please see man pages for details 
    

    

            
            
*/
class ShaBlock512BitContext : public HashContextBase
{
public:
    static const size_t BLOCK_SIZE = (512/8);  // 512bit
    
    virtual void Update(const void* pData, size_t size);
    virtual void InitializeWithContext(const void*, u64) {};

protected:
    u8      m_Block[BLOCK_SIZE];
    u32     m_Pool;
    u32     m_BlocksLow;
    u32     m_BlocksHigh;
    
    void    AddPadding();
    virtual void ProcessBlock() {}
    
    // Prohibit individual instantiation
    ShaBlock512BitContext() {}
    virtual ~ShaBlock512BitContext() {}
};

}} // namespace nn::crypto

#endif // __cplusplus


#endif /* NN_CRYPTO_CRYPTO_SHABLOCK512BITCONTEXT_H_ */
