/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     http_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HTTP_HTTP_RESULT_H_
#define NN_HTTP_HTTP_RESULT_H_


#include <nn/Result.h>
#include <nn/net/compatible/nhttp.h>

//Macro for converting result code from NHTTP library into HTTP ResultCode.
#define CHANGE_NHTTP_RESULT_CODE_MASK 0x000003ff
#define CHANGE_NHTTP_RESULT_CODE(nhttpCode) \
    (nhttpCode) & (CHANGE_NHTTP_RESULT_CODE_MASK)


/* Please see man pages for details 
  
  
*/

/* Please see man pages for details 
 
*/
enum nnHttpResultCode
{
    /* general use*/
    NN_HTTP_ER_NONE                     = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_NONE),                                //
    NN_HTTP_ER_INVALID_STATUS           = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_INVALID_STATUS),                      //
    NN_HTTP_ER_INVALID_PARAM            = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_INVALID_PARAM),                       //
    NN_HTTP_ER_NOMEM                    = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_NOMEM),                               //
    NN_HTTP_ER_CREATE_EVENT             = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CREATE_EVENT),                        //
    NN_HTTP_ER_CREATE_MUTEX             = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CREATE_MUTEX),                        //
    NN_HTTP_ER_CREATE_QUEUE             = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CREATE_QUEUE),                        //
    NN_HTTP_ER_CREATE_THREAD            = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CREATE_THREAD),                       //
    NN_HTTP_ER_CONNECTION_NOT_INITIALIZED          = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(100)),                //
    NN_HTTP_ER_ALREADY_ASSIGN_HOST      = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(101)),                           //
    NN_HTTP_ER_SESSION                  = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(102)),                           //
    NN_HTTP_ER_CLIENT_PROCESS_MAX       = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(103)),                           //
    NN_HTTP_ER_IPC_SESSION_MAX          = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(104)),                           //
    NN_HTTP_ER_TIMEOUT                  = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(105)),                           //

    /* For library processing */
    NN_HTTP_ER_ALREADY_INITIALIZED      = nn::Result::DESCRIPTION_ALREADY_INITIALIZED,  //
    NN_HTTP_ER_NOT_INITIALIZED          = nn::Result::DESCRIPTION_NOT_INITIALIZED,      //

    /* For message queue */
    NN_HTTP_ER_MSGQ_SEND_LSN    = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_MSGQ_SEND_LSN),         //
    NN_HTTP_ER_MSGQ_RECV_LSN    = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_MSGQ_RECV_LSN),         //
    NN_HTTP_ER_MSGQ_RECV_COMM   = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_MSGQ_RECV_COMM),        //

    /* For connection handling */
    NN_HTTP_ER_CONN_NOMORE      = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CONN_NOMORE),         //
    NN_HTTP_ER_CONN_NOSUCH      = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CONN_NOSUCH),         //
    NN_HTTP_ER_CONN_STATUS      = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CONN_STATUS),         //
    NN_HTTP_ER_CONN_ADD         = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CONN_ADD),            //
    NN_HTTP_ER_CONN_CANCELED    = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CONN_CANCELED),       //
    NN_HTTP_ER_CONN_HOST_MAX    = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CONN_HOST_MAX),       //
    NN_HTTP_ER_CONN_PROCESS_MAX = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(26)),            //

    /* For requests */
    NN_HTTP_ER_REQ_URL              = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_REQ_URL),             //
    NN_HTTP_ER_REQ_CONNMSG_PORT     = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_REQ_CONNMSG_PORT),    //
    NN_HTTP_ER_REQ_UNKNOWN_METHOD   = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_REQ_UNKNOWN_METHOD),  //

    /* For responses */
    NN_HTTP_ER_RES_HEADER           = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_RES_HEADER),          //
    NN_HTTP_ER_RES_NONEWLINE        = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_RES_NONEWLINE),       //
    NN_HTTP_ER_RES_BODYBUF          = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_RES_BODYBUF),         //
    NN_HTTP_ER_RES_BODYBUF_SHORTAGE = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(43)),            //

    /* For POST */
    NN_HTTP_ER_POST_ADDED_ANOTHER   = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_POST_ADDED_ANOTHER),  //
    NN_HTTP_ER_POST_BOUNDARY        = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_POST_BOUNDARY),       //
    NN_HTTP_ER_POST_SEND            = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_POST_SEND),           //
    NN_HTTP_ER_POST_UNKNOWN_ENCTYPE = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_POST_UNKNOWN_ENCTYPE),//
    NN_HTTP_ER_POST_NODATA          = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_POST_NODATA),         //

    /* SSL-related */
    NN_HTTP_ER_SSL                   = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SSL),                  //
    NN_HTTP_ER_SSL_CERT_EXIST        = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SSL_CERT_EXIST),       //
    NN_HTTP_ER_SSL_NO_CA_CERT_STORE  = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(200)),            //
    NN_HTTP_ER_SSL_NO_CLIENT_CERT    = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(201)),            //
    NN_HTTP_ER_SSL_CA_CERT_STORE_MAX = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(202)),            //
    NN_HTTP_ER_SSL_CLIENT_CERT_MAX   = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(203)),            //
    NN_HTTP_ER_SSL_FAIL_TO_CREATE_CERT_STORE = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(204)),    //
    NN_HTTP_ER_SSL_FAIL_TO_CREATE_CLIENT_CERT = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_CODE(205)),   //

    /* For sockets */
    NN_HTTP_ER_SOC_DNS  = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SOC_DNS),             //
    NN_HTTP_ER_SOC_SEND = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SOC_SEND),            //
    NN_HTTP_ER_SOC_RECV = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SOC_RECV),            //
    NN_HTTP_ER_SOC_CONN = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SOC_CONN),            //
    NN_HTTP_ER_SOC_KEEPALIVE_DISCONNECTED = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_SOC_KEEPALIVE_DISCONNECTED), //

    /* For proxies */
    NN_HTTP_ER_GET_PROXY_SETTING = CHANGE_NHTTP_RESULT_CODE(NHTTP_ER_GET_DEFAULT_PROXY)                   //
};

/*  

*/

#ifdef __cplusplus


namespace nn {
namespace http {
    /* Please see man pages for details 
     
         
    */
    enum ResultCode
    {
        /* general use*/
        ER_NONE                 = NN_HTTP_ER_NONE,                   //
        ER_INVALID_STATUS       = NN_HTTP_ER_INVALID_STATUS,         //
        ER_INVALID_PARAM        = NN_HTTP_ER_INVALID_PARAM,          //
        ER_NOMEM                = NN_HTTP_ER_NOMEM,                  //
        ER_CREATE_EVENT         = NN_HTTP_ER_CREATE_EVENT,           //
        ER_CREATE_MUTEX         = NN_HTTP_ER_CREATE_MUTEX,           //
        ER_CREATE_QUEUE         = NN_HTTP_ER_CREATE_QUEUE,           //
        ER_CREATE_THREAD        = NN_HTTP_ER_CREATE_THREAD,          //
        ER_CONNECTION_NOT_INITIALIZED      = NN_HTTP_ER_CONNECTION_NOT_INITIALIZED,        //
        ER_ALREADY_ASSIGN_HOST  = NN_HTTP_ER_ALREADY_ASSIGN_HOST,    //
        ER_SESSION              = NN_HTTP_ER_SESSION,                //
        ER_CLIENT_PROCESS_MAX   = NN_HTTP_ER_CLIENT_PROCESS_MAX,     //
        ER_IPC_SESSION_MAX      = NN_HTTP_ER_IPC_SESSION_MAX ,       //
        ER_TIMEOUT              = NN_HTTP_ER_TIMEOUT,                //

        /* For library processing */
        ER_ALREADY_INITIALIZED  = NN_HTTP_ER_ALREADY_INITIALIZED,    //
        ER_NOT_INITIALIZED      = NN_HTTP_ER_NOT_INITIALIZED,        //

        /* For message queue */
        ER_MSGQ_SEND_LSN        = NN_HTTP_ER_MSGQ_SEND_LSN,          //
        ER_MSGQ_RECV_LSN        = NN_HTTP_ER_MSGQ_RECV_LSN,          //
        ER_MSGQ_RECV_COMM       = NN_HTTP_ER_MSGQ_RECV_COMM,         //

        /* For connection handling */
        ER_CONN_NOMORE          = NN_HTTP_ER_CONN_NOMORE,            //
        ER_CONN_NOSUCH          = NN_HTTP_ER_CONN_NOSUCH,            //
        ER_CONN_STATUS          = NN_HTTP_ER_CONN_STATUS,            //
        ER_CONN_ADD             = NN_HTTP_ER_CONN_ADD,               //
        ER_CONN_CANCELED        = NN_HTTP_ER_CONN_CANCELED,          //
        ER_CONN_HOST_MAX        = NN_HTTP_ER_CONN_HOST_MAX,          //
        ER_CONN_PROCESS_MAX     = NN_HTTP_ER_CONN_PROCESS_MAX,       //

        /* For requests */
        ER_REQ_URL              = NN_HTTP_ER_REQ_URL,                //
        ER_REQ_CONNMSG_PORT     = NN_HTTP_ER_REQ_CONNMSG_PORT,       //
        ER_REQ_UNKNOWN_METHOD   = NN_HTTP_ER_REQ_UNKNOWN_METHOD,     //

        /* For responses */
        ER_RES_HEADER           = NN_HTTP_ER_RES_HEADER,             //
        ER_RES_NONEWLINE        = NN_HTTP_ER_RES_NONEWLINE,          //
        ER_RES_BODYBUF          = NN_HTTP_ER_RES_BODYBUF,            //
        ER_RES_BODYBUF_SHORTAGE = NN_HTTP_ER_RES_BODYBUF_SHORTAGE,   //

        /* For POST */
        ER_POST_ADDED_ANOTHER   = NN_HTTP_ER_POST_ADDED_ANOTHER,     //
        ER_POST_BOUNDARY        = NN_HTTP_ER_POST_BOUNDARY,          //
        ER_POST_SEND            = NN_HTTP_ER_POST_SEND,              //
        ER_POST_UNKNOWN_ENCTYPE = NN_HTTP_ER_POST_UNKNOWN_ENCTYPE,   //
        ER_POST_NODATA          = NN_HTTP_ER_POST_NODATA,            //

        /* SSL-related */
        ER_SSL                   = NN_HTTP_ER_SSL,                    //
        ER_SSL_CERT_EXIST        = NN_HTTP_ER_SSL_CERT_EXIST,         //
        ER_SSL_NO_CA_CERT_STORE  = NN_HTTP_ER_SSL_NO_CA_CERT_STORE,   //
        ER_SSL_NO_CLIENT_CERT    = NN_HTTP_ER_SSL_NO_CLIENT_CERT,     //
        ER_SSL_CA_CERT_STORE_MAX = NN_HTTP_ER_SSL_CA_CERT_STORE_MAX,  //
        ER_SSL_CLIENT_CERT_MAX   = NN_HTTP_ER_SSL_CLIENT_CERT_MAX,    //
        ER_SSL_FAIL_TO_CREATE_CERT_STORE = NN_HTTP_ER_SSL_FAIL_TO_CREATE_CERT_STORE,   //
        ER_SSL_FAIL_TO_CREATE_CLIENT_CERT = NN_HTTP_ER_SSL_FAIL_TO_CREATE_CLIENT_CERT, //

        /* For sockets */
        ER_SOC_DNS              = NN_HTTP_ER_SOC_DNS,                //
        ER_SOC_SEND             = NN_HTTP_ER_SOC_SEND,               //
        ER_SOC_RECV             = NN_HTTP_ER_SOC_RECV,               //
        ER_SOC_CONN             = NN_HTTP_ER_SOC_CONN,               //
        ER_SOC_KEEPALIVE_DISCONNECTED = NN_HTTP_ER_SOC_KEEPALIVE_DISCONNECTED, //

        /* For proxies*/
        ER_GET_PROXY_SETTING    = NN_HTTP_ER_GET_PROXY_SETTING                   //

    };

    namespace detail {
        /* Please see man pages for details 
         
         
         
         
        */
        NN_DEFINE_RESULT_FUNC_LM(MakePermanentResult, Result::LEVEL_PERMANENT, Result::MODULE_NN_HTTP);


        /* Please see man pages for details 
         
         
         
        */
        inline Result ChangeNetHttpRetCodeToResult(ResultCode returnCode)
        {
            if(returnCode == ER_NONE)
            {
                return ResultSuccess();
            }
            else if(returnCode == ER_INVALID_PARAM)
            {
                return MakePermanentResult(Result::SUMMARY_INVALID_ARGUMENT, returnCode);
            }
            else
            {
                return MakePermanentResult(Result::SUMMARY_INVALID_STATE, returnCode);
            }
        }

        /* Please see man pages for details 
         
         
         
        */
        inline Result ChangeNetHttpRetCodeToResult(s32 returnCode)
        {
            return ChangeNetHttpRetCodeToResult(static_cast<ResultCode>(CHANGE_NHTTP_RESULT_CODE(returnCode)));
        }
    }

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidStatusErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_INVALID_STATUS
    );


    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultInvalidParamErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_ARGUMENT, ER_INVALID_PARAM
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultOutOfMemoryErr,
        detail::MakePermanentResult, Result::SUMMARY_OUT_OF_RESOURCE, ER_NOMEM
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultCreateEventErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CREATE_EVENT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultCreateMutexErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CREATE_MUTEX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultCreateQueueErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CREATE_QUEUE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultCreateThreadErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CREATE_THREAD
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultNotConnectedErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONNECTION_NOT_INITIALIZED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultAlreadyAssignHostErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_ALREADY_ASSIGN_HOST
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultSessionErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SESSION
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultClientProcessMaxErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CLIENT_PROCESS_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultIpcSessionMaxErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_IPC_SESSION_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultAlreadyInitializedErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_ALREADY_INITIALIZED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultNotInitializedErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_NOT_INITIALIZED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultMessageSendToListenThreadErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_MSGQ_SEND_LSN
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultMessageRecvInListenThreadErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_MSGQ_RECV_LSN
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultMessageRecvInCommunicationThreadErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_MSGQ_RECV_COMM
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultConnectionNoMoreErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONN_NOMORE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultNoSuchConnectionErr,
        detail::MakePermanentResult, Result::SUMMARY_NOT_FOUND, ER_CONN_NOSUCH
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultConnectionStatusErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONN_STATUS
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultConnectionAddErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONN_ADD
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultConnectionCanceledErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONN_CANCELED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultConnectionHostMaxErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONN_HOST_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultConnectionProcessMaxErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_CONN_PROCESS_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultRequestUrlErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_REQ_URL
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultRequestPortErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_REQ_CONNMSG_PORT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultRequestUnknownMethodErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_REQ_UNKNOWN_METHOD
    );


    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultRequestHeaderErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_RES_HEADER
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultRequestNoNewLineErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_RES_NONEWLINE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultBodyBufErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_RES_BODYBUF
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultBodyBufShortage,
        detail::MakePermanentResult, Result::SUMMARY_WOULD_BLOCK, ER_RES_BODYBUF_SHORTAGE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultPostAddedAnotherErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_POST_ADDED_ANOTHER
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultPostBoundaryErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_POST_BOUNDARY
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultPostSendErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_POST_SEND
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultPostUnknownEnctypeErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_POST_UNKNOWN_ENCTYPE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultPostNoDataErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_POST_NODATA
    );


    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultSslErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultCertExistErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_CERT_EXIST
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultNoCaCertStoreErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_NO_CA_CERT_STORE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultNoClientCertErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_NO_CLIENT_CERT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultCaCertStoreMaxErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_CA_CERT_STORE_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultClientCertMaxErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_CLIENT_CERT_MAX
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultFailToCreateCertStoreErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_FAIL_TO_CREATE_CERT_STORE
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultFailToCreateClientCertErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SSL_FAIL_TO_CREATE_CLIENT_CERT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultDnsResolutionErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SOC_DNS
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultSocketSendErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SOC_SEND
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultSocketReceiveErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SOC_RECV
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultSocketConnectErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SOC_CONN
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultGetProxySettingErr,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_GET_PROXY_SETTING
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultNotImplementedErr,
        detail::MakePermanentResult, Result::SUMMARY_INTERNAL, nn::Result::DESCRIPTION_NOT_IMPLEMENTED
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultTimeout,
        detail::MakePermanentResult, Result::SUMMARY_NOTHING_HAPPENED, ER_TIMEOUT
    );

    /* Please see man pages for details 
        
        
        
    */
    NN_DEFINE_RESULT_CONST_LM(
        ResultSocketKeepAliveDisconnected,
        detail::MakePermanentResult, Result::SUMMARY_INVALID_STATE, ER_SOC_KEEPALIVE_DISCONNECTED
    );
}
}

#endif // __cplusplus





#endif /* NN_NHTTP_NHTTP_RESULT_H_ */
