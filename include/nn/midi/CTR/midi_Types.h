/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     midi_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIDI_CTR_MIDI_TYPES_H_
#define NN_MIDI_CTR_MIDI_TYPES_H_

/* Please see man pages for details 
    
    
*/

#include <nn/types.h>

namespace nn {
namespace midi {
namespace CTR {

#if !defined(NN_HARDWARE_CTR_LEGACY)
    const int MIDI_RECV_BUFFER_MAX = 1024 * 2;
#else
    const int MIDI_RECV_BUFFER_MAX = 4;
#endif

/* Please see man pages for details 
    

*/
struct DeviceInfo
{
    bit8    id;         //
    bit8    version;    //
    bit8    revision;   //
};

}
}
}


#endif  // ifndef NN_MIDI_CTR_MIDI_TYPES_H_
