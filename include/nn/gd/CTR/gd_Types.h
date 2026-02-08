/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Types.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_TYPES_H_
#define NN_GD_CTR_GD_TYPES_H_

// Doxygen definition

/* Please see man pages for details */
#define ENGLISH  1
/* Please see man pages for details */
#define JAPANESE 2
/* Please see man pages for details */
#define NN_GD_DOCUMENT_TYPE JAPANESE

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
*/
#else
/* Please see man pages for details 
    
*/
#endif
#include <nn/types.h>

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
enum gdBoolEnum
{
    GD_FALSE = 0,
    GD_TRUE = 1
};

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
typedef enum gdBoolEnum gdBool;

#endif // NN_GD_CTR_GD_TYPES_H_
