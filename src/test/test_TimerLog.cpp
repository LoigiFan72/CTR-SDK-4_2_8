/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_TimerLog.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#include <nn/test/test_TimerLog.h>

namespace nn{ 
namespace test{

int TimerLog::s_Counter = 0;
int TimerLog::s_CounterMax = 0;
TimerLog *TimerLog::s_pHead = 0;
s64 TimerLog::s_BaseTick = 0;
TimerLog *TimerLog::s_pAverageBuffer = 0;
size_t TimerLog::s_AverageBufferSize = 0;
size_t TimerLog::s_AverageRepeatNum = 0;
size_t TimerLog::s_AverageElementNum = 0;

void TimerLog::Initialize(int num)
{
    Finalize();
    s_pHead = new TimerLog[num];
    s_Counter = 0;
    s_CounterMax = num;
    s_BaseTick = nn::os::Tick::GetSystemCurrent();
}
void TimerLog::Finalize()
{
    if (s_pHead)
    {
        delete[] s_pHead;
    }
}

void TimerLog::ResetTimerLog()
{
    s_BaseTick = nn::os::Tick::GetSystemCurrent();
    s_Counter = 0;
}

void TimerLog::Reset()
{
    s_Counter = 0;
    s_BaseTick = nn::os::Tick::GetSystemCurrent();
}

void TimerLog::InitializeAverage(size_t bufSize)
{
    if (s_pAverageBuffer)
    {
        delete[] s_pAverageBuffer;
    }
    s_pAverageBuffer = new TimerLog[bufSize];

    if (s_pAverageBuffer)
    {
        s_AverageBufferSize = bufSize;
    }
    else
    {
        nn::dbg::detail::TPrintf("[TimerLog] AverageBuffer Out of memory.\n");
    }

    s_AverageRepeatNum = 0;
}

void TimerLog::FinalizeAverage()
{
    if (s_pAverageBuffer)
    {
        delete[] s_pAverageBuffer;
    }
}

void TimerLog::StartAverage()
{
    s_AverageRepeatNum = 0;
    s_AverageElementNum = 0;
    s_BaseTick = nn::os::Tick::GetSystemCurrent();
    for (int i = 0; i < s_AverageBufferSize; ++i)
    {
        s_pAverageBuffer[i].m_Tick = 0;
    }
}

void TimerLog::EndAverage(bool showLog, bool reset)
{
    if (s_AverageRepeatNum)
    {
        for (int i = 0; i < s_AverageElementNum; i++)
        {
            s_pAverageBuffer[i].m_charTag = s_pHead[i].m_charTag;
            s_pAverageBuffer[i].m_s32Tag = s_pHead[i].m_s32Tag;
            s_pAverageBuffer[i].m_Line = s_pHead[i].m_Line;
            s_pAverageBuffer[i].m_Tick /= s_AverageRepeatNum;
        }
    }

    if (showLog)
    {
        ShowAverageLog(reset);
    }
    else if (reset)
    {
        Reset();
    }
}

void TimerLog::RenewAverage(bool reset)
{
    int imax = (s_Counter < s_CounterMax) ? s_Counter : s_CounterMax;
    if (imax > s_AverageBufferSize)
        imax = s_AverageBufferSize;

    s64 base = s_BaseTick;
    for (int i = 0; i < imax; i++)
    {
        s_pAverageBuffer[i].m_Tick += s_pHead[i].m_Tick - base;
        base = s_pHead[i].m_Tick;
    }

    if (s_AverageElementNum < imax)
        s_AverageElementNum = imax;

    s_AverageRepeatNum++;

    if (reset)
    {
        Reset();
    }
}

void TimerLog::ShowAverageLog(bool reset)
{
    for (int i = 0; i < s_AverageElementNum; ++i)
    {
        s_pAverageBuffer[i].ShowElementLogAverageTime();
    }
    if (reset)
    {
        Reset();
    }
}

void TimerLog::AddTimerLog(char charTag, s32 s32Tag, int line)
{
    if (s_Counter < s_CounterMax)
    {
        s_pHead[s_Counter].m_charTag = charTag;
        s_pHead[s_Counter].m_s32Tag = s32Tag;
        s_pHead[s_Counter].m_Line = line;
        s_pHead[s_Counter++].m_Tick = nn::os::Tick::GetSystemCurrent();
    }
    else if (s_Counter < 0x7FFFFFFF)
    {
        s_Counter++;
    }
}

void TimerLog::ShowTimerLog(bool absolute, bool reset)
{
    int imax = (s_Counter < s_CounterMax) ? s_Counter : s_CounterMax;
    if (absolute)
    {
        for (int i = 0; i < imax; i++)
        {
            s_pHead[i].ShowLogAbsTime();
        }
    }
    else
    {
        s64 base = s_BaseTick;
        for (int i = 0; i < imax; i++)
        {
            s_pHead[i].ShowLogRelTime(base);
            base = s_pHead[i].m_Tick;
        }
    }

    if (s_Counter > s_CounterMax)
    {
        nn::dbg::detail::TPrintf("[TimerLog] %d logs were skipped (out of log buffer)\n", s_Counter - s_CounterMax);
    }

    if (reset)
    {
        Reset();
    }
}


} // namespace test
} // namespace nn

