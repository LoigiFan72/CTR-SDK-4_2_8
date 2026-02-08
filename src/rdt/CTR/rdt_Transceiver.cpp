/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Transceiver.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#include "rdt_Transceiver.h"

#include <nn/rdt/CTR/rdt_Result.h>

#include "Test.h"
#include "rdt_Segment.h"
#include "rdt_Stopwatch.h"
#include "rdt_Utility.h"

namespace
{

#ifdef _WIN32
    /* Please see man pages for details 
    
            
     */
    int SendRawData(SOCKET &sock, const void *pBuf, size_t bufSize)
    {
        ASSERT(pBuf!=NULL);
        ASSERT(bufSize > 0);

        const int c_flags = 0;
        int ret = ::send(sock, static_cast<const char*>(pBuf), bufSize, c_flags);
        if(ret < 1)
        {
            int err = WSAGetLastError();
            VERBOSE("::send() returned an error. (%d)\n", err);
            if(err==WSAEWOULDBLOCK)
            {
                // Resource temporarily unavailable
                VERBOSE("Continues because the error code was WSAEWOULDBLOCK. \n");
                return 0;
            }
            else if(err==WSAECONNRESET)
            {
                // Connection reset by peer.
                VERBOSE("The error code was WSAECONNRESET. Continues. \n");
                return 0;
            }
            else if(err==WSAECONNABORTED)
            {
                // Software caused connection abort. 
                VERBOSE("The error code was WSAECONNABORTED. Continues. \n");
                return 0;
            }
            else
            {
                PANIC("Stop. err = %d\n", err);
                return -1;
            }
        }
        else
        {
            return ret;
        }
    }


    /* Please see man pages for details 
    
           
           
     */
    int RecvRawData(SOCKET &sock, void *pBuf, size_t bufSize)
    {
        int ret = ::recv(sock, static_cast<char*>(pBuf), bufSize, 0);
        if(ret < 0)
        {
            int err = WSAGetLastError();
            switch(err)
            {
            case WSAEWOULDBLOCK:
                // Simply, there was no data.
                return 0;
            case WSAECONNRESET:
                LOG("Because the remote connection disappeared, data could not be obtained. \n");
                return -1;
            case WSAECONNABORTED:
                LOG("The host side aborted the connection. \n");
                return -1;
            default:
                LOG("::recv function returned an unknown error. (%d)\n", err);
                return -1;
            }
        }
        else
        {
            return ret;
        }
    }

#elif defined(NN_PLATFORM_CTR)

    // Different from the Windows version, added an argument to get uds errors.
    int SendRawData(nn::uds::EndpointDescriptor *pSendEp, u16 nodeId, u8 port, const void *pBuf, size_t bufSize, nn::Result *pResult)
    {
        using namespace nn::uds;
        ASSERT(pSendEp!=NULL);
        ASSERT(pBuf!=NULL);
        ASSERT(bufSize > 0);
        ASSERT(bufSize <= UDS_PACKET_PAYLOAD_MAX_SIZE);     // Does not exceed UDS packet maximum payload size
        ASSERT(pResult!=NULL);

        const bit8 c_option = NO_WAIT;

        // Measure with stop watch.
        static nn::rdt::CTR::detail::Stopwatch s_sw("uds::SendTo()");
        s_sw.Start();
        *pResult = SendTo(*pSendEp, pBuf, bufSize, nodeId, port, c_option);
        s_sw.Stop();

        if(pResult->IsSuccess())
        {
            VERBOSE("Sent data.\n");
            return bufSize;
        }
        else
        {
            nn::rdt::CTR::PrintResultCode(*pResult);
            LOG("SendTo() Failed.\n");
            return -1;
        }
    }

    // Different from the Windows version, added an argument to get uds errors.
    int RecvRawData(nn::uds::EndpointDescriptor *pRecvEp, void *pBuf, size_t bufSize, nn::Result *pResult)
    {
        using namespace nn::uds;
        ASSERT(pRecvEp!=NULL);
        ASSERT(pBuf!=NULL);
        ASSERT(bufSize > 0);
        ASSERT(bufSize <= UDS_PACKET_PAYLOAD_MAX_SIZE);     // Does not exceed UDS packet maximum payload size
        ASSERT(pResult!=NULL);

        u16 srcNodeId = 0x0000;
        size_t received = 0;
        const bit8 opt = nn::uds::NO_WAIT;

        // Measure with stopwatch.
        static nn::rdt::CTR::detail::Stopwatch s_sw("uds::ReceiveFrom()");
        s_sw.Start();
        *pResult = ReceiveFrom(*pRecvEp, pBuf, &received, &srcNodeId, bufSize, opt);
        s_sw.Stop();

        if(pResult->IsSuccess())
        {
            VERBOSE("Received.  Src Node: %u\n", srcNodeId);
            return received;
        }
        else
        {
            if(pResult->GetSummary()==nn::Result::SUMMARY_NOT_FOUND)
            {
                VERBOSE("It seems that data is not arrived.  It is not an error.\n");
                return 0;
            }
            else
            {
                nn::rdt::CTR::PrintResultCode(*pResult);
                LOG("ReceiveFrom() failed.\n");
                return -1;
            }
        }
    }
#endif // end of _WIN32


#ifdef _WIN32
    u16 port = 0;
    nn::rdt::CTR::Segment s_sendSeg;
    nn::rdt::CTR::Segment s_recvSeg;
    const char *c_msg = "Transceiver Unit Test\n";

    // For single unit tests.
    void serverSide(LPVOID pParam)
    {
        using namespace nn::rdt::CTR;
        SOCKET sock = SetupServerSide(port);

        // Wait until data arrives
        SleepCurrentThread(1000);

        Transceiver t;
        nn::Result result = t.Initialize(sock);
        CU_ASSERT(result.IsSuccess());

        result = t.Pull(&s_recvSeg);
        CU_ASSERT(result.IsSuccess());

        LOG("The content of the received segment is \n");
        s_recvSeg.PrintDebugInfo();

        LOG("Cleanup of the server-side socket. \n");
        CleanupServerSide(sock);
    }


    // For single unit tests.
    static void clientSide(LPVOID pParam)
    {
        using namespace nn::rdt::CTR;
        SOCKET sock = SetupClientSide(port);

        Transceiver t;
        nn::Result result = t.Initialize(sock);
        CU_ASSERT(result.IsSuccess());
        s_sendSeg.SetData(c_msg, strlen(c_msg));
        t.Put(s_sendSeg);  // Segment transmission

        // TCP session end
        LOG("Cleanup of the client-side socket. \n");
        CleanupClientSide(sock);
    }
#endif  // end of _WIN32

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR {


Transceiver::Transceiver(void)
     :m_initialized(false)
{
}


Transceiver::~Transceiver(void)
{
    Finalize();
}


#ifdef _WIN32
nn::Result Transceiver::Initialize(SOCKET sock)
{
    if(m_initialized)
    {
        return ResultAlreadyInitialized();
    }
    else
    {
        m_sock = sock;
        m_initialized = true;
        return ResultSuccess();
    }
}
#elif defined(NN_PLATFORM_CTR)
nn::Result Transceiver::Initialize(u16 nodeId, u8 port)
{
    if(m_initialized)
    {
        return ResultAlreadyInitialized();
    }
    else
    {
        nn::Result result;
        result = nn::uds::CreateEndpoint(&m_sendEp);
        if(result.IsFailure())
        {
            return result;
        }

        result = nn::uds::CreateEndpoint(&m_recvEp);
        if(result.IsFailure())
        {
            nn::Result r = nn::uds::DestroyEndpoint(&m_sendEp);
            NN_UTIL_PANIC_IF_FAILED(r);
            return result;
        }

        result = nn::uds::Attach(&m_recvEp, nodeId, port);  // Feature similar to bind() + connect() for the socket. Required before Receive function.
        if(result.IsFailure())
        {
            nn::Result r;
            r = nn::uds::DestroyEndpoint(&m_recvEp);
            NN_UTIL_PANIC_IF_FAILED(r);
            r = nn::uds::DestroyEndpoint(&m_sendEp);
            NN_UTIL_PANIC_IF_FAILED(r);
            return result;
        }

        m_remoteNodeId = nodeId;
        m_port = port;
        m_initialized = true;
        VERBOSE("Transceiver initialized.\n");
        return ResultSuccess();
    }
}
#else
    #error no platform selected
#endif


#ifdef _WIN32
void Transceiver::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
    }
    else
    {
        // Do nothing.
    }
}
#elif defined(NN_PLATFORM_CTR)
void Transceiver::Finalize(void)
{
    if(m_initialized)
    {
        m_initialized = false;
        nn::Result result;
        result = nn::uds::DestroyEndpoint(&m_recvEp);
        NN_UTIL_PANIC_IF_FAILED(result);
        result = nn::uds::DestroyEndpoint(&m_sendEp);
        NN_UTIL_PANIC_IF_FAILED(result);
    }
    else
    {
        // Do nothing.
    }
}
#else
    #error no platform selected
#endif


// Sends segment.
nn::Result Transceiver::Put(const Segment &seg)
{
    ASSERT(m_initialized);

#ifdef _WIN32
    int n = SendRawData(m_sock, &seg, sizeof(Segment));
#else
    nn::Result ret;
    int n = SendRawData(&m_sendEp, m_remoteNodeId, m_port, &seg, sizeof(Segment), &ret);
#endif
    if(n==sizeof(Segment))
    {
        // Condition where the transmission probably was made.
        // Whether it actually arrived to the remote side is a different issue.
        VERBOSE("The segment transmission probably was successful. \n");
        return ResultSuccess();
    }
    else
    {
        VERBOSE("An attempt to send the segment was made but it seems that it failed with SendRawData()... (n = %d)\n", n);
#ifdef _WIN32
        return MakeDisconnected();  // Since the Windows environment does not have UDS, we reluctantly evade the issue with MakeDisconnected()
#else
        return ret;                 // Return the UDS errors as is
#endif
    }
}


// Receive segment.
nn::Result Transceiver::Pull(Segment *pSeg)
{
    ASSERT(m_initialized);
    ASSERT(pSeg!=NULL);

#ifdef _WIN32
    int n = RecvRawData(m_sock, pSeg, sizeof(Segment));
#else
    nn::Result ret;
    int n = RecvRawData(&m_recvEp, pSeg, sizeof(Segment), &ret);
#endif
    if((n==sizeof(Segment)) && pSeg->IsValid())
    {
//        LOG("received segment:\n");
//        pSeg->PrintDebugInfo();
        return ResultSuccess();
    }
    else if(n==0)
    {
        // Data has not yet arrived. Through.
        return ResultNoData();
    }
    else
    {
        // Suspect connection interruption.
        LOG("It seems that size of segment is wrong(%d byte)\n", n);
#ifdef _WIN32
        return MakeDisconnected();  // Since the Windows environment does not have UDS, we reluctantly evade the issue with MakeDisconnected()
#else
        return ret;                 // Return the UDS errors as is
#endif
    }
}


#ifdef _WIN32
void Transceiver::Test(void)
{
    port = GetAvailablePort();

    // Create server and client threads
    HANDLE hThread[2];

    hThread[0] = (HANDLE)_beginthread(serverSide, 0, NULL);
    hThread[1] = (HANDLE)_beginthread(clientSide, 0, NULL);

    // Wait for thread to end
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    char buf[Segment::PAYLOAD_SIZE];
    u32 sz = s_recvSeg.GetData(buf, Segment::PAYLOAD_SIZE);
    buf[sz] = '\0';
    CU_ASSERT(strcmp(c_msg, buf)==0);
}
#endif


/*
memo
WSAECONNRESET
10054
 
Connection reset by peer. 
An existing connection was forcibly closed by the remote host.
This normally results if the peer application on the remote host is suddenly stopped,
the host is rebooted, the host or remote network interface is disabled,
or the remote host uses a hard close
(see setsockopt for more information on the SO_LINGER option on the remote socket).
This error may also result if a connection was broken due to keep-alive activity
detecting a failure while one or more operations are in progress.
Operations that were in progress fail with WSAENETRESET.
Subsequent operations fail with WSAECONNRESET.
WSAECONNABORTED
10053
 
Software caused connection abort. 
An established connection was aborted by the software in your host computer,
possibly due to a data transmission time-out or protocol error.








*/

}}} // namespace nn::rdt::CTR
