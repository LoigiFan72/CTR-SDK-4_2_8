/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     voicesel.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_VOICESEL_H_
#define NN_VOICESEL_H_

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
                
*/
/* Please see man pages for details 
    

    
  
*/
#if defined(NN_PLATFORM_CTR)
    #include <nn/voicesel/CTR/voicesel_Api.h>

    namespace nn {
        namespace voicesel {
            using namespace nn::voicesel::CTR;
        }
    }

#else
    #error no platform selected
#endif

/*  

*/

#endif  /* NN_VOICESEL_H_ */
