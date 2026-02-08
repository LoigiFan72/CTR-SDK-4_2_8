/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ngc.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47308 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NGC_H_
#define NN_NGC_H_

/* Please see man pages for details 
  
         
         
         
 */
#define NN_NGC_MAX_WORD_LENGTH              64

/* Please see man pages for details 
  
 */
#define NN_NGC_MAX_WORD_NUM                 16


/* Please see man pages for details 
 
 */
#define NN_NGC_MAX_TEXT_LENGTH              512


/* Please see man pages for details 
  
  
*/
/* Please see man pages for details 
  
  
         
*/
#if defined( NN_PLATFORM_CTR ) && defined( __cplusplus )
#   include <nn/ngc/CTR/ngc_Api.h>
#   include <nn/ngc/CTR/ngc_ProfanityFilterPatternList.h>
#   include <nn/ngc/CTR/ngc_ProfanityFilterBase.h>
#   include <nn/ngc/CTR/ngc_ProfanityFilter.h>

    namespace nn
    {
        namespace ngc
        {
            using namespace nn::ngc::CTR;
        }
    }
    
#else
#   error unknown platform
#endif


#if defined( __cplusplus )
    namespace nn
    {
        namespace ngc
        {
            /* Please see man pages for details 
              
                     
                     
                     
             */
            const u8 MAX_WORD_LENGTH    = NN_NGC_MAX_WORD_LENGTH;
            
            /* Please see man pages for details 
              
             */
            const u8 MAX_WORD_NUM       = NN_NGC_MAX_WORD_NUM;
            
            /* Please see man pages for details 
             
             */
            const u16 MAX_TEXT_LENGTH   = NN_NGC_MAX_TEXT_LENGTH;
        }
    }
#endif


#endif  // NN_NGC_H_
