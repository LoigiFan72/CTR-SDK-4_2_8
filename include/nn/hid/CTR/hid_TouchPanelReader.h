/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_TouchPanelReader.h

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
#ifndef NN_HID_CTR_HID_TOUCHPANELREADER_H_
#define NN_HID_CTR_HID_TOUCHPANELREADER_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_Result.h>
#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_TouchPanel.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>
#include <nn/util/util_NonCopyable.h>

namespace nn {
namespace hid {
namespace CTR {


/* Please see man pages for details 

              

*/
class TouchPanelReader : private nn::util::NonCopyable<TouchPanelReader>
{
public:
    /* Please see man pages for details 
      


      

    

    */
    TouchPanelReader(TouchPanel& touchPanel = GetTouchPanel( ))
        : m_TouchPanel(touchPanel)
        , m_IndexOfRead(-1)
        , m_TickOfRead(-1)
        {};

    /* Please see man pages for details 
      

    */
    ~TouchPanelReader( ) {};

    // TODO: After improving, write the sampling period.
    /* Please see man pages for details 
      

      
      
      
      

    */
    void Read(TouchPanelStatus* pBufs, s32* pReadLen, s32 bufLen);

    /* Please see man pages for details 
      

      
      
      
      

    */
    bool ReadLatest(TouchPanelStatus* pBuf);


    /* Please see man pages for details 
      
    */
    static const s8 MAX_READ_NUM = 7;

protected:
    TouchPanel&             m_TouchPanel;
    s32                     m_IndexOfRead;
    s64                     m_TickOfRead;
};

} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif  // #ifndef NN_HID_CTR_HID_TOUCHPANELREADER_H_
