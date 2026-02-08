/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_CriticalSection.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47236 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_CRITICALSECTION_H_
#define NN_OS_OS_CRITICALSECTION_H_

#include <nn/os/os_SimpleLock.h>
#include <nn/assert.h>
#include <nn/WithInitialize.h>
#include <nn/util/detail/util_ScopedLockImpl.h>
#include <nn/hw/ARM/reg_access.h>

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
    

    

    
    

    

    
    

    
    
    
    

    
*/

class CriticalSection : private nn::util::NonCopyable<CriticalSection>
{
public:
    /* Please see man pages for details 
      

                    

                    
    */
    CriticalSection() : m_ThreadUniqueValue(GetInvalidThreadUniqueValue()), m_LockCount(-1) {}

    /* Please see man pages for details 
      
    */
    CriticalSection(const nn::WithInitialize&) { Initialize(); }

    /* Please see man pages for details 
      

      
    */
    void Initialize();

    /* Please see man pages for details 
      

      
    */
    nn::Result TryInitialize()
    {
        Initialize();
        return ResultSuccess();
    }

    /* Please see man pages for details 
      

                    

      
    */
    void Finalize() { m_LockCount = -1; }

    /* Please see man pages for details 
      
    */
    ~CriticalSection() {}

    /* Please see man pages for details 
      

      
    */
    void Enter();

    /* Please see man pages for details 
      

      
    */
    bool TryEnter();

    /* Please see man pages for details 
      

      
    */
    void Leave();

    /* Please see man pages for details 
        

        
               
    */
    class ScopedLock;

    bool IsLocked() const
    {
        return m_Lock.IsLocked();
    }

private:
    void OnLocked()
    {
        NN_TASSERT_(m_LockCount == 0);

        // Save ID of thread that got critical section.
        this->m_ThreadUniqueValue = GetThreadUniqueValue();
    }

    // TODO: Recommend moving to ARM.
#ifdef NN_PROCESSOR_ARM946ES
    static uptr GetThreadUniqueValue()
    {
        return nn::os::CTR::ARM946ES::GetThreadId();
    }
    static uptr GetInvalidThreadUniqueValue()
    {
        return static_cast<uptr>(-1);
    }
#else
    static uptr GetThreadUniqueValue()
    {
        uptr v;
        HW_GET_CP15_THREAD_ID_USER_READ_ONLY(v);
        return v;
    }
    static uptr GetInvalidThreadUniqueValue()
    {
        return 0;
    }
#endif
    
    bool LockedByCurrentThread() const
    {
        return GetThreadUniqueValue() == m_ThreadUniqueValue;
    }
    bool IsInitialized() const
    {
        return m_LockCount >= 0;
    }

private:
    SimpleLock  m_Lock;
    uptr        m_ThreadUniqueValue;
    s32         m_LockCount;
};

NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(CriticalSection, Enter(), Leave());

}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

#define NN_OS_CRITICALSECTION_SIZE 12

/* Please see man pages for details 
  
  

  

  

  
*/

/* Please see man pages for details 
  
  

  
*/
NN_UTIL_DETAIL_CLIBIMPL_DEFINE_BUFFER_CLASS(nnosCriticalSection, nn::os::CriticalSection, NN_OS_CRITICALSECTION_SIZE, u32);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosCriticalSectionInitialize(nnosCriticalSection* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosCriticalSectionTryInitialize(nnosCriticalSection* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosCriticalSectionEnter(nnosCriticalSection* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosCriticalSectionTryEnter(nnosCriticalSection* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosCriticalSectionLeave(nnosCriticalSection* this_);

/* Please see man pages for details 
  
*/
NN_EXTERN_C void nnosCriticalSectionFinalize(nnosCriticalSection* this_);

/*  



*/

#endif
