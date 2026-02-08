/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ContinuationIterator.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/assert.h>
#include <nn/os/os_ContinuationIterator.h>

namespace nn { namespace os {

void Context::Initialize(void *pc, uptr sp)
{
    m_Registers.regs[8] = sp;
    m_Registers.regs[9] = reinterpret_cast<bit32>(pc);
}

asm bit32 Context::SwitchImpl(bit32 /* r0 */, Registers* /* from */, Registers* /* to */)
{
    ARM
    
    stmia r1, {r4-r11,sp,lr}
    ldmia r2, {r4-r11,sp,pc}
}

asm bit32 Context::SwitchImpl(bit32 /* r0 */, bit32 /* r1 */, Registers* /* from */, Registers* /* to */)
{
    ARM
    
    stmia r2, {r4-r11,sp,lr}
    ldmia r3, {r4-r11,sp,pc}
}

asm void Context::SwitchImpl(bit32 /* r0 */, Registers* /* to */)
{
    ARM
    
    ldmia r1, {r4-r11,sp,pc}
}

asm bit32 Context::CallOnOtherStackImpl(bit32 /* r0: arg0 */, void* /* r1: f */, Registers* /* r2: regs */, uptr /* r3: SP */)
{
    PRESERVE8
    ARM
    
    stmia r2, {r4-r11,sp,lr}
    mov   sp, r3  // Move stack
    mov   r4, r2  // r4 = regs save 
    blx   r1      // f(arg)
    ldmia r4, {r4-r11,sp,pc}
}

void ContinuationIteratorBase::Initialize(void *stackBottom)
{
    bit32 sp = reinterpret_cast<uptr>(stackBottom);
    
    // Save the context save region on the stack
    //   As a matter of fact, isn't necessary for the main context to be allocated for each task?
    #define AllocateFromStack(T, sp) reinterpret_cast<T*>((sp) -= sizeof(T))
        this->m_MainContext = AllocateFromStack(Context, sp);
        this->m_IteratorContext = AllocateFromStack(Context, sp);
    #undef AllocateFromStack
    
    // Create iterator context
    // Set to start from RunIterator
    m_IteratorContext->Initialize(reinterpret_cast<void*>(&RunIterator), sp);
}

void ContinuationIteratorBase::RunIterator(ContinuationIteratorBase* p)
{
    // Execute with the iterator context
    
    // Execute user-defined function
    p->m_Result = p->Run();
    
    // After the user-defined function finishes executing, switches to the main context
    // Since the iterator context is no longer necessary, call a function that does not save it
    // In r0, enter false as the END mark
    p->m_MainContext->Switch(false);
    
    // Do not return here
    NN_TPANIC_("No more element.");
}

Result ContinuationIteratorBase::Yield()
{
    // Execute with the iterator context
    
    // Switch to main context
    // In r0, enter true to instruct to continue
    // Save iterator context so that it can return
    m_MainContext->SwitchFrom(true, *m_IteratorContext);
    
    // Since the result is saved in m_Result with the main context, return this with the iterator context
    // 
    return m_Result;
}

bool ContinuationIteratorBase::MoveNext(Result result)
{
    // Save Result in m_Result
    this->m_Result = result;
    
    // Recover the iterator context with r0 as this
    // ("this" is used only when passed to RunIterator when first starting)
    if (m_IteratorContext->SwitchFrom(reinterpret_cast<bit32>(this), *m_MainContext))
    {
        // If true is returned, there is still more
        if (result.IsFailure())
        {
            // Even though Failure was returned in the iterator context Yield, it is invalid to return to this context again
            // 
            NN_TPANIC_("Iterator is already invalid.");
        }
        return true;
    }
    else
    {
        // End iterate
        return false;
    }
}

}}
