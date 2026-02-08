/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailHeapCommon.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/assert.h>
#include "./fnd_DetailHeap.h"
#include "./fnd_DetailHeapCommon.h"
#include "./fnd_DetailHeapCommonImpl.h"


namespace nn { namespace fnd { namespace detail {

/* ========================================================================
    static variables
   ======================================================================== */

/* ------------------------------------------------------------------------
    list-related
   ------------------------------------------------------------------------ */

static NNSFndList sRootList;                // root heap list
static bool sRootListInitialized = false;   // if sRootList is initialized, true


/* ------------------------------------------------------------------------
    fill-related
   ------------------------------------------------------------------------ */

#ifdef NN_BUILD_VERBOSE

    static u32 sFillVals[NN_OS_HEAP_FILL_MAX] =
    {
        0xC3C3C3C3, // value to fill with when creating heap
        0xF3F3F3F3, // value to fill with when allocating memory block
        0xD3D3D3D3, // value to fill with when deallocating memory block
    };

// #ifdef NN_BUILD_VERBOSE
#endif


/* ========================================================================
    Static functions
   ======================================================================== */

/* ------------------------------------------------------------------------
    list-related
   ------------------------------------------------------------------------ */

/*---------------------------------------------------------------------------*
  Name:         FindContainHeap
  Description:  Searches recursively from the list for the heap that includes the specified memory block.
                
  Arguments:    pList:     Pointer to list
                memBlock:  Pointer to memory block
  Returns:      When the heap that allocated the specified memory block is found, returns a pointer to that heap.
                
                Returns NULL if it is not found.
 *---------------------------------------------------------------------------


*/
static NNSiFndHeapHead*
FindContainHeap(
    NNSFndList* pList,
    const void* memBlock
)
{
    NNSiFndHeapHead* pHeapHd = NULL;
    while (NULL != (pHeapHd = reinterpret_cast<NNSiFndHeapHead*>(
                    GetNextListObject(pList, pHeapHd))))
    {
        if ( NNSiGetUIntPtr(pHeapHd->heapStart) <= NNSiGetUIntPtr(memBlock)
         &&  NNSiGetUIntPtr(memBlock) < NNSiGetUIntPtr(pHeapHd->heapEnd)
        )
        {
            NNSiFndHeapHead* pChildHeapHd = FindContainHeap(&pHeapHd->childList, memBlock);
            if(pChildHeapHd)
            {
                return pChildHeapHd;
            }

            return pHeapHd;
        }
    }

    return NULL;
}

/*---------------------------------------------------------------------------*
  Name:         FindListContainHeap
  Description:  Searches the parent heap that contains the heap, and returns a pointer to the parent heap list.
                
  Arguments:    pHeapHd:  Pointer to the header of search target heap
  Returns:      If the parent heap that includes the specified heap is found, the pointer to the child list of the parent heap is returned.
                
                If the parent heap is not found, a pointer to the root list is returned.
 *---------------------------------------------------------------------------


*/
static NNSFndList*
FindListContainHeap(NNSiFndHeapHead* pHeapHd)
{
    NNSFndList* pList = &sRootList;

    NNSiFndHeapHead* pContainHeap = FindContainHeap(&sRootList, pHeapHd);

    if(pContainHeap)
    {
        pList = &pContainHeap->childList;
    }

    return pList;
}

#if 1
    static inline void
//    static void
    DumpHeapList() {}
#else
    static void
    DumpHeapList()
    {
        NNSiFndHeapHead* pHeapHd = NULL;
        int count = 0;

        NN_TLOG_("Dump Heap List\n");
        while (NULL != (pHeapHd = GetNextListObject(&sRootList, pHeapHd)))
        {
            count++;
            NN_TLOG_("[%d] -> %p %08X\n", count, pHeapHd, pHeapHd->signature);
        }
    }
#endif

/* ========================================================================
    External functions (non-public)
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndInitHeapHead
  Description:  Initializes the heap header.
  Arguments:    pHeapHd:    Pointer to the heap header
                signature:  Signature
                heapStart:  Start address of heap memory
                heapEnd:    End address +1 of heap memory
                optFlag:    Heap option
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
NNSi_FndInitHeapHead(
    NNSiFndHeapHead*    pHeapHd,
    u32                 signature,
    void*               heapStart,
    void*               heapEnd,
    u16                 optFlag
)
{
    pHeapHd->signature = signature;

    pHeapHd->heapStart = heapStart;
    pHeapHd->heapEnd   = heapEnd;

    pHeapHd->attribute = 0;
    SetOptForHeap(pHeapHd, optFlag);

    FillNoUseMemory(
        pHeapHd,
        heapStart,
        GetOffsetFromPtr(heapStart, heapEnd));

    NN_OS_INIT_LIST(&pHeapHd->childList, NNSiFndHeapHead, link);

    // heap list operation
    if(! sRootListInitialized)
    {
        NN_OS_INIT_LIST(&sRootList, NNSiFndHeapHead, link);
        sRootListInitialized = true;
    }

    AppendListObject(FindListContainHeap(pHeapHd), pHeapHd);
    DumpHeapList();

}

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndFinalizeHeap
  Description:  Performs common heap cleanup.
  Arguments:    pHeapHd:  Pointer to the heap header
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
NNSi_FndFinalizeHeap(NNSiFndHeapHead* pHeapHd)
{
    // heap list operation
    RemoveListObject(FindListContainHeap(pHeapHd), pHeapHd);
    DumpHeapList();
}


/*---------------------------------------------------------------------------*
  Name:         NNSi_FndDumpHeapHead
  Description:  Displays heap header information.
  Arguments:    pHeapHd:  Pointer to the heap header
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
NNSi_FndDumpHeapHead(NNSiFndHeapHead const* pHeapHd)
{
    NN_TLOG_("[NNS Foundation ");

    switch(pHeapHd->signature)
    {
    case NNSI_EXPHEAP_SIGNATURE: NN_TLOG_("Exp");   break;
    case NNSI_FRMHEAP_SIGNATURE: NN_TLOG_("Frame"); break;
    case NNSI_UNTHEAP_SIGNATURE: NN_TLOG_("Unit");  break;
    default:
        NN_TASSERT_(false);
    }

    NN_TLOG_(" Heap]\n");

    NN_TLOG_("    whole [%p - %p)\n", pHeapHd, pHeapHd->heapEnd);
}


/* ========================================================================
    External Functions (public)
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         FindContainHeap
  Description:  Searches for the heap containing the memory block.
  Arguments:    memBlock:  Memory block to be searched for
  Returns:      When the heap that includes the specified memory block is found, returns the handle of that heap.
                
                If it is not found, NN_OS_HEAP_INVALID_HANDLE is returned.
 *---------------------------------------------------------------------------


*/
Heap
FindContainHeap(const void* memBlock)
{
    return FindContainHeap(&sRootList, memBlock);
}

/*---------------------------------------------------------------------------*
  Name:         DumpHeap
  Description:  Displays the information in the heap.
                This function is used for debugging.
  Arguments:    heap:    Handle for the frame heap.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
#if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)

    void
    DumpHeap(Heap heap)
    {
        NNSiFndHeapHead* pHeapHd = heap;
        switch(pHeapHd->signature)
        {
        case NNSI_EXPHEAP_SIGNATURE: NNSi_FndDumpHeap(heap);  break;
        default:
            NN_TLOG_("[NNS Foundation] dump heap : unknown heap. - %p\n", heap);
        }
    }

// #if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
#endif

/*---------------------------------------------------------------------------*
  Name:         SetFillValForHeap
  Description:  Sets a value to set in memory when creating a heap or allocating or deallocating a memory block.
                
                This function is for use in debugging.
                Always returns 0 in the final ROM version library (FINALROM).
  Arguments:    type:  Type of value to get
                val:   Value to set
  Returns:      Returns the previous value that was set in memory when the memory block was allocated.
 *---------------------------------------------------------------------------


*/

#ifdef NN_BUILD_VERBOSE

    u32
    SetFillValForHeap(
        int     type,
        u32     val
    )
    {
        NN_TASSERT_(type < NN_OS_HEAP_FILL_MAX);

        {
            u32 oldVal = sFillVals[type];
            sFillVals[type] = val;
            return oldVal;
        }
    }

// #ifdef NN_BUILD_VERBOSE
#endif


/*---------------------------------------------------------------------------*
  Name:         GetFillValForHeap
  Description:  Gets the value to set in memory when creating a heap or allocating or deallocating a memory block.
                
                This function is for use in debugging.
                Always returns 0 in the final ROM version library (FINALROM).
  Arguments:    type:  Type of value to get
  Returns:      Returns the value set in the memory of the type specified.
 *---------------------------------------------------------------------------


*/

#ifdef NN_BUILD_VERBOSE

    u32
    GetFillValForHeap(int type)
    {
        NN_TASSERT_(type < NN_OS_HEAP_FILL_MAX);

        return sFillVals[type];
    }

// #ifdef NN_BUILD_VERBOSE
#endif

}}} // namespace nn::os::fnd

