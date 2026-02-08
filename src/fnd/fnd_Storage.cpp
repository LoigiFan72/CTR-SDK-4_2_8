/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Storage.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <cstring>
#include <nn/fnd/fnd_Storage.h>

namespace nn { namespace fnd {

Result MemoryStorageReader::TryRead(size_t* pOut, void* buffer, size_t size)
{
    size_t& ret = *pOut;
    if (m_Size - m_Position < size)
    {
        ret = m_Size - m_Position;
    }
    else
    {
        ret = size;
    }
    NN_ASSERT(m_Position + ret <= m_Size);
    std::memcpy(buffer, m_Buffer + m_Position, ret);
    m_Position += ret;
    return ResultSuccess();
}

Result MemoryStorageWriter::TryWrite(size_t* pOut, const void* buffer, size_t size)
{
    size_t& ret = *pOut;
    if (m_Size - m_Position < size)
    {
        ret = m_Size - m_Position;
    }
    else
    {
        ret = size;
    }
    NN_ASSERT(m_Position + ret <= m_Size);
    std::memcpy(m_Buffer + m_Position, buffer, ret);
    m_Position += ret;
    return ResultSuccess();
}

}}
