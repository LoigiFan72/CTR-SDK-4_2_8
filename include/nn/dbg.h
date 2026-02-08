/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47344 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DBG_H_
#define NN_DBG_H_

/* Please see man pages for details 
  
  
*/

#include <nn/dbg/dbg_Break.h>
#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Logger.h>
#include <nn/dbg/dbg_PrintResult.h>

/* Please see man pages for details 
  
  
*/

#include <nn/dbg/dbg_Instrument.h>
#include <nn/dbg/dbg_Argument.h>

#if defined(NN_PLATFORM_CTR)
    #if defined(NN_SYSTEM_PROCESS)
        #if defined(NN_PROCESSOR_ARM_V6)
            #if ! defined(NN_HARDWARE_CTR_LEGACY)
                #include <nn/dbg/CTR/dbg_DirectPrint.h>
                #include <nn/dbg/CTR/dbg_ExceptionScreen.h>
            #endif
        #endif
    #endif

    #ifdef __cplusplus
        namespace nn { namespace dbg {
            using namespace ::nn::dbg::CTR;
        }}
    #endif
#else
    #error no platform selected
#endif


/* Please see man pages for details 
    
    
    
*/

/*  

*/

#endif /* NN_DBG_H_ */
