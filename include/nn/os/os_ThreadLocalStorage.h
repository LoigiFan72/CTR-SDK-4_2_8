/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ThreadLocalStorage.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47398 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
  

    
*/
#ifndef NN_OS_OS_THREADLOCALSTORAGE_H_
#define NN_OS_OS_THREADLOCALSTORAGE_H_

#include <nn/types.h>
#include <nn/config.h>

#ifdef __cplusplus

namespace nn{ namespace os{

    namespace detail
    {
        void InitializeThreadEnvrionment();
    }

/* Please see man pages for details 
    

    
    
            
            
            
            
            
            

            
*/
class ThreadLocalStorage
{
public:
    
    /* Please see man pages for details 
        
    */
    ThreadLocalStorage();

    /* Please see man pages for details 
        
    */
    ~ThreadLocalStorage();
    
    /* Please see man pages for details 
        

        
    */
    uptr GetValue() const;
    
    /* Please see man pages for details 
        

        
        
    */
    void SetValue(uptr value);
    

public:
    struct WithoutInitialize{};
    ThreadLocalStorage(const WithoutInitialize& dummy) { NN_UNUSED_VAR(dummy); }
    void Initialize();
    void Finalize();

    void SetValueTo(void* pTo, uptr value);

private:
    
    // Slot number
    s32 m_Index; 

    friend void nn::os::detail::InitializeThreadEnvrionment();

    // Clear the values stored in all slots.
    static void ClearAllSlots();
    
};

}} // namespace nn::os

#endif // __cplusplus

/* NN_OS_OS_THREADLOCALSTORAGE_H_ */
#endif /* NN_OS_OS_THREADLOCALSTORAGE_H_ */
