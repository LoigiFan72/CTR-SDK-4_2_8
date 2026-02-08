/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     pl_GameCoin.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_PL_CTR_PL_GAMECOIN_H_
#define NN_PL_CTR_PL_GAMECOIN_H_

#include <nn/types.h>
#include <nn/Result.h>

#ifdef  __cplusplus

namespace nn
{
namespace pl
{
namespace CTR
{

/* Please see man pages for details 
  
  
*/


/* Please see man pages for details 
    
*/
const u16   MAX_GAME_COIN_COUNT     = 300;

/* Please see man pages for details 
    

                
                
                
                

    
*/
void InitializeGameCoin();

/* Please see man pages for details 
    

    
*/
void FinalizeGameCoin();

/* Please see man pages for details 
    

                
                
                

    
    
*/
Result GetGameCoinCount(u16* pCount);

/* Please see man pages for details 
    

                

                
                

                
                
                
                

    
    
    
*/
Result UseGameCoin(u16* pCount, u16 useCount);


/*  

*/

}}}

#endif // __cplusplus

#endif // ifndef NN_PL_CTR_PL_GAMECOIN_H_
