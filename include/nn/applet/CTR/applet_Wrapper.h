/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     applet_Wrapper.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_APPLET_CTR_APPLET_WRAPPER_H_
#define NN_APPLET_CTR_APPLET_WRAPPER_H_

#include <nn/os.h>
#include <nn/applet/CTR/applet_Parameters.h>
#include <nn/applet/CTR/applet_API.h>

namespace nn {
namespace applet {
namespace CTR {
namespace detail {

    AppletWakeupState WaitForStarting( AppletId* pSenderId=NULL, u8* pParam=NULL, size_t paramSize=0, s32* pReadLen=NULL,
                                       nn::Handle *pHandle=NULL, nn::fnd::TimeSpan span=NN_APPLET_WAIT_INFINITE );
    bool ProcessHomeButton(void);
}
}
}
}

namespace nn {
namespace applet {
namespace CTR {
/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
     */
    AppletHomeButtonState GetHomeButtonState(void);

    /* Please see man pages for details 
        
     */
    void ClearHomeButtonState(void);

    /* Please see man pages for details 
        
        
     */
    bool IsExpectedToProcessHomeButton(void);

    /* Please see man pages for details 
        
        
     */
    inline bool ProcessHomeButton(void)
    {
        return detail::ProcessHomeButton();
    }

    /* Please see man pages for details 
        
     */
    void ProcessHomeButtonAndWait();
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
     */
    bool ProcessPowerButton(void);

    /* Please see man pages for details 
        
     */
    void ProcessPowerButtonAndWait();
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
     */
    bool IsExpectedToReplySleepQuery(void);

    /* Please see man pages for details 
        
        
     */
    void ReplySleepQuery( AppletQueryReply reply );

    /* Please see man pages for details 
        
        
     */
    void EnableSleep( bool isSleepCheck=nn::applet::CTR::SLEEP_IF_SHELL_CLOSED );

    /* Please see man pages for details 
        
        
                    
     */
    void DisableSleep( bool isReplyReject=nn::applet::CTR::REPLY_REJECT_IF_LATER );

    /* Please see man pages for details 
        

                    
                    

         
     */
    bool IsEnableSleep();
/*  

*/


/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
        
     */
    void SetHomeButtonCallback( AppletHomeButtonCallback callback, uptr arg=0 );

    /* Please see man pages for details 
        
        
        
     */
    void SetPowerButtonCallback( AppletPowerButtonCallback callback, uptr arg=0 );

    /* Please see man pages for details 
        
        
        
     */
    void SetSleepQueryCallback( AppletSleepQueryCallback callback, uptr arg=0 );

    /* Please see man pages for details 
        
        
        
     */
    void SetSleepCanceledCallback( AppletSleepCanceledCallback callback, uptr arg=0 );

    /* Please see man pages for details 
        
        
        
     */
    void SetAwakeCallback( AppletAwakeCallback callback, uptr arg=0 );
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

        
        
        
        
        
        

        
     */
    inline AppletWakeupState WaitForStarting( AppletId* pSenderId=NULL, u8* pParam=NULL, size_t paramSize=0, s32* pReadLen=NULL,
                                              nn::Handle *pHandle=NULL, nn::fnd::TimeSpan timeout=NN_APPLET_WAIT_INFINITE )
    {
        return detail::WaitForStarting( pSenderId, pParam, paramSize, pReadLen, pHandle, timeout );
    }
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
        
     */
    bool IsAppletPreloaded( AppletId id );

    /* Please see man pages for details 
        
        
     */
    void WaitForAppletPreloaded( AppletId id );
/*  

*/
}
}
}

#endif  // ifndef NN_APPLET_CTR_APPLET_WRAPPER_H_
