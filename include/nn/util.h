/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47508 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_UTIL_H_
#define NN_UTIL_H_

#if defined(NN_PLATFORM_CTR)
    #include <nn/util/util_Base64.h>
    #include <nn/util/util_Crc.h>
    #include <nn/util/util_Macros.h>
    #include <nn/util/util_Misc.h>
    #include <nn/util/util_NonCopyable.h>
    #include <nn/util/util_Result.h>
    #include <nn/util/util_Singleton.h>
    #include <nn/util/util_SizedEnum.h>
    #include <nn/util/detail/util_Symbol.h>
    #include <nn/dbg/dbg_Logger.h>

    #if defined(NN_PROCESSOR_ARM_V6)
        #ifdef NN_SYSTEM_PROCESS
            #include <nn/util/util_Color.h>
        #endif
    #endif

/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
    
    
*/

/*  

*/

#else
    #error no platform selected
#endif

#endif /* NN_UTIL_H_ */
