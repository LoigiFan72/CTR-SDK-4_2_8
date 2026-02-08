/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_TimeSpan.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47798 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

*/

#ifndef NN_FND_TIMESPAN_H_
#define NN_FND_TIMESPAN_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/os/os_HardwareParamsSelect.h>

#ifdef __cplusplus

namespace nn { namespace fnd {

/* Please see man pages for details 
    

    
    
           
           
           
           
           
*/
class TimeSpan
{
private:
    static const s64 TICKS_PER_SECOND = NN_HW_TICKS_PER_SECOND;
    
    typedef const class ZeroOnlyTag {} * ZeroOnly;
    
public:

//
//

    /* Please see man pages for details 
        
        
                      
                      
                      
        
        
    */
    TimeSpan(ZeroOnly zeroOnly = 0) : m_NanoSeconds(0) { NN_UNUSED_VAR(zeroOnly); }
    
    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromNanoSeconds(s64 nanoSeconds) { TimeSpan ret; ret.m_NanoSeconds = nanoSeconds; return ret; }
    
    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromMicroSeconds(s64 microSeconds) { return FromNanoSeconds(microSeconds * 1000); }
    
    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromMilliSeconds(s64 milliSeconds) { return FromNanoSeconds(milliSeconds * 1000 * 1000); }
    
    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromSeconds(s64 seconds) { return FromNanoSeconds(seconds * 1000 * 1000 * 1000); }

    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromMinutes(s64 minutes) { return FromNanoSeconds(minutes * 1000 * 1000 * 1000 * 60); }

    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromHours(s64 hours) { return FromNanoSeconds(hours * 1000 * 1000 * 1000 * 60 * 60); }

    /* Please see man pages for details 
    

    

    
    */
    static TimeSpan FromDays(s64 days) { return FromNanoSeconds(days * 1000 * 1000 * 1000 * 60 * 60 * 24); }

//

//
//

    /* Please see man pages for details 
    

    
    */
    s64 GetDays() const { return DivideNanoSeconds(0x683fff6f48f948e3LL, 45); }

    /* Please see man pages for details 
    

    
    */
    s64 GetHours() const { return DivideNanoSeconds(0x9c5fff26ed75ed55LL, 41); }

    /* Please see man pages for details 
    

    
    */
    s64 GetMinutes() const { return DivideNanoSeconds(0x12533fe68fd3d1dLL, 28); }

    /* Please see man pages for details 
    

    
    */
    s64 GetSeconds() const { return DivideNanoSeconds(0x112e0be826d694b3LL, 26); }

    /* Please see man pages for details 
    

    
    */
    s64 GetMilliSeconds() const { return DivideNanoSeconds(0x431bde82d7b634dbLL, 18); }

    /* Please see man pages for details 
    

    
    */
    s64 GetMicroSeconds() const { return DivideNanoSeconds(0x20c49ba5e353f7cfLL, 7); }

    /* Please see man pages for details 
    

    
    */
    s64 GetNanoSeconds() const { return m_NanoSeconds; }

//

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend bool operator==(const TimeSpan& lhs, const TimeSpan& rhs) { return lhs.m_NanoSeconds == rhs.m_NanoSeconds; }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend bool operator!=(const TimeSpan& lhs, const TimeSpan& rhs) { return !(lhs == rhs); }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend bool operator< (const TimeSpan& lhs, const TimeSpan& rhs) { return lhs.m_NanoSeconds <  rhs.m_NanoSeconds; }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend bool operator> (const TimeSpan& lhs, const TimeSpan& rhs) { return rhs < lhs; }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend bool operator<=(const TimeSpan& lhs, const TimeSpan& rhs) { return !(lhs > rhs); }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend bool operator>=(const TimeSpan& lhs, const TimeSpan& rhs) { return !(lhs < rhs); }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    TimeSpan& operator+=(const TimeSpan& rhs) { this->m_NanoSeconds += rhs.m_NanoSeconds; return *this; }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend TimeSpan operator+(const TimeSpan& lhs, const TimeSpan& rhs) { TimeSpan ret(lhs); return ret += rhs; }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    TimeSpan& operator-=(const TimeSpan& rhs) { this->m_NanoSeconds -= rhs.m_NanoSeconds; return *this; }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    friend TimeSpan operator-(const TimeSpan& lhs, const TimeSpan& rhs) { TimeSpan ret(lhs); return ret -= rhs; }

private:
    s64     m_NanoSeconds;

private:
    s64 DivideNanoSeconds(const s64 magic, const s32 rightShift) const
    {
        s64 n = MultiplyRightShift(m_NanoSeconds, magic);
        if (magic < 0)
        {
            n += m_NanoSeconds;
        }
        n >>= rightShift;
        return n + (static_cast<u64>(m_NanoSeconds) >> 63);
    }

    static s64 MultiplyRightShift(const s64 x, const s64 y)
    {
        const u64 x_lo = x & 0xffffffff;
        const s64 x_hi = x >> 32;

        const u64 y_lo = y & 0xffffffff;
        const s64 y_hi = y >> 32;

        const s64 z = x_hi * y_lo + ((x_lo * y_lo) >> 32);
        const s64 z_lo = z & 0xffffffff;
        const s64 z_hi = z >> 32;

        return x_hi * y_hi + z_hi + (static_cast<s64>(x_lo * y_hi + z_lo) >> 32);
    }
};

}}	// end of namespace nn

#endif // __cplusplus

#endif
