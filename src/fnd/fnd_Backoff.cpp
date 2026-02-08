/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Backoff.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/fnd/fnd_Backoff.h>

namespace nn { namespace fnd {

void
BackOffManager::BackOffImpl()
{
    // TODO: This implementation should be reviewed
    // It may be better also to have dependency core number
    u32 spinCount = m_order << (m_count - 1);
    
    // TODO: If there is a generic SpinWait, use it
    volatile int n;
    for (u32 i = 0; i < spinCount; ++i)
    {
        n = 0;
    }
}

} }

