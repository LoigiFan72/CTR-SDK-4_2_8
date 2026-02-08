/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font_CmdCache.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_CTR_FONT_CMD_CACHE_H_
#define NN_FONT_CTR_FONT_CMD_CACHE_H_

#include <GLES2/gl2.h>
#include <nn/gx.h>

namespace nn {
namespace font {
namespace CTR {

//
//
class CmdCache
{
public:
                        CmdCache();

    void                Init(
                            void*   buffer,
                            u32     size,
                            bool    isCopy  = true);

    void                Use() const;

    void                Add(
                            const u32*  command,
                            u32         size);

    void                RoundUp(u8 align);

    void                Clear() { m_CmdBufferSize = 0; }

    void*               GetAddr() const     { return m_CmdBuffer; }

    GLsizei             GetSize() const     { return m_CmdBufferSize; }

    void                Dump(
                            bool    asF32           = false,
                            bool    showMnemonic    = false
                        ) const
#if !defined(NN_BUILD_NOOPT) && !defined(NN_BUILD_VERBOSE)
    {
        (void)asF32;
        (void)showMnemonic;
    }
#else
    ;
#endif

    static void         Dump(
                            const void* from,
                            const void* to,
                            bool    asF32           = false,
                            bool    showMnemonic    = false
                        )
#if !defined(NN_BUILD_NOOPT) && !defined(NN_BUILD_VERBOSE)
    {
        (void)from;
        (void)to;
        (void)asF32;
        (void)showMnemonic;
    }
#else
    ;
#endif

private:
    static void         DumpCommon(
                            const void* from,
                            const void* to,
                            bool asF32,
                            bool showMnemonic
                        );

    GLubyte*            m_CmdBuffer;
    GLsizei             m_CmdBufferSize;
    GLsizei             m_CmdMaxBufferSize;

    bool                m_IsCopy;
    NN_PADDING3;
};

}   // namespace CTR
}   // namespace font
}   // namespace nn

#endif //  NN_FONT_CTR_FONT_CMD_CACHE_H_
