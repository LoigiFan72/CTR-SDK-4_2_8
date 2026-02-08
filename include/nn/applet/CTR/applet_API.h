/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     applet_API.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46369 $
 *---------------------------------------------------------------------------*/

#ifndef NN_APPLET_CTR_APPLET_API_H_
#define NN_APPLET_CTR_APPLET_API_H_

#include <nn/os.h>
#include <nn/applet/CTR/applet_Parameters.h>
#include <nn/applet/CTR/applet_AppJump.h>

#include <nn/gx.h>
#include <nn/hid.h>
#include <nn/fs/fs_Parameters.h>

/* Please see man pages for details 
    
*/
namespace nn {
namespace applet {
namespace CTR {
namespace detail {

    //---- Initialize/finalize
    Result Initialize( AppletAttr appletAttr = DEFAULT_APPLET_ATTRIBUTE );
    void   Enable(bool isSleepEnabled=true);

    bool   IsRegistered( AppletId appletId );
    bool   WaitForRegister( AppletId appletId, nn::fnd::TimeSpan span );
    bool   IsActive(void);
    void   SetActive(void);
    void   SetInactive(void);

    //================
    // GPU rights
    bool   IsGpuRightGiven(void);

    //================
    // Attach sharedMemory
    void AttachTransferMemoryHandle( os::TransferMemoryBlock* transferMemory, nn::Handle handle, size_t size, bit32 otherPermission );

    //================
    // Send user message to applet
    Result SendMessage( AppletId receiverId, const u8* pParam, size_t paramSize, nn::Handle handle=NN_APPLET_HANDLE_NONE, nn::fnd::TimeSpan timeout=WAIT_INFINITE );
    Result TrySendMessage( AppletId receiverId, const u8* pParam, size_t paramSize, nn::Handle handle=NN_APPLET_HANDLE_NONE );


    // Power button click notification
    AppletPowerButtonState GetPowerButtonState(void);
    void ClearPowerButtonState(void);

    // Termination request
    AppletOrderToCloseState GetOrderToCloseState(void);
    void ClearOrderToCloseState(void);

    //================
    // Preload library applet
    Result PreloadLibraryApplet( AppletId id );

    // Start library applet
    Result PrepareToStartLibraryApplet( AppletId id );
    Result StartLibraryApplet( AppletId id, const u8* pParam=NULL, size_t paramSize=0, Handle handle=NN_APPLET_HANDLE_NONE );

    // Cancel startup
    Result CancelLibraryApplet( bool isApplicationEnd=false );
    Result CancelLibraryAppletIfRegistered( bool isApplicationEnd=false, AppletWakeupState *pWakeupState=NULL );

    // Quit the application
    Result PrepareToCloseApplication( bool isCancelPreload=false );
    Result CloseApplication( const u8* pParam=NULL, size_t paramSize=0, Handle handle=NN_APPLET_HANDLE_NONE );

    // Restart
    Result RestartApplication( const void* pParam, size_t paramSize );
    bool   GetStartupArgument( void* pParam, size_t paramSize = NN_APPLET_PARAM_BUF_SIZE );

    //================
    // Receive argument
    bool ReceiveDeliverArg( u8 pParam[], size_t paramSize, u8 pHmacBuf[], size_t hmacBufSize, bit32* pUniqueId );
    bool ReceiveDeliverArg( u8 pParam[], u8 pHmacBuf[], bit32* pUniqueId );
    AppletWakeupState GetInitialWakeupState(void);

    //================
    Result GetSharedFont(Handle* pHandle, uptr* pAddr);
    Result GetWirelessRebootInfo(u8* pInfo, size_t size);
    Result Wrap(void* pWrappedBuffer, const void* pData, size_t dataSize, s32 idOffset, size_t idSize);
    Result Unwrap(void* pData, const void* pWrapped, size_t wrappedSize, s32 idOffset, size_t idSize);
    Result Wrap1(void* pWrappedBuffer, const void* pData, size_t dataSize, s32 idOffset, size_t idSize);
    Result Unwrap1(void* pData, const void* pWrapped, size_t wrappedSize, s32 idOffset, size_t idSize);
}
}
}
}

namespace nn {
namespace applet {
namespace CTR {

    using namespace nn::applet::CTR;

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

        
        
     */
    inline Result Initialize(AppletAttr appletAttr = NN_APPLET_DEFAULT_APPLET_ATTRIBUTE )
    {
        return detail::Initialize( appletAttr );
    }
    /* Please see man pages for details 
        

        
        
     */
    inline void Enable(bool isSleepEnabled=true)
    {
        detail::Enable(isSleepEnabled);
    }
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
        

        
        
        
    */
    inline bool ReceiveDeliverArg( u8 pParam[], size_t paramSize, u8 pHmacBuf[], size_t hmacBufSize, bit32* pUniqueId )
    {
        return detail::ReceiveDeliverArg( pParam, paramSize, pHmacBuf, hmacBufSize, pUniqueId );
    }
    inline bool ReceiveDeliverArg( u8 pParam[], u8 pHmacBuf[], bit32* pUniqueId )
    {
        return detail::ReceiveDeliverArg( pParam, pHmacBuf, pUniqueId );
    }

    /* Please see man pages for details 
        
        
    */
    inline AppletWakeupState GetInitialWakeupState(void)
    {
        return detail::GetInitialWakeupState();
    }

    /* Please see man pages for details 
        
        
        
     */
    inline bool IsRegistered( AppletId appletId )
    {
        return detail::IsRegistered( appletId );
    }

    /* Please see man pages for details 
        
        
     */
    inline bool IsActive(void)
    {
        return detail::IsActive();
    }

    /* Please see man pages for details 
        

                    
     */
    inline void SetActive(void)
    {
        detail::SetActive();
    }

    /* Please see man pages for details 
        

                    
    */
    inline void SetInactive(void)
    {
        detail::SetInactive();
    }

    /* Please see man pages for details 
        

        
     */
    bool IsInitialized();
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
        
        
     */
    inline bool WaitForRegister( AppletId appletId, nn::fnd::TimeSpan span = NN_APPLET_WAIT_INFINITE )
    {
        return detail::WaitForRegister( appletId, span );
    }
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

        
     */
    inline bool IsGpuRightGiven(void)
    {
        return detail::IsGpuRightGiven();
    }

/*  

*/

    /* Please see man pages for details 
        
        
        
        
        
     */
    inline void AttachTransferMemoryHandle( os::TransferMemoryBlock* transferMemory, nn::Handle handle, size_t size, bit32 otherPermission )
    {
        detail::AttachTransferMemoryHandle( transferMemory, handle, size, otherPermission );
    }

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
        
        
        
        
        
     */
    inline Result SendMessage( AppletId receiverId, const u8* pParam, size_t paramSize, nn::Handle handle=NN_APPLET_HANDLE_NONE, nn::fnd::TimeSpan timeout=WAIT_INFINITE )
    {
        return detail::SendMessage( receiverId, pParam, paramSize, handle, timeout );
    }

    /* Please see man pages for details 
        
        
        
        
        
        
     */
    inline Result TrySendMessage( AppletId receiverId, const u8* pParam, size_t paramSize, nn::Handle handle=NN_APPLET_HANDLE_NONE )
    {
        return detail::TrySendMessage( receiverId, pParam, paramSize, handle );
    }
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

        
                    
                    

                    
                    
     */
    inline AppletPowerButtonState GetPowerButtonState(void)
    {
        return detail::GetPowerButtonState();
    }

    /* Please see man pages for details 
        
     */
    inline void ClearPowerButtonState(void)
    {
        detail::ClearPowerButtonState();
    }

    bool IsReceivedWakeupByCancel(void);

    /* Please see man pages for details 
        

        
     */
    inline bool IsExpectedToProcessPowerButton(void)
    {
        return ( GetPowerButtonState() != POWER_BUTTON_STATE_NONE )? true: false;
    }
/*  

*/

    //================================================================
    // Termination request
    //================================================================
    inline AppletOrderToCloseState GetOrderToCloseState(void)
    {
        return detail::GetOrderToCloseState();
    }
    inline void ClearOrderToCloseState(void)
    {
        detail::ClearOrderToCloseState();
    }

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

                    
                    

                    

        
        
     */
    inline Result PreloadLibraryApplet( AppletId id )
    {
        return detail::PreloadLibraryApplet(id);
    }

    /* Please see man pages for details 
        

                    
                    

                    

        
     */
    inline Result CancelLibraryAppletIfRegistered( bool isApplicationEnd, AppletWakeupState *pWakeupState=NULL )
    {
        return detail::CancelLibraryAppletIfRegistered( isApplicationEnd, pWakeupState );
    }
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

                    

                    

                    

        
        
     */
    inline Result PrepareToStartLibraryApplet( AppletId id )
    {
        return detail::PrepareToStartLibraryApplet(id);
    }

    /* Please see man pages for details 
        

                    

                    

                    

                    

        
        
        
        
        
     */
    inline Result StartLibraryApplet( AppletId id, const u8* pParam=NULL, size_t paramSize=0, Handle handle=NN_APPLET_HANDLE_NONE )
    {
        return detail::StartLibraryApplet(id, pParam, paramSize, handle);
    }
/*  

*/

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        

        
     */
    inline bool IsExpectedToCloseApplication(void)
    {
        return ( GetOrderToCloseState() != ORDER_TO_CLOSE_STATE_NONE ||
                 IsReceivedWakeupByCancel() )? true: false;
    }

    /* Please see man pages for details 
        
        
        
     */
    inline Result PrepareToCloseApplication(void)
    {
        return detail::PrepareToCloseApplication();
    }

    /* Please see man pages for details 
        
        
        
        
        
        
     */
    inline Result CloseApplication( const u8* pParam=NULL, size_t paramSize=0, Handle handle=NN_APPLET_HANDLE_NONE )
    {
        return detail::CloseApplication( pParam, paramSize, handle );
    }

    /* Please see man pages for details 
        

        
        
        
        
     */
    inline Result RestartApplication( const void* pParam = NULL, size_t paramSize = NN_APPLET_PARAM_BUF_SIZE )
    {
        return detail::RestartApplication( pParam, paramSize );
    }

    /* Please see man pages for details 
        

        
        
        
        
    */
    inline bool GetStartupArgument( void* pParam, size_t paramSize = NN_APPLET_PARAM_BUF_SIZE )
    {
        return detail::GetStartupArgument( pParam, paramSize );
    }
/* Please see man pages for details 
    
 */

    // Obsolete function.
    inline Result PrepareToClosePreloadedApplication(void)
    {
        return detail::PrepareToCloseApplication( true );
    }
    inline Result ClosePreloadedApplication( const u8* pParam=NULL, size_t paramSize=0, Handle handle=NN_APPLET_HANDLE_NONE )
    {
        return detail::CloseApplication( pParam, paramSize, handle );
    }
}
}
}

#endif  // ifndef NN_APPLET_CTR_APPLET_API_H_
