/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_CriticalSection.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/assert.h>
#include <nn/config.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/fnd/fnd_Interlocked.h>
#include <nn/os/os_Timer.h>

//---------------------------------------------------------------------------

using namespace nn;
using namespace nn::fnd;
using namespace nn::svc;
using namespace nn::os;
using namespace nn::util;

namespace nn{ namespace os{


void CriticalSection::Initialize()
{
    m_Lock.Initialize();
    m_ThreadUniqueValue = GetInvalidThreadUniqueValue();
    m_LockCount         = 0;
}

void CriticalSection::Enter()
{
    NN_TASSERT_(IsInitialized());

    // If own thread has not entered critical section, attempt to enter it.
    // 

    if( ! LockedByCurrentThread() )
    {
        m_Lock.Lock();
        OnLocked();
    }

    ++this->m_LockCount;
}

bool CriticalSection::TryEnter()
{
    NN_TASSERT_(IsInitialized());

    // If own thread has not entered critical section, attempt to enter it.
    // 

    if( ! LockedByCurrentThread() )
    {
        if( ! m_Lock.TryLock() )
        {
            return false;
        }

        OnLocked();
    }

    ++this->m_LockCount;
    return true;
}

void CriticalSection::Leave()
{
    NN_TASSERT_(IsInitialized());
    NN_TASSERTMSG_(LockedByCurrentThread() && m_LockCount > 0, "CriticalSection is not entered on the current thread.");

    if (--this->m_LockCount == 0)
    {
        NN_TASSERTMSG_( m_Lock.IsLocked(), "CriticalSection is not entered.");
        
        // Clear ID of thread currently getting critical section.
        m_ThreadUniqueValue = GetInvalidThreadUniqueValue();

        m_Lock.Unlock();
    }
}


}} // namespace nn::os

#include <new>

using namespace nn::os;

extern "C" {

void nnosCriticalSectionInitialize(nnosCriticalSection* p)
{
    new (p) CriticalSection(nn::WithInitialize());
}

bool nnosCriticalSectionTryInitialize(nnosCriticalSection* p)
{
    new (p) CriticalSection(nn::WithInitialize());
    CriticalSection* pCriticalSection = reinterpret_cast<CriticalSection*>(p);
    Result result = pCriticalSection->TryInitialize();
    return result.IsSuccess();
}

void nnosCriticalSectionEnter(nnosCriticalSection* p)
{
    CriticalSection* pCriticalSection = reinterpret_cast<CriticalSection*>(p);
    pCriticalSection->Enter();
}

bool nnosCriticalSectionTryEnter(nnosCriticalSection* p)
{
    CriticalSection* pCriticalSection = reinterpret_cast<CriticalSection*>(p);
    return pCriticalSection->TryEnter();
}

void nnosCriticalSectionLeave(nnosCriticalSection* p)
{
    CriticalSection* pCriticalSection = reinterpret_cast<CriticalSection*>(p);
    pCriticalSection->Leave();
}

void nnosCriticalSectionFinalize(nnosCriticalSection* p)
{
    CriticalSection* pCriticalSection = reinterpret_cast<CriticalSection*>(p);
    pCriticalSection->~CriticalSection();
}

}
