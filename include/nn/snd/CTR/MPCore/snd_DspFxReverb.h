/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_DspFxReverb.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_CTR_SND_DSP_FX_REVERB_H_
#define NN_SND_CTR_SND_DSP_FX_REVERB_H_

#include <nn/os.h>
#include <nn/snd/CTR/Common/snd_Types.h>
#include <nn/util/util_NonCopyable.h>

#ifdef __cplusplus

/* Please see man pages for details 
    
*/

namespace nn  {
namespace snd {
namespace CTR {

/* Please see man pages for details 
    
 */
class DspFxReverb : private nn::util::NonCopyable<DspFxReverb>
{
public:
    /* Please see man pages for details 
        
     */
    struct FilterSize
    {
        u32  m_Comb0;    //
        u32  m_Comb1;    //
        u32  m_AllPass;  //
    };
    /* Please see man pages for details 
        
     */
    struct Param
    {
        //
        u32 m_EarlyReflectionTime;

        //
        u32 m_FusedTime;

        //
        u32 m_PreDelayTime;

        f32 m_Coloration;   //

        f32 m_Damping;      //

        //
        FilterSize* m_pFilterSize;

        f32 m_EarlyGain;    //
        f32 m_FusedGain;    //

        bool m_UseHpfDamping;   //
        NN_PADDING3;

        /* Please see man pages for details 
            
         */
        Param();
    };

public:
    //----------------------------------------------------------------
    //
    //----------------------------------------------------------------
    //
    /* Please see man pages for details 
        
     */
    DspFxReverb();

    /* Please see man pages for details 
        
     */
    ~DspFxReverb();
    //

    /* Please see man pages for details 
        
        
        
     */
    static size_t GetRequiredMemorySize(const DspFxReverb::Param& param);

    /* Please see man pages for details 
        
        
        
        
     */
    bool Initialize(uptr buffer, size_t size);

    /* Please see man pages for details 
        
     */
    void Finalize();

    /* Please see man pages for details 
        
        
        
     */
    bool Attach(AuxBusId id);

    /* Please see man pages for details 
        
     */
    void Detach();

    /* Please see man pages for details 
        
        
        
     */
    bool SetParam(const DspFxReverb::Param& param);

    /* Please see man pages for details 
        
        
        
     */
    bool Enable(bool enable = true);

    /* Please see man pages for details 
        
        
     */
    bool Disable()
    {
        return Enable(false);
    }

    /* Please see man pages for details 
        
        
     */
    bool IsEnabled()
    {
        return m_IsEnabled;
    }

    /* Please see man pages for details 
        
        
     */
    bool IsBufferInUse();

private:
    bool AssignWorkBuffer(uptr buffer, size_t size);

    void ReleaseWorkBuffer();

    static FilterSize s_DefaultFilterSize;

    uptr                        m_Buffer;
    uptr                        m_BufferPhysical;
    size_t                      m_BufferSize;

    bool                        m_IsInitialized;
    util::SizedEnum1<AuxBusId>  m_AuxBusId;
    bool                        m_IsEnabled;
    s8                          m_ProcessCount;  // Used to determine if memory can be deallocated
};

}}} // namespace nn::snd::CTR

#endif // __cplusplus

#endif // NN_SND_CTR_SND_DSP_FX_REVERB_H_
