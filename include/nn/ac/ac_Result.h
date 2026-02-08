/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ac_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_AC_AC_RESULT_H_
#define NN_AC_AC_RESULT_H_

#include <nn/Result.h>

#ifdef __cplusplus

namespace nn { namespace ac {
//New definition

    /*
        
    */
    enum Description
    {
        DESCRIPTION_WAN_CONNECTED = 50,                   //
        DESCRIPTION_LAN_CONNECTED,                        //
        DESCRIPTION_UNNECESSARY_HOTSPOT_LOGOUT,           //

        DESCRIPTION_PROCESSING = 70,                      //

        DESCRIPTION_FAILED_STARTUP = 100,                 //
        DESCRIPTION_FAILED_CONNECT_AP,                    //
        DESCRIPTION_FAILED_DHCP,                          //
        DESCRIPTION_CONFLICT_IP_ADDRESS,                  //
        DESCRIPTION_INVALID_KEY_VALUE,                    //
        DESCRIPTION_UNSUPPORT_AUTH_ALGORITHM,             //
        DESCRIPTION_DENY_USB_AP,                          //

        DESCRIPTION_INVALID_DNS = 150,                    //
        DESCRIPTION_INVALID_PROXY,                        //
        DESCRIPTION_FAILED_CONNTEST,                      //

        DESCRIPTION_UNSUPPORT_HOTSPOT = 200,              //
        DESCRIPTION_FAILED_HOTSPOT_AUTHENTICATION,        //
        DESCRIPTION_FAILED_HOTSPOT_CONNTEST,              //
        DESCRIPTION_UNSUPPORT_PLACE,                      //
        DESCRIPTION_FAILED_HOTSPOT_LOGOUT,                //
        DESCRIPTION_ALREADY_CONNECT_UNSUPPORT_AP,         //

        DESCRIPTION_FAILED_SCAN = 300,                    //
        DESCRIPTION_ALREADY_CONNECTING,                   //
        DESCRIPTION_NOT_CONNECTING,                       //
        DESCRIPTION_ALREADY_EXCLUSIVE,                    //
        DESCRIPTION_NOT_EXCLUSIVE,                        //
        DESCRIPTION_INVALID_LOCATION,                     //

        DESCRIPTION_NOT_AGREE_EULA = 900,                 //
        DESCRIPTION_WIFI_OFF,                             //
        DESCRIPTION_BROKEN_NAND,                          //
        DESCRIPTION_BROKEN_WIRELESS,                      //

        DESCRIPTION_END
    };

    /* Please see man pages for details 
      
      
    */

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultDebugOnly,
            Result::LEVEL_USAGE, Result::SUMMARY_WOULD_BLOCK, Result::MODULE_NN_AC, Result::DESCRIPTION_NOT_IMPLEMENTED
        );

    /* Please see man pages for details 
        
        
               
    */
        NN_DEFINE_RESULT_CONST(
                ResultAlreadyInitialized,
            Result::LEVEL_SUCCESS, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_AC, Result::DESCRIPTION_ALREADY_INITIALIZED
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultNotInitialized,
            Result::LEVEL_SUCCESS, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_AC, Result::DESCRIPTION_NOT_INITIALIZED
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultCanceled,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, Result::DESCRIPTION_CANCEL_REQUESTED
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultInvalidData,
            Result::LEVEL_USAGE, Result::SUMMARY_WOULD_BLOCK, Result::MODULE_NN_AC, Result::DESCRIPTION_INVALID_RESULT_VALUE
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultInvalidArgumentOutOfRange,
            Result::LEVEL_USAGE, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_AC, Result::DESCRIPTION_OUT_OF_RANGE
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultOutOfMemory,
            Result::LEVEL_FATAL, Result::SUMMARY_INTERNAL, Result::MODULE_NN_AC, Result::DESCRIPTION_OUT_OF_MEMORY
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultAlreadyExists,
            Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, Result::DESCRIPTION_ALREADY_EXISTS
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultNotAgreeEula,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_NOT_AGREE_EULA
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultWifiOff,
            Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, DESCRIPTION_WIFI_OFF
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultBrokenNand,
            Result::LEVEL_FATAL, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_AC, DESCRIPTION_BROKEN_NAND
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultBrokenWireless,
            Result::LEVEL_FATAL, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_AC, DESCRIPTION_BROKEN_WIRELESS
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultNotFoundAccessPoint,
            Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_AC, Result::DESCRIPTION_NOT_FOUND
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedStartup,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_STARTUP
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedConnectAp,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_CONNECT_AP
        );

    /* Please see man pages for details 
        
        
               
    */
        NN_DEFINE_RESULT_CONST(
                ResultInvalidKeyValue,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_INVALID_KEY_VALUE
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedDhcp,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_DHCP
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultConflictIpAddress,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_CONFLICT_IP_ADDRESS
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultUnsupportAuthAlgorithm,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_UNSUPPORT_AUTH_ALGORITHM
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultDenyUsbAp,
            Result::LEVEL_STATUS, Result::SUMMARY_INTERNAL, Result::MODULE_NN_AC, DESCRIPTION_DENY_USB_AP
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultInvalidDns,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_INVALID_DNS
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultInvalidProxy,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_INVALID_PROXY
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedConnTest,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_CONNTEST
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultUnsupportHotspot,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_UNSUPPORT_HOTSPOT
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedHotspotAuthentication,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_HOTSPOT_AUTHENTICATION
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedHotspotConntest,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_HOTSPOT_CONNTEST
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedHotspotLogout,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_HOTSPOT_LOGOUT
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultUnsupportPlace,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_UNSUPPORT_PLACE
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedHotspotLogout,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_HOTSPOT_LOGOUT
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultAlreadyConnectUnsupportAp,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_ALREADY_CONNECT_UNSUPPORT_AP
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultFailedScan,
            Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_FAILED_SCAN
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultAlreadyConnecting,
            Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, DESCRIPTION_ALREADY_CONNECTING
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultNotConnecting,
            Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, DESCRIPTION_NOT_CONNECTING
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultAlreadyExclusive,
            Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, DESCRIPTION_ALREADY_EXCLUSIVE
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultNotExclusive,
            Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, DESCRIPTION_NOT_EXCLUSIVE
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultInvalidLocation,
            Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_AC, DESCRIPTION_INVALID_LOCATION
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultLanConnected,
            Result::LEVEL_SUCCESS, Result::SUMMARY_SUCCESS, Result::MODULE_NN_AC, DESCRIPTION_LAN_CONNECTED
        );

    /* Please see man pages for details 
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultWanConnected,
            Result::LEVEL_SUCCESS, Result::SUMMARY_SUCCESS, Result::MODULE_NN_AC, DESCRIPTION_WAN_CONNECTED
        );

    /* Please see man pages for details 
        
        
        
    */
        NN_DEFINE_RESULT_CONST(
                ResultUnnecessaryHotspotLogout,
            Result::LEVEL_SUCCESS, Result::SUMMARY_SUCCESS, Result::MODULE_NN_AC, DESCRIPTION_UNNECESSARY_HOTSPOT_LOGOUT
        );

	/* Please see man pages for details 
		
		
	*/
		NN_DEFINE_RESULT_CONST(
				ResultProcessing,
			Result::LEVEL_USAGE, Result::SUMMARY_CANCELLED, Result::MODULE_NN_AC, DESCRIPTION_PROCESSING
		);

}}

#endif // __cplusplus

#endif
