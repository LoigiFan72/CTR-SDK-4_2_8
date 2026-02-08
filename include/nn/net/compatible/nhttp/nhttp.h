/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nhttp.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NHTTP_H_
#define NHTTP_H_

#include <nn/net/compatible/nssl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*=======================================================================*
    Constant definitions
 *=======================================================================*/
/* Please see man pages for details 
 
 */
#define NHTTP_CONNECTION_MAX        14          /* Please see man pages for details */

/* Please see man pages for details 
 
 */
#define NHTTP_ER_BASE           0xffffe000
#define NHTTP_ER_CODE(code)     ((s32)(NHTTP_ER_BASE|(code)))

typedef enum nhttp_error {
    NHTTP_ER_NONE               = 0,                /* Please see man pages for details */
    NHTTP_ER_INVALID_STATUS     = NHTTP_ER_CODE(1), /* Please see man pages for details */
    NHTTP_ER_INVALID_PARAM      = NHTTP_ER_CODE(2), /* Please see man pages for details */
    NHTTP_ER_NOMEM              = NHTTP_ER_CODE(3), /* Please see man pages for details */
    NHTTP_ER_CREATE_EVENT       = NHTTP_ER_CODE(4), /* Please see man pages for details */
    NHTTP_ER_CREATE_MUTEX       = NHTTP_ER_CODE(5), /* Please see man pages for details */
    NHTTP_ER_CREATE_QUEUE       = NHTTP_ER_CODE(6), /* Please see man pages for details */
    NHTTP_ER_CREATE_THREAD      = NHTTP_ER_CODE(7), /* Please see man pages for details */

    /* Message queue */
    NHTTP_ER_MSGQ_SEND_LSN      = NHTTP_ER_CODE(10),    /* Please see man pages for details */
    NHTTP_ER_MSGQ_RECV_LSN      = NHTTP_ER_CODE(11),    /* Please see man pages for details */
    NHTTP_ER_MSGQ_RECV_COMM     = NHTTP_ER_CODE(12),    /* Please see man pages for details */

    /* Connection handle */
    NHTTP_ER_CONN_NOMORE        = NHTTP_ER_CODE(20),    /* Please see man pages for details */
    NHTTP_ER_CONN_NOSUCH        = NHTTP_ER_CODE(21),    /* Please see man pages for details */
    NHTTP_ER_CONN_STATUS        = NHTTP_ER_CODE(22),    /* Please see man pages for details */
    NHTTP_ER_CONN_ADD           = NHTTP_ER_CODE(23),    /* Please see man pages for details */
    NHTTP_ER_CONN_CANCELED      = NHTTP_ER_CODE(24),    /* Please see man pages for details */
    NHTTP_ER_CONN_HOST_MAX      = NHTTP_ER_CODE(25),    /* Please see man pages for details */

    /* Request */
    NHTTP_ER_REQ_URL            = NHTTP_ER_CODE(30),    /* Please see man pages for details */
    NHTTP_ER_REQ_CONNMSG_PORT   = NHTTP_ER_CODE(31),    /* Please see man pages for details */
    NHTTP_ER_REQ_UNKNOWN_METHOD = NHTTP_ER_CODE(32),    /* Please see man pages for details */

    /* Response */
    NHTTP_ER_RES_HEADER         = NHTTP_ER_CODE(40),    /* Please see man pages for details */
    NHTTP_ER_RES_NONEWLINE      = NHTTP_ER_CODE(41),    /* Please see man pages for details */
    NHTTP_ER_RES_BODYBUF        = NHTTP_ER_CODE(42),    /* Please see man pages for details */

    /* POST */
    NHTTP_ER_POST_ADDED_ANOTHER = NHTTP_ER_CODE(50),    /* Please see man pages for details */
    NHTTP_ER_POST_BOUNDARY      = NHTTP_ER_CODE(51),    /* Please see man pages for details */
    NHTTP_ER_POST_SEND          = NHTTP_ER_CODE(52),    /* Please see man pages for details */
    NHTTP_ER_POST_UNKNOWN_ENCTYPE = NHTTP_ER_CODE(53), /* Please see man pages for details */
    NHTTP_ER_POST_NODATA        = NHTTP_ER_CODE(54),    /* Please see man pages for details */

    /* SSL */
    NHTTP_ER_SSL                = NHTTP_ER_CODE(60),    /* Please see man pages for details */
    NHTTP_ER_SSL_CERT_EXIST     = NHTTP_ER_CODE(61),    /* Please see man pages for details */

    /* socket */
    NHTTP_ER_SOC_DNS            = NHTTP_ER_CODE(70),    /* Please see man pages for details */
    NHTTP_ER_SOC_SEND           = NHTTP_ER_CODE(71),    /* Please see man pages for details */
    NHTTP_ER_SOC_RECV           = NHTTP_ER_CODE(72),    /* Please see man pages for details */
    NHTTP_ER_SOC_CONN           = NHTTP_ER_CODE(73),    /* Please see man pages for details */
    NHTTP_ER_SOC_KEEPALIVE_DISCONNECTED           = NHTTP_ER_CODE(74),    /* Please see man pages for details */

    /* Other */
    NHTTP_ER_GET_DEFAULT_PROXY  = NHTTP_ER_CODE(80),    /* Please see man pages for details */
    NHTTP_ER_DESTROY_NOTSTARTED_CONN  = NHTTP_ER_CODE(81),    /* Please see man pages for details */

    NHTTP_ER_MAX                    /* Please see man pages for details */
} NHTTPError;




/* Please see man pages for details 
 
 */
typedef enum nhttp_req_method {
    NHTTP_REQMETHOD_NONE,   /* Please see man pages for details */
    NHTTP_REQMETHOD_GET,    /* Please see man pages for details */
    NHTTP_REQMETHOD_POST,   /* Please see man pages for details */
    NHTTP_REQMETHOD_HEAD,   /* Please see man pages for details */
    NHTTP_REQMETHOD_MAX     /* Please see man pages for details */
} NHTTPReqMethod;


/* Please see man pages for details 
 
 */
typedef enum nhttp_encoding_type {
    NHTTP_ENCODING_TYPE_AUTO,       /* Please see man pages for details */
    NHTTP_ENCODING_TYPE_URL,        /* Please see man pages for details */
    NHTTP_ENCODING_TYPE_MULTIPART,  /* Please see man pages for details */
    NHTTP_ENCODING_TYPE_MAX         /* Please see man pages for details */
} NHTTPEncodingType;

/* Please see man pages for details 
 
 */
typedef enum nhttp_postdata_type {
    NHTTP_POST_DATA_TYPE_URLENCODE,      /* Please see man pages for details */
    NHTTP_POST_DATA_TYPE_MULTIPART,      /* Please see man pages for details */
    NHTTP_POST_DATA_TYPE_RAW,            /* Please see man pages for details */
    NHTTP_POST_DATA_TYPE_MAX             /* Please see man pages for details */
} NHTTPPostDataType;



/* Please see man pages for details 
 
 */
typedef enum nhttp_connection_event {
    NHTTP_CONN_EV_NONE,             /* Please see man pages for details */
    NHTTP_CONN_EV_POST_SEND,        /* Please see man pages for details */
    NHTTP_CONN_EV_POST_SEND_ALL,    /* Please see man pages for details */
    NHTTP_CONN_EV_HEADER_RECV_DONE, /* Please see man pages for details */
    NHTTP_CONN_EV_BODY_RECV_FULL,   /* Please see man pages for details */
    NHTTP_CONN_EV_BODY_RECV_DONE,   /* Please see man pages for details */
    NHTTP_CONN_EV_COMPLETE,         /* Please see man pages for details */
    NHTTP_CONN_EV_MAX               /* Please see man pages for details */
} NHTTPConnectionEvent;


/* Please see man pages for details 
 
 
 */
typedef enum nhttp_conn_status {
    NHTTP_CONNST_CREATED = 0,       /* Please see man pages for details */
    NHTTP_CONNST_INITIALIZED,       /* Please see man pages for details */
    NHTTP_CONNST_ENQUEUED_LSN,      /* Please see man pages for details */
    NHTTP_CONNST_IN_LSN,            /* Please see man pages for details */
    NHTTP_CONNST_ENQUEUED_COMM,     /* Please see man pages for details */
    NHTTP_CONNST_CONNECTING,        /* Please see man pages for details */
    NHTTP_CONNST_SENDING,           /* Please see man pages for details */
    NHTTP_CONNST_RECEIVING_HEADER,  /* Please see man pages for details */
    NHTTP_CONNST_RECEIVING_BODY,    /* Please see man pages for details */
    NHTTP_CONNST_RECEIVED,          /* Please see man pages for details */
    NHTTP_CONNST_FINISHED           /* Please see man pages for details */
} NHTTPConnStatus;


/*=======================================================================*
    Macro definitions
 *=======================================================================*/


/*=======================================================================*
    Type Definitions
 *=======================================================================*/

/* Memory allocator */
typedef void *(*NHTTPAlloc) (u32 name, u32 size, u32 align); /* Please see man pages for details */
typedef void (*NHTTPFree) (u32 name, void *ptr); /* Please see man pages for details */

/* Other */
typedef s32 NHTTPConnectionHandle;      /* Please see man pages for details */

/* Please see man pages for details 
 
 */
typedef s32 (*NHTTPConnectionCallback)(NHTTPConnectionHandle handle, NHTTPConnectionEvent event, void *arg);


/*=======================================================================*
    Structure definitions
 *=======================================================================*/

/* Please see man pages for details 
 
 */
typedef struct nhttp_config {
    NHTTPAlloc alloc;       /* Please see man pages for details */
    NHTTPFree free;         /* Please see man pages for details */
    u32 threadPrio;         /* Please see man pages for details */
    u32 threadNum;          /* Please see man pages for details */
    u32 queueDepth;         /* Please see man pages for details */
    u32 singleHostMax;      /* Please see man pages for details */
} NHTTPConfig;


/* Please see man pages for details 
 
 */
typedef struct nhttp_post_send_arg {
    const char *label;  /* Please see man pages for details */
    char *buf;          /* Please see man pages for details */
    u32 size;           /* Please see man pages for details */
    u32 offset;         /* Please see man pages for details */
} NHTTPPostSendArg;

/* Please see man pages for details 
 
 */
typedef struct nhttp_post_send_all_data_arg {
    char *label;        /* Please see man pages for details */
    char *buf;          /* Please see man pages for details */
    u32 size;           /* Please see man pages for details */
    u32 offset;         /* Please see man pages for details */
    BOOL isBinary;      /* Please see man pages for details */
} NHTTPPostSendAllDataArg;


/* Please see man pages for details 
 
 */
typedef struct nhttp_body_buf_arg {
    char *buf;          /* Please see man pages for details */
    u32 size;           /* Please see man pages for details */
    u32 offset;         /* Please see man pages for details */
} NHTTPBodyBufArg;


/*=======================================================================*
    Function Prototype Declarations
 *=======================================================================*/

/* Initialize/finalize */
s32 NHTTP_Startup(const NHTTPConfig *config);
s32 NHTTP_Cleanup(void);

/* Get Information */
void *NHTTP_CallAlloc(u32 name, u32 size, u32 align);
void NHTTP_CallFree(u32 name, void *ptr);

/* DNS cache */
s32 NHTTP_ClearDnsCaches(void);

/* Connection handle */
NHTTPConnectionHandle NHTTP_CreateConnection(const char *url, NHTTPReqMethod method, char *bodyBuf, u32 bufLen, NHTTPConnectionCallback callback, void *userParam);
s32 NHTTP_DestroyConnection(NHTTPConnectionHandle handle);
s32 NHTTP_StartConnection(NHTTPConnectionHandle handle);
s32 NHTTP_StartConnectionAsync(NHTTPConnectionHandle handle);
s32 NHTTP_CancelConnection(NHTTPConnectionHandle handle);
s32 NHTTP_WaitForConnection(NHTTPConnectionHandle handle);
s32 NHTTP_GetConnectionStatus(NHTTPConnectionHandle handle);
s32 NHTTP_GetConnectionProgress(NHTTPConnectionHandle handle, u32 *received, u32 *contentLen);
s32 NHTTP_GetConnectionError(NHTTPConnectionHandle handle);
s32 NHTTP_GetConnectionSSLError(NHTTPConnectionHandle handle);
void *NHTTP_GetUserParam(NHTTPConnectionHandle handle);

/* Set SSL certificate */
s32 NHTTP_SetVerifyOption(NHTTPConnectionHandle handle, u32 verifyOption);
s32 NHTTP_SetRootCA(NHTTPConnectionHandle handle, u8 *rootCAData, int rootCASize);
s32 NHTTP_SetInternalRootCA(NHTTPConnectionHandle handle, u32 internalCaCertId);
s32 NHTTP_SetRootCAStore(NHTTPConnectionHandle handle, NSSLCertStoreId rootCAId);
s32 NHTTP_SetClientCert(NHTTPConnectionHandle handle, u8 *clientCertData, int clientCertSize, u8 *privateKeyData, int privateKeySize);
s32 NHTTP_SetInternalClientCert(NHTTPConnectionHandle handle, u32 internalClientCertId);
s32 NHTTP_SetClientCertId(NHTTPConnectionHandle handle, NSSLCertId clientCertId);
s32 NHTTP_RemoveClientCert(NHTTPConnectionHandle handle);
s32 NHTTP_RemoveRootCA(NHTTPConnectionHandle handle);
s32 NHTTP_SetRootCADefault(NHTTPConnectionHandle handle);
s32 NHTTP_SetClientCertDefault(NHTTPConnectionHandle handle);
s32 NHTTP_DisableVerifyOptionForDebug(NHTTPConnectionHandle handle, u32 verifyOption);

/* Connection settings */
s32 NHTTP_SetProxy(NHTTPConnectionHandle handle, const char *proxy, u16 port, const char *userName, const char *password);
s32 NHTTP_SetProxyDefault(NHTTPConnectionHandle handle);
s32 NHTTP_SetBasicAuthorization(NHTTPConnectionHandle handle, const char *userName, const char *password);
s32 NHTTP_SetSocketBufferSize(NHTTPConnectionHandle handle, u32 size);
s32 NHTTP_SetSocketSendBufferSize(NHTTPConnectionHandle handle, u32 size);
s32 NHTTP_SetKeepAliveAvailability(NHTTPConnectionHandle handle, BOOL isUseKeepAlive);

/* HTTP request settings - nhttp_req.c */
s32 NHTTP_AddHeaderField(NHTTPConnectionHandle handle, const char *label, const char *value);
#ifdef NHTTP_POST_BY_CLIENT_HEAP_MODE
s32 NHTTP_RemoveExistingAddedPostData(NHTTPConnectionHandle handle, const char *label, void** memory);
s32 NHTTP_RemovePostDataHead(NHTTPConnectionHandle handle, void** memory);
s32 NHTTP_GetPostDataRaw(NHTTPConnectionHandle handle, void** memory);
size_t NHTTP_CalculateElementSize(const char* label, u32 valueLen);
#endif

#ifdef NHTTP_POST_BY_CLIENT_HEAP_MODE
s32 NHTTP_AddPostDataAscii(NHTTPConnectionHandle handle, const char *label, const char *value, void* memory);
s32 NHTTP_AddPostDataBinary(NHTTPConnectionHandle handle, const char *label, const void *value, u32 length, void* memory);
s32 NHTTP_AddPostDataRaw(NHTTPConnectionHandle handle, const void *value, u32 length, void* memory);
#else
s32 NHTTP_AddPostDataAscii(NHTTPConnectionHandle handle, const char *label, const char *value);
s32 NHTTP_AddPostDataBinary(NHTTPConnectionHandle handle, const char *label, const void *value, u32 length);
s32 NHTTP_AddPostDataRaw(NHTTPConnectionHandle handle, const void *value, u32 length);
#endif
s32 NHTTP_SetPostDataEncoding(NHTTPConnectionHandle handle, NHTTPEncodingType type);
s32 NHTTP_SetPostDataLazySet(NHTTPConnectionHandle handle, NHTTPPostDataType dataType, u32 length);

/* Get HTTP response - nhttp_res.c */
s32 NHTTP_GetBodyBuffer(NHTTPConnectionHandle handle, char **bodyBuffer, u32 *size);
s32 NHTTP_AllocBodyBuffer(NHTTPConnectionHandle handle, u32 size);
s32 NHTTP_FreeBodyBuffer(NHTTPConnectionHandle handle);
s32 NHTTP_GetHeaderField(NHTTPConnectionHandle, const char *label, char *value, u32 maxLen);
s32 NHTTP_GetHeaderAll(NHTTPConnectionHandle handle, char *value, u32 maxLen);
s32 NHTTP_GetResultCode(NHTTPConnectionHandle handle);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NHTTP_H_ */
