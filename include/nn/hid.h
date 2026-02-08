/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_H_
#define NN_HID_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
           
*/

#if defined(NN_PLATFORM_CTR)

    #ifdef  __cplusplus
        #include <nn/hid/CTR/hid_Result.h>
        #include <nn/hid/CTR/hid_Api.h>
        #include <nn/hid/CTR/hid_Pad.h>
        #include <nn/hid/CTR/hid_TouchPanel.h>
        #include <nn/hid/CTR/hid_Accelerometer.h>
        #include <nn/hid/CTR/hid_PadReader.h>
        #include <nn/hid/CTR/hid_TouchPanelReader.h>
        #include <nn/hid/CTR/hid_AccelerometerReader.h>
        #include <nn/hid/CTR/hid_GyroscopeReader.h>
        #include <nn/hid/CTR/hid_DebugPadReader.h>

        namespace nn {
            namespace hid {
                using namespace nn::hid::CTR;
            }
        }
    #endif // __cplusplus

#else
    #error no platform selected
#endif

#endif  // ifndef NN_HID_H_
