/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     news_UserTypes.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_NEWS_CTR_USER_USERTYPES_H_
#define NN_NEWS_CTR_USER_USERTYPES_H_

#include <nn/types.h>

namespace nn {
namespace news {
namespace CTR {

/*
  Notification library constants.
 */
static const int SUBJECT_LEN             = 32;    //
static const int MESSAGE_LEN             = 3000;  //
static const int PICTURE_SIZE            = 51200; //
static const int MESSAGE_URL_URL_SIZE    = 1024;  //

/* Please see man pages for details 
  
 */
enum TypeFlag
{
    TYPE_FLAG_NINTENDO   = 0,           //
    TYPE_FLAG_BOSS       = 1,           //
    TYPE_FLAG_HOMEMENU   = 2,           //
    TYPE_FLAG_USER       = 3,           //
    TYPE_FLAG_RESERVED   = 4,           //
    TYPE_FLAG_CEC        = 5,           //
    TYPE_FLAG_MAX
};

/* Please see man pages for details 
  
 */
struct JumpArg
{
    u8 version;                         //
    u8 reserved1[2];                    //
    u8 typeFlag;                        //
    u8 reserved2[4];                    //
    u32 serialId;                       //
    u32 dataVersion;                    //
    u64 jumpParam;                      //
};


} // end of namespace CTR
} // end of namespace news
} // end of namespace nn

#endif /* NN_NEWS_CTR_USER_USERTYPES_H_ */
