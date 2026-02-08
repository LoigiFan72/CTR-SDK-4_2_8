/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_PadReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

*/
#ifndef NN_HID_CTR_HID_PADREADER_H_
#define NN_HID_CTR_HID_PADREADER_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_AnalogStickClamper.h>
#include <nn/hid/CTR/hid_Result.h>
#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_pad.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>
#include <nn/util/util_NonCopyable.h>

namespace nn {
namespace hid {
namespace CTR {

/* Please see man pages for details 

             

*/

class PadReader : private nn::util::NonCopyable<PadReader>
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
    } StickClampMode;

    /* Please see man pages for details 
    

                    

    

    */
    PadReader(Pad& pad=GetPad( ));

    /* Please see man pages for details 
    

    */
    ~PadReader( ) {};

    /* Please see man pages for details 
      

                    
                    
                    

      
      
      
      

    */
    void Read(PadStatus* pBufs, s32* pReadLen, s32 bufLen);

    /* Please see man pages for details 
      

      
                    
                    
                    

      
      
      
      

    */
    bool ReadLatest(PadStatus* pBuf);

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    

      
      
      

    */
    void SetStickClamp(s16 min, s16 max);

    /* Please see man pages for details 
      

      
      
      
    */
    void GetStickClamp(s16* pMin, s16* pMax) const;

    /* Please see man pages for details 
      

      
    */
    StickClampMode GetStickClampMode( ) const;

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
    static const s8 MAX_READ_NUM = 7;

private:
    static AnalogStickClamper::ClampMode  ClamperClampMode(const StickClampMode mode);
    static StickClampMode ReaderClampMode(const AnalogStickClamper::ClampMode mode);
protected:
    static void HideKeyInfo(PadStatus* padStatus);


protected:
    Pad&                m_Pad;                  //8
    s32                 m_IndexOfRead;          //4
    bit32               m_LatestHold;           //4
    AnalogStickClamper  m_StickClamper;         //36
    bool                m_IsReadLatestFirst;   //1
    NN_PADDING3;                              //3
    NN_PADDING4;

    s64                 m_TickOfRead;           //8
};


// inline definition
inline void PadReader::GetStickClamp(s16* pMin, s16* pMax) const
{
    m_StickClamper.GetStickClamp(pMin,pMax);
}

inline PadReader::StickClampMode PadReader::GetStickClampMode( ) const
{
    return ReaderClampMode(m_StickClamper.GetStickClampMode());
}

inline void PadReader::SetStickClampMode(StickClampMode mode)
{
    m_StickClamper.SetStickClampMode(ClamperClampMode(mode));
}

/* Please see man pages for details 
  
                

  
  
  
*/
bool EnableSelectButton();

/* Please see man pages for details 
  

  
*/
void DisableSelectButton();


// Private function that does not require reference
bool IsSelectButtonEnabled();


} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif  // #ifndef NN_HID_CTR_HID_PADREADER_H_
