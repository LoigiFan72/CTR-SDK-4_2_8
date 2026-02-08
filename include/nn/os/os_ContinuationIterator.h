/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ContinuationIterator.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_OS_OS_CONTINUATIONITERATOR_H_
#define NN_OS_OS_CONTINUATIONITERATOR_H_

#ifdef __cplusplus

#include <nn/Result.h>
#include <nn/WithInitialize.h>
#include <csetjmp>

namespace nn { namespace os {

class Context
{
private:

    struct Registers
    {
        bit32 regs[10];
    } m_Registers;
    
    static void SwitchImpl(bit32 r0, Registers* to);
    static bit32 SwitchImpl(bit32 r0, Registers* from, Registers* to);
    static bit32 SwitchImpl(bit32 r0, bit32 r1, Registers* from, Registers* to);
    static bit32 CallOnOtherStackImpl(bit32 arg0, void* f, Registers* regs, uptr sp);
    
public:

    void Initialize(void* pc, uptr sp);
    void Switch(bit32 r0 = 0) { SwitchImpl(r0, &this->m_Registers); }
    bit32 SwitchFrom(bit32 r0, Context& currentContext) { return SwitchImpl(r0, &currentContext.m_Registers, &this->m_Registers); }
    bit32 SwitchFrom(bit32 r0, bit32 r1, Context& currentContext) { return SwitchImpl(r0, r1, &currentContext.m_Registers, &this->m_Registers); }
    
    static bit32 CallOnOtherStack(nn::os::Context& context, uptr sp, void* f) { return CallOnOtherStack(context, sp, f, 0); }
    static bit32 CallOnOtherStack(nn::os::Context& context, uptr sp, void* f, bit32 arg0) { return CallOnOtherStackImpl(arg0, f, &context.m_Registers, sp); }
    static bit32 CallOnOtherStack(uptr sp, void* f) { return CallOnOtherStack(sp, f, 0); }
    static bit32 CallOnOtherStack(uptr sp, void* f, bit32 arg0) { Context c; return CallOnOtherStack(c, sp, f, arg0); }

};

class ContinuationIteratorBase
{
private:
    
    Context* m_MainContext;
    Context* m_IteratorContext;
    Result m_Result;
    
    static void RunIterator(ContinuationIteratorBase* p);
    
protected:
    
    // With this iterator, override the executing process.
    virtual Result Run() = 0;
    
    virtual ~ContinuationIteratorBase() {}
    
public:

    // Specify stack with stackBottom and initialize
    void Initialize(void* stackBottom);
    
    // Return the process to MoveNext.
    // Can be called only in Run().
    // When the return is Failure, cannot call Yield again.
    Result Yield();
    
    // Executes until the next Yield or Run() ends.
    // When returns with Yield, returns true; when Run() ends, returns false.
    // When something other than ResultSuccess is specified in result, notification is made of returning forcibly with Run().
    // 
    bool MoveNext(Result result = nn::ResultSuccess());
    
    // After MoveNext returns false, gets the Run() execution result.
    // If this value is referenced before MoveNext returns false, operations will be undefined.
    Result GetResult() const { return m_Result; }
    
};

template <class T>
class ContinuationIterator : public ContinuationIteratorBase
{
private:

    T m_Value;
    
public:
    
    // Sets the iterator value.
    // Can be called only in Run().
    void SetCurrent(const T& value) { m_Value = value; }
    
    // Returns the iterator value.
    // Can be called only in Run().
    Result YieldReturn(const T& value) { SetCurrent(value); return Yield(); }

    // Gets the iterator value.
    const T& GetCurrent() const { return m_Value; }
    
};

}}

#endif

#endif
