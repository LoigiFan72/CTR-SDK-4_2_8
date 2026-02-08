/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Receiver.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49491 $
 *---------------------------------------------------------------------------*/

////#include <stdafx.h>

#ifndef NN_RDT_RECEIVER_H_
#define NN_RDT_RECEIVER_H_


#include <nn/rdt/CTR/rdt_define.h>

#include <nn/types.h>
#include <nn/Result.h>


namespace nn { namespace rdt { namespace CTR {


class ReceiverImpl;

/* Please see man pages for details 
    
 */
struct ReceiverConfig{
    void *pWorkBuf;     //
    void *pRecvBuf;     //
    u16   recvBufSize;  //
    u16   nodeId;       //
    u8    port;         //
    u8    padding[3];   //
#ifdef _WIN32
    SOCKET sock;
#endif
};


/* Please see man pages for details 
    





















*/
class Receiver{
public:
    static const size_t RECEIVER_WORKBUF_SIZE = 128;  //

    /* Please see man pages for details 
    

           
           
     */
    Receiver(void);


    /* Please see man pages for details 
    

           
           
     */
    ~Receiver(void);


    /* Please see man pages for details 
    

           
           
           
           

           
           
           
           
           
           

    

    
            
            
     */
    nn::Result Initialize(const ReceiverConfig &config);


    /* Please see man pages for details 
    

    
            
            
     */
    void Finalize(void);


    /* Please see man pages for details 
    

           
           
           

    
            
            
            
            
     */
    nn::Result Wait(void);


    /* Please see man pages for details 
    

           
           

    
            
            
            
            
     */
    nn::Result Close(void);


    /* Please see man pages for details 
    

           
           
           

           
           

    
    
                          
    
                          

    
            
            
            
            
     */
    nn::Result Receive(void *pBuf, size_t *pRecvSize, size_t bufSize);


/* Please see man pages for details 
    

           
           
           
           
           
           
           
           
           
           

    
            
            
            
*/
    nn::Result Process(void);


    /* Please see man pages for details 
    

           
           
           
           

    
     */
    void Cancel(void);


    /* Please see man pages for details 
    

    
     */
    enum ReceiverState GetStatus(void) const;


    /* Please see man pages for details 
    

           
           
           

    

    
     */
    void SetPacketLossRatio(int per);


    /* Please see man pages for details 
    

    
     */
    void PrintDebugInfo(void) const;


private:
    /* Please see man pages for details 
    
     */
    Receiver           (const Receiver&);


    /* Please see man pages for details 
    
     */
    Receiver& operator=(const Receiver&);


    /* Please see man pages for details 
    
     */
    ReceiverImpl *m_pImpl;
};


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_RECEIVER_H_
