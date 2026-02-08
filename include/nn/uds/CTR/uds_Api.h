/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47292 $
 *---------------------------------------------------------------------------*/

#ifndef INCLUDE_NN_UDS_CTR_UDS_API_H_
#define INCLUDE_NN_UDS_CTR_UDS_API_H_

/* Please see man pages for details 
    
*/

#include <nn/uds/CTR/uds_Type.h>
#include <nn/uds/CTR/uds_Result.h>
#include <nn/uds/CTR/uds_NetworkDescription.h>
#include <nn/cfg.h>

namespace nn {
namespace uds {
namespace CTR {

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
  

                
                
                
                
                

  
  
                                    
                                    
  

  
  
  
  
  
  
*/
nn::Result Initialize( nn::os::Event* pStatusUpdateEvent, void* receiveBuffer, const size_t bufferSize);

/* Please see man pages for details 
  

                
                
                
                
                
                

  
  
                                    
                                    
  
  

  
  
  
  
  
*/
nn::Result Initialize( nn::os::Event* pStatusUpdateEvent, void* receiveBuffer, const size_t bufferSize, nn::cfg::UserName* pUserName);

/* Please see man pages for details 
  

                
                
                
                
                
                

  
*/
void Finalize  ();

/*  

*/
/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
  

                
                
                
                
                

  
  
                                
                                
  
*/
bit32 CreateLocalCommunicationId( bit32 uniqueId, bool isDemo = false);

/* Please see man pages for details 
  

                
                
                

  
  
  
  
                                  
  

  
  
  
  
  
  
  
*/
nn::Result CreateNetwork(
        u8 subId,
        u8 maxEntry,
        bit32 localId,
        const char passphrase[],
        size_t passphraseLength );

/* Please see man pages for details 
  

                

                
                
                
                
                
                
                

  
  
  
  
                                  
  
  
  

  
  
  
  
  
  
  
  
  
*/
nn::Result CreateNetwork(
        u8 subId,
        u8 maxEntry,
        bit32 localId,
        const char passphrase[],
        size_t passphraseLength,
        const void* pData,
        size_t dataSize );

/* Please see man pages for details 
  
                

                
                
                

  
  
  
  
                                  
  
  

  
  
  
  
  
  
  
*/
nn::Result CreateNetwork(
        u8 subId,
        u8 maxEntry,
        bit32 localId,
        const char passphrase[],
        size_t passphraseLength,
        u8 channel );

/* Please see man pages for details 
  
                

                 

                 
                
                
                
                
                
                

  
  
  
  
                                  
  
  
  
  

  
  
  
  
  
  
  
  
  
*/
nn::Result CreateNetwork(
        u8 subId,
        u8 maxEntry,
        bit32 localId,
        const char passphrase[],
        size_t passphraseLength,
        u8 channel,
        const void* pData,
        size_t dataSize );

/* Please see man pages for details 
  

                
                
                

  
  
  
  

  
  
  
  
  
  
  
*/
nn::Result Scan( void* pBuffer, size_t bufferSize, u8 subId, bit32 localId );

/* Please see man pages for details 
  
  

                
                
                

  
  
  
  
  
                            
  

  
  
  
  
  
  
  
*/
nn::Result Scan( void* pBuffer, size_t bufferSize, u8 subId, bit32 localId, u8 channel, u16 scanTime = 0 );

/* Please see man pages for details 
  

                
                
                

  
  
  
                                          
  

  
  
  
  
  
  
  
  
  
  
  
*/
nn::Result ConnectNetwork(
        const NetworkDescription& networkDescription,
        ConnectType type,
        const char passphrase[],
        size_t passphraseLength );

/* Please see man pages for details 
  
                
                

  

  
  
  
  
  
  
*/
nn::Result EjectClient ( u16 nodeId );

/* Please see man pages for details 
  

                
                
                
                
                

  

  
  
  
  
  
  
*/
nn::Result DisallowToConnect(bool isDisallowToReconnect = false);

/* Please see man pages for details 
  

                
                
                
                
                

  
  
  
  
  
  
*/
nn::Result AllowToConnect();

/* Please see man pages for details 
  

                
                
                
                
                

  
  
  
  
  
  
*/
nn::Result EjectSpectator  ( void );
inline nn::Result EjectAudience  ( void ){ return EjectSpectator(); }

/* Please see man pages for details 
  

                
                
                
                

  
  
  
  
  
  
*/
nn::Result AllowToSpectate();

/* Please see man pages for details 
  

                
                
                
                
                
                
                

  
  
  
  
  
  
*/
nn::Result DestroyNetwork ( void );

/* Please see man pages for details 
  

                
                
                
                

  
  
  
  
  
  
*/
nn::Result DisconnectNetwork  ( void );

/*  

*/
/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
  

                
                
                

  

  
  
  
  
  
*/
nn::Result CreateEndpoint( EndpointDescriptor* pEndpointDesc );

/* Please see man pages for details 
  

               
               
               

               
               
               

  

  
  
  
  
  
  
*/
nn::Result SetMaxSendDelay ( nn::fnd::TimeSpan maxDelay );

/* Please see man pages for details 
  

               
               
               
               
               

  
  
  
  
  
  

  
  
  
  
  
  
  
  
  
  
  
*/
nn::Result SendTo  ( const EndpointDescriptor& endpointDesc, const void* data, size_t dataSize, u16 destNodeId, u8 port, bit8 option = 0x00 );

/* Please see man pages for details 
  

               
               
               
               

  
  
  
  
                                    
                                    
                                    

  
  
  
  
  
  
  
  
*/
nn::Result Attach  ( EndpointDescriptor* pEndpointDesc, u16 srcNodeId, u8 port, size_t receiveBufferSize = ATTACH_BUFFER_SIZE_DEFAULT );

/* Please see man pages for details 
  

               
               
               

  
  
  
  
  
                             

  
  
  
  
  
  
  
  
  
  
  
*/
nn::Result Receive     ( const EndpointDescriptor& endpointDesc, void* pBuffer, size_t* pReceivedSize, size_t bufferSize, bit8 option = 0x00 );

/* Please see man pages for details 
  

               
               
               
               
               

  
  
  
  
  
  

  
  
  
  
  
  
  
  
  
  
  
*/
nn::Result ReceiveFrom ( const EndpointDescriptor& endpointDesc, void* pBuffer, size_t* pReceivedSize, u16* pSrcNodeId, size_t bufferSize, bit8 option = 0x00 );

/* Please see man pages for details 
  

               
               
               
               

  

  
  
  
  
  
*/
nn::Result DestroyEndpoint( EndpointDescriptor* pEndpointDesc );

/*  

*/

/* Please see man pages for details 
  

                
                
                

  

  
  
  
  
*/
nn::Result GetConnectionStatus( ConnectionStatus* pStatus );

/* Please see man pages for details 
  

                

  

  
  
  
*/
nn::Result GetLinkLevel( LinkLevel* pLinkLevel );

/* Please see man pages for details 
  

                

  
*/
LinkLevel GetLinkLevel();

/* Please see man pages for details 
  
                
                

  

  
  
  
  
 */
nn::Result GetChannel(u8* pChannel);


/* Please see man pages for details 
  
                
                

  
  

  
  
  
  
  
  

*/
nn::Result GetNodeInformation ( NodeInformation* pNodeInfo, u16 nodeId );

/* Please see man pages for details 
  

                
                
                
                
                
                

  
  

  
  
  
  
  
  
  
*/
nn::Result SetApplicationDataToBeacon   ( const void* pData, size_t dataSize );

/* Please see man pages for details 
  

                
                
                
                
                

  
  
  

  
  
  
  
  
  
  
*/
nn::Result GetApplicationDataFromBeacon ( void* pBuffer, size_t* pDataSize, size_t bufferSize );

/* Please see man pages for details 
  
  

                
                
                
                
                

  

  
  

*/
nn::Result SetPowerSaveMode(PowerSaveMode mode);

namespace detail{

/* Please see man pages for details 
  
  

                
                
                
                

  

  
*/
nn::Result GetRadioStrengthInfo(RadioStrengthInfo* info);

/* Please see man pages for details 
  
  

                
                
                
                

  
  

  
  
  
  
  
*/
nn::Result DestroyEndpoint( EndpointDescriptor* pEndpointDesc, ReceiveReport* pReport );

} // end of namespace detail

} // end of namespace CTR
} // end of namespace uds
} // end of namespace nn



#endif  // ifndef INCLUDE_NN_UDS_CTR_UDS_API_H_
