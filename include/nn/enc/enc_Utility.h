/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     enc_Utility.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ENC_ENC_UTILITY_H_
#define NN_ENC_ENC_UTILITY_H_

#include <nn/enc/enc_Result.h>
#include <nn/enc/enc_Types.h>

#ifdef __cplusplus

namespace nn { namespace enc { namespace detail {

Result CheckParameters(
    bool dst, s32 *pGivenDstSize, s32 *pDstSize, bool *pWriteMode,
    bool src, s32 *pGivenSrcSize, s32 *pSrcSize, bool *pReadCheck
);

s32 CheckBreakType(u32 cur, u32 next);

s32 WriteBreakType(u8* pDst, u32 step, BreakType brType, bool writeMode);

}}}

#endif // __cplusplus

#endif /* NN_ENC_ENC_UTILITY_H_ */
