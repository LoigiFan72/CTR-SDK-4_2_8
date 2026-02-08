/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_MemoryTypes.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/*!
    @file

    :include nn/os.h
 */
#ifndef NN_OS_OS_MEMORYTYPES_H_
#define NN_OS_OS_MEMORYTYPES_H_

#include <nn/types.h>

#ifdef __cplusplus

namespace nn { namespace os {

enum MemoryState
{
    MEMORY_STATE_FREE,
    MEMORY_STATE_RESERVED,
    MEMORY_STATE_IO,
    MEMORY_STATE_STATIC,
    MEMORY_STATE_CODE,
    MEMORY_STATE_PRIVATE,
    MEMORY_STATE_SHARED,
    MEMORY_STATE_CONTINUOUS,
    MEMORY_STATE_ALIASED,
    MEMORY_STATE_ALIAS,
    MEMORY_STATE_ALIAS_CODE,
    MEMORY_STATE_LOCKED,

    MEMORY_STATE_MAX_BITS   = (1u << 31)
};

enum PageFlag
{
    MEMORY_FLAG_LOCKED           = (1u << 0),
    MEMORY_FLAG_STATE_CHANGED    = (1u << 1)
};

const int ALLOCATE_OPTION_LINEAR = 0x1u << 8;

enum MemoryOperation
{
    MEMORY_OPERATION_FREE           = (1 << 0),
    MEMORY_OPERATION_RESERVE        = (2 << 0),
    MEMORY_OPERATION_COMMIT         = (3 << 0),
    MEMORY_OPERATION_MAP            = (4 << 0),
    MEMORY_OPERATION_UNMAP          = (5 << 0),
    MEMORY_OPERATION_PROTECT        = (6 << 0),

    MEMORY_OPERATION_REGION_APP     = (1 << 8),
    MEMORY_OPERATION_REGION_SYSTEM  = (2 << 8),
    MEMORY_OPERATION_REGION_BASE    = (3 << 8),

    MEMORY_OPERATION_MASK           = (0xFFu <<  0),
    MEMORY_OPERATION_REGION_MASK    = (0xFu  <<  8),
    MEMORY_OPERATION_FLAG_LINEAR    = (0x1u  << 16),

    MEMORY_OPERATION_MAX_BITS       = (1u << 31)
};

enum MemoryPermission
{
    MEMORY_PERMISSION_NONE          = 0,
    MEMORY_PERMISSION_READ          = (1u <<  0),
    MEMORY_PERMISSION_WRITE         = (1u <<  1),
    MEMORY_PERMISSION_READ_WRITE    = (MEMORY_PERMISSION_READ | MEMORY_PERMISSION_WRITE),

    MEMORY_PERMISSION_DONT_CARE     = (1u << 28),
    MEMORY_PERMISSION_MAX_BITS      = (1u << 31)
};

}}

#endif // __cplusplus

#endif /* NN_OS_OS_MEMORYTYPES_H_ */
