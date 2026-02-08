/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47558 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_TYPES_H_
#define NN_CEC_CTR_CEC_TYPES_H_

#include <nn/types.h>
#include <nn/fnd.h>
#include <nn/cec/CTR/cec_Const.h>
#include <nn/cec/CTR/cec_MessageId.h>

namespace nn {
namespace cec {
namespace CTR {
    /* Please see man pages for details 
        
    */
    typedef u32 TitleId;
    typedef u32 GroupId;
    typedef bit64 SenderId;

    //
    //
    /* Please see man pages for details 
     

              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
     
     */
    typedef u8 SendMode;

        /* Please see man pages for details 
        
               */
        static const SendMode SENDMODE_RECV           = 0x1;
        /* Please see man pages for details 
        
               */
        static const SendMode SENDMODE_SEND           = 0x2;
        /* Please see man pages for details 
        
               */
        static const SendMode SENDMODE_SENDRECV       = 0x3;
        /* Please see man pages for details 
        
               */
        static const SendMode SENDMODE_EXCHANGE       = 0x0;

        static const SendMode CEC_SENDMODE_RECV       = SENDMODE_RECV;
        static const SendMode CEC_SENDMODE_SEND       = SENDMODE_SEND;
        static const SendMode CEC_SENDMODE_SENDRECV   = SENDMODE_SENDRECV;
        static const SendMode CEC_SENDMODE_EXCHANGE   = SENDMODE_EXCHANGE;
    //
    

    //
    //
    
    /* Please see man pages for details 
     

            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
     
     */
    typedef u8 MessageTypeFlag;
    
    /* Please see man pages for details 
    
               */
    static const MessageTypeFlag MESSAGE_TYPEFLAG_NON_FRIEND     = 0x1; 
    /* Please see man pages for details 
    
               */
    static const MessageTypeFlag MESSAGE_TYPEFLAG_FRIEND         = 0x2;
    /* Please see man pages for details 
    
               */
    static const MessageTypeFlag MESSAGE_TYPEFLAG_ANYONE         = MESSAGE_TYPEFLAG_NON_FRIEND|MESSAGE_TYPEFLAG_FRIEND;

    typedef MessageTypeFlag CecMessageTypeFlag;
    //


    //
    //

    /* Please see man pages for details 
     
     */
    typedef u32 MessageExHeaderType;
    
        static const MessageExHeaderType MESSAGE_EXHEADER_TYPE_MFILTER  = 0x00000001;   // ModuleFilter
        static const MessageExHeaderType MESSAGE_EXHEADER_TYPE_ICON     = 0x00000002;   //
        static const MessageExHeaderType MESSAGE_EXHEADER_TYPE_NAME     = 0x00000003;   // アプリ名
        static const MessageExHeaderType MESSAGE_EXHEADER_TYPE_INFO     = 0x00000004;   //
        static const MessageExHeaderType MESSAGE_EXHEADER_TYPE_REGION   = 0x00000005;   // REGION
    
    typedef MessageExHeaderType CecMessageExHeaderType;
    //

    static const u16 MESSAGE_MAGIC     = 0x6060;
    static const u32 MESSAGE_VERSION   = 0x00000000;
    typedef struct CecMessageHeader
    {
        u16 magic16;                //
        NN_PADDING2;

        u32 messSize;               //
        u32 headerSize;             //
        u32 bodySize;                //

        u32 cecTitleId;                 //
        u32 cecTitleId_reserve;         //
        u32 groupId;                //
        u32 sessionId;              //
        u8  messageId[CEC_SIZEOF_MESSAGEID];          //
        u32 messVersion;            //
        u8  messageId_pair[CEC_SIZEOF_MESSAGEID];     //
        u8  messageTypeFlag;        //
        u8  sendMode;               //
        bit8    flagUnread;                 //
        bit8    flagNew;                    //
        u64  senderId;              //
        u64  senderId2;             //
        nn::fnd::DateTimeParameters     sendDate;               //
        nn::fnd::DateTimeParameters     recvDate;               //
        nn::fnd::DateTimeParameters     createDate;             //
        u8  sendCount;              //
        u8  propagationCount;       //
        bit16   tag;                //
        //u32   PAD[4]; // 16 bytes
    } CecMessageHeader;


} // namespace CTR
} // namespace cec
} // namespace nn

#endif  //NN_CEC_CTR_CEC_TYPES_H_
