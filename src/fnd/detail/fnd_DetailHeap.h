/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailHeap.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
  

*/

#ifndef NN_FND_DETAIL_FND_DETAIL_HEAP_H_
#define NN_FND_DETAIL_FND_DETAIL_HEAP_H_

#include <nn/fnd/detail/fnd_DetailHeapHead.h>
#include <nn/fnd/fnd_HeapBase.h>
#include <nn/fnd/fnd_MemoryRange.h>
#include "fnd_DetailHeapCommon.h"

#define NN_OS_EXPHEAP_ALLOC_DIR_FRONT 0    // Allocate from front
#define NN_OS_EXPHEAP_ALLOC_DIR_REAR  1     // Allocate from back
#define NN_OS_EXPHEAP_ALLOC_MODE_FIRST 0
#define NN_OS_EXPHEAP_ALLOC_MODE_NEAR 1

#ifdef __cplusplus

namespace nn{ namespace fnd{ namespace detail {
/* Please see man pages for details 
  
  
*/
/* Please see man pages for details 
  
  
  
  

*/
/* =======================================================================
    Constant definitions
   ======================================================================== */

// Memory allocation direction
//Enums
//{
//    NN_OS_EXPHEAP_ALLOC_DIR_FRONT,    // Allocates from the front
//    NN_OS_EXPHEAP_ALLOC_DIR_REAR      // Allocates from the back
//};

// Memory allocation mode
//Enums
//{
    /*
        If this attribute value is set, memory larger than the size of the memory to allocate is maintained, and memory from the first empty region found is allocated.
        
        
    */
//    NN_OS_EXPHEAP_ALLOC_MODE_FIRST,

    /*
        If this attribute value is set, search for the empty region closest to the size of the memory to allocate, and allocate from that region.
       
        
    */
//    NN_OS_EXPHEAP_ALLOC_MODE_NEAR
//};


/* =======================================================================
    Type Definitions
   ======================================================================== */

// Callback function type called for each memory
typedef void        (*NNSFndHeapVisitor)(
                        void*               memBlock,
                        Heap    heap,
                        u32                 userParam);

/* =======================================================================
    Macro Functions
   ======================================================================== */



/* =======================================================================
    Function Prototypes
   ======================================================================== */
#if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
//

    void                NNSi_FndDumpHeap(
                            ConstHeap    heap);

//
#endif

/* Please see man pages for details 
  
  
  
  
  
  
                


*/
Heap    CreateHeap(
                        Heap    heapHandle,
                        void*   startAddress,
                        u32     size,
                        u16     optFlag = 0);


/* Please see man pages for details 
  
  
  


*/
void                DestroyHeap(
                        Heap    heap);


/* Please see man pages for details 
  
                
  
  

*/
void SetCurrentHeap(Heap heap);


/* Please see man pages for details 
  
                
  

*/
Heap  GetCurrentHeap(void);


/* Please see man pages for details 
  
                
                
  
  
  
                           
  
                
                


*/
void*               AllocFromHeap(
                        Heap    heap,
                        u32                 size,
                        int                 alignment = NN_OS_HEAP_DEFAULT_ALIGNMENT);


/* Please see man pages for details 
  
                
  
  
                           
  
                
                


*/
inline void*   AllocFromCurrentHeap(u32 size, int alignment = NN_OS_HEAP_DEFAULT_ALIGNMENT)
{
    return AllocFromHeap(GetCurrentHeap(), size, alignment);
}

/* Please see man pages for details 
  
  
  
  


*/
void                FreeToHeap(
                        Heap    heap,
                        void*               memBlock);


/* Please see man pages for details 
  
                
  
  

*/
inline  void    FreeToCurrentHeap(void* memBlock)
{
    FreeToHeap(GetCurrentHeap(), memBlock);
}

/* Please see man pages for details 
  
  
  
  
  
                


*/
u32                 ResizeForMBlockHeap(
                        Heap    heap,
                        void*               memBlock,
                        u32                 size);

/* Please see man pages for details 
  
  
  


*/
u32                 GetTotalFreeSizeForHeap(
                         ConstHeap heap);


/* Please see man pages for details 
  
                
  
  
                           
  


*/
u32                 GetAllocatableSizeForHeap(
                        ConstHeap    heap,
                        int                 alignment = NN_OS_HEAP_DEFAULT_ALIGNMENT);


/* Please see man pages for details 
  
  
  
  


*/
u16                 SetAllocModeForHeap(
                        Heap    heap,
                        u16                 mode);

/* Please see man pages for details 
  
  
  


*/
u16                 GetAllocModeForHeap(
                        Heap    heap);

/* Please see man pages for details 
  
  
  
  


*/
u16                 SetGroupIDForHeap(
                        Heap    heap,
                        u16                 groupID);

/* Please see man pages for details 
  
  
  


*/
u16                 GetGroupIDForHeap(
                        Heap    heap);

/* Please see man pages for details 
  
                
                
                
                    
                                    
                                    
                                    
                                        
                                        
                                        
  
  
  
  





*/
void                VisitAllocatedForHeap(
                        Heap    heap,
                        NNSFndHeapVisitor   visitor,
                        u32                 userParam);

/* Please see man pages for details 
  
  
  


*/
u32                 GetSizeForMBlockHeap(
                        const void*         memBlock);

/* Please see man pages for details 
  
  
  


*/
u16                 GetGroupIDForMBlockHeap(
                        const void*         memBlock);

/* Please see man pages for details 
  
  
  


*/
u16                 GetAllocDirForMBlockHeap(
                        const void*         memBlock);

/* Please see man pages for details 
  
  
  
  


*/
MemoryRange         AdjustHeap(
                        Heap                heap,
                        HeapAdjustMode          mode);

/* Please see man pages for details 
  
                
  
  
  


*/
bool                UseMarginOfAlignmentForHeap(
                        Heap                heap,
                        bool                reuse);


#if defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
inline bool CheckHeap(ConstHeap, u32) { return true; }
inline bool CheckForMBlockHeap(const void*, ConstHeap, u32) { return true; }
#else

/* Please see man pages for details 
  
  
  
  
                


*/
    bool                CheckHeap(
                            ConstHeap    heap,
                            u32                 optFlag);
/* Please see man pages for details 
  
  
  
  
  
                


*/
    bool                CheckForMBlockHeap(
                            const void*         memBlock,
                            ConstHeap    heap,
                            u32                 optFlag);

#endif



/*  

*/
/*  

*/


}}} // namespace nn::fnd::detail

#endif // __cplusplus

/* NN_OS_HEAP_H_ */
#endif

