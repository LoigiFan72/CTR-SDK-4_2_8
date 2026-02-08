/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     midi_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIDI_MIDI_RESULT_H_
#define NN_MIDI_MIDI_RESULT_H_

#ifdef __cplusplus

#include <nn/Result.h>

namespace nn {
namespace midi {

enum Description
{
    DESCRIPTION_ALREADY_OPENED = 1,
    DESCRIPTION_NOT_OPENED,
    DESCRIPTION_BUFFER_OVERFLOW,
    DESCRIPTION_DEVICE_FIFO_FULL,
    DESCRIPTION_DEVICE_FRAME_ERROR,
    DESCRIPTION_DEVICE_INVALID_DATA_LENGTH,
    DESCRIPTION_UNKNOWN_DEVICE
};

NN_DEFINE_RESULT_FUNC_LM(MakeUsageResult, Result::LEVEL_USAGE, Result::MODULE_NN_MIDI);
NN_DEFINE_RESULT_FUNC_LSM(MakeDeviceFatalResult, Result::LEVEL_FATAL, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_MIDI);

NN_DEFINE_RESULT_CONST(
    ResultNotImplemented,
    Result::LEVEL_FATAL, Result::SUMMARY_NOT_SUPPORTED, Result::MODULE_NN_MIDI, nn::Result::DESCRIPTION_NOT_IMPLEMENTED
);

NN_DEFINE_RESULT_CONST_LM(
    ResultAlreadyOpened,
    MakeUsageResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_ALREADY_OPENED
);

NN_DEFINE_RESULT_CONST_LM(
    ResultNotOpened,
    MakeUsageResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_NOT_OPENED
);

NN_DEFINE_RESULT_CONST_LM(
    ResultBufferOverflow,
    MakeUsageResult, Result::SUMMARY_INVALID_STATE, DESCRIPTION_BUFFER_OVERFLOW
);

NN_DEFINE_RESULT_CONST_LSM(
    ResultDeviceFifoFull,
    MakeDeviceFatalResult, DESCRIPTION_DEVICE_FIFO_FULL
);

NN_DEFINE_RESULT_CONST_LSM(
    ResultDeviceFrameError,
    MakeDeviceFatalResult, DESCRIPTION_DEVICE_FRAME_ERROR
);

NN_DEFINE_RESULT_CONST_LSM(
    ResultDeviceInvalidDataLength,
    MakeDeviceFatalResult, DESCRIPTION_DEVICE_INVALID_DATA_LENGTH
);

NN_DEFINE_RESULT_CONST_LSM(
    ResultUnknownDevice,
    MakeDeviceFatalResult, DESCRIPTION_UNKNOWN_DEVICE
);

} // end of namespace fs
} // end of namespace nn

#endif // #ifdef __cplusplus
#endif // #ifndef NN_MIDI_MIDI_RESULT_H_
