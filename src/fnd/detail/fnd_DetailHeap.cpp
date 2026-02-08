/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailHeap.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46866 $
 *---------------------------------------------------------------------------*/

#include <stdlib.h>
#include <nn/config.h>
#include <nn/os/os_Result.h>
#include "fnd_DetailHeap.h"
#include "fnd_DetailHeapCommonImpl.h"


/* ========================================================================
    Macro Constants
   ======================================================================== */

#if defined(NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK) && defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
#define HEAP_DISABLE_DEBUG_PRINT
#endif

#ifdef MULTI_CHAR_LITERAL
// signature for free memory block
#define MBLOCK_FREE_SIGNATURE   ('FR')

// signature for the memory block being used
#define MBLOCK_USED_SIGNATURE   ('UD')
#else
// signature for free memory block
#define MBLOCK_FREE_SIGNATURE   0x00004652  // "FR"

// signature for the memory block being used
#define MBLOCK_USED_SIGNATURE   0x00005544  // "UD"

#endif

// maximum value for the group ID
#define MAX_GROUPID             0xff

// default value for the group ID
#define DEFAULT_GROUPID         0

// Minimum value for alignment
#define MIN_ALIGNMENT           4

// Maximum value for alignment
#define MAX_ALIGNMENT           128

// default memory allocation mode
#define DEFAULT_ALLOC_MODE      NN_OS_EXPHEAP_ALLOC_MODE_FIRST

// minimum size to register as a free block (size not including header)
#define MIN_FREE_BLOCK_SIZE     4
// #define MIN_FREE_BLOCK_SIZE 16


namespace nn{ namespace fnd { namespace detail {

/* ========================================================================
    Structure definitions
   ======================================================================== */
typedef struct NNSiMemRegion NNSiMemRegion;

struct NNSiMemRegion
{
    void*       start;
    void*       end;
};


/* ========================================================================
    Macro Functions
   ======================================================================== */

#define HEAP_WARNING NN_TASSERTMSG_


/* ========================================================================
    Static functions
   ======================================================================== */

/* ------------------------------------------------------------------------
    Pointer operations
   ------------------------------------------------------------------------ */
/*
static NN_OS_INLINE void*
MaxPtr(void* a, void* b)
{
    return NNSiGetUIntPtr(a) > NNSiGetUIntPtr(b) ? a: b;
}
*/
#ifndef HEAP_DISABLE_DEBUG_PRINT
static inline bool
IsValidHeapHandle(ConstHeap handle)
{
    if (handle == NN_OS_HEAP_INVALID_HANDLE)
    {
        return false;
    }

    {
        NNSiFndHeapHead const * pHeapHd = handle;
        return pHeapHd->signature == NNSI_EXPHEAP_SIGNATURE;
    }
}
#endif


/*------------------------------------------------------------------------
  Create MemoryRange using void* and size.
------------------------------------------------------------------------*/
static inline MemoryRange MakeMemoryRange(void* addr, size_t size)
{
    return MemoryRange(reinterpret_cast<uptr>(addr),reinterpret_cast<uptr>(addr)+size);
}



/*---------------------------------------------------------------------------*
  Name:         GetHeapHeadPtrFromHeapHead

  Description:  Gets the pointer to the expanded heap header from the pointer to the heap header.

  Arguments:    pHHead:  Pointer to the heap header

  Returns:      Returns the pointer to the expanded heap header.
 *---------------------------------------------------------------------------*/
static inline NNSiFndExpHeapHead *
GetHeapHeadPtrFromHeapHead(NNSiFndHeapHead * pHHead)
{
    return &pHHead->nnsiFndExpHeapHead;
}

static inline NNSiFndExpHeapHead const*
GetHeapHeadPtrFromHeapHead(NNSiFndHeapHead const* pHHead)
{
    return &pHHead->nnsiFndExpHeapHead;
}

/*---------------------------------------------------------------------------*
  Name:         GetHeapHeadPtrFromHeapHead

  Description:  Gets the pointer to the heap header from the pointer to the expanded heap header.

  Arguments:    pEHHead:  Pointer to the expanded heap header.

  Returns:      Returns the pointer to the heap header.
 *---------------------------------------------------------------------------*/
static inline NNSiFndHeapHead*
GetHeapHeadPtrFromHeapHead(NNSiFndExpHeapHead* pEHHead)
{
    return reinterpret_cast<NNSiFndHeapHead*>(SubU32ToPtr(pEHHead, sizeof(NNSiFndHeapHead)-sizeof(NNSiFndExpHeapHead)));
}

/*---------------------------------------------------------------------------*
  Name:         GetHeapHeadPtrFromHandle

  Description:  Gets the pointer to the expanded heap header from the expanded heap handle.

  Arguments:    heap:  expanded heap handle

  Returns:      Returns the pointer to the expanded heap header.
 *---------------------------------------------------------------------------*/
static inline NNSiFndExpHeapHead *
GetHeapHeadPtrFromHandle(Heap heap)
{
    return GetHeapHeadPtrFromHeapHead(heap);
}

static inline NNSiFndExpHeapHead const*
GetHeapHeadPtrFromHandle(ConstHeap heap)
{
    return GetHeapHeadPtrFromHeapHead(heap);
}

/*---------------------------------------------------------------------------*
  Name:         GetMemPtrForMBlock

  Description:  Gets the pointer to the memory block from the pointer to the NNSiFndExpHeapMBlockHead structure.
                

  Arguments:    pMBlkHd:  pointer to the NNSiFndExpHeapMBlockHead structure

  Returns:      Returns the pointer to the memory block.
 *---------------------------------------------------------------------------*/
static inline void*
GetMemPtrForMBlock(NNSiFndExpHeapMBlockHead* pMBlkHd)
{
    return AddU32ToPtr(pMBlkHd, sizeof(NNSiFndExpHeapMBlockHead));
}

#if ! defined(NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK) && ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
static inline const void*
GetMemCPtrForMBlock(const NNSiFndExpHeapMBlockHead* pMBlkHd)
{
    return AddU32ToCPtr(pMBlkHd, sizeof(NNSiFndExpHeapMBlockHead));
}
#endif

/*---------------------------------------------------------------------------*
  Name:         GetMBlockHeadPtr

  Description:  Gets the pointer to the NNSiFndExpHeapMBlockHead structure from the pointer to the memory block.
                
                Gets the pointer to the memory block.

  Arguments:    memBlock:  pointer to the memory block

  Returns:      Returns the pointer to the NNSiFndExpHeapMBlockHead structure.
 *---------------------------------------------------------------------------*/
static inline NNSiFndExpHeapMBlockHead*
GetMBlockHeadPtr(void* memBlock)
{
    return reinterpret_cast<NNSiFndExpHeapMBlockHead*>(SubU32ToPtr(memBlock, sizeof(NNSiFndExpHeapMBlockHead)));
}

static inline const NNSiFndExpHeapMBlockHead*
GetMBlockHeadCPtr(const void* memBlock)
{
    return reinterpret_cast<const NNSiFndExpHeapMBlockHead*>(SubU32ToCPtr(memBlock, sizeof(NNSiFndExpHeapMBlockHead)));
}

static inline void*
GetMBlockEndAddr(NNSiFndExpHeapMBlockHead* pMBHead)
{
    return AddU32ToPtr(GetMemPtrForMBlock(pMBHead), pMBHead->blockSize);
}

/* ------------------------------------------------------------------------
    NNSiFndExpHeapMBlockHead structure access functions
   ------------------------------------------------------------------------ */

/*---------------------------------------------------------------------------*
  Name:         GetAlignmentForMBlock

  Description:  Gets the alignment value for the NNSiFndExpHeapMBlockHead structure.

  Arguments:    pMBlkHd:  pointer to the NNSiFndExpHeapMBlockHead structure

  Returns:      Returns the alignment value for the NNSiFndExpHeapMBlockHead structure.
 *---------------------------------------------------------------------------*/
static inline u16
GetAlignmentForMBlock(const NNSiFndExpHeapMBlockHead* pMBlkHd)
{
    return (u16)NNSi_FndGetBitValue(pMBlkHd->attribute, 8, 7);
}

/*---------------------------------------------------------------------------*
  Name:         SetAlignmentForMBlock

  Description:  Sets the alignment value for the NNSiFndExpHeapMBlockHead structure.

  Arguments:    pMBlkHd:    pointer to the NNSiFndExpHeapMBlockHead structure
                alignment:  alignment value to be set

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
SetAlignmentForMBlock(
    NNSiFndExpHeapMBlockHead*   pMBlkHd,
    u16                         alignment
)
{
    NNSi_FndSetBitValue(pMBlkHd->attribute, 8, 7, alignment);
}

static inline u16
GetGroupIDForMBlock(const NNSiFndExpHeapMBlockHead* pMBHead)
{
    return (u16)NNSi_FndGetBitValue(pMBHead->attribute, 0, 8);
}

static inline void
SetGroupIDForMBlock(
    NNSiFndExpHeapMBlockHead*   pMBHead,
    u16                         id
)
{
    NNSi_FndSetBitValue(pMBHead->attribute, 0, 8, id);
}

static inline u16
GetAllocDirForMBlock(const NNSiFndExpHeapMBlockHead* pMBHead)
{
    return (u16)NNSi_FndGetBitValue(pMBHead->attribute, 15, 1);
}

static inline void
SetAllocDirForMBlock(
    NNSiFndExpHeapMBlockHead*   pMBHead,
    u16                         mode
)
{
    NNSi_FndSetBitValue(pMBHead->attribute, 15, 1, mode);
}


/* ------------------------------------------------------------------------
    NNSiFndExpHeapHead structure access functions
   ------------------------------------------------------------------------ */

/*---------------------------------------------------------------------------*
  Name:         GetAllocMode

  Description:  Gets the memory allocation mode for the expanded heap.

  Arguments:    pEHHead:  Pointer to the expanded heap header.

  Returns:      Returns the memory allocation mode for the expanded heap.
 *---------------------------------------------------------------------------*/
static inline u16
GetAllocMode(NNSiFndExpHeapHead* pEHHead)
{
    return (u16)NNSi_FndGetBitValue(pEHHead->feature, 0, 1);
}

/*---------------------------------------------------------------------------*
  Name:         SetAllocMode

  Description:  Sets the memory allocation mode for the expanded heap.

  Arguments:    pEHHead:  Pointer to the expanded heap header.
                mode:     Memory allocation mode.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
SetAllocMode(
    NNSiFndExpHeapHead* pEHHead,
    u16                 mode
)
{
    NNSi_FndSetBitValue(pEHHead->feature, 0, 1, mode);
}

static void
GetRegionOfMBlock(
    NNSiMemRegion*              region,
    NNSiFndExpHeapMBlockHead*   block
)
{
    region->start = SubU32ToPtr(block, GetAlignmentForMBlock(block));
    region->end   = GetMBlockEndAddr(block);
}


/* ------------------------------------------------------------------------
    Memory block list operations
   ------------------------------------------------------------------------ */

static NNSiFndExpHeapMBlockHead*
RemoveMBlock(
    NNSiFndExpMBlockList*       list,
    NNSiFndExpHeapMBlockHead*   block
)
{
    NNSiFndExpHeapMBlockHead *const prev = block->pMBHeadPrev;
    NNSiFndExpHeapMBlockHead *const next = block->pMBHeadNext;

    // previous reference link
    if (prev)
    {
        prev->pMBHeadNext = next;
    }
    else
    {
        list->head = next;
    }

    // next reference link
    if (next)
    {
        next->pMBHeadPrev = prev;
    }
    else
    {
        list->tail = prev;
    }

    return prev;
}

static NNSiFndExpHeapMBlockHead*
InsertMBlock(
    NNSiFndExpMBlockList*       list,
    NNSiFndExpHeapMBlockHead*   target,
    NNSiFndExpHeapMBlockHead*   prev
)
{
    NNSiFndExpHeapMBlockHead* next;

    // previous reference link
    target->pMBHeadPrev = prev;
    if (prev)
    {
        next = prev->pMBHeadNext;
        prev->pMBHeadNext = target;
    }
    else
    {
        next = list->head;
        list->head = target;
    }

    // next reference link
    target->pMBHeadNext = next;
    if (next)
    {
        next->pMBHeadPrev = target;
    }
    else
    {
        list->tail = target;
    }

    return target;
}

/*---------------------------------------------------------------------------*
  Name:         AppendMBlock

  Description:  Adds a memory block to the end of the list.

  Arguments:    link:   List to be added to
                block:  Memory block to add

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
AppendMBlock(
    NNSiFndExpMBlockList*       list,
    NNSiFndExpHeapMBlockHead*   block
)
{
    (void)InsertMBlock(list, block, list->tail);
}

/*---------------------------------------------------------------------------*
  Name:         InitMBlock

  Description:  Initializes a memory block.

  Arguments:    pRegion:    pointer to the structure representing the region used for the memory block
                signature:  memory block signature

  Returns:      Returns the pointer to the initialized memory block.
 *---------------------------------------------------------------------------*/
static NNSiFndExpHeapMBlockHead*
InitMBlock(
    const NNSiMemRegion*    pRegion,
    u16                     signature
)
{
    NNSiFndExpHeapMBlockHead* block = reinterpret_cast<NNSiFndExpHeapMBlockHead*>(pRegion->start);

    block->signature = signature;
    block->attribute = 0;
    block->blockSize = GetOffsetFromPtr(GetMemPtrForMBlock(block), pRegion->end);
    block->pMBHeadPrev = NULL;
    block->pMBHeadNext = NULL;

    return block;
}

/*---------------------------------------------------------------------------*
  Name:         InitFreeMBlock

  Description:  Initializes the memory block for use as a free block.

  Arguments:    pRegion:    pointer to the structure representing the region used for the memory block

  Returns:      Returns the pointer to the initialized memory block.
 *---------------------------------------------------------------------------*/
static inline NNSiFndExpHeapMBlockHead*
InitFreeMBlock(
    const NNSiMemRegion*    pRegion
)
{
    return InitMBlock(pRegion, MBLOCK_FREE_SIGNATURE);
}

/*---------------------------------------------------------------------------*
  Name:         InitHeap

  Description:  Initializes the expanded heap.

  Arguments:    pHeapHead:     Pointer to the heap header.
                startAddress:  memory start address for the expanded heap
                endAddress:    terminal address for the memory for the expanded heap incremented by one
                optFlag:       Option flag

  Returns:      Returns the pointer to the heap header.
 *---------------------------------------------------------------------------*/
static NNSiFndHeapHead*
InitHeap(
    NNSiFndHeapHead* pHeapHead,
    void*   startAddress,
    void*   endAddress,
    u16     optFlag
)
{
    NNSiFndHeapHead* pHeapHd = pHeapHead;//reinterpret_cast<NNSiFndHeapHead*>(startAddress);
    NNSiFndExpHeapHead* pExpHeapHd = GetHeapHeadPtrFromHeapHead(pHeapHd);

    NNSi_FndInitHeapHead(           // common heap initializations
        pHeapHd,
        NNSI_EXPHEAP_SIGNATURE,
        startAddress,    // heapStart
        endAddress,                                             // heapEnd
        optFlag);

    pExpHeapHd->groupID = DEFAULT_GROUPID;      // Group ID
    pExpHeapHd->feature = 0;
    SetAllocMode(pExpHeapHd, DEFAULT_ALLOC_MODE);

    // create a free block
    {
        NNSiFndExpHeapMBlockHead* pMBHead;
        NNSiMemRegion region;
        region.start = pHeapHd->heapStart;
        region.end   = pHeapHd->heapEnd;
        pMBHead = InitFreeMBlock(&region);

        // block list
        pExpHeapHd->mbFreeList.head = pMBHead;
        pExpHeapHd->mbFreeList.tail = pMBHead;
        pExpHeapHd->mbUsedList.head = NULL;
        pExpHeapHd->mbUsedList.tail = NULL;

        return pHeapHd;
    }
}

/*---------------------------------------------------------------------------*
  Name:         AllocUsedBlockFromFreeBlock

  Description:  Allocates a new memory block from free blocks.

  Arguments:    pEHHead:      Pointer to the expanded heap header.
                pMBHeadFree:  Pointer to the free block header.
                mblock:       Address for the memory block to be allocated.
                size:         Size of the memory block to be allocated.
                direction:    Allocation direction.

  Returns:      Returns a pointer to the start of the allocated memory block.
 *---------------------------------------------------------------------------*/
static void*
AllocUsedBlockFromFreeBlock(
    NNSiFndExpHeapHead*         pEHHead,
    NNSiFndExpHeapMBlockHead*   pMBHeadFree,
    void*                       mblock,
    u32                         size,
    u16                         direction
)
{
    NNSiMemRegion freeRgnT;
    NNSiMemRegion freeRgnB;
    NNSiFndExpHeapMBlockHead* pMBHeadFreePrev;

    GetRegionOfMBlock(&freeRgnT, pMBHeadFree);
    freeRgnB.end   = freeRgnT.end;
    freeRgnB.start = AddU32ToPtr(mblock, size);
    freeRgnT.end   = SubU32ToPtr(mblock, sizeof(NNSiFndExpHeapMBlockHead));

    pMBHeadFreePrev = RemoveMBlock(&pEHHead->mbFreeList, pMBHeadFree);  // delete the free block for the time being

    // when there is no space for creating a free block
    if ((GetOffsetFromPtr(freeRgnT.start, freeRgnT.end) < sizeof(NNSiFndExpHeapMBlockHead) + MIN_FREE_BLOCK_SIZE) ||
       (direction == NN_OS_EXPHEAP_ALLOC_DIR_FRONT && !pEHHead->reuse))
    {
        freeRgnT.end = freeRgnT.start;  // include the alignment value for the block being used
    }
    else
    {
        pMBHeadFreePrev = InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgnT), pMBHeadFreePrev);
    }

    // when there is no space for creating a free block
    if ((GetOffsetFromPtr(freeRgnB.start, freeRgnB.end) < sizeof(NNSiFndExpHeapMBlockHead) + MIN_FREE_BLOCK_SIZE) ||
       (direction == NN_OS_EXPHEAP_ALLOC_DIR_REAR && !pEHHead->reuse))
    {
        freeRgnB.start= freeRgnB.end;   // include the block being used
    }
    else
    {
        (void)InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgnB), pMBHeadFreePrev);
    }

    // fill the memory for debugging
    FillAllocMemory(GetHeapHeadPtrFromHeapHead(pEHHead), freeRgnT.end, GetOffsetFromPtr(freeRgnT.end, freeRgnB.start));

    // create a new block
    {
        NNSiFndExpHeapMBlockHead* pMBHeadNewUsed;
        NNSiMemRegion region;

        region.start = SubU32ToPtr(mblock, sizeof(NNSiFndExpHeapMBlockHead));
        region.end   = freeRgnB.start;

        pMBHeadNewUsed = InitMBlock(&region, MBLOCK_USED_SIGNATURE);
        SetAllocDirForMBlock(pMBHeadNewUsed, direction);
        SetAlignmentForMBlock(pMBHeadNewUsed, (u16)GetOffsetFromPtr(freeRgnT.end, pMBHeadNewUsed));
        SetGroupIDForMBlock(pMBHeadNewUsed, pEHHead->groupID);
        AppendMBlock(&pEHHead->mbUsedList, pMBHeadNewUsed);
    }

    return mblock;
}

/*---------------------------------------------------------------------------*
  Name:         AllocFromHead

  Description:  Allocates the memory block from the start of the heap.

  Arguments:    pHeapHd:    Pointer to the heap header
                size:       Size of the memory block to be allocated.
                alignment:  alignment value

  Returns:      Returns a pointer to the allocated memory block if the allocation is successful.
                
                If the operation fails, NULL is returned.
 *---------------------------------------------------------------------------*/
static void*
AllocFromHead(
    NNSiFndHeapHead*    pHeapHd,
    u32                 size,
    int                 alignment
)
{
    NNSiFndExpHeapHead* pExpHeapHd = GetHeapHeadPtrFromHeapHead(pHeapHd);

    // Allocate the first one found?
    const bool bAllocFirst = GetAllocMode(pExpHeapHd) == NN_OS_EXPHEAP_ALLOC_MODE_FIRST;

    NNSiFndExpHeapMBlockHead* pMBlkHd      = NULL;
    NNSiFndExpHeapMBlockHead* pMBlkHdFound = NULL;
    u32 foundSize = 0xffffffff;
    void* foundMBlock = NULL;

    // search for free block
    for (pMBlkHd = pExpHeapHd->mbFreeList.head; pMBlkHd; pMBlkHd = pMBlkHd->pMBHeadNext)
    {
        void *const mblock    = GetMemPtrForMBlock(pMBlkHd);
        void *const reqMBlock = NNSi_FndRoundUpPtr(mblock, alignment);
        const u32 offset      = GetOffsetFromPtr(mblock, reqMBlock);    // generated offset

        if ( pMBlkHd->blockSize >= size + offset
         &&  foundSize > pMBlkHd->blockSize )
        {
            pMBlkHdFound  = pMBlkHd;
            foundSize     = pMBlkHd->blockSize;
            foundMBlock   = reqMBlock;

            if (bAllocFirst || foundSize == size)
            {
                break;
            }
        }
    }

    if (! pMBlkHdFound) // no blocks matching the conditions were found
    {
        return NULL;
    }

    return AllocUsedBlockFromFreeBlock( // allocate a region from the free block that was found
            pExpHeapHd,
            pMBlkHdFound,
            foundMBlock,
            size,
            NN_OS_EXPHEAP_ALLOC_DIR_FRONT);
}

/*---------------------------------------------------------------------------*
  Name:         AllocFromTail

  Description:  Allocates a memory block from the end of the heap.

  Arguments:    pHeapHd:    Pointer to the heap header
                size:       Size of the memory block to be allocated.
                alignment:  alignment value

  Returns:      Returns a pointer to the allocated memory block if the allocation is successful.
                
                If the operation fails, NULL is returned.
 *---------------------------------------------------------------------------*/
static void*
AllocFromTail(
    NNSiFndHeapHead*    pHeapHd,
    u32                 size,
    int                 alignment
)
{
    NNSiFndExpHeapHead* pExpHeapHd = GetHeapHeadPtrFromHeapHead(pHeapHd);

    // Allocate the first one found?
    const bool bAllocFirst = GetAllocMode(pExpHeapHd) == NN_OS_EXPHEAP_ALLOC_MODE_FIRST;

    NNSiFndExpHeapMBlockHead* pMBlkHd      = NULL;
    NNSiFndExpHeapMBlockHead* pMBlkHdFound = NULL;
    u32 foundSize = 0xffffffff;
    void* foundMBlock = NULL;

    // search for free block
    for (pMBlkHd = pExpHeapHd->mbFreeList.tail; pMBlkHd; pMBlkHd = pMBlkHd->pMBHeadPrev)
    {
        void *const mblock    = GetMemPtrForMBlock(pMBlkHd);
        void *const mblockEnd = AddU32ToPtr(mblock, pMBlkHd->blockSize);
        void *const reqMBlock = NNSi_FndRoundDownPtr(SubU32ToPtr(mblockEnd, size), alignment);  // aligned address

        if ( ComparePtr(reqMBlock, mblock) >= 0
         &&  foundSize > pMBlkHd->blockSize )
        {
            pMBlkHdFound = pMBlkHd;
            foundSize    = pMBlkHd->blockSize;
            foundMBlock  = reqMBlock;

            if (bAllocFirst || foundSize == size)
            {
                break;
            }
        }
    }

    if (! pMBlkHdFound) // no blocks matching the conditions were found
    {
        return NULL;
    }

    return AllocUsedBlockFromFreeBlock( // allocate a region from the free block that was found
            pExpHeapHd,
            pMBlkHdFound,
            foundMBlock,
            size,
            NN_OS_EXPHEAP_ALLOC_DIR_REAR);
}

/*---------------------------------------------------------------------------*
  Name:         RecycleRegion

  Description:  Incorporates an empty region into a free memory block.
                If it is adjacent to a free block, the free block is expanded.
                If it is not adjacent to a free block, and if the size is not close to the size of a free block, the empty region takes the alignment value of a used block adjacent to the end of the empty region.
                
                If there is no used block adjacent to the end of the empty region, the function fails.

  Arguments:    pEHHead:  Pointer to the expanded heap header.
                pRegion:  pointer to the empty region

  Returns:      Returns TRUE if the function is successful.
                Returns FALSE if it fails.
 *---------------------------------------------------------------------------*/
static bool
RecycleRegion(
    NNSiFndExpHeapHead*     pEHHead,
    const NNSiMemRegion*    pRegion
)
{
    NNSiFndExpHeapMBlockHead* pBlkPrFree  = NULL;   // immediately preceding free block
    NNSiMemRegion freeRgn = *pRegion;

    // search for free area next to the specified one
    {
        NNSiFndExpHeapMBlockHead* pBlk;

        for (pBlk = pEHHead->mbFreeList.head; pBlk; pBlk = pBlk->pMBHeadNext)
        {
            if (pBlk < pRegion->start)
            {
                pBlkPrFree = pBlk;
                continue;
            }

            if (pBlk == pRegion->end)   // Is the block adjacent to the end?
            {
                // combine the available regions
                freeRgn.end = GetMBlockEndAddr(pBlk);
                (void)RemoveMBlock(&pEHHead->mbFreeList, pBlk);

                // pad the header with NoUse
                FillNoUseMemory(GetHeapHeadPtrFromHeapHead(pEHHead), pBlk, sizeof(NNSiFndExpHeapMBlockHead));
            }
            break;
        }
    }

    // Is the immediately preceding free block adjacent to the front?
    if (pBlkPrFree && GetMBlockEndAddr(pBlkPrFree) == pRegion->start)
    {
        // combine the available regions
        freeRgn.start = pBlkPrFree;
        pBlkPrFree = RemoveMBlock(&pEHHead->mbFreeList, pBlkPrFree);
    }

    if (GetOffsetFromPtr(freeRgn.start, freeRgn.end) < sizeof(NNSiFndExpHeapMBlockHead)) // size is not suitable for use as a block
    {
        return false;   // Try to reduce the size using ResizeForMBlockHeap()
                        // And arrive here if there are not free blocks at the end of the heap
    }

    // fill the memory for debugging
    FillFreeMemory(GetHeapHeadPtrFromHeapHead(pEHHead), pRegion->start, GetOffsetFromPtr(pRegion->start, pRegion->end));

    (void)InsertMBlock(&pEHHead->mbFreeList,
        InitFreeMBlock(&freeRgn),   // create the free block
        pBlkPrFree);

    return true;
}

/*---------------------------------------------------------------------------*
  Name:         CheckMBlock

  Description:  Checks whether the header contents for the memory block are valid.

  Arguments:    pMBHead:    pointer to the header for the memory block to be checked
                pHeapHd:    pointer to the expanded heap header
                signature:  memory block signature
                heapType:   memory block type (used or free)
                flag:       Flag.

  Returns:      Returns true if the header contents for the memory block are valid, and returns false otherwise.
                
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static bool
    CheckMBlock(
        NNSiFndExpHeapMBlockHead const* pMBHead,
        NNSiFndHeapHead const*                pHeapHd,
        u16                             signature,
        const char*                     heapType,
        u32                             flag
    )
    {
        const bool bPrint = 0 != (flag & NN_OS_HEAP_ERROR_PRINT);
        const void *const memBlock = GetMemCPtrForMBlock(pMBHead);
        NN_UNUSED_VAR(heapType);

        if (pHeapHd)
        {
            if ( NNSiGetUIntPtr(pMBHead) < NNSiGetUIntPtr(pHeapHd->heapStart)
              || NNSiGetUIntPtr(memBlock) > NNSiGetUIntPtr(pHeapHd->heapEnd)
            )
            {
                HEAP_WARNING(bPrint, "[Fnd Exp Heap] Bad %s memory block address. - address %08X, heap area [%08X - %08X)\n",
                    heapType, memBlock, pHeapHd->heapStart, pHeapHd->heapEnd);
                return false;
            }
        }

        if (pMBHead->signature != signature)    // Is the signature different?
        {
            HEAP_WARNING(bPrint, "[Fnd Exp Heap] Bad %s memory block signature. - address %08X, signature %04X\n",
                heapType, memBlock, pMBHead->signature);
            return false;
        }

        if (pHeapHd)
        {
            if (NNSiGetUIntPtr(memBlock) + pMBHead->blockSize > NNSiGetUIntPtr(pHeapHd->heapEnd))
            {
                HEAP_WARNING(bPrint, "[Fnd Exp Heap] wrong size %s memory block. - address %08X, block size %08X\n",
                    heapType, memBlock, pMBHead->blockSize);
                return false;
            }
        }

        return true;
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         CheckUsedMBlock

  Description:  Checks whether the header contents for the memory block being used are valid.

  Arguments:    pMBHead:  pointer to the header for the memory block to be checked
                pHeapHd:  pointer to the expanded heap header
                flag:     Flag.

  Returns:      Returns true if the header contents for the memory block are valid, and returns false otherwise.
                
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static inline bool
    CheckUsedMBlock(
        NNSiFndExpHeapMBlockHead const* pMBHead,
        NNSiFndHeapHead const*                pHeapHd,
        u32                             flag
    )
    {
        return CheckMBlock(pMBHead, pHeapHd, MBLOCK_USED_SIGNATURE, "used", flag);
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         CheckFreeMBlock

  Description:  Checks whether the header contents for the free memory block are valid.

  Arguments:    pMBHead:  pointer to the header for the memory block to be checked
                pHeapHd:  pointer to the expanded heap header
                flag:     Flag.

  Returns:      Returns true if the header contents for the memory block are valid, and returns false otherwise.
                
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static inline bool
    CheckFreeMBlock(
        NNSiFndExpHeapMBlockHead const* pMBHead,
        NNSiFndHeapHead const*                pHeapHd,
        u32                             flag
    )
    {
        return CheckMBlock(pMBHead, pHeapHd, MBLOCK_FREE_SIGNATURE, "free", flag);
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         CheckMBlockPrevPtr

  Description:  Checks whether the link to before the memory block is correct.

  Arguments:    pMBHead:      pointer to the header for the memory block to be checked
                pMBHeadPrev:  pointer to the header for the memory block prior to the one being checked
                flag:         Flag.

  Returns:      Returns true if the link to before the memory block is correct, and returns false otherwise.
                
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static bool
    CheckMBlockPrevPtr(
        const NNSiFndExpHeapMBlockHead* pMBHead,
        const NNSiFndExpHeapMBlockHead* pMBHeadPrev,
        u32                             flag
    )
    {
        const bool bPrint = 0 != (flag & NN_OS_HEAP_ERROR_PRINT);

        if (pMBHead->pMBHeadPrev != pMBHeadPrev)
        {
            HEAP_WARNING(bPrint, "[NNS Foundation " "Exp" " Heap]" " Wrong link memory block. - address %08X, previous address %08X != %08X\n",
                GetMemCPtrForMBlock(pMBHead), pMBHead->pMBHeadPrev, pMBHeadPrev);
            return false;
        }

        return true;
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         CheckMBlockNextPtr

  Description:  Checks whether the link to after the memory block is correct.

  Arguments:    pMBHead:      pointer to the header for the memory block to be checked
                pMBHeadNext:  pointer to the header for the memory block after the one being checked
                flag:         Flag.

  Returns:      Returns true if the link to after the memory block is correct, and returns false otherwise.
                
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static bool
    CheckMBlockNextPtr(
        const NNSiFndExpHeapMBlockHead* pMBHead,
        const NNSiFndExpHeapMBlockHead* pMBHeadNext,
        u32                             flag
    )
    {
        const bool bPrint = 0 != (flag & NN_OS_HEAP_ERROR_PRINT);

        if (pMBHead->pMBHeadNext != pMBHeadNext)
        {
            HEAP_WARNING(bPrint, "[NNS Foundation " "Exp" " Heap]" " Wrong link memory block. - address %08X, next address %08X != %08X\n",
                GetMemCPtrForMBlock(pMBHead), pMBHead->pMBHeadNext, pMBHeadNext);
            return false;
        }

        return true;
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         CheckMBlockLinkTail

  Description:  Checks whether the memory block pointer is at the start or end of the memory block list.

  Arguments:    pMBHead:      pointer to the header for the memory block to be checked
                pMBHeadTail:  pointer to the memory block at the start or end of the memory block list
                headType:     string indicating the start or end
                flag:         Flag.

  Returns:      Returns true if the memory block pointer is at the start or end of the memory block list, and returns false otherwise.
                
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static bool
    CheckMBlockLinkTail(
        const NNSiFndExpHeapMBlockHead* pMBHead,
        const NNSiFndExpHeapMBlockHead* pMBHeadTail,
        const char*                     heapType,
        u32                             flag
    )
    {
        NN_UNUSED_VAR(heapType);
        const bool bPrint = 0 != (flag & NN_OS_HEAP_ERROR_PRINT);

        if (pMBHead != pMBHeadTail)
        {
            HEAP_WARNING(bPrint, "[NNS Foundation " "Exp" " Heap]" " Wrong memory brock list %s pointer. - address %08X, %s address %08X != %08X\n",
                heapType, GetMemCPtrForMBlock(pMBHead), heapType, pMBHead, pMBHeadTail);
            return false;
        }

        return true;
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         IsValidUsedMBlock

  Description:  Checks whether the memory block being used is appropriate.

  Arguments:    memBlock:  memory block to be checked
                heap:      handle for the expanded heap containing the memory block
                           If NULL is specified, it is not checked whether or not the memory block is contained in a heap.
                           

  Returns:      Returns TRUE if there is no problem with the specified memory block.
                Returns FALSE if there is a problem.
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    static bool
    IsValidUsedMBlock(
        const void*         memBlock,
        Heap    heap
    )
    {
        NNSiFndHeapHead* pHeapHd = heap;

        if (! memBlock)
        {
            return false;
        }

        return CheckUsedMBlock(GetMBlockHeadCPtr(memBlock), pHeapHd, 0);
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/* ========================================================================
    External functions (non-public)
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndDumpHeap

  Description:  Shows internal expanded heap information.
                This function is used for debugging.

  Arguments:    heap:    Handle for the expanded heap.

  Returns:      None.
 *---------------------------------------------------------------------------*/
//#if ! defined(NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK) && ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
#if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
    void
    NNSi_FndDumpHeap(ConstHeap heap)
    {
        NN_UNUSED_VAR(heap);

        NN_TASSERT_(IsValidHeapHandle(heap));

        {
            u32  usedSize = 0;
            u32  usedCnt = 0;
            u32  freeCnt = 0;

            NNSiFndHeapHead const* pHeapHd = heap;
            NNSiFndExpHeapHead const* pExpHeapHd = GetHeapHeadPtrFromHandle(pHeapHd);

            NNSi_FndDumpHeapHead(pHeapHd);

            NN_TLOG_("     attr  address:   size    gid aln   prev_ptr next_ptr\n");   // header line

            // ---------------- UsedBlock dump ----------------
            NN_TLOG_("    (Used Blocks)\n" );

            if (pExpHeapHd->mbUsedList.head == NULL)
            {
                NN_TLOG_("     NONE\n");
            }
            else
            {
                NNSiFndExpHeapMBlockHead* pMBHead;

                for (pMBHead = pExpHeapHd->mbUsedList.head; pMBHead; pMBHead = pMBHead->pMBHeadNext)
                {
                    if (pMBHead->signature != MBLOCK_USED_SIGNATURE)
                    {
                        NN_TLOG_("    xxxxx %08x: --------  --- ---  (-------- --------)\nabort\n", pMBHead);
                        break;
                    }

                    NN_TLOG_("    %s %08x: %8d  %3d %3d  (%08x %08x)\n",
                        GetAllocDirForMBlock(pMBHead) == NN_OS_EXPHEAP_ALLOC_DIR_REAR ? " rear" : "front",
                        GetMemPtrForMBlock(pMBHead),
                        pMBHead->blockSize,
                        GetGroupIDForMBlock( pMBHead ),
                        GetAlignmentForMBlock( pMBHead ),
                        pMBHead->pMBHeadPrev ? GetMemPtrForMBlock(pMBHead->pMBHeadPrev): NULL,
                        pMBHead->pMBHeadNext ? GetMemPtrForMBlock(pMBHead->pMBHeadNext): NULL
                    );

                    // ---- amount used
                    usedSize += sizeof(NNSiFndExpHeapMBlockHead) + pMBHead->blockSize + GetAlignmentForMBlock(pMBHead);

                    usedCnt ++;
                }
            }

            // ---------------- FreeBlock dump ----------------
            NN_TLOG_("    (Free Blocks)\n" );

            if (pExpHeapHd->mbFreeList.head == NULL)
            {
                NN_TLOG_("     NONE\n" );
            }
            else
            {
                NNSiFndExpHeapMBlockHead* pMBHead;

                for (pMBHead = pExpHeapHd->mbFreeList.head; pMBHead; pMBHead = pMBHead->pMBHeadNext)
                {
                    if (pMBHead->signature != MBLOCK_FREE_SIGNATURE)
                    {
                        NN_TLOG_("    xxxxx %08x: --------  --- ---  (-------- --------)\nabort\n", pMBHead);
                        break;
                    }

                    NN_TLOG_("    %s %08x: %8d  %3d %3d  (%08x %08x)\n",
                        " free",
                        GetMemPtrForMBlock(pMBHead),
                        pMBHead->blockSize,
                        GetGroupIDForMBlock( pMBHead ),
                        GetAlignmentForMBlock( pMBHead ),
                        pMBHead->pMBHeadPrev ? GetMemPtrForMBlock(pMBHead->pMBHeadPrev): NULL,
                        pMBHead->pMBHeadNext ? GetMemPtrForMBlock(pMBHead->pMBHeadNext): NULL
                    );

                    freeCnt ++;
                }
            }

            NN_TLOG_("\n");

            {
                u32 heapSize  = GetOffsetFromPtr(pHeapHd->heapStart, pHeapHd->heapEnd); // heap size (data region size)
//                OS_Printf("    %d / %d bytes (%6.2f%%) used (U:%d F:%d)\n",
                NN_TLOG_("    %d / %d bytes (%d%%) used (U:%d F:%d)\n",
                                   usedSize, heapSize, 100 * usedSize / heapSize, usedCnt, freeCnt);
            }

            NN_TLOG_("\n");
        }
    }
#endif
// #if ! defined(NN_SWITCH_DISABLE_ASSERT_WARNING_FOR_SDK) && ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
//#endif


/* ========================================================================
    External Functions (public)
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         CreateHeapEx

  Description:  Creates an expanded heap.

  Arguments:    startAddress: Start address of heap area
                size:         Size of heap area
                optFlag:      Option flag

  Returns:      If the function succeeds, a handle for the created expanded heap is returned.
                If the function fails, NN_OS_HEAP_INVALID_HANDLE is returned.
 *---------------------------------------------------------------------------*/
Heap
CreateHeap(
    Heap    heapHandle,
    void*   startAddress,
    u32     size,
    u16     optFlag
)
{
    void* endAddress;

    NN_NULL_TASSERT_(startAddress);

    endAddress   = NNSi_FndRoundDownPtr(AddU32ToPtr(startAddress, size), MIN_ALIGNMENT);
    startAddress = NNSi_FndRoundUpPtr(startAddress, MIN_ALIGNMENT);

    if ( NNSiGetUIntPtr(startAddress) > NNSiGetUIntPtr(endAddress)
     ||  GetOffsetFromPtr(startAddress, endAddress) < sizeof(NNSiFndExpHeapMBlockHead) + MIN_ALIGNMENT
    )
    {
        return NN_OS_HEAP_INVALID_HANDLE;
    }

    {   // initialization of the expanded heap
        NNSiFndHeapHead* pHeapHd = InitHeap(heapHandle, startAddress, endAddress, optFlag);
        return pHeapHd;  // the pointer to the heap header is used as the handle value
    }
}

/*---------------------------------------------------------------------------*
  Name:         DestroyHeap

  Description:  Destroys the expanded heap.

  Arguments:    heap: Handle for the expanded heap.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void
DestroyHeap(Heap heap)
{
    NN_TASSERT_(IsValidHeapHandle(heap));

    NNSi_FndFinalizeHeap(heap);
}

/*---------------------------------------------------------------------------*
  Name:         AllocFromHeapEx

  Description:  Allocates a memory block from the expanded heap.
                The memory block alignment can be specified.
                If a negative alignment value is specified, an available region is searched for from the back of the heap.

  Arguments:    heap:      Handle for the expanded heap.
                size:      Size of the memory block to be allocated (in bytes)
                alignment: Alignment of the memory block to be allocated
                           Allowable values: 4, 8, 16, 32, 64, 128, -4, -8, -16, -32, -64 or -128

  Returns:      Returns a pointer to the allocated memory block if the memory block allocation is successful.
                
                If the operation fails, NULL is returned.
 *---------------------------------------------------------------------------*/
void*
AllocFromHeap(
    Heap    heap,
    u32                 size,
    int                 alignment)
{
    void* memory = NULL;

    NN_TASSERT_(IsValidHeapHandle(heap));

    // Check alignment
    NN_TASSERT_(!(abs(alignment) & (abs(alignment) - 1)));
    NN_TASSERT_(MIN_ALIGNMENT <= abs(alignment) && abs(alignment) <= MAX_ALIGNMENT);

    if (size == 0)
    {
        size = 1;
    }

    size = NNSi_FndRoundUp(size, MIN_ALIGNMENT);    // size actually allocated

    if (alignment >= 0)     // allocate from the front
    {
        memory = AllocFromHead(heap, size, alignment);
    }
    else                    // allocate from the back
    {
        memory = AllocFromTail(heap, size, -alignment);
    }

    return memory;
}

/*---------------------------------------------------------------------------*
  Name:         ResizeForMBlockHeap

  Description:  Changes the size of the memory block allocated from the expanded heap.

  Arguments:    heap:     Handle for the expanded heap.
                memBlock: Pointer to the memory block to be resized
                size:     New size to be allocated (in bytes)

  Returns:      Returns the size of the resized memory block (in bytes), if the function is successful.
                Returns 0 if the function fails.
 *---------------------------------------------------------------------------*/
u32
ResizeForMBlockHeap(
    Heap    heap,
    void*               memBlock,
    u32                 size
)
{
    NNSiFndExpHeapHead* pEHHead;
    NNSiFndExpHeapMBlockHead* pMBHead;

    NN_TASSERT_(IsValidHeapHandle(heap));
    NN_TASSERT_(IsValidUsedMBlock(memBlock, heap));

    pEHHead = GetHeapHeadPtrFromHandle(heap);
    pMBHead = GetMBlockHeadPtr(memBlock);

    size = NNSi_FndRoundUp(size, MIN_ALIGNMENT);
    if (size == pMBHead->blockSize)  // when the block size is not changed
    {
        return size;
    }

    // for expanding the new area
    if (size > pMBHead->blockSize)
    {
        void* crUsedEnd = GetMBlockEndAddr(pMBHead);   // end address for the used block
        NNSiFndExpHeapMBlockHead* block;

        // search for the next free block
        for (block = pEHHead->mbFreeList.head; block; block = block->pMBHeadNext)
        {
            if (block == crUsedEnd)
            {
                break;
            }
        }

        // there is no next free block or the size is inadequate
        if (! block || size > pMBHead->blockSize + sizeof(NNSiFndExpHeapMBlockHead) + block->blockSize)
        {
            return 0;
        }

        {
            NNSiMemRegion rgnNewFree;
            void* oldFreeStart;
            NNSiFndExpHeapMBlockHead* nextBlockPrev;

            // get the free block region, and temporarily remove the free block
            GetRegionOfMBlock(&rgnNewFree, block);
            nextBlockPrev = RemoveMBlock(&pEHHead->mbFreeList, block);

            oldFreeStart = rgnNewFree.start;
            rgnNewFree.start = AddU32ToPtr(memBlock, size); // region position to be newly freed

            // when the remainder is smaller than the memory block size
            if (GetOffsetFromPtr(rgnNewFree.start, rgnNewFree.end) < sizeof(NNSiFndExpHeapMBlockHead))
            {
                rgnNewFree.start = rgnNewFree.end;  // absorbed into the used block
            }

            pMBHead->blockSize = GetOffsetFromPtr(memBlock, rgnNewFree.start);  // change the target block size

            // when the remainder is equal to or larger than the memory block size
            if (GetOffsetFromPtr(rgnNewFree.start, rgnNewFree.end) >= sizeof(NNSiFndExpHeapMBlockHead))
            {
                (void)InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&rgnNewFree), nextBlockPrev);   // create a new free block
            }

            FillAllocMemory(  // expanded portion fill
                heap,
                oldFreeStart,
                GetOffsetFromPtr(oldFreeStart, rgnNewFree.start));
        }
    }
    // when the new area is reduced
    else
    {
        NNSiMemRegion rgnNewFree;
        const u32 oldBlockSize = pMBHead->blockSize;

        rgnNewFree.start = AddU32ToPtr(memBlock, size); // region position to be newly freed
        rgnNewFree.end   = GetMBlockEndAddr(pMBHead);   // end address for the used block

        pMBHead->blockSize = size;  // change the target block size

        if (! RecycleRegion(pEHHead, &rgnNewFree))    // try to return to the free list
        {
            pMBHead->blockSize = oldBlockSize;  // restore to original form if failed
        }
    }

    return pMBHead->blockSize;
}

/*---------------------------------------------------------------------------*
  Name:         FreeToHeap

  Description:  Returns the memory block to the expanded heap.

  Arguments:    heap:     Handle for the expanded heap.
                memBlock: Pointer to the memory block to be returned

  Returns:      None.
 *---------------------------------------------------------------------------*/
void
FreeToHeap(
    Heap    heap,
    void*               memBlock
)
{
    NN_TASSERT_(IsValidHeapHandle(heap));

    {
        NNSiFndHeapHead* pHeapHd = heap;
        NNSiFndExpHeapHead* pExpHeapHd = GetHeapHeadPtrFromHandle(pHeapHd);
        NNSiFndExpHeapMBlockHead* pMBHead = GetMBlockHeadPtr(memBlock);
        NNSiMemRegion region;

        // Is it included in this heap?
        NN_TASSERT_(pHeapHd->heapStart <= memBlock && memBlock < pHeapHd->heapEnd);

        GetRegionOfMBlock(&region, pMBHead);
        (void)RemoveMBlock(&pExpHeapHd->mbUsedList, pMBHead);   // remove from the list being used
        (void)RecycleRegion(pExpHeapHd, &region);   // add the specified size from the specified address to the free region
    }
}

/*---------------------------------------------------------------------------*
  Name:         GetTotalFreeSizeForHeap

  Description:  Gets the total size of the available regions of the expanded heap.

  Arguments:    heap:     Handle for the expanded heap.

  Returns:      Returns the total size of the available regions in the expanded heap (in bytes).
 *---------------------------------------------------------------------------*/
u32
GetTotalFreeSizeForHeap( ConstHeap heap)
{
    NN_TASSERT_(IsValidHeapHandle(heap));

    {
        u32 sumSize = 0;
        NNSiFndExpHeapHead const* pEHHead = GetHeapHeadPtrFromHandle(heap);
        NNSiFndExpHeapMBlockHead const* pMBHead;

        for(pMBHead = pEHHead->mbFreeList.head; pMBHead; pMBHead = pMBHead->pMBHeadNext)
        {
            sumSize += pMBHead->blockSize;
        }

        return sumSize;
    }
}

/*---------------------------------------------------------------------------*
  Name:         GetAllocatableSizeForHeapEx

  Description:  Gets a memory block of the maximum allocatable size from the expanded heap.
                The memory block alignment can be specified.

  Arguments:    heap:      Handle for the expanded heap.
                alignment: Alignment of the memory block to be allocated
                           Allowable values: 4, 8, 16, 32, 64 or 128

  Returns:      Returns the maximum allocatable size from the expanded heap (in bytes).
 *---------------------------------------------------------------------------*/
u32
GetAllocatableSizeForHeap(
    ConstHeap    heap,
    int                 alignment
)
{
    NN_TASSERT_(IsValidHeapHandle(heap));

    // Check alignment
    NN_TASSERT_(!(abs(alignment) & (abs(alignment) - 1)));
    NN_TASSERT_(MIN_ALIGNMENT <= abs(alignment) && abs(alignment) <= MAX_ALIGNMENT);

    alignment = abs(alignment); // convert to a positive value just to be sure

    {
        NNSiFndExpHeapHead const* pEHHead = GetHeapHeadPtrFromHandle(heap);
        u32 maxSize = 0;
        u32 offsetMin = 0xFFFFFFFF;
        NNSiFndExpHeapMBlockHead* pMBlkHd;

        for (pMBlkHd = pEHHead->mbFreeList.head; pMBlkHd; pMBlkHd = pMBlkHd->pMBHeadNext)
        {
            // memory block position giving consideration to the alignment
            void* baseAddress = NNSi_FndRoundUpPtr(GetMemPtrForMBlock(pMBlkHd), alignment);

            if (NNSiGetUIntPtr(baseAddress) < NNSiGetUIntPtr(GetMBlockEndAddr(pMBlkHd)))
            {
                const u32 blockSize = GetOffsetFromPtr(baseAddress, GetMBlockEndAddr(pMBlkHd));
                // empty area due to the alignment
                const u32 offset = GetOffsetFromPtr(GetMemPtrForMBlock(pMBlkHd), baseAddress);

                /*
                    If the size is larger, or the the same but with less wasted space, the memory block is updated.
                    
                 */
                if ( maxSize < blockSize
                 ||  (maxSize == blockSize && offsetMin > offset)
                )
                {
                    maxSize = blockSize;
                    offsetMin= offset;
                }
            }
        }

        return maxSize;
    }
}

/*---------------------------------------------------------------------------*
  Name:         SetAllocModeForHeap

  Description:  Sets the memory allocation mode for the expanded heap.

  Arguments:    heap:  Handle for the expanded heap.
                mode:  Memory allocation mode.

  Returns:      Returns the memory allocation mode for the previous expanded heap.
 *---------------------------------------------------------------------------*/
u16
SetAllocModeForHeap(
    Heap    heap,
    u16                 mode
)
{
    NN_TASSERT_(IsValidHeapHandle(heap));

    {
        NNSiFndExpHeapHead *const pEHHead = GetHeapHeadPtrFromHandle(heap);
        u16 oldMode = GetAllocMode(pEHHead);
        SetAllocMode(pEHHead, mode);

        return oldMode;
    }
}

/*---------------------------------------------------------------------------*
  Name:         GetAllocModeForHeap

  Description:  Gets the memory allocation mode for the expanded heap.

  Arguments:    heap:    Handle for the expanded heap.

  Returns:      Returns the memory allocation mode for the expanded heap.
 *---------------------------------------------------------------------------*/
u16
GetAllocModeForHeap(Heap heap)
{
    NN_TASSERT_(IsValidHeapHandle(heap));
    return GetAllocMode(GetHeapHeadPtrFromHandle(heap));
}

/*---------------------------------------------------------------------------*
  Name:         UseMarginOfAlignmentForHeap

  Description:  Configures whether regions in the gaps that occur during alignment should be reused.
                
                Set to FALSE by default.
                
                Although it may be possible to efficiently utilize small memory blocks if TRUE is set, there is a risk that performance will go down when allocating memory because of generating a large number of free blocks.
                
                
                

  Arguments:    heap:    Expanded heap handle
                reuse:   If TRUE, reuse regions that are generated during alignment.
                        If FALSE, do not reuse.

  Returns:      Returns the value of the previous setting.
 *---------------------------------------------------------------------------*/
bool
UseMarginOfAlignmentForHeap(Heap heap, bool reuse)
{
    //MEMiExpHeapHead *const pEHHead = GetExpHeapHeadPtrFromHandle_(heap);
    NNSiFndExpHeapHead *const pEHHead = GetHeapHeadPtrFromHandle(heap);
    bool before;
    
    NN_TASSERT_(IsValidHeapHandle(heap));
    
    before = pEHHead->reuse;
    pEHHead->reuse = reuse;
    
    return before;
}


/*---------------------------------------------------------------------------*
  Name:         SetGroupIDForHeap

  Description:  Sets the group ID for the expanded heap.

  Arguments:    heap:    Handle for the expanded heap.
                groupID: Group ID value to be set.

  Returns:      Returns the previous group ID value.
 *---------------------------------------------------------------------------*/
u16
SetGroupIDForHeap(
    Heap    heap,
    u16                 groupID)
{
    NN_TASSERT_(IsValidHeapHandle(heap));
    NN_TASSERT_(groupID <= MAX_GROUPID);

    {
        NNSiFndExpHeapHead* pEHHead = GetHeapHeadPtrFromHandle(heap);
        u16 oldGroupID = pEHHead->groupID;
        pEHHead->groupID = groupID;

        return oldGroupID;
    }
}

/*---------------------------------------------------------------------------*
  Name:         GetGroupIDForHeap

  Description:  Gets the group ID for the expanded heap.

  Arguments:    heap:    Handle for the expanded heap.

  Returns:      Returns the group ID value.
 *---------------------------------------------------------------------------*/
u16
GetGroupIDForHeap(Heap heap)
{
    NN_TASSERT_(IsValidHeapHandle(heap));

    return GetHeapHeadPtrFromHandle(heap)->groupID;
}

/*---------------------------------------------------------------------------*
  Name:         VisitAllocatedForHeap

  Description:  For all memory blocks that are allocated from expanded heaps, the functions specified by the user are called.
                
                The order of the memory blocks called by the visitor function is the order in which they were allocated.

                The visitor type NNSFndHeapVisitor is defined as below.

                    typedef void (*NNSFndHeapVisitor)(
                                    void*               memBlock,
                                    Heap    heap,
                                    u32                 userParam);

                                        memBlock:   pointer to the memory block
                                        heap:       heap that includes the memory block
                                        userParam:  user parameter

  Arguments:    heap:       Handle for the expanded heap.
                visitor:    Function called for each memory block
                userParam:  User-specified parameter passed to the visitor function

  Returns:      None.
 *---------------------------------------------------------------------------*/
void
VisitAllocatedForHeap(
    Heap    heap,
    NNSFndHeapVisitor   visitor,
    u32                 userParam
)
{
    NN_TASSERT_(IsValidHeapHandle(heap));
    NN_NULL_TASSERT_(visitor);

    {
        NNSiFndExpHeapMBlockHead* pMBHead = GetHeapHeadPtrFromHandle(heap)->mbUsedList.head;

        while (pMBHead)
        {
            NNSiFndExpHeapMBlockHead* pMBHeadNext = pMBHead->pMBHeadNext;
            (*visitor)(GetMemPtrForMBlock(pMBHead), heap, userParam);
            pMBHead = pMBHeadNext;
        }
    }
}

/*---------------------------------------------------------------------------*
  Name:         GetSizeForMBlockHeap

  Description:  Gets the size of the memory block that was allocated from the expanded heap.

  Arguments:    memBlock:  pointer to the memory block for getting the size

  Returns:      Returns the size of the specified memory block (in bytes).
 *---------------------------------------------------------------------------*/
u32
GetSizeForMBlockHeap(const void* memBlock)
{
    NN_TASSERT_(IsValidUsedMBlock(memBlock, NULL));

    return GetMBlockHeadCPtr(memBlock)->blockSize;
}

/*---------------------------------------------------------------------------*
  Name:         GetGroupIDForMBlockHeap

  Description:  Gets the group ID for the memory block allocated from the expanded heap.

  Arguments:    memBlock:  pointer to the memory block for getting the group ID

  Returns:      Returns the group ID for the specified memory block.
 *---------------------------------------------------------------------------*/
u16
GetGroupIDForMBlockHeap(const void* memBlock)
{
    NN_TASSERT_(IsValidUsedMBlock(memBlock, NULL));

    return GetGroupIDForMBlock(GetMBlockHeadCPtr(memBlock));
}

/*---------------------------------------------------------------------------*
  Name:         GetAllocDirForMBlockHeap

  Description:  Gets the allocation direction for the memory block allocated from the expanded heap.

  Arguments:    memBlock:  pointer to the memory block

  Returns:      Returns the allocation direction for the specified memory block.
 *---------------------------------------------------------------------------*/
u16
GetAllocDirForMBlockHeap(const void* memBlock)
{
    NN_TASSERT_(IsValidUsedMBlock(memBlock, NULL));

    return GetAllocDirForMBlock(GetMBlockHeadCPtr(memBlock));
}

/*---------------------------------------------------------------------------*
  Name:         AdjustHeap

  Description:  Deallocates the expanded heap's available region, and reduces the memory region that is available for use by the expanded heap.
                There must not be memory blocks allocated from the back of heap memory.

  Arguments:    heap:      Handle for the expanded heap.
                mode:      Specifies whether the end (NN_FND_EXPHEAPD_ADJUST_TAIL) or start (NN_FND_EXPHEAPD_ADJUST_HEAD) is shortened.

                          
  Returns:      Returns a range of empty memory blocks resulting from adjusting the heap.

 *---------------------------------------------------------------------------*/
MemoryRange
AdjustHeap(Heap heap, HeapAdjustMode mode)
{
    NN_TASSERT_( IsValidHeapHandle(heap) );
    NN_TASSERT_( mode == HEAP_ADJUST_TAIL || mode == HEAP_ADJUST_HEAD );

    if ( mode == HEAP_ADJUST_TAIL )
    {
        NNSiFndHeapHead* pHeapHd = heap;
        NNSiFndExpHeapHead* pExpHeapHd = GetHeapHeadPtrFromHeapHead(pHeapHd);
        NNSiFndExpHeapMBlockHead* pMBlkHd  = pExpHeapHd->mbFreeList.tail;
        
        // Fail if there are no available regions
        if ( pMBlkHd == NULL )
        {
            return MakeMemoryRange(heap->heapEnd, 0);
        }
        
        void * const pMBlk      = GetMemPtrForMBlock( pMBlkHd );
        void * const pMBlkEnd   = AddU32ToPtr( pMBlk, pMBlkHd->blockSize );
        
        // Fail if there exists any memory blocks allocated from the end
        if ( pMBlkEnd != heap->heapEnd )
        {
            return MakeMemoryRange(heap->heapEnd, 0);
        }
        
        // Delete deallocated free block from the free list
        (void)RemoveMBlock( &pExpHeapHd->mbFreeList, pMBlkHd );
        
        u32 blockSize = pMBlkHd->blockSize + sizeof( NNSiFndExpHeapMBlockHead );
        pHeapHd->heapEnd = SubU32ToPtr( pHeapHd->heapEnd, blockSize );
        
        return MakeMemoryRange(pHeapHd->heapEnd, blockSize);
    }
    else if ( mode == HEAP_ADJUST_HEAD )
    {
        NNSiFndHeapHead* pHeapHd = heap;
        NNSiFndExpHeapHead* pExpHeapHd = GetHeapHeadPtrFromHeapHead(pHeapHd);
        NNSiFndExpHeapMBlockHead* pMBlkHd  = pExpHeapHd->mbFreeList.head;
        
        // Fail if there are no available regions
        if ( pMBlkHd == NULL )
        {
            return MakeMemoryRange(heap->heapStart, 0);
        }
        
        // Fail if any memory blocks allocated from the start are present
        if ( pMBlkHd != heap->heapStart )
        {
            return MakeMemoryRange(heap->heapStart, 0);
        }
        
        // Delete deallocated free block from the free list
        (void)RemoveMBlock( &pExpHeapHd->mbFreeList, pMBlkHd );
        
        u32 blockSize = pMBlkHd->blockSize + sizeof( NNSiFndExpHeapMBlockHead );
        pHeapHd->heapStart = AddU32ToPtr( pHeapHd->heapStart, blockSize );
        
        return MakeMemoryRange(pHeapHd->heapStart, blockSize);
    }
    else 
    {
        NN_PANIC("ExpHeap::Adjust invalid argument( invalid mode )");
        return MakeMemoryRange(heap->heapEnd, 0);
    }
}


/*---------------------------------------------------------------------------*
  Name:         CheckHeap

  Description:  Checks whether the expanded heap has been destroyed.

  Arguments:    heap:     Handle for the expanded heap.
                optFlag:  Flag.

  Returns:      Returns TRUE if the heap is normal.
                Returns FALSE if the heap has an error.
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    bool
    CheckHeap(
        ConstHeap    heap,
        u32                 optFlag
    )
    {
        const bool bPrint = 0 != (optFlag & NN_OS_HEAP_ERROR_PRINT);
        u32  totalBytes  = 0;

        if (! IsValidHeapHandle(heap))
        {
//            HEAP_WARNING(bPrint, "[NNS Foundation " "Exp" " Heap]" " Invalid heap handle. - %08X\n", heap);
            HEAP_WARNING(bPrint, "[Fnd Exp Heap] Invalid heap handle. - %08X\n", heap);
            return false;
        }

        {
            NNSiFndHeapHead const* pHeapHd = heap;
            NNSiFndExpHeapHead const* pExpHeapHd = GetHeapHeadPtrFromHeapHead(pHeapHd);
            NNSiFndExpHeapMBlockHead* pMBHead = NULL;
            NNSiFndExpHeapMBlockHead* pMBHeadPrev = NULL;

            // used block
            for (pMBHead = pExpHeapHd->mbUsedList.head; pMBHead; pMBHeadPrev = pMBHead, pMBHead = pMBHead->pMBHeadNext)
            {
                if ( ! CheckUsedMBlock(pMBHead, pHeapHd, optFlag)
                  || ! CheckMBlockPrevPtr(pMBHead, pMBHeadPrev, optFlag)   // Is the pointer to the previous block the same as the pointer to the memory block in the previous loop?
                )
                {
                    return false;
                }

                // calculate size occupied
                totalBytes += sizeof(NNSiFndExpHeapMBlockHead) + pMBHead->blockSize + GetAlignmentForMBlock(pMBHead);
            }

            if (! CheckMBlockLinkTail(pMBHeadPrev, pExpHeapHd->mbUsedList.tail, "tail", optFlag))  // Is the last block indicating the pointer to the final block?
            {
                return false;
            }

            // free block
            pMBHead = NULL;
            pMBHeadPrev = NULL;
            for (pMBHead = pExpHeapHd->mbFreeList.head; pMBHead; pMBHeadPrev = pMBHead, pMBHead = pMBHead->pMBHeadNext)
            {
                if ( ! CheckFreeMBlock(pMBHead, pHeapHd, optFlag)
                  || ! CheckMBlockPrevPtr(pMBHead, pMBHeadPrev, optFlag)   // Is the pointer to the previous block the same as the pointer to the memory block in the previous loop?
                )
                {
                    return false;
                }

                // calculate size occupied
                totalBytes += sizeof(NNSiFndExpHeapMBlockHead) + pMBHead->blockSize;
            }

            if (! CheckMBlockLinkTail(pMBHeadPrev, pExpHeapHd->mbFreeList.tail, "tail", optFlag))  // Is the last block indicating the pointer to the final block?
            {
                return false;
            }

            // Display all results.
            if (totalBytes != GetOffsetFromPtr(pHeapHd->heapStart, pHeapHd->heapEnd))
            {
                HEAP_WARNING(bPrint, "[NNS Foundation " "Exp" " Heap]" " Incorrect total memory block size. - heap size %08X, sum size %08X\n",
                    GetOffsetFromPtr(pHeapHd->heapStart, pHeapHd->heapEnd), totalBytes);
                return false;
            }

            return true;
        }
    }

// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

/*---------------------------------------------------------------------------*
  Name:         CheckForMBlockHeap

  Description:  This function checks if the memory block of the expanded heap was destroyed.

  Arguments:    memBlock:  Pointer to the memory block to be checked.
                heap:      Handle for the expanded heap.
                optFlag:   Flag.

  Returns:      Returns TRUE if the memory block is normal.
                Returns FALSE if the memory block has an error.
 *---------------------------------------------------------------------------*/
#ifndef HEAP_DISABLE_DEBUG_PRINT

    bool
    CheckForMBlockHeap(
        const void*         memBlock,
        ConstHeap    heap,
        u32                 optFlag
    )
    {
        const NNSiFndExpHeapMBlockHead* pMBHead = NULL;
        NNSiFndHeapHead const* pHeapHd = heap;

        if (! memBlock)
        {
            return false;
        }

        pMBHead = GetMBlockHeadCPtr(memBlock);

        if (! CheckUsedMBlock(pMBHead, pHeapHd, optFlag))
        {
            return false;
        }

        if (pMBHead->pMBHeadPrev)
        {
            if ( ! CheckUsedMBlock(pMBHead->pMBHeadPrev, pHeapHd, optFlag)     // check of signature and size of previous block
              || ! CheckMBlockNextPtr(pMBHead->pMBHeadPrev, pMBHead, optFlag)  // Is the previous block's pointer to the next block indicating the current block?
            )
            {
                return false;
            }
        }
        else
        {
            if (pHeapHd)
            {
                // When prev is NULL, the head pointer of the list should indicate the current (block).
                if (! CheckMBlockLinkTail(pMBHead, GetHeapHeadPtrFromHeapHead(pHeapHd)->mbUsedList.head, "head", optFlag))
                {
                    return false;
                }
            }
        }

        if (pMBHead->pMBHeadNext)
        {
            if ( ! CheckUsedMBlock(pMBHead->pMBHeadNext, pHeapHd, optFlag)     // check of signature and size of next block
              || ! CheckMBlockPrevPtr(pMBHead->pMBHeadNext, pMBHead, optFlag)  // Is the next block's pointer to the previous block indicating the current block?
            )
            {
                return false;
            }
        }
        else
        {
            if (pHeapHd)
            {
                // When next is NULL, the tail pointer of the list should indicate the current (block).
                if (! CheckMBlockLinkTail(pMBHead, GetHeapHeadPtrFromHeapHead(pHeapHd)->mbUsedList.tail, "tail", optFlag))
                {
                    return false;
                }
            }
        }

        return true;
    }
// #ifndef HEAP_DISABLE_DEBUG_PRINT
#endif

}}}
