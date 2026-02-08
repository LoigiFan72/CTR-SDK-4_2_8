/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     http_Common.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HTTP_HTTP_COMMON_H_
#define NN_HTTP_HTTP_COMMON_H_

#include <nn/Result.h>

#ifdef __cplusplus

#include <nn/types.h>

namespace nn {
namespace http {
    //----------------------------------------
    //
    //

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    

      
      
      
      
      
      
      
      
    */
    Result Initialize(uptr bufferAddress = 0, size_t bufferSize = 0);

    /* Please see man pages for details 
      
      
      
      
      
    */
    Result Finalize(void);

    /* Please see man pages for details 
      
      
      
      
      
    */
    Result ClearDnsCaches(void);

    //

    namespace {
        /* Please see man pages for details 
         
         */
        const char PORT_NAME_CONNECTION[]        = "http:C";

    }
} // end of namespace http
} // end of namespace nn

#endif /*__cplusplus*/

// Below is the C declaration

/* Please see man pages for details 
  
  
*/

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnhttpInitialize(uptr bufferAddress = 0, size_t bufferSize = 0);

/* Please see man pages for details 
  
*/
NN_EXTERN_C nnResult nnhttpFinalize(void);

/*  

*/

#endif /* NN_HTTP_HTTP_COMMON_H_ */
