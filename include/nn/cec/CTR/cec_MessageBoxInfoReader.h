/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_MessageBoxInfoReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_MESSAGE_BOX_INFO_READER_H_
#define NN_CEC_CTR_CEC_MESSAGE_BOX_INFO_READER_H_

#include <nn/cec/CTR/cec_Message.h>
#include <nn/cec/CTR/cec_MessageBox.h>

/*
    CEC/
    |
    +-- MessageBoxList
    \-- Message_BOX1/
    |   |
    |   +-- MessageBoxInfo
    |   \-- InBox/
    |   |   |
    |   |   +-- InBoxInfo
    |   |   +-- Message1
    |   |
    |   \-- OutBox/
    |       |
    |       +-- OutBoxIndex
    |       +-- OutBoxInfo
    |       +-- Message2
    |
    \-- Message_BOX2/
    |

------------------------------------

struct MessageBoxInfo
{
    u16 magic16;
    NN_PADDING2;
    u32 cecTitleId;                     // Unique Title ID
    u32 privateId;                  // Unique ID assigned by application. Used to make the key for access.
    MessageBoxFlag MessageBoxInfoFlag;         // MessageBoxInfo flag (System etc.)
    NN_PADDING3;
    char  hmacKey[MESSAGE_HMAC_KEYLEN];    // Key used to sign using HMAC
    u32 MessageBoxInfoSize;         // MessageBoxInfo size (in bytes)
    nn::fnd::DateTimeParameters lastOpened;     // Records time of access
    u8  reserved[256];             // reserved (name, icon etc. are written to a different file)
};

------------------------------------

  File: InBoxInfo/OutBoxInfo
  +----------------------+
  |  CEC Box Info Header |
  +----------------------+ -+
  |  CEC Message Header1 |  |
  +----------------------+  | CecMessageHeader_List
  |  CEC Message Header2 |  |
  +----------------------+  |
  |  CEC Message Header3 |  |
  +----------------------+  |
  |    ..........        |  |
  |                      |  |
  +----------------------+ -+

struct CecBoxInfoHeader
{
    u16 magic16;
    NN_PADDING2;
    u32 boxInfoSize;                // BoxInfo size
    u32 boxSizeMax;                 // Maximum MessageBox size (in bytes)
    u32 boxSize;                    // MessageBox size (amount used) (in bytes)
    u32 messNumMax;                 // Maximum number of messages that can be stored in the box
    u32 messNum;                    // Number of messages stored in the box
    u32 groupNumMax;                // Maximum number of message groups that can be stored in the box
    u32 messSizeMax;                // Max size of one message
};

*/


namespace nn {
namespace cec {
namespace CTR {
    
/* Please see man pages for details 
    
    
    

           
           

           
*/
class MessageBoxInfoReader
{
private:

    u32                           m_currentCecTitleId;
    struct MessageBoxInfo      m_cecMessageboxInfo;
    struct CecBoxInfoHeader       m_cecInboxInfo;
    CecMessageHeader*         m_cecInboxInfo_body[CEC_INBOX_MESSNUM_DEFAULT];
    struct CecBoxInfoHeader       m_cecOutboxInfo;
    CecMessageHeader*         m_cecOutboxInfo_body[CEC_OUTBOX_MESSNUM_DEFAULT];

public:
    //
    //
    /* Please see man pages for details 
     
               
     
     
     */
    explicit  MessageBoxInfoReader(const MessageBox& cecMessBox);
    MessageBoxInfoReader();
    ~MessageBoxInfoReader();
    
    /* Please see man pages for details 
     
                    
     
     
     */
    nn::Result LoadMessageBoxInfo(const MessageBox& cecMessBox);
    //

    //
    //
    /* Please see man pages for details 
     
     
     
     */
    MessageBoxFlag       GetMessageBoxInfoFlag();

    /* Please see man pages for details 
     
     
     
     */
    u32     GetBoxSizeMax(CecBoxType boxType);
    
    /* Please see man pages for details 
     
     
     
     */
    u32     GetBoxSize(CecBoxType boxType);

    /* Please see man pages for details 
     
     
     
     */
    u32     GetMessNumMax(CecBoxType boxType);

    /* Please see man pages for details 
     
     
     
     */
    u32     GetMessNum(CecBoxType boxType);

    u32     GetGroupNumMax(CecBoxType boxType);
    //

    CecMessageHeader*   GetCecMessageHeader(CecBoxType boxType, u32 messIndex);



    //
    //

    /* Please see man pages for details 
     
     
     
     
     */
    u32     GetMessageMessSize(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u32     GetMessageBodySize(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u32     GetMessageGroupId(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u32     GetMessageSessionId(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u8      GetMessageMessTypeFlag(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u8      GetMessageSendMode(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u8      GetMessageSendCount(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    u8      GetMessagePropagationCount(CecBoxType boxType, u32 messIndex);
    
    /* Please see man pages for details 
     
     
     
     
     */
    bit8      GetMessageFlag_Unread(CecBoxType boxType, u32 messIndex);
    
    /* Please see man pages for details 
     
     
     
     
     */
    bit8      GetMessageFlag_New(CecBoxType boxType, u32 messIndex);
    
    /* Please see man pages for details 
     
     
     
     
     */
    bit16      GetMessageTag(CecBoxType boxType, u32 messIndex);
    
    /* Please see man pages for details 
     
     
     
     
     */
    nn::fnd::DateTimeParameters     GetMessageSendDate(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    nn::fnd::DateTimeParameters     GetMessageRecvDate(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     
     
     
     
     */
    nn::fnd::DateTimeParameters     GetMessageCreateDate(CecBoxType boxType, u32 messIndex);

    /* Please see man pages for details 
     

                    

     
     
     
     */
    u8*       GetMessageMessIdPair(CecBoxType boxType, u32 messIndex);


    /* Please see man pages for details 
     
     
     
     
     */
    u8*       GetMessageMessId(CecBoxType boxType, u32 messIndex);


    /* Please see man pages for details 
     
     
     
     
     */
    u32       GetMessIndex(CecBoxType boxType, const MessageId& messageId);
    //

};


} // namespace CTR
} // namespace cec
} // namespace nn


#endif  //NN_CEC_CTR_CEC_MESSAGE_BOX_INFO_READER_H_

