/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_Accelerometer.h

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
#ifndef NN_HID_CTR_HID_ACCELEROMETER_H_
#define NN_HID_CTR_HID_ACCELEROMETER_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_HidBase.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>

namespace nn {
namespace hid {
namespace CTR {
/* Please see man pages for details 
    

    

*/
class Accelerometer : public HidBase
{
private:
    Accelerometer() {}
    ~Accelerometer() {}

    friend class HidDevices;
};
} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif  // #ifndef NN_HID_CTR_HID_ACCELEROMETER_H_
