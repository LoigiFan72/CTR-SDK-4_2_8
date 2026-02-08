/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_MessageBox.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47785 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_MESSAGE_BOX_H_
#define NN_CEC_CTR_CEC_MESSAGE_BOX_H_


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
    
*/          

#include <nn/cec/CTR/cec_Api.h>
#include <nn/cec/CTR/cec_Message.h>

namespace nn {
namespace cec {
namespace CTR {

static const size_t CEC_INBOX_SIZE_DEFAULT      = 512 * 1024;   //
static const size_t CEC_OUTBOX_SIZE_DEFAULT     = 512 * 1024;   //
static const u8 CEC_INBOX_MESSNUM_DEFAULT       = 99;           //
static const u8 CEC_OUTBOX_MESSNUM_DEFAULT      = 99;           //
static const size_t CEC_MESSSIZEMAX_DEFAULT     = 100 * 1024;   //  Unused Buttons

static const size_t CEC_BOX_DATA_SIZE_MAX       = 10 * 1024;

static const u8 CEC_BOXNUMMAX_APPLICATION      = 12;        // Maximum number of Boxes for general application
static const u8 CEC_BOXNUMMAX_SYSTEM           = 6;        // Maximum number of Boxes for system application
static const u8 CEC_BOXNUMMAX_SYSTEM2          = 6;         // Maximum number of Boxes for system application part 2
static const u8 MESSAGE_BOX_NUM_MAX            = (CEC_BOXNUMMAX_APPLICATION + CEC_BOXNUMMAX_SYSTEM + CEC_BOXNUMMAX_SYSTEM2);

static const u8 CEC_BOXDIR_NAMELEN_MAX         = 16;

//
//
/* Please see man pages for details 
   
 
 
 */
typedef bit8 MessageBoxFlag;
/* */
    static const bit8 MESSAGE_BOX_FLAG_APPLICATION  =  (0x1); 
/* */
    static const bit8 MESSAGE_BOX_FLAG_SYSTEM  =  (0x2);
/* */
    static const bit8 MESSAGE_BOX_FLAG_SYSTEM2  =  (0x4);  
/* */
    static const bit8 MESSAGE_BOX_FLAG_HIDDEN  =  (0x80);

//


/* Please see man pages for details 
 
 
 */
enum CecBoxType
{
    CEC_BOXTYPE_INBOX  = (0x0),     //
    CEC_BOXTYPE_OUTBOX = (0x1)      //
};


// Structures
static const u16 MESSAGEBOXLIST_MAGIC = 0x6868;
static const u32 CEC_BOX_VERSION      = 0x00000001;
struct MessageBoxList
{
    u16     magic16;
    NN_PADDING2;
    u32     CecBoxVersion;
    u32     DirNum;
    u8      DirName[MESSAGE_BOX_NUM_MAX][CEC_BOXDIR_NAMELEN_MAX];
};

//Message list for local management
static const u16 MESSAGEBOXINFO_MAGIC = 0x6363;
struct MessageBoxInfo
{
    u16 magic16;
    NN_PADDING2;
    u32 cecTitleId;                     // Title specific ID
    u32 privateId;                  // Specific ID assigned by application. It is the key for access.
    MessageBoxFlag MessageBoxInfoFlag;         // MessageBoxInfo flag (System, etc.)
    bool isActive;
    NN_PADDING2;
    char  hmacKey[MESSAGE_HMAC_KEYLEN];    // Key used when adding signature with HMAC
    u32 MessageBoxInfoSize;         // MessageBoxInfo size (bytes)
    nn::fnd::DateTimeParameters lastOpened;     // Record the time when accessed
    u8   flag1;                 // Flag 1 changed when accessed  Unread Flag
    u8   flag2;                 // Flag 2 changed when accessed  New Flag
    u8   flag3;                 // Flag 3 changed when accessed
    u8   flag4;                 // Flag 4 changed when accessed
    nn::fnd::DateTimeParameters lastReceived;     // Record the time when received
    u8  reserved[16];             // reserved (name/icon, etc. are written in a different file)
};


// In/outbox information file data structure

/*
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
*/



static const u16 CEC_BOXINFO_MAGIC         = 0x6262;
struct CecBoxInfoHeader
{
    u16 magic16;
    NN_PADDING2;
    u32 boxInfoSize;                // BoxInfo size
    u32 boxSizeMax;                 // MessageBox size (bytes) maximum value
    u32 boxSize;                    // MessageBox size (used volume) (bytes)
    u32 messNumMax;                 // Maximum number of messages that can be stored in the box
    u32 messNum;                    // Number of messages stored in the box
    u32 groupNumMax;                // Maximum number of Message Groups that can be stored in the box
    u32 messSizeMax;                // Maximum size of one message
};
static const u32 CEC_SIZEOF_BOXINFO_HEADER = (sizeof(struct CecBoxInfoHeader));


// Outbox Index file (indicates send order)
static const u16 CEC_OUTBOXINDEX_MAGIC     = 0x6767;
struct CecOutBoxIndexHeader
{
    u16 magic16;
    NN_PADDING2;
    size_t messageNum;                // Number of messages
};



/* Please see man pages for details 
    

           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           

*/

class MessageBox
{
 protected:
    u32     currentCecTitleId;

    bool    m_Initialized;
    bool    m_BoxAccessible;

    bool    b_SkippedWriteInboxInfo;
    bool    b_SkippedWriteOutboxInfo;

    u8* cecBoxBuf;

    struct MessageBoxList       cecMessageBoxList;
    struct MessageBoxInfo       cecMessageBoxInfo;

    struct CecBoxInfoHeader       cecInboxInfo;
    CecMessageHeader*             cecInboxInfo_body[CEC_INBOX_MESSNUM_DEFAULT];
    u8*                           cecInboxInfoBuf;
    struct CecBoxInfoHeader       cecOutboxInfo;
    CecMessageHeader*             cecOutboxInfo_body[CEC_OUTBOX_MESSNUM_DEFAULT];
    u8*                           cecOutboxInfoBuf;

    CecOutBoxIndexHeader          cecOutboxIndex_header;
    CECMessageId                    cecOutboxIndex[CEC_OUTBOX_MESSNUM_DEFAULT];
    
    static nn::os::CriticalSection    m_Cs;
    static nn::os::CriticalSection    m_CsMem;
    
    struct CecBoxInfoHeader       tmp_cecInboxInfo;
    struct CecBoxInfoHeader       tmp_cecOutboxInfo;


 public:

    explicit MessageBox(bool NoInitialize = false);
    virtual ~MessageBox();

 protected:
    nn::Result      Initialize();
    nn::Result      Finalize();

    nn::Result     WriteMessageBoxList();
    size_t     ReadMessageBoxList();
    nn::Result      AllocInboxInfoBodyBuf(size_t size);
    nn::Result      AllocOutboxInfoBodyBuf(size_t size);
    nn::Result      FreeInboxInfoBodyBuf();
    nn::Result      FreeOutboxInfoBodyBuf();


 public:
    u32         GetMessageBoxNum(MessageBoxFlag flag);
    size_t     ReadMessageBoxList(void* bufOut, size_t size);

    /* Please see man pages for details 
    
      
      
    */
    inline  u32 GetCurrentCecTitleId() const{return currentCecTitleId;}


    //
    //

    /* Please see man pages for details 
      
                    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                   
                   
                   
                    
                    
                    

      
                                    
      
                                    
                                    
      
                                    
                                    
                                    
                                    
                                    
      
                                
                                
      
      
                                
                                
                                
      
      
      
      
      
      
      
        
        
                                                    
                                                    

        
                                                    
                                                    
        
        
        
        
        
    */
    nn::Result  CreateMessageBox(
                    const TitleId cecTitleId, const u32 privateId,
                    const char* hmacKey,
                    const void*       icon,   size_t  iconSize,
                    const wchar_t*    name,   size_t  nameSize,
                    size_t  inboxSizeMax = CEC_INBOX_SIZE_DEFAULT, 
                    size_t  outboxSizeMax = CEC_OUTBOX_SIZE_DEFAULT, 
                    size_t  inboxMessNumMax = CEC_INBOX_MESSNUM_DEFAULT,
                    size_t  outboxMessNumMax = CEC_OUTBOX_MESSNUM_DEFAULT,
                    size_t  size = CEC_MESSSIZEMAX_DEFAULT
                );

    /* Please see man pages for details 
      
      

                    

      
      
                                    
                                    
      
                                    
                                    
                                    
                                    
                                    
      
      
      
      
      
      
        
        
        
                                                    
                                                    
        
        
        
        
    */
    nn::Result  CreateMessageBox(
                    const TitleId cecTitleId, const u32 privateId,
                    const char* hmacKey,
                    size_t  inboxSizeMax = CEC_INBOX_SIZE_DEFAULT, 
                    size_t  outboxSizeMax = CEC_OUTBOX_SIZE_DEFAULT, 
                    size_t  inboxMessNumMax = CEC_INBOX_MESSNUM_DEFAULT,
                    size_t  outboxMessNumMax = CEC_OUTBOX_MESSNUM_DEFAULT,
                    size_t  messageSizeMax = CEC_MESSSIZEMAX_DEFAULT
                );
                
    void       CreateInBox(const TitleId cecTitleId);
    void       CreateOutBox(const TitleId cecTitleId);

    /* Please see man pages for details 
      

                    

      
        
        
        
    */
    nn::Result      DeleteMessageBox();
    
    /* Please see man pages for details 
      
                    
      
      
      
        
        
    */
    nn::Result      DeleteMessageBox(const TitleId cecTitleId);

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    
                    
      
      
                                   
      
        
        
        
        
        
        
    */
    nn::Result      OpenMessageBox(const TitleId cecTitleId, const u32 privateId);


    void            CloseMessageBox(bool bWithoutCommit);

    /* Please see man pages for details 
      

                    
                    
                    
                    
      
    */
    void            CloseMessageBox();

    /* Please see man pages for details 
      

      
    */
    bool            IsOpened() const;
    
    //
    
    /* Please see man pages for details 
      
      
      
        
        
        
    */
    inline nn::Result      SetBoxActivate(bool active)
    {
        cecMessageBoxInfo.isActive = active;
        return WriteMessageBoxInfo();
    }
    
    /* Please see man pages for details 
      
      
    */
    inline bool            GetBoxActivate() const
    {
        return cecMessageBoxInfo.isActive;
    }

    /* Please see man pages for details 
    
      
      
    */
    nn::Result     ReadMessageBoxInfo(struct MessageBoxInfo* outbuf) const;

    nn::Result    GetBoxInfo(struct CecBoxInfoHeader* boxinfo, CecMessageHeader** boxInfoBody, CecBoxType boxType) const ;
    nn::Result     ReadBoxInfo(struct CecBoxInfoHeader* boxinfo, CecMessageHeader** boxInfoBody, u8* buf, CecBoxType boxType);
    
    nn::Result     ReadMessageBoxInfo(struct MessageBoxInfo* outbuf, TitleId cecTitleId) const;
    nn::Result     WriteBoxInfo( CecBoxType boxType ,CecBoxInfoHeader& boxInfo , CecMessageHeader** boxInfoBody);
 protected:
    nn::Result     ReadMessageBoxInfo() const;
    nn::Result     WriteMessageBoxInfo();

    nn::Result     ReadInBoxInfo();

    nn::Result     WriteInBoxInfo();
    nn::Result     ReadOutBoxInfo();
    nn::Result     WriteOutBoxInfo();

 
 public:
    //
    //
    /* Please see man pages for details 
      
      
      
      
      
      
      
        
        
        
        
        
    */
    nn::Result  ReadMessage(
        Message& cecMessage, void* buf, const size_t bufLen, const CecBoxType boxType, const MessageId& messageId);
    /* Please see man pages for details 
    
      
      
      
      
      
      
    */
    nn::Result  ReadMessage(
        void* bufOut, const size_t bufLen, const CecBoxType boxType, const MessageId& messageId);

    /* Please see man pages for details 
      

                    
                    
                    
                   
                   
                   
                   
      
      
      
      
        
        
        
        
        
        
        
        
        
        
        
    */
    nn::Result  WriteMessage(
        const Message& cecMessage,const CecBoxType boxType, MessageId& messageIdOut);

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                   
                   
                   


      
      
      
      
                                             
                                                                                          
      
        
        
        
        
        
        
        
        
        
        
        
        
    */
    nn::Result  WriteMessage(
        const Message& cecMessage,const CecBoxType boxType, MessageId& messageIdOut, bool withWriteBoxInfo);

    nn::Result  WriteMessage(
        const Message& cecMessage,const CecBoxType boxType)
    {
        MessageId messageIdOut;
        return WriteMessage(cecMessage, boxType, messageIdOut);
    }


    /* Please see man pages for details 
    
      

                    

      
      
      
      
      
    */
    nn::Result  WriteMessage(
        const void* message, const size_t messageLen ,const CecBoxType boxType, MessageId& messageIdOut);

    /* Please see man pages for details 
      

                    

      
      
      
        
        
        
    */
    nn::Result  DeleteMessage( const CecBoxType boxType, const MessageId& messageId);

    /* Please see man pages for details 
      

                    
                    
                    

      
      
      
                                             
      
        
        
        
    */
    nn::Result  DeleteMessage( const CecBoxType boxType, const MessageId& messageId, bool withWriteBoxInfo);
    
    /* Please see man pages for details 
      

                    

      
      
        
        
        
    */
    nn::Result  DeleteAllMessages(const CecBoxType boxType);

    /* Please see man pages for details 
    
      
      
    */
    u32  DeleteSentMessages();

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    

      
        
        
    */
    nn::Result  CommitMessageBox();

    //
    
 protected:
    u8      ReadInBoxMessage(void* bufOut, const size_t messageLen, const MessageId& messageId);
    u8     WriteInBoxMessage(const void* message, const size_t messageLen, MessageId* pMessageIdOut);
    u8     WriteInBoxMessage(Message& cecMessage, MessageId* pMessageId);
    u8      DeleteInBoxMessage(const CECMessageId messageId);
    u8      ReadOutBoxMessage(void* bufOut, const size_t messageLen, const MessageId& messageId);
    u8     WriteOutBoxMessage(const void* message, const size_t messageLen, MessageId* pMessageIdOut);
    u8     WriteOutBoxMessage(Message& cecMessage, MessageId* pMessageIdOut);
    u8      DeleteOutBoxMessage(const MessageId& messageId);

    nn::Result      CheckEulaParentalControl();
    

 public:
    // Box List

    //
    //
        
    /* Please see man pages for details 
      
      
      
      
      
        
        
    */
    nn::Result  GetMessageBoxData(u32 datatype, void* dataBuf, size_t dataBufSize) const;

    /* Please see man pages for details 
      
      
      
    */
    size_t      GetMessageBoxDataSize(const u32 datatype) const;

    /* Please see man pages for details 
      
      
      
      
      
        
        
        
        
    */
    nn::Result  SetMessageBoxData(u32 datatype, const void* data, size_t dataSize);
    
    /* Please see man pages for details 
      
      
                                
                                
                                
      
      
        
        
        
        
    */
    nn::Result  SetMessageBoxName(const wchar_t* data, size_t dataSize);
    
    /* Please see man pages for details 
      

                   
                   
                   
      
      
                                
                                
      
      
        
        
        
    */
    nn::Result  SetMessageBoxIcon(const void* data, size_t dataSize);
    
    /* Please see man pages for details 
      
      
                                
                                
                                
      
      
        
        
    */
    nn::Result  GetMessageBoxName(wchar_t* dataBuf, size_t dataBufSize) const;
    
    /* Please see man pages for details 
      
      
                                
                                
      
      
        
        
    */
    nn::Result  GetMessageBoxIcon(void* dataBuf, size_t dataBufSize) const;
    

    /*-----------------------------------------------*/
    
    //
    //
        
    /* Please see man pages for details 
    
      
      
    */
    inline MessageBoxFlag     GetBoxFlag() const
    {
        return cecMessageBoxInfo.MessageBoxInfoFlag;
    }
    
 protected:
    // Get the number of messages in the Box
    inline u32     GetInBoxMessNumMax() const
    {
        return cecInboxInfo.messNumMax;
    }

    inline u32     GetInBoxMessNum() const
    {
        return cecInboxInfo.messNum;
    }

    inline u32     GetOutBoxMessNumMax() const
    {
        return cecOutboxInfo.messNumMax;
    }

    inline u32     GetOutBoxMessNum() const
    {
        return cecOutboxInfo.messNum;
    }



    // Get the BOX capacity
 protected:
    inline u32     GetInBoxSizeMax() const
    {
        return cecInboxInfo.boxSizeMax;
    }

    inline u32     GetInBoxSize() const
    {
        return cecInboxInfo.boxSize;
    }
    inline u32     GetOutBoxSizeMax() const
    {
        return cecOutboxInfo.boxSizeMax;
    }

    inline u32     GetOutBoxSize() const
    {
        return cecOutboxInfo.boxSize;
    }

    inline u32     GetInBoxMessSizeMax() const
    {
        return cecInboxInfo.messSizeMax;
    }

    inline u32     GetOutBoxMessSizeMax() const
    {
        return cecOutboxInfo.messSizeMax;
    }

 public:
    /* Please see man pages for details 
      
      
      
    */
    inline u32     GetBoxSizeMax(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxSizeMax();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxSizeMax();
        }
    }

    /* Please see man pages for details 
      
      
      
    */
    inline u32     GetBoxSize(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxSize();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxSize();
        }
    }

    /* Please see man pages for details 
    
      
      
      
    */
    inline u32     GetBoxMessageSizeMax(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxMessSizeMax();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxMessSizeMax();
        }
    }



    /*-----------------------------------------------*/


    /* Please see man pages for details 
    
      
      
      
    */
    inline u32     GetBoxMessNumMax(CecBoxType boxType) NN_ATTRIBUTE_DEPRECATED
    {
        return GetBoxMessageNumMax(boxType);
    }
    
    /* Please see man pages for details 
      
      
      
    */
    inline u32     GetBoxMessageNumMax(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxMessNumMax();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxMessNumMax();
        }
    }
    /* Please see man pages for details 
    
      
      
      
    */
    inline u32     GetBoxMessNum(CecBoxType boxType) NN_ATTRIBUTE_DEPRECATED
    {
        return GetBoxMessageNum(boxType);
    };
    /* Please see man pages for details 
      
      
      
    */
    inline u32     GetBoxMessageNum(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxMessNum();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxMessNum();
        }
    }


    /*-----------------------------------------------*/
  private:
    inline u32     GetInBoxGroupNumMax() const
    {
        return cecInboxInfo.groupNumMax;
    }
    u32     GetInBoxGroupNum() const;

    inline u32     GetOutBoxGroupNumMax() const
    {
        return cecOutboxInfo.groupNumMax;
    }

    u32     GetOutBoxGroupNum() const;

  public:
    /* Please see man pages for details 
      
      
      
    */
    inline u32     GetBoxGroupNumMax(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxGroupNumMax();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxGroupNumMax();
        }
    }


    /* Please see man pages for details 
      
      
      
    */
    inline u32     GetBoxGroupNum(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxGroupNum();
        }else{
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            return GetOutBoxGroupNum();
        }
    }

    /* Please see man pages for details 
      
      
                    
                   
                   
                   
                   
                   
      
      
      
        
        
        
        
    */
    nn::Result     SetBoxGroupNumMax(u32 num, CecBoxType boxType);
 protected:
    nn::Result     SetInBoxGroupNumMax(u32 num);
    nn::Result     SetOutBoxGroupNumMax(u32 num);
    /*-----------------------------------------------*/

    u32     GetInBoxSessionNum() const;

 public:
    /* Please see man pages for details 
      

                  
                  
                  
                  
                  
                  
      
      
      
    */
    inline u32     GetBoxSessionNum(CecBoxType boxType) const
    {
        if(boxType == CEC_BOXTYPE_INBOX){
            return GetInBoxSessionNum();
        }
        else
        {
            NN_TASSERT_(boxType == CEC_BOXTYPE_OUTBOX);
            //return GetOutBoxSessionNum();
            return 0;
        }
    }

    /*-----------------------------------------------*/
    //

#if 1 // Use the BoxInfoReader Message information obtaining portion. Because it is duplicated, the portion originally in the Box class will be deleted in the future.
    //
    //
 protected:
    u32     GetInBoxMessHeader(CecMessageHeader& messHeader, const MessageId& messageId) const;
    u32     GetInBoxMessHeaderByIndex(CecMessageHeader& messHeader, u32 messIndex) const;

 public:
    /* Please see man pages for details 
      

                   
      
      
      
    */
    u8*     GetInBoxMessIdByIndex(u32 messIndex);

 protected:
    u32     GetOutBoxMessHeader(CecMessageHeader& messHeader, const MessageId& messageId) const;
    u32     GetOutBoxMessHeaderByIndex(CecMessageHeader& messHeader, u32 messIndex) const;
 public:

    /* Please see man pages for details 
      

                   
      
      
      
    */
    u8*     GetOutBoxMessIdByIndex(u32 messIndex);

    /* Please see man pages for details 
      

                   
      
      
      
      
    */
    size_t      GetMessSizeByMessId(CecBoxType boxType, const MessageId& messageId) const;
 protected:
    size_t      GetBodySizeByMessId(CecBoxType boxType, const MessageId& messageId) const;
    //
#endif

    CecMessageHeader*     GetMessHeaderByMessId(const CecBoxType boxType, const MessageId& messId) const;
 public:
    /* Please see man pages for details 
     
      
     
     
      
    */
    CecMessageHeader*     GetMessHeader(const CecBoxType boxType, const u32 messIndex) const;

    bool        MessageExists(CecBoxType boxType, const MessageId& messageId) const;
    //
    //

 public:
    /* Please see man pages for details 
     
     
     
     
     
     */
    inline u32     GetMessageMessSize(const CecBoxType boxType, const u32 messIndex) NN_ATTRIBUTE_DEPRECATED
    {
        return GetMessageSize(boxType, messIndex);
    } 
    /* Please see man pages for details 
     

                    
                    
                    
     
     
     
     
     */
    u32     GetMessageSize(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
     */
    u32     GetMessageBodySize(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    u32     GetMessageGroupId(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    u32     GetMessageSessionId(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
    
     
     
     
     
   
                    
                    
                    
     */
    inline MessageTypeFlag      GetMessageMessTypeFlag(const CecBoxType boxType, const u32 messIndex) NN_ATTRIBUTE_DEPRECATED
    {
        return GetMessageTypeFlag(boxType, messIndex);
    };
    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    MessageTypeFlag      GetMessageTypeFlag(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    SendMode      GetMessageSendMode(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    u8      GetMessageSendCount(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    u8      GetMessagePropagationCount(const CecBoxType boxType, const u32 messIndex) const;
    
    /* Please see man pages for details 
    
     
     
     
     
   
                    
                    
                    
     */
    bit8      GetMessageFlag_Unread(const CecBoxType boxType, const u32 messIndex) const;
    
    /* Please see man pages for details 
    
     
     
     
     
   
                    
                    
                    
     */
    bit8      GetMessageFlag_New(const CecBoxType boxType, const u32 messIndex) const;
    
    /* Please see man pages for details 
     

                    
                
     
     
     
     
                    
                    
                    
     */
    bit16      GetMessageTag(const CecBoxType boxType, const u32 messIndex) const;
    
    /* Please see man pages for details 
     
     
     
     

                    
                    
                    
                    
     */
    nn::fnd::DateTimeParameters     GetMessageSendDate(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     

                    
                    
                    
                    
     */
    nn::fnd::DateTimeParameters     GetMessageRecvDate(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
     
     
     
     
   
                    
                    
                    
     */
    nn::fnd::DateTimeParameters     GetMessageCreateDate(const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
    
     

                    
                    

     
     
     
     
        
        
        
     */
    inline nn::Result  GetMessageMessIdPair(MessageId* messId, const CecBoxType boxType, const u32 messIndex) NN_ATTRIBUTE_DEPRECATED
    {
        return  GetMessageIdPair(messId, boxType, messIndex);
    };
    /* Please see man pages for details 
     

                    
                    

     
     
     
     
        
        
        
     */
    nn::Result  GetMessageIdPair(MessageId* messId, const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
    
     

                    

     
     
     
     */
    inline MessageId   GetMessageMessIdPair(const CecBoxType boxType, const u32 messIndex) NN_ATTRIBUTE_DEPRECATED
    {
        return GetMessageIdPair(boxType, messIndex);
    } 
    /* Please see man pages for details 
     

                    

     
     
     
     */
    MessageId   GetMessageIdPair(const CecBoxType boxType, const u32 messIndex) const;


    /* Please see man pages for details 
    
     
     
     
     
     
        
        
        
     */
    inline nn::Result  GetMessageMessId(MessageId* messId, const CecBoxType boxType, const u32 messIndex) NN_ATTRIBUTE_DEPRECATED
    {
        return GetMessageId(messId, boxType, messIndex);
    }
    /* Please see man pages for details 
     
     
     
     
     
        
        
        
     */
    nn::Result  GetMessageId(MessageId* messId, const CecBoxType boxType, const u32 messIndex) const;

    /* Please see man pages for details 
    
     
     
     
     
     */
    inline MessageId   GetMessageMessId(const CecBoxType boxType, const u32 messIndex) NN_ATTRIBUTE_DEPRECATED
    {
        return GetMessageId(boxType, messIndex);
    }
    /* Please see man pages for details 
     
     
     
     
     */
    MessageId   GetMessageId(const CecBoxType boxType, const u32 messIndex) const;


    /* Please see man pages for details 
    
     
     
     
     
     */
    inline u32     GetMessIndex(CecBoxType boxType, MessageId& messId) NN_ATTRIBUTE_DEPRECATED{
        return GetMessageIndex(boxType, messId);
    };
    inline u32     GetMessIndex(CecBoxType boxType, u8* messId) NN_ATTRIBUTE_DEPRECATED{
        return GetMessageIndex(boxType, messId);
    } 
    
    /* Please see man pages for details 
     
     
     
     
     */
    u32     GetMessageIndex(CecBoxType boxType, const MessageId& messId) const;
    u32     GetMessageIndex(CecBoxType boxType, u8* messId) const;
    //
    
    /* Please see man pages for details 
      
      
                   
                    
      
      
    */
    u32             AppendOutBoxIndex(const MessageId& messageId);

    /* Please see man pages for details 
      
      
                   
                    
      
      
    */
    u32             RemoveOutBoxIndex(const MessageId& messageId);

    /* Please see man pages for details 
      
                   
                    
                    
      
      
    */
    u32             RoundOutBoxIndex(const MessageId& messageId);

 protected:
    /* Please see man pages for details 
      
      
    */
    u32             ResetOutBoxIndex();
    u32             ReadOutBoxIndex();
    nn::Result      WriteOutBoxIndex();

    nn::Result      IsAgreeEulaAppRequired() const;

 protected:
    //IPC
    virtual nn::Result OpenFile(const u32 cecTitleId, const u32 dataType, const u32 option, size_t* filesize ) const;
    virtual nn::Result ReadFile(void* readBuf, size_t readBufLen, size_t* readLen) const;
    virtual nn::Result WriteFile(const void* writeBuf, const size_t writeBufLen) const;
    virtual nn::Result ReadMessageFile(
        u32 cecTitleId, 
        u8 boxType, 
        const u8* pMessId, 
        size_t messIdLen, 
        size_t* pReadLen, 
        u8* pReadBuf, 
        size_t len);

    virtual nn::Result ReadMessageFileWithHmac(
        u32 cecTitleId, 
        u8 boxType, 
        const u8* pMessId, 
        size_t messIdLen, 
        size_t* pReadLen, 
        u8* pReadBuf, 
        size_t len, u8* pHmac);

    virtual nn::Result WriteMessageFile(
        u32 cecTitleId, 
        u8 boxType, 
        u8* pMessId, 
        size_t messIdLen, 
        const u8* pWriteBuf, 
        size_t len);
        
    virtual nn::Result WriteMessageFileWithHmac(
        u32 cecTitleId, 
        u8 boxType, 
        u8* pMessId, 
        size_t messIdLen, 
        const u8* pWriteBuf, 
        size_t len, u8* pHmac);
        
    virtual nn::Result Delete( u32 cecTitleId, u32 dataType, u8 boxType, const u8 pMessId[], size_t messIdLen );
    virtual nn::Result SetData(u32 cecTitleId, const u8* pSetBuf, size_t len, u32 option);
    virtual nn::Result ReadData(u8 *pReadBuf, size_t len, u32 option, const u8 optionData[], size_t optionDataLen) const;
    virtual nn::Result OpenAndWriteFile( const u8 pWriteBuf[], size_t writeBufLen, u32 cecTitleId, u32 dataType, u32 option ) const;
    virtual nn::Result OpenAndReadFile( u8 pReadBuf[], size_t readBufLen, size_t* pReadLen, u32 cecTitleId, u32 dataType, u32 option ) const ;
       
};

} // namespace CTR
} // namespace cec
} // namespace nn


#endif  //NN_CEC_CTR_CEC_MESSAGE_BOX_H_

