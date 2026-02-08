/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Stopwatch.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_RDT_STOPWATCH_H_
#define NN_RDT_STOPWATCH_H_

#ifdef _WIN32
// Do not use the stopwatch in a Windows environment.
// Want to be able to use it once the build error problem is resolved.
#else
//  #define ENABLE_RDT_STOPWATCH
#endif


#ifdef ENABLE_RDT_STOPWATCH

#include <nn/os.h>

#include <limits.h>

namespace nn { namespace rdt { namespace CTR { namespace detail {

/* Please see man pages for details 
    
*/
class Stopwatch{
public:
    // Performs clearing of management region, etc. Even if Initialize function is not explicitly called,
    // it is appropriately called in the constructor.
    static void Initialize(void);

    // Clean up. Call when there is no intention to use Stopwatch.
    static void Finalize(void);

    // Initialized, useable state?
    static bool IsInitialized(void) { return s_initialized; }

    // Unnamed stopwatch.
    Stopwatch(void);

    // Named stopwatch. Up to 32 characters.
    explicit Stopwatch(const char *name);

    // Destructor Remove self from list.
    ~Stopwatch(void);

    // Start measuring
    void Start(void);

    // End measurement.
    void Stop(void);

    // How many times was measurement run?
    int  GetTimes(void) const;

    // Reset measured numeric value. Do not reset name given to stopwatch.
    void Reset(void);

    // Print stopwatch results on console.
    void Print(void) const;

    // Reset contents of all stopwatches
    static void ResetAll(void);

    // Display contents of all stopwatches
    static void PrintAll(void);

    // Single unit test.
    static bool Test(void);

private:
    // Constants
    static const int MAX_STOPWATCHES = 32;
    static const int MAX_NAME_LENGTH = 32;

    // Instance management list
    static Stopwatch *s_paStopwatches[MAX_STOPWATCHES];

    // Variable maintaining whether initialization completed.
    static bool s_initialized;

    // Instance initialization
    bool initInstance(const char *name);

    // Register own instance in management list.
    // Returns false when there is no space for registration.
    bool addToList(void);

    // Delete own instance from management list.
    void removeFromList(void);

    // Attach name. When NULL pointer is passed, the name "NULL" is set. 
    // 
    void setName(const char *name);

    // Display item name.
    static void printHeadLine(void);

    // Display content (measurement result).
    void printContents(void) const;

    // Total time.
    s64 m_total;

    // Tick when Start function was called
    s64 m_start;

    // Smallest of the measurements
    s64 m_min;

    // Largest of the measurements
    s64 m_max;

    // Number of measurements so far.
    s32 m_times;

    // Padding. Since this class includes the s64 format, 8-byte alignment is required.
    NN_PADDING4;

    // Name given to stopwatch.
    char m_name[MAX_NAME_LENGTH];
};


inline void Stopwatch::Start(void)
{
    m_start = nn::os::Tick::GetSystemCurrent();
}


inline int Stopwatch::GetTimes(void) const
{
    return m_times;
}


inline void Stopwatch::Reset(void)
{
    m_total = 0;
    m_start = 0;
    m_min   = LLONG_MAX;
    m_max   = 0;
    m_times = 0;
}


}}}} // namespace nn::rdt::CTR::detail

#else  // else of ENABLE_RDT_STOPWATCH

namespace nn { namespace rdt { namespace CTR { namespace detail {

class Stopwatch {
public:
    static void Initialize   (void)        {               }
    static void Finalize     (void)        {               }
    static bool IsInitialized(void)        { return false; }
    Stopwatch                (void)        {               }
    explicit Stopwatch       (const char*) {               }
    ~Stopwatch               (void)        {               }
    void Start               (void)        {               }
    void Stop                (void)        {               }
    int  GetTimes            (void) const  { return 0;     }
    void Reset               (void)        {               }
    void Print               (void) const  {               }
    static void ResetAll     (void)        {               }
    static void PrintAll     (void)        {               }
    static bool Test         (void)        { return false; }
};

}}}} // namespace nn::rdt::CTR::detail

#endif  // end of ENABLE_RDT_STOPWATCH

#endif  // end of NN_RDT_STOPWATCH_H_
