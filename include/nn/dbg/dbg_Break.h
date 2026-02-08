/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Break.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48011 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_DBG_DBG_BREAK_H_
#define NN_DBG_DBG_BREAK_H_

#include <nn/Result.h>
#include <nn/types.h>
#include <nn/dbg/dbg_Enum.h>

//-------------------------------------------------------------------
// for C / C++

#ifdef __cplusplus
extern "C" {
#endif  // ifdef __cplusplus

/* Please see man pages for details 
    
*/
nnResult nndbgBreak(int reason);

/* Please see man pages for details 
    
*/
void nndbgPanic(void);


void nndbgBreakWithMessage_ (nndbgBreakReason reason, const char* filename, int lineno, const char* fmt, ...);
void nndbgBreakWithTMessage_(nndbgBreakReason reason, const char* filename, int lineno, const char* fmt, ...);

void nndbgBreakWithResultMessage_ (nndbgBreakReason reason, nnResult result, const char* filename, int lineno, const char* fmt, ...);
void nndbgBreakWithResultTMessage_(nndbgBreakReason reason, nnResult result, const char* filename, int lineno, const char* fmt, ...);

#ifdef __cplusplus
}
#endif  // ifdef __cplusplus



//-------------------------------------------------------------------
// for C++

#ifdef __cplusplus

namespace nn { namespace dbg {

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    typedef void (*BreakHandler)(BreakReason reason, Result* pResult,
                const char* filename, int lineno, const char* fmt, std::va_list args);

    nn::Result Break(nn::dbg::BreakReason reason);

    /* Please see man pages for details 
        
        
                

        
    */
    inline nn::Result Break()
    {
        return Break(BREAK_REASON_PANIC);
    }

    /* Please see man pages for details 
        
        
                
    */
    void Panic();

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    void SetBreakHandler(BreakHandler handler);


    namespace detail
    {
        namespace CTR
        {
            struct DllInfo
            {
                uptr    pathAddress;
                s32     pathLength;
                uptr    erAddress;
                uptr    rwAddress;
            };
        }

        Result NotifyDllLoadedToDebugger(const void* pDllInfo, size_t size);
        Result NotifyDllUnloadingToDebugger(const void* pDllInfo, size_t size);
    }
}}

#endif  // ifdef __cplusplus



#endif /* NN_DBG_DBG_BREAK_H_ */
