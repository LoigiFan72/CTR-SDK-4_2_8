/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     friends_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FRIENDS_CTR_FRIENDS_RESULT_H_
#define NN_FRIENDS_CTR_FRIENDS_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn {
namespace friends {
namespace CTR {

    namespace detail {
        static const u32 DESCRIPTION_FACILITY_SHIFT = 5;
        static const u32 DESCRIPTION_RETURN_CODE_UNDEFINED = (1 << (DESCRIPTION_FACILITY_SHIFT + 1)) - 1;
    }

    enum Description
    {
        DESCRIPTION_FACILITY_CORE           = 1 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_DDL            = 2 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_RENDEZVOUS     = 3 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_PYTHONCORE     = 4 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_TRANSPORT      = 5 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_DOCORE         = 6 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_FPD            = 7 << detail::DESCRIPTION_FACILITY_SHIFT,
        DESCRIPTION_FACILITY_AUTHENTICATION = 8 << detail::DESCRIPTION_FACILITY_SHIFT,

        DESCRIPTION_CORE_SUCCESS                                     = DESCRIPTION_FACILITY_CORE + 0,
        DESCRIPTION_CORE_SUCCESS_PENDING                             = DESCRIPTION_FACILITY_CORE + 1,
        DESCRIPTION_CORE_UNKNOWN                                     = DESCRIPTION_FACILITY_CORE + 2,
        DESCRIPTION_CORE_NOT_IMPLEMENTED                             = DESCRIPTION_FACILITY_CORE + 3,
        DESCRIPTION_CORE_INVALID_POINTER                             = DESCRIPTION_FACILITY_CORE + 4,
        DESCRIPTION_CORE_OPERATION_ABORTED                           = DESCRIPTION_FACILITY_CORE + 5,
        DESCRIPTION_CORE_EXCEPTION                                   = DESCRIPTION_FACILITY_CORE + 6,
        DESCRIPTION_CORE_ACCESS_DENIED                               = DESCRIPTION_FACILITY_CORE + 7,
        DESCRIPTION_CORE_INVALID_HANDLE                              = DESCRIPTION_FACILITY_CORE + 8,
        DESCRIPTION_CORE_INVALID_INDEX                               = DESCRIPTION_FACILITY_CORE + 9,
        DESCRIPTION_CORE_OUT_OF_MEMORY                               = DESCRIPTION_FACILITY_CORE + 10,
        DESCRIPTION_CORE_INVALID_ARGUMENT                            = DESCRIPTION_FACILITY_CORE + 11,
        DESCRIPTION_CORE_TIMEOUT                                     = DESCRIPTION_FACILITY_CORE + 12,
        DESCRIPTION_CORE_INITIALIZATION_FAILURE                      = DESCRIPTION_FACILITY_CORE + 13,
        DESCRIPTION_CORE_CALL_INITIATION_FAILURE                     = DESCRIPTION_FACILITY_CORE + 14,
        DESCRIPTION_CORE_REGISTRATION_ERROR                          = DESCRIPTION_FACILITY_CORE + 15,
        DESCRIPTION_CORE_BUFFER_OVERFLOW                             = DESCRIPTION_FACILITY_CORE + 16,
        DESCRIPTION_CORE_INVALID_LOCK_STATE                          = DESCRIPTION_FACILITY_CORE + 17,
        DESCRIPTION_CORE_UNDEFINED                                   = DESCRIPTION_FACILITY_CORE + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_DDL_SUCCESS                                      = DESCRIPTION_FACILITY_DDL + 0,
        DESCRIPTION_DDL_INVALID_SIGNATURE                            = DESCRIPTION_FACILITY_DDL + 1,
        DESCRIPTION_DDL_INCORRECT_VERSION                            = DESCRIPTION_FACILITY_DDL + 2,
        DESCRIPTION_DDL_UNDEFINED                                    = DESCRIPTION_FACILITY_DDL + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_RENDEZVOUS_SUCCESS                               = DESCRIPTION_FACILITY_RENDEZVOUS + 0,
        DESCRIPTION_RENDEZVOUS_CONNECTION_FAILURE                    = DESCRIPTION_FACILITY_RENDEZVOUS + 1,
        DESCRIPTION_RENDEZVOUS_NOT_AUTHENTICATED                     = DESCRIPTION_FACILITY_RENDEZVOUS + 2,
        DESCRIPTION_RENDEZVOUS_INVALID_USERNAME                      = DESCRIPTION_FACILITY_RENDEZVOUS + 3,
        DESCRIPTION_RENDEZVOUS_INVALID_PASSWORD                      = DESCRIPTION_FACILITY_RENDEZVOUS + 4,
        DESCRIPTION_RENDEZVOUS_USERNAME_ALREADY_EXISTS               = DESCRIPTION_FACILITY_RENDEZVOUS + 5,
        DESCRIPTION_RENDEZVOUS_ACCOUNT_DISABLED                      = DESCRIPTION_FACILITY_RENDEZVOUS + 6,
        DESCRIPTION_RENDEZVOUS_ACCOUNT_EXPIRED                       = DESCRIPTION_FACILITY_RENDEZVOUS + 7,
        DESCRIPTION_RENDEZVOUS_CONCURRENT_LOGIN_DENIED               = DESCRIPTION_FACILITY_RENDEZVOUS + 8,
        DESCRIPTION_RENDEZVOUS_ENCRYPTION_FAILURE                    = DESCRIPTION_FACILITY_RENDEZVOUS + 9,
        DESCRIPTION_RENDEZVOUS_INVALID_PID                           = DESCRIPTION_FACILITY_RENDEZVOUS + 10,
        DESCRIPTION_RENDEZVOUS_MAX_CONNECTIONS_REACHED               = DESCRIPTION_FACILITY_RENDEZVOUS + 11,
        DESCRIPTION_RENDEZVOUS_INVALID_GID                           = DESCRIPTION_FACILITY_RENDEZVOUS + 12,
        DESCRIPTION_RENDEZVOUS_INVALID_THREAD_ID                     = DESCRIPTION_FACILITY_RENDEZVOUS + 13,
        DESCRIPTION_RENDEZVOUS_INVALID_OPERATION_IN_LIVE_ENVIRONMENT = DESCRIPTION_FACILITY_RENDEZVOUS + 14,
        DESCRIPTION_RENDEZVOUS_DUPLICATE_ENTRY                       = DESCRIPTION_FACILITY_RENDEZVOUS + 15,
        DESCRIPTION_RENDEZVOUS_CONTROL_SCRIPT_FAILURE                = DESCRIPTION_FACILITY_RENDEZVOUS + 16,
        DESCRIPTION_RENDEZVOUS_CLASS_NOT_FOUND                       = DESCRIPTION_FACILITY_RENDEZVOUS + 17,
        DESCRIPTION_RENDEZVOUS_SESSION_VOID                          = DESCRIPTION_FACILITY_RENDEZVOUS + 18,
        DESCRIPTION_RENDEZVOUS_LSP_GATEWAY_UNREACHABLE               = DESCRIPTION_FACILITY_RENDEZVOUS + 19,
        DESCRIPTION_RENDEZVOUS_DDL_MISMATCH                          = DESCRIPTION_FACILITY_RENDEZVOUS + 20,
        DESCRIPTION_RENDEZVOUS_INVALID_FTP_INFO                      = DESCRIPTION_FACILITY_RENDEZVOUS + 21,
        DESCRIPTION_RENDEZVOUS_SESSION_FULL                          = DESCRIPTION_FACILITY_RENDEZVOUS + 22,
        DESCRIPTION_RENDEZVOUS_UNDEFINED                             = DESCRIPTION_FACILITY_RENDEZVOUS + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_PYTHONCORE_SUCCESS                               = DESCRIPTION_FACILITY_PYTHONCORE + 0,
        DESCRIPTION_PYTHONCORE_EXCEPTION                             = DESCRIPTION_FACILITY_PYTHONCORE + 1,
        DESCRIPTION_PYTHONCORE_TYPE_ERROR                            = DESCRIPTION_FACILITY_PYTHONCORE + 2,
        DESCRIPTION_PYTHONCORE_INDEX_ERROR                           = DESCRIPTION_FACILITY_PYTHONCORE + 3,
        DESCRIPTION_PYTHONCORE_INVALID_REFERENCE                     = DESCRIPTION_FACILITY_PYTHONCORE + 4,
        DESCRIPTION_PYTHONCORE_CALL_FAILURE                          = DESCRIPTION_FACILITY_PYTHONCORE + 5,
        DESCRIPTION_PYTHONCORE_MEMORY_ERROR                          = DESCRIPTION_FACILITY_PYTHONCORE + 6,
        DESCRIPTION_PYTHONCORE_KEY_ERROR                             = DESCRIPTION_FACILITY_PYTHONCORE + 7,
        DESCRIPTION_PYTHONCORE_OPERATION_ERROR                       = DESCRIPTION_FACILITY_PYTHONCORE + 8,
        DESCRIPTION_PYTHONCORE_CONVERSION_ERROR                      = DESCRIPTION_FACILITY_PYTHONCORE + 9,
        DESCRIPTION_PYTHONCORE_VALIDATION_ERROR                      = DESCRIPTION_FACILITY_PYTHONCORE + 10,
        DESCRIPTION_PYTHONCORE_UNDEFINED                             = DESCRIPTION_FACILITY_PYTHONCORE + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_TRANSPORT_SUCCESS                                = DESCRIPTION_FACILITY_TRANSPORT + 0,
        DESCRIPTION_TRANSPORT_UNKNOWN                                = DESCRIPTION_FACILITY_TRANSPORT + 1,
        DESCRIPTION_TRANSPORT_CONNECTION_FAILURE                     = DESCRIPTION_FACILITY_TRANSPORT + 2,
        DESCRIPTION_TRANSPORT_INVALID_URL                            = DESCRIPTION_FACILITY_TRANSPORT + 3,
        DESCRIPTION_TRANSPORT_INVALID_KEY                            = DESCRIPTION_FACILITY_TRANSPORT + 4,
        DESCRIPTION_TRANSPORT_INVALID_URL_TYPE                       = DESCRIPTION_FACILITY_TRANSPORT + 5,
        DESCRIPTION_TRANSPORT_DUPLICATE_ENDPOINT                     = DESCRIPTION_FACILITY_TRANSPORT + 6,
        DESCRIPTION_TRANSPORT_IO_ERROR                               = DESCRIPTION_FACILITY_TRANSPORT + 7,
        DESCRIPTION_TRANSPORT_TIMEOUT                                = DESCRIPTION_FACILITY_TRANSPORT + 8,
        DESCRIPTION_TRANSPORT_CONNECTION_RESET                       = DESCRIPTION_FACILITY_TRANSPORT + 9,
        DESCRIPTION_TRANSPORT_INCORRECT_REMOTE_AUTHENTICATION        = DESCRIPTION_FACILITY_TRANSPORT + 10,
        DESCRIPTION_TRANSPORT_SERVER_REQUEST_ERROR                   = DESCRIPTION_FACILITY_TRANSPORT + 11,
        DESCRIPTION_TRANSPORT_DECOMPRESSION_FAILURE                  = DESCRIPTION_FACILITY_TRANSPORT + 12,
        DESCRIPTION_TRANSPORT_CONGESTED_END_POINT                    = DESCRIPTION_FACILITY_TRANSPORT + 13,
        DESCRIPTION_TRANSPORT_UPNP_CANNOT_INIT                       = DESCRIPTION_FACILITY_TRANSPORT + 14,
        DESCRIPTION_TRANSPORT_UPNP_CANNOT_ADD_MAPPING                = DESCRIPTION_FACILITY_TRANSPORT + 15,
        DESCRIPTION_TRANSPORT_NAT_PMP_CANNOT_INIT                    = DESCRIPTION_FACILITY_TRANSPORT + 16,
        DESCRIPTION_TRANSPORT_NAT_PMP_CANNOT_ADD_MAPPING             = DESCRIPTION_FACILITY_TRANSPORT + 17,
        DESCRIPTION_TRANSPORT_UNDEFINED                              = DESCRIPTION_FACILITY_TRANSPORT + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_DOCORE_SUCCESS                                   = DESCRIPTION_FACILITY_DOCORE + 0,
        DESCRIPTION_DOCORE_CALL_POSTPONED                            = DESCRIPTION_FACILITY_DOCORE + 1,
        DESCRIPTION_DOCORE_STATION_NOT_REACHED                       = DESCRIPTION_FACILITY_DOCORE + 2,
        DESCRIPTION_DOCORE_TARGET_STATION_DISCONNECT                 = DESCRIPTION_FACILITY_DOCORE + 3,
        DESCRIPTION_DOCORE_LOCAL_STATION_LEAVING                     = DESCRIPTION_FACILITY_DOCORE + 4,
        DESCRIPTION_DOCORE_OBJECT_NOT_FOUND                          = DESCRIPTION_FACILITY_DOCORE + 5,
        DESCRIPTION_DOCORE_INVALID_ROLE                              = DESCRIPTION_FACILITY_DOCORE + 6,
        DESCRIPTION_DOCORE_CALL_TIMEOUT                              = DESCRIPTION_FACILITY_DOCORE + 7,
        DESCRIPTION_DOCORE_RMC_DISPATCH_FAILED                       = DESCRIPTION_FACILITY_DOCORE + 8,
        DESCRIPTION_DOCORE_MIGRATION_IN_PROGRESS                     = DESCRIPTION_FACILITY_DOCORE + 9,
        DESCRIPTION_DOCORE_NO_AUTHORITY                              = DESCRIPTION_FACILITY_DOCORE + 10,
        DESCRIPTION_DOCORE_NO_TARGET_STATION_SPECIFIED               = DESCRIPTION_FACILITY_DOCORE + 11,
        DESCRIPTION_DOCORE_JOIN_FAILED                               = DESCRIPTION_FACILITY_DOCORE + 12,
        DESCRIPTION_DOCORE_JOIN_DENIED                               = DESCRIPTION_FACILITY_DOCORE + 13,
        DESCRIPTION_DOCORE_CONNECTIVITY_TEST_FAILED                  = DESCRIPTION_FACILITY_DOCORE + 14,
        DESCRIPTION_DOCORE_UNKNOWN                                   = DESCRIPTION_FACILITY_DOCORE + 15,
        DESCRIPTION_DOCORE_UNFREED_REFERENCES                        = DESCRIPTION_FACILITY_DOCORE + 16,
        DESCRIPTION_DOCORE_UNDEFINED                                 = DESCRIPTION_FACILITY_DOCORE + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_FPD_SUCCESS                                      = DESCRIPTION_FACILITY_FPD + 0,
        DESCRIPTION_RMC_NOT_CALLED                                   = DESCRIPTION_FACILITY_FPD + 1,
        DESCRIPTION_DAEMON_NOT_INITIALIZED                           = DESCRIPTION_FACILITY_FPD + 2,
        DESCRIPTION_DAEMON_ALREADY_INITIALIZED                       = DESCRIPTION_FACILITY_FPD + 3,
        DESCRIPTION_NOT_CONNECTED                                    = DESCRIPTION_FACILITY_FPD + 4,
        DESCRIPTION_CONNECTED                                        = DESCRIPTION_FACILITY_FPD + 5,
        DESCRIPTION_INITIALIZATION_FAILURE                           = DESCRIPTION_FACILITY_FPD + 6,
        DESCRIPTION_OUT_OF_MEMORY                                    = DESCRIPTION_FACILITY_FPD + 7,
        DESCRIPTION_RMC_FAILED                                       = DESCRIPTION_FACILITY_FPD + 8,
        DESCRIPTION_INVALID_ARGUMENT                                 = DESCRIPTION_FACILITY_FPD + 9,
        DESCRIPTION_INVALID_LOCAL_ACCOUNT_ID                         = DESCRIPTION_FACILITY_FPD + 10,
        DESCRIPTION_INVALID_PRINCIPAL_ID                             = DESCRIPTION_FACILITY_FPD + 11,
        DESCRIPTION_INVALID_LOCAL_FRIEND_CODE                        = DESCRIPTION_FACILITY_FPD + 12,
        DESCRIPTION_LOCAL_ACCOUNT_NOT_EXISTS                         = DESCRIPTION_FACILITY_FPD + 13,
        DESCRIPTION_LOCAL_ACCOUNT_NOT_LOADED                         = DESCRIPTION_FACILITY_FPD + 14,
        DESCRIPTION_LOCAL_ACCOUNT_ALREADY_LOADED                     = DESCRIPTION_FACILITY_FPD + 15,
        DESCRIPTION_FRIEND_ALREADY_EXISTS                            = DESCRIPTION_FACILITY_FPD + 16,
        DESCRIPTION_FRIEND_NOT_EXISTS                                = DESCRIPTION_FACILITY_FPD + 17,
        DESCRIPTION_FRIEND_NUM_MAX                                   = DESCRIPTION_FACILITY_FPD + 18,
        DESCRIPTION_NOT_FRIEND                                       = DESCRIPTION_FACILITY_FPD + 19,
        DESCRIPTION_FILE_IO_ERROR                                    = DESCRIPTION_FACILITY_FPD + 20,
        DESCRIPTION_P2P_INTERNET_PROHIBITED                          = DESCRIPTION_FACILITY_FPD + 21,
        DESCRIPTION_UNKNOWN                                          = DESCRIPTION_FACILITY_FPD + 22,
        DESCRIPTION_INVALID_STATE                                    = DESCRIPTION_FACILITY_FPD + 23,
        DESCRIPTION_MII_NOT_EXISTS                                   = DESCRIPTION_FACILITY_FPD + 24,
        DESCRIPTION_ADD_FRIEND_PROHIBITED                            = DESCRIPTION_FACILITY_FPD + 25,
        DESCRIPTION_INVALID_PREFERENCE                               = DESCRIPTION_FACILITY_FPD + 26,
        DESCRIPTION_FPD_UNDEFINED                                    = DESCRIPTION_FACILITY_FPD + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_AUTHENTICATION_SUCCESS                           = DESCRIPTION_FACILITY_AUTHENTICATION + 0,
        DESCRIPTION_AUTHENTICATION_NAS_AUTHENTICATE_ERROR            = DESCRIPTION_FACILITY_AUTHENTICATION + 1,
        DESCRIPTION_AUTHENTICATION_TOKEN_PARSE_ERROR                 = DESCRIPTION_FACILITY_AUTHENTICATION + 2,
        DESCRIPTION_AUTHENTICATION_HTTP_CONNECTION_ERROR             = DESCRIPTION_FACILITY_AUTHENTICATION + 3,
        DESCRIPTION_AUTHENTICATION_HTTP_DNS_ERROR                    = DESCRIPTION_FACILITY_AUTHENTICATION + 4,
        DESCRIPTION_AUTHENTICATION_HTTP_GET_PROXY_SETTING            = DESCRIPTION_FACILITY_AUTHENTICATION + 5,
        DESCRIPTION_AUTHENTICATION_TOKEN_EXPIRED                     = DESCRIPTION_FACILITY_AUTHENTICATION + 6,
        DESCRIPTION_AUTHENTICATION_VALIDATION_FAILED                 = DESCRIPTION_FACILITY_AUTHENTICATION + 7,
        DESCRIPTION_AUTHENTICATION_INVALID_PARAM                     = DESCRIPTION_FACILITY_AUTHENTICATION + 8,
        DESCRIPTION_AUTHENTICATION_PRINCIPAL_ID_UNMATCHED            = DESCRIPTION_FACILITY_AUTHENTICATION + 9,
        DESCRIPTION_AUTHENTICATION_MOVE_COUNT_UNMATCH                = DESCRIPTION_FACILITY_AUTHENTICATION + 10,
        DESCRIPTION_AUTHENTICATION_UNDER_MAINTENANCE                 = DESCRIPTION_FACILITY_AUTHENTICATION + 11,
        DESCRIPTION_AUTHENTICATION_UNSUPPORTED_VERSION               = DESCRIPTION_FACILITY_AUTHENTICATION + 12,
        DESCRIPTION_AUTHENTICATION_UNKNOWN                           = DESCRIPTION_FACILITY_AUTHENTICATION + 13,
        DESCRIPTION_AUTHENTICATION_UNDEFINED                         = DESCRIPTION_FACILITY_AUTHENTICATION + detail::DESCRIPTION_RETURN_CODE_UNDEFINED,

        DESCRIPTION_FACILITY_CTR        = 0 << detail::DESCRIPTION_FACILITY_SHIFT,

        DESCRIPTION_INVALID_FRIEND_CODE = DESCRIPTION_FACILITY_CTR + 1,
        DESCRIPTION_NOT_LOGGED_IN,
        DESCRIPTION_NOT_FRIENDS_RESULT,
        DESCRIPTION_UNDEFINED_FACILITY,
        DESCRIPTION_AC_NOT_CONNECTED
    };


    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultCoreTimeOut,
        Result::LEVEL_STATUS,   Result::SUMMARY_CANCELLED,        Result::MODULE_NN_FRIENDS,
        DESCRIPTION_CORE_TIMEOUT
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultCoreCallInitiationFailure,
        Result::LEVEL_STATUS,   Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_CORE_CALL_INITIATION_FAILURE
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultTransportConnectionFailure,
        Result::LEVEL_STATUS,   Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_TRANSPORT_CONNECTION_FAILURE
    );


    /* Please see man pages for details 
        
        
               
    */
    NN_DEFINE_RESULT_CONST(
        ResultRmcNotCalled,
        Result::LEVEL_SUCCESS,   Result::SUMMARY_SUCCESS,          Result::MODULE_NN_FRIENDS,
        DESCRIPTION_RMC_NOT_CALLED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultDaemonNotInitialized,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_DAEMON_NOT_INITIALIZED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultDaemonAlreadyInitialized,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_DAEMON_ALREADY_INITIALIZED
    );

    /* Please see man pages for details 
        
        
        
               
    */    
    NN_DEFINE_RESULT_CONST(
        ResultNotConnected,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_NOT_CONNECTED
    );

    /* Please see man pages for details 
        
        
        
               
    */    
    NN_DEFINE_RESULT_CONST(
        ResultConnected,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_CONNECTED
    );

    /* Please see man pages for details 
        
        
        
    */    
    NN_DEFINE_RESULT_CONST(
        ResultInitializationFailure,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INITIALIZATION_FAILURE
    );

    /* Please see man pages for details 
        
        
        
    */    
    NN_DEFINE_RESULT_CONST(
        ResultOutOfMemory,
        Result::LEVEL_STATUS,    Result::SUMMARY_OUT_OF_RESOURCE,  Result::MODULE_NN_FRIENDS,
        DESCRIPTION_OUT_OF_MEMORY
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultRmcFailed,
        Result::LEVEL_PERMANENT, Result::SUMMARY_CANCELLED,        Result::MODULE_NN_FRIENDS,
        DESCRIPTION_RMC_FAILED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidArgument,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_ARGUMENT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidLocalAccountId,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_LOCAL_ACCOUNT_ID
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidPrincipalId,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_PRINCIPAL_ID
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidLocalFriendCode,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_LOCAL_FRIEND_CODE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultLocalAccountNotExists,
        Result::LEVEL_STATUS,    Result::SUMMARY_NOT_FOUND,        Result::MODULE_NN_FRIENDS,
        DESCRIPTION_LOCAL_ACCOUNT_NOT_EXISTS
    );

    /* Please see man pages for details 
        
        
               
    */
    NN_DEFINE_RESULT_CONST(
        ResultLocalAccountNotLoaded,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_LOCAL_ACCOUNT_NOT_LOADED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultLocalAccountAlreadyLoaded,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_LOCAL_ACCOUNT_ALREADY_LOADED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultFriendAlreadyExists,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT,   Result::MODULE_NN_FRIENDS,
        DESCRIPTION_FRIEND_ALREADY_EXISTS
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultFriendNotExists,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT,   Result::MODULE_NN_FRIENDS,
        DESCRIPTION_FRIEND_NOT_EXISTS
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultFriendNumMax,
        Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE,  Result::MODULE_NN_FRIENDS,
        DESCRIPTION_FRIEND_NUM_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultNotFriend,
        Result::LEVEL_PERMANENT, Result::SUMMARY_WRONG_ARGUMENT,   Result::MODULE_NN_FRIENDS,
        DESCRIPTION_NOT_FRIEND
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultFileIoError,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_FILE_IO_ERROR
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultP2pInternetProhibited,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_P2P_INTERNET_PROHIBITED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultUnknown,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_UNKNOWN
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidState,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_STATE
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultMiiNotExists,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_MII_NOT_EXISTS
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAddFriendProhibited,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_ADD_FRIEND_PROHIBITED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidPreference,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_PREFERENCE
    );


    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultNasAuthenticationError,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_NAS_AUTHENTICATE_ERROR
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationTokenParseError,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_TOKEN_PARSE_ERROR
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationHttpConnectionError,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_HTTP_CONNECTION_ERROR
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationDnsError,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_HTTP_DNS_ERROR
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationHttpGetProxySetting,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_HTTP_GET_PROXY_SETTING
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationTokenExpired,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_TOKEN_EXPIRED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationValidationFailed,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_VALIDATION_FAILED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationInvalidParam,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_INVALID_PARAM
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationPrincipalIdUnmatched,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_PRINCIPAL_ID_UNMATCHED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationMoveCountUnmatch,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_MOVE_COUNT_UNMATCH
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationUnderMaintenance,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_UNDER_MAINTENANCE
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationUnsupportedVersion,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_UNSUPPORTED_VERSION
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationUnknown,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_UNKNOWN
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAuthenticationUndefined,
        Result::LEVEL_STATUS,    Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AUTHENTICATION_UNDEFINED
    );


    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidFriendCode,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        DESCRIPTION_INVALID_FRIEND_CODE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultNotLoggedIn,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_NOT_LOGGED_IN
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultNotFriendsResult,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        DESCRIPTION_NOT_FRIENDS_RESULT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultUndefinedFacilitySuccess,
        Result::LEVEL_SUCCESS,   Result::SUMMARY_SUCCESS,          Result::MODULE_NN_FRIENDS,
        DESCRIPTION_UNDEFINED_FACILITY
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultUndefinedFacilityFailure,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INTERNAL,         Result::MODULE_NN_FRIENDS,
        DESCRIPTION_UNDEFINED_FACILITY
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAcNotConnected,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        DESCRIPTION_AC_NOT_CONNECTED
    );


    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultNotInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_NOT_INITIALIZED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyInitialized,
        Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_ALREADY_INITIALIZED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidHandle,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_INVALID_HANDLE
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultInvalidPointer,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_INVALID_POINTER
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultTooLarge,
        Result::LEVEL_USAGE,     Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_TOO_LARGE
    );


    /* Please see man pages for details 
        
        
        
               
    */
    NN_DEFINE_RESULT_CONST(
        ResultAlreadyDone,
        Result::LEVEL_SUCCESS,   Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_ALREADY_DONE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultTemporarilyBusy,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_BUSY
    );


    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultNotAuthorized,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_NOT_AUTHORIZED
    );

    /* Please see man pages for details 
        
        
    */
    NN_DEFINE_RESULT_CONST(
        ResultUnexpectedState,
        Result::LEVEL_STATUS,    Result::SUMMARY_INVALID_STATE,    Result::MODULE_NN_FRIENDS,
        Result::DESCRIPTION_NOT_IMPLEMENTED
    );


    namespace detail {
        inline Result MakeResult(Result::Level level, Result::Summary summary, int description)
            { return Result(level, summary, Result::MODULE_NN_FRIENDS, description); }

        inline Result MakeInfoResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_INFO, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakeFatalResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_FATAL, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakeResetResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_RESET, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakeReInitResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_REINIT, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakeUsageResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_USAGE, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakePermanentResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_PERMANENT, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakeTemporaryResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_TEMPORARY, summary, Result::MODULE_NN_FRIENDS, description); }
        inline Result MakeStatusResult(Result::Summary summary, int description)
            { return Result(Result::LEVEL_STATUS, summary, Result::MODULE_NN_FRIENDS, description); }
    }

} // end of namespace CTR
    using namespace CTR;
} // end of namespace friends
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_FRIENDS_CTR_FRIENDS_RESULT_H_ */
