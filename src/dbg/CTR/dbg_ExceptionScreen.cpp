/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_ExceptionScreen.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49370 $
 *---------------------------------------------------------------------------*/

#include <nn/nstd.h>
#include <nn/os.h>
#include <nn/fs.h>
#include <nn/hid.h>
#include <nn/gx.h>
#include <nn/ro.h>
#include <nn/dbg.h>
#include <cwchar>
#include <cstring>

namespace nn { namespace dbg { namespace CTR {

    ExceptionScreen* ExceptionScreen::s_ExceptionScreen = NULL;

    namespace
    {
        bool IsCodeAddress(uptr addr)
        {
            const uptr begin = os::GetCodeRegionAddress();
            const uptr end   = begin + os::GetCodeRegionSize();
            const bool inStatic = ( (begin <= addr) && (addr < end) );

            if( inStatic )
            {
                return true;
            }

            if( nn::ro::detail::IsCodeAddress != NULL )
            {
                return nn::ro::detail::IsCodeAddress(addr);
            }
            else
            {
                return false;
            }
        }

        uptr FindThreadStackBottomByStackAddr(uptr addr)
        {
            if( os::ManagedThread::IsEnabled() )
            {
                // Use information from ManagedThread
                os::ManagedThread* pFound = os::ManagedThread::FindByStackAddress(addr);
                if( pFound != NULL )
                {
                    return pFound->GetStackBottom();
                }
            }

            // If not ManagedThread, then as is appropriate
            const uptr bottom = addr + 16 * 1024;

            // Save the main thread
            if( (addr < NN_OS_ADDR_STACK_END)
                && (NN_OS_ADDR_STACK_END < bottom) )
            {
                return NN_OS_ADDR_STACK_END;
            }

            return bottom;
        }

        void EscapeForPath(wchar_t* pOut, const wchar_t* pIn)
        {
            int i;
            for ( i = 0; i < sizeof(pIn) / sizeof(wchar_t) - 1; ++ i )
            {
                if ( pIn[ i ] == L'/' || pIn[ i ] == L' ' || pIn[ i ] == L':' )
                {
                    pOut[ i ] = L'_';
                }
                else if ( pIn[ i ] == L'\0' )
                {
                    break;
                }
                else
                {
                    pOut[ i ] = pIn[ i ];
                }
            }

            pOut[ i ] = L'\0';
        }

        bool IsArmBranchOperation(bit32 op)
        {
            return
                ( ((op & 0x0f000000) == 0x0b000000)     // BL command
               || ((op & 0xfe000000) == 0xfa000000)     // BLX(1) command
               || ((op & 0x0ffffff0) == 0x012fff30) );  // BLX(2) command
        }

        bool IsArmBranchOperationAddress(uptr opAddr)
        {
            if( IsCodeAddress(opAddr) )
            {
                // Check whether branch command
                bit32 op = *reinterpret_cast<bit32*>(opAddr);
                if( IsArmBranchOperation(op) )
                {
                    return true;
                }
            }

            return false;
        }

        bool IsThumbBranchOperationAddress(uptr opAddr)
        {
            if( IsCodeAddress(opAddr) )
            {
                // Check whether branch command
                bit16 op = *reinterpret_cast<bit16*>(opAddr);
                if ((op & 0xe800) == 0xe800)          // Second half of BL and BLX(1) commands
                {
                    uptr opAddr2 = opAddr - 2;

                    if( IsCodeAddress(opAddr2) )
                    {
                        bit16 op2 = *reinterpret_cast<bit16*>(opAddr2);
                        if ((op2 & 0xf800) == 0xf000)  // First half of BL and BLX(1) commands
                        {
                            return true;
                        }
                    }
                }
                else if ((op & 0xff87) == 0x4780) // BLX(2) command
                {
                    return true;
                }
            }

            return false;
        }

        bool IsSavedLrValue(bit32 data)
        {
            // Judges numerical values that may be program addresses.
            if ((data & 0x3) == 0)
            {
                // ARM code when LR is a multiple of 4
                // Gets the previous command, and checks whether the address is contained in the program region
                bit32 opAddr = data - 4;
                if( IsArmBranchOperationAddress(opAddr) )
                {
                    return true;
                }
            }
            else if ((data & 0x1) == 0x1)
            {
                // Thumb code when LR is odd
                // Gets the previous command, and checks whether the address is contained in the program region
                bit32 opAddr = (data & ~1) - 2;
                if( IsThumbBranchOperationAddress(opAddr) )
                {
                    return true;
                }
            }

            return false;
        }

        void WriteToSd(const char* msg, int length, const wchar_t* pBuildInfo, const wchar_t* pSuffix) NN_IS_UNUSED_VAR;
        void WriteToSd(const char* msg, int length, const wchar_t* pBuildInfo, const wchar_t* pSuffix)
        {
            wchar_t buildInfo[ExceptionScreen::MAX_BUILD_INFO_CHARS];

            EscapeForPath(buildInfo, pBuildInfo);

            wchar_t filepath[ 64 ];
            nn::nstd::TSNPrintf( filepath , 63 ,
                                 L"sdmc:/exception_%ls_%ls.log" ,
                                 buildInfo , pSuffix );
            filepath[ 63 ] = L'\0';

            nn::fs::FileOutputStream fs;

            nn::fs::MountSdmc();
            nn::Result result = fs.TryInitialize( filepath , true );
            if ( result.IsSuccess() )
            {
                fs.Write( msg , length, true );
                fs.Finalize();
            }
            nn::fs::Unmount( "sdmc:" );
        }

        bool PutHaltMessage(nn::dbg::DirectPrint* pdp,  const nn::math::VEC2& pos, const char* msg )
        {
            pdp->PutString( pos, msg );
            if ( pdp->GetLastCursorPos().y < 240 )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        void ClearMessage(nn::dbg::DirectPrint* pdp,  const nn::math::VEC2& pos, const char* msg )
        {
            nn::util::Color8 tmp = pdp->GetCharColor();
            pdp->SetCharColor( pdp->GetBgColor() );
            PutHaltMessage( pdp, pos, msg );
            pdp->SetCharColor( tmp );
        }

        void ShowWithAutoScroll(nn::dbg::DirectPrint* pdp, const char* msg)
        {
            nn::math::VEC2 pos( 0 , 0 );

            while( 1 )
            {
                bool ret = PutHaltMessage( pdp, pos, msg );

                // Flush
                pdp->Flush();

                // Wait.
                nn::os::Tick t = nn::os::Tick::GetSystemCurrent();
                while( t.ToTimeSpan().GetMilliSeconds() <
                    nn::os::Tick::GetSystemCurrent().ToTimeSpan().GetMilliSeconds() - 400 ) {}

                // Erases image in previous frame.
                ClearMessage( pdp, pos, msg );

                // Coordinate update.
                if ( !ret )
                {
                    pos.y -= DirectPrint::FONT_HEIGHT;
                }
                else
                {
                    pos.y = 0;
                    break;
                }
            }
        }

        void ShowWithManualScroll(nn::dbg::DirectPrint* pdp, const char* msg)
        {
            nn::hid::Initialize();
            nn::hid::PadReader pad;
            nn::hid::PadStatus status;

            nn::math::VEC2 pos( 0 , 0 );

            bool update = true;
            bool inDrawBox = false;

            for(;;)
            {
                if ( update )
                {
                    inDrawBox = PutHaltMessage( pdp, pos, msg );
                    // Flush
                    pdp->Flush();
                }

                update = false;

                // Wait.
                nn::os::Tick t = nn::os::Tick::GetSystemCurrent();
                while( t.ToTimeSpan().GetMilliSeconds() <
                    nn::os::Tick::GetSystemCurrent().ToTimeSpan().GetMilliSeconds() - 16 ){}

                // Moves position depending on input.
                if ( pad.ReadLatest( &status ) )
                {
                    if ( status.trigger & nn::hid::BUTTON_DOWN )
                    {
                        // Moves down.
                        if ( !inDrawBox )
                        {
                            // Erases image in previous frame.
                            ClearMessage( pdp, pos, msg );
                            // Coordinate movement.
                            pos.y -= DirectPrint::FONT_HEIGHT;
                            update = true;
                        }
                    }
                    else if ( status.trigger & nn::hid::BUTTON_UP )
                    {
                        // Moves up.
                        if ( pos.y <= -DirectPrint::FONT_HEIGHT )
                        {
                            // Erases image in previous frame.
                            ClearMessage( pdp, pos, msg );
                            // Coordinate movement.
                            pos.y += DirectPrint::FONT_HEIGHT;
                            update = true;
                        }
                    }
                    else if ( status.trigger & nn::hid::BUTTON_START )
                    {
                        break;
                    }
                }
            }
        }

        bool IsDeviceMemoryAddress(uptr addr)
        {
            size_t size = os::GetDeviceMemorySize();
            uptr begin  = os::GetDeviceMemoryAddress();
            uptr end    = begin + size;

            return (begin <= addr) && (addr < end);
        }

        void StealDisplaybuffer(nn::dbg::DirectPrint* pdp)
        {
            GLint format;
            GLint width;
            GLint height;
            GLint addr;

            nngxActiveDisplay( NN_GX_DISPLAY1 );
            nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &addr );
            nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_FORMAT,  &format);
            nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_WIDTH,   &width);
            nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_HEIGHT,  &height);

            if( IsDeviceMemoryAddress(addr) )
            {
                pdp->ChangeDisplaybuffer( reinterpret_cast< void* > (addr) ,
                                          format,
                                          nn::math::VEC2( height , width ) );
                nngxSwapBuffers( NN_GX_DISPLAY1 );
            }
            else
            {
                NN_TLOG_("DirectPrint: Current displaybuffer is not on DeviceMemory. So can't use it for the DirectPrint.\n");
            }
        }

        void WaitKeyCombination() NN_IS_UNUSED_FUNC;
        void WaitKeyCombination()
        {
            const int numKeyPatterns = 4;
            const bit32 keyPattern[ numKeyPatterns ] =
            {
                nn::hid::CTR::BUTTON_A ,
                nn::hid::CTR::BUTTON_B ,
                nn::hid::CTR::BUTTON_X ,
                nn::hid::CTR::BUTTON_Y ,
            };

            int index = 0;
            nn::hid::PadReader pad;
            nn::hid::PadStatus status;

            for(;;)
            {
                if ( pad.ReadLatest( &status ) && status.trigger != 0 )
                {
                    if ( status.trigger & keyPattern[ index ] )
                    {
                        ++ index;
                    }
                    else
                    {
                        index = 0;
                    }
                    if ( index == numKeyPatterns )
                    {
                        break;
                    }
                }

                nn::os::Tick t = nn::os::Tick::GetSystemCurrent();
                while ( t.ToTimeSpan().GetMilliSeconds() <
                    nn::os::Tick::GetSystemCurrent().ToTimeSpan().GetMilliSeconds() - 16 ) {}
            }
        }
    }

//------------------------------------------------------------------------------

void ExceptionScreen::Create( nn::fnd::IAllocator* allocator, bit32 option )
{
    NN_POINTER_TASSERT_(allocator);

    s_ExceptionScreen = new (allocator->Allocate(sizeof(*s_ExceptionScreen), 8)) ExceptionScreen(option);
    s_ExceptionScreen->RegisterHandler();
}
//------------------------------------------------------------------------------

ExceptionScreen::ExceptionScreen(bit32 option)
    : m_Option(option)
{
    std::memset( m_BuildInfo, 0, sizeof( m_BuildInfo ) );
    std::memset( m_Suffix,    0, sizeof( m_Suffix    ) );
    m_DirectPrint.SetFillSpace(false);
}

//------------------------------------------------------------------------------

ExceptionScreen::~ExceptionScreen()
{
}

//------------------------------------------------------------------------------

void ExceptionScreen::RegisterHandler()
{
    nn::os::ARM::SetUserExceptionHandler(
            ExceptionHandler,
            m_Stack.GetStackBottom() );
}

//------------------------------------------------------------------------------

s32 ExceptionScreen::PutBackTraceString(char* pOut, size_t size, uptr stackPtr, bit32 lr)
{
    NN_POINTER_TASSERT_(pOut);

    int pos = 0;
    const bit32* stack = reinterpret_cast< const bit32* > ( stackPtr );
    uptr stackBottom = FindThreadStackBottomByStackAddr(stackPtr);

    pos += nn::nstd::TSPrintf( pOut + pos , " back trace:\n" );
    pos += nn::nstd::TSPrintf( pOut + pos , "     lr   0x%08x\n", lr & ~1);

    // Outputs LR that is saved in stack
    if (stackBottom > 0)
    {
        const int end = (reinterpret_cast<const bit32*>(stackBottom) - stack);
        
        int count = 0; // Back traces to 10 items to avoid buffer overflow
        // Searches to bottom of stack
        for (int i = 0; i < end; i++)
        {
            const bit32 data = stack[i];

            if( IsSavedLrValue(data) )
            {
                pos += nn::nstd::TSNPrintf( pOut + pos , size - pos,
                        "  [0x%03x] 0x%08x\n", i * sizeof(bit32), data );
                ++ count;

                if( (count >= 10) || (pos >= size) )
                {
                    break;
                }
            }
        }
    }

    return pos;
}

//------------------------------------------------------------------------------

void ExceptionScreen::OnHalt( const char* msg )
{
    if( m_Option.IsSet(OPTION_WAIT_KEY) )
    {
        // Start displaying with button input
        // Display if the A, B, X, and Y buttons are pressed in this order
        WaitKeyCombination();
    }

    PrepareDisplaybufferImpl();

    // Automatic scroll.
    ShowWithAutoScroll(&m_DirectPrint, msg);

    // Manual scroll.
    ShowWithManualScroll(&m_DirectPrint, msg);
}


//------------------------------------------------------------------------------
#include <nn/hw/ARM/code32.h>
void ExceptionScreen::ExceptionHandler(nn::os::ARM::ExceptionInfo* pei, nn::os::ARM::ExceptionContext* pec)
{
    nn::os::Thread::ChangeCurrentPriority( 0 ); // Very high

    s_ExceptionScreen->ExceptionHandlerBody( pei , pec );

    NN_TPANIC_("exception handler end.");
}
#include <nn/hw/ARM/codereset.h>
void ExceptionScreen::HandleException(nn::os::ARM::ExceptionInfo* pei, nn::os::ARM::ExceptionContext* pec)
{
    s_ExceptionScreen->ExceptionHandlerBody( pei , pec );
}
void ExceptionScreen::ExceptionHandlerBody(nn::os::ARM::ExceptionInfo* pei, nn::os::ARM::ExceptionContext* pec)
{
    char buf[ 0x400 ] = {};
    int pos;
    int prevPos = 0;
    NN_UNUSED_VAR(prevPos);

    pos = nn::nstd::TSNPrintf( buf , sizeof(buf) ,
                               "Exception Occured.\n"
                               " type    : %d\n"
                               " fsr     : 0x%08x\n"
                               " far     : 0x%08x\n"
                               " fpexc   : 0x%08x\n"
                               " fpinst  : 0x%08x\n"
                               " fpinst2 : 0x%08x\n"
                               , pei->type.Get()
                               , pei->fsr
                               , pei->far
                               , pei->fpexc
                               , pei->fpinst
                               , pei->fpinst2
                               );
    NN_PUT(buf + prevPos, pos - prevPos);
    prevPos = pos;
    //====== Display information for exception

    for (int i = 0; i < 16; i++)
    {
        pos += nn::nstd::TSPrintf( buf + pos , " r%02d: 0x%08x\n", i, pec->r[i] );
        NN_PUT(buf + prevPos, pos - prevPos);
        prevPos = pos;
    }
    {
        pos += nn::nstd::TSPrintf( buf + pos , " cpsr: 0x%08x\n", pec->cpsr );
        NN_PUT(buf + prevPos, pos - prevPos);
        prevPos = pos;
    }

    //====== Display back trace
    {
        pos += PutBackTraceString(buf + pos, sizeof(buf) - pos, pec->r[13], pec->r[14]);
        NN_PUT(buf + prevPos, pos - prevPos);
        prevPos = pos;
    }

    if( m_Option.IsSet(OPTION_WRITE_TO_SD) )
    {
        WriteToSd(buf, pos, m_BuildInfo, m_Suffix);
    }

    //====== Call loop that displays information
    if( m_Option.IsSet(OPTION_DIRECT_PRINT) )
    {
        OnHalt(buf);
    }
}
//------------------------------------------------------------------------------

void ExceptionScreen::SetBuildInfoImpl( const wchar_t* pBuildInfo )
{
    std::wcsncpy( m_BuildInfo , pBuildInfo , sizeof(m_BuildInfo) / sizeof(wchar_t) - 1 );
    m_BuildInfo[ sizeof(m_BuildInfo) / sizeof(wchar_t) - 1 ] = L'\0';
}

void ExceptionScreen::SetSuffixImpl( const wchar_t* pSuffix )
{
    std::wcsncpy( m_Suffix , pSuffix , sizeof(m_Suffix) / sizeof(wchar_t) - 1 );
    m_Suffix[ sizeof(m_Suffix) / sizeof(wchar_t) - 1 ] = L'\0';
}
//------------------------------------------------------------------------------

void ExceptionScreen::PrepareDisplaybufferImpl()
{
    if (m_DirectPrint.GetDisplaybuffer() == NULL)
    {
        // If the display buffer is not explicitely specified
        // the current display buffer is used
        StealDisplaybuffer(&m_DirectPrint);
    }
    if (m_DirectPrint.GetDisplaybuffer() == NULL)
    {
        // If a display buffer hasn't been set to begin with
        // a newly prepared display buffer is selected
        AssignNewDisplaybuffer();
    }
}

void ExceptionScreen::AssignNewDisplaybuffer()
{
    NN_TLOG_("DirectPrint: Try to create new displaybuffer.\n");

    nngxActiveDisplay( NN_GX_DISPLAY1 );
    nngxGenDisplaybuffers( 1 , m_Display );
    nngxBindDisplaybuffer( m_Display[ 0 ] );
    nngxDisplaybufferStorage( GL_RGB565 , 240 , 320 , NN_GX_MEM_FCRAM );
    nngxDisplayEnv( 0 , 0 );
    nngxSwapBuffers( NN_GX_DISPLAY1 );

    GLint param;
    nngxGetDisplaybufferParameteri( NN_GX_DISPLAYBUFFER_ADDRESS , &param );

    m_DirectPrint.ChangeDisplaybuffer( reinterpret_cast< void* > ( param ) ,
                                      GL_RGB565 ,
                                      nn::math::VEC2( 320 , 240 ) );
}



}}}
