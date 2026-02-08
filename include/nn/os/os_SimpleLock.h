/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_SimpleLock.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_SIMPLELOCK_H_
#define NN_OS_OS_SIMPLELOCK_H_

#include <nn/os/os_WaitableCounter.h>
#include <nn/util/detail/util_ScopedLockImpl.h>
#include <nn/util/util_NonCopyable.h>

#ifdef __cplusplus

namespace nn { namespace os {

class SimpleLock : private nn::util::NonCopyable<SimpleLock>
{
public:
    class ScopedLock;

private:
    nn::os::WaitableCounter m_Counter;

public:
    SimpleLock()  {}
    ~SimpleLock() {}

    void Initialize();
    void Finalize() {}

    void Lock();
    bool TryLock();
    void Unlock();

    bool IsLocked() const
    {
        return (*m_Counter < 0);
    }

private:
    void LockImpl();
};

NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(SimpleLock, Lock(), Unlock());

}} // namespace nn::os

#endif // __cplusplus


#endif  // ifndef NN_OS_OS_SIMPLELOCK_H_
