/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Voice.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46364 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_VOICE_H_
#define NN_SND_VOICE_H_

#include <nn/os.h>
#include <nn/Result.h>

#include <nn/snd/CTR/Common/snd_Types.h>

#ifdef __cplusplus

/* Please see man pages for details 
    
*/

namespace nn  { namespace snd { namespace CTR {

/* Please see man pages for details 
    
    
    
*/
typedef void (*VoiceDropCallbackFunc)(class Voice *, uptr userArg);

class VoiceImpl;
class VoiceManager;

/* Please see man pages for details 
    
 */
class Voice
{
    friend class VoiceManager;

public:

    /* Please see man pages for details 
        
     */
    enum State
    {
        STATE_PLAY,  //
        STATE_STOP,  //
        STATE_PAUSE  //
    };

private:
    const s32                           m_Id;                  // Voice number (for management)

    util::SizedEnum1<State>             m_State;               // Status
    util::SizedEnum1<InterpolationType> m_InterpolationType;   // Interpolation method
    NN_PADDING1;

    util::SizedEnum1<FilterType>        m_FilterType;          // Filter type
    MonoFilterCoefficients              m_MonoFilterCoeffs;    // Monopole filter coefficient
    BiquadFilterCoefficients            m_BiquadFilterCoeffs;  // Bipolar filter coefficient
    NN_PADDING2;

    s32                                 m_SampleRate;          // Sampling frequency
    f32                                 m_Pitch;               // Pitch (ratio for SampleRate)

    s32                                 m_Priority;            // Priority
    Voice *                             m_PriorVoice;          // Pointer to the Voice with high priority
    Voice *                             m_InferiorVoice;       // Pointer to the Voice with low priority

    VoiceDropCallbackFunc               m_Callback;            // Callback function called when Voice is deallocated by the system
    uptr                                m_UserArg;             // User argument when calling the above callback

    MixParam                            m_MixParam;            // Gain for each channel
    f32                                 m_Volume;              // Volume

    VoiceImpl*                          m_pImpl;

    void Initialize();
    void UpdateStatus(const void* pVars);
    void UpdateWaveBufferList();
    s32 GetId() const { return m_Id; }
    VoiceImpl* GetImpl() const { return m_pImpl; }

    /* Please see man pages for details 
        

                    
                    
     */
    explicit Voice(s32 id);

    /* Please see man pages for details 
        
     */
    ~Voice();

public:
    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
     */
    void AppendWaveBuffer(WaveBuffer* pBuffer);

    /* Please see man pages for details 
        
        
     */
    void DeleteWaveBuffer(WaveBuffer* pBuffer);

    /* Please see man pages for details 
        
        
     */
    void UpdateWaveBuffer(WaveBuffer* pBuffer);

    /*  

*/

    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
     */
    void SetChannelCount(s32 channelCount);

    /* Please see man pages for details 
        
        
     */
    void SetSampleFormat(SampleFormat format);

    /* Please see man pages for details 
        
        
     */
    void SetFrontBypassFlag(bool flag);

    void Set3dSurroundPreprocessed(bool flag);

    /* Please see man pages for details 
        
        
     */
    void SetStartFrameFadeInFlag(bool flag);

    /* Please see man pages for details 
        
        
     */
    void SetSampleRate(s32 sampleRate);

    /* Please see man pages for details 
        
        
     */
    void SetPitch(f32 pitch);

    /* Please see man pages for details 
        
        
     */
    void SetAdpcmParam(const AdpcmParam& param);

    /* Please see man pages for details 
        
        
     */
    void SetPriority(s32 priority);

    /* Please see man pages for details 
        
        
     */
    void SetState(State state);

    /* Please see man pages for details 
        
        
     */
    void SetMixParam(const MixParam& mixParam);

    /* Please see man pages for details 
        
        
     */
    void SetVolume(f32 volume);

    /* Please see man pages for details 
        
        
     */
    void SetInterpolationType(InterpolationType type);

    /* Please see man pages for details 
        
        
     */
    void SetFilterType(FilterType type);

    /* Please see man pages for details 
        
        
     */
    void EnableMonoFilter(bool enable);

    /* Please see man pages for details 
        
        
     */
    void SetMonoFilterCoefficients(const MonoFilterCoefficients* pCoeff) NN_ATTRIBUTE_DEPRECATED;

    /* Please see man pages for details 
        
        
     */
    void SetMonoFilterCoefficients(const MonoFilterCoefficients& coeff);

    /* Please see man pages for details 
        
        
     */
    void SetMonoFilterCoefficients(u16 cutoff);

    /* Please see man pages for details 
        
        
     */
    void EnableBiquadFilter(bool enable);

    /* Please see man pages for details 
        
        
     */
    void SetBiquadFilterCoefficients(const BiquadFilterCoefficients* pCoeff) NN_ATTRIBUTE_DEPRECATED;

    /* Please see man pages for details 
        
        
     */
    void SetBiquadFilterCoefficients(const BiquadFilterCoefficients& coeff);
    /*  

*/

    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
     */
    inline f32 GetPitch() const { return m_Pitch; }

    /* Please see man pages for details 
        
        
     */
    inline s32 GetPriority() const { return m_Priority; }

    /* Please see man pages for details 
        
        
     */
    inline Voice::State GetState() const { return m_State; }

    /* Please see man pages for details 
        
        
     */
    inline const MixParam& GetMixParam() const { return m_MixParam; }

    /* Please see man pages for details 
        
        
     */
    inline f32 GetVolume() const { return m_Volume; }

    /* Please see man pages for details 
        
        
     */
    inline InterpolationType GetInterpolationType() const { return m_InterpolationType; }

    /* Please see man pages for details 
        
        
     */
    inline FilterType GetFilterType() const { return m_FilterType; }

    /* Please see man pages for details 
        
        
     */
    void GetMonoFilterCoefficients(MonoFilterCoefficients* pCoeff) NN_ATTRIBUTE_DEPRECATED;

    /* Please see man pages for details 
        
        
     */
    void GetMonoFilterCoefficients(MonoFilterCoefficients& coeff);

    /* Please see man pages for details 
        
        
     */
    void GetBiquadFilterCoefficients(BiquadFilterCoefficients* pCoeff) NN_ATTRIBUTE_DEPRECATED;

    /* Please see man pages for details 
        
        
     */
    void GetBiquadFilterCoefficients(BiquadFilterCoefficients& coeff);
    /*  

*/

    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
     */
    s32 GetPlayPosition() const;

    /* Please see man pages for details 
        
        
     */
    bool IsPlaying() const;
    /*  

*/

    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
        
        
        
        
     */
    bool SetupBcwav(uptr addrBcwav, WaveBuffer* pWaveBuffer0, WaveBuffer* pWaveBuffer1, Bcwav::ChannelIndex channelIndex = Bcwav::CHANNEL_INDEX_L);
    /*  

*/
}; // class Voice

/* Please see man pages for details 
    
    
 */
/* Please see man pages for details 
    
    
    
    
    
 */
Voice* AllocVoice(s32 priority, VoiceDropCallbackFunc callback, uptr userArg);

/* Please see man pages for details 
    
    
 */
void FreeVoice(Voice* pVoice);

/* Please see man pages for details 
    
 */
enum VoiceDropMode
{
    VOICE_DROP_MODE_DEFAULT = 0,   //
    VOICE_DROP_MODE_REAL_TIME = 1  //
};

/* Please see man pages for details 
    

                
                
                

                
                
                

    
 */
void SetVoiceDropMode(VoiceDropMode mode);

/*  

*/

}}} // namespace nn::snd::CTR

#endif // __cplusplus

#endif //NN_SND_VOICE_H_
