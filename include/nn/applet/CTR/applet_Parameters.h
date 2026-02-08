/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     applet_Parameters.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_APPLET_CTR_APPLET_PARAMETERS_H_
#define NN_APPLET_CTR_APPLET_PARAMETERS_H_

#include <nn/fnd.h>
#include <nn/gx/CTR/gx_Lcd.h>

namespace nn{
namespace applet{
namespace CTR{

    enum Attribute
    {
        //Applet type
        TYPE_APP                        = (0x0<<0), //000 Application
        TYPE_APPLIB                     = (0x1<<0), //001 Library applet
        TYPE_SYS                        = (0x2<<0), //010 System applet
        TYPE_SYSLIB                     = (0x3<<0), //011 System library applet
        TYPE_RESIDENT                   = (0x4<<0), //100 Resident applet
        TYPE_MASK                       = (0x7<<0), //111 (Applet type mask)

        //Setting GPU rights
        MANUAL_GPU_RIGHT                = (1<<3),   // Assign/release manually

        //Setting DSP rights
        MANUAL_DSP_RIGHT                = (1<<4)    // Assign/release manually
    };
    const bit32 DEFAULT_APPLET_ATTRIBUTE = (TYPE_APP);

    enum DisplayBufferMode
    {
        FORMAT_R8G8B8A8                 = 0,
        FORMAT_R8G8B8                   = 1,
        FORMAT_R5G6B5                   = 2,
        FORMAT_R5G5B5A1                 = 3,
        FORAMT_R4G4B4A4                 = 4,
        FORMAT_UNIMPORTABLE             = 0xFFFFFFFF
    };

    /* Please see man pages for details 
      

             

             
    */
    enum HomeButtonState
    {
        HOME_BUTTON_NONE                = 0, //
        HOME_BUTTON_SINGLE_PRESSED      = 1, //
        HOME_BUTTON_DOUBLE_PRESSED      = 2  //
    };

    enum ShutdownState
    {
        SHUTDOWN_STATE_NONE             = 0, // No shutdown notification has been received
        SHUTDOWN_STATE_RECEIVED         = 1  // A shutdown notification has been received
    };

    enum PowerButtonState
    {
        POWER_BUTTON_STATE_NONE         = 0, // Not pressed
        POWER_BUTTON_STATE_CLICK        = 1  // Clicked
    };

    enum OrderToCloseState
    {
        ORDER_TO_CLOSE_STATE_NONE       = 0, // No close request
        ORDER_TO_CLOSE_STATE_RECEIVED   = 1  // Close request received
    };

    /* Please see man pages for details 
      

             
    */
    enum SleepNotificationState
    {
        NOTIFY_NONE                     = 0, //
        NOTIFY_SLEEP_QUERY              = 1, //
        NOTIFY_SLEEP_ACCEPT             = 2, //
        NOTIFY_SLEEP_REJECT             = 3, //
        NOTIFY_SLEEP_ACCEPTED           = 4, //
        NOTIFY_AWAKE                    = 5  //
    };

    enum AppJumpType
    {
        JUMP_OTHER                      = 0, // Jump to another application
        JUMP_CALLER                     = 1, // Jump to the original caller
        JUMP_SELF                       = 2  // Jump to self
    };

    enum AppletPos
    {
        POS_APP                         = 0, // Application
        POS_APPLIB                      = 1, // Library applet started by the application
        POS_SYS                         = 2, // System
        POS_SYSLIB                      = 3, // Library applet started by the library
        POS_RESIDENT                    = 4, // Resident applet
        POS_MAX,

        POS_NONE                        = -1 // No position
    };

    /* Please see man pages for details 
      

             
    */
    enum WakeupState
    {
        // Timeout
        WAKEUP_BY_TIMEOUT               = -1,  //

        //Went sleeping
        WAKEUP_SKIP                     = 0,  //

        //Wake-up due to a regular request > The waking application resumes execution
        WAKEUP_TO_START                 = 1,  //
        //Wake-up due to shutdown > The waking application resumes execution
        WAKEUP_BY_EXIT                  = 2,  //
        // Wake-up due to interrupt > The waking application resumes execution
        WAKEUP_BY_PAUSE                 = 3,  //
        //Wake-up due to cancel notification > The waking application exits.
        WAKEUP_BY_CANCEL                = 4,  //
        //Wake-up due to cancel notification > The waking application exits > Also make other applets/applications exit if necessary
        WAKEUP_BY_CANCELALL             = 5,  //
        // Wake-up due to POWER Button click > Jump to the sleep recommend screen, and the system menu is the only applet that could possibly wake up
        WAKEUP_BY_POWER_BUTTON_CLICK    = 6,  //
        //Wake-up in order to jump to the HOME Menu > The waking application executes JumpToHomeMenu().
        WAKEUP_TO_JUMP_HOME             = 7,  //
        //Wake-up in order to jump to the application > The waking application executes LeaveHomeMenu().
        WAKEUP_TO_JUMP_APPLICATION      = 8,  //
        //Wake-up to start application > The waking application executes StartApplication().
        WAKEUP_TO_LAUNCH_APPLICATION    = 9, //

        WAKEUP_STATE_MAX                = 63
    };

    /* Please see man pages for details 
      

             
             

             
             

             
             
    */

    enum QueryReply
    {
        REPLY_REJECT                    = 0, //
        REPLY_ACCEPT                    = 1, //
        REPLY_LATER                     = 2  //
    };


    enum UsableAppletId
    {
        APPLET_ID_NONE                  = 0,    // Unused Buttons
        //
        // application
        APPLICATION_APPLET_ID           = 0x300, // application

        // library applet
        APPLIB_APPLET_ID                = 0x400, // library applet

        // resident applet
        ERRDISP_APPLET_ID               = 0x501, // ERROR DISPLAY

        APPLET_ID_MAX
    };


    enum SleepCheckOnEnableSleep
    {
        SLEEP_IF_SHELL_CLOSED           = true,
        NO_SHELL_CHECK                  = false
    };
    enum ReplyRejectOnDisableSleep
    {
        REPLY_REJECT_IF_LATER           = true,
        NO_REPLY_REJECT                 = false
    };

    enum ParentalControlsScene
    {
        PARENTAL_CONTROLS_TOP          = 0,
        PARENTAL_CONTROLS_COPPACS      = 1
    };
    enum DataManagementScene
    {
        DATA_MANAGEMENT_TOP            = 0, // Do not use this value.
        DATA_MANAGEMENT_STREETPASS     = 1
    };

    enum MsetScene
    {
        MSET_INTERNET_SETTING_TOP           = 110,
        MSET_PARENTAL_CONTROLS_TOP          = 111,
        MSET_PARENTAL_CONTROLS_COPPACS      = 112,
        MSET_DATA_MANAGEMENT_TOP            = 113, // Do not use this value.
        MSET_DATA_MANAGEMENT_STREETPASS     = 117,

        MSET_SCENE_INVALID_VALUE            = 0xFFFFFFFF
    };

    /* Please see man pages for details 
      
    */
    typedef bit32                                  AppletId;

    /* Please see man pages for details 
      
    */
    typedef bit32                                   AppletAttr;

    typedef nn::applet::CTR::DisplayBufferMode      AppletDisplayBufferMode;

    typedef nn::applet::CTR::HomeButtonState        AppletHomeButtonState;

    typedef nn::applet::CTR::SleepNotificationState AppletSleepNotificationState;

    typedef nn::applet::CTR::ShutdownState          AppletShutdownState;

    typedef nn::applet::CTR::PowerButtonState       AppletPowerButtonState;

    typedef nn::applet::CTR::OrderToCloseState      AppletOrderToCloseState;

    typedef nn::applet::CTR::WakeupState            AppletWakeupState;

    typedef nn::applet::CTR::QueryReply             AppletQueryReply;

    typedef nn::applet::CTR::AppJumpType            AppletAppJumpType;

    typedef nn::applet::CTR::ParentalControlsScene  AppletParentalControlsScene;

    typedef nn::applet::CTR::DataManagementScene    AppletDataManagementScene;

    typedef nn::applet::CTR::MsetScene              AppletMsetScene;

    // Invalid handle
    extern const nn::Handle                         HANDLE_NONE;

    // Time
    /* Please see man pages for details 
      
             
    */
    const nn::fnd::TimeSpan WAIT_INFINITE           = nn::fnd::TimeSpan::FromNanoSeconds((s64)-1);
    /* Please see man pages for details 
      
             
    */
    const nn::fnd::TimeSpan NO_WAIT                 = 0;

    // Invalid applet ID
    const bit32 INVALID_ID                          = 0;

    // Invalid program ID
    const bit64 INVALID_PROGRAM_ID                  = 0xffffffffffffffffull;

    // ----- Group of callbacks
    /* Please see man pages for details 
      
    */
    typedef bool (*AppletHomeButtonCallback)( uptr arg, bool isActive, nn::applet::CTR::HomeButtonState state );
    /* Please see man pages for details 
      
    */
    typedef void (*AppletMessageCallback)( uptr arg, AppletId senderId, u8 pParam[], size_t paramSize, nn::Handle handle );

    // Memory request
    typedef void (*AppletRequestMemoryCallback)( uptr arg, size_t size, nn::Handle* pHandle );
    // Finalize memory request
    typedef void (*AppletReleaseMemoryCallback)( uptr arg );

    // DSP sleep
    typedef void (*AppletDspSleepCallback)( uptr arg );
    // DSP wakeup
    typedef void (*AppletDspWakeUpCallback)( uptr arg );

    /* Please see man pages for details 
      
    */
    typedef AppletQueryReply (*AppletSleepQueryCallback)( uptr arg );
    /* Please see man pages for details 
      
    */
    typedef void (*AppletSleepCanceledCallback)( uptr arg );
    /* Please see man pages for details 
      
    */
    typedef void (*AppletAwakeCallback)( uptr arg );

    /* Please see man pages for details 
      
    */
    typedef void (*AppletShutdownCallback)( uptr arg );
    /* Please see man pages for details 
      
    */
    typedef void (*AppletCloseAppletCallback)( uptr arg ); // Actually this is shared by all applets.

    /* Please see man pages for details 
      
    */
    typedef void (*AppletPowerButtonCallback)( uptr arg );

    /* Please see man pages for details 
      
    */
    typedef void (*AppletTransitionCallback)( uptr arg );

    /* Please see man pages for details 
      
    */
    typedef void (*AppletCloseCallback)( uptr arg );

}
}
}

/* Please see man pages for details 
    
    
*/
#define NN_APPLET_PORT_NAME_USER        "APT:U"  // User Application

/* Please see man pages for details 
    
*/
#define NN_APPLET_MAX_APPLET_NUM        5

#define NN_APPLET_PARAMETER_MAX         4096    //
#define NN_APPLET_PARAM_BUF_SIZE        768
#define NN_APPLET_HMAC_BUF_SIZE         32

// Includes padding so that the size (924KB) of the buffer used to store captured images can be used to store texture data.
#define NN_APPLET_CAPTURE_BUF_SIZE      (256 * (NN_GX_DISPLAY0_HEIGHT + NN_GX_DISPLAY1_HEIGHT + 512) * 3)

// Attributes
#define NN_APPLET_TYPE_APP                      (nn::applet::CTR::TYPE_APP)
#define NN_APPLET_TYPE_APPLIB                   (nn::applet::CTR::TYPE_APPLIB)
#define NN_APPLET_TYPE_SYS                      (nn::applet::CTR::TYPE_SYS)
#define NN_APPLET_TYPE_SYSLIB                   (nn::applet::CTR::TYPE_SYSLIB)
#define NN_APPLET_TYPE_RESIDENT                 (nn::applet::CTR::TYPE_RESIDENT)
#define NN_APPLET_TYPE_MASK                     (nn::applet::CTR::TYPE_MASK)

#define NN_APPLET_MANUAL_GPU_RIGHT              (nn::applet::CTR::MANUAL_GPU_RIGHT)
#define NN_APPLET_MANUAL_DSP_RIGHT              (nn::applet::CTR::MANUAL_DSP_RIGHT)

// HOME Button
#define NN_APPLET_HOME_BUTTON_NONE              (nn::applet::CTR::HOME_BUTTON_NONE)
#define NN_APPLET_HOME_BUTTON_SINGLE_PRESSED    (nn::applet::CTR::HOME_BUTTON_SINGLE_PRESSED)
#define NN_APPLET_HOME_BUTTON_DOUBLE_PRESSED    (nn::applet::CTR::HOME_BUTTON_DOUBLE_PRESSED)

// System notifications
#define NN_APPLET_NOTIFY_NONE                   (nn::applet::NOTIFY_NONE)
#define NN_APPLET_NOTIFY_SLEEP_QUERY            (nn::applet::NOTIFY_SLEEP_QUERY)
#define NN_APPLET_NOTIFY_SLEEP_ACCEPT           (nn::applet::NOTIFY_SLEEP_ACCEPT)
#define NN_APPLET_NOTIFY_SLEEP_REJECT           (nn::applet::NOTIFY_SLEEP_REJECT)
#define NN_APPLET_NOTIFY_AWAKE                  (nn::applet::NOTIFY_AWAKE)

// Applet type
#define NN_APPLET_POS_SYSLIB                    (nn::applet::CTR::POS_SYSLIB)
#define NN_APPLET_POS_SYS                       (nn::applet::CTR::POS_SYS)
#define NN_APPLET_POS_APP                       (nn::applet::CTR::POS_APP)
#define NN_APPLET_POS_APPLIB                    (nn::applet::CTR::POS_APPLIB)
#define NN_APPLET_POS_RESIDENT                  (nn::applet::CTR::POS_RESIDENT)
#define NN_APPLET_POS_MAX                       (nn::applet::CTR::POS_MAX)

// Responses to sleep queries
#define NN_APPLET_REPLY_ACCEPT                  (nn::applet::REPLY_ACCEPT)
#define NN_APPLET_REPLY_REJECT                  (nn::applet::REPLY_REJECT)
#define NN_APPLET_REPLY_LATER                   (nn::applet::REPLY_LATER)

//
#define NN_APPLET_NO_PREPARATION                (nn::applet::NO_PREPARATION)
#define NN_APPLET_PREPARED_TO_LAUNCH_APP        (nn::applet::PREPARED_TO_LAUNCH_APP)
#define NN_APPLET_PREPARED_TO_CLOSE_APP         (nn::applet::PREPARED_TO_CLOSE_APP)
#define NN_APPLET_PREPARED_TO_LAUNCH_APPLIB     (nn::applet::PREPARED_TO_LAUNCH_APPLIB)
#define NN_APPLET_PREPARED_TO_CLOSE_APPLIB      (nn::applet::PREPARED_TO_CLOSE_APPLIB)
#define NN_APPLET_PREPARED_TO_LAUNCH_SYS        (nn::applet::PREPARED_TO_LAUNCH_SYS)
#define NN_APPLET_PREPARED_TO_CLOSE_SYS         (nn::applet::PREPARED_TO_CLOSE_SYS)
#define NN_APPLET_PREPARED_TO_LAUNCH_SYSLIB     (nn::applet::PREPARED_TO_LAUNCH_SYSLIB)
#define NN_APPLET_PREPARED_TO_CLOSE_SYSLIB      (nn::applet::PREPARED_TO_CLOSE_SYSLIB)
#define NN_APPLET_PREPARED_TO_LAUNCH_RESIDENT   (nn::applet::PREPARED_TO_LAUNCH_RESIDENT)
#define NN_APPLET_PREPARED_TO_LEAVE_RESIDENT    (nn::applet::PREPARED_TO_LEAVE_RESIDENT)
#define NN_APPLET_PREPARED_TO_DO_HOMEMENU       (nn::applet::PREPARED_TO_DO_HOMEMENU)
#define NN_APPLET_PREPARED_TO_LEAVE_HOMEMENU    (nn::applet::PREPARED_TO_LEAVE_HOMEMENU)

// Applet ID
#define NN_APPLET_APPLICATION_APPLET_ID         (nn::applet::CTR::APPLICATION_APPLET_ID)
#define NN_APPLET_ERRDISP_APPLET_ID             (nn::applet::CTR::ERRDISP_APPLET_ID)

// Invalid handle
#define NN_APPLET_HANDLE_NONE                   (nn::applet::CTR::HANDLE_NONE)

// Time
#define NN_APPLET_WAIT_INFINITE                 (nn::applet::CTR::WAIT_INFINITE)
#define NN_APPLET_NO_WAIT                       (nn::applet::CTR::NO_WAIT)

// Invalid applet ID
#define NN_APPLET_INVALID_ID                    (nn::applet::CTR::INVALID_ID)
// Invalid program ID
#define NN_APPLET_INVALID_PROGRAM_ID            (nn::applet::CTR::INVALID_PROGRAM_ID)

#define NN_APPLET_DEFAULT_APPLET_ATTRIBUTE      (nn::applet::CTR::DEFAULT_APPLET_ATTRIBUTE)

/*  

*/


using nn::applet::CTR::AppletId;
using nn::applet::CTR::AppletAttr;

using nn::applet::CTR::AppletHomeButtonState;
using nn::applet::CTR::AppletSleepNotificationState;

using nn::applet::CTR::AppletHomeButtonCallback;
using nn::applet::CTR::AppletMessageCallback;
using nn::applet::CTR::AppletRequestMemoryCallback;
using nn::applet::CTR::AppletReleaseMemoryCallback;
using nn::applet::CTR::AppletDspSleepCallback;
using nn::applet::CTR::AppletDspWakeUpCallback;
using nn::applet::CTR::AppletSleepQueryCallback;
using nn::applet::CTR::AppletSleepCanceledCallback;
using nn::applet::CTR::AppletAwakeCallback;
using nn::applet::CTR::AppletShutdownCallback;
using nn::applet::CTR::AppletCloseAppletCallback;
using nn::applet::CTR::AppletPowerButtonCallback;

using nn::applet::CTR::AppletWakeupState;
using nn::applet::CTR::AppletQueryReply;


#endif  // ifndef NN_APPLET_CTR_APPLET_PARAMETERS_H_
