/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_BufferManager.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_FND_BUFFERMANAGER_H_
#define NN_FND_FND_BUFFERMANAGER_H_

#ifdef __cplusplus

#include <nn/types.h>

namespace nn { namespace fnd {

template <size_t BuddyPageSize, size_t MaxOrder, size_t MaxCache>
class BufferManager
{
public:

    typedef bit64 CacheHandle;
    
    // Allocate memory for small object
    void* AllocateSmall(size_t size);
    void DeallocateSmall(void* p, size_t size);
    
private:

    static const size_t BUDDY_PAGE_SIZE = BuddyPageSize;
    
    class CacheHandleTable
    {
    private:
        
        class Entry : public nn::fnd::IntrusiveLinkedList<Entry>::Item
        {
        private:
        
            CacheHandle m_Handle;
            nn::fnd::MemoryRange m_MemoryRange;
        
        public:
            
            Entry() : m_Handle(0) {}
            
            bool IsValid() const { return m_Handle != 0; }
            
            void Invalidate() { this->m_Handle = 0; }
            
            void Register(CacheHandle handle, nn::fnd::MemoryRange memoryRange)
            {
                NN_TASSERT_(!this->IsValid());
                this->m_Handle = handle;
                this->m_MemoryRange = memoryRange;
                NN_TASSERT_(this->IsValid());
            }
            
            nn::fnd::MemoryRange Unregister()
            {
                NN_TASSERT_(IsValid());
                Invalidate();
                return m_MemoryRange;
            }
            
            bool HasHandle(CacheHandle handle)
            {
                NN_TASSERT_(handle != 0);
                return handle == m_Handle;
            }
            
        };
        
        static const size_t MAX_CACHE = MaxCache;
        
        Entry m_Entries[MAX_CACHE];
        nn::fnd::IntrusiveLinkedList<Entry> m_CacheList;
        nn::os::CriticalSection m_CriticalSection;
        CacheHandle m_CurrentHandle;
        
        Entry* FindEntry(CacheHandle handle)
        {
            for (s32 i = 0; i < MAX_CACHE; ++i)
            {
                if (m_Entries[i].HasHandle(handle))
                {
                    return m_Entries + i;
                }
            }
            return 0;
        }
        
        Entry* FindEmptyEntry()
        {
            for (s32 i = 0; i < MAX_CACHE; ++i)
            {
                if (!m_Entries[i].IsValid())
                {
                    return m_Entries + i;
                }
            }
            return 0;
        }
        
        CacheHandle PublishCacheHandle()
        {
            return ++m_CurrentHandle;
        }
        
    public:
    
        CacheHandleTable() : m_CurrentHandle(0)
        {
            m_CriticalSection.Initialize();
        }
        
        bool Register(CacheHandle* pOut, const nn::fnd::MemoryRange& memoryRange)
        {
            nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);
            
            if (Entry* p = FindEmptyEntry())
            {
                CacheHandle handle = PublishCacheHandle();
                p->Register(handle, memoryRange);
                m_CacheList.PushBack(p);
                *pOut = handle;
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool Unregister(nn::fnd::MemoryRange* pOut, CacheHandle handle)
        {
            nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);
            
            if (Entry* p = FindEntry(handle))
            {
                m_CacheList.Erase(p);
                *pOut = p->Unregister();
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool UnregisterOldest(nn::fnd::MemoryRange* pOut)
        {
            nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);
            
            if (Entry* p = m_CacheList.GetFront())
            {
                m_CacheList.Erase(p);
                *pOut = p->Unregister();
                return true;
            }
            else
            {
                return false;
            }
        }
        
    };


    nn::fnd::BuddyHeapTemplate<BUDDY_PAGE_SIZE, MaxOrder, nn::os::LockPolicy::NoLock > m_Buddy;
    nn::os::CriticalSection m_CriticalSection;
    CacheHandleTable m_CacheHandleTable;
    
public:

    void Initialize(const nn::fnd::MemoryRange& memoryRange)
    {
        m_Buddy.Initialize(memoryRange.GetAddress(), memoryRange.GetSize());
        m_CriticalSection.Initialize();
    }
    
    // Register the specified buffer as cache.
    // Return handle to access cache.
    CacheHandle RegisterAsCache(const nn::fnd::MemoryRange& memoryRange)
    {
        CacheHandle ret;
        while (!m_CacheHandleTable.Register(&ret, memoryRange))
        {
            nn::fnd::MemoryRange cachedOut;
            if (m_CacheHandleTable.UnregisterOldest(&cachedOut))
            {
                this->DeallocateBuffer(cachedOut);
            }
        }
        return ret;
    }
    
    // Get the cache region corresponding to the given handle.
    // In this case, return true, write the region to *pOut, and cancel cache registration.
    // If necessary, cache could be corrupted and invalidated due to another allocation. In this case, return false.
    // 
    // The address returned here may not always be the same as the previous one.
    //Because it is designed to allow movement, it uses the address returned by this function, not the memory registered by RegisterAsCache. 
    //
    bool AcquireCache(nn::fnd::MemoryRange* pOut, CacheHandle handle)
    {
        return m_CacheHandleTable.Unregister(pOut, handle);
    }
    
    // Allocate a buffer bigger than requiredSize.
    // If there is sufficient space, allocate a buffer that is roughly the size of idealSize.
    nn::fnd::MemoryRange AllocateBuffer(size_t requiredSize, size_t idealSize)
    {
        s32 idealOrder = m_Buddy.GetOrder(idealSize);
        s32 requiredOrder = m_Buddy.GetOrder(requiredSize);
        
        nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);
        
        while (true)
        {
            for (s32 order = idealOrder; order >= requiredOrder; --order)
            {
                if (void* p = m_Buddy.AllocateByOrder(order))
                {
                    NN_TASSERT_(requiredSize <= (BUDDY_PAGE_SIZE << order));
                    return nn::fnd::MemoryRange(reinterpret_cast<uptr>(p), reinterpret_cast<uptr>(p) + BUDDY_PAGE_SIZE << order);
                }
            }
            nn::fnd::MemoryRange memoryRange;
            if (m_CacheHandleTable.UnregisterOldest(&memoryRange))
            {
                this->DeallocateBuffer(memoryRange);
            }
            else
            {
                // What do to in this case?
                return nn::fnd::MemoryRange(0, 0);
            }
        }
    }
    
    nn::fnd::MemoryRange AllocateBuffer(size_t size) { return AllocateBuffer(size, size); }
    
    void DeallocateBuffer(const nn::fnd::MemoryRange& memoryRange)
    {
        nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);
        m_Buddy.Free(reinterpret_cast<void*>(memoryRange.GetAddress()), m_Buddy.GetOrder(memoryRange.GetSize()));
    }

};

}}

#endif

#endif
