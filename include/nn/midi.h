/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     midi.h

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

#ifndef NN_MIDI_H_
#define NN_MIDI_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
           
*/

#if defined(NN_PLATFORM_CTR)
    #include <nn/midi/CTR/midi_Api.h>
    #include <nn/midi/midi_Result.h>
    
#ifdef  __cplusplus
    namespace nn {
        namespace midi {
            using namespace nn::midi::CTR;
        }
    }
#endif // __cplusplus

#else
    #error no platform selected
#endif

#endif  // ifndef NN_MIDI_H_
