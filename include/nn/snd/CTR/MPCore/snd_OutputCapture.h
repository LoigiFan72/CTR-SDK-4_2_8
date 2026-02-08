/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_OutputCapture.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47340 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_CTR_OUTPUT_CAPTURE_H_
#define NN_SND_CTR_OUTPUT_CAPTURE_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/snd/CTR/Common/snd_Const.h>

#ifdef __cplusplus

namespace nn {
namespace snd {
namespace CTR {

class Dspsnd;

/* Please see man pages for details 
    
 */
class OutputCapture
{
    friend class Dspsnd;  // Only Dspsnd can use OutputCapture::Write

private:
    /* Please see man pages for details 
        
        
        
     */
    void Write(s16* pData, s32 length = NN_SND_SAMPLES_PER_FRAME);

public:
    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
     */
    OutputCapture();

    /* Please see man pages for details 
        
     */
    ~OutputCapture();
    /* Please see man pages for details 
        
     */

    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
        
     */
    static inline size_t GetRequiredMemorySize(s32 frames)
    {
        return NN_SND_SAMPLES_PER_FRAME * sizeof(s16) * 2 * frames;
    }

    /* Please see man pages for details 
        
        
        
     */
    void Initialize(void* buffer, size_t size);

    /* Please see man pages for details 
        
     */
    void Finalize();
    /*  

*/

    /* Please see man pages for details 
        
        
     */
    /* Please see man pages for details 
        
        
     */
    void Enable(bool enable = true);

    /* Please see man pages for details 
        
     */
    void Disable() { Enable(false); }

    /* Please see man pages for details 
        
        
     */
    bool IsEnabled() const { return m_IsEnabled; }

    /* Please see man pages for details 
        
        
        
        
     */
    s32 Read(s16* pData, s32 length = NN_SND_SAMPLES_PER_FRAME);

    /* Please see man pages for details 
        
     */
    void Reset();
    /*  

*/

private:
    static const size_t UNIT_SIZE = sizeof(s16) * 2;  // 16bit, stereo

    uptr            m_BufferAddress;  // Address of buffer that stores the data to obtain
    s32             m_BufferLength;   // Buffer length
    s32             m_ReadPos;        // Read position
    s32             m_WritePos;       // Light position
    bool            m_IsEnabled;      // Enabled/disabled flag
    NN_PADDING3;
}; // class OutputCapture

/* Please see man pages for details 
    
    
 */
/* Please see man pages for details 
    
    
 */
void SetOutputCapture(OutputCapture* pCapture);
/*  

*/

} // namespace CTR
} // namespace snd
} // namespace nn

#endif // __cplusplus

#endif // NN_SND_CTR_OUTPUT_CAPTURE_H_
