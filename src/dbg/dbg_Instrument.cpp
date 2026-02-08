/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Instrument.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn.h>
#include <nn/dbg/dbg_Instrument.h>

#include <cstdio>
#include <cstdarg>
#include <cstring>


namespace
{
    #define NN_DBG_INS_PRINTF_BUFFER_LENGTH   1024

    void ins_VPrintf(const char* fmt, va_list arg)
    {
        char buf[NN_DBG_INS_PRINTF_BUFFER_LENGTH];
        int length = ::std::vsnprintf(buf, sizeof(buf), fmt, arg);
        if (length >= NN_DBG_INS_PRINTF_BUFFER_LENGTH)
        {
            length = NN_DBG_INS_PRINTF_BUFFER_LENGTH - 1;   // need not count \0 of tail end
        }
        NN_PUT(buf, length);
    }
    void ins_Printf(const char* fmt, ...)
    {
        va_list vlist;

        va_start(vlist, fmt);
        ins_VPrintf(fmt, vlist);
        va_end(vlist);
    }

    // Critical section for process exclusion
    nn::os::CriticalSection sCriticalSection = nn::WithInitialize();

    // Measurement: List
    nn::dbg::CTR::Instrument* sListHead = NULL;

    // Measurement: function for output
    void (*sLogFuncForInstrument)( const char*, ... ) = ins_Printf;

    // Statistic: function for output
    void (*sLogFuncForStatistics)( const char*, ... ) = ins_Printf;
}

namespace nn {
namespace dbg {
namespace CTR {

    //================================================================
    // Measurement
    //================================================================
    // Add to list
    void Instrument::AddToList( Instrument* pInfo )
    {
        if ( ! sListHead )
        {
            sListHead = pInfo;
        }
        else
        {
            Instrument* p = sListHead;
            while( p->mNext )
            {
                p = p->mNext;
            }
            p->mNext = pInfo;
        }

        pInfo->mNext = NULL;
    }

    // Delete from the list
    void Instrument::DeleteFromList( Instrument* pInfo )
    {
        Instrument* p = sListHead;
        Instrument* prev = NULL;
        while(p)
        {
            if ( p == pInfo )
            {
                if ( prev )
                {
                    prev->mNext = p->mNext;
                }
                else
                {
                    sListHead = p->mNext;
                }
                break;
            }
            prev = p;
            p++;
        }
    }

    // Search by thread ID
    Instrument* Instrument::SearchInfo( bit32 threadId )
    {
        Instrument* p = sListHead;
        while( p && p->mThreadId != threadId )
        {
            p = p->mNext;
        }
        return p;
    }

    // Pointer operation function: in final position?
    bool Instrument::IsBottom_BufferPtr( void* p )
    {
        p = reinterpret_cast<u8*>(p) + GetRecordSize();
        return ( p >= mBufferBottom )? true: false;
    }
    // Pointer operation function: advance one
    void* Instrument::Inc_BufferPtr( void* p )
    {
        p = reinterpret_cast<u8*>(p) + GetRecordSize();
        if ( p >= mBufferBottom )
        {
            p = mBufferTop;
        }
        return p;
    }
    // Pointer operation function: go back one
    void* Instrument::Dec_BufferPtr( void* p )
    {
        p = reinterpret_cast<u8*>(p) - GetRecordSize();
        if ( p < mBufferTop )
        {
            p = reinterpret_cast<u8*>(mBufferBottom) - GetRecordSize();
        }
        return p;
    }

    // Initialization
    void Instrument::Initialize( void* pBuffer, size_t bufferSize, s32 type )
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);
        bit32 id = nn::os::Thread::GetCurrentId();

        // Check if already registered
        if ( SearchInfo( id ) )
        {
            return;
        }

        mThreadId = id;
        mCount = 0;
        mType = type;

        // Ring mode and stack mode are not possible
        if ( IsRingBuffer() && ! IsTraceLog() )
        {
            return;
        }

        u32 size1 = GetRecordSize();
        mBufferSize = (bufferSize / size1) * size1;
        mBufferTop    = (bufferSize>0)? pBuffer: NULL;
        mBufferBottom = (bufferSize>0)? (reinterpret_cast<u8*>(mBufferTop) + mBufferSize): NULL;

        // Clear
        Clear();

        // Add to the list
        AddToList( this );
    }

    // End processing
    void Instrument::Finalize(void)
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);

        // Delete from the list
        DeleteFromList( this );
    }

    // Clear buffer
    void Instrument::Clear(void)
    {
        mBufferOrigin = mBufferTop;
        mBufferPtr    = mBufferTop;
        mBufferCount = 0;
    }

    // Enable measurement
    void Instrument::Enable( void )
    {
        mIsAvailable = true;
    }

    // Disable measurement
    void Instrument::Disable( void )
    {
        mIsAvailable = false;
    }

    // Measurement Entry
    void Instrument::EntryFunc( void *func_address, void *call_site )
    {
        if ( ! mIsAvailable )
        {
            return;
        }

        // Number of times called
        mCount++;
        mBufferCount++;

        // No buffer set
        if ( ! mBufferTop || ! mBufferPtr )
        {
            return;
        }

        // Record with system tick
        if ( IsRecordTick() )
        {
            RecordForLogWithTick* p = reinterpret_cast<RecordForLogWithTick*>(mBufferPtr);
            p->mAddress = reinterpret_cast<u32>(func_address) & 0xfffffffe;
            p->mCall    = reinterpret_cast<u32>(call_site);
            p->mTick    = nn::os::Tick::GetSystemCurrent();
        }
        // Record without system tick
        else
        {
            RecordForLog* p = reinterpret_cast<RecordForLog*>(mBufferPtr);
            p->mAddress = reinterpret_cast<u32>(func_address);
            p->mCall    = reinterpret_cast<u32>(call_site);
        }

        // Next pointer
        mBufferPtr = Inc_BufferPtr( mBufferPtr );
        if ( mBufferPtr == mBufferOrigin )
        {
            if ( IsRingBuffer() )
            {
                mBufferOrigin = Inc_BufferPtr( mBufferOrigin );
            }
            else
            {
                mBufferPtr = NULL;
            }
        }
    }

    // Measurement Exit
    void Instrument::ExitFunc( void *func_address, void *call_site )
    {
        NN_UNUSED_VAR( func_address );
        NN_UNUSED_VAR( call_site );
        if ( ! mIsAvailable )
        {
            return;
        }

        // No buffer set
        if ( ! mBufferTop || ! mBufferPtr )
        {
            return;
        }

        // Log mode
        if ( IsTraceLog() )
        {
            // Only when recording with system tick
            if ( IsRecordTick() )
            {
                RecordForLogWithTick* p = reinterpret_cast<RecordForLogWithTick*>(mBufferPtr);
                p->mAddress = (reinterpret_cast<u32>(func_address) & 0xfffffffe) | 0x1;
                p->mCall    = reinterpret_cast<u32>(call_site);
                p->mTick    = nn::os::Tick::GetSystemCurrent();

                // Next pointer
                mBufferPtr = Inc_BufferPtr( mBufferPtr );
                if ( mBufferPtr == mBufferOrigin )
                {
                    if ( IsRingBuffer() )
                    {
                        mBufferOrigin = Inc_BufferPtr( mBufferOrigin );
                    }
                    else
                    {
                        mBufferPtr = NULL;
                    }
                }
            }
        }
        // Stack mode
        else
        {
            if ( mBufferPtr != mBufferOrigin )
            {
                mBufferPtr = reinterpret_cast<u8*>(mBufferPtr) - GetRecordSize();
            }
        }
    }

    // Output function configuration
    void Instrument::SetLogFunction( void (*logFunc)( const char*, ... ) )
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);
        sLogFuncForInstrument = logFunc;
    }

    // Result output
    void Instrument::Dump( void )
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);

        // No buffer set
        if ( ! mBufferTop )
        {
            return;
        }

        sLogFuncForInstrument("count: %d\n", mCount );
        // Record with system tick
        if ( IsRecordTick() )
        {
            RecordForLogWithTick* p = reinterpret_cast<RecordForLogWithTick*>(mBufferOrigin);

            while( p != mBufferPtr )
            {
                if ( p->mAddress & 1 )
                {
                    sLogFuncForInstrument("func: %08x out                   tick: %llx\n", p->mAddress & 0xfffffffe, p->mTick);
                }
                else
                {
                    sLogFuncForInstrument("func: %08x in  caller: %08x  tick: %llx\n", p->mAddress & 0xfffffffe, p->mCall, p->mTick);
                }
                if ( ! IsRingBuffer() && IsBottom_BufferPtr(p) )
                {
                    break;
                }
                p = reinterpret_cast<RecordForLogWithTick*>(Inc_BufferPtr(p));
            }
        }
        // Record without system tick
        else
        {
            RecordForLog* p = reinterpret_cast<RecordForLog*>(mBufferOrigin);

            while( p != mBufferPtr )
            {
                sLogFuncForInstrument("func: %08x caller: %08x\n", p->mAddress, p->mCall);
                if ( ! IsRingBuffer() && IsBottom_BufferPtr(p) )
                {
                    break;
                }
                p = reinterpret_cast<RecordForLog*>(Inc_BufferPtr(p));
            }
        }
        sLogFuncForInstrument("\n");
    }

    //================================================================
    // Statistic
    //================================================================
    // Subroutine for output: align digits
    static f32 arrangeTick( f32 tick )
    {
        return
            ( tick > 1000000.f ) ? (tick / 1000000.f) :
            ( tick > 1000.f )    ? (tick / 1000.f)    :
            tick;
    }
    // Subroutine for output: units when aligning digits
    static const char* arrangeTickUnit( f32 tick )
    {
        return
            ( tick > 1000000.f ) ? "s " :
            ( tick > 1000.f )    ? "ms" :
            "us";
    }

    // Initialization
    void Statistics::Initialize( void* buffer, size_t bufferSize )
    {
        size_t size1 = sizeof(StatisticsRecord);

        // Buffer information
        mBuffer = reinterpret_cast<StatisticsRecord*>(buffer);
        mBufferSize = (bufferSize / size1) * size1;
        mBufferBottom = (mBuffer && bufferSize>0)? (reinterpret_cast<u8*>(mBuffer) + mBufferSize): NULL;

        Clear();
    }

    // Totals
    void Statistics::Collect( Instrument* pInfo, bool isClear )
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);
        if ( ! mBuffer )
        {
            return;
        }

        // Check each item of the measurement buffer
        RecordForLogWithTick* pRecord = reinterpret_cast<RecordForLogWithTick*>(pInfo->mBufferOrigin);
        while( pRecord != pInfo->mBufferPtr )
        {
            //NN_LOG("pRecord=%x pInfo->mBufferPtr=%x ring=%d bottom=%x\n", pRecord, pInfo->mBufferPtr, pInfo->IsRingBuffer(), pInfo->mBufferBottom );
            // exit line when there is time measurement
            if ( pInfo->IsRecordTick() && (pRecord->mAddress & 1) )
            {
                StatisticsRecord* p = mBuffer;
                while( p<mBufferBottom )
                {
                    if ( (pRecord->mAddress & 0xfffffffe) == p->mAddress )
                    {
                        // When there is entry
                        if ( p->mTickStart )
                        {
                            p->mTickSum += (pRecord->mTick - p->mTickStart);
                            p->mTickStart = 0;
                            p->mTickCount++;
                            break;
                        }
                    }
                    p++;
                }
            }
            // entry line with time measurement or entry line without time measurement
            else
            {
                // Search if already exists
                bool isFound = false;
                StatisticsRecord* pBlank = NULL;
                StatisticsRecord* p = mBuffer;
                while( p<mBufferBottom )
                {
                    if ( ! p->mAddress && ! pBlank )
                    {
                        pBlank = p;
                    }
                    // Update record since the address of the record in question exists
                    else if ( pRecord->mAddress == p->mAddress )
                    {
                        p->mEntryCount++;
                        p->mTickStart = pRecord->mTick;
                        isFound = true;
                        break;
                    }
                    p++;
                }

                // Did not find
                if ( ! isFound )
                {
                    //Register new since there is a space
                    if ( pBlank )
                    {
                        pBlank->mAddress = pRecord->mAddress;
                        pBlank->mEntryCount = 1;
                        pBlank->mTickCount = 0;
                        pBlank->mTickStart = pRecord->mTick;
                        pBlank->mTickSum = 0;
                    }
                    //Since there is no space, record that there was an ignored line
                    else
                    {
                        mIgnoredLines++;
                    }
                }
            }

            // Did it scan to the end for a normal buffer?
            if ( ! pInfo->IsRingBuffer() && ( reinterpret_cast<u8*>(pRecord) + pInfo->GetRecordSize() >= pInfo->mBufferBottom ) )
            {
                    break;
            }

            // Next record
            pRecord = reinterpret_cast<RecordForLogWithTick*>(pInfo->Inc_BufferPtr( pRecord ));
        }

        // Clear measurement buffer content
        if ( isClear )
        {
            pInfo->Clear();
        }
    }

    // information display
    void Statistics::Dump( bool isArrangeTick )
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);
        StatisticsRecord* p = mBuffer;
        if ( ! p )
        {
            return;
        }
        while( p<mBufferBottom )
        {
            if ( p->mAddress )
            {
                f32 sumMicroSec = p->mTickSum / (nn::os::Tick::TICKS_PER_SECOND / (1000.f * 1000.f));
                u32 ave = p->mTickSum / p->mTickCount;
                f32 aveMicroSec = ave / (nn::os::Tick::TICKS_PER_SECOND / (1000.f * 1000.f));

                if ( isArrangeTick )
                {
                    sLogFuncForStatistics( "func: %08x  count:%8d (%8d) sum: %10.2f %s (ave: %10.2f %s)\n",
                                           p->mAddress, p->mEntryCount, p->mTickCount,
                                           arrangeTick(sumMicroSec),
                                           arrangeTickUnit(sumMicroSec),
                                           arrangeTick(aveMicroSec),
                                           arrangeTickUnit(aveMicroSec) );
                }
                else
                {
                    sLogFuncForStatistics( "func: %08x  count:%8d (%8d) sum: %10.2f us (ave: %10.2f us)\n",
                                           p->mAddress, p->mEntryCount, p->mTickCount,
                                           sumMicroSec, aveMicroSec );
                }
            }
            p++;
        }
        sLogFuncForStatistics("\n");
    }
    // Discard information
    void Statistics::Clear(void)
    {
        StatisticsRecord* p = mBuffer;
        if ( ! p )
        {
            return;
        }
        while( p<mBufferBottom )
        {
            p->mAddress = NULL;
            p->mEntryCount = 0;
            p->mTickCount = 0;
            p->mTickSum = 0;
            p->mTickStart = 0;
            p++;
        }

        mIgnoredLines = 0;
    }

    // Output function setting
    void Statistics::SetLogFunction( void (*logFunc)( const char*, ... ) )
    {
        nn::os::CriticalSection::ScopedLock lock(sCriticalSection);
        sLogFuncForStatistics = logFunc;
    }
}

//================================================================================
// Call function for GCC format measurements
//================================================================================
extern "C"{

#ifdef NN_BUILD_VERBOSE
NN_WEAK_SYMBOL void __cyg_profile_func_enter( void *func_address, void *call_site )
{
    nn::dbg::CTR::Instrument* pInfo = nn::dbg::CTR::Instrument::SearchInfo( nn::os::Thread::GetCurrentId() );
    if ( pInfo )
    {
        pInfo->EntryFunc( func_address, call_site );
    }
}


NN_WEAK_SYMBOL void __cyg_profile_func_exit ( void *func_address, void *call_site )
{
    nn::dbg::CTR::Instrument* pInfo = nn::dbg::CTR::Instrument::SearchInfo( nn::os::Thread::GetCurrentId() );
    if ( pInfo )
    {
        pInfo->ExitFunc( func_address, call_site );
    }
}

#else

NN_WEAK_SYMBOL void __cyg_profile_func_enter( void *func_address, void *call_site )
{
    NN_UNUSED_VAR( func_address );
    NN_UNUSED_VAR( call_site );
    // Do nothing
}
NN_WEAK_SYMBOL void __cyg_profile_func_exit ( void *func_address, void *call_site )
{
    NN_UNUSED_VAR( func_address );
    NN_UNUSED_VAR( call_site );
    // Do nothing
}

#endif

} // namespace CTR
} // namespace dbg
} // namespace nn
