/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_FrameHeap.h

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

#ifndef NN_FND_FND_FRAMEHEAP_H_
#define NN_FND_FND_FRAMEHEAP_H_

#include <nn/types.h>
#include <nn/fnd/fnd_Allocator.h>
#include <nn/fnd/fnd_HeapBase.h>
#include <nn/fnd/fnd_MemoryRange.h>
#include <nn/assert.h>
#include <nn/os.h>

#ifdef __cplusplus

#define NN_FND_FRAMEHEAP_FREE_HEAD 1
#define NN_FND_FRAMEHEAP_FREE_TAIL 2
#define NN_FND_FRAMEHEAP_FREE_ALL (NN_FND_FRAMEHEAP_FREE_HEAD | NN_FND_FRAMEHEAP_FREE_TAIL)

#define NN_FND_FRAMEHEAP_ADJUST_TAIL 1
#define NN_FND_FRAMEHEAP_ADJUST_HEAD -1

namespace nn { namespace fnd {

/* Please see man pages for details 
    

    
              
              
 */
class FrameHeapBase : public HeapBase
{
public:
    
    class State;
    
protected:

    FrameHeapBase() : m_Addr(0) {}

    FrameHeapBase(uptr addr, size_t size, bit32 option = 0) : m_Addr(0) { Initialize(addr, size, option); }

    template <class MemoryBlock>
    FrameHeapBase(const MemoryBlock& block, bit32 option = 0) : m_Addr(0) { Initialize(block.GetAddress(), block.GetSize(), option); }

    void Initialize(uptr addr, size_t size, bit32 option = 0);

    void Finalize() { m_Addr = 0; }

    virtual ~FrameHeapBase() { Finalize(); }

    void* Allocate(size_t size, s32 alignment);

    size_t ResizeBlock(void* p, size_t newSize);
    
    void FreeAll(int mode);

    virtual void FreeV(void*) {}
 
    State SaveState();

    void RestoreState(State state);

    MemoryRange Adjust(int mode);

    size_t GetAllocatableSize(s32 alignment) const;

    virtual void* GetStartAddress() const { return reinterpret_cast<void*>(m_Addr); }

    virtual size_t GetTotalSize() const { return m_Size; }

    virtual void Dump() const;

    virtual bool HasAddress(const void* addr) const;
    
private:
    uptr m_Addr;
    size_t m_Size;
    uptr m_CurrentHead;
    uptr m_CurrentTail;
};

/* Please see man pages for details 
    
 */
class FrameHeapBase::State
{
public:
    
    /* Please see man pages for details 
        

        
     */
    explicit State(FrameHeapBase& heap) : m_Head(heap.m_CurrentHead), m_Tail(heap.m_CurrentTail) {}
    
    /* Please see man pages for details 
        
     */
    State() : m_Head(0), m_Tail(0) {}
    
private:
    uptr m_Head;
    uptr m_Tail;

    explicit State(uptr head, uptr tail) : m_Head(head), m_Tail(tail) {}
    
    friend class FrameHeapBase;
};

inline void* FrameHeapBase::Allocate(size_t size, s32 alignment)
{
    NN_TASSERT_(size > 0);
    NN_TASSERT_(alignment != 0);
    uptr ret;
    
    if ( alignment == 0 )
    {
        NN_TPANIC_("invalid argument: alignment == 0");
    }

    if ( alignment > 0 ) {
        ret = RoundUp(m_CurrentHead, alignment);
        uptr current = ret + size;

        if (current > m_CurrentTail)
        {
            return 0;
        }

        m_CurrentHead = current;
    }
    else
    {
        uptr current = ret = RoundDown(m_CurrentTail-size, -alignment);

        if (current < m_CurrentHead)
        {
            return 0;
        }

        m_CurrentTail = current;
    }


    // File options
    DebugFillMemory(ret, size, HEAP_FILL_TYPE_ALLOC);
    FillMemoryZero(ret, size);

    return reinterpret_cast<void*>(ret);
}

inline void FrameHeapBase::FreeAll(int mode)
{
    NN_TASSERT_(  mode == NN_FND_FRAMEHEAP_FREE_HEAD ||
                mode == NN_FND_FRAMEHEAP_FREE_TAIL ||
                mode == NN_FND_FRAMEHEAP_FREE_ALL);

    if ( mode & NN_FND_FRAMEHEAP_FREE_HEAD )
    {
        DebugFillMemory(m_Addr, m_CurrentHead - m_Addr, HEAP_FILL_TYPE_FREE);
        this->m_CurrentHead = this->m_Addr;
    }

    if ( mode & NN_FND_FRAMEHEAP_FREE_TAIL )
    {
        DebugFillMemory(m_CurrentTail, m_Addr + m_Size - m_CurrentTail, HEAP_FILL_TYPE_FREE);
        this->m_CurrentTail = this->m_Addr + this->m_Size;
    }
}

inline size_t FrameHeapBase::ResizeBlock(void* p, size_t newSize)
{
    // TODO: debug_fill
    uptr& addr = reinterpret_cast<uptr&>(p);
    NN_TASSERT_(m_Addr <= addr && addr < m_CurrentTail);
    NN_TASSERT_(addr <= m_CurrentHead);
    uptr current = addr + newSize;
    if (current < m_CurrentTail)
    {
        if ( current < this->m_CurrentHead )
        {
            DebugFillMemory(current, this->m_CurrentHead - current, HEAP_FILL_TYPE_FREE);
        }
        if ( this->m_CurrentHead < current )
        {
            FillMemoryZero(this->m_CurrentHead, current - this->m_CurrentHead);
        }
        this->m_CurrentHead = current;
        return newSize;
    }
    else
    {
        return 0;
    }
}

inline MemoryRange FrameHeapBase::Adjust(int mode)
{
    // TODO: debug_fill
    if ( mode == 0 )
    {
        NN_TPANIC_("invalid argument: mode == 0");
    }

    if ( mode > 0 )
    {
        if ( m_CurrentTail != m_Addr + m_Size )
        {
            NN_TPANIC_("invalid call: tail used");
        }

        DebugFillMemory(m_CurrentHead, m_Addr + m_Size - m_CurrentHead, HEAP_FILL_TYPE_FREE);

        uptr oldtail = m_Addr + m_Size;
        this->m_Size = m_CurrentHead - m_Addr;
        this->m_CurrentTail = m_CurrentHead;
        return MemoryRange(this->m_CurrentTail, oldtail);
    }
    else
    {
        if ( m_CurrentHead != m_Addr )
        {
            NN_TPANIC_("invalid call: head used");
        }

        DebugFillMemory(m_Addr, m_CurrentTail - m_Addr, HEAP_FILL_TYPE_FREE);

        uptr oldhead = m_Addr;
        this->m_Size = m_Addr + m_Size - m_CurrentTail;
        this->m_CurrentHead = m_CurrentTail;
        this->m_Addr = m_CurrentTail;
        return MemoryRange(oldhead, m_Addr);
    }
}

inline FrameHeapBase::State FrameHeapBase::SaveState()
{
    return State(m_CurrentHead, m_CurrentTail);
}

inline void FrameHeapBase::RestoreState(FrameHeapBase::State state)
{
    NN_TASSERT_(this->m_Addr <= state.m_Head && state.m_Head <= this->m_Addr + this->m_Size);
    NN_TASSERT_(this->m_Addr <= state.m_Tail && state.m_Tail <= this->m_Addr + this->m_Size);
    NN_TASSERT_(state.m_Head <= this->m_CurrentHead);
    NN_TASSERT_(state.m_Tail >= this->m_CurrentTail);

    this->m_CurrentHead = state.m_Head;
    this->m_CurrentTail = state.m_Tail;

    DebugFillMemory(m_CurrentHead, m_CurrentTail - m_CurrentHead, HEAP_FILL_TYPE_FREE);
}

inline size_t FrameHeapBase::GetAllocatableSize(s32 alignment) const
{
    NN_TASSERT_(alignment != 0);

    if ( alignment == 0 )
    {
        NN_TPANIC_("invalid argument: alignment == 0");
    }

    if ( alignment < 0 )
    {
        alignment = -alignment;
    }

    uptr addr = RoundUp(m_CurrentHead, alignment);
    if (addr <= m_CurrentTail)
    {
        return m_CurrentTail - addr;
    }
    else
    {
        return 0;
    }
}

inline bool FrameHeapBase::HasAddress(const void* addr) const
{
    return m_Addr <= reinterpret_cast<uptr>(addr)
        && reinterpret_cast<uptr>(addr) < (m_Addr+m_Size);
}

/* Please see man pages for details 
    

    
    
              
              
              
              
              
              
              
              
    
    
*/
template <class LockPolicy>
class FrameHeapTemplate : public FrameHeapBase, private LockPolicy::LockObject
{
private:
    typedef FrameHeapBase Base;
    typedef typename LockPolicy::LockObject LockObject;
    typedef typename LockPolicy::ScopedLock ScopedLock;
public:

    /* Please see man pages for details 
        
     */
    FrameHeapTemplate() {}

    /* Please see man pages for details 
        
      
        
        
        
     */
    FrameHeapTemplate(uptr addr, size_t size, bit32 option = 0) { Initialize(addr, size, option); }

    /* Please see man pages for details 
        
      
        
        
     */
    template <class MemoryBlock>
    FrameHeapTemplate(const MemoryBlock& block, bit32 option = 0) { Initialize(block.GetAddress(), block.GetSize(), option); }

    /* Please see man pages for details 
        

                    

                    
                    
                    
                    
                    
                    

        
        
                                
        
        
        

        
    */
    static FrameHeapTemplate* Create(HeapBase* parent, void* addr, size_t size, bit32 option = 0, bit32 placement = HEAP_INFOPLACEMENT_HEAD);

    /* Please see man pages for details 
        
      
        
        
        

        
     */
    void Initialize(uptr addr, size_t size, bit32 option = 0)
    {
        Base::Initialize(addr, size, option);
        LockObject::Initialize();
    }

    /* Please see man pages for details 
        

        
     */
    void Finalize()
    {
        LockObject::Finalize();
        Base::Finalize();
    }

    /* Please see man pages for details 
        

        
     */
    virtual ~FrameHeapTemplate() {}

    /* Please see man pages for details 
        

        
        

        

        
     */
    void* Allocate(size_t size, s32 alignment = DEFAULT_ALIGNMENT)
    {
        ScopedLock lk(*this);
        return Base::Allocate(size, alignment);
    }

    /* Please see man pages for details 
        

                    

        
        

        
     */
    size_t ResizeBlock(void* p, size_t newSize)
    {
        ScopedLock lk(*this);
        return Base::ResizeBlock(p, newSize);
    }
    
    /* Please see man pages for details 
        

                    

                    

                    

        

        
     */
    void Free(int mode = NN_FND_FRAMEHEAP_FREE_ALL)
    {
        ScopedLock lk(*this);
        Base::FreeAll(mode);
    }

    /* Please see man pages for details 
        

        

        
     */
    virtual void FreeV(void*) { NN_TASSERT_(0); }
    
    class ScopedFrame;
    
    /* Please see man pages for details 
        

        
     */
    State SaveState()
    {
        ScopedLock lk(*this);
        return Base::SaveState();
    }

    /* Please see man pages for details 
        

        

        
     */
    void RestoreState(State state)
    {
        ScopedLock lk(*this);
        Base::RestoreState(state);
    }

    /* Please see man pages for details 
        

                    
                    

                    
                    

        

        
     */
    MemoryRange Adjust(int mode = NN_FND_FRAMEHEAP_ADJUST_TAIL)
    {
        ScopedLock lk(*this);
        return Base::Adjust(mode);
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
    virtual bool HasAddress(const void* addr) const
    {
        ScopedLock lk(*this);
        return Base::HasAddress(addr);
    }

    /* Please see man pages for details 
        

        
     */
    virtual void Dump() const { Base::Dump(); };
    
    // FrameHeap's allocator is not supported
    //class Allocator;

private:
    uptr m_Addr;
    size_t m_Size;
    uptr m_CurrentHead; // The first address for the blank region
    uptr m_CurrentTail; // The last address + 4 for the blank region
    bit32 m_Option;
};

/* Please see man pages for details 
    
 */
template <class LockPolicy>
class FrameHeapTemplate<LockPolicy>::ScopedFrame
{
public:
    /* Please see man pages for details 
        

        
     */
    explicit ScopedFrame(FrameHeapTemplate<LockPolicy>& heap) : m_State(heap), m_Heap(heap) {}
    /* Please see man pages for details 
        
     */
    ~ScopedFrame() { m_Heap.RestoreState(m_State); }
    
private:
    FrameHeapTemplate<LockPolicy>::State m_State;
    FrameHeapTemplate<LockPolicy>& m_Heap;
};

/* Please see man pages for details 
    
*/
typedef FrameHeapTemplate<nn::os::LockPolicy::NoLock> FrameHeap;

/* Please see man pages for details 
    
*/
typedef FrameHeapTemplate<nn::os::LockPolicy::Object<nn::os::CriticalSection> > ThreadSafeFrameHeap;

template <class LockPolicy>
FrameHeapTemplate<LockPolicy>* FrameHeapTemplate<LockPolicy>::Create(HeapBase* parent, void* addr, size_t size, bit32 option, bit32 placement)
{
    FrameHeapTemplate* heap;

    if ( parent->FindHeap(addr) != parent ) return 0;

    if ( placement == HEAP_INFOPLACEMENT_HEAD )
    {
        heap = new (addr) FrameHeapTemplate(reinterpret_cast<uptr>(addr)+sizeof(FrameHeapTemplate), static_cast<size_t>(size - sizeof(FrameHeapTemplate)), option);
    }
    else if ( placement == HEAP_INFOPLACEMENT_TAIL )
    {
        void* placeaddr = reinterpret_cast<void*>(reinterpret_cast<uptr>(addr)+static_cast<size_t>(size - sizeof(FrameHeapTemplate)));
        heap = new (placeaddr) FrameHeapTemplate(reinterpret_cast<uptr>(addr), static_cast<size_t>(size - sizeof(FrameHeapTemplate)), option);
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
