/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Equation.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_EQUATION_H_
#define NN_MATH_EQUATION_H_

#include <nn/math/math_Config.h>


namespace nn { namespace math {


int SolveEquation2(f32* root, f32 a, f32 b, f32 c);
int SolveEquation3(f32* root, f32 a, f32 b, f32 c, f32 d);
int SolveEquation4(f32* root, f32 a, f32 b, f32 c, f32 d, f32 e);


}}  // nn::math

/* NN_MATH_EQUATION_H_ */
#endif
