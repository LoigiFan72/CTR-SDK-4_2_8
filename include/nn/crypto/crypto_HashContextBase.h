/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_HashContextBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_CRYPTO_CRYPTO_HASHCONTEXTBASE_H_
#define NN_CRYPTO_CRYPTO_HASHCONTEXTBASE_H_

#include <nn/types.h>
#include <nn/config.h>

#ifdef __cplusplus

namespace nn{ namespace crypto{

/* Please see man pages for details 
    

    

            
            
*/
class HashContextBase
{
public:
    
    /*
        
        
        
    */
    virtual void Initialize() {}
    
    /*
        
        
        
    */
    virtual void Finalize() {}
    
    /*
        
        
        
    */
    virtual void Update(const void* pData, size_t size)
    {
        NN_UNUSED_VAR(pData);
        NN_UNUSED_VAR(size);
    }
    
    /*
        
        
        
    */
    virtual size_t GetHashSize() { return 0; }
    size_t GetHashLength() NN_ATTRIBUTE_DEPRECATED { return GetHashSize(); }
    
    /*
        
        
        
    */
    virtual void GetHash(void* pOut)
    {
        NN_UNUSED_VAR(pOut);
    }
    
protected:

    // Prohibit individual instantiation
    HashContextBase() {}
    virtual ~HashContextBase() {}
    
    // Internal block process
    virtual void ProcessBlock() {}
    
private:
    
};


}} // namespace nn::crypto

#endif // __cplusplus


#endif /* NN_CRYPTO_CRYPTO_HASHCONTEXTBASE_H_ */
