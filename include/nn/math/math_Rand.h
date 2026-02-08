/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Rand.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47802 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_RAND_H_
#define NN_MATH_RAND_H_

#include <nn/math/math_Config.h>

namespace nn { 
namespace math {
/* Please see man pages for details 
    

    

    
    
*/
class RandomGenerator
{
public:
/* Please see man pages for details 
    

           
 */
    RandomGenerator(){}
/* Please see man pages for details 
    

    
 */
    RandomGenerator(u64 seed){this->SetSeed(seed);}
/* Please see man pages for details 
    
 */
    ~RandomGenerator(){}

/* Please see man pages for details 
    

    
 */
    void SetSeed(u64 seed);

/* Please see man pages for details 
    

    
    
 */
    u32 Generate(u32 max=0);
private:
    u64     m_x;    // Random number value
    u64     m_mul;  // Multiplier
    u64     m_add;  // The number to add
};

// This is a private class for maintaining compatibility with CTR-SDK 3.3
// Do not use it, because it may be removed in the future.
class RamdomGenerator
{
public:
    RamdomGenerator(){}
    RamdomGenerator(u64 seed){this->SetSeed(seed);}

    ~RamdomGenerator(){}

    void SetSeed(u64 seed);
    u32 Generate(u32 max=0);
private:
    u64     m_x;    // Random number value
    u64     m_mul;  // Multiplier
    u64     m_add;  // The number to add
};

}}

#endif //NN_MATH_RAND_H
