/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TYPES_H_
#define NN_BOSS_BOSS_TYPES_H_

#include <nn/types.h>
#include <nn/os/os_Event.h>
#include <nn/Handle.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>

/*=======================================================================*
    Type Definitions
 *=======================================================================*/

#ifdef __cplusplus

namespace nn {
namespace boss {

typedef nn::fs::TitleId         AppIdType;
typedef nn::fs::ExtSaveDataId   BossStorageId;

/* Please see man pages for details 
    
*/
typedef struct TaskPolicyConfig {
    u8                  priority;               //
    SchedulingPolicy    schedulingPolicy;       //
    TaskPermission      taskPermission;         //
    NN_PADDING1;
    u32                 targetDuration;         //
    u32                 execInterval;           //
    u32                 execCount;              //
} TaskPolicyConfig;


/* Please see man pages for details 
    
*/
typedef struct TaskOptionConfig {
    ExecOption      option;               //
    u8              step;                 //
    u8              targetStep;           //
    NN_PADDING1;
    u32             param1;               //
    u32             param2;               //
} TaskOptionConfig;

//------------------------------------------------------------
//  TASK ACTION   Cautions for 1st BOSS version
//      (1) ACTION supports "Download" and "NsaDownload"
//                    Although "Upload" and "Signal" are not implemented, parameters are provisionally defined
//
//      (2) Consideration regarding "nn::os::Event* event;" used with SIGNAL ACTION is required for development after 2nd BOSS.
//          
//          Event* is held in a structure, and using it by registering it in the BOSS database is a problem.
//
//
/* Please see man pages for details 
    
*/
typedef struct TaskActionConfig {
    Action              action;                                 //
    u8                  privateRootCA;                          //
    u8                  privateClientCert;                      //
    ApInfoType          infoAP;                                 //
    FileDescriptor      fDesc;                                  //
    CfgInfoType         infoCfg;                                //
    NN_PADDING2;
    u32                 execSerialId;                           //
    u32                 offset;                                 //
    nn::os::Event*      event;                                  //
    nn::Handle          fileHandle;                             //
    union File {
        char            filePath[MAX_FILEPATH_LENGTH];          //
        wchar_t         filePathW[MAX_FILEPATH_LENGTH];         //
        u8              param[MAX_TASK_FILE_PARAM];             //
    } file;
    char                url[MAX_URL_LENGTH];                    //

    struct HhttpRequestHeader{
        char            label[MAX_HTTP_HEADER_LABEL];           //
        char            value[MAX_HTTP_HEADER_VALUE];           //
    } httpRequestHeader[MAX_HTTP_HEADER];                       //

    u32                             rootCA[MAX_ROOT_CA];        //
    u32                             clientCert[MAX_CLIENT_CERT];//
    u32                             rootCANum;                  //
    u32                             clientCertNum;              //

    NN_PADDING4;
    char lastModified[MAX_LASTMODIFIED_LENGTH];                 //

} TaskActionConfig;

/* Please see man pages for details 
    
*/
typedef TaskActionConfig TaskActionUploadConfig;

/* Please see man pages for details 
    
*/
typedef TaskActionConfig TaskActionDownloadConfig;

/* Please see man pages for details 
    
*/
typedef TaskActionConfig TaskActionSignalConfig;

/* Please see man pages for details 
    
*/
typedef TaskActionConfig TaskActionNsaDownloadConfig;


/* Please see man pages for details 
    
*/
typedef struct TaskConfig {
    u32                 execInterval;           //
    u32                 execCount;              //
    u8                  taskId[TASK_ID_LENGTH]; //
} TaskConfig;


/* Please see man pages for details 
    
*/
typedef struct TaskStatusInfo {
    s64                 taskStartTime;        //
    s64                 stepStartTime;        //
    TaskStateCode       state;                //
    TaskStateCode       taskState;            //
    TaskStateCode       stateResume;          //
    TaskServiceStatus   serviceStatus;        //
    bool                serviceTerminated;    //
    TaskResultCode      resultCode;           //
    NN_PADDING2;

    u32                 commErrorCode;        //
    u32                 execCount;            //
    u32                 pendingTime;          //
    u32                 remainTime;           //
    u32                 progress;             //
    u32                 dataSize;             //
    u16                 activeRate;           //
    u16                 requestRate;          //
    u8                  activeStep;           //
    u8                  priority;             //
    NN_PADDING2;
    char lastModified[MAX_LASTMODIFIED_LENGTH];  //
} TaskStatusInfo;


/* Please see man pages for details 
    
*/
typedef TaskStatusInfo TaskStepStatusInfo ;

/* Please see man pages for details 
    
*/
typedef struct TaskErrorInfo {
    TaskResultCode errorResultCode;             //
    NN_PADDING3;
    u32         errorCode;                      //
    char        message[MAX_ERROR_MESSAGE];     //
} TaskErrorInfo;

/* Please see man pages for details 
    
*/
typedef struct HttpQuery {
    QueryType   type;                           //
    char        name[MAX_HTTP_QUERY_NAME];      //
    char        value[MAX_HTTP_QUERY_VALUE];    //
} HttpQuery;

/* Please see man pages for details 
    
*/
typedef struct TaskQueryConfig {
    HttpQuery   query[MAX_HTTP_QUERY];          //
} TaskQueryConfig;

/* Please see man pages for details 
    
*/
typedef struct DataStoreDownloadConfig
{
    u32         gameId;                                     //
    wchar_t     accessKey[MAX_ACCESS_KEY_LENGTH];           //
    wchar_t     newsSubject[MAX_NEWS_SUBJECT_LENGTH];       //
    wchar_t     newsMessage[MAX_NEWS_MESSAGE_LENGTH];       //
    u8          newsJumpParam[MAX_NEWS_JUMP_PARAM];         //
    NewsMode    newsMode;                                   //
    NN_PADDING1;
    bit32       newsSerialId;                               //
} DataStoreDownloadConfig;

/* Please see man pages for details 
    
*/
typedef struct DataStoreUploadConfig
{
    u32         gameId;                                     //
    wchar_t     accessKey[MAX_ACCESS_KEY_LENGTH];           //
    u16         period;                                     //
    u16         dataType;                                   //
    u16         dstPrincipalIdNum;                          //
    DstKind     dstKind;                                    //
    u32         dstPrincipalId[MAX_DST_PRINCIPAL_ID];       //
} DataStoreUploadConfig;

/* Please see man pages for details 
    
*/
typedef struct ApplicationIdInfoList {
    u16       size;                             //
    NN_PADDING2;
    NN_PADDING4;
    AppIdType appId[MAX_APPLICATION_ID];        //
} ApplicationIdInfoList;

/* Please see man pages for details 
    
*/
typedef struct TaskIdInfoList {
    u16     size;                               //
    NN_PADDING2;
    NN_PADDING4;
    u8      taskId[MAX_TASK_ID][TASK_ID_LENGTH];//
} TaskIdInfoList;

/* Please see man pages for details 
    
*/
typedef struct StepIdInfoList {
    u16       size;                     //
    NN_PADDING2;
    u8        stepId[MAX_TASK_ID];      //
} StepIdInfoList;

/* Please see man pages for details 
    
*/
typedef struct NsDataIdInfoList {
    u16       size;                     //
    u16       lastIndex;                //
    u32       lastSerial;               //
    u32*      pSerial;                  //
    size_t    serialSize;               //
} NsDataIdInfoList;

/* Please see man pages for details 
    
*/
typedef struct NsDataHeaderInfo {
    s64       titleId;                  //
    bit32     flags;                    //
    bit32     dataType;                 //
    s32       length;                   //
    u32       serialId;                 //
    u32       version;                  //
    NN_PADDING4;
} NsDataHeaderInfo;

} // end of namespace boss
} // end of namespace nn


#endif /*__cplusplus*/

#endif /* NN_BOSS_BOSS_TYPES_H_ */
