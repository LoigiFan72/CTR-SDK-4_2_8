/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Task.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
            
            
            
            
    

    
*/

#ifndef NN_OS_OS_TASK_H_
#define NN_OS_OS_TASK_H_

#include <nn/os/os_Synchronization.h>
#include <nn/fnd/fnd_Queue.h>
#include <nn/util/util_NonCopyable.h>

#ifdef __cplusplus

namespace nn { namespace os {


/*
    

    

*/
class ITask
{
public:
    virtual void Invoke() = 0;
    virtual ~ITask() {}
};

/*
    

    
*/
class QueueableTask : public nn::fnd::IntrusiveQueue<QueueableTask>::Item, public ITask
{
public:
    /*
        

        
     */
    virtual void Invoke() = 0;
};

/*
    

    
*/
class QueueableWaitTask : private QueueableTask
{
public:
    /* Please see man pages for details 
        

        
     */
    virtual nn::os::WaitObject* GetWaitObject() = 0;
    
    QueueableTask* AsNonWaitableTask() { return this; }
    
    friend class IWaitTaskInvoker;
};

class ITaskInvoker
{
public:
    virtual void AddTask(QueueableTask* task) = 0;
    virtual ~ITaskInvoker() {}
    // TODO: Priority settings, etc.
};

class IWaitTaskInvoker : public ITaskInvoker
{
public:
    virtual void AddWaitTask(QueueableWaitTask* task) = 0;
protected:
    static QueueableWaitTask* GetWaitTaskPointer(QueueableTask* p) { return static_cast<QueueableWaitTask*>(p); }
};

}}

#endif

#endif // NN_OS_OS_THREADPOOL_H_
