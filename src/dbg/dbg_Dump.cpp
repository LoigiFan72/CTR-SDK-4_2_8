/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_Dump.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/nstd.h>
#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Dump.h>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>

/****************************************************************************/
namespace nn {
namespace dbg {
namespace detail {
    void DumpMemory(const void* p, size_t size, bit32 flags)
    {
        char buffer[80];
        char bufferString[16 + 1];
        int  bufPos;
        int  memPos;
        uptr address;

        if (flags & NN_DBG_DUMP_FLAG_POINTER)
        {
            address = reinterpret_cast<uptr>(p);
        }
        else
        {
            address = 0;
        }

        detail::PutString("\n");
        {
            bufPos = 0;
            bufPos += nstd::TSPrintf(buffer, "            0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
            if (flags & NN_DBG_DUMP_FLAG_STRING)
            {
                bufPos += nstd::TSPrintf(&buffer[bufPos], "  0123456789abcdef");
            }
            bufPos += nstd::TSPrintf(&buffer[bufPos], "\n");
            detail::PutString(buffer, bufPos);
        }

        for(memPos = 0; size > 0; address += 0x10)
        {
            bufPos = 0;
            bufPos += nstd::TSPrintf(buffer, "%08x: ", address & static_cast<uptr>(~0xf));
            {
                int col = 0;

                if (flags & NN_DBG_DUMP_FLAG_POINTER && memPos == 0)
                {
                    for(; (address & 0xf) != col; ++col)
                    {
                        std::strcat(buffer, "   ");
                        bufPos += 3;

                        bufferString[col] = ' ';
                    }
                }
                for(; col < 0x10 && size > 0; ++col, --size, ++memPos)
                {
                    u8 val = reinterpret_cast<const u8*>(p)[memPos];
                    bufPos += nstd::TSPrintf(&buffer[bufPos], " %02x", val);
                    if (std::isprint(val))
                    {
                        bufferString[col] = val;
                    }
                    else
                    {
                        bufferString[col] = '.';
                    }
                }
                for(; col < 0x10 ; ++col)
                {
                    std::strcat(buffer, "   ");
                    bufPos += 3;

                    bufferString[col] = ' ';
                }
                bufferString[col] = '\0';
            }
            if (flags & NN_DBG_DUMP_FLAG_STRING)
            {
                bufPos += nstd::TSPrintf(&buffer[bufPos], "  %s", bufferString);
            }

            std::strcat(buffer, "\n");
            detail::PutString(buffer);
        }
    }

}  // namespace detail
}  // namespace dbg
}  // namespace nn

void nndbgDetailDumpMemory(const void* p, size_t size, bit32 flags)
{
    nn::dbg::detail::DumpMemory(p, size, flags);
}
