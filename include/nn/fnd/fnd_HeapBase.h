/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_HeapBase.h

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

#ifndef NN_FND_FND_HEAPBASE_H_
#define NN_FND_FND_HEAPBASE_H_

#include <nn/types.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/fnd/fnd_LinkedList.h>

// Default alignment
#define NN_FND_HEAP_DEFAULT_ALIGNMENT 4

// Zero out memory when memory is allocated.
#define NN_FND_HEAP_OPTION_ZERO_CLEAR (1 << 0)

// Memory fill when heap is created, memory is allocated, or memory is freed.
#define NN_FND_HEAP_OPTION_DEBUG_FILL (1 << 1)

//  If this bit stands, output error
#define NN_FND_HEAP_OPTION_ERROR_PRINT (1 << 0)

#ifdef __cplusplus

namespace nn { namespace fnd {

/* Please see man pages for details 
    
*/
enum HeapFillType
{
    HEAP_FILL_TYPE_NOUSE,    //
    HEAP_FILL_TYPE_ALLOC,    //
    HEAP_FILL_TYPE_FREE,     //
    
    HEAP_FILL_TYPE_MAX
};

enum HeapInfoPlacement
{
    HEAP_INFOPLACEMENT_HEAD,
    HEAP_INFOPLACEMENT_TAIL
};

/* Please see man pages for details 
	
*/
enum HeapAdjustMode
{
    HEAP_ADJUST_TAIL = 1,    //
    HEAP_ADJUST_HEAD = -1    //
};

/* Please see man pages for details 
    

    
    
              
 */
class HeapBase : public IntrusiveLinkedList<HeapBase>::Item
{
public:

    static const s32 DEFAULT_ALIGNMENT = 4;
    static const bit32 OPTION_ERROR_PRINT = NN_FND_HEAP_OPTION_ERROR_PRINT;

	/* Please see man pages for details 
	    

		
		
	*/
    static void SetFillValue(HeapFillType type, bit32 val);

	/* Please see man pages for details 
	    

		
	*/
    static bit32 GetFillValue(HeapFillType type);

    /* Please see man pages for details 
        
    */
    virtual ~HeapBase() = 0;

    /* Please see man pages for details 
        
    */
    virtual void FreeV(void*) = 0;

    /* Please see man pages for details 
        
    */
    virtual void* GetStartAddress() const = 0;
    
    /* Please see man pages for details 
        
    */
    virtual size_t GetTotalSize() const = 0;
    
    /* Please see man pages for details 
        
    */
    virtual void Dump() const = 0;

    /* Please see man pages for details 
        

        

        
    */
    virtual bool HasAddress(const void* addr) const = 0;

    /* Please see man pages for details 
        

        
    */
    HeapBase* GetParent() { return m_Parent; }

    /* Please see man pages for details 
        

        
    */
    HeapBase* GetRoot();

    /* Please see man pages for details 
        

        

        
        
            
            
            
    */
    HeapBase* FindHeap(void* addr);

    /* Please see man pages for details 
        

                

        
                            
                            
    */
    void Destroy(HeapBase* child);

protected:

    HeapBase(bit32 option = 0) : m_Parent(0), m_Option(0) { Initialize(option); }
    
    void Initialize(bit32 option) { m_Option = option; }

    /* Please see man pages for details 
        

        

                
    */
    void SetParent(HeapBase* parent);

    static uptr RoundDown(uptr addr, s32 alignment)
    {
        return (addr / alignment) * alignment;
    }

    static uptr RoundUp(uptr addr, s32 alignment)
    {
        return RoundDown(addr + alignment - 1, alignment);
    }

    void FillMemoryZero(uptr addr, size_t size)
    {
        if(m_Option & NN_FND_HEAP_OPTION_ZERO_CLEAR)
        {
            FillMemory32(addr, addr + size, 0);
        }
    }

#ifdef NN_BUILD_VERBOSE
    void DebugFillMemory(uptr addr, size_t size, HeapFillType type)
    {
        // TODO: If there is a faster function, replace with it
        if(this->m_Option & NN_FND_HEAP_OPTION_DEBUG_FILL)
        {
            FillMemory32(addr, addr + size, GetFillValue(type));
        }
    }
#else
    inline void DebugFillMemory(uptr, size_t, HeapFillType) {}
#endif

private:
    HeapBase* m_Parent;

    IntrusiveLinkedList<HeapBase> m_Children;
    
    bit32 m_Option;

    static void FillMemory(uptr addr, uptr end, bit8 value);
    static void FillMemory32(uptr addr, uptr end, bit32 value);
};

}}

#endif

#endif
