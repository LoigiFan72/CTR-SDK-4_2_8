/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Macros.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47344 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_MACROS_H_
#define NN_UTIL_UTIL_MACROS_H_

#include <nn/dbg/dbg_SmallSet.h>

#define NN_UTIL_LOG_POS     NN_LOG("%3d %s\n", __LINE__, NN_FILE_NAME);
#define NN_UTIL_TLOG_POS_   NN_TLOG_("%3d %s\n", __LINE__, NN_FILE_NAME);


#endif // ifndef NN_UTIL_UTIL_MACROS_H_
