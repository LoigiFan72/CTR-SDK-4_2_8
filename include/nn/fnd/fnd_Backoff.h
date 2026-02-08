/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Backoff.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_FND_BACKOFF_H_
#define NN_FND_FND_BACKOFF_H_

#ifdef __cplusplus

#include <nn/types.h>

namespace nn { namespace fnd {

class BackOffManager
{
private:
    const u32 m_order;
    u32 m_count;
    void BackOffImpl();

public:
    BackOffManager(u32 order) : m_order(order), m_count(0) {}

    void BackOff()
    {
        // The first contention (m_count == 0) is likely to be the result of thread switching, and not contention between cores. Passes without backing off.
        // 
        // 
        if (m_count++ > 0)
        {
            BackOffImpl();
        }
    }
};

}}

#endif // __cplusplus

#endif  // NN_FND_FND_BACKOFF_H_
