/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Const.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_CTR_COMMON_SND_CONST_H_
#define NN_SND_CTR_COMMON_SND_CONST_H_

// Clock
#define NN_SND_HW_BASE_CLOCK                (16756991)
#define NN_SND_HW_SYSTEM_CLOCK              (NN_SND_HW_BASE_CLOCK * 16)
#define NN_SND_HW_I2S_MCLK_32KH             (NN_SND_HW_SYSTEM_CLOCK /  32)
#define NN_SND_HW_I2S_CLOCK_32KHZ           (NN_SND_HW_SYSTEM_CLOCK / (32 * 256))
#define NN_SND_HW_I2S_MCLK_48KH             (NN_SND_HW_SYSTEM_CLOCK /  22)
#define NN_SND_HW_I2S_CLOCK_48KHZ           (NN_SND_HW_SYSTEM_CLOCK / (22 * 256))

#define NN_SND_HW_BASE_CLOCK_F32            (16756991.0)
#define NN_SND_HW_SYSTEM_CLOCK_F32          (NN_SND_HW_BASE_CLOCK * 16)
#define NN_SND_HW_I2S_MCLK_32KH_F32         (NN_SND_HW_SYSTEM_CLOCK /  32)
#define NN_SND_HW_I2S_CLOCK_32KHZ_F32       (NN_SND_HW_SYSTEM_CLOCK / (32 * 256))
#define NN_SND_HW_I2S_MCLK_48KH_F32         (NN_SND_HW_SYSTEM_CLOCK /  22)
#define NN_SND_HW_I2S_CLOCK_48KHZ_F32       (NN_SND_HW_SYSTEM_CLOCK / (22 * 256))

// Buffer length
#define NN_SND_BTDMP_OUTPUT_FRAME_TRIG_FREQ (20)
#define NN_SND_BTDMP_OUTPUT_FIFO_SIZE       (16)
#define NN_SND_OUTPUT_RINGBUF_LOADUNIT      (NN_SND_BTDMP_OUTPUT_FIFO_SIZE * NN_SND_BTDMP_OUTPUT_FRAME_TRIG_FREQ)

// Data samples per frame
#define NN_SND_SAMPLES_PER_FRAME            (NN_SND_OUTPUT_RINGBUF_LOADUNIT / 2)
#define NN_SND_USECS_PER_FRAME              ((NN_SND_SAMPLES_PER_FRAME * 1000000) / NN_SND_HW_I2S_CLOCK_32KHZ)

// Upper limit of voice
#define NN_SND_VOICE_NUM                    (24)

// Number of buffer jumps that can be executed in one frame
#define NN_SND_NEXT_BUFFER_NUM              (4)

// Monaural/stereo
#define NN_SND_PCM_ACOUS_MONAURAL           (1)
#define NN_SND_PCM_ACOUS_STEREO             (2)

// Playback argument related
#define NN_SND_VOLUME_EQUIV                 ((u16)0x1 << NN_SND_VOLUME_SHIFT)
#define NN_SND_VOLUME_DEFAULT               NN_SND_VOLUME_EQUIV
#define NN_SND_VOLUME_MAX                   (0xffff)
#define NN_SND_VOLUME_MIN                   (0x0000)
#define NN_SND_VOLUME_SHIFT                 (15)

#define NN_SND_TIMER_EQUIV                  ((u32)1 << NN_SND_TIMER_SHIFT)
#define NN_SND_TIMER_DEFAULT                NN_SND_TIMER_EQUIV
#define NN_SND_TIMER_MAX                    (0xffffffff)
#define NN_SND_TIMER_MIN                    (0x00000010)
#define NN_SND_TIMER_SHIFT                  (24)

// Sound depth
#define NN_SND_SURROUND_DEPTH_MIN           (0.0f)
#define NN_SND_SURROUND_DEPTH_MAX           (1.0f)

// The following is for debugging
#define NN_SND_DEBUG_3DS_SPEAKER            (0)
#define NN_SND_DEBUG_3DS_HEADPHONE          (1)

#endif // NN_SND_CTR_COMMON_SND_CONST_H_
