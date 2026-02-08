/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Enum.h

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

#ifndef NN_DBG_DBG_ENUM_H_
#define NN_DBG_DBG_ENUM_H_


typedef enum nndbgBreakReason
{
    NN_DBG_BREAK_REASON_PANIC,
    NN_DBG_BREAK_REASON_ASSERT,
    NN_DBG_BREAK_REASON_USER,

    NN_DBG_BREAK_REASON_MAX_BIT = (1u << 30)
}
nndbgBreakReason;

//-------------------------------------------------------------------
// for C / C++

#ifdef __cplusplus

namespace nn { namespace dbg {

    /* Please see man pages for details 
        
        
    
*/
    enum BreakReason
    {
        BREAK_REASON_PANIC,     //
        BREAK_REASON_ASSERT,    //
        BREAK_REASON_USER,       //
        BREAK_REASON_LOAD_RO,
        BREAK_REASON_UNLOAD_RO,

        BREAK_REASON_MAX_BIT = (1u << 31)
    };

    enum PerformanceCounterOperation
    {
        PERFORMANCE_COUNTER_OPERATION_ACQUIRE_CONTROL,
        PERFORMANCE_COUNTER_OPERATION_RELEASE_CONTROL,
        PERFORMANCE_COUNTER_OPERATION_GET_VALUE,
        PERFORMANCE_COUNTER_OPERATION_SET_VALUE,
        PERFORMANCE_COUNTER_OPERATION_GET_OVERFLOW,
        PERFORMANCE_COUNTER_OPERATION_RESET,
        PERFORMANCE_COUNTER_OPERATION_GET_EVENT,
        PERFORMANCE_COUNTER_OPERATION_SET_EVENT,
        PERFORMANCE_COUNTER_OPERATION_USE_VIRTUAL_COUNTER,

        PERFORMANCE_COUNTER_OPERATION_MAX_BIT = (1u << 31)
    };
}}

#endif  // ifdef __cplusplus

#endif /* NN_DBG_DBG_ENUM_H_ */
