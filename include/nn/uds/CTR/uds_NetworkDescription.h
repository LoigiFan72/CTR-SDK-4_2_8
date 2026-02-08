/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds_NetworkDescription.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46929 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
*/

#ifndef LIBRARIES_UDS_CTR_UDS_NETWORK_DESCRIPTION_H_
#define LIBRARIES_UDS_CTR_UDS_NETWORK_DESCRIPTION_H_

#include <cstring>
#include <nn/uds/CTR/uds_Type.h>
#include <nn/uds/CTR/uds_Result.h>
#include <nn/uds/CTR/uds_InfoElement.h>

namespace nn {
namespace uds {
namespace CTR {

/* Please see man pages for details 
    
    
    
*/
class NetworkDescription
{

public:
/* Please see man pages for details 
  
*/
    enum CompareResult
    {
        SAME_NETWORK_SAME_DATA,     //
        SAME_NETWORK_DIFFERENT_DATA, //
        DIFFERENT_NETWORK           //
    };

/* Please see man pages for details 
  
  
                
                

  
  
  
  
  
  
  
*/
    nn::Result Initialize( u32 localId, u8 subId, u8 maxEntry, u8 channel, const void* pData, size_t dataSize );
/* Please see man pages for details 
  
  
                
                

  
  
  
  
  
*/
    void Initialize( u32 localId, u8 subId, u8 maxEntry, u8 channel );
/* Please see man pages for details 
  
  
                
                

  
  
  
  
*/
    void Initialize( const detail::NetworkDescriptionElement* element, u8 channel, const bit8 bssid[MAC_ADDRESS_SIZE]);

/* Please see man pages for details 
  
  
                
  
*/
    void Finalize() { m_IsInitialized = false; std::memset(m_Bssid, 0x00, MAC_ADDRESS_SIZE); }
/* Please see man pages for details 
  
  
*/
    const bit8* GetBssid() const{ return m_Bssid; }
/* Please see man pages for details 
  
  
*/
    u32         GetGameId() const {return this->GetLocalCommunicationId(); }
/* Please see man pages for details 
  
  
*/
    u32         GetLocalCommunicationId() const {return m_IsInitialized? detail::UDS_BE2LE32(m_Element.gameId):0; }
/* Please see man pages for details 
  
  
*/
    u8          GetSubId() const {return m_IsInitialized? m_Element.subId:0; }
/* Please see man pages for details 
  

                
                
                
                
                
                
                
                
                
                
                   
                
                
                
                
                
                
                
                
                
                
                
                
                
                
  
*/
    u32         GetTemporaryId() const {return m_IsInitialized? detail::UDS_BE2LE32(m_Element.temporaryId):0; }
/* Please see man pages for details 
  
  
*/
    u16         GetChannel() const { return m_IsInitialized? m_Channel:0; }
/* Please see man pages for details 
  
  
*/
    u8          GetNowEntry() const { return m_IsInitialized? m_Element.nowEntry:0 ; }
/* Please see man pages for details 
  
  
*/
    u8          GetMaxEntry() const { return m_IsInitialized? m_Element.maxEntry:0 ; }
/* Please see man pages for details 
  

  
  
  
*/
    size_t      GetApplicationData(bit8* buffer, const size_t bufferSize) const;
/* Please see man pages for details 
  
  
  
  
*/
    bool        CanConnectAsSpectator() const { return ( m_IsInitialized && !(detail::UDS_BE2LE16(m_Element.attribute) & detail::EJECT_SPECTAOTR_FLAG)); }
/* Please see man pages for details 
  
  
  
  
*/
    bool        CanConnectAsClient()    const { return ( m_IsInitialized && !(detail::UDS_BE2LE16(m_Element.attribute) & detail::DISALLOW_CONNECT_FLAG)); }
/* Please see man pages for details 
  
  
  
  
*/
    bool        CanReconnectAsClient()  const { return ( m_IsInitialized && !this->CanConnectAsClient() && !(detail::UDS_BE2LE16(m_Element.attribute) & detail::DISALLOW_RECONNECT_FLAG)); }//!<Checks if reconnection is permitted for Clients. The determination of whether it is a reconnection is made when the Master actually connects, so there is no guarantee that reconnection is possible even if this value is true.

/* Please see man pages for details 
  

  
  
*/
    CompareResult CompareWith(const NetworkDescription& otherOne) const;

/* Please see man pages for details 
  
  

  
  
  
*/
    CompareResult CompareWith(bit8 bssid[MAC_ADDRESS_SIZE], detail::NetworkDescriptionElement* element) const;

/* Please see man pages for details 
  
  
  
                

  
  
  
  
*/
    nn::Result Decompose(detail::NetworkDescriptionElement* element, u8* channel, bit8 bssid[MAC_ADDRESS_SIZE]);

/* Please see man pages for details 
  
                    
  
  
  
  
*/
    bool         operator==(NetworkDescription &networkDescription);
/* Please see man pages for details 
  
                    
  
  
  
  
*/
    bool         operator!=(NetworkDescription &networkDescription);

private:
    bit8        m_Bssid[MAC_ADDRESS_SIZE];        //
    u16         m_Channel;      //
    bool        m_IsInitialized;
    NN_PADDING3;
    detail::NetworkDescriptionElement m_Element;  //

};

typedef NetworkDescription  NetworkDescription2;    // Type in order to call NetworkDescription that was revised with .hid

} // end of namespace CTR
} // end of namespace uds
} // end of namespace nn

#endif /* LIBRARIES_UDS_CTR_UDS_NETWORK_DESCRIPTION_H_ */
