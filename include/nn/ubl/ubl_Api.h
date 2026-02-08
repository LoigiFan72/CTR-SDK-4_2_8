/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ubl_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_UBL_UBL_API_H_
#define NN_UBL_UBL_API_H_

#include <nn/fnd.h>
#include <nn/Result.h>

namespace nn {
namespace ubl {

/*=======================================================================*
    Function Prototype Declarations
 *=======================================================================*/

/*
  
                

  
 */
nn::Result Initialize(void);

/*
  
 */
void Finalize(void);

/*
  
  
                
                
                

  
 */
nn::Result InitializeWithoutGlobalBlackList(void);

/*
  
  

  

  
 */
nn::Result Reload(bool enableGlobalBlackList = false);

/*
  

  
 */
nn::Result Clear(void);

/*
  
  
                
                

  
  
  

  
 */
bool IsExist(u64 authorId , u32 titleId , u64 dataId);

/*
  

  
 */
u32 GetTotalLocalUser(void);

/*
  
                
                

  
 */
u64 GetUserId(void);

/*
  

  
  
  
 */
bool GetUserName(wchar_t* name);

/*
  

  
  

  
 */
u64 GetHashValue(const void* inputBuffer , size_t inputSize);

/*
  
  
                
                
                

  
  

  
 */
nn::Result Entry(u64 id, const nn::fnd::DateTime* dt);

} // end of namespace ubl
} // end of namespace nn

#endif /* NN_UBL_UBL_API_H_ */
