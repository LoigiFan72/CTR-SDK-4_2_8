/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_HandleObject.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
  

  
*/

#ifndef NN_OS_OS_HANDLEOBJECT_H_
#define NN_OS_OS_HANDLEOBJECT_H_

#include <nn/Result.h>
#include <nn/Handle.h>
#include <nn/svc.h>

#include <nn/assert.h>
#include <nn/util/util_NonCopyable.h>

#ifdef __cplusplus

namespace nn {
namespace os {

class HandleManager;

/* Please see man pages for details 
    
    
    
    
    
    
    
    

*/
class HandleObject : private nn::util::NonCopyable<HandleObject>
{
public:

    /* Please see man pages for details 
    

    
    */
    nn::Handle GetHandle() const { return m_Handle; }

    /* Please see man pages for details 
    

    
    */
    bool IsValid() const { return m_Handle.IsValid(); }

protected:

    /* Please see man pages for details 
    

                  
    */
#pragma push
#pragma diag_suppress 2530
    HandleObject() {}
#pragma pop

    /* Please see man pages for details 
    

                  
    */
    ~HandleObject();

    /* Please see man pages for details 
    

    

    
    */
    void SetHandle(nn::Handle handle);

    /* Please see man pages for details 
    

    
    */
    void Close();

    void Finalize();
    
    void ClearHandle();

private:

    nn::Handle m_Handle;
    friend class HandleManager;

};

// In-line implementation

inline void HandleObject::Close()
{
    if (IsValid())
    {
        nn::svc::CloseHandle(m_Handle);
        m_Handle = Handle();
    }
}

inline HandleObject::~HandleObject()
{
    Close();
}

inline void HandleObject::Finalize()
{
    Close();
}

inline void HandleObject::SetHandle(nn::Handle handle)
{
    NN_TASSERTMSG_(!IsValid(), "current handle(=%08X) is active\n", m_Handle.GetPrintableBits());
    NN_TASSERT_(handle.IsValid());
    
    m_Handle = handle;
}

inline void HandleObject::ClearHandle()
{
    m_Handle = Handle();
}

}   // end of namespace os
}   // end of namespace nn

#endif // __cplusplus

#endif  // ifndef NN_OS_OS_HANDLEOBJECT_H_
