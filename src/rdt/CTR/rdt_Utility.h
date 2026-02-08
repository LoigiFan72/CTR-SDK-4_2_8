/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Utility.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_UTILITY_H_
#define NN_RDT_UTILITY_H_


#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include <time.h>
#else
#include <nn/types.h>
#endif

#include <nn/rdt/CTR/rdt_Misc.h>

/* Please see man pages for details 
    
*/

#ifdef _WIN32
#define PRINTF printf
#else
#define PRINTF NN_LOG
#endif


inline void infinite_loop(void)
{
#if defined(NN_BUILD_NOOPT) || defined(NN_BUILD_VERBOSE)
    while(1)
    {
    }
#else
    // Do nothing. (Release build)
#endif
}


#define WARNING(exp) (void) ((exp) || (nn::rdt::CTR::GetLogLevel()==nn::rdt::CTR::LOG_LEVEL_NONE) || \
                                  (PRINTF("WARNING: %s line: %d\n", __FILE__, __LINE__), \
                                  0))


#define WARNINGMSG(exp, ...) (void) ((exp) || (nn::rdt::CTR::GetLogLevel()==nn::rdt::CTR::LOG_LEVEL_NONE) ||  \
                                  (PRINTF("WARNING: %s line: %d ", __FILE__, __LINE__), \
                                   PRINTF(__VA_ARGS__),                                 \
                                   PRINTF("\n"),                                        \
                                  0))

#define PANIC(...) (void) (PRINTF("PANIC: %s line: %d ", __FILE__, __LINE__), \
                           PRINTF(__VA_ARGS__),                               \
                           PRINTF("\n"),                                      \
                           infinite_loop()/*abort()*/)

#define ASSERT(exp) (void) ((exp) || \
                             (PRINTF("ASSERT: %s line: %d\n", __FILE__, __LINE__), \
                              infinite_loop() /*abort()*/,                         \
                              0))



#define ASSERTMSG(exp, ...) (void) ((exp) || \
                                    (PRINTF("ASSERTMSG: %s line: %d ", __FILE__, __LINE__), \
                                     PRINTF(__VA_ARGS__),                                   \
                                     PRINTF("\n"),                                          \
                                     infinite_loop() /*abort()*/,                           \
                                     0))

#define LOG(...) if(nn::rdt::CTR::GetLogLevel()==nn::rdt::CTR::LOG_LEVEL_ALL)(void) (PRINTF(__VA_ARGS__))

#define VERBOSE(...) (void)(0)


#ifdef _WIN32
#define ALIGN_ASSERT(exp, align) ASSERTMSG( ((uptr)(exp)) % (align) == 0, "%s must be %d byte aligned.", #exp, align )
#elif defined(NN_PLATFORM_CTR)
#define ALIGN_ASSERT(exp, align) NN_ALIGN_ASSERT(exp, align)
#endif

//#define alignof(type) ((int)offsetof(struct { char top; type bot; }, bot))
template <class T>
class Align{
public:
    Align(void)
    {
        struct S{
            char top;  // Only want a 1-byte variable.
            T    t;
        };

        LOG("offset: %d\n", offsetof(S, t));
    }
};


namespace nn { namespace rdt { namespace CTR {

// Forward declaration
class Sender;
class Receiver;

// Performs network preparation and cleanup.
// Purpose is to keep until the state where data transmission can be done.
void SetupNetwork  (void);
void CleanupNetwork(void);

// Create and destroy instances. Use Destroy function to destroy the pointers returned by Create group functions.
Sender*   CreateSender   (u16 port, void *pSendBuf, u16 sendBufSize);
void      DestroySender  (Sender *s);

Receiver* CreateReceiver (u16 port, void *pRecvBuf, u16 recvBufSize);
void      DestroyReceiver(Receiver *r);

// Thread idle. Difference between Windows environment and CTR environment is eliminated with internal implementation.
void SleepCurrentThread(s32 msec);


// Used when the pointer to the buffer is a NULL pointer.
inline nn::Result MakeNullPointerResult(void)
{
    return MakeUsageResult(
        Result::SUMMARY_INVALID_ARGUMENT,
        Result::MODULE_NN_RDT,
        Result::DESCRIPTION_INVALID_POINTER);
}


// Used when the argument displaying buffer length is zero.
inline nn::Result MakeZeroSizeResult(void)
{
    return MakeUsageResult(
        Result::SUMMARY_INVALID_ARGUMENT,
        Result::MODULE_NN_RDT,
        Result::DESCRIPTION_INVALID_SIZE);
}


// Used when not in a state in which functions should be called.
inline nn::Result MakeInvalidState(void)
{
    return MakeStatusResult(
        Result::SUMMARY_INVALID_STATE,
        Result::MODULE_NN_RDT,
        Result::DESCRIPTION_INVALID_RESULT_VALUE);  //  Value is not appropriate?
}


// Return value of a unimplemented function.
inline nn::Result MakeNotImplemented(void)
{
    return MakeFatalResult(
        Result::SUMMARY_INTERNAL,
        Result::MODULE_NN_RDT,
        Result::DESCRIPTION_NOT_IMPLEMENTED);
}


// Failure in resource allocation
inline nn::Result MakeResourceAllocationFailure(void)
{
    return MakeStatusResult(
        Result::SUMMARY_OUT_OF_RESOURCE,
        Result::MODULE_NN_RDT,
        Result::DESCRIPTION_OUT_OF_MEMORY);   // Would like a DESCRIPTION of the case when resources other than memory are insufficient...
}


// Returns as a case when initialization is attempted in a state where initialization has been completed.
inline nn::Result MakeAlreadyInitialized(void)
{
        return MakeInfoResult(
            Result::SUMMARY_NOTHING_HAPPENED,
            Result::MODULE_NN_RDT,
            Result::DESCRIPTION_ALREADY_INITIALIZED);
}


// When RST is received from a remote site, this error code notifies the user of that fact.
inline nn::Result MakeResetReceived(void)
{
        return MakeReInitResult(
            Result::SUMMARY_CANCELLED,            // 
            Result::MODULE_NN_RDT,
            Result::DESCRIPTION_CANCEL_REQUESTED);  //
}


// Error when the connection is lost.
inline nn::Result MakeDisconnected(void)
{
        return MakeReInitResult(
            Result::SUMMARY_OUT_OF_RESOURCE,
            Result::MODULE_NN_RDT,
            Result::DESCRIPTION_NOT_FOUND);       //
}


// When there is no received segment (not arrived yet).
inline nn::Result MakeNoData(void)
{
    return MakeTemporaryResult(
        Result::SUMMARY_NOT_FOUND,
        Result::MODULE_NN_RDT,
        Result::DESCRIPTION_NO_DATA);
}


// Used when there is a slight concern about it, but not so much as to have an error declaration.
inline nn::Result MakeNothingHappened(void)
{
        return MakeInfoResult(
            Result::SUMMARY_NOTHING_HAPPENED,
            Result::MODULE_NN_RDT,
            Result::DESCRIPTION_SUCCESS);
}

#ifdef _WIN32
// Executes setup and cleanup of server-side socket. For Windows only.
// The implementation calls listen(), accept(), and other processes to prepare for the sending and receiving of data. 
// 
SOCKET SetupServerSide(u16 port);
void CleanupServerSide(SOCKET sock);

// Executes setup and cleanup of client-side socket.
// The implementation calls connect() and other processes to prepare to send and receive data. 
// 
SOCKET SetupClientSide(u16 port);
void CleanupClientSide(SOCKET sock);

// Returns the port number that can be used.
u16 GetAvailablePort(void);

// Millisecond format.
typedef clock_t MSEC_T;
MSEC_T GetCurrentTimeAsMillisecond(void);

#else
template <class T>
T min(T a, T b)
{
    return a < b ? a : b;
}

template <class T>
T max(T a, T b)
{
    return a > b ? a : b;
}


// Millisecond format.
typedef s64 MSEC_T;
MSEC_T GetCurrentTimeAsMillisecond(void);


void PrintResultCode(nn::Result r);

#endif // end of _WIN32


// When this function was called, gets how much of the stack was consumed.
void stackChecker(void);


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_UTILITY_H_
