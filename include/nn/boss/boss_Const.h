/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_Const.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_CONST_H_
#define NN_BOSS_BOSS_CONST_H_

#include <nn/types.h>
#include <nn/Result.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

        // NSD data types
        static const bit32 DATA_TYPE_ALL            = 0xffffffff;   //
        static const bit32 DATA_TYPE_APPDATA        = 0x00010000;   //
        static const bit32 DATA_TYPE_NEWS           = 0x00020000;   //
        static const bit32 DATA_TYPE_EXBANNER       = 0x00040000;   //
        static const bit32 DATA_TYPE_DATASTORE      = 0x00080000;   //

        // BOSS system constants
        static const u32 MAX_FILEPATH_LENGTH        = 256;          //
        static const u32 MAX_URL_LENGTH             = 512;          //
        static const u32 MAX_HTTP_HEADER_LABEL      = 32;           //
        static const u32 MAX_HTTP_HEADER_VALUE      = 256;          //
        static const u32 MAX_HTTP_HEADER            = 3;            //
        static const u32 MAX_HTTP_QUERY_NAME        = 15;           //
        static const u32 MAX_HTTP_QUERY_VALUE       = 16;           //
        static const u32 MAX_HTTP_QUERY             = 3;            //
        static const u32 MAX_ROOT_CA                = 3;            //
        static const u32 MAX_CLIENT_CERT            = 1;            //
        static const u32 TASK_ID_LENGTH             = 8;            //
        static const u32 MAX_ERROR_MESSAGE          = 256;          //
        static const u32 MAX_APPLICATION_ID         = 128;          //
        static const u32 MAX_TASK_ID                = 128;          //
        static const u32 MAX_STEP_ID                = 128;          //
        static const u32 CURRENT_STEP_ID            = MAX_STEP_ID;  //
        static const u32 DEFAULT_STEP_ID            = 0;            //
        static const u32 U32_CANNOT_GET_DATA        = 0xFFFFFFFF;   //
        static const u32 MAX_LASTMODIFIED_LENGTH    = 64;           //
        static const u32 UNLIMITED_COUNT            = 0xFFFFFFFF;   //
        static const u32 MAX_STORAGE_ENTRY_COUNT    = 2000;         //
        static const u32 DEFAULT_STORAGE_ENTRY_COUNT = 0;           //
        static const u32 MAX_STORAGE_RECYCLE_COUNT  = 32;           //
        static const u32 MAX_ACCESS_KEY_LENGTH      = 9;            //
        static const u32 MAX_DST_PRINCIPAL_ID       = 100;          //
        static const u32 MAX_NEWS_SUBJECT_LENGTH    = 32;           //
        static const u32 MAX_NEWS_MESSAGE_LENGTH    = 150;          //
        static const u32 MAX_NEWS_JUMP_PARAM        = 8;            //
        static const u32 MAX_TASK_FILE_PARAM        = 512;          //
        static const char FG_ONLY_TASK_ID[]         ="FGONLYT";     //

        /* Please see man pages for details 
            
                   
        */
        enum PositionBase
        {
            /* Please see man pages for details 
                
            */
            POSITION_BASE_BEGIN,

            /* Please see man pages for details 
                
            */
            POSITION_BASE_CURRENT,

            /* Please see man pages for details 
                
            */
            POSITION_BASE_END
        };

        /* Please see man pages for details 
            
                   
        */
        enum PropertyType
        {
            // Constants for referencing TaskPolicy attributes
            TASK_PRIORITY,              //
            TASK_SCHEDULING_POLICY,     //
            TASK_TARGET_DURATION,       //
            TASK_EXEC_INTERVAL,         //
            TASK_EXEC_COUNT,            //
            TASK_PERMISSION,            //

            // Constants for referencing TaskAction attributes
            ACTION_CODE,                //
            ACTION_URL,                 //
            ACTION_OFFSET,              //
            ACTION_FILEDESC,            //
            ACTION_FILEPATH,            //
            ACTION_FILEPATH_W,          //
            ACTION_FILE_HANDLE,         //
            ACTION_HTTP_HEADER,         //
            ACTION_CLIENT_CERT,         //
            ACTION_ROOT_CA,             //
            ACTION_PRIVATE_CLIENT_CERT, //
            ACTION_PRIVATE_ROOT_CA,     //
            ACTION_AP_INFO,             //
            ACTION_CLIENT_CERT_NUM,     //
            ACTION_ROOT_CA_NUM,         //
            ACTION_LAST_MODIFIED_TIME,  //
            ACTION_SERIAL_ID,           //
            SIGNAL_TASK_EVENT,          //

            // Constants for referencing TaskOption attributes
            TASK_EXEC_OPTION,           //
            TASK_STEP,                  //
            TASK_OPTION_TARGET_STEP,    //
            TASK_OPTION_PARAM1,         //
            TASK_OPTION_PARAM2,         //

            // Constants for referencing TaskStatus attributes
            TASK_STATE_CODE,            //
            TASK_STATE_TASK,            //
            TASK_STATE_RESUME,          //
            TASK_RESULT_CODE,           //
            TASK_SERVICE_STATUS,        //
            TASK_SERVICE_TERMINATED,    //
            TASK_COMM_ERROR_CODE,       //
            TASK_CURRENT_PRIORITY,      //
            TASK_EXECUTE_COUNT,         //
            TASK_PENDING_TIME,          //
            TASK_REMAIN_TIME,           //
            TASK_START_TIME,            //
            TASK_STEP_START_TIME,       //
            TASK_PROGRESS,              //
            TASK_DATA_SIZE,             //
            TASK_CURRENT_STEP,          //
            TASK_ACTIVE_RATE,           //
            TASK_REQUEST_RATE,          //
            TASK_LAST_MODIFIED_TIME,    //

            // Constants for referencing TaskError attributes
            TASK_ERROR_RESULT_CODE,     //
            TASK_ERROR_CODE,            //
            TASK_ERROR_MESSAGE,         //

            // Constants for referencing ApplicationIdList attributes. (Enumerator used during internal processing.)
            TASK_APPID_LIST_SIZE,       //
            TASK_APPID_LIST,            //

            // Constants for referencing TaskIdList attributes. (Enumerator used during internal processing.)
            TASK_TASKID_LIST_SIZE,      //
            TASK_TASKID_LIST,           //

            // Constants for referencing StepIdList attributes. (Enumerator used during internal processing.)
            TASK_STEPID_LIST_SIZE,      //
            TASK_STEPID_LIST,           //

            // Constants for referencing NsDataIdList attributes. (Enumerator used during internal processing.)
            TASK_NSDATA_LIST_SIZE,      //
            TASK_NSDATA_LIST,           //

            // Constants used during internal processing.
            ACTION_SIGNAL_TASK_EVENT,   //
            ACTION_HTTP_HEADER_VALUE,   //
            TASK_ID,                    //

            // Constants for referencing attributes added anew in SDK version x.x and onward.
            ACTION_FILE_PARAM,                              //
            ACTION_CFG_INFO,                                //

            ACTION_DATASTORE_GAME_ID,                       //
            ACTION_DATASTORE_ACCESS_KEY,                    //

            ACTION_DATASTORE_DOWNLOAD_NEWS_SUBJECT,         //
            ACTION_DATASTORE_DOWNLOAD_NEWS_MESSAGE,         //
            ACTION_DATASTORE_DOWNLOAD_NEWS_JUMP_PARAM,      //
            ACTION_DATASTORE_DOWNLOAD_NEWS_MODE,            //
            ACTION_DATASTORE_DOWNLOAD_NEWS_SERIAL_ID,       //

            ACTION_DATASTORE_UPLOAD_PERIOD,                 //
            ACTION_DATASTORE_UPLOAD_DATA_TYPE,              //
            ACTION_DATASTORE_UPLOAD_DST_PRINCIPAL_ID_NUM,   //
            ACTION_DATASTORE_UPLOAD_DST_KIND,               //
            ACTION_DATASTORE_UPLOAD_DST_PRINCIPAL_ID,       //

            PROPERTY_TYPE_MAX_VALUE = (0x1u << 15)          //
        };

        /* Please see man pages for details 
            
                   
        */
        enum SchedulingPolicy
        {
            ENUM_POLICY_START,              //
            STANDARD_POLICY,                //
            ENUM_POLICY_END,                //
            SCHEDULING_POLICY_MAX_VALUE = (0x1u << 7)   //
        };

        /* Please see man pages for details 
            
                   
        */
        enum TaskPermission
        {
            TASK_PERMISSION_IN_NONE = 0,            //
            TASK_PERMISSION_IN_EULA_DISAGREEMENT,   //
            TASK_PERMISSION_IN_PARENTAL_CONTROL,    //
            TASK_PERMISSION_IN_BOTH,                //
            TASK_PERMISSION_MAX_VALUE = (0x1u << 7) //
        };

        /* Please see man pages for details 
            
                   
        */
        enum TaskPriority
        {
            PRIORITY_EXPEDITE1  = 21,       //
            PRIORITY_EXPEDITE2  = 22,       //
            PRIORITY_EXPEDITE3  = 23,       //
            PRIORITY_EXPEDITE4  = 24,       //
            PRIORITY_EXPEDITE5  = 25,       //
            PRIORITY_EXPEDITE6  = 26,       //
            PRIORITY_EXPEDITE7  = 27,       //
            PRIORITY_EXPEDITE8  = 28,       //
            PRIORITY_EXPEDITE   = 35,       //
            PRIORITY_HIGH       = 80,       //
            PRIORITY_MEDIUM     = 125,      //
            PRIORITY_LOW        = 170,      //
            PRIORITY_LOWEST     = 215,      //
            PRIORITY_LOWEST1    = 221,      //
            PRIORITY_LOWEST2    = 222,      //
            PRIORITY_LOWEST3    = 223,      //
            PRIORITY_LOWEST4    = 224,      //
            PRIORITY_LOWEST5    = 225,      //
            PRIORITY_LOWEST6    = 226,      //
            PRIORITY_LOWEST7    = 227,      //
            PRIORITY_LOWEST8    = 228,      //
            PRIORITY_STOPPED    = 255,      //
            PRIORITY_MAX_VALUE = (0x1u << 7)    //
        };

        /* Please see man pages for details 
            
                   
        */
        enum Action
        {
            ENUM_ACTION_START,          //
            DOWNLOAD_TASK,              //
            NSA_DOWNLOAD_TASK,          //
            UPLOAD_TASK,                //
            SIGNAL_TASK,                //
            CONFIG_UPLOAD_TASK,         //
            PLAYHISTORY_UPLOAD_TASK,    //
            PEDOMETER_UPLOAD_TASK,      //
            TASKINFO_UPLOAD_TASK,       //
            STREETPASSLOG_UPLOAD_TASK,  //
            DATASTORE_DOWNLOAD_TASK,    //
            DATASTORE_UPLOAD_TASK,      //
            ENUM_ACTION_END,            //
            ACTION_MAX_VALUE = (0x1u << 7)  //
        };

        /* Please see man pages for details 
            
                   
        */
        enum ExecOption
        {
            ENUM_EXECOPTION_START,              //
            NORMAL_EXEC,                        //
            ENUM_EXECOPTION_END,                //
            OPTION_MAX_VALUE = (0x1u << 7)      //
        };

        /* Please see man pages for details 
            
                   
        */
        enum TaskStateCode
        {
            TASK_STOPPED,                                  //
            TASK_WAITING_TIMER,                            //
            TASK_WAITING,                                  //
            TASK_RUNNING,                                  //
            TASK_PAUSED,                                   //
            TASK_REGISTERED,                               //
            TASK_DONE,                                     //
            TASK_ERROR,                                    //
            TASK_RETRY,                                    //
            GET_TASK_STATE_ERROR,                          //
            STATUS_MAX_VALUE = (0x1u << 7)                 //
        };

        /* Please see man pages for details 
         
                  
         */
        enum TaskResultCode
        {
            TASK_SUCCESS,                                  //
            BOSS_ERROR_NOMEM,                              //

            GET_TASK_RESULT_ERROR,                         //
            TASK_NOT_EXIST,                                //
            TASK_CANCELED,                                 //

            // HTTP communication errors
            HTTP_ERROR_NOMEM,                              //
            HTTP_ERROR_CREATE_EVENT,                       //
            HTTP_ERROR_CREATE_MUTEX,                       //
            HTTP_ERROR_CREATE_QUEUE,                       //
            HTTP_ERROR_CREATE_THREAD,                      //
            HTTP_ERROR_IPC_SESSION,                        //
            HTTP_ERROR_CLIENT_PROCESS_MAX,                 //
            HTTP_ERROR_IPC_SESSION_MAX,                    //
            HTTP_ERROR_MSGQ_SEND_LSN,                      //
            HTTP_ERROR_MSGQ_RECV_LSN,                      //
            HTTP_ERROR_MSGQ_SEND_COMM,                     //
            HTTP_ERROR_CONN_NOMORE,                        //
            HTTP_ERROR_CONN_STATUS,                        //
            HTTP_ERROR_CONN_ADD,                           //
            HTTP_ERROR_CONN_HOST_MAX,                      //
            HTTP_ERROR_INVALID_URL,                        //
            HTTP_ERROR_RESPONSE_HEADER,                    //
            HTTP_ERROR_NO_NEWLINE,                         //
            HTTP_ERROR_SSL,                                //
            HTTP_ERROR_CERT_EXIST,                         //
            HTTP_ERROR_NO_CA_CERT_STORE,                   //
            HTTP_ERROR_NO_CLIENT_CERT,                     //
            HTTP_ERROR_CA_CERT_STORE_MAX,                  //
            HTTP_ERROR_CLIENT_CERT_MAX,                    //
            HTTP_ERROR_FAIL_TO_CREATE_CERT_STORE,          //
            HTTP_ERROR_FAIL_TO_CREATE_CLIENT_STORE,        //
            HTTP_ERROR_DNS,                                //
            HTTP_ERROR_SEND,                               //
            HTTP_ERROR_RECV,                               //
            HTTP_ERROR_CONNECT,                            //
            HTTP_ERROR_GET_PROXY_SETTING,                  //
            HTTP_ERROR_TIMEOUT,                            //
            HTTP_ERROR_401_UNAUTHORIZED,                   //
            HTTP_ERROR_403_FORBIDDEN,                      //
            HTTP_ERROR_404_NOT_FOUND,                      //
            HTTP_ERROR_408_REQUEST_TIMEOUT,                //
            HTTP_ERROR_416_REQUESTED_RANGE_NOT_SATISFABLE, //
            HTTP_ERROR_500_INTERNAL_SERVER_ERROR,          //
            HTTP_ERROR_502_BAD_GATEWAY,                    //
            HTTP_ERROR_503_SERVICE_UNAVAILABLE,            //
            HTTP_ERROR_504_GATEWAY_TIMEOUT,                //
            HTTP_ERROR_505_VERSION_NOT_SUPPORTED,          //
            HTTP_ERROR_UNSUPPORTED_STATUS,                 //

            // SSL error
            SSL_ERROR_FAILED,                              //
            SSL_ERROR_WANT_READ,                           //
            SSL_ERROR_WANT_WRITE,                          //
            SSL_ERROR_SYSCALL,                             //
            SSL_ERROR_ZERO_RETURN,                         //
            SSL_ERROR_WANT_CONNECT,                        //
            SSL_ERROR_SSLID,                               //
            SSL_ERROR_VERIFY_CERT,                         //
            SSL_ERROR_VERIFY_COMMON_NAME,                  //
            SSL_ERROR_VERIFY_ROOT_CA,                      //
            SSL_ERROR_VERIFY_CHAIN,                        //
            SSL_ERROR_VERIFY_DATE,                         //
            SSL_ERROR_GET_SERVER_CERT,                     //
            SSL_ERROR_VERIFY_REVOKED_CERT,                 //
            SSL_ERROR_OUT_OF_MEMORY,                       //
            SSL_ERROR_SESSION,                             //
            SSL_ERROR_FAIL_TO_CREATE_CERT_STROE,           //
            SSL_ERROR_FAIL_TO_CREATE_CRL_STORE,            //
            SSL_ERROR_FAIL_TO_CREATE_CLIENT_CERT,          //
            SSL_ERROR_CLIENT_PROCESS_MAX,                  //
            SSL_ERROR_IPC_SESSION,                         //
            SSL_ERROR_INTERNAL_CERT,                       //
            SSL_ERROR_INTERNAL_CRL,                        //

            // File system access errors
            FS_ERROR_INVALID_POSITION_BASE,                //
            FS_ERROR_ARCHIVE_NOT_FOUND,                    //
            FS_ERROR_FAILED_OPEN_FILE,                     //
            FS_ERROR_UNSUPPORTED_OPERATION,                //
            FS_ERROR_INVALID_PATH_FORMAT,                  //
            FS_ERROR_ACCESS_DENIED,                        //
            FS_ERROR_LIBRARY_NOT_INITIALIZED,              //
            FS_ERROR_INVALID_POSITION,                     //
            FS_ERROR_TOO_LONG_PATH,                        //
            FS_ERROR_NOT_DEVELOPMENT_ID,                   //
            FS_ERROR_HASH_MISMATCH,                        //
            FS_ERROR_NO_SUCH_PROCESS_REGISTERED,           //
            FS_ERROR_INVALID_CXI_FORMAT,                   //
            FS_ERROR_UNSUPPORTED_ALIGNMENT,                //
            FS_ERROR_INVALID_HANDLE,                       //
            FS_ERROR_NOT_FOUND,                            //

            // NSA Errors
            NSA_ERROR_STORAGE_INSUFFICIENCY,               //
            NSA_ERROR_NUMBER_OF_NSD_MAX,                   //
            NSA_ERROR_VERIFY_HASH,                         //
            NSA_ERROR_VERIFY_SIGNATURE,                    //
            NSA_NSD_ERROR_VERIFY_HASH,                     //
            NSA_NSD_ERROR_VERIFY_SIGNATURE,                //
            NSA_NSD_ERROR_INVALID_FORMAT,                  //
            NSA_ERROR_INVALID_FORMAT,                      //

            // Unexpected errors
            SEVERE_ERROR,                                  //
            UNKNOWN_ERROR,                                 //
            FS_UNKNOWN_ERROR = (UNKNOWN_ERROR + nn::Result::MODULE_NN_FS),  //
            ERROR_MAX_VALUE = (0x1u << 7)                  //
        };

        /* Please see man pages for details 
            
                   
        */
        enum TaskServiceStatus
        {
            SERVICE_TERMINATED,                            //
            SERVICE_AVAILABLE,                             //
            SERVICE_UNKNOWN,                               //
            GET_SERVICE_STATUS_ERROR,                      //
            SERVICE_MAX_VALUE = (0x1u << 7)                //
        };

        /* Please see man pages for details 
            
                   
        */
        enum HeaderInfoType
        {
            NSD_TITLEID,                                //
            NSD_FLAGS,                                  //
            NSD_DATATYPE,                               //
            NSD_LENGTH,                                 //
            NSD_SERIALID,                               //
            NSD_VERSION,                                //
            NSD_ALL,                                    //
            NSD_HEADER_MAX_VALUE = (0x1u << 7)          //
        };

        /* Please see man pages for details 
            
                   
        */
        enum FileDescriptor
        {
            CHAR_TYPE,                                  //
            WCHAR_TYPE,                                 //
            HANDLE_TYPE,                                //
            BOSSDB_TYPE,                                //
            BOSSSTORAGE_TYPE,                           //
            DATASTORE_DOWNLOAD_TYPE,                    //
            DATASTORE_UPLOAD_TYPE,                      //
            FILE_TYPE_MAX_VALUE = (0x1u << 7)           //
        };

        /* Please see man pages for details 
            
                   
        */
        enum ApInfoType
        {
            APINFOTYPE_NONE         = 0x00,             //
            APINFOTYPE_APGROUP      = 0x01,             //
            APINFOTYPE_APAREA       = 0x02,             //
            APINFOTYPE_AP           = 0x04,             //
            APINFOTYPE_MAX_VALUE    = (0x1u << 7)       //
        };

        /* Please see man pages for details 
            
                   
        */
        enum CfgInfoType
        {
            CFGINFOTYPE_NONE        = 0x00,             //
            CFGINFOTYPE_COUNTRY     = 0x01,             //
            CFGINFOTYPE_LANGUAGE    = 0x02,             //
            CFGINFOTYPE_MAX_VALUE   = (0x1u << 7)       //
        };

        /* Please see man pages for details 
            
                   
        */
        enum StorageType
        {
            USER_EXT_SAVEDATA_STORAGE,                  //
            SHARED_EXT_SAVEDATA_STORAGE,                //
            BOSSSTORAGETYPE_MAX_VALUE = (0x1u << 7)     //
        };

        /* Please see man pages for details 
            
                   
        */
        enum NewsMode
        {
            NEWSMODE_NONE,                              //
            NEWSMODE_PUBLISH,                           //
            NEWSMODE_MAX_VALUE = (0x1u << 7)            //
        };

        /* Please see man pages for details 
            
                   
                   
        */
        enum DstKind
        {
            DSTKIND_FRIEND = 1,                         //
            DSTKIND_SPECIFIED = 2,                      //
            DSTKIND_SPECIFIED_FRIEND = 4,               //
            DSTKIND_MAX_VALUE = (0x1u << 31)            //
        };

        /* Please see man pages for details 
            
                   
        */
        enum QueryType
        {
            QUERYTYPE_NONE,                                     //

            QUERYTYPE_ASCII,                                    //
            QUERYTYPE_S32,                                      //
            QUERYTYPE_U32,                                      //
            QUERYTYPE_S64,                                      //
            QUERYTYPE_U64,                                      //

            QUERYTYPE_HEX_S32 = QUERYTYPE_S32 | (0x1u << 4),    //
            QUERYTYPE_HEX_U32 = QUERYTYPE_U32 | (0x1u << 4),    //
            QUERYTYPE_HEX_S64 = QUERYTYPE_S64 | (0x1u << 4),    //
            QUERYTYPE_HEX_U64 = QUERYTYPE_U64 | (0x1u << 4),    //

            QUERYTYPE_MAX_VALUE = (0x1u << 7)                   //
        };

} // end of namespace boss
} // end of namespace nn


#endif /*__cplusplus*/

#endif /* NN_BOSS_BOSS_CONST_H_ */
