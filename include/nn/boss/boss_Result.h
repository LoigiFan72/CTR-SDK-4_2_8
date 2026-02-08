/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_RESULT_H_
#define NN_BOSS_BOSS_RESULT_H_

#include <nn/Result.h>
#include <nn/assert.h>

#ifdef __cplusplus

/* Please see man pages for details 
    
*/

namespace nn {
namespace boss {

    /* Please see man pages for details 
     
               
    */
    enum ResultCode
    {
        ER_NONE                         = 0     ,//

    // Boss libraries Argument Error

        //Pointer NULL error
        ER_INVALID_POLICY                       ,//
        ER_INVALID_ACTION                       ,//
        ER_INVALID_OPTION                       ,//
        ER_INVALID_APPIDLIST                    ,//
        ER_INVALID_TASKID_LIST                  ,//
        ER_INVALID_STEPID_LIST                  ,//
        ER_INVALID_NSDATA_IDLIST                ,//
        ER_INVALID_TASKSTATUS                   ,//
        ER_INVALID_PROPERTYVALUE                ,//
        ER_INVALID_NEWARRIVAL_EVENT             ,//
        ER_INVALID_NEWARRIVAL_FLAG              ,//
        ER_INVALID_OPTOUT_FLAG                  ,//
        ER_INVALID_TASKERROR                    ,//
        ER_INVALID_NSDATA_VALUE                 ,//
        ER_INVALID_NSDATA_INFO                  ,//
        ER_INVALID_NSDATA_READFLAG              ,//
        ER_INVALID_NSDATA_TIME                  ,//
        ER_INVALID_NEXTEXECUTETIME              ,//
        ER_HTTP_REQUEST_HEADER_POINTER_NULL     ,//
        ER_INVALID_POLICYLIST_AVAILABILITY      ,//
        ER_INVALID_TESTMODE_AVAILABILITY        ,//
        ER_INVALID_CONFIG_PARENTAL_CONTROL      ,//
        ER_INVALID_CONFIG_EULA_AGREEMENT        ,//
        ER_INVALID_POLICYLIST_ENV_ID            ,//
        ER_INVALID_POLICYLIST_URL               ,//

        //Parameter scope check error
        ER_INVALID_TASK_ID                      ,//
        ER_INVALID_TASK_STEP                    ,//
        ER_INVALID_PROPERTYTYPE                 ,//
        ER_INVALID_URL                          ,//
        ER_INVALID_FILEPATH                     ,//
        ER_INVALID_TASK_PRIORITY                ,//
        ER_INVALID_TASK_TARGETDURATION          ,//
        ER_ACTIONCODE_OUT_OF_RANGE              ,//
        ER_INVALID_NSDATA_SEEK_POSITION         ,//
        ER_INVALID_MAX_HTTP_REQUEST_HEADER      ,//
        ER_INVALID_MAX_CLIENT_CERT              ,//
        ER_INVALID_MAX_ROOT_CA                  ,//
        ER_SCHEDULING_POLICY_OUT_OF_RANGE       ,//
        ER_APINFOTYPE_OUT_OF_RANGE              ,//
        ER_TASK_PERMISSION_OUT_OF_RANGE         ,//

        // Boss lib Execute Error
        ER_WAITFINISH_TIMEOUT                   ,//
        ER_WAITFINISH_TASK_NOT_DONE             ,//

        // Boss lib/Process Execute Error
        ER_IPC_NOT_SESSION_INITIALIZED          ,//
        ER_IPC_PROPERTY_SIZE_ERROR              ,//
        ER_IPC_TOO_MANY_REQUESTS                ,//
        ER_ALREADY_INITIALIZED                  ,//

        // Boss Process Execute Error
        ER_OUT_OF_MEMORY                        ,//
        ER_INVALID_NUMBER_OF_NSD                ,//
        ER_NSDATA_INVALID_FORMAT                ,//

        ER_APLI_NOT_EXIST                       ,//
        ER_TASK_NOT_EXIST                       ,//
        ER_TASK_STEP_NOT_EXIST                  ,//
        ER_APLI_ID_ALREADY_EXIST                ,//
        ER_TASK_ID_ALREADY_EXIST                ,//
        ER_TASK_STEP_ALREADY_EXIST              ,//
        ER_INVALID_SEQUENCE                     ,//
        ER_DATABASE_FULL                        ,//
        ER_CANT_UNREGISTER_TASK                 ,//
        ER_TASK_NOT_REGISTERED                  ,//
        ER_INVALID_FILEHANDLE                   ,//
        ER_INVALID_TASK_SCHEDULING_POLICY       ,//
        ER_INVALID_HTTP_REQUEST_HEADER          ,//
        ER_INVALID_HEADTYPE                     ,//
        ER_STORAGE_ACCESSPERMISSION             ,//
        ER_STORAGE_INSUFFICIENCY                ,//
        ER_INVALID_APPID_STORAGE_NOTFOUND       ,//
        ER_NSDATA_NOTFOUND                      ,//
        ER_INVALID_NSDATA_GETHEAD_SIZE          ,//
        ER_NSDATA_LIST_SIZE_SHORTAGE            ,//
        ER_NSDATA_LIST_UPDATED                  ,//
        ER_NOT_CONNECT_AP_WITH_LOCATION         ,//
        ER_NOT_CONNECT_NETWORK                  ,//
        ER_INVALID_FRIENDCODE                   ,//
        ER_FILE_ACCESS                          ,//
        ER_TASK_ALREADY_PAUSED                  ,//
        ER_TASK_ALREADY_RESUMED                 ,//
        ER_UNEXPECT                             ,//

        RESULT_CODE_LAST                        ,//

        // Boss 2nd Later ResultCode
        ER_INVALID_STORAGE_PARAMETER = 192      ,//
        ER_CFGINFOTYPE_OUT_OF_RANGE             ,//
        ER_INVALID_MAX_HTTP_QUERY               ,//
        ER_INVALID_MAX_DATASTORE_DST            ,//
        ER_NSALIST_INVALID_FORMAT               ,//
        ER_NSALIST_DOWNLOAD_TASK_ERROR          ,//

        // Common ResultCode
        ER_INVALID_SIZE     = nn::Result::DESCRIPTION_INVALID_SIZE      ,//
        ER_INVALID_POINTER  = nn::Result::DESCRIPTION_INVALID_POINTER   ,//
        ER_NOT_FOUND        = nn::Result::DESCRIPTION_NOT_FOUND         ,//
        ER_ALREADY_EXISTS   = nn::Result::DESCRIPTION_ALREADY_EXISTS    ,//
        ER_OUT_OF_RANGE     = nn::Result::DESCRIPTION_OUT_OF_RANGE      ,//

        RESULT_CODE_MAX_VALUE = (0x1u << 10)
    };

    NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInternalResult, Result::LEVEL_STATUS, Result::SUMMARY_INTERNAL, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeOutOfResourceResult, Result::LEVEL_PERMANENT, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInvalidStateResult, Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeCancelledResult, Result::LEVEL_STATUS, Result::SUMMARY_CANCELLED, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeInvalidArgumentResult, Result::LEVEL_PERMANENT, Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeNothingHappenedResult, Result::LEVEL_PERMANENT, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_BOSS);
    NN_DEFINE_RESULT_FUNC_LSM(MakeWouldBlockResult, Result::LEVEL_PERMANENT, Result::SUMMARY_WOULD_BLOCK, Result::MODULE_NN_BOSS);

/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPolicy,
        MakeInvalidArgumentResult, ER_INVALID_POLICY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidAction,
        MakeInvalidArgumentResult, ER_INVALID_ACTION
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidOption,
        MakeInvalidArgumentResult, ER_INVALID_OPTION
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidAppIdList,
        MakeInvalidArgumentResult, ER_INVALID_APPIDLIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskIdList,
        MakeInvalidArgumentResult, ER_INVALID_TASKID_LIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidStepIdList,
        MakeInvalidArgumentResult, ER_INVALID_STEPID_LIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataIdList,
        MakeInvalidArgumentResult, ER_INVALID_NSDATA_IDLIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskStatus,
        MakeInvalidStateResult, ER_INVALID_TASKSTATUS
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPropertyValue,
        MakeInvalidArgumentResult, ER_INVALID_PROPERTYVALUE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNewArrivalEvent,
        MakeInvalidArgumentResult, ER_INVALID_NEWARRIVAL_EVENT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNewArrivalFlag,
        MakeInvalidArgumentResult, ER_INVALID_NEWARRIVAL_FLAG
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidOptoutFlag,
        MakeInvalidArgumentResult, ER_INVALID_OPTOUT_FLAG
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskError,
        MakeInvalidStateResult, ER_INVALID_TASKERROR
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataValue,
        MakeInvalidArgumentResult, ER_INVALID_NSDATA_VALUE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataInfo,
        MakeInvalidArgumentResult, ER_INVALID_NSDATA_INFO
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataReadFlag,
        MakeInvalidArgumentResult, ER_INVALID_NSDATA_READFLAG
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataTime,
        MakeInvalidArgumentResult, ER_INVALID_NSDATA_TIME
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNextExecuteTime,
        MakeInvalidArgumentResult, ER_INVALID_NEXTEXECUTETIME
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultHttpRequestHeaderPointerNull,
        MakeInvalidArgumentResult, ER_HTTP_REQUEST_HEADER_POINTER_NULL
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPolicyListAvailability,
        MakeInvalidArgumentResult, ER_INVALID_POLICYLIST_AVAILABILITY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTestModeAvailability,
        MakeInvalidArgumentResult, ER_INVALID_TESTMODE_AVAILABILITY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidConfigParentalControl,
        MakeInvalidArgumentResult, ER_INVALID_CONFIG_PARENTAL_CONTROL
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidConfigEulaAgreement,
        MakeInvalidArgumentResult, ER_INVALID_CONFIG_EULA_AGREEMENT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPolicyListEnvId,
        MakeInvalidArgumentResult, ER_INVALID_POLICYLIST_ENV_ID
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPolicyListUrl,
        MakeInvalidArgumentResult, ER_INVALID_POLICYLIST_URL
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskId,
        MakeInvalidArgumentResult, ER_INVALID_TASK_ID
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskStep,
        MakeInvalidArgumentResult, ER_INVALID_TASK_STEP
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPropertyType,
        MakeInvalidArgumentResult, ER_INVALID_PROPERTYTYPE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidUrl,
        MakeInvalidArgumentResult, ER_INVALID_URL
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidFilePath,
        MakeInvalidArgumentResult, ER_INVALID_FILEPATH
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskPriority,
        MakeInvalidArgumentResult, ER_INVALID_TASK_PRIORITY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskTargetDuration,
        MakeInvalidArgumentResult, ER_INVALID_TASK_TARGETDURATION
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultActionCodeOutOfRange,
        MakeInvalidArgumentResult, ER_ACTIONCODE_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataSeekPosition,
        MakeInvalidArgumentResult, ER_INVALID_NSDATA_SEEK_POSITION
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidMaxHttpRequestHeader,
        MakeOutOfResourceResult, ER_INVALID_MAX_HTTP_REQUEST_HEADER
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidMaxClientCert,
        MakeOutOfResourceResult, ER_INVALID_MAX_CLIENT_CERT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidMaxRootCa,
        MakeOutOfResourceResult, ER_INVALID_MAX_ROOT_CA
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultSchedulingPolicyOutOfRange,
        MakeInvalidArgumentResult, ER_SCHEDULING_POLICY_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultApInfoTypeOutOfRange,
        MakeInvalidArgumentResult, ER_APINFOTYPE_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskPermissionOutOfRange,
        MakeInvalidArgumentResult, ER_TASK_PERMISSION_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultWaitFinishTimeout,
        MakeWouldBlockResult, ER_WAITFINISH_TIMEOUT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultWaitFinishTaskNotDone,
        MakeWouldBlockResult, ER_WAITFINISH_TASK_NOT_DONE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultIpcNotSessionInitialized,
        MakeInvalidStateResult, ER_IPC_NOT_SESSION_INITIALIZED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultIpcPropertySizeError,
        MakeOutOfResourceResult, ER_IPC_PROPERTY_SIZE_ERROR
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultIpcTooManyRequests,
        MakeOutOfResourceResult, ER_IPC_TOO_MANY_REQUESTS
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAlreadyInitialized,
        MakeInvalidStateResult, ER_ALREADY_INITIALIZED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultOutOfMemory,
        MakeOutOfResourceResult, ER_OUT_OF_MEMORY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNumberOfNsd,
        MakeOutOfResourceResult, ER_INVALID_NUMBER_OF_NSD
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNsDataInvalidFormat,
        MakeOutOfResourceResult, ER_NSDATA_INVALID_FORMAT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAppNotExist,
        MakeInvalidStateResult, ER_APLI_NOT_EXIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskNotExist,
        MakeInvalidStateResult, ER_TASK_NOT_EXIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskStepNotExist,
        MakeInvalidStateResult, ER_TASK_STEP_NOT_EXIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultApliIdAlreadyExist,
        MakeInvalidStateResult, ER_APLI_ID_ALREADY_EXIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskIdAlreadyExist,
        MakeInvalidStateResult, ER_TASK_ID_ALREADY_EXIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskStepAlreadyExist,
        MakeInvalidStateResult, ER_TASK_STEP_ALREADY_EXIST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidSequence,
        MakeInvalidStateResult, ER_INVALID_SEQUENCE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultDatabaseFull,
        MakeInvalidStateResult, ER_DATABASE_FULL
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultCantUnregisterTask,
        MakeInvalidStateResult, ER_CANT_UNREGISTER_TASK
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskNotRegistered,
        MakeInvalidStateResult, ER_TASK_NOT_REGISTERED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidFileHandle,
        MakeInvalidStateResult, ER_INVALID_FILEHANDLE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidTaskSchedulingPolicy,
        MakeInvalidStateResult, ER_INVALID_TASK_SCHEDULING_POLICY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidHttpRequestHeader,
        MakeInvalidStateResult, ER_INVALID_HTTP_REQUEST_HEADER
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidHeadType,
        MakeInvalidStateResult, ER_INVALID_HEADTYPE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultStorageAccessPermission,
        MakeInvalidStateResult, ER_STORAGE_ACCESSPERMISSION
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultStorageInsufficiency,
        MakeInvalidStateResult, ER_STORAGE_INSUFFICIENCY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultStorageNotFound,
        MakeInvalidStateResult, ER_INVALID_APPID_STORAGE_NOTFOUND
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNsDataNotFound,
        MakeInvalidStateResult, ER_NSDATA_NOTFOUND
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidNsDataGetHeadSize,
        MakeInternalResult, ER_INVALID_NSDATA_GETHEAD_SIZE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNsDataListSizeShortage,
        MakeWouldBlockResult, ER_NSDATA_LIST_SIZE_SHORTAGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNsDataListUpdated,
        MakeWouldBlockResult, ER_NSDATA_LIST_UPDATED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotConnectApWithLocation,
        MakeInvalidStateResult, ER_NOT_CONNECT_AP_WITH_LOCATION
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotConnectNetwork,
        MakeInvalidStateResult, ER_NOT_CONNECT_NETWORK
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidFriendcode,
        MakeInvalidStateResult, ER_INVALID_FRIENDCODE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultFileAccess,
        MakeInternalResult, ER_FILE_ACCESS
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskAlreadyPaused,
        MakeInternalResult, ER_TASK_ALREADY_PAUSED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultTaskAlreadyResumed,
        MakeInternalResult, ER_TASK_ALREADY_RESUMED
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultUnexpect,
        MakeInternalResult, ER_UNEXPECT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidStorageParameter,
        MakeInvalidArgumentResult, ER_INVALID_STORAGE_PARAMETER
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultCfgInfoTypeOutOfRange,
        MakeInvalidArgumentResult, ER_CFGINFOTYPE_OUT_OF_RANGE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidMaxHttpQuery,
        MakeOutOfResourceResult, ER_INVALID_MAX_HTTP_QUERY
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidMaxDataStoreDst,
        MakeOutOfResourceResult, ER_INVALID_MAX_DATASTORE_DST
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNSAListInvalidFormat,
        MakeOutOfResourceResult, ER_NSALIST_INVALID_FORMAT
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNSAListDownloadTaskError,
        MakeInvalidStateResult, ER_NSALIST_DOWNLOAD_TASK_ERROR
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidSize,
        MakeInvalidArgumentResult, ER_INVALID_SIZE
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultInvalidPointer,
        MakeInvalidArgumentResult, ER_INVALID_POINTER
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultNotFound,
        MakeInvalidStateResult, ER_NOT_FOUND
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultAlreadyExists,
        MakeInvalidStateResult, ER_ALREADY_EXISTS
    );

/* Please see man pages for details 
    
    
    
*/
    NN_DEFINE_RESULT_CONST_LSM(
        ResultOutOfRange,
        MakeInvalidArgumentResult, ER_OUT_OF_RANGE
    );

/*  

*/

    namespace detail {
        /* Please see man pages for details 
         
         
         
         
        */
        inline Result MakePermanentResult(Result::Summary summary, s32 errCode)
        { return nn::MakePermanentResult(summary, Result::MODULE_NN_BOSS, errCode); }

        /* Please see man pages for details 
         
         
         
        */
        inline Result ChangeBossRetCodeToResult(ResultCode returnCode)
        {
            switch(returnCode)
            {
            case ER_NONE:
                return ResultSuccess();
                //break;
            case ER_INVALID_POLICY:
                return ResultInvalidPolicy();
                //break;
            case ER_INVALID_ACTION:
                return ResultInvalidAction();
                //break;
            case ER_INVALID_OPTION:
                return ResultInvalidOption();
                //break;
            case ER_INVALID_APPIDLIST:
                return ResultInvalidAppIdList();
                //break;
            case ER_INVALID_TASKID_LIST:
                return ResultInvalidTaskIdList();
                //break;
            case ER_INVALID_STEPID_LIST:
                return ResultInvalidStepIdList();
                //break;
            case ER_INVALID_NSDATA_IDLIST:
                return ResultInvalidNsDataIdList();
                //break;
            case ER_INVALID_TASKSTATUS:
                return ResultInvalidTaskStatus();
                //break;
            case ER_INVALID_PROPERTYVALUE:
                return ResultInvalidPropertyValue();
                //break;
            case ER_INVALID_NEWARRIVAL_EVENT:
                return ResultInvalidNewArrivalEvent();
                //break;
            case ER_INVALID_NEWARRIVAL_FLAG:
                return ResultInvalidNewArrivalFlag();
                //break;
            case ER_INVALID_OPTOUT_FLAG:
                return ResultInvalidOptoutFlag();
                //break;
            case ER_INVALID_TASKERROR:
                return ResultInvalidTaskError();
                //break;
            case ER_INVALID_NSDATA_VALUE:
                return ResultInvalidNsDataValue();
                //break;
            case ER_INVALID_NSDATA_INFO:
                return ResultInvalidNsDataInfo();
                //break;
            case ER_INVALID_NSDATA_READFLAG:
                return ResultInvalidNsDataReadFlag();
                //break;
            case ER_INVALID_NSDATA_TIME:
                return ResultInvalidNsDataTime();
                //break;
            case ER_INVALID_NEXTEXECUTETIME:
                return ResultInvalidNextExecuteTime();
                //break;
            case ER_HTTP_REQUEST_HEADER_POINTER_NULL:
                return ResultHttpRequestHeaderPointerNull();
                //break;
            case ER_INVALID_POLICYLIST_AVAILABILITY:
                return ResultInvalidPolicyListAvailability();
                //break;
            case ER_INVALID_TESTMODE_AVAILABILITY:
                return ResultInvalidTestModeAvailability();
                //break;
            case ER_INVALID_TASK_ID:
                return ResultInvalidTaskId();
                //break;
            case ER_INVALID_TASK_STEP:
                return ResultInvalidTaskStep();
                //break;
            case ER_INVALID_PROPERTYTYPE:
                return ResultInvalidPropertyType();
                //break;
            case ER_INVALID_URL:
                return ResultInvalidUrl();
                //break;
            case ER_INVALID_FILEPATH:
                return ResultInvalidFilePath();
                //break;
            case ER_INVALID_TASK_PRIORITY:
                return ResultInvalidTaskPriority();
                //break;
            case ER_INVALID_TASK_TARGETDURATION:
                return ResultInvalidTaskTargetDuration();
                //break;
            case ER_ACTIONCODE_OUT_OF_RANGE:
                return ResultActionCodeOutOfRange();
                //break;
            case ER_INVALID_NSDATA_SEEK_POSITION:
                return ResultInvalidNsDataSeekPosition();
                //break;
            case ER_INVALID_MAX_HTTP_REQUEST_HEADER:
                return ResultInvalidMaxHttpRequestHeader();
                //break;
            case ER_INVALID_MAX_CLIENT_CERT:
                return ResultInvalidMaxClientCert();
                //break;
            case ER_INVALID_MAX_ROOT_CA:
                return ResultInvalidMaxRootCa();
                //break;
            case ER_SCHEDULING_POLICY_OUT_OF_RANGE:
                return ResultSchedulingPolicyOutOfRange();
                //break;
            case ER_APINFOTYPE_OUT_OF_RANGE:
                return ResultApInfoTypeOutOfRange();
                //break;
            case ER_TASK_PERMISSION_OUT_OF_RANGE:
                return ResultTaskPermissionOutOfRange();
                //break;
            case ER_WAITFINISH_TIMEOUT:
                return ResultWaitFinishTimeout();
                //break;
            case ER_WAITFINISH_TASK_NOT_DONE:
                return ResultWaitFinishTaskNotDone();
                //break;
            case ER_IPC_NOT_SESSION_INITIALIZED:
                return ResultIpcNotSessionInitialized();
                //break;
            case ER_IPC_PROPERTY_SIZE_ERROR:
                return ResultIpcPropertySizeError();
                //break;
            case ER_IPC_TOO_MANY_REQUESTS:
                return ResultIpcTooManyRequests();
                //break;
            case ER_ALREADY_INITIALIZED:
                return ResultAlreadyInitialized();
                //break;
            case ER_OUT_OF_MEMORY:
                return ResultOutOfMemory();
                //break;
            case ER_INVALID_NUMBER_OF_NSD:
                return ResultInvalidNumberOfNsd();
                //break;
            case ER_NSDATA_INVALID_FORMAT:
                return ResultNsDataInvalidFormat();
                //break;
            case ER_APLI_NOT_EXIST:
                return ResultAppNotExist();
                //break;
            case ER_TASK_NOT_EXIST:
                return ResultTaskNotExist();
                //break;
            case ER_TASK_STEP_NOT_EXIST:
                return ResultTaskStepNotExist();
                //break;
            case ER_APLI_ID_ALREADY_EXIST:
                return ResultApliIdAlreadyExist();
                //break;
            case ER_TASK_ID_ALREADY_EXIST:
                return ResultTaskIdAlreadyExist();
                //break;
            case ER_TASK_STEP_ALREADY_EXIST:
                return ResultTaskStepAlreadyExist();
                //break;
            case ER_INVALID_SEQUENCE:
                return ResultInvalidSequence();
                //break;
            case ER_DATABASE_FULL:
                return ResultDatabaseFull();
                //break;
            case ER_CANT_UNREGISTER_TASK:
                return ResultCantUnregisterTask();
                //break;
            case ER_TASK_NOT_REGISTERED:
                return ResultTaskNotRegistered();
                //break;
            case ER_INVALID_FILEHANDLE:
                return ResultInvalidFileHandle();
                //break;
            case ER_INVALID_TASK_SCHEDULING_POLICY:
                return ResultInvalidTaskSchedulingPolicy();
                //break;
            case ER_INVALID_HTTP_REQUEST_HEADER:
                return ResultInvalidHttpRequestHeader();
                //break;
            case ER_INVALID_HEADTYPE:
                return ResultInvalidHeadType();
                //break;
            case ER_STORAGE_ACCESSPERMISSION:
                return ResultStorageAccessPermission();
                //break;
            case ER_STORAGE_INSUFFICIENCY:
                return ResultStorageInsufficiency();
                //break;
            case ER_INVALID_APPID_STORAGE_NOTFOUND:
                return ResultStorageNotFound();
                //break;
            case ER_NSDATA_NOTFOUND:
                return ResultNsDataNotFound();
                //break;
            case ER_INVALID_NSDATA_GETHEAD_SIZE:
                return ResultInvalidNsDataGetHeadSize();
            case ER_NSDATA_LIST_SIZE_SHORTAGE:
                return ResultNsDataListSizeShortage();
                //break;
            case ER_NSDATA_LIST_UPDATED:
                return ResultNsDataListUpdated();
                //break;
            case ER_NOT_CONNECT_AP_WITH_LOCATION:
                return ResultNotConnectApWithLocation();
                //break;
            case ER_NOT_CONNECT_NETWORK:
                return ResultNotConnectNetwork();
                //break;
            case ER_INVALID_FRIENDCODE:
                return ResultInvalidFriendcode();
                //break;
            case ER_FILE_ACCESS:
                return ResultFileAccess();
                //break;
            case ER_TASK_ALREADY_PAUSED:
                return ResultTaskAlreadyPaused();
                //break;
            case ER_TASK_ALREADY_RESUMED:
                return ResultTaskAlreadyResumed();
                //break;
            case ER_UNEXPECT:
                return ResultUnexpect();
                //break;
            case ER_INVALID_STORAGE_PARAMETER:
                return ResultInvalidStorageParameter();
                //break;
            case ER_CFGINFOTYPE_OUT_OF_RANGE:
                return ResultCfgInfoTypeOutOfRange();
                //break;
            case ER_INVALID_MAX_HTTP_QUERY:
                return ResultInvalidMaxHttpQuery();
                //break;
            case ER_INVALID_MAX_DATASTORE_DST:
                return ResultInvalidMaxDataStoreDst();
                //break;
            case ER_NSALIST_INVALID_FORMAT:
                return ResultNSAListInvalidFormat();
                //break;
            case ER_NSALIST_DOWNLOAD_TASK_ERROR:
                return ResultNSAListDownloadTaskError();
                //break;
            case ER_INVALID_SIZE:
                return ResultInvalidSize();
                //break;
            case ER_INVALID_POINTER:
                return ResultInvalidPointer();
                //break;
            case ER_NOT_FOUND:
                return ResultNotFound();
                //break;
            case ER_ALREADY_EXISTS:
                return ResultAlreadyExists();
                //break;
            case ER_OUT_OF_RANGE:
                return ResultOutOfRange();
                //break;

            default:
                return ResultUnexpect();
                //break;
            }
        }
    }
}
}
#endif // __cplusplus

#endif /* NN_BOSS_BOSS_RESULT_H_ */
