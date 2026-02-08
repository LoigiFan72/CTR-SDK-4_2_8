/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dlp_FakeClient.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47174 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DLP_CTR_DLP_FAKE_CLIENT_H_
#define NN_DLP_CTR_DLP_FAKE_CLIENT_H_

#include <nn/dlp/CTR/dlp_Type.h>

#ifdef __cplusplus

namespace nn {
namespace dlp {
namespace CTR {

/*
    
 */
class FakeClient
{
public:
    FakeClient() {};
    ~FakeClient() {};


    /*
    

    

    

     */
        static size_t GetBufferSize(u8 scanNum);


    /*
      

                    
                    
                    

      
      
      
      

      
      
      
      
      
      
      
      

     */
        static nn::Result Initialize(u8 scanNum, nn::Handle eventHandle, void* pBuffer, const size_t bufferSize);


    /*
      

      
      

     */
        static nn::Result Finalize();


    /*
      

                    
                    
                    

      

      
      
      
     */
        static nn::Result GetEventDesc(EventDesc* pEventDesc);


    /*
      

                    
                    

      
      
      

      
      
      
      

    */
        static nn::Result StartScan(u32 uniqueId, u8 childIndex, const u8* pMac = NULL);


    /*
      

                    

      
      

    */
        static nn::Result StopScan();


    /*
      

                    
                    
                    

      
      

      
      
      
      

    */
        static nn::Result GetServerInfo(ServerInfo* pServerInfo, const u8* pMac);


    /*
      

      
      
      
      

      
      
      
      

    */
        static nn::Result GetTitleInfo(TitleInfo* pTitleInfo, const u8* pMac, u32 uniqueId, u8 childIndex);


    /*
      

                    
                    
                    
                    

      
      

      
      
      
      

    */
        static nn::Result GetTitleInfo(TitleInfo* pTitleInfo, bool isReset = false);


    /*
      

      

      
      
      
      

     */
        static nn::Result DeleteScanInfo(const u8* pMac);


    /*
      

      
      
      

      
      
      
      
      
      
      
      
      
      

    */
        static nn::Result StartFakeSession(const u8* pMac, u32 uniqueId, u8 childIndex);


    /*
      

      

      
      
      

    */
        static nn::Result GetPassphrase(char* pPassphrase);


    /*
      

      
      

    */
        static nn::Result StopFakeSession();


    /*
      

                    

      

      
      

     */
        static nn::Result  GetMyStatus(ClientStatus* pStatus);


    /*
      

      
      
      

      
      
      

    */
        static nn::Result GetConnectingNodes(u8* pNum, u16* pNodeIds, u16 size);


    /*
      

      
      

      
      
      
      

    */
        static nn::Result  GetNodeInfo(NodeInfo* pNodeInfo, u16 nodeId);


    /*
      

      

      
      

    */
        static nn::Result GetLinkLevel(nn::uds::LinkLevel* pLinkLevel);


    // (Unpublished functions)
    /*
      
      

      

      
      

     */
        static nn::Result GetChannels(bit16* pChannels);

        static nn::Result StartScan(const u8* pMac  = NULL);

private:
        static nn::Result StartScanInternal(bit16 channels, u32 uniqueId, u8 childIndex, const u8* pMac, bool useFilter);

};

} // namespace CTR
} // namespace dlp
} // namespace nn

#endif // __cplusplus
#endif  // ifndef NN_DLP_CTR_DLP_FAKE_CLIENT_H_
