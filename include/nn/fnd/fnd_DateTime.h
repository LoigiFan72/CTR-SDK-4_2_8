/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DateTime.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47798 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_DATETIME_API_H_
#define NN_FND_DATETIME_API_H_

/* Please see man pages for details 

    
*/

#include <nn/types.h>
#include <nn/assert.h>
#include <nn/fnd/fnd_TimeSpan.h>

#ifdef __cplusplus

namespace nn {
namespace fnd {

/* Please see man pages for details 
    
*/
enum Week
{
    WEEK_SUNDAY = 0,   //
    WEEK_MONDAY,       //
    WEEK_TUESDAY,      //
    WEEK_WEDNESDAY,    //
    WEEK_THURSDAY,     //
    WEEK_FRIDAY,       //
    WEEK_SATURDAY,     //
    WEEK_MAX
};

/* Please see man pages for details 
    
*/
struct DateTimeParameters
{
    s32     year;         //
    s8      month;        //
    s8      day;          //
    Week    week;         //
    s8      hour;         //
    s8      minute;       //
    s8      second;       //
    s16     milliSecond;  //
};

/* Please see man pages for details 
    

    

    

    
    

    
    
    
    

*/
class DateTime
{
public:
    /* Please see man pages for details 
        

        
    */
    DateTime() : m_MilliSeconds(0) {}

    /* Please see man pages for details 
        

        
    */
    DateTime(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 millisecond=0);

    /* Please see man pages for details 
        

        

        
    */
    s32  GetYear() const;       

    /* Please see man pages for details 
        

        

        
    */
    s32 GetMonth() const;

    /* Please see man pages for details 
        

        

        
    */
    s32 GetDay() const;

    /* Please see man pages for details 
        

        

        
    */
    Week GetWeek() const;

    /* Please see man pages for details 
        

        

        
    */
    s32 GetHour() const;

    /* Please see man pages for details 
        

        

        
    */
    s32 GetMinute() const;

    /* Please see man pages for details 
        

        

        
    */
    s32 GetSecond() const;

    /* Please see man pages for details 
        

        

        
    */
    s32 GetMilliSecond() const;

    /* Please see man pages for details 
        

        
    */
    DateTimeParameters GetParameters() const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceYear(s32 year) const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceMonth(s32 month) const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceDay(s32 day) const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceHour(s32 hour) const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceMinute(s32 minute) const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceSecond(s32 second) const;

    /* Please see man pages for details 
        
        
    */
    DateTime ReplaceMilliSecond(s32 millisecond) const;

    /* Please see man pages for details 
        
    */
    friend bool operator==(const DateTime& lhs, const DateTime& rhs) { return lhs.m_MilliSeconds == rhs.m_MilliSeconds; }

    /* Please see man pages for details 
        
    */
    friend bool operator!=(const DateTime& lhs, const DateTime& rhs) { return !(lhs == rhs); }

    /* Please see man pages for details 
        
    */
    friend bool operator< (const DateTime& lhs, const DateTime& rhs) { return lhs.m_MilliSeconds <  rhs.m_MilliSeconds; }

    /* Please see man pages for details 
        
    */
    friend bool operator> (const DateTime& lhs, const DateTime& rhs) { return rhs < lhs; }

    /* Please see man pages for details 
        
    */
    friend bool operator<=(const DateTime& lhs, const DateTime& rhs) { return !(lhs > rhs); }

    /* Please see man pages for details 
        
    */
    friend bool operator>=(const DateTime& lhs, const DateTime& rhs) { return !(lhs < rhs); }

    /* Please see man pages for details 
        
    */
    DateTime& operator+=(const TimeSpan& rhs) { this->m_MilliSeconds += rhs.GetMilliSeconds(); return *this; }

    /* Please see man pages for details 
        
    */
    friend DateTime operator+(const DateTime& lhs, const TimeSpan& rhs) { DateTime ret(lhs); return ret += rhs; }
    
    /* Please see man pages for details 
        
    */
    DateTime& operator-=(const TimeSpan& rhs) { this->m_MilliSeconds -= rhs.GetMilliSeconds(); return *this; }

    /* Please see man pages for details 
        
    */
    friend DateTime operator-(const DateTime& lhs, const TimeSpan& rhs) { DateTime ret(lhs); return ret -= rhs; }

    /* Please see man pages for details 
        

        
        

        
    */
    friend TimeSpan operator-(const DateTime& lhs, const DateTime& rhs) { return TimeSpan::FromMilliSeconds(lhs.m_MilliSeconds - rhs.m_MilliSeconds); }

    /* Please see man pages for details 
        

        

        
        
        

        
        
        
        
        
        
        

        
    */
    static DateTime FromParameters(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 millisecond=0);

    /* Please see man pages for details 
        

        

        

        
        
        

        

        
    */
    static DateTime FromParameters(const DateTimeParameters &dateTimeParameters);

    /* Please see man pages for details 
        

        
        
        

        
    */
    static bool IsValidDate(s32 year, s32 month, s32 day);

    /* Please see man pages for details 
        

        

        
        
        
        
        
        
        

        
    */
    static bool IsValidParameters(s32 year, s32 month, s32 day, s32 hour=0, s32 minute=0, s32 second=0, s32 millisecond=0);

    /* Please see man pages for details 
        

        

        

        
    */
    static bool IsValidParameters(const DateTimeParameters &dateTimeParameters);

    /* Please see man pages for details 
        

        

        
    */
    static s32  IsLeapYear(s32 year);

    /* Please see man pages for details 
        

        
        
        

        

        
        
        
    */
    static s32  DateToDays(s32 year, s32 month, s32 day);

    /* Please see man pages for details 
        

        
        
        
        
    */
    static void DaysToDate(s32 *pYear, s32 *pMonth, s32 *pDay, s32 days);

    /* Please see man pages for details 
        

        

        
    */
    static Week DaysToWeekday(s32 days);

    /* Please see man pages for details 
        

        

        

        
        

        
        
        
        

        
        
    */
    static DateTime GetNow();

    /* Please see man pages for details 
        
    */
    static const DateTime MIN_DATETIME;

    /* Please see man pages for details 
        
    */
    static const DateTime MAX_DATETIME;

private:
    s64 m_MilliSeconds;

    DateTime(s64 milliseconds) : m_MilliSeconds(milliseconds) { NN_ASSERT(MIN_MILLISECONDS <= milliseconds && milliseconds <= MAX_MILLISECONDS); }

    static const s64 MIN_MILLISECONDS = -3155673600000LL;
    static const s64 MAX_MILLISECONDS = 5995900800000LL - 1;
};

} // namespace fnd {
} // namespace nn {

#endif // #ifdef __cplusplus

#endif //   #ifndef NN_FND_DATETIME_API_H_
