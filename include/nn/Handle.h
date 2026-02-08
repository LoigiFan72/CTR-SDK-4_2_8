/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     Handle.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47231 $
 *---------------------------------------------------------------------------*/


#ifndef NN_HANDLE_H_
#define NN_HANDLE_H_

#include <nn/types.h>
#include <nn/Result.h>


//-------------------------------------------------------------------
// for C / C++

#ifdef __cplusplus
extern "C" {
#endif  // ifdef __cplusplus

    typedef struct nnHandle
    {
        bit32   value;
    }
    nnHandle;

    extern const nnHandle NN_INVALID_HANDLE_VALUE;

#ifdef __cplusplus
}
#endif  // ifdef __cplusplus



//-------------------------------------------------------------------
// for C++

#ifdef __cplusplus

namespace nn
{

    class Handle
    {
    public:
        Handle() : m_Handle(0)
        {
        }

        Handle(nnHandle handle) : m_Handle(handle.value)
        {
        }

        explicit Handle(bit32 handle)
        {
            m_Handle = handle;
        }

        bool IsValid() const
        {
            return m_Handle != 0;
        }

    #if ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT) || ! defined(NN_SWITCH_DISABLE_DEBUG_PRINT_FOR_SDK)
        bit32 GetPrintableBits() const
        {
            return m_Handle;
        }
    #endif

        bool operator ==(const Handle& rhs) const { return this->m_Handle == rhs.m_Handle; }
        bool operator !=(const Handle& rhs) const { return this->m_Handle != rhs.m_Handle; }
        operator nnHandle() const { nnHandle handle = {this->m_Handle}; return handle; }

    private:
        bit32 m_Handle;
    };

    namespace
    {
        const nnHandle PSEUDO_HANDLE_CURRENT_THREAD  = {0xFFFF8000};
        const nnHandle PSEUDO_HANDLE_CURRENT_PROCESS = {0xFFFF8001};
        const nnHandle INVALID_HANDLE_VALUE = {0};
    }

}
#endif  // ifdef __cplusplus



#endif /* NN_HANDLE_H_ */
