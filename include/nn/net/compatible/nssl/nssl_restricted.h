/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nssl_restricted.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef __NSSL_RESTRICTED_H__
#define __NSSL_RESTRICTED_H__

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

/*---------------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------------*/

#include <nn/net/compatible/nos.h>

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/
#define NSSL_MAX_SSLCERT_NAME_BUF_LEN            256 /* Only used in NSSLCertInfo */

/* errors that are set in verifyCB() */
#define NSSL_VERIFYERRORS_COMMON_NAME            0x01
#define NSSL_VERIFYERRORS_ROOT_CA                0x02
#define NSSL_VERIFYERRORS_DATE                   0x04
#define NSSL_VERIFYERRORS_CHAIN                  0x08
#define NSSL_VERIFYERRORS_REVOKED_CERT           0x20
#define NSSL_VERIFYERRORS_USER                   0x40
#define NSSL_VERIFYERRORS_EV                     0x80

#define NSSL_CPS_URI_LENGTH                      256

/*---------------------------------------------------------------------------*
 * EV Policy ID
 *---------------------------------------------------------------------------*/
#define NSSL_EVID_COMODO             "1.3.6.1.4.1.6449.1.2.1.5.1"
#define NSSL_EVID_CYBERTRUST         "1.3.6.1.4.1.6334.1.100.1"
#define NSSL_EVID_DIGICERT           "2.16.840.1.114412.2.1"
#define NSSL_EVID_DIGINOTAR          "2.16.528.1.1001.1.1.1"
#define NSSL_EVID_ENTRUST            "2.16.840.1.114028.10.1.2"
#define NSSL_EVID_GEOTRUST           "1.3.6.1.4.1.14370.1.6"
#define NSSL_EVID_GLOBALSIGN         "1.3.6.1.4.1.4146.1.1"
#define NSSL_EVID_GODADDY            "2.16.840.1.114413.1.7.23.3"
#define NSSL_EVID_NETWORKSOLUTIONS   "1.3.6.1.4.1.782.1.2.1.8.1"
#define NSSL_EVID_QUOVADIS           "1.3.6.1.4.1.8024.0.2.100.1.2"
#define NSSL_EVID_SECOM              "1.2.392.200091.100.731.1"
#define NSSL_EVID_STARFIELD          "2.16.840.1.114414.1.7.23.3"
#define NSSL_EVID_SWISSSIGN          "2.16.756.1.89.1.2.1.1"
#define NSSL_EVID_THAWTE             "2.16.840.1.113733.1.7.48.1"
#define NSSL_EVID_TRUSTWAVE          "2.16.840.1.114404.1.1.2.4.1"
#define NSSL_EVID_VERISIGN           "2.16.840.1.113733.1.7.23.6"

/*---------------------------------------------------------------------------*
 * Types/Declarations
 *---------------------------------------------------------------------------*/

typedef struct NSSLCertInfo {
    char subjectName[NSSL_MAX_SSLCERT_NAME_BUF_LEN];
    char issuerName[NSSL_MAX_SSLCERT_NAME_BUF_LEN];
    u8* serialNumber; // big-endian byte stream
    u32 serialNumberSize;
    u32 notBefore; // seconds
    u32 notAfter;  // seconds
    u8 fingerPrint[20];

    BOOL isEV;
    u8 cpsURI[NSSL_CPS_URI_LENGTH];

} NSSLCertInfo;

typedef BOOL (*NSSLVerifyCallback)( u32 errors,
                                    const NSSLCertInfo* serverCertInfo,
                                    const NSSLCertInfo* rootCACertInfo,
                                    void* userArg );

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/
s32     NSSL_SetVerifyCallback    ( NSSLId sslId, NSSLVerifyCallback verifyCallback, void* userArg );
s32     NSSL_AddEVPolicyId(NSSLId sslId, char *policyId);

#ifdef  __cplusplus
}
#endif  // __cplusplus
#endif  // __NSSL_RESTRICTED_H__
