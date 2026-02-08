/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_CTR_MPCORE_SND_API_H_
#define NN_SND_CTR_MPCORE_SND_API_H_

#include <nn/Result.h>
#include <nn/snd/CTR/Common/snd_Types.h>
#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/snd/CTR/MPCore/snd_OutputCapture.h>
#include <nn/snd/CTR/MPCore/snd_FxDelay.h>
#include <nn/snd/CTR/MPCore/snd_FxReverb.h>

#ifdef __cplusplus

/* Please see man pages for details 
    
*/

namespace nn  { namespace snd { namespace CTR {

/* Please see man pages for details 
    
*/
static const s32 NN_SND_DSP_MAXIMUM_CYCLES = 622535;


/* Please see man pages for details 
  
  
*/
/* Please see man pages for details 
    

    
    
    
    
*/
nn::Result Initialize();

/* Please see man pages for details 
    

    
    
*/
nn::Result Finalize();

/* Please see man pages for details 
    

                

    
*/
void InitializeWaveBuffer(WaveBuffer * pWaveBuffer);

/* Please see man pages for details 
    
 */
nn::Result StartSoundThread(
    void (*callback)(uptr),
    uptr arg,
    uptr stackBuffer,
    size_t stackSize,
    s32 prio,
    s32 coreNo = NN_OS_CORE_NO_USE_PROCESS_VALUE
);

/* Please see man pages for details 
    
 */
nn::Result StartUserSoundThread(uptr stackBuffer, size_t stackSize, s32 prio);

/* Please see man pages for details 
    
 */
nn::Result StartSoundThread(
    const ThreadParameter* mainThreadParam,
    void                   (*mainThreadCallback)(uptr),
    uptr                   mainThreadArg,
    const ThreadParameter* userThreadParam,
    void                   (*userThreadCallback)(uptr),
    uptr                   userThreadArg,
    s32                    coreNo
);

/* Please see man pages for details 
    
 */
void FinalizeSoundThread();

/* Please see man pages for details 
    
 */
inline void FinalizeUserSoundThread() {}

/* Please see man pages for details 
    

                

    
 */
void EnableSoundThreadTickCounter(bool enable);

/* Please see man pages for details 
    

                
 */
nn::os::Tick GetSoundThreadTick();

/* Please see man pages for details 
    
 */
void LockSoundThread();

/* Please see man pages for details 
    
 */
void UnlockSoundThread();

/*  

*/

/* Please see man pages for details 
  

  
*/
/* Please see man pages for details 
    

                

    
    
    
*/
nn::Result FlushDataCache( uptr addr, size_t size );

/* Please see man pages for details 
    

                

    
    
    
*/
nn::Result InvalidateDataCache( uptr addr, size_t size );

/*  

*/

/* Please see man pages for details 
  

  
*/

/* Please see man pages for details 
    
*/
void WaitForDspSync();

/* Please see man pages for details 
    
    
*/
void WaitForDspSync(nn::os::Tick* pTick);

/* Please see man pages for details 
    
*/
void SendParameterToDsp();

/* Please see man pages for details 

 */

/* Please see man pages for details 
  

  
  
  
  
*/
s32 GetSampleLength( s32 size, SampleFormat format, s32 channelCount ) ;

/* Please see man pages for details 
    
    
 */
/* Please see man pages for details 
    

    
*/
void SetMasterVolume ( f32 volume );

/* Please see man pages for details 
    
    
*/
f32 GetMasterVolume();

/* Please see man pages for details 
    

                

                

    
    
*/
void SetAuxReturnVolume ( AuxBusId busId, f32 volume );

/* Please see man pages for details 
    

                

                

    
    
*/
f32 GetAuxReturnVolume ( AuxBusId busId ) ;

/* Please see man pages for details 
    

    
    
    
*/
void RegisterAuxCallback( AuxBusId busId, AuxCallback callback, uptr userData );

/* Please see man pages for details 
    

    
    
    
*/
void GetAuxCallback( AuxBusId busId, AuxCallback* pCallback, uptr* pUserData );

/* Please see man pages for details 
    

    
*/
void ClearAuxCallback( AuxBusId busId );

/* Please see man pages for details 
    
    
    
    
 */
bool SetAuxFrontBypass(AuxBusId busId, bool flag);
/*  

*/

/* Please see man pages for details 
  
  
 */
/* Please see man pages for details 
    

    
    
 */
bool SetSoundOutputMode(OutputMode mode);

/* Please see man pages for details 
    

    
 */
OutputMode GetSoundOutputMode();

/* Please see man pages for details 
  
  
  
*/
bool SetClippingMode(ClippingMode mode);

/* Please see man pages for details 
  
  
*/
ClippingMode GetClippingMode();

/* Please see man pages for details 
    

    
    
 */
bool SetRearRatio(f32 depth);

/* Please see man pages for details 
    

                
                
                

                

    
    
 */
bool SetSurroundDepth(f32 depth);

/* Please see man pages for details 
    

    
    
 */
bool SetSurroundSpeakerPosition(SurroundSpeakerPosition pos);

/*  

*/

/* Please see man pages for details 
    

                
                
                

    
*/
void SetMaximumDspCycles( s32 cycles );

/* Please see man pages for details 
    

    
*/
s32 GetMaximumDspCycles();

/* Please see man pages for details 
    

    
*/
s32 GetDspCycles();

/* Please see man pages for details 
    
 */
void Sleep();

/* Please see man pages for details 
    
 */
void WakeUp();

/* Please see man pages for details 
    
 */
void OrderToWaitForFinalize();

/* Please see man pages for details 
    
    
 */
bool GetHeadphoneStatus();

/* Please see man pages for details 
    
    
 */
bool UpdateHeadphoneStatus();

/* Please see man pages for details 
    
    
    
 */
inline Result SetHeadphoneOutOnShellClose(bool forceout)
{
    return dsp::ForceHeadphoneOut(forceout);
}

/* Please see man pages for details 
    
    
 */
/* Please see man pages for details 
    
    
    
    
 */
bool GetMixedBusData(s16* pData, s32 nSamplesPerFrame = NN_SND_SAMPLES_PER_FRAME);
/*  

*/

/* Please see man pages for details 
    
    
 */
/* Please see man pages for details 
    
    
 */
s32 GetDroppedSoundFrameCount();

/* Please see man pages for details 
    
 */
void ClearDroppedSoundFrameCount();

/*  

*/

/* Please see man pages for details 
  
  
 */
/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
 */
void EncodeAdpcmData(s16* pInput, u8* pOutput, s32 nSamples, s32 sampleRate, s32 loopStart, s32 loopEnd, DspsndAdpcmHeader* pInfo);

/* Please see man pages for details 
  

  
  
  
  
  
 */
void DecodeAdpcmData(const u8* pInput, s16* pOutput, const AdpcmParam& param, AdpcmContext& context, s32 nSamples);

/* Please see man pages for details 
  

  
  
 */
s32 GetAdpcmOutputBufferSize(s32 nSamples);

/* Please see man pages for details 
  

  
  
 */
u32 ConvertAdpcmPos2Nib(u32 nPos);
/* Please see man pages for details 
  

  
  
 */
u32 ConvertAdpcmNib2Pos(u32 nNib);
/*  

*/

/* Please see man pages for details 
  

  
*/

/* Please see man pages for details 
  

                

                
                
                

                
                

                
                

                
                
                
                
                

                
                
                
                

  
  

  
                              

  
  
  
  
  
 */
bool SetEffect(AuxBusId busId, FxDelay* fx);

/* Please see man pages for details 
  

                

                
                
                

                
                

                
                

                
                
                
                
                

                
                
                
                


  
  

  
                              
  
  
  
  

  
 */
bool SetEffect(AuxBusId busId, FxReverb* fx);

/* Please see man pages for details 
  

                

                
                


  

  
  
  

  
 */
void ClearEffect(AuxBusId busId);

/*  

*/

/* Please see man pages for details 
    
    
 */
void SetOutputBufferCount(s32 count);

/* Please see man pages for details 
    
 */
s32 GetOutputBufferCount();

/* Please see man pages for details 
    

                
                
                

                
                
                
                
                
                

                
                  

                
                  

                
                
                

                

    
 */
void SetSyncMode(SyncMode mode);

/* Please see man pages for details 
    
 */
SyncMode GetSyncMode();

}}} // namespace nn::snd::CTR

#endif // __cplusplus

// Below is the C declaration
/* Please see man pages for details 
    

    
*/

/* Please see man pages for details 

*/
NN_EXTERN_C nnResult nnsndInitialize();

/*  

*/

#endif // NN_SND_CTR_MPCORE_SND_API_H_
