/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_HidBase.h

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

#ifndef NN_HID_CTR_HID_HIDBASE_H_
#define NN_HID_CTR_HID_HIDBASE_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/fnd/fnd_Timespan.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_Event.h>

namespace nn {
namespace hid {
namespace CTR {


/* Please see man pages for details 
    
*/
class HidBase : public nn::os::EventBase
{
protected:
    HidBase() : nn::os::EventBase() {}
    ~HidBase() {}

private:
    uptr            m_pResource;

public:
    /* Please see man pages for details 
      
      
    */
    void WaitSampling( );

    /* Please see man pages for details 
      

      
      
      
    */
    bool WaitSampling(nn::fnd::TimeSpan timeout);

    /* Please see man pages for details 
        

        
        

        
        
    */
    static s32 WaitSamplingAny(HidBase* devices[], s32 numDevices);

    /* Please see man pages for details 
        

        
        

        

        
        
        
    */
    static s32 WaitSamplingAny(HidBase* devices[], s32 numDevices, nn::fnd::TimeSpan timeout);

    uptr            GetResource();
    void            SetResource(uptr resource);
};



// inline definitions
inline void HidBase::WaitSampling( )
{
    WaitOne();
}

inline bool HidBase::WaitSampling(nn::fnd::TimeSpan timeout)
{
    return WaitOne(timeout);
}


inline s32 HidBase::WaitSamplingAny(HidBase* devices[], s32 numDevices)
{
    return nn::os::WaitObject::WaitAny(reinterpret_cast<nn::os::WaitObject**>(devices), numDevices);
}

inline s32 HidBase::WaitSamplingAny(HidBase* devices[], s32 numDevices, nn::fnd::TimeSpan timeout)
{
    return nn::os::WaitObject::WaitAny(reinterpret_cast<nn::os::WaitObject**>(devices), numDevices, timeout);
}

inline uptr HidBase::GetResource()
{
    return m_pResource;
}

inline void HidBase::SetResource(uptr resource)
{
    m_pResource = resource;
}

} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif  // #ifndef NN_HID_CTR_HID_HIDBASE_H_
