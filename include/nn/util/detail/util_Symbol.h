/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Symbol.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47508 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_UTIL_DETAIL_UTIL_SYMBOL_H_
#define NN_UTIL_DETAIL_UTIL_SYMBOL_H_


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
#define NN_UTIL_REFER_SYMBOL(symbol)    nnutilReferSymbol_(NULL, &(symbol))

//

//


#ifdef __cplusplus
extern "C" {
#endif

    void nnutilReferSymbol_(const void* sym, ...);

#ifdef __cplusplus
} // extern "C"
#endif


#endif  // ifdef NN_UTIL_DETAIL_UTIL_SYMBOL_H_
