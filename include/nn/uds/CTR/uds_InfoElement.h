/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds_InfoElement.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
*/

#ifndef LIBRARIES_UDS_CTR_UDS_IE_H_
#define LIBRARIES_UDS_CTR_UDS_IE_H_

#include <nn/types.h>

namespace nn {
namespace uds {
namespace CTR {
namespace detail {

const bit8 VSIE_OUI[ OUI_SIZE ]      = {0x00, 0x1f, 0x32};  //

const size_t VSIE_SIZE_MAX   = 250;

//Connection information included in NetworkDescription
const bit16 EJECT_SPECTAOTR_FLAG     = 0x0001; //!< Flag to disconnect connected spectators, with new connections prohibited
const bit16 DISALLOW_CONNECT_FLAG    = 0x0002; //!< Prohibit new client connections
const bit16 DISALLOW_RECONNECT_FLAG  = 0x0004; //!< Prohibit client re-connections @ref Only referenced when DISALLOW_CONNECT_FLAG is enabled
const bit16 DIRECT_BROADCAST_FLAG    = 0x8000; //!< Flag for whether to use DirectBroadcast; be sure to set this flag


/*
  
 */
enum SubType
{
    NETWORK_DESCRIPTION_IE  = 21,   //
    SPECTATOR_PACKET_IE     = 22,   //
    SPECTATOR_ACK_IE        = 23,   //
    NODE_INFORMATION_IE_1   = 24,   //
    NODE_INFORMATION_IE_2   = 25,   //
    SCAN_ON_CONNECTION_IE_1 = 26    //
};

/*
  
 */
struct NetworkDescriptionElement
{
    //Common header
    bit8  oui[3];           //
    u8    subType;          //
    u32   gameId;           //
    u8    subId;            //
    u8    sequenceNumber;   //
    bit16 attribute;        //
    u32   temporaryId;      //
    u8    nowEntry;         //
    u8    maxEntry;         //
    u8    tmpEntry;         //
    bit8  platform;         //
    u8    securityType;     //
    u8    reserved[10];     //
    u8    digest[20];         //
    u8    appDataLength;    //
    bit8  appData[NET_DESC_APPDATA_SIZE_MAX];   //
};

/*
  
 */
struct NodeInformationElement
{
    //Common header
    bit8  oui[3];           //
    u8    subType;          //
    bit8  payload[VSIE_SIZE_MAX];
};

/*
  
 */
struct ScanOnConnectionElement
{
    //Common header
    bit8  oui[3];           //
    u8    subType;          //
    u32   gameId;           //
    u8    subId;            //
    u8    reserved[3];
};

} // end of namespace detail
} // end of namespace CTR
} // end of namespace uds
} // end of namespace nn

#endif /* LIBRARIES_UDS_CTR_UDS_IE_H_ */
