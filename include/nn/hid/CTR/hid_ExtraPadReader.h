/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_ExtraPadReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_CTR_HID_EXTRAPADREADER_H_
#define NN_HID_CTR_HID_EXTRAPADREADER_H_

#include <nn/hid/CTR/hid_ExtraPad.h>
#include <nn/hid/CTR/hid_ExtraPadStatus.h>
#include <nn/hid/CTR/hid_AnalogStickClamper.h>
#include <nn/hid/CTR/hid_PadReader.h>


/*
 *
 */
namespace nn
{

namespace hid
{

namespace CTR
{


/* Please see man pages for details 

    
    
    
    
    
  
    
    
    
 */
class ExtraPadReader
{

public:

    /* Please see man pages for details 
      
      
             
     */
    typedef enum
    {
        /* Please see man pages for details */
        STICK_CLAMP_MODE_CIRCLE  = AnalogStickClamper::STICK_CLAMP_MODE_CIRCLE,
        /* Please see man pages for details */
        STICK_CLAMP_MODE_CROSS   = AnalogStickClamper::STICK_CLAMP_MODE_CROSS,
        /* Please see man pages for details */
        STICK_CLAMP_MODE_MINIMUM = AnalogStickClamper::STICK_CLAMP_MODE_MINIMUM
    }StickClampMode;

    /* Please see man pages for details 
      
      
     */
    /* Please see man pages for details 
    

                    

    */

    ExtraPadReader();

    /* Please see man pages for details 
    

    */
    virtual ~ExtraPadReader();

    /* Please see man pages for details 
      
      
      
     */

    /* Please see man pages for details 
      

                    
                    

                    
                    
                    

      
      
      
      

    */
    void Read(ExtraPadStatus* pBufs, s32* pReadLen, s32 bufLen);

    /* Please see man pages for details 
      

                    
                    
                    

      
      
      
      
     */
    bool ReadLatest(ExtraPadStatus* pBuf);


    /* Please see man pages for details 
      
      
      
     */

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    

      
      
      

    */
    void SetStickClamp(s16 min, s16 max);

    /* Please see man pages for details 
      

      
      
      

    */
    void GetStickClamp(s16* pMin, s16* pMax) const;

    /* Please see man pages for details 
      

      

    */
    StickClampMode GetStickClampMode() const;

    /* Please see man pages for details 
      

                    
                    

      
      

    */
    void SetStickClampMode(StickClampMode mode);

    /* Please see man pages for details 
      

                     

      
      
    */
    f32 NormalizeStick(s16 x);

    /* Please see man pages for details 
      

                     
                     

      
      
      
      
      
    */
    void NormalizeStickWithScale( f32* normalized_x, f32* normalized_y, s16 x, s16 y );

    /* Please see man pages for details 
      

                      
                      
                      
                      
                      
                      

      
      
      
    */
    void SetNormalizeStickScaleSettings( f32 scale, s16 threshold  );

    /* Please see man pages for details 
      

      
      
      
    */
    void GetNormalizeStickScaleSettings( f32* scale, s16* threshold  ) const;

    /* Please see man pages for details 
      
      
      
     */



    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    

      
      
      

    */
    void SetExtraStickClamp(s16 min, s16 max);

    /* Please see man pages for details 
      

      
      
      

    */
    void GetExtraStickClamp(s16* pMin, s16* pMax) const;

    /* Please see man pages for details 
      

      

    */
    StickClampMode GetExtraStickClampMode() const;

    /* Please see man pages for details 
      

                    
                    

      
      

    */
    void SetExtraStickClampMode(StickClampMode mode);

    /* Please see man pages for details 
      

                     

      
      
    */
    f32 NormalizeExtraStick(s16 x);

    /* Please see man pages for details 
      

                     
                     

      
      
      
      
      
    */
    void NormalizeExtraStickWithScale( f32* normalized_x, f32* normalized_y, s16 x, s16 y );

    /* Please see man pages for details 
      

                      
                      
                      
                      
                      
                      

      
      
      
    */
    void SetNormalizeExtraStickScaleSettings( f32 scale, s16 threshold  );

    /* Please see man pages for details 
      

      
      
      
    */
    void GetNormalizeExtraStickScaleSettings( f32* scale, s16* threshold  ) const;

    /*  

*/

private:
    static AnalogStickClamper::ClampMode ClamperClampMode(StickClampMode mode);
    static StickClampMode ReaderClampMode(AnalogStickClamper::ClampMode  mode);
    static void ConvertFromExtraPadStatusToPadStatus(PadStatus* pPadStatus, const ExtraPadStatus* pExtraPadStatus);

protected:

    NN_PADDING4;
    AnalogStickClamper m_ExtraStickClamper;
    AnalogStickClamper m_StickClamper;
    s32         m_IndexOfRead;
    bit32       m_LatestHold;
    PadReader m_PadReader;
    bool       m_IsReadLatestFirst;
    NN_PADDING3;
    NN_PADDING4;
    s64         m_TickOfRead;
};


/* =======================================================================
  inline definition
 ======================================================================== */

inline void ExtraPadReader::SetExtraStickClamp(s16 min, s16 max)
{
    m_ExtraStickClamper.SetStickClamp(min,max);
}

inline void ExtraPadReader::GetExtraStickClamp(s16* pMin, s16* pMax) const
{
    m_ExtraStickClamper.GetStickClamp(pMin,pMax);
}

inline void ExtraPadReader::SetExtraStickClampMode(StickClampMode mode)
{
    m_ExtraStickClamper.SetStickClampMode(ClamperClampMode(mode));
}

inline ExtraPadReader::StickClampMode ExtraPadReader::GetExtraStickClampMode() const
{
    return ReaderClampMode(m_ExtraStickClamper.GetStickClampMode());
}

inline f32 ExtraPadReader::NormalizeExtraStick(s16 x)
{
    return m_ExtraStickClamper.NormalizeStick(x);
}

inline void ExtraPadReader::NormalizeExtraStickWithScale( f32* normalized_x, f32* normalized_y, s16 x, s16 y )
{
    m_ExtraStickClamper.NormalizeStickWithScale(normalized_x,normalized_y,x,y);
}

inline void ExtraPadReader::SetNormalizeExtraStickScaleSettings(f32 scale, s16 threshold)
{
    m_ExtraStickClamper.SetNormalizeStickScaleSettings(scale,threshold);
}

inline void ExtraPadReader::GetNormalizeExtraStickScaleSettings(f32* scale, s16* threshold) const
{
    m_ExtraStickClamper.GetNormalizeStickScaleSettings(scale,threshold);
}




}

}

}

#endif /* NN_HID_CTR_HID_EXTRAPADREADER_H_ */
