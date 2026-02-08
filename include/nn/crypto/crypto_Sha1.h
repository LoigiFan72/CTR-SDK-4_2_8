/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_Sha1.h

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

#ifndef NN_CRYPTO_CRYPTO_SHA1_H_
#define NN_CRYPTO_CRYPTO_SHA1_H_

#include <nn/crypto/crypto_HashContextBase.h>
#include <nn/crypto/crypto_ShaBlock512BitContext.h>

#ifdef __cplusplus

namespace nn{ namespace crypto{

/* Please see man pages for details 
    

    
*/
class Sha1Context : public ShaBlock512BitContext
{
public:
    static const size_t HASH_SIZE  = (160/8);  // 160bit
    
private:
    u32     m_H[5];
    
protected:
    virtual void ProcessBlock();
    
public:
    
    /* Please see man pages for details 
        
        
        
    */
    Sha1Context() {}
    
    /* Please see man pages for details 
        
        
        
    */
    virtual ~Sha1Context() {};
    
    /* Please see man pages for details 
        
        
        
    */
    virtual void Initialize();
    
    /* Please see man pages for details 
        

        
    */
    virtual void InitializeWithContext(const void *pContext, u64 size);

    /* Please see man pages for details 
        
        
        
    */
    virtual void Finalize() {}
    
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    virtual void Update(const void* pData, size_t size);
    
    /* Please see man pages for details 
        
        
        
    */
    virtual size_t GetHashSize() { return HASH_SIZE; }
    size_t GetHashLength() NN_ATTRIBUTE_DEPRECATED { return GetHashSize(); }
    
    /* Please see man pages for details 
        
        
        
        
        
    */
    virtual void GetHash(void* pOut);
    
};  // sizeof(Sha1Context) == 100

/* Please see man pages for details 
    
    
    
    
    
    
    
*/
void CalculateSha1(void *pOut, const void *pData, size_t size);

}} // namespace nn::crypto

#endif // __cplusplus


#endif /* NN_CRYPTO_CRYPTO_SHA1_H_ */
