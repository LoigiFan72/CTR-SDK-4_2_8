/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_MessageBoxSystem.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47558 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_MESSAGE_BOX_SYSTEM_H_
#define NN_CEC_CTR_CEC_MESSAGE_BOX_SYSTEM_H_


#include <nn/cec/CTR/cec_Api.h>
#include <nn/cec/CTR/cec_Types.h>
#include <nn/cec/CTR/cec_MessageBox.h>

namespace nn {
namespace cec {
namespace CTR {


/* Please see man pages for details 

    

*/

class MessageBoxSystem : public MessageBox
{
    
 public:

    explicit  MessageBoxSystem(bool NoInitialize = false);
    virtual ~MessageBoxSystem();


    //
    //

    u32     GetMessageBoxList(MessageBoxList& messageBoxList);

    /* Please see man pages for details 
      

      
      
      
    */
    u32     GetMessageBoxTitleIdList(TitleId* titleIdList, MessageBoxFlag flag);
    
    /* Please see man pages for details 
      

      
      
                                    
      
                                    
      
      
      
      
      
      
      
    */
    nn::Result  CreateMessageBox_System(
                const TitleId cecTitleId, const u32 privateId,
                const char* hmacKey,
                MessageBoxFlag flag,
                size_t  inboxSizeMax = CEC_INBOX_SIZE_DEFAULT, 
                size_t  outboxSizeMax = CEC_OUTBOX_SIZE_DEFAULT, 
                size_t  inboxMessNumMax = CEC_INBOX_MESSNUM_DEFAULT,
                size_t  outboxMessNumMax = CEC_OUTBOX_MESSNUM_DEFAULT,
                size_t  messageSizeMax = CEC_MESSSIZEMAX_DEFAULT
            );

    /* Please see man pages for details 
      

      
      
                                  
      
      
      
    */
    nn::Result  GetMessageBoxDataDirect(TitleId cecTitleId, const u32 datatype, void* dataBuf, const size_t dataBufSize);

    nn::Result      DeleteAllBoxes();
    void SetLastOpenedDate(const nn::fnd::DateTimeParameters& dateTime);
    nn::fnd::DateTimeParameters GetLastOpenedDate() const;
    nn::fnd::DateTimeParameters GetLastReceivedDate() const;

    nn::Result  DeleteOldestMessageBox(MessageBoxFlag flag);

    /* Please see man pages for details 
      
                    
      
      
    */
    virtual nn::Result      OpenMessageBoxForce(const TitleId cecTitleId);

    nn::Result    SetMessageBoxFlag(const MessageBoxFlag flag);
    
    nn::Result  SetMessageBodyDirect(const TitleId cecTitleId, const CecBoxType boxType, const MessageId& messageId, const void* dataBody, const size_t dataBodyLen);
    size_t  GetMessageBodySizeDirect(const TitleId cecTitleId, const CecBoxType boxType, const MessageId& messageId) const;
    nn::Result  GetMessageBodyDirect(const TitleId cecTitleId, const CecBoxType boxType, const MessageId& messageId, void* dataBody, const size_t dataBodyLen) const;
};

} // namespace CTR
} // namespace cec
} // namespace nn

#endif  //NN_CEC_CTR_CEC_MESSAGE_BOX_SYSTEM_H_

