/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_TYPES_H_
#define NN_SND_TYPES_H_

#include <nn/snd/CTR/Common/snd_Bcwav.h>

/* Please see man pages for details 
    
*/

#ifdef __cplusplus
#include <nn/os.h>
namespace nn { namespace snd { namespace CTR {

/* Please see man pages for details 
  
 */
typedef struct
{
    s16 n0;                             //
    s16 d1;                             //
} MonoFilterCoefficients;

/* Please see man pages for details 
  
 */
typedef struct
{
    s16 n0;                             //
    s16 n1;                             //
    s16 n2;                             //
    s16 d1;                             //
    s16 d2;                             //
} BiquadFilterCoefficients;

/* Please see man pages for details 
  
*/
typedef enum
{
    CHANNEL_INDEX_FRONT_LEFT  = 0,  //
    CHANNEL_INDEX_FRONT_RIGHT = 1,  //
    CHANNEL_INDEX_REAR_LEFT   = 2,  //
    CHANNEL_INDEX_REAR_RIGHT  = 3,  //
    CHANNEL_INDEX_NUM         = 4   //
}
ChannelIndex;

/* Please see man pages for details 
  
 */
typedef enum
{
    OUTPUT_MODE_MONO          = 0,  //
    OUTPUT_MODE_STEREO        = 1,  //
    OUTPUT_MODE_3DSURROUND    = 2   //
} OutputMode;

/* Please see man pages for details 
  
*/
typedef enum
{
    CLIPPING_MODE_NORMAL      = 0,  //
    CLIPPING_MODE_SOFT        = 1   //
} ClippingMode;

/* Please see man pages for details 
  
 */
typedef enum
{
    SURROUND_SPEAKER_POSITION_SQUARE = 0,  //
    SURROUND_SPEAKER_POSITION_WIDE   = 1,  //
    SURROUND_SPEAKER_POSITION_NUM
} SurroundSpeakerPosition;

/* Please see man pages for details 
  
*/
enum InterpolationType
{
    INTERPOLATION_TYPE_POLYPHASE, //
    INTERPOLATION_TYPE_LINEAR,    //
    INTERPOLATION_TYPE_NONE       //
};

/* Please see man pages for details 
  
*/
typedef enum
{
    FILTER_TYPE_NONE     = 0,       //
    FILTER_TYPE_MONOPOLE = 1,       //
    FILTER_TYPE_BIQUAD   = 2,       //
    FILTER_TYPE_BOTH     = 3        //
}
FilterType;

/* Please see man pages for details 
  
*/
typedef enum
{
    AUX_BUS_NULL = -1,

    AUX_BUS_A    =  0, //
    AUX_BUS_B    =  1, //
    AUX_BUS_NUM  =  2  //
}
AuxBusId;

/* Please see man pages for details 
    
*/
struct MixParam
{
    f32 mainBus[CHANNEL_INDEX_NUM];  //
    f32 auxBusA[CHANNEL_INDEX_NUM];  //
    f32 auxBusB[CHANNEL_INDEX_NUM];  //

    /* Please see man pages for details 
      
     */
    MixParam()
    {
        for (int i = 0; i < CHANNEL_INDEX_NUM; i++)
        {
            mainBus[i] = auxBusA[i] = auxBusB[i] = 0.0f;
        }
    }
}; // MixParam

/* Please see man pages for details 
    
*/
struct WaveBuffer
{
    /* Please see man pages for details 
      
    */
    enum Status
    {
        STATUS_FREE, //
        STATUS_WAIT, //
        STATUS_PLAY, //
        STATUS_DONE, //
        STATUS_TO_BE_DELETED  //
    };

    // For the user
    const void * bufferAddress;   //
    s32 sampleLength;             //

    const AdpcmContext * pAdpcmContext; //

    uptr userParam;               //

    bool loopFlag;                //
    util::SizedEnum1<Status> status;                //
    u16 bufferId;                 //

    struct WaveBuffer * next;     //
}; // WaveBuffer

/* Please see man pages for details 
  
*/
enum SampleFormat
{
    SAMPLE_FORMAT_PCM8  = Bcwav::ENCODING_PCM8,      //
    SAMPLE_FORMAT_PCM16 = Bcwav::ENCODING_PCM16,     //
    SAMPLE_FORMAT_ADPCM = Bcwav::ENCODING_DSP_ADPCM  //
};

static const s32 VOICE_PRIORITY_NODROP = 0x7fff; //

/* Please see man pages for details 
  
*/
typedef struct
{
    s32* frontLeft;  //
    s32* frontRight; //
    s32* rearLeft;   //
    s32* rearRight;  //
}
AuxBusData;

/* Please see man pages for details 
  
  
  
  
  
*/
typedef void(*AuxCallback)( AuxBusData* data, s32 sampleLength, uptr userData );

/* Please see man pages for details 
    
 */
struct ThreadParameter
{
    uptr   stackBuffer;                 //
    uptr   stackSize;                   //
    size_t priority;                    //
};

/* Please see man pages for details 
    
 */
enum SyncMode
{
    SYNC_MODE_STRICT = 0,
    SYNC_MODE_LOOSE = 1,
    SYNC_MODE_NUM = 2
};

}}} // namespace nn::snd::CTR

#endif // __cplusplus

// Below is the C declaration

typedef struct
{
    s16 n0;                             //
    s16 d1;                             //
} nnsndMonoFilterCoefficients;

/* Please see man pages for details 
  
 */
typedef struct
{
    s16 n0;                             //
    s16 n1;                             //
    s16 n2;                             //
    s16 d1;                             //
    s16 d2;                             //
} nnsndBiquadFilterCoefficients;

typedef enum
{
    NN_SND_FILTER_TYPE_NONE     = 0,    //
    NN_SND_FILTER_TYPE_MONOPOLE = 1,    //
    NN_SND_FILTER_TYPE_BIQUAD   = 2,    //
    NN_SND_FILTER_TYPE_BOTH     = 3     //
} nnsndFilterType;

typedef enum
{
    NN_SND_AUX_BUS_A   = 0, //
    NN_SND_AUX_BUS_B   = 1, //
    NN_SND_AUX_BUS_NUM = 2  //
} nnsndAuxBusId;

typedef enum nnsndSampleFormat
{
    NN_SND_SAMPLE_FORMAT_PCM8  = NN_SND_BCWAV_ENCODING_PCM8,      //
    NN_SND_SAMPLE_FORMAT_PCM16 = NN_SND_BCWAV_ENCODING_PCM16,     //
    NN_SND_SAMPLE_FORMAT_ADPCM = NN_SND_BCWAV_ENCODING_DSP_ADPCM  //
} nnsndSampleFormat;

typedef enum nnsndChannelIndex
{
    NN_SND_CHANNEL_INDEX_FRONT_LEFT  = 0,  //
    NN_SND_CHANNEL_INDEX_FRONT_RIGHT = 1,  //
    NN_SND_CHANNEL_INDEX_REAR_LEFT   = 2,  //
    NN_SND_CHANNEL_INDEX_REAR_RIGHT  = 3,  //
    NN_SND_CHANNEL_INDEX_NUM         = 4   //
} nnsndChannelIndex;

typedef enum nnsndOutputMode
{
    NN_SND_OUTPUT_MODE_MONO          = 0,  //
    NN_SND_OUTPUT_MODE_STEREO        = 1,  //
    NN_SND_OUTPUT_MODE_3DSURROUND    = 2   //
} nnsndOutputMode;

typedef enum
{
    NN_SND_CLIPPING_MODE_NORMAL      = 0,  //
    NN_SND_CLIPPING_MODE_SOFT        = 1   //
} nnsndClippingMode;

typedef enum nnsndSurroundSpeakerPosition
{
    NN_SND_SURROUND_SPEAKER_POSITION_SQUARE = 0,  //
    NN_SND_SURROUND_SPEAKER_POSITION_WIDE   = 1   //
} nnsndSurroundSpeakerPosition;

typedef enum nnsndSyncMode
{
    NN_SND_SYNC_MODE_STRICT = 0,
    NN_SND_SYNC_MODE_LOOSE = 1,
    NN_SND_SYNC_MODE_NUM = 2
} nnsndSyncMode;

#endif //NN_SND_TYPES_H_
