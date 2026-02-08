/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_Server.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48665 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_SERVER_H_
#define NN_DLP_CTR_DLP_SERVER_H_

#include <nn/dlp/CTR/dlp_Type.h>

#ifdef __cplusplus

namespace nn {
namespace dlp {
namespace CTR {

/*
    
 */
class Server
{
public:
    Server() {};
    ~Server() {};

    /*
      

      
      
                                        
      
                                        

      

     */
        static size_t GetBufferSize(u8 maxClientNum, size_t blockBufferSize = MIN_NETWORK_BLOCK_BUFFER_SIZE * 2, size_t blockBufferNum = MIN_NETWORK_BLOCK_BUFFER_NUM);


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
                        size_t blockBufferNum = MIN_NETWORK_BLOCK_BUFFER_NUM);

    /*
      

      
      

    */
        static nn::Result Finalize();


    /*
      

      

      
      

    */
        static nn::Result GetState(ServerState* pState);


    /*
      

                    
                    
                    

      

      
      
      

    */
        static nn::Result GetEventDesc(EventDesc* pEventDesc);


    /*
      

      
      

      
      
      
      
      

     */
        static nn::Result OpenSessions(bool isManualAccept = false, u8 channel = 0);


    /*
      

                    
                    
                    

      

      
      
      
      

     */
        static nn::Result AcceptClient(u16 nodeId);


    /*
      

                    

      

      
      
      
      

     */
        static nn::Result DisconnectClient(u16 nodeId);


    /*
      

                    
                    
                    
                    

      
      
      
      
      

    */
        static nn::Result StartDistribute();


    /*
      

                    
                    
                    
                    
                    

      
      
      
      

     */
        static nn::Result RebootAllClients(const char passpharase[] = NULL);


    /*
      

      
      

    */
        static nn::Result CloseSessions();


    /*
      

      
      
      

      
      
      

    */
        static nn::Result GetConnectingClients(u16* pNum, u16 clients[], u16 size);


    /*
      


      
      

      
      
      
      

    */
        static nn::Result  GetClientInfo(
                                NodeInfo*       pClientInfo,
                                u16             nodeId);


    /*
      

      
      

      
      
      
      

    */
        static nn::Result  GetClientState(
                                ClientState*     pClientState,
                                u16              nodeId);


    /*
      

      
      
      
      

      
      
      
      

    */
        static nn::Result  GetClientState(
                                ClientState*     pClientState,
                                size_t*          pTotalNum,
                                size_t*          pDownloadedNum,
                                u16              nodeId);


    /*
      

      

      
      

    */
        static nn::Result GetLinkLevel(nn::uds::LinkLevel* pLinkLevel);


    /*
      
      

                    
                    
                    
                    
                    

      
      
      
      
      
      
      

      
      
      
      
      
      
      
      
      
      
      
      

        */
            static nn::Result Initialize(
                            nn::Handle eventHandle,
                            u8 maxClientNum,
                            u8 childIndex,
                            void* pBuffer,
                            size_t bufferSize,
                            size_t blockBufferSize = MIN_NETWORK_BLOCK_BUFFER_SIZE * 2,
                            size_t blockBufferNum = MIN_NETWORK_BLOCK_BUFFER_NUM);
};

} // namespace CTR
} // namespace dlp
} // namespace nn


#endif // __cplusplus
#endif  // ifndef NN_DLP_CTR_DLP_SERVER_H_

