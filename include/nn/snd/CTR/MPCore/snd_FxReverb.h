/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_FxReverb.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_FX_REVERB_H_
#define NN_SND_FX_REVERB_H_

#ifdef __cplusplus

namespace nn  { namespace snd { namespace CTR {

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
class FxReverb
{
public:
    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    struct FilterSize
    {
        u32  m_Comb0;    //
        u32  m_Comb1;    //
        u32  m_AllPass;  //

        //---------------------------------------------------------------------------
        //
        //
        //
        //---------------------------------------------------------------------------
        FilterSize()
        : m_Comb0( 19 * NN_SND_SAMPLES_PER_FRAME ),
          m_Comb1( 23 * NN_SND_SAMPLES_PER_FRAME ),
          m_AllPass( 13 * NN_SND_SAMPLES_PER_FRAME )
        {}
    };

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    struct Param
    {
        u32 m_EarlyReflectionTime;  //
        u32 m_FusedTime;            //
        u32 m_PreDelayTime;         //
        f32 m_Coloration;           //
        f32 m_Damping;              //

        //
        FilterSize* m_pFilterSize;

        f32 m_EarlyGain;            //
        f32 m_FusedGain;            //

        bool m_UseHpfDamping;       //
        NN_PADDING3;

        //---------------------------------------------------------------------------
        //
        //
        //
        //---------------------------------------------------------------------------
        Param()
        : m_EarlyReflectionTime( 60 ),  // msec
          m_FusedTime( 4000 ),          // msec
          m_PreDelayTime( 100 ),        // msec
          m_Coloration( 0.5f ),
          m_Damping( 0.4f ),
          m_pFilterSize( &s_DefaultFilterSize ),
          m_EarlyGain( 0.6f ),
          m_FusedGain( 0.4f ),
          m_UseHpfDamping( false )
        {}
    };

    //----------------------------------------
    //
    //
    //---------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    FxReverb();

    //---------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    virtual ~FxReverb();
    //

    //----------------------------------------------------------------
    //
    //----------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    bool SetParam( const Param& param );

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    const Param& GetParam() const
    {
        return m_Param;
    }
    //

    //----------------------------------------
    //
    //

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    size_t GetRequiredMemSize();

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    bool AssignWorkBuffer( uptr buffer, size_t size );

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    void ReleaseWorkBuffer();
    //

    /* Please see man pages for details */
    bool Initialize();

    /* Please see man pages for details */
    void Finalize();

    /* Please see man pages for details */
    void UpdateBuffer( uptr data );

private:
    struct WorkBuffer
    {
        s32*  m_EarlyReflection[4]; // For first reflection
        s32*  m_PreDelay[4];        // For pre-delay
        s32*  m_CombFilter[4][2];   // For comb filter (2-stage)
        s32*  m_AllPassFilter[4];   // For all-pass filter (1-stage)
        s32   m_Lpf[4];             // For LPF
    };

    static FilterSize s_DefaultFilterSize;

    void AllocBuffer();
    void FreeBuffer();

    void InitializeParam();

    Param           m_Param;
    uptr            m_pBuffer;
    size_t          m_BufferSize;
    FilterSize      m_FilterSize;
    WorkBuffer      m_WorkBuffer;

    s32  m_EarlyLength;
    s32  m_EarlyPos;

    s32  m_PreDelayLength;
    s32  m_PreDelayPos;

    s32  m_CombFilterLength[2];
    s32  m_CombFilterPos[2];
    s32  m_CombFilterCoef[2];

    s32  m_AllPassFilterLength;
    s32  m_AllPassFilterPos;
    s32  m_AllPassFilterCoef;

    s32  m_LastLpfOut[4];


    // Parameters below changed as if calculated by the InitializeParam function
    s32 m_EarlyGain;
    s32 m_FusedGain;
    s32 m_LpfCoef1;
    s32 m_LpfCoef2;

    u32 m_EarlyReflectionTimeAtInitialize;
    u32 m_PreDelayTimeAtInitialize;
    FilterSize m_FilterSizeAtInitialize;

    bool m_IsActive;

    NN_PADDING3;
};

}}} // namespace nn::snd::CTR

#endif // __cplusplus

#endif /* NN_SND_FX_REVERB_H_ */

