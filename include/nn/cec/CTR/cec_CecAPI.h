/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_CecAPI.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_CEC_API_H_
#define NN_CEC_CTR_CEC_CEC_API_H_

#include <nn/cec/CTR/cec_Cec.h>

namespace nn {
namespace cec {
namespace CTR {

namespace detail {

    namespace
    {
        // For general applications, application that gets state (SPIDER), and BOSS.
        const char PORT_NAME_CEC[]      = "cecd:u";
        // MMEN NEWS
        const char PORT_NAME_CEC_SYS[]  = "cecd:s";
        // For NDM
        const char PORT_NAME_CEC_NDM[]  = "cecd:ndm";
    }


    Result InitializeCecControl();
    Result InitializeCecControlSys();
    Result FinalizeCecControl();
    Result FinalizeCecControlSys();

    Result WaitForSessionValid();


    Result Open(u32 cecTitleId, u32 dataType, u32 option, size_t* filesize);
    Result Read(size_t* pReadLen, u8 pReadBuf[], size_t len);
    Result ReadMessage(u32 cecTitleId, u8 in_or_out_box, const u8 pMessId[], size_t messIdLen, size_t* pReadLen, u8 pReadBuf[], size_t len);
    Result ReadMessageWithHmac(u32 cecTitleId, u8 in_or_out_box, const u8 pMessId[], size_t messIdLen, size_t* pReadLen, u8 pReadBuf[], size_t len , const u8 pHmac[]);
    Result Write(const u8 pWriteBuf[], size_t len);
    Result WriteMessage(u32 cecTitleId, u8 in_or_out_box, u8 pMessId[], size_t messIdLen, const u8 pWriteBuf[], size_t len);
    Result WriteMessageWithHmac(u32 cecTitleId, u8 in_or_out_box, u8 pMessId[], size_t messIdLen, const u8 pWriteBuf[], size_t len , const u8 pHmac[]);
    Result Delete(u32 cecTitleId, u32 dataType, u8 in_or_out_box, const u8 pMessId[], size_t messIdLen);

    nn::Result SetData(u32 cecTitleId, const u8 pData[], size_t len, u32 option);
    nn::Result ReadData(u8 pReadBuf[], size_t len, u32 option , const u8 optionData[], size_t optionDataLen);

    Result Start(u32 option);
    Result Stop(u32 option);

    Result GetCecdState(u32* state);
    Result GetCecInfoBuffer(u32 cecTitleId, u8 pCecInfoBuffer[], size_t size);
    Result GetCecInfoEventHandle(nn::Handle* pEventHandle);
    Result GetChangeStateEventHandle(nn::Handle* pEventHandle);
    Result OpenAndReadFile(u8* readBuf, size_t readBufLen, size_t* readLen,
        u32 fileCecTitleId, u32 fileDataType, u32 fileOption);
    Result OpenAndWriteFile(const u8* writeBuf, size_t writeBufLen, 
        u32 fileCecTitleId, u32 fileDataType, u32 fileOption);

    nn::Result GetEventLog(u8 pStreetPassEventsBuf[], s32* pEnd, s32 start, s32 length);
    nn::Result GetEventLogStart(s32* pStart);
    nn::Result GetEventLogLength(s32* pLength);
    nn::Result CalcEventLogStart(s32* pNewStart, s32 start, s32 offset);


    //Result SystemOpenBox( u32 cecTitleId );
    Result SetCecTestMode(bit8 testMode);
    Result GetCecInfoEventHandleSys(nn::Handle* pEventHandle);

} // end of namespace detail
} // end of namespace CTR
} // end of namespace cec
} // end of namespace nn



#endif  // ifndef NN_CEC_CTR_CEC_CEC_API_H_
