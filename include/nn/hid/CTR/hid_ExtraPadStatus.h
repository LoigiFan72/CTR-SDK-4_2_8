/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_ExtraPadStatus.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_CTR_EXTRA_PAD_STATUS_H_
#define NN_HID_CTR_EXTRA_PAD_STATUS_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>

namespace nn{
namespace hid{
namespace CTR{


/* Please see man pages for details */
struct ExtraPadStatus{
    /* Please see man pages for details */
    AnalogStickStatus stick;

    /* Please see man pages for details */
    AnalogStickStatus extraStick;

    /* Please see man pages for details */
    bit32   hold;
    /* Please see man pages for details */
    bit32   trigger;
    /* Please see man pages for details */
    bit32   release;

    /* Please see man pages for details */
    u8      batteryLevel;

    /* Please see man pages for details */
    bool   isConnected;

    NN_PADDING2;
};

}
}
}


#endif /* HID_EXTRAPADSTATUS_H_ */
