/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     svc_Inlines.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SVC_SVC_INLINES_H_
#define NN_SVC_SVC_INLINES_H_

#include <nn/types.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/svc/svc_Stub.h>
#include <nn/os/os_SvcTypes.autogen.h>



#ifdef __cplusplus

namespace nn {
namespace svc {

    inline Result CreateEvent(Handle* pOut, bool isManualReset)
    {
        const os::ResetType rt = (isManualReset ? os::RESET_TYPE_STICKY: os::RESET_TYPE_ONESHOT);
        return CreateEvent(pOut, rt);
    }
    inline Result CreateTimer(Handle* pOut, bool isManualReset)
    {
        const os::ResetType rt = (isManualReset ? os::RESET_TYPE_STICKY: os::RESET_TYPE_ONESHOT);
        return CreateTimer(pOut, rt);
    }
    inline Result WaitSynchronization(s32* pOut, Handle handles[], s32 numHandles, bool waitAll, s64 timeout)
    {
//        if( numHandles == 1 )
//        {
//            *pOut = 0;
//            return WaitSynchronization1(handles[0], timeout);
//        }
//        else
//        {
            return WaitSynchronizationN(pOut, handles, numHandles, waitAll, timeout);
//        }
    }

} // end of namespace svc
} // end of namespace nn

#endif  // ifdef __cplusplus




#endif  // ifndef NN_SVC_SVC_INLINES_H_
