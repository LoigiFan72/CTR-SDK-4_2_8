/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_DeliverArg.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <string>
#include <nn/os.h>
#include <nn/util.h>
#include <nn/assert.h>

#include <nn/os/os_DeliverArg.h>

//---------------------------------------------------------------------------

namespace
{
    const u16 crc16_table[16] =
    {
        0x0000, 0xCC01, 0xD801, 0x1400,
        0xF001, 0x3C00, 0x2800, 0xE401,
        0xA001, 0x6C00, 0x7800, 0xB401,
        0x5000, 0x9C01, 0x8801, 0x4400
    };

    u16 CalcCRC16withIv(u16 iv, const void* buf, u32 size)
    {
        u16 r1;
        u16 total = iv;
        u8* data = (u8*)buf;

        while (size-- > 0)
        {
            // Lower 4 bits
            r1 = crc16_table[total & 0xf];
            total = (total >> 4) & 0x0fff;
            total = total ^ r1 ^ crc16_table[*data & 0xf];

            // Upper 4 bits
            r1 = crc16_table[total & 0xf];
            total = (total >> 4) & 0x0fff;
            total = total ^ r1 ^ crc16_table[(*data >> 4) & 0xf];

            data++;
        }
        return total;
    }

    s32 GetArgcCore(const char* p)
    {
        s32 n = 0;
        for (; *p; p++, n++)
        {
            while (*p)
            {
                p++;
            }
        }
        return n;
    }

    const char* GetArgvCore(const char* p, int n)
    {
        NN_TASSERT_(n >= 0);
        for (; *p && n > 0; p++, n--)
        {
            while (*p)
            {
                p++;
            }
        }
        return (*p) ? p : NULL;
    }
}

namespace nn { namespace os {

void DeliverArg::InitializeForEnc(DeliverArgInfo* pInfo, s32 nBinSize)
{
    NN_TASSERT_(2 <= (NN_OS_DELIVER_ARG_BUFFER_SIZE-nBinSize) && nBinSize >= 0);
    NN_TASSERT_(pInfo != NULL);

    m_pInfo = pInfo;

    // Buffer initialization
    ::std::memset(m_pInfo, 0, NN_OS_DELIVER_ARG_INFO_SIZE);

    // Initialize parameters.
    m_State = BUFFER_STATE_ACCESSIBLE | BUFFER_STATE_WRITABLE;
    m_pInfo->argBufferSize = (u16)(NN_OS_DELIVER_ARG_BUFFER_SIZE - nBinSize);
    m_pInfo->binarySize = 0;

    // Pointer initialization
    m_pBuf = m_pInfo->buf;
    *(m_pBuf + 0) = '\0';
    *(m_pBuf + 1) = '\0';
}

void DeliverArg::InitializeForDec(DeliverArgInfo* pInfo)
{
    NN_TASSERT_(pInfo != NULL);

    m_pInfo = pInfo;

    // Initialize parameters.
    m_State = BUFFER_STATE_ACCESSIBLE | BUFFER_STATE_WRITABLE;
}

nn::Result DeliverArg::SetString(const char* pString)
{
    // BufferState confirmation
    if ((m_State & BUFFER_STATE_WRITABLE) == 0)
    {
        return ResultDeliverArgNotReady();
    }

    // Buffer length confirmation
    s32 length = ::std::strlen(pString);
    if (length > m_pInfo->argBufferSize - (m_pBuf - m_pInfo->buf) - 2)
    {
        return ResultDeliverArgOverSize();
    }

    // Copy of argument string
    ::std::strcpy((char*)m_pBuf, pString);
    m_pBuf += length;
    *m_pBuf++ = '\0';
    *m_pBuf   = '\0';

    return ResultSuccess();
}

nn::Result DeliverArg::SetString(const char* pString, char cs)
{
    int length;
    const char* endp;

    // BufferState confirmation
    if ((m_State & BUFFER_STATE_WRITABLE) == 0)
    {
        return ResultDeliverArgNotReady();
    }

    while (true)
    {
        // Separator skip
        while (*pString == cs)
        {
            pString++;
        }

        // End if NULL
        if (*pString == '\0')
        {
            break;
        }

        // Search separator
        endp = pString;
        while (*endp != cs && *endp != '\0')
        {
            endp++;
        }
        length = endp - pString;

        // Buffer size confirmation
        if (length > m_pInfo->argBufferSize - (m_pBuf - m_pInfo->buf) - 2)
        {
            return ResultDeliverArgOverSize();
        }

        // String copy
        while(pString != endp)
        {
            *m_pBuf++ = *(u8*)pString++;
        }
        *m_pBuf++ = '\0';
        *m_pBuf   = '\0';
    }

    return ResultSuccess();
}

nn::Result DeliverArg::SetBinary(const void* pBinary, s32 nSize)
{
    // BufferState confirmation
    if ((m_State & BUFFER_STATE_WRITABLE) == 0)
    {
        return ResultDeliverArgNotReady();
    }

    // Buffer length confirmation
    if (nSize > NN_OS_DELIVER_ARG_BUFFER_SIZE - m_pInfo->argBufferSize - m_pInfo->binarySize)
    {
        return ResultDeliverArgOverSize();
    }

    // Binary data copy
    u8* pDest = &m_pInfo->buf[m_pInfo->argBufferSize + m_pInfo->binarySize];
    ::std::memcpy(pDest, pBinary, nSize);
    m_pInfo->binarySize += (u16)nSize;

    return ResultSuccess();
}

void DeliverArg::ConvertToArguments(const char *pString, char cs, char *pBuffer, s32 nBufferSize)
{
    char   *p = pBuffer;
    char   *pEnd = pBuffer + nBufferSize;
    bool    isQuoted = false;

    while (true)
    {
        // Separator skip
        while (*pString == cs && p < pEnd)
        {
            pString++;
        }

        // Store argument string
        while (*pString && p < pEnd)
        {
            // Confirm whether quote
            if (*pString == '\"')
            {
                isQuoted = (isQuoted == false);
                pString++;
                continue;
            }

            // break if separator is found
            else if (*pString == cs && isQuoted == false)
            {
                break;
            }

            *p++ = *pString++;
        }

        // End if end of buffer
        if (p >= pEnd)
        {
            *(pEnd - 2) = '\0';
            *(pEnd - 1) = '\0';
            break;
        }

        // End if end of string
        if (*pString == '\0')
        {
            while ((p + 1) >= pEnd)
            {
                p--;
            }
            *p++ = '\0';
            *p = '\0';
            break;
        }

        // Insert '\0' and continue if separator
        if (*pString == cs)
        {
            *p++ = '\0';
        }
    }

    // Quit
    if (p < pEnd)
    {
        *p++ = '\0';
    }
}

void DeliverArg::SetTitleId(bit64 titleId)
{
    m_TitleId = titleId;
}

void DeliverArg::SetMakerCode(bit16 makerCode)
{
    m_MakerCode = makerCode;
}

nn::Result DeliverArg::Encode(void)
{
    // BufferState confirmation
    if ((m_State & BUFFER_STATE_ACCESSIBLE) == 0)
    {
        return ResultDeliverArgNotReady();
    }

    // makerCode and titleId settings
    m_pInfo->makerCode = m_MakerCode;
    m_pInfo->titleId   = m_TitleId;

    // flag settings
    m_pInfo->flag = NN_OS_DELIVER_ARG_FLAG_ENCODE | NN_OS_DELIVER_ARG_FLAG_VALID;

    // CRC calculation
    m_pInfo->crc = 0;
    m_pInfo->crc = CalcCRC16withIv(0xffff, reinterpret_cast<const void*>(m_pInfo), sizeof(DeliverArgInfo));

    return ResultSuccess();
}

nn::Result DeliverArg::Decode(void)
{
    // DeliverArg validity confirmation
    if (IsValid() == false)
    {
        return ResultDeliverArgNotReady();
    }

    // Buffer confirmation
    if (m_pInfo == NULL)
    {
        return ResultDeliverArgNotReady();
    }

    // Checks CRC.
    u16 crc = m_pInfo->crc;
    m_pInfo->crc = 0;
    m_pInfo->crc = CalcCRC16withIv(0xffff, reinterpret_cast<const void*>(m_pInfo), sizeof(DeliverArgInfo));

    if (crc != m_pInfo->crc)
    {
        SetStateInvalid();
        return ResultInvalidDeliverArg();
    }

    // Error code flag release
    m_pInfo->flag &= ~NN_OS_DELIVER_ARG_FLAG_ENCODE;

    // BufferState update
    m_State = BUFFER_STATE_ACCESSIBLE;

    return ResultSuccess();
}

u32 DeliverArg::GetState(void)
{
    return m_State;
}

void DeliverArg::SetState(u32 state)
{
    m_State = state;
}

void DeliverArg::SetStateInvalid(void)
{
    m_State = BUFFER_STATE_INVALID;
}

s32 DeliverArg::GetBinarySize(void)
{
    if ((m_State & BUFFER_STATE_ACCESSIBLE) == 0)
    {
        return -1;
    }

    return m_pInfo->binarySize;
}

nn::Result DeliverArg::GetBinary(void* pBinary, int* pSize, int nMaxSize)
{
    nn::Result result;
    s32 nCopySize;

    // BufferState confirmation
    if ((m_State & BUFFER_STATE_ACCESSIBLE) == 0)
    {
        return ResultDeliverArgNotReady();
    }

    // Buffer length confirmation
    if (nMaxSize < m_pInfo->binarySize)
    {
        result = ResultDeliverArgOverSize();
        nCopySize = nMaxSize;
    }
    else
    {
        result = ResultSuccess();
        nCopySize = m_pInfo->binarySize;
    }

    // Binary data copy
    ::std::memcpy(pBinary, &m_pInfo->buf[m_pInfo->argBufferSize], nCopySize);
    if (pSize)
    {
        *pSize = nCopySize;
    }

    return result;
}

bit64 DeliverArg::GetTitleId(void)
{
    return (m_State & BUFFER_STATE_ACCESSIBLE) ? m_pInfo->titleId : 0;
}

bit32 DeliverArg::GetGameCode(void)
{
    return (m_State & BUFFER_STATE_ACCESSIBLE) ? *(reinterpret_cast<u32*>(&m_pInfo->titleId)) : 0;
}

bit16 DeliverArg::GetMakerCode(void)
{
    return (m_State & BUFFER_STATE_ACCESSIBLE) ? m_pInfo->makerCode : 0;
}

bool DeliverArg::IsValid(void)
{
    return (m_pInfo->flag & NN_OS_DELIVER_ARG_FLAG_VALID) ? true : false;
}

bool DeliverArg::IsEncoded(void)
{
    return (m_pInfo->flag & (NN_OS_DELIVER_ARG_FLAG_ENCODE | NN_OS_DELIVER_ARG_FLAG_VALID)) ? true : false;
}

nn::Result DeliverArg::SetSysParam(bit16 param)
{
    if (m_pInfo && (m_State & BUFFER_STATE_WRITABLE) == 0)
    {
        return ResultDeliverArgNotReady();
    }
    m_pInfo->sysParam = param;
    return ResultSuccess();
}

u16 DeliverArg::GetSysParam(void)
{
    if (m_pInfo && (m_State & BUFFER_STATE_ACCESSIBLE) == 0)
    {
        return 0;
    }
    return m_pInfo->sysParam;
}

s32 DeliverArg::GetArgc(void)
{
    if (m_pInfo && m_State == BUFFER_STATE_ACCESSIBLE)
    {
        return GetArgcCore(reinterpret_cast<const char*>(m_pInfo->buf)) + 1;
    }
    return 0;
}

const char* DeliverArg::GetArgv(int n)
{
    static const char* procName = "main";
    NN_TASSERT_(n >= 0);

    if (m_pInfo && m_State == BUFFER_STATE_ACCESSIBLE)
    {
        return (n == 0) ? procName: GetArgvCore(reinterpret_cast<const char*>(m_pInfo->buf), n - 1);
    }
    return NULL;
}

}} // namespace nn::os
