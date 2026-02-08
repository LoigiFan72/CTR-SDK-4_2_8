/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_RegionCode.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_REGION_CODE_H_
#define NN_CFG_CTR_CFG_REGION_CODE_H_

namespace nn {
namespace cfg {
namespace CTR {

/* Please see man pages for details 
    
*/
enum CfgRegionCode
{
    CFG_REGION_JAPAN     = 0,   //
    CFG_REGION_AMERICA   = 1,   //
    CFG_REGION_EUROPE    = 2,   //
    CFG_REGION_AUSTRALIA = 3,   //
    CFG_REGION_CHINA     = 4,   //
    CFG_REGION_KOREA     = 5,   //
    CFG_REGION_TAIWAN    = 6,   //
    CFG_REGION_MAX
};

} // end of namespace CTR
} // end of namespace cfg
} // end of namespace nn

#endif      // NN_CFG_CTR_CFG_REGION_CODE_H_
