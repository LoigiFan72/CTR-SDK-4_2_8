/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Dump.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_DBG_DBG_DUMP_H_
#define NN_DBG_DBG_DUMP_H_

#include <nn/types.h>
#include <nn/dbg/dbg_DebugString.h>
#include <nn/config.h>

#define NN_DBG_DUMP_FLAG_POINTER         1
#define NN_DBG_DUMP_FLAG_STRING          2

/* Please see man pages for details 
    
    
    
    

    
*/
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
    #ifdef __cplusplus
        #define NN_DUMP_MEMORY( p, size, flags )    nn::dbg::detail::DumpMemory(p, size, flags)
    #else   // ifdef __cplusplus
        #define NN_DUMP_MEMORY( p, size, flags )    nndbgDetailDumpMemory(p, size, flags)
    #endif  // ifdef __cplusplus else
#else   // ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
    #define NN_DUMP_MEMORY( p, size, flags )        ((void)0)
#endif  // ifndef NN_SWITCH_DISABLE_DEBUG_PRINT else

#define NN_DUMP( p, size )                  NN_DUMP_MEMORY(p, size, 0)
#define NN_DUMP_POINTER( p, size )          NN_DUMP_MEMORY(p, size, NN_DBG_DUMP_FLAG_POINTER)
#define NN_DUMP_STRING( p, size )           NN_DUMP_MEMORY(p, size, NN_DBG_DUMP_FLAG_POINTER|NN_DBG_DUMP_FLAG_STRING)

#ifdef __cplusplus

namespace nn {
namespace dbg {
namespace detail {

    void DumpMemory(const void* p, size_t size, bit32 flags);
}
}
}


#endif // __cplusplus

//-------------------------------------------------------------------
// for C / C++

#include <nn/util/detail/util_CLibImpl.h>

NN_EXTERN_C void nndbgDetailDumpMemory(const void* p, size_t size, bit32 flags);

#endif
