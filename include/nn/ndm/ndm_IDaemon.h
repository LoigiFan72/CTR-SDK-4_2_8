/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ndm_IDaemon.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NDM_IDAEMON_H_
#define NN_NDM_IDAEMON_H_

#include <nn/types.h>
#include <nn/os/os_Event.h>


#ifdef __cplusplus

namespace nn{
namespace ndm{

class IDaemon
{
public:
    enum Status
    {
        STATUS_WORKING,
        STATUS_IDLE,
        STATUS_SUSPENDING,
        STATUS_SUSPENDED
    };

    virtual Result Attach(nn::os::Event& event) = 0;
    virtual Result Detach(void) = 0;

    // Permit daemon to run.
    // The daemon permitted to run can start to use network functionality, such as wireless.
    virtual Result Resume(void) = 0;
    
    // Halt the daemon.
    // If daemon receives a request, it enters the STATUS_SUSPENDING state before returning the process.
    // When communication has completely terminated, enters STATUS_SUSPENDED state.
    virtual Result SuspendAsync(bool bImmediate) = 0;

    virtual Result QueryStatus(Status& status) = 0;

    virtual Result QueryIsHalfAwakeTriggered(bool& bTriggered)
    {
        bTriggered = false;
        return ResultSuccess();
    }
};

}
}

#endif // __cplusplus

#endif // NN_NDM_IDAEMON_H_
