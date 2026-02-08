/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_Utility.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47707 $
 *---------------------------------------------------------------------------*/

#include <nn/cx.h>
#include "cx_Utility.h"
#include <zlib.h>

namespace nn {
namespace cx {
namespace detail {


    s32 ConvertZlibReturnCode(int zlibReturnCode)
    {
        switch( zlibReturnCode )
        {
        case Z_OK:              return ERROR_CODE_SUCCESS;
        case Z_STREAM_END:      return ERROR_CODE_SUCCESS;
        case Z_NEED_DICT:       return ERROR_CODE_UNSUPPORTED;
        case Z_ERRNO:           return ERROR_CODE_UNSUPPORTED;
        case Z_STREAM_ERROR:    return ERROR_CODE_BUFFER_OVERRUN;
        case Z_DATA_ERROR:      return ERROR_CODE_UNSUPPORTED;
        case Z_MEM_ERROR:       return ERROR_CODE_BUFFER_OVERRUN;
        case Z_BUF_ERROR:       return ERROR_CODE_DATA_SHORTAGE;
        case Z_VERSION_ERROR:   return ERROR_CODE_UNSUPPORTED;
        }
        return ERROR_CODE_UNSUPPORTED;
    }



}}}
