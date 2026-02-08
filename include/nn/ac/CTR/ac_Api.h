/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ac_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46687 $
 *---------------------------------------------------------------------------*/

#ifndef NN_AC_CTR_AC_API_H_
#define NN_AC_CTR_AC_API_H_

/* Please see man pages for details 
    
*/

#include <nn/os/os_Event.h>
#include <nn/ac/ac_Result.h>
#include <nn/ac/CTR/ac_Types.h>

#ifdef __cplusplus

namespace nn {
namespace ac {
namespace CTR {

    /* Please see man pages for details 
        

               
               
               
               

        
        
        
        
    */
    Result Initialize();

    /* Please see man pages for details 
        

        
        
        
        
    */
    Result Finalize();

    /* Please see man pages for details 
        

        
    */
    bool IsInitialized();

    /* Please see man pages for details 
        

               
               
               
               
               

        

        
        
        
        
    */
    Result CreateDefaultConfig( Config* config );

    /* Please see man pages for details 
        

               
               
               
               

        
        

        
        
        
        
    */
    Result DebugSetApType( Config* config, u32 aptype );

    /* Please see man pages for details 
        

               
               
               
               
               
               
               

        
        

        
        
        
        
    */
    Result DebugSetNetworkArea( Config* config, NetworkArea networkArea );

    /* Please see man pages for details 
        

               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               

        

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    */
    Result Connect( Config& config );

    /* Please see man pages for details 
        

               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               

        
        

        
        
        
        
        
        
        
        
    */
    Result ConnectAsync( Config& config, os::Event* event );

    /* Please see man pages for details 
        

               
               

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    */
    Result GetConnectResult();

    /* Please see man pages for details 
        

               
               
               
               
               
               
               
               
               
               
               
               

        
        
        
        
        
    */
    Result CancelConnectAsync();

    /* Please see man pages for details 
        

               
               

        

        
        
        
        
    */
    Result GetLinkLevel( LinkLevel* linkLevel );

    /* Please see man pages for details 
        

               
               
               

        
    */
    LinkLevel GetLinkLevel();

    /* Please see man pages for details 
        

               
               
               

        
        
        
        
        

        
        
        
        
    */
    Result DebugSetNetworkSetting1( const u8 ssid[], u8 ssidLength, SecurityMode securityMode, const u8 key[], u8 keyLen );

    /* Please see man pages for details 
        

               
               

        
        
        
        
        
    */
    Result Close();

    /* Please see man pages for details 
        

               
               
               
               
               

        

        
        
        
        
        
    */
    Result CloseAsync( os::Event* event );

    /* Please see man pages for details 
        

               
               

        
        
        
        
        
    */
    Result GetCloseResult();

    /* Please see man pages for details 
        

               
               
               

        

        
        
        
        
    */
    Result GetLastErrorCode( u32* errorCode );

    /* Please see man pages for details 
        

               
               

        

        
        
        
        
    */
    Result GetLastDetailErrorCode( u32* errorCode );

    /* Please see man pages for details 
        

               
               
               
               
               
               
               

        
    */
    bool IsConnected();

    /* Please see man pages for details 
        

        
        
        

        

        
        
        
        
        
    */
    Result GetConnectingNetworkArea( NetworkArea* area );

    /* Please see man pages for details 
        

        
        
        

        
        
        
        

        

        
        
        
        
        
    */
    Result GetConnectingApType( ApType* apType );

    /* Please see man pages for details 
        

        

        
        
        
        
        
        
    */
    Result GetConnectingNintendoZoneBeaconSubset( NintendoZoneBeaconSubset* beacon );

    /* Please see man pages for details 
        

        

        
        
        
        
        
        
    */
    Result GetConnectingHotspotSubset( HotspotSubset* hotspot );

    /* Please see man pages for details 
        

        

        
        
        
        
    */
    Result RegisterDisconnectEvent(nn::os::Event* event);

    namespace
    {
        const char PORT_NAME_USER[]      = "ac:u";
    }
}
}
}

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
    

    

    
*/

/* Please see man pages for details 

*/
NN_EXTERN_C nnResult nnacInitialize(void);

/* Please see man pages for details 

*/
NN_EXTERN_C nnResult nnacFinalize(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacCreateDefaultConfig( nnacConfig* config );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacDebugSetNetworkArea( nnacConfig* config, nnacNetworkArea networkArea );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacConnect( nnacConfig* config );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacConnectAsync( nnacConfig* config, nnosEvent* event );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacCancelConnectAsync(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetConnectResult(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacDebugSetNetworkSetting1( const u8 ssid[], u8 ssidLength, nnacSecurityMode securityMode, const u8 key[], u8 keyLen );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacDebugFlushNetworkSetting(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacClose(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacCloseAsync( nnosEvent* event );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetCloseResult(void);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetLinkLevel( nnacLinkLevel* linkLevel );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetLastErrorCode( u32* errorCode );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetLastDetailErrorCode( u32* errorCode );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetConnectingApType( nnacApType* apType );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetConnectingNintendoZoneBeaconSubset( nnacNintendoZoneBeaconSubset* beacon );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacGetConnectingHotspotSubset( nnacHotspotSubset* hotspot );

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnacRegisterDisconnectEvent( nnosEvent* event );

/*  

*/

#endif  // ifndef NN_AC_CTR_AC_API_H_
