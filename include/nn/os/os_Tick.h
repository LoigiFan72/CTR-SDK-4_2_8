/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_Tick.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47819 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_OS_OS_TICK_H_
#define NN_OS_OS_TICK_H_

#include <nn/svc.h>
#include <nn/os/os_HardwareParamsSelect.h>
#include <nn/fnd/fnd_TimeSpan.h>
#include <nn/math/math_Misccellaneous.h>

#ifdef __cplusplus

namespace nn { namespace os {

/* Please see man pages for details 
    

    

           
           
           

           
           

           
           

           
           
*/
class Tick
{
public:
    /* Please see man pages for details 
        
    */
    static const s64 TICKS_PER_SECOND  = NN_HW_TICKS_PER_SECOND;

public:

//
//

    /* Please see man pages for details 
        

        
    */
    explicit Tick(s64 tick = 0) : m_Tick(tick) {}

    /* Please see man pages for details 
        

        
    */
    Tick(nn::fnd::TimeSpan span);

    /* Please see man pages for details 
        

        
    */
    static Tick GetSystemCurrent();

//

//
//

    /* Please see man pages for details 
        
    */
    operator s64() const { return m_Tick; }

    /* Please see man pages for details 
        
    */
    operator nn::fnd::TimeSpan() const;

    /* Please see man pages for details 
        

        
    */
    nn::fnd::TimeSpan ToTimeSpan() const;

//

//
//

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    Tick& operator-=(Tick rhs);

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    Tick operator-(Tick rhs) const;

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    Tick& operator+=(Tick rhs);

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    Tick operator+(Tick rhs) const;

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    Tick& operator+=(fnd::TimeSpan rhs);

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //----------------------------------------------------------------------
    Tick operator+(fnd::TimeSpan rhs) const;

//

//
//

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    s64 ToNanoSeconds() const;

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    s64 ToMicroSeconds() const;

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    s64 ToMilliSeconds() const;

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    s64 ToSeconds() const;

//

private:
    s64 m_Tick;
};


inline Tick Tick::GetSystemCurrent()
{
    return Tick(nn::svc::GetSystemTick());
}

inline Tick::Tick(nn::fnd::TimeSpan span)
    : m_Tick( nnmathMultiplyRate32(
                span.GetNanoSeconds(),
                math::MakeRate32<TICKS_PER_SECOND, 1000 * 1000 * 1000>::VALUE) )
{
}

inline Tick::operator nn::fnd::TimeSpan() const
{
    return nn::fnd::TimeSpan::FromNanoSeconds(
        nnmathMultiplyRate(
            m_Tick,
            math::MakeRate<1000 * 1000 * 1000, TICKS_PER_SECOND>::VALUE ));
}

inline nn::fnd::TimeSpan Tick::ToTimeSpan() const
{
    return *this;
}

inline Tick& Tick::operator+=(fnd::TimeSpan rhs)
{
    const s64 tick = nnmathMultiplyRate32(
                        rhs.GetNanoSeconds(),
                        math::MakeRate32<TICKS_PER_SECOND, 1000 * 1000 * 1000>::VALUE );
    this->m_Tick += tick;
    return *this;
}

inline Tick& Tick::operator-=(Tick rhs)               { this->m_Tick -= rhs.m_Tick; return *this; }
inline Tick  Tick::operator-(Tick rhs)          const { Tick ret(*this); return ret -= rhs; }
inline Tick& Tick::operator+=(Tick rhs)               { this->m_Tick += rhs.m_Tick; return *this; }
inline Tick  Tick::operator+(Tick rhs)          const { Tick ret(*this); return ret += rhs; }
inline Tick  Tick::operator+(fnd::TimeSpan rhs) const { Tick ret(*this); return ret += rhs; }

inline s64 Tick::ToNanoSeconds() const
{
    return nnmathMultiplyRate(
                m_Tick,
                math::MakeRate<1000 * 1000 * 1000, TICKS_PER_SECOND>::VALUE );
}
inline s64 Tick::ToMicroSeconds() const
{
    return nnmathMultiplyRate32(
                m_Tick,
                math::MakeRate32<1000 * 1000, TICKS_PER_SECOND>::VALUE );
}
inline s64 Tick::ToMilliSeconds() const
{
    return nnmathMultiplyRate32(
                m_Tick,
                math::MakeRate32<1000, TICKS_PER_SECOND>::VALUE );
}
inline s64 Tick::ToSeconds() const
{
    return nnmathMultiplyRate32(
                m_Tick,
                math::MakeRate32<1, TICKS_PER_SECOND>::VALUE );
}

}}

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
  
  

  

  

  
*/

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertFromNanoSeconds(s64 ns)
{
    return nnmathMultiplyRate32(ns, nnmathMakeRate32(NN_HW_TICKS_PER_SECOND, 1000 * 1000 * 1000));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertFromMicroSeconds(s64 us)
{
    return nnmathMultiplyRate(us, nnmathMakeRate(NN_HW_TICKS_PER_SECOND, 1000 * 1000));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertFromMilliSeconds(s64  ms)
{
    return nnmathMultiplyRate(ms, nnmathMakeRate(NN_HW_TICKS_PER_SECOND, 1000));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertFromSeconds(s64 s)
{
    return nnmathMultiplyRate(s, nnmathMakeRate(NN_HW_TICKS_PER_SECOND, 1));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertToNanoSeconds(s64 tick)
{
    return nnmathMultiplyRate(tick, nnmathMakeRate(1000 * 1000 * 1000, NN_HW_TICKS_PER_SECOND));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertToMicroSeconds(s64 tick)
{
    return nnmathMultiplyRate32(tick, nnmathMakeRate32(1000 * 1000, NN_HW_TICKS_PER_SECOND));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertToMilliSeconds(s64 tick)
{
    return nnmathMultiplyRate32(tick, nnmathMakeRate32(1000, NN_HW_TICKS_PER_SECOND));
}

/* Please see man pages for details 
    

    

    
*/
NN_EXTERN_C inline s64 nnosTickConvertToSeconds(s64 tick)
{
    return nnmathMultiplyRate32(tick, nnmathMakeRate32(1, NN_HW_TICKS_PER_SECOND));
}

/* Please see man pages for details 
  
*/
NN_EXTERN_C s64 nnosTickGetSystemCurrent(void);

/*  



*/

#endif /* NN_OS_OS_TICK_H_ */
