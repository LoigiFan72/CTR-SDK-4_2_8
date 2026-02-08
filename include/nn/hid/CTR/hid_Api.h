/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_CTR_HID_API_H_
#define NN_HID_CTR_HID_API_H_

/* Please see man pages for details 
    
*/

#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_Pad.h>
#include <nn/hid/CTR/hid_TouchPanel.h>
#include <nn/hid/CTR/hid_Accelerometer.h>
#include <nn/hid/CTR/hid_Gyroscope.h>
#include <nn/hid/CTR/hid_DebugPad.h>

namespace nn {
namespace hid {
namespace CTR {

namespace detail{
    typedef enum _IPCPortType
    {
        PORT_SPVR = 0,
        PORT_USER,
        NUM_OF_IPC_PORTS
    } IPCPortType;
}

namespace{
    const char *const PORT_NAME_SPVR = "hid:SPVR";
    const char *const PORT_NAME_USER = "hid:USER";
}


/* Please see man pages for details 
  

  
*/

/* Please see man pages for details 


    
    
    

    
    
    

*/
nn::Result    Initialize( );

/* Please see man pages for details 




*/
void          Finalize( );

/*  

*/

/* Please see man pages for details 


              



*/
Pad&          GetPad( );

/* Please see man pages for details 


              



*/
TouchPanel&   GetTouchPanel();

/* Please see man pages for details 


              



*/
Accelerometer& GetAccelerometer();
/* Please see man pages for details 


              



*/
Gyroscope&    GetGyroscope();


/* Please see man pages for details 


              



*/
DebugPad&      GetDebugPad();

} // namespace CTR {
} // namespace hid {
} // namespace nn {



#endif //   #ifndef NN_HID_CTR_HID_API_H_
