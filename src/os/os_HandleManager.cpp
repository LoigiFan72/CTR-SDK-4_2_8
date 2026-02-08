/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_HandleManager.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/os/os_HandleManager.h>


#include <new>
using namespace nn::os;


void nnosHandleManagerAttachEventHandle(nnosEvent* p, nnHandle handle)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    HandleManager::AttachHandle(pEvent, handle);
}

void nnosHandleManagerDetachEventHandle(nnosEvent* p)
{
    Event* pEvent = reinterpret_cast<Event*>(p);
    HandleManager::DetachHandle(pEvent);
}

void nnosHandleManagerAttachMutexHandle(nnosMutex* p, nnHandle handle)
{
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    HandleManager::AttachHandle(pMutex, handle);
}

void nnosHandleManagerDetachMutexHandle(nnosMutex* p)
{
    Mutex* pMutex = reinterpret_cast<Mutex*>(p);
    HandleManager::DetachHandle(pMutex);
}

void nnosHandleManagerAttachSemaphoreHandle(nnosSemaphore* p, nnHandle handle)
{
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    HandleManager::AttachHandle(pSemaphore, handle);
}

void nnosHandleManagerDetachSemaphoreHandle(nnosSemaphore* p)
{
    Semaphore* pSemaphore = reinterpret_cast<Semaphore*>(p);
    HandleManager::DetachHandle(pSemaphore);
}

void nnosHandleManagerAttachTimerHandle(nnosTimer* p, nnHandle handle)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    HandleManager::AttachHandle(pTimer, handle);
}

void nnosHandleManagerDetachTimerHandle(nnosTimer* p)
{
    Timer* pTimer = reinterpret_cast<Timer*>(p);
    HandleManager::DetachHandle(pTimer);
}

#if NN_PLATFORM_HAS_MMU
void nnosHandleManagerAttachSharedMemoryHandle(nnosSharedMemoryBlock* p, nnHandle handle)
{
    SharedMemoryBlock* pSharedMemoryBlock = reinterpret_cast<SharedMemoryBlock*>(p);
    HandleManager::AttachHandle(pSharedMemoryBlock, handle);
}

void nnosHandleManagerDetachSharedMemoryHandle(nnosSharedMemoryBlock* p)
{
    SharedMemoryBlock* pSharedMemoryBlock = reinterpret_cast<SharedMemoryBlock*>(p);
    HandleManager::DetachHandle(pSharedMemoryBlock);
}
#endif  // if NN_PLATFORM_HAS_MMU
