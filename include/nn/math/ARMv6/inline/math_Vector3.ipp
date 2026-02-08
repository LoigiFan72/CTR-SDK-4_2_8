/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Vector3.ipp

  Copyright (C)2009-2010 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 13623 $
 *---------------------------------------------------------------------------*/

#include <cmath>

namespace nn { 
namespace math {
namespace ARMv6 {
/* ------------------------------------------------------------------------
        VEC3
   ------------------------------------------------------------------------ */

/* Please see man pages for details 
    
    
*/

/*
  

  
  

  
 */
NN_MATH_INLINE VEC3*
VEC3NormalizeC(VEC3* pOut, const VEC3* p)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(p);

    f32 mag = (p->x * p->x) + (p->y * p->y) + (p->z * p->z);

    NN_ASSERTMSG(mag != 0, "MATHNormalize3():  zero magnitude vector");

    mag = 1.0f / ::std::sqrtf(mag);

    pOut->x = p->x * mag;
    pOut->y = p->y * mag;
    pOut->z = p->z * mag;
    
    return pOut;
}


NN_MATH_INLINE VEC3*
VEC3NormalizeC_FAST(VEC3* pOut, const VEC3* p)
{
    NN_NULL_ASSERT(pOut);
    NN_NULL_ASSERT(p);

    register f32 x, y, z, mag;
    
    x = p->x;
    y = p->y;
    z = p->z;
    
    mag = (x * x) + (y * y) + (z * z);

    NN_ASSERTMSG(mag != 0, "MATHNormalize3():  zero magnitude vector");

    mag = 1.0f / ::std::sqrtf(mag);
    
    x *= mag;
    y *= mag;
    z *= mag;

    pOut->x = x;
    pOut->y = y;
    pOut->z = z;

    return pOut;
}


/*  

*/
}  // namespcae ARMv6
}  // namespace math
}  // namespace nn
