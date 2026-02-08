/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_AnalogStickClamper.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_CTR_HID_ANALOG_STICK_CLAMPER_H_
#define NN_HID_CTR_HID_ANALOG_STICK_CLAMPER_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/Result.h>
#include <nn/util/util_SizedEnum.h>

namespace nn {
namespace hid {
namespace CTR {

const f32 DEFAULT_SCALE_OF_NORMALIZE_STICK     = 1.5f;
const s16 DEFAULT_THRESHOLD_OF_NORMALIZE_STICK = 141;

/* Please see man pages for details 
  
*/
const s16   MIN_OF_STICK_CLAMP_MODE_CIRCLE  = 40;

/* Please see man pages for details 
  
*/
const s16   MIN_OF_STICK_CLAMP_MODE_CROSS   = 36;

/* Please see man pages for details 
  
*/
const s16   LIMIT_OF_STICK_CLAMP_MAX              = 145;



class AnalogStickClamper
{
public:
    enum ClampMode
    {
        STICK_CLAMP_MODE_CIRCLE = 0,
        STICK_CLAMP_MODE_CROSS,
        STICK_CLAMP_MODE_MINIMUM
    };

public:
    AnalogStickClamper();
    ~AnalogStickClamper(){};

    void SetStickClamp(s16 min, s16 max);
    void SetStickClampFree(s16 min, s16 max);
    void GetStickClamp(s16* pMin, s16* pMax) const;
    ClampMode GetStickClampMode( ) const;
    void SetStickClampMode(ClampMode mode);
    f32 NormalizeStick(s16 x);
    void NormalizeStickWithScale( f32* normalized_x, f32* normalized_y, s16 x, s16 y );
    void SetNormalizeStickScaleSettings( f32 scale, s16 threshold  );
    void GetNormalizeStickScaleSettings( f32* scale, s16* threshold  ) const;

    void ClampValueOfClamp();
    void ClampCore(s16* pOutX, s16* pOutY,s32 x,s32 y);

private:
    s16                 m_MinOfStickClampCircle;
    s16                 m_MinOfStickClampCross;
    s16                 m_MinOfStickClampMinimum;
    s16                 m_MaxOfStickClampCircle;
    s16                 m_MaxOfStickClampCross;
    s16                 m_MaxOfStickClampMinimum;
    nn::util::SizedEnum1<ClampMode>      m_StickClampMode;
    NN_PADDING1;
    s16                 m_Threshold;
    f32                 m_Scale;
    f32                 m_Stroke;
    f32                 m_StrokeVelocity;
    f32                 m_LastLength;
    f32                 m_LastDiff;

};

// inline definition
inline void AnalogStickClamper::GetStickClamp(s16* pMin, s16* pMax) const
{
    if (m_StickClampMode == STICK_CLAMP_MODE_CIRCLE)
    {
       *pMin = m_MinOfStickClampCircle;
       *pMax = m_MaxOfStickClampCircle;
    }
    else if (m_StickClampMode == STICK_CLAMP_MODE_CROSS)
    {
       *pMin = m_MinOfStickClampCross;
       *pMax = m_MaxOfStickClampCross;
    }
    else
    {
        *pMin = m_MinOfStickClampMinimum;
        *pMax = m_MaxOfStickClampMinimum;
    }
}

inline AnalogStickClamper::ClampMode AnalogStickClamper::GetStickClampMode( ) const
{
    return m_StickClampMode;
}

inline void AnalogStickClamper::SetStickClampMode(ClampMode mode)
{
    m_StickClampMode = mode;
}




}}}

#endif /* NN_HID_CTR_HID_ANALOG_STICK_CLAMPER_H_ */
