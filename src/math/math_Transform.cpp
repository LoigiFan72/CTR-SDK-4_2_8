/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Transform.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Transform.h>

namespace nn { namespace math {

/* ------------------------------------------------------------------------
        Functions used for making simple reports
   ------------------------------------------------------------------------ */

/*
  
  
  
  
  
 


*/
void
Transform2::Report(bool bNewline, const char* name) const
{
    if (name) { NN_MATH_REPORT("%s", name); }
    else { NN_MATH_REPORT("Transform2\n"); }

    NN_MATH_REPORT("Scale    <%f, %f>\n", scale.x, scale.y);
    NN_MATH_REPORT("Rotate   <%f, %f>\n", rotate.x, rotate.y);
    NN_MATH_REPORT("Translate<%f, %f>\n", translate.x, translate.y);

    if (bNewline) { NN_MATH_REPORT("\n"); }
}

/*!--------------------------------------------------------------------------*
  Name:         Transform3::Report



  
 

 
 *---------------------------------------------------------------------------*/
void
Transform3::Report(bool bNewline, const char* name) const
{
    if (name) { NN_MATH_REPORT("%s", name); }
    else { NN_MATH_REPORT("Transform3\n"); }

    NN_MATH_REPORT("Scale    <%f, %f, %f>\n", scale.x, scale.y, scale.z);
    NN_MATH_REPORT("Rotate   <%f, %f, %f>\n", rotate.x, rotate.y, rotate.z);
    NN_MATH_REPORT("Translate<%f, %f, %f>\n", translate.x, translate.y, translate.z);

    if (bNewline) { NN_MATH_REPORT("\n"); }
}


}  // namespace math
}  // namespace nn
