/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mic_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIC_CTR_MIC_TYPES_H_
#define NN_MIC_CTR_MIC_TYPES_H_

#include <nn/Result.h>

namespace nn {
namespace mic {
namespace CTR {
    /* Please see man pages for details 
      
    */
    enum SamplingType
    {
        SAMPLING_TYPE_8BIT         = 0,                       //!< Enable 8-bit (unsigned) sampling. Output data range is 0 to 255. 
        SAMPLING_TYPE_16BIT        = 1,                       //!< Enable 16-bit (unsigned) sampling. Output data range is 0 to 65535. 
        SAMPLING_TYPE_SIGNED_8BIT  = 2,                       //!< Enable 8-bit (signed) sampling. Output data range is -128 to 127. 
        SAMPLING_TYPE_SIGNED_16BIT = 3                        //!< Enable 16-bit (signed) sampling. Output data range is -32768 to 32767. 
    };
    /* Please see man pages for details 
      
    */
    enum SamplingRate
    {
        SAMPLING_RATE_32730      = 0,                         //!< 32.73kHz (actually 32728.498046875 Hz)
        SAMPLING_RATE_16360      = 1,                         //!< 16.36kHz (actually  16364.2490234375 Hz)
        SAMPLING_RATE_10910      = 2,                         //!< 10.91kHz (actually  10909.4993489583 Hz)
        SAMPLING_RATE_8180       = 3                          //!< 8.18kHz  (actually  8182.12451171875 Hz)
    };

    /* Please see man pages for details */
    const u8 SAMPLING_TYPE_8BIT_SILENT_DATA = 128;
    /* Please see man pages for details */
    const u16 SAMPLING_TYPE_16BIT_SILENT_DATA = 32768;
    /* Please see man pages for details */
    const s8 SAMPLING_TYPE_SIGNED_8BIT_SILENT_DATA = 0;
    /* Please see man pages for details */
    const s16 SAMPLING_TYPE_SIGNED_16BIT_SILENT_DATA = 0;

    /* Please see man pages for details 
      
               
               

               
    */
    const int g_ForbiddenArea[8]  = {3, 5, 9, 16, 32, 51, 110, 128};

    const u8 TYPE_8BIT_GUARANTEED_RANGE = 201;
    const u16 TYPE_16BIT_GUARANTEED_RANGE = 51310;

    /* Please see man pages for details 
    
    */
    const u8 TYPE_8BIT_GUARANTEED_INPUT_MIN = 27;
    /* Please see man pages for details 
    
    */
    const u8 TYPE_8BIT_GUARANTEED_INPUT_MAX = TYPE_8BIT_GUARANTEED_INPUT_MIN + TYPE_8BIT_GUARANTEED_RANGE;
    /* Please see man pages for details 
    
    */
    const u16 TYPE_16BIT_GUARANTEED_INPUT_MIN = 7105;
    /* Please see man pages for details 
    
    */
    const u16 TYPE_16BIT_GUARANTEED_INPUT_MAX = TYPE_16BIT_GUARANTEED_INPUT_MIN + TYPE_16BIT_GUARANTEED_RANGE;
    /* Please see man pages for details 
    
    */
    const s8 TYPE_SIGNED_8BIT_GUARANTEED_INPUT_MIN = -101;
    /* Please see man pages for details 
    
    */
    const s8 TYPE_SIGNED_8BIT_GUARANTEED_INPUT_MAX = TYPE_SIGNED_8BIT_GUARANTEED_INPUT_MIN + TYPE_8BIT_GUARANTEED_RANGE;
    /* Please see man pages for details 
    
    */
    const s16 TYPE_SIGNED_16BIT_GUARANTEED_INPUT_MIN = -25663;
    /* Please see man pages for details 
    
    */
    const s16 TYPE_SIGNED_16BIT_GUARANTEED_INPUT_MAX = TYPE_SIGNED_16BIT_GUARANTEED_INPUT_MIN + TYPE_16BIT_GUARANTEED_RANGE;

    /* Please see man pages for details 
    
           
    */
    const u8 AMP_GAIN_DEFAULT_VALUE = 43;

} // namespace CTR
} // namespace mic
} // namespace nn

#endif //NN_MIC_CTR_MIC_TYPES_H_
