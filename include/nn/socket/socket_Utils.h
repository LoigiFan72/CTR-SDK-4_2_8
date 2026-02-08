/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_Utils.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_UTILS_H_
#define NN_SOCKET_SOCKET_UTILS_H_

#include <nn/socket/socket_Types.h>
#include <nn/socket/socket_Const.h>

namespace nn {
namespace socket {
    /* Please see man pages for details 
      

      
     */

    /* Please see man pages for details 
      
      
      
      
    */
    s32 GetDefaultGateway(u8* pGateway);

    /* Please see man pages for details 
      
      
      
      
      
    */
    s32 GetPrimaryAddress(u8* pHostAddress, u8* pNetmask);

    /* Please see man pages for details 
      
      
      
      
      
    */
    s32 GetResolver(u8* pResolver1, u8* pResolver2);

    /* Please see man pages for details 
      

                    
                    

      
      
      
    */
    s32 GetMacAddress(u8 pMacAddress[ETH_ALEN]);
    
#ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
    /* Please see man pages for details 
      
      
      
    */
    void DumpRoutingTable(void);
#endif
    /*  

*/
}
}

#endif  // ifndef NN_SOCKET_SOCKET_UTILS_H_
