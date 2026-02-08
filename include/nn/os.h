/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47268 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_H_
#define NN_OS_H_

/* Please see man pages for details 
    

    
    
*/

/* Please see man pages for details 
    
                
*/

/* Please see man pages for details 
    
                

    
*/

#ifdef __cplusplus
    #include <nn/os/os_SvcTypes.autogen.h>
#endif

#include <nn/os/os_Alarm.h>
#include <nn/os/os_AutoStackManager.h>
#include <nn/os/os_BlockingQueue.h>
#include <nn/os/os_CriticalSection.h>
#include <nn/os/os_Default.h>
#include <nn/os/os_ExceptionHandlerSelect.h>
#include <nn/os/os_HandleObject.h>
#include <nn/os/os_Initialize.h>
#include <nn/os/os_InterCoreBlockingQueue.h>
#include <nn/os/os_InterCoreCriticalSection.h>
#include <nn/os/os_InterCoreLightSemaphore.h>
#include <nn/os/os_LightBarrier.h>
#include <nn/os/os_LightEvent.h>
#include <nn/os/os_LightSemaphore.h>
#include <nn/os/os_LockPolicy.h>
#include <nn/os/os_ManagedThread.h>
#include <nn/os/os_Memory.h>
#include <nn/os/os_MemoryBarrierSelect.h>
#include <nn/os/os_MemoryBlock.h>
#include <nn/os/os_MemoryBlockBase.h>
#include <nn/os/os_MemoryTypes.h>
#include <nn/os/os_Result.h>
#include <nn/os/os_SharedMemory.h>
#include <nn/os/os_SimpleAutoStackManager.h>
#include <nn/os/os_SimpleAutoStackManagerBase.h>
#include <nn/os/os_SpinWaitSelect.h>
#include <nn/os/os_StackMemory.h>
#include <nn/os/os_StackMemoryAutoStackManager.h>
#include <nn/os/os_StackMemoryBlock.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_Thread.h>
#include <nn/os/os_ThreadLocalStorage.h>
#include <nn/os/os_ThreadPool.h>
#include <nn/os/os_Tick.h>
#include <nn/os/os_TransferMemoryBlock.h>
#include <nn/os/os_Types.h>
#include <nn/os/os_WaitableCounter.h>
#include <nn/os/os_EnvironmentSelect.h>

/* Please see man pages for details 
  
  
  
*/


/*  

*/

#include <nn/os/os_Event.h>
#include <nn/os/os_Mutex.h>
#include <nn/os/os_Semaphore.h>

#if defined(NN_PLATFORM_CTR)
    #include <nn/os/CTR/os_CpuControl.h>
#else
    #error no platform selected
#endif


#endif /* NN_OS_H_ */
