/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_CpuControl.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_OS_CPUCONTROL_H_
#define NN_OS_OS_CPUCONTROL_H_

#include <nn/types.h>

#ifdef __cplusplus
namespace nn { namespace os { namespace CTR {

    /*
      

                    

                    
                                    

      

     */
    Result SetApplicationCpuTimeLimit(s32 limitPercent);

    /*
      

                    

      
                    

     */
    s32 GetApplicationCpuTimeLimit();

}}}
#endif


#endif  // ifndef NN_OS_OS_CPUCONTROL_H_
