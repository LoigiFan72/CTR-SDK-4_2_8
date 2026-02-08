/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_MessageId.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_MESSAGEID_H_
#define NN_CEC_CTR_CEC_MESSAGEID_H_

#include <nn/cec/CTR/cec_Const.h>
#include <nn/config.h>

namespace nn {
namespace cec {
namespace CTR {

    // Leave for the sake of compatibility
    typedef u8  CECMessageId[CEC_SIZEOF_MESSAGEID];
    
    /* Please see man pages for details 
     

                
                
                
                
                
                
                
     */
    class MessageId
    {
    public:
        static const size_t SIZE = CEC_SIZEOF_MESSAGEID;     // 8
        static const size_t ENCODED_SIZE = 12 /*(SIZE * 4 / 3) +  (3 - (SIZE * 4 / 3) % 3)*/;

        /* Please see man pages for details 
         
         */
        MessageId(void);
        /* Please see man pages for details 
         
         
         */
        explicit MessageId(const u8 msgId[SIZE]);
        explicit MessageId(const char* msgId);
        explicit MessageId(CECMessageId msgId);// NN_ATTRIBUTE_DEPRECATED;

        /* Please see man pages for details 
         
         
         */
        const u8* GetBinary(void) const;

        /* Please see man pages for details 
         
         
         */
        void GetBinary(u8 msgId[SIZE]) const;
        /* Please see man pages for details 
         
         
         */
        bool IsEqual(const u8 msgId[SIZE]) const;

        /* Please see man pages for details 
         
         
         
         */
        bool IsEmpty(void) const;
        /* Please see man pages for details 
         
         
         
         */
        const char* GetString(void) const;
        /* Please see man pages for details 
         
         
         
         */
        const char* GetEncodedString(void) const;

    private:
        u8      m_data[SIZE];
    };

    inline const u8* MessageId::GetBinary(void) const
    {
        return m_data;
    }


} // namespace CTR
} // namespace cec
} // namespace nn


#endif  //NN_CEC_CTR_CEC_MESSAGEID_H_

