/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_DlpVersion.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_DLP_VERSION_H_
#define NN_DLP_CTR_DLP_DLP_VERSION_H_

#include <nn/types.h>


namespace nn {
namespace dlp {
namespace CTR {

#define NN_DLP_DEFINE_DLP_VERSION(major, minor)  ((bit16)major<<8 | (bit16)minor&0x00FF)

const bit16   DLP_VERSION = NN_DLP_DEFINE_DLP_VERSION(1, 1);

/*
 *  Ver             :  1.0
 *  CTR-SDK Ver     :  0.14.23, 1.*, 2.0
 *                     Launch version
 *
 *  Ver             :  1.1
 *  CTR-SDK Ver     :  3.0
 *                     Added CUP version information to the advertise packet (AdvertiseBody0)
 *                     Added a DUP toggle flag to the advertise packet (AdvertiseBody0)

 */
} // namespace CTR
} // namespace dlp
} // namespace nn

#endif  // ifndef NN_DLP_CTR_DLP_DLP_VERSION_H_
