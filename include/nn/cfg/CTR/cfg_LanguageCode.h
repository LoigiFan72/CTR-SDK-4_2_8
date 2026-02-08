/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_LanguageCode.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_LANGUAGE_CODE_H_
#define NN_CFG_CTR_CFG_LANGUAGE_CODE_H_

namespace nn {
namespace cfg {
namespace CTR {

/* Please see man pages for details 
    
*/
enum CfgLanguageCode
{
    CFG_LANGUAGE_JAPANESE      = 0,            //
    CFG_LANGUAGE_ENGLISH       = 1,            //
    CFG_LANGUAGE_FRENCH        = 2,            //
    CFG_LANGUAGE_GERMAN        = 3,            //
    CFG_LANGUAGE_ITALIAN       = 4,            //
    CFG_LANGUAGE_SPANISH       = 5,            //
    CFG_LANGUAGE_SIMP_CHINESE  = 6,            //
    CFG_LANGUAGE_KOREAN        = 7,            //
    CFG_LANGUAGE_DUTCH         = 8,            //
    CFG_LANGUAGE_PORTUGUESE    = 9,            //
    CFG_LANGUAGE_RUSSIAN       = 10,           //
    CFG_LANGUAGE_TRAD_CHINESE  = 11,           //
    CFG_LANGUAGE_CODE_MAX
};

} // end of namespace CTR
} // end of namespace cfg
} // end of namespace nn

#endif      // NN_CFG_CTR_CFG_LANGUAGE_CODE_H_
