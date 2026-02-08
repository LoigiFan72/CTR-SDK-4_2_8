/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ir_Communicator.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_IR_CTR_COMMUNICATIONAPI_H_
#define NN_IR_CTR_COMMUNICATIONAPI_H_

#include <nn/types.h>
#include <nn/fnd.h>
#include <nn/Result.h>
#include <nn/ir/CTR/ir_Types.h>

namespace nn {
namespace ir {
namespace CTR{

/*
    
 */
class Communicator
{
private:
    Communicator() {};
    ~Communicator() {};


public:
    /* Please see man pages for details 
    
    
    */
    static const size_t IR_PASSPHRASE_LENGTH_MIN = 8;         //
    static const size_t IR_PASSPHRASE_LENGTH_MAX = 255;       //
    /*  

*/


    /* Please see man pages for details 
      

      
    */

    /* Please see man pages for details 
    

                
                

                
                
                
                
                

    
    
    
    
    
    
    


    
    
    
    
    */

    static Result Initialize(
        void* pBuf, size_t bufSize,
        size_t receiveBufferDataSize, size_t receiveBufferManagementSize,
        size_t sendBufferDataSize, size_t sendBufferManagementSize,
        nn::ir::CTR::BaudRate baudrate = nn::ir::CTR::BAUD_RATE_115200);

    /* Please see man pages for details 
    

                

    
    
    
    */
    static Result Finalize(void);

    /*  

*/

    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

    

                

                
                
                
                

                
                

                
                
                

                
                
                
                


    
    
    
    
    
    
    
    */
    static Result WaitConnection();

    /* Please see man pages for details 
    

    

                
                

    

    
    
    
    
    
    
    

    
    */
    static Result WaitConnection(nn::fnd::TimeSpan sendReplyDelay);

    /* Please see man pages for details 
    

                

                
                

                
                

                
                

                
                
                

                
                
                
                

    
    
    
    
    
    
    
    */
    static Result RequireConnection();

    /* Please see man pages for details 
    

    

                

                
                
                
                

                
                

                
                

                
                

                
                
                
                

                
                
                

                
                
                
                

    
    
    
    
    
    
    
    */
    static Result AutoConnection();

    /* Please see man pages for details 
    

    

                
                
                

                
                
                
                
                

                
                

                
                

    
    
    
    
    

    
    
    
    
    
    
    
    */
    static Result AutoConnection(nn::fnd::TimeSpan sendReplyDelay,
                nn::fnd::TimeSpan waitRequestMin, nn::fnd::TimeSpan waitRequestMax,
                nn::fnd::TimeSpan waitReplyMin, nn::fnd::TimeSpan waitReplyMax);

    /* Please see man pages for details 
    

                
                

                
                

                
                
                

    
    */
    static ConnectionRole GetConnectionRole(void);

    /* Please see man pages for details 
      
      
    */

    /* Please see man pages for details 
      

                    
                    
                    

      
      
                                    
                                    
      
    */
    static bit32 CreateCommunicationId( bit32 uniqueId, bool isDemo = false);


    /* Please see man pages for details 
    

    
    
    
     */
    static bool  IsConfirmedId();


    /* Please see man pages for details 
    

                
                

                
                

                
                

                

    
    
    
    

    
    
    
    
    
    
    
    
     */
    static Result RequireToConfirmId(u8 subId, bit32 communicationId,  const char passphrase[], size_t passphraseLength);


    /* Please see man pages for details 
    

                
                

                
                

                
                

                

    
    
    
    
    

    
    
    
    
    
    
    
    
     */
    static Result WaitToConfirmId(u8 subId, bit32 communicationId,  const char passphrase[], size_t passphraseLength, nn::fnd::TimeSpan timeout);


    /*  

*/


    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

                

                
                

                
                
                

                
                
                
                


    
    
    
    
    
    */
    static Result Disconnect(void);

    /*  

*/

    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

                

    

    
    */
    static void GetReceiveEvent( nn::os::Event* pEvent);

    /* Please see man pages for details 
    

                

    

    
    */
    static void GetSendEvent( nn::os::Event* pEvent);

    /* Please see man pages for details 
    

                
                
                

                
                   
                
                   
                
                   
                
                   

    

    
    */
    static void GetConnectionStatusEvent( nn::os::Event* pEvent);

    /*  

*/

    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

                
                
                

                
                
                

                
                

                

                
                

                
                
                


    
    
    
    

    
    
    
    
    
    
    
    
    
    */
    static Result Receive(void* pDst, size_t size, size_t *pReceiveSize, s32 *pRemainCount);

    /* Please see man pages for details 
    

                
                
                


                
                

                
                
                
                
                


                

    
    
    
    

    
    
    
    
    
    
    
    
    */
    static Result Send(void *pBuffer, size_t dataSize, size_t bufferSize,bool restore = false);

    /*  

*/

    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

    

    
    
    
    
    
    
    
    */
    static Result GetLatestReceiveErrorResult(bool clear);

    /* Please see man pages for details 
    

    

    
    
    
    */
    static Result GetLatestSendErrorResult(bool clear);

    /* Please see man pages for details 
    

    
    */
    static ConnectionStatus GetConnectionStatus(void);

    /* Please see man pages for details 
    

    
    */
    static TryingToConnectStatus GetTryingToConnectStatus(void);

    /* Please see man pages for details 
    
                

    
    
    
    

    
    */
    static void GetReceiveSizeFreeAndUsed(size_t *pSizeFree, s32 *pCountFree, size_t *pSizeUsed, s32 *pCountUsed);

    /* Please see man pages for details 
    
                

    
    
    
    

    
    */
    static void GetSendSizeFreeAndUsed(size_t *pSizeFree, s32 *pCountFree, size_t *pSizeUsed, s32 *pCountUsed);

    /* Please see man pages for details 
    

                
                
                

                

    

    
    
    
    
    
    
    */
    static Result GetNextReceiveDataSize(size_t *pSize);

    /*  

*/

    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

    
    
    
    
    
    */
    static Result ClearReceiveBuffer(void);

    /* Please see man pages for details 
    

    
    
    
    
    
    */
    static Result ClearSendBuffer(void);

    /* Please see man pages for details 
    
                

    

    
    
    
    
    
    
    */
    static Result DropNextReceiveData(s32 *pRemainCount);

    /*  

*/

    /* Please see man pages for details 
        

        
    */

    /* Please see man pages for details 
    

                

    

    
    */
    static size_t GetManagementSize(s32 dataNum);

    /* Please see man pages for details 
    
                

    

    
    */
    static size_t GetPacketSize(size_t dataSize);

    /* Please see man pages for details 
    

    
    */
    static size_t GetReservedSize(void);

    /* Please see man pages for details 
    

                
                

    

    
    */
    static size_t CalculateBufferSizeToCommunicate(size_t dataSize);


    /* Please see man pages for details 
    

    

                
                
                
                

    
    
    
    
    

    
    */
    static void GetAutoConnectionParametorFromBaudRate(nn::ir::CTR::BaudRate baudrate,
            nn::fnd::TimeSpan* pWaitRequestMin, nn::fnd::TimeSpan* pWaitRequestMax,
            nn::fnd::TimeSpan* pWaitReplyMin, nn::fnd::TimeSpan* pWaitReplyMax);

    /* Please see man pages for details 
    

    

                
                

    
    */
    static nn::fnd::TimeSpan GetDefaultSendReplyDelay(void);



    /*  

*/

    static nn::fnd::TimeSpan CalculateCommunicationTime(nn::ir::CTR::BaudRate baudrate,size_t size);




private :
    static bool mIsConfirmed;
    static nn::ir::CTR::BaudRate mBaudRate;

    static void Reset();
};

}
}
}


#endif /* NN_IR_CTRCOMMUNICATIONAPI_H_ */
