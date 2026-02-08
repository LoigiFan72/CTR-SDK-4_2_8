/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Matrix22.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Matrix22.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Matrix22.ipp>
#endif

namespace nn { namespace math {

/* ------------------------------------------------------------------------
        MTX22
   ------------------------------------------------------------------------ */

/*!--------------------------------------------------------------------------*
  Name:         MTX22::Report

  

  
  

  
 *---------------------------------------------------------------------------*/
void
MTX22::Report(bool bNewline, const char* name) const
{
    if (name)
        NN_MATH_REPORT("%s", name);
    else
        NN_MATH_REPORT("MTX22");

    NN_MATH_REPORT(     "<%f, %f\n",  f._00, f._01 );
    NN_MATH_REPORT("      %f, %f>\n", f._10, f._11 );

    if (bNewline)
        NN_MATH_REPORT("\n");
}

}  // namespace math
}  // namespace nn
