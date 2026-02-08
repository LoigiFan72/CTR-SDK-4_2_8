/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_ServerWithName.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_SERVER_WITH_NAME_H_
#define NN_DLP_CTR_DLP_SERVER_WITH_NAME_H_

#include <nn/dlp/CTR/dlp_Type.h>
#include <nn/cfg.h>

#ifdef __cplusplus

namespace nn {
namespace dlp {
namespace CTR {

/*
    
 */
class ServerWithName : public Server
{
public:
    ServerWithName() {};
    ~ServerWithName() {};


    /*
      

                    
                    
                    
                    
                    
                    
                    
                    
                    

      
      
      
      
      
      
      
      
      

      
      
      
      
      
      
      
      
      
      
      
      

    */
        static nn::Result Initialize(
                        bool* pNotice,
                        nn::Handle eventHandle,
                        u8 maxClientNum,
                        u8 childIndex,
                        void* pBuffer,
                        size_t bufferSize,
                        size_t blockBufferSize = MIN_NETWORK_BLOCK_BUFFER_SIZE * 2,
                        size_t blockBufferNum = MIN_NETWORK_BLOCK_BUFFER_NUM,
                        nn::cfg::UserName* pUserName = NULL );


    /*
      
      

                    
                    
                    
                    
                    
                    
                    
                    
                    

      
      
      
      
      
      
      
      

      
      
      
      
      
      
      
      
      
      
      

    */
        static nn::Result Initialize(
                        nn::Handle eventHandle,
                        u8 maxClientNum,
                        u8 childIndex,
                        void* pBuffer,
                        size_t bufferSize,
                        size_t blockBufferSize = MIN_NETWORK_BLOCK_BUFFER_SIZE * 2,
                        size_t blockBufferNum = MIN_NETWORK_BLOCK_BUFFER_NUM,
                        nn::cfg::UserName* pUserName = NULL );

};

} // namespace CTR
} // namespace dlp
} // namespace nn


#endif // __cplusplus
#endif  // ifndef NN_DLP_CTR_DLP_SERVER_WITH_NAME_H_

