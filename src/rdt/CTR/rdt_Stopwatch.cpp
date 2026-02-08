/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rdt_Stopwatch.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "rdt_Stopwatch.h"

#include <nn/dbg.h>
#include <nn/os.h>
#include <nn/fnd.h>

#include <string.h>

#ifdef ENABLE_RDT_STOPWATCH

namespace
{

}  // End of anonymous namespace

namespace nn { namespace rdt { namespace CTR { namespace detail{


bool Stopwatch::s_initialized = false;
Stopwatch* Stopwatch::s_paStopwatches[MAX_STOPWATCHES];

void Stopwatch::Initialize(void)
{
    if(!s_initialized)
    {
        for(int i=0; i<MAX_STOPWATCHES; ++i)
        {
            s_paStopwatches[i] = NULL;
        }
        s_initialized = true;
    }
    else
    {
        return;  // Do nothing.
    }
}


void Stopwatch::Finalize(void)
{
    if(s_initialized)
    {
        s_initialized = false;
    }
    else
    {
        NN_LOG("Stopwatch is not initialized, but Finalized() called...\n");
        // Do nothing.
    }
}


// Reset contents of all stopwatches
void Stopwatch::ResetAll(void)
{
    for(int i=0; i<MAX_STOPWATCHES; ++i)
    {
        if(s_paStopwatches[i])
        {
            s_paStopwatches[i]->Reset();
        }
    }
}


// Display contents of all stopwatches
void Stopwatch::PrintAll(void)
{
    printHeadLine();
    for(int i=0; i<MAX_STOPWATCHES; ++i)
    {
        if(s_paStopwatches[i])
        {
            s_paStopwatches[i]->printContents();
        }
    }
}



Stopwatch::Stopwatch(void)
{
    if(!IsInitialized())
    {
        NN_LOG("Initialize Stopwatch...\n");
        Initialize();
    }

    bool ret = initInstance("(No name)");
    if(!ret)
    {
        NN_LOG("Failed to initInstance().\n");
    }
}


Stopwatch::Stopwatch(const char *name)
{
    NN_NULL_ASSERT(name);

    if(!IsInitialized())
    {
        NN_LOG("Initialize Stopwatch...\n");
        Initialize();
    }

    bool ret = initInstance(name);
    if(!ret)
    {
        NN_LOG("Failed to initInstance().\n");
    }
}


Stopwatch::~Stopwatch(void)
{
    removeFromList();
}


void Stopwatch::Stop(void)
{
    s64 diff = nn::os::Tick::GetSystemCurrent() - m_start;

    if(diff > m_max)
    {
        m_max = diff;
    }

    if(diff < m_min)
    {
        m_min = diff;
    }

    m_total += diff;

    ++m_times;
}


void Stopwatch::Print(void) const
{
    printHeadLine();
    printContents();
}


void Stopwatch::printHeadLine(void)
{
    nn::dbg::detail::Printf( "   Average,      Min,      Max,      Total,    Times,  Name   (Unit is usec)\n" );
}


void Stopwatch::printContents(void) const
{
    using nn::dbg::detail::Printf;

    if(m_times > 0)
    {
        // Display units in microseconds.
        s64  total = nnosTickConvertToMicroSeconds(m_total);
        s64  min   = nnosTickConvertToMicroSeconds(m_min);
        s64  max   = nnosTickConvertToMicroSeconds(m_max);
        f64  avg   = static_cast<f64>(total) / m_times;
        Printf( "%10.2llf, %8lld, %8lld, %10lld, %8d, \"%s\"\n", avg, min, max, total, m_times, m_name);
    }
    else if(m_times == 0)
    {
        Printf( "      ------     NO DATA     ------        %s\"\n", m_name);
    }
    else
    {
        NN_PANIC("m_times is negative! (%d)\n", m_times);
    }
}


bool Stopwatch::initInstance(const char *name)
{
    Reset();
    setName(name);
    return addToList();
}


// Register own instance in management list.
bool Stopwatch::addToList(void)
{
    for(int i=0; i<MAX_STOPWATCHES; ++i)
    {
        if(s_paStopwatches[i]==NULL)
        {
            s_paStopwatches[i] = this;
            return true;
        }
    }

    NN_PANIC("No space to addTo().  Too many Stopwatches...");
    return false;
}


// Delete own instance from management list.
void Stopwatch::removeFromList(void)
{
    for(int i=0; i<MAX_STOPWATCHES; ++i)
    {
        if(s_paStopwatches[i]==this)
        {
            s_paStopwatches[i] = NULL;
            return;
        }
    }

    NN_PANIC("Cannot find my instance!  Why?");
}


void Stopwatch::setName(const char *name)
{
    if(name)
    {
        strlcpy(m_name, name, sizeof(m_name));
    }
    else
    {
        strlcpy(m_name, "(NULL)", sizeof(m_name));
    }
}


bool Stopwatch::Test(void)
{
    Stopwatch::Initialize();

    Stopwatch sp("AAABBBCCC");

    for(int i=0; i<100; ++i)
    {
        sp.Start();
        nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(10));
        sp.Stop();
    }

    Stopwatch nanashi;

    nanashi.Start();
    nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMicroSeconds(50));
    nanashi.Stop();

    Stopwatch::PrintAll();

    Stopwatch::Finalize();

    return true;
}



}}}} // namespace nn::rdt::CTR::detail


#endif // end of ENABLE_RDT_STOPWATCH
