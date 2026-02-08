/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Admin.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_ADMIN_H_
#define NN_SOCKET_SOCKET_ADMIN_H_

#include <nn/types.h>
#include <nn/socket/socket_Types.h>

   
#define NN_SOCKET_NO_DEPEND_HEADER 1

#pragma push
#pragma diag_suppress 1301,2530
#include <nn/socket/socket_Admin.autogen.h>
#pragma diag_default 1301,2530
#pragma pop

#undef NN_SOCKET_NO_DEPEND_HEADER

#endif  // ifndef NN_SOCKET_SOCKET_ADMIN_H_
