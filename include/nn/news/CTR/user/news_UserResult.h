/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     news_UserResult.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_NEWS_CTR_USER_USERRESULT_H_
#define NN_NEWS_CTR_USER_USERRESULT_H_

#include <nn/Result.h>

namespace nn {
namespace news {
namespace CTR {
namespace user {

enum Description
{
    DESCRIPTION_NONE,
    DESCRIPTION_INVALID_SUBJECT_SIZE,  //
    DESCRIPTION_INVALID_MESSAGE_SIZE,  //
    DESCRIPTION_INVALID_PICTURE_SIZE,  //
    DESCRIPTION_INVALID_PICTURE,       //
    DESCRIPTION_MAX
};

/* Please see man pages for details 
  
  
  
*/
NN_DEFINE_RESULT_CONST(
    ResultInvalidSubjectSize,
    Result::LEVEL_PERMANENT,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_NEWS,
    DESCRIPTION_INVALID_SUBJECT_SIZE
);

/* Please see man pages for details 
  
  
  
*/
NN_DEFINE_RESULT_CONST(
    ResultInvalidMessageSize,
    Result::LEVEL_PERMANENT,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_NEWS,
    DESCRIPTION_INVALID_MESSAGE_SIZE
);

/* Please see man pages for details 
  
  
  
*/
NN_DEFINE_RESULT_CONST(
    ResultInvalidPictureSize,
    Result::LEVEL_PERMANENT,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_NEWS,
    DESCRIPTION_INVALID_PICTURE_SIZE
);

/* Please see man pages for details 
  
  
  
*/
NN_DEFINE_RESULT_CONST(
    ResultInvalidPicture,
    Result::LEVEL_PERMANENT,
    Result::SUMMARY_INVALID_ARGUMENT,
    Result::MODULE_NN_NEWS,
    DESCRIPTION_INVALID_PICTURE
);

} // end of namespace user
} // end of namespace CTR
} // end of namespace news
} // end of namespace nn

#endif /* NN_NEWS_CTR_USER_USERRESULT_H_ */

