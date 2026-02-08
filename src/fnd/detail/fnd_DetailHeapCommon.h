/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailHeapCommon.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_DETAIL_FND_DETAIL_HEAPCOMMON_H_
#define NN_FND_DETAIL_FND_DETAIL_HEAPCOMMON_H_

#include <nn/types.h>
#include <nn/fnd/detail/fnd_DetailHeapHead.h>
#include "./fnd_DetailList.h"

#ifdef __cplusplus

namespace nn { namespace fnd { namespace detail {
/* Please see man pages for details 
  
  
*/
/* Please see man pages for details 
  
  
*/
//
/* ========================================================================
    Macro Constants
   ======================================================================== */

// Invalid heap handle
#define NN_OS_HEAP_INVALID_HANDLE     NULL

// Default alignment size when memory is allocated from heap
#define NN_OS_HEAP_DEFAULT_ALIGNMENT    4

#define NNSI_CREATE_HEAP_SIGNATURE(a,b,c,d)  ( ((a & 0xFF) << 24) | ((b & 0xFF) << 16) | ((c & 0xFF) << 8) | ((d & 0xFF) << 0) )

// Signature of expanded heap
#define NNSI_EXPHEAP_SIGNATURE    NNSI_CREATE_HEAP_SIGNATURE('E','X','P','H')

// Signature of frame heap
#define NNSI_FRMHEAP_SIGNATURE    NNSI_CREATE_HEAP_SIGNATURE('F','R','M','H')

// Signature of unit heap
#define NNSI_UNTHEAP_SIGNATURE    NNSI_CREATE_HEAP_SIGNATURE('U','N','T','H')


/* ------------------------------------------------------------------------
    Fill-related
   ------------------------------------------------------------------------ */

// Zero out memory when memory is allocated.
#define NN_OS_HEAP_OPT_0_CLEAR        (1 <<0)

// Memory filled when heap is created, memory is allocated, or memory is freed.
#define NN_OS_HEAP_OPT_DEBUG_FILL     (1 <<1)


/* ------------------------------------------------------------------------
    Heap check related
   ------------------------------------------------------------------------ */

//  If this bit stands, output error
#define NN_OS_HEAP_ERROR_PRINT        (1 <<0)


/* ========================================================================
    enum constant
   ======================================================================== */

enum {
    NN_OS_HEAP_FILL_NOUSE,    // When debug fill is not used
    NN_OS_HEAP_FILL_ALLOC,    // When debug fill is allocated
    NN_OS_HEAP_FILL_FREE,     // When debug fill is freed

    NN_OS_HEAP_FILL_MAX
};


/* =======================================================================
    Type Definitions
   ======================================================================== */

/* Please see man pages for details 
    
*/
typedef ExpHeapImpl NNSiFndHeapHead;
typedef NNSiFndHeapHead* Heap;   // Type to represent heap handle
typedef NNSiFndHeapHead const * ConstHeap;


/*---------------------------------------------------------------------------*
  Name:         MemGetHeapTotalSize
  Description:  Gets the memory size allocated to the heap (including that of the header).
                
  Arguments:    heap    Heap handle
  Returns:      Returns the memory size allocated to the heap (including that of the header).
                
 *---------------------------------------------------------------------------


*/
static inline s32
GetHeapTotalSize(ConstHeap heap)
{
    return ((s32)(heap->heapEnd) - (s32)(heap->heapStart));
}

/* ========================================================================
    Macro Functions
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         GetHeapStartAddress
  Description:  Gets start address of memory area used by heap
  Arguments:    heap:  Heap handle
  Returns:      Return start address of memory area used by heap
 *---------------------------------------------------------------------------


*/
#define             GetHeapStartAddress(heap) \
                        ((void*)(((nn::fnd::detail::NNSiFndHeapHead*)(heap))->heapStart))

/*---------------------------------------------------------------------------*
  Name:         GetHeapEndAddress
  Description:  Gets end address +1 of memory region used by heap.
  Arguments:    heap:  Heap handle
  Returns:      Return end address +1 of memory area used by heap
 *---------------------------------------------------------------------------


*/
#define             GetHeapEndAddress(heap) \
                        (((nn::fnd::detail::NNSiFndHeapHead*)(heap))->heapEnd)

/* =======================================================================
    Function Prototypes
   ======================================================================== */

Heap    FindContainHeap(
                        const void* memBlock);

#if defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
    #define             DumpHeap(heap)				((void)0)
#else
	void                DumpHeap(
	                        Heap heap);
#endif

#ifndef NN_BUILD_VERBOSE
    #define             SetFillValForHeap(type, val) (0)
#else
    u32                 SetFillValForHeap(
                            int     type,
                            u32     val);
#endif

#ifndef NN_BUILD_VERBOSE
    #define             GetFillValForHeap(type)      (0)
#else
    u32                 GetFillValForHeap(
                            int     type);
#endif
//

/*  

*/
/*  

*/


}}} // namespace nn::os

#endif // __cplusplus

/* NN_OS_HEAPCOMMON_H_ */
#endif /* NN_OS_OS_HEAPCOMMON_H_ */
