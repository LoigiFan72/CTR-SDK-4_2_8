/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_H_
#define NN_SND_H_

/* Please see man pages for details 
    
*/

/* Please see man pages for details 
    
    
*/

#if defined(NN_PLATFORM_CTR)
    #include <nn/types.h>
    #include <nn/Result.h>
    #include <nn/dsp.h>

    #include <nn/snd/CTR/snd_Result.h>
    #include <nn/snd/CTR/Common/snd_Types.h>
    #include <nn/snd/CTR/Common/snd_Adpcm.h>
    #include <nn/snd/CTR/Common/snd_Const.h>
    #include <nn/snd/CTR/Common/snd_Bcwav.h>
    #include <nn/snd/CTR/MPCore/snd_Api.h>
    #include <nn/snd/CTR/MPCore/snd_Voice.h>
    #include <nn/snd/CTR/MPCore/snd_OutputCapture.h>
    #include <nn/snd/CTR/MPCore/snd_FxDelay.h>
    #include <nn/snd/CTR/MPCore/snd_FxReverb.h>
    #include <nn/snd/CTR/MPCore/snd_DspFxDelay.h>
    #include <nn/snd/CTR/MPCore/snd_DspFxReverb.h>
    namespace nn {
        namespace snd {
            using namespace nn::snd::CTR;
        }
    }
#else
    #error no platform selected
#endif


#endif  // ifndef NN_SND_H_
