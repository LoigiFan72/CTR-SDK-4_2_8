/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailHeapCommonImpl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_DETAIL_FND_DETAIL_HEAPCOMMONIMPL_H_
#define NN_FND_DETAIL_FND_DETAIL_HEAPCOMMONIMPL_H_

#include <nn/types.h>

#ifdef __cplusplus

namespace nn { namespace fnd { namespace detail {
//

/* =======================================================================
    Type Definitions
   ======================================================================== */

typedef s32 NNSiIntPtr;     // signed integer type mutually convertible with void* pointer
typedef u32 NNSiUIntPtr;    // unsigned integer type mutually convertible with void* pointer


/* ========================================================================
    Macro Functions
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndRoundUp
  Description:  Rounds up to align with specified alignment.
  Arguments:    value:      target data
                alignment:  alignment value
  Returns:      Returns a value that has been rounded up to the specified alignment value.
 *---------------------------------------------------------------------------


*/
#define NNSi_FndRoundUp(value, alignment) \
    (((value) + (alignment-1)) & ~(alignment-1))

#define NNSi_FndRoundUpPtr(ptr, alignment) \
    ((void*)NNSi_FndRoundUp(NNSiGetUIntPtr(ptr), alignment))

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndRoundDown
  Description:  Rounds down to align for a specified alignment value.
  Arguments:    value:      target data
                alignment:  alignment value
  Returns:      Returns a value that has been rounded down to the specified alignment.
 *---------------------------------------------------------------------------


*/
#define NNSi_FndRoundDown(value, alignment) \
    ((value) & ~(alignment-1))

#define NNSi_FndRoundDownPtr(ptr, alignment) \
    ((void*)NNSi_FndRoundDown(NNSiGetUIntPtr(ptr), alignment))

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndGetBitValue
  Description:  Gets a value at a specific bit position.
  Arguments:    data:  Data that contains the bit data to be gotten.
                st:    Start bit (start from 0)
                bits:  Number of bits (maximum 31)
  Returns:      Returns the value at a specific bit position.
 *---------------------------------------------------------------------------


*/
#define     NNSi_FndGetBitValue(data, st, bits) \
    (((data) >>(st)) & ((1 <<(bits)) -1))

/*---------------------------------------------------------------------------*
  Name:         NNSi_FndSetBitValue
  Description:  Sets a value at a specific bit position.
  Arguments:    data:  Variable that holds the bit data that is to be set
                st:    Start bit (start from 0)
                bits:  Number of bits (maximum 31)
                val:   Bit data to set.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
#define     NNSi_FndSetBitValue(data, st, bits, val)                        \
                do                                                          \
                {                                                           \
                    u32 maskBits = (u32)((1 <<(bits)) -1);                   \
                    u32 newVal = (val) & maskBits; /* mask for safety */    \
                    (void)(maskBits <<= st);                                 \
                    (data) &= ~maskBits; /* clears the region to set */        \
                    (data) |= newVal <<(st);                                 \
                } while(false);


/* ========================================================================
    Inline Functions
   ======================================================================== */

/* ------------------------------------------------------------------------
    Pointer operations
   ------------------------------------------------------------------------ */

inline NNSiUIntPtr
NNSiGetUIntPtr(const void* ptr)
{
    return (NNSiUIntPtr)ptr;
}

inline u32
GetOffsetFromPtr(const void* start, const void* end)
{
    return NNSiGetUIntPtr(end) - NNSiGetUIntPtr(start);
}

inline void*
AddU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}

inline const void*
AddU32ToCPtr(const void* ptr, u32 val)
{
    return (const void*)( NNSiGetUIntPtr(ptr) + val );
}

inline void*
SubU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) - val );
}

inline const void*
SubU32ToCPtr(const void* ptr, u32 val)
{
    return (const void*)( NNSiGetUIntPtr(ptr) - val );
}

inline int
ComparePtr(const void* a, const void* b)
{
    const u8* wa = reinterpret_cast<const u8*>(a);
    const u8* wb = reinterpret_cast<const u8*>(b);

    return wa - wb;
}


inline u16
GetOptForHeap(const NNSiFndHeapHead* pHeapHd)
{
    return (u16)NNSi_FndGetBitValue(pHeapHd->attribute, 0, 8);
}

inline void
SetOptForHeap(
    NNSiFndHeapHead*    pHeapHd,
    u16                 optFlag
)
{
    NNSi_FndSetBitValue(pHeapHd->attribute, 0, 8, optFlag);
}


/* ------------------------------------------------------------------------
    Fill memory
   ------------------------------------------------------------------------ */

   
//  Tentative memset
inline void MI_CpuFill32(void* dest, u32 data, u32 size)
{
    u32* pDest = reinterpret_cast<u32*>(dest);
    NN_TASSERT_(((u32)pDest & 0xfffffffc) == (u32)pDest);  // dest should be 4-byte aligned
    NN_TASSERT_((size & 0xfffffffc) == size);  // size should be 4-byte aligned
    for(int i = 0; i < size / 4; ++i)
    {
        pDest[i] = data;
    }
}
   
inline void
FillAllocMemory(
    NNSiFndHeapHead*    pHeapHd,
    void*               address,
    u32                 size
)
{

    if (GetOptForHeap(pHeapHd) & NN_OS_HEAP_OPT_0_CLEAR)
    {
        MI_CpuFill32(address, 0, size);
    }
    else
    {
        #if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT)
            if (GetOptForHeap(pHeapHd) & NN_OS_HEAP_OPT_DEBUG_FILL)
            {
                MI_CpuFill32(address, GetFillValForHeap(NN_OS_HEAP_FILL_ALLOC), size);
            }
        #endif
    }
}

#if defined(NN_SWITCH_DISABLE_DEBUG_PRINT)
    #define FillFreeMemory(pHeapHd, address, size)  ((void) 0)
#else
    inline void
    FillFreeMemory(
        NNSiFndHeapHead*    pHeapHd,
        void*               address,
        u32                 size
    )
    {
        if (GetOptForHeap(pHeapHd) & NN_OS_HEAP_OPT_DEBUG_FILL)
        {
            MI_CpuFill32(address, GetFillValForHeap(NN_OS_HEAP_FILL_FREE), size);
        }
    }
#endif

#if defined(NN_SWITCH_DISABLE_DEBUG_PRINT)
    #define FillNoUseMemory(pHeapHd, address, size)  ((void) 0)
#else
    inline void
    FillNoUseMemory(
        NNSiFndHeapHead*    pHeapHd,
        void*               address,
        u32                 size
    )
    {
        if (GetOptForHeap(pHeapHd) & NN_OS_HEAP_OPT_DEBUG_FILL)
        {
            MI_CpuFill32(address, GetFillValForHeap(NN_OS_HEAP_FILL_NOUSE), size);
        }
    }
#endif


/* =======================================================================
    Function Prototypes
   ======================================================================== */

void        NNSi_FndInitHeapHead(
                NNSiFndHeapHead*    pHeapHd,
                u32                 signature,
                void*               heapStart,
                void*               heapEnd,
                u16                 optFlag);

void        NNSi_FndFinalizeHeap(
                NNSiFndHeapHead* pHeapHd);

void        NNSi_FndDumpHeapHead(
                NNSiFndHeapHead const* pHeapHd);

//

}}} // namespace nn::os

#endif // __cplusplus

/* NN_OS_HEAPCOMMONI_H_ */
#endif /* NN_OS_OS_HEAPCOMMONIMPL_H_ */
