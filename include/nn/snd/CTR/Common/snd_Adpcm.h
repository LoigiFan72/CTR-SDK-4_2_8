/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Adpcm.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_ADPCM_H_
#define NN_SND_ADPCM_H_

#if !defined(_I386)
#include <nn/dsp/CTR/Common/dsp_Types.h>
#endif // #if !defined(_I386))

#ifndef CTR_DSP
namespace nn  { namespace snd { namespace CTR {
#endif // CTR_DSP

#define NN_SND_ADPCM_DOL_PS_SIZE_IN_NIB    (2)
#define NN_SND_ADPCM_DOL_DATA_NUM_IN_BLOCK (14)
#define NN_SND_ADPCM_DOL_NIBL_NUM_IN_BLOCK (16)

// Constants that depend on the operating environment.
#ifdef NN_PROCESSOR_ARM11MPCORE
#define NN_SND_ADPCM_DOL_BLOCK_SIZE   (8) //
#else  // #ifdef NN_PROCESSOR_ARM11MPCORE
#define NN_SND_ADPCM_DOL_BLOCK_SIZE   (4) //
#endif // #ifdef NN_PROCESSOR_ARM11MPCORE

typedef struct
{
    s16 a[8][2];

    u16 gain;
    u16 pred_scale;
    s16 yn1;
    s16 yn2;

    // Loop context
    u16 loop_pred_scale;
    s16 loop_yn1;
    s16 loop_yn2;

    u16 pad[1];
} DspsndAdpcmState;

typedef struct
{
    u32 num_samples;
    u32 num_adpcm_nibbles;
    u32 sample_rate;

    u16 loop_flag;
    u16 format;
    u32 sa;     // loop start address
    u32 ea;     // loop end address
    u32 ca;     // current address

    DspsndAdpcmState state;

    u16 pad[10];

} DspsndAdpcmHeader;

/* Please see man pages for details 
    
*/
struct AdpcmParam
{
    u16 coef[16]; //
}; // AdpcmParam


/* Please see man pages for details 
    
*/
struct AdpcmContext
{
    u16 pred_scale; //
    s16 yn1;        //
    s16 yn2;        //
};

#ifndef CTR_DSP
}}} // namespace nn::snd::CTR
#endif // CTR_DSP

#endif // #ifndef NN_SND_ADPCM_H_
