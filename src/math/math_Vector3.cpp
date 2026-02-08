/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector3.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <cmath>
#include <nn/math/math_Vector3.h>

#if !defined(NN_MATH_AS_INLINE)
#include <nn/math/inline/math_Vector3.ipp>
#endif

namespace nn { namespace math {

/* ------------------------------------------------------------------------
        VEC3
   ------------------------------------------------------------------------ */

/*!--------------------------------------------------------------------------*
  Name:         VEC3::Report

  

  
  

 
 *---------------------------------------------------------------------------*/
void
VEC3::Report(bool bNewline, const char* name) const
{
    if (name) { NN_MATH_REPORT("%s", name); }
    else { NN_MATH_REPORT("VEC3"); }

    NN_MATH_REPORT("<%f, %f, %f>", x, y, z);
    
    if (bNewline) { NN_MATH_REPORT("\n"); }
}

}  // namespace math
}  // namespace nn
