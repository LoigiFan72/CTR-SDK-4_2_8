/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_IpcWrapper.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_IPCWRAPPER_H_
#define NN_SOCKET_SOCKET_IPCWRAPPER_H_

#include <nn/socket/socket_Types.h>
#include <nn/socket/socket_Const.h>
#include <nn/socket/socket_User.h>

#define NN_SOCKET_RETURN_IF_FAILED(result)  \
    do \
    { \
        ::nn::Result nn_util_return_if_failure_result = (result); \
        if (nn_util_return_if_failure_result.IsFailure()) \
        { \
            return detail::ConvertErrorResult(nn_util_return_if_failure_result); \
        } \
    } while(0)   

namespace nn {
namespace socket {
namespace detail {
    Result Socket( s32* rval, s32 af, s32 type, s32 protocol );
    Result Listen( s32* rval, s32 s, s32 backlog );
    Result Accept( s32* rval, s32 s, u8 sockAddr[], size_t salen );
    Result Bind( s32* rval, s32 s, const u8 sockAddr[], size_t salen );
    Result Connect( s32* rval, s32 s, const u8 sockAddr[], size_t salen );
    Result RecvFrom( s32* rval, s32 s, u8 buf[], s32 len, s32 flags, u8 sockFrom[], size_t salen );
    Result RecvFromSmall( s32* rval, s32 s, u8 buf[], s32 len, s32 flags, u8 sockFrom[], size_t salen );
    Result SendTo( s32* rval, s32 s, const u8 buf[], s32 len, s32 flags, const u8 sockTo[], size_t salen );
    Result SendToSmall( s32* rval, s32 s, const u8 buf[], s32 len, s32 flags, const u8 sockTo[], size_t salen );
    Result SendToSmallMulti( s32* rval, s32 s, const u8 buf[], s32 len, s32 flags, const u8 sockTo[], size_t salen, size_t satotallen );
    Result Close( s32* rval, s32 s );
    Result Shutdown( s32* rval, s32 s, s32 how );
    Result GetSockOpt( s32* rval, s32 s, s32 level, s32 optname, u8 optval[], s32* optlen );
    Result SetSockOpt( s32* rval, s32 s, s32 level, s32 optname, const u8 optval[], s32 optlen );
    Result Fcntl( s32* rval, s32 s, s32 cmd, s32 val );
    Result Poll( s32* rval, PollFd fds[], u32 nfds, s32 timeout );
    Result SockAtMark( s32* rval, s32 s );
    Result GetHostId( u32* hostId );
    Result GetSockName( s32* rval, s32 s, u8 sockAddr[], size_t salen );
    Result GetPeerName( s32* rval, s32 s, u8 sockAddr[], size_t salen );
    Result GetHostByName( s32* rval, const char8 hname[], size_t hnameLen, u8 hostCarrier[], size_t hostCarrierLen );
    Result GetHostByAddr( s32* rval, const u8 addr[], size_t addrLen, s32 type, u8 hostCarrier[], size_t hostCarrierLen );
    Result GetAddrInfo( s32* rval, const char8 nodeName[], size_t nodeNameLen, const char8 servName[], size_t servNameLen, const u8 hints[], s32 hintsLen, s32* resAddrNum, u8 ress[], size_t ressLen );
    Result GetNameInfo( s32* rval, const u8 sa[], size_t saLen, char8 node[], size_t nodeLen, char8 service[], size_t serviceLen, s32 flag );
    Result GetNetworkOpt( s32* rval, s32 level, s32 optname, u8 optval[], s32* optlen );
    Result SetNetworkOpt( s32* rval, s32 level, s32 optname, const u8 optval[], s32 optlen );
    Result GetResolverInfo( s32* rval, nn::socket::DnsServerInfo* pDnsServerInfo );

    Result IcmpSocket( s32* rval, s32 af );
    Result IcmpPing( s32* rval, s32 s, const u8 data[], s32 len, u8 remote[], size_t salen, s32 timeout );
    Result IcmpCancel( s32* rval, s32 s );
    Result IcmpClose( s32* rval, s32 s );

}
}
}

#endif  // ifndef NN_SOCKET_SOCKET_IPCWRAPPER_H_
