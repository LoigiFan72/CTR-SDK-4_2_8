/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_Sound.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_SOUND_H_
#define NN_CFG_CTR_CFG_SOUND_H_

namespace nn {
namespace cfg {
namespace CTR {

/* Please see man pages for details 
    
*/
enum CfgSoundOutputMode
{
    CFG_SOUND_OUTPUT_MODE_MONO,     //
    CFG_SOUND_OUTPUT_MODE_STEREO,   //
    CFG_SOUND_OUTPUT_MODE_SURROUND  //
};

} // end of namespace CTR
} // end of namespace cfg
} // end of namespace nn

#endif      // NN_CFG_CTR_CFG_SOUND_H_
