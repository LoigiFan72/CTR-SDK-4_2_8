/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47558 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_API_H_
#define NN_CEC_CTR_CEC_API_H_

#include <nn/types.h>
#include <nn/fnd.h>

namespace nn {
namespace cec {
namespace CTR {

    enum CecFileType
    {
        FILETYPE_MESSAGE_BOX_LIST = 1,
        FILETYPE_MESSAGE_BOX_INFO = 2,
        FILETYPE_INBOX_INFO       = 3,
        FILETYPE_OUTBOX_INFO      = 4,
        FILETYPE_OUTBOX_INDEX     = 5,
        FILETYPE_INBOX_MESSAGE    = 6,
        FILETYPE_OUTBOX_MESSAGE   = 7,
        FILETYPE_CEC_BASE_DIR    = 10,
        FILETYPE_MESSAGE_BOX_DIR    = 11,
        FILETYPE_MESSAGE_INBOX_DIR  = 12,
        FILETYPE_MESSAGE_OUTBOX_DIR = 13,

        FILETYPE_END,

        FILETYPE_BOXDATA_START = 100,
        
        FILETYPE_BOXDATA_ICON,     //
        FILETYPE_BOXDATA_NAME_1 = 110,   //
        FILETYPE_BOXDATA_NAME_2,   //
        FILETYPE_BOXDATA_NAME_3,   //
        FILETYPE_BOXDATA_NAME_4,   //
        FILETYPE_BOXDATA_TEXT_1 = 120,   //
        FILETYPE_BOXDATA_TEXT_2,   //
        FILETYPE_BOXDATA_TEXT_3,   //
        FILETYPE_BOXDATA_TEXT_4,   //
        FILETYPE_BOXDATA_DATA_1 = 130,   //
        FILETYPE_BOXDATA_DATA_2,   //
        FILETYPE_BOXDATA_DATA_3,   //
        FILETYPE_BOXDATA_DATA_4,   //
        FILETYPE_BOXDATA_FLAG_1 = 140,   //
        FILETYPE_BOXDATA_FLAG_2,   //
        FILETYPE_BOXDATA_FLAG_3,   //
        FILETYPE_BOXDATA_FLAG_4,   //
        FILETYPE_BOXDATA_PROGRAM_ID = 150,

        FILETYPE_BOXDATA_END = 200,
        
        FILETYPE_ANY               = 0xff
    };

    
/* Please see man pages for details 
 
 
 */
    typedef enum CecBoxDataType
    {
        BOXDATA_TYPE_START = FILETYPE_BOXDATA_START,    //
        BOXDATA_TYPE_ICON,           //
        BOXDATA_TYPE_NAME_1 = FILETYPE_BOXDATA_NAME_1,   //
        BOXDATA_TYPE_END   = FILETYPE_BOXDATA_END     //
    }BoxDataType;

    typedef enum CecBoxDataTypeEx
    {
        //BOXDATA_TYPE_START = FILETYPE_BOXDATA_START,    // Unused
        
        //BOXDATA_TYPE_ICON,     // ICON
        //BOXDATA_TYPE_NAME_1 = 110,   // NAME1
        BOXDATA_TYPE_NAME_2 = BOXDATA_TYPE_NAME_1+1,   //
        BOXDATA_TYPE_NAME_3,   //
        BOXDATA_TYPE_NAME_4,   //
        BOXDATA_TYPE_TEXT_1 = FILETYPE_BOXDATA_TEXT_1,   //
        BOXDATA_TYPE_TEXT_2,   //
        BOXDATA_TYPE_TEXT_3,   //
        BOXDATA_TYPE_TEXT_4,   //
        BOXDATA_TYPE_DATA_1 = FILETYPE_BOXDATA_DATA_1,   //
        BOXDATA_TYPE_DATA_2,   //
        BOXDATA_TYPE_DATA_3,   //
        BOXDATA_TYPE_DATA_4,   //
        BOXDATA_TYPE_FLAG_1 = FILETYPE_BOXDATA_FLAG_1,   //
        BOXDATA_TYPE_FLAG_2,   //
        BOXDATA_TYPE_FLAG_3,   //
        BOXDATA_TYPE_FLAG_4,   //
        BOXDATA_TYPE_PROGRAM_ID = FILETYPE_BOXDATA_PROGRAM_ID   //

        //BOXDATA_TYPE_END = FILETYPE_BOXDATA_END       // Unused
    }BoxDataTypeEx;


    namespace
    {
        const bit32 FILEOPT_READ         = (1<<1);
        const bit32 FILEOPT_WRITE        = (1<<2);
        const bit32 FILEOPT_READWRITE    = FILEOPT_READ|FILEOPT_WRITE;
        const bit32 FILEOPT_MKDIR        = (1<<3);
        const bit32 FILEOPT_NOCHECK      = (1<<4);
        const bit32 FILEOPT_DUMP         = (1<<30);
    }
    


u8* Base64CecTitleId2Str(u32 cecTitleId);
u32 Base64Str2CecTitleId(const u8* str);


void CecBinaryDump(const void* data, u32 len, u8 type);
void DateParam2Str(char* outStr, nn::fnd::DateTimeParameters date);


void SetAllocFunc(nn::fnd::IAllocator& cecAllocFunc);
void InitializeAllocFunc(uptr bufferAddress, size_t bufferSize);
void FinalizeAllocFunc(void);


} // namespace CTR
} // namespace cec
} // namespace nn


#endif  //NN_CEC_CTR_CEC_API_H_

