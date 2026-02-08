/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Synchronization.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_Synchronization.h>
#include <nn/os/os_Result.h>
#include <nn/assert.h>
#include <nn/Handle.h>
#include <nn/svc/svc_Stub.h>
#include <nn/util/util_StaticAssert.h>
//---------------------------------------------------------------------------

using namespace nn;
//using namespace nn::svc;

namespace nn{ namespace os{

// TODO: Must move to ARM
namespace {

    struct WaitMultipleObjectsArgs {
        s32* pOut;
        WaitObject** objs;
        s32 numHandles;
        bool waitAll;
        u8 padding[3];
        s64* timeout;
    };

    nn::Result WaitMultipleImpl(WaitMultipleObjectsArgs* args, nn::Handle* handles)
    {
        for (int i = 0; i < args->numHandles; ++i)
        {
            handles[i] = args->objs[i]->GetHandle();
        }
        return nn::svc::WaitSynchronization(args->pOut, handles, args->numHandles, args->waitAll, *args->timeout);
    }

    NN_STATIC_ASSERT(sizeof(nn::Handle) == 4);
    asm nn::Result WaitMultipleImplWithAlloca(WaitMultipleObjectsArgs*, s32, nn::Result (*)(WaitMultipleObjectsArgs*, nn::Handle*))
    {
        ARM
        PRESERVE8
        
        push  {lr}
        
        bics  r3, r1, #1
        addne r1, r1, #1 // Add 1 if r1 is odd (for 8-byte alignment)
        
        mov   r3, r1, LSL #2
        
        sub   sp, sp, r3
        mov   r1, sp
        
        push  {r3}
        
        blx   r2
        
        pop   {r3}
        add   sp, sp, r3
        
        pop   {pc}
    }

}

nn::Result WaitObject::WaitMultiple(s32* pOut, WaitObject* objs[], s32 numHandles, bool waitAll, s64 timeout)
{
    // TORIAEZU: If there are about 10 it is usually enough.
    const s32 STATIC_ALLOCATE_SIZE = 10;
    if (numHandles <= STATIC_ALLOCATE_SIZE)
    {
        nn::Handle handles[STATIC_ALLOCATE_SIZE];
        for (int i = 0; i < numHandles; ++i)
        {
            handles[i] = objs[i]->GetHandle();
        }
        return nn::svc::WaitSynchronization(pOut, handles, numHandles, waitAll, timeout);
    }
    else
    {
        WaitMultipleObjectsArgs args;
        args.pOut = pOut;
        args.objs = objs;
        args.numHandles = numHandles;
        args.waitAll = waitAll;
        args.timeout = &timeout;
        return WaitMultipleImplWithAlloca(&args, numHandles, &WaitMultipleImpl);
    }
}

}} // namespace nn::os


using namespace nn::os;

extern "C" {

bool nnosWaitObjectWaitOne(nnosWaitObject* p, s64 nanoSecondsTimeout)
{
    WaitObject* pWaitObject = reinterpret_cast<WaitObject*>(p);
    return pWaitObject->WaitOne(nn::fnd::TimeSpan::FromNanoSeconds(nanoSecondsTimeout));
}

bool nnosWaitObjectWaitAll(nnosWaitObject* objs[], s32 numObjects, s64 nanoSecondsTimeout)
{
    WaitObject** pWaitObjects = reinterpret_cast<WaitObject**>(objs);
    return WaitObject::WaitAll(pWaitObjects, numObjects, nn::fnd::TimeSpan::FromNanoSeconds(nanoSecondsTimeout));
}

s32 nnosWaitObjectWaitAny(nnosWaitObject* objs[], s32 numObjects, s64 nanoSecondsTimeout)
{
    WaitObject** pWaitObjects = reinterpret_cast<WaitObject**>(objs);
    return WaitObject::WaitAny(pWaitObjects, numObjects, nn::fnd::TimeSpan::FromNanoSeconds(nanoSecondsTimeout));
}

}
