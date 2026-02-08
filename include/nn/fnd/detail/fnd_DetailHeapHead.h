/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailHeapHead.h

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

#ifndef NN_FND_DETAIL_FND_DETAIL_HEAP_HEAD_H_
#define NN_FND_DETAIL_FND_DETAIL_HEAP_HEAD_H_

#ifdef __cplusplus

namespace nn{ namespace fnd{ namespace detail {

    /*---------------------------------------------------------------------------*
      Name:         NNSFndLink
      Description:  Node structure for doubly linked list. Stores this structure as a member of the structure that you want linked to the list structure.
                    
     *---------------------------------------------------------------------------
*/
    typedef struct
    {
        void*       prevObject;     // Pointer to the previous linked object.
        void*       nextObject;     // Pointer to the next linked object.

    } NNSFndLink;


    /*---------------------------------------------------------------------------*
      Name:         NNSFndList
      Description:  Doubly-linked list structure.
     *---------------------------------------------------------------------------
*/
    typedef struct 
    {
        void*       headObject;     // Pointer to the object linked to the top of the list.
        void*       tailObject;     // Pointer to the object linked to the end of the list.
        u16         numObjects;     // Number of objects linked in the list.
        u16         offset;         // Offset for NNSFndLink type structure member.

    } NNSFndList;

    // Header information for memory
    struct NNSiFndExpHeapMBlockHead
    {
        u16                         signature;      // Signature
        u16                         attribute;      // Attribute
                                                    // [8:groupID]
                                                    // [7:alignment]
                                                    // [1:temporary flag]

        u32                         blockSize;      // Block size (data area only)

        NNSiFndExpHeapMBlockHead*   pMBHeadPrev;    // Previous block
        NNSiFndExpHeapMBlockHead*   pMBHeadNext;    // Next block
    };

    // Memory list
    struct NNSiFndExpMBlockList
    {
        NNSiFndExpHeapMBlockHead*   head;   // Pointer to memory linked to the start of the list
        NNSiFndExpHeapMBlockHead*   tail;   // Pointer to memory linked to the end of the list
    };

    // Header information for expanded heap
    struct NNSiFndExpHeapHead
    {
        NNSiFndExpMBlockList        mbFreeList;     // Free list
        NNSiFndExpMBlockList        mbUsedList;     // Used list

        u16                         groupID;        // Current group ID (lower 8 bits only)
        u16                         feature;        // Attribute
        bool                        reuse;          // Configures whether to reuse gap regions that occur during alignment.
        NN_PADDING3;
    };

    struct ExpHeapImpl
    {
        ExpHeapImpl() : signature(0) {}

        u32             signature;

        NNSFndLink      link;
        NNSFndList      childList;

        void*           heapStart;      // Heap start address
        void*           heapEnd;        // Heap end (+1) address

        u32             attribute;      // Attribute
                                        // [8:Option flag]
        NNSiFndExpHeapHead nnsiFndExpHeapHead;
    };

}}} // namespace nn::fnd::detail

#endif // __cplusplus

/* NN_FND_DETAIL_FND_DETAIL_HEAP_HEAD_H_ */
#endif

