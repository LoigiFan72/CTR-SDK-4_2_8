/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ndm_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NDM_CTR_TYPES_H_
#define NN_NDM_CTR_TYPES_H_

#include <nn/types.h>

#ifdef __cplusplus

namespace nn {
namespace ndm {
namespace CTR {

enum ExclusiveMode
{
    EM_NONE,                // Not mutex mode.
    EM_INFRA,               // Infrastructure communication.
    EM_LOCAL,               // Local communication. Also halt scheduler operation.
    EM_CEC,                 // StreetPass. (Limited to StreetPass protocol)
    EM_INTENT_CEC           // Communication for exchange of SteetPass data. (Does not limit protocol)
};

/* Please see man pages for details 
    
 */
enum DaemonName
{
    DN_CEC,                         //
    DN_BOSS,                        //
    DN_NIM,                         //
    DN_FRIENDS,                     //
    NUM_OF_DAEMONS
};

/* Please see man pages for details 
    
 */
enum DaemonMask
{
    DM_CEC      = 1 << DN_CEC,      //
    DM_BOSS     = 1 << DN_BOSS,     //
    DM_NIM      = 1 << DN_NIM,      //
    DM_FRIENDS  = 1 << DN_FRIENDS   //
};

const bit32 MASK_BACKGROUOND_DAEMONS        = DM_CEC | DM_BOSS | DM_NIM;
const bit32 MASK_ALL_DAEMONS                = DM_CEC | DM_BOSS | DM_NIM | DM_FRIENDS;
const bit32 MASK_DEFAULT_ENABLED_DAEMONS    = DM_CEC | DM_FRIENDS;

} // namespace CTR

using namespace CTR;

const bit32 CONTROL_MASK_DEFAULT    = MASK_BACKGROUOND_DAEMONS;
const bit32 CONTROL_MASK_ALL        = MASK_ALL_DAEMONS;
const bit32 ENABLED_MASK_DEFAULT    = MASK_DEFAULT_ENABLED_DAEMONS;

}
}

#endif // __cplusplus

#endif // NN_NDM_CTR_TYPES_H_
