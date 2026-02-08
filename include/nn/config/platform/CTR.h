/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     CTR.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_CONFIG_PLATFORM_CTR_H_
#define NN_CONFIG_PLATFORM_CTR_H_



//
//

//
//

//---------------------------------------------------------------------------
//
//
//
//
//
//
//---------------------------------------------------------------------------
#define NN_ENDIAN               NN_ENDIAN_VALUE_LITTLE


//---------------------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------------------
#define NN_ENDIAN_VALUE_BIG     'B'

//---------------------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------------------
#define NN_ENDIAN_VALUE_LITTLE  'L'

//

//


#if     defined(NN_PROCESSOR_ARM_V6)
    #define NN_PLATFORM_HAS_MMU             1
    #define NN_PLATFORM_USE_FP              1
    #define NN_PLATFORM_HAS_16BIT_LL_SC     1
#else
    #define NN_PLATFORM_HAS_MMU             0
    #define NN_PLATFORM_USE_FP              0
    #define NN_PLATFORM_HAS_16BIT_LL_SC     0
#endif


/* NN_CONFIG_PLATFORM_CTR_H_ */
#endif
