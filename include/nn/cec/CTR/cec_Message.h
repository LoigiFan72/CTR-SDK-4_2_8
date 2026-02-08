/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_Message.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47558 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_MESSAGE_H_
#define NN_CEC_CTR_CEC_MESSAGE_H_

#include <nn/fnd.h>
#include <nn/cec/CTR/cec_Const.h>
#include <nn/cec/CTR/cec_Types.h>

namespace nn {
namespace cec {
namespace CTR {

static const u32 CEC_EXHEADER_NUM_MAX    = 16;
static const size_t CEC_EXHEADER_SIZE_MAX   = 8 * 1024;

/* Please see man pages for details 

    
    
*/
typedef struct CecMessageExHeader
{
    u32  exHeaderType;          //
    u32  exHeaderLen;           //
    u8*  exHeaderData;          //
} CecMessageExHeader;

static const u8 LOAD_FLAG_POINTER   = 1;
static const u8 LOAD_FLAG_MALLOC    = 0;

/* Please see man pages for details 
    
    
*/
class Message
{
public:

    /* Please see man pages for details 
     
     
     */
                    Message();
    
    /* Please see man pages for details 
    
     
     
     
     
     */
                    Message(const void* messData, size_t messSize);

    /* Please see man pages for details 
     
     
     */
                    ~Message() {}



    //
    //
    /* Please see man pages for details 
     

                    
                    
     
     
     
                                    
                                    
     
                                    
     
                                    
     
                                    
                                    
                                    
     
                                    
                                    
                                    
     
                                    
                                    
     
     
                                    
                                    
                                    
     
     
     
     
     
     
     */
    nn::Result      NewMessage(
                        TitleId         cecTitleId,
                        u32             groupId,
                        MessageTypeFlag messageTypeFlag,
                        SendMode        sendMode,
                        u8              sendCount,
                        u8              propagationCount,
                        const void*     icon,
                        size_t          iconSize,
                        const wchar_t*  infoTextData,
                        size_t          infoTextSize);
    /* Please see man pages for details 
     

                    
                    
                    
                    
     
     
     
                                    
                                    
     
                                    
     
                                    
     
                                    
                                    
                                    
     
                                    
                                    
                                    
     
     
     
     
     
     
     
     */
    nn::Result      NewMessage(
                        TitleId         cecTitleId,
                        u32             groupId, 
                        MessageTypeFlag messageTypeFlag,
                        SendMode        sendMode, 
                        u8              sendCount,
                        u8              propagationCount);
    //


    //
    //
    /* Please see man pages for details 
    
     
     
     
     
     
     */
    nn::Result      SetCecTitleId(TitleId cecTitleId);

    /* Please see man pages for details 
     
     
     */
    TitleId         GetCecTitleId() const
    {
        return m_MessageHeader.cecTitleId;
    }

    /* Please see man pages for details 
     
                    

                    
                    
                    
                    
                    
     
     
     
     
     */
    nn::Result      SetGroupID(u32 groupId);

    /* Please see man pages for details 
     
                    
     
     */
    u32             GetGroupID() const
    {
        return m_MessageHeader.groupId;
    }
    
    /* Please see man pages for details 
    
     
     
     
     */
    nn::Result      SetSessionID(u32 sessionId);

    /* Please see man pages for details 
    
     

                    
                     
     
     */
    u32             GetSessionID() const
    {
        return m_MessageHeader.sessionId;
    }

    /* Please see man pages for details 
    
     
     
     
     */
    nn::Result      SetMessSize(u32 messSize);

    /* Please see man pages for details 
     

                    
                    
     
     
     */
    u32             GetMessSize() const
    {
        return m_MessageHeader.messSize;
    }
    /* Please see man pages for details 
     

                    
                    
                    
     
     
     */
    u32             GetMessageSize() const
    {
        return GetMessSize();
    }

    
    /* Please see man pages for details 
    
     
     
     
     */
    nn::Result      SetHeaderSize(u32 headerSize);

    /* Please see man pages for details 
     
     
     */
    u32             GetHeaderSize() const
    {
        return m_MessageHeader.headerSize;
    }
    
    /* Please see man pages for details 
    
     
     
     
     */
    nn::Result      SetBodySize(u32 bodySize);
    
    /* Please see man pages for details 
     
     
     */
    u32             GetBodySize() const
    {
        return m_MessageHeader.bodySize;
    }

    
    /* Please see man pages for details 
    
     
     
     
     */
    nn::Result      SetMessageId(const MessageId& messageId);
    
    /* Please see man pages for details 
     
                    
     
     
     */
    MessageId       GetMessageId(MessageId* messId) const;

    nn::Result      SetMessageVersion(u32 messVersion);
    u32             GetMessageVersion() const
    {
        return m_MessageHeader.messVersion;
    }


    /* Please see man pages for details 
    
     
     
     
     */
    nn::Result      SetMessageId_Pair(const MessageId& messIdPair);

    /* Please see man pages for details 
     
                    
     
     
     */
    MessageId       GetMessageId_Pair(MessageId* messIdPair) const;

    /* Please see man pages for details 
     
     
     
     
     */
    nn::Result      SetMessageTypeFlag(MessageTypeFlag messTypeFlag);
    
    /* Please see man pages for details 
     
     
     */
    MessageTypeFlag GetMessageTypeFlag() const
    {
        return m_MessageHeader.messageTypeFlag;
    }
    
    /* Please see man pages for details 
     
     
     
     
     
        
     */
    nn::Result      SetSendMode(SendMode sendMode);
    
    /* Please see man pages for details 
     
     
     */
    SendMode        GetSendMode() const
    {
        return m_MessageHeader.sendMode;
    }


    /* Please see man pages for details 
    
     
     */
    nn::Result      SetSenderID(u64 senderId);
    /* Please see man pages for details 
    
     
     */
    u64             GetSenderID() const
    {
        return m_MessageHeader.senderId;
    }

    /* Please see man pages for details 
    
     
                    
     */
    nn::Result      SetSendDate(const nn::fnd::DateTimeParameters&        date);
    /* Please see man pages for details 
     
     
     */
    nn::fnd::DateTimeParameters     GetSendDate() const
    {
        return m_MessageHeader.sendDate;
    }

    /* Please see man pages for details 
    
     
                    
     */
    nn::Result      SetRecvDate(const nn::fnd::DateTimeParameters&        date);
    /* Please see man pages for details 
     
     
     */
    nn::fnd::DateTimeParameters          GetRecvDate() const
    {
        return m_MessageHeader.recvDate;
    }

    /* Please see man pages for details 
    
     
                    
     */
    nn::Result      SetCreateDate(const nn::fnd::DateTimeParameters&        date);
    /* Please see man pages for details 
     
     
     */
    nn::fnd::DateTimeParameters          GetCreateDate() const
    {
        return m_MessageHeader.createDate;
    }


    /* Please see man pages for details 
     

                    

     
     
     
     */
    nn::Result      SetSendCount(u8 sendCount);

    /* Please see man pages for details 
     

                    

     
     */
    u8              GetSendCount() const
    {
        return m_MessageHeader.sendCount;
    }

    /* Please see man pages for details 
     

                    
                    
                    
     
     
     
     
     */
    nn::Result      SetPropagationCount(u8 propagationCount);

    /* Please see man pages for details 
     
     
     */
    u8              GetPropagationCount() const
    {
        return m_MessageHeader.propagationCount;
    }


    /* Please see man pages for details 
    
     
     
                                
                                
     
     */
    nn::Result      SetFlag_Unread(u8 flag);

    /* Please see man pages for details 
    
     
                    
     
     */
    u8              GetFlag_Unread() const
    {
        return m_MessageHeader.flagUnread;
    }


    /* Please see man pages for details 
    
     
     
                                
                                
     
     
     */
    nn::Result      SetFlag_New(u8 flag);

    /* Please see man pages for details 
    
     
                    
     
     */
    u8              GetFlag_New() const
    {
        return m_MessageHeader.flagNew;
    }


    /* Please see man pages for details 
     

                    

     
     
     */
    void            SetTag(u16 tag);

    /* Please see man pages for details 
     
     
     */
    bit16           GetTag() const
    {
        return m_MessageHeader.tag;
    }


    /* Please see man pages for details 
     

                    
     
     
     
     
     
     
     
     
     
     */
    nn::Result      SetExHeader(MessageExHeaderType exhType, size_t exhLen, const void* exhBody);
    
    /* Please see man pages for details 
     
     
     
     
     
     
     
     
     */
    nn::Result      GetExHeader(MessageExHeaderType exhType, size_t* exhLen, void** exhBody) const;


    /* Please see man pages for details 
    
     
     
     
     
     
     
     */
    nn::Result      SetModuleFilter_MCR(const u8* filterM,const u8* filterC,const u8* filterR, u8 size);
    nn::Result      SetModuleFilter(const u8* filter, size_t size);
    u32             GetModuleFilter(void** filter, size_t* size) const;

    /* Please see man pages for details 
     

                    
     
     
     
     
     
     
     
     
     */
    nn::Result      SetIcon(void* iconData, size_t iconSize)
    {
        return SetExHeader(MESSAGE_EXHEADER_TYPE_ICON, iconSize, iconData);
    }

    /* Please see man pages for details 
     

                    
     
     
     
     
     
     
     
     */
    nn::Result      GetIcon(void** iconData, size_t* iconSize) const
    {
        return GetExHeader(MESSAGE_EXHEADER_TYPE_ICON, iconSize, iconData);
    }

    /* Please see man pages for details 
     

                    
     
     
     
     
     
     
     
     
     */
    nn::Result      SetInfoText(const wchar_t* infoTextData, size_t infoTextSize)
    {
        return SetExHeader(MESSAGE_EXHEADER_TYPE_INFO , infoTextSize, infoTextData);
    }

    /* Please see man pages for details 
     

                    
     
     
     
     
     
     
     
     */
    nn::Result      GetInfoText(const wchar_t** infoTextData, size_t* infoTextSize) const;
    
    /* Please see man pages for details 
     
     
     
     
     
     
     
     
     
     
     */
    nn::Result      SetMessageBody(const void* dataBody, size_t size);
    
    /* Please see man pages for details 
     
     
     
     
     */
    u32             GetMessageBody(void* dataBody, size_t size) const;

    /* Please see man pages for details 
     
     
     
     
     */
    void*           GetMessageBodyPointer(void** pBody,size_t* size);

    /* Please see man pages for details 
     
     
     
     
     
     */
    nn::Result      SetMessageBodyPointer(void* p_dataBody, size_t size);

    //
    
    /* Please see man pages for details 
    
      

                 
      
     
     
      
     */
    nn::Result      InputMessage(const void* mess, size_t size);
    
    nn::Result      InputMessage(const void* mess);
    
    nn::Result      InputMessageHeaderWithEx(const void* mess, size_t size);

    nn::Result      InputMessageHeader(const void* mess, size_t size);
    /* Please see man pages for details 
    
      
                

                 

     
      
     */
    u32             OutputMessage(void* messData) const;

    u32             MakeMessageBinary(void* messData) const;
    void            OutputMessageHeader(void* pHeaderBuf) const;
    
    static u32      CheckMessageSize(const void* mess);

    void            DumpMessage() const;

private:
    u32             CalcCecMessSize();
    void            InitializeMessage();
    nn::Result      SetExHeaderWithoutCalc(MessageExHeaderType exhType, size_t exhLen, const void* exhBody);
    nn::Result      SetMessageBodyWithoutCalc(const void* dataBody, size_t size);
    nn::Result      SetHmacSha256(void* input);
    nn::Result      GetHmacSha256(void* outBuf, u32 size = CEC_SIZEOF_HASH)  const;

private:
    CecMessageHeader    m_MessageHeader;
    CecMessageExHeader  m_MessageExHeader[CEC_EXHEADER_NUM_MAX] NN_ATTRIBUTE_ALIGN(4);
    s8                  m_NumOfExHeader;
    u8                  m_FlagInput;
    NN_PADDING2;
    u32                 m_MessageBodyLen;
    u8*                 m_pMessageBody;
    u8*                 m_pHash;
    u32                 m_HashSize;
    u8                  m_HmacKey[MESSAGE_HMAC_KEYLEN];
    NN_PADDING4;
};



} // namespace CTR
} // namespace cec
} // namespace nn






#endif  //NN_CEC_CTR_CEC_MESSAGE_H_
