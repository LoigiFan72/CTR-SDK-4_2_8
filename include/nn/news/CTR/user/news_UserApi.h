/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     news_UserApi.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_NEWS_CTR_NEWS_USER_USERAPI_H_
#define NN_NEWS_CTR_NEWS_USER_USERAPI_H_

#include <nn/fnd.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/news/CTR/user/news_UserTypes.h>

namespace nn {
namespace news {
namespace CTR {
namespace user {

/* Please see man pages for details 
  
  
*/
Result
Initialize();

/* Please see man pages for details 
  
  
*/
Result
Finalize();

/* Please see man pages for details 
  
  
  
  
  
  
  
  
  
*/
Result
PostNews(
    const wchar_t* subject,
    const wchar_t* message,
    const u8* picture = NULL,
    size_t pictureSize = 0,
    u32 serialId = 0,
    u32 dataVersion = 0,
    u64 jumpParam = 0
    );

/* Please see man pages for details 
  
  
  
  
*/
size_t
GetWorkBufferSizeForNewsUrl(
    const wchar_t* message,
    const u8* url
    );

/* Please see man pages for details 
  
  
  
  
  
  
  
  
  
  
  
*/
Result
PostNewsUrl(
    const wchar_t* subject,
    const wchar_t* message,
    const u8* url,
    u8* workBuf,
    const u8* picture = NULL,
    size_t pictureSize = 0,
    u32 serialId = 0,
    u32 dataVersion = 0,
    u64 jumpParam = 0
    );


/* Please see man pages for details 
  
                
                
                
  
  
*/
bool IsFromNewsList( JumpArg* jumpArg );

}
}
}
}

#endif /* NN_NEWS_CTR_NEWS_USER_USERAPI_H_ */
