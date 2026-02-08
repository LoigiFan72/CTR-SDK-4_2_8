/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dsp_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DSP_CTR_DSP_TYPES_H_
#define NN_DSP_CTR_DSP_TYPES_H_

#ifndef CTR_DSP
/*---------------------------------------------------------------------------*
 * includes
 *---------------------------------------------------------------------------*/
#include <nn/types.h>

/*---------------------------------------------------------------------------*
 * namespaces
 *---------------------------------------------------------------------------*/
namespace nn {
namespace dsp {
namespace CTR {
#else
#include <dsp/types.h>
#endif // CTR_DSP

/*---------------------------------------------------------------------------*/
/* Declarations */

// Type definitions to use when sharing data during inter-processor communication.
typedef u16 DSPAddr;        // This type expresses an address in the DSP (2 bytes, 1 word)
typedef u16 DSPWord;        // This type expresses a size in the DSP (2 bytes, 1 word)
typedef u16 DSPByte;        // This type expresses a single-byte unit in the DSP (1 byte, 1 word)
typedef u32 DSPWord32;      // This type expresses a size in the DSP (2 bytes, 1 word)
typedef u32 DSPByte32;      // This type expresses a single-byte unit in the DSP (1 byte, 1 word)
typedef u32 DSPAddrInARM;   // This type has converted DSP addresses into bytes

// Explicit Type-Conversion Macros
#define NN_DSP_ADDR_TO_ARM(address)    (u32)((address) << 1)
#define NN_DSP_ADDR_TO_DSP(address)    (u16)((u32)(address) >> 1)
#define NN_DSP_WORD_TO_ARM(word)       (u16)((word) << 1)
#define NN_DSP_WORD_TO_DSP(word)       (u16)((word) >> 1)
#define NN_DSP_WORD_TO_ARM32(word)     (u32)((word) << 1)
#define NN_DSP_WORD_TO_DSP32(word)     (u32)((word) >> 1)
#define NN_DSP_32BIT_TO_ARM(value)     (u32)(((u32)(value) >> 16) | ((u32)(value) << 16))
#define NN_DSP_32BIT_TO_DSP(value)     (u32)(((u32)(value) >> 16) | ((u32)(value) << 16))
#ifdef NN_SYSTEM_PROCESS
#define NN_DSP_BYTE_TO_UNIT(byte)      (u16)(byte)
#define NN_DSP_UNIT_TO_BYTE(unit)      (u16)(unit)
#else
#define NN_DSP_BYTE_TO_UNIT(byte)      (u16)((byte) >> 1)
#define NN_DSP_UNIT_TO_BYTE(unit)      (u16)((unit) << 1)
#endif // #ifdef NN_SYSTEM_PROCESS

// The native size for sizeof(char) (this is 2 on the DSP and 1 on an ARM processor)
#define NN_DSP_WORD_UNIT       (3 - sizeof(DSPWord))

#ifndef CTR_DSP
} // namespace CTR {
} // namespace dsp {
} // namespace nn {
#endif // CTR_DSP

#endif  // ifndef NN_DSP_CTR_DSP_TYPES_H_
