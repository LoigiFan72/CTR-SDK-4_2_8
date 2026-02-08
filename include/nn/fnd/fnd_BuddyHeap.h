/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_BuddyHeap.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_FND_BUDDYHEAP_H_
#define NN_FND_FND_BUDDYHEAP_H_

#include <nn/types.h>
#include <nn/fnd/fnd_HeapBase.h>
#include <nn/fnd/fnd_Allocator.h>

namespace nn {
namespace fnd {

template<size_t PageSize, s32 MaxOrder>
class BuddyHeapBase : public nn::fnd::HeapBase
{
protected:
    template <s32 align, typename T>
    static T DivUp(T x)
    {
        return static_cast<T>( (x + (align - 1)) / align );
    }

    template<size_t alignment>
    static uptr RoundDown(uptr addr)
    {
        return (addr / alignment) * alignment;
    }

    template<size_t alignment>
    static uptr RoundUp(uptr addr)
    {
        return RoundDown<alignment>(addr + alignment - 1);
    }

public:
    static const size_t ALIGN = 8;

    /* Please see man pages for details 
        
    */
    static size_t GetNumMaxPages(void)
    {
        return 1 << (MAX_ORDER - 1);
    }

    /* Please see man pages for details 
        
    */
    static size_t GetMaxSize(void)
    {
        return GetNumMaxPages() * PAGE_SIZE;
    }

    /* Please see man pages for details 
        
        
        
    
*/
    void Initialize(uptr addr, size_t numPages)
    {
        NN_ASSERT((addr % ALIGN) == 0);

        m_HeapStart = addr;
        m_HeapSize  = PAGE_SIZE * numPages;

        NN_LOG_DEBUG("start %p\n", m_HeapStart);
        NN_LOG_DEBUG("size  %p\n", m_HeapSize);
        
        const size_t numMaxPages    = GetNumMaxPages();
        NN_LOG_DEBUG("numMaxPages %d\n", numMaxPages);
        const size_t maxSize        = GetMaxSize();
        NN_LOG_DEBUG("maxSize %d\n", maxSize);
        const size_t numMaxOrders   = m_HeapSize / maxSize;
        NN_LOG_DEBUG("numMaxOrders %d\n", numMaxOrders);
        
        NN_ASSERT(numMaxOrders > 0);

        // Provisional initialization of management area
        // Allocates one management area for each page.
        m_pPages = reinterpret_cast<Page*>(m_HeapStart);
        
        for (size_t i = 0; i < numPages; i++)
        {
            m_pPages[i].pNext  = NULL;
        }
        
        for (size_t i = 0; i < MAX_ORDER; ++i )
        {
            m_FreeArea[i].Initialize();
        }
        for (size_t i = 0; i < numMaxOrders; i++)
        {
            // Registers the start address of each page to the free list.
            m_FreeArea[MAX_ORDER - 1].PushBack(&(m_pPages[i * numMaxPages]));
        }
      
        // Relocate the management area (normally should be located in the same place)
        const size_t manageAreaSize = sizeof(Page) * numPages;

        if(m_pPages != reinterpret_cast<Page*>(AllocateByOrder(GetNearestHigherOrder(DivUp<PAGE_SIZE>(manageAreaSize)))))
        {
            NN_LOG_WARN("failed to allocate page managing area.");
        }
    }

    /* Please see man pages for details 
        
    */
    void Finalize(void){}

    /* Please see man pages for details 
        
        
        
    

*/
    void* AllocateByOrder(s32 order)
    {
        NN_ASSERT(order >= 0);
        
        NN_LOG_DEBUG("demands order %d\n", order);    
        

        Page* pPage = GetFreePage(order);
        NN_LOG_DEBUG("pPage = %08x\n", pPage);
        
        if(pPage)
        {
            uptr addr = GetAddressFromPage(*pPage);
            
            NN_LOG_DEBUG("returns order %d, address 0x%08X\n", order, addr);
            
            return reinterpret_cast<void*>(addr);
        }
        else
        {
            return NULL;
        }
    }

    /* Please see man pages for details 
        
               
        
        
    

*/
    void Free(void* p, s32 order)
    {
        if(!p)
        {
            return;
        }
        
        NN_ASSERT((reinterpret_cast<uptr>(p) - m_HeapStart) % PAGE_SIZE == 0);
        
        Page* pPage = GetPageFromAddress(reinterpret_cast<uptr>(p));

        // Is the page index divisible by the order?
        NN_ASSERT(GetIndexFromPage(*pPage) % (1 << order) == 0);

        NN_LOG_DEBUG("addr = 0x%08x, order = %d, pPage = 0x%08x\n", p, order, pPage);
        
        JointBuddies(pPage, order);
    }

    virtual void FreeV(void*) { NN_ASSERT(false); }

    /* Please see man pages for details 
        
    */
    virtual void* GetStartAddress() const { return reinterpret_cast<void*>(m_HeapStart); }
    
    /* Please see man pages for details 
        
    */
    virtual size_t GetTotalSize() const { return m_HeapSize; }
    
    /* Please see man pages for details 
        
    */
    virtual void Dump() const{};

    /* Please see man pages for details 
        
    */
    virtual bool HasAddress(const void* addr) const
    {
        return m_HeapStart <= reinterpret_cast<uptr>(addr)
           && reinterpret_cast<uptr>(addr) < m_HeapStart + m_HeapSize;
    }

    /* Please see man pages for details 
        
        
        
    

*/
    static s32 GetOrder(size_t size)
    {
        return GetNearestHigherOrder(DivUp<PAGE_SIZE>(size));
    }

    static const size_t PAGE_SIZE = PageSize;
    static const s32    MAX_ORDER = MaxOrder;

private:
    // Page entry.
    struct Page
    {
        Page* pNext;
    };

    // Construct a linked list for each memory block of the same size.
    class PageList
    {
    private:
        Page* m_pFirstPage;    // Start element of the page list
        Page* m_pLastPage;     // End element of the page list

    public:
        // Initializes page list.
        void Initialize()
        {
            m_pFirstPage = NULL;
            m_pLastPage = NULL;
        }

        /*
            
            
        
*/
        Page* PopFront()
        {
            NN_ASSERT(m_pFirstPage);

            // Gets the first page's contents from the page list.
            Page* pPage = m_pFirstPage;

            // Advances the page list by one.
            m_pFirstPage = pPage->pNext;
            pPage->pNext = NULL;

            // If the top and bottom of the page list are the same, you have reached the end of the page list.  
            // 
            // (Page list element is empty)
            if(pPage == m_pLastPage)
            {
                m_pLastPage = NULL;
            }

            return pPage;
        }

        /*
            
            
        
*/
        void PushBack(Page* pPage)
        {
            NN_ASSERT(!pPage->pNext);

            // Is page list empty?
            if(!m_pFirstPage)
            {
                // Add as the first element.
                m_pFirstPage = pPage;
            }
            else
            {
                // Add to the end of the list.
                m_pLastPage->pNext = pPage;
            }

            m_pLastPage = pPage;
        }

        /*
            
            
            
        

*/
        bool Remove(Page* pPage)
        {
            NN_NULL_TASSERT_(pPage);

            // Is page list empty?
            if(m_pFirstPage == NULL)
            {
                return false;
            }

            Page* pPrevPage = NULL;
            Page* page = m_pFirstPage;

            for(;;)
            {
                if(page == pPage)
                {
                    // If a page to be deleted was found
                    if(page == m_pFirstPage)
                    {
                        // The page to be deleted was at the top of the page list, so advance down the list by one and delete the element. 
                        //
                        m_pFirstPage = page->pNext;
                    }
                    else if(page == m_pLastPage)
                    {
                        // Page to delete was at the end of the page list, so set the last element back by one. 
                        // 
                        m_pLastPage = pPrevPage;
                        m_pLastPage->pNext = NULL;
                    }
                    else
                    {
                        // Reconnect the linked list for the pages between the beginning and the end. 
                        // Reconnect the linked list. 
                        pPrevPage->pNext = page->pNext;
                    }

                    page->pNext = NULL;

                    return true;
                }

                if(page->pNext == NULL)
                {
                    return false;
                }

                pPrevPage = page;
                page = page->pNext;
            }

            // not reached
        }

        /*
            
            
        
*/
        bool IsEmpty() const
        {
            if(m_pFirstPage)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    PageList m_FreeArea[MAX_ORDER];
    
    uptr    m_HeapStart;
    size_t  m_HeapSize;

    /*
        
        
        
        
    


*/
    Page* GetFreePage(s32 order)
    {
        for(s32 i = order; i < MAX_ORDER; i++)
        {
            // Search the page list that corresponds to the "order" (power) of 2
            // If no empty page was registered to that page, search for the page specified by the power of order+1, which is higher by one.
            // 
            if(!(m_FreeArea[i].IsEmpty())) 
            {
                // Free memory found.
                Page* pPage = m_FreeArea[i].PopFront();
                
                NN_NULL_TASSERT_(pPage);
                
                // When allocating memory that is too large for the request, break up the unused portion, and re-register it to the empty page list.
                //
                DivideBuddies(pPage, order, i);

                return pPage;
            }
        }
        
        NN_LOG_WARN("No free pages order %d\n", order);
        return NULL;
    }

    /*
        
        
        
        
    
*/
    void DivideBuddies(Page* pPage, s32 demandedOrder, s32 freeOrder)
    {
        for(s32 i = freeOrder; demandedOrder < i; i--)
        {
            Page* pDividedPage = &pPage[(1 << (i - 1))];;
            
            // Break up into small portions and register to the empty page list.
            // If a large, 16KB empty page is found for a 4KB request, the remaining 12KB (16KB - 4KB) that is not needed for allocation should be divided into two page lists (4KB and 8KB) and added to the free list. 
            //

            NN_LOG_DEBUG("divides buddy address 0x%08X and 0x%08X, order%d\n", GetAddressFromPage(*pPage), GetAddressFromPage(*pDividedPage), i);
            m_FreeArea[i - 1].PushBack(pDividedPage);
        }
    }

    /*
        
        
        
        
    

*/
    void JointBuddies(Page* pPage, s32 order)
    {
        // Maximum "order" - 1
        while(order < MAX_ORDER - 1)
        {
            // Request pages that become buddies.
            Page* pBuddyPage = GetBuddy(pPage, order);
            
            // Is there a buddy on the free list?
            if(m_FreeArea[order].Remove(pBuddyPage))
            {
                // If so, delete it (jointed) from the free list and attempt joint at (order + 1).

                // If the page was not aligned to (order + 1), then set address to Buddy.
                if(!IsAlignedToOrder(pPage, order + 1))
                {
                    pPage = pBuddyPage;
                }
                
                NN_LOG_DEBUG("joints buddy address 0x%08X and 0x%08X, order %d", GetAddressFromPage(*pPage), GetAddressFromPage(*GetBuddy(pPage, order)), order);
                
                
                order++;
            }
            else
            {
                // If not, joint failed. Add page to the free list.
                break;
            }
        }
        
        // Buddy was being used or jointed up to max order
        NN_LOG_DEBUG("adding a free page, address 0x%08X, order %d", GetAddressFromPage(*pPage), order );
        m_FreeArea[order].PushBack(pPage);
    }

    /* Please see man pages for details 
        
        
        
    

*/
    inline uptr GetAddressFromPage(const Page& page) const
    {
        return m_HeapStart + GetIndexFromPage(page) * PAGE_SIZE;
    }

    /* Please see man pages for details 
        
        
        
    

*/
    inline Page* GetPageFromAddress(uptr addr)
    {
        // TODO: Range check
        return &m_pPages[(addr - m_HeapStart) / PAGE_SIZE];
    }
    
    /*
        
        
        
    

*/
    inline s32 GetIndexFromPage(const Page& page) const
    {
        return &page - m_pPages;
    }

    inline Page* GetBuddy(Page* pPage, s32 order)
    {
        // If the page index is divisible by the above order, the next right is Buddy    
        if(IsAlignedToOrder(pPage, order + 1))
        {
            return pPage + GetNumPagesByOrder(order);
        }
        else // If not, the next left is Buddy
        {
            return pPage - GetNumPagesByOrder(order);
        }
    }
    
    /*
        
        
        
        
    

*/
    inline bool IsAlignedToOrder(Page* pPage, s32 order) const
    {
        return GetIndexFromPage(*pPage) % GetNumPagesByOrder(order) == 0; 
    }
    
    /*
        
        
        
    

*/
    inline int GetNumPagesByOrder(s32 order) const
    {
        return (1 << order);
    }

    static s32 GetNearestHigherOrder(size_t numPages)
    {
        for(int order = 0; order <= MAX_ORDER; order++)
        {
            if( numPages <= (1U << order) ) {
                return order;
            }
        }
        
        NN_LOG_WARN("No nearest higher order: numPages=%d, MAX_ORDER=%d", numPages, MAX_ORDER);
        return -1;
    }

    static s32 GetNearestLowerOrder(size_t numPages)
    {
        for(int order = 0; order <= MAX_ORDER; order++) 
        {
            if( numPages < (1 << order) ) {
                return order - 1;
            }
        }
        
        NN_LOG_WARN("No nearest lower order: numPages=%d, MAX_ORDER=%d", numPages, MAX_ORDER);
        return -1;
    }

    Page* m_pPages;
};

template <size_t PageSize, s32 MaxOrder, class LockPolicy>
class BuddyHeapTemplate : public BuddyHeapBase<PageSize, MaxOrder>, private LockPolicy::LockObject
{
private:
    typedef BuddyHeapBase<PageSize, MaxOrder> Base;
    typedef typename LockPolicy::LockObject LockObject;
    typedef typename LockPolicy::ScopedLock ScopedLock;

public:
    BuddyHeapTemplate() {}

    template <class MemoryBlockT>
    explicit BuddyHeapTemplate(const MemoryBlockT& block)
    {
        Initialize(block.GetAddress(), block.GetSize());
    }

    /*
        
        
        
    
*/
    void Initialize(uptr addr, size_t size)
    {
        uptr addrAligned = Base::RoundUp<Base::ALIGN>(addr);
        size -= addrAligned - addr;

        Base::Initialize(addrAligned, size / Base::PAGE_SIZE);
        LockObject::Initialize();
    }

    /*
        
    */
    void Finalize()
    {
        LockObject::Finalize();
        Base::Finalize();
    }

    /* Please see man pages for details 
        
        
        
    

*/
    void* AllocateByOrder(s32 order)
    {
        ScopedLock lk(*this);
        return Base::AllocateByOrder(order);
    }

    /* Please see man pages for details 
        
        
        
     
*/
    void Free(void* p, s32 order)
    {
        ScopedLock lk(*this);
        Base::Free(p, order);
    }

    class Allocator;
};

template <size_t PageSize, s32 MaxOrder, class LockPolicy>
class BuddyHeapTemplate<PageSize, MaxOrder, LockPolicy>::Allocator : public nn::fnd::IAllocator
{
private:
    typedef BuddyHeapTemplate<PageSize, MaxOrder, LockPolicy> BuddyHeap;
    static const size_t ALIGN = BuddyHeap::ALIGN;

public:
    Allocator(BuddyHeap& heap) : m_Heap(0) { Initialize(heap); }

    /* Please see man pages for details 
        
     */
    Allocator() : m_Heap(0) {}

    /* Please see man pages for details 
        
        
    
*/
    void Initialize(BuddyHeap& heap)
    {
        NN_TASSERT_(!this->m_Heap);
        this->m_Heap = &heap;
    }

    /* Please see man pages for details 
        
        
     
*/
    BuddyHeap* GetHeap() { return m_Heap; }

    /* Please see man pages for details 
        
        
     
*/
    const BuddyHeap* GetHeap() const { return m_Heap; }

    /* Please see man pages for details 
        
        
        
        
    

*/
    virtual void* Allocate(size_t size, s32 alignment = nn::fnd::HeapBase::DEFAULT_ALIGNMENT)
    {
        NN_ASSERT(alignment <= ALIGN);
        if (alignment > ALIGN)
        {
            return NULL;
        }

        // Stores excess memory in order to store the order at the start of the allocated memory.
        //
        s32 order = m_Heap->GetOrder(size + ALIGN);
        //NN_TLOG_("size: %d => order: %d\n", size, order);
        void* p = m_Heap->AllocateByOrder(order);
        if (!p)
        {
            return NULL;
        }
        NN_LOG_DEBUG("Alloc size %d, order %d\n", size + ALIGN, order);
        *reinterpret_cast<s32*>(p) = order;
        return reinterpret_cast<void*>(reinterpret_cast<uptr>(p) + ALIGN);
    }

    /* Please see man pages for details 
        
        
    
*/
    virtual void Free(void* p)
    {
        p = reinterpret_cast<void*>(reinterpret_cast<uptr>(p) - ALIGN);
        s32 order = *reinterpret_cast<s32*>(p);
        m_Heap->Free(p, order);
    }

private:
    BuddyHeap* m_Heap;     //
};

}}

#endif /* NN_FND_FND_BUDDYHEAP_H_ */
