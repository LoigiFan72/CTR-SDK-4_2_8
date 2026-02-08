/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_DebugPadReader.h

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
#ifndef NN_HID_CTR_HID_DEBUG_PAD_READER_H_
#define NN_HID_CTR_HID_DEBUG_PAD_READER_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_Result.h>
#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_pad.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>
#include <nn/util/util_SizedEnum.h>
#include <nn/util/util_NonCopyable.h>

namespace nn {
namespace hid {
namespace CTR {
/* Please see man pages for details 

             
             
             

*/

class DebugPadReader : private nn::util::NonCopyable<DebugPadReader>
{
public:
    /* Please see man pages for details 
      
      
     */

    typedef enum
    {
        /* Please see man pages for details */
        STICK_CLAMP_MODE_CIRCLE_WITH_PLAY = 0,
        /* Please see man pages for details */
        STICK_CLAMP_MODE_CIRCLE_WITHOUT_PLAY
    } StickClampMode;

    /* Please see man pages for details 
    

                    

    

    */
    DebugPadReader(DebugPad& debugPad=GetDebugPad( ))
        : m_DebugPad(debugPad)
        , m_IndexOfRead(-1)
        , m_IsReadLatestFirst(true)
        , m_StickClampMode(STICK_CLAMP_MODE_CIRCLE_WITH_PLAY)
        , m_TickOfRead(-1)
        {};

    /* Please see man pages for details 
    

    */
    ~DebugPadReader( ) {};

    /* Please see man pages for details 
      

      
      
      
      

    */
    void Read(DebugPadStatus* pBufs, s32* pReadLen, s32 bufLen);

    /* Please see man pages for details 
      

      

      
      
                      
                      

    */
    bool ReadLatest(DebugPadStatus* pBuf);

    /* Please see man pages for details 
      

      

    */
    StickClampMode GetStickClampMode( ) const;

    /* Please see man pages for details 
      

                    
                   

      
      

    */
    void SetStickClampMode(StickClampMode mode);


    /* Please see man pages for details 
      
    */
    static const s8 MAX_READ_NUM = 7;

protected:
    DebugPad&           m_DebugPad;
    s32                 m_IndexOfRead;
    bit16               m_LatestHold;
    bool                m_IsReadLatestFirst;
    nn::util::SizedEnum1<StickClampMode>      m_StickClampMode;
    NN_PADDING4;
    s64                 m_TickOfRead;
};


// inline definition

inline DebugPadReader::StickClampMode DebugPadReader::GetStickClampMode( ) const
{
    return m_StickClampMode;
}

inline void DebugPadReader::SetStickClampMode(DebugPadReader::StickClampMode mode)
{
    m_StickClampMode = mode;
}

} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif  // #ifndef NN_HID_CTR_HID_DEBUG_PAD_READER_H_
