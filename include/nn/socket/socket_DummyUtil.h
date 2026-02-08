/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_DummyUtil.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_DUMMYUTIL_H_
#define NN_SOCKET_SOCKET_DUMMYUTIL_H_

#include <nn/ac.h>
#include <nn/socket/socket_Types.h>

namespace nn {
namespace socket {
namespace dummy_util {

    // No Security / DHCP
    Result InitializeNetwork(const char* ssid) NN_ATTRIBUTE_DEPRECATED;
    Result InitializeNetwork(const u8* ssid, size_t ssidLength) NN_ATTRIBUTE_DEPRECATED;

    // DHCP
    Result InitializeNetwork(const char* ssid, ac::SecurityMode security, const u8 key[64]) NN_ATTRIBUTE_DEPRECATED;
    Result InitializeNetwork(const u8* ssid, size_t ssidLength, ac::SecurityMode security, const u8 key[64]) NN_ATTRIBUTE_DEPRECATED;

    Result FinalizeNetwork(void) NN_ATTRIBUTE_DEPRECATED;

} // end of namespace dummy_util
} // end of namespace socket
} // end of namespace nn

#endif // NN_SOCKET_SOCKET_DUMMYUTIL_H_
