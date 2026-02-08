/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_LockPolicy.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_OS_OS_LOCKPOLICY_H_
#define NN_OS_OS_LOCKPOLICY_H_

#ifdef __cplusplus

#include <nn/Result.h>
#include <nn/WithInitialize.h>

namespace nn { namespace os {

/* Please see man pages for details 
    
*/
struct LockPolicy {

    /* Please see man pages for details 
        
    */
    struct NoLock
    {
        class LockObject
        {
        public:
            void Initialize() {}
            nn::Result TryInitialize() { return ResultSuccess(); }
            void Finalize() {}
        };
        
        class ScopedLock
        {
        public:
            ScopedLock(const LockObject&) {}
            ~ScopedLock() {}
        };
    };

    /* Please see man pages for details 
        
        
        
        
                
    */
    template <class Locker>
    struct Object
    {
        class ScopedLock;
        
        class LockObject
        {
            friend class ScopedLock;
            mutable Locker mutex;
        public:
            void Initialize() { mutex.Initialize(); }
            nn::Result TryInitialize() { return mutex.TryInitialize(); }
            void Finalize() { mutex.Finalize(); }
        };
        
        class ScopedLock : private Locker::ScopedLock
        {
        public:
            ScopedLock(const LockObject& obj) : Locker::ScopedLock(obj.mutex) {}
        };
    };
    

    /* Please see man pages for details 
        
        
        
        
                
    */
    template <class Locker>
    struct Global
    {
    private:
        static Locker g_Mutex;
    public:
        class LockObject
        {
        public:
            void Initialize() {}
            nn::Result TryInitialize() { return ResultSuccess(); }
            void Finalize() {}
        };
        
        class ScopedLock : private Locker::ScopedLock
        {
        public:
            ScopedLock(const LockObject&) : Locker::ScopedLock(g_Mutex) {}
        };
    };

};

template <class Locker> Locker LockPolicy::Global<Locker>::g_Mutex = nn::WithInitialize();

}}

#endif

#endif
