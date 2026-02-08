/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47665 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_H_
#define NN_MATH_H_

#include <nn/config.h>

/* Please see man pages for details 
    
*/

#ifdef __cplusplus
    #if NN_PLATFORM_USE_FP
        #include <nn/math/math_Config.h>
        #include <nn/math/math_Types.h>
        #include <nn/math/math_Constant.h>
        #include <nn/math/math_Arithmetic.h>
        #include <nn/math/math_Triangular.h>
        #include <nn/math/math_Equation.h>
        #include <nn/math/math_Rand.h>
        #include <nn/math/math_MersenneTwister.h>
        #include <nn/math/math_TinyMt.h>
    #endif  // if NN_PLATFORM_USE_FP

    #include <nn/math/math_Utility.h>
#endif  // ifdef __cplusplus

/* NN_MATH_H_ */
#endif
