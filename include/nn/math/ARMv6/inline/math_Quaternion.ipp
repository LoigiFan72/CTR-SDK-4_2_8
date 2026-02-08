/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Quaternion.ipp

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
/* Please see man pages for details 
    
    
*/

#define NN_QUAT_EPSILON        0.00001F


/*
  

  
  
  

  
 */
NN_MATH_INLINE QUAT*
QUATMultC(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2)
{
    QUAT * __restrict pDst;
    QUAT  tmp;

    NN_NULL_ASSERT( pOut  );
    NN_NULL_ASSERT( q1  );
    NN_NULL_ASSERT( q2 );

    if ( q1 == pOut || q2 == pOut )
    {
        pDst = &tmp;
    }
    else
    {
        pDst = pOut;
    }

    pDst->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
    pDst->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
    pDst->y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z;
    pDst->z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;
    
    if ( pDst == &tmp )
    {
        *pOut = tmp;
    }
    
    return pOut;
}
NN_MATH_INLINE QUAT*
QUATMultC_FAST(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2)
{
    register f32 x, y, z, w;
    register f32 q1x, q1y, q1z, q1w;
    register f32 q2x, q2y, q2z, q2w;

    q1x = q1->x;
    q1y = q1->y;
    q1z = q1->z;
    q1w = q1->w;

    q2x = q2->x;
    q2y = q2->y;
    q2z = q2->z;
    q2w = q2->w;

    x = q1w * q2x + q1x * q2w + q1y * q2z - q1z * q2y;
    y = q1w * q2y + q1y * q2w + q1z * q2x - q1x * q2z;
    z = q1w * q2z + q1z * q2w + q1x * q2y - q1y * q2x;
    w = q1w * q2w - q1x * q2x - q1y * q2y - q1z * q2z;

    pOut->x = x;
    pOut->y = y;
    pOut->z = z;
    pOut->w = w;

    return pOut;

}


/*
  

  
  

  
 */
NN_MATH_INLINE QUAT*
QUATNormalizeC(QUAT* pOut, const QUAT* __restrict q)
{
    f32 mag;

    NN_NULL_ASSERT( q );
    NN_NULL_ASSERT( pOut );

    mag = (q->x * q->x) + (q->y * q->y) + (q->z * q->z) + (q->w * q->w);

    if ( mag >= NN_QUAT_EPSILON )
    {
        mag = 1.0F / ::std::sqrtf(mag);
        
        pOut->x = q->x * mag;
        pOut->y = q->y * mag;
        pOut->z = q->z * mag;
        pOut->w = q->w * mag;
    }
    else
    {
        pOut->x = pOut->y = pOut->z = pOut->w = 0.0F;
    }
    
    return pOut;
}

NN_MATH_INLINE QUAT*
QUATNormalizeC_FAST(QUAT* pOut, const QUAT* __restrict q)
{
    f32 mag;

    NN_NULL_ASSERT( q );
    NN_NULL_ASSERT( pOut );

    register f32 x, y, z, w;

    x = q->x;
    y = q->y;
    z = q->z;
    w = q->w;

    mag = (x * x) + (y * y) + (z * z) + (w * w);

    if ( mag >= NN_QUAT_EPSILON )
    {
        mag = 1.0F / ::std::sqrtf(mag);
        
        x = x * mag;
        y = y * mag;
        z = z * mag;
        w = w * mag;

        pOut->x = x;
        pOut->y = y;
        pOut->z = z;
        pOut->w = w;

    }
    else
    {
        pOut->x = pOut->y = pOut->z = pOut->w = 0.0F;
    }
    
    return pOut;
}

/*
  

  
  

  
 */
NN_MATH_INLINE QUAT*
QUATInverseC(QUAT* pOut, const QUAT* __restrict q)
{
    f32 mag, norminv;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q );

    mag = ( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );

    if ( mag == 0.0f )
    {
        mag = 1.0f;
    }

    // [Inverse] = [Conjugate] / [Magnitude]
    norminv = 1.0f / mag;
    pOut->x = -q->x * norminv;
    pOut->y = -q->y * norminv;
    pOut->z = -q->z * norminv;
    pOut->w =  q->w * norminv;
    
    return pOut;
}
NN_MATH_INLINE QUAT*
QUATInverseC_FAST(QUAT* pOut, const QUAT* __restrict q)
{
    f32 mag, norminv;

    NN_NULL_ASSERT( pOut );
    NN_NULL_ASSERT( q );
    
    register f32 x, y, z, w;
    
    x = q->x;
    y = q->y;
    z = q->z;
    w = q->w;

    mag = ( x * x + y * y + z * z + w * w );

    if ( mag == 0.0f )
    {
        mag = 1.0f;
    }

    // [Inverse] = [Conjugate] / [Magnitude]
    norminv = 1.0f / mag;
    x = -x * norminv;
    y = -y * norminv;
    z = -z * norminv;
    w =  w * norminv;

    pOut->x = x;
    pOut->y = y;
    pOut->z = z;
    pOut->w = w;

    return pOut;
}
/*  

*/
}  //namespace ARMv6
}  // namespace math
}  // namespace nn

