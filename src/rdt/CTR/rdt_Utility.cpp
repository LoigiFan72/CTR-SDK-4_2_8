/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Utility.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_Utility.h"

#include <nn/rdt/CTR/rdt_Sender.h>
#include <nn/rdt/CTR/rdt_Receiver.h>

#ifdef _WIN32
#include <iostream>
#include <assert.h>
#else
#include <nn/os.h>
#include <nn/fnd.h>
#include <nn/dbg.h>
#endif  // end of _WIN32

namespace
{
#ifdef _WIN32
    WSADATA s_wsaData;
    SOCKET  s_sendSock = INVALID_SOCKET;
    SOCKET  s_recvSock = INVALID_SOCKET;
    u8      s_senderWorkBuf[nn::rdt::CTR::Sender::SENDER_WORKBUF_SIZE];
    u8      s_receiverWorkBuf[nn::rdt::CTR::Receiver::RECEIVER_WORKBUF_SIZE];
#endif
}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {

                   
#ifdef _WIN32
void SetupNetwork(void)
{
    // Specifies winsock version. Seems to be three types: 1.0, 1.1, and 2.0.
    int result = WSAStartup(MAKEWORD(2, 0), &s_wsaData);
    assert(result==0);  // Zero is returned if successful.
}


void CleanupNetwork(void)
{
    WSACleanup();
}


SOCKET SetupServerSide(u16 port)
{
    using namespace std;

    SOCKET sock0;              // Socket waiting for connection
    struct sockaddr_in addr;   // Information of socket to establish a pair with client that connects
    struct sockaddr_in client; // Stores information of newly connected client
    int len;
    SOCKET sock;
    int result = 0;

    // Create socket
    sock0 = socket(AF_INET, SOCK_STREAM, 0);
    // sock0 = socket(AF_UNSPEC, SOCK_STREAM, 0);  // Example of deliberate failure.
    if(sock0==INVALID_SOCKET)
    {
        cout << "socket() failed." << "Error: " << WSAGetLastError() << endl;
        abort();
    }

    // Socket settings
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);  // Byte order conversion. Host to Network short.
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    result = bind(sock0, (struct sockaddr*)&addr, sizeof(addr));
    if(result!=0)
    {
        cout << "port: " << port << endl;
        cout << "bind() failed. " << "Error: " << WSAGetLastError() << endl;
        abort();
    }

    // Wait
    result = listen(sock0, 5);
    assert(result==0);  // If no errors, listen() returns zero.


    // Allow connections
    len = sizeof(client);
////    cout << "Before the accept function was called, 'len' was " << len << "." << endl;
    sock = accept(sock0, (struct sockaddr*)&client, &len);
    if(sock==INVALID_SOCKET)
    {
        cout << "accept() failed." << "Error: " << WSAGetLastError() << endl;
        abort();
    }
////    cout  << "After the accept function was called, 'len' became " << len << "." << endl;

    // Make socket to non-blocking mode
    {
        u_long val = 1;
        int ret = ioctlsocket(sock, FIONBIO, &val);
        if(ret!=0)
        {
            printf("error: %d\n", ret);
            abort();
        }
    }

    return sock;
}


void CleanupServerSide(SOCKET sock)
{
    // TCP session end
    closesocket(sock);
}


SOCKET SetupClientSide(u16 port)
{
    struct sockaddr_in server;
    SOCKET sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Structure to specify connection destination
    server.sin_family = AF_INET;
    server.sin_port   = htons(port);  // Network byte order conversion
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    // Connect to server. If no errors occur, connect() returns zero.
    int ret = connect(sock, (struct sockaddr *)&server, sizeof(server));
    assert(ret==0);

    // Make socket to non-blocking mode
    {
        u_long val = 1;
        int ret = ioctlsocket(sock, FIONBIO, &val);
        if(ret!=0)
        {
            printf("error: %d\n", ret);
            abort();
        }
    }

    return sock;
}


void CleanupClientSide(SOCKET sock)
{
    closesocket(sock);
}


// Returns the port number that can be used.
// Port numbers are differentiated for debug builds and release builds
// (targeting simultaneous execution)
u16 GetAvailablePort(void)
{
    const u16 PERIOD = 5000;
#ifdef NDEBUG
    const u16 OFFSET = 50000;
#else
    const u16 OFFSET = 50000 + PERIOD;
#endif

    static u16 s_counter = 0;

    u16 ret = s_counter + OFFSET;
    s_counter = (s_counter + 1) % PERIOD;

    // Port numbers that can be freely used are nos. 49152 - 65535
    ASSERT((49152<=ret) && (ret <= 65535));
    return ret;
}


// Create and destroy instances.
Sender* CreateSender(u16 port, void *pSendBuf, u16 sendBufSize)
{
    if(s_sendSock==INVALID_SOCKET)
    {
        s_sendSock = SetupClientSide(port);
        if(s_sendSock!=INVALID_SOCKET)
        {
            Sender *s = new Sender();
            SenderConfig cfg;
            cfg.pWorkBuf    = s_senderWorkBuf;
            cfg.pSendBuf    = pSendBuf;
            cfg.sendBufSize = sendBufSize;
            cfg.sock        = s_sendSock;
            nn::Result result = s->Initialize(cfg);
            if(result.IsFailure())
            {
                PANIC("Sender initialization failed! \n");
            }
            return s;
        }
        else
        {
            PANIC("Failed to create socket. \n");
            return NULL;
        }
    }
    else
    {
        PANIC("%s called multiple times. \n", __FUNCTION__);
        return NULL;
    }
}


void DestroySender(Sender *s)
{
    ASSERT(s!=NULL);
    ASSERT(s_sendSock!=INVALID_SOCKET);

    s->Finalize();
    delete s;
    CleanupClientSide(s_sendSock);
    s_sendSock = INVALID_SOCKET;
}


Receiver* CreateReceiver (u16 port, void *pRecvBuf, u16 recvBufSize)
{
    if(s_recvSock==INVALID_SOCKET)
    {
        s_recvSock = SetupServerSide(port);
        if(s_recvSock!=INVALID_SOCKET)
        {
            Receiver *r = new Receiver();
            ReceiverConfig cfg;
            cfg.pWorkBuf    = s_receiverWorkBuf;
            cfg.pRecvBuf    = pRecvBuf;
            cfg.recvBufSize = recvBufSize;
            cfg.sock        = s_recvSock;
            nn::Result result = r->Initialize(cfg);
            if(result.IsFailure())
            {
                PANIC("Receiver initialization failed! \n");
            }
            return r;
        }
        else
        {
            PANIC("Failed to create socket. \n");
            return NULL;
        }
    }
    else
    {
        PANIC("%s called multiple times. \n", __FUNCTION__);
        return NULL;
    }
}


void DestroyReceiver(Receiver *r)
{
    ASSERT(r!=NULL);
    ASSERT(s_recvSock!=INVALID_SOCKET);

    delete r;
    CleanupClientSide(s_recvSock);
    s_recvSock = INVALID_SOCKET;
}


void SleepCurrentThread(s32 msec)
{
    Sleep(msec);
}


MSEC_T GetCurrentTimeAsMillisecond(void)
{
    return clock();
}


#else
// Below is for CTR.


void SleepCurrentThread(s32 msec)
{
    nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(msec));
}


MSEC_T GetCurrentTimeAsMillisecond(void)
{
    return nn::os::Tick::GetSystemCurrent().ToTimeSpan().GetMilliSeconds();
}


void PrintResultCode(nn::Result r)
{
    if(GetLogLevel()==LOG_LEVEL_ALL)
    {
        if(r.IsSuccess())
        {
            LOG("Success.\n");
        }
        else
        {
            LOG("Failure...\n");
            NN_DBG_TPRINT_RESULT_(r);
        }
    }
}


#endif

// When this function was called, gets how much of the stack was consumed.
void stackChecker(void)
{
    int dmy;
#ifdef NN_SWITCH_DISABLE_DEBUG_PRINT
    NN_UNUSED_VAR(dmy);
#endif
    LOG("addr: 0x%08x\n", &dmy);
    LOG("%d bytes used.\n", 0x0fffffff - reinterpret_cast<u32>(&dmy));
}



}}} // namespace nn::rdt::CTR
