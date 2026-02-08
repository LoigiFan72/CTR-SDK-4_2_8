/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_Type.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47023 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_TYPE_H_
#define NN_DLP_CTR_DLP_TYPE_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/cfg.h>
#include <nn/uds.h>

namespace nn {
namespace dlp {
namespace CTR {
/*
    
    
  */
const size_t    MAX_CHILD_IMPORT_SIZE           = 32 * 1024 * 1024;         //
const s32       SHORT_TITLE_NAME_LENGTH         = 64;                       //
const s32       LONG_TITLE_NAME_LENGTH          = 128;                      //
const s32       ICON_HEIGHT_PIXEL               = 48;                       //
const s32       ICON_WIDTH_PIXEL                = 48;                       //
const s32       ICON_PIXEL_COUNT                = ICON_WIDTH_PIXEL * ICON_HEIGHT_PIXEL; //
const s32       RATING_INFO_SIZE                = 16;                       //
const u16       MAX_NODE_NUM                    = nn::uds::CTR::NODE_MAX;   //
const u16       MAX_CLIENT_NUM                  = MAX_NODE_NUM - 1;         //
const u8        MAX_SCAN_NUM                    = 16;                       //
const size_t    MIN_NETWORK_BLOCK_BUFFER_NUM    = 2;                        //
const size_t    MAX_NETWORK_BLOCK_BUFFER_NUM    = 4;                        //
const size_t    MIN_NETWORK_BLOCK_BUFFER_SIZE   = 128*1024;                 //
const size_t    MAX_NETWORK_BLOCK_BUFFER_SIZE   = 512*1024;                 //
const size_t    MAX_CHILD_UDS_PASSPHRASE_LENGTH = 9;                        //

/*  

*/


enum SessionType
{
    SESSION_TYPE_INVALID            = 0,
    SESSION_TYPE_TITLE              = 1,        // Download session for the child device program
    SESSION_TYPE_SYSTEM             = 2         // Download session of the system required to run the title
};


/*
  
 */
enum ClientState
{
    CLIENT_STATE_INVALID                        = 0x00,    //
    CLIENT_STATE_DISCONNECTED_NETWORK           = 0x01,    //
    CLIENT_STATE_SCANNING                       = 0x02,    //
    CLIENT_STATE_WAITING_CONNECT                = 0x03,    //
    CLIENT_STATE_WAITING_INVITE                 = 0x04,    //
    CLIENT_STATE_JOINED_SESSION                 = 0x05,    //
    CLIENT_STATE_DOWNLOADING                    = 0x06,    //
    CLIENT_STATE_DOWNLOAD_COMPLETE              = 0x07,    //
    CLIENT_STATE_REBOOTING                      = 0x09,    //
    CLIENT_STATE_ERROR                          = 0x80,    //
    CLIENT_STATE_WAITING_ACCEPT                 = 0x40,    //


    // Do not use the following. State for the system application
    CLIENT_STATE_CONFIRMING_DOWNLOAD_PROGRESS   = 0x41,    //
    CLIENT_STATE_RECONNECTING_NETWORK           = 0x08     //
};


/*
  

                
                
                
                


 */
enum ServerState
{
    SERVER_STATE_INVALID = 0,                           //
    SERVER_STATE_INITIALIZED = 1,                       //
    SERVER_STATE_OPENED_SESSIONS = 2,                   //
    SERVER_STATE_DISTRIBUTING = 11,                     //
    SERVER_STATE_COMPLETE_DISTRIBUTION = 8,             //
    SERVER_STATE_REBOOTING_CLIENTS = 9,                 //
    SERVER_STATE_ERROR = 10,                            //

    // Below is a state that can be used only in the SDK
    SERVER_STATE_PREPARING_FOR_SYSTEM_DISTRIBUTION = 3, //
    SERVER_STATE_DISTRIBUTING_SYSTEM = 4,               //
    SERVER_STATE_WAITING_RECONNECT = 5,                 //
    SERVER_STATE_PREPARING_FOR_TITLE_DISTRIBUTION = 6,  //
    SERVER_STATE_DISTRIBUTING_TITLE = 7                 //
};


/*
  
 */
enum EventType
{
    EVENT_TYPE_INVALID = 0,
    // SERVER
    EVENT_TYPE_SERVER_STATE_DISTRIBUTING = 19,                      //
    EVENT_TYPE_SERVER_STATE_COMPLETE_DISTRIBUTION = 6,              //
    EVENT_TYPE_SERVER_STATE_ERROR = 7,                              //

    // CLIENT
    EVENT_TYPE_CLIENT_DISCOVERED_SERVER = 8,                        //
    EVENT_TYPE_CLIENT_SCAN_BUFFER_FULL = 9,                         //
    EVENT_TYPE_CLIENT_DISCOVERED_TITLE = 10,                        //
    EVENT_TYPE_CLIENT_STATE_WAITING_INVITE = 11,                    //
    EVENT_TYPE_CLIENT_STATE_JOINED_SESSION = 12,                    //
    EVENT_TYPE_CLIENT_STATE_DOWNLOADING = 13,                       //
    EVENT_TYPE_CLIENT_STATE_DOWNLOAD_COMPLETE = 14,                 //
    EVENT_TYPE_CLIENT_STATE_REBOOTING = 16,                         //
    EVENT_TYPE_CLIENT_STATE_DISCONNECTED_NETWORK = 17,              //
    EVENT_TYPE_CLIENT_STATE_ERROR = 18,                             //

    // Do not use the following. Event for the system application
    EVENT_TYPE_CLIENT_STATE_RECONNECTING_NETWORK = 15,              //


    // Do not use the following. For compatibility with previous SDK versions
    EVENT_TYPE_SERVER_STATE_PREPARING_FOR_SYSTEM_DISTRIBUTION = 1,  //
    EVENT_TYPE_SERVER_STATE_DISTRIBUTING_SYSTEM = 2,                //
    EVENT_TYPE_SERVER_STATE_WAITING_RECONNECT = 3,                  //
    EVENT_TYPE_SERVER_STATE_PREPARING_FOR_TITLE_DISTRIBUTION = 4,   //
    EVENT_TYPE_SERVER_STATE_DISTRIBUTING_TITLE = 5                  //
};


/*
  
 */
typedef struct
{
    u8 mac[6];                                  //
    NN_PADDING2;
} ClientDiscoveredServer;


/*
  
 */
typedef struct
{
    u32             uniqueId;                   //
    u8              childIndex;                 //
    NN_PADDING3;
    u8              mac[6];                     //
    u16             programVersion;             //
} ClientDiscoveredTitle;


/*
  
 */
typedef struct
{
    u16 nodeId;                                 //
    NN_PADDING2;
} ClientStateWaitingInvite;


/*
  
 */
typedef struct
{
    nn::util::SizedEnum1<EventType> type;       //
    NN_PADDING3;
    NN_PADDING4;
    union{
        // Client
        ClientDiscoveredServer      clientDiscoveredServer;     //
        ClientDiscoveredTitle       clientDiscoveredTitle;      //
        ClientStateWaitingInvite    clientStateWaitingInvite;   //

        u8 placeHolder[16]; // For IPC
    } ;
} EventDesc;


/*
  
 */
typedef nn::uds::NodeInformation NodeInfo;


/*
  
 */
typedef struct
{
    u16                                 nodeId;                   //
    nn::util::SizedEnum1<SessionType>   sessionType;              //   Do not use Member for the system application.
    nn::util::SizedEnum1<ClientState>   state;                    //
    size_t                              totalNum;                 //   Do not use Member for the system application.
    size_t                              downloadedNum;            //   Do not use Member for the system application.
} ClientStatus;

/*
  
 */
typedef struct
{
   bit16                            image[ICON_PIXEL_COUNT];    //
} IconInfo;


/*
  
 */
typedef struct
{
    u32                                             uniqueId;                                   //
    u8                                              childIndex;                                 //
    NN_PADDING3;
    u8                                              mac[6];                                     //
    u16                                             programVersion;                             //
    bit8                                            ratingInfo[RATING_INFO_SIZE];               //
    wchar_t                                         shortTitleName[SHORT_TITLE_NAME_LENGTH];    //
    wchar_t                                         longTitleName[LONG_TITLE_NAME_LENGTH];      //
    IconInfo                                        icon;                                       //
    u32                                             importSize;                                 //
    nn::util::SizedEnum1<nn::cfg::CfgRegionCode>    region;                                     //
    bool                                            ulcd;                                       //
    NN_PADDING2;
} TitleInfo;


/*
  
 */
typedef struct
{
    u8                                          mac[6];                         //
    u8                                          channel;                        //
    nn::util::SizedEnum1<nn::uds::LinkLevel>    linkLevel;                      //
    u8                                          maxNodeNum;                     //
    u8                                          nodeNum;                        //
    bit16                                       dlpVersion;                     //
    NN_PADDING4;
    NodeInfo                                    nodeInfo[MAX_NODE_NUM];         //
    nn::os::Tick                                lastUpdateTick;                 //
} ServerInfo;


/*
  
 */
typedef struct
{
    u8                                  bssid[6];                       //
    char                                passphrase[MAX_CHILD_UDS_PASSPHRASE_LENGTH]; //
    NN_PADDING1;
} RebootInfo;

} // end of namespace CTR
} // end of namespace dlp
} // end of namespace nn

#endif  // ifndef NN_DLP_CTR_DLP_TYPE_H_
