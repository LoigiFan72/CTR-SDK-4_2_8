/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     Test.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef NN_RDT_TEST_H_
#define NN_RDT_TEST_H_

#ifdef _WIN32
#include <CUnit.h>
#include <Basic.h>
#else
#define CU_ASSERT(exp)
// ↑ 
// Actually want to include as shown below.
// #include <nn/test/compatible/test_CunitAssert.h>
#endif

namespace nn { namespace rdt { namespace CTR {

/* Please see man pages for details 
    
*/

}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_TEST_H_
