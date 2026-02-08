/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DateTime.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47227 $
 *---------------------------------------------------------------------------*/

#include <nn/fnd/fnd_DateTime.h>
#include <nn/os/os_SharedInfo.h>
#include <nn/assert.h>
#include <nn/ptm/CTR/ptm_Rtc.h>
#include <algorithm>

namespace
{
    static const s32 MILLISECONDS_DAY = 1000 * 60 * 60 * 24;

    inline s32 Modulo32(s32 a, s32 b)
    {
        return (((a % b) + b) % b);
    }

    inline s32 AlignedDays(s64 milliSeconds)
    {
        s64 ms = milliSeconds + ( 730119LL * MILLISECONDS_DAY);
        return ms / MILLISECONDS_DAY - 730119LL;
    }

    inline s32 MilliSecondsOnDay(s64 milliSeconds)
    {
        s64 ms = milliSeconds + (730119LL * MILLISECONDS_DAY);
        return ms % MILLISECONDS_DAY;
    }
}

namespace nn { namespace fnd {

    const DateTime DateTime::MAX_DATETIME = DateTime(DateTime::MAX_MILLISECONDS);
    const DateTime DateTime::MIN_DATETIME = DateTime(DateTime::MIN_MILLISECONDS);

    s32 DateTime::IsLeapYear(s32 year)
    {
        if ( year % 400 == 0 )
        {
            return 1;
        }
        else if ( year % 100 == 0 )
        {
            return 0;
        }
        else if ( year % 4 == 0 )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    bool DateTime::IsValidDate(s32 year, s32 month, s32 day)
    {
        const s32 monthdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        const s64 startYear = DateTime(MIN_MILLISECONDS).GetYear();
        const s64 endYear   = DateTime(MAX_MILLISECONDS).GetYear();
        
        if ( !(startYear <= year && year <= endYear) )
        {
            return false;
        }

        if ( !(1 <= month && month <= 12) )
        {
            return false;
        }

        s32 mdays;
        if ( month == 2 )
        {
            mdays = monthdays[month-1] + IsLeapYear(year);
        }
        else
        {
            mdays = monthdays[month-1];
        }

        return 1 <= day && day <= mdays;
    }

    bool DateTime::IsValidParameters(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 millisecond)
    {
        return IsValidDate(year,month,day)
            && 0 <= hour   && hour   < 24
            && 0 <= minute && minute < 60
            && 0 <= second && second < 60
            && 0 <= millisecond && millisecond < 1000;
    }

    bool DateTime::IsValidParameters(const DateTimeParameters &dateTimeParameters)
    {
        return IsValidParameters(
                dateTimeParameters.year,
                dateTimeParameters.month,
                dateTimeParameters.day,
                dateTimeParameters.hour,
                dateTimeParameters.minute,
                dateTimeParameters.second,
                dateTimeParameters.milliSecond)
            && dateTimeParameters.week
                == DaysToWeekday(DateToDays(
                    dateTimeParameters.year,
                    dateTimeParameters.month,
                    dateTimeParameters.day));
    }

    s32  DateTime::DateToDays(s32 year, s32 month, s32 day)
    {
        NN_TASSERT_(DateTime::IsValidDate(year,month,day));

        day -= 1;
        year -= 2000;

        if ( month <= 2 ){
            month += (12 - 3);
            year -= 1;
        }
        else{
            month -= 3;
        }

        int offset = 1;

        if ( year < 0 )
        {
            offset = IsLeapYear(year);
        }

        return ((((365 * 4 + 1) * 25 - 1) * 4 + 1) * (year / 100) / 4)
             + (( 365 * 4 + 1) * (year % 100) / 4)
             + (153 * month + 2) / 5
             + day + (31 + 28)
             + offset;
    }

    void DateTime::DaysToDate(s32 *pYear, s32 *pMonth, s32 *pDay, s32 days)
    {
        const s32 c4days = (((365 * 4 + 1) * 25 - 1) * 4 + 1);
        const s32 c1days =  ((365 * 4 + 1) * 25 - 1);
        const s32 y4days =   (365 * 4 + 1);
        const s32 y1days =    365;
        s32 year, month, day;

        days -= 31 + 29;

        s32 c4    = days / c4days;
        s32 c4ds  = days % c4days;

        if ( c4ds < 0)
        {
            c4ds += c4days;
            c4 -= 1;
        }

        s32 c1    = c4ds / c1days;
        s32 c1ds  = c4ds % c1days;
        s32 y4    = c1ds / y4days;
        s32 y4ds  = c1ds % y4days;
        s32 y1    = y4ds / y1days;
        s32 ydays = y4ds % y1days;

        year = 2000 + c4 * 400 + c1 * 100 + y4 * 4 + y1;
        month = (5 * ydays + 2) / 153;
        day = ydays - (153 * month + 2) / 5 + 1;

        if (y1 == 4 || c1 == 4)
        {
            month = 2 + (12 - 3);
            day = 29;
            year -= 1;
        }

        if ( month <= (12-3) )
        {
            month += 3;
        }
        else
        {
            month -= 12 - 3;
            year += 1;
        }

        if ( pYear )
        {
            *pYear = year;
        }
        if ( pMonth )
        {
            *pMonth = month;
        }
        if ( pDay )
        {
            *pDay = day;
        }
    }

    Week DateTime::DaysToWeekday(s32 days)
    {
        return static_cast<Week>(Modulo32((days + WEEK_SATURDAY), WEEK_MAX));
    }

    DateTime::DateTime(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 millisecond)
        :m_MilliSeconds(
            DateTime::FromParameters(year,month,day,hour,minute,second,millisecond).m_MilliSeconds)
    {
        NN_TASSERT_(MIN_MILLISECONDS <= m_MilliSeconds && m_MilliSeconds <= MAX_MILLISECONDS);
    }


    s32  DateTime::GetYear() const
    {
        s32 year;
        DaysToDate(
            &year,
            NULL,
            NULL,
            AlignedDays(m_MilliSeconds));
        return year;
    }

    s32  DateTime::GetMonth() const
    {
        s32 month;
        DaysToDate(
            NULL,
            &month,
            NULL,
            AlignedDays(m_MilliSeconds));
        return month;
    }

    s32  DateTime::GetDay() const
    {
        s32 day;
        DaysToDate(
            NULL,
            NULL,
            &day,
            AlignedDays(m_MilliSeconds));
        return day;
    }

    Week DateTime::GetWeek() const
    {
        return DaysToWeekday(
            AlignedDays(m_MilliSeconds));
    }

    s32  DateTime::GetHour() const        
    {
        return MilliSecondsOnDay(m_MilliSeconds) / 1000 / 60 / 60 % 24; 
    }
    
    s32  DateTime::GetMinute() const      
    {
        return MilliSecondsOnDay(m_MilliSeconds) / 1000 / 60 % 60; 
    }
    
    s32  DateTime::GetSecond() const      
    {
        return MilliSecondsOnDay(m_MilliSeconds) / 1000 % 60;
    }

    s32  DateTime::GetMilliSecond() const 
    {
        return MilliSecondsOnDay(m_MilliSeconds) % 1000;
    }

    DateTime DateTime::FromParameters(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 millisecond)
    {
        NN_TASSERT_(IsValidParameters(year, month, day, hour, minute, second, millisecond));
        DateTime datetime;
        datetime.m_MilliSeconds = 
            millisecond
          + 1000LL * second
          + 1000LL * 60 * minute
          + 1000LL * 60 * 60 * hour
          + 1000LL * 60 * 60 * 24 * static_cast<s64>(DateToDays(year,month,day));
        return datetime;
    }

    DateTime DateTime::FromParameters(const DateTimeParameters &dateTimeParameters)
    {
        return FromParameters(
            dateTimeParameters.year,
            dateTimeParameters.month,
            dateTimeParameters.day,
            dateTimeParameters.hour,
            dateTimeParameters.minute,
            dateTimeParameters.second,
            dateTimeParameters.milliSecond);
    }

    DateTime DateTime::ReplaceMilliSecond(s32 millisecond) const
    {
        NN_TASSERT_(0 <= millisecond && millisecond < 1000);
        return *this + TimeSpan::FromMilliSeconds(millisecond - GetMilliSecond());
    }

    DateTime DateTime::ReplaceSecond(s32 second) const
    {
        NN_TASSERT_(0 <= second && second < 60);
        return *this + TimeSpan::FromSeconds(second - GetSecond());
    }

    DateTime DateTime::ReplaceMinute(s32 minute) const
    {
        NN_TASSERT_(0 <= minute && minute < 60);
        return *this + TimeSpan::FromMinutes(minute - GetMinute());
    }

    DateTime DateTime::ReplaceHour(s32 hour) const
    {
        NN_TASSERT_(0 <= hour && hour < 24);
        return *this + TimeSpan::FromHours(hour - GetHour());
    }

    DateTime DateTime::ReplaceDay(s32 day) const
    {
        s32 year,month;
        DaysToDate(
            &year,
            &month,
            NULL,
            AlignedDays(m_MilliSeconds));
        return FromParameters(
            year,
            month,
            day,
            GetHour(),
            GetMinute(),
            GetSecond(),
            GetMilliSecond());
    }

    DateTime DateTime::ReplaceMonth(s32 month) const
    {
        s32 year,day;
        DaysToDate(
            &year,
            NULL,
            &day,
            AlignedDays(m_MilliSeconds));
        return FromParameters(
            year,
            month,
            day,
            GetHour(),
            GetMinute(),
            GetSecond(),
            GetMilliSecond());
    }

    DateTime DateTime::ReplaceYear(s32 year) const
    {
        s32 month,day;
        DaysToDate(
            NULL,
            &month,
            &day,
            AlignedDays(m_MilliSeconds));
        return FromParameters(
            year, 
            month,
            day,
            GetHour(), 
            GetMinute(), 
            GetSecond(), 
            GetMilliSecond());
    }

    DateTime DateTime::GetNow()
    {
        return nn::fnd::DateTime::MIN_DATETIME
#ifdef NN_PROCESSOR_ARM11MPCORE
             + nn::fnd::TimeSpan::FromMilliSeconds(nn::ptm::CTR::detail::GetSwcMilliSeconds())
#endif
            ;
    }

    DateTimeParameters DateTime::GetParameters() const
    {
        DateTimeParameters parameters;

        s32 msec = MilliSecondsOnDay(m_MilliSeconds);
        s32 days = AlignedDays(m_MilliSeconds);
        s32 year,month,day;

        DaysToDate(&year,&month,&day, days);

        parameters.year = year;
        parameters.month = month;
        parameters.day = day;
        parameters.week = DaysToWeekday(days);
        parameters.hour = msec / (1000 * 60 * 60);
        parameters.minute = msec / (1000 * 60) % 60;
        parameters.second = msec / 1000 % 60;
        parameters.milliSecond = msec % 1000;

        return parameters;
    }
}}

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
