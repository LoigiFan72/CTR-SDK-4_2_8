/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_UnitHeap.h

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

#ifndef NN_FND_FND_UNIT_HEAP_H_
#define NN_FND_FND_UNIT_HEAP_H_

#include <nn/fnd/fnd_HeapBase.h>
#include <nn/util/util_TypeTraits.h>
#include <nn/util/util_StaticAssert.h>
#include <nn/fnd/fnd_Allocator.h>
#include <nn/assert.h>
#include <nn/os.h>


#ifdef __cplusplus

namespace nn { namespace fnd {

/* Please see man pages for details 
    

    
              
              
 */
class UnitHeapBase : public HeapBase
{
public:

    /* Please see man pages for details 
        

        
        
        
     */
    static size_t GetRequiredHeapSize(size_t unit, size_t numUnit, s32 alignment = DEFAULT_ALIGNMENT);
    
protected:

    UnitHeapBase() : m_FreeNode(0) {}

    UnitHeapBase(size_t unit, uptr addr, size_t size, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0) : m_FreeNode(0) { Initialize(unit, addr, size, alignment, option); }

    template <class MemoryBlock>
    explicit UnitHeapBase(size_t unit, const MemoryBlock& block, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0) : m_FreeNode(0) { Initialize(unit, block.GetAddress(), block.GetSize(), alignment, option); }

    void Initialize(size_t unit, uptr addr, size_t size, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0);

    void Invalidate();

    void Finalize();

    virtual ~UnitHeapBase();

    void* Allocate();

    void Free(void* p);

    virtual void FreeV(void* p);

    size_t GetUnitSize() const { return m_Unit; }

    size_t GetAllocatableCount() const { return m_Size / m_Unit - m_Count; }

    size_t GetAllocatedCount() const { return m_Count; }

    s32 GetAlignment() const { return m_Alignment; }

    virtual void* GetStartAddress() const { return reinterpret_cast<void*>(m_Addr); }

    virtual size_t GetTotalSize() const { return m_Size; }

    virtual void Dump() const;

    virtual bool HasAddress(const void* addr) const;

private:

    bool IsFreeNode(uptr addr) const;

    struct Node
    {
        Node* next;
    };

    size_t m_Unit;
    uptr m_Addr;
    size_t m_Size;
    Node* m_FreeNode;
    s32 m_Alignment;
    size_t m_Count;
    
};

inline void UnitHeapBase::Finalize()
{
    if (m_FreeNode == 0)
    {
        return;
    }
    NN_TASSERT_(m_Count == 0);
    this->m_FreeNode = 0;
}

inline UnitHeapBase::~UnitHeapBase()
{
    Finalize();
}

inline void UnitHeapBase::Invalidate()
{
    this->m_FreeNode = 0;
}

inline void* UnitHeapBase::Allocate()
{
    void* ret = reinterpret_cast<void*&>(m_FreeNode);
    if (ret)
    {
        this->m_FreeNode = m_FreeNode->next;
        ++this->m_Count;

        // File options
        DebugFillMemory(reinterpret_cast<uptr>(ret), m_Unit, HEAP_FILL_TYPE_ALLOC);
        FillMemoryZero(reinterpret_cast<uptr>(ret), m_Unit);
    }

    return ret;
}

inline bool UnitHeapBase::HasAddress(const void* addr) const
{
    return m_Addr <= reinterpret_cast<uptr>(addr)
        && reinterpret_cast<uptr>(addr) < (m_Addr+m_Size);
}

inline void UnitHeapBase::Free(void* p)
{
    NN_TASSERT_(HasAddress(p));

    DebugFillMemory(reinterpret_cast<uptr>(p), m_Unit, HEAP_FILL_TYPE_FREE);

    reinterpret_cast<Node*&>(p)->next = m_FreeNode;
    this->m_FreeNode = reinterpret_cast<Node*&>(p);
    --this->m_Count;
}

inline void UnitHeapBase::FreeV(void* p)
{
    Free(p);
}

/* Please see man pages for details 
    

    
    
              
              
              
              
              
              
              
              
    
    
*/
template <class LockPolicy>
class UnitHeapTemplate : public UnitHeapBase, private LockPolicy::LockObject
{
private:
    typedef UnitHeapBase Base;
    typedef typename LockPolicy::LockObject LockObject;
    typedef typename LockPolicy::ScopedLock ScopedLock;
public:

    /* Please see man pages for details 
        

        
        
        
     */
    static size_t GetRequiredHeapSize(size_t unit, size_t numUnit, s32 alignment = DEFAULT_ALIGNMENT)
    {
        return Base::GetRequiredHeapSize(unit, numUnit, alignment);
    }

    /* Please see man pages for details 
        
     */
    UnitHeapTemplate() {}

    /* Please see man pages for details 
        
      
        
        
        
        
        
     */
    UnitHeapTemplate(size_t unit, uptr addr, size_t size, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0)
    {
        Initialize(unit, addr, size, alignment, option);
    }

    /* Please see man pages for details 
        
      
        
        
        
        
     */
    template <class MemoryBlock>
    explicit UnitHeapTemplate(size_t unit, const MemoryBlock& block, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0)
    {
        Initialize(unit, block.GetAddress(), block.GetSize(), alignment, option);
    }

    /* Please see man pages for details 
        

                
                
                
                
                
                
                

        
        
        
        
        
        
        
    */
    static UnitHeapTemplate* Create(HeapBase* parent, size_t unit, void* addr, size_t size, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0, bit32 placement = HEAP_INFOPLACEMENT_HEAD);

    /* Please see man pages for details 
        
               
      
        
        
        
        
        
     */
    void Initialize(size_t unit, uptr addr, size_t size, s32 alignment = DEFAULT_ALIGNMENT, bit32 option = 0)
    {
        Base::Initialize(unit, addr, size, alignment, option);
        LockObject::Initialize();
    }

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
    virtual ~UnitHeapTemplate() {}

    /* Please see man pages for details 
        

        
                
    */
    void* Allocate()
    {
        ScopedLock lk(*this);
        return Base::Allocate();
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
    size_t GetUnitSize() const { return Base::GetUnitSize(); }

    /* Please see man pages for details 
        

        
    */
    size_t GetAllocatableCount() const
    {
        ScopedLock lk(*this);
        return Base::GetAllocatableCount();
    }

    /* Please see man pages for details 
        

        
    */
    size_t GetAllocatedCount() const {
        ScopedLock lk(*this);
        return Base::GetAllocatedCount();
    }

    /* Please see man pages for details 
        

        
    */
    size_t GetAlignment() const {
        ScopedLock lk(*this);
        return Base::GetAlignment();
    }

    /* Please see man pages for details 
        

        
     */
    virtual void* GetStartAddress() const { return Base::GetStartAddress(); }

    /* Please see man pages for details 
        

        
     */
    virtual size_t GetTotalSize() const { return Base::GetTotalSize(); }

    /* Please see man pages for details 
        

        
     */
    virtual void Dump() const
    {
        ScopedLock lk(*this);
        Base::Dump();
    }
    
    /* Please see man pages for details 
        

        

        
    */
    virtual bool HasAddress(const void* addr) const { return Base::HasAddress(addr); }

    class Allocator;
    
};

/* Please see man pages for details 
    
 */
template <class LockPolicy>
class UnitHeapTemplate<LockPolicy>::Allocator : public IAllocator
{
public:
    
    /* Please see man pages for details 
        
        
        
     */
    Allocator(UnitHeapTemplate<LockPolicy>& heap) : m_Heap(&heap) {}

    /* Please see man pages for details 
        
     */
    Allocator() : m_Heap(0) {}
    
    /* Please see man pages for details 
        
        
        
     */
    void Initialize(UnitHeapTemplate<LockPolicy>& heap) { m_Heap = &heap; }

    /* Please see man pages for details 
        
        
     */
    UnitHeapTemplate<LockPolicy>* GetHeap() { return m_Heap; }
    
    /* Please see man pages for details 
        
        
     */
    const UnitHeapTemplate<LockPolicy>* GetHeap() const { return m_Heap; }
    
    /* Please see man pages for details 
        
        
        
        
        
        
    */
    virtual void* Allocate(size_t size, s32 alignment);
    
    /* Please see man pages for details 
        
        
    */
    virtual void Free(void* p);

private:
    UnitHeapTemplate<LockPolicy>* m_Heap;
};

template <class LockPolicy>
inline void* UnitHeapTemplate<LockPolicy>::Allocator::Allocate(size_t size, s32 alignment)
{
    if (size == m_Heap->m_Unit && alignment >= 0 && m_Heap->m_Alignment % alignment == 0)
    {
        return m_Heap->Allocate();
    }
    else
    {
        return 0;
    }
}

template <class LockPolicy>
inline void UnitHeapTemplate<LockPolicy>::Allocator::Free(void* p)
{
    m_Heap->Free(p);
}

/* Please see man pages for details 
    
*/
typedef UnitHeapTemplate<nn::os::LockPolicy::NoLock> UnitHeap;

/* Please see man pages for details 
    
*/
typedef UnitHeapTemplate<nn::os::LockPolicy::Object<nn::os::CriticalSection> > ThreadSafeUnitHeap;

template <class LockPolicy>
UnitHeapTemplate<LockPolicy>* UnitHeapTemplate<LockPolicy>::Create(HeapBase* parent, size_t unit, void* addr, size_t size, s32 alignment, bit32 option, bit32 placement)
{
    UnitHeapTemplate* heap;
    if ( parent->FindHeap(addr) != parent ) return 0;

    if ( placement == HEAP_INFOPLACEMENT_HEAD )
    {
        heap = new (addr) UnitHeapTemplate(unit, reinterpret_cast<uptr>(addr)+sizeof(UnitHeapTemplate), static_cast<size_t>(size - sizeof(UnitHeapTemplate)), alignment, option);
    }
    else if ( placement == HEAP_INFOPLACEMENT_TAIL )
    {
        void* placeaddr = reinterpret_cast<void*>(reinterpret_cast<uptr>(addr)+static_cast<size_t>(size - sizeof(UnitHeapTemplate)));
        heap = new (placeaddr) UnitHeapTemplate(unit, reinterpret_cast<uptr>(addr), static_cast<size_t>(size - sizeof(UnitHeapTemplate)), alignment, option);
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
