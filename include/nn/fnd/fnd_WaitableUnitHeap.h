/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_WaitableUnitHeap.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_FND_WAITABLEUNITHEAP_H_
#define NN_FND_FND_WAITABLEUNITHEAP_H_

#include <nn/os.h>
#include <nn/fnd/fnd_UnitHeap.h>

#ifdef __cplusplus

namespace nn { namespace fnd {

// not documented
// Untested
template <class LockPolicy = nn::os::LockPolicy::Object<nn::os::CriticalSection>, class Semaphore = nn::os::LightSemaphore>
class WaitableUnitHeap : private UnitHeapTemplate<LockPolicy>
{
private:

    typedef UnitHeapTemplate<LockPolicy> Base;
    Semaphore m_Semaphore;

public:

    using Base::GetRequiredHeapSize;

    WaitableUnitHeap() {}

    WaitableUnitHeap(size_t unit, uptr addr, size_t size, s32 alignment = Base::DEFAULT_ALIGNMENT, bit32 option = 0)
    {
        Initialize(unit, addr, size, alignment, option);
    }
    
    template <class MemoryBlock>
    explicit WaitableUnitHeap(size_t unit, const MemoryBlock& block, s32 alignment = Base::DEFAULT_ALIGNMENT, bit32 option = 0)
    {
        Initialize(unit, block.GetAddress(), block.GetSize(), alignment, option);
    }
    
    void Initialize(size_t unit, uptr addr, size_t size, s32 alignment = Base::DEFAULT_ALIGNMENT, bit32 option = 0)
    {
        Base::Initialize(unit, addr, size, alignment, option);
        s32 maxCount = Base::GetTotalSize() / Base::GetUnitSize();
        this->m_Semaphore.Initialize(maxCount, maxCount);
    }

    using Base::Invalidate;

    /* Please see man pages for details 
        
    */
    void Finalize()
    {
        m_Semaphore.Finalize();
        Base::Finalize();
    }
    
    /* Please see man pages for details 
        

        
    */
    void* TryAllocate()
    {
        if (m_Semaphore.TryAcquire())
        {
            void* ret = Base::Allocate();
            NN_TASSERT_(ret);
            return ret;
        }
        else
        {
            return 0;
        }
    }

    /* Please see man pages for details 
        
               

        
    */
    void* Allocate()
    {
        m_Semaphore.Acquire();
        void* ret = Base::Allocate();
        NN_TASSERT_(ret);
        return ret;
    }
    
    /* Please see man pages for details 
        

        
    */
    void Free(void* p)
    {
        Base::Free(p);
        m_Semaphore.Release();
    }

    /* Please see man pages for details 
        

               

        
	*/
    virtual void FreeV(void* p) { Free(p); }

    using Base::GetUnitSize;

    using Base::GetAllocatableCount;
    
    /* Please see man pages for details 
        

        
     */
    virtual void* GetStartAddress() const { return Base::GetStartAddress(); }

    /* Please see man pages for details 
        

        
     */
    virtual size_t GetTotalSize() const { return Base::GetTotalSize(); }

    /* Please see man pages for details 
        
    */
    virtual void Dump() const { Base::Dump(); }
    
    /* Please see man pages for details 
        

        

        
	*/
    virtual bool HasAddress(const void* addr) const { return Base::HasAddress(addr); }

    class Allocator;
    
};

template <class LockPolicy, class Semaphore>
class WaitableUnitHeap<LockPolicy, Semaphore>::Allocator : public IAllocator
{
public:
    
    Allocator(WaitableUnitHeap& heap) : m_Heap(&heap) {}

    Allocator() : m_Heap(0) {}
    
    void Initialize(WaitableUnitHeap& heap) { m_Heap = &heap; }

    WaitableUnitHeap* GetHeap() { return m_Heap; }
    
    const WaitableUnitHeap* GetHeap() const { return m_Heap; }
    
    virtual void* Allocate(size_t size, s32 alignment);
    
    virtual void Free(void* p) { m_Heap->Free(p); }

private:
    WaitableUnitHeap* m_Heap;
};

template <class LockPolicy, class Semaphore>
inline void* WaitableUnitHeap<LockPolicy, Semaphore>::Allocator::Allocate(size_t size, s32 alignment)
{
    if (size == m_Heap->GetUnitSize() && alignment >= 0 && m_Heap->GetUnitSize() % alignment == 0)
    {
        return m_Heap->Allocate();
    }
    else
    {
        return 0;
    }
}

}}

#endif

#endif
