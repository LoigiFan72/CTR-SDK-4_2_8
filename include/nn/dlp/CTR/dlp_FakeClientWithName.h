/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_FakeClientWithName.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_FAKE_CLIENT_WITH_NAME_H_
#define NN_DLP_CTR_DLP_FAKE_CLIENT_WITH_NAME_H_

#include <nn/dlp/CTR/dlp_Type.h>
#include <nn/cfg.h>

#ifdef __cplusplus

namespace nn {
namespace dlp {
namespace CTR {

/*
    
 */
class FakeClientWithName : public FakeClient
{
public:
    FakeClientWithName() {};
    ~FakeClientWithName() {};


    /*
      

                    
                    
                    
                    
                    
                    
                    
                    
                    

      
      
      
      
      

      
      
      
      
      
      
      
      

     */
        static nn::Result Initialize(u8 scanNum, nn::Handle eventHandle, void* pBuffer, const size_t bufferSize, nn::cfg::UserName* pUserName = NULL );

};

} // namespace CTR
} // namespace dlp
} // namespace nn

#endif // __cplusplus
#endif  // ifndef NN_DLP_CTR_DLP_FAKE_CLIENT_WIHT_NAME_H_
