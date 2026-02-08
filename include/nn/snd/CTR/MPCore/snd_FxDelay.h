/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_FxDelay.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_FX_DELAY_H_
#define NN_SND_FX_DELAY_H_

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
//
//
//---------------------------------------------------------------------------
class FxDelay
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
        //
        u32 m_DelayTime;

        //
        f32 m_FeedbackGain;  

        //
        f32 m_Damping;

        //
        bool m_IsEnableSurround;

        NN_PADDING3;
        
        //---------------------------------------------------------------------------
        //
        //
        //
        //
        //---------------------------------------------------------------------------
        Param()
        : m_DelayTime( 250 ),
          m_FeedbackGain( 0.4f ),
          m_Damping( 0.5f ),
          m_IsEnableSurround( false )
          {}
    };

    //----------------------------------------------------------------
    //
    //----------------------------------------------------------------
    //
    //---------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    FxDelay();

    //---------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    virtual ~FxDelay();
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
    //---------------------------------------------------------------------------
    bool SetParam( const FxDelay::Param& param );
    
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
        s32* m_Delay[4];      //
        s32  m_Lpf[4];        //
    };
    
    void AllocBuffer();
    void FreeBuffer();
    void InitializeParam();
    
    Param   m_Param;
    uptr    m_pBuffer;            //
    size_t  m_BufferSize;        //
    
    WorkBuffer  m_WorkBuffer;    //
    
    u32     m_DelayFrames;       //
    u32     m_CurFrame;          //
    
    s32     m_FeedbackGain;      //
    s32     m_LpfCoef1;          //
    s32     m_LpfCoef2;          //
    
    u32     m_DelayTimeAtInitialize;
    bool    m_IsEnableSurroundAtInitialize;

    u8      m_ProcessChannelCount;
    bool    m_IsActive;          //

    NN_PADDING1;
};

}}} // namespace nn::snd::CTR

#endif // __cplusplus

#endif /* NN_SND_FX_DELAY_H_ */

