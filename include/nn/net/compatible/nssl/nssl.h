/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nssl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef __NSSL_H__
#define __NSSL_H__

/*---------------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------------*/

#include <nn/net/compatible/nos.h>

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/
#define NSSL_VERIFY_NONE                         0x00
#define NSSL_VERIFY_COMMON_NAME                  0x01
#define NSSL_VERIFY_ROOT_CA                      0x02
#define NSSL_VERIFY_DATE                         0x04

/* Removed because with the BSAFE verification system, could not turned off the chain verification "only" */
/* 2011/07/29 Restored */
#define NSSL_VERIFY_CHAIN                        0x08

#define NSSL_VERIFY_SUBJECT_ALT_NAME             0x10
#define NSSL_VERIFY_EV                           0x20
#define NSSL_OPTION_SESSION_CACHE                0x100
#define NSSL_VERIFY_IGNORE                       0x200 /*Option to verify certificate, but connect by ignoring verification results*/
#define NSSL_GET_ALL_SERVER_CERT_CHAIN           0x400 /*Option to get all data of the certificate chain*/

#define NSSL_OPTION_NO_TLSv11                    0x800 /*Option to disable TLS1.1. When it is used, communications are with TLS1.0.*/

#define NSSL_ERROR_BASE                          0xfffff000
#define NSSL_ERROR_CODE(code)                    ((s32)(NSSL_ERROR_BASE|(code)))

/* Specify all values so that what error occurs can be determined when the error code is printed in numbers */
enum {
    NSSL_EFAILED                                 = NSSL_ERROR_CODE(1),
    NSSL_EWANT_READ                              = NSSL_ERROR_CODE(2),
    NSSL_EWANT_WRITE                             = NSSL_ERROR_CODE(3),
    NSSL_ESYSCALL                                = NSSL_ERROR_CODE(5),
    NSSL_EZERO_RETURN                            = NSSL_ERROR_CODE(6),
    NSSL_EWANT_CONNECT                           = NSSL_ERROR_CODE(7),
    NSSL_ESSLID                                  = NSSL_ERROR_CODE(8),
    NSSL_EVERIFY_COMMON_NAME                     = NSSL_ERROR_CODE(9),
    NSSL_EVERIFY_ROOT_CA                         = NSSL_ERROR_CODE(10),
    NSSL_EVERIFY_CHAIN                           = NSSL_ERROR_CODE(11),
    NSSL_EVERIFY_DATE                            = NSSL_ERROR_CODE(12),
    NSSL_EGET_SERVER_CERT                        = NSSL_ERROR_CODE(13),
    NSSL_EROOTCAID                               = NSSL_ERROR_CODE(14), // Not used
    NSSL_ECLIENTCERTID                           = NSSL_ERROR_CODE(15), // Not used
    NSSL_EVERIFY_REVOKED_CERT                    = NSSL_ERROR_CODE(16),
    NSSL_ESTATE                                  = NSSL_ERROR_CODE(17),
    NSSL_EVERIFY_USER                            = NSSL_ERROR_CODE(18),
    NSSL_ERANDOM                                 = NSSL_ERROR_CODE(19),
    NSSL_EVERIFY_SERVER_CERT                     = NSSL_ERROR_CODE(20),
    NSSL_ECERT_BUF_ALREADY_SET                   = NSSL_ERROR_CODE(21),
    NSSL_ENOMEM                           		 = NSSL_ERROR_CODE(22), /* Support for memory allocation failure error code */
    NSSL_ENONE                                   = 0
};

/* Please see man pages for details 
 
 
 */
#define NSSL_ID_MAX                              6

/* Please see man pages for details 
 
 */
#define CERT_SIZE               1024*2  /* Please see man pages for details */

#define NSSL_CERTS_MAX          50      /* Please see man pages for details */
#define NSSL_CERTSTORE_MAX      14      /* Please see man pages for details */
#define NSSL_CERTS_PER_STORE    40      /* Please see man pages for details */

#define NSSL_CRLS_MAX           10      /* Please see man pages for details */
#define NSSL_CRLSTORE_MAX       3       /* Please see man pages for details */
#define NSSL_CRLS_PER_STORE     3       /* Please see man pages for details */

#define NSSL_EV_MAX             30       /* Please see man pages for details */
/**/

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 
 
 
 
 
 */
typedef struct NSSLConfig
{
    /* Please see man pages for details 
     
     
     
     */
    void* (*alloc)(u32 name, u32 size, u32 align);
    /* Please see man pages for details 
     
     
     */
    void  (*free)(u32 name, void *ptr);
    /* Please see man pages for details 
     
     
     
     
     */
    void* (*realloc)(void *ptr, u32 size);
    /* Please see man pages for details 
     
     
     
     */
    u32   fixedHeapSize;
} NSSLConfig;

typedef s32 NSSLId; /* Please see man pages for details */
typedef s32 NSSLCertId; /* Please see man pages for details */
typedef s32 NSSLCertStoreId; /* Please see man pages for details */
typedef s32 NSSLCRLId; /* Please see man pages for details */
typedef s32 NSSLCRLStoreId; /* Please see man pages for details */

/* For debugging */
typedef struct NSSLResource
{
    int numDescSsl;
    u32 freeHeapSize;
    u32 usedHeapSize;
    u32 maxHeapSize;
} NSSLResource;

/*---------------------------------------------------------------------------*
 * Cert Data
 *---------------------------------------------------------------------------*/
#define NSSL_ROOTCA_NINTENDO_0                   1
#define NSSL_ROOTCA_NINTENDO_1                   2
#define NSSL_ROOTCA_NINTENDO_2                   3

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
s32             NSSL_Init            ( const NSSLConfig* config );
s32             NSSL_Finish          ( void );
NSSLId          NSSL_NewClient       ( int socket, u32 option, const char* serverName );
s32             NSSL_DoHandshake     ( NSSLId sslId );
s32             NSSL_DoHandshakeEx   ( NSSLId sslId, char* serverCertData, size_t serverCertSize, u32* serverCertNum );
s32             NSSL_DoHandshakeWithGetCertInfo(NSSLId sslId, size_t* serverCertSize, u32* serverCertNum );
s32             NSSL_Read            ( NSSLId sslId, char* buf, size_t bufSize );
s32             NSSL_Peek            ( NSSLId sslId, char* buf, size_t bufSize );
s32             NSSL_Write           ( NSSLId sslId, const char* buf, size_t bufSize );
s32             NSSL_Shutdown        ( NSSLId sslId );
s32             NSSL_SetServerCertStore(NSSLId sslId, NSSLCertStoreId storeId);
s32             NSSL_SetClientCert        ( NSSLId sslId, NSSLCertId certId);
s32             NSSL_SetCRLStore          ( NSSLId sslId, NSSLCRLStoreId storeId);
s32             NSSL_DisableVerifyOptionForDebug( NSSLId i_sslId, u32 i_verifyOption );

s32             NSSL_SetUTCTime           ( s64 utcTime );

s32             NSSL_GetCipherInfo( NSSLId sslId, char** version, char** name, int* algBits, int* effectiveBits );
s32             NSSL_GetCertVerifyErrors( NSSLId sslId, u32* pCertVerifyErrors);
s32             NSSL_SetServerCertBuffer( NSSLId sslId, u8* pBuf, size_t bufSize);

void            NSSL_GetResource(NSSLResource* resource);

/* functions for certificates */
NSSLCertId      NSSL_RegisterCert(u8 *cert, int certSize);
NSSLCertId      NSSL_RegisterCertWithKey(u8 *cert, int certSize, u8 *key, int keySize);
s32             NSSL_UnregisterCert(NSSLCertId certId);
BOOL            NSSL_IsValidCertId(NSSLCertId id);

/* functions for certificate store */
NSSLCertStoreId NSSL_CertStore_Create(void);
s32             NSSL_CertStore_Destroy(NSSLCertStoreId storeId);
void            NSSL_CertStore_DestroyAll(NSSLCertStoreId storeId);
s32             NSSL_CertStore_AddCert(NSSLCertStoreId storeId, NSSLCertId certId);
s32             NSSL_CertStore_RemoveCert(NSSLCertStoreId storeId, NSSLCertId certId);
BOOL            NSSL_CertStore_IsValidId(NSSLCertStoreId storeId);

/* functions for CRL */
NSSLCRLId       NSSL_RegisterCRL(u8 *crl, int len);
s32             NSSL_UnregisterCRL(NSSLCRLId crlId);
BOOL            NSSL_IsValidCRLId(NSSLCRLId id);

/* functions for CRL store */
NSSLCRLStoreId  NSSL_CRLStore_Create(void);
s32             NSSL_CRLStore_Destroy(NSSLCRLStoreId storeId);
void            NSSL_CRLStore_DestroyAll(NSSLCRLStoreId storeId);
s32             NSSL_CRLStore_AddCRL(NSSLCRLStoreId storeId, NSSLCRLId crlId);
s32             NSSL_CRLStore_RemoveCRL(NSSLCRLStoreId storeId, NSSLCRLId crlId);
BOOL            NSSL_CRLStore_IsValidId(NSSLCRLStoreId storeId);

BOOL            NSSL_IsAvailable     ( void );
void            NSSL_GatherEntropy   ( void );

#ifdef  __cplusplus
}
#endif  // __cplusplus
#endif  // __NSSL_H__
