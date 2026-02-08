/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     crypto_RsaKey.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CRYPTO_CRYPTO_RSAKEY_H_
#define NN_CRYPTO_CRYPTO_RSAKEY_H_

#include <nn/os.h>
#include <nn/types.h>
#include <nn/config.h>
#include <nn/Result.h>

#ifdef __cplusplus

namespace nn{ namespace crypto{

/* Please see man pages for details 
    

            


            
*/
class RsaKey
{
public:
    RsaKey();
    ~RsaKey(){};
    
    static const int MAX_KEY_LENGTH = 2048;
    static const int MAX_KEY_BYTES = MAX_KEY_LENGTH / 8;
    
    /* Please see man pages for details 
        
        
        
        
        
        
                    

        
    */
    nn::Result InitializeKey( const void* pModulus, const void* pExp, s32 keyLength, bool isPrivate );
    
    /* Please see man pages for details 
      

      
      
                 
                 
      
      
    */
    nn::Result InitializePrivateKey( const void* pKey, s32 keyLength );
    
    /* Please see man pages for details 
      

      
        
      
                 
                 
      
      
    */
    nn::Result InitializePublicKey( const void* pKey, s32 keyLength );
    
    /* Please see man pages for details 
      
                

      
    */
    void Finalize();
    
    /* Please see man pages for details 
      

      
    */
    s32 GetKeyLength() const { return m_KeyLength; }
    s32 GetKeySize() const NN_ATTRIBUTE_DEPRECATED { return GetKeyLength(); }
    
    /* Please see man pages for details 
      
      
      
    */
    bool IsPrivate() const { return m_IsPrivateKey; }
    
    /* Please see man pages for details 
      
      
      
    */
    const void* GetModulus() const { return m_Modulus; }
    
    /* Please see man pages for details 
      
      
      
    */
    const void* GetExp() const { return m_Exp; }
   
private :
    u8 m_Modulus[ MAX_KEY_BYTES ];
    u8 m_Exp[ MAX_KEY_BYTES ];
    s32 m_KeyLength;
    bool m_IsPrivateKey;
    NN_PADDING3;
};

}} // namespace nn::crypto

#endif // __cplusplus

#endif /* NN_CRYPTO_CRYPTO_RSAKEY_H_ */
