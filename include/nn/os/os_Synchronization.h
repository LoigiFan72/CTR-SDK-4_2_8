/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Synchronization.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47812 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_SYNCHRONIZATION_H_
#define NN_OS_OS_SYNCHRONIZATION_H_

#include <nn/types.h>
#include <nn/Result.h>
#include <nn/os/os_HandleObject.h>
#include <nn/os/os_ErrorHandlerSelect.h>
#include <nn/fnd/fnd_TimeSpan.h>

#include <nn/util/util_Result.h>

/* Please see man pages for details 
    
    
*/
#define NN_OS_WAIT_INFINITE                 -1

#ifdef __cplusplus

namespace nn{ namespace os{

const s64 WAIT_INFINITE = NN_OS_WAIT_INFINITE;

/* Please see man pages for details 
    

    

            
            
            
            
            

            
            

            
            
*/
class WaitObject : public HandleObject
{
public:
    
    /* Please see man pages for details 
        

        
    */
    void WaitOne();

    /* Please see man pages for details 
        

        

        
    */
    bool WaitOne(nn::fnd::TimeSpan timeout);
    
    /* Please see man pages for details 
        

        
        

        
    */
    static void WaitAll(WaitObject* objs[], s32 numObjects);

    /* Please see man pages for details 
        

        
        

        

        
    */
    static bool WaitAll(WaitObject* objs[], s32 numObjects, nn::fnd::TimeSpan timeout);
    
    // 
    /* Please see man pages for details 
        

        
        

        
    */
    static s32 WaitAny(WaitObject* objs[], s32 numObjects);

    /* Please see man pages for details 
        

        
        

        

        
    */
    static s32 WaitAny(WaitObject* objs[], s32 numObjects, nn::fnd::TimeSpan timeout);
    
protected:

    // Prohibit individual instantiation
    WaitObject() {}
    ~WaitObject() {}
    
private:
    
    nn::Result WaitOneImpl(s64 nanoSecondsTimeout);
    static nn::Result WaitMultiple(s32* pOut, WaitObject* objs[], s32 numObjects, bool waitAll, s64 nanoSecondsTimeout);
    
};

/* Please see man pages for details 
    

    
            

*/
class InterruptEvent : public WaitObject
{
protected:
    InterruptEvent() {}
    ~InterruptEvent() {}
};

// In-line implementation

inline nn::Result WaitObject::WaitOneImpl(s64 nanoSecondsTimeout)
{
    s32 dummy;
    Handle handle = GetHandle();
    return nn::svc::WaitSynchronization(&dummy, &handle, 1, false, nanoSecondsTimeout);
}

inline void WaitObject::WaitOne()
{
    NN_OS_ERROR_IF_FAILED(WaitOneImpl(WAIT_INFINITE));
}

inline bool WaitObject::WaitOne(nn::fnd::TimeSpan timeout)
{
    nn::Result result = WaitOneImpl(timeout.GetNanoSeconds());
    NN_OS_ERROR_IF_FAILED(result);
    return result.GetDescription() != nn::Result::DESCRIPTION_TIMEOUT;
}

inline bool WaitObject::WaitAll(WaitObject* objs[], s32 numObjects, nn::fnd::TimeSpan timeout)
{
    s32 dummy;
    nn::Result result = WaitMultiple(&dummy, objs, numObjects, true, timeout.GetNanoSeconds());
    NN_OS_ERROR_IF_FAILED(result);
    return result.GetDescription() != nn::Result::DESCRIPTION_TIMEOUT;
}

inline void WaitObject::WaitAll(WaitObject* objs[], s32 numObjects)
{
    s32 dummy;
    NN_OS_ERROR_IF_FAILED(WaitMultiple(&dummy, objs, numObjects, true, WAIT_INFINITE));
}

inline s32 WaitObject::WaitAny(WaitObject* objs[], s32 numObjects, nn::fnd::TimeSpan timeout)
{
    s32 ret;
    nn::Result result = WaitMultiple(&ret, objs, numObjects, false, timeout.GetNanoSeconds());
    NN_OS_ERROR_IF_FAILED(result);
    return (result.GetDescription() == nn::Result::DESCRIPTION_TIMEOUT) ? -1 : ret;
}

inline s32 WaitObject::WaitAny(WaitObject* objs[], s32 numObjects)
{
    s32 ret;
    NN_OS_ERROR_IF_FAILED(WaitMultiple(&ret, objs, numObjects, false, WAIT_INFINITE));
    return ret;
}

}} // namespace nn::os

#endif // __cplusplus

// Below is the C declaration
#include <nn/util/detail/util_CLibImpl.h>

NN_UTIL_DETAIL_CLIBIMPL_DEFINE_ABSTRACT_BUFFER_CLASS(nnosWaitObject)

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosWaitObjectWaitOne(nnosWaitObject* p, s64 nanoSecondsTimeout);

/* Please see man pages for details 
  
*/
NN_EXTERN_C bool nnosWaitObjectWaitAll(nnosWaitObject* objs[], s32 numObjects, s64 nanoSecondsTimeout);

/* Please see man pages for details 
  
*/
NN_EXTERN_C s32 nnosWaitObjectWaitAny(nnosWaitObject* objs[], s32 numObjects, s64 nanoSecondsTimeout);

/* NN_OS_SYNCHRONIZATION_H_ */
#endif /* NN_OS_OS_SYNCHRONIZATION_H_ */
