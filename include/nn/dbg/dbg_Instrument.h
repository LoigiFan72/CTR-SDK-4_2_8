/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Instrument.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/
/* Please see man pages for details 
    



*/

#ifndef DBG_INSTRUMENT_H_
#define DBG_INSTRUMENT_H_

#ifdef __cplusplus

namespace nn {
namespace dbg {
namespace CTR {

    enum InstrumentType
    {
        TRACE_STACK   = (0<<0), // Stack mode
        TRACE_LOG     = (1<<0), // Log mode
        RECORD_TICK   = (1<<1), // Also record tick
        RING_BUFFER   = (1<<2)  // Ring buffer
    };

    //================================================================
    // Record measurement 1
    //================================================================
    // When also record tick
    struct RecordForLogWithTick
    {
        u32 mAddress; //Use least significant bit in 0==in, 1==out
        u32 mCall;
        s64 mTick;
    };

    // When not recording tick
    struct RecordForLog
    {
        u32 mAddress;
        u32 mCall;
    };

    //================================================================
    // Measurement class
    //================================================================
    /* Please see man pages for details 
        
    */
    class Instrument
    {
        friend class Statistics;
    public:
        Instrument() : mIsAvailable(false)
        {
        }
        /* Please see man pages for details 
          
        */
        void Initialize( void* buffer, size_t bufferSize, s32 type=TRACE_STACK );
        /* Please see man pages for details 
          
        */
        void Finalize( void );

        /* Please see man pages for details 
          
        */
        void Dump( void );
        /* Please see man pages for details 
          
        */
        void Clear( void );

        /* Please see man pages for details 
          
        */
        void Enable( void );
        /* Please see man pages for details 
          
        */
        void Disable( void );

        /* Please see man pages for details 
          
        */
        static void SetLogFunction( void (*logFunc)( const char*, ... ) );

        /* Please see man pages for details 
          
        */
        inline size_t GetRecordSize(void)
        {
            return (mType & RECORD_TICK)? sizeof(RecordForLogWithTick): sizeof(RecordForLog);
        }
        inline bool IsRingBuffer(void)
        {
            return (mType & RING_BUFFER);
        }
        inline bool IsRecordTick(void)
        {
            return (mType & RECORD_TICK);
        }
        inline bool IsTraceLog(void)
        {
            return (mType & TRACE_LOG);
        }

        inline int GetBufferCount(void)
        {
            return mBufferCount;
        }
        inline int GetEntryCount(void)
        {
            return mCount;
        }

        // for internal
        static Instrument* SearchInfo( bit32 threadId );
        void EntryFunc( void *func_address, void *call_site );
        void ExitFunc( void *func_address, void *call_site );

    private:
        static void AddToList( Instrument* pInfo );
        static void DeleteFromList( Instrument* pInfo );
        bool  IsBottom_BufferPtr( void* p );
        void* Inc_BufferPtr( void* p );
        void* Dec_BufferPtr( void* p );

        bit32 mThreadId;
        int   mCount;

        void* mBufferTop;
        void* mBufferBottom;
        int   mBufferSize;

        void* mBufferOrigin;
        void* mBufferPtr;

        int   mBufferCount;

        Instrument* mNext;

        s32   mType;
        bool  mIsAvailable;
        NN_PADDING3;
    };

    //================================================================
    // 1 item of the total
    //================================================================
    struct StatisticsRecord
    {
        u32  mAddress;
        int  mEntryCount;
        int  mTickCount;
        NN_PADDING4;
        s64  mTickStart;
        s64  mTickSum;
    };

    //================================================================
    // Totals
    //================================================================
    /* Please see man pages for details 
        
    */
    class Statistics
    {
    public:
        /* Please see man pages for details 
          
        */
        void Initialize( void* buffer=NULL, size_t bufferSize=0 );
        /* Please see man pages for details 
          
        */
        void Collect( Instrument* info, bool isClear=true );

        /* Please see man pages for details 
          
        */
        void Dump( bool isArrangeTick=true );
        /* Please see man pages for details 
          
        */
        void Clear(void);

        /* Please see man pages for details 
          
        */
        static void SetLogFunction( void (*logFunc)( const char*, ... ) );

        /* Please see man pages for details 
          
        */
        int GetIgnoredLines(void)
        {
            return mIgnoredLines;
        }

    private:
        StatisticsRecord*  mBuffer;
        size_t mBufferSize;
        void*  mBufferBottom;

        int    mIgnoredLines;
    };

} // namespace CTR
} // namespace dbg
} // namespace nn

#endif // __cplusplus

#define NN_DBG_TRACE_STACK      (nn::dbg::CTR::TRACE_STACK)
#define NN_DBG_TRACE_LOG        (nn::dbg::CTR::TRACE_LOG)
#define NN_DBG_RECORD_TICK      (nn::dbg::CTR::RECORD_TICK)
#define NN_DBG_RING_BUFFER      (nn::dbg::CTR::RING_BUFFER)

//================================================================================
// Call function for GCC format measurements
//================================================================================
#ifdef __cplusplus
extern "C"{
#endif

NN_WEAK_SYMBOL void __cyg_profile_func_enter( void *func_address, void *call_site )
    __attribute__ ((no_instrument_function));

NN_WEAK_SYMBOL void __cyg_profile_func_exit ( void *func_address, void *call_site )
    __attribute__ ((no_instrument_function));

#ifdef __cplusplus
}
#endif

#endif  // DBG_INSTRUMENT_H_

