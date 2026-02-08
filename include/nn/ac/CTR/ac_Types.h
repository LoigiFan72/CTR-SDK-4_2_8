/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ac_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_AC_CTR_AC_TYPES_H_
#define NN_AC_CTR_AC_TYPES_H_

#include <nn/config.h>
#include <nn/types.h>

/* Please see man pages for details 
 
 */
typedef enum nnacApType
{
    NN_AC_AP_TYPE_NONE = 0,                             //
    NN_AC_AP_TYPE_USER_SETTING_1 = 1 << 0,              //
    NN_AC_AP_TYPE_USER_SETTING_2 = 1 << 1,              //
    NN_AC_AP_TYPE_USER_SETTING_3 = 1 << 2,              //
    NN_AC_AP_TYPE_NINTENDO_WIFI_USB_CONNECTOR = 1 << 3, //
    NN_AC_AP_TYPE_NINTENDO_ZONE = 1 << 4,               //
    NN_AC_AP_TYPE_WIFI_STATION = 1 << 5,                //
    NN_AC_AP_TYPE_FREESPOT = 1 << 6,                    //
    NN_AC_AP_TYPE_HOTSPOT = 1 << 7,                     //

    NN_AC_AP_TYPE_ALL = 0x7FFFFFFF                      //
} nnacApType;

/* Please see man pages for details 
 
 */
typedef enum nnacNetworkArea
{
    NN_AC_NETWORK_AREA_WAN = 0,     //
    NN_AC_NETWORK_AREA_AUTO = 1,    //
    NN_AC_NETWORK_AREA_LAN = 2      //
} nnacNetworkArea;

/* Please see man pages for details 
 
 */
typedef enum nnacSecurityMode
{
    NN_AC_OPEN,             //
    NN_AC_WEP_40BIT,        //
    NN_AC_WEP_104BIT,       //
    NN_AC_WEP_128BIT,       //
    NN_AC_WPA_TKIP,         //
    NN_AC_WPA2_TKIP,        //
    NN_AC_WPA_AES,          //
    NN_AC_WPA2_AES          //
} nnacSecurityMode;

/* Please see man pages for details 
  
*/
typedef enum nnacLinkLevel
{
    NN_AC_LINK_LEVEL_0 = 0,   //
    NN_AC_LINK_LEVEL_1,       //
    NN_AC_LINK_LEVEL_2,       //
    NN_AC_LINK_LEVEL_3        //
} nnacLinkLevel;

/* Please see man pages for details 
 
 */
typedef struct nnacConfig
{
    u8 value[512];
} nnacConfig;

/* Please see man pages for details 
 
 */
typedef struct nnacNintendoZoneBeaconSubset
{
    u8 apnum[10];
    NN_PADDING2;
    u8 hotspotname[24];
} nnacNintendoZoneBeaconSubset;

/* Please see man pages for details 
 
 */
typedef struct nnacHotspotSubset
{
    u8 apnum[10];
    NN_PADDING2;
    u8 hotspotname[64];
} nnacHotspotSubset;

#ifdef __cplusplus

namespace nn {
namespace ac {
namespace CTR {

    /* Please see man pages for details 
     
     */
    enum ApType
    {
        AP_TYPE_NONE = 0,                             //
        AP_TYPE_USER_SETTING_1 = 1 << 0,              //
        AP_TYPE_USER_SETTING_2 = 1 << 1,              //
        AP_TYPE_USER_SETTING_3 = 1 << 2,              //
        AP_TYPE_NINTENDO_WIFI_USB_CONNECTOR = 1 << 3, //
        AP_TYPE_NINTENDO_ZONE = 1 << 4,               //
        AP_TYPE_WIFI_STATION = 1 << 5,                //
        AP_TYPE_FREESPOT = 1 << 6,                    //
        AP_TYPE_HOTSPOT = 1 << 7,                     //

        AP_TYPE_ALL = 0x7FFFFFFF                      //
    };

    /* Please see man pages for details 
     
     */
    enum NetworkArea
    {
        NETWORK_AREA_WAN = 0,     //
        NETWORK_AREA_AUTO = 1,    //
        NETWORK_AREA_LAN = 2      //
    };

    /* Please see man pages for details 
     
     */
    enum SecurityMode
    {
        OPEN,             //
        WEP_40BIT,        //
        WEP_104BIT,       //
        WEP_128BIT,       //
        WPA_TKIP,         //
        WPA2_TKIP,        //
        WPA_AES,          //
        WPA2_AES          //
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
    typedef nnacConfig Config;

    /* Please see man pages for details 
     
     */
    typedef nnacNintendoZoneBeaconSubset NintendoZoneBeaconSubset;

    /* Please see man pages for details 
     
     */
    typedef nnacHotspotSubset HotspotSubset;

} // namespace CTR
} // namespace ac
} // namespace nn

#endif // __cplusplus

#endif //NN_AC_CTR_AC_TYPES_H_
