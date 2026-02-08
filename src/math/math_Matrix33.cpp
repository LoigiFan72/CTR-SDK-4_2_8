/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix33.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Matrix33.h>


#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix33.ipp>
#include <nn/math/ARMv6/inline/math_Matrix33.ipp>
#endif


namespace nn { namespace math {

/* ------------------------------------------------------------------------
        MTX33
   ------------------------------------------------------------------------ */

/*!--------------------------------------------------------------------------*
  Name:         MTX33::Report

  

  
 

 
 *---------------------------------------------------------------------------*/
void
MTX33::Report(bool bNewline, const char* name) const
{
    if (name)
        NN_MATH_REPORT("%s", name);
    else
        NN_MATH_REPORT("MTX33");

    NN_MATH_REPORT(     "<%f, %f, %f\n",  f._00, f._01, f._02);
    NN_MATH_REPORT("      %f, %f, %f\n",  f._10, f._11, f._12);
    NN_MATH_REPORT("      %f, %f, %f>\n", f._20, f._21, f._22);

    if (bNewline)
        NN_MATH_REPORT("\n");
}

}  // namespace math
}  // namespace nn
