/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Default.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48011 $
 *---------------------------------------------------------------------------*/

#include <nn/Result.h>
#include <nn/math.h>
#include <nn/dbg.h>
#include <nn/dbg/dbg_Default.h>
#include <nn/init.h>

using namespace nn::dbg;


namespace nn { namespace dbg {

    namespace
    {
        template <typename T>
        inline T Replace(T& var, T v)
        {
            T old = var;
            var = v;
            return old;
        }

        void HandleBreak(nn::dbg::BreakReason reason, nn::Result* pResult,
                    const char* filename, int lineno, const char* fmt, std::va_list args) NN_IS_UNUSED_FUNC;
        void HandleBreak(nn::dbg::BreakReason reason, nn::Result* pResult,
                    const char* filename, int lineno, const char* fmt, std::va_list args)
        {
            ExceptionScreen::PrepareDisplaybuffer();

            // Wait one frame
            os::Thread::Sleep(fnd::TimeSpan::FromMilliSeconds(20));

            DirectPrint* pdp = ExceptionScreen::GetDirectPrint();

            math::VEC2 pos(0, 0);

            pdp->SetFillSpace(true);

            switch(reason)
            {
            case BREAK_REASON_PANIC:    pdp->Printf(pos, "Panic!"); break;
            case BREAK_REASON_ASSERT:   pdp->Printf(pos, "Assertion failed"); break;
            case BREAK_REASON_USER:     pdp->Printf(pos, "User Break"); break;
            default:                    pdp->Printf(pos, "unknown break reason %d", reason); break;
            }
            pos.x += DirectPrint::FONT_WIDTH;
            pos.y += DirectPrint::FONT_HEIGHT;

            if( pResult != NULL )
            {
                pdp->Printf(pos, "%-13s 0x%08X", "Result:", pResult->GetPrintableBits());
                pos.y += DirectPrint::FONT_HEIGHT;
            }
            if( filename != NULL )
            {
                pdp->Printf(pos, true, true, "%-13s %s(%d)", "File(Line):", filename, lineno);
                pos.y += DirectPrint::FONT_HEIGHT;
            }
            if( fmt != NULL )
            {
                pdp->Printf(pos, "Message:");
                pos.x += DirectPrint::FONT_WIDTH * 2;
                pos.y += DirectPrint::FONT_HEIGHT;

                pdp->Printf(pos, "----");
                pos.y += DirectPrint::FONT_HEIGHT;

                const f32 prevX = Replace(pos.x, 0.f);
                pdp->VPrintf(pos, fmt, args);
                pos.x = prevX;
                pos.y = pdp->GetLastCursorPos().y + DirectPrint::FONT_HEIGHT;

                pdp->Printf(pos, "----");
                pos.y += DirectPrint::FONT_HEIGHT;
            }

            pos.x = 0;
            pdp->Printf(pos, "stop.");
            pdp->Flush();
        }
    }

    void SetDefaultExceptionHandler()
    {
#if NN_PLATFORM_HAS_MMU
    #if ! defined(NN_HARDWARE_CTR_LEGACY)
        nn::dbg::ExceptionScreen::Create(init::GetAllocator());
    #endif
#endif  // if NN_PLATFORM_HAS_MMU
    }

    void SetDefaultBreakHandler()
    {
#if NN_PLATFORM_HAS_MMU
    #if ! defined(NN_HARDWARE_CTR_LEGACY)
        nn::dbg::SetBreakHandler(&HandleBreak);
    #endif
#endif  // if NN_PLATFORM_HAS_MMU
    }

}}
