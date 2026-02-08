/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds_Type.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47441 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
*/

#ifndef NN_UDS_CTR_UDS_TYPE_H_
#define NN_UDS_CTR_UDS_TYPE_H_

#include <nn/cfg.h>

namespace nn {
namespace uds {
namespace CTR {

    namespace
    {
        const char PORT_NAME_UDS[]    = "nwm::UDS";
    }

const u16 BROADCAST_NODE_ID = 0xffff;               //!< Node ID representing all node address of the network. Data sent to BROADCAST_NODE_ID can be retrieved by Spectators.

const u8 NODE_MAX     = 16;                         //
const u8 ENDPOINT_MAX = 16;                         //


/* Please see man pages for details 
  
  
*/
const u8  NET_DESC_APPDATA_SIZE_MAX      = 200;     //
const u16 UDS_PACKET_PAYLOAD_MAX_SIZE   = 1478;     //
const size_t ATTACH_BUFFER_SIZE_MIN     = (UDS_PACKET_PAYLOAD_MAX_SIZE + 128); 	//
const size_t ATTACH_BUFFER_SIZE_DEFAULT = (UDS_PACKET_PAYLOAD_MAX_SIZE * 8);   	//
/*  

*/
/* Please see man pages for details 
  
  
*/
const size_t UDS_PASSPHRASE_LENGTH_MIN = 8;         //
const size_t UDS_PASSPHRASE_LENGTH_MAX = 255;       //
/* Please see man pages for details 
  
*/

/* Please see man pages for details 
  
  
*/
const bit8 NO_WAIT = 0x01;         //
const bit8 FORCE_DIRECT_BC = 0x02; //
/*  

*/

const u8 MAC_ADDRESS_SIZE   = 6;
const u8 OUI_SIZE           = 3;

/* Please see man pages for details 
  
*/
enum State
{
    STATE_NONE = 0,                 //
    STATE_PROCESSING_INITIALIZE,    //
    STATE_PROCESSING_FINALIZE,      //
    STATE_DISCONNECTED,             //
    STATE_CREATING_NETWORK,         //
    STATE_DESTROYING_NETWORK,       //
    STATE_MASTER,                   //
    STATE_CONNECTING_NETWORK,       //
    STATE_DISCONNECTING_NETWORK,    //
    STATE_CLIENT,                   //
    STATE_SPECTATOR,                //
    STATE_ERROR,                    //
    STATE_MAX,
    STATE_MAX_BIT = (1u << 31)

};

const State STATE_AUDIENCE = STATE_SPECTATOR;

/* Please see man pages for details 
  
*/
enum DisconnectReason
{
    BEFORE_COMMUNICATION = 0,   //
    NETWORK_IS_AVAILABLE,       //
    REQUEST_FROM_MYSELF,        //
    REQUEST_FROM_SYSTEM,        //
    DISCARDED_FROM_NETWORK,     //
    CONNECTION_LOST,            //
    UNKNOWN_DISCONNECT_REASON,   //
    DISCONNECT_REASON_MAX,
    DISCONNECT_REASON_MAX_BIT = (1u << 31)
};

/* Please see man pages for details 
  
*/
enum ConnectType
{
    CONNECT_AS_CLIENT = 1,          //
    CONNECT_AS_SPECTATOR,           //
    CONNECT_AS_MASTER               //
};

const ConnectType CONNECT_AS_AUDIENCE  = CONNECT_AS_SPECTATOR ;

/* Please see man pages for details 
  
*/
enum PowerSaveMode
{
    ALWAYS_ACTIVE,      //
    POWERSAVE_NORMAL,   //
    POWERSAVE_HIGH,      //
    POWERSAVE_MODE_MAX
};

/* Please see man pages for details 
  
*/
enum LinkLevel
{
    LINK_LEVEL_0 = 0,   //
    LINK_LEVEL_1,       //
    LINK_LEVEL_2,       //
    LINK_LEVEL_3        //
};



/* Please see man pages for details 
  
*/
struct ConnectionStatus
{
    State               nowState;                   //
    DisconnectReason    disconnectReason;           //
    u16                 myNodeId;                   //
    bit16               updateNodeBitmap;           //
    u16                 nodeIdList[NODE_MAX];       //
    u8                  nowEntry;                   //
    u8                  maxEntry;                   //
    bit16               slotBitmap;                 //
};

/* Please see man pages for details 
  
  
*/
enum DataFrameIndex
{
    UNICAST_DATAFRAME = 0,      //
    BROADCAST_DATAFRAME,        //
    NUM_OF_DATAFRAME
};

static const size_t SCRAMBLED_LOCAL_FRINED_CODE_SIZE = 12; //

/* Please see man pages for details 
  

            
            
            

            
            
            
*/
struct ScrambledLocalFriendCode
{
        bit16 value[SCRAMBLED_LOCAL_FRINED_CODE_SIZE/sizeof(bit16)];    //
};

/* Please see man pages for details 
  
*/
struct NodeInformation
{
    ScrambledLocalFriendCode scrambledLocalFriendCode; //
    nn::cfg::CTR::UserName userName; //
    u16     nodeId;             //
    NN_PADDING2;
};

const u8 NODE_INFORMATION_SIZE = sizeof(NodeInformation);

/* Please see man pages for details 
  

                
*/
struct EndpointDescriptor
{
    u32  id;                 //
};


//Below are the definitions used by internal processes.
namespace detail{

    /* Please see man pages for details 
    
    
    */
    struct RadioStrength
    {
        s8   rssi;
        bool isValid;
    };

    /* Please see man pages for details 
    
    
    
           
    */
    class RadioStrengthInfo
    {
    public:
        RadioStrengthInfo(){m_IsInitialized = false;}
        void Initialize( const RadioStrength& masterLink, const RadioStrength directLink[NODE_MAX] );
        ~RadioStrengthInfo(){m_IsInitialized = false;}

        s8 GetAverage();    //
        s8 GetMinimum();    //
        s8 GetMaximum();    //
        s8 GetMasterLink(); //

    private:
        bool m_IsInitialized;
        void GetRawData(s8 rawLink[NODE_MAX] ); //

        RadioStrength m_MasterLink;
        RadioStrength m_DirectLink[NODE_MAX];
    };

    // Received result for each Endpoint that could be obtained by DestroyEndpoint.
    struct ReceiveReport
    {
        u32 id;             //
        u16 targetNodeId;   //
        u16 port;           //
        u32 receiveCount;   //
        u32 lostCount;      //
    };

    inline u16 UDS_BE2LE16( u16 value )
    {
        return static_cast<u16>( (((value) & 0xFF00UL) >> 8UL) | (((value) & 0x00FFUL) << 8UL));
    }

    inline u32 UDS_BE2LE32( u32 value )
    {
    return static_cast<u32>( (((value) & 0xFF000000UL) >> 24UL) | (((value) & 0x00FF0000UL) >> 8UL) | (((value) & 0x0000FF00UL) << 8UL) | (((value) & 0x000000FFUL) << 24UL));
    }

    inline u64 UDS_BE2LE64( u64 value )
    {
        u64 returnValue;
        u32* tmpA = reinterpret_cast<u32*>(&(returnValue));
        u32* tmpB = reinterpret_cast<u32*>(&(value));

        tmpA[0] = UDS_BE2LE32(tmpB[1]);
        tmpA[1] = UDS_BE2LE32(tmpB[0]);

        return returnValue;
    }

    inline u32 UDS_LE2BE32( u32 value)
    {
        return static_cast<u32>( (((value) & 0xFF000000UL) >> 24UL) | (((value) & 0x00FF0000UL) >> 8UL) | (((value) & 0x0000FF00UL) << 8UL) | (((value) & 0x000000FFUL) << 24UL));
    }

    inline u16 UDS_LE2BE16( u16 value )
    {
        return static_cast<u16>( (((value) & 0xFF00UL) >> 8UL) | (((value) & 0x00FFUL) << 8UL));
    }

    inline u64 UDS_LE2BE64( u64 value )
    {
        u64 returnValue;
        u32* tmpA = reinterpret_cast<u32*>(&(returnValue));
        u32* tmpB = reinterpret_cast<u32*>(&(value));

        tmpA[0] = UDS_LE2BE32(tmpB[1]);
        tmpA[1] = UDS_LE2BE32(tmpB[0]);

        return returnValue;
    }

    // UDS versions
    // 1.0: Initial version
    // 2.0: Revised the return values of ConnectNetwork() in CTR-SDK 2.X series (ctr-support:1415). Now sends Deauth at Eject().
    // 3.0: Resolved the latency issue in Finalize() in CTR-SDK 3.X series (+100 msec prior to version 3.0) (ctr-net:1631).
    // 4.0: ResultInvalidState(ctr-net:1667) for Initialize() during sleep in CTR-SDK 4.X series
    #define NN_UDS_DEFINE_UDS_VERSION(major, minor)  ((bit16)major<<8 | (bit16)minor&0x00FF)
    const   bit16  UDS_SDK_VERSION = NN_UDS_DEFINE_UDS_VERSION(4, 0);

/*
inline u32 UDS_LE2BE32( u32 value)
{
    NN_ASM("rev value, value");
    return value;
}
*/

} //end of namespace detail
} // end of namespace CTR
} // end of namespace uds
} // end of namespace nn

#endif /* NN_UDS_CTR_UDS_TYPE_H_ */
