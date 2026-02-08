/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Interlocked.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/config.h>
#include <nn/fnd/ARMv6/fnd_Interlocked.h>

#include <nn/hw/ARM/code32.h>

namespace nn 
{
    namespace fnd 
    {
        namespace ARMv6 
        {

asm s32 Interlocked::CompareAndSwap(s32* pTarget NN_IS_UNUSED_VAR, s32 comp NN_IS_UNUSED_VAR, s32 swap NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(1)
    ldrex   r3, [r0]        // Loads the *pTarget value to r3
    cmp     r3, r1          // Compares r3 to value.
    bne     NN_FSYM(2)      // Because branching and clrex cannot conditionally execute

    // When comparison succeeds
    strex   r3, r2, [r0]    // Writes swap to *pTarget

    cmp     r3, #0          // Did writing succeed?
    bne     NN_BSYM(1)      // Start from the beginning if it failed

    mov     r0, r1          // Return value is comp because comparison succeeded
    bx      lr

    // When comparison fails
NN_LSYM(2)
    clrex                   // Clear exclusive monitoring
    mov     r0, r3          // Return value is the *pTarget value
    bx      lr
}

asm s32 Interlocked::Swap(s32* pTarget NN_IS_UNUSED_VAR, s32 value NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(2)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    strex   r3, r1, [r0]        // Writes the value value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(2)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value immediately before writing succeeded
    bx      lr
}

asm s32 Interlocked::Increment(s32* pTarget NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(3)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    add     r2, r2, #1          // Increment r2
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(3)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::Decrement(s32* pTarget NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(4)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    sub     r2, r2, #1          // Decrement r2
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(4)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::Add(s32* pTarget NN_IS_UNUSED_VAR, s32 value NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(5)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    add     r2, r2, r1          // Adds value to r2
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(5)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::Substract(s32* pTarget NN_IS_UNUSED_VAR, s32 value NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(6)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    sub     r2, r2, r1          // Subtracts value from r2
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(6)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::BitwiseOr(s32* pTarget NN_IS_UNUSED_VAR, s32 value NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(7)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    orr     r2, r2, r1          // OR of r2 and value
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(7)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::BitwiseAnd(s32* pTarget NN_IS_UNUSED_VAR, s32 value NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(8)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    and     r2, r2, r1          // AND of r2 and value
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(8)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::BitwiseXor(s32* pTarget NN_IS_UNUSED_VAR, s32 value NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(9)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    eor     r2, r2, r1          // XOR of r2 and value
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(9)          // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

asm s32 Interlocked::BitwiseNot(s32* pTarget NN_IS_UNUSED_VAR)
{
    PRESERVE8

NN_LSYM(10)
    ldrex   r2, [r0]            // Loads the *pTarget value to r2
    mvn     r2, r2              // NOT r2
    strex   r3, r2, [r0]        // Writes the r2 value to *pTarget

    cmp     r3, #0              // Did writing succeed?
    bne     NN_BSYM(10)         // Start from the beginning if it failed

    mov     r0, r2              // Return value is the *pTarget value when writing succeeds
    bx      lr
}

u64 Interlocked::CompareAndSwap(u64* pTarget, const u64& comp, u64 swap)
{
    while (true)
    {
        u64 x = __ldrexd(pTarget);
        if (x == comp)
        {
            if (__strexd(swap, pTarget) == 0)
            {
                return comp;
            }
        }
        else
        {
            __clrex();
            return x;
        }
    }
}

        }
    }
}

