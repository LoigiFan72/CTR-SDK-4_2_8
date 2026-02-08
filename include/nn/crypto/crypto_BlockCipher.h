/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_BlockCipher.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_BLOCKCIPHER_
#define NN_CRYPTO_CRYPTO_BLOCKCIPHER_

#include <nn/types.h>


namespace nn {
namespace crypto {



/* Please see man pages for details 
    

    

    
    
    

    
    
*/
class BlockCipher
{
public:
    BlockCipher(){}
    virtual ~BlockCipher(){}

    /* Please see man pages for details 
        

        

        
    */
    virtual size_t GetBlockSize() const = 0;

    /* Please see man pages for details 
        

        

        
    */
    virtual size_t GetKeySize()   const = 0;



    /* Please see man pages for details 
        

        

        
        
    */
    virtual void SetKey(const void* pKey, size_t keySize) = 0;


    
    /* Please see man pages for details 
        

        
        
        

        
                
                
        
                
                
    */
    virtual void Encrypt(void* pDst, const void* pSrc) const = 0;

    /* Please see man pages for details 
        

        
        
        

        
                
                
        
                
                
    */
    virtual void Decrypt(void* pDst, const void* pSrc) const = 0;
};



}   // namespace crypto
}   // namespace nn



#endif /* NN_CRYPTO_CRYPTO_BLOCKCIPHER_ */
