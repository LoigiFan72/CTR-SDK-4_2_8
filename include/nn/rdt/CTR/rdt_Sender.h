/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Sender.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49491 $
 *---------------------------------------------------------------------------*/

////#include <stdafx.h>

#ifndef NN_RDT_SENDER_H_
#define NN_RDT_SENDER_H_


#include <nn/rdt/CTR/rdt_define.h>

#include <nn/types.h>
#include <nn/Result.h>


namespace nn { namespace rdt { namespace CTR {


class SenderImpl;

/* Please see man pages for details 
    
 */
struct SenderConfig{
    void *pWorkBuf;    //
    void *pSendBuf;    //
    u16   sendBufSize; //
    u16   nodeId;      //
    u8    port;        //
    u8    padding[3];  //
#ifdef _WIN32
    SOCKET sock;
#endif
};


/* Please see man pages for details 
    






















*/
class Sender{
public:
    static const size_t SENDER_WORKBUF_SIZE = 32 * 1024;  //

    /* Please see man pages for details 
    

           
           
     */
    Sender(void);


    /* Please see man pages for details 
    

           
           
     */
   ~Sender(void);


    /* Please see man pages for details 
    

           
           
           
           

           
           
           
           
           
           

    

    
            
            
     */
    nn::Result Initialize(const SenderConfig &config);


    /* Please see man pages for details 
    

    
            
            
     */
    void Finalize(void);


    /* Please see man pages for details 
    

           
           
           

    
            
            
            
            
     */
    nn::Result Open(void);


    /* Please see man pages for details 
    

           
           
           
           

    
            
            
            
            
     */
    nn::Result Close(void);


    /* Please see man pages for details 
    

           
           
           
           
           
           
           
           

      
      
                          

      
              
              
              
     */
    nn::Result Send(const void *pBuf, size_t bufSize);


    /* Please see man pages for details 
    

           
           
           
           
           
           
           
           
           
           
           
           
           

    
            
            

            
            
            
            
     */
    nn::Result Process(void);


    /* Please see man pages for details 
    

           
           
           
           

    
     */
    void Cancel(void);


    /* Please see man pages for details 
    

    
     */
    enum SenderState GetStatus(void) const;


    /* Please see man pages for details 
    

           
           
           

    

    
     */
    void SetPacketLossRatio(int per);


    /* Please see man pages for details 
    

    
     */
    void PrintDebugInfo(void) const;


private:
    /* Please see man pages for details 
    
     */
    Sender           (const Sender&);


    /* Please see man pages for details 
    
     */
    Sender& operator=(const Sender&);


    /* Please see man pages for details 
    
     */
    SenderImpl *m_pImpl;
};


}}} // namespace nn::rdt::CTR

#endif  // end of NN_RDT_SENDER_H_
