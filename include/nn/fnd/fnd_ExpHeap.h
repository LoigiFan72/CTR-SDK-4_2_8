/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_ExpHeap.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47798 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
  

*/

#ifndef NN_FND_FND_EXPHEAP_H_
#define NN_FND_FND_EXPHEAP_H_

#include <nn/types.h>
#include <nn/fnd/fnd_HeapBase.h>
#include <nn/fnd/fnd_MemoryRange.h>
#include <nn/fnd/fnd_Allocator.h>
#include <nn/util/util_TypeTraits.h>
#include <nn/util/detail/util_CLibImpl.h>
#include <nn/util/util_SizedEnum.h>
#include <nn/fnd/detail/fnd_DetailHeapHead.h>
#include <nn/os.h>

#define NN_FND_EXPHEAP_ALLOCATION_MODE_FIRST_FIT 0
#define NN_FND_EXPHEAP_ALLOCATION_MODE_BEST_FIT 1

#define NN_FND_EXPHEAP_ALLOCATION_DIRECTION_FRONT 0
#define NN_FND_EXPHEAP_ALLOCATION_DIRECTION_REAR 1

#ifdef __cplusplus

namespace nn { namespace fnd {

/* Please see man pages for details 
    

    
              
              
 */
class ExpHeapBase : public HeapBase
{
public:

    /* Please see man pages for details 
        
     */
    enum AllocationMode
    {
        /* Please see man pages for details 
            
         */
        ALLOCATION_MODE_FIRST_FIT = NN_FND_EXPHEAP_ALLOCATION_MODE_FIRST_FIT,
        /* Please see man pages for details 
            
         */
        ALLOCATION_MODE_BEST_FIT  = NN_FND_EXPHEAP_ALLOCATION_MODE_BEST_FIT
    };

    /* Please see man pages for details 
        
     */
    enum AllocationDirection
    {
        /* Please see man pages for details 
            
         */
        ALLOCATION_DIRECTION_FRONT = NN_FND_EXPHEAP_ALLOCATION_DIRECTION_FRONT,
        /* Please see man pages for details 
            
         */
        ALLOCATION_DIRECTION_REAR  = NN_FND_EXPHEAP_ALLOCATION_DIRECTION_REAR
    };

    /* Please see man pages for details 
        
    */
    typedef void (*BlockVisitor)(void* pBlock, const ExpHeapBase* heap, uptr param);

    /* Please see man pages for details 
        

        

        
     */
    size_t GetSizeOf(const void* pBlock) const;

    /* Please see man pages for details 
        

        

        
     */
    bit8 GetGroupIdOf(const void* pBlock) const;

    /* Please see man pages for details 
        

        

        
     */
    AllocationDirection GetDirectionOf(const void* pBlock) const;
    
protected:

	ExpHeapBase() : m_AllocCount(0) {}

    template <class MemoryBlock>
    explicit ExpHeapBase(const MemoryBlock& block, bit32 option) { Initialize(block.GetAddress(), block.GetSize(), option); }

    ExpHeapBase(uptr addr, size_t size, bit32 option) { Initialize(addr, size, option); }

    void Initialize(uptr addr, size_t size, bit32 option);

    void Invalidate();

    void Finalize();

    virtual ~ExpHeapBase() { Finalize(); }

    void* Allocate(size_t byteSize, s32 alignment = DEFAULT_ALIGNMENT, bit8 groupId = 0, AllocationMode mode = ALLOCATION_MODE_FIRST_FIT, bool reuse = false);

    void Free(void* p);

    virtual void FreeV(void* p) { Free(p); }

    size_t ResizeBlock(void* p, size_t newSize);

    void VisitAllBlocks(BlockVisitor visitor, uptr param);

    virtual void* GetStartAddress() const;

    virtual size_t GetTotalSize() const;

    size_t GetTotalFreeSize() const;

    size_t GetAllocatableSize(s32 alignment = DEFAULT_ALIGNMENT) const;

    u32 Adjust();

    MemoryRange Adjust(HeapAdjustMode mode);

    bool CheckHeap(bit32 option = OPTION_ERROR_PRINT) const;

    bool CheckBlock(const void* p, bit32 option = OPTION_ERROR_PRINT) const;

    virtual void Dump() const;

    virtual bool HasAddress(const void* addr) const;

private:

    detail::ExpHeapImpl m_ExpHeapImpl;

    size_t m_AllocCount;
    
};

/* Please see man pages for details 
    

    
    
              
              
              
              
              
              
              
              
    
    
 */
template <class LockPolicy>
class ExpHeapTemplate : public ExpHeapBase, private LockPolicy::LockObject
{
private:
    typedef ExpHeapBase Base;
    typedef typename LockPolicy::LockObject LockObject;
    typedef typename LockPolicy::ScopedLock ScopedLock;
public:

    /* Please see man pages for details 
        

        
        
        
     */
    ExpHeapTemplate() {}

    /* Please see man pages for details 
        

        
        
        
        
        
        

        
     */
    template <class MemoryBlock>
    explicit ExpHeapTemplate(const MemoryBlock& block, bit32 option = 0)
    {
        Initialize(block.GetAddress(), block.GetSize(), option);
    }

    /* Please see man pages for details 
        

        
      
        
        
        

        
        
        
     */
    ExpHeapTemplate(uptr addr, size_t size, bit32 option = 0)
    {
        Initialize(addr, size, option);
    }

    /* Please see man pages for details 
        
      
        
        
        
        
        

        
     */
    void Initialize(uptr addr, size_t size, bit32 option = 0)
    {
        Base::Initialize(addr, size, option);
        LockObject::Initialize();
    }

    /* Please see man pages for details 
        

                

                
                
                
                
                
                

        
        
        
        
        
    */
    static ExpHeapTemplate* Create(HeapBase* parent, void* addr, size_t size, bit32 option = 0, bit32 placement = HEAP_INFOPLACEMENT_HEAD);

    /* Please see man pages for details 
        

        
     */
    void Invalidate() { Base::Invalidate(); }

    /* Please see man pages for details 
        

        
     */
    void Finalize()
    {
        LockObject::Finalize();
        Base::Finalize();
    }

    /* Please see man pages for details 
        

        
     */
    virtual ~ExpHeapTemplate() {}

    /* Please see man pages for details 
        

        

        

        
        
        
        
        

        
     */
    void* Allocate(size_t byteSize, s32 alignment = DEFAULT_ALIGNMENT, bit8 groupId = 0, AllocationMode mode = ALLOCATION_MODE_FIRST_FIT, bool reuse = false)
    {
        ScopedLock lk(*this);
        return Base::Allocate(byteSize, alignment, groupId, mode, reuse);
    }

    /* Please see man pages for details 
        

        

        
     */
    void Free(void* p)
    {
        ScopedLock lk(*this);
        Base::Free(p);
    }

    /* Please see man pages for details 
        

                        

        

        
    */
    virtual void FreeV(void* p) { Free(p); }

    /* Please see man pages for details 
        

        
        

        
     */
    size_t ResizeBlock(void* p, size_t newSize)
    {
        ScopedLock lk(*this);
        return Base::ResizeBlock(p, newSize);
    }

    /* Please see man pages for details 
        

        
        

        
     */
    void VisitAllBlocks(BlockVisitor visitor, uptr param)
    {
        ScopedLock lk(*this);
        return Base::VisitAllBlocks(visitor, param);
    }

    /* Please see man pages for details 
        

        
     */
    virtual void* GetStartAddress() const
    {
        ScopedLock lk(*this);
        return Base::GetStartAddress();
    }

    /* Please see man pages for details 
        

        
     */
    virtual size_t GetTotalSize() const
    {
        ScopedLock lk(*this);
        return Base::GetTotalSize();
    }

    /* Please see man pages for details 
        

        
     */
    size_t GetTotalFreeSize() const
    {
        ScopedLock lk(*this);
        return Base::GetTotalFreeSize();
    }

    /* Please see man pages for details 
        

        

        
     */
    size_t GetAllocatableSize(s32 alignment = DEFAULT_ALIGNMENT) const
    {
        ScopedLock lk(*this);
        return Base::GetAllocatableSize(alignment);
    }

    /* Please see man pages for details 
        

        

                
                

        
     */
    u32 Adjust()
    {
        ScopedLock lk(*this);
        return Base::Adjust();
    }

    /* Please see man pages for details 
        

        

        

        
                            
     */
    MemoryRange Adjust(HeapAdjustMode mode)
    {
        ScopedLock lk(*this);
        return Base::Adjust(mode);
    }

    /* Please see man pages for details 
        

        

        
     */
    bool CheckHeap(bit32 option = OPTION_ERROR_PRINT) const
    {
        ScopedLock lk(*this);
        return Base::CheckHeap(option);
    }

    /* Please see man pages for details 
        

        
        

        
     */
    bool CheckBlock(const void* p, bit32 option = OPTION_ERROR_PRINT) const
    {
        ScopedLock lk(*this);
        return Base::CheckBlock(p, option);
    }
    
    /* Please see man pages for details 
        

        

        
    */
    virtual bool HasAddress(const void* addr) const
    {
        ScopedLock lk(*this);
        return Base::HasAddress(addr);
    }

    /* Please see man pages for details 
        

        
     */
    virtual void Dump() const
    {
        ScopedLock lk(*this);
        Base::Dump();
    }

    class Allocator;
    
};

/* Please see man pages for details 
    
 */
template <class LockPolicy>
class ExpHeapTemplate<LockPolicy>::Allocator : public IAllocator
{
public:
    
    /* Please see man pages for details 
        
        
        
        
        
        
     */
    Allocator(ExpHeapTemplate<LockPolicy>& heap, bit8 groupId = 0, AllocationMode mode = ExpHeapBase::ALLOCATION_MODE_FIRST_FIT, bool reuse = false) : m_Heap(0) { Initialize(heap, groupId, mode, reuse); }

    /* Please see man pages for details 
        
     */
    Allocator() : m_Heap(0) {}

    /* Please see man pages for details 
        
        
        
        
        
        
     */
    void Initialize(ExpHeapTemplate<LockPolicy>& heap, bit8 groupId = 0, AllocationMode mode = ExpHeapBase::ALLOCATION_MODE_FIRST_FIT, bool reuse = false)
    {
        NN_TASSERT_(!this->m_Heap);
        this->m_Heap = &heap;
        this->m_GroupId = groupId;
        this->m_AllocationMode = mode;
        this->m_Reuse = reuse;
    }
    
    /* Please see man pages for details 
        
        
     */
    ExpHeapTemplate<LockPolicy>* GetHeap() { return m_Heap; }
    
    /* Please see man pages for details 
        
        
     */
    const ExpHeapTemplate<LockPolicy>* GetHeap() const { return m_Heap; }

    /* Please see man pages for details 
        
        
        
        
        
        
    */
    virtual void* Allocate(size_t size, s32 alignment) { return m_Heap->Allocate(size, alignment, m_GroupId, m_AllocationMode, m_Reuse); }
    
    /* Please see man pages for details 
        
        
    */
    virtual void Free(void* p) { m_Heap->Free(p); }

    /* Please see man pages for details 
        
        
     */
    bit8 GetGroupId() const { return m_GroupId; }
    
    /* Please see man pages for details 
        
        
     */
    void SetGroupId(bit8 groupId) { this->m_GroupId = groupId; }

    /* Please see man pages for details 
        
        
     */
    AllocationMode GetAllocationMode() const { return m_AllocationMode; }
    
    /* Please see man pages for details 
        
        
     */
    void SetAllocationMode(AllocationMode allocationMode) { this->m_AllocationMode = allocationMode; }

    /* Please see man pages for details 
        
        
     */
    bool GetUseMarginOfAlignment() const { return m_Reuse; }
    
    /* Please see man pages for details 
        
        
     */
    void SetUseMarginOfAlignment(bool reuse) { m_Reuse = reuse; }

private:
    ExpHeapTemplate<LockPolicy>* m_Heap;
    bit8 m_GroupId;
    nn::util::SizedEnum1<AllocationMode> m_AllocationMode;
    bool m_Reuse;
    NN_PADDING1;
};

/* Please see man pages for details 
    
*/
typedef ExpHeapTemplate<nn::os::LockPolicy::NoLock> ExpHeap;

/* Please see man pages for details 
    
*/
typedef ExpHeapTemplate<nn::os::LockPolicy::Object<nn::os::CriticalSection> > ThreadSafeExpHeap;

template <class LockPolicy>
ExpHeapTemplate<LockPolicy>* ExpHeapTemplate<LockPolicy>::Create(HeapBase* parent, void* addr, size_t size, bit32 option, bit32 placement)
{
    ExpHeapTemplate* heap;

    if ( parent->FindHeap(addr) != parent ) return 0;
    
    if ( placement == HEAP_INFOPLACEMENT_HEAD )
    {
        heap = new (addr) ExpHeapTemplate(reinterpret_cast<uptr>(addr)+sizeof(ExpHeapTemplate), static_cast<size_t>(size - sizeof(ExpHeapTemplate)), option);
    }
    else if ( placement == HEAP_INFOPLACEMENT_TAIL )
    {
        void* placeaddr = reinterpret_cast<void*>(reinterpret_cast<uptr>(addr)+static_cast<size_t>(size - sizeof(ExpHeapTemplate)));
        heap = new (placeaddr) ExpHeapTemplate(reinterpret_cast<uptr>(addr), static_cast<size_t>(size - sizeof(ExpHeapTemplate)), option);
    }
    else
    {
        return 0;
    }
    
    heap->SetParent(parent);
    
    return heap;
}

}}

#endif

#endif
