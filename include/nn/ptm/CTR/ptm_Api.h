/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ptm_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46687 $
 *---------------------------------------------------------------------------*/

#ifndef NN_PTM_CTR_PTM_API_H_
#define NN_PTM_CTR_PTM_API_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/fnd.h>

namespace nn {
namespace ptm {
namespace CTR {

    /* Please see man pages for details 
    
    
                

    
    */
    Result Initialize();

    /* Please see man pages for details 
    

    
    */
    Result Finalize();

    /* Please see man pages for details 
        
        
    */

    /* Please see man pages for details 
        

        
        
    */
    Result RegisterAlarmEvent(nn::os::Event &event);

    /* Please see man pages for details 
        

        

        
        
        
        
        
    */
    Result SetRtcAlarm(nn::fnd::DateTime datetime);

    /* Please see man pages for details 
        
        
        
        
        

        

        
        
    */
    Result GetRtcAlarm(nn::fnd::DateTime *pDatetime);

    /* Please see man pages for details 
        
        
        
        

        
    */
    Result CancelRtcAlarm();

    /*  

*/

    /* Please see man pages for details 
        
        
    */

    /* Please see man pages for details 
        
    */
    enum AdapterState
    {
        ADAPTERSTATE_NOCONNECTED,       //
        ADAPTERSTATE_CONNECTED          //
    };

    /* Please see man pages for details 
        
    */
    enum BatteryChargeState
    {
        BATTERYCHARGESTATE_NOCHARGING,   //
        BATTERYCHARGESTATE_CHARGING      //
    };

    /* Please see man pages for details 
        
    */
    enum BatteryLevel
    {
        BATTERYLEVEL_0,                 //
        BATTERYLEVEL_1,                 //
        BATTERYLEVEL_2,                 //
        BATTERYLEVEL_3,                 //
        BATTERYLEVEL_4,                 //
        BATTERYLEVEL_5,                 //

        BATTERYLEVEL_MIN = BATTERYLEVEL_0,  //
        BATTERYLEVEL_MAX = BATTERYLEVEL_5   //
    };

    /* Please see man pages for details 
        
    
        
    */
    enum HardwareType
    {
        HARDWARE_TYPE_DEVICE,           //
        HARDWARE_TYPE_BOARD,            //
        HARDWARE_TYPE_DEBUGGER          //
    };

    /* Please see man pages for details 
        

        
    */
    AdapterState    GetAdapterState();

    /* Please see man pages for details 
        

        
    */
    BatteryLevel    GetBatteryLevel();

    /* Please see man pages for details 
        

        
    */
    BatteryChargeState GetBatteryChargeState();

    /*  

*/
} // end of namespace CTR
} // end of namespace ptm
} // end of namespace nn


#endif  // ifndef NN_PTM_CTR_PTM_API_H_
